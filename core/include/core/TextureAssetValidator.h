#pragma once

#include "AssetValidator.h"
#include "Asset.h"
#include "ValidationRule.h"

#include <vector>
#include <memory>
#include <variant>

namespace core
{
    class TextureAssetValidator : public AssetValidator<TextureAsset>
    {
    public:
        void AddRule(std::unique_ptr<ValidationRule<TextureAsset>> rule) override;
        std::vector<ValidationResult> Validate(const TextureAsset& asset) const override;

    private:
        std::vector<std::unique_ptr<ValidationRule<TextureAsset>>> m_rules;
    };
}
