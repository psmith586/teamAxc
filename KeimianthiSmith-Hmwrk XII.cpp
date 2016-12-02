#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<string.h>

using namespace std;

// Functions for Changing
void Modify(char [] , int SIZE);
void Add(char [ , int SIZE);

const int NAME_SIZE = 60,
          ADD_SIZE = 60,
          LOC_SIZE = 100,
          PHONE_SIZE = 15,
          DATE_SIZE [11];


struct accountHolder
{
    char name[NAME_SIZE];
    char address[ADD_SIZE];
    char location[LOC_SIZE];
    double balance;
    char date[DATE_SIZE];

};

void Add(char [], int SIZE)  //function to add New record in Data File
{
    char ch = 'y';
    fil.open("binary.dat" , ios::app | ios::binary);
    while(ch =='y' || ch =='Y')
    {
            fileobj.input();
            fil.write((char*)&fileobj, sizeof(fileobj));
        cout << "Want to continue....";
        cin >> ch;
    }
    fil.close();


}


void Modify(char [], int SIZE) //Function to Modify Particular Record from Data File
{

    char n(100);
    cout << "Enter the Name you're searching for. ";
    gets(n);

    fil.open("binary.dat" ios::in | ios::out |ios::binary);//using binary.dat for the file name
    if(!fil)  //using fil as variable for filename unless you want it to be something else
    {
            cout << "File not found";
            exit(0);
    }
    else
    {
        fil.read((char*)&fileobj, sizeof(fileobj));
        while(!file.eof())
        {
                if(strcmp(n,fileobj.getn())== 0)
                {
                    fil.seekg(0,ios::cur);
                    cout << "Enter New Record.." << endl;
                    fileobj.input();
                    fil.seekp(fil.tellg() - sizeof(fileobj));
                    fil.write((char*)&fileobj, sizeof(fileobj));

                }
                else
                {
                    cout << "Press Any Key...For search" << endl;
                    getchar();
                }
                fil.read((char*)&fileobj, sizeof(fileobj));
        }
    }
    fil.close();
}

