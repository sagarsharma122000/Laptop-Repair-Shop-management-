#include<iostream>
#include<fstream>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class account_query
{
private:
    char id_number[20];
    char name[10];
    char pName[10];
    float total_Balance;
    long long int phn;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void account_query::read_data()
{
	cout<<"\nEnter ID Number: ";
    cin>>id_number;
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter the Phone Number: ";
    cin>>phn;
    cout<<"Enter Product Name: ";
    cin>>pName;
    cout<<"Enter Balance: ";
    cin>>total_Balance;
    cout<<endl;
}
void account_query::show_data()
{
    cout<<"ID Number: "<<id_number<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Phone Number: "<<phn<<endl;
    cout<<"Product Name: "<<pName<<endl;
    cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
}
void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.txt",ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.txt");
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n************************************************Data from file****************************************************"<<endl;
    cout<<"********************************************************************************************************************"<<endl;
	while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.txt");
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.txt", ios::in);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    char c;
    cout<<"Do You Want to edit this record(Y/N) : ";
    cin>>c;
    if(c=='y' || c=='Y')
    {
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"****************************************Record "<<n<<" has following data*********************************************"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.txt", ios::out|ios::in);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\n******************************************Enter data to Modify*************************************************** "<<endl;
    cout<<"******************************************************************************************************************"<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"*******************************************Data Edit Successfully**************************************************"<<endl<<endl;
    }
	else
	{
		cout<<"Thank You ";
	}
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.txt");
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.txt", ios::out);
    infile.seekg(0);
    char z;
    cout<<"Do You Want to delete this record(Y/N) : ";
    cin>>z;
    if(z=='y' || z=='Y')
    {
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.txt");
    rename("tmpfile.txt", "record.txt");
    cout<<"*******************************************Record deleted successfully**************************************************"<<endl;
	}
	else
	{
		cout<<"Thank You ";
	}
}
int main()
{
    account_query A;
    int choice;
    cout<<"************************************************COMPUTER SHOP MANAGEMENT*********************************************"<<endl;
    cout<<"*********************************************************************************************************************"<<endl;
	while(true)
    {
        cout<<"                                            Select one option below ";
        cout<<"\n                                       \t1-->Add record to file";
        cout<<"\n                                       \t2-->Show record from file";
        cout<<"\n                                       \t3-->Search Record from file";
        cout<<"\n                                       \t4-->Update Record";
        cout<<"\n                                       \t5-->Delete Record";
        cout<<"\n                                       \t6-->Quit";
        cout<<"\n\n                                      Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
