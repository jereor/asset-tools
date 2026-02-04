#include "ValidateMode.h"

#include "core/Logger.h"
#include "core/AssetParser.h"
#include "core/AssetValidator.h"
#include "core/TextureSizeRule.h"

#include <fstream>
#include <vector>

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

core::ToolResult ValidateMode::Run(const std::vector<std::string>& args)
{
    core::ToolResult toolResult;

    if (args.size() != 1)
    {
		toolResult.AddError("Invalid number of arguments. Expected 1 argument: <asset_file>");
		toolResult.exitCode = core::ExitCode::InvalidArguments;
        return toolResult;
    }
    
    std::ifstream file(args[0]);
    if (!file)
    {
        toolResult.AddError("Failed to open asset file: " + args[0]);
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
        auto parseResult = parser.ParseLine(line);
        if (!parseResult.asset)
        {
            toolResult.AddError(parseResult.error);
            hasErrors = true;
            continue;
        }

        auto results = validator.Validate(*parseResult.asset);
        for (const auto& result : results)
        {
            toolResult.AddError(result.message);
            hasErrors = true;
        }
    }

    if (hasErrors)
    {
		toolResult.exitCode = core::ExitCode::ToolFailure;
        return toolResult;
    }

    toolResult.exitCode = core::ExitCode::Success;
    return toolResult;
}
