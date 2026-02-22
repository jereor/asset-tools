#include "core/TextureSizeRule.h"

#include <format>

namespace core
{
    ValidationResult TextureSizeRule::Validate(const Asset& asset) const
    {
        if (asset.type != AssetType::Texture)
        {
            return { true, "" };
        }

        if (asset.sizeKB > m_maxSizeKb)
        {
            std::string errorMessage = std::format("Texture '{}' exceeds size limit ({} KB)", asset.name, m_maxSizeKb);
            return { false, errorMessage };
        }

        return { true, "" };
    }
}
