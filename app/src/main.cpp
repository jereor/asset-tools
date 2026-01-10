#include "core/Version.h"
#include "core/Logger.h"

#include <vector>
#include <string>
#include <iostream>

namespace
{
    void PrintHelp()
    {
        std::cout <<
            "AssetTools - Internal Game Development Tool\n\n"
            "Usage:\n"
            "  AssetTools [options]\n\n"
            "Options:\n"
            "  --help       Show this help message\n"
            "  --version    Show version information\n";
    }

    bool HasFlag(const std::vector<std::string>& args, const std::string& flag)
    {
        for (const auto& arg : args)
        {
            if (arg == flag)
                return true;
        }
        return false;
    }
}

int main(int argc, char* argv[])
{
    // Convert argv into a safer container
    std::vector<std::string> args(argv + 1, argv + argc);

    core::Logger::Init("AssetTools.log");

    if (args.empty() || HasFlag(args, "--help"))
    {
        PrintHelp();
        core::Logger::Info("Displayed help");
        core::Logger::Shutdown();
        return 0;
    }

    if (HasFlag(args, "--version"))
    {
        std::cout << core::GetVersionString() << std::endl;
        core::Logger::Info("Displayed version");
        core::Logger::Shutdown();
        return 0;
    }

    core::Logger::Warning("Unknown arguments provided");
    PrintHelp();

    core::Logger::Shutdown();
    return 1;
}
