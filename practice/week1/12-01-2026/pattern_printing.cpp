#include <iostream>
using namespace std;

int main()
{
    int inputNumber;

    cout << "Enter Number Of Rows : ";
    cin >> inputNumber;

    //Rectangular Numerical Pattern
    for(int i = 1; i <= inputNumber; i++)
    {
        int count = 0;
        int value = i;

        while(count <= inputNumber - 1)
        {
            cout << value ;

            if(value == inputNumber)
            {
                value = 1;
            }
            else
            {
                value++;
            }

            count++;
        }

        cout << endl;
    }

    cout<< endl;

    //Alternate Number Printing
    for(int rowIndex = 1; rowIndex <= inputNumber; rowIndex++)
    {
        for(int columnIndex = 1 ; columnIndex <= inputNumber; columnIndex++)
        {
            if((rowIndex + columnIndex) % 2 == 0)
            {
                cout << "1";
            }
            else
            {
                cout << "2";
            }
        } 
        cout << endl;         
    }

    //Traingular Pattern Printing
    for(int rowIndex = 1; rowIndex <= inputNumber; rowIndex++)
    {
        for(int columnIndex = 1 ; columnIndex <= inputNumber - rowIndex; columnIndex++)
        {
            cout << " ";
        }

        for(int columnIndex = 1 ; columnIndex <= rowIndex; columnIndex++)
        {
            cout << columnIndex;
        } 

        for(int columnIndex = rowIndex - 1 ; columnIndex >= 1; columnIndex--)
        {
            cout << columnIndex;
        } 

        cout << endl;         
    }
}