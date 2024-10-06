#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_ADDR "142.93.199.100"
#include "../lib/terrorexchange.h"

bool set_buffer_with_request_header(void *buffer, size_t *buffer_bytes_used, size_t *buffer_capacity, struct client_request_header *header)
{
	if(buffer == NULL)
	{
		fprintf(stderr, "[set_buffer_with_request_header]: Buffer to set with request header points to NULL.\n");
		return false;
	}

	if(header == NULL)
	{
		fprintf(stderr, "[set_buffer_with_request_header]: Request header to write into buffer points to NULL.\n");
		return false;
	}

	// offsets
	size_t unsigned_short_size = sizeof(unsigned short);
	size_t client_request_enum_size = sizeof(enum client_requests);

	// set buffer
	(*buffer_bytes_used) = 0;
	memcpy(buffer, &header->request_type);
	(*buffer_bytes_used) = client_request_enum_size;

	memcpy(buffer + (*buffer_bytes_used), header->parameter_count, unsigned_short_size);
	(*buffer_bytes_used) += unsigned_short_size;

	memcpy(buffer + (*buffer_bytes_used), header->bytes_to_send, unsigned_short_size);
	(*buffer_bytes_used) += unsigned_short_size; 

	return true;
}

bool client_receive_response_header(int socket, struct server_response_header *response_header)
{
	if(response_header == NULL)
	{
		fprintf(stderr, "[client_receive_response_header]: Response header was NULL.\n");
		return false;
	}

	byte buffer[sizeof(struct server_request_header)];
	int buffer_size = sizeof(buffer);

	int bytes_received = recv(socket, buffer, buffer_size, 0);
	int current_offset = 0;

	if(bytes_received < buffer_size)
	{
		fprintf(stderr, "[client_receive_response_header]: Failed to receive response header from server.\n");
		free(buffer);
		return false;
	}

	// Deserialize the response type and the expected parameters count
	// Copying byte ranges, so use memcpy
	memcpy(&header->request_type, buffer, sizeof(enum server_responses));
	current_offset = sizeof(enum server_responses);

	memcpy(&header->parameter_count, buffer + current_offset, sizeof(unsigned short));
	current_offset += sizeof(unsigned short);

	memcpy(&header->bytes_to_send, buffer + current_offset, sizeof(unsigned short));

	return true; // success
}


