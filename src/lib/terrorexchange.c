#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "terrorexchange.h"

struct request_header* request_header_create(enum ACTION action, enum SUBJECT subject, size_t parameter_count, size_t metadata_total_size, size_t parameters_total_size, size_t total_bytes)
{
	struct request_header *new_request_header = malloc(sizeof(struct request_header));
	if(new_request_header == NULL)
	{
		fprintf(stderr, "[request_header_create]: Failed to allocate memory for a new request header struct.\n");
		return NULL;
	}
	new_request_header->action = action;
	new_request_header->subject = subject;
	new_request_header->parameter_count = parameter_count;
	new_request_header->metadata_total_size = metadata_total_size;
	new_request_header->parameters_total_size = parameters_total_size;
	new_request_header->total_bytes = total_bytes;

	return new_request_header;
} 

struct payload* payload_create(size_t member_size, size_t member_count)
{
	struct payload *new_payload = malloc(sizeof(struct payload));
	if(new_payload == NULL)
	{
		fprintf(stderr, "[payload_create]: Failed to allocate memory for new payload struct.\n");
		return NULL;
	}

	new_payload->member_size = member_size;
	new_payload->member_count = member_count;

	return new_payload;
}

bool send_request_header(int socket, struct request_header *header, uint32_t shared_secret)
{
	if(header == NULL)
	{
		fprintf(stderr, "[send_request_header]: Cannot send request header that points to NULL.\n");
		return false;
	}

	// Set the members to networ byte order so the recipient can receive OK 
	// regardless of their system's endianness
	header->action = htonl(header->action);
	header->subject = htonl(header->subject);
	header->parameter_count = htonl(header->parameter_count);
	header->metadata_total_size = htonl(header->metadata_total_size);
	header->parameters_total_size = htonl(header->parameters_total_size);
	header->total_bytes = htonl(header->total_bytes);

	ssize_t bytes_sent;
	// bytes_sent = send(socket, header, sizeof(struct request_header), 0);
	bytes_sent = secure_send(socket, header, sizeof(struct request_header), 0, shared_secret);

	// All data sent OK
	if(bytes_sent == sizeof(struct request_header))
		return true;

	// Return false if bad connection
	if(bytes_sent < 0)
	{
		fprintf(stderr, "[send_request_header]: Failed to send data. Send function returned -1.\n");
		return false;
	}

	// Continue sending rest of bytes
	ssize_t total_bytes_sent = bytes_sent;
	while(total_bytes_sent < sizeof(struct request_header))
	{
		bytes_sent = secure_send(socket, header + total_bytes_sent, sizeof(struct request_header) - total_bytes_sent, 0, shared_secret);
		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_request_header]: Unable to send remaining bytes. Send function returned -1.\n");
			return false;
		}
		total_bytes_sent += bytes_sent;
	}
	return true;
}

bool receive_request_header(int socket, struct request_header *header, uint32_t shared_secret)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_request_header]: Cannot load received request header into a request header struct that points to NULL. Argument provided is bad.\n");
		return false;
	}

	ssize_t bytes_received;
	bytes_received = secure_recv(socket, header, sizeof(struct request_header), 0, shared_secret);
	if(bytes_received < 0)
	{
		fprintf(stderr, "[receive_request_header]: Failed to receive data. Recv function returned -1.\n");
		return false;
	}

	// Receive remaining bytes if all are not sent
	if(bytes_received < sizeof(struct request_header))
	{
		ssize_t total_bytes_received = bytes_received;
		while(total_bytes_received < sizeof(struct request_header))
		{
			bytes_received = secure_recv(socket, header + total_bytes_received, sizeof(struct request_header) - total_bytes_received, 0, shared_secret);
			if(bytes_received < 0)
			{
				fprintf(stderr, "[receive_request_header]: Failed to receive data. Recv function returned -1 while trying to receive remaining bytes.\n");
				return false;
			}

			total_bytes_received += bytes_received;
		}
	}

	// Set values to host order for endianness
	header->action = ntohl(header->action);
	header->subject = ntohl(header->subject);
	header->parameter_count = ntohl(header->parameter_count); 
	header->metadata_total_size = ntohl(header->metadata_total_size);
	header->parameters_total_size = ntohl(header->parameters_total_size);
	header->total_bytes = ntohl(header->total_bytes);

	return true;
}

// parameter_count member of outbound request header is used to signal the type of acknowledgement.
bool send_acknowledgement(int socket, enum ACKNOWLEDGEMENT_TYPE type, uint32_t shared_secret)
{
	// (1) Create acknowledgement request header
	// (2) DO NOT convert to network byte order, because send_request_header 
	//     function will do it.
	struct request_header acknowledgement; 
	acknowledgement.action = SEND;
	acknowledgement.subject = ACKNOWLEDGEMENT;
	acknowledgement.parameter_count = type;
	acknowledgement.metadata_total_size = 0;
	acknowledgement.parameters_total_size = 0;
	acknowledgement.total_bytes = 0;

	// Send the acknowledgement
	bool status;
	status = send_request_header(socket, &acknowledgement, shared_secret);
	if(status == false)
		fprintf(stderr, "[send_acknowledgement]: Could not send acknowledgement. send_request_header() returned false.\n");

	return status;
}

// This is not guaranteed to receive an OK acknowledgement. 
// You should check if the subject is ACKNOWLEDGEMENT afterwards; it might be NOT_FOUND
// instead.
bool receive_acknowledgement(int socket, struct request_header *header, uint32_t shared_secret)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_acknowledgement]: Cannot read to-be-received request header into a request header struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive acknowledgement
	bool status;
	status = receive_request_header(socket, header, shared_secret);
	if(status == false)
		fprintf(stderr, "[receive_acknowledgement]: Failed to receive acknowledgement. receive_request_header returned false.\n");

	return status;
}

