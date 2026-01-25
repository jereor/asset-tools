#pragma once

#include "ToolMode.h"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class ToolModeFactory
{
public:
	ToolModeFactory() = delete;

	static bool Register(const std::string& name, std::unique_ptr<ToolMode>(*funcCreate)());
	static std::unique_ptr<ToolMode> Create(const std::string& name);
	static std::vector<std::string> GetAvailableModes();

private:
	static std::unordered_map<std::string, std::unique_ptr<ToolMode>(*)()>& GetModesMap();
};