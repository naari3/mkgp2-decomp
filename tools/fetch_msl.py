#!/usr/bin/env python3
"""Fetch the genuine Metrowerks MSL C/C++ headers (CodeWarrior for GameCube 2.5).

The game links real MSL C++ containers (std::deque / Metrowerks::cdeque,
std::vector, ...; see docs/notes/msl_cpp.md).  The headers are Metrowerks
copyright, so they are NOT committed: this script downloads the installer ISO
from archive.org and unpacks the MSL tree to build/msl_cw25/ (git-ignored).

    python3 tools/fetch_msl.py            # -> build/msl_cw25/MSL_C++ ...
No dependencies beyond the Python standard library (ISO 9660 and
InstallShield 6 cabinet readers are below).
"""
import hashlib
import os
import shutil
import struct
import sys
import urllib.request
import zlib

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


def iso_root_files(iso, names, dest):
    """Copy root-directory files out of an ISO 9660 image (no dependencies)."""
    want = {n.upper() + ";1": n for n in names}
    with open(iso, "rb") as f:
        f.seek(16 * 2048)
        pvd = f.read(2048)
        if pvd[1:6] != b"CD001":
            sys.exit("not an ISO 9660 image")
        lba, size = struct.unpack_from("<I", pvd, 158)[0], struct.unpack_from("<I", pvd, 166)[0]
        f.seek(lba * 2048)
        d = f.read(size)
        o = 0
        while o < len(d):
            n = d[o]
            if n == 0:  # records do not cross sectors
                o = (o // 2048 + 1) * 2048
                continue
            name = d[o + 33:o + 33 + d[o + 32]].decode("latin-1").upper()
            if name in want:
                ext, sz = struct.unpack_from("<I", d, o + 2)[0], struct.unpack_from("<I", d, o + 10)[0]
                f2 = open(os.path.join(dest, want.pop(name)), "wb")
                pos = f.tell()
                f.seek(ext * 2048)
                left = sz
                while left:
                    buf = f.read(min(left, 1 << 20))
                    f2.write(buf)
                    left -= len(buf)
                f2.close()
                f.seek(pos)
            o += n
    if want:
        sys.exit("missing in ISO: " + ", ".join(want.values()))


def cab_extract(hdr_path, cab_paths, out, prefix):
    """Unpack the files under `prefix` from an InstallShield 6 cabinet set:
    data1.hdr holds the file table, every file is a run of
    [u16 length][raw deflate] chunks in one of the volumes."""
    h = open(hdr_path, "rb").read()
    sig, ver, _, p, _ = struct.unpack_from("<5I", h, 0)
    if sig != 0x28635349 or (ver >> 12) & 0xF < 6:
        sys.exit("unexpected InstallShield cabinet version %#x" % ver)
    fto, = struct.unpack_from("<I", h, p + 0xC)
    dcount, = struct.unpack_from("<I", h, p + 0x1C)
    fcount, = struct.unpack_from("<I", h, p + 0x28)
    fto2, = struct.unpack_from("<I", h, p + 0x2C)

    def cstr(o):
        return h[o:h.index(b"\0", o)].decode("latin-1")

    dirs = [cstr(p + fto + o) for o in struct.unpack_from("<%dI" % dcount, h, p + fto)]
    vols = [open(c, "rb") for c in cab_paths]
    count = 0
    for i in range(fcount):
        q = p + fto + fto2 + i * 0x57
        flags, = struct.unpack_from("<H", h, q)
        esize, csize, doff = struct.unpack_from("<3Q", h, q + 2)
        nameoff, = struct.unpack_from("<I", h, q + 0x3A)
        didx, = struct.unpack_from("<H", h, q + 0x3E)
        volume, = struct.unpack_from("<H", h, q + 0x55)
        if flags & 8 or not nameoff or not doff:
            continue
        path = (dirs[didx] + "\\" + cstr(p + fto + nameoff)).replace("\\", "/")
        if not path.startswith(prefix):
            continue
        if flags & 3 or h[q + 0x54] & 1:
            sys.exit("split/obfuscated cabinet entry: " + path)
        f = vols[volume - 1]
        f.seek(doff)
        raw = f.read(csize)
        if flags & 4:
            o, parts = 0, []
            while o < csize:
                n, = struct.unpack_from("<H", raw, o)
                parts.append(zlib.decompress(raw[o + 2:o + 2 + n], -15))
                o += 2 + n
            raw = b"".join(parts)
        if len(raw) != esize:
            sys.exit("size mismatch: " + path)
        dst = os.path.join(out, *path.split("/"))
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        open(dst, "wb").write(raw)
        count += 1
    for f in vols:
        f.close()
    return count


def main():
    if os.path.isfile(os.path.join(include_dirs()[0], "deque")):
        print("already present:", OUT)
        return 0
    os.makedirs(WORK, exist_ok=True)
    iso = os.path.join(WORK, "CW_GC_2.5.ISO")
    if not os.path.isfile(iso):
        print("downloading", URL)
        urllib.request.urlretrieve(URL, iso + ".part")
        os.replace(iso + ".part", iso)
    sha = hashlib.sha256()
    with open(iso, "rb") as f:
        for buf in iter(lambda: f.read(1 << 20), b""):
            sha.update(buf)
    if sha.hexdigest() != SHA256:
        sys.exit("unexpected ISO sha256 " + sha.hexdigest())
    iso_root_files(iso, CAB_FILES, WORK)
    x = os.path.join(WORK, "x")
    n = cab_extract(os.path.join(WORK, "data1.hdr"),
                    [os.path.join(WORK, "data1.cab"), os.path.join(WORK, "data2.cab")], x, "msl/")
    if os.path.isdir(OUT):
        shutil.rmtree(OUT)
    shutil.copytree(os.path.join(x, "msl"), OUT)
    sanitize(OUT)
    shutil.rmtree(WORK)
    print("ok: %d files -> %s (rerun configure.py)" % (n, OUT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
