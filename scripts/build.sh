#!/usr/bin/env bash
# Build script for daily work (fastest, only rebuilds changed files)
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"

echo "=== AssetTools Build (Release) ==="

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v ninja >/dev/null || echo "Warning: Ninja not found (CMake may fallback)"

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build" -G Ninja
cmake --build "$PROJECT_ROOT/build" --config Release --parallel

echo "Build completed successfully."
