#include "ToolModeFactory.h"

std::unordered_map<std::string, ToolModeFactory::CreateMethod>& ToolModeFactory::GetModesMap()
{
	// Static local variables are initialized on first use
	// This guarantees s_modes exists before any registration
	static std::unordered_map<std::string, ToolModeFactory::CreateMethod> s_modes;
	return s_modes;
}

bool ToolModeFactory::Register(const std::string& name, CreateMethod createMethod)
{
	auto& modes = GetModesMap();
	
	if (auto it = modes.find(name); it == modes.end())
	{
		modes[name] = createMethod;
		return true;
	}
	return false;
}

std::unique_ptr<ToolMode> ToolModeFactory::Create(const std::string& name, const ToolConfig& toolConfig)
{
	auto& modes = GetModesMap();

	if (auto it = modes.find(name); it != modes.end())
		return it->second(toolConfig); // call the Create function

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