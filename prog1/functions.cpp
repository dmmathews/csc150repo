#pragma pack(1)
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
#include "functions.h"

using namespace std;


bool isNameOrCityError(char name[])
{
    //iterate through every element, check if each is valid
    int count = 0;
    while (name[count] != '\0')
    {
        if (isalpha(name[count]) || ' ' == name[count] || '.' == name[count])
        {
            ;
        }
        else
        {
            return true;
        }
        count++;
    }
    return false;
}

bool isAddressError(char address[])
{
    //iterate through every element, check if each is valid
    int count = 0;
    while (address[count] != '\0')
    {
        if (isalpha(address[count]) || ' ' == address[count]
            || '.' == address[count] || isdigit(address[count])
            || '#' == address[count])
        {
            ;
        }
        else
        {
            return true;
        }
        count++;
    }
    return false;
}

bool isStateError(char state[])
{
    if (!isupper(state[0]))
    {
        //first character not uppercase
        return true;
    }
    else if (!isalpha(state[1]))
    {
        //second character not letter
        return true;
    }
    if (!isState(state))
    {
        //not a valid state
        return true;
    }
    return false;
}

bool isState(char state[])
{
    char temp[3];
    temp[0] = toupper(state[0]);
    temp[1] = toupper(state[1]);
    for (int i = 0; i < 55; i++)
    {
        if (temp[0] == STATES[i][0])
        {
            if (temp[1] == STATES[i][1])
            {
                return true;
            }
        }
    }
    return false;
}

//extracts bits bits from num starting at bit start
int extractBitInt(int num, int start, int bits)
{
    int mask = int(pow(2, bits) - 1);
    num >>= start;
    num &= mask;
    return num;
}

int extractDay(int num)
{
    int mask = 63;
    num &= mask;
    return num;
}

int extractMonth(int num)
{
    int mask = 15;
    num >>= 6;
    num &= mask;
    return num;
}

int extractYear(int num)
{
    int mask = 4095;
    num >>= 12;
    num &= mask;
    return num;
}


//returns true if files open correctly.
bool extractFiles(ifstream &fin, ofstream &foutG, ofstream &foutB, char **argv)
{
    fin.open(argv[1], ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "Error opening file" << argv[1] << endl;
        return false;
    }
    foutG.open(argv[2], ios::out | ios::binary);
    if (!foutG.is_open())
    {
        cout << "Error opening file" << argv[2] << endl;
        return false;
    }
    foutB.open(argv[3]);
    if (!foutB.is_open())
    {
        cout << "Error opening file" << argv[3] << endl;
        return false;
    }
    return true;
}

void isZipCodeError(int zip, bool errors[])
{
    int temp = 0;
    temp = extractBitInt(zip, 14, 18);
    if (temp < 10000 || 99999 < temp)
    {
        //output error
        errors[5] = true;
    }
    temp = extractBitInt(zip, 0, 14);
    if (temp != 0 && (temp < 1000 || 9999 < temp) )
    {
        //output error
        errors[6] = true;
    }
}

void isBirthDateError(int date, bool errors[])
{
    int month = 0;
    int day = 0;
    int year = 0;

    month = extractMonth(date);
    day = extractDay(date);
    year = extractYear(date);

    //check month for validity
    if (month < 1 || 12 < month)
    {
        errors[7] = true;
    }
    //check day for validity
    if (day < 1 || 31 < day)
    {
        errors[8] = true;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || 30 < day)
        {
            errors[8] = true;
        }
    }
    else if (month == 2)
    {
        if (day < 1 || 28 < day)
        {
            errors[8] = true;
        }
    }
    //check year for validity
    if (year < 1900 || CURRENTYEAR < year)
    {
        //output error
        errors[9] = true;
    }
}

void isLicenceDateError(int date, bool errors[])
{
    int month = 0;
    int day = 0;
    int year = 0;

    month = extractMonth(date);
    day = extractDay(date);
    year = extractYear(date);

    //check month for validity
    if (month < 1 || 12 < month)
    {
        errors[10] = true;
    }
    //check day for validity
    if (day < 1 || 31 < day)
    {
        errors[11] = true;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || 30 < day)
        {
            errors[11] = true;
        }
    }
    else if (month == 2)
    {
        if (day < 1 || 28 < day)
        {
            errors[11] = true;
        }
    }
    //check year for validity
    if (year < 1900 || CURRENTYEAR < year)
    {
        //output error
        errors[12] = true;
    }
}

void isExpirationDateError(Record rec, bool errors[])
{
    int date = rec.expirationDate;
    int month = 0;
    int day = 0;
    int year = 0;

    month = extractMonth(date);
    day = extractDay(date);
    year = extractYear(date);

    //check month for validity
    if (month < 1 || 12 < month)
    {
        errors[13] = true;
    }
    //check day for validity
    if (day < 1 || 31 < day)
    {
        errors[14] = true;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || 30 < day)
        {
            errors[14] = true;
        }
    }
    else if (month == 2)
    {
        if (day < 1 || 28 < day)
        {
            errors[14] = true;
        }
    }
    //check year for validity
    if (year < 1900 || CURRENTYEAR < year)
    {
        //output error
        errors[15] = true;
    }
    if (!compDates(rec))
    {
        errors[16] = true;
    }
}

