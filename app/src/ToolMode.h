#pragma once

#include "core/ExitCode.h"
#include <vector>
#include <string>

class ToolMode
{
public:
    virtual ~ToolMode() = default;

    virtual core::ExitCode Run(const std::vector<std::string>& args) = 0;
};
