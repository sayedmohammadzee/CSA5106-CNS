#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

void encrypt(char message[], int key) {
    int i;
    char encrypted[MAX_LENGTH];

    for (i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            encrypted[i] = ((message[i] - 'a') + key) % 26 + 'a';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            encrypted[i] = ((message[i] - 'A') + key) % 26 + 'A';
        } else {
            encrypted[i] = message[i];
        }
    }
    encrypted[i] = '\0';

    printf("Encrypted message: %s\n", encrypted);
}

void decrypt(char message[], int key) {
    int i;
    char decrypted[MAX_LENGTH];

    for (i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            decrypted[i] = ((message[i] - 'a') - key + 26) % 26 + 'a';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            decrypted[i] = ((message[i] - 'A') - key + 26) % 26 + 'A';
        } else {
            decrypted[i] = message[i];
        }
    }
    decrypted[i] = '\0';

    printf("Decrypted message: %s\n", decrypted);
}

int main() {
    char message[MAX_LENGTH];
    int key;

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key (a number between 0 and 25): ");
    scanf("%d", &key);

    // Clear input buffer
    while (getchar() != '\n')
        ;

    encrypt(message, key);
    decrypt(message, key);

    return 0;
}

