#include <stdbool.h>
#include <stdlib.h>

#ifndef TERROREXCHANGE_H
#define TERROREXCHANGE_H
#define byte unsigned char
#define COEFFICIENT 31

enum ACTION { GET, POST }; 
enum SUBJECT { // Typical data objects
	       CATEGORY, PROFILE, POST, NOTIFICATION, REPORT, DEVELOPER_TEST_MESSAGE,

	       ACKNOWLEDGEMENT
	     };

enum ACKNOWLEDGEMENT {OK, MALFORMED, DUPLICATE, NOT_FOUND, UNAUTHORIZED, FAILED};

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

struct client_request_header
{
	enum client_requests request_type;
	unsigned short parameter_count;
	unsigned short bytes_to_send;
};

struct server_response_header
{
	enum server_responses response_type;
	unsigned short parameter_count;
	unsigned short bytes_to_send; 
};

struct message_parameter
{
	byte member_size;
	unsigned short member_count;
	void *data;
};

struct message_parameter* message_parameter_create(byte member_size, unsigned short member_count);

bool server_confirm_user_existence(char username[]);

bool validate_username(char username[]);

struct user* user_create(char username[], char fname[], char lname[], byte age);

struct post* post_create(size_t id, char creator[], char *text, unsigned short text_length, byte category, 
		byte month, byte day, unsigned short year, bool qustion, size_t qid);

// Anticipates static location for binary file
bool client_sign_in_with_cache(void);

bool client_create_login_cache(char uname[], char pass[]);

#endif
