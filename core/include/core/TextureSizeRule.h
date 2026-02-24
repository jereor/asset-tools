#pragma once

#include "ValidationRule.h"
#include "Asset.h"

namespace core
{
    class TextureSizeRule : public ValidationRule<Asset>
    {
    public:
        explicit TextureSizeRule(const int maxSizeKb) : m_maxSizeKb(maxSizeKb) {}

        ValidationResult Validate(const Asset& asset) const override;
    private:
        const int m_maxSizeKb;
    };
}
