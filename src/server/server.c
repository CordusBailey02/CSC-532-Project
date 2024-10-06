#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <pthread.h>
#include  "../lib/terrorexchange.h"

bool set_buffer_with_response_header(void *buffer, size_t *buffer_bytes_used, size_t *buffer_capacity, struct server_response_header *header)
{
	if(buffer == NULL)
	{
		fprintf(stderr, "[set_buffer_with_response_header]: Buffer to set points to NULL.\n");
		return false;
	}

	if(header == NULL)
	{
		fprintf(stderr, "[set_buffer_with_response_header]: Response header to write to buffer points to NULL.\n");
		return false;
	}

	// offsets
	size_t unsigned_short_size = sizeof(unsigned short);
	size_t server_response_enum_size = sizeof(enum server_responses);

	// set buffer
	(*buffer_bytes_used) = 0;
	memcpy(buffer, &header->response_type, server_response_enum_size);
	(*buffer_bytes_used) = server_response_enum_size;

	memcpy(buffer + (*buffer_bytes_used), header->parameter_count, unsigned_short_size);
	(*buffer_bytes_used) += unsigned_short_size;

	memcpy(buffer + (*buffer_bytes_used), header->bytes_to_send, unsigned_short_size);
	(*buffer_bytes_used) += unsigned_short_size;

	return true;
}

bool server_receive_request_header(int client_socket, struct client_request_header *request_header)
{
	if(request_header == NULL)
	{
		fprintf(stderr, "[server_receive_request_header]: request header was NULL.\n");
		return false;
	}

	byte buffer[sizeof(struct client_request_header)];
	int buffer_size = sizeof(buffer);

	int bytes_received = recv(client_socket, buffer, buffer_size, 0);
	int current_offset = 0;

	if(bytes_received < buffer_size)
	{
		fprintf(stderr, "Failed to receive request header from client socket %d.\n", client_socket);
		return false; // failure
	}

	// Deserialize the request type and the expected parameters count
	// copying byte ranges, so use memcpy
	memcpy(&request_header->request_type, buffer, sizeof(enum client_requests));
	current_offset = sizeof(enum client_requests);
	memcpy(&request_header->parameter_count, buffer + current_offset, sizeof(unsigned short));
	current_offset += sizeof(unsigned short);
	memcpy(&request_header->bytes_to_send, buffer + current_offset, sizeof(unsigned short));

	return true; // success
}

// this already has to be the correct size. Caller should make sure the data is good to go.
bool server_receive_parameters_from_client(int client_socket, struct message_parameter **parameters, size_t *parameters_length, unsigned short parameters_expected)
{ 
	if(parameters == NULL)
	{
		fprintf(stderr, "[server_receive_parameters_from_client]: Parameters buffer is NULL.\n");
		return false;
	}

	// For error checking transmissions
	size_t bytes_expected;

	// For creating parameters
	byte member_size = 0;
	unsigned short member_count = 0;

	int bytes_received = 0;

	struct message_parameter *current_parameter;

	while( (*parameters_length) < parameters_expected )
	{
		// Receive individual member size
		bytes_expected = sizeof(member_size);
		bytes_received = recv(client_socket, &member_size, bytes_expected, 0);
		if(bytes_received != bytes_expected)
		{
			return false;
		}

		// Receive member count
		bytes_expected = sizeof(member_count);
		bytes_received = recv(client_socket, &member_count, bytes_expected, 0);
		if(bytes_received != bytes_expected)
		{
			return false;
		}

		// Create partial parameter AND update current parameter
		parameters[(*parameters_length)] = message_parameter_create(member_size, member_count);
		current_parameter = parameters[(*parameters_length)];
		if(current_parameter == NULL)
		{
			fprintf(stderr, "[server_receive_parameters_from_client]: Failed to create new parameter in parameters buffer with call to message_parameter_create.\n");
			return false;
		}
		current_parameter->data = malloc(member_size * member_count);
		
		// Receive parameter --- into current parameter's buffer
		bytes_expected = member_count * member_size;
		bytes_received = recv(client_socket, current_parameter->data, bytes_expected, 0);
		if(bytes_received != bytes_expected)
		{
			return false;
		}

		// Increment parameters counted
		(*parameters_length)++;
	}
	return true;
}

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


	// Cleanup
	close(client_socket);
	close(server_fd);
	return 0;
}
