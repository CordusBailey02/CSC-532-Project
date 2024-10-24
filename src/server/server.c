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
	
	struct client_request_header request_header;
	struct server_response_header response_header;

	// Set up buffer for sending data to client
	void *send_buffer = malloc(4096);
	if(send_buffer == NULL)
	{
		fprintf(stderr, "[handle_client - client socket %d]: Failed to allocate 4096 bytes for send_buffer.\n", client_socket);
		close(client_socket);
		return;
	}
	size_t send_buffer_bytes_used = 0;
	size_t send_buffer_capacity = 4096;

	// Set up buffer for receiving data from client
	void *receive_buffer = malloc(4096);
	{
		fprintf(stderr, "[handle_client - client socket %d]: Failed to allocate 4096 bytes for receive_buffer.\n", client_socket);
		free(send_buffer);
		close(client_socket);
		return;
	}
	size_t receive_buffer_bytes_used = 0;
	size_t receive_buffer_capacity = 4096;

	// Receiving parameters from client
	struct message_parameter **parameters_buffer = malloc(sizeof(struct message_parameter*) * 5);
	if(parameters_buffer == NULL)
	{ 
		fprintf(stderr, "[handle_client - client socket %d]: Failed to allocate parameters buffer (5 parameters - default).\n", client_socket);
		free(send_buffer);
		free(receive_buffer);
		close(client_socket);
		return;
	}
	size_t parameters_buffer_length = 0;
	size_t parameters_buffer_capacity = 5;

	int send_result;
	bool set_buffer_status;
	bool receive_status;

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
		memset(send_buffer, 0, send_buffer_bytes_used);
		memset(receive_buffer, 0, receive_buffer_bytes_used);
		parameters_buffer_length = 0;

		// Receive the request header
		receive_status = server_receive_request_header(client_socket, &request_header); 
		if(receive_status == false)
		{
			response_header.response_type = MALFORMED;
			response_header.parameter_count = 0;
			response_header.bytes_to_send = 0;
			set_buffer_with_response_header(send_buffer, &send_buffer_bytes_used, &send_buffer_capacity, &response_header);

			send_result = send(client_socket, send_buffer, send_buffer_bytes_used, 0);
			if(send_result < 0)
			{
				fprintf(stderr, "[handle_client]: Unable to send MALFORMED respose header to client socket %d.\n", client_socket);
				break;
			}
			continue; // resume from start of loop
		} 

		// Pack response header into a buffer so that it can be sent
		// to the client with send(3)
		response_header.response_type = OK;
		response_header.parameter_count = 0;
		response_header.bytes_to_send = 0;

		set_buffer_status = set_buffer_with_response_header(send_buffer, &send_buffer_bytes_used, &send_buffer_capacity, &response_header);
		if(set_buffer_status == false)
		{
			fprintf(stderr, "[handle_client]: Failed to pack response header into buffer for transmission to client socket %d.\n", client_socket);
			break;
		}

		// Tell client that it can send the rest of the parameters
		send_result = send(client_socket, send_buffer, send_buffer_bytes_used, 0);
		if(send_result < 0)
		{
			fprintf(stderr, "[handle_client]: Failed to advise client that it may send over request parameters. Failed to send OK to client socket %d.\n", client_socket);
		}

		// Set up parameters buffer
		if(parameters_buffer_capacity < request_header.parameter_count)
		{
			parameters_buffer = realloc(parameters_buffer, sizeof(struct message_parameter) * request_header.parameter_count);
			parameters_buffer_capacity = request_header.parameter_count;
			if(parameters_buffer == NULL)
			{
				fprintf(stderr, "[handle_client]: Failed to reallocate parameters buffer to store %hu parameters. Cannot setup for request made by client socket %d.\n", request_header.parameter_count, client_socket);
				break;
			}
		}

		// Receive parameters from client
		receive_status = server_receive_parameters_from_client(client_socket, parameters_buffer, &parameters_buffer_length, request_header.parameter_count);
		if(receive_status == false)
		{
			fprintf(stderr, "[handle_client - client socket %d]: Receive false status after call to server_receive_parameters_from_client.\n");
			break;
		}

		// Based on the type of request made, do something
		switch(request_header.request_type)
		{
			case GET_CATEGORY:
				break;

			case GET_PROFILE:
				break;

			case GET_POST:
				break;

			case GET_NOTIFICATION:
				break;
			
			case CREATE_POST:
				break;

			case CREATE_ACCOUNT:
				break;

			case CREATE_NOTIFICATION:
				break;

			case CREATE_REPORT:
				break;

			case CREATE_VERIFICATION_REQUEST:
				break;

			case DEVELOPER_TEST:
				printf("Message received from client:\n");
				printf("\tREQUEST TYPE: %d\n", request_header.request_type);
				printf("\tPARAMETERS: %hu\n", request_header.parameter_count);
				printf("\tBYTES: %hu\n", request_header.bytes_to_send);	
				for(unsigned short i = 0; i < parameters_buffer_length; i++)
				{
					printf("\tPARAMETER %hu MEMBER SIZE: %d\n", i, parameters_buffer[i]->member_size);
					printf("\tPARAMETER %hu MEMBER COUNT: %hu\n", i, parameters_buffer[i]->member_count);
					printf("\tPARAMETER %hu: \"%s\"\n", i, parameters_buffer[i]->data);
				}
				printf("\n");
				break;

			default:
				fprintf(stderr, "[handle client - client socket %d]: Unimplemented request type was sent off. Server does not know how to proceed.\n");
				break;
		}	
	}

	// Cleanup
	if(send_buffer != NULL) free(send_buffer);
	if(receive_buffer != NULL) free(receive_buffer);
	if(parameters_buffer != NULL) free(parameters_buffer);

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