bool send_payload_metadata(int socket, struct payload *outbound_payload, uint32_t shared_secret)
{
	if(outbound_payload == NULL)
	{
		fprintf(stderr, "[send_payload_metadata]: Cannot send the metadata of a payload struct that points to NULL. Bad argument.\n");
		return false;
	}

	// (1) Create PAYLOAD METADATA request header
	// (2) DO NOT convert to network byte order, because send_request_header 
	//     function will do it.
	struct request_header payload_metadata; 
	payload_metadata.action = SEND;
	payload_metadata.subject = PAYLOAD_METADATA;
	payload_metadata.parameter_count = outbound_payload->member_count;
	payload_metadata.metadata_total_size = 2 * sizeof(size_t);
	payload_metadata.parameters_total_size = outbound_payload->member_count * outbound_payload->member_size;
	payload_metadata.total_bytes = payload_metadata.parameters_total_size;

	// Send the payload metadata 
	bool status;
	status = send_request_header(socket, &payload_metadata, shared_secret);
	if(status == false)
		fprintf(stderr, "[send_payload_metadata]: Could not send payload metadata. send_request_header() returned false.\n");

	return status;
}

// receives a SEND PAYLOAD METADATA request header and uses that data to initialize a
// payload (the inbound_payload parameter)
bool receive_payload_metadata(int socket, struct payload *inbound_payload, uint32_t shared_secret)
{
	if(inbound_payload == NULL)
	{
		fprintf(stderr, "[receive_payload_metadata]: Cannot read to-be-received payload into a payload struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive payload metadata 
	struct request_header header;
	bool status;
	status = receive_request_header(socket, &header, shared_secret);
	if(status == false)
		fprintf(stderr, "[receive_payload_metadata]: Failed to receive payload metadata request header. receive_request_header returned false.\n");

	// Set the inbound payload with the data of the request header
	// NOTE: data is already in host format, as per the receive_request_header function.
	inbound_payload->member_size = header.parameters_total_size / header.parameter_count;
	inbound_payload->member_count = header.parameter_count;

	return status;
}

bool send_payload(int socket, struct payload *outbound_payload, uint32_t shared_secret)
{
	if(outbound_payload == NULL)
	{
		fprintf(stderr, "[send_payload]: Cannot send a payload struct that points to NULL. Bad argument provided.\n");
		return false;
	}

	void *payload_data = outbound_payload->data;
	ssize_t bytes_sent = 0;
	size_t total_bytes_sent = 0;
	size_t total_bytes_to_send = outbound_payload->member_size * outbound_payload->member_count;
	int send_attempts = 0;
	// try to send data all at once - payload is smaller than one chunk
	if(total_bytes_to_send <= CHUNK_SIZE)
	{
		printf("[send_payload] Attempting to send payload data as a singular chunk (%zu total bytes).\n", total_bytes_to_send);
		bytes_sent = secure_send(socket, payload_data, total_bytes_to_send, 0, shared_secret);
		if(bytes_sent == total_bytes_to_send)
		{
			printf("[send_payload] All the bytes of the payload were sent with one call to send().\n");
			return true;
		}

		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_payload]: Failed to send payload with %zu bytes - send() returned -1.\n", total_bytes_to_send);
			return false;
		}

		// Continue sending the rest of the bytes
		total_bytes_sent = bytes_sent;
		printf("[send_payload] Attempting to send remaining %zu bytes of payload data.\n", total_bytes_to_send - total_bytes_sent);
		while(total_bytes_sent < total_bytes_to_send)
		{
			bytes_sent = secure_send(socket, payload_data + total_bytes_sent, total_bytes_to_send - total_bytes_sent, 0, shared_secret);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[send_payload]: Failed to send remaining %zu bytes of payload. Send() returned -1.\n", total_bytes_to_send - total_bytes_to_send);
				return false;
			}

			total_bytes_sent += bytes_sent;
		}
		printf("[send_payload] All bytes were sent in one chunk!\n");
		return true; // all bytes sent
	}

	// Send the data in chunks.
	char chunk_buffer[CHUNK_SIZE];
	size_t chunk_buffer_used = 0;
	size_t bytes_remaining = total_bytes_to_send;
	size_t total_chunk_bytes_sent;
	bytes_sent = 0;
	total_bytes_sent = 0;
	printf("[send_payload] Attempting to send payload data in several chunks.\n");
	while(bytes_remaining > 0)
	{
		// set chunk
		if(bytes_remaining > CHUNK_SIZE)
		{
			memcpy(chunk_buffer, payload_data + total_bytes_sent, CHUNK_SIZE);
			chunk_buffer_used = CHUNK_SIZE;
		}
		else
		{
			memcpy(chunk_buffer, payload_data + total_bytes_sent, bytes_remaining);
			chunk_buffer_used = bytes_remaining;
		}
	
		// send the chunk
		bytes_sent = secure_send(socket, chunk_buffer, chunk_buffer_used, 0, shared_secret);
		if(bytes_sent < 0)
		{
			fprintf(stderr, "[payload_send]: Failed to send chunk of size %zu to recipient. %zu bytes of %zu bytes were sent in all (across all chunks). Send() function returned -1.\n", chunk_buffer_used, total_bytes_sent, total_bytes_to_send);
			return false;
		}

		// keep sending the rest of the bytes in the chunk
		// if not all were sent
		total_chunk_bytes_sent = bytes_sent;
		while(total_chunk_bytes_sent < chunk_buffer_used)
		{
			bytes_sent = secure_send(socket, chunk_buffer + total_chunk_bytes_sent, chunk_buffer_used - total_chunk_bytes_sent, 0, shared_secret);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[send_payload]: Failed to send %zu bytes of chunk buffer to recipient. %zu bytes of %zu were sent in total across all chunks. %zu bytes of the current chunk were sent. Send() function returned -1.\n", chunk_buffer_used - total_chunk_bytes_sent, total_bytes_sent, total_bytes_to_send, bytes_sent);
				return false;
			}

			total_chunk_bytes_sent += bytes_sent;
		}

		// update remaining bytes to be sent across chunks
		// and total bytes sent (offset for payload_data when 
		// using memcpy to set chunks).
		total_bytes_sent += total_chunk_bytes_sent;
		bytes_remaining -= total_chunk_bytes_sent;
	}
	return true;
}

