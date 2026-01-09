add_library(core STATIC
    src/Version.cpp
    src/Logger.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
