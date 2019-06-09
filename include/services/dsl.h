#ifndef DSL_H
#define DSL_H

#include <string>
#include <map>
#include <vector>

class DSL {
    private:
        static std::string parse(std::string string, std::map<std::string, std::string> object);
        static std::string parse(std::string string, std::map<std::string, std::vector<std::map<std::string, std::string> > > objArr);
        static std::string parseTags(std::string string, std::map<std::string ,std::string> object);
        static std::string parsePartials(std::string string, std::map<std::string, std::vector<std::map<std::string, std::string> > > objArr);
    public:
        static std::string route(std::string string, std::string route = "", std::string id = "");
};

#endif