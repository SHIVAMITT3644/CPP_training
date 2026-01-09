#include <iostream>
using namespace std;

int main()
{
    // for loop
    int number;

    cout << "Enter a number" << endl;
    cin >> number;

    for (int index = 1; index < 11; index++)
    {
        cout << number << " * " << index << " = " << number * index << endl;
    }

    // while loop statement

    int number1;
    int index = 1;
    int sum = 0;

    cout << endl
         << "Enter a number to get sum of n natural number" << endl;
    cin >> number1;

    while (index <= number1)
    {
        sum += index;
        index++;
    }

    cout << "Sum Of N Natural Number is " << sum << endl;

    // pattern printing using loops

    int rowNumber;

    cout << "Enter number of Rows" << endl;
    cin >> rowNumber;

    // solid box printing
    for (int index = 1; index <= rowNumber; index++)
    {
        int rowIterator = 1;

        while (rowIterator <= rowNumber)
        {
            cout << "*";
            rowIterator++;
        }
        cout << endl;
    }

    cout << endl;

    // hollow box printing
    for (int rowIterator = 1; rowIterator <= rowNumber; rowIterator++)
    {
        for (int columnIterator = 1; columnIterator <= rowNumber; columnIterator++)
        {
            if (rowIterator == 1 || rowIterator == rowNumber)
            {
                cout << "*";
            }
            else
            {
                if (columnIterator == 1 || columnIterator == rowNumber)
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    // Right angle traingle pattern printing
    for (int rowIterator = 1; rowIterator <= rowNumber; rowIterator++)
    {
        for (int columnIterator = 1; columnIterator <= rowIterator; columnIterator++)
        {
            cout << "*";
        }
        cout << endl;
    }

    cout << endl;

    // Inverse RightAngle Traingle
    for (int rowIterator = 1; rowIterator <= rowNumber; rowIterator++)
    {
        for (int columnIterator = rowNumber - rowIterator + 1; columnIterator >= 1; columnIterator--)
        {
            cout << "*";
        }
        cout << endl;
    }

    // Normal Traingle Printing
    for (int rowIterator = 0; rowIterator < rowNumber; rowIterator++)
    {
        for (int columnIterator = rowNumber - rowIterator - 1; columnIterator >= 0; columnIterator--)
        {
            cout << " ";
        }
        for (int columnIterator = 0; columnIterator < (2 * rowIterator + 1); columnIterator++)
        {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}