/** ***************************************************************************
 * @file
 *
 * @brief Program demonstrating dynamic arrays and recursive problem solving
 *
 * @mainpage Program 3- Maze Solver
 *
 * @section Program Information:
 *
 * @author David Mathews
 *
 * @date April 12th, 2019
 *
 * @par Instructor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         McLaury 313
 *
 * @section program_section Program Information
 *
 * @details This program inputs one or more mazes from a given text file,
 * solves them, and outputs the fastest solution for each maze to a known
 * output location. If more than one solution exits, it will output one of
 * them. Mazes are solved using the following rules
 *
 * 1. A '*' is a wall. 
 * 2. An 'L' is impassible terrain.
 * 3. A 'W' is difficult terrain and takes double the movement to traverse it.
 * 4. The 'E' is the exit. Stepping onto this tile takes a step.
 * 5. All other characters are normal movement locations and take a single step
    to move one tile horizontally or vertically. Diagonal movement is not
    allowed
 * 6. Movement is not counted for the starting location, merely steps taken
    from there.
 *
 * After each maze is solved, the memory that was dynamically allocated for the
 * maze is freed up and returned to the system.
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe input_numbers.txt results.txt
   d:\> c:\bin\prog3.exe input_numbers.txt results.txt
   @endverbatim
 *
 *
 * @par Modifications and Development Timeline:
   <a href="https://gitlab.mcs.sdsmt.edu/7472735/csc215s19programs/tree/master/prog3"
   >Link to commit history on gitlab</a>
 *****************************************************************************/
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


/** ***************************************************************************
 * @author David Mathews
 *
 * @par Description:
 * This function solves a given file of mazes and outputs the solutions to a
 * seperate file.
 *
 * @param[in] argc - The number of command arguments given at program start
 * @param[in,out] argv - A 2D character array of the starting command arguments
 *
 * @returns 0 - The program ran successfully
 * @returns 1 - The program failed/crashed/had an error
 *****************************************************************************/
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
        cout << "Usage: prog3.exe, infile.txt, outfile.txt" << endl;
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function solves a given maze recursively and returns the fastest
* solution in bestPath. The number of steps taken for this solution is returned
* in bestSteps.
*
* @param[in] arrptr - the maze entered as a dynamic 2d character array
* @param[in] xpos - the starting column in the maze
* @param[in] ypos - the starting row in the maze
* @param[in] steps - the number of current steps taken in the maze
* @param[in] row - the number of rows in the maze
* @param[in] column - the number of columns in the maze
* @param[out] bestPath - the maze returned as a dynamic 2d character array
* @param[out] bestSteps - the fastest number of steps in the solution
******************************************************************************/
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function frees up the dynamic memory of a 2D array of row rows.
*
* @param[in] arrptr - the 2D array to be freed
* @param[in] row - the number or rows in the array to be freed
****************************************************************************/
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function reads a maze into a 2D character array
*
* @param[out] arrptr - the array to store the maze in
* @param[in] row - the number of rows in the maze
* @param[in] column - the number of columns in the maze
* @param[in] in - the file to read the maze in from
*
* @returns true - the maze was successfully read in
* @returns false - the maze was not successfully read in
****************************************************************************/
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function dynamically allocates a 2D character array of size row by
* column
*
* @param[out] arrptr - the array to allocate memory for
* @param[in] row - the number of rows to be allocated
* @param[in] column - the number of columns to be allocated
*
* @returns true - the memory was successfully allocated
* @returns false - the memory was not successfully allocated
****************************************************************************/
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function copies a 2D character array from arrptr to bestPath
*
* @param[in] arrptr - the array to copy data from
* @param[out] bestPath - the array to copy data to
* @param[in] row - the number of rows to be copied
* @param[in] column - the number of columns to be copied
****************************************************************************/
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

/** ***************************************************************************
* @author David Mathews
*
* @par Description:
* This function prints a given 2D character array to a file
*
* @param[in] arrptr - the array to be printed
* @param[in] row - the number of rows in the array
* @param[in] column - the number of columns in the array
* @param[out] out - the file to print the array to
****************************************************************************/
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
