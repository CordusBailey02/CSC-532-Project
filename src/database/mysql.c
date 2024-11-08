#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mysql.h"


MYSQL *conn;


void mysql_cleanup()
{
    mysql_close(conn); 
}


int mysql_connection_init()
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
        fprintf(stderr, "[mysql_connection_init] %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    if(mysql_real_connect(conn, hostname, username, psw, db, port, unix_socket, client_flag) == NULL)
    {
        fprintf(stderr, "[mysql_connection_init] %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


char ***mysql_query(char *query_name, struct payload **inbound_payloads, int *return_flag, int *num_fields, int *num_rows)
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
        if(payload_length < 4)
        {
            query_length_check = true;
        }
        else
        {
            int j = snprintf(query, 100, "CALL add_new_user(\'%s\', \'%s\', \'%s\', \'%s\', 0, 0);",
                (char *) inbound_payloads[0]->data,
                (char *) inbound_payloads[1]->data,
                (char *) inbound_payloads[2]->data,
                (char *) inbound_payloads[3]->data);
        }
        
    }
    else if(query_name == "get_all_users")
    {
        int j = snprintf(query, 100, "CALL get_all_users();");
    }
    else if(query_name == "check_user")
    {
        int j = snprintf(query, 100, "CALL get_all_users(\'%s\');",
            (char *) inbound_payloads[0]->data);
    }
    else
    {
        printf("[mysql_query] No query found...");
        *return_flag = INEXISTENT_QUERY;
        return results_table;
    }

    if(query_length_check)
    {
        printf("[mysql_query] Inbound payload had an insuffucient amount of data.");
        *return_flag = INSUFFICIENT_PARAMETERS;
        return results_table;
    }

    printf("[mysql_query] Query: %s\n", query);
    
    if(mysql_query(conn, query))
    {
        printf("[mysql_query] Query Failed...\n");
        fprintf(stderr, "[mysql_query] Error: %s\n", mysql_error(conn));
        return results_table;
    }

    printf("[mysql_query] Query success...\n");

    // Now that the query has successfully completed, gather the results and return each row.
    
    MYSQL_RES *result;
    MYSQL_ROW row;
    unsigned int table_index = 0;

    result = mysql_store_result(conn);
    *num_rows = mysql_num_rows(result);
    *num_fields = mysql_num_fields(result);
    results_table = realloc(results_table, sizeof(row) * (*num_rows));

    if (result) 
    {
        printf("[mysql_query] Gathering result...\n");
        while ((row = mysql_fetch_row(result)) != 0)
        {
            results_table[table_index] = row;
            table_index = table_index + 1;
        }
    }
    else 
    {
        printf("[mysql_query] No result...\n");
        if(mysql_field_count(conn) == 0)
        {
            // *num_rows = mysql_affected_rows(conn);
            results_table[0][0] = "OK";
            return results_table;
        }
        else 
        {
            fprintf(stderr, "[mysql_query] Error: %s\n", mysql_error(conn));
            return results_table;
        }
    }

    return results_table;
}