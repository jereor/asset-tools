#pragma once

#include "ParseResult.h"
#include <string>

namespace core
{
    class AssetParser
    {
    public:
        ParseResult ParseLine(const std::string& line) const;
    };
}
