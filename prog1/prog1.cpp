#pragma pack(1)
#include "functions.h"


using namespace std;

//function headers here

int main(int argc, char *argv[])
{
    //declare variables here
    
    ifstream fin;
    ofstream foutG;
    ofstream foutB;
    Record currentRec;
    bool errors[25] = { false };
    int size = 0;

    //main function here
    if (argc != 4)
    {
        cout << "Usage: prog1.exe, oldFile, newGood, newBad";
        return 0;
    }

    //open files, check for error
    if (!extractFiles(fin, foutG, foutB, argv))
    {
        return 0;
    }

    // find amount of records in fin
    fin.seekg(0, ios::end);
    size = int(fin.tellg() / sizeof(Record));

    //read all records in fin one at a time
    for (int i = 0; i < size; i++)
    {
        //read in record
        fin.seekg(i * sizeof(Record), ios::beg);
        fin.read((char*)&currentRec, sizeof(Record));

        //clear error statements
        for (int i = 0; i < NUMERRORS; i++)
        {
            errors[i] = false;
        }

        //check for errors in currentRec
        errors[0] = isNameOrCityError(currentRec.name);
        errors[1] = isAddressError(currentRec.address);
        errors[2] = isNameOrCityError(currentRec.city);
        errors[3] = isStateError(currentRec.state);
        isZipCodeError(currentRec.zipCode, errors);
        isBirthDateError(currentRec.birthDate, errors);
        isLicenceDateError(currentRec.licensedDate, errors);
        isExpirationDateError(currentRec, errors);
        isRadioClassError(currentRec.radioClass);
        isCallSignError(currentRec.callSign, errors);
        //output to correct file
        
        if (isError(errors, NUMERRORS))
        {
            //output to foutB
            printErrors(currentRec, errors, foutB);
        }
        else
        {
            //output to foutG
            printGood(currentRec, foutG);
        }
        
        ;
    }


    //close files
    fin.close();
    foutB.close();
    foutG.close();
    return 0;
}