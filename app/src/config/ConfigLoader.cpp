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
    struct convert<TextureConfig::TextureValidationConfig> {
        static bool decode(const Node& node, TextureConfig::TextureValidationConfig& validationConfig) {
            if (!node["allowedFormats"] || !node["maxSizeKb"] || !node["mipmapsRequired"]) {
                return false;
            }

            validationConfig.allowedFormats = node["allowedFormats"].as<std::vector<std::string>>();
            validationConfig.maxSizeKb = node["maxSizeKb"].as<int>();
            validationConfig.mipmapsRequired = node["mipmapsRequired"].as<bool>();

            return true;
        }
    };

    template<>
    struct convert<TextureConfig> {
        static bool decode(const Node& node, TextureConfig& config) {
            if ( !node["metadata"] || !node["validation"]) {
                return false;
            }

            config.metadata = node["metadata"].as<ConfigMetadata>();
            config.validation = node["validation"].as<TextureConfig::TextureValidationConfig>();

            return true;
        }
    };

    template<>
    struct convert<AudioConfig::AudioValidationConfig> {
        static bool decode(const Node& node, AudioConfig::AudioValidationConfig& validationConfig) {
            if (!node["channels"] || !node["sampleRate"] || !node["maxDurationSeconds"]) {
                return false;
            }

            validationConfig.channels = node["channels"].as<std::vector<std::string>>();
            validationConfig.sampleRate = node["sampleRate"].as<int>();
            validationConfig.maxDurationSeconds = node["maxDurationSeconds"].as<int>();

            return true;
        }
    };

    template<>
    struct convert<AudioConfig> {
        static bool decode(const Node& node, AudioConfig& config) {
            if (!node["metadata"] || !node["validation"]) {
                return false;
            }

            config.metadata = node["metadata"].as<ConfigMetadata>();
            config.validation = node["validation"].as<AudioConfig::AudioValidationConfig>();

            return true;
        }
    };
}

std::filesystem::path ConfigLoader::ResolveConfigPath(std::string_view configFilePath)
{
    std::filesystem::path path(configFilePath);
    
    if (path.is_absolute()) {
        return path;
    }
    
    return kConfigsFolder / path;
}

template<typename T>
std::expected<T, core::ToolResult> LoadConfigFromFile(std::string_view configFilePath)
{
    std::filesystem::path resolvedPath = ConfigLoader::ResolveConfigPath(configFilePath);
    try {
        YAML::Node configNode = YAML::LoadFile(resolvedPath.string());
        T config = configNode.as<T>();
        return config;
    }
    catch (const YAML::BadFile& e) {
        core::ToolResult toolResult;
        toolResult.AddError("Failed to open config file '{}': {}", resolvedPath.string(), e.what());
        toolResult.exitCode = core::ExitCode::FileNotFound;
        return std::unexpected(toolResult);
    }
    catch (const YAML::ParserException& e) {
        core::ToolResult toolResult;
        toolResult.AddError("YAML parsing error in file '{}': {}", resolvedPath.string(), e.what());
        toolResult.exitCode = core::ExitCode::ConfigParseError;
        return std::unexpected(toolResult);
    }
    catch (const YAML::Exception& e) {
        core::ToolResult toolResult;
        toolResult.AddError("YAML error in file '{}': {}", resolvedPath.string(), e.what());
        toolResult.exitCode = core::ExitCode::ConfigParseError;
        return std::unexpected(toolResult);
    }
    catch (...) {
        core::ToolResult toolResult;
        toolResult.AddError("Config loader encountered an unknown error");
        toolResult.exitCode = core::ExitCode::ToolFailure;
        return std::unexpected(toolResult);
    }
}

std::expected<BaseConfig, core::ToolResult> ConfigLoader::LoadBaseConfig(std::string_view configFilePath)
{
    return LoadConfigFromFile<BaseConfig>(configFilePath);
}

std::expected<TextureConfig, core::ToolResult> ConfigLoader::LoadTextureConfig(std::string_view configFilePath)
{
    return LoadConfigFromFile<TextureConfig>(configFilePath);
}

std::expected<AudioConfig, core::ToolResult> ConfigLoader::LoadAudioConfig(std::string_view configFilePath)
{
    return LoadConfigFromFile<AudioConfig>(configFilePath);
}
