#!/bin/bash
# mkgp2-decomp local build setup for cloud threads. Run from the repo root.
# Usage: bash tools/cloud_setup.sh
# Needs two files that cannot be in the repo (copyrighted / large), found in
# $MKGP2_SHARE (default /mnt/project-files, the Claude project's shared folder):
#   "Mario Kart Arcade GP 2 (Japan).iso" and compilers_20251118.zip.
# Everything else (tools, notes, sweep logs) lives in the repo.
set -e
ROOT=$(pwd)
SHARE=${MKGP2_SHARE:-/mnt/project-files}
# 0) Grind mode for cloud threads: tools/grind_stop_hook.py (Stop hook in .claude/settings.json)
#    keeps the thread working from the shared work queue (tools/helpers/workqueue.py) instead of idling. Env exported here
#    does not reach the Claude process, so the hook also checks this git-ignored marker.
export MKGP2_GRIND=1
touch .grind
STAGE=/home/claude/mkgp2-assets
mkdir -p "$STAGE" orig/GNLJ82/sys build/tools build/compilers
# 1) main.dol from the user's ISO (DOL offset at 0x420 of the disc header)
if [ ! -f orig/GNLJ82/sys/main.dol ]; then
  cp "$SHARE/Mario Kart Arcade GP 2 (Japan).iso" "$STAGE/game.iso"
  python3 - "$STAGE/game.iso" orig/GNLJ82/sys/main.dol <<'PY'
import struct,sys,hashlib
f=open(sys.argv[1],'rb'); f.seek(0x420); dol=struct.unpack('>I',f.read(4))[0]
f.seek(dol); h=f.read(0x100)
o=struct.unpack('>18I',h[:72]); s=struct.unpack('>18I',h[0x90:0x90+72])
f.seek(dol); d=f.read(max(a+b for a,b in zip(o,s)))
assert hashlib.sha1(d).hexdigest()=='ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65'
open(sys.argv[2],'wb').write(d)
PY
  rm -f "$STAGE/game.iso"
fi
# 2) Shared build cache: build/ snapshot of a recent main commit in $SHARE/build-cache
#    (tools/build_cache.py). Turns the ~5 min first build into seconds when it hits.
RESTORED=0
if python3 tools/build_cache.py restore; then RESTORED=1; fi
# 3) CodeWarrior compilers (files.decomp.dev is blocked by the network policy; the user uploaded the zip)
if [ ! -d build/compilers/GC ]; then
  cp "$SHARE/compilers_20251118.zip" "$STAGE/"
  python3 -c "import zipfile;zipfile.ZipFile('$STAGE/compilers_20251118.zip').extractall('build/compilers')"
fi
# 4) GitHub-hosted tools (allowed). Skipped after a cache restore: a re-download would
#    give them new mtimes and make ninja rebuild everything.
if [ $RESTORED = 0 ] || [ ! -x build/tools/wibo ]; then
  python3 tools/download_tool.py binutils build/binutils --tag 2.42-2
  python3 tools/download_tool.py wibo build/tools/wibo --tag 1.0.3
  python3 tools/download_tool.py dtk build/tools/dtk --tag v1.8.3
  python3 tools/download_tool.py objdiff-cli build/tools/objdiff-cli --tag v3.6.1
  python3 tools/download_tool.py sjiswrap build/tools/sjiswrap --tag v1.2.2
  chmod +x build/tools/* build/binutils/*
fi
# 4b) Genuine Metrowerks MSL C++ headers (docs/notes/msl_cpp.md). Never committed:
#     taken from the shared folder when a copy is there, else fetched from archive.org.
#     Without them the MSL TUs link the target objects (main.dol still OK, fewer functions).
if [ ! -f "build/msl_cw25/MSL_C++/MSL_Common/Include/deque" ]; then
  if [ -f "$SHARE/msl_cw25.tar.gz" ]; then
    mkdir -p build && tar -xzf "$SHARE/msl_cw25.tar.gz" -C build
  elif python3 tools/fetch_msl.py; then
    tar -czf "$STAGE/msl_cw25.tar.gz" -C build msl_cw25 && cp "$STAGE/msl_cw25.tar.gz" "$SHARE/" || true
  fi
  RESTORED=0  # build.ninja must be regenerated with the MSL units
fi
# 5) configure + build + SHA-1 check. Without the cache the first run splits for ~150 s
#    and compiles for ~145 s; after a restore ninja regenerates build.ninja itself if needed.
if [ $RESTORED = 0 ]; then
  python3 configure.py --binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo
fi
ninja all_source progress build/GNLJ82/report.json build/GNLJ82/ok
# 6) compiler source (CC0 decompilation of GC/2.0-2.7 mwcceppc, read-only reference; docs/mwcc_internals.md)
sh tools/install_mweppc.sh --build || sh tools/install_mweppc.sh || true
# 7) git hooks: show open agent-board messages (docs/agents/) after every pull/rebase
sh tools/install_githooks.sh n3 || true
# 8) refresh the shared cache for the next thread (background; skips itself when
#    HEAD is not on origin/main, the tree is dirty, or a snapshot for HEAD exists)
setsid nohup python3 tools/build_cache.py save > "$STAGE/build_cache_save.log" 2>&1 < /dev/null &
touch .setup_done
echo "cloud_setup: done (build cache restored: $RESTORED)"
