#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//function headers here
void solveMaze(char **arrptr, int xpos, int ypos, int steps, int row, char **&bestPath, int &bestSteps);
void freeMemory(char **&arrptr, int row);
bool readMaze(char **&arrptr, char **&bestPath, int &row, int &column, int &posx, int &posy, istream &in);
bool dynamic2dChar(char **&arrptr, int row, int column);
void mazeCpy(char **&arrptr, char **&bestPath, int row);
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
    readMaze(arrptr, bestPath, row, column, xpos, ypos, fin);

    //set bestSteps to the largest possible value for the given maze;
    bestSteps = row * column * 2;
    //find solution
    solveMaze(arrptr, xpos, ypos, 0, row, bestPath, bestSteps);

    //output solution
    cout << endl << endl;
    printMaze(bestPath, row, column, cout);

    //free up memory
    freeMemory(arrptr, row);
    freeMemory(bestPath, row);

    //close files / clean up memory

    fin.close();
    fout.close();
    return 0;
}

//place functions here

void solveMaze(char **arrptr,int xpos, int ypos, int steps, int row, char **&bestPath, int &bestSteps)
{
    //check if current location is valid
    if (arrptr[ypos][xpos] == '*' || arrptr[ypos][xpos] == 'L'
        || arrptr[ypos][xpos] == '-' || arrptr[ypos][xpos] == '=')
    {
        return;
    }
    if (arrptr[ypos][xpos] == 'E')
    {
        //found exit
        cout << "Path found with " << steps << "steps" << endl;
        if (steps < bestSteps)
        {
            mazeCpy(arrptr, bestPath, row);
            bestSteps = steps;
        }
        arrptr[ypos][xpos] = 'E';
        printMaze(arrptr, 10, 20, cout);
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
    solveMaze(arrptr, xpos, ypos + 1, steps, row, bestPath, bestSteps);
    solveMaze(arrptr, xpos, ypos - 1, steps, row, bestPath, bestSteps);
    solveMaze(arrptr, xpos + 1, ypos, steps, row, bestPath, bestSteps);
    solveMaze(arrptr, xpos - 1, ypos, steps, row, bestPath, bestSteps);

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
        if (arrptr[i] != nullptr)
        {
            delete[] arrptr[i];
        }
    }
    delete[] arrptr;
}

bool readMaze(char **&arrptr, char **&bestPath, int &row, int &column, int &posx, int &posy, istream &in)
{
    //input maze information
    in >> row;
    in >> column;
    in >> posx;
    in >> posy;
    
    //dynamically allocate memory for the maze
    if (!dynamic2dChar(arrptr, row, column) || !dynamic2dChar(bestPath, row, column))
    {
        return false;
    }

    //input maze
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

void mazeCpy(char **&arrptr, char **&bestPath, int row)
{
    for (int i = 0; i < row; i++)
    {
        strcpy(bestPath[i], arrptr[i]);
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
