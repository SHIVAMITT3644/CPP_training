#include <iostream>
#include <fstream>
#include "CsvParser.h"
#include "rapidcsv.h"
#include "Constants.h"

CsvParser::CsvParser(const std::string& fileName): fileName(fileName)
{
}

bool CsvParser::openFile(std::ifstream& file, bool& isOpened)
{
    file.open(RESOURCE_FOLDER_CONSTANT + fileName);
    if (!file.is_open())
    {
        std::cerr << CSV_FILE_NOT_OPEN_MESSAGE;
        isOpened = false;
    }
    else
    {
        isOpened = true;
    }
    return isOpened;
}

bool CsvParser::isFileEmpty(std::ifstream& file, bool& isEmpty)
{
    if (file.peek() == EOF)
    {
        std::cerr << CSV_EMPTY_ERROR_MESSAGE;
        isEmpty = true;
    }
    else
    {
        isEmpty = false;
    }
    return isEmpty;
}

bool CsvParser::parseCsv(std::ifstream& file, bool& isParsedSuccessfully)
{
    try
    {
        csvDocument = rapidcsv::Document(file);
        isParsedSuccessfully = true;
    }
    catch (const std::exception&)
    {
        std::cerr << CSV_PARSING_ERROR_MESSAGE;
        std::cerr << "---------------------------------\n";
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << CSV_UNKNOWN_ERROR_MESSAGE;
        isParsedSuccessfully = false;
    }
    return isParsedSuccessfully;
}

bool CsvParser::parseFile()
{
    bool isParsedSuccessfully = true;
    bool fileOpenedSuccessfully = false;
    bool fileIsEmpty = false;

    std::ifstream file;

    openFile(file, fileOpenedSuccessfully);

    if (fileOpenedSuccessfully)
    {
        isFileEmpty(file, fileIsEmpty);

        if (!fileIsEmpty)
        {
            parseCsv(file, isParsedSuccessfully);
        }
        else
        {
            isParsedSuccessfully = false;
        }
    }
    else
    {
        isParsedSuccessfully = false;
    }

    file.close();
    return isParsedSuccessfully;
}
bool CsvParser::displayCell(const std::string& cellValue, size_t columnIndex, size_t totalColumns)
{
    std::cout << cellValue;

    if (columnIndex < totalColumns - 1)
    {
        std::cout << " | ";
    }
    return true;
}

bool CsvParser::displayRow(size_t rowIndex, size_t totalColumns, bool& isDisplayedSuccessfully)
{
    for (size_t columnIndex = 0; columnIndex < totalColumns; ++columnIndex)
    {
        try
        {
            std::string cellValue = csvDocument.GetCell<std::string>(columnIndex, rowIndex);
            displayCell(cellValue, columnIndex, totalColumns);
        }
        catch (const std::exception&)
        {
            std::cerr << CSV_ERROR_DISPLAYING_MESSAGE << "\n";
            isDisplayedSuccessfully = false;
        }
        catch (...)
        {
            std::cerr << CSV_EMPTY_ERROR_MESSAGE;
            isDisplayedSuccessfully = false;
        }
    }

    std::cout << "\n";
    return isDisplayedSuccessfully;
}

bool CsvParser::showParsedFile()
{
    bool isDisplayedSuccessfully = true;

    try
    {
        std::cout << CSV_DATA_TEMPLATE;

        size_t totalRows = csvDocument.GetRowCount();
        size_t totalColumns = csvDocument.GetColumnCount();

        for (size_t rowIndex = 0; rowIndex < totalRows; ++rowIndex)
        {
            displayRow(rowIndex, totalColumns, isDisplayedSuccessfully);
        }

        std::cout << FORMATING_MESSAGE;
    }
    catch (const std::exception&)
    {
        std::cerr << CSV_ERROR_DISPLAYING_MESSAGE << "\n";
        isDisplayedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << CSV_EMPTY_ERROR_MESSAGE;
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}
