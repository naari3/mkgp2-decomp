#!/usr/bin/env python3
"""Claim / release matching units via GitHub issues (gh CLI).

Protocol (docs/unit_first_strategy.md §claim):
  - 1 unit = 1 open issue, label `unit-claim`, title `[unit-claim] <Unit>`
  - open issue = claimed (assignee = claimer). closed = unclaimed
  - claim before starting a unit; done/release when finished/abandoning

Usage:
  python tools/claim_unit.py list                 # open claims
  python tools/claim_unit.py claim VfxSlot        # claim a unit (assigns @me)
  python tools/claim_unit.py claim VfxSlot --dry-run
  python tools/claim_unit.py done VfxSlot         # completed -> close
  python tools/claim_unit.py release VfxSlot      # abandon   -> close

Mechanical tool only: validates that the unit exists and is not already
claimed, then drives `gh issue ...`. Which unit to claim is your judgment
(see tools/plan_units.py for the ranking).

Requires: gh CLI authenticated against the repo remote (gh auth login).
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
sys.path.insert(0, str(HERE))

LABEL = "unit-claim"
TITLE_PREFIX = "[unit-claim] "

# Windows console は cp932 のことがあり、issue body の日本語 / 記号で
# UnicodeEncodeError になるため stdout/stderr を utf-8 に固定する
for _stream in (sys.stdout, sys.stderr):
    if hasattr(_stream, "reconfigure"):
        _stream.reconfigure(encoding="utf-8", errors="replace")


def run_gh(args: list[str], check: bool = True) -> subprocess.CompletedProcess:
    proc = subprocess.run(
        ["gh", *args], cwd=ROOT, capture_output=True, text=True,
        encoding="utf-8",
    )
    if check and proc.returncode != 0:
        sys.exit(f"gh {' '.join(args[:3])}... failed:\n{proc.stderr.strip()}")
    return proc


def fetch_open_claims() -> dict[str, dict]:
    """{unit_name: {number, url, assignees: [login], createdAt}}.

    Raises SystemExit on gh failure (callers that want graceful degrade
    should catch via fetch_open_claims_safe).
    """
    proc = run_gh([
        "issue", "list", "--label", LABEL, "--state", "open",
        "--json", "number,title,assignees,url,createdAt",
        "--limit", "200",
    ])
    out: dict[str, dict] = {}
    for it in json.loads(proc.stdout or "[]"):
        title = it.get("title", "")
        if not title.startswith(TITLE_PREFIX):
            continue
        unit = title[len(TITLE_PREFIX):].strip()
        out[unit] = {
            "number": it["number"],
            "url": it.get("url", ""),
            "assignees": [a.get("login", "?") for a in it.get("assignees", [])],
            "createdAt": it.get("createdAt", ""),
        }
    return out


def fetch_open_claims_safe() -> dict[str, dict] | None:
    """None if gh is unavailable / unauthenticated, instead of exiting."""
    try:
        proc = subprocess.run(
            ["gh", "issue", "list", "--label", LABEL, "--state", "open",
             "--json", "number,title,assignees,url,createdAt",
             "--limit", "200"],
            cwd=ROOT, capture_output=True, text=True, encoding="utf-8",
        )
    except FileNotFoundError:
        return None
    if proc.returncode != 0:
        return None
    out: dict[str, dict] = {}
    for it in json.loads(proc.stdout or "[]"):
        title = it.get("title", "")
        if not title.startswith(TITLE_PREFIX):
            continue
        unit = title[len(TITLE_PREFIX):].strip()
        out[unit] = {
            "number": it["number"],
            "url": it.get("url", ""),
            "assignees": [a.get("login", "?") for a in it.get("assignees", [])],
            "createdAt": it.get("createdAt", ""),
        }
    return out


def unit_members(unit: str) -> list[tuple[int, dict]]:
    from plan_units import load_functions, prefix_of
    fns = load_functions()
    return sorted(
        (a, v) for a, v in fns.items() if prefix_of(v["name"]) == unit
    )


def build_body(unit: str, members: list[tuple[int, dict]]) -> str:
    pending = [(a, v) for a, v in members if v["status"] == "pending"]
    total_b = sum(v["size"] for _a, v in pending)
    lines = [
        f"Unit claim: **{unit}** ({len(pending)} pending fn / {total_b}B)",
        "",
        "この issue が open の間、この unit は claim 済みです。",
        "着手前のランキング確認は `python tools/plan_units.py`、",
        "手順は `docs/unit_first_strategy.md` を参照。",
        "",
        "完了したら `python tools/claim_unit.py done " + unit + "`、",
        "手放す場合は `python tools/claim_unit.py release " + unit + "`。",
        "",
        "| addr | size | status | name |",
        "|---|---|---|---|",
    ]
    for a, v in members:
        lines.append(
            f"| 0x{a:08x} | {v['size']}B | {v['status']} | `{v['name']}` |"
        )
    lines += [
        "",
        "_snapshot at claim time; 最新状態は plan_units.py で再取得_",
    ]
    return "\n".join(lines)


def cmd_list(_args) -> int:
    claims = fetch_open_claims()
    if not claims:
        print("open claim なし")
        return 0
    for unit, c in sorted(claims.items()):
        who = ",".join(c["assignees"]) or "(unassigned)"
        print(f"{unit:<24} #{c['number']:<5} {who:<16} {c['url']}")
    return 0


def cmd_claim(args) -> int:
    unit = args.unit
    if unit.startswith("retrofit:"):
        # C++ retrofit batch claim (docs/unit_first_strategy.md 4.6):
        # 対象は TU 名 (configure.py の Object パス)。pending 検証は不要
        # (対象 fn は asm_fn/nonmatching)。scan_extab_actions.py --retrofit
        # の dispatch レーンから選ぶ。
        tu = unit[len("retrofit:"):]
        cfg = (ROOT / "configure.py").read_text(encoding="utf-8")
        if tu not in cfg:
            sys.exit(f"TU '{tu}' が configure.py に見つからない "
                     f"(retrofit:<configure の Object パス> 形式で指定)")
        claims = fetch_open_claims()
        if unit in claims:
            c = claims[unit]
            who = ",".join(c["assignees"]) or "(unassigned)"
            sys.exit(f"既に claim 済み: #{c['number']} by {who}\n{c['url']}")
        body = "\n".join([
            f"C++ retrofit batch claim: **{tu}**",
            "",
            "TU 丸ごと exceptions-on / real C++ 変換で asm_fn park を昇格する。",
            "レシピ: `docs/notes/cpp-ctor-retrofit-mangled-bridge.md`",
            "対象一覧: `python tools/scan_extab_actions.py --retrofit`",
            "",
            f"完了: `python tools/claim_unit.py done {unit}` /"
            f" 手放す: `python tools/claim_unit.py release {unit}`",
        ])
        if args.dry_run:
            print(f"[dry-run] gh issue create --title '{TITLE_PREFIX}{unit}'")
            print(body)
            return 0
        proc = run_gh([
            "issue", "create", "--title", TITLE_PREFIX + unit,
            "--label", LABEL, "--assignee", "@me", "--body", body,
        ])
        print(proc.stdout.strip())
        return 0

    members = unit_members(unit)
    if not members:
        sys.exit(f"unit '{unit}' に該当する関数が symbols.txt に無い "
                 f"(prefix 完全一致、大文字小文字区別)")
    pending = [m for m in members if m[1]["status"] == "pending"]
    if not pending:
        sys.exit(f"unit '{unit}' に pending 関数が無い (全部消化済み?)")

    claims = fetch_open_claims()
    if unit in claims:
        c = claims[unit]
        who = ",".join(c["assignees"]) or "(unassigned)"
        sys.exit(f"既に claim 済み: #{c['number']} by {who}\n{c['url']}")

    title = TITLE_PREFIX + unit
    body = build_body(unit, members)
    if args.dry_run:
        print(f"[dry-run] gh issue create --title '{title}' "
              f"--label {LABEL} --assignee @me")
        print("---- body ----")
        print(body)
        return 0
    proc = run_gh([
        "issue", "create", "--title", title, "--label", LABEL,
        "--assignee", "@me", "--body", body,
    ])
    print(proc.stdout.strip())
    return 0


def _close(unit: str, reason: str, comment: str) -> int:
    claims = fetch_open_claims()
    if unit not in claims:
        sys.exit(f"unit '{unit}' の open claim が見つからない "
                 f"(claim_unit.py list で確認)")
    num = str(claims[unit]["number"])
    run_gh(["issue", "close", num, "--reason", reason, "--comment", comment])
    print(f"closed #{num} ({reason}): {unit}")
    return 0


def cmd_done(args) -> int:
    return _close(args.unit, "completed",
                  f"unit {args.unit} 完食。claim を close する。")


def cmd_release(args) -> int:
    return _close(args.unit, "not planned",
                  f"unit {args.unit} の claim を手放す (未完了)。再 claim 可。")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="cmd", required=True)

    sub.add_parser("list", help="open claim 一覧")

    p_claim = sub.add_parser("claim", help="unit を claim する")
    p_claim.add_argument("unit")
    p_claim.add_argument("--dry-run", action="store_true")

    p_done = sub.add_parser("done", help="完了 close")
    p_done.add_argument("unit")

    p_rel = sub.add_parser("release", help="未完了 close (手放す)")
    p_rel.add_argument("unit")

    args = parser.parse_args()
    return {"list": cmd_list, "claim": cmd_claim,
            "done": cmd_done, "release": cmd_release}[args.cmd](args)


if __name__ == "__main__":
    sys.exit(main())
