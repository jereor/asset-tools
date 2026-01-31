add_executable(AssetTools
    src/main.cpp
    src/modes/InspectMode.cpp
    src/modes/ScanMode.cpp
    src/modes/ToolModeFactory.cpp
    src/modes/ValidateMode.cpp
)

target_link_libraries(AssetTools
    PRIVATE core
    PRIVATE yaml-cpp::yaml-cpp
)
