#ifndef CLASS_RESPONCE_FUNC_H
#define CLASS_RESPONCE_FUNC_H

#include "Base.h"
#include <sstream>
#include <bits/stdc++.h>

namespace Responce{
    class Func : public Base{
        std::function<std::string()> func;
        public:
        Func(std::function<std::string()> func_):func(func_){}
        ~Func(){}
        
        std::vector<unsigned char> Get(){
            std::string s = func();

            std::vector<unsigned char> output;
            output.insert(output.end(), s.begin(), s.end());

            return output;
        }
    };
}

#endif