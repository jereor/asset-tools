#!/usr/bin/env bash
# Build script for when you have CMake issues (complete reset, removes the build folder)
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"

echo "=== AssetTools Fresh Build (hard reset) ==="

if [[ -d "$PROJECT_ROOT/build" ]]; then
    echo "Removing build directory..."
    rm -rf "$PROJECT_ROOT/build"
fi

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v ninja >/dev/null || echo "Warning: Ninja not found (CMake may fallback)"

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build" -G Ninja
cmake --build "$PROJECT_ROOT/build" --config Release --parallel

echo "Build completed successfully."
