#include "../../include/services/controller.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <sqlite3.h> 
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void Controller::handle_request(const char *buffer, int socket){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("pethero.db", &db);

    if( rc ) {
        std::cout << "Can't open database!";
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    /* Create SQL statement */
    // std::string sql = "CREATE TABLE COMPANY("  \
    //     "ID INT PRIMARY KEY     NOT NULL," \
    //     "NAME           TEXT    NOT NULL," \
    //     "AGE            INT     NOT NULL," \
    //     "ADDRESS        CHAR(50)," \
    //     "SALARY         REAL );";

    // /* Execute SQL statement */
    // rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    
    // if( rc != SQLITE_OK ){
    //     std::cout << "SQL Error: " << zErrMsg << std::endl;
    //     sqlite3_free(zErrMsg);
    // } else {
    //     std::cout << "Table created successfully" << std::endl;
    // }

    // std::string sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
    //      "VALUES (5, 'Joao Pedro', 20, 'Rua Dias Adorno, 52', 100000.00 );";

    // rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    
    // if( rc != SQLITE_OK ){
    //     std::cout << "SQL Error: " << zErrMsg << std::endl;
    //     sqlite3_free(zErrMsg);
    // } else {
    //     std::cout << "Records created successfully" << std::endl;
    // }

    const char* data = "Callback function called";

    /* Create SQL statement */
    std::string sql = "SELECT * from tracks";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        std::cout << "SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Operation done successfully" << std::endl;
    }

    sqlite3_close(db);

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