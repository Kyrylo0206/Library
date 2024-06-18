#include <iostream>
#include <windows.h>
#include <string>

int main() {

    typedef char* (*encrypt_ptr_t)(char*, int);
    typedef char* (*decrypt_ptr_t)(char*, int);

    std::string operation;
    std::string text;
    int key;

    std::cout << "Enter operation (encrypt/decrypt): ";
    std::cin >> operation;
    std::cin.ignore();  // ignore the newline character left in the input buffer

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter key: ";
    std::cin >> key;

    HINSTANCE handle = LoadLibrary(TEXT("Dll2.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        std::cout << "Library not found\n";
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");

    if (encrypt_ptr == nullptr || decrypt_ptr == nullptr) {
        std::cout << "Function not found\n";
        FreeLibrary(handle);
        return 1;
    }

    if (operation == "encrypt") {
        char* encrypted = encrypt_ptr(&text[0], key);
        std::cout << "Encrypted text: " << encrypted << "\n";
        free(encrypted);
    }
    else if (operation == "decrypt") {
        char* decrypted = decrypt_ptr(&text[0], key);
        std::cout << "Decrypted text: " << decrypted << "\n";
        free(decrypted);
    }
    else {
        std::cout << "Invalid operation\n";
    }

    FreeLibrary(handle);
    return 0;
}
