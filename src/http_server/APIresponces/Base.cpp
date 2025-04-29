#include "Base.h"

namespace Responce{
    Base::Base(){}

    Base::~Base(){}

    std::vector<unsigned char>  Base::Get(){throw std::runtime_error("cannot \"get\" base request");}
    void Base::Post(std::unordered_map<std::string, std::string>& m_req){throw std::runtime_error("cannot \"post\" base request");}
}

#include "File.cpp"
#include "Func.cpp"
#include "FakeSON.cpp"
