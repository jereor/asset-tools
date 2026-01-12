#include "core/TextureSizeRule.h"

namespace core
{
    ValidationResult TextureSizeRule::Validate(const Asset& asset) const
    {
        if (asset.type != AssetType::Texture)
        {
            return { true, "" };
        }

        if (asset.sizeKB > 1024)
        {
            return {
                false,
                "Texture '" + asset.name + "' exceeds size limit (1024 KB)"
            };
        }

        return { true, "" };
    }
}
