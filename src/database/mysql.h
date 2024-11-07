#include <stdlib.h>
#include <stdint.h>

enum DATABASE_ERROR { SUCCESS, CONNECTION_ERROR, INEXISTENT_QUERY, INSUFFICIENT_PARAMETERS};

int connection_innit(void);

char ***query_mysql(char *query_name, struct payload **inbound_payloads, int *return_flag, int *num_fields, int *num_rows);

