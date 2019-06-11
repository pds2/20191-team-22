#include "../../include/services/sqlite3_db.h"
#include "../../include/services/animal.h"
#include "../../include/services/adopter.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

#define ANIMALS_TABLE_NAME "animals"
#define ANIMALS_TABLE_JOIN_ATTRIBUTE "id"

#define INTERESTS_TABLE_NAME "interests"
#define INTERESTS_TABLE_JOIN_ATTRIBUTE "user_rowid"

#define USERS_TABLE_NAME "users"
#define USERS_TABLE_JOIN_ATTRIBUTE "id"

Animal::Animal(int id, std::string name, std::string type, std::string color, int age, float height, float weight){
    _id = id;
    _name = name;
    _type = type;
    _color = color;
    _age = age;
    _height = height;
    _weight = weight;
}

std::vector<Animal> Animal::index(){
    std::vector<std::map<std::string, std::string> > animals_data = _db.index(ANIMALS_TABLE_NAME);

    std::vector<Animal> animals;

    for (std::map<std::string, std::string> animal_data : animals_data){
        Animal animal(
            std::stoi(animal_data["ID"]),
            animal_data["NAME"],
            animal_data["TYPE"],
            animal_data["COLOR"],
            std::stoi(animal_data["AGE"]),
            std::stof(animal_data["HEIGHT"]),
            std::stof(animal_data["WEIGHT"])
        );

        animals.push_back(animal);
    }

    return animals;
}

Animal Animal::get(int id){
    std::map<std::string, std::string> animal_data = _db.get(ANIMALS_TABLE_NAME, id);

    Animal animal(
        std::stoi(animal_data["ID"]),
        animal_data["NAME"],
        animal_data["TYPE"],
        animal_data["COLOR"],
        std::stoi(animal_data["AGE"]),
        std::stof(animal_data["HEIGHT"]),
        std::stof(animal_data["WEIGHT"])
    );

    return animal;
}

bool Animal::create(std::map<std::string, std::string> insert_params){
    return _db.create(ANIMALS_TABLE_NAME, insert_params);
}

bool Animal::update(std::map<std::string, std::string> update_params, int id){
    return _db.update(ANIMALS_TABLE_NAME, update_params, id);
}

bool Animal::destroy(int id){
    return _db.destroy(ANIMALS_TABLE_NAME, id);
}

std::vector<User> Animal::show_interested(){
    std::map<std::string, std::string> conditions;
    std::vector<std::map<std::string, std::string> > join_conditions;
    std::vector<User> interested;

    std::map<std::string, std::string> interests_join_conditions;

    conditions["interests.animal_rowid"] = std::to_string(this->_id);
    
    // JOIN interests ON interests.animal_rowid = animals.rowid 
    interests_join_conditions["join_table_name"] = INTERESTS_TABLE_NAME;
    interests_join_conditions["join_table_attribute"] = INTERESTS_TABLE_JOIN_ATTRIBUTE;
    interests_join_conditions["source_table_name"] = USERS_TABLE_NAME;
    interests_join_conditions["source_table_attribute"] = USERS_TABLE_JOIN_ATTRIBUTE;

    join_conditions.push_back(interests_join_conditions);

    std::vector< std::map<std::string, std::string> > adopters_vector = _db.get_where(USERS_TABLE_NAME, conditions, join_conditions);

    for (std::map<std::string, std::string> adopter_data : adopters_vector){
        for (std::pair<std::string, std::string> pair : adopter_data){
            std::cout << pair.first << " |||||| " << pair.second << std::endl;
        }
        User adopter = User::get(std::stoi(adopter_data["ID"]));

        interested.push_back(adopter);
    }

    return interested;
}

std::map<std::string, std::string> Animal::to_map(){
    std::map<std::string, std::string> attribute_map;

    attribute_map["ID"] = std::to_string(this->_id);
    attribute_map["NAME"] = this->_name;
    attribute_map["TYPE"] = this->_type;
    attribute_map["COLOR"] = this->_color;
    attribute_map["AGE"] = std::to_string(this->_age);
    attribute_map["HEIGHT"] = std::to_string(this->_height);
    attribute_map["WEIGHT"] = std::to_string(this-> _weight);

    return attribute_map;
}