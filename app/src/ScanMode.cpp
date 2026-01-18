#include "ScanMode.h"

#include "core/Logger.h"

#include "ToolModeFactory.h"

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(ScanMode::GetFactoryName(), ScanMode::Create);
}

 std::string ScanMode::GetFactoryName()
 {
     return "scan";
 }

  std::unique_ptr<ToolMode> ScanMode::Create()
 {
    return std::make_unique<ScanMode>();
 }

core::ExitCode ScanMode::Run(const std::vector<std::string>& args)
{
    core::Logger::Info("Running scan mode");

    // TODO: Implement asset scanning
    core::Logger::Info("Scanning assets...");

    return core::ExitCode::Success;
}
