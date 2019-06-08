#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <fstream>
#include <regex>
#include <map>

class Controller {
    private:
        void get(std::string filename, int socket, std::string status);
        std::string build_response(std::string status, std::ifstream &file);
        void handle_method(std::string method, int socket, std::string filename, const char *buffer);
        void post(std::string route, std::string buffer, int socket);
        void destroy(std::string route, std::string buffer, int socket);
        static std::map<std::string, std::string> get_body(std::string buffer);
        
    public:
        void handle_request(const char *buffer, int socket);
};

#endif