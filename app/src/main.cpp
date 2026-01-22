#include "core/Version.h"
#include "core/Logger.h"
#include "core/ExitCode.h"

#include "ToolModeFactory.h"
#include "ScanMode.h"
#include "ValidateMode.h"
#include "InspectMode.h"

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
            "  inspect     Inspect asset metadata\n"
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

    std::unique_ptr<ToolMode> mode = ToolModeFactory::Create(args[0]);

    if (mode == nullptr)
    {
        core::Logger::Error("Unknown mode: " + args[0]);
        
        auto availableModes = ToolModeFactory::GetAvailableModes();
        if (!availableModes.empty())
        {
            core::Logger::Info("Available modes:");
            for (const auto& modeName : availableModes)
                core::Logger::Info("  - " + modeName);
        }
        
        PrintHelp();
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::InvalidArguments);
    }

    auto result = mode->Run(
        std::vector<std::string>(args.begin() + 1, args.end())
    );

    for each(core::Diagnostic diagnostic in result.diagnostics)
    {
        switch (diagnostic.level)
        {
            case core::LogLevel::Info:
                core::Logger::Info(diagnostic.message);
			    break;
            case core::LogLevel::Warning:
				core::Logger::Warning(diagnostic.message);
                break;
			case core::LogLevel::Error:
                core::Logger::Error(diagnostic.message);
				break;
        }
    }

    core::Logger::Shutdown();
    return static_cast<int>(result.exitCode);
}
