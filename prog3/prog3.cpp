#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//function headers here
bool solveMaze(char *arr[], int xpos, int ypos);
bool freeMemory(char *arr[]);
void printMaze(char *arr[], int size, ostream &out);



main(int argc, char *argv[])
{
    //place variables here

    ifstream fin;
    ofstream fout;

    //check argc

    if (argc != 3)
    {
        cout << "Usage: prog3.exe, infile, outfile" << endl;
        return 0;
    }

    //open files
    fin.open(argv[1]);
    if (!fin.is_open())
    {
        cout << "Error, file " << argv[1] << " failed to open." << endl;
        return 0;
    }
    fout.open(argv[2]);

    if (!fout.is_open())
    {
        cout << "Error, file " << argv[2] << " failed to open." << endl;
        return 0;
    }


    //input maze

    //dynamically allocate memory

    //find solution

    //output solution
    
    //free up memory


    //close files / clean up memory

    fin.close();
    fout.close();
    return 0;
}

//place functions here

bool solveMaze(char *arr[],int xpos, int ypos)
{
    //check if current location is valid

    //mark current location

    //move each of the four avaliable directions

    //unmark location
    return false;
}

bool freeMemory(char *arr[])
{
    ;
}

void printMaze(char *arr[], int size, ostream &out)
{
    for (int i = 0; i < size; i++)
    {
        out << arr[i];
    }
}
