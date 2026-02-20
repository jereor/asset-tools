#include "InspectMode.h"

#include "ToolModeFactory.h"
#include "core/Logger.h"

#include <filesystem>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <sstream>

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(InspectMode::GetFactoryName(), InspectMode::Create);
}

 std::string InspectMode::GetFactoryName()
 {
     return "inspect";
 }

  std::unique_ptr<ToolMode> InspectMode::Create(const ToolConfig& config)
 {
    return std::make_unique<InspectMode>(config);
 }

namespace
{
    static inline const std::filesystem::path kProjectRoot = PROJECT_ROOT;

    std::filesystem::path ResolveAssetPath(std::string_view assetFilePath, ToolConfig config)
    {
        std::filesystem::path path(assetFilePath);
        
        if (path.is_absolute()) {
            return path;
        }

        std::filesystem::path assetsRoot = kProjectRoot / config.baseConfig.paths.assetsRoot;
        return assetsRoot / path;
    }

    std::string GetFileExtension(const std::filesystem::path& filePath)
    {
        std::string ext = filePath.extension().string();

        // Convert extension to lowercase (for case-insensitive match)
        std::transform(ext.begin(), ext.end(), ext.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return ext;
    }

    static constexpr std::string_view supportedExtensions[] = {
        ".png", ".jpg", ".wav", ".fbx", ".json"
    };

    bool IsSupportedExtension(std::string_view ext)
    {
        return std::find(std::begin(supportedExtensions),  std::end(supportedExtensions), ext) 
                != std::end(supportedExtensions);
    }

    std::string SupportedExtensionsToString()
    {
        std::ostringstream out;
        bool first = true;

        for (std::string_view ext : supportedExtensions)
        {
            if (!first)
                out << ", ";
            out << ext;
            first = false;
        }

        return out.str();
    }

    std::string FileSizeToString(const std::uintmax_t& bytes)
    {
        constexpr std::string_view units[] = { "B", "KB", "MB", "GB", "TB" };

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
            std::filesystem::file_time_type ftime = std::filesystem::last_write_time(filePath);

            // Convert filesystem clock to system_clock
            using namespace std::chrono;
            system_clock::time_point sctp = time_point_cast<system_clock::duration>(
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

core::ToolResult InspectMode::Run(const std::vector<std::string>& args)
{
    core::ToolResult toolResult;

    if (args.size() != 1)
    {
        toolResult.AddError("Invalid number of arguments. Expected 1 argument: <asset_path>");
        toolResult.exitCode = core::ExitCode::InvalidArguments;
		return toolResult;
    }

    std::filesystem::path assetPath = ResolveAssetPath(args[0], m_config);
    if (!std::filesystem::exists(assetPath))
    {
        toolResult.AddError("Asset not found: {}", assetPath.string());
        toolResult.exitCode = core::ExitCode::FileNotFound;
        return toolResult;
    }

    if (!std::filesystem::is_regular_file(assetPath))
    {
        toolResult.AddError("The specified path is not a regular file: {}", assetPath.string());
        toolResult.exitCode = core::ExitCode::InvalidArguments;
        return toolResult;
    }

    std::string fileExt  = GetFileExtension(assetPath);
    if (!IsSupportedExtension(fileExt))
    {
        toolResult.AddError("Unsupported file extension: {}", fileExt);
        toolResult.AddInfo("Supported extensions: " + SupportedExtensionsToString());
        toolResult.exitCode = core::ExitCode::UnsupportedFormat;
        return toolResult;
    }

    std::uintmax_t fileSize = std::filesystem::file_size(assetPath);

    toolResult.AddInfo("Asset inspection result:");
    toolResult.AddInfo("  Name: {}", assetPath.filename().string());
    toolResult.AddInfo("  Extension: {}", fileExt);
    toolResult.AddInfo("  Size: {}", FileSizeToString(fileSize));
    toolResult.AddInfo("  Last Modified: {}", LastWriteTimeToString(assetPath));
    toolResult.exitCode = core::ExitCode::Success;
    return toolResult;
}
