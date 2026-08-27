#!/usr/bin/env bash
set -euo pipefail

# Set BUILD_PATH from env or default
BUILD_PATH="out/build"
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

if [[ "${1:-}" == "--clean" ]]; then
    rm -rf "$PROJECT_ROOT/$BUILD_PATH"
elif [[ $# -gt 0 ]]; then
    echo "Usage: $0 [--clean]" >&2
    exit 2
fi

# Step 1: Configure
mkdir -p "$PROJECT_ROOT/$BUILD_PATH"
cd "$PROJECT_ROOT/$BUILD_PATH"
cmake --version
cmake "$PROJECT_ROOT" -DCMAKE_BUILD_TYPE=Debug

# Step 2: Build
cmake --build . --parallel 4

# Step 3: Test
ctest --verbose --output-on-failure -C Debug
