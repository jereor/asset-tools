:: Build script for when you have CMake issues (complete reset, remove the build folder)

@echo off
setlocal

echo === AssetTools Fresh Build (removes all dependencies) ===

if exist build (
    echo Removing build directory...
    rmdir /s /q build
)

cmake -S . -B build || exit /b 1
cmake --build build --config Release --parallel || exit /b 1

echo Build completed successfully.
endlocal
