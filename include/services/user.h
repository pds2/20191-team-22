#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include "./sqlite3_db.h"
#include "./animal.h"

using namespace std;

class Animal;

class User {
protected:
    int _id;
    string _name;
    string _cpf;
    string _email;
    string _phone_number;
    string _address;
    char _gender;
    string _password;
public:
    static SQLite3DB _db;
    User(int id, string name, string cpf, string email, string phone_number, string address, char gender, string password);

    int get_id();
    string get_name();
    string get_cpf();
    string get_email();
    string get_phone_number();
    string get_address();
    char get_gender();
    string get_password();

    static std::vector<User> index();
    static User get(int id);
    static bool create(std::map<std::string, std::string> insert_params);
    static bool update(std::map<std::string, std::string> update_params, int id);
    static bool destroy(int id);

    static bool login(std::string email, std::string password);
    
    std::vector<Animal> animals();
    std::vector<Animal> liked_animals();
    std::vector<Animal> remaining_animals();
    std::map<std::string, std::string> to_map();
};

#endif