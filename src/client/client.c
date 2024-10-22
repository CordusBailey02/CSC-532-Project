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
