#!/usr/bin/env bash
# Build script for daily work (fastest, only rebuilds changed files)
set -euo pipefail

SCRIPT_DIR=$(dirname "$0")
PROJECT_ROOT=$(realpath "$SCRIPT_DIR/..")

echo "=== AssetTools Build (Release) ==="

cmake -S "$PROJECT_ROOT" -B "$PROJECT_ROOT/build"
cmake --build "$PROJECT_ROOT/build" --config Release --parallel

echo "Build completed successfully."
