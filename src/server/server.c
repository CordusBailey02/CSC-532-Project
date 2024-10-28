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
#define CONNECTION_BACKLOG_CAPACITY 128

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

bool check_valid_request_header(struct request_header *header)
{
	if(header->action != GET && header->action != SEND)
		return false;

	switch(header->subject)
	{
		case CATEGORY:
			break;
		case PROFILE:
			break;
		case POST:
			break;
		case NOTIFICATION:
			break;
		case REPORT:
			break;
		case DEVELOPER_TEST_MESSAGE:
			break;
		case PAYLOAD_METADATA:
			break;
		case PAYLOAD:
			break;
		case ACKNOWLEDGEMENT:
			break;
		default:
			return false;
			break;
	}

	if(header->metadata_total_size > header->total_bytes) return false;
	if(header->parameters_total_size > header->total_bytes) return false;
	if(header->metadata_total_size + header->parameters_total_size > header->total_bytes) return false;
	
	return true;
}

// Generates a 4 digit code for the email verification
int generate_code()
{
    int num = rand() % 9000 + 1000;
    return num;
}

// Sends an email to the provided email
// Generates code in function and sends it in the email
void send_email(const char* name, const char* email)
{
    // Generate the 4 digit number
    int generated_code = generate_code();

    printf("Generated numbers: %d\n", generated_code);

    // Call the Python script
    char command[256];
    // Paramaters to send: Name, email, generated_code
    snprintf(command, sizeof(command), "python3 send_email.py %s %s %d", name, email, generated_code);
    system(command);

	// STORE THE CODE TO COMPARE WHAT THE CLIENT INPUTS
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
		return NULL;
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
		return NULL;
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
		printf("Waiting to receive request header for client socket %d...\n", client_socket);
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
		printf("Received request header for client socket %d\n", client_socket);
	
		// Check that the request header was actually valid 
		if(check_valid_request_header(&inbound_request_header) == false)
		{
			fprintf(stderr, "[handle_client] Received request header was formatted inproperly. Sending MALFORMED messgage to sender. check_valid_request_header() returned false.\n");
			send_status = send_acknowledgement(client_socket, MALFORMED);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{		
				send_status = send_acknowledgement(client_socket, MALFORMED);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "[handle_client] Failed to send MALFORMED acknowledgement to client after receiving a malformed request header. MAX_SEND_ATTEMPTS was met/surpassed.\n");
				continue;
			}
			send_attempts = 0;
			continue;
		}

		// Acknowledge that you received it (AND IT WAS A GOOD HEADER)	
		printf("Sending OK acknowledgement to client with client socket %d...\n", client_socket);
		send_status = send_acknowledgement(client_socket, OK);
		while(send_status == false && send_attempts < 10)
		{
			send_status = send_acknowledgement(client_socket, OK);
			send_attempts++;
		}
		if(send_attempts >= 10)
		{
			fprintf(stderr, "[handle_client] Unable to send acknowledgement to client. Send attempts reached or exceeded 10 (send_acknowledgement returned false)\n");
			continue;
		}
		send_attempts = 0;
		printf("Sent OK acknowledgement to client with client socket %d.\n", client_socket);
		
		// Setup inbound payloads buffer (to store all payloads) 
		payloads_expected = inbound_request_header.parameter_count;
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
		printf("%zu payloads are expected from client with client socket %d.\n", payloads_expected, client_socket);

		// Receive payloads (metadata, then payload itself)
		struct payload *current_inbound_payload;	
		inbound_payloads_length = 0;
		payloads_received = 0;
		clean_payload_buffer(inbound_payloads, &inbound_payloads_length); // no previous data
		while(payloads_received < payloads_expected)
		{
			current_inbound_payload = inbound_payloads[payloads_received];
			if(current_inbound_payload == NULL)
			{
				current_inbound_payload = malloc(sizeof(struct payload));
				if(current_inbound_payload == NULL)
				{
					fprintf(stderr, "[handle_client] Failed to allocate sufficient memory to hold inbound payload structs.\n");
					break;
				}
			}
			
			// Receive payload metadata so you can prepare to actually receive the payload itself
			printf("Waiting to receive payload metadata #%zu from client with client socket %d.\n", payloads_received + 1, client_socket);
			receive_status = receive_payload_metadata(client_socket, current_inbound_payload);
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload_metadata(client_socket, current_inbound_payload);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "[handle_client] Failed to receive payload metadata from the client. 10 or more attempts were reached. receive_payload_metadata() returned false.\n");
				continue;
			}
			receive_attempts = 0;
			printf("Received payload metadata for payload #%zu from client with client socket %d.\n", payloads_received + 1, client_socket);

			// Acknowledge receipt of payload metadata
			printf("Sending OK acknowledgement for payload %zu's metadata to client with client_socket %d.\n", payloads_received + 1, client_socket);
			send_status = send_acknowledgement(client_socket, OK);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(client_socket, OK);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "[handle_client] Failed to send OK acknowledgement for receipt of payload metadata for payload #%zu out of %zu.\n", payloads_received + 1, payloads_expected);
				continue;
			}
			send_attempts = 0;
			printf("Sent OK acknowledgement to client with client socket %d.\n", client_socket);

			// Ensure current inbound payload can actually store the data
			current_inbound_payload->data = malloc(current_inbound_payload->member_count * current_inbound_payload->member_size);
			if(current_inbound_payload->data == NULL)
			{
				fprintf(stderr, "[handle_client] Failed to allocate %zu bytes for the data buffer of the current inbound payload (payload %zu)\n", current_inbound_payload->member_size * current_inbound_payload->member_count, payloads_received);
				send_status = send_acknowledgement(client_socket, INSUFFICIENT_MEMORY);
				break;
			}

			// Actually receive the payload
			printf("Waiting to receive payload %zu's data attribute from client with client socket %d.\n", payloads_received + 1, client_socket);
			receive_status = receive_payload(client_socket, current_inbound_payload);
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload(client_socket, current_inbound_payload);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "[handle client] Failed to receive payload from client. Received %zu payloads in total. Expected to receive %zu overall.\n", payloads_received, payloads_expected);
				clean_payload_buffer(inbound_payloads, &inbound_payloads_length);
				break;
			}
			receive_attempts = 0;
			printf("Received payload %zu's data attribute from client with client socket %d.\n", payloads_received + 1, client_socket);		

			// Acknowledge that you received the payload
			printf("Sending OK acknowledgement to client with client socket %d.\n", client_socket);
			send_status = send_acknowledgement(client_socket, OK);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(client_socket, OK);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "[handle_client] Failed to send OK acknowledgement to client after receiving the data for payload #%zu of %zu.\n", payloads_received + 1, payloads_expected);
				clean_payload_buffer(inbound_payloads, &inbound_payloads_length);
				break;
			}
			send_attempts = 0;
			printf("Sent OK acknowledgement to client with client socket %d.\n", client_socket);

			// Increment and now restart at loop beginning to receive the rest of the payloads
			payloads_received++;
			inbound_payloads_length++;
		}
		printf("Done receiving payloads from client with client socket %d!\n", client_socket);

		// If all the payloads WERE NOT received, start back from
		// beginning of routine 
		if(payloads_received != payloads_expected)
		{
			fprintf(stderr, "[handle_client] Did not receive expected amount of payloads from the client. Expected %zu but only received %zu.\n", payloads_expected, payloads_received);
			continue;
		}
		
		// If all payloads WERE received, then respond to the client accordingly
		if(inbound_request_header.action == GET)
		{
			printf("Responding to GET request from client with client socket %d...\n", client_socket);
			switch(inbound_request_header.subject)
			{
				case DEVELOPER_TEST_MESSAGE:
					break;
				default:
					break;
			}
		}
		else // client is sending us data
		{
			printf("Responding to SEND request from client with client socket %d...\n", client_socket);
			switch(inbound_request_header.subject)
			{
				case DEVELOPER_TEST_MESSAGE:
					printf("SEND DEVELOPER_TEST_MESSAGE received from client with client socket %d.\n", client_socket);
					if(inbound_payloads[0] == NULL) 
						printf("inbound payload 0 is null.\n");
					else
						printf("inbound payload 0 is NOT null.\n");
					if(inbound_payloads[0]->data == NULL)
						printf("inbound payload 0 data is null.\n");
					else 
						printf("inbound payload 0 data is NOT null.\n");
					printf("Message received from client was \"%s\"\n", (char *) inbound_payloads[0]->data);
					printf("Attempting to use send_developer_test_message function to reply to client with client socket %d.\n", client_socket);
					send_status = send_developer_test_message(client_socket, &outbound_request_header, (char *) inbound_payloads[0]->data);
					if(send_status == false)
					{
						fprintf(stderr, "[handle_client] Main logic: Failed to send developer test message to client. Something might be wrong with the connection.\n");
						break;
					}
					printf("Successfully sent developer test message back to client.\n");	
					break;
				default:
					break;
			}
		}

		// continue whole thing of receiving/sending data
	}

	close(client_socket);
	return NULL;
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
	if(listen(server_fd, CONNECTION_BACKLOG_CAPACITY) < 0)
	{
		fprintf(stderr, "Listening failed.\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Now listening for connections on TCP port 8080.\n");

	// Accept client connections --- spawn a new thread for each new connection.
	while(true)
	{
		struct sockaddr_in client_addr;
		int addrlen = sizeof(client_addr);
		int *client_socket = malloc(sizeof(int));
		if(client_socket == NULL)
		{ 
			fprintf(stderr, "Failed to allocate memory for client socket.\n");
			continue;
		}	
		*client_socket = accept(server_fd, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen);
		if(*client_socket < 0)
		{
			fprintf(stderr, "Failed to accept connection.\n");
			free(client_socket);
			continue;
		}
		printf("Client connection accepted.\n");

		// Perform handshake with the client
		uint32_t shared_secret;
		if (server_handshake(*client_socket, &shared_secret) < 0) {
			fprintf(stderr, "Server handshake failed.\n");
			close(*client_socket);
			free(client_socket);
    	}

		// Spawn a new thread to handle the client using handle_client function.
		pthread_t thread_id;
		if(pthread_create(&thread_id, NULL, handle_client, (void *) client_socket) != 0)
		{
			fprintf(stderr, "Failed to create thread.\n");
			close(*client_socket);
			free(client_socket);
		}
		// Cleanup resources after the thread finishes.
		else 
			pthread_detach(thread_id);
	}

	// Cleanup
	close(server_fd);
	return 0;
}
