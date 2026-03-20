#ifndef ICRYPTOSERVICE_H
#define ICRYPTOSERVICE_H

#include <string>

class ICryptoService
{
public:
    virtual ~ICryptoService() = default;

    virtual std::string encrypt(const std::string& plainText) = 0;
    virtual std::string decrypt(const std::string& cipherText) = 0;
};

#endif
