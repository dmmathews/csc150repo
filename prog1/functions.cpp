#pragma pack(1)
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
//#include <functions.h>

bool isNameOrCityValid(char name[])
{
    //iterate through every element, check if each is valid
    int count = 0;
    while (name[count] != '\n')
    {
        if (!isalpha(name[count]) || ' ' == name[count] || '.' == name[count])
        {
            return false;
        }
    }
    return true;
}

bool isAdressValid(char address[30])
{
    //iterate through every element, check if each is valid
    int count = 0;
    while (address[count] != '\n')
    {
        if (!isalpha(address[count]) || ' ' == address[count]
            || '.' == address[count] || !isdigit(address[count])
            || '#' == address[count])
        {
            return false;
        }
    }
    return true;
}

bool isStateValid(char city[])
{
    if (!isupper(city[0]))
    {
        //first character not uppercase
        return false;
    }
    else if (!isalpha(city[1]))
    {
        //second character not letter
        return false;
    }
    if (!isState(city))
    {
        //not a valid state
        return false;
    }
    return true;
}

bool isState(char city[])
{
    char temp[2] = { city[0], city[1] };
    tolower(temp[0]);
    tolower(temp[1]);
    if (temp[0] == 'a')
    {
        if (temp[1] == 'l' || temp[1] == 'k'
            || temp[1] == 'r' || temp[1] == 'z')
        {
            return true;
        }
    }
    else if (temp[0] == 'c')
    {
        if (temp[1] == 'a' || temp[1] == 'o'
            || temp[1] == 't')
        {
            return true;
        }
    }
    else if (temp[0] == 'd')
    {
        if (temp[1] == 'e')
        {
            return true;
        }
    }
    else if (temp[0] == 'f')
    {
        if (temp[1] == 'l')
        {
            return true;
        }
    }
    else if (temp[0] == 'g')
    {
        if (temp[1] == 'a')
        {
            return true;
        }
    }
    else if (temp[0] == 'h')
    {
        if (temp[1] == 'i')
        {
            return true;
        }
    }
    else if (temp[0] == 'i')
    {
        if (temp[1] == 'd' || temp[1] == 'l'
            || temp[1] == 'n' || temp[1] == 'a')
        {
            return true;
        }
    }
    else if (temp[0] == 'k')
    {
        if (temp[1] == 's' || temp[1] == 'y')
        {
            return true;
        }
    }
    else if (temp[0] == 'l')
    {
        if (temp[1] == 'a')
        {
            return true;
        }
    }
    else if (temp[0] == 'm')
    {
        if (temp[1] == 'e' || temp[1] == 'd'
            || temp[1] == 'a' || temp[1] == 'i'
            || temp[1] == 'n' || temp[1] == 's'
            || temp[1] == 'o' || temp[1] == 't')
        {
            return true;
        }
    }
    else if (temp[0] == 'n')
    {
        if (temp[1] == 'e' || temp[1] == 'v'
            || temp[1] == 'h' || temp[1] == 'j'
            || temp[1] == 'm' || temp[1] == 'y'
            || temp[1] == 'c' || temp[1] == 'd')
        {
            return true;
        }
    }
    else if (temp[0] == 'o')
    {
        if (temp[1] == 'h' || temp[1] == 'k'
            || temp[1] == 'r')
        {
            return true;
        }
    }
    else if (temp[0] == 'p')
    {
        if (temp[1] == 'a')
        {
            return true;
        }
    }
    else if (temp[0] == 's')
    {
        if (temp[1] == 'c' || temp[1] == 'd')
        {
            return true;
        }
    }
    else if (temp[0] == 't')
    {
        if (temp[1] == 'n' || temp[1] == 'x')
        {
            {
                return true;
            }
        }
    }
    else if (temp[0] == 'u')
    {
        if (temp[1] == 't')
        {
            {
                return true;
            }
        }
    }
    else if (temp[0] == 'v')
    {
        if (temp[1] == 't' || temp[1] == 'a')
        {
            {
                return true;
            }
        }
    }
    else if (temp[0] == 'w')
    {
        if (temp[1] == 'a' || temp[1] == 'v'
            || temp[1] == 'i' || temp[1] == 'y')
        {
            {
                return true;
            }
        }
    }
    return false;
}


//extracts bits bits from num starting 1 after bit start
int extractBitInt(int num, int start, int bits)
{
    int mask = pow(2, bits)-1;
    num >> start;
    num &= mask;
    return num;
}