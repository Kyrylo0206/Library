#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(char* rawText, int key) {
    int len = strlen(rawText);
    char* encryptedText = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        if (rawText[i] >= 'a' && rawText[i] <= 'z') {
            encryptedText[i] = ((rawText[i] - 'a' + key) % 26) + 'a';
        } else if (rawText[i] >= 'A' && rawText[i] <= 'Z') {
            encryptedText[i] = ((rawText[i] - 'A' + key) % 26) + 'A';
        } else {
            encryptedText[i] = rawText[i];
        }
    }
    encryptedText[len] = '\0';
    return encryptedText;
}
