#pragma once

#include "core/ExitCode.h"
#include "core/ToolResult.h"
#include <vector>
#include <string>

class ToolMode
{
public:
    virtual ~ToolMode() = default;

    virtual core::ToolResult Run(const std::vector<std::string>& args) = 0;
};
