add_executable(AssetTools
    src/main.cpp
    src/ScanMode.cpp
    src/ValidateMode.cpp
)

target_link_libraries(AssetTools
    PRIVATE core
)
