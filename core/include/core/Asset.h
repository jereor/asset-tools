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

    struct Asset
    {
        std::string name;
        AssetType type;
        int sizeKB;
    };
}
