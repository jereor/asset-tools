#include "ValidateMode.h"

#include "core/Logger.h"
#include "core/AssetParser.h"
#include "core/AssetValidator.h"
#include "core/TextureSizeRule.h"

#include <fstream>

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(ValidateMode::GetFactoryName(), ValidateMode::Create);
}

 std::string ValidateMode::GetFactoryName()
 {
     return "validate";
 }

  std::unique_ptr<ToolMode> ValidateMode::Create()
 {
    return std::make_unique<ValidateMode>();
 }

core::ExitCode ValidateMode::Run(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        core::Logger::Error("AssetTools validate requires an asset file path\n"
                            "Usage: AssetTools validate <asset_file>");
        return core::ExitCode::InvalidArguments;
    }
    
    std::ifstream file(args[0]);
    if (!file)
    {
        core::Logger::Error("Failed to open asset file: " + args[0]);
        return core::ExitCode::ToolFailure;
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
            core::Logger::Error(parseResult.error);
            hasErrors = true;
            continue;
        }

        auto results = validator.Validate(*parseResult.asset);
        for (const auto& result : results)
        {
            core::Logger::Error(result.message);
            hasErrors = true;
        }
    }

    if (hasErrors)
    {
        return core::ExitCode::ToolFailure;
    }

    core::Logger::Info("All assets validated successfully");
    return core::ExitCode::Success;
}
