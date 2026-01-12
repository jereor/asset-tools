#pragma once

#include "Asset.h"
#include "ValidationRule.h"
#include <vector>
#include <memory>

namespace core
{
    class AssetValidator
    {
    public:
        void AddRule(std::unique_ptr<ValidationRule> rule);
        std::vector<ValidationResult> Validate(const Asset& asset) const;

    private:
        std::vector<std::unique_ptr<ValidationRule>> m_rules;
    };
}
