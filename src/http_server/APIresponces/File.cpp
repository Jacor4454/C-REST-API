#include "File.h"

std::string getContentType(std::string s){
    if(s == ".txt")
        return "text/plain";
    
    throw std::runtime_error("file type not supported to send");
}

namespace Responce{
    File::File(std::string path_, std::string fileType_):
    path(path_),
    fileType(fileType_)
    {

    }

    File::~File(){

    }

    std::string File::Get(){
        std::stringstream ss;
        std::ifstream file(path);
        
        ss << "HTTP/1.1 200 OK\r\n"
        "Content-Type: " << getContentType(fileType) << "\r\n"
        "\r\n";

        std::string s;
        while(getline(file, s)){
            ss << s;
        }

        file.close();

        return ss.str();
    }
}
