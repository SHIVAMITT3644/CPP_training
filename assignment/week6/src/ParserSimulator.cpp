#include <iostream>
#include "ParserSimulator.h"
#include "Input.h"
#include "Constants.h"
#include "JsonParsor.h"
#include "CsvParser.h"

void runJsonParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput("JSON");

    JsonParser jsonParser(fileName);

    if (!jsonParser.parseFile())
    {
        isOperationSuccessful = false;
    }
    else
    {
        std::cout << "\nFile Successfully Parsed.\n";

        if (!jsonParser.showParsedFile())
        {
            std::cout << "Error while displaying parsed data.\n";
            isOperationSuccessful = false;
        }
    }

    if (!isOperationSuccessful)
    {
        std::cout << "\nJSON Parser Operation Completed With Errors.\n";
    }
    else
    {
        std::cout << "\nJSON Parser Operation Completed Successfully.\n";
    }
}

void runCsvParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput("CSV");

    CsvParser csvParser(fileName);

    if (!csvParser.parseFile())
    {
        isOperationSuccessful = false;
    }
    else
    {
        std::cout << "\nFile Successfully Parsed.\n";

        if (!csvParser.showParsedFile())
        {
            std::cout << "Error while displaying parsed data.\n";
            isOperationSuccessful = false;
        }
    }

    if (!isOperationSuccessful)
    {
        std::cout << "\nCSV Parser Operation Completed With Errors.\n";
    }
    else
    {
        std::cout << "\nCSV Parser Operation Completed Successfully.\n";
    }
}

#include "XmlParser.h"

void runXmlParser()
{
    std::string fileName;
    bool isOperationSuccessful = true;

    fileName = readFileInput("XML");

    XmlParser xmlParser(fileName);

    if (!xmlParser.parseFile())
    {
        isOperationSuccessful = false;
    }
    else
    {
        std::cout << "\nFile Successfully Parsed.\n";

        if (!xmlParser.showParsedFile())
        {
            std::cout << "Error while displaying parsed data.\n";
            isOperationSuccessful = false;
        }
    }

    if (!isOperationSuccessful)
    {
        std::cout << "\nXML Parser Operation Completed With Errors.\n";
    }
    else
    {
        std::cout << "\nXML Parser Operation Completed Successfully.\n";
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