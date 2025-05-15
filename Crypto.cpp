#include "Crypto.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

Crypto::Crypto(char k, const std::string& pwd) : key(k), password(pwd) {}

string Crypto::decryptPasswordFile(const string& encryptedFile) const {
    ifstream file(encryptedFile, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open encrypted password file.\n";
        return "";
    }

    string encryptedData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Decrypt the password file using Crypto's processing function
    string decryptedData = process(encryptedData, "YourDecryptionKey", encryptedFile);

    if (decryptedData.empty()) {
        cerr << "Error: Failed to decrypt password file.\n";
    }

    return decryptedData;
}

bool Crypto::authenticate(const string& enteredPassword, const string& filename) const {
    //  Load decrypted passwords from `Pass.txt_encrypted.txt`
    string decryptedPasswords = decryptPasswordFile("C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\Pass.txt_encrypted.txt");

    if (decryptedPasswords.empty()) {
        cerr << "Error: Could not retrieve passwords.\n";
        return false;
    }

    // Extract passwords dynamically
    string file2Password = decryptedPasswords.substr(decryptedPasswords.find("file2=") + 6, 4);
    string file3Password = decryptedPasswords.substr(decryptedPasswords.find("file3=") + 6, 6);
    string file4Password = decryptedPasswords.substr(decryptedPasswords.find("file4=") + 6, 8);


    // 🔹 Trim any extra spaces or newlines
    file2Password.erase(remove(file2Password.begin(), file2Password.end(), '\n'), file2Password.end());
    file3Password.erase(remove(file3Password.begin(), file3Password.end(), '\n'), file3Password.end());
    file4Password.erase(remove(file4Password.begin(), file4Password.end(), '\n'), file4Password.end());

    // 🔓 Validate passwords dynamically
    if ((filename.find("File2") != string::npos && enteredPassword == file2Password) ||
        (filename.find("File3") != string::npos && enteredPassword == file3Password) ||
        (filename.find("File4") != string::npos && enteredPassword == file4Password)) {
        return true;
    }

    cerr << "Error: Incorrect password! Access denied.\n";
    return false;
}

string Crypto::process(const string& data, const string& enteredPassword, const string& filename) const {
    // Require password authentication for files 2-4
    if (filename == "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File2.txt_encrypted.txt" ||
        filename == "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File3.txt_encrypted.txt" ||
        filename == "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File4.txt_encrypted.txt") {

        if (!authenticate(enteredPassword, filename)) {
            cerr << "Error: Incorrect password! Cannot process file.\n";
            return "";
        }
        cout << "Password accepted! Proceeding with decryption...\n";
    }

    if (data.empty()) {
        cerr << "Error: File data is empty. Cannot process!\n";
        return "";
    }

    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] ^= key;  // Encryption/decryption process
    }
    return result;
}

// Map file shortcuts to real paths
string Crypto::mapFileShortcut(const string& shortcut) {
    string lowercaseShortcut = shortcut;
    transform(lowercaseShortcut.begin(), lowercaseShortcut.end(), lowercaseShortcut.begin(), ::tolower);

    if (lowercaseShortcut == "file1") {
        return "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File1.txt_encrypted.txt";
    }
    else if (lowercaseShortcut == "file2") {
        return "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File2.txt_encrypted.txt";
    }
    else if (lowercaseShortcut == "file3") {
        return "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File3.txt_encrypted.txt";
    }
    else if (lowercaseShortcut == "file4") {
        return "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File4.txt_encrypted.txt";
    }

    return shortcut;
}