#include "../../include/services/sqlite3_db.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

std::map<std::string, std::string> SQLite3DB::get_return_values(){
    static std::map<std::string, std::string> get_return_values;
    return get_return_values;
}

std::vector< std::map<std::string, std::string> > SQLite3DB::index_return_values(){
    static std::vector< std::map<std::string, std::string> > index_return_values;
    return index_return_values;
}

SQLite3DB::SQLite3DB(){
    rc = sqlite3_open("pethero.db", &db);
    if( rc ) {
        std::cout << "Não é possível abrir o banco de dados!";
    } else {
        std::cout << "Abriu o banco com sucesso!" << std::endl;
    }
}

int SQLite3DB::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int SQLite3DB::get_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        std::string colName(azColName[i]);
        std::string colValue(argv[i] ? argv[i] : "NULL");

        get_return_values().insert(std::pair<std::string,std::string>(colName, colValue));
    }
    return 0;
}

int SQLite3DB::index_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    std::map<std::string, std::string> helper_map;

    for(i = 0; i<argc; i++) {
        std::string colName(azColName[i]);
        std::string colValue(argv[i] ? argv[i] : "NULL");

        helper_map.insert(std::pair<std::string,std::string>(colName, colValue));
    }

    index_return_values().push_back(helper_map);
    return 0;
}

std::vector< std::map<std::string, std::string> > SQLite3DB::index(std::string table_name){
    index_return_values().clear();
    std::string sql = "SELECT * FROM " + table_name;
    
    rc = sqlite3_exec(db, sql.c_str(), index_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::map<std::string, std::string> error_map;

        error_map["ERROR"] = zErrMsg;
        index_return_values().push_back(error_map);
        sqlite3_free(zErrMsg);
    }

    return index_return_values();
}

std::map<std::string, std::string> SQLite3DB::get(std::string table_name, int id){
    get_return_values().clear();
    std::string sql = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id);

    rc = sqlite3_exec(db, sql.c_str(), get_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        get_return_values().insert(std::pair<std::string,std::string>("ERROR", zErrMsg));
        sqlite3_free(zErrMsg);
    }

    return get_return_values();
}

bool SQLite3DB::create(std::string table_name, std::map<std::string, std::string> insert_params){
    std::string column_data = "", values_data = "";
    for (std::pair<std::string,std::string> pair : insert_params){
        column_data.append(pair.first + ",");
        values_data.append("'" + pair.second + "',");
    }

    column_data.pop_back();
    values_data.pop_back();

    std::string sql = "INSERT INTO " + table_name + 
    "(" + column_data + ") VALUES (" + values_data + ");";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

bool SQLite3DB::update(std::string table_name, std::map<std::string, std::string> insert_params, int id){
    std::string update_data = "";
    for (std::pair<std::string,std::string> pair : insert_params){
        update_data.append(pair.first + " = '" + pair.second + "',");
    }

    update_data.pop_back();

    std::string sql = "UPDATE " + table_name + " SET " +
    update_data + "WHERE id = " + std::to_string(id);
    ;

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

bool SQLite3DB::destroy(std::string table_name, int id){
    std::string sql = "DELETE FROM " + table_name + " WHERE id = " + std::to_string(id); 
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

SQLite3DB::~SQLite3DB(){
    sqlite3_close(db);
} 
