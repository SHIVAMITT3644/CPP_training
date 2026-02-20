#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include "Parser.h"
#include "tinyxml2.h"

class XmlParser : public Parser
{
private:
    std::string fileName;
    tinyxml2::XMLDocument xmlDocument;
    void printNode(tinyxml2::XMLNode* node, int indentationLevel);

public:
    XmlParser(const std::string& fileName);

    bool parseFile() override;
    bool showParsedFile() override;
    ~XmlParser();
};

#endif