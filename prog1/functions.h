#pragma pack(1)
#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

//structure
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

// typedefs
// enums
// constants
const int CURRENTYEAR = 2019;
const char STATES[55][3] = { "AL", "AK","AZ","AR", "CA", "CO","CT","DE","FL", "GA",
    "HI","ID", "IL", "IN","IA","KS", "KY", "LA","ME","MD", "MA", "MI", "MN",
    "MS","MO", "MT", "NE","NV","NH", "NJ", "NM","NY","NC","ND", "OH","OK","OR",
    "PA", "RI","SC","SD","TN", "TX","UT","VT","VA", "WA","WV","WI", "WY" };
    
const int NUMERRORS = 22;
const char RADIOCLASSES[] = { 'N', 'T', 'P', 'G', 'A', 'X' };
// function prototypes

bool isNameOrCityError(char name[]);
bool isAddressError(char address[]);
bool isStateError(char state[]);
bool isState(char state[]);
bool isRadioClassError(char letter);
int extractBitInt(int num, int start, int bits);
bool extractFiles(ifstream &fin, ofstream &foutG, ofstream &foutB, char **argv);
void isZipCodeError(int zip, bool errors[]);
void isBirthDateError(int date, bool errors[]);
void isLicenceDateError(int date, bool errors[]);
void isExpirationDateError(Record rec, bool errors[]);
void isCallSignError(char arr[5], bool errors[]);
int extractMonth(int num);
int extractDay(int num);
int extractYear(int num);
bool compDates(Record rec);
bool isError(bool errors[], int size);
void printGood(Record rec, ofstream &fout);
void printErrors(Record rec, bool errors[], ofstream &fout);


#endif