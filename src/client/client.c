#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
// #define SERVER_ADDR "142.93.199.100"
#define SERVER_ADDR "127.0.0.1"
#define USERNAME_MAX_LENGTH 16
#define PASSWORD_MAX_LENGTH 16
#include "../lib/terrorexchange.h"
#include "../lib/secure_connection.h"

struct client_state {
	char *username;
	char *email;
	bool signed_in;
	enum SUBJECT last_thing_sent;
	enum SUBJECT last_thing_received;	
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
	else if(strcmp(str, "LOGIN_ATTEMPT") == 0)		return LOGIN_ATTEMPT;
	else if(strcmp(str, "USERNAME_CHANGE") == 0)		return USERNAME_CHANGE;
	else if(strcmp(str, "PASSWORD_CHANGE") == 0)		return PASSWORD_CHANGE;
	else if(strcmp(str, "ACCOUNT_CREATE") == 0)		return ACCOUNT_CREATE;
	else if(strcmp(str, "VERIFICATION_REQUEST") == 0)	return VERIFICATION_REQUEST;
	else 							return SUBJECT_ERROR;
}

int main(int argc, char **argv)
{
	bool use_gui = true;
	if(argc > 1) {
		if(strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--no-gui") == 0 )
			use_gui = false;
	}

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

	// Perform handshake with the server
	uint32_t shared_secret;
	if (client_handshake(tcp_socket, &shared_secret) < 0) {
		fprintf(stderr, "Client handshake failed.\n");
		close(tcp_socket);
		exit(EXIT_FAILURE);
	}
	
	// for getting user input to send requests
	char input_buffer[4096]; 
	size_t input_buffer_length = 0;
	size_t input_buffer_capacity = 4096;

	char outbound_buffer[4096];
	size_t outbound_data_buffer_length = 0;
	size_t outbound_data_buffer_capacity = 4096;
	
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
	
	char default_username[] = "guest";
	char *username = default_username;
	char *password;
	char *email;
	int username_length = 0;
	int password_length = 0;
	int email_length = 0;
	bool valid_email = false;

	char *verification_type;
	int verification_type_length = 0;
	char **file_paths = malloc(sizeof(char *) * 5);
	if(file_paths == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for a buffer to hold 5 file paths.\n");
		close(tcp_socket);
		exit(EXIT_FAILURE);
	}
	int file_paths_length = 0;
	int file_paths_capacity = 5;
	
	struct client_state client_user_state;
	client_user_state.username = default_username;
	client_user_state.email = NULL;
	client_user_state.signed_in = false;
	client_user_state.last_thing_sent = INITIAL_SUBJECT_CODE;
	client_user_state.last_thing_received = INITIAL_SUBJECT_CODE;
		
	// Used to prevent client from waiting to receive something when data was 
	// input erroneously. If nothing was sent, it will never receive anything.
	// So, it shouldn't enter the waiting logic as it will wait forever.
	bool DATA_SENT_FLAG = false;
	
	if(use_gui == true)
	{
		// START GUI AND CONNECT TO IT
		// (1) Create connection socket
		int client_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(client_fd == -1)
		{
			fprintf(stderr, "Failed to create socket for connection to GUI process.\n");
			exit(EXIT_FAILURE);
		}

		// (2) bind socket to IP addr and port for GUI connection
		struct sockaddr_in client_addr;
		client_addr.sin_family = AF_INET;
		client_addr.sin_addr.s_addr = INADDR_ANY; // bind to all available network ifaces
		client_addr.sin_port = htons(55000); 	       // random port chosen for the client and GUI to communicate
		if( bind(client_fd, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0 )
		{
			fprintf(stderr, "Failed to bind socket to port 55000 (port for client-GUI communication.\n"); 
			close(client_fd);
			exit(EXIT_FAILURE);
		}

		// (3) Listen for connection from GUI
		if( listen(client_fd, 0) < 0 ) // only want ONE gui connection - no backlogging for several
		{
			fprintf(stderr, "Listening on port 55000 for GUI connection failed.\n");
			close(client_fd);
			exit(EXIT_FAILURE);
		}
		printf("Listening on port 55000 for a connection from the GUI.\n");
		
		// (4) spawn GUI process
		system("../../LinuxProtoTypeGUI_v0.8/clientGUI");

		// (5) Accept GUI connection
		struct sockaddr_in GUI_PROCESS_ADDR;	
		int gui_process_addrlen = sizeof(GUI_PROCESS_ADDR);
		int *gui_socket = malloc(sizeof(int));
		if(gui_socket == NULL)
		{ 
			fprintf(stderr, "Failed to allocate memory for client socket.\n");
			exit(EXIT_FAILURE);
		}
		*gui_socket = accept(client_fd, (struct sockaddr*) &client_addr, (socklen_t*) &gui_process_addrlen);
		if(*gui_socket < 0)
		{
			fprintf(stderr, "Failed to accept connection.\n");
			free(gui_socket);
			exit(EXIT_FAILURE);
		}
		printf("GUI connection established.\n");
	}
	
	// MAINLOOP: Input data and send off to the server. Then, receive data.
	while(true)
	{
		// temporary. Later this doesnt have to get checked each time.
		// The LOGIN_ATTEMPT and ACCOUNT_CREATE procedure will update the 
		// username pointer.
		if(client_user_state.signed_in == false) client_user_state.username = default_username;

		// get user input
		printf("\n%s@demake$ ", client_user_state.username);
		fgets(input_buffer, 4096, stdin);
		input_buffer_length = strlen(input_buffer);

		// remove newline and replace with null terminator
		if(input_buffer_length == 0) continue;
		input_buffer[input_buffer_length - 1] = '\0';
		input_buffer_length -= 1;

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
		memcpy(outbound_buffer, data, strlen(data) + 1);

		// exit the program when user enters "exit"
		if(strcmp(action_type, "exit") == 0) {
			for(int i = 0; i < inbound_payloads_length; i++) {
				if(inbound_payloads[i]->data == NULL) continue;

				free(inbound_payloads[i]->data);
				free(inbound_payloads[i]);
			}
			free(inbound_payloads);
			
			if(client_user_state.username != default_username)
				free(client_user_state.username);
	
			close(tcp_socket);
			exit(EXIT_SUCCESS);
		} 

		// SEND SOMETHING TO THE SERVER BASED ON WHAT THE USER INPUT
		if(outbound_request_header.action == GET)
		{
			fprintf(stderr, "GET DATA ABILITY UNIMPLEMENTED.\n");
			DATA_SENT_FLAG = false;
			continue;
		}
		else // SENDing data to the server
		{
			DATA_SENT_FLAG = false;
			switch(outbound_request_header.subject)
			{
				case DEVELOPER_TEST_MESSAGE:
					send_status = send_developer_test_message(tcp_socket, &outbound_request_header, data, shared_secret);
					if(send_status == false)
					{
						fprintf(stderr, "[ERROR] Failed to send developer test message to the server.\n");
						DATA_SENT_FLAG = false;
					}
					DATA_SENT_FLAG = true;
					client_user_state.last_thing_sent = DEVELOPER_TEST_MESSAGE;
					break;

				case LOGIN_ATTEMPT:
					// Parse input for username
					username = strtok(outbound_buffer, " ");
					if(username == NULL)
					{
						fprintf(stderr, "Unable to tokenize user input to resolve username.\n");
						continue;		
					}
					username_length = strlen(username) + 1;
					if(username_length >= USERNAME_MAX_LENGTH)
					{
						fprintf(stderr, "Username is too long (%d+ characters).\n", USERNAME_MAX_LENGTH);
						continue;
					}
					// Parse input for password
					password = strtok(NULL, " ");
					if(password == NULL) {
						fprintf(stderr, "Unable to tokenize user input to resolve password.\n");
						continue;
					}
					password_length = strlen(password) + 1;
					if(password_length >= PASSWORD_MAX_LENGTH) {
						fprintf(stderr, "Password is too long (%d+ characters).\n", PASSWORD_MAX_LENGTH);
						continue;
					}
					printf("Got username: \"%s\", password: \"%s\".\n", username, password);

					// Try to send off to the server (UNIMPLEMENTED)
					send_status = send_login_attempt(tcp_socket, &outbound_request_header, username, username_length, password, password_length, shared_secret);
					if(send_status == false) {	
						fprintf(stderr, "[ERROR] Failed to send login attempt to the server. send_login_attempt returned false.\n");
						continue;
					}
					DATA_SENT_FLAG = true;
					client_user_state.last_thing_sent = LOGIN_ATTEMPT;
					break;

				case ACCOUNT_CREATE:
					// Parse input for username
					username = strtok(outbound_buffer, " ");
					if(username == NULL)
					{
						fprintf(stderr, "Unable to tokenize user input to resolve username.\n");
						continue;
					}
					username_length = strlen(username) + 1;
					if(username_length > USERNAME_MAX_LENGTH)
					{
						fprintf(stderr, "Username is too long (%d+ characters).\n", USERNAME_MAX_LENGTH);
						continue;
					}
					// Parse input for email
					email = strtok(NULL, " ");
					if(email == NULL)
					{
						fprintf(stderr, "Unable to tokenize user input to resolve email.\n");
						continue;
					}
					email_length = strlen(email) + 1;
					if(email_length >= 64)
					{
						fprintf(stderr, "Email is too long (64+ characters).\n");
						continue;
					}
					for(int email_i = 0; email_i < email_length; email_i++)
					{
						if(email[email_i] == '@') {
							valid_email = true;
							break;
						}
					} 
					if(valid_email == false) { 
						fprintf(stderr, "Email address \"%s\" does not have a domain (no @ symbol found).\n", email);
						DATA_SENT_FLAG = false;
						continue;
					}

					// Parse input for password
					password = strtok(NULL, " ");
					if(password == NULL) {
						fprintf(stderr, "Unable to tokenize password to resolve password.\n");
						DATA_SENT_FLAG = false;
						continue;
					}
					password_length = strlen(password) + 1;
					if(password_length > PASSWORD_MAX_LENGTH)
					{
						fprintf(stderr, "Password is too long (%d+ characters).\n", PASSWORD_MAX_LENGTH);
						DATA_SENT_FLAG = false;
						continue;
					}
					// remove later
					printf("Got username: \"%s\", email: \"%s\", password: \"%s\".\n", username, email, password);
					// send the information off to the server
					send_status = send_account_create(tcp_socket, &outbound_request_header, username, username_length, email, email_length, password, password_length, shared_secret);
					if(send_status == false)
					{
						fprintf(stderr, "[ERROR] Failed to send account creation attempt to the server. send_account_create returned false.\n");
						DATA_SENT_FLAG = false;
					}
					DATA_SENT_FLAG = true;
					client_user_state.last_thing_sent = ACCOUNT_CREATE;
					break;

				case VERIFICATION_REQUEST:
					if(client_user_state.signed_in == false) { 
						fprintf(stderr, "\nSystem: You must be signed in to send a verification request.\n");
						break;
					}

					printf("WARNING: File paths cannot contain spaces! Replace spaces with hyphens (-) until a better parsing system is created.\n");
					DATA_SENT_FLAG = false;
					file_paths_length = 0;
					// Parse for username
					username = strtok(outbound_buffer, " ");
					if(username == NULL) {
						fprintf(stderr, "Unable to tokenize user input to resolve username.\n");
						continue;
					}
				
					// Parse for email
					email = strtok(NULL, " ");
					if(email == NULL) {
						fprintf(stderr, "Unable to tokenize user input to resolve email.\n");
						continue;
					}

					// Parse for type of verification
					verification_type = strtok(NULL, " ");
					if(verification_type == NULL) {
						fprintf(stderr, "Unable to tokenize user input to resolve type of verification request.\n");
						continue;
					}
					
					// Parse for paths of documents to be uploaded
					file_paths[file_paths_length] = strtok(NULL, " ");
					while(file_paths[file_paths_length] != NULL)
					{
						file_paths_length++;
						if(file_paths_length >= file_paths_capacity)
						{
							file_paths_capacity += 5;
							file_paths = realloc(file_paths, sizeof(char *) * file_paths_capacity);

							if(file_paths == NULL) {
								fprintf(stderr, "Failed to allocate more memory for the file paths buffer. Current length is %d and the call to realloc tried to expand it to %d. Maybe the system is low on memory?\n", file_paths_length, file_paths_capacity);
								close(tcp_socket);
								exit(EXIT_FAILURE);
							}
						}
						file_paths[file_paths_length] = strtok(NULL, " ");
					}

					// try to send this information off to the server
					send_status = send_verification_request(tcp_socket, &outbound_request_header, username, email, verification_type, file_paths, file_paths_length, shared_secret);
					if(send_status == false) {
						fprintf(stderr, "[ERROR] Failed to send verification request to the server. The function send_verification_request() returned false.\n");
						break;
					}
					DATA_SENT_FLAG = true;
					client_user_state.last_thing_sent = VERIFICATION_REQUEST;
					
					// clean up strings within file paths buffer (leave buffer itself)
					for(int i = 0; i < file_paths_length; i++)
						free(file_paths[i]);
					
					break;

				default:
					fprintf(stderr, "Unimplemented SEND case for subject %s.\n", subject_type);
					DATA_SENT_FLAG = false;					
					break;
			}
		}
		
		// Don't wait to receive data if you never sent anything (forever halting)
		if(DATA_SENT_FLAG == false) continue;
		
		// Wait to receive data back for what we sent.
		printf("Waiting to receive response request header from server...\n");
		receive_status = receive_request_header(tcp_socket, &inbound_request_header, shared_secret);
		receive_attempts = 1;
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_request_header(tcp_socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "Failed to receive new information from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe there is a connection issue?\n");
			continue;
		}
		receive_attempts = 0;
		printf("Received request header from server. Subject code was %d.\n", inbound_request_header.subject);
	
		// Ensure payloads buffer is big enough to hold the number of payloads specified.
		printf("Checking if there is sufficient memory to store specified payloads...\n");
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
		printf("Memory check done.\n");

		// Send acknowledgement of receipt
		printf("Sending acknowledgement to server...\n");
		send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
		send_attempts = 1;
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "Failed to send OK acknowledgement to server after receiving request header. Send attempts reached/exceeded MAX_SEND_ATTEMPTS. Maybe there is something wrong with the connection?\n");
			continue;
		}
		send_attempts = 0;
		printf("Acknowledgement sent.\n");

		// Begin receiving payload metadata and payloads.
		payloads_received = 0;
		payloads_expected = inbound_request_header.parameter_count;
		
		printf("Receiving payloads...\n");
		while(payloads_received < payloads_expected)
		{
			if(inbound_payloads[inbound_payloads_length] == NULL)
			{
				inbound_payloads[inbound_payloads_length] = malloc(sizeof(struct payload));
				if(inbound_payloads[inbound_payloads_length] == NULL)
				{
					fprintf(stderr, "Failed to allocate memory to hold first payload in payload buffer.\n");
					break;
				}
			}
			current_inbound_payload = inbound_payloads[inbound_payloads_length];

			// Receive payload metadata
			printf("Receiving payload metadata for payload #%ld...\n", payloads_received + 1);
			receive_status = receive_payload_metadata(tcp_socket, current_inbound_payload, shared_secret);
			receive_attempts = 1;
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload_metadata(tcp_socket, current_inbound_payload, shared_secret);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "Failed to receive payload metadata for first payload from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe something is wrong with the connection?\n");
				break;
			}
			receive_attempts = 0;
			printf("Metadata for payload #%ld received. According to this payload, %zu bytes should be received.\n", payloads_received + 1, current_inbound_payload->member_size * current_inbound_payload->member_count);

			// Ensure the current inbound payload can actually hold the data that is about to be received.
			printf("Checking if current inbound payload can store payload #%ld...\n", payloads_received + 1);
			if(current_inbound_payload->data != NULL)
				free(current_inbound_payload->data);

			current_inbound_payload->data = malloc(current_inbound_payload->member_size * current_inbound_payload->member_count);
			if(current_inbound_payload->data == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for the data buffer of the first payload to be received from the server.\n");
				break;
			}
			printf("Memory check complete.\n");
			
			// Send acknowledgement for the payload metadata
			printf("Sending acknowledgement for the receipt of the metadata for payload #%ld...\n", payloads_received + 1);
			send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
			send_attempts = 1;
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{
				send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "Failed to send acknowledgement for receipt of payload metadata to the server. Send attempts exceeded MAX_SEND_ATTEMPTS. Maybe there is an issue with the connection?\n");
				break;
			}
			send_attempts = 0;
			printf("Acknowledgement sent.\n");

			// Receive actual payload
			printf("Receiving actual payload data for payload #%ld...\n", payloads_received + 1);
			receive_status = receive_payload(tcp_socket, current_inbound_payload, shared_secret);
			receive_attempts = 1;
			while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
			{
				receive_status = receive_payload(tcp_socket, current_inbound_payload, shared_secret);
				receive_attempts++;
			}
			if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
			{
				fprintf(stderr, "Failed to receive payload $%zu from the server. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Maybe there is something wrong with the connection?\n", payloads_received + 1);
				break;
			}
			receive_attempts = 0;
			printf("Actual data for payload #%ld received.\n", payloads_received + 1);

			// Acknowledge receipt of payload
			printf("Attempting to send OK acknowledgement for receipt of payload...\n");
			send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
			send_attempts = 1;
			while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
			{	
				send_status = send_acknowledgement(tcp_socket, OK, shared_secret);
				send_attempts++;
			}
			if(send_attempts >= MAX_SEND_ATTEMPTS)
			{
				fprintf(stderr, "Failed to send OK acknowledgement to server after receiving payload #%zu. Send attempts reached/exceeded MAX_SEND_ATTEMPTS. Maybe there is something wrong with the connection?\n", payloads_received + 1);
				break;
			}
			send_attempts = 0;
			printf("Acknowledgement sent.\n");

			payloads_received++;
		}
		
		// Review data received.
		if(inbound_request_header.action == GET)
		{
			switch(inbound_request_header.subject)
			{
				default:
					fprintf(stderr, "Received a GET request header from server with unknown/unimplemented subject (code %d). No action will be taken.\n", inbound_request_header.subject);
					break;
			}
		}
		else // server is SENDING us stuff
		{
			switch(inbound_request_header.subject)
			{
				case DEVELOPER_TEST_MESSAGE:
					// Receiving developer test message as a response for an attempt at signing in
					if(client_user_state.last_thing_sent == LOGIN_ATTEMPT) {
						// User entered wrong credentials
						if(strcmp(inbound_payloads[0]->data, "false") == 0) {
							printf("[System] Sign-in credentials are incorrect.\n");
							break;
						}

						// User entered valid credentials
						if(client_user_state.username == default_username) {
							client_user_state.username = malloc(sizeof(char) * (strlen(username) + 1));
							if(client_user_state.username == NULL) {
								fprintf(stderr, "[Fatal Error] Cannot allocate memory for username buffer in client state. Maybe the system has run out of memory?\n");
								close(tcp_socket);
								exit(EXIT_FAILURE);
							}
							strcpy(client_user_state.username, username);
						}
					}
					// CASE (2): Receiving developer test message for other reason
					printf("Received: ");
					for(int i = 0; i < payloads_received; i++)
						printf("\"%s\" ", (char *) inbound_payloads[i]->data);
					break;
			
				case LOGIN_ATTEMPT_RESPONSE:
					// check response
					if(strcmp(inbound_payloads[0]->data, "false") == 0)
					{
						fprintf(stderr, "[sign in error] No user found with provided credentials.\n");
						username = default_username;
					}
					else
						client_user_state.signed_in = true;	
					// if valid sign-in, change username
					break;

				default:
					fprintf(stderr, "Received a SEND request header from server with unknown/unimplemented subject (code %d). No action will be taken.\n", inbound_request_header.subject);
					break;
			}
		}
	}

	close(tcp_socket);
	return 0;
}
