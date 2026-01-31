:: Build script for when something feels off (clean binaries and rebuild all)

@echo off
setlocal

echo === AssetTools Clean Build ===

cmake -S . -B build || exit /b 1
cmake --build build --config Release --clean-first || exit /b 1

echo Build completed successfully.
endlocal
