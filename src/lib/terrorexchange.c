<<<<<<< HEAD
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
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

bool send_request_header(int socket, struct request_header *header)
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
	bytes_sent = send(socket, header, sizeof(struct request_header), 0);

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
		bytes_sent = send(socket, header + total_bytes_sent, sizeof(struct request_header) - total_bytes_sent, 0);
		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_request_header]: Unable to send remaining bytes. Send function returned -1.\n");
			return false;
		}
		total_bytes_sent += bytes_sent;
	}
	return true;
}

bool receive_request_header(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_request_header]: Cannot load received request header into a request header struct that points to NULL. Argument provided is bad.\n");
		return false;
	}

	ssize_t bytes_received;
	bytes_received = recv(socket, header, sizeof(struct request_header), 0);
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
			bytes_received = recv(socket, header + total_bytes_received, sizeof(struct request_header) - total_bytes_received, 0);
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

bool send_acknowledgement(int socket, enum ACKNOWLEDGMENT_TYPE type)
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
	status = send_request_header(socket, &acknowledgement);
	if(status == false)
		fprintf(stderr, "[send_acknowledgement]: Could not send acknowledgement. send_request_header() returned false.\n");

	return status;
}

// This is not guaranteed to receive an OK acknowledgement. 
// You should check if the subject is ACKNOWLEDGEMENT afterwards; it might be NOT_FOUND
// instead.
bool receive_acknowledgement(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_acknowledgement]: Cannot read to-be-received request header into a request header struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive acknowledgement
	bool status;
	status = receive_request_header(socket, header);
	if(status == false)
		fprintf(stderr, "[receive_acknowledgement]: Failed to receive acknowledgement. receive_request_header returned false.\n");

	return status;
}

bool send_payload_metadata(int socket, struct payload *outbound_payload)
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
	status = send_request_header(socket, &payload_metadata);
	if(status == false)
		fprintf(stderr, "[send_payload_metadata]: Could not send payload metadata. send_request_header() returned false.\n");

	return status;
}

// receives a SEND PAYLOAD METADATA request header and uses that data to initialize a
// payload (the inbound_payload parameter)
bool receive_payload_metadata(int socket, struct payload *inbound_payload)
{
	if(inbound_payload == NULL)
	{
		fprintf(stderr, "[receive_payload_metadata]: Cannot read to-be-received payload into a payload struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive payload metadata 
	struct request_header header;
	bool status;
	status = receive_request_header(socket, &header);
	if(status == false)
		fprintf(stderr, "[receive_payload_metadata]: Failed to receive payload metadata request header. receive_request_header returned false.\n");

	// Set the inbound payload with the data of the request header
	// NOTE: data is already in host format, as per the receive_request_header function.
	inbound_payload->member_size = header.parameters_total_size / header.parameter_count;
	inbound_payload->member_count = header.parameter_count;

	return status;
}

bool send_payload(int socket, struct payload *outbound_payload)
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
	// try to send data all at once - payload is smaller than one chunk
	if(total_bytes_to_send <= CHUNK_SIZE)
	{
		bytes_sent = send(socket, payload_data, total_bytes_to_send, 0);

		if(bytes_sent == total_bytes_to_send)
			return true;

		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_payload]: Failed to send payload with %zu bytes - send() returned -1.\n", total_bytes_to_send);
			return false;
		}

		// Continue sending the rest of the bytes
		total_bytes_sent = bytes_sent;
		while(total_bytes_sent < total_bytes_to_send)
		{
			bytes_sent = send(socket, payload_data + total_bytes_sent, total_bytes_to_send - total_bytes_sent, 0);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[send_payload]: Failed to send remaining %zu bytes of payload. Send() returned -1.\n", total_bytes_to_send - total_bytes_to_send);
				return false;
			}

			total_bytes_sent += bytes_sent;
		}
		return true; // all bytes sent
	}

	// Send the data in chunks.
	char chunk_buffer[CHUNK_SIZE];
	size_t chunk_buffer_used = 0;
	size_t bytes_remaining = total_bytes_to_send;
	size_t total_chunk_bytes_sent;
	bytes_sent = 0;
	total_bytes_sent = 0;
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
bool receive_payload(int socket, struct payload *inbound_payload)
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
		// First try
		bytes_received = recv(socket, inbound_payload->data, total_bytes_to_receive, 0);
		if(bytes_received == total_bytes_to_receive)
			return true;
		if(bytes_received < 0)
		{
			fprintf(stderr, "[receive_payload]: Failed to receive payload with %zu bytes. Recv() returned -1.\n", total_bytes_to_receive);
			return false;
		}

		// Continue receiving the data that remains.
		total_bytes_received = bytes_received;
		while(total_bytes_received < total_bytes_to_receive)
		{
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

=======
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
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

bool send_request_header(int socket, struct request_header *header)
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
	bytes_sent = send(socket, header, sizeof(struct request_header), 0);

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
		bytes_sent = send(socket, header + total_bytes_sent, sizeof(struct request_header) - total_bytes_sent, 0);
		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_request_header]: Unable to send remaining bytes. Send function returned -1.\n");
			return false;
		}
		total_bytes_sent += bytes_sent;
	}
	return true;
}

