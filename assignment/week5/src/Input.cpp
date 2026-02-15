#include <iostream>
#include <string>
#include <istream>
#include <termios.h>
#include <unistd.h>
#include "Constants.h"

void readCompleteLineInput(std::istream &inputStream, std::string &output,  const std::string &message)
{
    while (true)
    {
        output.clear();
        inputStream >> std::noskipws;

        std::cout << message;

        char currentCharacter;
        bool hasNonSpaceCharacter = false;

        while (inputStream >> currentCharacter)
        {
            if (currentCharacter == '\n')
            {
                break;
            }

            output.push_back(currentCharacter);

            if (currentCharacter != ' ' && currentCharacter != '\t')
            {
                hasNonSpaceCharacter = true;
            }
        }

        inputStream >> std::skipws;

        if (!hasNonSpaceCharacter)
        {
            std::cout << INVALID_STRING_INPUT_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }
}

bool hasValidNumericBoundaries(const std::string &input)
{
    bool isValid = true;

    if (input.empty())
    {
        isValid = false;
    }
    else if (input.front() == ' ' || input.back() == ' ')
    {
        isValid = false;
    }

    return isValid;
}

bool isDigit(char character)
{
    return (character >= '0' && character <= '9');
}

int getStartIndex(const std::string &input, bool &isValid)
{
    int startIndex = 0;

    if (input[0] == '-')
    {
        startIndex = 1;

        if (input.length() == 1)
        {
            isValid = false;
        }
    }

    return startIndex;
}

bool validateIntegerNumber(const std::string &input, int &finalValue)
{
    bool isValid = true;
    finalValue = 0;

    if (!hasValidNumericBoundaries(input))
    {
        isValid = false;
    }
    else
    {
        bool isNegative = false;
        int startIndex = 0;

        startIndex = getStartIndex(input, isValid);

        if (startIndex == 1)
        {
            isNegative = true;
        }
        else
        {
            isNegative = false;
        }

        if (isValid == true)
        {
            for (int i = startIndex; i < input.length(); i++)
            {
                if (isDigit(input[i]))
                {
                    finalValue = finalValue * 10 + (input[i] - '0');
                }
                else
                {
                    isValid = false;
                }
            }

            if (isValid == true)
            {
                if (isNegative == true)
                {
                    finalValue = -finalValue;
                }
            }
            else
            {
                finalValue = 0;
            }
        }
    }

    return isValid;
}

bool parseDecimalCore(const std::string &input, int startIndex, double &value)
{
    bool isValid = true;
    bool readingFraction = false;
    double divisor = 1.0;
    int dotCount = 0;
    value = 0.0;

    for (int i = startIndex; i < input.length() && isValid; i++)
    {
        char character = input[i];

        if (character == '.')
        {
            dotCount++;
            readingFraction = true;

            if (dotCount > 1)
            {
                isValid = false;
            }
        }
        else if (isDigit(character))
        {
            if (!readingFraction)
            {
                value = value * 10 + (character - '0');
            }
            else
            {
                divisor *= 10;
                value += (character - '0') / divisor;
            }
        }
        else
        {
            isValid = false;
        }
    }

    return isValid;
}

bool validateDecimalNumber(const std::string &input, double &finalValue)
{
    bool isValid = true;
    finalValue = 0.0;

    if (!hasValidNumericBoundaries(input))
    {
        isValid = false;
    }
    else
    {
        bool isNegative = false;
        int startIndex = getStartIndex(input, isValid);

        if (isValid)
        {
            isNegative = (startIndex == 1);
            isValid = parseDecimalCore(input, startIndex, finalValue);

            if (isValid && isNegative)
            {
                finalValue = -finalValue;
            }
        }
    }

    return isValid;
}

int readValidUserInput(const std::string &inputMessage)
{
    bool isInputValid = false;
    int validatedValue = 0;
    std::string rawInput;

    while (!isInputValid)
    {
        readCompleteLineInput(std::cin, rawInput, inputMessage);

        isInputValid = validateIntegerNumber(rawInput, validatedValue);

        if (!isInputValid)
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }

    return validatedValue;
}

double readValidFloatingInput(const std::string &inputMessage)
{
    bool isInputValid = false;
    double validatedValue = 0.0;
    std::string rawInput;

    while (!isInputValid)
    {
        readCompleteLineInput(std::cin, rawInput, inputMessage);

        isInputValid = validateDecimalNumber(rawInput, validatedValue);

        if (!isInputValid)
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }

    return validatedValue;
}

std::string readHiddenPassword(const std::string& message)
{
    std::string password;
    char ch;
    std::cout << message;

    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true)
    {
        ch = getchar();

        if (ch == '\n')
        {
            break;
        }
            
        if (ch == 127 || ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << "*";
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cout << std::endl;
    return password;
}
