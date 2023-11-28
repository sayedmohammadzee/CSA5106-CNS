#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to prepare the key
void prepareKey(char *key, char *preparedKey) {
    int i, j, k = 0;
    int flag = 0;
    char temp[26] = {0};
    
    // Copy key to temp array
    strcpy(temp, key);
    
    // Remove duplicate letters from key
    for (i = 0; i < strlen(key); ++i) {
        if (key[i] == 'j')
            key[i] = 'i';
        for (j = i + 1; j < strlen(key); ++j) {
            if (key[i] == key[j]) {
                for (k = j; k < strlen(key); ++k) {
                    key[k] = key[k + 1];
                }
            }
        }
    }

    // Prepare the key
    for (i = 0; i < strlen(key); ++i) {
        preparedKey[i] = key[i];
        temp[key[i] - 'a'] = 1;
    }

    // Fill the remaining letters
    for (i = 0; i < 26; ++i) {
        if (temp[i] == 0) {
            if (i == ('j' - 'a'))
                continue;
            preparedKey[strlen(key) + flag++] = i + 'a';
        }
    }
}

// Function to find position of a letter in the grid
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to generate the Playfair cipher matrix
void generateMatrix(char *key, char matrix[SIZE][SIZE]) {
    char preparedKey[25];
    prepareKey(key, preparedKey);
    
    int k = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = preparedKey[k++];
        }
    }
}

// Function to encrypt a pair of letters
void encrypt(char matrix[SIZE][SIZE], char a, char b) {
    int rowA, colA, rowB, colB;
    findPosition(matrix, a, &rowA, &colA);
    findPosition(matrix, b, &rowB, &colB);

    if (rowA == rowB) {
        colA = (colA + 1) % SIZE;
        colB = (colB + 1) % SIZE;
    } else if (colA == colB) {
        rowA = (rowA + 1) % SIZE;
        rowB = (rowB + 1) % SIZE;
    } else {
        int temp = colA;
        colA = colB;
        colB = temp;
    }

    printf("%c%c%c%c", matrix[rowA][colA], matrix[rowB][colB], matrix[rowA][colB], matrix[rowB][colA]);
}

int main() {
    char key[25];
    char plaintext[100];
    char matrix[SIZE][SIZE];

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Remove non-alphabetic characters and convert to lowercase
    for (int i = 0; plaintext[i]; i++) {
        plaintext[i] = tolower(plaintext[i]);
        if (!isalpha(plaintext[i])) {
            for (int j = i; plaintext[j]; j++) {
                plaintext[j] = plaintext[j + 1];
            }
        }
    }

    generateMatrix(key, matrix);

    // Encrypt the plaintext
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 < len) {
            encrypt(matrix, plaintext[i], plaintext[i + 1]);
        } else {
            // If the plaintext has an odd number of characters, append 'x' to make pairs
            encrypt(matrix, plaintext[i], 'x');
        }
    }

    return 0;
}

