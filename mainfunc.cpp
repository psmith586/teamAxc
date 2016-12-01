#include<iostream>
#include<fstream>

using namespace std;

const int NAME_SIZE = 60, ADD_SIZE = 60, LOC_SIZE = 100, PHONE_SIZE = 15


struct accountHolder
{
    char name[NAME_SIZE];
    char address[ADD_SIZE];
    char location[LOC_SIZE];
    double balance;

};
