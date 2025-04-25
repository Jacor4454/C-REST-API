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
        File(std::string path_, std::string fileType_);
        ~File();
        
        std::vector<unsigned char> Get();
    };
}

#endif