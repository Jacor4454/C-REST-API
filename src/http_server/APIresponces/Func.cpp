#include "Func.h"

namespace Responce{
    Func::Func(std::function<std::string()> func_):
    func(func_)
    {

    }

    Func::~Func(){

    }

    std::vector<unsigned char> Func::Get(){
        std::string s = func();

        std::vector<unsigned char> output;
        output.insert(output.end(), s.begin(), s.end());

        return output;
    }
}
