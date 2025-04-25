#include "FakeSON.h"

namespace Responce{
    JSON::JSON(std::unordered_map<std::string, std::string>* data_):
    data(data_)
    {

    }

    JSON::~JSON(){

    }

    std::vector<unsigned char> JSON::Get(){
        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/json\r\n"
        "\r\n{\n";

        for(auto& [n, x] : *data)
            ss << "\"" << n << "\" : " << x << ",\n";
        ss.seekp(-2, ss.cur);
        ss << "\n}\n";
        std::string s = ss.str();

        std::vector<unsigned char> output;
        output.insert(output.end(), s.begin(), s.end());

        return output;
    }
}
