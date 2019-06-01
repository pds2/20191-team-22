#ifndef SQLITE3_DB_H
#define SQLITE3_DB_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <map>
#include <vector>
#include "sqlite3_interface.h"

class SQLite3DB : public SQLite3Interface {
    private: 
        sqlite3 *db;
        char *zErrMsg;
        int rc;
        const char* data;
        static std::map<std::string, std::string> get_return_values();
        static std::vector< std::map<std::string, std::string> > index_return_values();
    public:
        SQLite3DB();

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
        static int get_callback(void *NotUsed, int argc, char **argv, char **azColName);
        static int index_callback(void *NotUsed, int argc, char **argv, char **azColName);

        virtual std::vector<std::map<std::string, std::string> > index(std::string table_name);
        virtual std::map<std::string, std::string> get(std::string table_name, int id);
        virtual bool create(std::string table_name, std::map<std::string, std::string> insert_params);
        virtual bool update(std::string table_name, std::map<std::string, std::string> insert_params, int id);
        virtual bool destroy(std::string table_name, int id);

        ~SQLite3DB(); 
};

#endif