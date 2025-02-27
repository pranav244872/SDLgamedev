#include "Logger.h"

#ifdef _WIN32
#include <windows.h>
#endif

std::string Logger::getCurrentDateTime(const std::string& type) 
{
    // Get the current time as a time_point from the system clock
    auto now = std::chrono::system_clock::now();
    
    // Convert to a time_t object, which represents the time in seconds
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // Convert time_t to tm struct (local time)
    std::tm local_time = *std::localtime(&now_time);
    
    // Create a stringstream to format the date/time string
    std::ostringstream oss;
    
    // Format the time in the desired format: [DD/Mon/YYYY HH:MM:SS]
    oss << type << " ["
        << std::put_time(&local_time, "%d/%b/%Y %H:%M:%S") 
        << "] ";
    
    return oss.str();
}

// Helper function to wrap text in color
std::string Logger::applyColor(const std::string& text, const std::string& color)
{
#ifdef _WIN32
    return text; // On Windows, we handle coloring differently
#else
    return color + text + "\033[0m"; // Reset after the text
#endif
}

void Logger::Log(const std::string& message)
{
    std::string logMessage = getCurrentDateTime("LOG") + message;
#ifdef _WIN32
    setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Green for logs
    std::cout << logMessage << std::endl;
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
#else
    std::string coloredMessage = applyColor(logMessage, "\033[32m"); // Green for logs
    std::cout << coloredMessage << std::endl;
#endif
}

void Logger::Err(const std::string& message)
{
    std::string errorMessage = getCurrentDateTime("ERR") + message;
#ifdef _WIN32
    setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Red for errors
    std::cerr << errorMessage << std::endl;
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
#else
    std::string coloredMessage = applyColor(errorMessage, "\033[31m"); // Red for errors
    std::cerr << coloredMessage << std::endl;
#endif
}

#ifdef _WIN32
void Logger::setConsoleColor(unsigned short color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#endif
