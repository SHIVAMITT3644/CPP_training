#include <iostream>
using namespace std;

#define MAX_inputString_LENGTH 50

double userDefinedAtof(const char* inputString)
{
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 1.0;
    int sign = 1;

    while(*inputString ==  ' ')
    {
        inputString++;
    }

    if(*inputString == '-')
    {
        sign = -1;
        inputString++;
    }
    else if(*inputString == '+')
    {
        inputString++;
    }

    while(*inputString >= '0' && *inputString <= '9')
    {
        result = result * 10 + (*inputString - '0');
        inputString++;
    }

    if(*inputString == '.')
    {
        inputString++;

        while(*inputString >= '0' && *inputString <= '9')
        {
            fraction = fraction * 10 + (*inputString - '0');
            divisor *= 10;
            inputString++;
        }
    }

    return sign * (result + fraction / divisor);
}

int main()
{
    char inputString[MAX_inputString_LENGTH];

    cout << "Enter a floating point number: ";
    cin.getline(inputString,MAX_inputString_LENGTH);

    double value = userDefinedAtof(inputString);
    cout << "Converted value: " << value << endl;

    return 0;
}