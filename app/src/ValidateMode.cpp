#include "ValidateMode.h"
#include "core/Logger.h"

core::ExitCode ValidateMode::Run(const std::vector<std::string>& args)
{
    core::Logger::Info("Running validate mode");

    // TODO: Implement asset validation
    core::Logger::Error("Validation failed: invalid asset detected");

    return core::ExitCode::ToolFailure;
}
