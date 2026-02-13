#pragma once
#include "ToolConfig.h"
#include "core/ToolResult.h"

#include <expected>
#include <filesystem>

class ConfigLoader
{
public:
	static std::expected<BaseConfig, core::ToolResult> LoadBaseConfig(std::string_view configFilePath);
	static std::expected<TextureConfig, core::ToolResult> LoadTextureConfig(std::string_view configFilePath);
	static std::expected<AudioConfig, core::ToolResult> LoadAudioConfig(std::string_view configFilePath);

	static std::filesystem::path ResolveConfigPath(std::string_view configFilePath);

private:
	static inline const std::filesystem::path kProjectRoot = PROJECT_ROOT;
    static inline const std::filesystem::path kConfigsFolder = kProjectRoot / "configs";
};
