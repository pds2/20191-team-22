#include "../../include/services/controller.h"
#include "../../include/services/sqlite3_db.h"
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
    std::string response;
    if(route == "/favicon.ico")
        return;

    if(route == "/" || route == "/?") //TOSQUEIRA
        route = "/home.html";

    // Remove slash from header
    route.erase(0,1);

    std::ifstream file;
    file.open("views/" + route);
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        file.open("views/404.html");
        response = build_response("404 Not Found" , file);
    }else{
        response = build_response(status, file);
    }

    const char *cstr = response.c_str();
    write(socket , cstr , response.length());
}

std::string Controller::build_response(std::string status, std::ifstream &file){
    std::string res = "HTTP/1.1"+ status +"\nContent-Type: text/html\nContent-Length: ";

    std::string helper_string = "";

    char ch;
    int file_size = 0;
    while(file.get(ch)) {
        file_size++;
        helper_string += ch;
    }

    res.append(std::to_string(file_size));
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