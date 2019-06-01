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
<<<<<<< HEAD
#include <map>
=======
>>>>>>> 2c6ecd665f73b91cf656c53dc5eaeaa169e16c9e

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void Controller::handle_request(const char *buffer, int socket){
    SQLite3DB db = SQLite3DB();

    std::map<std::string, std::string> map = db.get("COMPANY", 1);
    for (std::pair<std::string,std::string> pair : map){
        std::cout << pair.first << std::endl << pair.second << std::endl;
    }

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

void Controller::get(std::string route, int socket){
    std::string response;
    if(route == "/favicon.ico")
        return;

    if(route == "/")
        route = "/index.html";

    // Remove slash from header
    route.erase(0,1);

    std::ifstream file;
    file.open("views/" + route);
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        file.open("views/404.html");
        response = build_response("404 Not Found" , file);
    }else{
        response = build_response("200 OK", file);
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
        get(route, socket);

    }else if (method == "POST"){
        post(route, buff, socket);

    }else if (method == "PUT"){
        //put();
    }
}

void Controller::post(std::string route, std::string buffer, int socket){
    static std::map<std::string, std::string> body = get_body(buffer);
    for(std::pair<std::string, std::string> pair : body){
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    get(route, socket);
}

std::map<std::string, std::string> Controller::get_body(std::string buffer){
    std::regex reg ("(.*?)=(.*?)&");
    std::smatch matches;
    std::regex_search(buffer, matches, reg);
    std::string str = buffer;
    std::map<std::string, std::string> result;

    while(std::regex_search(str, matches, reg)){
        
        result[matches.str(1)] = matches.str(2);
        
        // Eliminate the previous match and create
        // a new string to search
        str = matches.suffix().str();
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

// void Controller::PrintMatches2(std::string str,
//         std::regex reg){
    
//     // This holds the first match
//     std::sregex_iterator currentMatch(str.begin(),
//             str.end(), reg);
    
//     // Used to determine if there are any more matches
//     std::sregex_iterator lastMatch;
    
//     // While the current match doesn't equal the last
//     while(currentMatch != lastMatch){
//         std::smatch match = *currentMatch;
//         std::cout << match.str() << "\n";
//         currentMatch++;
//     }
//     std::cout << std::endl;
    
// }