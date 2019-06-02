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

SQLite3DB Animal::_db = SQLite3DB();

std::vector<Animal> Animal::index(){
    std::vector<std::map<std::string, std::string> > animals_data = _db.index(ANIMALS_TABLE_NAME);

    std::vector<Animal> animals;

    for (std::map<std::string, std::string> animal_data : animals_data){
        Animal animal;
    
        animal._id = std::stoi(animal_data["iod"]);
        animal._name = animal_data["NAME"];
        animal._type = animal_data["TYPE"];
        animal._color = animal_data["COLOR"];
        animal._age = std::stoi(animal_data["AGE"]);
        animal._height = std::stof(animal_data["HEIGHT"]);
        animal._weight = std::stof(animal_data["WEIGHT"]);

        animals.push_back(animal);
    }

    return animals;
}

Animal Animal::get(int id){
    std::map<std::string, std::string> animal_data = _db.get(ANIMALS_TABLE_NAME, id);

    Animal animal;
    
    animal._id = std::stoi(animal_data["iod"]);
    animal._name = animal_data["NAME"];
    animal._type = animal_data["TYPE"];
    animal._color = animal_data["COLOR"];
    animal._age = std::stoi(animal_data["AGE"]);
    animal._height = std::stof(animal_data["HEIGHT"]);
    animal._weight = std::stof(animal_data["WEIGHT"]);

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

std::vector<Adopter> Animal::show_interested(){
    std::map<std::string, std::string> conditions;
    std::vector<std::map<std::string, std::string> > join_conditions;
    std::vector<Adopter> interested;

    std::map<std::string, std::string> interests_join_conditions;

    conditions["interests.animal_oid"] = this->_id;
    
    interests_join_conditions["join_table_name"] = "INTERESTS";
    interests_join_conditions["join_table_attribute"] = "animal_oid";
    interests_join_conditions["source_table_name"] = ANIMALS_TABLE_NAME;
    interests_join_conditions["join_table_name"] = "oid";

    join_conditions.push_back(interests_join_conditions);

    std::vector< std::map<std::string, std::string> > adopters_vector = _db.get_where("users", conditions, join_conditions);

    for (std::map<std::string, std::string> adopter_data : adopters_vector){
        Adopter adopter = Adopter();
        adopter.get(std::stoi(adopter_data["iod"]));

        interested.push_back(adopter);
    }

    return interested;
}