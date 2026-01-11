#include "ScanMode.h"
#include "core/Logger.h"

core::ExitCode ScanMode::Run(const std::vector<std::string>& args)
{
    core::Logger::Info("Running scan mode");

    // TODO: Implement asset scanning
    core::Logger::Info("Scanning assets...");

    return core::ExitCode::Success;
}
