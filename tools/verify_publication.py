#!/usr/bin/env python3
"""Read-only delivery check. Never dispatch, merge, push or update state."""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import json
import re
import subprocess
import urllib.request


def gh_json(*args: str):
    result = subprocess.run(["gh", *args], check=True, capture_output=True,
                            text=True, encoding="utf-8", timeout=30)
    return json.loads(result.stdout)


def verify(sha: str, repo: str, page: str) -> dict:
    if not re.fullmatch(r"[0-9a-f]{40}", sha):
        raise ValueError("expected a full lowercase 40-character commit SHA")
    runs = gh_json("run", "list", "--repo", repo, "--workflow", "Build",
                   "--commit", sha, "--limit", "5", "--json",
                   "databaseId,headSha,status,conclusion,url")
    runs = [r for r in runs if r["headSha"] == sha]
    if not runs:
        return {"ok": False, "sha": sha, "reason": "ci_not_started"}
    run = runs[0]
    detail = gh_json("run", "view", str(run["databaseId"]), "--repo", repo,
                     "--json", "status,conclusion,jobs,url")
    jobs = {j["name"]: j for j in detail["jobs"]}
    ci_ok = (detail["status"] == "completed" and detail["conclusion"] == "success"
             and jobs.get("deploy-pages", {}).get("conclusion") == "success"
             and any(n.startswith("build") and j.get("conclusion") == "success"
                     for n, j in jobs.items()))
    if not ci_ok:
        return {"ok": False, "sha": sha, "run_url": detail["url"],
                "reason": "ci_not_success", "status": detail["status"],
                "conclusion": detail["conclusion"]}
    separator = "&" if "?" in page else "?"
    request = urllib.request.Request(page + separator + "verify=" + sha,
                                     headers={"Cache-Control": "no-cache"})
    with urllib.request.urlopen(request, timeout=30) as response:
        html = response.read().decode("utf-8")
        status = response.status
    match = re.search(r"commit\s*<code>([0-9a-f]{40})</code>", html)
    public_sha = match.group(1) if match else None
    return {"ok": status == 200 and public_sha == sha, "sha": sha,
            "public_sha": public_sha, "http_status": status,
            "run_url": detail["url"], "page_url": page,
            "reason": "verified" if status == 200 and public_sha == sha else "public_sha_mismatch"}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sha", required=True)
    parser.add_argument("--repo", default="naari3/mkgp2-decomp")
    parser.add_argument("--page", default="https://naari3.github.io/mkgp2-decomp/")
    args = parser.parse_args()
    try:
        result = verify(args.sha, args.repo, args.page)
    except (ValueError, OSError, subprocess.SubprocessError) as exc:
        result = {"ok": False, "sha": args.sha, "reason": "check_error", "error": str(exc)}
    result["checked_at"] = datetime.now(timezone.utc).isoformat()
    print(json.dumps(result, ensure_ascii=False))
    return 0 if result["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
