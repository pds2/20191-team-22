#include "../../include/services/dsl.h"
#include "../../include/services/user.h"
#include "../../include/services/animal.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>

std::string DSL::route(std::string string, std::string route, std::string id){

    if(id != ""){
        std::cout << "Rendering page " << route << " for the id: " << id << std::endl;

        if(route == "home"){
            std::map<std::string, std::vector<std::map<std::string, std::string> > > objArr;
            std::vector<Animal> animals;
            std::vector<std::map<std::string, std::string> > objectsToMap;
            User user = User::get(std::stoi(id));

            animals = user.animals();

            for(Animal animal : animals)
                objectsToMap.push_back(animal.to_map());
            
            objArr["_animals"] = objectsToMap;
            string = parsePartials(string, objArr);
        }
        if(route == "profile") {
            User user = User::get(std::stoi(id));
            string = parse(string, user.to_map());
        }
        if(route == "interested_users") {}
        if(route == "user_interests") {}
        if(route == "") {}
        if(route == "") {}
        if(route == "") {}
    }

    return string;
}

std::string DSL::parse(std::string string, std::map<std::string, std::string> object){

    if(!object.empty()){
        return parseTags(string, object);
    }else{
        return string;
    }
}

std::string DSL::parse(std::string string, std::map<std::string, std::vector<std::map<std::string, std::string> > > objArr){

    if(!objArr.empty()){
        return parsePartials(string, objArr);
    }else{
        return string;
    }
}

std::string DSL::parseTags(std::string string, std::map<std::string, std::string> object){
    std::regex reg("[{]{2}(\\w+)[}]{2}"); // Regex que detecta o formato {{tag}}
    std::smatch matches;
    std::string res;

    while(std::regex_search(string, matches, reg)){
            res += matches.prefix().str();
            res += object[matches.str(1)];

            // Eliminate the previous match and create
            // a new string to search
            string = matches.suffix().str();
    }
    res += string;

    return res;
}

std::string DSL::parsePartials(std::string string, std::map<std::string, std::vector<std::map<std::string, std::string> > > objArr){
    std::regex reg("[\\[]{2}(\\w+)[\\]]{2}"); // Regex que detecta o formato {{tag}}
    std::smatch matches;
    std::string res;
    std::string helper_string;

    while(std::regex_search(string, matches, reg)){
        std::ifstream partial;

        res += matches.prefix().str();
        for(std::map<std::string, std::string> object : objArr[matches.str(1)]){
            std::cout << matches.str(1) << std::endl;
            partial.open("views/" + matches.str(1) + ".html");
            if (!partial) {
                // Error handling
                std::cout << "Unable to open file" << std::endl;
                
            }else{
                helper_string = "";
                char ch;
                while(partial.get(ch))
                    helper_string += ch;
                
                res += parseTags(helper_string, object);
                
            }
            partial.close();
        }

        // Eliminate the previous match and create
        // a new string to search
        string = matches.suffix().str();

    }
    res += string;
    // std::cout << res << std::endl;
    return res;
}

