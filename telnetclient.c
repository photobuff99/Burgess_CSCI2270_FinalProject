#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define HOST        "127.0.0.1"
#define PORT        "6667"
#define BUFFERSIZE  256
#define DO          "9397"
#define DONT        "9398"
#define WILL        "9830"
#define WONT        "9842"

        /********************************************************
         * telnetclient.c                                       *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         * Runs expGame here, waits for state, sends state to   *
         * server, server sends back updated state, repeat      *
         ********************************************************/

/*
 * Returns a socket connected to the specified host/port
 * Internet family unspecified
 * connect() is attempted
 */
int GetTCPConnection(const char *host, const char *port)
{
    int             socketfd,
                    rv;
    struct addrinfo hints,
                    *result,
                    *rp; 

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    rv = getaddrinfo(host, port, &hints, &result);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rv));
        return -1;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        socketfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (socketfd == -1)
            continue;
        if (connect(socketfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;
        close(socketfd);
    }
    if (rp == NULL) {
        fprintf(stderr, "Could not allocate socket/connect\n");
        freeaddrinfo(result);
        return -1;
    }
    freeaddrinfo(result);
    return socketfd;
}

int main(int argc, char *argv[])
{
    int     connection,
            bytes,
            rv;
    char    buffer[BUFFERSIZE];

    memset(buffer, 0, sizeof buffer);
    fgets(buffer, sizeof buffer, stdin);
    buffer[sizeof buffer -1] = 0;
    printf("echo: %s\n", buffer);
    
    //connection = GetTCPConnection(argv[1], argv[2]);
    connection = GetTCPConnection(HOST, PORT);
    if (connection == -1)
        return -1;
    bytes = send(connection, buffer, sizeof buffer, 0);
    if (bytes < sizeof buffer) {
        if (bytes == -1)
            perror("Error on send()\n");
        else
            fprintf(stderr, "Not all bytes sent\n");
    }
    bytes = recv(connection, buffer, sizeof buffer, 0);
    buffer[bytes] = '\0';
    printf("%s\n", buffer);
    close(connection);
}
