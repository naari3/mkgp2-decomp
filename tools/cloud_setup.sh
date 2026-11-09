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
# 2) CodeWarrior compilers (files.decomp.dev is blocked by the network policy; the user uploaded the zip)
if [ ! -d build/compilers/GC ]; then
  cp "$SHARE/compilers_20251118.zip" "$STAGE/"
  python3 -c "import zipfile;zipfile.ZipFile('$STAGE/compilers_20251118.zip').extractall('build/compilers')"
fi
# 3) GitHub-hosted tools (allowed)
python3 tools/download_tool.py binutils build/binutils --tag 2.42-2
python3 tools/download_tool.py wibo build/tools/wibo --tag 1.0.3
python3 tools/download_tool.py dtk build/tools/dtk --tag v1.8.3
python3 tools/download_tool.py objdiff-cli build/tools/objdiff-cli --tag v3.6.1
python3 tools/download_tool.py sjiswrap build/tools/sjiswrap --tag v1.2.2
chmod +x build/tools/* build/binutils/*
# 4) configure + full build + SHA-1 check (first run splits for ~100s)
python3 configure.py --binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo
ninja all_source progress build/GNLJ82/report.json build/GNLJ82/ok
# 5) compiler source (CC0 decompilation of GC/2.0-2.7 mwcceppc, read-only reference; docs/mwcc_internals.md)
sh tools/install_mweppc.sh || true
# 6) git hooks: show open agent-board messages (docs/agents/) after every pull/rebase
sh tools/install_githooks.sh n3 || true
