#include "ValidateMode.h"

#include "core/Logger.h"
#include "core/Asset.h"
#include "core/AssetValidator.h"
#include "core/TextureSizeRule.h"

core::ExitCode ValidateMode::Run(const std::vector<std::string>& args)
{
    core::Logger::Info("Running validate mode");

    core::Asset asset{
        "TestTexture",
        core::AssetType::Texture,
        2048
    };

    core::AssetValidator validator;
    validator.AddRule(std::make_unique<core::TextureSizeRule>());

    auto results = validator.Validate(asset);

    if (!results.empty())
    {
        for (const auto& result : results)
        {
            core::Logger::Error(result.message);
        }
        return core::ExitCode::ToolFailure;
    }

    core::Logger::Info("Validation successful");
    return core::ExitCode::Success;
}
