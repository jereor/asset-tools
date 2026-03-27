#!/usr/bin/env bash
# Build script for debugging
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"

echo "=== AssetTools Build (Debug) ==="

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v ninja >/dev/null || echo "Warning: Ninja not found (CMake may fallback)"

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build" -G Ninja
cmake --build "$PROJECT_ROOT/build" --config Debug --parallel

echo "Build completed successfully."
