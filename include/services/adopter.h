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
    Adopter(int id, string name, string cpf, string email, string phone_number, string address, char gender, string password)
            : User(id, name, cpf, email, phone_number, address, gender, password){}

    Adopter(User user) : User(
        user.get_id(),
        user.get_name(),
        user.get_cpf(),
        user.get_email(),
        user.get_phone_number(),
        user.get_address(),
        user.get_gender(),
        user.get_password()
    ){}
            
    bool register_interest(int animal_id);
    std::vector<Animal> show_interests();
};

#endif