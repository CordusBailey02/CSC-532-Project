#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "terrorexchange.h"

#ifndef TERROREXCHANGEGUI_H
#define TERROREXCHANGEGUI_H
#define byte unsigned char
//#define COEFFICIENT 31
//#define CHUNK_SIZE 16384
//#define MAX_SEND_ATTEMPTS 10
//#define MAX_RECEIVE_ATTEMPTS 10

extern int client_tcp_socket = 0;

bool gui_send_request_header(int socket, struct request_header *header);
bool gui_receive_request_header(int socket, struct request_header *header);

bool gui_send_acknowledgement(int socket, enum ACKNOWLEDGEMENT_TYPE type);
bool gui_receive_acknowledgement(int socket, struct request_header *header);

bool gui_send_payload_metadata(int socket, struct payload *outbound_payload);
bool gui_receive_payload_metadata(int socket, struct payload *inbound_payload);

bool gui_send_payload(int socket, struct payload *outbound_payload);
bool gui_receive_payload(int socket, struct payload *inbound_payload);

bool gui_send_developer_test_message(int socket, struct request_header *outbound_request_header, char *message);
bool gui_send_login_attempt(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *password, int password_length);
bool gui_send_account_create(int socket, struct request_header *outbound_request_header, char *username, int username_length, char *email, int email_length, char *password, int password_length);

#endif
