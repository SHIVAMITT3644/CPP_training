#include <iostream>
#include <fstream>
#include "json.hpp"
#include "JsonParsor.h"
#include "Constants.h"

JsonParser::JsonParser(const std::string& fileName) : fileName(fileName)
{
}

bool JsonParser::openFile(std::ifstream& file, bool& isOpened)
{
    file.open(RESOURCE_FOLDER_CONSTANT + fileName);
    if (!file.is_open())
    {
        std::cerr << JSON_FILE_NOT_OPEN_MESSAGE;
        isOpened = false;
    }
    else
    {
        isOpened = true;
    }
    return isOpened;
}

bool JsonParser::isFileEmpty(std::ifstream& file, bool& isEmpty)
{
    if (file.peek() == EOF)
    {
        std::cerr << JSON_EMPTY_ERROR_MESSAGE;
        isEmpty = true;
    }
    else
    {
        isEmpty = false;
    }
    return isEmpty;
}   

bool JsonParser::parseJson(std::ifstream& file, bool& isParsedSuccessfully)
{
    try
    {
        jsonObject = nlohmann::json::parse(file);
        isParsedSuccessfully = true;
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cerr << JSON_PARSING_ERROR_MESSAGE;
        std::cerr << "Byte position: " << error.byte << "\n";
        std::cerr << FORMATING_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (const nlohmann::json::exception&)
    {
        std::cerr << JSON_EXCEPTION_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (const std::exception&)
    {
        std::cerr << STANDARD_EXCEPTION_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << UNKNOWN_ERROR_MESSAGE;
        isParsedSuccessfully = false;
    }
    return isParsedSuccessfully;
}

bool JsonParser::parseFile()
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
            parseJson(file, isParsedSuccessfully);
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

void JsonParser::showJsonValue(const nlohmann::ordered_json& jsonData, int indentationLevel)
{
    std::string indentation(indentationLevel, ' ');
    std::cout << indentation << jsonData << "\n";
}

void JsonParser::showJsonObject(const nlohmann::ordered_json& jsonData, int indentationLevel)
{
    std::string indentation(indentationLevel, ' ');

    for (auto objectIterator = jsonData.begin(); objectIterator != jsonData.end(); ++objectIterator)
    {
        const std::string& keyName = objectIterator.key();
        const nlohmann::ordered_json& valueData = objectIterator.value();

        std::cout << indentation << keyName << " : ";

        if (valueData.is_structured())
        {
            std::cout << "\n";
            showJson(valueData, indentationLevel + 4);
        }
        else
        {
            showJsonValue(valueData, 0);
        }
    }
}

void JsonParser::showJsonArray(const nlohmann::ordered_json& jsonData, int indentationLevel)
{
    size_t elementIndex = 1;
    for (const nlohmann::ordered_json& arrayElement : jsonData)
    {
        if (indentationLevel == 0)
        {
            std::cout << "Element " << elementIndex << ":\n";
            showJson(arrayElement, indentationLevel + 4);
            std::cout << FORMATING_MESSAGE;
        }
        else
        {
            showJson(arrayElement, indentationLevel + 4);
        }
        ++elementIndex;
    }
}

void JsonParser::showJson(const nlohmann::ordered_json& jsonData, int indentationLevel)
{
    if (jsonData.is_object())
    {
        showJsonObject(jsonData, indentationLevel);
    }
    else if (jsonData.is_array())
    {
        showJsonArray(jsonData, indentationLevel);
    }
    else
    {
        showJsonValue(jsonData, indentationLevel);
    }
}

bool JsonParser::showParsedFile()
{
    bool isDisplayedSuccessfully = true;

    try
    {
        std::cout << JSON_DATA_TEMPLATE;

        showJson(jsonObject,0);

        std::cout << FORMATING_MESSAGE;
    }
    catch (const nlohmann::json::exception& )
    {
        std::cerr << JSON_ERROR_DISPLAYING_MESSAGE  << "\n";
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}
