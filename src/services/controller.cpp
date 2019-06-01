#include "../../include/services/controller.h"
#include "../../include/services/sqlite3_db.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void Controller::handle_request(const char *buffer, int socket){
    SQLite3DB db = SQLite3DB();

    std::map<std::string, std::string> map = db.get("COMPANY", 1);
    for (std::pair<std::string,std::string> pair : map){
        std::cout << pair.first << std::endl << pair.second << std::endl;
    }

    std::string buff(buffer);
    std::cout << buff << std::endl;
    std::istringstream iss(buff);

    // HTTP methods
    iss >> buff;
    std::string http_method = buff;

    // Filename
    iss >> buff;
    std::string filename = buff;

    if(filename == "/favicon.ico"){
        close(socket);
        return;
    }

    if(filename == "/")
        filename = "/index.html";

    // Remove slash from header
    filename.erase(0,1);

    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        close(socket);
        exit(1); // terminate with error
    }

    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";

    std::string helper_string = "";

    int file_character_count = 0;
    char ch;
    int i = 0;
    while(file.get(ch)) {
            i++;
            helper_string += ch;
    }

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