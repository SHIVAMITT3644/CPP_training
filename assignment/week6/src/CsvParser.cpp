#include <iostream>
#include <fstream>
#include "CsvParser.h"
#include "rapidcsv.h"
#include "Constants.h"

CsvParser::CsvParser(const std::string& fileName): fileName(fileName)
{
}

bool CsvParser::parseFile()
{
    bool isParsedSuccessfully = true;

    std::ifstream fileOpened(RESOURCE_FOLDER_CONSTANT + fileName);

    try
    {
        if (!fileOpened.is_open())
        {
            std::cerr << CSV_FILE_NOT_OPEN_MESSAGE;
            isParsedSuccessfully = false;
        }
        else if (fileOpened.peek() == EOF)
        {
            std::cerr << CSV_EMPTY_ERROR_MESSAGE;
            isParsedSuccessfully = false;
        }
        else
        {
            csvDocument = rapidcsv::Document(fileOpened);
        }
    }
    catch (const std::exception& exceptionObject)
    {
        std::cerr << CSV_PARSING_ERROR_MESSAGE;
        std::cerr << "Message: " << exceptionObject.what() << "\n";
        std::cerr << "---------------------------------\n";
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << CSV_UNKNOWN_ERROR_MESSAGE;
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
        std::cout <<  CSV_DATA_TEMPLATE;

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

        std::cout << FORMATING_MESSAGE;
    }
    catch (const std::exception& exceptionObject)
    {
        std::cerr << CSV_ERROR_DISPLAYING_MESSAGE << exceptionObject.what() << "\n";
        isDisplayedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << CSV_EMPTY_ERROR_MESSAGE;
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}
