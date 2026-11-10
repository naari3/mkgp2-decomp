#!/usr/bin/env python3
"""TU boundary audit: find translation-unit boundaries in splits.txt that the
original link layout disagrees with.

Evidence comes from the target asm that dtk writes to build/GNLJ82/asm (every
code/data reference, keyed by address, so it does not depend on how the
current splits cut the program) plus splits.txt, symbols.txt, build.ninja
(compiler per TU), configure.py (Matching/NonMatching) and report.json.

Signals
  MERGE  compiler-private data (.rodata/.sdata2 literals, strings, jump
         tables, local statics) or a static function used by functions of
         more than one TU.  CW never shares those across TUs, so every TU
         between the first and the last user was one original TU.
  OWN    data nobody owns in splits.txt (auto_ data) that only one TU's code
         uses.  The TU should own the range (section-anchor pools, RankPanel).
  SPLIT  one TU's private data falls into clusters separated by foreign or
         unreferenced data, and the clusters' users are disjoint runs of the
         TU's functions (RaceHud -> CSSceneGetTitle).  Also: more than one
         static initializer (.ctors entry) in a TU, and mixed prologue styles
         (GC 1.x `mflr; stw r0,4(r1); stwu` vs 2.x `stwu; mflr`).
  CC     prologue style that disagrees with the TU's configured mw_version.

Usage
  python3 tools/tu_audit.py                      # writes docs/reports/tu_boundary_audit.md
  python3 tools/tu_audit.py --claims claims.txt  # flag claimed TUs (one path per line,
                                                 # or `[unit-claim] retrofit:<path>` titles)
  python3 tools/tu_audit.py --fetch-claims       # claims via `gh api` (explicit pages)
  python3 tools/tu_audit.py --rev <git rev>      # audit an older splits.txt
  python3 tools/tu_audit.py validate             # re-find past merges/splits
  python3 tools/tu_audit.py --json out.json      # full machine-readable output
Needs a finished `ninja` (asm, report.json).
"""
import argparse
import bisect
import functools
import collections
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VER = "GNLJ82"
ASM_DIR = os.path.join(ROOT, "build", VER, "asm")

DATA_SECS = (".rodata", ".sdata2", ".data", ".sdata", ".bss", ".sbss", ".sbss2")
# literal pools: CW emits these per TU and never shares them
POOL_SECS = (".rodata", ".sdata2")
TEXT_SECS = (".text", ".init")

# past wins used by `validate`: (commit, kind, what)
KNOWN_WINS = [
    ("0195f28", "merge", "tobj: 10 split TUs -> tobj_nm.c"),
    ("b40edd9", "merge", "cobj/lobj whole-file merges"),
    ("70325a3", "merge", "texpdag_unlock -> texpdag_nm1"),
    ("924f64a", "split", "RaceHud 0x8014ADB4.. -> CSSceneGetTitle"),
    ("d5f92ed", "own", "RankPanel owns .rodata 0x80361D60..0x80361ED0"),
]


def h(x):
    return "0x%08X" % x


# ---------------------------------------------------------------- inputs

