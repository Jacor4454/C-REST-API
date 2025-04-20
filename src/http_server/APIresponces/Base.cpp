#include "Base.h"

namespace Responce{
    Base::Base(){}

    Base::~Base(){}

    std::string Base::Get(){throw std::runtime_error("I told you not to do this you idiot");}
}

#include "File.cpp"
