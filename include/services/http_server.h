#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

#include "sqlite3_db.h"

class HttpServer {
    private:
        int server_fd, new_socket; long valread;
        struct sockaddr_in address;
        int addrlen;
    public:
        HttpServer();

        void send_response();
};



#endif