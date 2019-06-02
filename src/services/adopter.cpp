#include "../../include/services/sqlite3_db.h"
#include "../../include/services/animal.h"
#include "../../include/services/adopter.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

#define USERS_TABLE_NAME "users"

std::vector<Animal> Adopter::show_interests(){
    std::map <std::string, std::string> conditions;
    std::vector <std::map<std::string, std::string> > join_conditions;
    std::vector <Animal>  interests;

    std::map<std::string, std::string> interests_join_conditions;

    conditions["interests.users_oid"] = this->_id;
    
    interests_join_conditions["join_table_name"] = "INTERESTS";
    interests_join_conditions["join_table_attribute"] = "user_oid";
    interests_join_conditions["source_table_name"] = USERS_TABLE_NAME;
    interests_join_conditions["join_table_name"] = "oid";

    join_conditions.push_back(interests_join_conditions);

    std::vector< std::map<std::string, std::string> > animals_vector = _db.get_where("animals", conditions, join_conditions);

    for (std::map<std::string, std::string> animal_data : animals_vector){
        Animal animal = Animal();
        animal.get(std::stoi(animal_data["iod"]));

        interests.push_back(animal);
    }

    return interests;
}