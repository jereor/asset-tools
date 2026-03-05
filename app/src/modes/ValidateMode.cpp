#include "ValidateMode.h"

#include "ToolModeFactory.h"
#include "core/Asset.h"
#include "core/AssetParser.h"
#include "core/TextureAssetValidator.h"
#include "core/TextureSizeRule.h"

#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <unordered_set>

namespace
{
    bool g_validateRegistered = ToolModeFactory::Register(ValidateMode::GetFactoryName(), ValidateMode::Create);
}

std::string ValidateMode::GetFactoryName()
{
    return "validate";
}

std::unique_ptr<ToolMode> ValidateMode::Create(const ToolConfig& config)
{
    return std::make_unique<ValidateMode>(config);
}

namespace
{
    static inline const std::filesystem::path kProjectRoot = PROJECT_ROOT;

    std::filesystem::path ResolveAssetPath(std::string_view assetFilePath, ToolConfig config)
    {
        std::filesystem::path path(assetFilePath);
        
        if (path.is_absolute()) {
            return path;
        }

        std::filesystem::path assetsRoot = kProjectRoot / config.baseConfig.paths.assetsRoot;
        return assetsRoot / path;
    }

    std::string GetFileExtension(const std::filesystem::path& filePath)
    {
        std::string ext = filePath.extension().string();

        // Convert extension to lowercase (for case-insensitive match)
        std::transform(ext.begin(), ext.end(), ext.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return ext;
    }

    // TODO: Get supported extensions from configs
    static constexpr std::string_view supportedExtensions[] = {
        ".png", ".jpg", ".wav"
    };

    bool IsSupportedExtension(std::string_view ext)
    {
        return std::find(std::begin(supportedExtensions),  std::end(supportedExtensions), ext) 
                != std::end(supportedExtensions);
    }

    std::string SupportedExtensionsToString()
    {
        std::ostringstream out;
        bool first = true;

        for (std::string_view ext : supportedExtensions)
        {
            if (!first)
                out << ", ";
            out << ext;
            first = false;
        }

        return out.str();
    }
}

core::ToolResult ValidateMode::Run(const std::vector<std::string>& args)
{
    core::ToolResult toolResult;

    if (args.size() != 1)
    {
		toolResult.AddError("Invalid number of arguments. Expected 1 argument: <asset_file>");
		toolResult.exitCode = core::ExitCode::InvalidArguments;
        return toolResult;
    }

    std::filesystem::path assetPath = ResolveAssetPath(args[0], m_config);
    if (!std::filesystem::exists(assetPath))
    {
        toolResult.AddError("Asset not found: {}", assetPath.string());
        toolResult.exitCode = core::ExitCode::FileNotFound;
        return toolResult;
    }

    if (!std::filesystem::is_regular_file(assetPath))
    {
        toolResult.AddError("The specified path is not a regular file: {}", assetPath.string());
        toolResult.exitCode = core::ExitCode::InvalidArguments;
        return toolResult;
    }

    std::string fileExt = GetFileExtension(assetPath);
    if (!IsSupportedExtension(fileExt))
    {
        toolResult.AddError("Unsupported file extension: {}", fileExt);
        toolResult.AddInfo("Supported extensions: " + SupportedExtensionsToString());
        toolResult.exitCode = core::ExitCode::UnsupportedFormat;
        return toolResult;
    }
    
    std::ifstream file(assetPath);
    if (!file)
    {
        toolResult.AddError("Failed to find asset file: {}", assetPath.string());
        toolResult.exitCode = core::ExitCode::FileNotFound;
        return toolResult;
    }

    // -- Parse asset file into struct --
    core::AssetParser assetParser;
    std::variant<std::monostate, core::TextureAsset, core::AudioAsset> asset = assetParser.ParseAsset(assetPath);

    // -- Get the asset type --
    core::AssetType assetType = core::AssetType::Unknown;
    if (auto textureAssetPtr = std::get_if<core::TextureAsset>(&asset))
    {
        assetType = core::AssetType::Texture;
        toolResult.AddInfo("Parsed a texture asset: {}", textureAssetPtr->file.name);
    }
    else if (auto audioAssetPtr = std::get_if<core::AudioAsset>(&asset))
    {
        assetType = core::AssetType::Audio;
        toolResult.AddInfo("Parsed an audio asset: {}", audioAssetPtr->file.name);
    }

    // -- Get validation configs --
    TextureConfig::TextureValidationConfig textureValidationConfig;
    AudioConfig::AudioValidationConfig audioValidationConfig;
    if (assetType == core::AssetType::Texture)
    {
        if (!m_config.textureConfig)
        {
            toolResult.AddError("No texture config provided. Please provide it to validate texture assets. Use --help to see how.");
            toolResult.exitCode = core::ExitCode::InvalidArguments;
            return toolResult;
        }

        textureValidationConfig = m_config.textureConfig.value().validation;
    }
    else if (assetType == core::AssetType::Audio)
    {
        if (!m_config.audioConfig)
        {
            toolResult.AddError("No audio config provided. Please provide it to validate audio assets. Use --help to see how.");
            toolResult.exitCode = core::ExitCode::InvalidArguments;
            return toolResult;
        }

        audioValidationConfig = m_config.audioConfig.value().validation;
    }

    // -- Validate assets --
    std::vector<core::ValidationResult> results;
    if (assetType == core::AssetType::Texture)
    {
        core::TextureAssetValidator validator;
        validator.AddRule(std::make_unique<core::TextureSizeRule>(textureValidationConfig.maxSizeKb));
        results = validator.Validate(std::get<core::TextureAsset>(asset));
    }

    // TODO: Validate audio assets with new AssetValidator 

    bool validationFailed = false;
    for (const core::ValidationResult& result : results)
    {
        if (!result.success)
        {
            toolResult.AddError(result.message);
            validationFailed = true;
        }
    }

    if (validationFailed)
    {
		toolResult.exitCode = core::ExitCode::ValidationFailed;
        return toolResult;
    }

    toolResult.AddInfo("Asset validation completed successfully with no errors.");
    toolResult.exitCode = core::ExitCode::Success;
    return toolResult;
}
