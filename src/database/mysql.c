#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    MYSQL *conn = mysql_init(NULL);

    if(conn == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    if(mysql_real_connect(conn, hostname, username, psw, db, port, unix_socket, client_flag) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    mysql_close(conn);    
    return EXIT_SUCCESS;
}