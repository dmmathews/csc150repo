#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//function headers here
void solveMaze(char **arrptr, int xpos, int ypos, int steps, int row, int column, char **&bestPath, int &bestSteps);
void freeMemory(char **&arrptr, int row);
bool readMaze(char **&arrptr, int row, int column, istream &in);
bool dynamic2dChar(char **&arrptr, int row, int column);
void mazeCpy(char **&arrptr, char **&bestPath, int row, int column);
void printMaze(char **arrptr, int row, int column, ostream &out);



int main(int argc, char *argv[])
{
    //place variables here
    char **arrptr = nullptr;
    char **bestPath = nullptr;
    int bestSteps = -1;
    int column = 0;
    int row = 0;
    int xpos = 0;
    int ypos = 0;
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
    while (fin >> row >> column >> ypos >> xpos)
    {
        //dynamically allocate memory for the maze
        if (!dynamic2dChar(arrptr, row, column + 1))
        {
            cout << "Memory allocation error";
            return false;
        }

        //dynamically allocate memory for the solution
        if (!dynamic2dChar(bestPath, row, column + 1))
        {
            cout << "Memory allocation error";
            return 0;
        }

        //read in maze
        readMaze(arrptr, row, column, fin);

        //set bestSteps to the largest possible value for the given maze;
        bestSteps = row * column * 2;

        //find solution
        if (arrptr[ypos][xpos] == 'W')
        {
            solveMaze(arrptr, xpos, ypos, -1, row, column, bestPath, bestSteps);
        }
        else
        {
            solveMaze(arrptr, xpos, ypos, 0, row, column, bestPath, bestSteps);
        }

        //output solution
        fout << "Size: " << row << "x" << column << endl;
        fout << "Start loc: " << ypos << " " << xpos << endl;
        fout << "Shortest Path: " << bestSteps << endl;
        printMaze(bestPath, row, column, fout);
        fout << endl;

        //free up memory
        freeMemory(arrptr, row);
        freeMemory(bestPath, row);
    }

    //close files / clean up memory

    fin.close();
    fout.close();
    return 0;
}

//place functions here

void solveMaze(char **arrptr,int xpos, int ypos, int steps, int row, int column, char **&bestPath, int &bestSteps)
{
    //check if current location is valid
    if (arrptr[ypos][xpos] == '*' || arrptr[ypos][xpos] == 'L'
        || arrptr[ypos][xpos] == '-' || arrptr[ypos][xpos] == '=')
    {
        return;
    }
    if (arrptr[ypos][xpos] == 'E')
    {
        //reset best steps to the fastest path to the exit
        if (steps < bestSteps)
        {
            mazeCpy(arrptr, bestPath, row, column);
            bestSteps = steps;
        }
        return;
    }

    // calculate number of steps and mark current location
    if (arrptr[ypos][xpos] == 'W')
    {
        steps += 2;
        arrptr[ypos][xpos] = '=';

    }
    else
    {
        steps++;
        arrptr[ypos][xpos] = '-';
    }

    //move each of the four avaliable directions
    solveMaze(arrptr, xpos, ypos + 1, steps, row, column, bestPath, bestSteps);
    solveMaze(arrptr, xpos, ypos - 1, steps, row, column, bestPath, bestSteps);
    solveMaze(arrptr, xpos + 1, ypos, steps, row, column, bestPath, bestSteps);
    solveMaze(arrptr, xpos - 1, ypos, steps, row, column, bestPath, bestSteps);

    //unmark location
    if (arrptr[ypos][xpos] == '=')
    {
        arrptr[ypos][xpos] = 'W';
    }
    else
    {
        arrptr[ypos][xpos] = ' ';
    }
    return;
}

void freeMemory(char **&arrptr, int row)
{
    if (arrptr == nullptr)
    {
        return;
    }
    for (int i = 0; i < row; i++)
    {
        delete[] arrptr[i];
    }
    delete[] arrptr;
}

bool readMaze(char **&arrptr, int row, int column, istream &in)
{
    //clear the base input newline
    in.getline(arrptr[0], column);
    for (int i = 0; i < row; i++)
    {
        in.getline (arrptr[i], column+1);
    }
    return true;
}
bool dynamic2dChar(char **&arrptr, int row, int column)
{
    arrptr = new (nothrow) char *[row];
    if (arrptr == nullptr)
    {
        cout << "Error allocating memory";
        return false;
    }
    for (int i = 0; i < row; i++)
    {
        arrptr[i] = new (nothrow) char[column];
        if (arrptr[i] == nullptr)
        {
            //clean up memory if memory not allocated right
            for (int j = 0; j < i; j++)
            {
                delete[] arrptr[j];
            }
            delete[] arrptr;
            cout << "Error allocating memory";
            return false;
        }
    }
    return true;
}

void mazeCpy(char **&arrptr, char **&bestPath, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            bestPath[i][j] = arrptr[i][j];
        }
    }
}

void printMaze(char **arrptr, int row, int column, ostream &out)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            out << arrptr[i][j];
        }
        out << endl;
    }
}   