// DATA BUFFER IN INBOUND_PAYLOAD->DATA SHOULD ALREADY BE ALLOCATED FROM THE INFORMATION
// RECEIVED BY CALLING RECEIVE_PAYLOAD_METADATA
bool receive_payload(int socket, struct payload *inbound_payload, uint32_t shared_secret)
{
	if(inbound_payload == NULL) {
		fprintf(stderr, "[receive_payload]: Cannot load incoming payload data into a payload struct that points to NULL.\n");
		return false;
	}
	if(inbound_payload->data == NULL){
		fprintf(stderr, "[receive_payload]: Cannot load incoming payload data into a payload struct with a data buffer that points to NULL.\n");
		return false;
	}
	
	size_t total_bytes_to_receive = inbound_payload->member_size * inbound_payload->member_count;
	if(total_bytes_to_receive == 0)
	{
		fprintf(stderr, "[receive_payload]: Total bytes to receive was calculated as 0 bytes. The inbound payload struct may have incorrect metadata information. This could have happened if the metadata was not received or loaded into the payload struct correctly with previous calls to receive_payload_metadata().\n");
		return false;
	}
	size_t total_bytes_received = 0;
	ssize_t bytes_received = 0;

	// Try to receive all the data at once if chunking is not required.
	if(total_bytes_to_receive <= CHUNK_SIZE)
	{
		printf("[receive_payload] Attempting to receive payload (%zu bytes) all in one chunk from connection with socket #%d.\n", total_bytes_to_receive, socket);
		// First try
		bytes_received = secure_recv(socket, inbound_payload->data, total_bytes_to_receive, 0, shared_secret);
		printf("[receive_payload] Received %ld bytes from connection with socket #%d (expected %zu byte).\n", bytes_received, socket, total_bytes_to_receive); 
		if(bytes_received == total_bytes_to_receive)
		{
			printf("[receive_payload] Received all bytes from client socket #%d in one call to send().\n", socket);
			return true;
		}

		if(bytes_received < 0)
		{
			fprintf(stderr, "[receive_payload]: Failed to receive payload with %zu bytes. Recv() returned -1.\n", total_bytes_to_receive);
			return false;
		}

		// Continue receiving the data that remains.
		total_bytes_received = bytes_received;
		while(total_bytes_received < total_bytes_to_receive)
		{
			printf("[receive_payload] Starting pointer is %p. Expecting to receive %zu bytes.\n", inbound_payload->data + total_bytes_received, total_bytes_to_receive - total_bytes_received);
			bytes_received = secure_recv(socket, inbound_payload->data + total_bytes_received, total_bytes_to_receive - total_bytes_received, 0, shared_secret);
			if(bytes_received < 0)
			{
				fprintf(stderr, "[receive_payload]: Failed to receive remaining %zu bytes of payload. %zu bytes were received in total up until this failure. Send() returned -1.\n", total_bytes_to_receive - total_bytes_received, total_bytes_received);
				return false;
			}
			total_bytes_received += bytes_received;
		}
		return true; // all bytes received in one chunk
	}

	// Send the data in chunks if size is greater than single chunk size.
	char chunk_buffer[CHUNK_SIZE];
	ssize_t chunk_buffer_amt_to_use = 0;
	size_t bytes_remaining = total_bytes_to_receive;
	size_t total_chunk_bytes_received = 0;
	bytes_received = 0;
	total_bytes_received = 0;
	while(bytes_remaining > 0)
	{
		// Set anticipated amount of buffer
		if(bytes_remaining > CHUNK_SIZE)
			chunk_buffer_amt_to_use = CHUNK_SIZE;
		else
			chunk_buffer_amt_to_use = bytes_remaining;

		// Receive data into the chunk buffer
		bytes_received = secure_recv(socket, chunk_buffer, chunk_buffer_amt_to_use, 0, shared_secret);
		if(bytes_received < 0)
		{
			fprintf(stderr, "[receive_payload]: Failed to receive chunk of size %zu from sender. %zu bytes of %zu bytes were received in all (across all chunks). Recv() function returned -1.\n", chunk_buffer_amt_to_use, total_bytes_received, total_bytes_to_receive);
			return false;
		}

		// keep receiving the rest of the bytes in the inbound chunk
		total_chunk_bytes_received = bytes_received;
		while(total_chunk_bytes_received < chunk_buffer_amt_to_use)
		{
			bytes_received = secure_recv(socket, chunk_buffer + total_chunk_bytes_received, chunk_buffer_amt_to_use - total_chunk_bytes_received, 0, shared_secret);
			if(bytes_received < 0)
			{
				fprintf(stderr, "[receive_payload]: Failed to receive %zu bytes of chunk buffer. %zu bytes of %zu were received in total across all bytes. %zu bytes of the current chunk were received. Recv() function returned -1.\n", chunk_buffer_amt_to_use - total_chunk_bytes_received, total_bytes_received, total_bytes_to_receive, total_chunk_bytes_received);
				return false;
			}
			total_chunk_bytes_received += bytes_received;
		}
		// Set the inbound payload's data buffer with the memory of the chunk.
		memcpy(inbound_payload->data + total_bytes_received, chunk_buffer, chunk_buffer_amt_to_use);

		// update remaining bytes to be sent across chunks
		// and total bytes sent (offset for payload_data when using memcpy)
		total_bytes_received += total_chunk_bytes_received;
		bytes_remaining -= total_chunk_bytes_received;
	}
	return true;
}

void print_too_many_send_attempts_error(int socket, char *function_name, char *outbound_thing, int item_number)
{
	printf("[%s] Failed to send %s #%d to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", function_name, outbound_thing, item_number, socket, MAX_SEND_ATTEMPTS);
}

void print_too_many_receive_attempts_error(int socket, char *function_name, char *outbound_thing, int item_number, char *additional_comment)
{
	printf("[%s] Failed to receive %s #%d to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe there is something wrong with the connection?", function_name, outbound_thing, item_number, socket, MAX_RECEIVE_ATTEMPTS);
	if(additional_comment != NULL)
		printf("%s", additional_comment);

	printf("\n");
}

