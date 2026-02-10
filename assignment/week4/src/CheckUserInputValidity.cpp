#include "CheckUserInputValidity.h"

bool CheckUserInputValidity::validateWholeNumber(const std::string& inputFromUser, int& finalValue)
{
    bool isInputValid = true;
    finalValue = 0;

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

            finalValue = finalValue * 10 + (currentCharacter - '0');
        }
    }

    return isInputValid;
}

bool CheckUserInputValidity::hasValidDecimalFormatBoundaries(const std::string& inputFromUser)
{
    bool isInputValid = true;

    if (inputFromUser.length() == 0)
    {
        isInputValid = false;
    }
    else if (inputFromUser[0] == ' ' || inputFromUser[inputFromUser.length() - 1] == ' ')
    {
        isInputValid = false;
    }

    return isInputValid;
}

bool CheckUserInputValidity::convertDecimalStringToValue(const std::string& inputFromUser, double& finalValue)
{
    bool isInputValid = true;

    int decimalPointCount = 0;
    bool readingFractionalPart = false;
    double fractionalDivisor = 1.0;

    for (int position = 0; position < inputFromUser.length() && isInputValid; position++)
    {
        char currentCharacter = inputFromUser[position];

        if (currentCharacter == '.')
        {
            decimalPointCount++;

            if (decimalPointCount > 1)
            {
                isInputValid = false;
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
                finalValue = finalValue * 10 + (currentCharacter - '0');
            }
            else
            {
                fractionalDivisor *= 10;
                finalValue += (currentCharacter - '0') / fractionalDivisor;
            }
        }
        else
        {
            isInputValid = false;
        }
    }

    return isInputValid;
}

bool CheckUserInputValidity::validateDecimalNumber(const std::string& inputFromUser, double& finalValue)
{
    bool isInputValid = true;
    finalValue = 0.0;

    if (!hasValidDecimalFormatBoundaries(inputFromUser))
    {
        isInputValid = false;
    }
    else
    {
        isInputValid = convertDecimalStringToValue(inputFromUser, finalValue);
    }

    return isInputValid;
}
