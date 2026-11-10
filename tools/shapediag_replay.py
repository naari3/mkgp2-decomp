#!/usr/bin/env python3
"""Replay landed fixes against tools/shapediag.py.

    python3 tools/shapediag_replay.py run [-j 4] [--only FN] [--retry]
    python3 tools/shapediag_replay.py report [--md docs/reports/shapediag_replay.md]

Ground truth = every landed fix this project recorded with a commit:
  * tools/patterns/hits.jsonl (rule_id, fn, landed_commit)
  * the onmokoworks Codex table in docs/regalloc_patterns.md (category, fn, commit)

For each one the tree just BEFORE the fix commit is extracted (src, include,
configure.py, tools, config), the function's TU is compiled there with that
tree's own compile command (falls back to today's command for the unit) and
the result is compared with today's target object by shapediag. Rows go to
docs/sweeps/shapediag/replay.jsonl (restartable):

  status   repro      a diff was reproduced; `classes` = shapediag classes,
                      `reg_lines` = aligned lines that differ in registers only
           reg_only   reproduced, the instruction sequence is the same
           same       pre-fix source already gives the target's instructions
                      (the fix was data / splits / flags / another function)
           no_source  the fix commit has no earlier source with the function
                      (asm -> C landing, or fixed outside src/)
           no_build   the old tree does not compile here
           no_fn      compiled, function not found in the object

`report` joins the rows with EXPECT (which classes are the right pointer for
each rule) and prints hit / miss per rule.
"""
import argparse, collections, json, os, re, shutil, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import shapediag as sd

ROOT = sd.ROOT
OUT = ROOT / "docs/sweeps/shapediag/replay.jsonl"

