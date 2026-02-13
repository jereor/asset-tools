add_executable(AssetTools
    src/main.cpp
    src/modes/InspectMode.cpp
    src/modes/ScanMode.cpp
    src/modes/ToolModeFactory.cpp
    src/modes/ValidateMode.cpp
    src/config/ConfigLoader.cpp
)

target_compile_definitions(AssetTools PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

target_include_directories(AssetTools PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable strict warnings
if(MSVC)
    target_compile_options(AssetTools PRIVATE /W4)
else()
    target_compile_options(AssetTools PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(AssetTools
    PRIVATE core
    PRIVATE yaml-cpp::yaml-cpp
)
