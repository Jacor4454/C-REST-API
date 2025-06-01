#ifndef CLASS_RESPONCE_SVG_H
#define CLASS_RESPONCE_SVG_H

#include "Base.h"
#include "../../svg/src/class_svg.h"

namespace Responce{
    class TextRest : public Base{
        std::vector<unsigned char> ucs;
        public:
        TextRest(std::string s_, std::string fileType){
            std::stringstream ss;
            ss << "HTTP/1.1 200 OK\r\n"
            "Content-Type: " << contentType[fileType] << "\r\n"
            "Content-Length: " << s_.size() << "\r\n"
            "\r\n";
            std::string s = ss.str();
            ucs.insert(ucs.end(), s.begin(), s.end());
            ucs.insert(ucs.end(), s_.begin(), s_.end());
        }
        
        std::vector<unsigned char> Get(){return ucs;}
    };
}

#endif