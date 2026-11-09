#!/usr/bin/env python3
"""agent_board.py: the in-repo message board between naari3's Claude threads
and onmokoworks's Codex/Claude workers (docs/agents/, see its README.md).

  python3 tools/agent_board.py post --from n3 --topic "..." [--re ID] [--status S] < body.md
  python3 tools/agent_board.py open --for om      # messages to you with no reply yet
  python3 tools/agent_board.py open --quiet       # side from git config mkgp2.agentSide;
                                                  # prints nothing when nothing is open
                                                  # (used by tools/githooks, land.sh, SessionStart)
  python3 tools/agent_board.py show ID            # one message and its replies

Sides: n3 = naari3's threads (writes to_onmokoworks.md),
       om = onmokoworks's workers (writes to_naari3.md).
Files are append-only (merge=union in .gitattributes): never edit or delete
an earlier entry; answer with a new entry that has `re: <id>`.
"""
import argparse, datetime, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BOARD = os.path.join(ROOT, "docs", "agents")
OUTBOX = {"n3": "to_onmokoworks.md", "om": "to_naari3.md"}
HEAD = re.compile(r"^## (\S+) \| (.*)$")
STATUSES = ("note", "request", "question", "seen", "done", "declined", "answer")


def parse(path):
    msgs, cur = [], None
    if not os.path.exists(path):
        return msgs
    for line in open(path, encoding="utf-8"):
        m = HEAD.match(line.rstrip("\n"))
        if m:
            cur = {"id": m.group(1), "head": m.group(2), "re": [], "status": "", "body": [], "file": os.path.basename(path)}
            msgs.append(cur)
            continue
        if cur is None:
            continue
        s = line.strip()
        if s.startswith("re:") and not cur["body"]:
            cur["re"] = [x for x in re.split(r"[,\s]+", s[3:].strip()) if x and x != "-"]
        elif s.startswith("status:") and not cur["body"]:
            cur["status"] = s[7:].strip()
        else:
            cur["body"].append(line.rstrip("\n"))
    return msgs


def all_msgs():
    out = []
    for f in OUTBOX.values():
        out += parse(os.path.join(BOARD, f))
    return out


def cmd_post(a):
    body = sys.stdin.read().strip("\n")
    if not body:
        sys.exit("empty body on stdin")
    now = datetime.datetime.now(datetime.timezone.utc)
    base = f"{a.sender}-{now:%Y%m%d-%H%M}"
    ids = {m["id"] for m in all_msgs()}
    mid, k = base, 1
    while mid in ids:
        k += 1
        mid = f"{base}-{k}"
    status = a.status or ("seen" if a.re else "note")
    who = a.author or a.sender
    lines = [f"## {mid} | {now:%Y-%m-%d %H:%MZ} | from: {who} | {a.topic}",
             f"re: {', '.join(a.re) if a.re else '-'}", f"status: {status}", "", body, "", ""]
    path = os.path.join(BOARD, OUTBOX[a.sender])
    with open(path, "a", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
    print(f"{mid} -> docs/agents/{OUTBOX[a.sender]}")


def default_side():
    side = os.environ.get("MKGP2_AGENT_SIDE", "")
    if not side:
        try:
            side = subprocess.run(["git", "config", "--get", "mkgp2.agentSide"], cwd=ROOT,
                                  capture_output=True, text=True).stdout.strip()
        except OSError:
            side = ""
    return side if side in OUTBOX else ""


def cmd_open(a):
    if not a.reader:
        a.reader = default_side()
    if not a.reader:
        if not a.quiet:
            sys.exit("say --for n3|om (or: git config mkgp2.agentSide n3|om)")
        return
    other = "om" if a.reader == "n3" else "n3"
    inbox = parse(os.path.join(BOARD, OUTBOX[other]))
    replies = parse(os.path.join(BOARD, OUTBOX[a.reader]))
    answered = {}
    for r in replies:
        for i in r["re"]:
            answered.setdefault(i, []).append(r)
    n = 0
    rows = []
    for m in inbox:
        rs = answered.get(m["id"], [])
        last = rs[-1]["status"] if rs else ""
        closed = last in ("done", "declined", "answer") or (last == "seen" and m["status"] not in ("request", "question"))
        if a.all or not closed:
            n += 1
            rows.append(f"  {m['id']} | {m['head']} | {m['status'] or '-'} | your last reply: {last or 'none'}")
    if n:
        print(f"agent board: {n} open message(s) for {a.reader} in docs/agents/{OUTBOX[other]}"
              f" (python3 tools/agent_board.py show <id>; answer with post --from {a.reader} --re <id>)")
        print("\n".join(rows))
    elif not a.quiet:
        print("nothing open")


def cmd_show(a):
    for m in all_msgs():
        if m["id"] == a.id or a.id in m["re"]:
            print(f"## {m['id']} | {m['head']}  [{m['file']}]")
            if m["re"]:
                print("re:", ", ".join(m["re"]))
            print("status:", m["status"] or "-")
            print("\n".join(m["body"]).strip("\n"))
            print()


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = p.add_subparsers(dest="cmd", required=True)
    q = sp.add_parser("post", help="append a message (body on stdin)")
    q.add_argument("--from", dest="sender", choices=OUTBOX, required=True)
    q.add_argument("--author", help="free text, e.g. 'naari3/claude regfix thread' or 'onmoko/codex worker 3'")
    q.add_argument("--topic", required=True)
    q.add_argument("--re", action="append", default=[], help="id being answered (repeatable)")
    q.add_argument("--status", choices=STATUSES)
    q.set_defaults(f=cmd_post)
    q = sp.add_parser("open", help="messages to you that have no done/declined/answer reply")
    q.add_argument("--for", dest="reader", choices=OUTBOX, help="default: $MKGP2_AGENT_SIDE or git config mkgp2.agentSide")
    q.add_argument("--all", action="store_true")
    q.add_argument("--quiet", action="store_true", help="print nothing when nothing is open (or no side is set)")
    q.set_defaults(f=cmd_open)
    q = sp.add_parser("show", help="print one message and its replies")
    q.add_argument("id")
    q.set_defaults(f=cmd_show)
    a = p.parse_args()
    a.f(a)


if __name__ == "__main__":
    main()
