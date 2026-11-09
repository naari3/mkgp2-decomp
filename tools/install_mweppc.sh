#!/bin/sh
# Fetch the C source of the compiler we match against: doldecomp/mweppc, a CC0
# (public domain) decompilation of mwcceppc.exe GC/2.0, 2.0p2, 2.5, 2.6 and 2.7.
# Read it when diagnosing a scheduling / register-allocation / coalescing near
# miss; the index of where to look is docs/mwcc_internals.md.
#
#   sh tools/install_mweppc.sh          clone/update build/mweppc at the pinned commit
#   sh tools/install_mweppc.sh --build  also try to build the GC/2.6 clang/native compiler
#
# The source alone needs only github.com. Building needs clang, lld, llvm, uv
# AND archive.org (it downloads the CodeWarrior Pro 5 MSL runtime); the cloud
# containers' network policy blocks archive.org, so --build only works where it
# is reachable (a local machine, or an environment that allows it).
set -e
ROOT=$(cd "$(dirname "$0")/.." && pwd)
DIR="$ROOT/build/mweppc"
COMMIT=919828d97d33d236da675824d43c5d57332afe74   # 2026-11-03
if [ ! -d "$DIR/.git" ]; then
  mkdir -p "$ROOT/build"
  git clone -q https://github.com/doldecomp/mweppc "$DIR"
fi
if ! git -C "$DIR" cat-file -e "$COMMIT^{commit}" 2>/dev/null; then
  git -C "$DIR" fetch -q origin
fi
git -C "$DIR" -c advice.detachedHead=false checkout -q "$COMMIT"
echo "mweppc source at build/mweppc ($COMMIT); start with docs/mwcc_internals.md"
if [ "$1" = "--build" ]; then
  cd "$DIR"
  uv sync
  .venv/bin/python configure.py --version GC_2_6
  ninja build/GC_2_6/native/mwcceppc || {
    echo "mweppc build failed (archive.org reachable? see the header of this script)" >&2
    exit 1
  }
  echo "built build/mweppc/build/GC_2_6/native/mwcceppc"
fi
