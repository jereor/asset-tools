#include "core/AssetParser.h"

#include <algorithm>
#include <cctype>

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

    static constexpr std::string_view textureExtensions[] = {
        ".jpg", ".png", "psd", ".tga"
    };

    bool IsTextureExtension(const std::string_view& ext)
    {
        return std::find(std::begin(textureExtensions), std::end(textureExtensions), ext)
                != std::end(textureExtensions);
    }

    static constexpr std::string_view audioExtensions[] = {
        ".wav", ".mp3", ".ogg", ".aif"
    };

    bool IsAudioExtension(const std::string& ext)
    {
        return std::find(std::begin(audioExtensions), std::end(audioExtensions), ext)
                != std::end(audioExtensions);
    }
}

namespace core
{
    [[nodiscard]] std::variant<std::monostate, TextureAsset, AudioAsset> core::AssetParser::ParseAsset(const std::filesystem::path &assetPath) const
    {
        std::string fileName = assetPath.filename().string();
        std::string fileExtension = GetFileExtension(assetPath);
        int fileSizeKB = static_cast<int>(std::filesystem::file_size(assetPath) / 1024);
        File file { .name=fileName, .extension=fileExtension, .sizeKB=fileSizeKB };

        if (IsTextureExtension(fileExtension))
        {
            // TODO: Fully initialize TextureAsset
            return TextureAsset { .file=file };
        }

        if (IsAudioExtension(fileExtension))
        {
            // TODO: Fully initialize AudioAsset
            return AudioAsset { .file=file };
        }

        return std::monostate{};
    }
}


