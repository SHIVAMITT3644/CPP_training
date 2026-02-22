#include <iostream>
#include "ParserSimulator.h"
#include "Input.h"
#include "Constants.h"
#include "JsonParsor.h"
#include "CsvParser.h"
#include "XmlParser.h"

void runJsonParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput(JSON);

    if (!fileName.empty())
    {
        JsonParser jsonParser(fileName);

        if (!jsonParser.parseFile())
        {
            isOperationSuccessful = false;
        }
        else
        {
            std::cout << FILE_PARSED_MESSAGE;

            if (!jsonParser.showParsedFile())
            {
                std::cout << FILE_PARSED_FAILED_MESSAGE;
                isOperationSuccessful = false;
            }
        }

        if (isOperationSuccessful)
        {
            std::cout << "\n" << JSON << OPERATION_SUCCESS_MESSAGE;
        }
        else
        {
            std::cout << "\n" << JSON << OPERATION_FAILED_MESSAGE;
        }
    }
    else
    {
        std::cout << "\n" << JSON << OPERATION_CANCELLED_MESSAGE;
    }
}

void runCsvParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput(CSV);

    if (!fileName.empty())
    {
        CsvParser csvParser(fileName);

        if (!csvParser.parseFile())
        {
            isOperationSuccessful = false;
        }
        else
        {
            std::cout << FILE_PARSED_MESSAGE;

            if (!csvParser.showParsedFile())
            {
                std::cout << FILE_PARSED_FAILED_MESSAGE;
                isOperationSuccessful = false;
            }
        }

        if (isOperationSuccessful)
        {
            std::cout << "\n" << CSV << OPERATION_SUCCESS_MESSAGE;
        }
        else
        {
            std::cout << "\n" << CSV << OPERATION_FAILED_MESSAGE;
        }
    }
    else
    {
        std::cout << "\n" << CSV  << OPERATION_CANCELLED_MESSAGE;
    }
}

void runXmlParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput(XML);

    if (!fileName.empty())
    {
        XmlParser xmlParser(fileName);

        if (!xmlParser.parseFile())
        {
            isOperationSuccessful = false;
        }
        else
        {
            std::cout << FILE_PARSED_MESSAGE;

            if (!xmlParser.showParsedFile())
            {
                std::cout << FILE_PARSED_FAILED_MESSAGE;
                isOperationSuccessful = false;
            }
        }

        if (isOperationSuccessful)
        {
            std::cout << "\n" << XML << OPERATION_SUCCESS_MESSAGE;
        }
        else
        {
            std::cout << "\n" << XML << OPERATION_FAILED_MESSAGE;
        }
    }
    else
    {
        std::cout << "\n" << XML << OPERATION_CANCELLED_MESSAGE;
    }
}

bool runParserSimulator()
{
    bool isSuccess = false;
    int parserUserChoice = 0;
    
    while (parserUserChoice != 4)
    {
        std::cout << MAIN_MENU_BODY;

        parserUserChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        switch (parserUserChoice)
        {
        case 1:
            runJsonParser();
            break;

        case 2:
            runCsvParser();
            break;

        case 3:
        runXmlParser();
            break;

        case 4:
            std::cout << EXIT_PROGRAM_MESSAGE;
            break;

        default:
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
            break;
        }
    }
    isSuccess = true;

    return isSuccess;
}
