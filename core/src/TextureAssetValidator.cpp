#include "core/TextureAssetValidator.h"

namespace core
{
    void TextureAssetValidator::AddRule(std::unique_ptr<ValidationRule<TextureAsset>> rule)
    {
        m_rules.push_back(std::move(rule));
    }

    std::vector<ValidationResult> TextureAssetValidator::Validate(const TextureAsset& asset) const
    {
        std::vector<ValidationResult> results;

        for (const auto& rule : m_rules)
        {
            ValidationResult result = rule->Validate(asset);
            if (!result.success)
            {
                results.push_back(result);
            }
        }

        return results;
    }
}
