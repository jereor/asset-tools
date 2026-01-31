:: Build script for daily work (fastest, only rebuilds changed files)

@echo off
setlocal

echo === AssetTools Build (Release) ===

cmake -S . -B build || exit /b 1
cmake --build build --config Release --parallel || exit /b 1

echo Build completed successfully.
endlocal