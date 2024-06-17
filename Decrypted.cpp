#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decrypt(char* encryptedText, int key) {
    int len = strlen(encryptedText);
    char* decryptedText = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        if (encryptedText[i] >= 'a' && encryptedText[i] <= 'z') {
            decryptedText[i] = ((encryptedText[i] - 'a' - key + 26) % 26) + 'a';
        } else if (encryptedText[i] >= 'A' && encryptedText[i] <= 'Z') {
            decryptedText[i] = ((encryptedText[i] - 'A' - key + 26) % 26) + 'A';
        } else {
            decryptedText[i] = encryptedText[i];
        }
    }
    decryptedText[len] = '\0';
    return decryptedText;
}
