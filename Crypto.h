#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto {
private:
    char key;
    std::string password;

public:
    Crypto(char k, const std::string& pwd);

    bool authenticate(const std::string& enteredPassword, const std::string& filename) const;
    std::string process(const std::string& data, const std::string& enteredPassword, const std::string& filename) const;
    static std::string mapFileShortcut(const std::string& shortcut);

    // New function for decrypting `Pass.txt_encrypted.txt`
    std::string decryptPasswordFile(const std::string& encryptedFile) const;
};

#endif