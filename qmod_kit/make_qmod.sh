#!/usr/bin/env bash
# Packs a built libvrm-qavatars.so into a .qmod (a .qmod is just a zip).
# Usage (from the repo root, after the .so is built):  bash qmod_kit/make_qmod.sh [path/to/libvrm-qavatars.so]
set -e
cd "$(dirname "$0")/.."

SO="${1:-}"
if [ -z "$SO" ]; then
  for c in build/libvrm-qavatars.so libvrm-qavatars.so; do [ -f "$c" ] && SO="$c" && break; done
fi
if [ -z "$SO" ] || [ ! -f "$SO" ]; then
  echo "ERROR: libvrm-qavatars.so not found. Build first (qpm s build) or pass the path as an argument." >&2
  exit 1
fi
[ -f shaders.sbund ] || { echo "ERROR: shaders.sbund missing" >&2; exit 1; }

OUT="VRM_Qavatars_Revived_1.40.8.qmod"
TMP="$(mktemp -d)"
cp qmod_kit/mod.json "$TMP/mod.json"
cp "$SO" "$TMP/libvrm-qavatars.so"
cp shaders.sbund "$TMP/shaders.sbund"

rm -f "$OUT"
( cd "$TMP" && zip -X -q "$OLDPWD/$OUT" mod.json libvrm-qavatars.so shaders.sbund )
rm -rf "$TMP"
echo "Created $OUT"
unzip -l "$OUT"
