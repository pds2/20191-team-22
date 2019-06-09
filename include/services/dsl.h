#ifndef DSL_H
#define DSL_H

#include <string>

class DSL {
    private:
        static std::string parse(std::string string);
    public:
        static std::string route(std::string string, std::string route = "", std::string id = "");
};

#endif