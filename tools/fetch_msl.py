#!/usr/bin/env python3
"""Fetch the genuine Metrowerks MSL C/C++ headers (CodeWarrior for GameCube 2.5).

The game links real MSL C++ containers (std::deque / Metrowerks::cdeque,
std::vector, ...; see docs/notes/msl_cpp.md).  The headers are Metrowerks
copyright, so they are NOT committed: this script downloads the installer ISO
from archive.org and unpacks the MSL tree to build/msl_cw25/ (git-ignored).

    python3 tools/fetch_msl.py            # -> build/msl_cw25/MSL_C++ ...
Needs: `unshield` (apt install unshield) and `pycdlib` (pip install pycdlib).
"""
import hashlib
import os
import shutil
import subprocess
import sys
import urllib.request

URL = "https://archive.org/download/cw-gc-2.5/CW_GC_2.5.ISO"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "build", "msl_cw25")
WORK = os.path.join(ROOT, "build", "_msl_fetch")
SHA256 = "90443a70b7450e93089427d62c1e980f9363b3bdd6527d16ec9c19078cd82bc6"
CAB_FILES = ["data1.cab", "data1.hdr", "data2.cab"]


def include_dirs(base=OUT):
    """-i directories, in the order mwcc needs them."""
    return [
        os.path.join(base, "MSL_C++", "MSL_Common", "Include"),
        os.path.join(base, "MSL_C", "MSL_Common", "Include"),
        os.path.join(base, "MSL_C", "PPC_EABI", "Include"),
        os.path.join(base, "MSL_C", "MSL_Common_Embedded", "Include"),
        os.path.join(base, "MSL_C", "MSL_Common_Embedded", "Math", "Include"),
    ]


def sanitize(base):
    """sjiswrap wants UTF-8 input: replace the few non-ASCII bytes (all in
    comments, e.g. the copyright sign) with '?'."""
    for d, _, files in os.walk(base):
        if "Include" not in d.split(os.sep):
            continue
        for f in files:
            path = os.path.join(d, f)
            data = open(path, "rb").read()
            if b"\0" in data or all(b < 0x80 for b in data):
                continue
            open(path, "wb").write(bytes(b if b < 0x80 else 0x3F for b in data))


def main():
    if os.path.isfile(os.path.join(include_dirs()[0], "deque")):
        print("already present:", OUT)
        return 0
    try:
        import pycdlib
    except ImportError:
        sys.exit("pip install pycdlib")
    if not shutil.which("unshield"):
        sys.exit("apt install unshield")
    os.makedirs(WORK, exist_ok=True)
    iso = os.path.join(WORK, "CW_GC_2.5.ISO")
    if not os.path.isfile(iso):
        print("downloading", URL)
        urllib.request.urlretrieve(URL, iso + ".part")
        os.replace(iso + ".part", iso)
    digest = hashlib.sha256(open(iso, "rb").read()).hexdigest()
    if digest != SHA256:
        sys.exit("unexpected ISO sha256 " + digest)
    cd = pycdlib.PyCdlib()
    cd.open(iso)
    for name in CAB_FILES:
        cd.get_file_from_iso(os.path.join(WORK, name), iso_path="/" + name.upper() + ";1")
    cd.close()
    x = os.path.join(WORK, "x")
    subprocess.check_call(["unshield", "-d", x, "x", os.path.join(WORK, "data1.cab")],
                          stdout=subprocess.DEVNULL)
    src = os.path.join(x, "PPC_EABI_Support", "msl")
    if os.path.isdir(OUT):
        shutil.rmtree(OUT)
    shutil.copytree(src, OUT)
    sanitize(OUT)
    shutil.rmtree(WORK)
    print("ok:", OUT)
    return 0


if __name__ == "__main__":
    sys.exit(main())
