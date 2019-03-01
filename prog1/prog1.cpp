/**************************************************************************//**
 * @file
 *
 * @brief Sorts given database of records and outputs good records and bad
 * records to seperate files.
 *
 * @mainpage Program 1 - Database Checker
 *
 * @section Course Info
 *
 * @author David Mathews
 *
 * @date Feb 28, 2019
 *
 * @par Instructor:
 *         Professor Roger L Schrader
 *
 * @par Course:
 *         CSC 215 - M002 - 1:00 pm
 *
 * @par Location:
 *         Mc Laury - Room 313
 *
 * @section program_section Program Information
 *
 * @details This program first checks if the number of given command arguments
 * is valid. It then uses the command arguments to open three files, one input
 * and two outputs, using the extractFiles function. The input and one of the
 * outputs are binary files, while the other output is a text file. The program
 * then reads in the records stored in the input binary file one by one. 
 *      For each record read in from the file, the program will check each of
 * the items in the record for errors, outputting the presense of errors into
 * a boolean array using the following functions:
 *       isNameOrCityError, isAddressError, isStateError, isState,
 * isRadioClassError, extractBitInt , isZipCodeError,
 * isBirthDateError, isLiceneDateError, isExpirationDateError, isCallSignError,
 * extractMonth, extractDay, extractYear, compDates
 *       Once each of the items has been checked, the program will
 * output the record to one of the two output files.
 *      If the record contains any errors, (as evidenced by the isError) 
 * the record will be outputted to a text file with all of the error messages
 * printed after it using the printErrors function
 *      If the record does not contain any errors, the record will be outputted
 * to a binary file in the proper format using the printGood function
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage: 
   @verbatim
   c:\>prog1.exe oldFile.bin, newGood.bin, newBad.txt
   d:\> c:\bin\prog1.exe oldFile.bin, newGood.bin, newBad.txt

   oldFile.bin - The file containing records to be checked for errors
   newGood.bin - The file that good records are to be stored in
   newBad.txt - The file to output bad records and their errors to
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @todo comment code thouroughly
 * @todo check for typos
 * @todo error check code thouroughly
 *
 * <a href="https://gitlab.mcs.sdsmt.edu/7472735/csc215s19programs/commits/master">
 The gitlab commit log</a>
 *****************************************************************************/
#pragma pack(1)
#include "functions.h"


using namespace std;

//function headers here

/** ***************************************************************************
 * @author David Mathews
 *
 * @par Description:
 * This function checks to see whether an entered cstring contains only leters,
 * spaces, and periods.
 *
 * @param[in] argc - The number of command arguments given at program start
 * @param[in] argv - A 2D character array of the starting command arguments
 *
 * @returns 0 - The program ran successfully
 * @returns 1 - The program failed/crashed/had an error
 *****************************************************************************/
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
        cout << "Usage: prog1.exe, oldFile.bin, newGood.bin, newBad.txt";
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
        isLicenseDateError(currentRec.licensedDate, errors);
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