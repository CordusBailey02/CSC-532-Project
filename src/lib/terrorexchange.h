#include <stdbool.h>
#include <stdlib.h>

#ifndef TERROREXCHANGE_H
#define TERROREXCHANGE_H
#define byte unsigned char
#define COEFFICIENT 31

enum ACTION { GET, SEND }; 
enum SUBJECT { // Typical data objects
	       CATEGORY, PROFILE, POST, NOTIFICATION, REPORT, DEVELOPER_TEST_MESSAGE,

	       ACKNOWLEDGEMENT
	     };

enum ACKNOWLEDGEMENT {OK, MALFORMED, DUPLICATE, NOT_FOUND, UNAUTHORIZED, FAILED};

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
	byte id; // initial assumption that there will not be
		 // more than 256 categories
	char name[32];
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

struct payload* payload_create(size_t member_size, size_t member_count);

bool send_request_header(int socket, struct request_header *header);
bool receive_request_header(int socket, struct request_header *header);

bool send_acknowledgement(int socket);
bool receive_acknowledgement(int socket);

bool server_confirm_user_existence(char username[]);

bool validate_username(char username[]);

struct user* user_create(char username[], char fname[], char lname[], byte age);

struct post* post_create(size_t id, char creator[], char *text, unsigned short text_length, byte category, 
		byte month, byte day, unsigned short year, bool qustion, size_t qid);

// Anticipates static location for binary file
bool client_sign_in_with_cache(void);

bool client_create_login_cache(char uname[], char pass[]);

#endif