bool compDates(Record rec)
{
    //check if expiration year is bigger then licensed year
    if (extractYear(rec.expirationDate) < extractYear(rec.licensedDate))
    {
        return false;
    }
    // check if expiration year is same as licensed year
    if (extractYear(rec.expirationDate) == extractYear(rec.licensedDate))
    {
        //check if expiration month and day is bigger then licensed month and day
        if (extractBitInt(rec.expirationDate, 0, 9) < extractBitInt(rec.licensedDate, 0, 9))
        {
            return false;
        }
    }
    return true;
}

bool isRadioClassError(char letter)
{
    int radioClassSize = 6;
    for (int i = 0; i < radioClassSize; i++)
    {
        if (RADIOCLASSES[i] == letter)
        {
            //not valid radio class
            return true;
        }
    }
    return false;
}


void isCallSignError(char arr[5], bool errors[])
{
    //checks if characters in call sign are letters
    
    if (arr[0] == 'K' || arr[0] == 'W' || arr[0] == 'N')
    {
        
    }
    else
    {
        //error if charactor is not a valid letter
        errors[16] = true;
        if (!isalpha(arr[0]))
        {
            //error if charactor is not a letter
            errors[19] = true;
        }
    }
    
    if (isupper(arr[1]) || isupper(arr[3]) || isupper(arr[4]))
    {
        ;
    }
    else
    {
        //error if charactor is not uppercase
        errors[17] = true;
        if (!isalpha(arr[1]) || !isalpha(arr[2]) || !isalpha(arr[3]))
        {
            ;
        }
        else
        {
            //error if charactor is not a letter
            errors[19] = true;
        }
    }

    if (!isdigit(arr[2]))
    {
        errors[18] = true;
    }
}

bool isError(bool errors[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (errors[i] == true)
        {
            return true;
        }
    }
    return false;
}

void printGood(Record rec, ofstream &fout)
{
    fout.seekp(0, ios::end);
    fout.write((char *) &rec, sizeof(Record));
}

//prints all errors to text file
void printErrors(Record rec, bool errors[], ofstream &fout)
{
    for (int i = 0; i < 80; i++)
    {
        fout << "=";
    }
    fout << fixed << setprecision(5) << endl;
    fout << "Name:             " << rec.name <<  endl;
    fout << "Address:          " << rec.address << endl;
    fout << "City State Zip:   " << rec.city << ", " << rec.state[0]
        << rec.state[1] << " " << extractBitInt(rec.zipCode, 14, 18)
        << "-" << setprecision(4) << extractBitInt(rec.zipCode, 0, 14) << endl;
    fout << "Birthdate:        " << extractMonth(rec.birthDate) << "/"
        << extractDay(rec.birthDate) << "/"<< extractYear(rec.birthDate) << endl;
    fout << "Licensing Dates:  " << extractMonth(rec.licensedDate) 
        << "/" << extractDay(rec.licensedDate) << "/" << extractYear(rec.licensedDate)
        << " - " << extractMonth(rec.expirationDate) << "/" << extractDay(rec.expirationDate)
        << "/" << extractYear(rec.expirationDate) << endl;
    fout << "Class - Callsign: " << rec.radioClass << " - " << rec.callSign[0]
        << rec.callSign[1] << rec.callSign[2] << rec.callSign[3] << rec.callSign[4] << endl;

    fout << endl;
    if (errors[0] == true)
    {
        fout << "Invalid character in the name field" << endl;
    }
    if (errors[1] == true)
    {
        fout << "Invalid character in the address field" << endl;
    }
    if (errors[2] == true)
    {
        fout << "Invalid character in the city field" << endl;
    }
    if (errors[3] == true)
    {
        fout << "Invalid State code" << endl;
    }
    if (errors[4] == true)
    {
        fout << "First character of State Code not capitalized" << endl;
    }
    if (errors[5] == true)
    {
        fout << "Invalid 5 digit zip code" << endl;
    }
    if (errors[6] == true)
    {
        fout << "Invalid 4 digit plus code" << endl;
    }
    if (errors[7] == true)
    {
        fout << "Invalid month in Birthday" << endl;
    }
    if (errors[8] == true)
    {
        fout << "Invalid day in Birthday" << endl;
    }
    if (errors[9] == true)
    {
        fout << "Invalid year in Birthday" << endl;
    }
    if (errors[10] == true)
    {
        fout << "Invalid month in License" << endl;
    }
    if (errors[11] == true)
    {
        fout << "Invalid day in License" << endl;
    }
    if (errors[12] == true)
    {
        fout << "Invalid year in License" << endl;
    }
    if (errors[13] == true)
    {
        fout << "Invalid month in Expiration" << endl;
    }
    if (errors[14] == true)
    {
        fout << "Invalid day in Expiration" << endl;
    }
    if (errors[15] == true)
    {
        fout << "Invalid year in Expiration" << endl;
    }
    if (errors[16] == true)
    {
        fout << "Expiration Date is not after the License Date" << endl;
    }
    if (errors[17] == true)
    {
        fout << "Radio Class code is invalid" << endl;
    }
    if (errors[18] == true)
    {
        fout << "Invalid first character in call sign" << endl;
    }
    if (errors[19] == true)
    {
        fout << "Invalid second, fourth or fifth character in call sign" << endl;
    }
    if (errors[20] == true)
    {
        fout << "Invalid digit in call sign" << endl;
    }
    if (errors[21] == true)
    {
        fout << "Call Sign not upper case" << endl;
    }
}
