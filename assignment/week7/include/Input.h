#ifndef INPUT_H
#define INPUT_H 
#include <iostream>

int readValidUserInput(const std::string& inputMessage);
double readValidFloatingInput(const std::string& inputMessage);
void readCompleteLineInput(std::istream& inputStream, std::string& output , const std::string& message);
std::string readHiddenPassword(const std::string& message);

#endif