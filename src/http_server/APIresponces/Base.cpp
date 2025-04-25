#include "Base.h"

namespace Responce{
    Base::Base(){}

    Base::~Base(){}

    std::vector<unsigned char>  Base::Get(){throw std::runtime_error("I told you not to do this you idiot");}
}

#include "File.cpp"
#include "Func.cpp"
#include "FakeSON.cpp"
