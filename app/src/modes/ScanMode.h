#pragma once
#include "ToolMode.h"

#include "ToolModeFactory.h"

#include <string>
#include <memory>

class ScanMode final : public ToolMode
{
public:
    core::ToolResult Run(const std::vector<std::string>& args) override;

    static std::string GetFactoryName();
    static std::unique_ptr<ToolMode> Create();
};
