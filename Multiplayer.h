#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H
#include <iostream>
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

struct TurnInfo
{
    bool    yourTurn;
    int     otherPlayerVertex;
};

struct InitialPositions
{
    int player1;
    int player2;
};

class Connection
{
  private:
    int server;
  public:
    Connection(const char *host, const char *port);
   ~Connection();
    InitialPositions GetInitialPositions();
    TurnInfo GetTurnInfo();
    void SendPosition(int vertex);
    inline bool IsValid() { return server ? true : false; }

};

Connection::Connection(const char *host, const char *port)
{
    server = GetTCPConnection(host, port);
    if (server == -1)
        std::cout << "Error connecting to server" << std::endl;
}
Connection::~Connection()
{
    if (IsValid())
        close(server);
}

InitialPositions GetInitialPositions()
{
    
}

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


#endif
