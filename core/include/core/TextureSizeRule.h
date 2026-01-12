#pragma once

#include "ValidationRule.h"

namespace core
{
    class TextureSizeRule : public ValidationRule
    {
    public:
        ValidationResult Validate(const Asset& asset) const override;
    };
}