bool receive_request_header(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_request_header]: Cannot load received request header into a request header struct that points to NULL. Argument provided is bad.\n");
		return false;
	}

	ssize_t bytes_received;
	bytes_received = recv(socket, header, sizeof(struct request_header), 0);
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
			bytes_received = recv(socket, header + total_bytes_received, sizeof(struct request_header) - total_bytes_received, 0);
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

bool send_acknowledgement(int socket)
{
	// (1) Create acknowledgement request header
	// (2) DO NOT convert to network byte order, because send_request_header 
	//     function will do it.
	struct request_header acknowledgement; 
	acknowledgement.action = SEND;
	acknowledgement.subject = ACKNOWLEDGEMENT;
	acknowledgement.parameter_count = 0;
	acknowledgement.metadata_total_size = 0;
	acknowledgement.parameters_total_size = 0;
	acknowledgement.total_bytes = 0;

	// Send the acknowledgement
	bool status;
	status = send_request_header(socket, &acknowledgement);
	if(status == false)
		fprintf(stderr, "[send_acknowledgement]: Could not send acknowledgement. send_request_header() returned false.\n");

	return status;
}

// This is not guaranteed to receive an OK acknowledgement. 
// You should check if the subject is ACKNOWLEDGEMENT afterwards; it might be NOT_FOUND
// instead.
bool receive_acknowledgement(int socket, struct request_header *header)
{
	if(header == NULL)
	{
		fprintf(stderr, "[receive_acknowledgement]: Cannot read to-be-received request header into a request header struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive acknowledgement
	bool status;
	status = receive_request_header(socket, header);
	if(status == false)
		fprintf(stderr, "[receive_acknowledgement]: Failed to receive acknowledgement. receive_request_header returned false.\n");

	return status;
}

bool send_payload_metadata(int socket, struct payload *outbound_payload)
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
	status = send_request_header(socket, &payload_metadata);
	if(status == false)
		fprintf(stderr, "[send_payload_metadata]: Could not send payload metadata. send_request_header() returned false.\n");

	return status;
}

// receives a SEND PAYLOAD METADATA request header and uses that data to initialize a
// payload (the inbound_payload parameter)
bool receive_payload_metadata(int socket, struct payload *inbound_payload)
{
	if(inbound_payload == NULL)
	{
		fprintf(stderr, "[receive_payload_metadata]: Cannot read to-be-received payload into a payload struct that points to NULL. Argument is bad.\n");
		return false;
	}

	// receive payload metadata 
	struct request_header header;
	bool status;
	status = receive_request_header(socket, &header);
	if(status == false)
		fprintf(stderr, "[receive_payload_metadata]: Failed to receive payload metadata request header. receive_request_header returned false.\n");

	// Set the inbound payload with the data of the request header
	// NOTE: data is already in host format, as per the receive_request_header function.
	inbound_payload->member_size = header.parameters_total_size / header.parameter_count;
	inbound_payload->member_count = header.parameter_count;

	return status;
}

bool send_payload(int socket, struct payload *outbound_payload)
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
	// try to send data all at once - payload is smaller than one chunk
	if(total_bytes_to_send <= CHUNK_SIZE)
	{
		bytes_sent = send(socket, payload_data, total_bytes_to_send, 0);

		if(bytes_sent == total_bytes_to_send)
			return true;

		if(bytes_sent < 0)
		{
			fprintf(stderr, "[send_payload]: Failed to send payload with %zu bytes - send() returned -1.\n", total_bytes_to_send);
			return false;
		}

		// Continue sending the rest of the bytes
		total_bytes_sent = bytes_sent;
		while(total_bytes_sent < total_bytes_to_send)
		{
			bytes_sent = send(socket, payload_data + total_bytes_sent, total_bytes_to_send - total_bytes_sent, 0);
			if(bytes_sent < 0)
			{
				fprintf(stderr, "[send_payload]: Failed to send remaining %zu bytes of payload. Send() returned -1.\n", total_bytes_to_send - total_bytes_to_send);
				return false;
			}

			total_bytes_sent += bytes_sent;
		}
		return true; // all bytes sent
	}

	// Send the data in chunks.
	char chunk_buffer[CHUNK_SIZE];
	size_t chunk_buffer_used = 0;
	size_t bytes_remaining = total_bytes_to_send;
	size_t total_chunk_bytes_sent;
	bytes_sent = 0;
	total_bytes_sent = 0;
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

bool receive_payload(int socket, struct payload *inbound_payload)
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

	// Try to send all the data at once if chunking is not required.
	if(total_bytes_to_receive <= CHUNK_SIZE)
	{
		// First try
		bytes_received = recv(socket, inbound_payload->data, total_bytes_to_receive, 0);
		if(bytes_received == total_bytes_to_receive)
			return true;
		if(bytes_received < 0)
		{
			fprintf(stderr, "[receive_payload]: Failed to receive payload with %zu bytes. Recv() returned -1.\n", total_bytes_to_receive);
			return false;
		}

		// Continue sending the data that remains.
		total_bytes_received = bytes_received;
		while(total_bytes_received < total_bytes_to_receive)
		{
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

>>>>>>> 20e88ae20a17fde9f5c2448a271892149c76d61f
