#pragma once

#include <string>

namespace core
{
    enum class AssetType
    {
        Texture,
        Audio,
        Unknown
    };

    struct File
    {
        std::string name{};
        std::string extension{};
        int sizeKB{};
    };

    struct TextureAsset
    {
        File file{};
        int width{};
        int height{};
    };

    struct AudioAsset
    {
        File file{};
        int duration{};
        int sampleRate{};
        int channelCount{};
    };
}
