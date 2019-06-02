#include "../../include/services/sqlite3_db.h"
#include "../../include/services/user.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

#define USERS_TABLE_NAME "users"

SQLite3DB User::_db = SQLite3DB();

std::vector<User> User::index(){
    std::vector<std::map<std::string, std::string> > users_data = _db.index(USERS_TABLE_NAME);

    std::vector<User> users;

    for (std::map<std::string, std::string> user_data : users_data){
        User user;
    
        user._id = std::stoi(user_data["iod"]);
        user._name = user_data["NAME"];
        user._cpf = user_data["CPF"];
        user._email = user_data["EMAIL"];
        user._phone_number = user_data["PHONE_NUMBER"];
        user._address = user_data["ADDRESS"];
        user._gender = user_data["GENDER"][0];

        users.push_back(user);
    }

    return users;
}

User User::get(int id){
    std::map<std::string, std::string> user_data = _db.get(USERS_TABLE_NAME, id);

    User user;
    
    user._id = std::stoi(user_data["iod"]);
    user._name = user_data["NAME"];
    user._cpf = user_data["CPF"];
    user._email = user_data["EMAIL"];
    user._phone_number = user_data["PHONE_NUMBER"];
    user._address = user_data["ADDRESS"];
    user._gender = user_data["GENDER"][0];

    return user;
}

bool User::create(std::map<std::string, std::string> insert_params){
    return _db.create(USERS_TABLE_NAME, insert_params);
}

bool User::update(std::map<std::string, std::string> update_params, int id){
    return _db.update(USERS_TABLE_NAME, update_params, id);
}

bool User::destroy(int id){
    return _db.destroy(USERS_TABLE_NAME, id);
}