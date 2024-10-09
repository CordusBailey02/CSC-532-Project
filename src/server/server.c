#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <pthread.h>
#include  "../lib/terrorexchange.h"
#include  "../lib/secure_connection.h"

// arg parameter is the client's socket
void* handle_client(void *arg)
{
	int client_socket = *(int *) arg; // dereference the argument casted as int ptr
	free(arg);

	size_t buffer_size = 4096;
	void *buffer = malloc(4096);
	long bytes_received;

	// Maintain connection with client via loop
	while(true)
	{ 
		memset(buffer, 0, buffer_size); // clear buffer

		// Receive client data
		bytes_received = recv(client_socket, buffer, buffer_size, 0);


		// When bytes received is 0, the client terminated the connection
		if(bytes_received == 0)
		{
			fprintf(stderr, "Client terminated the connection.\n");
			break;
		}

		// When bytes received is -1, an error occurred
	}
}
 
int main(int argc, char **argv)
{
	// Create connection socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1)
	{
		fprintf(stderr, "Failed to create socket.\n");
		exit(EXIT_FAILURE);
	}

	// Bind socket to IP addr and port
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; // bind to all available network ifaces
	server_addr.sin_port = htons(8080); // tcp

	if(bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "Failed to bind socket to TCP port.\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Listen for connections from clients
	if(listen(server_fd, 3) < 0)
	{
		fprintf(stderr, "Listening failed.\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Now listening for connections on TCP port 8080.\n");

	// Accept client connections --- just one for now, multithreading/forking/non-blocking IO comes later
	int addrlen = sizeof(server_addr);
	int client_socket = accept(server_fd, (struct sockaddr*) &server_addr, (socklen_t*) &addrlen);
	if(client_socket < 0)
	{
		fprintf(stderr, "Failed to accept connection.\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Client connection accepted.\n");

	unsigned long long shared_secret;
    if (server_handshake(client_socket, &shared_secret) < 0) {
        fprintf(stderr, "Server handshake failed.\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }


	// Cleanup
	close(client_socket);
	close(server_fd);
	return 0;
}
