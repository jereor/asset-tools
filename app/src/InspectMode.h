#pragma once
#include "ToolMode.h"

class InspectMode : public ToolMode
{
public:
    core::ExitCode Run(const std::vector<std::string>& args) override;
};
