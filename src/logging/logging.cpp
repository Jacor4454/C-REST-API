#include "logging.h"

std::ofstream log::file;
time_t log::timestamp;

void log::open(std::string s){
    if(file)
        file.close();
    file.open(s);
}

void log::close(){
    if(file)
        file.close();
}

void log::add(std::string s){
    if(!file)
        throw std::runtime_error("cannot log when log is closed");
    
    time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    char formattedTime[50];
    
    strftime(formattedTime, 50, "%a %b %e %H:%M:%S %Y", &datetime);
    file << formattedTime << ": " << s << "\n";
    
    file.flush();
}
