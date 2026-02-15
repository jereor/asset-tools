#include "core/Logger.h"

#include <iostream>
#include <fstream>
#include <mutex>
#include <ctime>

namespace core
{
    namespace
    {
        std::ofstream g_logFile;
        std::mutex g_logMutex;
        bool g_initialized = false;

        const char* ToString(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Info:    return "INFO";
            case LogLevel::Warning: return "WARN";
            case LogLevel::Error:   return "ERROR";
            default:                return "UNKNOWN";
            }
        }
    }

    void Logger::Init(std::string_view logFilePath)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (g_initialized)
            return;

        g_logFile.open(logFilePath.data(), std::ios::out | std::ios::trunc);
        g_initialized = true;
    }

    void Logger::Shutdown()
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (g_logFile.is_open())
            g_logFile.close();

        g_initialized = false;
    }

    void Logger::Log(LogLevel level, std::string_view message)
    {
        Write(level, message);
    }

    void Logger::Info(std::string_view message)
    {
        Write(LogLevel::Info, message);
    }

    void Logger::Warning(std::string_view message)
    {
        Write(LogLevel::Warning, message);
    }

    void Logger::Error(std::string_view message)
    {
        Write(LogLevel::Error, message);
    }

    void Logger::Write(LogLevel level, std::string_view message)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);

        if (!g_initialized)
            return;

        std::time_t now = std::time(nullptr);
        char timeBuffer[26]; // Allocate memory buffer (ctime_s = 26 characters)
#ifdef _WIN32
    // Windows: use ctime_s (secure version)
    ctime_s(timeBuffer, sizeof(timeBuffer), &now);
#else
    // MacOS and Linux: use ctime_r (thread-safe version)
    ctime_r(&now, timeBuffer);
#endif

        timeBuffer[24] = '\0'; // Remove trailing newline added by ctime_s

        std::string line =
            "[" + std::string(timeBuffer) + "]" +
            "[" + ToString(level) + "] " +
            message.data();

        std::cout << line << std::endl;

        if (g_logFile.is_open())
        {
            g_logFile << line << std::endl;
        }
    }
}
