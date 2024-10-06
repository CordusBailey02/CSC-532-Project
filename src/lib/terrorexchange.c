#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terrorexchange.h"

struct message_parameter* message_parameter_create(byte member_size, unsigned short member_count)
{
	struct message_parameter *new_parameter = malloc(sizeof(struct message_parameter));
	if(new_parameter == NULL)
	{
		fprintf(stderr, "[message_parameter_create]: Failed to allocate memory for new message_parameter.\n");
		return NULL;
	}

	new_parameter->member_size = member_size;
	new_parameter->member_count = member_count;

	return new_parameter;
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

