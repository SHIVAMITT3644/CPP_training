#include <iostream>
#include "XmlParser.h"

using namespace tinyxml2;

XmlParser::XmlParser(const std::string& fileName)
{
    this->fileName = fileName;
}

bool XmlParser::parseFile()
{
    bool isParsedSuccessfully = true;

    try
    {
        XMLError error = xmlDocument.LoadFile(("resources/" + fileName).c_str());

        if (error != XML_SUCCESS)
        {
            std::cerr << "\n---------------------------------\n";
            std::cerr << "XML Parse Error:\n";
            std::cerr << "Message: " << xmlDocument.ErrorStr() << "\n";
            std::cerr << "Line: " << xmlDocument.ErrorLineNum() << "\n";
            std::cerr << "---------------------------------\n";
            isParsedSuccessfully = false;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Standard Exception while parsing XML: " << e.what() << "\n";
        isParsedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred while parsing XML.\n";
        isParsedSuccessfully = false;
    }

    return isParsedSuccessfully;
}

void XmlParser::printNode(XMLNode* node, int indentationLevel)
{
    if (!node) return;

    std::string indentation(indentationLevel, ' ');

    if (XMLElement* element = node->ToElement())
    {
        std::cout << indentation << element->Name() << " : ";

        // If element has child elements, print newline and recurse
        if (element->FirstChildElement())
        {
            std::cout << "\n";
            for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                printNode(child, indentationLevel + 4);
            }
        }
        else if (element->GetText())
        {
            // Print the text value
            std::cout << element->GetText() << "\n";
        }
        else
        {
            std::cout << "\n";
        }
    }
}

bool XmlParser::showParsedFile()
{
    bool isDisplayedSuccessfully = true;

    try
    {
        std::cout << "\n=========== XML DATA ===========\n\n";

        // Get root element (e.g., <students>)
        XMLElement* root = xmlDocument.RootElement();
        if (!root)
        {
            std::cerr << "Error: XML Document is empty.\n";
            isDisplayedSuccessfully = false;
        }
        else
        {
            int elementCount = 1;
            // Iterate through all child elements of root
            for (XMLElement* student = root->FirstChildElement(); student != nullptr; student = student->NextSiblingElement())
            {
                std::cout << "Element " << elementCount << ":\n";
                printNode(student, 4);  // recursively print student
                std::cout << "\n=================================\n";
                ++elementCount;
            }
        }

        std::cout << "\n=================================\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error displaying XML: " << e.what() << "\n";
        isDisplayedSuccessfully = false;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred while displaying XML.\n";
        isDisplayedSuccessfully = false;
    }

    return isDisplayedSuccessfully;
}

XmlParser::~XmlParser()
{
}