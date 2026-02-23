#include <iostream>
#include <fstream>
#include "json.hpp"
#include "JsonParsor.h"
#include "Constants.h"

JsonParser::JsonParser(const std::string& fileName) : fileName(fileName)
{
}

bool JsonParser::parseFile()
{
    bool isParsedSuccessfully = true;

    std::ifstream fileOpened(RESOURCE_FOLDER_CONSTANT + fileName);

    try
    {
        if (!fileOpened.is_open())
        {
            std::cerr << JSON_FILE_NOT_OPEN_MESSAGE;
            isParsedSuccessfully = false;
        }
        else if (fileOpened.peek() == EOF)
        {
            std::cerr << JSON_EMPTY_ERROR_MESSAGE;
            isParsedSuccessfully = false;
        }
        else
        {
            jsonObject = nlohmann::json::parse(fileOpened);
        }     
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cerr << JSON_PARSING_ERROR_MESSAGE;
        std::cerr << "Byte position: " << error.byte << "\n";
        std::cerr << FORMATING_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (const nlohmann::json::exception& )
    {
        std::cerr << JSON_EXCEPTION_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (const std::exception& )
    {
        std::cerr << STANDARD_EXCEPTION_MESSAGE;
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << UNKNOWN_ERROR_MESSAGE;
        isParsedSuccessfully = false;
    }

    fileOpened.close();

    return isParsedSuccessfully;
}

void JsonParser::showJson(const nlohmann::ordered_json& jsonData, int indentationLevel)
{
    std::string indentation(indentationLevel, ' ');

    if (jsonData.is_object())
    {
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
                std::cout << valueData << "\n";
            }
        }
    }
    else if (jsonData.is_array())
    {
        size_t elementIndex = 1;

        for (const auto& arrayElement : jsonData)
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
    else
    {
        std::cout << indentation << jsonData << "\n";
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
