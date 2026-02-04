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

  std::unique_ptr<ToolMode> ScanMode::Create(const ToolConfig& config)
 {
    return std::make_unique<ScanMode>(config);
 }

core::ToolResult ScanMode::Run(const std::vector<std::string>& args)
{
    core::ToolResult toolResult;
    toolResult.AddInfo("Running scan mode");

    // TODO: Implement asset scanning
    toolResult.AddInfo("Scanning assets...");

	toolResult.exitCode = core::ExitCode::Success;
    return toolResult;
}
