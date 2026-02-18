#include "ValidateMode.h"

#include "ToolModeFactory.h"
#include "core/Logger.h"
#include "core/AssetParser.h"
#include "core/AssetValidator.h"
#include "core/TextureSizeRule.h"

#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <unordered_set>

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(ValidateMode::GetFactoryName(), ValidateMode::Create);
}

std::string ValidateMode::GetFactoryName()
{
    return "validate";
}

std::unique_ptr<ToolMode> ValidateMode::Create(const ToolConfig& config)
{
    return std::make_unique<ValidateMode>(config);
}

namespace
{
    std::string GetFileExtension(const std::filesystem::path& filePath)
    {
        std::string ext = filePath.extension().string();

        // Convert extension to lowercase (for case-insensitive match)
        std::transform(ext.begin(), ext.end(), ext.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return ext;
    }
}

core::ToolResult ValidateMode::Run(const std::vector<std::string>& args)
{
    core::ToolResult toolResult;

    if (args.size() != 1)
    {
		toolResult.AddError("Invalid number of arguments. Expected 1 argument: <asset_file>");
		toolResult.exitCode = core::ExitCode::InvalidArguments;
        return toolResult;
    }

    std::string fileExt = GetFileExtension(args[0]);
    if (fileExt != ".txt")
    {
        toolResult.AddError("Unsupported file extension: {}", fileExt);
        toolResult.AddInfo("Only .txt files are supported for validation in this mode.");
        toolResult.exitCode = core::ExitCode::UnsupportedFormat;
        return toolResult;
    }
    
    std::ifstream file(args[0]);
    if (!file)
    {
        toolResult.AddError("Failed to open asset file: {}", args[0]);
        toolResult.exitCode = core::ExitCode::ToolFailure;
        return toolResult;
    }

    core::AssetParser parser;
    core::AssetValidator validator;
    validator.AddRule(std::make_unique<core::TextureSizeRule>());

    std::string line;
    bool hasErrors = false;

    while (std::getline(file, line))
    {
        core::ParseResult parseResult = parser.ParseLine(line);
        if (!parseResult.asset)
        {
            toolResult.AddError(parseResult.error);
            hasErrors = true;
            continue;
        }

        std::vector<core::ValidationResult> results = validator.Validate(*parseResult.asset);
        for (const core::ValidationResult& result : results)
        {
            toolResult.AddError(result.message);
            hasErrors = true;
        }
    }

    if (hasErrors)
    {
		toolResult.exitCode = core::ExitCode::ValidationFailed;
        return toolResult;
    }

    toolResult.AddInfo("Asset validation completed successfully with no errors.");
    toolResult.exitCode = core::ExitCode::Success;
    return toolResult;
}
