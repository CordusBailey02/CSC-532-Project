#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MODULUS_BITS 16 // Adjust the bits for prime generation as needed

// Function for modular exponentiation
uint32_t mod_exp(uint32_t base, uint32_t exp, uint32_t mod) {
    uint32_t result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

// Simple function to generate a random number in the range [min, max)
uint32_t rand_range(uint32_t min, uint32_t max) {
    return min + (rand() % (max - min));
}

// A naive primality test
bool is_prime(uint32_t n) {
    if (n < 2) return false;
    for (uint32_t i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to generate a simple prime (for educational purposes)
uint32_t generate_prime(int bits) {
    uint32_t prime;
    do {
        prime = rand_range(1U << (bits - 1), (1U << bits));
    } while (!is_prime(prime));
    return prime;
}

// Structure for a key pair
typedef struct {
    uint32_t private_key;
    uint32_t public_key;
} DHKeyPair;

// Function to create a new key pair
DHKeyPair* create_keypair(uint32_t g, uint32_t p) {
    DHKeyPair *keypair = malloc(sizeof(DHKeyPair));
    if (!keypair) return NULL; // Check for allocation failure
    keypair->private_key = rand_range(1, p); // Generate a private key
    keypair->public_key = mod_exp(g, keypair->private_key, p); // Compute public key
    return keypair;
}

// Function to compute shared secret
uint32_t compute_shared_secret(DHKeyPair *keypair, uint32_t other_public_key, uint32_t p) {
    return mod_exp(other_public_key, keypair->private_key, p);
}

// Function for client handshake
int client_handshake(int socket, uint32_t *shared_secret) {
    srand(time(NULL)); // Seed the random number generator

    uint32_t p = generate_prime(MODULUS_BITS); // Example prime
    uint32_t g = 2; // Primitive root

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
    srand(time(NULL)); // Seed the random number generator

    uint32_t p = generate_prime(MODULUS_BITS); // Example prime
    uint32_t g = 2; // Primitive root

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