void print_acknowledgement_type_mismatch_error(int socket, char *function_name, char *message_type, enum ACKNOWLEDGEMENT_TYPE wrong_type, enum ACKNOWLEDGEMENT_TYPE right_type)
{
	fprintf(stderr, "[%s] Received acknowledgement from connection with socket %d for %s; however, the acknowledgement was of type %d (wanted %d). Maybe the data was sent erroneously?\n", function_name, socket, message_type, wrong_type, right_type);
}

// This sets the request header properly for you. There is no need to configure it in advance.
bool send_developer_test_message(int connection_socket, struct request_header *outbound_request_header, char *message, uint32_t shared_secret)
{
	if(outbound_request_header == NULL)
	{
		fprintf(stderr, "[send_developer_test_message] Cannot send a request header struct that points to NULL.\n");
		return false;
	}

	if(message == NULL)
	{
		fprintf(stderr, "[send_developer_test_message] Cannot send a message with a char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	
	bool send_status;
	int send_attempts = 0;
	bool receive_status;
	int receive_attempts = 0;
	struct request_header inbound_request_header;
	int message_length = strlen(message) + 1;

	// Set outbound request header with proper values
	outbound_request_header->action = SEND;
	outbound_request_header->subject = DEVELOPER_TEST_MESSAGE;
	outbound_request_header->parameter_count = 1;
	outbound_request_header->metadata_total_size = 2 * sizeof(size_t);
	outbound_request_header->parameters_total_size = message_length;
	outbound_request_header->total_bytes = outbound_request_header->metadata_total_size + outbound_request_header->parameters_total_size;

	// Send SEND DEVELOPER_TEST_MESSAGE message
	printf("[send_developer_test_message] Trying to send SEND DEVELOPER_TEST_MESSAGE request header to connection with connection socket %d.\n", connection_socket);
	send_status = send_request_header(connection_socket, outbound_request_header, shared_secret);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = send_request_header(connection_socket, outbound_request_header, shared_secret);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to send SEND DEVELOPER_TEST_MESSAGE request header to the client. Something might be wrong with the connection.\n");
		return false;
	}
	send_attempts = 0;
	printf("[send_developer_test_message] Sent request header to connection with connection socket %d.\n", connection_socket);

	// Wait for OK acknowledgement
	printf("[send_developer_test_message] Waiting to receive acknowledgement from connection with connection socket %d.\n", connection_socket);
	receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{	
		receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
		receive_attempts++;
	}
	if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to receive SEND ACKNOWLEDGMENT request header from the sender. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Something might be wrong with the connection.\n");
		return false;
	}
	receive_attempts = 0;
	printf("[send_developer_test_message] Received acknowledgement from connection with connection socket %d.\n", connection_socket);

	// Send payload metadata
	struct payload outbound_payload;
	outbound_payload.member_size = sizeof(char);
	outbound_payload.member_count = message_length;
	printf("[send_developer_test_message] Sending payload metadata. Member size is %zu and member count is %zu.\n", outbound_payload.member_size, outbound_payload.member_count);
	send_status = send_payload_metadata(connection_socket, &outbound_payload, shared_secret);
	send_attempts = 1;
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = send_payload_metadata(connection_socket, &outbound_payload, shared_secret);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to send payload metadata to the recipient. Send attempts reached/exceed MAX_SEND_ATTEMPTS. There might be something wrong with the connection.\n");
		return false;
	}
	send_attempts = 0;

	// Receive acknowledgement for payload metadata
	receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
	receive_attempts = 1;
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{	
		receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
		receive_attempts++;
	}
	if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to receive acknowledgement from recipient after delivering payload metadata. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS. Something might be wrong with the connection.\n");
		return false;
	}
	receive_attempts = 0;

	// Send payload itself
	outbound_payload.data = malloc(message_length);
	if(outbound_payload.data == NULL)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to allocate memory for the outbound payload's data member. Malloc returned NULL.\n");
		return false;
	}
	memcpy(outbound_payload.data, message, message_length);
	send_status = send_payload(connection_socket, &outbound_payload, shared_secret);
	send_attempts = 1;
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = send_payload(connection_socket, &outbound_payload, shared_secret);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to send test message's payload of size %d bytes to the recipient. Send attempts reached/exceeded MAX_SEND_ATTEMPTS. Something might be wrong with the connection.\n", message_length);
		free(outbound_payload.data);
		return false;
	}
	send_attempts = 0;
	free(outbound_payload.data);
	
	// Receive acknowledgement for payload receipt
	receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
	receive_attempts = 1;
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{
		receive_status = receive_acknowledgement(connection_socket, &inbound_request_header, shared_secret);
		receive_attempts++;
	}
	if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to receive acknowledgement after sending test message's paylod from recipient. Receive attempts exceeded MAX_RECEIVE_ATTEMPTS. Something might be wrong with the connection.\n");
		return false;
	}

	return true;
}

