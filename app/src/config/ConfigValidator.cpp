#include "ConfigValidator.h"

#include "ToolConfig.h"

#include <optional>

using Rule = std::function<std::optional<std::string>(const TextureConfig&)>;

ConfigValidator& ConfigValidator::AddRule(Rule rule) {
    m_rules.push_back(std::move(rule));
    return *this;
}

std::vector<std::string> ConfigValidator::Validate(const TextureConfig& config) const {
    std::vector<std::string> errors;
    for (const auto& rule : m_rules) {
        if (auto error = rule(config))
            errors.push_back(*error);
    }
    return errors;
}
