#include "mainwindow.h"
#include <QApplication>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define CLIENT_PROCESS_ADDR "127.0.0.1"

int main(int argc, char *argv[])
{
    // Establish connection to client process
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket < 0)
    {
        fprintf(stderr, "Failed to create socket.\n");
        exit(EXIT_FAILURE); // performs cleanup
    }

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(55000); // tcp port
    client_addr.sin_addr.s_addr = inet_addr(CLIENT_PROCESS_ADDR);

    if(connect(tcp_socket, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0)
    {
        fprintf(stderr, "Connection to client failed.\n");
        close(tcp_socket);
        exit(EXIT_FAILURE); // performs cleanup as well
    }

    printf("Client connection established.\n\n");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_ADDR "127.0.0.1"

// Establish connection to client process
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket < 0)
    {
        fprintf(stderr, "Failed to create socket.\n");
        exit(EXIT_FAILURE); // performs cleanup
    }

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(55000); // tcp port
    client_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if(connect(tcp_socket, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0)
    {
        fprintf(stderr, "Connection to client failed.\n");
        close(tcp_socket);
        exit(EXIT_FAILURE); // performs cleanup as well
    }

    printf("Client connection established.\n\n");
*/
