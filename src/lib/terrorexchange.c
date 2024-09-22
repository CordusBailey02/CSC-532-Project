#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terrorexchange.h"

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

