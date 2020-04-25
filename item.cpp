#include<iostream>
#include<direct.h>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<process.h>
#include<stdlib.h>
using namespace std;
class Item
{
  private:
  int no;
  int qty;
  int prc;
  char name[10];

  public:
  void EntData();
  void DispData();
  void Storeitem();
  void Readitem();
  void Searchitem();
  void Deleteitem();
  int getno()
  {
    return no;
  }
}s1;

void Item::EntData()
{
  cout<<"\n\nEnter the item name:";
  fflush(stdin);
  cin.getline(name,10);
  cout<<"\nEnter the item number:";
  cin>>no;
  cout<<"\nEnter the price:";
  cin>>prc;
  cout<<"\nEnter the quantity:";
  cin>>qty;
}

void Item::DispData()
{
  cout<<"\n\nItem Name:"<<name;
  cout<<"\nItem No.:"<<no;
  cout<<"\nQuantity:"<<qty;
  cout<<"\nPrice:"<<prc;
}

void Item::Storeitem()
{
  ofstream fout;
  fout.open("ifile.txt",ios::app|ios::binary);
  fout.write((char*)&s1,sizeof(s1));
  fout.close();
}

void Item::Readitem()
{
  ifstream fin;
  fin.open("ifile.txt",ios::in|ios::binary);
  if(!fin)
  {
    cout<<"\nFile Not Found!";
    return;
  }
  fin.read((char*)&s1,sizeof(s1));
  while(!fin.eof())
  {
   DispData();
   fin.read((char*)&s1,sizeof(s1));
  }
  fin.close();
}

void Item::Searchitem()
{
  int ino;
  char found='n';
  ifstream fin;
  fin.open("ifile.txt",ios::in|ios::binary);
  if(!fin)
  {
    cout<<"File Not Found!";
    return;
  }
  cout<<"Enter the item number to be searched for:";
  cin>>ino;
  while(!fin.eof())
  {
    fin.read((char*)&s1,sizeof(s1));
    if(s1.getno()==ino)
    {
      s1.DispData();
      found='y';
      break;
    }
  }
  if(found=='n')
  {
    cout<<"\nItem number not found in a file!"<<endl;
  }
  fin.close();
}

void Item::Deleteitem()
{
  int ino;
  cout<<"\nEnter the item number:";
  cin>>ino;
  ifstream fin;
  fin.open("ifile.txt",ios::in|ios::binary);
  ofstream fout;
  fout.open("tempfile.txt",ios::out|ios::binary);
  if(!fin)
  {
    cout<<"\nFile Not found!";
    return;
  }
  fin.seekg(0,ios::beg);
  while(fin.read((char*)&s1,sizeof(Item)))
  {
    if(s1.getno()!=ino)
    {
      fout.write((char*)&s1,sizeof(Item));
    }
  }
  fin.close();
  fout.close();
  remove("ifile.txt");
  rename("tempfile.txt","ifile.txt");
  cout<<"\nRecord Deleted!";
}

int main()
{
  int ch;
  char c='n';
  label:
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tMain Menu:";
  cout<<"\n\n\t\t\t1.Enter new Data";
  cout<<"\n\t\t\t2.View Data";
  cout<<"\n\t\t\t3.Search Data";
  cout<<"\n\t\t\t4.Delete Data";
  cout<<"\n\t\t\t5.Exit";
  cout<<"\n\n\t\t\tEnter your choice:";
  cin>>ch;
  if(ch==1)
  {
    do
    {
      system("cls"); 
      s1.EntData();
      s1.Storeitem();
      system("cls");
      cout<<"\nThe Data Entered by you is:-";
      s1.DispData();
      cout<<"\nDo you want to insert some more records?(y/n):";
      cin>>c;
    }while(c=='y'||c=='Y');
    if(c=='n'||c=='N')
    {
      goto label;
    }
  }

  else if(ch==2)
  {
    system("cls");
    s1.Readitem();
    cout<<"\n\n\t\t\t\t\tPlease enter any key to go back to Main Menu!";
    getch();
    goto label;
  }

  else if(ch==3)
  {
    do
    {
      system("cls");
      s1.Searchitem();
      cout<<"\nDo you want to search for some more records?(y/n)";
      cin>>c;
    }while(c=='y'||c=='Y');
    if(c=='n'||c=='N')
    {
      goto label;
    }
  }

  else if(ch==4)
  {
    do
    {
      system("cls");
      s1.Deleteitem();
      cout<<"\nDo you want to delete any more records?(y/n):";
      cin>>c;
    }while(c=='y'||c=='Y');
    if(c=='n'||c=='N')
    {
      goto label;
    }
  }

  else if(ch==5)
  {
    cout<<"\n\n\n\n\t\t\t\t\tThankyou! for using our software...";
    cout<<"\n\t\t\t\t\tProgrammed By:- Mr. Aman Patel";
    getch();
    exit(0);
  }

  else
  {
    cout<<"\nInvalid Choice! Please try again and enter a correct option...";
    getch();
    goto label;
  }
  getch();
  return 0;
}