// This sets the request header properly for you. There is no need to configure it in advance.
bool send_login_attempt(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *password, int password_length, uint32_t shared_secret)
{
	if(outbound_request_header == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Cannot send a login attempt using a request header struct that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(username == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Cannot send a login attempt using a username char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(password == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Cannot send a login attempt using a password char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	
	bool send_status; 
	int send_attempts = 0;
	bool receive_status;
	int receive_attempts = 0;
	struct request_header inbound_request_header;
	
	// Set outbound request header with proper values
	outbound_request_header->action = SEND;
	outbound_request_header->subject = LOGIN_ATTEMPT;
	outbound_request_header->parameter_count = 2;
	outbound_request_header->metadata_total_size = outbound_request_header->parameter_count * 2 * sizeof(size_t);
	outbound_request_header->parameters_total_size = username_length + password_length + 2; // +2 for 2 null terminators
	outbound_request_header->total_bytes = outbound_request_header->parameters_total_size + outbound_request_header->metadata_total_size;

	// Send SEND LOGIN_ATTEMPT message
	printf("[send_login_attempt] Trying to send SEND LOGIN_ATTEMPT request header to connection with socket %d.\n", socket);
	send_status = send_request_header(socket, outbound_request_header, shared_secret);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = send_request_header(socket, outbound_request_header, shared_secret);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_login_attempt] Failed to send SEND LOGIN_ATTEMPT request header to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", socket, MAX_SEND_ATTEMPTS);
		return false;
	} 
	send_attempts = 0;

	// Receive acknowledgement
	printf("[send_login_attempt] Waiting to receive acknowledgement from connection with socket #%d.\n", socket);
	receive_status = receive_request_header(socket, &inbound_request_header, shared_secret);
	while(receive_status == false)
	{
		receive_status == receive_request_header(socket, &inbound_request_header, shared_secret);
		receive_attempts++;
	}
	if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
	{
		fprintf(stderr, "[send_login_attempt] Failed to receive acknowledgement for SEND LOGIN_ATTEMPT from connection with socket #%d. Receive attempts eached/exceeced MAX_RECEIVE_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", socket, MAX_RECEIVE_ATTEMPTS);
		return false;
	}

	// Check valid acknowledgement
	if(inbound_request_header.parameter_count != OK)
	{
		fprintf(stderr, "[send_login_attempt] Received acknowledgement from client with socket #%d for SEND LOGIN_ATTEMPT; however, the acknowledgement type was %ld (wanted %d). Maybe the data sent was incorrect?\n", socket, inbound_request_header.parameter_count, OK);
		return false;
	}
	
	// Prepare payloads to be sent
	int payloads_sent = 0;
	int payloads_to_send = 2;
	struct payload outbound_payloads[2];
	outbound_payloads[0].member_size = 1;
	outbound_payloads[0].member_count = username_length;
	outbound_payloads[0].data = malloc(username_length);
	if(outbound_payloads[0].data == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Failed to allocate memory buffer for outbound payload 1 (of 2). It needed to store %d bytes to hold the username. Is the system low on memory?\n", username_length);
		return false;
	}
	memcpy(outbound_payloads[0].data, username, username_length);

	outbound_payloads[1].member_size = 1;
	outbound_payloads[1].member_count = password_length;
	outbound_payloads[1].data = malloc(password_length);
	if(outbound_payloads[1].data == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Failed to allocate memory for outbound payload 2 (of 2). It needed to store %d bytes to hold the password. Is the system low on memory?\n", password_length);
		free(outbound_payloads[0].data);
		return false;
	}
	memcpy(outbound_payloads[1].data, password, password_length);

	// Send payload metadata then actual payload
	while(payloads_sent < payloads_to_send)
	{
		// Send payload N metadata
		send_status = send_payload_metadata(socket, &outbound_payloads[payloads_sent], shared_secret);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_payload_metadata(socket, &outbound_payloads[payloads_sent], shared_secret);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "[send_login_attempt] Failed to send metadata for payload #%d to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe something is wrong with the connection?\n", payloads_sent + 1, socket, MAX_SEND_ATTEMPTS);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		send_attempts = 0;
			
		// Receive acknowledgement
		receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "[send_login_attempt] Failed to receive acknowledgement for receipt of payload #%d's metadata from connection with socket #%d. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", payloads_sent + 1, socket, MAX_RECEIVE_ATTEMPTS);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		receive_attempts = 0;
		
		// Check valid acknowledgement
		if(inbound_request_header.parameter_count != OK)
		{
			fprintf(stderr, "[send_login_attempt] Received acknowledgement from connection with socket #%d for SEND LOGIN_ATTEMPT; however, the acknowledgement type was %ld (wanted %d). Maybe the data sent was incorrect?\n", socket, inbound_request_header.parameter_count, OK);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		
		// Send payload N
		send_status = send_payload(socket, &outbound_payloads[payloads_sent], shared_secret);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_payload(socket, &outbound_payloads[payloads_sent], shared_secret);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "[send_login_attempt] Failed to send data for payload #%d to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe there is something wrong with the connection?", payloads_sent + 1, socket, MAX_SEND_ATTEMPTS);
			// cleanup payloads
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		send_attempts = 0;

		// Receive acknowledgement
		receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "[send_login_attempt] Failed to receive acknowledgement for receipt of the data for payload #%d for connection with socket #%d for SEND LOGIN_ATTMEMPT. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS (%d). Maybe something is wrong with the connection?", payloads_sent + 1, socket, MAX_RECEIVE_ATTEMPTS);		
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		receive_attempts++;

		// Check valid acknowledgement
		if(inbound_request_header.parameter_count != OK)
		{
			fprintf(stderr, "[send_login_attempt] Received acknowledgement from connection with socket #%d for SEND LOGIN_ATTEMPT; however, the acknowledgement type was %ld (wanted %d). Maybe the data sent was incorrect?\n", socket, inbound_request_header.parameter_count, OK);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			return false;
		}
		
		// Update payload data
		payloads_sent++;
	}
	return true;
}

