#include "FakeSON.h"

namespace Responce{
    JSON::JSON(){

    }

    JSON::~JSON(){

    }

    std::vector<unsigned char> JSON::Get(){
        data_mutex.lock();

        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/json\r\n"
        "\r\n{\n";

        for(auto& [n, x] : data)
            ss << "\"" << n << "\" : " << x << ",\n";
        ss.seekp(-2, ss.cur);
        ss << "\n}\n";
        std::string s = ss.str();

        std::vector<unsigned char> output;
        output.insert(output.end(), s.begin(), s.end());

        data_mutex.unlock();

        return output;
    }

    void JSON::lock(){data_mutex.lock();}
    void JSON::unlock(){data_mutex.unlock();}

    // copy data into map
    void JSON::Post(std::unordered_map<std::string, std::string>& m_reqs){
        data_mutex.lock();

        data.clear();
        for(auto& [n, x] : m_reqs)
            data[n] = x;
            
        data_mutex.unlock();
    }

    std::string& JSON::operator[](std::string& s) {
        return data[s];
    }
    std::string& JSON::operator[](const char* s){return data[s];}
}
