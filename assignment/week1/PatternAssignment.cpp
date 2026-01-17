#include <iostream>
#include <limits>

bool isEven(int sizeOfBell)
{
    return sizeOfBell % 2 == 0;
}

int toggleBit(int alternatingBit)
{
    return alternatingBit == 1 ? 0 : 1;
}

void printUpperAlternating01Pattern(int sizeOfBell, int rowIndex)
{
    int alternatingBit = 1;

    for (int columnIndex = 1; columnIndex <= rowIndex; columnIndex++)
    {
        std :: cout << alternatingBit << " ";
        alternatingBit = toggleBit(alternatingBit);
    }
}

void printUpperSpacePattern(int sizeOfBell, int rowIndex)
{
    int upperRowSpaceCount ;

    if(isEven(sizeOfBell))
    {
        upperRowSpaceCount = 2*(2*sizeOfBell - (2 * (rowIndex-1)) - 1);
    }
    else
    {
        upperRowSpaceCount = (2*(2*sizeOfBell - (2 * (rowIndex-1)) - 1) + 2);
    }

    for (int columnIndex = 1; columnIndex <= upperRowSpaceCount; columnIndex++)
    {
        std :: cout << " ";
    }
}

void printUpperPortion(int sizeOfBell)
{
    for (int rowIndex = 1; rowIndex <= sizeOfBell; rowIndex++)
    {
        printUpperAlternating01Pattern(sizeOfBell,rowIndex);
        printUpperSpacePattern(sizeOfBell,rowIndex);
        printUpperAlternating01Pattern(sizeOfBell,rowIndex);

        std :: cout << std :: endl;
    }
}

int computeMiddleRowLength(int sizeOfBell)
{  
    if(isEven(sizeOfBell))
    {
       return  (2 * sizeOfBell + 1);
    }
    else
    {
        return (2 * sizeOfBell + 2);
    }
}

void printMiddlePortion(int sizeOfBell)
{
    int alternatingBit = 1;
    int middleRowLength = computeMiddleRowLength(sizeOfBell);

    for (int columnIndex = 1; columnIndex <= middleRowLength; columnIndex++)
    {
        std :: cout << alternatingBit << " ";
        alternatingBit = toggleBit(alternatingBit);
    }

    std :: cout << std :: endl;
}

void printLowerAlternating01Pattern(int sizeOfBell, int rowIndex)
{
    int alternatingBit = 1;

    for (int columnIndex = 1; columnIndex <=  (sizeOfBell - rowIndex + 1); columnIndex++)
    {
        std :: cout << alternatingBit << " ";
        alternatingBit = toggleBit(alternatingBit);
    }
}


void printLowerSpacePattern(int sizeOfBell, int rowIndex)
{
    int lowerRowSpaceCount ;

    if(isEven(sizeOfBell))
    {
        lowerRowSpaceCount = 2*(2 * rowIndex - 1);
    }
    else
    {
        lowerRowSpaceCount = (2*(2 * rowIndex - 1) + 2);
    }

    for (int columnIndex = 1; columnIndex <= lowerRowSpaceCount; columnIndex++)
    {
        std :: cout << " ";
    }
}

void printLowerPortion(int sizeOfBell)
{
    for (int rowIndex = 1; rowIndex <= sizeOfBell; rowIndex++)
    {
        printLowerAlternating01Pattern(sizeOfBell , rowIndex);
        printLowerSpacePattern(sizeOfBell , rowIndex);
        printLowerAlternating01Pattern(sizeOfBell , rowIndex);
        
        std :: cout << std :: endl;
    }
}

bool containsGarbageAfterInput()
{
    char bufferCharacter;

    while(std::cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if (bufferCharacter != ' ' && bufferCharacter != '\t')
        {
            return true;
        }          
    }

    return false;
}

void readValidatedInteger(int &sizeOfBell)
{
    while (true)
    {
        std::cout << "\nplease enter size of bell: ";

        if (!(std::cin >> sizeOfBell))
        {
            std::cout << "Error: Please enter a valid integer value only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (containsGarbageAfterInput())
        {
            std::cout << "Error: Enter a valid input.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return; 
    }
}

void readValidCharacter(char &character)
{
    while (true)
    {
        std::cout << "\nDo you want to generate another pattern? (y/n): ";

        if(!(std::cin >> character))
        {
            std::cout << "Error: Please enter a valid character.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;

        }
        
        if (containsGarbageAfterInput())
        {
            std::cout << "Error: Enter a valid input.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (character == 'y' || character == 'Y' || character == 'n' || character == 'N')
        {
            break;
        }

        std::cout << "Not valid choice! Please enter y or n." << std::endl;
    }

    return;
}


int main()
{
    std::string userInputString;
    int sizeOfBell;
    char userChoice;

    do
    {
        readValidatedInteger(sizeOfBell);       
        printUpperPortion(sizeOfBell);
        printMiddlePortion(sizeOfBell);
        printLowerPortion(sizeOfBell);
        readValidCharacter(userChoice);
 
    } while (userChoice == 'y' || userChoice == 'Y');

    std::cout << "\nThank you for using the Pattern Generator!" << std::endl;

    return 0;
}

