add_executable(AssetTools
    src/main.cpp
    src/ScanMode.cpp
    src/ValidateMode.cpp
    src/InspectMode.cpp
)

target_link_libraries(AssetTools
    PRIVATE core
)
