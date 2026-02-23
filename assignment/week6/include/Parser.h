#ifndef PARSER_H
#define PARSER_H
#include <string>

class Parser
{
    public:

    virtual bool parseFile() = 0;
    virtual bool showParsedFile() = 0;
};

#endif
