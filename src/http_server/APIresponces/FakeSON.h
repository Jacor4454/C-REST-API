#ifndef CLASS_RESPONCE_JSON_H
#define CLASS_RESPONCE_JSON_H

#include "Base.h"
#include <sstream>
#include <bits/stdc++.h>
#include <unordered_map>

namespace Responce{
    class JSON : public Base{
        std::unordered_map<std::string, std::string> data;
        public:
        JSON();
        ~JSON();
        
        std::vector<unsigned char> Get();
        void Post(std::unordered_map<std::string, std::string>&);

        std::string& operator[](std::string& s);
        std::string& operator[](const char* s);
    };
}

#endif