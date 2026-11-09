#!/usr/bin/env python3
"""Install what tools/mwccdbg.py and tools/regfix.py need into build/mwccdbg/.

  python3 tools/mwccdbg_install.py

* cadmic/mwcc-debugger, pinned (not vendored: no licence file).
* Windows: nothing else to build. mwcceppc.exe runs natively under gdb
  (tools/mwccdbg_native.py). Needs a 32-bit x86 gdb with Python, e.g. MSYS2
  `pacman -S mingw-w64-i686-gdb` (C:/msys64/mingw32/bin/gdb.exe); put it on
  PATH or set MWCCDBG_GDB. Checked below.
* Linux/macOS: encounter/retrowin32 (gdb-stub branch) for the emulator, the
  prebuilt copy from the project share if present, else a cargo build
  (about 4 min, needs cmake), plus a system gdb with Python.
"""
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
D = ROOT / "build" / "mwccdbg"
DBG_COMMIT = "bad9cea"
RW_COMMIT = "11dbea5a"
SHARE = Path("/mnt/project-files/setup/mwccdbg/retrowin32")


def run(*a, **k):
    print("+", " ".join(map(str, a)), flush=True)
    subprocess.run(list(map(str, a)), check=True, **k)


def main():
    D.mkdir(parents=True, exist_ok=True)
    md = D / "mwcc-debugger"
    if not md.exists():
        run("git", "clone", "https://github.com/cadmic/mwcc-debugger", md)
    run("git", "-C", md, "checkout", "-q", DBG_COMMIT)
    native = os.environ.get("MWCCDBG_NATIVE", "1" if os.name == "nt" else "0") == "1"
    gdb = os.environ.get("MWCCDBG_GDB", "gdb")
    if not native:
        rw = D / "retrowin32"
        if not rw.exists():
            if SHARE.exists():
                shutil.copy(SHARE, rw)
            else:
                src = D / "retrowin32-src"
                if not src.exists():
                    run("git", "clone", "-b", "gdb-stub", "https://github.com/encounter/retrowin32.git", src)
                run("git", "-C", src, "checkout", "-q", RW_COMMIT)
                run("cargo", "build", "-p", "retrowin32", "-F", "x86-unicorn", "--profile", "lto", cwd=src)
                shutil.copy(src / "target" / "lto" / "retrowin32", rw)
            rw.chmod(0o755)
    # gdb check: Python support, and (native) an i386-capable build
    try:
        r = subprocess.run([gdb, "-batch", "-nx", "-ex", "py print('PY_OK')", "-ex", "show configuration"],
                           capture_output=True, text=True)
    except OSError:
        sys.exit(f"gdb not found ({gdb}); install it or set MWCCDBG_GDB")
    if "PY_OK" not in r.stdout:
        sys.exit(f"{gdb} has no Python support")
    if native and "i686" not in r.stdout and "i386" not in r.stdout:
        print(f"WARNING: {gdb} does not look like a 32-bit x86 build; mwcceppc.exe is 32-bit "
              "(MSYS2: mingw-w64-i686-gdb)")
    print(f"ok ({'native gdb' if native else 'retrowin32'}): python3 tools/mwccdbg.py <unit> <fn>")


if __name__ == "__main__":
    main()
