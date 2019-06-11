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

#define USERS_TABLE_NAME "users"
#define USERS_TABLE_JOIN_ATTRIBUTE "rowid"

#define INTERESTS_TABLE_NAME "interests"
#define INTERESTS_TABLE_JOIN_ATTRIBUTE "user_rowid"

bool Adopter::register_interest(int animal_id){
    std::map<std::string, std::string> insert_params;
    insert_params["user_rowid"] = std::to_string(_id);
    insert_params["animal_rowid"] = std::to_string(animal_id);

    return _db.create(INTERESTS_TABLE_NAME, insert_params);
}

std::vector<Animal> Adopter::show_interests(){
    std::map <std::string, std::string> conditions;
    std::vector <std::map<std::string, std::string> > join_conditions;
    std::vector <Animal>  interests;

    std::map<std::string, std::string> interests_join_conditions;

    conditions["interests.users_rowid"] = std::to_string(this->_id);
    
    // JOIN interests ON interests.user_rowid = users.rowid 
    interests_join_conditions["join_table_name"] = INTERESTS_TABLE_NAME;
    interests_join_conditions["join_table_attribute"] = INTERESTS_TABLE_JOIN_ATTRIBUTE;
    interests_join_conditions["source_table_name"] = USERS_TABLE_NAME;
    interests_join_conditions["source_table_attribute"] = USERS_TABLE_JOIN_ATTRIBUTE;

    join_conditions.push_back(interests_join_conditions);

    // Vector full of animal data
    std::vector< std::map<std::string, std::string> > animals_vector = _db.get_where(ANIMALS_TABLE_NAME, conditions, join_conditions);

    for (std::map<std::string, std::string> animal_data : animals_vector){
        Animal animal = Animal::get(std::stoi(animal_data["iod"]));

        interests.push_back(animal);
    }

    return interests;
}