#pragma once
#include "ToolMode.h"

class ScanMode : public ToolMode
{
public:
    core::ExitCode Run(const std::vector<std::string>& args) override;
};
