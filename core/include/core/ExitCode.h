#pragma once
namespace core
{
    // ExitCode ranges:
    // 0–99   : Success / informational
    // 100–199: User / content errors
    // 200–299: Tool / infrastructure errors
    enum class ExitCode
    {
        Success = 0,

        InvalidArguments = 100,
        FileNotFound = 101,
        UnsupportedFormat = 102,
        ValidationFailed = 103,
        ConfigNotFound = 104,
        ConfigParseError = 105,
        ConfigValidationError = 106,

        ToolFailure = 200,
    };

    enum class ExitCodeCategory
    {
        Success,
        UserError,
        ToolError
    };

    constexpr ExitCodeCategory GetExitCodeCategory(ExitCode exitCode)
    {
        int value = static_cast<int>(exitCode);
        if (value == 0) return ExitCodeCategory::Success;
        if (value < 200) return ExitCodeCategory::UserError;
        return ExitCodeCategory::ToolError;
    }
}
