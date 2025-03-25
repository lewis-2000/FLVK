#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

class Logger
{
public:
	static void information(const std::string& message); // Log information message
	static void error(const std::string& message); // Log error message
	static void runtimeError(const std::string& message);

private:
	static std::string getTimestamp(); // Get current timestamp in HH:MM:SS format
};

// Get current timestamp in HH:MM:SS format
inline std::string Logger::getTimestamp()
{
	auto now = std::chrono::system_clock::now(); // Get current time
	auto time = std::chrono::system_clock::to_time_t(now); // Convert to time_t
    std::tm tm{};
    localtime_s(&tm, &time);  // Use localtime_r(&time, &tm); on Linux
    std::ostringstream oss;
	oss << std::put_time(&tm, "%H:%M:%S"); // Format time as HH:MM:SS
	return oss.str(); // Return formatted time
}

inline void Logger::information(const std::string& message)
{
	std::cout << "[" << getTimestamp() << "] LOG INFO: " << message << '\n'; // Log information message
}

inline void Logger::error(const std::string& message)
{
	std::cerr << "[" << getTimestamp() << "] LOG ERROR: " << message << '\n'; // Log error message
}

inline void Logger::runtimeError(const std::string& message)
{
	std::cerr << "[" << getTimestamp() << "] RUNTIME ERROR: " << message << '\n'; // Log runtime error message
}

#endif // LOGGER_H
