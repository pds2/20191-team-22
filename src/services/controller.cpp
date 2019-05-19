#include "../../include/services/controller.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

void Controller::handle_request(const char *buffer, int socket){
    std::string buff(buffer);
    std::cout << buff << std::endl;
    std::istringstream iss(buff);

    // HTTP methods
    iss >> buff;
    std::string http_method = buff;

    // Filename
    iss >> buff;
    std::string filename = buff;

    if(filename == "/")
        filename = "/index.html";

    // Remove slash from header
    filename.erase(0,1);

    std::fstream file;
    file.open(filename);

    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";

    std::string helper_string = "";

    int file_character_count = 0;
    char ch;
    int i = 0;
    while(!file.eof())
        {
            file.get(ch);
            i++;
            helper_string += ch;
        }

    // Remove duplicate char at end of string
    helper_string.erase(helper_string.length() - 2, helper_string.length() - 1);

    hello.append(std::to_string(i));
    hello.append("\n\n");
    hello.append(helper_string);
    
    file.close();

    const char *cstr = hello.c_str();
    // printf("%s\n", buffer);
    write(socket , cstr , hello.length());
    printf("------------------Hello message sent-------------------");
    close(socket);
}