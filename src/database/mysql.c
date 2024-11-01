#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/terrorexchange.h"


MYSQL *conn;


void cleanup()
{
    mysql_close(conn); 
}


int connection_init()
{
    const char *hostname = getenv("SQL_HOSTNAME");
    const char *username = getenv("SQL_USERNAME");
    const char *psw = getenv("SQL_PASSWORD");
    const char *db = getenv("SQL_DB");
    const unsigned int port = 25060;
    const char *unix_socket = NULL;
    const unsigned long client_flag = 0;
    conn = mysql_init(NULL);

    if(conn == NULL)
    {
        fprintf(stderr, "\n%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    if(mysql_real_connect(conn, hostname, username, psw, db, port, unix_socket, client_flag) == NULL)
    {
        fprintf(stderr, "\n%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


char ***query_mysql(char *query_name, struct payload **inbound_payloads, int *return_flag, int *num_fields, int *num_rows)
{
    char query[100];

    size_t payload_length = inbound_payloads[0]->member_count;
    bool query_length_check = false;
    char ***results_table = malloc(num_fields[0] * num_rows[0] + 10);
    results_table[0][0] = "NULL";

    // reset return_flag, num_fields, num_rows
    *return_flag = SUCCESS;
    *num_fields = 0;
    *num_rows = 0;

    if(connection_init())
    {
        printf("\nConnection Failed...\n");
        *return_flag = CONNECTION_ERROR;
        return results_table;
    }

    printf("\nConnection success...\n");


    // Check the given query name and send a call to MYSQL run the corresponding 
    // stored procedure.
    if(query_name == "get_categories_from_user")
    {

        int j = snprintf(query, 100, "CALL get_categories_from_user(\'%s\');",
            (char *) inbound_payloads[0]->data);
    }
    else if(query_name == "add_user_category")
    {
        if(payload_length < 2)
        {
            query_length_check = true;
        }
        else
        {
            int j = snprintf(query, 100, "CALL add_user_category(\'%s\', \'%d\');",
                (char *) inbound_payloads[0]->data,
                atoi(inbound_payloads[1]->data));
        }
    }
    else if(query_name == "get_user_reports")
    {
        int j = snprintf(query, 100, "CALL add_user_category(\'%s\');",
            (char *) inbound_payloads[0]);
    }
    else if(query_name == "add_new_category")
    {
        int j = snprintf(query, 100, "CALL add_new_category(\'%s\');",
            (char *) inbound_payloads[0]);
    }
    else if(query_name == "add_new_user")
    {
        if(payload_length < 2)
        {
            query_length_check = true;
        }
        else
        {
            int j = snprintf(query, 100, "CALL add_new_user(\'%s\', \'%s\', \'%s\', 0, 0);",
                (char *) inbound_payloads[0]->data,
                (char *) inbound_payloads[1]->data,
                (char *) inbound_payloads[2]->data);
        }
        
    }
    else if(query_name == "get_all_users")
    {
        int j = snprintf(query, 100, "CALL get_all_users();");
    }
    else
    {
        printf("No query found...");
        *return_flag = INEXISTENT_QUERY;
        return results_table;
    }

    if(query_length_check)
    {
        printf("Inbound payload had an insuffucient amount of data.");
        *return_flag = INSUFFICIENT_PARAMETERS;
        return results_table;
    }

    printf("\nQuery: %s\n", query);
    
    if(mysql_query(conn, query))
    {
        printf("\nQuery Failed...\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return results_table;
    }

    printf("\nQuery success...\n");

    // Now that the query has successfully completed, gather the results and return each row.
    
    MYSQL_RES *result;
    MYSQL_ROW row;
    unsigned int table_index = 0;

    result = mysql_store_result(conn);
    *num_rows = mysql_num_rows(result);
    *num_fields = mysql_num_fields(result);
    results_table = realloc(results_table, sizeof(row) * *num_rows);

    if (result) 
    {
        printf("\nWe have result...\n");
        while ((row = mysql_fetch_row(result)) != 0)
        {
            results_table[table_index] = row;
        }
    }
    else 
    {
        printf("\nNo result...\n");
        if(mysql_field_count(conn) == 0)
        {
            // *num_rows = mysql_affected_rows(conn);
            results_table[0][0] = "OK";
            return results_table;
        }
        else 
        {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            return results_table;
        }
    }

    return results_table;
}



int main(int argc, char **argv)
{
    char *result;

    // char *data[] = {"test", "first", "last"};

    // result = query_mysql("add_new_user", data);

    // char *user_data[] = {"user2", "user", "2"};

    // result = query_mysql("add_new_user", user_data);

    // char *empty[] = {};

    // result = query_mysql("get_all_users", empty);

    cleanup();
       
    return EXIT_SUCCESS;
}
