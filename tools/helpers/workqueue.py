#!/usr/bin/env python3
"""Shared grind queue without lost updates.

Why: threads run in different containers that share /mnt/project-files through
an rclone FUSE mount. flock there is only local to one container and
read-modify-write of one shared file loses edits (last write wins). So no
thread ever rewrites a shared file here:

  queue/seed.txt          ID|item text      (written once; never edited)
  queue/log/<who>.jsonl   one event per line, appended ONLY by thread <who>
  queue.md                read-only view, re-rendered from seed+logs on every call

State is a pure function of seed + all logs, so concurrent writers can't
clobber each other. Two threads taking the same item at once: the earliest
take timestamp wins (ties: name); `take` waits SETTLE seconds, re-reads, and
moves on to another item if it lost.

Usage (always pass --who or set MKGP2_THREAD; use your thread's short name):
  workqueue.py list [--all] [--grep RE]        open items (or everything)
  workqueue.py take [ID] [--grep RE]           claim ID, or the first open item matching RE
  workqueue.py done ID --note <commit>          (--commit SHA works too)
  workqueue.py done ID --commit SHA --force     close an item parked or held by someone else
  workqueue.py park ID --note "<one-line reason>"
  workqueue.py release ID                      give a claim back without a verdict
  workqueue.py add "fn | TU | % | note"        new candidate
  workqueue.py mine                            items you hold
  workqueue.py render                          rewrite queue.md
  workqueue.py snapshot                        copy queue.md + seed + logs to docs/sweeps/queue/ (then commit)
A claim older than STALE_H hours counts as abandoned and can be taken again.
"""
import argparse, glob, hashlib, json, os, re, sys, time
from datetime import datetime, timezone, timedelta

# Live queue state stays in the shared folder (needs atomic appends across containers);
# a snapshot is copied to docs/sweeps/queue/ in the repo.
BASE = os.environ.get("MKGP2_QUEUE_DIR", os.path.join(os.environ.get("MKGP2_SHARE", "/mnt/project-files"), "setup"))
QDIR = os.path.join(BASE, "queue")
SEED = os.path.join(QDIR, "seed.txt")
LOGDIR = os.path.join(QDIR, "log")
VIEW = os.path.join(BASE, "queue.md")
SETTLE = float(os.environ.get("MKGP2_QUEUE_SETTLE", "15"))
STALE_H = 6

HEADER = """# Shared grind queue (GENERATED VIEW - DO NOT EDIT)

This file is rewritten from `queue/seed.txt` + `queue/log/*.jsonl` by
`python3 -I tools/helpers/workqueue.py`. Hand edits are lost.
Use the helper (it never rewrites shared files, so nothing is lost):

    Q=tools/helpers/workqueue.py; export MKGP2_THREAD=<your short name>
    python3 $Q list --grep 'game/'      # open items
    python3 $Q take [ID] [--grep RE]     # claim (waits ~15 s to settle races)
    python3 $Q done ID --note <commit>   |  park ID --note "<reason>"  |  release ID
    python3 $Q add "fn | TU | % | note"

Before touching the TU: rebase on origin/main, check open `unit-claim` issues
(explicit page numbers), open your own `[unit-claim]` issue; skip onmokoworks TUs.
Never end a turn waiting for instructions: when one item is done, take the next.
Queue empty: pragmasweep `--set all` on near misses in your range.
Wrap-up switch: create `/mnt/project-files/setup/GRIND_STOP`.

"""


def now():
    return datetime.now(timezone.utc)


def iso(t):
    return t.strftime("%Y-%m-%dT%H:%M:%S.%fZ")


def parse_t(s):
    return datetime.strptime(s, "%Y-%m-%dT%H:%M:%S.%fZ").replace(tzinfo=timezone.utc)


def load_seed():
    items = {}
    order = []
    try:
        with open(SEED, encoding="utf-8") as f:
            for l in f:
                l = l.rstrip("\n")
                if "|" not in l:
                    continue
                i, text = l.split("|", 1)
                items[i] = text
                order.append(i)
    except OSError:
        pass
    return items, order


def load_events():
    ev = []
    for p in glob.glob(os.path.join(LOGDIR, "*.jsonl")):
        try:
            with open(p, encoding="utf-8") as f:
                for l in f:
                    try:
                        ev.append(json.loads(l))
                    except ValueError:
                        pass  # torn last line while being appended
        except OSError:
            pass
    ev.sort(key=lambda e: (e.get("t", ""), e.get("who", "")))
    return ev


def state():
    items, order = load_seed()
    st = {i: {"text": items[i], "status": "open", "who": None, "t": None, "note": ""} for i in order}
    for e in load_events():
        op, i, who = e.get("op"), e.get("id"), e.get("who")
        if op == "add":
            if i not in st:
                st[i] = {"text": e.get("text", ""), "status": "open", "who": None, "t": None, "note": ""}
                order.append(i)
            continue
        s = st.get(i)
        if s and op == "done" and e.get("force") and s["status"] == "parked":
            # done --force: a later match overrides a park (anyone's)
            s.update(status="done", who=who, t=parse_t(e["t"]), note=e.get("note", ""))
            continue
        if not s or s["status"] in ("done", "parked"):
            if s and op in ("done", "park") and s["status"] in ("done", "parked"):
                pass  # first verdict wins
            continue
        t = parse_t(e["t"])
        if op == "take":
            stale = s["status"] == "claimed" and t - s["t"] > timedelta(hours=STALE_H)
            if s["status"] == "open" or stale or s["who"] == who:
                s.update(status="claimed", who=who, t=t)
        elif op == "release" and s["status"] == "claimed" and s["who"] == who:
            s.update(status="open", who=None, t=None)
        elif op in ("done", "park"):
            s.update(status="done" if op == "done" else "parked", who=who, t=t, note=e.get("note", ""))
    return st, order


