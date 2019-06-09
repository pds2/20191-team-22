#include "../../include/services/controller.h"
#include "../../include/services/sqlite3_db.h"
#include "../../include/services/dsl.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <map>

void Controller::handle_request(const char *buffer, int socket){
    std::string buff(buffer);
    std::cout << buff << std::endl;
    std::istringstream iss(buff);

    // HTTP method
    iss >> buff;
    std::string http_method = buff;

    // Route
    iss >> buff;
    std::string route = buff;


    handle_method(http_method, socket, route, buffer);
    printf("------------------Response sent-------------------");
    close(socket);
}

void Controller::get(std::string route, int socket, std::string status){
    std::regex parseRoute ("[\\/](\\w+)[\\/]?(\\d+)?");
    std::smatch matches;
    std::string response;
    std::string id;

    std::cout << route << std::endl;
    // Route parsing
    std::regex_search(route, matches, parseRoute);
    route = matches.str(1);
    id = matches.str(2);

    std::cout << route + " -- " << id << std::endl;
    // Routes defaults
    if(route == "favicon")
        return;

    if(route == "/" || route == "/?" || route == "") //TOSQUEIRA
        route = "home";

    std::ifstream file;
    file.open("views/" + route + ".html");
    
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        file.open("views/404.html");
        response = build_response("404 Not Found" , file);
    }else{
        response = build_response(status, file, route, id);
    }

    const char *cstr = response.c_str();
    write(socket , cstr , response.length());
}

std::string Controller::build_response(std::string status, std::ifstream &file, std::string route, std::string id){
    std::string res = "HTTP/1.1"+ status +"\nContent-Type: text/html\nContent-Length: ";
    std::string helper_string = "";

    char ch;
    while(file.get(ch)) {
        helper_string += ch;
    }

    std::cout << "file parsed" << std::endl;
    helper_string = DSL::route(helper_string, route, id);

    res.append(std::to_string(helper_string.length()));
    res.append("\n\n");
    res.append(helper_string);
    
    file.close();

    return res;
}

void Controller::handle_method(std::string method, int socket, std::string route, const char *buffer){
    std::string buff(buffer);
    if(method == "GET"){
        get(route, socket, "200 OK");

    }else if (method == "POST"){
        post(route, buff, socket);

    }else if (method == "PUT"){
        //patch();
    }
}

void Controller::post(std::string route, std::string buffer, int socket){
    static std::map<std::string, std::string> body;
    body.clear();

    body = get_body(buffer);
    if(body["delete"] == "true"){
        destroy(route, buffer, socket);
        return;
    }
    for(std::pair<std::string, std::string> pair : body){
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // get(route, socket, "201 Created");
    std::string response = "HTTP/1.1 200 OK";
    const char *cstr = response.c_str();
    write(socket , cstr , response.length());
}

void Controller::destroy(std::string route, std::string buffer, int socket){
    std::cout << "Destroyed" << std::endl;
}

std::map<std::string, std::string> Controller::get_body(std::string buffer){
    std::map<std::string, std::string> result;
    result.clear();

    const std::regex propertiesReg ("(.*?)=(.*?)&");
    const std::regex bodyReg ("\\s{3,}(.*)");
    const std::regex beautify ("(.*?)\\+");
    std::smatch matches;

    std::regex_search(buffer, matches, bodyReg);
    std::string body; 
    body = matches.str(1);
    body += "&";

    while(std::regex_search(body, matches, propertiesReg)){
        std::string value;
        value = matches.str(2);
        
        result[matches.str(1)] = value; 
        
        // Eliminate the previous match and create
        // a new string to search
        body = matches.suffix().str();
    }
    return result;
}

// void Controller::PrintMatches(std::string str,
//         std::regex reg){
    
//     // Used when your searching a string
//     std::smatch matches;
    
//     // Show true and false in output
//     std::cout << std::boolalpha;
       
//     // Determines if there is a match and match 
//     // results are returned in matches
//     while(std::regex_search(str, matches, reg)){
//         std::cout << "Checked for Results : " << 
//                 matches.ready() << "\n";
        
//         std::cout << "Are there no matches : " << 
//                 matches.empty() << "\n";
        
//         std::cout << "Number of matches : " << 
//                 matches.size() << "\n";
        
//         // Get the first match
//         std::cout << matches.str(1) << "\n";
        
//         // Eliminate the previous match and create
//         // a new string to search
//         str = matches.suffix().str();
        
//         std::cout << "\n";
//     }
// }