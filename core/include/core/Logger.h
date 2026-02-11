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
        static void Init(std::string_view logFilePath);
        static void Shutdown();

        static void Log(LogLevel level, std::string_view message);

        static void Info(std::string_view message);
        static void Warning(std::string_view message);
        static void Error(std::string_view message);

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
        static void Write(LogLevel level, std::string_view message);
    };
}
