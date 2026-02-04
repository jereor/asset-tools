#include "ConfigLoader.h"

#include <yaml-cpp/yaml.h>

#include <fstream>
#include <string>
#include <sstream>
#include <format>

namespace YAML {
    template<>
    struct convert<ConfigMetadata> {
        static bool decode(const Node& node, ConfigMetadata& metadata) {
            if (!node["name"] || !node["description"] || !node["version"]) {
                return false;
            }

            metadata.name = node["name"].as<std::string>();
            metadata.description = node["description"].as<std::string>();
            metadata.version = node["version"].as<float>();

            return true;
        }
    };

    template<>
    struct convert<BaseConfig::BaseValidationConfig> {
        static bool decode(const Node& node, BaseConfig::BaseValidationConfig& validationConfig) {
            if (!node["failOnWarning"]) {
                return false;
            }

            validationConfig.failOnWarning = node["failOnWarning"].as<bool>();

            return true;
        }
    };

    template<>
    struct convert<BaseConfig::BasePathConfig> {
        static bool decode(const Node& node, BaseConfig::BasePathConfig& pathConfig) {
            if (!node["assetsRoot"]) {
                return false;
            }

            pathConfig.assetsRoot = node["assetsRoot"].as<std::string>();

            return true;
        }
    };

    template<>
    struct convert<BaseConfig::BaseLoggingConfig> {
        static bool decode(const Node& node, BaseConfig::BaseLoggingConfig& loggingConfig) {
            if (!node["verbose"]) {
                return false;
            }

            loggingConfig.verbose = node["verbose"].as<bool>();

            return true;
        }
    };

    template<>
    struct convert<BaseConfig> {
        static bool decode(const Node& node, BaseConfig& config) {
            if (!node["metadata"] || !node["validation"] || !node["paths"] || !node["logging"]) {
                return false;
            }

            config.metadata = node["metadata"].as<ConfigMetadata>();
            config.validation = node["validation"].as<BaseConfig::BaseValidationConfig>();
            config.paths = node["paths"].as<BaseConfig::BasePathConfig>();
            config.logging = node["logging"].as<BaseConfig::BaseLoggingConfig>();

            return true;
        }
    };

    template<>
    struct convert<TextureConfig> {
        static bool decode(const Node& node, TextureConfig& config) {
            if ( !node["metadata"] || !node["maxSizeKb"] || !node["allowedFormats"] || !node["mipmapsRequired"]) {
                return false;
            }

            config.metadata = node["metadata"].as<ConfigMetadata>();
            config.maxSizeKb = node["maxSizeKb"].as<int>();
            config.allowedFormats = node["allowedFormats"].as<std::vector<std::string>>();
            config.mipmapsRequired = node["mipmapsRequired"].as<bool>();

            return true;
        }
    };

    template<>
    struct convert<AudioConfig> {
        static bool decode(const Node& node, AudioConfig& config) {
            if (!node["metadata"] || !node["sampleRate"] || !node["channels"] || !node["maxDurationSeconds"]) {
                return false;
            }

            config.metadata = node["metadata"].as<ConfigMetadata>();
            config.sampleRate = node["sampleRate"].as<int>();
            config.channels = node["channels"].as<std::vector<std::string>>();
            config.maxDurationSeconds = node["maxDurationSeconds"].as<int>();

            return true;
        }
    };
}

std::expected<ToolConfig, core::ToolResult> ConfigLoader::LoadConfig(const std::string& configFilePath)
{
    core::ToolResult toolResult;
    try {
        YAML::Node configNode = YAML::LoadFile(configFilePath);
        auto baseConfig = configNode.as<BaseConfig>();
        auto toolConfig = ToolConfig{ .baseConfig = baseConfig };
        return toolConfig;
    }
    catch (const YAML::BadFile&) {
        toolResult.AddError("Config file not found: {}", configFilePath);
        toolResult.exitCode = core::ExitCode::ConfigNotFound;
        return std::unexpected(toolResult);

    }
    catch (const YAML::ParserException& e) {
        toolResult.AddError("Config parse error at line {}: {}", e.mark.line, e.msg);
        toolResult.exitCode = core::ExitCode::ConfigParseError;
        return std::unexpected(toolResult);

    }
    catch (const YAML::Exception& e) {
        toolResult.AddError("Config validation error: {}", e.what());
        toolResult.exitCode = core::ExitCode::ConfigValidationError;
        return std::unexpected(toolResult);
    }
    catch (...) {
        toolResult.AddError("Config loader encountered an unknown error");
        toolResult.exitCode = core::ExitCode::ToolFailure;
        return std::unexpected(toolResult);
    }
}
