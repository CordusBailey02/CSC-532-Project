<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_ADDR "142.93.199.100"
#include "../lib/terrorexchange.h"
#include "../lib/secure_connection.h"

enum ACTION string_to_request_header_action(char *str, size_t str_length)
{
	if(str == NULL)
	{
		fprintf(stderr, "[string_to_request_header_action]: Cannot parse string that points to NULL. Bad argument provided for char *str.\n");
		return ACTION_ERROR;
	}

	if(strcmp(str, "GET") == 0) 		return GET;
	else if(strcmp(str, "SEND") == 0) 	return SEND;
	else					return ACTION_ERROR;
}

enum SUBJECT string_to_request_header_subject(char *str, size_t str_length)
{
	if(str == NULL)
	{
		fprintf(stderr, "[string_to_request_header_subject]: Cannot parse string that points to NULL. Bad argument provided for char *str.\n");
		return SUBJECT_ERROR;
	}

	if(strcmp(str, "CATEGORY") == 0) return CATEGORY;
	else if(strcmp(str, "PROFILE") == 0) return PROFILE;
	else if(strcmp(str, "POST") == 0) return POST;
	else if(strcmp(str, "NOTIFICATION") == 0) return NOTIFICATION;
	else if(strcmp(str, "REPORT") == 0) return REPORT;
	else if(strcmp(str, "DEVELOPER_TEST_MESSAGE") == 0) return DEVELOPER_TEST_MESSAGE;
	else if(strcmp(str, "PAYLOAD_METADATA") == 0) return PAYLOAD_METADATA;	
	else if(strcmp(str, "PAYLOAD") == 0) return PAYLOAD;
	else if(strcmp(str, "ACKNOWLEDGEMENT") == 0) return ACKNOWLEDGEMENT;
	else return SUBJECT_ERROR;
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

	// for getting user input to send requests
	char input_buffer[4096]; 
	size_t input_buffer_length = 0;
	size_t input_buffer_capacity = 4096;
	struct outbound_request_header; 
	struct inbound_request_header;
	char *action_type;
	char *subject_type;
	char *data;
	while(true)
	{
		fgets(input_buffer, 4096, stdin);
		input_buffer_length = strlen(input_buffer);
		action_type = strtok(input_buffer, " ");
		if(action_type == NULL)
		{
			fprintf(stderr, "Unable to parse input. Action type is incorrect.\n");
			break;
		}
		subject_type = strtok(NULL, " ");
		if(action_type == NULL)
		{
			fprintf(stderr, "Unable to parse input. Subject type is incorrect.\n");
			break;
		}
		data = subject_type + strlen(subject_type) + 1; // pointer arithmetic.
		printf("Got action as \"%s\".\n", action_type);
		printf("Got subject as \"%s\".\n", subject_type);
		printf("Got data as \"%s\".\n", data);
	}

	// Perform handshake with the server
	uint32_t shared_secret;
	if (client_handshake(tcp_socket, &shared_secret) < 0) {
		fprintf(stderr, "Client handshake failed.\n");
		close(tcp_socket);
		exit(EXIT_FAILURE);
	}

	char message[] = "Hello, secure world! This works...";
	ssize_t bytes_sent = secure_send(tcp_socket, message, strlen(message), 0, shared_secret);
    	if (bytes_sent < 0) {
		perror("send");
    	}

	printf("Sent encrypted message and signature.\n");

	close(tcp_socket);
	return 0;
}
=======
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_ADDR "142.93.199.100"
#include "../lib/terrorexchange.h"
#include "../lib/secure_connection.h"

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

<<<<<<< HEAD
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
=======
	// Perform handshake with the server
	uint32_t shared_secret;
    if (client_handshake(tcp_socket, &shared_secret) < 0) {
        fprintf(stderr, "Client handshake failed.\n");
        close(tcp_socket);
        exit(EXIT_FAILURE);
    }

	char message[] = "Hello, secure world! This works...";
    ssize_t bytes_sent = secure_send(tcp_socket, message, strlen(message), 0, shared_secret);
    if (bytes_sent < 0) {
        perror("send");
    }

    printf("Sent encrypted message and signature.\n");

>>>>>>> d62fcb76f2e6664762e90db84916487e114b5a10
	close(tcp_socket);
	return 0;
}
>>>>>>> 20e88ae20a17fde9f5c2448a271892149c76d61f
