/**************************************************************************//**
 * @file
 * @brief Contains all function headers and constants for program
 *****************************************************************************/
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

/*!
 * @brief Contains a record for a single person in the database
 */

struct Record
{
    char name[30];                  /*!< the name of the person */
    char address[30];               /*!< the address the person lives at*/
    char city[28];                  /*!< the city the person lives in*/
    char state[2];                  /*!< the state the person lives in*/
    unsigned int zipCode;           /*!< the zip and plus code of the person*/
    unsigned int birthDate;         /*!< the birthday of the person */
    unsigned int licensedDate;      /*!< the date of license issued to the person */
    unsigned int expirationDate;    /*!< the date of license expiration for the person */
    char radioClass;                /*!< the radio class of the person */
    char callSign[5];               /*!< the callSign of the person */
};

// constants

/*!
 * @brief The Current Year
 */
const int CURRENTYEAR = 2019;

/*!
 * @brief All possible valid states codes for the isstate function
 */
const char STATES[55][3] = { "AL", "AK","AZ","AR", "CA", "CO","CT","DE","FL", "GA",
    "HI","ID", "IL", "IN","IA","KS", "KY", "LA","ME","MD", "MA", "MI", "MN",
    "MS","MO", "MT", "NE","NV","NH", "NJ", "NM","NY","NC","ND", "OH","OK","OR",
    "PA", "RI","SC","SD","TN", "TX","UT","VT","VA", "WA","WV","WI", "WY" };
    
/*!
 * @brief The maximum number of error messages for a record
 */
const int NUMERRORS = 22;

/*!
 * @brief All possible valid Radio Classes for the isRadioClassError function
 */
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
void isLicenseDateError(int date, bool errors[]);
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