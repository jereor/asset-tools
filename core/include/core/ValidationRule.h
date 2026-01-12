#pragma once

#include "Asset.h"
#include "ValidationResult.h"

namespace core
{
    class ValidationRule
    {
    public:
        virtual ~ValidationRule() = default;
        virtual ValidationResult Validate(const Asset& asset) const = 0;
    };
}
