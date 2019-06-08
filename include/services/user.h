#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include "./sqlite3_db.h"

using namespace std;

class User {
protected:
    int _id;
    string _name;
    string _cpf;
    string _email;
    string _phone_number;
    string _address;
    char _gender;
public:
    static SQLite3DB _db;
    User(int id, string name, string cpf, string email, string phone_number, string address, char gender);

    static std::vector<User> index();
    static User get(int id);
    static bool create(std::map<std::string, std::string> insert_params);
    static bool update(std::map<std::string, std::string> update_params, int id);
    static bool destroy(int id);
};

#endif