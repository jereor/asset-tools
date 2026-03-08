#!/usr/bin/env bash
# Build script for when something feels off (clean binaries and rebuild all)
set -euo pipefail

SCRIPT_DIR=$(dirname "$0")
PROJECT_ROOT=$(realpath "$SCRIPT_DIR/..")

echo "=== AssetTools Clean Build ==="

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build"
cmake --build "$PROJECT_ROOT/build" --config Release --clean-first

echo "Build completed successfully."