# rule_id (or Codex category) -> shapediag classes that point at that lever.
# "REG" = the lever is a colouring lever: a register-only verdict is the right
# answer (regfix diag's job). Filled from the replay results, by hand.
POOL = ["address:pool", "address:materialise", "address:sda", "reloc:symbol"]
ARGS = ["order:args"]
EXPECT = {
    # data / pools
    "anchor-addi-object-boundary": POOL, "data-ownership": POOL, "merge-pool-owner": POOL, "split-data-object": POOL,
    "alias-in-range": POOL,
    # argument order
    "arg-order-prototype": ARGS, "callee-proto-float-before-int": ARGS, "float-arg-sum-load-then-add-in-place": ARGS,
    # copies
    "cast-keeps-copy-of-cse-temp": ["copy:direction", "copy:target-extra"],
    "entry-block-param-copy": ["copy:target-extra", "copy:ours-extra", "copy:direction"],
    "base-local-two-uses": ["address:materialise", "copy:target-extra"],
    "li-cse-inline-locals": ["load:const-vs-copy", "copy:direction", "REG"],
    "loop-in-inline-iv-init-copy": ["load:const-vs-copy", "copy:direction", "REG"],
    # expression / operand order
    "expr-operand-order": ["operand-order", "order:expr", "REG"],
    "second-operand-named-local-no-propagation": ["operand-order", "order:expr"],
    "three-term-sum-grouping-rotation": ["operand-order", "order:expr"],
    "offset-after-index": ["operand-order", "select:indexed"],
    "expr-shape": ["operand-order", "order:expr", "select:other", "select:muldiv", "REG"],
    # loads / aliasing
    "restrict-input-ptrs": ["order:load", "order:store", "load:ours-reloads"],
    "const-pointee-hoist": ["order:load", "order:store", "load:ours-reloads"],
    "no-cached-pointer": ["load:target-reloads", "address:materialise", "copy:ours-extra"],
    "ref-local-across-loop": ["address:materialise", "saved-regs", "load:ours-reloads", "REG"],
    # constants
    "const-creation-order-assign-in-expr": ["order:const", "load:const-vs-copy", "REG"],
    "float-literal-and-local-roles": ["order:const", "load:const-vs-copy", "REG"],
    "literal-vs-extern": ["order:const", "load:const-vs-copy", "REG"],
    "codex:literal-vs-extern-constant": ["order:const", "load:const-vs-copy", "operand-order", "copy:ours-extra", "order:args", "load:target-reloads", "REG"],
    "float-literal-zero-inline-param": ["order:const", "load:const-vs-copy", "REG"],
    "hoisted-fpr-pair-named-decl-order": ["order:regswap", "order:const", "REG"],
    # shape
    "inplace-div-no-propagation": ["saved-regs"],
    "inline-mul-blocks-fmadd": ["select:fused"],
    "return-copy-reschedules-last-block": ["order:epilogue"],
    "dead-truncation-reschedules-block": ["order:other", "extend"],
    "base-init-in-body": ["order:store", "order:const"],
    "local-array-initialiser": ["order:store", "order:copyrun", "stack:offset", "stack:frame"],
    "loop-unroll-budget": ["loop:ctr", "loop:shape", "REG"],
    "rolled-loop-blocks-cse": ["loop:ctr", "loop:shape", "load:target-reloads", "REG"],
    "repeated-copies-are-unrolled-loop": ["loop:ctr", "loop:shape", "REG"],
    "loop-index-shape": ["select:indexed", "select:update", "loop:shape", "order:loopstep", "REG"],
    "new-expression-vs-alloc-ctor": ["loop:shape", "call:inline"],
    "goto-two-return-blocks": ["loop:shape", "order:blocks"],
    "recursive-auto-inline": ["call:inline", "REG"],
    "inline-matched-sibling": ["call:inline", "REG"],
    "inline-boundary": ["call:inline", "REG"],
    "pragma-opt-off": ["load:target-reloads", "load:ours-reloads", "saved-regs", "select:muldiv", "REG"],
    "stmt-order": ["order:store", "order:load", "order:other", "REG"],
    "decl-order-value-locals-before-case-pointer": ["stack:offset", "REG"],
    "unsigned-param": ["select:signedness", "extend", "REG"],
    "real-definition-type": ["select:signedness", "extend", "select:other", "REG"],
    # Codex categories (broad)
    "codex:types": ["extend", "select:signedness", "select:compare", "select:other", "select:muldiv", "order:epilogue", "stack:offset", "order:load", "order:store", "address:materialise", "order:regswap", "REG"],
    "codex:loop": ["loop:ctr", "loop:shape", "order:loopstep", "select:compare", "select:update", "select:indexed", "select:signedness", "order:store"],
    "codex:expression-form": ["operand-order", "order:expr", "select:other", "select:muldiv", "select:bool", "copy:ours-extra", "copy:target-extra", "REG"],
    "codex:declaration-order": ["stack:offset", "order:load", "copy:ours-extra", "address:materialise", "REG"],
    "codex:local-lifetimes": ["copy:ours-extra", "copy:target-extra", "saved-regs", "stack:offset", "operand-order", "address:materialise", "REG"],
    "codex:inline-helper": ["call:inline", "copy:ours-extra", "copy:target-extra", "saved-regs", "select:fused", "stack:offset", "REG", "operand-order", "order:args", "load:const-vs-copy", "address:materialise", "order:regswap", "loop:shape", "order:store", "order:load", "load:target-reloads"],
    "pointer-as-cse-temp-before-split-counter": ["load:const-vs-copy", "REG"],
    "codex:other": None,
    "hand": None, "try-scope-inside-if": None,
}
# every other rule in hits.jsonl is a colouring lever
DEFAULT = ["REG"]


def sh(cmd, cwd=ROOT, **kw):
    return subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, **kw)


def cases():
    seen, out = set(), []
    for l in open(ROOT / "tools/patterns/hits.jsonl"):
        if not l.strip():
            continue
        h = json.loads(l)
        if h.get("outcome") != "landed" or not h.get("landed_commit"):
            continue
        k = (h["fn"], h["landed_commit"][:7])
        if k in seen:
            continue
        seen.add(k)
        out.append(dict(fn=h["fn"], commit=h["landed_commit"], rule=h["rule_id"], src="hits", note=(h.get("note") or "")[:200]))
    cat = None
    for l in open(ROOT / "docs/regalloc_patterns.md"):
        m = re.match(r"^### (.+?) \(\d+\)", l)
        if m:
            cat = "codex:" + m.group(1).split("/")[0].strip().lower().replace(" ", "-")
            continue
        if l.startswith("## "):
            cat = None
        if not cat or not l.startswith("| `"):
            continue
        cols = [c.strip() for c in l.strip().strip("|").split("|")]
        if len(cols) < 6:
            continue
        fn, commit = cols[0].strip("`"), cols[-1].strip("` ")
        if not re.fullmatch(r"[0-9a-f]{7,40}", commit):
            continue
        k = (fn, commit[:7])
        if k in seen:
            continue
        seen.add(k)
        out.append(dict(fn=fn, commit=commit, rule=cat, src="codex", note=(cols[3] + " => " + cols[4])[:200]))
    return out


