#include<bits/stdc++.h>
using namespace std;

class person
{
private:
    char name[80];              //person’s name
    short age;                  //person’s age
public:
    static int personCount();
    friend istream& operator >> (istream& in, person& p);
    friend ostream& operator << (ostream& out, person& p) ;
    void diskOut() const;            //write to file
    void diskIn(int);          //read from file
    void showData()const ;            //display person’s data
    string get_name(){return name;}
};

int person::personCount()          //return number of persons
{
    //in file
    ifstream infile;
    infile.open("PERSFILE.DAT");
    infile.seekg(0, ios::end);    //go to 0 bytes from end
    //calculate number of persons
    return (int)infile.tellg() / sizeof(person);
} ////////////////////////////////////////////////////////////////

istream& operator >> (istream& in, person& p)              //get person’s data
{
    cout << "Enter name: ";
    in >> p.name;
    cout << "Enter age: ";
    in >> p.age;
    return in;
}///------------------------------------------------------------

ostream& operator << (ostream& out, person& p)
{
    out.setf(ios::left);
    out <<"|"<< setw(10) << p.name << "|" << setw(4) << p.age << "|\n";
    return out;
}///------------------------------------------------------------

void person::diskOut() const           //write person to end of file
{
    ofstream outfile;             //make stream
    //open it
    outfile.open("PERSFILE.DAT", ios::app|ios::binary );
    outfile.write( (char*)this, sizeof(*this) ); //write to it
} ///-------------------------------------------------------------

void person::diskIn(int i)
{
    ifstream infile;                           //make stream
    infile.open("PERSFILE.DAT");  //open it
    infile.seekg( i*sizeof(person) );         //move file ptr
    infile.read( (char*)this, sizeof(*this) ); //read one person
}///---------------------------------------------------------------
void person::showData()const             //display person’s data
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileOperation
{

private:
    person p;
    void head()const;
public:

    void pack();
    void unpack();
    int search(char key[]);
    void Modify(char key[]);
    void Delete(char key[]);

};
void FileOperation::head() const
{
    cout.setf(ios::left);
    cout<<"+----------+----+\n";
    cout<<"|"<<setw(10)<<"Name"<<"|"<<setw(4)<<"AGE"<<"|\n";
    cout<<"+----------+----+\n";
}

void FileOperation::pack()
{
    char ch;
    do
    {
        cin>>p;
        p.diskOut();
        cout << "Do another (y/n)? "<<endl;
        cin >> ch;
    }
    while(ch=='y');
}

void FileOperation::unpack()
{
    int n=person::personCount();
    head();
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        cout<<p;
    }
    cout<<"+----------+----+\n";
}

int FileOperation::search(char key[])
{
    int n=person::personCount();
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        string name=p.get_name();
        if(strcmp(name.c_str(),key)==0 )
        {
            cout<<"found\n";
            p.showData() ;
            return i;
        }
    }
    return -1;
}


void FileOperation::Delete(char Key[])
{
    int n=person::personCount();
    vector<person> vp;
    int f=search(Key);
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        if(f!=i)
            vp.push_back(p);
    }
    ofstream outfile;
    outfile.open("PERSFILE.DAT", ios::binary );
    for(int i=0;i<vp.size();i++)
        outfile.write( (char*)&vp[i], sizeof(person) );
}
void FileOperation::Modify(char Key[])
{
    int n=person::personCount();
    vector<person> vp;
    int f=search(Key);
    if(f==-1){cout<<"Not FOUND \n"  ; return;  }
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        if(f!=i)
            vp.push_back(p);
        else
            cin>>p, vp.push_back(p);
    }
    ofstream outfile;
    outfile.open("PERSFILE.DAT", ios::binary );
    for(int i=0;i<vp.size();i++)
        outfile.write( (char*)&vp[i], sizeof(person) );
}
int main()
{
    FileOperation o;
    while(true)
    {
        cout<<"1.Insert\n2.Show All\n3.Search\n4.modify\n5.Delete\n6.Exit\n";
        cout<<"Enter your choice: ";
        int ch;
        cin>>ch;
        switch(ch)
        {
        case 1:
        {
            o.pack();
            break;
        }
        case 2:
        {
            o.unpack();
            break;
        }
        case 3:{
            char key[80];
            cout<<"Enter name to search :: ";
            cin>>key;
            if(!o.search(key))cout<<"Not Found\n";
            break;
        }
        case 4:{
            char key[80];
            cout<<"Enter name to Modify :: ";
            cin>>key;
            o.Modify(key);
            break;
        }
        case 5:{
            char key[80];
            cin>>key;
            cout<<"Enter name to Delete :: ";
            o.Delete(key);
            break;
        }
        default:
            exit(0);
        }
    }
}
