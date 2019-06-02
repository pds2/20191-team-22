#ifndef ADOPTER_H
#define ADOPTER_H

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <map>
#include <sqlite3.h>
#include "user.h"
#include "animal.h"

class Adopter : public User {
public:
    // bool register_interest();
    std::vector<Animal> show_interests();
};

#endif