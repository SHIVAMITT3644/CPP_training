#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <string>
#include"Parser.h"
#include "json.hpp"

class JsonParser : public Parser
{
    std::string fileName;
    nlohmann::ordered_json jsonObject;

    void showJson(const nlohmann::ordered_json& jsonData , int indentationLevel);

    public:
    JsonParser(const std::string& fileName);
    bool parseFile() override;
    bool showParsedFile() override;
};

#endif
