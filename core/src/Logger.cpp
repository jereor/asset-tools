#include "core/Logger.h"

#include <iostream>
#include <fstream>
#include <mutex>
#include <ctime>

namespace
{
    std::ofstream g_logFile;
    std::mutex g_logMutex;
    bool g_initialized = false;

    const char* ToString(core::LogLevel level)
    {
        switch (level)
        {
        case core::LogLevel::Info:    return "INFO";
        case core::LogLevel::Warning: return "WARN";
        case core::LogLevel::Error:   return "ERROR";
        default:                      return "UNKNOWN";
        }
    }
}

namespace core
{
    void Logger::Init(const std::string& logFilePath)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (g_initialized)
            return;

        g_logFile.open(logFilePath, std::ios::out | std::ios::trunc);
        g_initialized = true;
    }

    void Logger::Shutdown()
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (g_logFile.is_open())
            g_logFile.close();

        g_initialized = false;
    }
}

namespace core
{
    void Logger::Log(LogLevel level, const std::string& message)
    {
        Write(level, message);
    }

    void Logger::Info(const std::string& message)
    {
        Write(LogLevel::Info, message);
    }

    void Logger::Warning(const std::string& message)
    {
        Write(LogLevel::Warning, message);
    }

    void Logger::Error(const std::string& message)
    {
        Write(LogLevel::Error, message);
    }
}

namespace core
{
    void Logger::Write(LogLevel level, const std::string& message)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (!g_initialized)
            return;

        std::time_t now = std::time(nullptr);
        char timeBuffer[26]; // Allocate memory buffer (ctime_s = 26 characters)
        ctime_s(timeBuffer, sizeof(timeBuffer), &now);

        timeBuffer[24] = '\0'; // Remove trailing newline

        std::string line = "[" + std::string(timeBuffer) + "]" + "[" +
                           ToString(level) + "] " + message;
        
        std::cout << line << std::endl;

        if (g_logFile.is_open())
        {
            g_logFile << line << std::endl;
        }
    }
}
