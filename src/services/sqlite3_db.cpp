#include "../../include/services/sqlite3_db.h"
#include "../../include/services/table_return.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

TableReturn &SQLite3DB::return_table(){
    static TableReturn table_return;
    return table_return;
}

bool SQLite3DB::create_tables(){
    std::string sql = "CREATE TABLE USERS("  \
      "ID             INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "CPF            TEXT    NOT NULL," \
      "EMAIL          TEXT    NOT NULL," \
      "PHONE_NUMBER   TEXT    NOT NULL," \
      "ADDRESS        TEXT    NOT NULL," \ 
      "GENDER         CHAR(1) NOT NULL," \ 
      "PASSWORD       TEXT    NOT NULL" \ 
       "); \
       CREATE TABLE ANIMALS("  \
      "ID             INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "COLOR          TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "HEIGHT         FLOAT   NOT NULL," \ 
      "WEIGHT         FLOAT   NOT NULL," \ 
      "USER_ROWID     INT   NOT NULL," \
      "FOREIGN KEY (USER_ROWID) REFERENCES users(id)" \  
       "); \
       CREATE TABLE INTERESTS("  \
      "USER_ROWID           INT    NOT NULL," \
      "ANIMAL_ROWID         INT    NOT NULL," \
      "FOREIGN KEY (USER_ROWID) REFERENCES users(id)" \ 
      "FOREIGN KEY (ANIMAL_ROWID) REFERENCES animals(id)" \
       "); \
       ";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK ){
        std::cout << zErrMsg << std::endl;
        return false;
    }

    return true;
}

void SQLite3DB::populate_tables(){
    std::string sql = "INSERT INTO users (name, cpf, email, phone_number, address, gender, password) VALUES("  \
        "'Douglas', '10191817188', 'oi@oi.com', '83788363927', 'daushdouasdn', 'M', 'TESTE'" \
        ");" \
        "INSERT INTO animals (name, type, color, age, height, weight, user_rowid) VALUES("  \
        "'Douglinhas', 'Cachorro', 'Preto', '3', '1', '4', '1'" \
        ");" ;

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    } else {
        std::cout << "Dados inseridos com sucesso!" << std::endl;
    }
}

SQLite3DB::SQLite3DB(){
    rc = sqlite3_open("pethero.db", &db);
    if( rc ) {
        std::cout << "Não é possível abrir o banco de dados!";
    } else {
        std::cout << "Abriu o banco com sucesso!" << std::endl;
    }
    create_tables();
    populate_tables();
}

// Method necessary for sqlite3.h returns
int SQLite3DB::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Method necessary for sqlite3.h returns
int SQLite3DB::get_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        std::string colName(azColName[i]);
        std::string colValue(argv[i] ? argv[i] : "NULL");

        TableReturn &table_return = return_table();

        table_return.get_return_values.insert(std::pair<std::string,std::string>(colName, colValue));
    }
    return 0;
}

// Method necessary for sqlite3.h returns
int SQLite3DB::index_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    std::map<std::string, std::string> helper_map;

    for(i = 0; i<argc; i++) {
        std::string colName(azColName[i]);
        std::string colValue(argv[i] ? argv[i] : "NULL");

        helper_map.insert(std::pair<std::string,std::string>(colName, colValue));
    }

    TableReturn &table_return = return_table();

    table_return.index_return_values.push_back(helper_map);
    return 0;
}

std::vector< std::map<std::string, std::string> > SQLite3DB::index(std::string table_name){
    TableReturn &table_return = return_table();

    // Clear previous query
    table_return.index_return_values.clear();
    std::string sql = "SELECT * FROM " + table_name;
    
    rc = sqlite3_exec(db, sql.c_str(), index_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::map<std::string, std::string> error_map;

        error_map["ERROR"] = zErrMsg;
        table_return.index_return_values.push_back(error_map);
        sqlite3_free(zErrMsg);
    }

    return table_return.index_return_values;
}

std::map<std::string, std::string> SQLite3DB::get(std::string table_name, int id){
    TableReturn &table_return = return_table();

    // Clear previous query
    table_return.get_return_values.clear();
    std::string sql = "SELECT * FROM " + table_name + " WHERE rowid = " + std::to_string(id);

    rc = sqlite3_exec(db, sql.c_str(), get_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        table_return.get_return_values.insert(std::pair<std::string,std::string>("ERROR", zErrMsg));
        sqlite3_free(zErrMsg);
    }

    return table_return.get_return_values;
}

bool SQLite3DB::create(std::string table_name, std::map<std::string, std::string> insert_params){
    std::string column_data = "", values_data = "";

    // Format for insert
    for (std::pair<std::string,std::string> pair : insert_params){
        column_data.append(pair.first + ",");
        values_data.append("'" + pair.second + "',");
    }

    column_data.pop_back();
    values_data.pop_back();

    std::string sql = "INSERT INTO " + table_name + 
    "(" + column_data + ") VALUES (" + values_data + ");";

    std::cout << sql << std::endl;
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

bool SQLite3DB::update(std::string table_name, std::map<std::string, std::string> insert_params, int id){
    std::string update_data = "";

    // Format for update
    for (std::pair<std::string,std::string> pair : insert_params){
        update_data.append(pair.first + " = '" + pair.second + "',");
    }

    update_data.pop_back();

    std::string sql = "UPDATE " + table_name + " SET " +
    update_data + "WHERE rowid = " + std::to_string(id);
    ;

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

bool SQLite3DB::destroy(std::string table_name, int id){
    std::string sql = "DELETE FROM " + table_name + " WHERE rowid = " + std::to_string(id); 
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        return false;
    } 

    return true;
}

std::vector< std::map<std::string, std::string> > SQLite3DB::get_where(std::string table_name, std::map<std::string, std::string> conditions, std::vector<std::map<std::string, std::string> > join_conditions){
    TableReturn &table_return = return_table();

    // Clear previous query
    table_return.index_return_values.clear();

    std::string update_data = "";
    std::string conditions_data = "";

    // Format conditions data
    for (std::pair<std::string,std::string> pair : conditions){
            update_data.append(pair.first + " = '" + pair.second + "' AND ");
    }

    update_data.erase(update_data.size() - 5, 5);

    // Format join data
    for(std::map<std::string, std::string> map : join_conditions){
        conditions_data.append(
            "JOIN " + map["join_table_name"] + " ON " +
            map["join_table_name"] + "." + map["join_table_attribute"] +
            " = " + 
            map["source_table_name"] + "." + map["source_table_attribute"] + " "
        );
    }

    std::string sql = "SELECT * FROM " + table_name + 
    conditions_data +
    " WHERE " + update_data;
    ;

    rc = sqlite3_exec(db, sql.c_str(), index_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::map<std::string, std::string> error_map;

        error_map["ERROR"] = zErrMsg;
        table_return.index_return_values.push_back(error_map);
        sqlite3_free(zErrMsg);
    }

    return table_return.index_return_values;
}

SQLite3DB::~SQLite3DB(){
    sqlite3_close(db);
} 
