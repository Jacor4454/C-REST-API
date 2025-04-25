#ifndef CLASS_RESPONCE_BASE_H
#define CLASS_RESPONCE_BASE_H

#include <string>
#include <stdexcept>
#include <vector>

namespace Responce{
    class Base{
        public:
        Base();
        ~Base();
        
        virtual std::vector<unsigned char>  Get();
    };
}

#endif