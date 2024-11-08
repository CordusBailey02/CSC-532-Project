#include <stdlib.h>
#include <stdint.h>
#include "../lib/terrorexchange.h"

#ifndef TERRORBASE_H
#define TERRORBASE_H 

enum DATABASE_ERROR { SUCCESS, CONNECTION_ERROR, INEXISTENT_QUERY, INSUFFICIENT_PARAMETERS};

void mysql_cleanup();

int mysql_connection_init(void);

char ***mysql_database_query(char *query_name, struct payload **inbound_payloads, int *return_flag, int *num_fields, int *num_rows);

#endif
