#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include "Parser.h"
#include "rapidcsv.h"

class CsvParser : public Parser
{
    std::string fileName;
    rapidcsv::Document csvDocument;
    bool openFile(std::ifstream& file, bool& isOpened);
    bool isFileEmpty(std::ifstream& file, bool& isEmpty);
    bool parseCsv(std::ifstream& file, bool& isParsedSuccessfully);
    bool displayCell(const std::string& cellValue, size_t columnIndex, size_t totalColumns);
    bool displayRow(size_t rowIndex, size_t totalColumns, bool& isDisplayedSuccessfully);
    
    
public:
    CsvParser(const std::string& fileName);

    bool parseFile() override;
    bool showParsedFile() override;
};

#endif
