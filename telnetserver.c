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

#define PORT        "6667"
#define BACKLOG     10
#define BUFFERSIZE  256
#define DO          "9397"
#define DONT        "9398"
#define WILL        "9830"
#define WONT        "9842"

        /********************************************************
         * telnetserver.c                                       *
         *                                                      *
         *                                                      *
         *                                                      *
         *                                                      *
         * sends player info to server                          *
         ********************************************************/

/*
 * Returns a socket bound to passive IP and specified port
 * Internet family unspecified
 * listen() has not been called on the returned socket
 */
int GetTCPListener(const char *port)
{
    int             listener,
                    rv;
    struct addrinfo hints,
                    *result,
                    *rp;
    //int yes=1; Unnecessary? We'll see!

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;        // Unspecified family
    hints.ai_socktype = SOCK_STREAM;    // TCP stream
    hints.ai_flags = AI_PASSIVE;        // Localhost IP
    hints.ai_protocol = 0;              // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    rv = getaddrinfo(NULL, port, &hints, &result);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rv));
        return -1;
    }

    // Loop through results, use first valid result
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        listener = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (listener == -1) {
            perror("Error on socket()\n");
            continue;
        }
        if ((rv = bind(listener, rp->ai_addr, rp->ai_addrlen)) == 0) {
            break;
        }
        perror("Error on bind()\n");
        close(listener);
    }

    // If none of the results were valid
    if (rp == NULL) {
        fprintf(stderr, "Could not allocate/bind listener socket\n");
        freeaddrinfo(result);
        return -1;
    }
    freeaddrinfo(result);
    return listener;
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    else
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int     listener,
            client,
            bytes,
            maxfd,
            rv,
            i;
    char    buffer[BUFFERSIZE],
            addrstr[INET6_ADDRSTRLEN];
    fd_set  all_fds,
            read_fds;

    struct sockaddr_storage client_address;
    socklen_t               address_len;

    // Allocating and binding socket
    listener = GetTCPListener(argv[1]);
    if (listener == -1) {
        fprintf(stderr, "Failed to initiate server\n");
        return -1;
    }

    // Start listening on the new socket
    rv = listen(listener, BACKLOG);
    if (rv == -1) {
        fprintf(stderr, "Failed to start listening on socket\n");
        return -1;
    }

    FD_ZERO(&all_fds);
    FD_ZERO(&read_fds);
    FD_SET(listener, &all_fds);
    maxfd = listener;  // listener is the only fd at this point
    
    while (1) {
        // Copy all fds into read_fds set, for use in select()
        read_fds = all_fds;

        // If read() will not block on a socket, keep it in read_fds
        // For listener, accept() will not block, read() is not an option
        rv = select(maxfd+1, &read_fds, NULL, NULL, NULL);
        if (rv == -1) {
            perror("Error on select()\n");
            continue;
        }

        for (i = 0; i <= maxfd; ++i) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener) {
                    client = accept(listener,
                                (struct sockaddr *)&client_address,
                                &address_len);
                    if (client == -1)
                        perror("Error on accept()\n");
                    else {
                        FD_SET(client, &all_fds);
                        if (client > maxfd)
                            maxfd = client;
                    }
                } else { // If i is a client file descriptor
                    memset(buffer, 0, sizeof buffer);
                    bytes = recv(i, buffer, sizeof buffer, 0);
                    if (bytes <= 0) {
                        if (bytes == 0)
                            printf("server: socket %d hung up\n", i);
                        else if (bytes < 0)
                            perror("Error on recv()\n");
                        close(i);
                        FD_CLR(i, &all_fds);
                    } else {
                        printf("Received: %s from client\n", buffer);
                        bytes = send(i, buffer, sizeof buffer, 0);
                        if (bytes == -1)
                            perror("Error on send()\n");
                        else if (bytes < sizeof buffer)
                            fprintf(stderr, "Not all bytes sent\n");
                    }

                }
            }
        }
    }
    for (i = 0; i <= maxfd; ++i)
        if (FD_ISSET(i, &all_fds))
            close(i);
    close(listener);
}
