#include "CryptoService.h"

CryptoService::CryptoService(const std::string& key)
    : key(key)
{
}

std::string CryptoService::encrypt(const std::string& plainText)
{
    if (key.empty())
    {
        return plainText;
    }

    std::string encryptedText = plainText;

    for (size_t index = 0; index < plainText.length(); index++)
    {
        encryptedText[index] = plainText[index] ^ key[index % key.length()];
    }

    return encryptedText;
}

std::string CryptoService::decrypt(const std::string& cipherText)
{
    if (key.empty())
    {
        return cipherText;
    }

    std::string decryptedText = cipherText;

    for (size_t index = 0; index < cipherText.length(); index++)
    {
        decryptedText[index] = cipherText[index] ^ key[index % key.length()];
    }

    return decryptedText;
}
