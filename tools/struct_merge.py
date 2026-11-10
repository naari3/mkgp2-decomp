#!/usr/bin/env python3
"""Merge the per-TU partial views of ONE real type into one full definition.

Most duplicated struct names that are left after tools/struct_dedup.py are
views: each TU declares only the members it touches and pads the rest, and
every TU invented its own member names.  For a name a human has judged to be
one real type this tool

  * lays every copy out, keeps each member a file really accesses (or that
    has a descriptive name) and drops unaccessed padding;
  * merges the members by offset into one definition (most specific pointer
    type, most used descriptive name; gaps become `pad_XXX`);
  * writes include/game/types/<Name>.h, replaces each copy by the #include
    and renames the member accesses in that file;
  * builds, and puts back every file whose object changed or that no longer
    compiles (a file that used the old shared header gets the old definition
    back as a local copy), until every object is byte-identical.

    python3 tools/struct_merge.py show KartDriver      # merged layout, conflicts
    python3 tools/struct_merge.py run KartDriver PlayerData ...
    python3 tools/struct_merge.py run --rename Kart=KartDriver KartDriver

`run` needs a clean tree and an up-to-date build.  It leaves the result
uncommitted.  `--rename Old=New` first treats every definition called Old as
a copy of New (same real type under another name; the type name is replaced
in those files).  Notes: docs/notes/struct_dedup.md, "Merging views".
"""
import argparse
import json
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import struct_dedup as S  # noqa: E402

ROOT = S.ROOT
# member names that say nothing: a filler word, or a word plus an offset.
# (struct_dedup's GENERIC_RE also takes all-hex words such as `eff` or `fade`.)
GENERIC_RE = re.compile(
    r"^(_*|pad|unk|field|fld|gap|reserved|dummy|m|f|x|u|data|_?0x|w|b|byte|word|bytes|words|"
    r"u8|u16|u32|s8|s16|s32|f32|val|value|v|obj|ptr|p|flag|buf|count|handle|param|arg|argument)"
    r"_?(?=[0-9A-Fa-f]*[0-9])[0-9A-Fa-f]*$|^_*(pad|unk|gap|reserved|dummy)\w*$", re.I)


def norm_type(m):
    t = S.canon_type(" ".join(x for x in m.type.split() if x not in ("const", "volatile")))
    return S.KNOWN_TYPEDEF.get(t, t)


class Copy:
    """One definition of the type in one file (or the shared header as seen
    from a file that includes it)."""

    def __init__(self, sc, d, file, via_shared, oldname=None):
        self.d, self.file, self.via_shared = d, file, via_shared
        self.oldname = oldname          # set when the copy has another type name
        with open(os.path.join(ROOT, file), encoding="latin-1", newline="") as fh:
            self.raw = fh.read()
        s = S.strip_comments(self.raw, keep_strings=True)
        self.ok = len(s) == len(self.raw)
        if not via_shared:
            s = s[:d.start] + " " * (d.end - d.start) + s[d.end:]
        self.outside = s
        self.local = S._local_types(sc, file)
        self.offs = S.member_offsets(d, self.local)
        self.size = None
        if self.offs is not None:
            lo = S.layout(d, self.local)
            self.size = lo[0] if lo else None
        self.accessed = set()
        for m in d.members:
            if m.name and re.search(r"(\.|->)\s*%s\b" % re.escape(m.name), s):
                self.accessed.add(m.name)


def collect(sc, name, aliases=()):
    copies, notes = [], []
    shared = sc.shared_defs.get(name)
    for d in sc.defs:
        if d.name != name and d.name not in aliases:
            continue
        if not d.file.endswith((".c", ".cpp")):
            notes.append(f"{d.file}:{d.line}: copy in a header (left alone)")
            continue
        if d.members is None or d.kind != "struct" or any(m.name is None or m.bits is not None for m in d.members):
            notes.append(f"{d.file}:{d.line}: has methods, bitfields or nested types (left alone)")
            continue
        if sum(1 for x in sc.by_file[d.file] if x.name == d.name) > 1:
            notes.append(f"{d.file}:{d.line}: name defined twice in the file (left alone)")
            continue
        c = Copy(sc, d, d.file, False, d.name if d.name != name else None)
        if c.offs is None or not c.ok:
            notes.append(f"{d.file}:{d.line}: layout not computable (left alone)")
            continue
        copies.append(c)
    for sn in [name] + list(aliases):
        shared = sc.shared_defs.get(sn)
        if shared is None or shared.members is None:
            continue
        inc = f"{S.TYPES_INC}/{sn}.h"
        have = {c.file for c in copies}
        for hn in sorted(os.listdir(os.path.join(ROOT, S.TYPES_DIR))):
            if hn != sn + ".h" and hn.endswith(".h"):
                with open(os.path.join(ROOT, S.TYPES_DIR, hn), encoding="latin-1") as fh:
                    if f'"{inc}"' in fh.read():
                        notes.append(f"INDIRECT {S.TYPES_DIR}/{hn}: includes the shared definition of {sn}")
        for f in sc.files:
            if f in have or f == "include/" + inc:
                continue
            if inc in sc.includes(f):
                if not f.endswith((".c", ".cpp")):
                    notes.append(f"INDIRECT {f}: header that includes the shared definition of {sn}")
                    continue
                c = Copy(sc, shared, f, True, sn if sn != name else None)
                c.shared_name = sn
                if not re.search(r'#[ \t]*include[ \t]*"%s"' % re.escape(inc), c.raw):
                    notes.append(f"INDIRECT {f}: takes {sn} through another header")
                if c.offs is not None and c.ok:
                    copies.append(c)
    return copies, notes


