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
        void create(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket);
        void destroy(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket);
        void update(std::string route, std::string buffer, std::map<std::string, std::string> body, int socket);
        static std::map<std::string, std::string> get_body(std::string buffer);
        void RouteRedirect(std::string route, std::map<std::string,std::string> body);
        
    public:
        void handle_request(const char *buffer, int socket);
};

#endif