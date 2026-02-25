#include "config/ToolConfig.h"

#include <functional>
#include <optional>
#include <vector>
#include <string>

class ConfigValidator {
public:
    using Rule = std::function<std::optional<std::string>(const TextureConfig&)>;

    ConfigValidator& AddRule(Rule rule);
    std::vector<std::string> Validate(const TextureConfig& config) const;
private:
    std::vector<Rule> m_rules;
};