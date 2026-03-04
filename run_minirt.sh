#!/usr/bin/env bash
set -euo pipefail

# Launch MiniRT: builds if needed and runs with the provided scene
# Usage: ./run_minirt.sh [scene_file]

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$PROJECT_DIR"

SCENE_FILE="${1:-tests/test1.rt}"

if [ ! -f "$SCENE_FILE" ]; then
  echo "Scene file not found: $SCENE_FILE" >&2
  echo "Provide a .rt file, e.g.: ./run_minirt.sh tests/test1.rt" >&2
  exit 1
fi

make
./bin/miniRT "$SCENE_FILE"
