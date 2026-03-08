#!/usr/bin/env bash
# Build script for debugging
set -euo pipefail

SCRIPT_DIR=$(dirname "$0")
PROJECT_ROOT=$(realpath "$SCRIPT_DIR/..")

echo "=== AssetTools Build (Debug) ==="

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build"
cmake --build "$PROJECT_ROOT/build" --config Debug --parallel

echo "Build completed successfully."
