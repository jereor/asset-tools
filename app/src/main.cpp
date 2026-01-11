#include "core/Version.h"
#include "core/Logger.h"
#include "core/ExitCode.h"

#include "ScanMode.h"
#include "ValidateMode.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

namespace
{
    void PrintHelp()
    {
        std::cout <<
            "AssetTools - Internal Game Development Tool\n\n"
            "Usage:\n"
            "  AssetTools <mode> [options]\n\n"
            "Modes:\n"
            "  scan        Scan assets\n"
            "  validate    Validate assets\n\n"
            "Options:\n"
            "  --help       Show this help message\n"
            "  --version    Show version information\n";
    }
}

int main(int argc, char* argv[])
{
    // Convert argv into a safer container
    std::vector<std::string> args(argv + 1, argv + argc);

    core::Logger::Init("AssetTools.log");

    if (args.empty())
    {
        core::Logger::Warning("No mode specified");
        PrintHelp();
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::InvalidArguments);
    }

    if (args[0] == "--help")
    {
        PrintHelp();
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::Success);
    }

    if (args[0] == "--version")
    {
        std::cout << core::GetVersionString() << std::endl;
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::Success);
    }

    std::unique_ptr<ToolMode> mode;

    if (args[0] == "scan")
    {
        mode = std::make_unique<ScanMode>();
    }
    else if (args[0] == "validate")
    {
        mode = std::make_unique<ValidateMode>();
    }
    else
    {
        core::Logger::Error("Unknown mode: " + args[0]);
        PrintHelp();
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::InvalidArguments);
    }

    auto result = mode->Run(
        std::vector<std::string>(args.begin() + 1, args.end())
    );

    core::Logger::Shutdown();
    return static_cast<int>(result);
}
