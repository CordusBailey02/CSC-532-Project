# Note about Sending Information (Message Parameters)

Information is sent in the form of request/response headers, followed by up to 255 parameters. The number of parameters that will be sent is defined in the request/response header.

A parameter is made of 3 pieces of information
1. `member_size`: The size in bytes of each member in the parameter's `data` attribute.
2. `member_count`: The number of `member_size`-sized members in the parameter's `data` attribute.
3. `data`: An array containing `member_count` items that are each of size `member_size`.

A parameter is capable of representing a single piece of information (e.g. an int or a double), or an array of homogeneous elements (e.g. an array of ints or a string). 

**If hetergeneous data needs to be sent,** then several parameters should be used. 


# Calling Convention

The caller is always expected to ensure that the data is properly setup before calling the functions.

# Sending a Request to the Server

1. The client sends a request header to the server.
2. The server acknowledges the request header with OK or an error message. 
3. The client sends a parameter (or parameters) to the server.
4. The server acknowledges each individual parameter.
5. The server processes the information provided to send the requested data to the client.
6. The server sends a final response header to the client.
7. The client acknowledges the response header.
8. The server sends response parameters to the client. 
9. The client acknowledges each individual parameter.

## Sending a Request Header (Client)

This is done with 2 functions: `set_buffer_with_request_header(3)` and `send(4)`. 

`bool set_buffer_with_request_header(void *buffer, size_t *buffer_bytes_used, struct client_request_header *header)` deserializes the `client_request_header` struct passed to it and sets it into the `buffer` passed to it. The value held by `buffer_bytes_used` is updated so that the variable may be used with the `send(4)` function afterwards. The function returns false if something goes wrong and true otherwise.

The buffer is then set up to be used with `send(4)`.

`send(int sockfd, const void *buf, size_t length, int flags)` is used to send the request header to the server. The socket should already be known, and the `const void *buf` and `size_t length` parameters correspond to the `buffer` and `buffer_bytes_used` parameters previously passed into `set_buffer_with_request_header(3)`. The `flags` parameter can be usually be 0.'

Example
```c
struct client_request_header header;
header.request_type = GET_POST;
header.parameter_count = 1;
header.bytes_to_send = 11; // 1 byte for param count, 2 bytes for param size, 8 bytes for param (64 bit int for post id)

void *send_buffer = malloc(256);
if(send_buffer == NULL)
	exit(EXIT_FAILURE);
size_t send_buffer_bytes_used = 0;
size_t send_buffer_capacity = 256;

bool set_buffer_status;
set_buffer_status = set_buffer_with_request_header(send_buffer, &send_buffer_bytes_used, &header);
if(set_buffer_status == false)
	exit(EXIT_FAILURE);

int send_status;
send_status = send(socket, send_buffer, send_buffer_bytes_used, 0);
if(send_status < 0)
	exit(EXIT_FAILURE);
```
 
## Sending a Response Header (Server)

This is done with 2 functions: `set_buffer_with_response_header(4)` and `send(4)`.

`bool set_buffer_with_response_header(void *buffer, size_t *buffer_bytes_used, size_t *buffer_capacity, struct server_response_header *header)` deserializes the `server_response_header` struct passed to it and sets it into the `buffer` passed to it. The value held by `buffer_bytes_used` is updated so that the variable may be used with the `send(4)` function afterwards. The function returns false if something goes wrong and true otherwise.  
- The calling convention is the caller must ensure that the buffer is sufficiently large to deserialize the response header. This can be done with a simple `sizeof(enum server_response_header)` call when allocating the buffer.

The buffer is then set up to be used with `send(4)`. 

`send(int sockfd, const void *buf, size_t length, int flags)` is used to send the response header to the client. The client socket should already be known, and the `const void *buf` and `size_t length` parameters correspond to the `buffer` and `buffer_bytes_used` parameters previously passed into `set_buffer_with_response_header(4)`. The `flags` parameter can usually be 0. 

Example
```c
struct server_response_header header;
header.response_type = OK;
header.parameter_count = 0;
header.bytes_to_send = 0;

void *send_buffer = malloc(256);
if(send_buffer == NULL)
	exit(EXIT_FAILURE);
size_t send_buffer_bytes_used = 0;
size_t send_buffer_capacity = 256;

bool set_buffer_status;
set_buffer_status = set_buffer_with_response_header(send_buffer, &send_buffer_bytes_used, &send_buffer_capacity, &header);
if(set_buffer_status == false)
	exit(EXIT_FAILURE);

int send_status;
send_status = send(client_socket, send_buffer, send_buffer_bytes_used, 0);
if(send_status < 0)
	exit(EXIT_FAILURE);
```

## Sending Request Parameters (Client)

This is done with the function `client_send_parameters_to_server(3)`.

`bool client_send_parameters_to_server(int socket, struct message_parameter **parameters, size_t parameters_length)` is used to send the request parameters contained within `parameters` to the server. The function returns true if all of the parameters are received by the server and false otherwise.  

## Sending Response Parameters (Server)


