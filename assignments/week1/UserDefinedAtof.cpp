#include <iostream>
#include <limits>

float parseUnsignedInteger(const std::string& input, size_t& currentStringIndex)
{
    float numericValue = 0.0f;

    while (currentStringIndex < input.length() && input[currentStringIndex] >= '0' && input[currentStringIndex] <= '9')
    {
        numericValue = numericValue * 10.0f + static_cast<float>(input[currentStringIndex] - '0');
        currentStringIndex++;
    }

    return numericValue;
}

float computePowerOfTen(int exponent)
{
    float result = 1.0f;

    if (exponent > 0)
    {
        for (int baseTenIteration = 0; baseTenIteration < exponent; ++baseTenIteration)
        {
            result *= 10.0f;
        }
    }
    else if (exponent < 0)
    {
        for (int baseTenIteration = 0; baseTenIteration < -exponent; ++baseTenIteration)
        {
            result /= 10.0f;
        }
    }

    return result;
}

void applyExponentIfPresent(const std::string& userInput, size_t& currentStringIndex, float& numericValue)
{
    if (currentStringIndex < userInput.length() && (userInput[currentStringIndex] == 'e' || userInput[currentStringIndex] == 'E'))
    {
        currentStringIndex++;

        int exponentSign = 1;

        if (currentStringIndex < userInput.length() && userInput[currentStringIndex] == '-')
        {
            exponentSign = -1;
            currentStringIndex++;
        }
        else if (currentStringIndex < userInput.length() && userInput[currentStringIndex] == '+')
        {
            currentStringIndex++;
        }

        int exponentMagnitude = static_cast<int>(parseUnsignedInteger(userInput, currentStringIndex));

        numericValue *= computePowerOfTen(exponentSign * exponentMagnitude);
    }
}

float userDefinedAtof(const std::string& userInput)
{
    size_t currentStringIndex = 0;
    int numberSign = 1;

    if (currentStringIndex < userInput.length() && userInput[currentStringIndex] == '-')
    {
        numberSign = -1;
        currentStringIndex++;
    }
    else if (currentStringIndex < userInput.length() && userInput[currentStringIndex] == '+')
    {
        currentStringIndex++;
    }

    float integerPart = parseUnsignedInteger(userInput, currentStringIndex);

    float fractionalPart = 0.0f;
    float fractionDivisor = 1.0f;

    if (currentStringIndex < userInput.length() && userInput[currentStringIndex] == '.')
    {
        currentStringIndex++;

        size_t fractionStartIndex = currentStringIndex;
        fractionalPart = parseUnsignedInteger(userInput, currentStringIndex);
        size_t fractionDigitCount = currentStringIndex - fractionStartIndex;

        for (size_t decimalShift = 0; decimalShift < fractionDigitCount; ++decimalShift)
        {
            fractionDivisor *= 10.0f;
        }
    }

    float finalResult = integerPart + (fractionalPart / fractionDivisor);

    applyExponentIfPresent(userInput, currentStringIndex, finalResult);

    return static_cast<float>(numberSign) * finalResult;
}

bool containsGarbageAfterInput()
{
    char bufferCharacter;

    while(std :: cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if(bufferCharacter != ' ' && bufferCharacter != '\t')
        {
            return true;
        }
    }

    return false;
}

void readUserInput(std :: string &userInput)
{
    while(true)
    {
        userInput.clear();

        if(!(std :: cin >> userInput))
        {
            std::cout << "Please enter valid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        char bufferCharacter;

        while(std :: cin.get(bufferCharacter) && bufferCharacter != '\n')
        {
            userInput += bufferCharacter;   
        }

        break;
    }
}

void readValidCharacter(char &userChoice)
{
    while(true)
    {
        std:: cout << "\nDo you want to enter another number? (y/n): ";

        if(!(std ::  cin >> userChoice))
        {
            std:: cout << "Error: Please enter a valid character.\n";
            std :: cin.clear();
            std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if(containsGarbageAfterInput())
        {
            std:: cout << "Error: Please enter a valid character.\n";
            std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (userChoice == 'y' || userChoice == 'Y' || userChoice == 'n' || userChoice == 'N')
        {
            break;
        }

        std :: cout << "Not valid choice! Please enter y or n." << std::endl;
    }

    return ;
}

int main()
{
    std :: string userInput;
    char userChoice;

    do
    {
        std :: cout << "\nEnter a floating point number: ";
        readUserInput(userInput);

        float result = userDefinedAtof(userInput);
        std :: cout << "Converted value: " << result << "\n";

        readValidCharacter(userChoice);

    } while (userChoice == 'y' || userChoice == 'Y');
    
    return 0;
}