_report = None


def owner_unit(fn):
    global _report
    if _report is None:
        _report = {}
        for u in json.load(open(ROOT / f"build/{sd.VERSION}/report.json"))["units"]:
            for f in u.get("functions", []):
                _report.setdefault(f["name"], u["name"].split("/", 1)[1])
    return _report.get(fn)


def old_tree(commit, base):
    """extract commit^ (sources + build description) -> directory"""
    d = Path(base) / commit[:10]
    if (d / ".ok").exists():
        return d
    d.mkdir(parents=True, exist_ok=True)
    p = subprocess.Popen(["git", "archive", f"{commit}^", "src", "include", "libs", "configure.py", "tools", "config"],
                         cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    t = subprocess.run(["tar", "-x", "-C", str(d)], stdin=p.stdout, capture_output=True)
    p.wait()
    if p.returncode or t.returncode:
        return None
    for n in ("build", "orig"):
        if not (d / n).exists() and (ROOT / n).exists():
            os.symlink(ROOT / n, d / n)
    (d / ".ok").write_text("")
    return d


def old_command(d, unit):
    """compile command line of `unit` as the old tree's configure.py gives it"""
    if not (d / "build.ninja").exists():
        sh([sys.executable, "configure.py", "--binutils", "build/binutils", "--compilers", "build/compilers",
            "--wrapper", "build/tools/wibo"], cwd=d, timeout=300)
    if not (d / "build.ninja").exists():
        return None
    r = sh(["ninja", "-t", "commands", f"build/{sd.VERSION}/src/{unit}.o"], cwd=d)
    lines = [l for l in r.stdout.strip().splitlines() if "mwcceppc" in l]
    return lines[-1] if lines else None


def replay(c, base):
    fn, commit = c["fn"], c["commit"]
    row = dict(c)
    r = sh(["git", "show", "--name-only", "--format=", commit])
    if r.returncode:
        return dict(row, status="no_source", detail="commit not in this clone")
    changed = r.stdout.split()
    paths = [p for p in changed if p.startswith("src/") and p.endswith((".c", ".cpp", ".cp"))]
    named, other = [], []
    for p in paths:
        t = subprocess.run(["git", "show", f"{commit}^:{p}"], capture_output=True, cwd=ROOT)
        if t.returncode == 0:
            (named if re.search(rb"\b" + re.escape(fn.encode()) + rb"\b", t.stdout) else other).append(p)
    row["changed"] = [p for p in changed if not p.startswith("docs/")][:8]
    if not named and not other:
        return dict(row, status="no_source", detail="the fix commit changes no source file that existed before (asm -> C in a new file, or data/splits only)")
    owner = owner_unit(fn)
    if not owner:
        return dict(row, status="no_fn", detail="function not in today's report.json (renamed since)")
    d = old_tree(commit, base)
    if d is None:
        return dict(row, status="no_build", detail="git archive failed")
    last = None
    # the function may be defined under a C++ name: try the other changed files too
    for path in named + other[:3]:
        last = replay_path(row, fn, owner, d, path, base, by_name=path in named)
        if last["status"] not in ("no_fn", "no_build"):
            return last
    return last


def replay_path(row, fn, owner, d, path, base, by_name=True):
    row = dict(row)
    unit = os.path.splitext(path)[0][4:]
    cmdline = old_command(d, unit)
    cwd = d
    how = "old command"
    if not cmdline:
        cmdline = sd._cmd_for(unit) or sd._cmd_for(owner)
        how = "today's command"
        if not cmdline:
            return dict(row, status="no_build", detail="no compile command")
    parts = cmdline.split(" && ")
    comp = parts[0].replace(" -MMD", "")
    out = Path(tempfile.mkdtemp(prefix="o_", dir=base))
    comp = re.sub(r"-c \S+ -o \S+", lambda _: f"-c {path} -o {out}", comp)
    cp = subprocess.run(comp, shell=True, capture_output=True, text=True, cwd=cwd)
    obj = out / (Path(path).stem + ".o")
    if not obj.exists():
        return dict(row, status="no_build", detail=(how + ": " + (cp.stdout + cp.stderr).strip()[:200]).replace("\n", " "))
    # the unit's postprocess steps (renames), retargeted at our object
    orig_o = f"build/{sd.VERSION}/src/{unit}.o"
    for st in parts[1:]:
        if orig_o in st.replace("\\", "/") and "transform_dep" not in st:
            subprocess.run(st.replace("\\", "/").replace(orig_o, str(obj)), shell=True, capture_output=True, cwd=cwd)
    (tf, tst), (of, ost) = sd.disasm(ROOT / f"build/{sd.VERSION}/obj/{owner}.o"), sd.disasm(obj)
    shutil.rmtree(out, ignore_errors=True)
    res, err, picked = None, "not found", "name"
    t = sd.pick_fn(tf, fn)
    if t is not None:
        o = sd.pick_fn(of, fn)
        if o is None:
            # by body similarity, but never a function that is another target function
            ren = {k: v for v, ks in sd._renames().items() for k in ks}
            free = {k: v for k, v in of.items() if k not in tf and ren.get(k, k) not in tf}
            o = sd.pick_fn(free, fn, like=t)
            picked = "similar body"
        if o is not None:
            sd.unify(t, tst, o, ost)
            res, err = sd.analyse(t, o), None
    row["picked"] = picked
    if err:
        return dict(row, status="no_fn", detail="compiled, function not found in the old object (asm before the fix, or another name)")
    cl = [(k, len(fs), next((x.note for x in fs if x.note), "")[:160]) for k, w, fs in sd.summarise(res)]
    row.update(n_target=res["n_target"], n_ours=res["n_ours"], reg_lines=res["reg_lines"], classes=cl,
               net=res.get("net", {}), how=how, path=path)
    row["status"] = "repro" if cl else ("reg_only" if res["reg_lines"] else "same")
    return row


def cmd_run(a):
    OUT.parent.mkdir(parents=True, exist_ok=True)
    done = {}
    if OUT.exists() and not a.fresh:
        for l in open(OUT):
            r = json.loads(l)
            done[(r["fn"], r["commit"])] = r
    todo = [c for c in cases() if (not a.only or a.only in c["fn"])
            and ((c["fn"], c["commit"]) not in done or a.retry or a.only
                 or (a.retry_status and done[(c["fn"], c["commit"])]["status"] in a.retry_status.split(",")))]
    base = a.tmp or tempfile.mkdtemp(prefix="sdreplay_")
    print(f"{len(todo)} cases, trees in {base}")
    # one tree per commit: group so parallel workers do not extract the same tree twice
    by = collections.OrderedDict()
    for c in todo:
        by.setdefault(c["commit"], []).append(c)

    def work(group):
        rows = []
        for c in group:
            try:
                rows.append(replay(c, base))
            except Exception as e:
                rows.append(dict(c, status="no_build", detail=f"exception {e!r}"[:200]))
        if not a.keep:
            shutil.rmtree(Path(base) / group[0]["commit"][:10], ignore_errors=True)
        return rows
    with ThreadPoolExecutor(a.jobs) as ex:
        for rows in ex.map(work, by.values()):
            for r in rows:
                done[(r["fn"], r["commit"])] = r
                print(f"{r['status']:9s} {r['fn']} ({r['commit'][:8]}, {r['rule']}): "
                      + (", ".join(f"{k}x{n}" for k, n, _ in r.get("classes", [])) or r.get("detail", ""))[:150], flush=True)
            with open(OUT, "w") as f:
                for r in done.values():
                    f.write(json.dumps(r) + "\n")
    print(collections.Counter(r["status"] for r in done.values()))


def verdict(r):
    exp = EXPECT.get(r["rule"], DEFAULT)
    if r["status"] in ("no_source", "no_build", "no_fn", "same"):
        return "not reproducible"
    # symbol names of an old object are not comparable with today's target (renamed since)
    got = {k for k, _, _ in r.get("classes", []) if not k.startswith("reloc:")}
    if exp is None:
        return "unrated"
    if not got:
        return "register-only (right)" if "REG" in exp else "register-only (lever is structural)"
    if got & set(exp):
        return "hit"
    if "REG" in exp:
        return "register lever, other classes shown"
    return "miss"


def cmd_report(a):
    rows = [json.loads(l) for l in open(OUT)]
    st = collections.Counter(r["status"] for r in rows)
    vd = collections.Counter(verdict(r) for r in rows)
    L = ["# shapediag replay: landed fixes rebuilt from the source before the fix", "",
         "Generated by `python3 tools/shapediag_replay.py run` + `report --md docs/reports/shapediag_replay.md`.",
         "Cases: tools/patterns/hits.jsonl and the Codex table of docs/regalloc_patterns.md "
         f"({len(rows)} fixes with a commit).", "",
         "| reproduction | count |", "|---|---|"]
    names = dict(repro="diff reproduced, instruction sequence differs", reg_only="diff reproduced, register-only",
                 same="pre-fix source already has the target's instructions (fix was data / flags / elsewhere)",
                 no_source="no earlier source in the fix commit (asm -> C, or fixed outside src/)",
                 no_build="old tree does not build here", no_fn="function not found")
    for k, v in st.most_common():
        L.append(f"| {names.get(k, k)} | {v} |")
    L += ["", "| verdict (reproduced cases, against EXPECT in the tool) | count |", "|---|---|"]
    for k, v in vd.most_common():
        L.append(f"| {k} | {v} |")
    L += ["", "| verdict | rule / category | fn | commit | insns t/o | reg lines | shapediag classes | first note |", "|---|---|---|---|---|---|---|---|"]
    order = ["miss", "register-only (lever is structural)", "unrated", "register lever, other classes shown", "hit",
             "register-only (right)", "not reproducible"]
    for r in sorted(rows, key=lambda r: (order.index(verdict(r)), r["rule"], r["fn"])):
        cs = [x for x in r.get("classes", []) if not x[0].startswith("reloc:")]
        cl = ", ".join(f"{k} ({n})" for k, n, _ in cs) or r["status"]
        note = next((f"{k}: {nt}" for k, n, nt in cs if nt), r.get("detail", ""))
        note = note.replace("|", "\\|")[:150]
        L.append(f"| {verdict(r)} | {r['rule']} | `{r['fn']}` | {r['commit'][:8]} | "
                 f"{r.get('n_target', '')}/{r.get('n_ours', '')} | {r.get('reg_lines', '')} | {cl} | {note} |")
    text = "\n".join(L) + "\n"
    if a.md:
        Path(a.md).write_text(text)
    for k, v in st.most_common():
        print(f"{v:4d} {k}")
    print()
    for k, v in vd.most_common():
        print(f"{v:4d} {k}")
    if a.rules:
        by = collections.defaultdict(collections.Counter)
        for r in rows:
            if r["status"] in ("repro", "reg_only"):
                for k, _, _ in r.get("classes", []) or [("REG", 0, "")]:
                    by[r["rule"]][k] += 1
        for k, v in sorted(by.items()):
            print(f"{k}: {dict(v)}")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run")
    p.add_argument("-j", "--jobs", type=int, default=4)
    p.add_argument("--only")
    p.add_argument("--retry", action="store_true")
    p.add_argument("--fresh", action="store_true")
    p.add_argument("--retry-status", help="rerun rows with these statuses (comma separated)")
    p.add_argument("--keep", action="store_true", help="keep the extracted trees")
    p.add_argument("--tmp")
    p = sub.add_parser("report")
    p.add_argument("--md")
    p.add_argument("--rules", action="store_true", help="print classes per rule (to fill EXPECT)")
    a = ap.parse_args()
    return cmd_run(a) if a.cmd == "run" else cmd_report(a)


if __name__ == "__main__":
    sys.exit(main())
