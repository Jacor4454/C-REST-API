#ifndef CLASS_RESPONCE_BASE_H
#define CLASS_RESPONCE_BASE_H

#include <string>
#include <stdexcept>

namespace Responce{
    class Base{
        public:
        Base();
        ~Base();
        
        virtual std::string Get();
    };
}

#endif