HINTS_PATH = os.path.join(ROOT, "tools", "struct_merge_hints.json")


def load_hints():
    if os.path.exists(HINTS_PATH):
        with open(HINTS_PATH) as fh:
            return json.load(fh)
    return {}


def subpaths(sc, f, types=None):
    """(offset, size) -> access path for the parts of a composite member:
    array elements, array prefixes, members of an embedded shared struct."""
    t, ptr, dims, raw = f.type
    out = {}
    if raw:
        return out
    base = t.replace("struct ", "")
    inner = None
    if ptr:
        es = 4
    elif base in S.PRIM_SIZE:
        es = S.PRIM_SIZE[base]
    else:
        types = types or sc.shared_defs
        sd = types.get(base)
        if sd is None or sd.members is None:
            return out
        inner = S.member_offsets(sd, dict(types))
        lo = S.layout(sd, dict(types))
        if inner is None or lo is None:
            return out
        es = lo[0]
    n = 1
    for dmn in dims:
        n *= S.const_eval(dmn) or 1
    if len(dims) > 1:
        return out
    for i in range(n):
        idx = f"[{i}]" if dims else ""
        if dims:
            out[(f.off + i * es, es)] = f.name + idx
            if 0 < i < n:
                out.setdefault((f.off, i * es), f.name)
        for m, mo, msz in (inner or []):
            out.setdefault((f.off + i * es + mo, msz), f"{f.name}{idx}.{m.name}")
    return out


class Field:
    def __init__(self, off, size):
        self.off, self.size = off, size
        self.cands = []     # (copy, member)
        self.name = None
        self.type = None    # (type, ptr, dims, raw-if-fnptr)
        self.losers = []


def spelled(m):
    t = norm_type(m)
    if m.ptr and "const" in m.type.split():
        t = "const " + t        # pointer to const: part of the type
    return (t, m.ptr, tuple(m.dims), m.raw if m.fnptr else None)


def merge(sc, name, copies, hint=None):
    hint = hint or {}
    fields = {}
    for c in copies:
        for m, off, size in c.offs:
            acc = m.name in c.accessed
            if not acc and GENERIC_RE.match(m.name):
                continue
            fields.setdefault((off, size), Field(off, size)).cands.append((c, m))
    # resolve overlaps: the extent more files access wins
    def weight(f):
        return (sum(1 for c, m in f.cands if m.name in c.accessed), len(f.cands), -f.size)
    accepted, conflicts = [], []
    for f in sorted(fields.values(), key=weight, reverse=True):
        clash = [a for a in accepted if a.off < f.off + f.size and f.off < a.off + a.size]
        if clash:
            conflicts.append((f, clash))
        else:
            accepted.append(f)
    forced = {}
    for off, decl in (hint.get("fields") or {}).items():
        toks = S.TOKEN_RE.findall(decl)
        ms = S.parse_member(toks)
        d = S.Def()
        d.kind, d.name, d.members = "struct", "_hint", ms
        (m, _, size), = S.member_offsets(d, dict(sc.shared_defs))
        f = fields.get((int(off, 16), size)) or Field(int(off, 16), size)
        f.forced = m
        forced[(f.off, f.size)] = f
        accepted = [a for a in accepted if not (a.off < f.off + f.size and f.off < a.off + a.size)]
        accepted.append(f)
    accepted.sort(key=lambda f: f.off)
    used = set()
    names = {int(k, 16): v for k, v in (hint.get("names") or {}).items()}
    for f in accepted:
        if getattr(f, "forced", None) is not None:
            f.type, f.name = spelled(f.forced), f.forced.name
            used.add(f.name)
            continue
        votes = Counter()
        for c, m in f.cands:
            sp = spelled(m)
            w = 3 if m.name in c.accessed else 1
            base = sp[0].replace("struct ", "").replace("const ", "")
            if sp[1] and base == "void":
                w -= 0.5            # any typed pointer beats void *
            if not sp[1] and base not in S.PRIM_SIZE and base not in sc.shared:
                continue            # embedded struct that is not shared
            votes[sp] += w
        if not votes:
            f.type = ("unsigned char", 0, (str(f.size),), None)
            f.unresolved = True
        else:
            best = max(votes.items(), key=lambda kv: (kv[1], kv[0][0] != "void"))[0]
            # void * loses to a typed pointer even when outvoted
            typed = [k for k in votes if k[1] and k[0].replace("struct ", "").replace("const ", "") != "void" and not k[3]]
            if best[1] and best[0].replace("struct ", "").replace("const ", "") == "void" and typed:
                best = max(typed, key=lambda k: votes[k])
            f.type = best
        nvotes = Counter()
        for c, m in f.cands:
            if not GENERIC_RE.match(m.name):
                nvotes[m.name] += 3 if m.name in c.accessed else 1
        f.nvotes = nvotes
        if f.off in names:
            nm = names[f.off]
        elif nvotes:
            nm = max(nvotes.items(), key=lambda kv: (kv[1], len(kv[0]), kv[0]))[0]
        else:
            # nobody named it: keep the placeholder most files already use
            gv = Counter(m.name for c, m in f.cands)
            nm = gv.most_common(1)[0][0] if gv else "unk_%03X" % f.off
        if nm in used:
            nm = "%s_%03X" % (nm, f.off)
        used.add(nm)
        f.name = nm
    # a composite view (array, embedded struct) replaces the scalars it tiles
    for f, clash in list(conflicts):
        if (f.off, f.size) in forced or any(a not in accepted for a in clash):
            continue
        f.type = None
        sps = [spelled(m) for c, m in f.cands if m.name in c.accessed] or [spelled(m) for c, m in f.cands]
        f.type = Counter(sps).most_common(1)[0][0]
        nv = Counter(m.name for c, m in f.cands if not GENERIC_RE.match(m.name))
        f.name = names.get(f.off) or (nv.most_common(1)[0][0] if nv else "unk_%03X" % f.off)
        f.nvotes = nv
        sp = subpaths(sc, f)
        if all((a.off, a.size) in sp for a in clash) and (f.name not in used or f.name in {a.name for a in clash}):
            accepted = [a for a in accepted if a not in clash] + [f]
            used.add(f.name)
            conflicts.remove((f, clash))
    accepted.sort(key=lambda f: f.off)
    size = max([c.size or 0 for c in copies] + [f.off + f.size for f in accepted])
    if hint.get("size"):
        size = int(hint["size"], 16)
    return accepted, conflicts, size


