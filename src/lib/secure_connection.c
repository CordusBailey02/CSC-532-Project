#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "secure_connection.h"

#define MODULUS_BITS 16 

// Function for modular exponentiation
uint32_t mod_exp(uint32_t base, uint32_t exp, uint32_t mod) {
    uint32_t result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod; 
    }
    return result;
}

// Function to return a random number between min and max
uint32_t rand_range(uint32_t min, uint32_t max) {
    return min + (rand() % (max - min));
}

// Test to check if a number is prime
bool is_prime(uint32_t n) {
    if (n < 2) return false;
    for (uint32_t i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to generate a prime number
uint32_t generate_prime(int bits) {
    uint32_t prime;
    do {
        prime = rand_range(1U << (bits - 1), (1U << bits));
    } while (!is_prime(prime));
    return prime;
}


// Function to create a new key pair
DHKeyPair* create_keypair(uint32_t g, uint32_t p) {
    DHKeyPair *keypair = malloc(sizeof(DHKeyPair));

    if (!keypair) return NULL;

    // Compute private and public key
    keypair->private_key = rand_range(1, p);
    keypair->public_key = mod_exp(g, keypair->private_key, p); 

    return keypair;
}

// Function to compute shared secret
uint32_t compute_shared_secret(DHKeyPair *keypair, uint32_t other_public_key, uint32_t p) {
    return mod_exp(other_public_key, keypair->private_key, p);
}

// Function for client handshake
int client_handshake(int socket, uint32_t *shared_secret) {


    uint32_t p;
    if (recv(socket, &p, sizeof(p), 0) < 0) {
        perror("Failed to receive p from server");
        return -1;
    }

    uint32_t g = 2;

    // Create a new ephemeral key pair
    DHKeyPair *client_keypair = create_keypair(g, p);
    if (!client_keypair) return -1;

    // Send the public key to the server
    if (send(socket, &client_keypair->public_key, sizeof(client_keypair->public_key), 0) < 0) {
        perror("Failed to send public key");
        free(client_keypair);
        return -1;
    }

    // Receive the server's public key
    uint32_t server_public_key;
    if (recv(socket, &server_public_key, sizeof(server_public_key), 0) < 0) {
        perror("Failed to receive server public key");
        free(client_keypair);
        return -1;
    }

    // Compute the shared secret
    *shared_secret = compute_shared_secret(client_keypair, server_public_key, p);
    printf("Shared secret computed by client: %u\n", *shared_secret);

    // Clean up
    free(client_keypair);
    return 0;
}

// Function for server handshake
int server_handshake(int socket, uint32_t *shared_secret) {
    // Seed the random number generator
    srand(time(NULL));

    uint32_t p = generate_prime(MODULUS_BITS);
    send(socket, &p, sizeof(p), 0);
    uint32_t g = 2;

    // Create a new ephemeral key pair
    DHKeyPair *server_keypair = create_keypair(g, p);
    if (!server_keypair) return -1;

    // Receive the client's public key
    uint32_t client_public_key;
    if (recv(socket, &client_public_key, sizeof(client_public_key), 0) < 0) {
        perror("Failed to receive client public key");
        free(server_keypair);
        return -1;
    }

    // Send the server's public key to the client
    if (send(socket, &server_keypair->public_key, sizeof(server_keypair->public_key), 0) < 0) {
        perror("Failed to send server public key");
        free(server_keypair);
        return -1;
    }

    // Compute the shared secret
    *shared_secret = compute_shared_secret(server_keypair, client_public_key, p);
    printf("Shared secret computed by server: %u\n", *shared_secret);

    // Clean up
    free(server_keypair);
    return 0;
}


// XOR Encryption/Decryption
void xor_encrypt_decrypt(uint8_t *data, size_t len, uint8_t *key, size_t key_len) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % key_len];
    }
}


ssize_t secure_send(int sockfd, const void *buf, size_t len, int flags, uint32_t shared_secret) {
    uint8_t *encrypted_buf = malloc(len);
    if (!encrypted_buf) {
        perror("Memory allocation failed");
        return -1;
    }

    memcpy(encrypted_buf, buf, len);
    xor_encrypt_decrypt(encrypted_buf, len, (uint8_t*)&shared_secret, sizeof(shared_secret));

    ssize_t bytes_sent = send(sockfd, encrypted_buf, len, flags);
    free(encrypted_buf);

    return bytes_sent;
}

ssize_t secure_recv(int sockfd, void *buf, size_t len, int flags, uint32_t shared_secret) {
    ssize_t bytes_received = recv(sockfd, buf, len, flags);
    if (bytes_received > 0) {
        xor_encrypt_decrypt((uint8_t*)buf, bytes_received, (uint8_t*)&shared_secret, sizeof(shared_secret));
    }
    return bytes_received;
}
