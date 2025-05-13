#ifndef CLASS_RESPONCE_BASE_H
#define CLASS_RESPONCE_BASE_H

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace Responce{
    class Base{
        public:
        Base();
        virtual ~Base();
        
        virtual std::vector<unsigned char>  Get();
        virtual void Post(std::unordered_map<std::string, std::string>&);
    };
}

#endif