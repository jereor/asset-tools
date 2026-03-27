cmake_minimum_required(VERSION 3.16...4.2)
project(AssetTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress system header warnings on MSVC
add_compile_options(
    $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets> # Treat headers included with <> as external headers
    $<$<CXX_COMPILER_ID:MSVC>:/external:W0> # Set the warning level to 0 (none) for external headers
)

add_subdirectory(core)
add_subdirectory(app)