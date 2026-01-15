#pragma once

namespace core
{
    enum class ExitCode
    {
        Success = 0,
        InvalidArguments = 1,
        ToolFailure = 2,
        FileNotFound = 3,
        UnsupportedFormat = 4
    };
}
