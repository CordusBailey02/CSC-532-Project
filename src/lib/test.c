#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "secure_connection.h" 

int main(int argc, char **argv)
{
	if(argc < 3)
		exit(EXIT_FAILURE);
	
	uint32_t key = (uint32_t) atoi(argv[1]);
	int data_length = strlen(argv[2]) + 1;
	char *data = malloc(data_length); 
	if(data == NULL ) exit(EXIT_FAILURE);
	strcpy(data, argv[2]);
	printf("\"%s\" -> ", data);	
	// encrypt
	xor_encrypt_decrypt( (uint8_t *) data, data_length, (uint8_t *) &key, sizeof(key));
	printf("%hhu\n", (uint8_t) *data); 
	// decrypt
	printf("%hhu -> ", (uint8_t) *data); 
	xor_encrypt_decrypt( (uint8_t *) data, data_length, (uint8_t *) &key, sizeof(key));	
	printf("\"%s\"", data);	
	free(data);
	return 0;
}
