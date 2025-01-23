#include "Logger.h"

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
    oss << type << "["
        << std::put_time(&local_time, "%d/%b/%Y %H:%M:%S") 
        << "] ";
    
    return oss.str();
}

void Logger::Log(const std::string& message)
{
	std::cout << getCurrentDateTime("LOG") << message << std::endl;
}

void Logger::Err(const std::string& message)
{
	std::cerr << getCurrentDateTime("ERR") << message << std::endl;
}
