#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


MYSQL *conn;

enum DATABASE_ERROR
{
    INEXISTENT_QUERY,
    INSUFFICIENT_PARAMETERS,
    CONNECTION_ERROR
}

void cleanup()
{
    mysql_close(conn); 
}


int connection_init()
{
    const char *hostname = $SQL_HOSTNAME;
    const char *username = $SQL_USERNAME;
    const char *psw = $SQL_PASSWORD;
    const char *db = $SQL_DB;
    const unsigned int port = $SQL_PORT;
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

    if(connection_init())
    {
        printf("\nConnection Failed...\n");
        &return_flag = CONNECTION_ERROR;
        return "NULL";
    }

    printf("\nConnection success...\n");


    // Check the given query name and send a call to MYSQL run the corresponding 
    // stored procedure.
    if(query_name == "get_categories_from_user")
    {

        int j = snprintf(query, 100, "CALL get_categories_from_user(\'%s\');",
            inbound_payloads[0]->data);
    }
    else if(query_name == "add_user_category")
    {
        if(payload_length < 2)
        {
            query_length_check = true;
            break;
        }
        int j = snprintf(query, 100, "CALL add_user_category(\'%s\', \'%d\');",
            inbound_payloads[0]->data,
            atoi(inbound_payloads[1]->data));
    }
    else if(query_name == "get_user_reports")
    {
        int j = snprintf(query, 100, "CALL add_user_category(\'%s\');",
            inbound_payloads[0]);
    }
    else if(query_name == "add_new_category")
    {
        int j = snprintf(query, 100, "CALL add_new_category(\'%s\');",
            inbound_payloads[0]);
    }
    else if(query_name == "add_new_user")
    {
        if(payload_length < 2)
        {
            query_length_check = true;
            break;
        }
        int j = snprintf(query, 100, "CALL add_new_user(\'%s\', \'%s\', \'%s\', 0, 0);",
            inbound_payloads[0]->data,
            inbound_payloads[1]->data,
            inbound_payloads[2]->data);
    }
    else if(query_name == "get_all_users")
    {
        int j = snprintf(query, 100, "CALL get_all_users();");
    }
    else
    {
        printf("No query found...");
        &return_flag = INEXISTANT_QUERY;
        return "NULL";
    }

    if(query_length_check)
    {
        printf("Inbound payload had an insuffucient amount of data.");
        &return_flag = INSUFFICIENT_PARAMETERS;
        return "NULL";
    }

    printf("\nQuery: %s\n", query);
    
    if(mysql_query(conn, query))
    {
        printf("\nQuery Failed...\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return "NULL";
    }

    printf("\nQuery success...\n");

    // Now that the query has successfully completed, gather the results and return each row.
    
    unsigned int num_rows;
    MYSQL_RES *result;
    MYSQL_ROW row;
    unsigned int table_index = 0;

    result = mysql_store_result(conn);
    uint64_t *num_rows = mysql_num_rows(result);
    char ***results_table = malloc(sizeof(row*) * num_rows);

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
            num_rows = mysql_affected_rows(conn);
            return "OK";
        }
        else 
        {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            return "NULL";
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
