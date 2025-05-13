#!/usr/bin/env bash
set -euo pipefail

BUILD_PATH="out/build"
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$PROJECT_ROOT/$BUILD_PATH"
cmake --build . --parallel 4