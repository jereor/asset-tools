#include "core/TextureSizeRule.h"

#include <format>

namespace core
{
    ValidationResult TextureSizeRule::Validate(const TextureAsset& asset) const
    {
        if (asset.file.sizeKB > m_maxSizeKb)
        {
            std::string errorMessage = std::format("Texture '{}' exceeds size limit ({} KB)", asset.file.name, m_maxSizeKb);
            return { false, errorMessage };
        }

        return { true, "" };
    }
}
