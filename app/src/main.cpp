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
    const std::string kDefaultLogFilePath = "AssetTools.log";
    const std::string kDefaultBaseConfigPath = "base.yaml";

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

    struct ConfigPaths {
        std::string basePath;
        std::string texturePath;
        std::string audioPath;
    };

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

    core::Logger::Init(kDefaultLogFilePath);
    core::Logger::Info("Log file opened: {}", kDefaultLogFilePath);

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

    // -- Parse config file paths from command line arguments --
    ConfigPaths configPaths;

    auto baseConfigIt = std::find(args.begin(), args.end(), "--base-config");
    if (baseConfigIt != args.end() && std::next(baseConfigIt) != args.end()) {
        core::Logger::Info("Using base config file from command line argument: {}", *std::next(baseConfigIt));
        configPaths.basePath = *std::next(baseConfigIt);
        args.erase(baseConfigIt, std::next(baseConfigIt, 2));
    }
    else {
        core::Logger::Info("No base config file specified, using default:  {}", std::string(kDefaultBaseConfigPath));
        configPaths.basePath = kDefaultBaseConfigPath;
    }
    
    auto textureConfigIt = std::find(args.begin(), args.end(), "--texture-config");
    if (textureConfigIt != args.end() && std::next(textureConfigIt) != args.end()) {
        core::Logger::Info("Using texture config file from command line argument: {}", *std::next(textureConfigIt));
        configPaths.texturePath = *std::next(textureConfigIt);
        args.erase(textureConfigIt, std::next(textureConfigIt, 2));
    }

    auto audioConfigIt = std::find(args.begin(), args.end(), "--audio-config");
    if (audioConfigIt != args.end() && std::next(audioConfigIt) != args.end()) {
        core::Logger::Info("Using audio config file from command line argument: {}", *std::next(audioConfigIt));
        configPaths.audioPath = *std::next(audioConfigIt);
        args.erase(audioConfigIt, std::next(audioConfigIt, 2));
    }

    // - - Load configs --
    ToolConfig toolConfig;

    core::Logger::Info("Loading base config file: {}", configPaths.basePath);
	std::expected<BaseConfig, core::ToolResult> baseConfigResult = ConfigLoader::LoadBaseConfig(configPaths.basePath);
    if (!baseConfigResult.has_value())
    {
        LogDiagnostics(baseConfigResult.error().diagnostics);
        core::Logger::Error("Failed to load  base config file: {}", configPaths.basePath);
        core::Logger::Shutdown();
        return static_cast<int>(baseConfigResult.error().exitCode);
	}
    toolConfig.baseConfig = baseConfigResult.value();
    core::Logger::Info("Base config loaded: {} v{}",  toolConfig.baseConfig.metadata.name, toolConfig.baseConfig.metadata.version);
    
    if (!configPaths.texturePath.empty()) {
        core::Logger::Info("Loading texture config file: {}", configPaths.texturePath);
        std::expected<TextureConfig, core::ToolResult> textureConfigResult = ConfigLoader::LoadTextureConfig(configPaths.texturePath);
        if (!textureConfigResult.has_value())
        {
            LogDiagnostics(textureConfigResult.error().diagnostics);
            core::Logger::Error("Failed to load texture config file: {}", configPaths.texturePath);
            core::Logger::Shutdown();
            return static_cast<int>(textureConfigResult.error().exitCode);
        }
        toolConfig.textureConfig = textureConfigResult.value();
        core::Logger::Info("Texture config loaded: {} v{}",  toolConfig.textureConfig.metadata.name, toolConfig.textureConfig.metadata.version);
    }
    else {
        core::Logger::Info("No texture config provided. Skipping it.");
    }
    
    if (!configPaths.texturePath.empty()) {
        core::Logger::Info("Loading audio config file: {}", configPaths.audioPath);
        std::expected<AudioConfig, core::ToolResult> audioConfigResult = ConfigLoader::LoadAudioConfig(configPaths.audioPath);
        if (!audioConfigResult.has_value())
        {
            LogDiagnostics(audioConfigResult.error().diagnostics);
            core::Logger::Error("Failed to load audio config file: {}", configPaths.audioPath);
            core::Logger::Shutdown();
            return static_cast<int>(audioConfigResult.error().exitCode);
        }
        toolConfig.audioConfig = audioConfigResult.value();
        core::Logger::Info("Audio config loaded: {} v{}",  toolConfig.audioConfig.metadata.name, toolConfig.audioConfig.metadata.version);
    }
    else {
        core::Logger::Info("No audio config provided. Skipping it.");
    }

    // -- Create the specified mode --
    std::unique_ptr<ToolMode> mode = ToolModeFactory::Create(args[0], toolConfig);

    if (mode == nullptr)
    {
        core::Logger::Error("Unknown mode: {}", args[0]);
        
        auto availableModes = ToolModeFactory::GetAvailableModes();
        if (!availableModes.empty())
        {
            core::Logger::Info("Available modes:");
            for (const auto& modeName : availableModes)
                core::Logger::Info("  - {}", modeName);
        }
        
        PrintHelp();
        core::Logger::Shutdown();
        return static_cast<int>(core::ExitCode::InvalidArguments);
    }

    // -- Run the mode  --
    auto result = mode->Run(
        std::vector<std::string>(args.begin() + 1, args.end())
    );

    LogDiagnostics(result.diagnostics);

    if (result.exitCode == core::ExitCode::ValidationFailed)
    {
        core::Logger::Error("VALIDATION FAILURE: Please fix the validation errors and try again.");
    }
    else if (result.IsUserError())
    {
        core::Logger::Error("USER ERROR: Please review the errors and try again.");
    }
    else if (result.IsToolError()) {
        core::Logger::Error("TOOL ERROR: Please report the bug to the tool developer and provide the logs.");
    }
    else if (result.IsSuccess()) {
        core::Logger::Info("SUCCESS: Task completed successfully with no errors.");
    }

    core::Logger::Shutdown();
    return static_cast<int>(result.exitCode);
}
