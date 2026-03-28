# Dev Decisions

## Decision
- Chose: vcpkg > CMake FetchContent
- Because: faster with caching and scales better
- Tradeoff: upfront setup

## Decision
- Chose: vcpkg > conan
- Because: easier to learn, can switch to conan later when needed
- Tradeoff: simple workflow and clean CMake integration | hard to package internal packages and limited versioning