def header(sc, name, fields, size, copies):
    guard = "GAME_TYPES_" + re.sub(r"\W", "_", name).upper() + "_H"
    incs, fwd, body = [], [], []
    pos = 0

    def pad(to):
        nonlocal pos
        if to > pos:
            body.append(f"    /* 0x{pos:03X} */ unsigned char pad_{pos:03X}[0x{to - pos:X}];")
            pos = to
    for f in fields:
        pad(f.off)
        t, ptr, dims, raw = f.type
        cq = "const " if t.startswith("const ") else ""
        base = t.replace("const ", "").replace("struct ", "").replace("union ", "")
        if base not in S.PRIM_SIZE and base != "void" and not all(x in S.BUILTIN for x in base.split()):
            if base == name:
                t = cq + "struct " + name
            elif ptr and not raw:
                # a pointer needs only the tag: files with their own view of
                # the pointee keep compiling
                fwd.append(base)
                t = cq + "struct " + base
            elif base in sc.shared:
                incs.append(sc.shared[base])
        if raw:
            decl = S._fmt_decl(re.sub(r"\( \* \w+ \)", "( * %s )" % f.name, raw, count=1))
        else:
            decl = "*" * ptr + f.name + "".join(f"[{S._fmt_decl(x)}]" for x in dims)
        also = sorted(k for k in getattr(f, "nvotes", {}) if k != f.name)
        if not also and f.name in (getattr(f, "also_seen", None) or ()):
            also = []
        note = ""
        if also or getattr(f, "also_seen", None):
            names_ = sorted(set(also) | set(getattr(f, "also_seen", ()) or ()) - {f.name})
            if names_:
                note = "  /* also: " + ", ".join(names_) + " */"
        body.append(f"    /* 0x{f.off:03X} */ {t} {decl};{note}")
        pos = f.off + f.size
    pad(size)
    lines = [f"#ifndef {guard}", f"#define {guard}", ""]
    for i in sorted(set(incs)):
        lines.append(f'#include "{i}"')
    if incs:
        lines.append("")
    for t in sorted(set(fwd)):
        lines.append(f"struct {t};")
    if fwd:
        lines.append("")
    lines.append(f"/* Merged from {len(copies)} per-TU views by tools/struct_merge.py: members are")
    lines.append(" * the ones some TU accesses; the size is the largest any view declared. */")
    lines.append(f"typedef struct {name} {name};")
    lines.append(f"struct {name} {{")
    lines += body
    lines.append("};")
    lines += ["", f"#endif /* {guard} */", ""]
    return "\n".join(lines)


