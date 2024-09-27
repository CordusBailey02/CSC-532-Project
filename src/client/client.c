#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_ADDR "142.93.199.100"
#include "../lib/terrorexchange.h"

int main(int argc, char **argv)
{
	// Establish connection to server machine
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(tcp_socket < 0)
	{
		fprintf(stderr, "Failed to create socket.\n");
		exit(EXIT_FAILURE); // performs cleanup
	}

	struct sockaddr_in server_addr; 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080); // tcp port
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if(connect(tcp_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "Connection to server failed.\n");
		close(tcp_socket);
		exit(EXIT_FAILURE); // performs cleanup as well
	}

	printf("Server connection established.\n\n");

	close(tcp_socket);
	return 0;
}
