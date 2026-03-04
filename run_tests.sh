#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$PROJECT_DIR"

SCENES_DIR="tests"
BIN="bin/miniRT"

if [ ! -d "$SCENES_DIR" ]; then
  echo "No existe el directorio de escenas: $SCENES_DIR" >&2
  exit 1
fi

make -s

if [ ! -x "$BIN" ]; then
  echo "No se encontró binario en $BIN" >&2
  exit 1
fi

shopt -s nullglob
scenes=("$SCENES_DIR"/*.rt)
shopt -u nullglob

if [ ${#scenes[@]} -eq 0 ]; then
  echo "No se encontraron archivos .rt en $SCENES_DIR" >&2
  exit 1
fi

for scene in "${scenes[@]}"; do
  echo "\n=== Ejecutando: $scene ==="
  if ! "$BIN" "$scene"; then
    echo "Fallo al ejecutar $scene" >&2
  fi
done
