#ifndef CLASS_RESPONCE_BASE_H
#define CLASS_RESPONCE_BASE_H

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace Responce{
    static std::unordered_map<std::string, std::string> contentType({{".txt", "text/plain"}, {".html", "text/html"}, {".css", "text/css"}, {".ico", "image/x-icon"}, {".png", "image/png"}, {".svg", "image/svg+xml"}});
    class Base{
        public:
        Base();
        virtual ~Base();
        
        virtual std::vector<unsigned char>  Get();
        virtual void Post(std::unordered_map<std::string, std::string>&);
    };
}

#include "File.h"
#include "Func.h"
#include "FakeSON.h"
#include "Text.h"

#endif