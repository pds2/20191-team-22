#include "../../include/services/controller.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>

void Controller::handle_request(const char *buffer, int socket){

    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 21\n\n<h1>Hello world!</h1>";

    std::string buff(buffer);
    std::cout << buff << std::endl;
    std::istringstream iss(buff);

    iss >> buff;
    std::cout << buff << std::endl;
    iss >> buff;
    std::cout << buff << std::endl;

    // printf("%s\n", buffer);
    write(socket , hello , strlen(hello));
    printf("------------------Hello message sent-------------------");
    close(socket);
}