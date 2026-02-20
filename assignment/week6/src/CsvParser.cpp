#include <iostream>
#include <fstream>
#include "CsvParser.h"
#include "rapidcsv.h"

CsvParser::CsvParser(const std::string& fileName)
{
    this->fileName = fileName;
}

bool CsvParser::parseFile()
{
    bool isParsedSuccessfully = true;

    std::ifstream fileOpened("resources/" + fileName);

    try
    {
        if (!fileOpened.is_open())
        {
            std::cerr << "Error: Unable to open CSV file.\n";
            isParsedSuccessfully = false;
        }
        else if (fileOpened.peek() == std::ifstream::traits_type::eof())
        {
            std::cerr << "Error: CSV file is empty.\n";
            isParsedSuccessfully = false;
        }
        else
        {
            rapidcsv::Document csvDocument("resources/" + fileName);
        }
    }
    catch (const std::exception& exceptionObject)
    {
        std::cerr << "\n---------------------------------\n";
        std::cerr << "CSV Parse Error:\n\n";
        std::cerr << "Message: " << exceptionObject.what() << "\n";
        std::cerr << "---------------------------------\n";
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred while parsing CSV.\n";
        isParsedSuccessfully = false;
    }

    fileOpened.close();

    return isParsedSuccessfully;
}

bool CsvParser::showParsedFile()
{
    bool isDisplayedSuccessfully = true;

    try
    {
        std::cout << "\n=========== CSV DATA ===========\n\n";

        rapidcsv::Document csvDocument("resources/" + fileName);

        size_t totalRows = csvDocument.GetRowCount();
        size_t totalColumns = csvDocument.GetColumnCount();

        for (size_t rowIndex = 0; rowIndex < totalRows; ++rowIndex)
        {
            for (size_t columnIndex = 0; columnIndex < totalColumns; ++columnIndex)
            {
                std::string cellValue = csvDocument.GetCell<std::string>(columnIndex, rowIndex);
                std::cout << cellValue;

                if (columnIndex < totalColumns - 1)
                {
                    std::cout << " | ";
                }
            }

            std::cout << "\n";
        }

        std::cout << "\n=================================\n";
    }
    catch (const std::exception& exceptionObject)
    {
        std::cerr << "Error displaying CSV: " << exceptionObject.what() << "\n";
        isDisplayedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred while displaying CSV.\n";
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}

CsvParser::~CsvParser()
{
}