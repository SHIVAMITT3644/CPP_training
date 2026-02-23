#include <iostream>
#include "ParserSimulator.h"
#include "Input.h"
#include "Constants.h"
#include "JsonParsor.h"
#include "CsvParser.h"
#include "XmlParser.h"

void runParser(Parser* parser, std::string fileType)
{
    bool isOperationSuccessful = true;

    if (parser != nullptr)
    {
        if (!parser->parseFile())
        {
            isOperationSuccessful = false;
        }
        else
        {
            std::cout << FILE_PARSED_MESSAGE;

            if (!parser->showParsedFile())
            {
                std::cout << FILE_PARSED_FAILED_MESSAGE;
                isOperationSuccessful = false;
            }
        }

        if (isOperationSuccessful)
        {
            std::cout << "\n" << fileType << OPERATION_SUCCESS_MESSAGE;
        }
        else
        {
            std::cout << "\n" << fileType << OPERATION_FAILED_MESSAGE;
        }
    }
    else
    {
        std::cout << "\n" << fileType << OPERATION_CANCELLED_MESSAGE;
    }

    delete parser;
}

void parseFileByType(const std::string& fileType)
{
    std::string fileName = readFileInput(fileType);

    if (fileName.empty())
    {
        std::cout << "\n" << fileType << OPERATION_CANCELLED_MESSAGE;
    }
    else
    {
        Parser* parser = nullptr;

        if (fileType == JSON)
        {
            parser = new JsonParser(fileName);
        }
        else if (fileType == CSV)
        {
            parser = new CsvParser(fileName);
        }
        else if (fileType == XML)
        {
            parser = new XmlParser(fileName);
        }

        runParser(parser, fileType);
    }

}

void handleParserChoice(int choice)
{
    switch (choice)
    {
        case 1:
            parseFileByType(JSON);
            break;

        case 2:
            parseFileByType(CSV);
            break;

        case 3:
            parseFileByType(XML);
            break;

        case 4:
            std::cout << EXIT_PROGRAM_MESSAGE;
            break;

        default:
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
            break;
    }
}

bool runParserSimulator()
{
    int parserUserChoice = 0;
    bool isSuccess = false;

    while (parserUserChoice != 4)
    {
        std::cout << MAIN_MENU_BODY;
        parserUserChoice = readValidUserInput(ENTER_CHOICE_PROMPT);
        handleParserChoice(parserUserChoice);
    }

    isSuccess = true;
    return isSuccess;
}
