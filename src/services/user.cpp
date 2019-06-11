#include "../../include/services/sqlite3_db.h"
#include "../../include/services/user.h"
#include "../../include/services/animal.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

#define USERS_TABLE_NAME "users"
#define ANIMALS_TABLE_NAME "animals"
#define INTERESTS_TABLE_NAME "interests"

User::User(int id, std::string name, std::string cpf, std::string email, std::string phone_number, std::string address, char gender, std::string password){
    _id = id;
    _name = name;
    _cpf = cpf;
    _email = email;
    _phone_number = phone_number;
    _address = address;
    _gender = gender;
    _password = password;
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

string User::get_password(){
    return this->_password;
}

std::vector<User> User::index(){
    std::vector<std::map<std::string, std::string> > users_data = _db.index(USERS_TABLE_NAME);

    std::vector<User> users;

    for (std::map<std::string, std::string> user_data : users_data){
        User user(
            std::stoi(user_data["id"]),
            user_data["NAME"],
            user_data["CPF"],
            user_data["EMAIL"],
            user_data["PHONE_NUMBER"],
            user_data["ADDRESS"],
            user_data["GENDER"][0],
            user_data["PASSWORD"]
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
            user_data["GENDER"][0],
            user_data["PASSWORD"]
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

bool User::login(std::string email, std::string password){
    std::map<std::string, std::string> user_data;
    user_data["EMAIL"] = email;
    user_data["PASSWORD"] = password;

    std::vector< std::map<std::string, std::string> > data = _db.get_where(USERS_TABLE_NAME, user_data);

    if (data.empty()){
        return false;
    }
    return true;
}

std::vector<Animal> User::animals(){
    std::vector<Animal> animals;
    std::map<std::string, std::string> helper_map;
    helper_map["USER_ROWID"] = std::to_string(this->_id);

    // Return user animals in map form
    std::vector< std::map<std::string, std::string> > helper_vector = _db.get_where(ANIMALS_TABLE_NAME, helper_map);

    for(std::map<std::string, std::string> map : helper_vector){
        if (map["ERROR"] != "")
            break;

        Animal animal = Animal::get(std::stoi(map["ID"]));
        animals.push_back(animal);
    }

    return animals;
}

std::vector<Animal> User::liked_animals(){
    std::vector<Animal> animals;
    std::map<std::string, std::string> helper_map;
    helper_map["USER_ROWID"] = std::to_string(this->_id);

    std::vector< std::map<std::string, std::string> > helper_vector = _db.get_where(INTERESTS_TABLE_NAME, helper_map);
    for(std::map<std::string, std::string> map : helper_vector){
        if (map["ERROR"] != "")
            break;

        Animal animal = Animal::get(std::stoi(map["ANIMAL_ROWID"]));
        animals.push_back(animal);
    }

    return animals;
}


// Method to simplify user output to views
std::map<std::string, std::string> User::to_map(){
    std::map<std::string, std::string> attribute_map;

    attribute_map["ID"] = std::to_string(this->_id);
    attribute_map["NAME"] = this->_name;
    attribute_map["CPF"] = this->_cpf;
    attribute_map["EMAIL"] = this->_email;
    attribute_map["PHONE_NUMBER"] = this->_phone_number;
    attribute_map["ADDRESS"] = this->_address;
    attribute_map["GENDER"] = this->_gender;
    attribute_map["PASSWORD"] = this->_password;

    return attribute_map;
}