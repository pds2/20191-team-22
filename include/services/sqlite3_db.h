#ifndef SQLITE3_DB_H
#define SQLITE3_DB_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <map>
#include <vector>
#include "sqlite3_interface.h"
#include "table_return.h"

class SQLite3DB : public SQLite3Interface {
    private: 
        sqlite3 *db;
        char *zErrMsg;
        int rc;
        const char* data;
    public:
        SQLite3DB();

        // DB initialization methods
        bool create_tables();
        void populate_tables();

        static TableReturn &return_table();

        // Callback methods for SQLite3 
        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
        static int get_callback(void *NotUsed, int argc, char **argv, char **azColName);
        static int index_callback(void *NotUsed, int argc, char **argv, char **azColName);

        // Main methods for SQL data manipulation
        virtual std::vector<std::map<std::string, std::string> > index(std::string table_name);
        virtual std::map<std::string, std::string> get(std::string table_name, int id);
        virtual bool create(std::string table_name, std::map<std::string, std::string> insert_params);
        virtual bool update(std::string table_name, std::map<std::string, std::string> insert_params, int id);
        virtual bool destroy(std::string table_name, int id);

        virtual std::vector< std::map<std::string, std::string> > get_where(std::string table_name, std::map<std::string, std::string> conditions, std::vector<std::map<std::string, std::string> > join_conditions = std::vector<std::map<std::string, std::string> >());
        virtual std::vector< std::map<std::string, std::string> > where_in(std::string table_name, std::map<std::string, std::string> conditions, std::vector<std::map<std::string, std::string> > join_conditions = std::vector<std::map<std::string, std::string> >());

        ~SQLite3DB(); 
};

#endif