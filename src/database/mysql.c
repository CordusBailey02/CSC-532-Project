#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


MYSQL *conn;

void cleanup()
{
    mysql_close(conn); 
}


int connection_init()
{
    conn = mysql_init(NULL);

    if(conn == NULL)
    {
        fprintf(stderr, "\n%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    if(mysql_real_connect(conn, hostname, username, psw, db, port, unix_socket, client_flag) == NULL)
    {
        fprintf(stderr, "\n%s\n", mysql_error(conn));
        // mysql_close(conn);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


char *query_mysql(char *query_name, char **data)
{
    // Example of setup

    // char *data[] = {username, firstname, lastname};

    // fail = query_mysql(query_name, data);

    char query[100];
    MYSQL_RES *result;
    MYSQL *mysql;
    unsigned int num_rows;
    unsigned int num_fields;
    char *result_string;

    if(connection_init())
    {
        printf("\nConnection Failed...\n");
        return "NULL";
    }

    printf("\nConnection success...\n");

    if(query_name == "get_categories_from_user")
    {
        int j = snprintf(query, 100, "CALL get_categories_from_user(\'%s\');", data[0]);
    }
    else if(query_name == "add_user_category")
    {
        int j = snprintf(query, 100, "CALL add_user_category(\'%s\', \'%d\');", data[0], atoi(data[1]));
    }
    else if(query_name == "get_user_reports")
    {
        int j = snprintf(query, 100, "CALL add_user_category(\'%s\');", data[0]);
    }
    else if(query_name == "add_new_category")
    {
        int j = snprintf(query, 100, "CALL add_new_category(\'%s\');", data[0]);
    }
    else if(query_name == "add_new_user")
    {
        int j = snprintf(query, 100, "CALL add_new_user(\'%s\', \'%s\', \'%s\', 0, 0);", data[0], data[1], data[2]);
    }
    else
    {
        printf("No query found...");
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

    result = mysql_store_result(conn);

    if (result) 
    {
        printf("\nWe have result...\n");
        MYSQL_ROW row;
        num_fields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result)) != 0)
        {
            unsigned long *lengths;
            int i;

            lengths = mysql_fetch_lengths(result);
            for(i = 0; i < num_fields; i++)
            {
                strcat(result_string, row[i] ? row[i] : "NULL");
                strcat(result_string, ",");
                printf("[%s] ", result_string);
            }
            printf("\n");
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

    return result_string;
}



int main(int argc, char **argv)
{
    int fail;

    cleanup();
       
    return EXIT_SUCCESS;
}