def parse_splits(text):
    """-> list of units {name, ranges{sec:(s,e)}} in file order."""
    units, cur, in_sections = [], None, False
    for line in text.splitlines():
        if not line.strip():
            continue
        if not line[0].isspace():
            name = line.rstrip()
            if name.endswith(":"):
                name = name[:-1]
            in_sections = name == "Sections"
            cur = None if in_sections else {"name": name.split(":")[0].strip(), "ranges": {}}
            if cur:
                units.append(cur)
            continue
        if cur is None:
            continue
        m = re.match(r"\s+(\S+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)", line)
        if m:
            cur["ranges"][m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
    return units


@functools.lru_cache(None)
def parse_symbols(path):
    syms = {}
    rx = re.compile(r'^("[^"]+"|\S+) = ([.\w]+):0x([0-9A-Fa-f]+); // (.*)$')
    for line in open(path, encoding="utf-8", errors="replace"):
        m = rx.match(line)
        if not m:
            continue
        attrs = dict(a.split(":", 1) for a in m.group(4).split() if ":" in a)
        syms[int(m.group(3), 16)] = {
            "name": m.group(1).strip('"'), "sec": m.group(2),
            "type": attrs.get("type", ""), "scope": attrs.get("scope", ""),
            "data": attrs.get("data", ""),
        }
    return syms


HDR = re.compile(r"^# (\.?[\w]+):0x[0-9A-Fa-f]+ \| 0x([0-9A-Fa-f]+) \| size: 0x([0-9A-Fa-f]+)")
DEF = re.compile(r'^\.(fn|obj|sym) ("[^"]+"|[^,\s]+)')
INSN = re.compile(r"^/\* ([0-9A-F]{8}) [0-9A-F]{8}  [0-9A-F ]{11} \*/\t(\S+)\s*(.*)$")
REL = re.compile(r'("[^"]+"|[A-Za-z_$?.][^\s,()@"+]*)(?:\+0x[0-9A-Fa-f]+)?@(ha|h|l|sda21)')
BR = re.compile(r'^("[^"]+"|[^\s,]+)$')
DWORD = re.compile(r'^\s+\.4byte ("[^"]+"|[A-Za-z_$?.@][^\s+"]*)')


@functools.lru_cache(None)
def parse_asm():
    """-> objs {addr: {name,sec,size,kind}}, refs [(src_addr, src_kind, tgt_name)],
          prolog {fn_addr: 'old'|'new'|None}, ctors [fn names]"""
    objs, refs, prolog, ctors = {}, [], {}, []
    for dp, _, fs in os.walk(ASM_DIR):
        for f in fs:
            if not f.endswith(".s"):
                continue
            sec, pend, cur, cur_kind, first = None, None, None, None, []
            for line in open(os.path.join(dp, f), encoding="utf-8", errors="replace"):
                if line.startswith(".section") or line.rstrip() in (".text", ".data", ".rodata", ".bss", ".init"):
                    sec = line.split()[1].rstrip(",") if line.startswith(".section") else line.strip()
                    sec = sec.strip('"')
                    continue
                m = HDR.match(line)
                if m:
                    pend = (m.group(1), int(m.group(2), 16), int(m.group(3), 16))
                    continue
                m = DEF.match(line)
                if m and pend:
                    if cur_kind == "fn" and cur is not None:
                        prolog[cur] = _style(first)
                    kind = m.group(1)
                    name = m.group(2).strip('"')
                    s, a, sz = pend
                    objs[a] = {"name": name, "sec": s, "size": sz, "kind": kind}
                    cur, cur_kind, first, pend = a, kind, [], None
                    continue
                if cur is None:
                    continue
                if sec == ".ctors":
                    m = DWORD.match(line)
                    if m:
                        ctors.append(m.group(1).strip('"'))
                    continue
                if sec in ("extab", "extabindex"):
                    continue
                m = INSN.match(line)
                if m:
                    op, args = m.group(2), m.group(3)
                    if len(first) < 6:
                        first.append((op, args))
                    for r in REL.finditer(args):
                        refs.append((cur, "code", r.group(1).strip('"')))
                    if op in ("b", "bl") and BR.match(args.strip()):
                        t = args.strip().strip('"')
                        if not t.startswith(".L"):
                            refs.append((cur, "code", t))
                    continue
                m = DWORD.match(line)
                if m and cur_kind == "obj":
                    t = m.group(1).strip('"')
                    if not t.startswith(".L") and not t.startswith("0x"):
                        refs.append((cur, "data", t))
            if cur_kind == "fn" and cur is not None:
                prolog[cur] = _style(first)
    return objs, refs, prolog, ctors


def _style(first):
    ops = [(o, a.replace(" ", "")) for o, a in first]
    for i, (o, a) in enumerate(ops):
        if o == "stwu" and a.endswith("(r1)") and a.startswith("r1,"):
            return "new" if any(x == "mflr" for x, _ in ops[i + 1:i + 3]) else None
        if o == "mflr" and a == "r0":
            nxt = ops[i + 1:i + 3]
            if nxt and nxt[0][0] == "stw" and nxt[0][1] == "r0,0x4(r1)":
                return "old"
            return None
    return None


@functools.lru_cache(None)
def parse_configure():
    """-> {tu_path: True(Matching)/False}"""
    st = {}
    for line in open(os.path.join(ROOT, "configure.py"), encoding="utf-8"):
        m = re.search(r'Object\(\s*(\w+)\s*,\s*"([^"]+)"', line)
        if m:
            st[m.group(2)] = m.group(1)
    return st


@functools.lru_cache(None)
def parse_ninja():
    """-> {tu_path: mw_version}"""
    cc, cur = {}, None
    p = os.path.join(ROOT, "build.ninja")
    if not os.path.exists(p):
        return cc
    for line in open(p, encoding="utf-8", errors="replace"):
        m = re.match(r"^build build/%s/src/(\S+)\.o: mwcc" % VER, line)
        if m:
            cur = m.group(1)
            continue
        if cur:
            m = re.match(r"\s+mw_version = (\S+)", line)
            if m:
                cc[cur] = m.group(1)
                cur = None
            elif line.startswith("build "):
                cur = None
    return cc


@functools.lru_cache(None)
def parse_report():
    """-> {unit_stem: {fn_addr: fuzzy%}}"""
    p = os.path.join(ROOT, "build", VER, "report.json")
    out = {}
    if not os.path.exists(p):
        return out
    for u in json.load(open(p)).get("units", []):
        name = u["name"].split("/", 1)[1] if "/" in u["name"] else u["name"]
        fns = {}
        for f in u.get("functions", []) or []:
            va = int(f.get("metadata", {}).get("virtual_address", 0) or 0)
            if va:
                fns[va] = f.get("fuzzy_match_percent", 0.0) or 0.0
        out[name] = fns
    return out


def load_claims(path, fetch):
    claims = set()
    lines = []
    if path:
        lines += open(path, encoding="utf-8").read().splitlines()
    if fetch:
        page = 1
        while True:
            try:
                out = subprocess.run(
                    ["gh", "api", "repos/naari3/mkgp2-decomp/issues?labels=unit-claim&state=open&per_page=100&page=%d" % page],
                    capture_output=True, text=True, check=True).stdout
            except Exception as e:  # noqa
                print("claim fetch failed: %s" % e, file=sys.stderr)
                break
            items = json.loads(out)
            for it in items:
                lines.append(it["title"] + "\t" + ((it.get("user") or {}).get("login") or ""))
            if len(items) < 100:
                break
            page += 1
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        who = ""
        if "\t" in line:
            line, who = line.split("\t", 1)
        m = re.search(r"retrofit:(\S+)", line)
        path_ = m.group(1) if m else line.split()[0]
        claims.add((path_, who.strip()))
    return claims


DIFF_DIR = os.path.join(ROOT, "build", VER, "tu_audit_disasm")


def _bodies(path):
    out, cur = {}, None
    for line in open(path, encoding="utf-8", errors="replace"):
        if line.startswith(".fn "):
            cur = line[4:].split(",")[0].strip().strip('"')
            out[cur] = []
            continue
        if line.startswith(".endfn"):
            cur = None
            continue
        if cur is None:
            continue
        mm = re.match(r"/\* [0-9A-F]+ [0-9A-F]+  .. .. .. .. \*/\t(.*)", line)
        if mm:
            out[cur].append(re.sub(r"\.L_[0-9A-F]+", ".L", mm.group(1)))
    return out


_SYMREF = re.compile(r'("[^"]+"|[A-Za-z_$?.@][^\s,()"+]*)(\+0x[0-9A-Fa-f]+)?@(ha|h|l|sda21)')


def _symrefs(lines):
    # names are normalised away: an owned object shows up as `...rodata.0` or `@123` in our
    # object, which is fine; what matters is whether a reference exists at all
    return collections.Counter(mm.group(3) for l in lines for mm in _SYMREF.finditer(l))


def classify_diffs(m):
    """For every not-yet-matching function of a built TU: 'reg' (only register numbers
    differ), 'sched' (same instructions, other order), 'reloc' (the set of symbol
    references differs: section anchor / data ownership / literal pooling), 'other'. -> {fn_addr: (class, n_diff_lines)}"""
    import difflib
    os.makedirs(DIFF_DIR, exist_ok=True)
    dtk = os.path.join(ROOT, "build", "tools", "dtk")
    tgt_cache = {}
    out = {}
    for u in m.units:
        if u["auto"]:
            continue
        nm = [(f, p) for f, p in m.nonmatch_fns(u["id"]) if p is not None]
        if not nm:
            continue
        obj = os.path.join(ROOT, "build", VER, "src", u["stem"] + ".o")
        tobj = os.path.join(ASM_DIR, u["stem"] + ".s")
        if not os.path.exists(obj) or not os.path.exists(tobj):
            continue
        mine_s = os.path.join(DIFF_DIR, u["stem"].replace("/", "__") + ".s")
        if not os.path.exists(mine_s) or os.path.getmtime(mine_s) < os.path.getmtime(obj):
            subprocess.run([dtk, "elf", "disasm", obj, mine_s], capture_output=True)
        if not os.path.exists(mine_s):
            continue
        mine = _bodies(mine_s)
        tgt = tgt_cache.setdefault(tobj, _bodies(tobj))
        for f, _ in nm:
            name = m.objs[f]["name"]
            a, b = tgt.get(name), mine.get(name)
            if a is None or b is None:
                continue
            dl = [l[1:] for l in difflib.unified_diff(a, b, lineterm="", n=0)
                  if l[:1] in "+-" and not l.startswith(("+++", "---"))]
            if not dl:
                continue
            regn = lambda x: re.sub(r"\b[rf]\d+\b", "R", x)
            if len(a) == len(b) and all(regn(x) == regn(y) for x, y in zip(a, b)):
                cls = "reg"
            elif _symrefs(a) != _symrefs(b):
                cls = "reloc"
            elif sorted(map(regn, a)) == sorted(map(regn, b)):
                cls = "sched"
            else:
                cls = "other"
            out[f] = (cls, len(dl))
    return out


# ---------------------------------------------------------------- model

class Model:
    def __init__(self, splits_text, claims=()):
        self.syms = parse_symbols(os.path.join(ROOT, "config", VER, "symbols.txt"))
        self.objs, raw_refs, self.prolog, self.ctors = parse_asm()
        self.status = parse_configure()
        self.cc = parse_ninja()
        self.report = parse_report()
        self.claims = {}
        for p, who in claims:
            self.claims[self._stem(p)] = who
        self.byname = {}
        for a, o in self.objs.items():
            self.byname.setdefault(o["name"], a)
        for a, s in self.syms.items():
            self.byname.setdefault(s["name"], a)
        self._build_units(parse_splits(splits_text))
        self.fn_addrs = sorted(a for a, o in self.objs.items() if o["kind"] == "fn")
        # refs resolved to addresses
        self.users = collections.defaultdict(set)      # tgt addr -> {src fn addr}
        self.dusers = collections.defaultdict(set)     # tgt addr -> {src data obj addr}
        self.calls = collections.defaultdict(set)      # fn addr -> {callers}
        for src, kind, name in raw_refs:
            t = self.byname.get(name)
            if t is None or t == src:
                continue
            to = self.objs.get(t)
            if to is None:
                continue
            if kind == "code":
                if to["kind"] == "fn":
                    self.calls[t].add(src)
                else:
                    self.users[t].add(src)
            else:
                self.dusers[t].add(src)
        # one level of propagation: data used only through a table inherits the table's users
        self.iusers = collections.defaultdict(set)
        for t, srcs in self.dusers.items():
            for s in srcs:
                so = self.objs.get(s)
                if so and so["kind"] != "fn":
                    self.iusers[t] |= self.users.get(s, set())

    @staticmethod
    def _stem(p):
        return re.sub(r"\.(c|cpp|cp|s)$", "", p)

    def _build_units(self, units):
        # add auto pseudo-units for unsplit .text gaps so unsplit code counts as its own unit
        text_fns = sorted((a, o["size"]) for a, o in self.objs.items()
                          if o["kind"] == "fn" and o["sec"] == ".text")
        owned = sorted((u["ranges"][".text"][0], u["ranges"][".text"][1])
                       for u in units if ".text" in u["ranges"])
        gaps, cur = [], None
        starts = [s for s, _ in owned]
        for a, sz in text_fns:
            i = bisect.bisect_right(starts, a) - 1
            inside = i >= 0 and owned[i][0] <= a < owned[i][1]
            if inside:
                cur = None
                continue
            if cur and cur["ranges"][".text"][1] == a:
                cur["ranges"][".text"] = (cur["ranges"][".text"][0], a + sz)
            else:
                cur = {"name": "auto_text_%08X" % a, "ranges": {".text": (a, a + sz)}, "auto": True}
                gaps.append(cur)
        self.units = units + gaps
        for i, u in enumerate(self.units):
            u["id"] = i
            u.setdefault("auto", False)
            u["stem"] = self._stem(u["name"])
        tus = sorted((u for u in self.units if ".text" in u["ranges"]),
                     key=lambda u: u["ranges"][".text"][0])
        for k, u in enumerate(tus):
            u["pos"] = k
        self.text_units = tus
        self.iv = {}
        for sec in TEXT_SECS + DATA_SECS + (".ctors",):
            lst = sorted((u["ranges"][sec][0], u["ranges"][sec][1], u["id"])
                         for u in self.units if sec in u["ranges"])
            self.iv[sec] = ([x[0] for x in lst], lst)

    def unit_at(self, sec, addr):
        if sec not in self.iv:
            return None
        starts, lst = self.iv[sec]
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0 and lst[i][0] <= addr < lst[i][1]:
            return lst[i][2]
        return None

    def fn_unit(self, fa):
        o = self.objs[fa]
        return self.unit_at(o["sec"], fa)

    def fns_of(self, uid):
        u = self.units[uid]
        if ".text" not in u["ranges"]:
            return []
        s, e = u["ranges"][".text"]
        i = bisect.bisect_left(self.fn_addrs, s)
        out = []
        while i < len(self.fn_addrs) and self.fn_addrs[i] < e:
            out.append(self.fn_addrs[i])
            i += 1
        return out

    def user_units(self, addr, indirect=True):
        srcs = set(self.users.get(addr, ()))
        if indirect:
            srcs |= self.iusers.get(addr, set())
        return {self.fn_unit(s) for s in srcs} - {None}

    def is_private(self, addr):
        o = self.objs[addr]
        name = o["name"]
        sym = self.syms.get(addr, {})
        if o["sec"] in POOL_SECS:
            return True
        if name.startswith("@") or name.startswith("jumptable") or "$" in name:
            return True
        if sym.get("scope") == "local" or sym.get("data") == "string":
            return True
        return False

    def is_anon(self, addr):
        n = self.objs[addr]["name"]
        # provisional names from tools/data_names.py (`Foo_data_80401234`) count as unnamed
        return (n.startswith("lbl_") or n.startswith("@") or n.startswith("jumptable") or "$" in n
                or re.search(r"_(data|bss|rodata)_[0-9A-F]{8}$", n) is not None)

    # -- per unit info
    def status_of(self, uid):
        u = self.units[uid]
        if u["auto"]:
            return "asm"
        st = self.status.get(u["name"])
        return {"Matching": "Matching", "NonMatching": "NonMatching", "Equivalent": "Equivalent"}.get(st, st or "?")

    def nonmatch_fns(self, uid):
        u = self.units[uid]
        rep = self.report.get(u["stem"]) or self.report.get(u["name"])
        fns = self.fns_of(uid)
        if u["auto"] or rep is None:
            return [(f, None) for f in fns]
        return [(f, rep.get(f)) for f in fns if rep.get(f) is not None and rep.get(f) < 100.0]

    def claim_of(self, uid):
        return self.claims.get(self.units[uid]["stem"])

    def label(self, uid):
        u = self.units[uid]
        s = u["name"]
        if ".text" in u["ranges"]:
            a, b = u["ranges"][".text"]
            s += " [%X..%X]" % (a, b)
        return s


# ---------------------------------------------------------------- signals

def find_merges(m, max_units=24, max_bytes=0x20000):
    """Private data (or static fn) used from >1 unit -> unit position spans."""
    ev = collections.defaultdict(list)  # (pmin,pmax) -> [(addr, users)]
    for a, o in m.objs.items():
        if o["kind"] == "fn":
            sym = m.syms.get(a, {})
            if sym.get("scope") != "local":
                continue
            us = {m.fn_unit(c) for c in m.calls.get(a, ())} | {m.fn_unit(a)}
        else:
            if o["sec"] not in DATA_SECS or not m.is_private(a):
                continue
            us = m.user_units(a, indirect=False)
            own = m.unit_at(o["sec"], a)
            if own is not None and ".text" in m.units[own]["ranges"]:
                us = us | {own}
        us = {u for u in us if u is not None and "pos" in m.units[u]}
        if len(us) < 2:
            continue
        ps = sorted(m.units[u]["pos"] for u in us)
        lo, hi = m.text_units[ps[0]], m.text_units[ps[-1]]
        dist = hi["ranges"][".text"][0] - lo["ranges"][".text"][1]
        if ps[-1] - ps[0] > max_units or dist > max_bytes:
            continue
        if not m.is_anon(a) and o["kind"] != "fn" and o["sec"] not in POOL_SECS:
            continue
        ev[(ps[0], ps[-1])].append(a)
    # union overlapping spans
    spans = sorted(ev)
    groups = []
    for lo, hi in spans:
        if groups and lo <= groups[-1]["hi"]:
            g = groups[-1]
            g["hi"] = max(g["hi"], hi)
        else:
            g = {"lo": lo, "hi": hi, "ev": []}
            groups.append(g)
        g["ev"] += ev[(lo, hi)]
    out = []
    for g in groups:
        uids = [m.text_units[p]["id"] for p in range(g["lo"], g["hi"] + 1)]
        secs = collections.Counter(m.objs[a]["sec"] for a in g["ev"])
        w = sum(1.0 if m.is_anon(a) else 0.4 for a in g["ev"])
        out.append({"kind": "merge", "units": uids, "evidence": sorted(set(g["ev"])),
                    "secs": dict(secs), "weight": w})
    return out


def find_owns(m):
    """Unowned data used only by one (non-auto) unit."""
    out = []
    for sec in DATA_SECS:
        objs = sorted(a for a, o in m.objs.items() if o["sec"] == sec and o["kind"] != "fn")
        run = None

        def flush():
            if run and run["uses"]:
                out.append(run)
        for a in objs:
            o = m.objs[a]
            if m.unit_at(sec, a) is not None:
                flush()
                run = None
                continue
            us = m.user_units(a)
            if not us:
                if run:
                    run["end"] = a + o["size"]
                    run["unref"] += 1
                continue
            if len(us) == 1:
                u = next(iter(us))
                if m.units[u]["auto"]:
                    flush()
                    run = None
                    continue
                if run and run["unit"] == u:
                    run["end"] = a + o["size"]
                    run["uses"] += 1
                    run["objs"].append(a)
                    continue
                flush()
                run = {"kind": "own", "unit": u, "sec": sec, "start": a, "end": a + o["size"],
                       "uses": 1, "unref": 0, "objs": [a]}
                continue
            flush()
            run = None
        flush()
    # trim trailing unreferenced objects (they may belong to the next TU)
    for r in out:
        last = r["objs"][-1]
        r["end"] = last + m.objs[last]["size"]
    return out


def find_splits(m, min_gap=0x100):
    out = []
    for sec in (".rodata", ".sdata2", ".data"):
        secobjs = sorted(a for a, o in m.objs.items() if o["sec"] == sec and o["kind"] != "fn")
        uu = [m.user_units(a) for a in secobjs]
        # foreign[i] = number of objects in [0, i) used by any unit (prefix sums by unit later)
        excl = collections.defaultdict(list)  # unit -> [obj index]
        for i, us in enumerate(uu):
            if len(us) == 1:
                excl[next(iter(us))].append(i)
        used_pref = [0]
        for us in uu:
            used_pref.append(used_pref[-1] + (1 if us else 0))
        for uid, idxs in excl.items():
            u = m.units[uid]
            if u["auto"] or ".text" not in u["ranges"] or len(idxs) < 2:
                continue
            fns = m.fns_of(uid)
            if len(fns) < 2:
                continue
            fidx = {f: i for i, f in enumerate(fns)}
            mine = []
            for i in idxs:
                a = secobjs[i]
                srcs = m.users.get(a, set()) | m.iusers.get(a, set())
                mine.append((i, a, sorted(fidx[s] for s in srcs if s in fidx)))
            clusters = [[mine[0]]]
            for prev, cur in zip(mine, mine[1:]):
                # objects strictly between that some unit uses are foreign (excl. ones are ours or other's)
                foreign = used_pref[cur[0]] - used_pref[prev[0] + 1]
                gap = cur[1] - (prev[1] + m.objs[prev[1]]["size"])
                if foreign or gap >= min_gap:
                    clusters.append([cur])
                else:
                    clusters[-1].append(cur)
            if len(clusters) < 2:
                continue
            spans = []
            for c in clusters:
                ix = [k for _, _, l in c for k in l]
                if not ix:
                    continue
                spans.append((min(ix), max(ix), c[0][1], c[-1][1] + m.objs[c[-1][1]]["size"]))
            for (lo1, hi1, s1, e1), (lo2, hi2, s2, e2) in zip(spans, spans[1:]):
                if hi1 < lo2:
                    out.append({"kind": "split", "unit": uid, "sec": sec, "at": fns[lo2],
                                "earliest": fns[hi1 + 1],
                                "first": (s1, e1, lo1, hi1), "second": (s2, e2, lo2, hi2),
                                "gap": s2 - e1, "nfns": len(fns)})
    # merge evidence for the same split point across sections
    byk = collections.defaultdict(list)
    for s in out:
        byk[(s["unit"], s["at"])].append(s)
    res = []
    for (uid, at), ss in byk.items():
        res.append({"kind": "split", "unit": uid, "at": at, "secs": [s["sec"] for s in ss],
                    "detail": ss, "weight": len(ss) + sum(1 for s in ss if s["gap"] >= 0x20) * 0.5})
    return res


def find_ctor_splits(m):
    out = []
    per = collections.defaultdict(list)
    for name in m.ctors:
        a = m.byname.get(name)
        if a is None or a not in m.objs:
            continue
        uid = m.fn_unit(a)
        if uid is not None:
            per[uid].append(a)
    for uid, fs in per.items():
        if len(fs) > 1:
            out.append({"kind": "sinit", "unit": uid, "fns": sorted(fs)})
    return out


def find_cc(m):
    """prologue style per unit; mixed styles and style vs configured compiler."""
    # learn style per compiler from Matching TUs
    learn = collections.defaultdict(collections.Counter)
    per_unit = {}
    for u in m.units:
        if ".text" not in u["ranges"]:
            continue
        sts = [(f, m.prolog.get(f)) for f in m.fns_of(u["id"])]
        sts = [(f, s) for f, s in sts if s]
        per_unit[u["id"]] = sts
        cc = m.cc.get(u["stem"])
        if cc and m.status_of(u["id"]) == "Matching":
            for _, s in sts:
                learn[cc][s] += 1
    style_of_cc = {}
    for cc, c in learn.items():
        tot = sum(c.values())
        top, n = c.most_common(1)[0]
        if tot >= 5 and n / tot > 0.97:
            style_of_cc[cc] = top
    out = []
    for uid, sts in per_unit.items():
        kinds = [s for _, s in sts]
        if "old" in kinds and "new" in kinds:
            # boundaries where style changes
            ch = [sts[i + 1][0] for i in range(len(sts) - 1) if sts[i][1] != sts[i + 1][1]]
            out.append({"kind": "cc-mixed", "unit": uid, "changes": ch,
                        "old": kinds.count("old"), "new": kinds.count("new")})
            continue
        if not kinds:
            continue
        cc = m.cc.get(m.units[uid]["stem"])
        exp = style_of_cc.get(cc)
        if cc and exp and kinds[0] != exp:
            out.append({"kind": "cc-mismatch", "unit": uid, "cc": cc, "style": kinds[0],
                        "expected": exp, "n": len(kinds)})
    return out, style_of_cc, learn


# ---------------------------------------------------------------- ranking/report

def annotate(m, p):
    uids = p["units"] if "units" in p else [p["unit"]]
    nm = []
    for u in uids:
        nm += [(u, f, s) for f, s in m.nonmatch_fns(u)]
    p["nonmatch"] = nm
    # "hot": not-yet-matching functions that touch the evidence data themselves
    ev = set(p.get("evidence", ())) | set(p.get("objs", ()))
    if p["kind"] == "split":
        lo = p["detail"][0]["second"][2]
        fns = m.fns_of(p["unit"])
        hotf = set(fns[lo:])
        p["hot"] = [x for x in nm if x[1] in hotf]
    else:
        srcs = set()
        for a in ev:
            srcs |= m.users.get(a, set()) | m.iusers.get(a, set()) | m.calls.get(a, set())
        p["hot"] = [x for x in nm if x[1] in srcs]
    p["hot_reloc"] = [x for x in p["hot"] if getattr(m, "diffcls", {}).get(x[1], ("",))[0] == "reloc"]
    if p["kind"] == "merge":
        # smallest sub-span per hot function: the TUs that share evidence with it
        p["minimal"] = []
        for u, f, pct in p["hot"]:
            pos = {m.units[u]["pos"]}
            for a in ev:
                if f in (m.users.get(a, set()) | m.calls.get(a, set())):
                    for uu in m.user_units(a, indirect=False) | ({m.fn_unit(c) for c in m.calls.get(a, ())} - {None}):
                        if "pos" in m.units[uu]:
                            pos.add(m.units[uu]["pos"])
                    if m.objs[a]["kind"] == "fn":
                        pos.add(m.units[m.fn_unit(a)]["pos"])
            span = [m.text_units[k]["id"] for k in range(min(pos), max(pos) + 1)]
            p["minimal"].append((f, pct, span))
    p["matching_units"] = [u for u in uids if m.status_of(u) == "Matching"]
    p["claimed"] = [(u, m.claim_of(u)) for u in uids if m.claim_of(u) is not None]
    return p


def score(p):
    base = p.get("weight", 1.0)
    unlock = len(p["nonmatch"])
    reloc = len(p.get("hot_reloc", ()))
    s = base * (1 + 2 * len(p["hot"]) + 8 * reloc + 0.25 * (unlock - len(p["hot"])))
    # No penalty for a merge that takes the Matching flag from some TUs: the
    # original TU structure wins (docs/matching_rules.md section 2, rule 5).
    if p["claimed"]:
        s *= 0.2
    return s


def fn_label(m, f, pct=None):
    n = m.objs[f]["name"]
    c = getattr(m, "diffcls", {}).get(f)
    if c:
        n += " [%s]" % c[0]
    return n + " (asm)" if pct is None else "%s %.2f%%" % (n, pct)


def warn(m, p):
    w = []
    if p["claimed"]:
        w.append("CLAIMED: " + ", ".join("%s (%s)" % (m.units[u]["name"], who or "?") for u, who in p["claimed"]))
    if p["kind"] == "merge" and p["matching_units"] and len(p["matching_units"]) < len(p["units"]):
        w.append("note: %d Matching TU(s) lose the flag until the merged TU matches fully "
                 "(allowed when the function count rises, matching_rules 2.5): %s" % (
            len(p["matching_units"]), ", ".join(m.units[u]["name"] for u in p["matching_units"][:6])))
    return w


def render(m, merges, owns, splits, sinits, ccs, style_of_cc, learn, validation=None, top=60):
    L = []
    L.append("# TU boundary audit")
    L.append("")
    L.append("Generated by `python3 tools/tu_audit.py` (see its docstring). Re-run after ninja; "
             "the claims check needs `--claims FILE` or `--fetch-claims`.")
    L.append("")
    L.append("Evidence is address-based (target asm), so it is independent of the current cuts. "
             "Scores = evidence weight x (1 + non-matching functions in the touched TUs); "
             "near misses with a reloc/anchor diff weigh most. A merge that takes the Matching flag "
             "from some TUs is NOT discounted (matching_rules section 2, rule 5: land it when main.dol "
             "is OK and the count of 100% functions rises); claimed TUs are heavily discounted.")
    L.append("")
    L.append("Claims loaded: %d (%s). Re-check open unit-claims before acting." % (
        len(m.claims), ", ".join(sorted("%s=%s" % (k, v or "?") for k, v in m.claims.items())) or "none"))
    L.append("")
    L.append("| signal | proposals |")
    L.append("|---|---|")
    L.append("| MERGE (private data/static fn shared across TUs) | %d |" % len(merges))
    L.append("| SPLIT (data clusters line up with a function boundary) | %d |" % len(splits))
    L.append("| OWN (unowned data used by exactly one TU) | %d |" % len(owns))
    L.append("| SINIT (more than one static initializer in a TU) | %d |" % len(sinits))
    L.append("| CC (mixed prologue styles / style vs mw_version) | %d |" % len(ccs))
    L.append("")
    if validation:
        L.append("## Validation against past wins")
        L.append("")
        L.append("Each commit's parent splits.txt was audited; the row is OK when a proposal "
                 "covers the TUs that commit changed.")
        L.append("")
        L.append("| commit | kind | what | found |")
        L.append("|---|---|---|---|")
        for c, k, what, ok, note in validation:
            L.append("| %s | %s | %s | %s %s |" % (c, k, what, "OK" if ok else "MISSED", note))
        L.append("")

    def nm_str(p, k=8):
        nm = p["nonmatch"]
        if not nm:
            return "none (already matched code)"
        xs = [fn_label(m, f, s) for _, f, s in nm[:k]]
        return "%d: %s%s" % (len(nm), ", ".join(xs), " ..." if len(nm) > k else "")

    if getattr(m, "diffcls", None):
        cnt = collections.Counter(c for c, _ in m.diffcls.values())
        L.append("## Near-miss diff classes")
        L.append("")
        L.append("Every not-yet-matching function of a built TU, diffed against the target: "
                 "`reg` = only register numbers differ, `sched` = same instructions in another "
                 "order, `reloc` = the symbol references themselves differ (section anchor, data "
                 "ownership, literal pooling: the kind a TU boundary fix can solve), `other`. "
                 "Counts: %s. `reloc` functions get a large score bonus below." % dict(cnt))
        L.append("")
        L.append("| fn | TU | diff lines | proposals touching it |")
        L.append("|---|---|---|---|")
        allp = [(k, i, p) for k, ps in (("M", sorted(merges, key=score, reverse=True)),
                                       ("S", sorted(splits, key=score, reverse=True)),
                                       ("O", sorted(owns, key=score, reverse=True))) for i, p in enumerate(ps, 1)]
        for f, (c, n) in sorted(m.diffcls.items(), key=lambda x: x[1][1]):
            if c != "reloc":
                continue
            refs = ["%s%d" % (k, i) for k, i, p in allp if any(x[1] == f for x in p["hot"])][:6]
            L.append("| `%s` | `%s` | %d | %s |" % (m.objs[f]["name"], m.units[m.fn_unit(f)]["name"], n, ", ".join(refs) or "-"))
        L.append("")
    L.append("## MERGE proposals")
    L.append("")
    L.append("Every TU between the first and last user of a shared private object was one TU. "
             "Merge recipe: docs/thread_tips.md 'Over-split class TU merge recipe'.")
    L.append("")
    for i, p in enumerate(sorted(merges, key=score, reverse=True)[:top], 1):
        us = p["units"]
        L.append("### M%d. %d TUs %X..%X (score %.1f)" % (
            i, len(us), m.units[us[0]]["ranges"][".text"][0], m.units[us[-1]]["ranges"][".text"][1], score(p)))
        for w in warn(m, p):
            L.append("- **%s**" % w)
        L.append("- TUs: " + ", ".join("`%s` (%s)" % (m.units[u]["name"], m.status_of(u)) for u in us[:14])
                 + (" ..." if len(us) > 14 else ""))
        ev = p["evidence"]
        L.append("- evidence: %d shared objects %s, e.g. %s" % (
            len(ev), json.dumps(p["secs"]),
            ", ".join("`%s`" % m.objs[a]["name"] for a in ev[:6])))
        L.append("- not yet matching: " + nm_str(p) + "; touching the shared data: %d" % len(p["hot"]))
        seen = set()
        for f, pct, span in p.get("minimal", []):
            key = tuple(span)
            if len(span) < 2 or key in seen:
                continue
            seen.add(key)
            nmat = sum(1 for x in span if m.status_of(x) == "Matching")
            L.append("  - smallest merge for `%s`: %d TUs `%s` .. `%s` (%d Matching)" % (
                fn_label(m, f, pct), len(span), m.units[span[0]]["name"], m.units[span[-1]]["name"], nmat))
        L.append("")
    L.append("## SPLIT proposals")
    L.append("")
    L.append("The TU's private data forms separate clusters (foreign or unreferenced data, or a "
             ">=0x100 gap, between them) and each cluster is used by its own run of functions. "
             "Cut the TU at the given function; the new TU owns the second cluster.")
    L.append("")
    for i, p in enumerate(sorted(splits, key=score, reverse=True)[:top], 1):
        u = p["unit"]
        L.append("### S%d. `%s` at %s (`%s`) (score %.1f)" % (
            i, m.units[u]["name"], h(p["at"]), m.objs[p["at"]]["name"], score(p)))
        for w in warn(m, p):
            L.append("- **%s**" % w)
        L.append("- status %s, %d functions; cut anywhere from `%s` to `%s`" % (
            m.status_of(u), p["detail"][0]["nfns"],
            m.objs[max(d["earliest"] for d in p["detail"])]["name"], m.objs[p["at"]]["name"]))
        for d in p["detail"]:
            s1, e1, a1, b1 = d["first"]
            s2, e2, a2, b2 = d["second"]
            L.append("- %s: fns #%d..#%d use %X..%X, fns #%d..#%d use %X..%X (gap 0x%X)" % (
                d["sec"], a1, b1, s1, e1, a2, b2, s2, e2, d["gap"]))
        L.append("- not yet matching: " + nm_str(p) + "; in the second part: %d" % len(p["hot"]))
        L.append("")
    L.append("## OWN proposals")
    L.append("")
    L.append("Unowned (auto_) data that only this TU's code uses. Add the range to the TU in "
             "splits.txt and define the objects (docs/thread_tips.md 'section anchor'). Ranges stop at the "
             "last referenced object; trailing unreferenced objects may belong to the next TU.")
    L.append("")
    L.append("| # | TU | status | section | range | objs | users not matching | warn |")
    L.append("|---|---|---|---|---|---|---|---|")
    for i, p in enumerate(sorted(owns, key=score, reverse=True)[:top * 2], 1):
        u = p["unit"]
        L.append("| O%d | `%s` | %s | %s | %X..%X | %d | %s | %s |" % (
            i, m.units[u]["name"], m.status_of(u), p["sec"], p["start"], p["end"], p["uses"],
            ", ".join(fn_label(m, f, x) for _, f, x in p["hot"][:4]) or "-", "; ".join(warn(m, p))))
    L.append("")
    L.append("## SINIT: more than one static initializer in one TU")
    L.append("")
    for p in sinits:
        L.append("- `%s`: %s" % (m.units[p["unit"]]["name"], ", ".join(m.objs[f]["name"] for f in p["fns"])))
    if not sinits:
        L.append("- none")
    L.append("")
    L.append("## CC: compiler-version hints")
    L.append("")
    L.append("Prologue style learned from Matching TUs: " + ", ".join(
        "%s=%s" % (cc, style_of_cc[cc]) for cc in sorted(style_of_cc)) + ". "
        "Style counts (old=`mflr; stw r0,4(r1); stwu`, new=`stwu; mflr`): " + ", ".join(
        "%s %s" % (cc, dict(learn[cc])) for cc in sorted(learn)) + ".")
    L.append("")
    for p in sorted(ccs, key=lambda p: (p["kind"], m.units[p["unit"]]["name"])):
        u = p["unit"]
        if p["kind"] == "cc-mixed":
            L.append("- MIXED `%s` (%s): %d old / %d new, style changes at %s" % (
                m.units[u]["name"], m.status_of(u), p["old"], p["new"],
                ", ".join("`%s`" % m.objs[f]["name"] for f in p["changes"][:6])))
        else:
            L.append("- `%s` (%s) is %s but its %d prologues are %s-style (expected %s)" % (
                m.units[u]["name"], m.status_of(u), p["cc"], p["n"], p["style"], p["expected"]))
    L.append("")
    return "\n".join(L)


def run_audit(splits_text, claims=(), diffs=False):
    m = Model(splits_text, claims)
    m.diffcls = classify_diffs(m) if diffs else {}
    merges = [annotate(m, p) for p in find_merges(m)]
    owns = [annotate(m, p) for p in find_owns(m)]
    splits = [annotate(m, p) for p in find_splits(m)]
    sinits = find_ctor_splits(m)
    ccs, style_of_cc, learn = find_cc(m)
    return m, merges, owns, splits, sinits, ccs, style_of_cc, learn


def git_show(rev, path="config/%s/splits.txt" % VER):
    return subprocess.run(["git", "-C", ROOT, "show", "%s:%s" % (rev, path)],
                          capture_output=True, text=True, check=True).stdout


def validate(m_cache=None):
    rows = []
    for c, kind, what in KNOWN_WINS:
        try:
            before = parse_splits(git_show(c + "^"))
            after = parse_splits(git_show(c))
        except subprocess.CalledProcessError:
            rows.append((c, kind, what, False, "(commit not in history; fetch --unshallow)"))
            continue
        aft = {(u["name"], tuple(sorted(u["ranges"].items()))) for u in after}
        changed = {u["name"] for u in before if (u["name"], tuple(sorted(u["ranges"].items()))) not in aft}
        res = run_audit(git_show(c + "^"))
        m, merges, owns, splits = res[0], res[1], res[2], res[3]
        hit, note = False, ""
        if kind == "merge":
            for p in merges:
                names = {m.units[u]["name"] for u in p["units"]}
                cov = names & changed
                if len(cov) >= 2:
                    hit = True
                    note += "%d/%d changed TUs in one group; " % (len(cov), len(changed))
        elif kind == "split":
            for p in splits:
                if m.units[p["unit"]]["name"] in changed:
                    hit = True
                    note += "%s at %s; " % (m.units[p["unit"]]["name"], h(p["at"]))
        else:
            for p in owns:
                if m.units[p["unit"]]["name"] in changed:
                    hit = True
                    note += "%s %s %X..%X; " % (m.units[p["unit"]]["name"], p["sec"], p["start"], p["end"])
        rows.append((c, kind, what, hit, note[:300]))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", nargs="?", default="report", choices=["report", "validate"])
    ap.add_argument("--splits", help="splits.txt to audit (default config/%s/splits.txt)" % VER)
    ap.add_argument("--rev", help="audit splits.txt from this git revision")
    ap.add_argument("--claims", help="file with claimed TU paths / unit-claim issue titles")
    ap.add_argument("--fetch-claims", action="store_true", help="fetch open unit-claim issues with gh api")
    ap.add_argument("--out", default=os.path.join(ROOT, "docs", "reports", "tu_boundary_audit.md"))
    ap.add_argument("--json", help="also write all proposals as JSON")
    ap.add_argument("--top", type=int, default=60)
    ap.add_argument("--no-validate", action="store_true", help="skip the past-wins check in the report")
    a = ap.parse_args()
    if a.cmd == "validate":
        for r in validate():
            print("%-8s %-6s %-5s %s  %s" % (r[0], r[1], "OK" if r[3] else "MISS", r[2], r[4]))
        return
    if a.rev:
        text = git_show(a.rev)
    else:
        text = open(a.splits or os.path.join(ROOT, "config", VER, "splits.txt"), encoding="utf-8").read()
    claims = load_claims(a.claims, a.fetch_claims)
    res = run_audit(text, claims, diffs=True)
    val = None if a.no_validate else validate()
    md = render(*res, validation=val, top=a.top)
    with open(a.out, "w", encoding="utf-8") as f:
        f.write(md + "\n")
    print("wrote %s" % a.out)
    if a.json:
        m = res[0]
        def conv(p):
            q = dict(p)
            for k in ("units",):
                if k in q:
                    q[k] = [m.units[u]["name"] for u in q[k]]
            if "unit" in q:
                q["unit"] = m.units[q["unit"]]["name"]
            q["nonmatch"] = [m.objs[f]["name"] for _, f, _ in p.get("nonmatch", [])]
            q["matching_units"] = [m.units[u]["name"] for u in p.get("matching_units", [])]
            q["claimed"] = [m.units[u]["name"] for u, _ in p.get("claimed", [])]
            q.pop("detail", None)
            if "evidence" in q:
                q["evidence"] = [m.objs[x]["name"] for x in q["evidence"]]
            if "objs" in q:
                q["objs"] = [m.objs[x]["name"] for x in q["objs"]]
            for k in ("fns", "changes"):
                if k in q:
                    q[k] = [m.objs[x]["name"] for x in q[k]]
            if "at" in q:
                q["at"] = m.objs[q["at"]]["name"]
            return q
        allp = {"merge": res[1], "own": res[2], "split": res[3], "sinit": res[4], "cc": res[5]}
        json.dump({k: [conv(p) for p in v] for k, v in allp.items()}, open(a.json, "w"), indent=1)


if __name__ == "__main__":
    main()
