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

int User::get_id(){
    return this->_id;
}

std::string User::get_name(){
    return this->_name;
}

std::string User::get_cpf(){
    return this->_cpf;
}

std::string User::get_email(){
    return this->_email;
}

std::string User::get_phone_number(){
    return this->_phone_number;
}

std::string User::get_address(){
    return this->_address;
}

char User::get_gender(){
    return this->_gender;
}

std::vector<User> User::index(){
    std::vector<std::map<std::string, std::string> > users_data = _db.index(USERS_TABLE_NAME);

    std::vector<User> users;

    for (std::map<std::string, std::string> user_data : users_data){
        User user(
            std::stoi(user_data["row_id"]),
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
            id,
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