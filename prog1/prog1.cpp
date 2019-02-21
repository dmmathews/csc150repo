#pragma pack(1)
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
#include <struct>


using namespace std;

struct Record
{
    char name[30];
    char address[30];
    char city[28];
    char state[2];
    unsigned int zipCode;
    unsigned int birthDate;
    unsigned int licensedDate;
    unsigned int expirationDate;
    char radioClass;
    char callSign[5];
};
//function headers here

int main(int argc, char *argv[])
{
    //declare variables here

    //main function here

    return 0;
}

//write functions here

