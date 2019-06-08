#include "../../include/services/controller.h"
#include "../../include/services/sqlite3_db.h"
#include "../../include/services/animal.h"
#include "../../include/services/user.h"
#include "../../include/services/adopter.h"
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

    for(std::pair<std::string, std::string> pair : body){
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    if(body["delete"] == "true"){
        destroy(route, buffer, body, socket);
        return;
    }else if (body["put"] == "true"){
        std::cout << "Entrei no PUT" << std::endl;
        update(route, buffer, body, socket);
        return;
    }
    else{
        create(route, buffer, body, socket);
        return;
    }
}

void Controller::create(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket){
    // get(route, socket, "201 Created");
    std::string class_name = body["class_name"];
    bool result;

    if (class_name == std::string("animal")){
        result = Animal::destroy(std::stoi(body["animal_rowid"]));
    } 
    else if (class_name == std::string("user")){
        result = User::destroy(std::stoi(body["user_rowid"]));
    }
    else if (class_name == std::string("interest")){
        User user = User::get(std::stoi(body["user_rowid"]));
        Adopter adopter = Adopter(
            user.get_id(),
            user.get_name(),
            user.get_cpf(),
            user.get_email(),
            user.get_phone_number(),
            user.get_address(),
            user.get_gender()
            );

        result = adopter.register_interest(std::stoi(body["animal_rowid"]));
    }

    if (result){
        std::cout << "Interesse do Animal de ID " << body["animal_rowid"] << " com usuário de ID " << body["user_rowid"] << " criado com sucesso!" << std::endl;
        std::string response = "HTTP/1.1 200 OK";
        const char *cstr = response.c_str();
        write(socket , cstr , response.length());
    } else {
        std::cout << "Não foi possível excluir o animal de ID " << body["id"] << std::endl;
        get("/500.html", socket, "500 Internal Server Errors");
    }
}

void Controller::destroy(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket){
    // get(route, socket, "201 Created");
    std::string class_name = body["class_name"];
    bool result;

    if (class_name == std::string("animal")){
        result = Animal::destroy(std::atoi(body["animal_rowid"].c_str()));
    } 
    else if (class_name == std::string("user")){
        result = User::destroy(std::atoi(body["user_rowid"].c_str()));
    }

    if (result){
        std::cout << "Animal de ID " << body["animal_rowid"] << " excluído com sucesso!" << std::endl;
        std::string response = "HTTP/1.1 200 OK";
        const char *cstr = response.c_str();
        write(socket , cstr , response.length());
    } else {
        std::cout << "Não foi possível excluir o animal de ID " << body["id"] << std::endl;
        get("/500.html", socket, "500 Internal Server Errors");
    }
}

void Controller::update(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket){
    // get(route, socket, "201 Created");
    std::string class_name = body["class_name"];

    body.erase("class_name");
    body.erase("delete");
    body.erase("put");

    std::cout << "DELETEI TUDO DO PUT" << std::endl;
    for (std::pair<std::string,std::string> pair : body){
        std::cout << pair.first << " ||| " << pair.second << std::endl;
    }
    bool result;

    if (class_name == std::string("animal")){
        std::cout << "Entrei no IF" << std::endl;
        std::cout << body["rowid"] << std::endl;
        result = Animal::update(body, std::atoi(body["rowid"].c_str()));
    } 
    else if (class_name == std::string("user")){
        result = User::update(body, std::atoi(body["rowid"].c_str()));
    }

    if (result){
        std::cout << "Animal de ID " << body["animal_rowid"] << " atualizado com sucesso!" << std::endl;
        std::string response = "HTTP/1.1 200 OK";
        const char *cstr = response.c_str();
        write(socket , cstr , response.length());
    } else {
        std::cout << "Não foi possível atualizar o animal de ID " << body["animal_rowid"] << std::endl;
        get("/500.html", socket, "500 Internal Server Errors");
    }
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