def plan(sc, name, aliases=()):
    hint = load_hints().get(name, {})
    aliases = list(aliases) + list(hint.get("aliases", []))
    if not hint.get("header") and os.path.exists(os.path.join(ROOT, S.TYPES_DIR, name + ".h")):
        sd = sc.shared_defs.get(name)
        if sd is None or sd.members is None or sd.kind != "struct":
            return None         # the shared definition is a class: not a plain view
    copies, notes = collect(sc, name, aliases)
    copies = [c for c in copies if c.file not in hint.get("exclude", [])]
    if not copies:
        return None
    types = dict(sc.shared_defs)
    inc = f"{S.TYPES_INC}/{name}.h"
    if hint.get("header"):
        # an existing header already has the full definition: views move onto it
        hp = hint["header"]
        inc = hp.replace("include/", "", 1)
        copies = [c for c in copies if c.file != hp]
        hdefs, _ = S.scan_file(hp)
        with open(os.path.join(ROOT, hp), encoding="latin-1") as fh:
            for tm in re.finditer(r"^\s*typedef\s+((?:unsigned|signed|char|short|int|long|float|double|\s)+?)\s+(\w+)\s*;", fh.read(), re.M):
                S.KNOWN_TYPEDEF.setdefault(tm.group(2), " ".join(tm.group(1).split()))
        for g in sc.closure_files(hp):
            for x in sc.by_file.get(g, []):
                if x.name and x.members is not None:
                    types.setdefault(x.name, x)
        for x in hdefs:
            if x.name and x.members is not None:
                types[x.name] = x
        md = [d for d in hdefs if d.name == name]
        offs = S.member_offsets(md[0], types)
        fields, conflicts = [], []
        for m, off, sz in offs:
            if GENERIC_RE.match(m.name):
                continue
            f = Field(off, sz)
            f.type, f.name = spelled(m), m.name
            fields.append(f)
        size = S.layout(md[0], types)[0]
        text = None
        chk = offs
    else:
        fields, conflicts, size = merge(sc, name, copies, hint)
        old = os.path.join(ROOT, S.TYPES_DIR, name + ".h")
        if os.path.exists(old):
            # alternative names an earlier merge recorded stay recorded
            with open(old, encoding="latin-1") as fh:
                seen = {int(a, 16): b.split(", ") for a, b in
                        re.findall(r"/\* 0x([0-9A-F]+) \*/[^\n]*/\* also: (.*?) \*/", fh.read())}
            for f in fields:
                f.also_seen = seen.get(f.off)
        text = header(sc, name, fields, size, copies)
        # self check: the header must lay out exactly as planned
        defs, _ = S.scan_file(f"{S.TYPES_DIR}/{name}.h", text)
        md = [d for d in defs if d.name == name]
        chk = None
        if md and md[0].members is not None:
            loc = dict(sc.shared_defs)
            loc[name] = md[0]
            chk = S.member_offsets(md[0], loc)
    by_off = {}
    if chk is None:
        notes.append("SELF CHECK: merged header layout not computable")
    else:
        got = {m.name: o for m, o, _ in chk}
        for f in fields:
            if got.get(f.name) != f.off:
                notes.append(f"SELF CHECK FAILED: {f.name} planned 0x{f.off:X} got {got.get(f.name)}")
                chk = None
                break
    paths = {}
    for f in fields:
        paths.update(subpaths(sc, f, types))
    for f in fields:
        if not getattr(f, "unresolved", False):
            paths[(f.off, f.size)] = f.name
    plans = []
    for c in copies:
        ren, bad = {}, None
        for m, off, sz in c.offs:
            if m.name not in c.accessed:
                continue
            tgt = paths.get((off, sz))
            if tgt is None:
                bad = f"accesses {m.name} at 0x{off:X}+{sz}, which overlaps another view's member"
                break
            if tgt != m.name:
                ren[m.name] = tgt
        if c.size and c.size != size and re.search(
                r"sizeof\s*\(\s*(struct\s+)?%s\s*\)|\b%s\s+\w+\s*(\[[^\]]*\])?\s*[;=]" % (
                    re.escape(c.d.name), re.escape(c.d.name)), c.outside):
            bad = bad or f"uses the size of its view (0x{c.size:X}, merged 0x{size:X})"
        plans.append((c, ren, bad))
    return dict(name=name, copies=copies, notes=notes, fields=fields, conflicts=conflicts,
                size=size, text=text, plans=plans, ok=chk is not None, inc=inc)


def cmd_show(args):
    sc = S.Scan()
    for name in args.names:
        p = plan(sc, name, [a for a, n in args.rename if n == name])
        if p is None:
            print(f"{name}: no mergeable copies")
            continue
        print(p["text"] or f"(definition stays in {p['inc']})")
        for f, clash in p["conflicts"]:
            who = ", ".join(sorted({f"{c.file} ({m.name})" for c, m in f.cands}))
            print(f"CONFLICT 0x{f.off:X}+{f.size}: {who} overlaps "
                  + ", ".join(f"{a.name} 0x{a.off:X}+{a.size}" for a in clash))
        for f in p["fields"]:
            types = {spelled(m)[:3] for c, m in f.cands}
            if len(types) > 1:
                print(f"TYPES 0x{f.off:X} {f.name}: " + " | ".join(
                    sorted({f"{t} {'*' * pt}{''.join('[%s]' % x for x in dm)}" for t, pt, dm in types})))
        for f in p["fields"]:
            nv = getattr(f, "nvotes", None)
            if nv and len(nv) > 1:
                print(f"NAMES 0x{f.off:X} -> {f.name}: " + ", ".join(f"{k} x{v}" for k, v in nv.most_common()))
        for c, ren, bad in p["plans"]:
            tag = "shared-user" if c.via_shared else "copy"
            print(f"{tag:11} {c.file}: " + (f"SKIP {bad}" if bad else
                  (", ".join(f"{a}->{b}" for a, b in ren.items()) or "no renames")))
        for n in p["notes"]:
            print("note:", n)


