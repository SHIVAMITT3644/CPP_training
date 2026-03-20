#ifndef CRYPTOSERVICE_H
#define CRYPTOSERVICE_H

#include <string>
#include "ICryptoService.h"

class CryptoService : public ICryptoService
{
private:
    std::string key;

public:
    CryptoService(const std::string& key);

    std::string encrypt(const std::string& plainText) override;
    std::string decrypt(const std::string& cipherText) override;
};

#endif
