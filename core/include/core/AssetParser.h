#pragma once

#include "Asset.h"

#include <variant>
#include <string>
#include <filesystem>

namespace core
{
    class AssetParser
    {
    public:
       [[nodiscard]] std::variant<std::monostate, TextureAsset, AudioAsset> ParseAsset(const std::filesystem::path& assetPath) const;
    };
}
