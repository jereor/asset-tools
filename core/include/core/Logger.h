#pragma once

#include <string>
#include <format>

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

        template<typename... Args>
        static void Info(std::format_string<Args...> fmt, Args&&... args)
        {
            Write(LogLevel::Info, std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void Warning(std::format_string<Args...> fmt, Args&&... args)
        {
            Write(LogLevel::Warning, std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void Error(std::format_string<Args...> fmt, Args&&... args)
        {
            Write(LogLevel::Error, std::format(fmt, std::forward<Args>(args)...));
        }

    private:
        static void Write(LogLevel level, const std::string& message);
    };
}
