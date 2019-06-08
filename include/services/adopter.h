#ifndef ADOPTER_H
#define ADOPTER_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include <sqlite3.h>
#include "user.h"

class Animal;

class Adopter : public User {
public:
    Adopter(int id, string name, string cpf, string email, string phone_number, string address, char gender)
            : User(id, name, cpf, email, phone_number, address, gender){}
            
    bool register_interest(int animal_id);
    std::vector<Animal> show_interests();
};

#endif