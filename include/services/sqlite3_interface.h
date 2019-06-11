#ifndef SQLITE3_INTERFACE_H
#define SQLITE3_INTERFACE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

class SQLite3Interface {
    public:
        virtual std::vector<std::map<std::string, std::string> > index(std::string table_name) = 0;
        virtual std::map<std::string, std::string> get(std::string table_name, int id) = 0;
        virtual bool create(std::string table_name, std::map<std::string, std::string> insert_params) = 0;
        virtual bool update(std::string table_name, std::map<std::string, std::string> insert_params, int id) = 0;
        virtual bool destroy(std::string table_name, int id) = 0;

        virtual std::vector<std::map<std::string, std::string> > get_where(std::string table_name, std::map<std::string, std::string> conditons, std::vector<std::map<std::string, std::string> > join_conditions) = 0;
        virtual std::vector< std::map<std::string, std::string> > where_in(std::string table_name, std::map<std::string, std::string> conditions, std::vector<std::map<std::string, std::string> > join_conditions) = 0;
};

#endif