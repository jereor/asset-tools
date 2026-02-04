#pragma once
#include "ToolMode.h"

#include "ToolModeFactory.h"
#include "../config/ToolConfig.h"

#include <string>
#include <memory>

class InspectMode final : public ToolMode
{
public:
    explicit InspectMode(const ToolConfig& config) : m_config(config) {}

    core::ToolResult Run(const std::vector<std::string>& args) override;

    static std::string GetFactoryName();
    static std::unique_ptr<ToolMode> Create(const ToolConfig& config);
private:
    ToolConfig m_config;
};