def marker(s):
    if s["status"] == "open":
        return "[ ]"
    if s["status"] == "claimed":
        return "[%s %s]" % (s["who"], s["t"].strftime("%m-%d %H:%M"))
    return "[%s %s: %s]" % ("done" if s["status"] == "done" else "parked", s["who"], s["note"])


def render(st=None, order=None):
    if st is None:
        st, order = state()
    out = [HEADER]
    n = sum(1 for i in order if st[i]["status"] == "open")
    out.append("%d open / %d total, rendered %s\n\n" % (n, len(order), iso(now())[:16]))
    for i in order:
        out.append("- %s %s %s\n" % (marker(st[i]), i, st[i]["text"]))
    tmp = VIEW + ".tmp.%d" % os.getpid()
    try:
        with open(tmp, "w", encoding="utf-8") as f:
            f.write("".join(out))
        os.replace(tmp, VIEW)
    except OSError as ex:
        print("warning: could not render view:", ex, file=sys.stderr)


def append(who, op, i, **kw):
    os.makedirs(LOGDIR, exist_ok=True)
    e = dict(t=iso(now()), who=who, op=op, id=i, **kw)
    with open(os.path.join(LOGDIR, re.sub(r"[^A-Za-z0-9_.-]", "_", who) + ".jsonl"), "a", encoding="utf-8") as f:
        f.write(json.dumps(e, ensure_ascii=False) + "\n")


def show(i, s):
    print("%s %s %s" % (marker(s), i, s["text"]))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["list", "take", "done", "park", "release", "add", "mine", "render", "snapshot"])
    ap.add_argument("arg", nargs="?")
    ap.add_argument("--who", default=os.environ.get("MKGP2_THREAD"))
    ap.add_argument("--note", default="")
    ap.add_argument("--commit", help="alias for --note on done")
    ap.add_argument("--force", action="store_true",
                    help="done: also close an item that is parked or held by another thread")
    ap.add_argument("--grep")
    ap.add_argument("--all", action="store_true")
    a = ap.parse_args()
    if a.cmd in ("take", "done", "park", "release", "add", "mine") and not a.who:
        sys.exit("pass --who NAME or set MKGP2_THREAD")
    st, order = state()
    rx = re.compile(a.grep, re.I) if a.grep else None

    if a.cmd == "list":
        for i in order:
            s = st[i]
            if (a.all or s["status"] == "open") and (not rx or rx.search(s["text"])):
                show(i, s)
    elif a.cmd == "mine":
        for i in order:
            if st[i]["status"] == "claimed" and st[i]["who"] == a.who:
                show(i, st[i])
    elif a.cmd == "render":
        render(st, order)
    elif a.cmd == "snapshot":
        # copy the live queue (view + seed + logs) into the repo so the notes are shared knowledge
        import shutil
        dst = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                           "docs", "sweeps", "queue")
        render(st, order)
        shutil.copytree(QDIR, dst, dirs_exist_ok=True)
        shutil.copy(VIEW, os.path.join(dst, "queue_snapshot.md"))
        print("snapshot ->", dst, "(commit it)")
    elif a.cmd == "add":
        if not a.arg:
            sys.exit("add needs the item text")
        i = "N" + hashlib.sha1(a.arg.encode()).hexdigest()[:6]
        append(a.who, "add", i, text=a.arg)
        render()
        print("added", i)
    elif a.cmd in ("done", "park", "release"):
        if a.arg not in st:
            sys.exit("unknown id %r" % a.arg)
        if a.commit and not a.note:
            a.note = a.commit
        if a.cmd != "release" and not a.note:
            sys.exit("%s needs --note (or --commit)" % a.cmd)
        s0 = st[a.arg]
        if a.cmd == "done" and not a.force and (
                s0["status"] == "parked" or (s0["status"] == "claimed" and s0["who"] != a.who)):
            show(a.arg, s0)
            sys.exit("item is %s by %s; rerun with --force if it really landed" % (s0["status"], s0["who"]))
        if a.force and a.cmd == "done":
            append(a.who, a.cmd, a.arg, note=a.note, force=True)
        else:
            append(a.who, a.cmd, a.arg, note=a.note)
        render()
        st, _ = state()
        show(a.arg, st[a.arg])
    elif a.cmd == "take":
        tried = set()
        for _ in range(6):
            if a.arg:
                cand = a.arg
                if cand not in st:
                    sys.exit("unknown id %r" % cand)
                if st[cand]["status"] != "open" and not (st[cand]["status"] == "claimed" and st[cand]["who"] == a.who):
                    s = st[cand]
                    if not (s["status"] == "claimed" and now() - s["t"] > timedelta(hours=STALE_H)):
                        show(cand, s)
                        sys.exit("not open")
            else:
                cand = next((i for i in order if i not in tried and st[i]["status"] == "open"
                             and (not rx or rx.search(st[i]["text"]))), None)
                if cand is None:
                    sys.exit("no open item matches; queue empty for you -> pragmasweep fallback")
            tried.add(cand)
            append(a.who, "take", cand)
            time.sleep(SETTLE)
            st, order = state()
            if st[cand]["status"] == "claimed" and st[cand]["who"] == a.who:
                render(st, order)
                print("TOOK", end=" ")
                show(cand, st[cand])
                return
            print("lost race for %s to %s, trying another" % (cand, st[cand]["who"]), file=sys.stderr)
            if a.arg:
                sys.exit(1)
        sys.exit("could not claim anything after several tries")


if __name__ == "__main__":
    main()
