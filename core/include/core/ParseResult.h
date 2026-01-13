#pragma once

#include "Asset.h"
#include <string>
#include <optional>

namespace core
{
    struct ParseResult
    {
        std::optional<Asset> asset;
        std::string error;
    };
}
