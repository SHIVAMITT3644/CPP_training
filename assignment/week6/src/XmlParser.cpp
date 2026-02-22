#include <iostream>
#include "XmlParser.h"
#include "Constants.h"

using namespace tinyxml2;

XmlParser::XmlParser(const std::string& fileName) : fileName(fileName)
{
}

bool XmlParser::parseFile()
{
    bool isParsedSuccessfully = true;

    XMLError error =
        xmlDocument.LoadFile((RESOURCE_FOLDER_CONSTANT + fileName).c_str());

    if (error != XML_SUCCESS)
    {
        std::cerr << FORMATING_MESSAGE;
        std::cerr << XML_PARSING_ERROR_MESSAGE;
        std::cerr << "Message: " << xmlDocument.ErrorStr() << "\n";
        std::cerr << "Line: " << xmlDocument.ErrorLineNum() << "\n";
        std::cerr << FORMATING_MESSAGE;

        isParsedSuccessfully = false;
    }

    return isParsedSuccessfully;
}

void XmlParser::showNode(XMLNode* node, int indentationLevel)
{
    if (!node) return;

    std::string indentation(indentationLevel, ' ');

    if (XMLElement* element = node->ToElement())
    {
        std::cout << indentation << element->Name() << " : ";

        if (element->FirstChildElement())
        {
            std::cout << "\n";
            for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                showNode(child, indentationLevel + 4);
            }
        }
        else if (element->GetText())
        {
            
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

    std::cout << XML_DATA_TEMPLATE;

    XMLElement* root = xmlDocument.RootElement();

    if (!root)
    {
        std::cerr << XML_EMPTY_ERROR_MESSAGE;
        isDisplayedSuccessfully = false;
    }
    else
    {
        int elementCount = 1;

        for (XMLElement* childElement = root->FirstChildElement(); childElement != nullptr; childElement = childElement->NextSiblingElement())
        {
            std::cout << "Element " << elementCount << ":\n";
            showNode(childElement, 4);
            std::cout << FORMATING_MESSAGE;
            ++elementCount;
        }
    }

    std::cout << FORMATING_MESSAGE;

    return isDisplayedSuccessfully;
}
