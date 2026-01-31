cmake_minimum_required(VERSION 3.16...4.2)
project(AssetTools)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Include yaml-cpp
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG c9371de7836d113c0b14bfa15ca70f00ebb3ac6f  # 2025-4-30, post 0.8.0 CMake fix
)
set(CMAKE_POLICY_DEFAULT_CMP0169 OLD)
FetchContent_MakeAvailable(yaml-cpp)

# Suppress warnings for third-party libraries
if(MSVC)
    target_compile_options(yaml-cpp PRIVATE /W0)
else()
    target_compile_options(yaml-cpp PRIVATE -w)
endif()

add_subdirectory(core)
add_subdirectory(app)