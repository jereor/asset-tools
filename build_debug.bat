:: Build script for debugging
@echo off
setlocal

echo === AssetTools Build (Debug) ===

cmake -S . -B build || exit /b 1
cmake --build build --config Debug --parallel || exit /b 1

echo Build completed successfully.
endlocal
