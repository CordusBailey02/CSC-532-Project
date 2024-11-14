#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include  "../lib/terrorexchange.h"
#include  "../lib/secure_connection.h"
#include "../database/terrorbase.h"
#define CONNECTION_BACKLOG_CAPACITY 128
#define PATH_MAX_SIZE 1024
#define VERIFICATION_FS_ROOT "verification-requests"

// used to pass multiple arguments to the pthread for each
// client connection
struct client_data
{
	int client_socket;
	uint32_t shared_secret;
};

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
		case LOGIN_ATTEMPT: 
			break;
		case USERNAME_CHANGE:
			break;
		case PASSWORD_CHANGE:
			break;
		case ACCOUNT_CREATE:
			break;
		case VERIFICATION_REQUEST:
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
	/*
	int client_socket = *(int *) arg; // dereference the argument casted as int ptr
	free(arg);
	*/
	struct client_data *client_connection_data = (struct client_data *) arg;
	int client_socket = client_connection_data->client_socket;
	uint32_t shared_secret = client_connection_data->shared_secret;
	free(client_connection_data);

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

	char *temporary_response;

	char ***mysql_result_table = malloc(4096);
	int *mysql_return_flag = malloc(sizeof(int));
	int *mysql_num_fields = malloc(sizeof(int));
	int *mysql_num_rows = malloc(sizeof(int));

	*mysql_return_flag = SUCCESS;
	*mysql_num_fields = 0;
	*mysql_num_rows = 0;

	bool variable_arguments_are_not_null = true;
	char file_system_write_path[PATH_MAX_SIZE];

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
		receive_status = receive_request_header(client_socket, &inbound_request_header, shared_secret);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_request_header(client_socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "[handle_client] Unable to receive request header from client. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Call to receive_request_header returned false. There might be something wrong with the connection.\n");
			continue;
		}
		receive_attempts = 0;	
		printf("Received request header for client socket %d\n", client_socket);
	
		// Check that the request header was actually valid 
		if(check_valid_request_header(&inbound_request_header) == false)
		{
			fprintf(stderr, "[handle_client] Received request header was formatted inproperly. Sending MALFORMED messgage to sender. check_valid_request_header() returned false.\n");
			send_status = send_acknowledgement(client_socket, MALFORMED, shared_secret);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{		
				send_status = send_acknowledgement(client_socket, MALFORMED, shared_secret);
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
		send_status = send_acknowledgement(client_socket, OK, shared_secret);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_acknowledgement(client_socket, OK, shared_secret);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "[handle_client] Unable to send acknowledgement to client. Send attempts reached or exceeded MAX_SEND_ATTEMPTS (send_acknowledgement returned false). Maybe something is wrong with the connection?\n");
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
		inbound_payloads_length = 0;
		payloads_received = 0;
		while(payloads_received < payloads_expected)
		{
			if(inbound_payloads[inbound_payloads_length] == NULL)
			{
				inbound_payloads[inbound_payloads_length] = malloc(sizeof(struct payload));
				if(inbound_payloads[inbound_payloads_length] == NULL)
				{
					fprintf(stderr, "[handle_client] Failed to allocate sufficient memory to hold inbound payload structs.\n");
					break;
				}
			}
			
			// Receive payload metadata so you can prepare to actually receive the payload itself
			printf("Waiting to receive payload metadata #%zu from client with client socket %d.\n", payloads_received + 1, client_socket);
			receive_status = receive_payload_metadata(client_socket, inbound_payloads[inbound_payloads_length], shared_secret);
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload_metadata(client_socket, inbound_payloads[inbound_payloads_length], shared_secret);
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
			send_status = send_acknowledgement(client_socket, OK, shared_secret);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(client_socket, OK, shared_secret);
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
			inbound_payloads[inbound_payloads_length]->data = malloc(inbound_payloads[inbound_payloads_length]->member_count * inbound_payloads[inbound_payloads_length]->member_size);
			if(inbound_payloads[inbound_payloads_length]->data == NULL)
			{
				fprintf(stderr, "[handle_client] Failed to allocate %zu bytes for the data buffer of the current inbound payload (payload %zu)\n", inbound_payloads[inbound_payloads_length]->member_size * inbound_payloads[inbound_payloads_length]->member_count, payloads_received);
				send_status = send_acknowledgement(client_socket, INSUFFICIENT_MEMORY, shared_secret);
				break;
			}

			// Actually receive the payload
			printf("Waiting to receive payload %zu's data attribute from client with client socket %d.\n", payloads_received + 1, client_socket);
			receive_status = receive_payload(client_socket, inbound_payloads[inbound_payloads_length], shared_secret);
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload(client_socket, inbound_payloads[inbound_payloads_length], shared_secret);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "[handle client] Failed to receive payload from client. Received %zu payloads in total. Expected to receive %zu overall.\n", payloads_received, payloads_expected);
				break;
			}
			receive_attempts = 0;
			printf("Received payload %zu's data attribute from client with client socket %d.\n", payloads_received + 1, client_socket);		

			// Acknowledge that you received the payload
			printf("Sending OK acknowledgement to client with client socket %d.\n", client_socket);
			send_status = send_acknowledgement(client_socket, OK, shared_secret);
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(client_socket, OK, shared_secret);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "[handle_client] Failed to send OK acknowledgement to client after receiving the data for payload #%zu of %zu.\n", payloads_received + 1, payloads_expected);
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
				case POST:
					printf("[UNIMPLEMENTED ERROR] Cannot fetch posts at the moment.\n");
					break;
				default:
					break;
			}
		}
		else // client is sending us data - SEND
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
					send_status = send_developer_test_message(client_socket, &outbound_request_header, (char *) inbound_payloads[0]->data, shared_secret);
					if(send_status == false)
					{
						fprintf(stderr, "[handle_client] Main logic: Failed to send developer test message to client. Something might be wrong with the connection.\n");
						break;
					}
					printf("Successfully sent developer test message back to client.\n");	
					break;

				case LOGIN_ATTEMPT:
					bool login_success = false;
					printf("SEND LOGIN_ATTEMPT received from client with client socket %d.\n", client_socket);
					if(inbound_payloads[0]->data == NULL)
					{
						fprintf(stderr, "[handle_client] Inbound payload #1's data buffer is NULL. For a SEND LOGIN_ATTEMPT request header, 2 non-NULL payloads are expected. Maybe the data was sent erroneously?\n");
						break;
					}
					if(inbound_payloads[1]->data == NULL)
					{
						fprintf(stderr, "[handle_client] Inbound payload #2's data buffer is NULL. For a SEND LOGIN_ATTEMPT request header, 2 non-NULL payloads are expected. Maybe the data was sent erroneously?\n");
						break;
					}
					printf("Got username: \"%s\", password: \"%s\"\n", (char *) inbound_payloads[0]->data, (char *) inbound_payloads[1]->data);
					// DO DATABASE THING HERE
					mysql_result_table = mysql_database_query("check_user", inbound_payloads, mysql_result_table, mysql_return_flag, mysql_num_fields, mysql_num_rows);
					switch(*mysql_return_flag)
					{
						case SUCCESS:
							printf("Got result: %d rows, %d fields.\n", (*mysql_num_rows), (*mysql_num_fields));
							break;
						case CONNECTION_ERROR:
							fprintf(stderr,"[handle_client] Connection to MYSQL when running query produced an error. Check error given.\n");
						case INEXISTENT_QUERY:
							fprintf(stderr, "[handle_client] Attempted query given does not exist.\n");
							break;
						case INSUFFICIENT_PARAMETERS:
							fprintf(stderr, "[handle_client] Attempted query requires more parameters than was given.\n");
							break;
						default:
							break;
					}
					for(int i = 0; i < *mysql_num_rows; i++)
					{
						printf("[ ");
						for(int j = 0; j < (*mysql_num_fields); j++)
							printf("\"%s\" ", mysql_result_table[i][j]);
						printf("]\n"); 	
					}

					if(!strcmp(mysql_result_table[0][0], "exists"))
					{
						unsigned char hash[20];
						SHA1(inbound_payloads[1]->data, inbound_payloads[1]->member_size, hash);
						mysql_result_table = mysql_database_query("get_user_sha", inbound_payloads, mysql_result_table, mysql_return_flag, mysql_num_fields, mysql_num_rows);
						switch(*mysql_return_flag)
						{
							case SUCCESS:
								printf("Got result: %d rows, %d fields.\n", (*mysql_num_rows), (*mysql_num_fields));
								break;
							case CONNECTION_ERROR:
								fprintf(stderr,"[handle_client] Connection to MYSQL when running query produced an error. Check error given.\n");
							case INEXISTENT_QUERY:
								fprintf(stderr, "[handle_client] Attempted query given does not exist.\n");
								break;
							case INSUFFICIENT_PARAMETERS:
								fprintf(stderr, "[handle_client] Attempted query requires more parameters than was given.\n");
								break;
							default:
								break;
						}
						if(!strcmp(mysql_result_table[0][0], hash))
						{
							login_success = true;
						}
					}
					printf("Login Success: %s\n", login_success ? "TRUE" : "FALSE");
					
					// TEMPORARY RESPONSE UNTIL DATABASE BEHAVIOR IS IMPLEMENTED
					temporary_response = malloc(40 + 3);
					if(temporary_response == NULL)
					{
						fprintf(stderr, "[handle_client] Failed to allocate memory for a temporary message to send back to the client until the database connection is implemented.\n");
						break;
					}
					sprintf(temporary_response, "%s \n", login_success ? "TRUE" : "FALSE");
					send_status = send_developer_test_message(client_socket, &outbound_request_header, temporary_response, shared_secret);
					free(temporary_response);
					if(send_status == false)
					{
						fprintf(stderr, "[handle_client] Failed to send developer test message to client. Something might be wrong with the connection.\n");
						break;
					}
					printf("Successfully sent temporary response to client with socket #%d for their SEND LOGIN_ATTEMPT message.\n", client_socket);
					break;

				case ACCOUNT_CREATE:
					printf("SEND ACCOUNT_CREATE received from client with client socket %d.\n", client_socket);
					if(inbound_payloads[0]->data == NULL)
					{
						fprintf(stderr, "[handle_client] Inbound payload #%d's data buffer is NULL. For a SEND ACCOUNT_CREATE request header, 3 non-NULL payloads are expected. Maybe the data was sent erroneously?\n", client_socket);
						break;
					}
					if(inbound_payloads[1]->data == NULL)
					{
						fprintf(stderr, "[handle_client] Inbound payload #2's data buffer is NULL. For a SEND ACCOUNT_CREATE request header, 3 non-NULL payloads are expected. Maybe the data was sent erroneously from client with socket #%d?\n", client_socket);
						break;
					}
					if(inbound_payloads[2]->data == NULL)
					{
						fprintf(stderr, "[handle_client] Inbound payload 3's data buffer is NULL. For a SEND ACCOUNT_CREATE request header, 3 non-NULL payloads are expected. Maybe the data was sent erroneously from client with socket #%d?\n", client_socket);
						break;
					}
					// Review what was received
					printf("Got username: \"%s\", email: \"%s\", password: \"%s\" from client with socket #%d.\n", (char*) inbound_payloads[0]->data, (char*) inbound_payloads[1]->data, (char*) inbound_payloads[2]->data, client_socket);

					// Send a temporary response
					int username_length, email_length, password_length;
					username_length = strlen(inbound_payloads[0]->data);
					email_length = strlen(inbound_payloads[1]->data);
					password_length = strlen(inbound_payloads[2]->data);
					temporary_response = malloc(username_length + email_length + password_length + 60);
					if(temporary_response == NULL)
					{
						fprintf(stderr, "[handle_client] Failed to allocate memory for a temporary message to send back to the client until the database connection is implemented.\n");
						continue;
					}
					sprintf(temporary_response, "Got username: \"%s\", email: \"%s\", password: \"%s\".\n", (char*) inbound_payloads[0]->data, (char*) inbound_payloads[1]->data, (char*) inbound_payloads[2]->data);
					printf("Temporary response to send off to client is \"%s\"\n", temporary_response);
					send_status = send_developer_test_message(client_socket, &outbound_request_header, temporary_response, shared_secret);
					free(temporary_response);
					if(send_status == false)
					{
						fprintf(stderr, "[handle_client] Failed to send developer test message to client as part of temporary response to send_account_create to client with socket #%d.\n", client_socket);
						break;
					}
					printf("Successfully sent temporary response to client with socket #%d for their send account_create request.\n", client_socket);
					break;

				case VERIFICATION_REQUEST:
					printf("Received SEND VERIFICATION_REQUEST request header from client with socket %d.\n", client_socket);

					// Check that verification category exists (e.g. "programmer")
					if(inbound_payloads[0]->data == NULL) {
						fprintf(stderr, "[handle_client] Inbound payload 0's data buffer is NULL. For a SEND VERIFICATION_REQUEST request header, at least 2 non-NULL parameters must be sent.\n");
						break;
					}
						
					// Check that the binary data of the files is not NULL
					variable_arguments_are_not_null = true;
					for(int i = 1; i < inbound_payloads_length; i++) {
						if(inbound_payloads[i]->data != NULL) continue;

						fprintf(stderr, "[handle_client] Inbound payload #%d has a data buffer that is NULL. Expected file binary data, but there is nothing there. No files can be stored and reviewed later.\n", i + 1);
						variable_arguments_are_not_null = false;
					}
					
					// Jump out of this section if files are not loaded
					if(variable_arguments_are_not_null == false) 
						break;

					// Check validity of professional category
					//
					// Resolve file path on system to save it

					// Write files into file system


					break;

				default:
					printf("Unimplemented subject code for SEND message from client with socket #%d.\n", client_socket);
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
	if(argc < 2) {
		fprintf(stderr, "Not enough args... Provide a port...");
		exit(EXIT_FAILURE);
	}
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
	server_addr.sin_port = htons(atoi(argv[1])); // tcp

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
	printf("Now listening for connections on TCP port %d.\n", atoi(argv[1]));

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
			continue;
    		}
		
		// Create client data to pass to handle_client so thread has both
		// client socket and shared secret
		struct client_data *client_connection_data = malloc(sizeof(struct client_data));
		if(client_connection_data == NULL)
		{
			fprintf(stderr, "Failed to allocate memory for a client data struct. Client with socket %d will not be accepted/handled (pthread cannot run handle_client without client_socket and shared_key).\n", *client_socket);
			close(*client_socket);
			free(client_socket);
			continue;
		}
		client_connection_data->client_socket = *client_socket;
		client_connection_data->shared_secret = shared_secret;

		// Spawn a new thread to handle the client using handle_client function.
		pthread_t thread_id;
		// if(pthread_create(&thread_id, NULL, handle_client, (void *) client_socket) != 0)
		if(pthread_create(&thread_id, NULL, handle_client, (void *) client_connection_data) != 0)
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
