#pragma once

#include <string>
#include <vector>

struct ConfigMetadata {
    std::string name;
    std::string description;
    float version;
};

struct BaseConfig {
    struct BaseValidationConfig {
        bool failOnWarning;
    };

    struct BasePathConfig {
        std::string assetsRoot;
    };

    struct BaseLoggingConfig {
        bool verbose;
    };

    ConfigMetadata metadata;
    BaseValidationConfig validation;
    BasePathConfig paths;
    BaseLoggingConfig logging;
};

struct TextureConfig {
    ConfigMetadata metadata;
    int maxSizeKb;
    std::vector<std::string> allowedFormats;
    bool mipmapsRequired;
};

struct AudioConfig {
    ConfigMetadata metadata;
    int sampleRate;
    std::vector<std::string> channels;
    int maxDurationSeconds;
};

struct ToolConfig {
    BaseConfig baseConfig;
};
