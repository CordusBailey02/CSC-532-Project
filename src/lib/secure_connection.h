#ifndef SECURE_CONNECTION_H
#define SECURE_CONNECTION_H

typedef struct {
    unsigned long long private_key;
    unsigned long long public_key;
} DHKeyPair;

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod);
unsigned long long rand_range(unsigned long long min, unsigned long long max);
unsigned long long generate_prime(int bits);
int is_prime(unsigned long long n);
DHKeyPair* create_keypair(unsigned long long g, unsigned long long p);
unsigned long long compute_shared_secret(DHKeyPair *keypair, unsigned long long other_public_key, unsigned long long p);
int client_handshake(int socket, unsigned long long *shared_secret);
int server_handshake(int socket, unsigned long long *shared_secret);

#endif // SECURE_CONNECTION_H