def rename_accesses(c, text, ren, name):
    """Rename `.old` / `->old`.  When another struct in reach also has a member
    called `old`, only accesses through variables declared with this type."""
    if not ren:
        return text
    others = set()
    for g in c.sc.closure_files(c.file):
        for x in c.sc.by_file.get(g, []) + ([c.sc.shared_defs[n] for n in c.sc.shared_defs
                                              if g == f"include/{S.TYPES_INC}/{n}.h"]):
            if x is not c.d and x.name != c.d.name:
                for m in (x.members or []):
                    if m.name:
                        others.add(m.name)
    plain = {a: b for a, b in ren.items() if a not in others}
    careful = {a: b for a, b in ren.items() if a in others}
    if plain:
        pat = re.compile(r"(\.|->)(\s*)(%s)\b" % "|".join(map(re.escape, plain)))
        text = pat.sub(lambda m: m.group(1) + m.group(2) + plain[m.group(3)], text)
    if careful:
        tn = re.escape(c.d.name)
        vars_ = set(re.findall(r"\b%s\b(?:\s|const|\*)*?[\s*]([A-Za-z_]\w*)\s*(?=[;,=)\[])" % tn, c.outside))
        vars_ -= {"const", "volatile"}
        alt = "|".join(map(re.escape, careful))
        if vars_:
            pat = re.compile(r"\b(%s)(\s*(?:->|\.)\s*)(%s)\b" % ("|".join(map(re.escape, sorted(vars_))), alt))
            text = pat.sub(lambda m: m.group(1) + m.group(2) + careful[m.group(3)], text)
        pat = re.compile(r"(\(\s*\(\s*(?:const\s+)?(?:struct\s+)?%s\s*\*\s*\)\s*(?:[^()]|\([^()]*\))*\)\s*->\s*)(%s)\b" % (tn, alt))
        text = pat.sub(lambda m: m.group(1) + careful[m.group(2)], text)
    return text


def apply(sc, p, dry=False):
    name = p["name"]
    inc = f'#include "{p["inc"]}"'
    touched = []
    for c, ren, bad in p["plans"]:
        if bad:
            continue
        c.sc = sc
        text = c.raw
        tail = text
        if not c.via_shared:
            d = c.d
            head = text[:d.start] + inc + S._pad_lines(text, d, 0)
            tail = text[d.end:]
            tail = rename_accesses(c, tail, ren, name)
            pre = rename_accesses(c, text[:d.start], ren, name)
            text = pre + inc + S._pad_lines(c.raw, d, 0) + tail
            if c.oldname:
                text = re.sub(r"\b%s\b" % re.escape(c.oldname), name, text)
        else:
            text = rename_accesses(c, text, ren, name)
            if c.oldname:
                line = re.compile(r'(#[ \t]*include[ \t]*)"%s/%s\.h"' % (re.escape(S.TYPES_INC), re.escape(c.oldname)))
                if not line.search(text):
                    continue        # reaches the alias header indirectly
                text = line.sub(lambda m: m.group(1) + '"%s"' % p["inc"], text, count=1)
                text = re.sub(r"\b%s\b" % re.escape(c.oldname), name, text)
            elif p["text"] is None and p["inc"] != f"{S.TYPES_INC}/{name}.h":
                line = re.compile(r'(#[ \t]*include[ \t]*)"%s/%s\.h"' % (re.escape(S.TYPES_INC), re.escape(name)))
                if not line.search(text):
                    continue
                text = line.sub(lambda m: m.group(1) + '"%s"' % p["inc"], text, count=1)
        touched.append((c, text))
    if dry:
        return touched
    if p["text"] is not None:
        hp = os.path.join(ROOT, S.TYPES_DIR, name + ".h")
        with open(hp, "w", newline="\n") as fh:
            fh.write(p["text"])
    for c, text in touched:
        with open(os.path.join(ROOT, c.file), "w", encoding="latin-1", newline="") as fh:
            fh.write(text)
    return touched


def old_header_body(name):
    r = subprocess.run(["git", "show", f"HEAD:{S.TYPES_DIR}/{name}.h"], cwd=ROOT, capture_output=True)
    if r.returncode:
        return None
    t = r.stdout.decode("latin-1")
    t = re.sub(r"^\s*#\s*(ifndef|define|endif)\b.*$", "", t, flags=re.M)
    return t.strip() + "\n"