// This sets the request header properly for you. There is no need to configure it in advance.
bool send_account_create(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *email, int email_length, char *password, int password_length, uint32_t shared_secret)
{
	if(outbound_request_header == NULL)
	{
		fprintf(stderr, "[send_account_create] Cannot send an account_create request header with an outbound request header struct that points to NULL. Bad argument provided.\n");
		return false;
	} 
	if(username == NULL)
	{
		fprintf(stderr, "[send_account_create] Cannot send an account_create request header with a username char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(email == NULL)
	{
		fprintf(stderr, "[send_account_create] Cannot send an account_create request header with an email char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(password == NULL)
	{
		fprintf(stderr, "[send_account_create] Cannot send an account_create request header with a password char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}

	bool send_status;
	bool receive_status;
	int send_attempts = 0;
	int receive_attempts = 0;
	struct request_header inbound_request_header;
	
	// Set outbound request header with proper values
	outbound_request_header->action = SEND;
	outbound_request_header->subject = ACCOUNT_CREATE;
	outbound_request_header->parameter_count = 3;
	outbound_request_header->metadata_total_size = outbound_request_header->parameter_count * 2 * sizeof(size_t);
	outbound_request_header->parameters_total_size = username_length + password_length + email_length;
	outbound_request_header->total_bytes = outbound_request_header->parameters_total_size + outbound_request_header->metadata_total_size;

	// Send SEND ACCOUNT_CREATE message
	printf("[send_account_create] Trying to send SEND ACCOUNT_CREATE request header to connection with socket #%d.\n", socket);
	send_status = send_request_header(socket, outbound_request_header, shared_secret);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = send_request_header(socket, outbound_request_header, shared_secret);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_account_create] Failed to send SEND ACCOUNT_CREATE request header to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe something is wrong with the connection?\n", socket, MAX_SEND_ATTEMPTS);
		return false;
	}
	send_attempts = 0;

	// Receive acknowledgement
	printf("[send_account_create] Waiting to receive acknowledgement from connection with socket #%d.\n", socket);
	receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{
		receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
		receive_attempts++;
	}
	if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
	{
		fprintf(stderr, "[send_account_create] Failed to receive acknowledgement from connection with socket #%d after sending SEND ACCOUNT_CREATE request header. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", socket, MAX_RECEIVE_ATTEMPTS);
		return false;
	}
	
	// Check valid acknowledgement
	if(inbound_request_header.parameter_count != OK)
	{
		fprintf(stderr, "[send_account_create] Received acknowledgement from connection with socket #%d for SEND ACCOUNT_CREATE; however an acknowledgement type other than OK was received. Maybe the data was sent erroneously?\n", socket);
		return false;
	}

	// Prepare payloads to be send
	int payloads_sent = 0;
	int payloads_to_send = 3; 
	struct payload outbound_payloads[3];
	outbound_payloads[0].member_size = 1;
	outbound_payloads[0].member_count = username_length;
	outbound_payloads[0].data = malloc(username_length);
	if(outbound_payloads[0].data == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Failed to allocate memory buffer for outbound payload 1 (of 3). Needed to allocate %d bytes. Is the system low on memory?\n", username_length);
		return false;
	}
	memcpy(outbound_payloads[0].data, username, username_length);

	outbound_payloads[1].member_size = 1;
	outbound_payloads[1].member_count = email_length;
	outbound_payloads[1].data = malloc(email_length);
	if(outbound_payloads[1].data == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Failed to allocate memory buffer for outbound payload 2 (of 3). Needed to allocate %d bytes. Is the system low on memory?\n", email_length);
		return false;
	}
	memcpy(outbound_payloads[1].data, email, email_length);

	outbound_payloads[2].member_size = 1;
	outbound_payloads[2].member_count = password_length;
	outbound_payloads[2].data = malloc(password_length);
	if(outbound_payloads[2].data == NULL)
	{
		fprintf(stderr, "[send_login_attempt] Failed to allocate memory buffer for outbound payload 3 (of 3). Needed to allocate %d bytes. Is the system low on memory?\n", password_length);
		return false;
	}
	memcpy(outbound_payloads[2].data, password, username_length);
	
	// Send payload metadata and then actual payload
	while(payloads_sent < payloads_to_send)
	{
		// Send metadata of payload N
		send_status = send_payload_metadata(socket, &outbound_payloads[payloads_sent], shared_secret);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_payload_metadata(socket, &outbound_payloads[payloads_sent], shared_secret);
			send_attempts++;
		}
		if(send_attempts >= MAX_SEND_ATTEMPTS)
		{
			fprintf(stderr, "[send_account_create] Failed to send metadata for payload #%d to connection with socket #%d. Send attempts reached/exceeded MAX_SEND_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", payloads_sent + 1, socket, MAX_SEND_ATTEMPTS);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		}
		send_attempts = 0;

		// Receive acknowledgement
		receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			fprintf(stderr, "[send_account_create] Failed to receive acknowledgement for receipt of metadata of payload #%d from connection with socket #%d. Receive attempts reached/exceeded MAX_RECEIVE_ATTEMPTS (%d). Maybe there is something wrong with the connection?\n", payloads_sent + 1, socket, MAX_RECEIVE_ATTEMPTS);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		}
		receive_attempts = 0;

		// Check valid acknowledgement
		if(inbound_request_header.parameter_count != OK)
		{
			fprintf(stderr, "[send_account_create] Received acknowledgement from connection with socket %d for SEND ACCOUNT_CREATE; however, the acknowledgement was of type %ld (wanted %d). This happened after the transmission of the metadata for payload #%d. Maybe the data was sent erroneously?\n", socket, inbound_request_header.parameter_count, OK, payloads_sent);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		}
		
		// Send payload N
		send_status = send_payload(socket, &outbound_payloads[payloads_sent], shared_secret);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = send_payload(socket, &outbound_payloads[payloads_sent], shared_secret);
			send_attempts++;
		}
		if(send_status >= MAX_SEND_ATTEMPTS)
		{
			print_too_many_send_attempts_error(socket, "send_account_create", "data member of payload", payloads_sent + 1);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		}
		send_attempts = 0;

		// Receive acknowledgement 
		receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = receive_acknowledgement(socket, &inbound_request_header, shared_secret);
			receive_attempts++;
		}
		if(receive_attempts >= MAX_RECEIVE_ATTEMPTS)
		{
			print_too_many_receive_attempts_error(socket, "send_account_create", "acknowledgement for receipt of data member for payload", payloads_sent + 1, NULL);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		}
		receive_attempts = 0;

		// Check valid acknowledgement
		if(inbound_request_header.parameter_count != OK)
		{
			print_acknowledgement_type_mismatch_error(socket, "send_account_create", "SEND ACCOUNT_CREATE", inbound_request_header.parameter_count, OK);
			fprintf(stderr, "This happened after trying to get an acknowledgement for the receipt of the data member of payload #%d.\n", payloads_sent + 1);
			free(outbound_payloads[0].data);
			free(outbound_payloads[1].data);
			free(outbound_payloads[2].data);
			return false;
		} 

		// update for the loop condition
		payloads_sent++;
	}
	return true;
}

