#ifndef CLASS_LOGGING_H
#define CLASS_LOGGING_H

#include <fstream>
#include <iostream>
#include <ctime>

class log{
    private:
    static std::ofstream file;
    static time_t timestamp;

    public:
    static void open(std::string);
    static void close();
    static void add(std::string);
};

#endif