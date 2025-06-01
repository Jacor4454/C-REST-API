#ifndef CLASS_RESPONCE_FILE_H
#define CLASS_RESPONCE_FILE_H

#include "Base.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Responce{
    class File : public Base{
        std::string path;
        std::string fileType;
        public:
        File(std::string path_, std::string fileType_):path(path_),fileType(fileType_){}
        ~File(){}
        
        std::vector<unsigned char> Get(){
            std::stringstream ss;
            ss << "HTTP/1.1 200 OK\r\n"
            "Content-Type: " << contentType[fileType] << "\r\n"
            "\r\n";
            std::string s = ss.str();

            std::ifstream file(path, std::ios::binary);
            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
            file.close();

            std::vector<unsigned char> output;
            output.reserve(s.size() + buffer.size());
            output.insert(output.end(), s.begin(), s.end());
            output.insert(output.end(), buffer.begin(), buffer.end());

            return output;
        }
    };
}

#endif