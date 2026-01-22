add_executable(AssetTools
    src/InspectMode.cpp
    src/main.cpp
    src/ScanMode.cpp
    src/ToolModeFactory.cpp
    src/ValidateMode.cpp
)

target_link_libraries(AssetTools
    PRIVATE core
)
