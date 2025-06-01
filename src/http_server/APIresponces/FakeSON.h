#ifndef CLASS_RESPONCE_JSON_H
#define CLASS_RESPONCE_JSON_H

#include "Base.h"
#include <sstream>
#include <bits/stdc++.h>
#include <unordered_map>

namespace Responce{
    class JSON : public Base{
        std::mutex data_mutex;
        std::unordered_map<std::string, std::string> data;
        public:
        JSON(){}
        ~JSON(){}
        
        std::vector<unsigned char> Get(){
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
        void Post(std::unordered_map<std::string, std::string>& m_reqs){
            data_mutex.lock();

            data.clear();
            for(auto& [n, x] : m_reqs)
                data[n] = x;
                
            data_mutex.unlock();
        }

        void lock(){data_mutex.lock();}
        void unlock(){data_mutex.unlock();}

        std::string& operator[](std::string& s){return data[s];}
        std::string& operator[](const char* s){return data[s];}
    };
}

#endif