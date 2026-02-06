#ifndef CHECK_USER_INPUT_VALIDITY_H
#define CHECK_USER_INPUT_VALIDITY_H

#include <string>

class CheckUserInputValidity
{
    bool hasValidDecimalFormatBoundaries(const std::string& inputFromUser);
    bool convertDecimalStringToValue(const std::string& inputFromUser, double& value);

protected:
    bool validateWholeNumber(const std::string& inputFromUser, int& value);
    bool validateDecimalNumber(const std::string& inputFromUser, double& value);
};

#endif
