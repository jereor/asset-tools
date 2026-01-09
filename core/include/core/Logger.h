#pragma once

#include <string>

namespace core
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    class Logger
    {
    public:
        static void Init(const std::string& logFilePath);
        static void Shutdown();

        static void Log(LogLevel level, const std::string& message);

        static void Info(const std::string& message);
        static void Warning(const std::string& message);
        static void Error(const std::string& message);

    private:
        static void Write(LogLevel level, const std::string& message);
    };
}
