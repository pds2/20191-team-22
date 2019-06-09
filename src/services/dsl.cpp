#include "../../include/services/dsl.h"
#include <string>
#include <iostream>

std::string DSL::route(std::string string, std::string route, std::string id){

    if(id != ""){
        std::cout << "Rendering page " << route << " for the id: " << id << std::endl;

        if(route == "home"){}
        if(route == "profile") {}
        if(route == "interested_users") {}
        if(route == "user_interests") {}
        if(route == "") {}
        if(route == "") {}
        if(route == "") {}
    }

    return string;
}

std::string DSL::parse(std::string string){

}

