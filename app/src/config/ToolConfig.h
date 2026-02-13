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
    struct TextureValidationConfig {
        std::vector<std::string> allowedFormats;
        int maxSizeKb;
        bool mipmapsRequired;
    };

    ConfigMetadata metadata;
    TextureValidationConfig validation;
};

struct AudioConfig {
    struct AudioValidationConfig {
        std::vector<std::string> channels;
        int sampleRate;
        int maxDurationSeconds;
    };
    
    ConfigMetadata metadata;
    AudioValidationConfig validation;
};

struct ToolConfig {
    BaseConfig baseConfig;
    TextureConfig textureConfig;
    AudioConfig audioConfig;
};
