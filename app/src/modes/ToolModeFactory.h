#pragma once

#include "ToolMode.h"
#include "../config/ToolConfig.h"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class ToolModeFactory
{
public:
	ToolModeFactory() = delete;

	using CreateMethod = std::unique_ptr<ToolMode>(*)(const ToolConfig&);

	static bool Register(const std::string& name, CreateMethod createMethod);
	static std::unique_ptr<ToolMode> Create(const std::string& name, const ToolConfig& toolConfig);
	static std::vector<std::string> GetAvailableModes();

private:
	static std::unordered_map<std::string, CreateMethod>& GetModesMap();
};