#ifndef INPUT_H
#define INPUT_H 
#include <iostream>

int readValidUserInput(const std::string& inputMessage);
std::string readFileInput(const std::string& type);
void readCompleteLineInput(std::istream& inputStream, std::string& output , const std::string& message);
#endif