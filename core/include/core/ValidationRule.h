#pragma once

#include "ValidationResult.h"

namespace core
{
    template<typename T>
    class ValidationRule
    {
    public:
        virtual ~ValidationRule() = default;
        virtual ValidationResult Validate(const T& data) const = 0;
    };
}
