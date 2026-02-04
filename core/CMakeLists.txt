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

# Enable strict warnings
if(MSVC)
    target_compile_options(core PRIVATE /W4)
else()
    target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(core 
    PUBLIC yaml-cpp
)
