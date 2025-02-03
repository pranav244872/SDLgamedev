#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream> 
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

class Logger
{
	public:
		static std::string applyColor
		(
			const std::string& text, 
			const std::string& color
		);
		static std::string getCurrentDateTime(const std::string& type);
		static void Log(const std::string& message);
		static void Err(const std::string& message);
};

#endif
