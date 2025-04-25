#include "File.h"

namespace Responce{
    std::unordered_map<std::string, std::string> contentType({{".txt", "text/plain"}, {".html", "text/html"}, {".css", "text/css"}, {".ico", "image/x-icon"}, {".png", "image/png"}});

    File::File(std::string path_, std::string fileType_):
    path(path_),
    fileType(fileType_)
    {

    }

    File::~File(){

    }

    std::vector<unsigned char> File::Get(){
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
}
