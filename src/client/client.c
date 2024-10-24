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
