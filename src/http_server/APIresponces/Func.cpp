#include "Func.h"

namespace Responce{
    Func::Func(std::function<std::string()> func_):
    func(func_)
    {

    }

    Func::~Func(){

    }

    std::string Func::Get(){
        return func();
    }
}
