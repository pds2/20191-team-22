#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include "sqlite3_db.h"

class User;

class Animal {
private:
    int _id;
    std::string _name;
    std::string _type;
    std::string _color;
    int _age;
    float _height;
    float _weight;

public:
    static SQLite3DB _db;
    Animal(int id, std::string name, std::string type, std::string color, int age, float height, float weigth);

    static std::vector<Animal> index();
    static Animal get(int id);
    static bool create(std::map<std::string, std::string> insert_params);
    static bool update(std::map<std::string, std::string> update_params, int id);
    static bool destroy(int id);

    std::vector<User> show_interested();
};

#endif
