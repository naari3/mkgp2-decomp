#!/usr/bin/env python3
"""Shared build cache for cloud threads.

A fresh thread spends ~5 minutes on its first ninja run: dtk split (~150 s,
single-threaded) plus ~3000 mwcc compiles (~145 s on 4 vCPU). This script keeps
a snapshot of build/ (+ .ninja_log/.ninja_deps/build.ninja/...) in the
project's shared folder, keyed by the main commit it was built from, so the
next thread only rebuilds what changed since that commit.

    python3 tools/build_cache.py restore   # used by tools/cloud_setup.sh
    python3 tools/build_cache.py save      # snapshot the current build (clean tree only)
    python3 tools/build_cache.py list

Restoring after a fresh `git clone` needs mtime care: every checked-out file is
newer than the cached outputs, so ninja would rebuild everything. `restore`
sets all tracked files (and orig/.../main.dol) to an old fixed time, then
touches only the files that differ between the snapshot commit and HEAD, so
ninja sees exactly those as changed.

`save` only writes a snapshot when the tracked tree is clean, HEAD is on
origin/main, and ninja has no work left for the setup targets; otherwise the
cached objects might not match the commit they are keyed by.
"""
import os
import subprocess
import sys
import tempfile
import time

ROOT = os.environ.get("MKGP2_ROOT") or os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SHARE = os.environ.get("MKGP2_SHARE", "/mnt/project-files")
CACHE = os.path.join(SHARE, "build-cache")
KEEP = 3
OLD = 946684800  # 2000-01-01, older than any cached output
# setup targets minus `progress`, which is phony and always runs
TARGETS = ["all_source", "build/GNLJ82/report.json", "build/GNLJ82/ok"]
MEMBERS = ["build", ".ninja_log", ".ninja_deps", "build.ninja", "objdiff.json",
           "compile_commands.json"]
MAIN_DOL = "orig/GNLJ82/sys/main.dol"


def git(*args, check=True):
    r = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    if check and r.returncode:
        raise RuntimeError(f"git {' '.join(args)}: {r.stderr.strip()}")
    return r


def snapshots():
    if not os.path.isdir(CACHE):
        return []
    out = []
    for name in os.listdir(CACHE):
        if name.startswith("build-") and name.endswith(".tgz"):
            out.append((name[6:-4], os.path.join(CACHE, name)))
    return out


def cmd_list():
    for sha, path in sorted(snapshots(), key=lambda s: os.path.getmtime(s[1])):
        st = os.stat(path)
        print(f"{sha[:10]}  {st.st_size / 1e6:6.0f} MB  "
              f"{time.strftime('%Y-%m-%d %H:%MZ', time.gmtime(st.st_mtime))}")


def best_snapshot():
    """The cached commit closest behind HEAD (must be an ancestor of HEAD)."""
    best = None
    for sha, path in snapshots():
        if git("cat-file", "-e", sha + "^{commit}", check=False).returncode:
            continue
        if git("merge-base", "--is-ancestor", sha, "HEAD", check=False).returncode:
            continue
        n = int(git("rev-list", "--count", f"{sha}..HEAD").stdout)
        if best is None or n < best[0]:
            best = (n, sha, path)
    return best


def set_old(paths):
    for p in paths:
        try:
            os.utime(p, (OLD, OLD), follow_symlinks=False)
        except FileNotFoundError:
            pass


def cmd_restore():
    if os.path.exists(os.path.join(ROOT, ".ninja_log")):
        print("build_cache: a build already exists here; not restoring")
        return 1
    best = best_snapshot()
    if best is None:
        print("build_cache: no usable snapshot (none is an ancestor of HEAD)")
        return 1
    n, sha, path = best
    t = time.time()
    with tempfile.TemporaryDirectory() as tmp:
        # copy off the FUSE mount first, then extract locally
        local = os.path.join(tmp, "b.tgz")
        subprocess.run(["cp", path, local], check=True)
        subprocess.run(["tar", "-xzf", local, "-C", ROOT], check=True)
    tracked = git("ls-files", "-z").stdout.split("\0")
    os.chdir(ROOT)
    set_old([p for p in tracked if p] + [MAIN_DOL])
    changed = [p for p in git("diff", "--name-only", "-z", sha).stdout.split("\0") if p]
    now = time.time()
    for p in changed:
        if os.path.lexists(p):
            os.utime(p, (now, now), follow_symlinks=False)
    print(f"build_cache: restored {sha[:10]} ({n} commits behind HEAD, "
          f"{len(changed)} files changed) in {time.time() - t:.1f}s")
    return 0


def cmd_save():
    os.chdir(ROOT)
    if git("status", "--porcelain", "--untracked-files=no").stdout.strip():
        print("build_cache: tracked files modified; not saving")
        return 1
    head = git("rev-parse", "HEAD").stdout.strip()
    git("fetch", "-q", "origin", "main", check=False)
    if git("merge-base", "--is-ancestor", head, "origin/main", check=False).returncode:
        print("build_cache: HEAD is not on origin/main; not saving")
        return 1
    if any(sha == head for sha, _ in snapshots()):
        print(f"build_cache: snapshot for {head[:10]} already exists")
        return 0
    r = subprocess.run(["ninja", "-n", *TARGETS], capture_output=True, text=True)
    if "no work to do" not in r.stdout:
        print("build_cache: build is not up to date; not saving")
        return 1
    t = time.time()
    os.makedirs(CACHE, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        local = os.path.join(tmp, "b.tgz")
        members = [m for m in MEMBERS if os.path.lexists(m)]
        subprocess.run(["tar", "-I", "gzip -1", "-cf", local, *members], check=True)
        part = os.path.join(CACHE, f".part-{head}-{os.getpid()}")
        subprocess.run(["cp", local, part], check=True)
        os.replace(part, os.path.join(CACHE, f"build-{head}.tgz"))
    for _, path in sorted(snapshots(), key=lambda s: os.path.getmtime(s[1]))[:-KEEP]:
        try:
            os.remove(path)
        except OSError:
            pass
    print(f"build_cache: saved {head[:10]} in {time.time() - t:.1f}s")
    return 0


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "list"
    fn = {"restore": cmd_restore, "save": cmd_save, "list": cmd_list}.get(cmd)
    if fn is None:
        print(__doc__)
        return 2
    return fn() or 0


if __name__ == "__main__":
    sys.exit(main())
