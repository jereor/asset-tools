#include "InspectMode.h"

#include "core/Logger.h"

#include <filesystem>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <sstream>

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

    static const std::unordered_set<std::string> supportedExtensions = {
            ".png",
            ".jpg",
            ".wav",
            ".fbx",
            ".json"
    };

    bool IsSupportedExtension(std::string ext)
    {
        if (ext.empty())
            return false;

        return supportedExtensions.find(ext) != supportedExtensions.end();
    }

    std::string SupportedExtensionsToString()
    {
        std::ostringstream out;
        bool first = true;

        for (const auto& ext : supportedExtensions)
        {
            if (!first)
                out << ", ";
            out << ext;
            first = false;
        }

        return out.str();
    }

    std::string FileSizeToString(std::uintmax_t bytes)
    {
        constexpr const char* units[] = { "B", "KB", "MB", "GB", "TB" };

        double size = static_cast<double>(bytes);
        std::size_t unit = 0;

        while (size >= 1024.0 && unit < std::size(units) - 1)
        {
            size /= 1024.0;
            ++unit;
        }

        std::ostringstream out;
        out << std::fixed << std::setprecision(unit == 0 ? 0 : 2)
            << size << ' ' << units[unit];

        return out.str();
    }

    std::string LastWriteTimeToString(const std::filesystem::path& filePath)
    {
        try
        {
            auto ftime = std::filesystem::last_write_time(filePath);

            // Convert filesystem clock to system_clock
            using namespace std::chrono;
            auto sctp = time_point_cast<system_clock::duration>(
                ftime - decltype(ftime)::clock::now() + system_clock::now());

            std::time_t cftime = system_clock::to_time_t(sctp);

            std::tm tm;
#ifdef _WIN32
            localtime_s(&tm, &cftime);
#else
            localtime_r(&cftime, &tm);
#endif

            std::ostringstream out;
            out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return out.str();
        }
        catch (...)
        {
            return std::string{};
        }
    }
}

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(InspectMode::GetFactoryName(), InspectMode::Create);
}

 std::string InspectMode::GetFactoryName()
 {
     return "inspect";
 }

  std::unique_ptr<ToolMode> InspectMode::Create()
 {
    return std::make_unique<InspectMode>();
 }

core::ExitCode InspectMode::Run(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        core::Logger::Error("AssetTools inspect expects exactly 1 argument\n"
                            "Usage: AssetTools inspect <asset_path>");
        return core::ExitCode::InvalidArguments;
    }

    std::filesystem::path assetPath{args[0]};
    if (!std::filesystem::exists(assetPath))
    {
        core::Logger::Error("Asset does not exist: " + assetPath.string());
        return core::ExitCode::FileNotFound;
    }

    if (!std::filesystem::is_regular_file(assetPath))
    {
        core::Logger::Error("Path is not a regular file: " + assetPath.string());
        return core::ExitCode::InvalidArguments;
    }

    auto fileExt = GetFileExtension(assetPath);
    if (!IsSupportedExtension(fileExt))
    {
        core::Logger::Error("Unsupported file extension: " + fileExt);
		core::Logger::Info("Supported extensions: " + SupportedExtensionsToString());
        return core::ExitCode::UnsupportedFormat;
    }

    std::uintmax_t fileSize = std::filesystem::file_size(assetPath);

    core::Logger::Info("Asset inspection result:");
    core::Logger::Info("  Name: " + assetPath.filename().string());
    core::Logger::Info("  Extension: " + fileExt);
    core::Logger::Info("  Size: " + FileSizeToString(fileSize));
    core::Logger::Info("  Last Modified: " + LastWriteTimeToString(assetPath));
    return core::ExitCode::Success;
}
