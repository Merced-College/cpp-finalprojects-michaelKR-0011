#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib> // Required for system()

#include "Crypto.h"

using namespace std;

bool requirePasswordBeforeOpening(const string& filename, const Crypto& crypto, string& tempPassword) {
    const string protectedFiles[] = {
        "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File2.txt_encrypted.txt",
        "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File3.txt_encrypted.txt",
        "C:\\Users\\kaosr\\OneDrive\\Documents\\FINALL\\FINAL\\File4.txt_encrypted.txt"
    };

    for (const string& protectedFile : protectedFiles) {
        if (filename == protectedFile) {
            cout << "\n>>> ACCESS RESTRICTED <<<\n";
            cout << "Enter authentication code: ";
            getline(cin, tempPassword);

            if (!crypto.authenticate(tempPassword, filename)) {
                cerr << "\nERROR: Invalid credentials. Access Denied.\n";
                return false;
            }
            cout << "\n Access Granted.\n";
        }
    }
    return true;
}

int main() {
    string userPassword = "1234";
    Crypto crypto('K', userPassword);
    string filename, tempPassword;

    cout << "\n*** WELCOME ***\n";
    cout << "Press ENTER to continue...";
    cin.get();

    while (true) {
        cout << "\n==========================\n";
        cout << "AVAILABLE FILES:\n";
        cout << "1. File1\n";
        cout << "2. File2 (Restricted)\n";
        cout << "3. File3 (Restricted)\n";
        cout << "4. File4 (Restricted)\n";
        cout << "==========================\n";
        cout << "Select file or type 'exit' to quit: ";
        getline(cin, filename);

        if (filename == "exit") {
            cout << "\nTerminating session...\n";
            break;
        }

        filename = Crypto::mapFileShortcut(filename);

        if (!requirePasswordBeforeOpening(filename, crypto, tempPassword)) {
            continue;
        }

        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "\nERROR: Unable to retrieve file.\n";
            continue;
        }

        string fileData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        if (fileData.empty()) {
            cerr << "\nERROR: File is empty or corrupted.\n";
            continue;
        }

        string decryptedData = crypto.process(fileData, tempPassword, filename);
        if (!decryptedData.empty()) {
            cout << "\n DECRYPTED CONTENT:\n";
            cout << decryptedData << endl;
        }
        else {
            cerr << "\nERROR: Decryption failed.\n";
        }

        cout << "\nPress ENTER to return...";
        cin.get();
        system("cls"); // Clears the terminal on Windows
    }

    return 0;
}