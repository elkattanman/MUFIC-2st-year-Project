#include<bits/stdc++.h>
using namespace std;
#define PraisesTOAllah return 0;

void head()
{
    cout.setf(ios::left);
    cout<<"\n+----+----------+------+------+--------+------+\n";
    cout <<"|"<< setw(4) << "ID" << "|" << setw(10) << "Name"<< "|" << setw(6) << "Amount" << "|"
              <<setw(6) << "Price" << "|" <<setw(8) << "Type" << "|" << setw(6) << "Sh_Num" << "|\n";
    cout<<"+----+----------+------+------+--------+------+\n";
}

class inventory
{
protected:
    short id;
    char name[30];
    int amount;
    double price;
    char type[20];
    short shelf_number;
public:
    static int inventoryCount();
    friend istream& operator >> (istream& in, inventory& p);
    friend ostream& operator << (ostream& out, inventory& p) ;
    void diskOut() const;            //write to file
    void diskIn(int);          //read from file
    short get_id(){ return id; }
    void set_id(short i) { id=i; }
};
int inventory::inventoryCount()          //return number of inventorys
{
    //in file
    ifstream infile;
    infile.open("PRODFILE.DAT",ios::app);
    infile.seekg(0, ios::end);    //go to 0 bytes from end
    //calculate number of inventorys
    return (int)infile.tellg() / sizeof(inventory);
} ////////////////////////////////////////////////////////////////

istream& operator >> (istream& in, inventory& p)              //get inventory�s data
{
    cout << "Enter Product_Name: ";
    in >> p.name;
    cout << "Enter Product_Amount: ";
    in >> p.amount;
    cout << "Enter Price: ";
    in >> p.price;
    cout << "Enter Type_of_Product: ";
    in >> p.type;
    cout << "Enter Shelf_Number: ";
    in >> p.shelf_number;
    return in;
}///------------------------------------------------------------

ostream& operator << (ostream& out, inventory& p)
{
    out.setf(ios::left);
    out <<"|"<< setw(4) << p.id << "|" << setw(10) << p.name << "|" << setw(6) << p.amount<< "|"
             <<setw(6) << p.price << "|" <<setw(8) << p.type << "|" << setw(6) << p.shelf_number << "|\n";
    return out;
}///------------------------------------------------------------

void inventory::diskOut() const           //write inventory to end of file
{
    ofstream outfile;             //make stream
    //open it
    outfile.open("PRODFILE.DAT", ios::app|ios::binary );
    outfile.write( (char*)this, sizeof(inventory) ); //write to it
} ///-------------------------------------------------------------

void inventory::diskIn(int i)
{
    ifstream infile;                           //make stream
    infile.open("PRODFILE.DAT",ios::app);  //open it
    if(infile){
        infile.seekg( i*sizeof(inventory) );         //move file ptr
        infile.read( (char*)this, sizeof(*this) ); //read one inventory
    }else
        cout<<"file not Found";
}///---------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileOperation
{
private:
    inventory p;
public:
    void pack();   ///insert
    void unpack();  ///read
    int search(short key);
    void Modify(short key);
    void Delete(short key);
};


void FileOperation::pack()
{
    int id;
    char ch='y';
    do
    {
        cout << "Enter Product_ID: ";
        cin>>id;
        int f=search(id);
        if( f==-1){
            cin>>p;
            p.set_id(id);
            p.diskOut();
        }
        else{
            cout<<p.get_id()<<" ID Exist\n";
            continue;
        }
        cout << "Do another (y/n)? "<<endl;
        cin >> ch;
    }
    while(ch=='y');
}

void FileOperation::unpack()
{
    int n=inventory::inventoryCount();
    head();
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        cout<<p;
    }
    cout<<"+----+----------+------+------+--------+------+\n";
}

int FileOperation::search(short key)
{
    int n=inventory::inventoryCount();
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        if(p.get_id() == key )
        {
            return i;
        }
    }
    return -1;
}


void FileOperation::Delete(short Key)
{
    int n=inventory::inventoryCount();
    vector<inventory> vp;
    int f=search(Key);
    if(f==-1)
        return;
    for( int i=0 ; i<n ; ++i )
    {
        p.diskIn(i);
        if(f!=i)
            vp.push_back(p);
    }
    ofstream outfile;
    outfile.open("PRODFILE.DAT", ios::binary );

    for(int i=0;i<vp.size();i++)
        outfile.write( (char*)&vp[i], sizeof(inventory) );
}

void FileOperation::Modify(short Key)
{
    int n=inventory::inventoryCount();
    vector<inventory> vp;
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
    outfile.open("PRODFILE.DAT", ios::binary );
    for(int i=0;i<vp.size();i++)
        outfile.write( (char*)&vp[i], sizeof(inventory) );
}
int main()
{
    system("color fc");
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
            short key;
            cout<<"Enter ID to search :: ";
            cin>>key;
            int f=o.search(key);
            head();
            if(f==-1)
                cout<<"|------------Record Not Found---------------|\n";
            else{
                inventory p;
                p.diskIn(f);
                cout<<p;
                cout<<"+----+----------+------+------+--------+------+\n";
            }
            break;
        }
        case 4:{
            short key;
            cout<<"Enter ID to Modify :: ";
            cin>>key;
            o.Modify(key);
            break;
        }
        case 5:{
            short key;
            cout<<"Enter ID to Delete :: ";
            cin>>key;
            o.Delete(key);
            break;
        }
        default:
            exit(0);
        }
        system("pause");
        system("cls");
    }
    PraisesTOAllah
}
