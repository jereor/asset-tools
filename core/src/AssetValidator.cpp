#include "core/AssetValidator.h"

namespace core
{
    void AssetValidator::AddRule(std::unique_ptr<ValidationRule> rule)
    {
        m_rules.push_back(std::move(rule));
    }

    std::vector<ValidationResult> AssetValidator::Validate(const Asset& asset) const
    {
        std::vector<ValidationResult> results;

        for (const auto& rule : m_rules)
        {
            auto result = rule->Validate(asset);
            if (!result.success)
            {
                results.push_back(result);
            }
        }

        return results;
    }
}
