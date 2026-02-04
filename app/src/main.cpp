#include "core/Version.h"
#include "core/Logger.h"
#include "core/ExitCode.h"

#include "config/ConfigLoader.h"
#include "modes/ToolModeFactory.h"
#include "modes/ScanMode.h"
#include "modes/ValidateMode.h"
#include "modes/InspectMode.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <expected>

#include <yaml-cpp/yaml.h>

namespace
{
    constexpr const char* kDefaultConfigPath = "../../../configs/base.yaml";

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

    void LogDiagnostics(std::vector<core::Diagnostic> diagnostics)
    {
        for (const core::Diagnostic& diagnostic : diagnostics)
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

    std::string configPath;
    auto configIt = std::find(args.begin(), args.end(), "--config");
    if (configIt != args.end() && std::next(configIt) != args.end()) {
        core::Logger::Info("Using config file from command line argument: {}", *std::next(configIt));
        configPath = *std::next(configIt);
    }
    else {
        core::Logger::Info("No config file specified, using default:  {}", std::string(kDefaultConfigPath));
        configPath = kDefaultConfigPath;
    }

    core::Logger::Info("Loading config file: " + configPath);
	std::expected<ToolConfig, core::ToolResult> configResult = ConfigLoader::LoadConfig(configPath);
    if (!configResult.has_value())
    {
        LogDiagnostics(configResult.error().diagnostics);
        core::Logger::Error("Failed to load config file: " + configPath);
        core::Logger::Shutdown();
        return static_cast<int>(configResult.error().exitCode);
	}

	const ToolConfig& toolConfig = *configResult;
    core::Logger::Info("Base config loaded: " + toolConfig.baseConfig.metadata .name);
    

    std::unique_ptr<ToolMode> mode = ToolModeFactory::Create(args[0], toolConfig);

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

    LogDiagnostics(result.diagnostics);
    core::Logger::Shutdown();
    return static_cast<int>(result.exitCode);
}
