#include <iostream>
#include "Constants.h"
#include "ParserSimulator.h"

int main()
{
    if(!runParserSimulator())
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}