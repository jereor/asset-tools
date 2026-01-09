#include "core/Version.h"
#include "core/Logger.h"

int main()
{
    core::Logger::Init("AssetTools.log");

    core::Logger::Info("Application started");
    core::Logger::Info(core::GetVersionString());
    core::Logger::Warning("This is a test warning");
    core::Logger::Error("This is a test error");

    core::Logger::Shutdown();

    return 0;
}
