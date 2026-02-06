#include "CheckUserInputValidity.h"

bool CheckUserInputValidity::validateWholeNumber(const std::string& inputFromUser, int& value)
{
    bool isInputValid = true;
    value = 0;

    if (inputFromUser.length() == 0)
    {
        isInputValid = false;
    }
    else if (inputFromUser[0] == ' ' || inputFromUser[inputFromUser.length() - 1] == ' ')
    {
        isInputValid = false;
    }
    else
    {
        for (int position = 0; position < inputFromUser.length(); position++)
        {
            char currentCharacter = inputFromUser[position];

            if (currentCharacter < '0' || currentCharacter > '9')
            {
                isInputValid = false;
                break;
            }

            value = value * 10 + (currentCharacter - '0');
        }
    }

    return isInputValid;
}

bool CheckUserInputValidity::hasValidDecimalFormatBoundaries(const std::string& inputFromUser)
{
    bool isValid = true;

    if (inputFromUser.length() == 0)
    {
        isValid = false;
    }
    else if (inputFromUser[0] == ' ' || inputFromUser[inputFromUser.length() - 1] == ' ')
    {
        isValid = false;
    }

    return isValid;
}

bool CheckUserInputValidity::convertDecimalStringToValue(const std::string& inputFromUser, double& value)
{
    bool isValid = true;

    int decimalPointCount = 0;
    bool readingFractionalPart = false;
    double fractionalDivisor = 1.0;

    for (int position = 0; position < inputFromUser.length() && isValid; position++)
    {
        char currentCharacter = inputFromUser[position];

        if (currentCharacter == '.')
        {
            decimalPointCount++;

            if (decimalPointCount > 1)
            {
                isValid = false;
            }
            else
            {
                readingFractionalPart = true;
            }
        }
        else if (currentCharacter >= '0' && currentCharacter <= '9')
        {
            if (!readingFractionalPart)
            {
                value = value * 10 + (currentCharacter - '0');
            }
            else
            {
                fractionalDivisor *= 10;
                value += (currentCharacter - '0') / fractionalDivisor;
            }
        }
        else
        {
            isValid = false;
        }
    }

    return isValid;
}

bool CheckUserInputValidity::validateDecimalNumber(const std::string& inputFromUser, double& value)
{
    bool isValid = true;
    value = 0.0;

    if (!hasValidDecimalFormatBoundaries(inputFromUser))
    {
        isValid = false;
    }
    else
    {
        isValid = convertDecimalStringToValue(inputFromUser, value);
    }

    return isValid;
}
