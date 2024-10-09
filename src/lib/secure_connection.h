#ifndef SECURE_CONNECTION_H
#define SECURE_CONNECTION_H

typedef struct {
    uint32_t private_key;
    uint32_t public_key;
} DHKeyPair;

uint32_t mod_exp(uint32_t base, uint32_t exp, uint32_t mod);
uint32_t rand_range(uint32_t min, uint32_t max);
uint32_t generate_prime(int bits);
bool is_prime(uint32_t n);

DHKeyPair* create_keypair(uint32_t g, uint32_t p);

uint32_t compute_shared_secret(DHKeyPair *keypair, uint32_t other_public_key, uint32_t p);
int client_handshake(int socket, uint32_t *shared_secret);
int server_handshake(int socket, uint32_t *shared_secret);

#endif // SECURE_CONNECTION_H
