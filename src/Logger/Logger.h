#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

class Logger
{
public:
    static void Log(const std::string& message);
    static void Err(const std::string& message);

private:
    static std::string getCurrentDateTime(const std::string& type);
    static std::string applyColor(const std::string& text, const std::string& color);

#ifdef _WIN32
    static void setConsoleColor(unsigned short color);
#endif
};

#endif // LOGGER_H
