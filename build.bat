@echo off
setlocal

echo === AssetTools Build Script ===

set BUILD_DIR=build

if exist %BUILD_DIR% (
    echo Removing existing build directory...
    rmdir /s /q %BUILD_DIR%
)

echo Creating build directory...
mkdir %BUILD_DIR%
cd %BUILD_DIR% || exit /b 1

echo Configuring project with CMake...
cmake .. || exit /b 1

echo Building project...
cmake --build . || exit /b 1

echo Build completed successfully.
endlocal
