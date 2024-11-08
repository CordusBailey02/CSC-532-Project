#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "terrorexchange.h"

bool gui_send_request_header(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[gui_send_request_header]: Cannot send request header that points to NULL.\n");
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
	bytes_sent = send(socket, header, sizeof(struct request_header), 0);

	// All data sent OK
	if(bytes_sent == sizeof(struct request_header))
		return true;

	// Return false if bad connection
	if(bytes_sent < 0)
	{
		fprintf(stderr, "[gui_send_request_header]: Failed to send data. Send function returned -1.\n");
		return false;
	}

	// Continue sending rest of bytes
	ssize_t total_bytes_sent = bytes_sent;
	while(total_bytes_sent < sizeof(struct request_header))
	{
		bytes_sent = send(socket, header + total_bytes_sent, sizeof(struct request_header) - total_bytes_sent, 0);
		if(bytes_sent < 0)
		{
			fprintf(stderr, "[gui_send_request_header]: Unable to send remaining bytes. Send function returned -1.\n");
			return false;
		}
		total_bytes_sent += bytes_sent;
	}
	return true;
}

bool gui_receive_request_header(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[gui_receive_request_header]: Cannot load received request header into a request header struct that points to NULL. Argument provided is bad.\n");
		return false;
	}

	ssize_t bytes_received;
	bytes_received = recv(socket, header, sizeof(struct request_header), 0);
	if(bytes_received < 0)
	{
		fprintf(stderr, "[gui_receive_request_header]: Failed to receive data. Recv function returned -1.\n");
		return false;
	}

	// Receive remaining bytes if all are not sent
	if(bytes_received < sizeof(struct request_header))
	{
		ssize_t total_bytes_received = bytes_received;
		while(total_bytes_received < sizeof(struct request_header))
		{
			bytes_received = recv(socket, header + total_bytes_received, sizeof(struct request_header) - total_bytes_received, 0);
			if(bytes_received < 0)
			{
				fprintf(stderr, "[gui_receive_request_header]: Failed to receive data. Recv function returned -1 while trying to receive remaining bytes.\n");
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
bool gui_send_acknowledgement(int socket, enum ACKNOWLEDGEMENT_TYPE type)
{
	// (1) Create acknowledgement request header
	// (2) DO NOT convert to network byte order, because gui_send_request_header 
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
	status = gui_send_request_header(socket, &acknowledgement);
	if(status == false)
		fprintf(stderr, "[gui_send_acknowledgement]: Could not send acknowledgement. gui_send_request_header() returned false.\n");

	return status;
}

// This is not guaranteed to receive an OK acknowledgement. 
// You should check if the subject is ACKNOWLEDGEMENT afterwards; it might be NOT_FOUND
// instead.
bool gui_receive_acknowledgement(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[gui_receive_acknowledgement]: Cannot read to-be-received request header into a request header struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive acknowledgement
	bool status;
	status = gui_receive_request_header(socket, header);
	if(status == false)
		fprintf(stderr, "[gui_receive_acknowledgement]: Failed to receive acknowledgement. gui_receive_request_header returned false.\n");

	return status;
}

bool gui_send_payload_metadata(int socket, struct payload *outbound_payload)
{
	if(outbound_payload == NULL)
	{
		fprintf(stderr, "[gui_send_payload_metadata]: Cannot send the metadata of a payload struct that points to NULL. Bad argument.\n");
		return false;
	}

	// (1) Create PAYLOAD METADATA request header
	// (2) DO NOT convert to network byte order, because gui_send_request_header 
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
	status = gui_send_request_header(socket, &payload_metadata);
	if(status == false)
		fprintf(stderr, "[gui_send_payload_metadata]: Could not send payload metadata. gui_send_request_header() returned false.\n");

	return status;
}

// receives a SEND PAYLOAD METADATA request header and uses that data to initialize a
// payload (the inbound_payload parameter)
bool gui_receive_payload_metadata(int socket, struct payload *inbound_payload)
{
	if(inbound_payload == NULL)
	{
		fprintf(stderr, "[receive_payload_metadata]: Cannot read to-be-received payload into a payload struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive payload metadata 
	struct request_header header;
	bool status;
	status = gui_receive_request_header(socket, &header);
	if(status == false)
		fprintf(stderr, "[receive_payload_metadata]: Failed to receive payload metadata request header. gui_receive_request_header returned false.\n");

	// Set the inbound payload with the data of the request header
	// NOTE: data is already in host format, as per the gui_receive_request_header function.
	inbound_payload->member_size = header.parameters_total_size / header.parameter_count;
	inbound_payload->member_count = header.parameter_count;

	return status;
}

bool gui_send_payload(int socket, struct payload *outbound_payload)
{
	if(outbound_payload == NULL)
	{
		fprintf(stderr, "[gui_send_payload]: Cannot send a payload struct that points to NULL. Bad argument provided.\n");
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
		printf("[gui_send_payload] Attempting to send payload data as a singular chunk (%zu total bytes).\n", total_bytes_to_send);
		bytes_sent = send(socket, payload_data, total_bytes_to_send, 0);
		if(bytes_sent == total_bytes_to_send)
		{
			printf("[gui_send_payload] All the bytes of the payload were sent with one call to send().\n");
			return true;
		}

		if(bytes_sent < 0)
		{
			fprintf(stderr, "[gui_send_payload]: Failed to send payload with %zu bytes - send() returned -1.\n", total_bytes_to_send);
			return false;
		}

		// Continue sending the rest of the bytes
		total_bytes_sent = bytes_sent;
		printf("[gui_send_payload] Attempting to send remaining %zu bytes of payload data.\n", total_bytes_to_send - total_bytes_sent);
		while(total_bytes_sent < total_bytes_to_send)
		{
			bytes_sent = send(socket, payload_data + total_bytes_sent, total_bytes_to_send - total_bytes_sent, 0);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[gui_send_payload]: Failed to send remaining %zu bytes of payload. Send() returned -1.\n", total_bytes_to_send - total_bytes_to_send);
				return false;
			}

			total_bytes_sent += bytes_sent;
		}
		printf("[gui_send_payload] All bytes were sent in one chunk!\n");
		return true; // all bytes sent
	}

	// Send the data in chunks.
	char chunk_buffer[CHUNK_SIZE];
	size_t chunk_buffer_used = 0;
	size_t bytes_remaining = total_bytes_to_send;
	size_t total_chunk_bytes_sent;
	bytes_sent = 0;
	total_bytes_sent = 0;
	printf("[gui_send_payload] Attempting to send payload data in several chunks.\n");
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
		bytes_sent = send(socket, chunk_buffer, chunk_buffer_used, 0);
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
			bytes_sent = send(socket, chunk_buffer + total_chunk_bytes_sent, chunk_buffer_used - total_chunk_bytes_sent, 0);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[gui_send_payload]: Failed to send %zu bytes of chunk buffer to recipient. %zu bytes of %zu were sent in total across all chunks. %zu bytes of the current chunk were sent. Send() function returned -1.\n", chunk_buffer_used - total_chunk_bytes_sent, total_bytes_sent, total_bytes_to_send, bytes_sent);
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
bool gui_receive_payload(int socket, struct payload *inbound_payload)
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
		bytes_received = recv(socket, inbound_payload->data, total_bytes_to_receive, 0);
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
			bytes_received = recv(socket, inbound_payload->data + total_bytes_received, total_bytes_to_receive - total_bytes_received, 0);
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
		bytes_received = recv(socket, chunk_buffer, chunk_buffer_amt_to_use, 0);
		if(bytes_received < 0)
		{
			fprintf(stderr, "[receive_payload]: Failed to receive chunk of size %zu from sender. %zu bytes of %zu bytes were received in all (across all chunks). Recv() function returned -1.\n", chunk_buffer_amt_to_use, total_bytes_received, total_bytes_to_receive);
			return false;
		}

		// keep receiving the rest of the bytes in the inbound chunk
		total_chunk_bytes_received = bytes_received;
		while(total_chunk_bytes_received < chunk_buffer_amt_to_use)
		{
			bytes_received = recv(socket, chunk_buffer + total_chunk_bytes_received, chunk_buffer_amt_to_use - total_chunk_bytes_received, 0);
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

// This sets the request header properly for you. There is no need to configure it in advance.
bool gui_send_developer_test_message(int connection_socket, struct request_header *outbound_request_header, char *message)
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
	send_status = gui_send_request_header(connection_socket, outbound_request_header);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = gui_send_request_header(connection_socket, outbound_request_header);
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
	receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{	
		receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
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
	send_status = gui_send_payload_metadata(connection_socket, &outbound_payload);
	send_attempts = 1;
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = gui_send_payload_metadata(connection_socket, &outbound_payload);
		send_attempts++;
	}
	if(send_attempts >= MAX_SEND_ATTEMPTS)
	{
		fprintf(stderr, "[send_developer_test_message] Failed to send payload metadata to the recipient. Send attempts reached/exceed MAX_SEND_ATTEMPTS. There might be something wrong with the connection.\n");
		return false;
	}
	send_attempts = 0;

	// Receive acknowledgement for payload metadata
	receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
	receive_attempts = 1;
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{	
		receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
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
	send_status = gui_send_payload(connection_socket, &outbound_payload);
	send_attempts = 1;
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = gui_send_payload(connection_socket, &outbound_payload);
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
	receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
	receive_attempts = 1;
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{
		receive_status = gui_receive_acknowledgement(connection_socket, &inbound_request_header);
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
bool gui_send_login_attempt(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *password, int password_length)
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
	send_status = gui_send_request_header(socket, outbound_request_header);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = gui_send_request_header(socket, outbound_request_header);
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
	receive_status = gui_receive_request_header(socket, &inbound_request_header);
	while(receive_status == false)
	{
		receive_status == gui_receive_request_header(socket, &inbound_request_header);
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
		send_status = gui_send_payload_metadata(socket, &outbound_payloads[payloads_sent]);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = gui_send_payload_metadata(socket, &outbound_payloads[payloads_sent]);
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
		receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
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
		send_status = gui_send_payload(socket, &outbound_payloads[payloads_sent]);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = gui_send_payload(socket, &outbound_payloads[payloads_sent]);
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
		receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
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
bool gui_send_account_create(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *email, int email_length, char *password, int password_length)
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
	send_status = gui_send_request_header(socket, outbound_request_header);
	while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
	{
		send_status = gui_send_request_header(socket, outbound_request_header);
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
	receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
	while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
	{
		receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
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
		send_status = gui_send_payload_metadata(socket, &outbound_payloads[payloads_sent]);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = gui_send_payload_metadata(socket, &outbound_payloads[payloads_sent]);
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
		receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
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
		send_status = gui_send_payload(socket, &outbound_payloads[payloads_sent]);
		while(send_status == false && send_attempts < MAX_SEND_ATTEMPTS)
		{
			send_status = gui_send_payload(socket, &outbound_payloads[payloads_sent]);
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
		receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
		while(receive_status == false && receive_attempts < MAX_RECEIVE_ATTEMPTS)
		{
			receive_status = gui_receive_acknowledgement(socket, &inbound_request_header);
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
