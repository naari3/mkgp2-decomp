#!/bin/sh
# Fetch the C source of the compiler we match against: doldecomp/mweppc, a CC0
# (public domain) decompilation of mwcceppc.exe GC/2.0, 2.0p2, 2.5, 2.6 and 2.7.
# Read it when diagnosing a scheduling / register-allocation / coalescing near
# miss; the index of where to look is docs/mwcc_internals.md.
#
#   sh tools/install_mweppc.sh          clone/update build/mweppc at the pinned commit
#   sh tools/install_mweppc.sh --build  also build native Linux compilers
#        build/mweppc/build/GC_{2_0,2_5,2_6,2_7}/native/mwcceppc (~75 s each, x86 Linux)
#
# The source alone needs only github.com. Building needs clang, lld, llvm, uv
# and archive.org (it downloads the CodeWarrior Pro 5 MSL runtime; allowed in
# the project's cloud environment since 2026-11-09). On 2026-11-09 the native
# compilers produced byte-identical .text for all 415 of our GC/2.0-2.7 units
# (only the known 2 extab padding bytes differ in 16), so they can stand in for
# wibo + mwcceppc.exe, with the source free to patch for logging.
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
git -C "$DIR" -c advice.detachedHead=false checkout -q -f "$COMMIT"
rm -f "$DIR/include/compiler/MwTrace.h"
# decision trace (MWCC_TRACE=file [MWCC_TRACE_FN=linkname]); output-neutral, see docs/mwcc_internals.md
git -C "$DIR" apply "$ROOT/tools/mweppc_trace/trace.patch"
echo "mweppc source at build/mweppc ($COMMIT); start with docs/mwcc_internals.md"
if [ "$1" = "--build" ]; then
  cd "$DIR"
  uv sync
  .venv/bin/python configure.py
  ninja build/GC_2_0/native/mwcceppc build/GC_2_5/native/mwcceppc \
        build/GC_2_6/native/mwcceppc build/GC_2_7/native/mwcceppc || {
    echo "mweppc build failed (archive.org reachable? see the header of this script)" >&2
    exit 1
  }
  echo "built build/mweppc/build/GC_2_*/native/mwcceppc"
fi
