#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void printUpperPortion(int totalLength);
void printMiddlePortion(int totalLength);
void printLowerPortion(int totalLength);
bool isValidInteger(const string &input);

int main()
{
    int totalLength;
    string input;

    cout << "Enter a Number" << endl;

    getline(cin, input);

    if (!isValidInteger(input))
    {
        cout << "Error: Please enter a valid integer value only." << endl;
        return 0;
    }

    totalLength = stoi(input);

    if(totalLength == 0)
    {
        return 0;
    }

    printUpperPortion(totalLength);
    printMiddlePortion(totalLength);
    printLowerPortion(totalLength);

    return 0;
}

void printUpperPortion(int totalLength)
{
    for (int rowIndex = 1; rowIndex <= totalLength; rowIndex++)
    {
        int temperoryValue = 1;

        for (int columnIndex = 1; columnIndex <= rowIndex; columnIndex++)
        {
            cout << temperoryValue << " ";

            if (temperoryValue == 1)
            {
                temperoryValue = 0;
            }
            else
            {
                temperoryValue = 1;
            }
        }

        for (int columnIndex = 1; columnIndex <= 2*(2*totalLength - (2 * (rowIndex-1)) - 1); columnIndex++)
        {
            cout << " ";
        }

        temperoryValue = 1;

        for (int columnIndex = 1; columnIndex <= rowIndex; columnIndex++)
        {
            cout << temperoryValue << " ";

            if (temperoryValue == 1)
            {
                temperoryValue = 0;
            }
            else
            {
                temperoryValue = 1;
            }
        }

        cout << endl;
    }
}

void printMiddlePortion(int totalLength)
{
    int temperoryValue = 1;
 
    for (int columnIndex = 1; columnIndex <= 2 * totalLength + 1; columnIndex++)
    {
        cout << temperoryValue << " ";

        if (temperoryValue == 1)
        {
            temperoryValue = 0;
        }
        else
        {
            temperoryValue = 1;
        }
    }
    cout << endl;
}

void printLowerPortion(int totalLength)
{
    for (int rowIndex = 1; rowIndex <= totalLength; rowIndex++)
    {
        int temperoryValue = 1;

        for (int columnIndex = 1; columnIndex <=  (totalLength - rowIndex + 1); columnIndex++)
        {
            cout << temperoryValue << " ";

            if (temperoryValue == 1)
            {
                temperoryValue = 0;
            }
            else
            {
                temperoryValue = 1;
            }
        }

        for (int columnIndex = 1; columnIndex <= 2*(2 * rowIndex - 1); columnIndex++)
        {
            cout << " ";
        }

        temperoryValue = 1;

        for (int columnIndex = 1; columnIndex <= (totalLength - rowIndex + 1); columnIndex++)
        {
            cout << temperoryValue << " ";

            if (temperoryValue == 1)
            {
                temperoryValue = 0;
            }
            else
            {
                temperoryValue = 1;
            }
        }

        cout << endl;
    }
}

bool isValidInteger(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    for (char ch : input)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }

    return true;
}
