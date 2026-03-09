#!/usr/bin/env sh
# Interactive build - runs build and waits for user input (useful when running outside a terminal)
set -euo pipefail

SCRIPT_DIR=$(dirname "$0")
"$SCRIPT_DIR/build.sh"

read -rp "Press Enter to continue..."
