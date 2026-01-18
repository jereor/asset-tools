#include "ToolModeFactory.h"

std::unordered_map<std::string, std::unique_ptr<ToolMode>(*)()>& ToolModeFactory::GetModesMap()
{
	// Static local variables are initialized on first use
	// This guarantees s_modes exists before any registration
	static std::unordered_map<std::string, std::unique_ptr<ToolMode>(*)()> s_modes;
	return s_modes;
}

bool ToolModeFactory::Register(const std::string& name, std::unique_ptr<ToolMode>(*createMethod)())
{
	auto& modes = GetModesMap();
	
	if (auto it = modes.find(name); it == modes.end())
	{
		modes[name] = createMethod;
		return true;
	}
	return false;
}

std::unique_ptr<ToolMode> ToolModeFactory::Create(const std::string& name)
{
	auto& modes = GetModesMap();

	if (auto it = modes.find(name); it != modes.end())
		return it->second(); // call the Create function

	return nullptr;
}

std::vector<std::string> ToolModeFactory::GetAvailableModes()
{
	auto& modes = GetModesMap();
	std::vector<std::string> result;
	result.reserve(modes.size());
	
	for (const auto& [name, _] : modes)
		result.push_back(name);
	
	return result;
}