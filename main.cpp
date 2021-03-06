#include "include/services/http_server.h"
#include "include/services/controller.h"
#include "include/services/sqlite3_interface.h"
#include "include/services/sqlite3_db.h"

#include "include/services/animal.h"
#include "include/services/user.h"

/// Singleton DB
SQLite3DB db = SQLite3DB();

SQLite3DB Animal::_db = db; /// Set DB for Animal queries
SQLite3DB User::_db = db; /// Set DB for User queries

/*! \mainpage Main page
 *
 * In this doc, you will find information about
 * the functions of the program and the data behind it.
 * For more general information, please check out the README.md
 * or the main GitHub page.
 *
 */

int main(int argc, char const *argv[])
{   
    HttpServer();  
    return 0;
}