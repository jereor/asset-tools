#pragma once

#include "ValidationRule.h"

namespace core
{
    class TextureSizeRule : public ValidationRule
    {
    public:
        explicit TextureSizeRule(const int maxSizeKb) : m_maxSizeKb(maxSizeKb) {}

        ValidationResult Validate(const Asset& asset) const override;
    private:
        const int m_maxSizeKb;
    };
}
