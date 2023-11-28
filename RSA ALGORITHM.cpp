#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1)
        return 0; // Not a prime number
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0; // Not a prime number
    }
    return 1; // Prime number
}

// Function to generate public and private keys
void generateKeys(int p, int q, int *publicKey, int *privateKey) {
    int n, phi_n, e, d;

    // Calculate n and phi(n)
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi(n) and e is coprime with phi(n)
    for (e = 2; e < phi_n; e++) {
        if (gcd(e, phi_n) == 1)
            break;
    }

    // Calculate d, the modular multiplicative inverse of e modulo phi(n)
    d = 0;
    while (1) {
        if ((e * d) % phi_n == 1)
            break;
        d++;
    }

    // Assign public and private keys
    publicKey[0] = e;
    publicKey[1] = n;
    privateKey[0] = d;
    privateKey[1] = n;
}

// Function to encrypt a message using public key
int encrypt(int message, int publicKey[]) {
    int e = publicKey[0];
    int n = publicKey[1];
    return fmod(pow(message, e), n);
}

// Function to decrypt a message using private key
int decrypt(int encryptedMessage, int privateKey[]) {
    int d = privateKey[0];
    int n = privateKey[1];
    return fmod(pow(encryptedMessage, d), n);
}

int main() {
    int p, q;
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    if (!isPrime(p) || !isPrime(q)) {
        printf("Both numbers must be prime.\n");
        return 1;
    }

    int publicKey[2], privateKey[2];
    generateKeys(p, q, publicKey, privateKey);

    int message;
    printf("Enter a message to encrypt: ");
    scanf("%d", &message);

    int encryptedMessage = encrypt(message, publicKey);
    printf("Encrypted message: %d\n", encryptedMessage);

    int decryptedMessage = decrypt(encryptedMessage, privateKey);
    printf("Decrypted message: %d\n", decryptedMessage);

    return 0;
}