bool send_verification_request(int socket, struct request_header *outbound_request_header, char *verification_type, char **file_paths, int file_paths_length)
{ 
	if(outbound_request_header == NULL){
		fprintf(stderr, "[send_verification_request] Cannot use request header struct that points to NULL for an outbound request header. Bad argument provided.\n");
		return false;
	}
	if(verification_type == NULL) {
		fprintf(stderr, "[send_verification_request] Cannot use verification type char pointer that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(file_paths == NULL)
	{
		fprintf(stderr, "[send_verification_request] Cannot use file paths string pointer (char **) that points to NULL. Bad argument provided.\n");
		return false;
	}
	if(file_paths_length <= 0) {
		fprintf(stderr, "[send_verification_request] Cannot use a buffer for file paths that is reported to be 0 length or less (length parameter was given as %d). Bad argument provided.\n", file_paths_length);
		return false;
	}
	// ensure NO strings point to NULL
	for(int i = 0; i < file_paths_length; i++)
	{
		if(file_paths[file_paths_length] != NULL) continue;

		fprintf(stderr, "[send_verification_request] Preemptive check - Cannot use a file path char pointer that points to NULL. Member #%d of the file paths buffer points to NULL.\n", i + 1);
		return false;
	}
	
	bool send_status;
	bool receive_status;
	int send_attempts = 0;
	int receive_attempts = 0;
	struct request_header inbound_request_header;
	
	// set the outbound request header with the proper values
	outbound_request_header->action = SEND;
	outbound_request_header->subject = VERIFICATION_REQUEST;
	outbound_request_header->parameter_count = 1 + file_paths_length;
	outbound_request_header->metadata_total_size = 
	outbound_request_header->
	outbound_request_header->
	// read the binary data of the files to be sent off
	for(int i = 0; i < file_paths_length; i++)
	{
		
	}
}

size_t get_file_size(char *file_path, enum FILE_IO_CODE *return_code)
{
	if(return_code == NULL){
		fprintf(stderr, "[get_file_size] Cannot load a FILE_IO_CODE into a pointer that points to NULL. Bad argument provided.\n");
		return NULL;
	}

	if(file_path == NULL){
		fprintf(stderr, "[get_file_size] File path not provided. char *file_path points  to NULL.\n");
		(*return_code) = BAD_FILE_PATH;
		return NULL;
	}

	FILE *fh;
	fh = fopen(file_path, "rb");
	if(fh == NULL) {
		fprintf(stderr, "[get_file_size] Cannot open \"%s\" for reading. Does it exist? Are there permission errors?\n", file_path);
		(*return_code) = BAD_FILE_PATH;
		return 0;
	}
	
	fseek(fh, 0, SEEK_END);
	file_size = ftell(fh);
	fclose(fh);
	(*return_code) = IO_OK;
	return file_size;
}

void* read_binary_file(char *file_path, enum FILE_IO_CODE *return_code, size_t file_size)
{
	if(return_code == NULL)
	{
		fprintf(stderr, "[read_binary_file] Cannot load a FILE_IO_CODE into a pointer that points to NULL. Bad argument provided.\n");
		return NULL;
	}

	if(file_path == NULL)
	{
		fprintf(stderr, "[read_binary_file] File path not provided. char *file_path points  to NULL.\n");
		(*return_code) = BAD_FILE_PATH;
		return NULL;
	}
	
	// Open file and ensure it actually exists
	FILE *fh;
	fh = fopen(file_path, "rb");
	if(fh == NULL)
	{
		fprintf(stderr, "[read_binary_file] Failed to open the file stored at \"%s\".\n Does this file exist?\n", file_path);
		(*return_code) = BAD_FILE_PATH;
		return NULL;
	}

	// Make sure file is not too big
	size_t file_size = 0;
	fseek(fh, 0, SEEK_END);
	file_size = ftell(fh);
	if(file_size >= max_bytes)
	{
		fprintf(stderr, "[read_binary_file] File size is too large. Max file size is %ld bytes, but the given file is %zu bytes.\n", max_bytes, file_size);
		fclose(fh);
		(*return_code) = IO_TOO_LARGE;
		return NULL;
	}

	// Read the entire file
	void *file_data = malloc(file_size);
	size_t bytes_read = fread(file_data, file_size, 1, fh); 
	if(bytes_read != file_size)
	{
		fprintf(stderr, "[read_binary_file] Failed to read %zu bytes from the file. Stopped reading after %zu bytes.\n", file_size, bytes_read);
		fclose(fh);
		(*return_code) = BYTES_READ_MISMATCH;
		free(file_data);
	}

	// Return OK code and pointer to the file's data
	(*return_code) = IO_OK;
	return file_data;
}

bool server_confirm_user_existence(char username[])
{
	// in the meantime, until DB is setup
	return true;
}

bool validate_username(char username[])
{
	if(username == NULL)
	{
		fprintf(stderr, "validate_username: Username argument is a NULL pointer.\n");
		return false;
	}

	size_t username_length = strlen(username);
	if(username_length == 0)
	{
		fprintf(stderr, "validate_username: Usernames must be at least 1 character long.\n");
		return false;
	}

	if(username_length >= 16)
	{
		fprintf(stderr, "validate_username: Usernames can only be 15 characters long. Username \"%s\" exceeds this.\n", username);
		return false;
	}

	byte counter = 0;
	while(true)
	{
		char symbol = username[counter];
		// Reject capital letters and certain symbols
		if(symbol >= 58 && symbol <= 96)
		{
			fprintf(stderr, "validate_username: Usernames cannot contain symbols or capital letters. \"%c\" is an illegal character.\n", symbol);
			return false;
		}

		// Reject other symbols not covered by previous check
		if(symbol >= 32 && symbol <= 47)
		{
			fprintf(stderr, "validate_username: Usernames cannot contain symbols or capital letters. \"%c\" is an illegal character.\n", symbol);
			return false;
		}

		// Reject even more symbols
		if(symbol >= 123 && symbol <= 255)
		{
			fprintf(stderr, "validate_username: Usernames cannot contain symbols or capital letters. \"%c\" is an illegal character.\n", symbol);
			return false;
		}

		if(symbol == '\0')
			break;

		counter++;
	}
	return true;
}

struct user* user_create(char username[], char fname[], char lname[], byte age)
{
	// validate username
	if(!validate_username(username))
	{
		fprintf(stderr, "user_create: Cannot create user.\n");
		return NULL;
	}

	// validate firstname
	if(fname == NULL)
	{
		fprintf(stderr, "user_create: Firstname argument is a NULL pointer.\n");
		return NULL;
	}
	size_t fname_length = strlen(fname);
	if(fname_length == 0 || fname_length >= 32)
	{
		fprintf(stderr, "user_create: First name is too long. First names may only be 31 characters long.\n");
		return NULL;
	}

	// validate lastname 
	if(lname == NULL)
	{
		fprintf(stderr, "user_create: Lastname argument is a NULL pointer.\n");
		return NULL;
	}
	size_t lname_length = strlen(lname);
	if(lname_length == 0 || lname_length >= 32)
	{
		fprintf(stderr, "user_create: Last name is too long. First names may only be 31 characters long.\n");
		return NULL;
	}

	// Create user
	struct user *new_user = malloc(sizeof(struct user));
	if(new_user == NULL)
	{
		fprintf(stderr, "user_create: Failed to create new user. Malloc call returned NULL.\n");
		return NULL;
	}
	strcpy(new_user->username, username);
	strcpy(new_user->fname, fname);
	strcpy(new_user->lname, lname);
	new_user->age = age;

	return new_user;
}

struct post* post_create(size_t id, char creator[], char *text, unsigned short text_length, byte category, 
		byte month, byte day, unsigned short year, bool qustion, size_t qid)
{
	// unimplemented
	struct post *new_post = malloc(sizeof(struct post));
	if(new_post == NULL)
	{
		fprintf(stderr, "post_create: Could not allocate memory for new post struct.\n");
		return NULL;
	}

	return new_post;
}

bool client_sign_in_with_cache(void)
{
	// Check for cache file
	FILE *fh = fopen("/user/lcache.bin", "rb");
	if(fh == NULL)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache does not exist.\n");
		return false;
	}

	// Begin reading file
	unsigned short read_v;
	size_t bytes_read = fread(&read_v, 2, 1, fh);

	// Exit if file's data cannot be read
	if(bytes_read != 2)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Failed to read contents of login cache. File was opened, but data cannot be read.\n");
		fclose(fh);
		return false;
	}

	// Exit if file's data is malformed
	if(read_v != 2)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Unrecognized control character at start.\n");
		fclose(fh);
		return false;
	}

	// Read data item 1
	unsigned short unumbers[16];
	byte numbers_len = 0;
	read_v = 0;
	bytes_read = fread(&read_v, 2, 1, fh);
	while(true)
	{
		// Bad data is read --- exit
		if(bytes_read != 2)
		{
			fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected 2 bytes, but read something else.\n");
			fclose(fh);
			return false;
		}

		// end of current item
		if(read_v == 3) 
			break; 

		// max length reached
		if(numbers_len >= 15)
		{
			// force value of read_v to be appropriate control
			// value for next loop
			bytes_read = fread(&read_v, 2, 1, fh);
			if(bytes_read != 2)
			{
				fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected 2 bytes, but read something else.\n");
				fclose(fh);
				return false;
			}
			break;
		}

		// insert into buffer
		unumbers[numbers_len] = read_v;
		numbers_len++;

		// Read next value
		bytes_read = fread(&read_v, 2, 1, fh);
	}

	// expected that we are resuming after reading a control value
	if(read_v != 3)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected control value, but read something else.\n");
		fclose(fh);
		return false;
	}

	// expect to read next control value
	bytes_read = fread(&read_v, 2, 1, fh);
	if(bytes_read != 2)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected to read 2 bytes, but read something else.\n");
		fclose(fh);
		return false;
	}

	// check that control value was read demarcating start of next item
	if(read_v != 2)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected to read control value, but read something else.\n");
		fclose(fh);
		return false;
	}

	// New buffer to read from
	unsigned short pnumbers[16];
	byte pnumbers_len = 0;
	while(true)
	{
		// Bad data is read --- exit
		if(bytes_read != 2)
		{
			fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected 2 bytes, but read something else.\n");
			fclose(fh);
			return false;
		}

		// end of current item
		if(read_v == 3) 
			break; 

		// max length reached
		if(pnumbers_len >= 15)
		{
			// force value of read_v to be appropriate control
			// value for next loop
			bytes_read = fread(&read_v, 2, 1, fh);
			if(bytes_read != 2)
			{
				fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected 2 bytes, but read something else.\n");
				fclose(fh);
				return false;
			}
			break;
		}

		// insert into buffer
		pnumbers[pnumbers_len] = read_v;
		pnumbers_len++;

		// Read next value
		bytes_read = fread(&read_v, 2, 1, fh);
	}

	// Double-check that control value was read.
	if(read_v != 3)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Login cache is malformed. Expected to read control value, but read something else.\n");
		fclose(fh);
		return false;
	}

	// cache file no longer necessary, close it.
	fclose(fh);

	// Decode values
	char *uname = malloc(sizeof(char) * (numbers_len + 1));
	if(uname == NULL)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Failed to allocate memory for username credential.\n");
		return false;	
	}
	
	char *pbuf = malloc(sizeof(char) * (pnumbers_len + 1)); 
	if(pbuf == NULL)
	{
		fprintf(stderr, "[client_sign_in_with_cache]: Failed to allocate memory for password credential.\n");
		free(uname);
		return false;
	}

	// decode uname
	for(byte i = 0; i < numbers_len; i++)
		uname[i] = unumbers[i] / 31;

	// decode password
	for(byte i = 0; i < pnumbers_len; i++)
		pbuf[i] = pnumbers[i] / 31;

	// insert null terminators
	uname[numbers_len] = '\0';
	pbuf[pnumbers_len] = '\0';

	// Send credentials to server IMPLEMENT THIS LATER! 
	free(uname);
	free(pbuf);
	return true;
}

bool client_create_login_cache(char uname[], char pass[]);
