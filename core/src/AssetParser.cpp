#include "core/AssetParser.h"

#include <sstream>

namespace core
{
    static AssetType ParseType(std::string_view token)
    {
        if (token == "Texture") return AssetType::Texture;
        if (token == "Audio") return AssetType::Audio;
        return AssetType::Unknown;
    }

    ParseResult AssetParser::ParseLine(const std::string& line) const
    {
        std::istringstream stream(line);

        std::string typeToken;
        std::string name;
        int sizeKB = 0;

        if (!(stream >> typeToken >> name >> sizeKB))
        {
            return { std::nullopt, "Invalid asset format: " + line };
        }

        AssetType type = ParseType(typeToken);
        if (type == AssetType::Unknown)
        {
            return { std::nullopt, "Unknown asset type: " + typeToken };
        }

        Asset asset{ name, type, sizeKB };
        return { asset, "" };
    }
}
