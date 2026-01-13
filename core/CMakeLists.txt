add_library(core STATIC
    src/AssetParser.cpp
    src/AssetValidator.cpp
    src/Logger.cpp
    src/TextureSizeRule.cpp
    src/Version.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
