#pragma once

#include "ValidationRule.h"
#include "Asset.h"

#include <variant>

namespace core
{
    class TextureSizeRule : public ValidationRule<TextureAsset>
    {
    public:
        explicit TextureSizeRule(const int maxSizeKb) : m_maxSizeKb(maxSizeKb) {}

        ValidationResult Validate(const TextureAsset& asset) const override;
    private:
        const int m_maxSizeKb;
    };
}
