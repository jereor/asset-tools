#!/usr/bin/env bash
# Build script for when something feels off (clean binaries and rebuild all)
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"

echo "=== AssetTools Clean Build (soft reset) ==="

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v ninja >/dev/null || echo "Warning: Ninja not found (CMake may fallback)"

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build" -G Ninja
cmake --build "$PROJECT_ROOT/build" --config Release --parallel --clean-first

echo "Build completed successfully."