bool client_send_parameters_to_server(int socket, struct message_parameter **parameters, size_t parameters_length)
{
	if(parameters == NULL)
	{
		fprintf(stderr, "[client_send_parameters_to_server]: Parameters buffer points to NULL.\n");
		return false;
	}

	int send_status;                   // (1) For error checking
	int parameters_sent = 0;           // (2) Loop condition 

	struct message_parameter *current_parameter;
	size_t bytes_to_send;

	// Receiving acknowledgements from server
	int bytes_received;
	struct server_response_header response_header;
	bool receive_header_status;

	while(parameters_sent < parameters_length)
	{
		// Grab current parameter
		current_parameter = parameters[parameters_sent];

		// Check that parameter actually has data to send
		if(current_parameter->data == NULL)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Parameter %d has no data in its data member (void *data). Aborting parameter transmission (no further parameters will be sent).\n", parameters_sent);
			return false;
		}

		// Send individual member size
		send_status = send(socket, &current_parameter->member_size, sizeof(current_parameter->member_size));
		if(send_status < 0)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Failed to send member_size attribute of parameter %d to server.\n", parameters_sent);
			return false;
		}

		// Send member count
		send_status = send(socket, &current_parameter->member_count, sizeof(current_parameter->member_count));
		if(send_status < 0)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Failed to send member_count attribute of parameter %d to server.\n", parameters_sent);
			return false;
		}

		// Send parameter
		bytes_to_send = current_parameter->member_size * current_parameter->member_count;
		send_status = send(socket, current_parameter->data, bytes_to_send);
		if(send_status < 0)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Failed to the data buffer (void *data) of parameter %d to the server. No further parameters will be sent.\n", parameters_sent);
			return false;
		}

		// Receive response from server
		receive_header_status = client_receive_response_header(socket, &response_header);
		if(receive_header_status == false)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Failed to receive response header from client after sending parameter %d to server. Call to client_receive_response_header failed.\n", parameters_sent);
			return false;
		}
	
		// Check response is OK
		if(response_header.response_type != OK)
		{
			fprintf(stderr, "[client_send_parameters_to_server]: Failed to receive OK (0) from server after sending parmameter %d. Response type was %d.\n", parameters_sent, response_header.response_type); 
			return false;
		}

		// Increment parameters sent
		parameters_sent++;
	}
	return true;
}

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

	// For getting user input
	char *input_buffer = malloc(4096);
	if(input_buffer == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for input buffer.\n");
	}
	size_t input_buffer_length = 0;
	size_t input_buffer_capacity = 4096;	
	char c;

	// For sending requests
	struct request_header header;
	struct message_parameter **send_parameters = malloc(sizeof(struct message_parameter*) * 5); // default size
	if(send_parameters == NULL)
	{
		fprintf(stderr, "Failed to allocate buffer for storing parameters to be sent from client to server.\n");
		free(input_buffer);
		close(tcp_socket);
		return 1;
	}
	size_t send_parameters_length = 0;
	size_t send_parameters_size = 5;
	struct message_parameter current_send_parameter;
	bool send_parameters_status;

	// For breaking down user input
	char **tokens = malloc(sizeof(char*) * 5);
	size_t tokens_length = 0;
	size_t tokens_capacity = 5;

	// continuously send input to the client
	while(true)
	{
		c = fgetc(stdin);

		// send off request
		if(c == "\n")
		{
			// Break up individual pieces of request
			input_buffer[input_buffer_length] = '\0';
			char *token = strtok(input_buffer, ",");
			while(token != NULL)
			{
				tokens[tokens_length] = malloc(strlen(token));
				strcpy(tokens[tokens_length], token);
				tokens_length++;
				if(tokens_length >= tokens_capacity)
				{
					tokens_capacity *= 2;
					tokens = realloc(sizeof(char *) * tokens_capacity);
					if(tokens == NULL)
					{
						fprintf(stderr, "Failed to allocate more memory for tokenizing input.\n");
						break;
					}
				}
				token = strtok(NULL, ",");
			}
	
			// Form request
			if(strcmp(tokens[0], "DEVELOPER_TEST") == 0)
			{
				// build request header
				header->request_type = DEVELOPER_TEST;
				header->parameter_count = 1;
				header->bytes_to_send = strlen(tokens[2]);

				// send request header
				
				
				// build request parameters
				send_parameters[send_parameters_length] = message_parameter_create(1, header->bytes_to_send + 1);
				current_send_parameter = send_parameters[parameters_length];
				if(current_send_parameter == NULL)
				{
					fprintf(stderr, "Failed to create message_parameter before sending off to server.\n");
					break;
				}
				send_parameters_length++;
				
				// send request parameters
				send_parameters_status = client_send_parameters_to_server(tcp_socket, send_parameters, send_parameters_length);
				if(send_parameters_status == false)
				{
					fprintf(stderr, "Failed to send parameters off to server.\n");
					break;
				}

			}
			else
				break;
		}

		// increase string
		else
		{
			if(input_buffer_length >= input_buffer_capacity)
			{
				input_buffer_capacity *= 2;
				input_buffer = realloc(input_buffer, sizeof(char) * input_buffer_capacity);
				if(input_buffer == NULL)
				{
					fprintf(stderr, "Failed to allocate more memory for input buffer.\n");
					for(size_t i = 0; i < tokens_length; i++)
						free(tokens[i]);

					free(tokens);
					break;
				}
			}
			input_buffer[input_buffer_length] = c;
			input_buffer_length++;
		}
	}
	close(tcp_socket);
	return 0;
}
