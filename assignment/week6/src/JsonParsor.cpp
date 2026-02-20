    #include <iostream>
    #include <fstream>
    #include "json.hpp"
    #include "JsonParsor.h"

    JsonParser :: JsonParser(const std::string& fileName)
    {
        this->fileName = fileName;
    }

    bool JsonParser::parseFile()
    {
        bool isParsedSuccessfully = true;

        std::ifstream fileOpened("resources/" + fileName);

        try
        {
            if (!fileOpened.is_open())
            {
                std::cerr << "Error: Unable to open file.\n";
                isParsedSuccessfully = false;
            }
            else if (fileOpened.peek() == std::ifstream::traits_type::eof())
            {
                std::cerr << "Error: File is empty.\n";
                isParsedSuccessfully = false;
            }
            else
            {
                fileOpened >> db;
            }

            
        }
        catch (const nlohmann::json::parse_error& e)
        {
            std::cerr << "\n---------------------------------\n";
            std::cerr << "JSON Parse Error:\n\n";
            std::cerr << "Message:   " << e.what() << "\n";
            std::cerr << "Byte position: " << e.byte << "\n";
            std::cerr << "---------------------------------\n";
            isParsedSuccessfully = false;
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON Exception:\n";
            std::cerr << e.what() << "\n";
            isParsedSuccessfully = false;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Standard Exception:\n";
            std::cerr << e.what() << "\n";
            isParsedSuccessfully = false;
        }
        catch (...)
        {
            std::cerr << "Unknown error occurred.\n";
            isParsedSuccessfully = false;
        }

        fileOpened.close();

        return isParsedSuccessfully;
    }

    void JsonParser::printJson(const nlohmann::ordered_json& jsonData, int indentationLevel)
    {
        std::string indentation(indentationLevel, ' ');

        if (jsonData.is_object())
        {
            for (auto objectIterator = jsonData.begin(); objectIterator != jsonData.end(); ++objectIterator)
            {
                const std::string& keyName = objectIterator.key();
                const nlohmann::json& valueData = objectIterator.value();

                std::cout << indentation << keyName << " : ";

                if (valueData.is_structured())
                {
                    std::cout << "\n";
                    printJson(valueData, indentationLevel + 4);
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
                    printJson(arrayElement, indentationLevel + 4);
                    std::cout << "\n=================================\n";
                }
                else
                {
                    printJson(arrayElement, indentationLevel + 4);
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
            std::cout << "\n=========== JSON DATA ===========\n\n";

            printJson(db,0);

            std::cout << "\n=================================\n";
        }
        catch (const nlohmann::json::exception& exceptionObject)
        {
            std::cerr << "Error displaying JSON: " << exceptionObject.what() << "\n";
            isDisplayedSuccessfully = false;
        }

        return isDisplayedSuccessfully;
    }

    JsonParser :: ~JsonParser()
    {

    }