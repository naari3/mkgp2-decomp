#!/usr/bin/env python3
"""Claude Code Stop hook that keeps grinding threads from idling.

Registered in .claude/settings.json. It does nothing (the turn ends normally)
unless grind mode is on, so a normal interactive Claude Code session in this
repo is not affected. Grind mode is on when either:
  - the environment variable MKGP2_GRIND=1 is set for the Claude process, or
  - the git-ignored marker file `.grind` exists in the repo root
    (`bash tools/cloud_setup.sh` creates it for cloud threads,
    because env vars exported by setup.sh do not reach the Claude process).

When grind mode is on, the hook blocks the stop and tells Claude to take the
next open line of the shared work queue (QUEUE below), or, if the queue is
empty, to re-run pragmasweep on near misses in its range.

Safety valves (the hook never blocks forever):
  - At most MKGP2_GRIND_MAX (default 30) consecutive blocks per session.
    The count resets whenever a turn starts from a real message
    (stop_hook_active is false in the hook input).
  - If the file STOP_FILE exists, every thread may stop (wrap-up switch).
  - Any error inside the hook lets the stop through.

Test:  echo '{"session_id":"t","stop_hook_active":false}' | MKGP2_GRIND=1 python3 tools/grind_stop_hook.py
"""
import json
import os
import re
import sys

_SHARE = os.environ.get("MKGP2_SHARE", "/mnt/project-files")   # live queue state only
QUEUE = os.environ.get("MKGP2_GRIND_QUEUE", f"{_SHARE}/setup/queue.md")
STOP_FILE = os.environ.get("MKGP2_GRIND_STOP", f"{_SHARE}/setup/GRIND_STOP")
STATE_DIR = os.environ.get("MKGP2_GRIND_STATE", "/tmp/mkgp2_grind")
OPEN_RE = re.compile(r"^- \[ \] ")


def repo_root():
    d = os.environ.get("CLAUDE_PROJECT_DIR")
    if d:
        return d
    return os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def enabled():
    if os.environ.get("MKGP2_GRIND") == "1":
        return True
    return os.path.exists(os.path.join(repo_root(), ".grind"))


def open_items():
    try:
        with open(QUEUE, encoding="utf-8") as f:
            return [l.rstrip("\n") for l in f if OPEN_RE.match(l)]
    except OSError:
        return None


def bump_counter(session, active, cap):
    """Return True if this block is still within the cap."""
    os.makedirs(STATE_DIR, exist_ok=True)
    safe = re.sub(r"[^A-Za-z0-9_.-]", "_", session or "default")
    path = os.path.join(STATE_DIR, safe + ".count")
    n = 0
    if active:
        try:
            with open(path) as f:
                n = int(f.read().strip() or 0)
        except (OSError, ValueError):
            n = 0
    n += 1
    with open(path, "w") as f:
        f.write(str(n))
    return n <= cap


def main():
    if not enabled():
        return 0
    if os.path.exists(STOP_FILE):
        return 0
    try:
        data = json.load(sys.stdin)
    except ValueError:
        data = {}
    try:
        cap = int(os.environ.get("MKGP2_GRIND_MAX", "30"))
    except ValueError:
        cap = 30
    if not bump_counter(data.get("session_id"), bool(data.get("stop_hook_active")), cap):
        return 0

    items = open_items()
    common = (
        "Grind mode: do not end your turn waiting for instructions. "
        "Before starting any function: git fetch origin main and rebase, check that no open "
        "unit-claim issue names the TU (list them with explicit page numbers), and open your own "
        "[unit-claim] issue. Land with a clean build (rm -rf build/GNLJ82/src; main.dol OK) and "
        "push to main. Post a short result line only when something lands or you are truly blocked. "
    )
    if items:
        reason = (
            common
            + f"Take the next open item in your range ({len(items)} open) ONLY via the helper "
            "(never edit queue.md by hand; it is a generated view and hand edits are lost): "
            "`python3 -I tools/helpers/workqueue.py take [ID] [--grep RE] --who <your thread name>`, "
            "then `workqueue.py done ID --note <commit>` or `workqueue.py park ID --note \"<reason>\"`, "
            "and take the next one. Next open item: " + items[0][:300]
        )
    else:
        reason = (
            common
            + f"The work queue {QUEUE} has no open lines. Re-run "
            "`python3 tools/pragmasweep.py fn <TU> <FN> --set all` (or `batch --min 90`) on the "
            "near misses and docs/gave_up.md rows in your range that nobody claims, try "
            "TU merges/splits for pooled-base rows, and add any new candidates you find to the "
            "queue with `workqueue.py add \"fn | TU | % | note\" --who <name>`."
        )
    json.dump({"decision": "block", "reason": reason}, sys.stdout)
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception:  # never wedge a session because of the hook
        sys.exit(0)
