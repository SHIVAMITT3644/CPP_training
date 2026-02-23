#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <string>
#include"Parser.h"
#include "json.hpp"

class JsonParser : public Parser
{
    std::string fileName;
    nlohmann::ordered_json jsonObject;

    bool openFile(std::ifstream& file, bool& isOpened);
    bool isFileEmpty(std::ifstream& file, bool& isEmpty);
    bool parseJson(std::ifstream& file, bool& isParsedSuccessfully);
    void showJsonValue(const nlohmann::ordered_json& jsonData, int indentationLevel);
    void showJsonObject(const nlohmann::ordered_json& jsonData, int indentationLevel);
    void showJsonArray(const nlohmann::ordered_json& jsonData, int indentationLevel);
    void showJson(const nlohmann::ordered_json& jsonData , int indentationLevel);

    public:
    JsonParser(const std::string& fileName);
    bool parseFile() override;
    bool showParsedFile() override;
};

#endif
