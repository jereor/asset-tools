#pragma once
#include "core/ExitCode.h"
#include "core/Logger.h"
#include <vector>
#include <string>
#include <algorithm>

namespace core
{
    struct Diagnostic
    {
        core::LogLevel level;
        std::string message;
    };

    struct ToolResult
    {
        core::ExitCode exitCode = core::ExitCode::Success;
        std::vector<Diagnostic> diagnostics;

        void AddInfo(std::string msg)
        {
            AddDiagnostic(core::LogLevel::Info, std::move(msg));
        }

        void AddWarning(std::string msg)
        {
            AddDiagnostic(core::LogLevel::Warning, std::move(msg));
        }

        void AddError(std::string msg)
        {
            AddDiagnostic(core::LogLevel::Error, std::move(msg));
        }

        bool HasErrors() const noexcept
        {
            return std::any_of(diagnostics.cbegin(), diagnostics.cend(),
                [](const auto& d) { return d.level == core::LogLevel::Error; });
        }

        core::ExitCodeCategory GetExitCodeCategory() const noexcept
        {
            return core::GetExitCodeCategory(exitCode);
        }

        bool IsSuccess() const noexcept { return exitCode == core::ExitCode::Success; }
        bool IsUserError() const noexcept { return GetExitCodeCategory() == core::ExitCodeCategory::UserError; }
        bool IsToolError() const noexcept { return GetExitCodeCategory() == core::ExitCodeCategory::ToolError; }

    private:
        void AddDiagnostic(core::LogLevel level, std::string msg)
        {
            diagnostics.emplace_back(Diagnostic{ level, std::move(msg) });
        }
    };
}