def localize(f, names):
    """Put `f` back as committed; where it took a merged type from the shared
    header, give it the old shared definition as a local copy."""
    subprocess.run(["git", "checkout", "--", f], cwd=ROOT, check=True)
    with open(os.path.join(ROOT, f), encoding="latin-1", newline="") as fh:
        text = fh.read()
    ok = True
    for n in names:
        body = old_header_body(n)
        if body is None:
            continue
        line = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"%s/%s\.h"[ \t]*\r?$' % (re.escape(S.TYPES_INC), re.escape(n)), re.M)
        if line.search(text):
            eol = S.eol_of(text)
            text = line.sub(lambda m: body.replace("\n", eol).rstrip(), text, count=1)
        else:
            ok = False      # reaches the header through another header
    with open(os.path.join(ROOT, f), "w", encoding="latin-1", newline="") as fh:
        fh.write(text)
    return ok


def src_of(obj):
    base = obj.replace("build/GNLJ82/", "", 1)[:-2]
    for ext in (".c", ".cpp"):
        if os.path.exists(os.path.join(ROOT, base + ext)):
            return base + ext
    return None


def refresh(sc, files, name):
    gone = set(files)
    sc.defs = [d for d in sc.defs if d.file not in gone]
    for f in gone:
        defs, text = S.scan_file(f)
        sc.by_file[f] = defs
        sc.text[f] = text
        sc.defs.extend(defs)
    hp = f"{S.TYPES_DIR}/{name}.h"
    if os.path.exists(os.path.join(ROOT, hp)):
        sc.shared[name] = f"{S.TYPES_INC}/{name}.h"
        for d in S.scan_file(hp)[0]:
            if d.name:
                sc.shared_defs[d.name] = d
    sc.__dict__.pop("_inc_cache", None)


def cmd_run(args):
    if subprocess.run(["git", "status", "--porcelain", "--untracked-files=no"], cwd=ROOT,
                      capture_output=True, text=True).stdout.strip() and not args.dirty:
        sys.exit("run: tree not clean")
    if not args.no_baseline:
        if subprocess.run(["ninja"], cwd=ROOT, capture_output=True).returncode:
            sys.exit("run: baseline build failed")
        subprocess.run([sys.executable, "tools/struct_dedup.py", "hashes", "save"], cwd=ROOT, check=True)
    sc = S.Scan()
    claimed = S.open_claim_paths() if not args.include_claimed else set()
    merged, dropped = [], []
    localized = {}
    users = defaultdict(set)      # file -> merged names it now takes from a header
    shared_user = defaultdict(set)
    for name in args.names:
        p = plan(sc, name, [a for a, n in args.rename if n == name])
        if p is not None and any(n.startswith("INDIRECT") for n in p["notes"]):
            print(f"{name}: not merged, the shared header is included by other headers "
                  f"({sum(1 for n in p['notes'] if n.startswith('INDIRECT'))} files): by hand")
            continue
        if p is None or not p["ok"]:
            print(f"{name}: not merged" + ("" if p is None else " (" + "; ".join(p["notes"]) + ")"))
            continue
        p["plans"] = [(c, ren, bad or ("claimed" if c.file.replace("src/", "", 1) in claimed else None))
                      for c, ren, bad in p["plans"]]
        skipped_shared = [c.file for c, ren, bad in p["plans"] if bad and c.via_shared]
        touched = apply(sc, p)
        merged.append(name)
        for c, _ in touched:
            users[c.file].add(name)
            if c.via_shared:
                shared_user[c.file].add(c.shared_name)
        for f in skipped_shared:
            if not localize(f, [name]):
                print(f"  WARNING {f}: includes {name}.h indirectly and cannot take the merged type")
        print(f"{name}: {len(touched)} files on the merged definition, "
              f"{sum(1 for c, r, b in p['plans'] if b)} skipped, {len(p['conflicts'])} overlap conflicts")
        # later names must see the files as they are now
        refresh(sc, [c.file for c, _ in touched] + skipped_shared, name)
    # every user must rebuild even when ninja has no header dependency for it
    for f in users:
        os.utime(os.path.join(ROOT, f))
    for rnd in range(1, 12):
        r = subprocess.run(["ninja", "-k", "0"], cwd=ROOT, capture_output=True, text=True)
        with open(os.path.join(ROOT, "build", f"struct_merge_round{rnd}.log"), "w") as fh:
            fh.write(r.stdout)
        bad = set()
        errs = {}
        for m in re.finditer(r"^FAILED: (build/GNLJ82/src/\S+\.o)[^\n]*\n[^\n]*\n((?:(?!\[\d+/\d+\]|FAILED:).*\n){0,12})", r.stdout, re.M):
            bad.add(m.group(1))
            errs[m.group(1)] = " | ".join(x[1:].strip() for x in m.group(2).splitlines() if x.startswith("#   ") and "Error:" not in x)[:300]
        why = "compile error"
        if not bad:
            h = subprocess.run([sys.executable, "tools/struct_dedup.py", "hashes", "diff"], cwd=ROOT,
                               capture_output=True, text=True)
            bad = set(re.findall(r"^CHANGED (\S+)", h.stdout, re.M))
            why = "object changed"
            if r.returncode and not bad:
                print(r.stdout[-3000:])
                sys.exit("run: build failed with no object to blame")
            if not bad:
                print(h.stdout.strip().splitlines()[-1])
                print(f"run: clean after round {rnd}")
                break
        for o in sorted(bad):
            f = src_of(o)
            if f is None:
                sys.exit(f"run: no source for {o}")
            if f not in users:
                hit = [n for n in merged if f"{S.TYPES_INC}/{n}.h" in sc.includes(f)]
                if not hit and any(f"{S.TYPES_INC}/{n}.h" in sc.includes(f) for n in dropped):
                    os.utime(os.path.join(ROOT, f))
                    continue
                if not hit:
                    sys.exit(f"run: {f} failed but was not edited ({why}) and reaches no merged header")
                for n in hit:
                    print(f"  DROPPED {n}: {f} takes it through another header and no longer builds")
                    merged.remove(n)
                    dropped.append(n)
                    hp = os.path.join(S.TYPES_DIR, n + ".h")
                    if subprocess.run(["git", "ls-files", "--error-unmatch", hp], cwd=ROOT, capture_output=True).returncode:
                        os.remove(os.path.join(ROOT, hp))
                    else:
                        subprocess.run(["git", "checkout", "--", hp], cwd=ROOT, check=True)
                    for g in [g for g, ns in users.items() if n in ns]:
                        localize(g, [x for x in shared_user.get(g, ()) if x not in hit and x in merged])
                        users.pop(g)
                        os.utime(os.path.join(ROOT, g))
                os.utime(os.path.join(ROOT, f))
                continue
            ok = localize(f, shared_user.get(f, ()))
            if shared_user.get(f):
                localized[f] = set(shared_user[f])
            print(f"  put back {f} ({why})" + ("" if ok else "  WARNING: indirect include, fix by hand")
                  + (": " + errs.get(o, "") if why == "compile error" else ""))
            users.pop(f)
    else:
        sys.exit("run: did not converge")
    left = Counter()
    for f, ns in users.items():
        for n in ns:
            left[n] += 1
    for name in merged:
        hp = os.path.join(ROOT, S.TYPES_DIR, name + ".h")
        if load_hints().get(name, {}).get("header"):
            print(f"{name}: {left[name]} files moved onto the existing header")
            continue
        if not left[name] and os.path.exists(hp):
            if subprocess.run(["git", "ls-files", "--error-unmatch", hp], cwd=ROOT, capture_output=True).returncode:
                os.remove(hp)
            else:
                subprocess.run(["git", "checkout", "--", hp], cwd=ROOT)
                # files that got the old definition as a local copy take the header again
                for f, ns in localized.items():
                    if name in ns:
                        ns.discard(name)
                        localize(f, ns)
                print(f"{name}: no file kept the merged definition; header and its users restored (rebuild to confirm)")
        print(f"{name}: {left[name]} files use the merged definition")


