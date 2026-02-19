#include <iostream>
#include <fstream>
#include <string>

int main()
{
    try
    {
        std::ofstream outFile("example.txt");

        if (!outFile.is_open())
            throw std::runtime_error("Failed to open file for writing");

        outFile << "Hello, this is a file handling example.\n";
        outFile << "Learning C++ file operations.\n";

        outFile.close();

        if (outFile.fail())
            throw std::runtime_error("Error occurred while closing the file after writing");

        std::cout << "Data written successfully.\n";


        //Reading from File
        std::ifstream inFile("example.txt");

        if (!inFile.is_open())
            throw std::runtime_error("Failed to open file for reading");

        std::string line;

        std::cout << "\nReading from file:\n";

        while (std::getline(inFile, line))
        {
            std::cout << line << std::endl;
        }

        inFile.close();

        if (inFile.fail())
            throw std::runtime_error("Error occurred while closing the file after reading");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}