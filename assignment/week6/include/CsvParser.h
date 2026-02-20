#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include "Parser.h"
#include "rapidcsv.h"

class CsvParser : public Parser
{
    std::string fileName;
    rapidcsv::Document* csvDocument;

public:
    CsvParser(const std::string& fileName);

    bool parseFile() override;
    bool showParsedFile() override;

    ~CsvParser();
};

#endif