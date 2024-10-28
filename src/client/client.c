#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_ADDR "142.93.199.100"
// #define SERVER_ADDR "127.0.0.1"
#include "../lib/terrorexchange.h"
#include "../lib/secure_connection.h"

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

	if(strcmp(str, "CATEGORY") == 0) 			return CATEGORY;
	else if(strcmp(str, "PROFILE") == 0) 			return PROFILE;
	else if(strcmp(str, "POST") == 0) 			return POST;
	else if(strcmp(str, "NOTIFICATION") == 0) 		return NOTIFICATION;
	else if(strcmp(str, "REPORT") == 0) 			return REPORT;
	else if(strcmp(str, "DEVELOPER_TEST_MESSAGE") == 0) 	return DEVELOPER_TEST_MESSAGE;
	else if(strcmp(str, "PAYLOAD_METADATA") == 0) 		return PAYLOAD_METADATA;	
	else if(strcmp(str, "PAYLOAD") == 0) 			return PAYLOAD;
	else if(strcmp(str, "ACKNOWLEDGEMENT") == 0) 		return ACKNOWLEDGEMENT;
	else 							return SUBJECT_ERROR;
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
	
	struct request_header outbound_request_header; 
	struct request_header inbound_request_header;

	bool send_status;
	bool receive_status;
	int send_attempts = 0;
	int receive_attempts = 0;

	char *action_type;
	char *subject_type;
	char *data;

	size_t inbound_payloads_length = 0;
	size_t inbound_payloads_capacity = 5;
	struct payload **inbound_payloads = malloc(sizeof(struct payload*) * inbound_payloads_capacity);
	if(inbound_payloads == NULL)
	{
		fprintf(stderr, "Failed to allocate memory to hold default payload count of %zu payloads.\n", inbound_payloads_capacity);
		close(tcp_socket);
		exit(EXIT_FAILURE);
	}
	struct payload *current_inbound_payload;
	size_t payloads_received = 0;
	size_t payloads_expected = 0;

	// MAINLOOP: Input data and send off to the server. Then, receive data.
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

		outbound_request_header.action = string_to_request_header_action(action_type, strlen(action_type));
		outbound_request_header.subject = string_to_request_header_subject(subject_type, strlen(subject_type));
	
		printf("Got action as \"%s\" (code %d).\n", action_type, outbound_request_header.action);
		printf("Got subject as \"%s\" (code %d).\n", subject_type, outbound_request_header.subject);
		printf("Got data as \"%s\" (length %zu).\n", data, strlen(data));


		if(outbound_request_header.action == GET)
		{
			fprintf(stderr, "GET DATA ABILITY UNIMPLEMENTED.\n");
			continue;
		}
		else // sending data to the server
		{
			switch(outbound_request_header.subject)
			{
				case DEVELOPER_TEST_MESSAGE:
					send_status = send_developer_test_message(tcp_socket, &outbound_request_header, data);
					if(send_status == false)
					{
						fprintf(stderr, "[ERROR] Failed to send developer test message to the server.\n"); break;
					}
					break;
				default:
					fprintf(stderr, "Unimplemented SEND case for subject %s.\n", subject_type);
					break;
			}
		}

		// Wait to receive data back for what we sent.
		receive_status = receive_request_header(tcp_socket, &inbound_request_header);
		receive_attempts = 1;
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_request_header(tcp_socket, &inbound_request_header);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "Failed to receive new information from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe there is a connection issue?\n");
			continue;
		}
		receive_attempts = 0;
	
		// Ensure payloads buffer is big enough to hold the number of payloads specified.
		if(inbound_payloads_capacity < inbound_request_header.parameter_count)
		{
			inbound_payloads_capacity = inbound_request_header.parameter_count + 5;
			inbound_payloads = realloc(inbound_payloads, sizeof(struct payload*) * inbound_payloads_capacity);
			if(inbound_payloads == NULL)
			{
				fprintf(stderr, "Failed to reallocate memory of inbound payloads buffer so that it can hold %zu payloads.\n", inbound_payloads_capacity);
				close(tcp_socket);
				exit(EXIT_FAILURE);
			}
		}

		// Send acknowledgement of receipt
		send_status = send_acknowledgement(tcp_socket, OK);
		send_attempts = 1;
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_acknowledgement(tcp_socket, OK);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "Failed to send OK acknowledgement to server after receiving request header. Send attempts reached/exceeded MAX_SEND_ATTEMPTS. Maybe there is something wrong with the connection?\n");
			continue;
		}
		send_attempts = 0;

		// Begin receiving payload metadata and payloads.
		payloads_received = 0;
		payloads_expected = inbound_request_header.parameter_count;

		if(inbound_payloads[0] == NULL) 
		{
			inbound_payloads[0] = malloc(sizeof(struct payload));
			if(inbound_payloads[0] == NULL)
			{
				fprintf(stderr, "Failed to allocate memory to hold first payload in payload buffer.\n");
				continue;
			}
		}
		current_inbound_payload = inbound_payloads[0];	
		while(payloads_received < payloads_expected)
		{
			// Receive payload metadata
			receive_status = receive_payload_metadata(tcp_socket, current_inbound_payload);
			receive_attempts = 1;
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload_metadata(tcp_socket, current_inbound_payload);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "Failed to receive payload metadata for first payload from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe something is wrong with the connection?\n");
				break;
			}
			receive_attempts = 0;

			// Ensure the current inbound payload can actually hold the data that is about to be received.
			if(current_inbound_payload->data != NULL)
				free(current_inbound_payload->data);

			current_inbound_payload->data = malloc(current_inbound_payload->member_size * current_inbound_payload->member_count);
			if(current_inbound_payload->data == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for the data buffer of the first payload to be received from the server.\n");
				break;
			}
			
			// Send acknowledgement for the payload metadata
			send_status = send_acknowledgement(tcp_socket, OK);
			send_attempts = 1;
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(tcp_socket, OK);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "Failed to send acknowledgement for receipt of payload metadata to the server. Send attempts exceeded MAX_SEND_ATTEMPTS. Maybe there is an issue with the connection?\n");
				break;
			}
			send_attempts = 0;

			// Receive actual payload
			receive_status = receive_payload(tcp_socket, current_inbound_payload);
			receive_attempts = 1;
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload(tcp_socket, current_inbound_payload);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "Failed to receive payload $%zu from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe there is something wrong with the connection?\n", payloads_received + 1);
				break;
			}
			receive_attempts = 0;

			// Acknowledge receipt of payload
			send_status = send_acknowledgement(tcp_socket, OK);
			send_attempts = 1;
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{	
				send_status = send_acknowledgement(tcp_socket, OK);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "Failed to send OK acknowledgement to server after receiving payload #%zu. Send attempts reached/exceeded MAX_SEND_ATTEMPTS. Maybe there is something wrong with the connection?\n", payloads_received + 1);
				break;
			}
			send_attempts = 0;

			payloads_received++;
		}
		
		// Review data received.
		if(inbound_request_header.action == SEND && inbound_request_header.subject == DEVELOPER_TEST_MESSAGE)
		{
			printf("Received: ");
			for(int i = 0; i < payloads_received; i++)
				printf("\"%s\" ", (char *) inbound_payloads[i]->data);
		}
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
