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

void clean_payload_buffer(struct payload **payload_buffer, size_t *length)
{
	if(length == NULL)
		return;

	struct payload *current;
	for(size_t i = 0; i < (*length); i++)
	{
		current = payload_buffer[i];
		if(current->data != NULL)
			free(current->data);
		
		free(current);
	}
}

// arg parameter is the client's socket
void* handle_client(void *arg)
{
	int client_socket = *(int *) arg; // dereference the argument casted as int ptr
	free(arg);

	struct request_header inbound_request_header;
	struct request_header outbound_request_header;

	void *inbound_buffer = malloc(4096);
	if(inbound_buffer == NULL)
	{
		fprintf(stderr, "[handle_client] Cannot allocate default 4096 bytes for the inbound buffer.\n");
		return;
	}
	size_t inbound_buffer_length = 0;
	size_t inbound_buffer_capacity = 4096;
	bool receive_status;
	int receive_attempts = 0;

	void *outbound_buffer = malloc(4096);
	if(outbound_buffer == NULL)
	{
		fprintf(stderr, "[handle_client] Cannot allocate default 4096 bytes for the outbound buffer.\n");
		free(inbound_buffer);
		return;
	}
	size_t outbound_buffer_length = 0;
	size_t outbound_buffer_capacity = 4096;
	bool send_status;
	int send_attempts = 0;

	struct payload **inbound_payloads = malloc(sizeof(struct payload*) * 5);
	size_t inbound_payloads_length = 0;
	size_t inbound_payloads_capacity = 5;
	size_t payloads_expected = 0;
	size_t payloads_received = 0;

	// Maintain connection with client via loop
	// The entire process of 1st receiving the request type and the number of
	// parameters to be received, 2nd receiving the first parameter, ... finally 
	// receiving the last parameter is contained in this loop. The loop is thereby 
	// quite long.
	// BREAK    -> client connection has to be torn down - pthread has memory issue
	// CONTINUE -> communication done improperly and 
	while(true)
	{ 
		// Clear the buffers
		memset(inbound_buffer, 0, inbound_buffer_capacity);
		memset(outbound_buffer, 0, outbound_buffer_capacity);

		receive_attempts = 0;
		send_attempts = 0;

		// Receive the request header
		receive_status = receive_request_header(client_socket, &inbound_request_header);
		while(receive_status == false && receive_attempts < 10)
		{
			receive_status = receive_request_header(client_socket, &inbound_request_header);
			receive_attempts++;
		}
		if(receive_attempts >= 10)
		{
			fprintf(stderr, "[handle_client] Unable to receive request header from client. Call to receive_request_header returned false.\n");
			continue;
		}
		receive_attempts = 0;

		// Acknowledge that you received it
		send_status = send_acknowledgement(client_socket, OK);
		while(send_status == false && send_attempts < 10)
		{
			send_status = send_acknowledgement(client_scoket, OK);
			send_attempts++;
		}
		if(send_attempts >= 10)
		{
			fprintf(stderr, "[handle_client] Unable to send acknowledgement to client. Send attempts reached or exceeded 10 (send_acknowledgement returned false)\n");
			continue;
		}
		send_attempts = 0;
		
		// Setup inbound payloads buffer (to store all payloads) 
		payloads_expected = inbound_request_header.parameter_count;
		payloads_received = 0;
		if(inbound_payloads_capacity < payloads_expected)
		{
			inbound_payloads_capacity = payloads_expected + 5;
			inbound_payloads = realloc(inbound_payloads, sizeof(struct payload*) * inbound_payloads_capacity);
			if(inbound_payloads == NULL)
			{
				fprintf(stderr, "[handle_client] Failed to realloc more memory so that the inbound payloads buffer could store %zu payload pointers.\n", inbound_payloads_capacity);
				// PUT CLEAN UP ROUTINE HERE LATER.
				break; 
			}
		}

		// Receive payloads (metadata, then payload itself)
		struct payload *current_inbound_payload;	
		while(payloads_received < payloads_expected)
		{
			current_inbound_payload = inbound_payloads[payloads_received];
			
			// Receive payload metadata so you can prepare to actually receive the payload itself
			receive_status = receive_payload_metadata(client_socket, current_inbound_payload);
			while(receive_status == false && receive_attempts < 10)
			{
				receive_status = receive_payload_metadata(client_socket, current_inbound_payload);
				receive_attempts++;
			}
			if(receive_attempts >= 10)
			{
				fprintf(stderr, "[handle_client] Failed to receive payload metadata from the client. 10 or more attempts were reached. receive_payload_metadata() returned false.\n");

				continue;
			}

			send_status = send_acknowledgement(client_socket);

			// Ensure current inbound payload can actually store the data
			current_inbound_payload->data = malloc(current_inbound_payload->parameters_total_size);
			if(current_inbound_payload->data == NULL)
			{
				fprintf(stderr, "[handle_client] Failed to allocate %zu bytes for the data buffer of the current inbound payload (payload %zu)\n", current_inbound_payload.parameters_total_size, payloads_received);
				send_status = send_acknowledgement(client_socket, INSUFFICIENT_MEMORY);
				break;
			}

			// Actually receive the payload
			receive_status = receive_payload(client_socket, current_inbound_payload);
			if(receive_status == false)
			{
				fprintf(stderr, "[handle client] Failed to receive payload from client. Received %zu payloads in total. Expected to receive %zu overall.\n", payloads_received, payloads_expected);
				send_status = send_acknowledgement(client_socket, FAILED);
				clean_payload_buffer(inbound_payloads, inbound_payloads_length);
				break;
			}
			inbound_payloads_length++;

			// Acknowledge that you received it 
			send_status = send_acknowledgement(client_socket, OK);
			if(send_status == false)
			{
			}
		}
	}

	close(client_socket);
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

	// Perform handshake with the client
	uint32_t shared_secret;
    if (server_handshake(client_socket, &shared_secret) < 0) {
        fprintf(stderr, "Server handshake failed.\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }


	char buffer[1024];
    ssize_t bytes_received = secure_recv(client_socket, buffer, sizeof(buffer), 0, shared_secret);
    
	if (bytes_received < 0) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }
    //buffer[bytes_received] = '\0'; // Null-terminate the string
    printf("Received: %s\n", buffer);

	// Cleanup
	close(client_socket);
	close(server_fd);
	return 0;
}
