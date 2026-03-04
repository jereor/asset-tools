#pragma once

#include "Asset.h"
#include "ValidationRule.h"

#include <vector>
#include <memory>
#include <variant>

namespace core
{
    template<typename T>
    class AssetValidator
    {
    public:
        virtual void AddRule(std::unique_ptr<ValidationRule<T>> rule) = 0;
        virtual std::vector<ValidationResult> Validate(const T& asset) const = 0;

    private:
        std::vector<std::unique_ptr<ValidationRule<T>>> m_rules;
    };
}