def _build_bad():
    """Build; -> (objects that failed to compile, objects whose hash changed)."""
    r = subprocess.run(["ninja", "-k", "0"], cwd=ROOT, capture_output=True, text=True)
    failed = set(re.findall(r"^FAILED: (build/GNLJ82/src/\S+\.o)", r.stdout, re.M))
    h = subprocess.run([sys.executable, "tools/struct_dedup.py", "hashes", "diff"], cwd=ROOT,
                       capture_output=True, text=True)
    changed = set(re.findall(r"^CHANGED (\S+)", h.stdout, re.M))
    if r.returncode and not failed and not changed:
        print(r.stdout[-2000:])
        sys.exit("classes: build failed with no object to blame")
    return {src_of(o) for o in failed}, {src_of(o) for o in changed}


def cmd_classes(args):
    """C++ classes (methods, virtuals, bases) cannot be merged member by
    member.  Try each existing spelling of the class as THE definition in
    every other file that has a copy; keep the spelling the most files accept
    byte-identically, share it and leave the rest."""
    if subprocess.run(["git", "status", "--porcelain", "--untracked-files=no"], cwd=ROOT,
                      capture_output=True, text=True).stdout.strip() and not args.dirty:
        sys.exit("classes: tree not clean")
    if subprocess.run(["ninja"], cwd=ROOT, capture_output=True).returncode:
        sys.exit("classes: baseline build failed")
    subprocess.run([sys.executable, "tools/struct_dedup.py", "hashes", "save"], cwd=ROOT, check=True,
                   capture_output=True)
    claimed = S.open_claim_paths() if not args.include_claimed else set()
    total = 0
    sc = S.Scan()
    type_names = {d.name for d in sc.defs if d.name}
    for name in args.names:
        defs = [d for d in sc.defs if d.name == name and d.file.endswith((".c", ".cpp"))
                and sum(1 for x in sc.by_file[d.file] if x.name == name) == 1
                and "#" not in d.body and d.file.replace("src/", "", 1) not in claimed]
        raws = {}
        for d in defs:
            with open(os.path.join(ROOT, d.file), encoding="latin-1", newline="") as fh:
                raws[d.file] = fh.read()
        defs = [d for d in defs if len(raws[d.file]) == len(sc.text[d.file])]
        if not defs:
            print(f"{name}: no copies in source files")
            continue
        hp = os.path.join(ROOT, S.TYPES_DIR, name + ".h")
        cands = []      # (label, text of the definition, files that already have it)
        if os.path.exists(hp):
            hd = [d for d in S.scan_file(f"{S.TYPES_DIR}/{name}.h")[0] if d.name == name]
            if not hd:
                print(f"{name}: shared header has no definition of it")
                continue
            with open(hp, encoding="latin-1") as fh:
                ht = fh.read()
            cands.append(("shared header", ht[hd[0].start:hd[0].end], set()))
        else:
            groups = defaultdict(list)
            for d in defs:
                groups[S.ctx_key(d)].append(d)
            for k, v in sorted(groups.items(), key=lambda kv: (-len(kv[1]), -len(kv[1][0].raw)))[:args.variants]:
                d = v[0]
                cands.append((f"{d.file}:{d.line}", raws[d.file][d.start:d.end], {x.file for x in v}))
        best = None
        for label, text, own in cands:
            targets = [d for d in defs if d.file not in own]
            for d in targets:
                eol = S.eol_of(raws[d.file])
                new = raws[d.file][:d.start] + text.replace("\r\n", "\n").replace("\n", eol) + raws[d.file][d.end:]
                with open(os.path.join(ROOT, d.file), "w", encoding="latin-1", newline="") as fh:
                    fh.write(new)
            failed, changed = _build_bad()
            ok = [d for d in targets if d.file not in failed and d.file not in changed]
            for d in targets:
                with open(os.path.join(ROOT, d.file), "w", encoding="latin-1", newline="") as fh:
                    fh.write(raws[d.file])
            print(f"{name}: spelling of {label}: {len(ok)}/{len(targets)} other files accept it"
                  f" ({len(failed)} do not compile, {len(changed)} change)")
            if best is None or len(ok) + len(own) > best[0]:
                best = (len(ok) + len(own), label, text, own, ok)
            if len(ok) == len(targets):
                break
        n, label, text, own, ok = best
        if n < 2 and not os.path.exists(hp):
            _build_bad()
            print(f"{name}: no spelling is accepted by a second file; left alone")
            continue
        if not os.path.exists(hp):
            src = next(d for d in defs if d.file in own)
            with open(hp, "w", encoding="latin-1", newline="\n") as fh:
                fh.write(S.ctx_header_text(src, sc, type_names))
        inc = f'#include "{S.TYPES_INC}/{name}.h"'
        moved = [d for d in defs if d.file in own] + ok
        for d in moved:
            t = raws[d.file]
            with open(os.path.join(ROOT, d.file), "w", encoding="latin-1", newline="") as fh:
                fh.write(t[:d.start] + inc + S._pad_lines(t, d, 0) + t[d.end:])
        for rnd in range(4):
            failed, changed = _build_bad()
            bad = (failed | changed) & {d.file for d in moved}
            if (failed | changed) - bad:
                sys.exit(f"classes: unrelated objects changed: {sorted((failed | changed) - bad)[:5]}")
            if not bad:
                break
            for f in bad:
                with open(os.path.join(ROOT, f), "w", encoding="latin-1", newline="") as fh:
                    fh.write(raws[f])
            moved = [d for d in moved if d.file not in bad]
        if not moved and not subprocess.run(["git", "ls-files", "--error-unmatch", hp], cwd=ROOT,
                                            capture_output=True).returncode == 0:
            os.remove(hp)
        total += len(moved)
        print(f"{name}: {len(moved)} of {len(defs)} copies now take the shared definition ({label})", flush=True)
        refresh(sc, [d.file for d in moved], name)
    print(f"classes: {total} copies replaced")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for n in ("show", "run"):
        a = sub.add_parser(n)
        a.add_argument("names", nargs="+")
        a.add_argument("--rename", action="append", default=[], metavar="Old=New")
        if n == "run":
            a.add_argument("--dirty", action="store_true", help="allow uncommitted changes")
            a.add_argument("--no-baseline", action="store_true", help="hashes already saved")
            a.add_argument("--include-claimed", action="store_true")
    a = sub.add_parser("classes")
    a.add_argument("names", nargs="+")
    a.add_argument("--variants", type=int, default=6, help="spellings to try per class")
    a.add_argument("--dirty", action="store_true")
    a.add_argument("--include-claimed", action="store_true")
    args = ap.parse_args()
    args.rename = [tuple(x.split("=", 1)) for x in getattr(args, "rename", [])]
    {"show": cmd_show, "run": cmd_run, "classes": cmd_classes}[args.cmd](args)


if __name__ == "__main__":
    main()
