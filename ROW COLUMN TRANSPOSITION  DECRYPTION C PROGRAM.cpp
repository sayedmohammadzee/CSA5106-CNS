#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to decrypt the message using row-column transposition
void decryptMessage(char *encryptedMessage, int rows, int columns) {
    int i, j, index = 0;
    char transposedMatrix[rows][columns];
    char decryptedMessage[strlen(encryptedMessage)];

    // Filling the transposed matrix
    for (i = 0; i < columns; ++i) {
        for (j = 0; j < rows; ++j) {
            transposedMatrix[j][i] = encryptedMessage[index++];
        }
    }

    // Constructing the decrypted message from the transposed matrix
    index = 0;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {
            decryptedMessage[index++] = transposedMatrix[i][j];
        }
    }
    decryptedMessage[index] = '\0'; // Adding null terminator to mark end of string

    printf("Decrypted Message: %s\n", decryptedMessage);
}

int main() {
    char encryptedMessage[] = "YEMEHDLROEC N NAOWGSF"; // Example encrypted message
    int rows = 3; // Number of rows in the transposition matrix
    int columns = 7; // Number of columns in the transposition matrix

    printf("Encrypted Message: %s\n", encryptedMessage);
    decryptMessage(encryptedMessage, rows, columns);

    return 0;
}

