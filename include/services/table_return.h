#ifndef TABLE_RETURN_H
#define TABLE_RETURN_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <iterator> 
#include <vector>
#include <map>

class TableReturn {
public:
    // Methods for handling DB return values
    std::map<std::string, std::string> get_return_values;
    std::vector< std::map<std::string, std::string> > index_return_values;
};

#endif
