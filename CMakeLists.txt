cmake_minimum_required(VERSION 3.16...4.2)
project(AssetTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and link yaml-cpp, fetch from Git if not found
include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG c9371de7836d113c0b14bfa15ca70f00ebb3ac6f  # 2025-4-30, post 0.8.0 CMake fix
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(yaml-cpp)

# Suppress warnings for third-party libraries
if(MSVC)
    target_compile_options(yaml-cpp PRIVATE /W0)
else()
    target_compile_options(yaml-cpp PRIVATE -w)
endif()

# Suppress system header warnings on MSVC
add_compile_options(
    $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets> # Treat headers included with <> as external headers
    $<$<CXX_COMPILER_ID:MSVC>:/external:W0> # Set the warning level to 0 (none) for external headers
)

add_subdirectory(core)
add_subdirectory(app)