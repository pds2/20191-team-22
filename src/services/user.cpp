#include "../../include/services/sqlite3_db.h"
#include "../../include/services/user.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

#define USERS_TABLE_NAME "users"

User::User(int id, std::string name, std::string cpf, std::string email, std::string phone_number, std::string address, char gender){
    _id = id;
    _name = name;
    _cpf = cpf;
    _email = email;
    _phone_number = phone_number;
    _address = address;
    _gender = gender;
}

std::vector<User> User::index(){
    std::vector<std::map<std::string, std::string> > users_data = _db.index(USERS_TABLE_NAME);

    std::vector<User> users;

    for (std::map<std::string, std::string> user_data : users_data){
        User user(
            std::stoi(user_data["iod"]),
            user_data["NAME"],
            user_data["CPF"],
            user_data["EMAIL"],
            user_data["PHONE_NUMBER"],
            user_data["ADDRESS"],
            user_data["GENDER"][0]
        );

        users.push_back(user);
    }

    return users;
}

User User::get(int id){
    std::map<std::string, std::string> user_data = _db.get(USERS_TABLE_NAME, id);

    User user(
            std::stoi(user_data["iod"]),
            user_data["NAME"],
            user_data["CPF"],
            user_data["EMAIL"],
            user_data["PHONE_NUMBER"],
            user_data["ADDRESS"],
            user_data["GENDER"][0]
        );

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