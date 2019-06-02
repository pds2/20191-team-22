#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include "sqlite3_db.h"
#include "adopter.h"

using namespace std;

class Animal {
private:
    int _id;
    string _name;
    string _type;
    string _color;
    int _age;
    float _height;
    float _weight;

public:
    static SQLite3DB _db;
    Animal();

    std::vector<Animal> index();
    Animal get(int id);
    static bool create(std::map<std::string, std::string> insert_params);
    static bool update(std::map<std::string, std::string> update_params, int id);
    static bool destroy(int id);

    vector<Adopter> show_interested();
};

#endif
