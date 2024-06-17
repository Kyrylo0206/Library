#include "lib.h"
#include <stdio.h>
#include <windows.h>

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <encrypt/decrypt> <text> <key>\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];
    char *text = argv[2];
    int key = atoi(argv[3]);

    HINSTANCE handle = LoadLibrary(TEXT("caesar.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        printf("Library not found\n");
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");

    if (encrypt_ptr == nullptr || decrypt_ptr == nullptr) {
        printf("Function not found\n");
        FreeLibrary(handle);
        return 1;
    }

    if (strcmp(operation, "encrypt") == 0) {
        char* encrypted = encrypt_ptr(text, key);
        printf("Encrypted text: %s\n", encrypted);
        free(encrypted);
    } else if (strcmp(operation, "decrypt") == 0) {
        char* decrypted = decrypt_ptr(text, key);
        printf("Decrypted text: %s\n", decrypted);
        free(decrypted);
    } else {
        printf("Invalid operation\n");
    }

    FreeLibrary(handle);
    return 0;
}
