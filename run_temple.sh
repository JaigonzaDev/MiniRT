#!/usr/bin/env bash
set -euo pipefail

SCENE="tests/scenes/mandatory/temple.rt"
BIN="./miniRT"

if [[ ! -x "$BIN" ]]; then
  echo "Building miniRT..." >&2
  make >/dev/null
fi

if [[ ! -f "$SCENE" ]]; then
  echo "Scene not found: $SCENE" >&2
  exit 1
fi

echo "Running: $BIN $SCENE" >&2
exec $BIN "$SCENE"
