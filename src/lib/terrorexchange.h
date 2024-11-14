#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "secure_connection.h"

#ifndef TERROREXCHANGE_H
#define TERROREXCHANGE_H
#define byte unsigned char
#define COEFFICIENT 31
#define CHUNK_SIZE 16384
#define MAX_SEND_ATTEMPTS 10
#define MAX_RECEIVE_ATTEMPTS 10
#define MAX_FILE_SIZE_IN_BYTES 128000000 // 128 MB (decimal, not IEC)

enum ACTION { GET, SEND, ACTION_ERROR};	// ERROR is for functions that return an ACTION
					// enum. If they run into an error, then ERROR
					// is returned.
enum SUBJECT { // Typical data objects
	       CATEGORY, PROFILE, POST, NOTIFICATION, REPORT, DEVELOPER_TEST_MESSAGE,

	       PAYLOAD_METADATA, PAYLOAD,

	       ACKNOWLEDGEMENT,

	       LOGIN_ATTEMPT, USERNAME_CHANGE, PASSWORD_CHANGE, ACCOUNT_CREATE, USER_DATA,
	       LOGIN_ATTEMPT_RESPONSE, 

	       VERIFICATION_REQUEST,

		   POST_CREATE,

	       SUBJECT_ERROR,

	       INITIAL_SUBJECT_CODE
	     };

// parameter_count member of outbound request header is used to signal the type of acknowledgement. 
enum ACKNOWLEDGEMENT_TYPE {OK, MALFORMED, DUPLICATE, NOT_FOUND, UNAUTHORIZED, FAILED,
			   INSUFFICIENT_MEMORY, 
		 	   ACKNOWLEDGEMENT_TYPE_ERROR };

enum FILE_IO_CODE { IO_OK, IO_TOO_LARGE, BAD_FILE_PATH, ZERO_UPPER_LIMIT, BYTES_READ_MISMATCH, INITIAL_IO_VALUE, SIZE_ZERO_FILE };

struct request_header
{
	enum ACTION action;
	enum SUBJECT subject;
	size_t parameter_count;
	size_t metadata_total_size;
	size_t parameters_total_size;
	size_t total_bytes;
};

struct payload
{
	size_t member_size;
	size_t member_count;
	void *data;
};

struct category
{
	int id; // initial assumption that there will not be
		 // more than 256 categories
	char name[64];
};

struct user
{
	char username[16];
	char fname[32];
	char lname[32];
	byte age;
	bool verified;
	struct category verified_categories[16];
}; 

struct post
{
	size_t id;
	char creator[16]; // username of user (foreign key)
	char *text;
	unsigned short text_length;
	byte category;  // foreign key

	// date information
	byte month;
	byte day;
	unsigned short year;

	// if post is a response to a question
	bool question;
	size_t qid; // question id (foreign key to other posts)	
};

bool professional_category_exists(char *professional_category);

bool directory_exists(char *path);
bool create_directory(char *path);

struct payload* payload_create(size_t member_size, size_t member_count);

bool send_request_header(int socket, struct request_header *header, uint32_t shared_secret);
bool receive_request_header(int socket, struct request_header *header, uint32_t shared_secret);

bool send_acknowledgement(int socket, enum ACKNOWLEDGEMENT_TYPE type, uint32_t shared_secret);
bool receive_acknowledgement(int socket, struct request_header *header, uint32_t shared_secret);

bool send_payload_metadata(int socket, struct payload *outbound_payload, uint32_t shared_secret);
bool receive_payload_metadata(int socket, struct payload *inbound_payload, uint32_t shared_secret);

bool send_payload(int socket, struct payload *outbound_payload, uint32_t shared_secret);
bool receive_payload(int socket, struct payload *inbound_payload, uint32_t shared_secret);

void print_too_many_send_attempts_error(int socket, char *function_name, char *outbound_thing, int item_number);
void print_too_many_receive_attempts_error(int socket, char *function_name, char *outbound_thing, int item_number, char *additional_comment);
void print_acknowledgement_type_mismatch_error(int socket, char *function_name, char *message_type, enum ACKNOWLEDGEMENT_TYPE wrong_type, enum ACKNOWLEDGEMENT_TYPE right_type);

bool send_developer_test_message(int socket, struct request_header *outbound_request_header, char *message, uint32_t shared_secret);
bool send_login_attempt(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *password, int password_length, uint32_t shared_secret);
bool send_account_create(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *email, int email_length, char *password, int password_length, uint32_t shared_secret);
bool send_verification_request(int socket, struct request_header *outbound_request_header, char *username, char *email, char *verification_type, char **file_paths, int file_paths_length, uint32_t shared_secret);

size_t get_file_size(char *file_path, enum FILE_IO_CODE *return_code);
void* read_binary_file(char *file_path, enum FILE_IO_CODE *return_code, size_t file_size);

bool server_confirm_user_existence(char username[]);

bool validate_username(char username[]);

struct user* user_create(char username[], char fname[], char lname[], byte age);

struct post* post_create(size_t id, char creator[], char *text, unsigned short text_length, byte category, 
		byte month, byte day, unsigned short year, bool qustion, size_t qid);

// Anticipates static location for binary file
bool client_sign_in_with_cache(void);

bool client_create_login_cache(char uname[], char pass[]);

#endif
