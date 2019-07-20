#include<bits/stdc++.h>
using namespace std;
class Inventery
{
private:
    char p_id[3],p_name[20],p_shelf[3],p_price[3],p_amount[3],p_type[20],buf [45];

public:
    void read()
    {
        cout<<"p_id : ";
        cin>>p_id;
        cout<<"p_name : ";
        cin>>p_name;
        cout<<"p_shelf : ";
        cin>>p_shelf;
        cout<<"p_price : ";
        cin>>p_price;
        cout<<"p_amount : ";
        cin>>p_amount;
        cout<<"p_type : ";
        cin>>p_type;
    }
    void insert(fstream &ofile)
    {
        read();
        strcpy(buf,"");
        strcat(buf,p_id);
        strcat(buf,"|");
        strcat(buf,p_name);
        strcat(buf,"|");
        strcat(buf,p_shelf);
        strcat(buf,"|");
        strcat(buf,p_price);
        strcat(buf,"|");
        strcat(buf,p_amount);
        strcat(buf,"|");
        strcat(buf,p_type);
        strcat(buf,"|");
        strcat(buf,"\n");
        ofile.write(buf,strlen(buf));
    }
    void display (fstream &ifile)
    {
        char extra[45];
        while(!ifile.eof())
        {
            ifile.getline(p_id,3,'|');
            ifile.getline(p_name,20,'|');
            ifile.getline(p_shelf,3,'|');
            ifile.getline(p_price,3,'|');
            ifile.getline(p_amount,3,'|');
            ifile.getline(p_type,20,'|');
            ifile.getline(extra,45,'\n');
            cout<<p_id<<"\t";
            cout<<p_name<<"\t";
            cout<<p_shelf<<"\t";
            cout<<p_price<<"\t";
            cout<<p_amount<<"\t";
            cout<<p_type<<"\n";
        }
    }
    int search(fstream &ifile,char key[])
    {
        char extra[45];
        while(!ifile.eof())
        {
            ifile.getline(p_id,3,'|');
            ifile.getline(p_name,20,'|');
            ifile.getline(p_shelf,3,'|');
            ifile.getline(p_price,3,'|');
            ifile.getline(p_amount,3,'|');
            ifile.getline(p_type,20,'|');
            ifile.getline(extra,45,'\n');
            if(strcmp(p_name,key)==0)
           {
                cout<<"record found and details are:"<<endl;
                cout<<"ID : "<<p_id<<endl;
                cout<<"name : "<<p_name<<endl;
                cout<<"Shelf : "<<p_shelf<<endl;
                cout<<"Price : "<<p_price<<endl;
                cout<<"Amount : "<<p_amount<<endl;
                cout<<"Type : "<<p_type<<endl;
                return 1;
            }
        }
        return 0;
    }
    void update (fstream &ifile,char key[])
    {
        Inventery s[10];
        char extra[50];
        int i=0;
        while(!ifile.eof())
        {
            ifile.getline(s[i].p_id,3,'|');
            ifile.getline(s[i].p_name,20,'|');
            ifile.getline(s[i].p_shelf,3,'|');
            ifile.getline(s[i].p_price,3,'|');
            ifile.getline(s[i].p_amount,3,'|');
            ifile.getline(s[i].p_type,20,'|');
            ifile.getline(extra,45,'\n');
            i++;
        }
        ifile.close();
        int flag=0;
        for(int j=0; j<i; j++)
        {
            if(strcmp(key,s[j].p_name)==0)
            {
                flag=1;
                cout<<"record found details are : "<<endl;
                cout<<s[j].p_id<<endl;
                cout<<s[j].p_name<<endl;
                cout<<s[j].p_shelf<<endl;
                cout<<s[j].p_price<<endl;
                cout<<s[j].p_amount<<endl;
                cout<<s[j].p_type<<endl;
                cout<<"enter the modification details"<<endl;
                cout<<"enter the id : ";
                cin>>s[j].p_id;
                cout<<"enter the name : ";
                cin>>s[j].p_name;
                cout<<"enter the shelf : ";
                cin>>s[j].p_shelf;
                cout<<"enter the price : ";
                cin>>s[j].p_price;
                cout<<"enter the amount : ";
                cin>>s[j].p_amount;
                cout<<"enter the type : ";
                cin>>s[j].p_type;
            }
        }
        if(flag==0)
        {
            cout<<"Record not found\n";
            return;
        }
        ifile.open("inventery.txt",ios::out|ios::trunc);

        cout<<"i = "<<i <<endl;

        for(int k=0; k<i; k++)
        {
            strcpy(buf,"");
            strcat(buf,s[k].p_id);
            strcat(buf,"|");
            strcat(buf,s[k].p_name);
            strcat(buf,"|");
            strcat(buf,s[k].p_shelf);
            strcat(buf,"|");
            strcat(buf,s[k].p_price);
            strcat(buf,"|");
            strcat(buf,s[k].p_amount);
            strcat(buf,"|");
            strcat(buf,s[k].p_type);
            strcat(buf,"|");
            strcat(buf,"\n");
            ifile.write(buf,strlen(buf));
        }
    }
    void Delete (fstream &ifile,char key[])
    {
        Inventery s[10];
        char extra[50];
        int i=0;
        while(!ifile.eof())
        {
            ifile.getline(s[i].p_id,3,'|');
            ifile.getline(s[i].p_name,20,'|');
            ifile.getline(s[i].p_shelf,3,'|');
            ifile.getline(s[i].p_price,3,'|');
            ifile.getline(s[i].p_amount,3,'|');
            ifile.getline(s[i].p_type,20,'|');
            ifile.getline(extra,45,'\n');
            i++;
        }
        ifile.close();
        int flag=0;
        int d;
        for(int j=0; j<i; j++)
        {
            if(strcmp(key,s[j].p_name)==0)
            {
                flag=1;
                d=j;
            }
        }
        if(flag==0)
        {
            cout<<"Record not found\n";
            return;
        }
        ifile.open("inventery.txt",ios::out|ios::trunc);

        cout<<"i = "<<i <<endl;
        for(int k=d;k<i;k++){
          s[k]=s[k+1];
        }
        i--;
        for(int k=0; k<i; k++)
        {
            strcpy(buf,"");
            strcat(buf,s[k].p_id);
            strcat(buf,"|");
            strcat(buf,s[k].p_name);
            strcat(buf,"|");
            strcat(buf,s[k].p_shelf);
            strcat(buf,"|");
            strcat(buf,s[k].p_price);
            strcat(buf,"|");
            strcat(buf,s[k].p_amount);
            strcat(buf,"|");
            strcat(buf,s[k].p_type);
            strcat(buf,"|");
            strcat(buf,"\n");
            ifile.write(buf,strlen(buf));
        }
    }
};
int main()
{
    int n,i,ch;
    char key[10];
    Inventery inv;
    fstream ifile,ofile;
    ofile.open("inventery.txt",ios::trunc|ios::app);
    ofile.close();
    for(;;)
    {
        system("cls");
        cout<<"1.insert\n2.display\n3.search\n4.modify\n5.exit\n";
        cout<<"enter your choice : ";
        cin>>ch;
        switch(ch)
        {
        case 1:
        {
            fstream ofile;
            ofile.open("inventery.txt",ios::out|ios::app);
            cout<<"enter the no. of product : ";
            cin>>n;
            for(i=0; i<n; i++)
            {
                inv.insert(ofile);
            }
            ofile.close();
            break;
        }
        case 2:
        {
            fstream infile;
            infile.open("inventery.txt",ios::in);
            inv.display(infile);
            system("pause");
            infile.close();
            break;
        }
        case 3:
        {
            cout<<"enter the record name to be searched : ";
            cin>>key;
            fstream ifile;
            ifile.open("inventery.txt",ios::in);
            if(inv.search(ifile,key)==0)
                cout<<"\nrecord not found\n";
            system("pause");
            ifile.close();
            break;
        }
        case 4:
        {
            fstream iofile;
            iofile.open("inventery.txt",ios::in|ios::out);
            cout<<"enter the record name to be modified : ";
            cin>>key;
            inv.update(iofile,key);
            system("pause");
            iofile.close();
            break;
        }
        case 5:
        {
            fstream iofile;
            iofile.open("inventery.txt",ios::in|ios::out);
            cout<<"enter the record name to be modified : ";
            cin>>key;
            inv.Delete(iofile,key);
            system("pause");
            iofile.close();
            break;
        }
        default:
            return 0;
        }
    }
    return 0;
}
