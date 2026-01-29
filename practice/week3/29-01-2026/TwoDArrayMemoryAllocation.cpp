#include <iostream>
#include <limits>
#include <cctype>

void readValidatedInteger(int &value)
{
    while (true)
    {
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Please enter a valid integer value only.\n";
        }
        else
        {
            return;
        }
    }
}

bool hasExtraGarbage()
{
    char ch;
    while (std::cin.get(ch))
    {
        if (ch == '\n')
            break;
        if (!std::isspace(static_cast<unsigned char>(ch)))
            return true;
    }
    return false;
}

int main()
{
    int row, column;

    std::cout << "Enter the no of Row : ";
    readValidatedInteger(row);

    std::cout << "Enter the no of Column : ";
    readValidatedInteger(column);

    int **ptr = new int*[row];
    for (int i = 0; i < row; i++)
    {
        ptr[i] = new int[column];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            readValidatedInteger(ptr[i][j]);
        }
    }

    if (hasExtraGarbage())
    {
        std::cout << "Error: Extra invalid input detected.\n";

        for (int i = 0; i < row; i++)
        {
            delete[] ptr[i];
        }
            
        delete[] ptr;
    }
    else
    {
        std::cout << "\nOriginal Matrix:\n\n";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                std::cout << ptr[i][j] << " ";
            }
            std::cout << "\n";
        }


        int sum = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                sum += ptr[i][j];
            }
        }

        std::cout << "\nThe sum of matrix is " << sum << "\n";

    
        for (int i = 0; i < row; i++)
        {
            delete[] ptr[i];
        }
            
        delete[] ptr;

    }

    return 0;
}
