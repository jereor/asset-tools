#!/usr/bin/env sh
# Build script for when you have CMake issues (complete reset, remove the build folder)
set -euo pipefail

SCRIPT_DIR=$(dirname "$0")
PROJECT_ROOT=$(realpath "$SCRIPT_DIR/..")

echo "=== AssetTools Fresh Build (removes all dependencies) ==="

if [ -d "$PROJECT_ROOT/build" ]; then
    echo "Removing build directory..."
    rm -rf "$PROJECT_ROOT/build"
fi

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build"
cmake --build "$PROJECT_ROOT/build" --config Release --parallel

echo "Build completed successfully."
