#pragma once
#include "ToolMode.h"

class ValidateMode : public ToolMode
{
public:
    core::ExitCode Run(const std::vector<std::string>& args) override;
};
