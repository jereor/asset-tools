#pragma once
#include "ToolConfig.h"
#include "core/ToolResult.h"

#include <expected>

class ConfigLoader
{
public:
	static std::expected<ToolConfig, core::ToolResult> LoadConfig(std::string_view configFilePath);
};
