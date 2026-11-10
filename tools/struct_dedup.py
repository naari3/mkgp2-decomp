#!/usr/bin/env python3
"""Find struct/union types that are redefined per translation unit and move
identical ones into one shared header.

    python3 tools/struct_dedup.py scan            # census -> docs/reports/struct_dedup.md
    python3 tools/struct_dedup.py groups Vec3     # every definition of one name
    python3 tools/struct_dedup.py apply --max-groups 20 [--name Vec3] [--dry]
    python3 tools/struct_dedup.py hashes save|diff   # object code before/after

What "identical" means here (class A, the only class `apply` touches):
same type name, same kind, and the same member list after normalising white
space, comments and `float x, y, z;` into one declarator per member.  Member
types must be C built-ins, pointers, or types that every member TU already
takes from the same shared header (so the tool can be rerun to a fixpoint:
leaf types first, then the structs that contain them).

Classes that are only reported:
  B  same name, same byte layout, different member names/padding spelling
  C  same byte layout under different names (candidates, need a human)

`apply` writes include/game/types/<Name>.h and replaces each definition in
place with `#include "game/types/<Name>.h"`.  A struct definition emits no
code, so every object must stay byte-identical: check with `hashes save`
before and `hashes diff` after a full `ninja`.  Details: docs/notes/struct_dedup.md
"""
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCAN_DIRS = ["src/game", "src/ui", "src/sound", "src/util", "src/resource", "include/game"]
TYPES_DIR = "include/game/types"
TYPES_INC = "game/types"

BUILTIN = {
    "void", "char", "short", "int", "long", "float", "double", "signed",
    "unsigned", "const", "volatile", "struct", "union", "enum", "bool",
}
PRIM_SIZE = {
    "char": 1, "signed char": 1, "unsigned char": 1, "bool": 1,
    "short": 2, "unsigned short": 2, "signed short": 2, "short int": 2,
    "unsigned short int": 2,
    "int": 4, "unsigned int": 4, "signed int": 4, "unsigned": 4, "signed": 4,
    "long": 4, "unsigned long": 4, "signed long": 4, "long int": 4,
    "unsigned long int": 4,
    "float": 4, "double": 8, "long long": 8, "unsigned long long": 8,
    "signed long long": 8,
}
# typedef names that mean the same thing in every header of this repo
KNOWN_TYPEDEF = {
    "u8": "unsigned char", "s8": "signed char", "u16": "unsigned short",
    "s16": "short", "u32": "unsigned long", "s32": "long", "f32": "float",
    "f64": "double", "u64": "unsigned long long", "s64": "long long",
    "BOOL": "int", "uint": "unsigned int", "ushort": "unsigned short",
    "uchar": "unsigned char", "undefined": "unsigned char",
    "undefined1": "unsigned char", "undefined2": "unsigned short",
    "undefined4": "unsigned int", "byte": "unsigned char",
}

TOKEN_RE = re.compile(r"[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+[uUlL]*|\d+[uUlL]*|::|->|<<|>>|\S")


def strip_comments(text):
    """Replace comments and string/char literals by spaces, keeping offsets."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                out[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(out)


DEF_RE = re.compile(
    r"\b(?:(typedef)\s+)?(struct|union|class)\b\s*([A-Za-z_]\w*)?\s*(:[^{;()]*)?\{"
)


def match_brace(s, i):
    depth = 0
    n = len(s)
    while i < n:
        c = s[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def depth_map(s):
    """Brace depth before every '{' of the file, ignoring `extern "C" {`."""
    # string literals are blanked, so `extern "C" {` looks like `extern " " {`
    depth = 0
    stack = []
    res = {}
    for m in re.finditer(r'extern\s*"\s*"\s*\{|[{}]', s):
        t = m.group(0)
        if t == "}":
            if stack:
                depth -= stack.pop()
        else:
            pos = m.end() - 1
            res[pos] = depth
            inc = 0 if t.startswith("extern") else 1
            stack.append(inc)
            depth += inc
    return res


def split_members(body):
    """Split a struct body into member strings at depth 0 ';'."""
    members, depth, cur = [], 0, []
    for tok in TOKEN_RE.findall(body):
        if tok in "{([":
            depth += 1
        elif tok in "})]":
            depth -= 1
        if tok == ";" and depth == 0:
            members.append(cur)
            cur = []
        else:
            cur.append(tok)
    if cur:
        members.append(cur)
    return members


def split_top(tokens, sep=","):
    parts, depth, cur = [], 0, []
    for t in tokens:
        if t in "{([":
            depth += 1
        elif t in "})]":
            depth -= 1
        if t == sep and depth == 0:
            parts.append(cur)
            cur = []
        else:
            cur.append(t)
    parts.append(cur)
    return parts


class Member:
    __slots__ = ("type", "decl", "name", "ptr", "dims", "bits", "fnptr", "raw")


def parse_member(tokens):
    """-> list of Member, or None when the member is not a plain data member."""
    if not tokens:
        return []
    if "{" in tokens or "#" in tokens or "operator" in tokens:
        return None
    if tokens[0] in ("public", "private", "protected", "virtual", "static",
                     "friend", "typedef", "enum", "inline", "template"):
        return None
    # type specifier = leading identifiers up to the first declarator token
    i = 0
    spec = []
    n = len(tokens)
    while i < n and re.match(r"[A-Za-z_]", tokens[i]):
        spec.append(tokens[i])
        i += 1
    if not spec:
        return None
    rest = tokens[i:]
    out = []
    if rest and rest[0] in ("*", "(", ",", "[", ":") or not rest:
        # the last identifier of spec is the first declarator's name unless
        # the declarator starts with '*' or '('
        if not rest or rest[0] in (",", "[", ":"):
            if len(spec) < 2:
                return None
            rest = [spec.pop()] + rest
    else:
        return None
    if spec[-1] in ("struct", "union", "enum", "const", "volatile", "unsigned", "signed") and \
            spec[-1] in ("struct", "union", "enum"):
        return None
    for d in split_top(rest):
        m = Member()
        m.type = " ".join(spec)
        m.raw = " ".join(d)
        m.fnptr = "(" in d
        m.bits = None
        m.dims = []
        m.ptr = 0
        m.name = None
        if m.fnptr:
            # `(*name)(args)` only
            mm = re.match(r"^(\* )*\( \* (\w+) \) \(.*\)$", m.raw)
            if not mm:
                return None
            m.name = mm.group(2)
            m.ptr = 1
        else:
            j = 0
            while j < len(d) and d[j] in ("*", "const", "volatile", "__restrict"):
                if d[j] == "*":
                    m.ptr += 1
                j += 1
            if j < len(d) and re.match(r"[A-Za-z_]", d[j]):
                m.name = d[j]
                j += 1
            elif not (j < len(d) and d[j] == ":"):
                return None
            while j < len(d) and d[j] == "[":
                k = d.index("]", j)
                m.dims.append(" ".join(d[j + 1:k]))
                j = k + 1
            if j < len(d) and d[j] == ":":
                m.bits = " ".join(d[j + 1:])
                j = len(d)
            if j != len(d):
                return None
        m.decl = m.raw
        out.append(m)
    return out


def const_eval(expr):
    expr = re.sub(r"(\d)[uUlL]+\b", r"\1", expr)
    if not re.fullmatch(r"[0-9A-Fa-fxX+\-*/() ]+", expr or ""):
        return None
    try:
        v = eval(expr.replace("/", "//"), {"__builtins__": {}})
    except Exception:
        return None
    return v if isinstance(v, int) and v >= 0 else None


class Def:
    """One struct/union definition found in a file."""

    def __init__(self):
        self.file = None
        self.start = self.end = 0       # span of the whole declaration incl ';'
        self.line = 0
        self.kind = None
        self.tag = None
        self.typedef = False
        self.names = []                 # typedef declarators, raw
        self.body = ""
        self.members = None             # list[Member] or None (not plain)
        self.skip = None                # reason this def is never auto-moved
        self.name = None
        self.cpp = False

    def key(self):
        return (self.kind, self.name,
                tuple((canon_type(m.type), m.decl) for m in self.members))

    def deps(self):
        """Type names the body needs that are not built in."""
        d = set()
        for m in self.members:
            for t in m.type.split():
                if t not in BUILTIN:
                    d.add(t)
            if m.fnptr:
                for t in re.findall(r"[A-Za-z_]\w*", m.raw.split(")", 1)[1]):
                    if t not in BUILTIN:
                        d.add(t)
        d.discard(self.name)
        if self.tag:
            d.discard(self.tag)
        return d


def canon_type(t):
    return " ".join(x for x in t.split())


def scan_file(path, text=None):
    if text is None:
        with open(os.path.join(ROOT, path), encoding="latin-1", newline="") as f:
            text = f.read()
    s = strip_comments(text)
    dm = depth_map(s)
    defs = []
    pos = 0
    while True:
        m = DEF_RE.search(s, pos)
        if not m:
            break
        ob = m.end() - 1
        cb = match_brace(s, ob)
        if cb < 0:
            break
        pos = cb + 1
        if dm.get(ob, 1) != 0:
            pos = ob + 1 if dm.get(ob, 1) == 0 else cb + 1
            continue
        # preceded by something on the same statement (static, extern, const, '=' ...)?
        k = m.start() - 1
        while k >= 0 and s[k] in " \t\r\n":
            k -= 1
        prev_ok = k < 0 or s[k] in ";}" or _is_pp_line_end(s, k)
        semi = s.find(";", cb)
        if semi < 0:
            break
        tail = s[cb + 1:semi].strip()
        d = Def()
        d.file = path
        d.start, d.end = m.start(), semi + 1
        d.line = s.count("\n", 0, m.start()) + 1
        d.kind = m.group(2)
        d.tag = m.group(3)
        d.typedef = bool(m.group(1))
        d.body = s[ob + 1:cb]
        d.cpp = path.endswith((".cpp", ".hpp"))
        pos = semi + 1
        if not prev_ok:
            d.skip = "has storage/qualifier prefix"
        elif m.group(4):
            d.skip = "has base class"
        elif d.kind == "class":
            d.skip = "class"
        elif "#" in d.body:
            d.skip = "preprocessor in body"
        elif "=" in tail or "(" in tail:
            d.skip = "variable definition"
        elif d.typedef:
            d.names = [x.strip() for x in tail.split(",") if x.strip()]
            plain = [x for x in d.names if re.fullmatch(r"\w+", x)]
            if len(plain) != 1:
                d.skip = "typedef without exactly one plain name"
            else:
                d.name = plain[0]
                if len(d.names) != 1:
                    d.skip = "typedef with extra declarators"
                elif d.tag and d.tag != d.name:
                    d.skip = "tag differs from typedef name"
        else:
            if tail:
                d.skip = "variable definition"
            elif not d.tag:
                d.skip = "anonymous"
            else:
                d.name = d.tag
        if d.name is None:
            d.name = d.tag or (d.names[0] if d.names else None)
        mem = []
        for toks in split_members(d.body):
            pm = parse_member(toks)
            if pm is None:
                mem = None
                break
            mem.extend(pm)
        d.members = mem
        if mem is None and not d.skip:
            d.skip = "non-plain member (method, nested type, access label)"
        if mem is not None and not mem and not d.skip:
            d.skip = "empty"
        defs.append(d)
    return defs, s


def _is_pp_line_end(s, k):
    ls = s.rfind("\n", 0, k) + 1
    return s[ls:k + 1].lstrip().startswith("#")


def list_files():
    out = subprocess.run(["git", "ls-files", "--"] + SCAN_DIRS, cwd=ROOT,
                         capture_output=True, text=True, check=True).stdout.split("\n")
    return [f for f in out if f.endswith((".c", ".cpp", ".h", ".hpp", ".inc"))
            and not f.startswith(TYPES_DIR + "/")]


def shared_types():
    """name -> header for every type already in include/game/types."""
    res = {}
    d = os.path.join(ROOT, TYPES_DIR)
    if os.path.isdir(d):
        for f in sorted(os.listdir(d)):
            if f.endswith(".h"):
                res[f[:-2]] = f"{TYPES_INC}/{f}"
    return res


INC_RE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*[<"]([^>"]+)[>"]', re.M)


def layout(d, local, depth=0):
    """-> (size, [(off, size, kind)]) or None.  `local` maps a type name to the
    Def visible in the same file."""
    off = 0
    items = []
    maxal = 1
    union = d.kind == "union"
    total = 0
    bit_left = 0
    for m in d.members:
        if m.bits is not None:
            return None
        t = canon_type(" ".join(x for x in m.type.split() if x not in ("const", "volatile")))
        t = KNOWN_TYPEDEF.get(t, t)
        sub = None
        if m.ptr:
            size, al, kind = 4, 4, "p"
        elif t in PRIM_SIZE:
            size = al = PRIM_SIZE[t]
            kind = "f" if t in ("float", "double") else ("b" if size == 1 else "i")
        else:
            name = t.replace("struct ", "").replace("union ", "")
            ld = local.get(name)
            if ld is None or ld is d or depth > 6 or ld.members is None:
                return None
            sub = layout(ld, local, depth + 1)
            if sub is None:
                return None
            size, al, kind = sub[0], sub[2], "s"
        count = 1
        for dim in m.dims:
            v = const_eval(dim)
            if v is None:
                return None
            count *= v
        if not union:
            off = (off + al - 1) // al * al
        o = 0 if union else off
        if kind == "s":
            for c in range(count):
                for (so, ss, sk) in sub[1]:
                    items.append((o + c * size + so, ss, sk))
        elif kind == "b":
            items.append((o, size * count, "b"))
        else:
            for c in range(count):
                items.append((o + c * size, size, kind))
        maxal = max(maxal, al)
        if union:
            total = max(total, size * count)
        else:
            off += size * count
    if not union:
        total = off
    total = (total + maxal - 1) // maxal * maxal
    # merge adjacent byte runs so pad spelling does not matter
    merged = []
    for it in sorted(items):
        if merged and it[2] == "b" and merged[-1][2] == "b" and merged[-1][0] + merged[-1][1] == it[0]:
            merged[-1] = (merged[-1][0], merged[-1][1] + it[1], "b")
        else:
            merged.append(it)
    return total, merged, maxal


class Scan:
    def __init__(self):
        self.files = list_files()
        self.defs = []
        self.by_file = {}
        self.text = {}
        self.shared = shared_types()
        self.shared_defs = {}
        for name, hdr in self.shared.items():
            for d in scan_file("include/" + hdr)[0]:
                if d.name:
                    self.shared_defs[d.name] = d
        for f in self.files:
            try:
                defs, s = scan_file(f)
            except Exception as e:  # keep going, report
                print(f"scan failed {f}: {e}", file=sys.stderr)
                continue
            self.by_file[f] = defs
            self.text[f] = s
            self.defs.extend(defs)

    def includes(self, f):
        """Every header `f` reaches through quoted/angle includes that resolve
        inside the repo (transitively), spelled as written in the #include."""
        cache = self.__dict__.setdefault("_inc_cache", {})
        if f in cache:
            return cache[f]
        seen, out, todo = {f}, set(), [f]
        while todo:
            cur = todo.pop()
            for spell in INC_RE.findall(self._text_of(cur)):
                out.add(spell)
                for base in (os.path.dirname(cur), "include", "src"):
                    cand = os.path.normpath(os.path.join(base, spell))
                    if os.path.isfile(os.path.join(ROOT, cand)):
                        if cand not in seen:
                            seen.add(cand)
                            todo.append(cand)
                        break
        cache[f] = out
        return out

    def _text_of(self, f):
        # self.text has string literals blanked, so read the file again
        extra = self.__dict__.setdefault("_extra", {})
        if f not in extra:
            try:
                with open(os.path.join(ROOT, f), encoding="latin-1") as fh:
                    t = fh.read()
            except OSError:
                t = ""
            extra[f] = re.sub(r"/\*.*?\*/|//[^\n]*", " ", t, flags=re.S)
        return extra[f]

    def movable(self, d):
        """None when `d` may be moved now, else the reason."""
        if d.skip:
            return d.skip
        s = self.text[d.file]
        # the name must not be declared elsewhere in the file (forward decl,
        # second definition under #if, ...)
        others = [x for x in self.by_file[d.file] if x is not d and x.name == d.name]
        if others:
            return "name defined twice in file"
        if re.search(r"\b(struct|union|class)\s+%s\s*;" % re.escape(d.name), s):
            return "forward declaration in file"
        if re.search(r"\btypedef\s+(struct|union)\s+\w+\s+\**%s\s*;" % re.escape(d.name), s):
            return "separate typedef in file"
        if d.tag is None and re.search(r"\b(struct|union)\s+%s\b" % re.escape(d.name),
                                       s[:d.start] + s[d.end:]):
            return "anonymous typedef but tag used"
        if d.tag is None and (not d.file.endswith(".c") or "cplusplus" in s
                              or d.file in cpp_by_flags()):
            # C++ mangles an unnamed struct differently from a named one
            return "anonymous typedef in C++ (name mangling)"
        inc = self.includes(d.file)
        for dep in d.deps():
            hdr = self.shared.get(dep)
            if hdr is None:
                return f"needs {dep} (not shared yet)"
            if hdr not in inc:
                return f"needs {dep} (file has its own)"
        return None


_CPP_FLAGS = None


def cpp_by_flags():
    """.c files that configure.py compiles as C++ (`-lang=c++` on the Object line)."""
    global _CPP_FLAGS
    if _CPP_FLAGS is None:
        _CPP_FLAGS = set()
        with open(os.path.join(ROOT, "configure.py")) as f:
            for line in f:
                if "c++" in line and "Object(" in line:
                    m = re.search(r'Object\(\s*\w+\s*,\s*"([^"]+)"', line)
                    if m:
                        _CPP_FLAGS.add("src/" + m.group(1))
    return _CPP_FLAGS


def cmd_scan(args):
    sc = Scan()
    by_name = defaultdict(list)
    for d in sc.defs:
        if d.name:
            by_name[d.name].append(d)
    nfiles = len({d.file for d in sc.defs})
    groups = build_groups(sc)
    lay_groups = defaultdict(list)
    nolayout = 0
    for f, defs in sc.by_file.items():
        local = dict(sc.shared_defs)
        local.update({x.name: x for x in defs if x.name})
        for d in defs:
            if d.members is None or not d.members:
                continue
            lo = layout(d, local)
            if lo is None:
                nolayout += 1
                continue
            d_lay = (d.kind, lo[0], tuple(lo[1]))
            lay_groups[d_lay].append(d)
    lines = []
    w = lines.append
    w("# Per-TU struct copies: census (tools/struct_dedup.py scan)")
    w("")
    w("Regenerate with `python3 tools/struct_dedup.py scan`. How the tool decides: docs/notes/struct_dedup.md.")
    w("")
    w("| Item | Count |")
    w("|---|---|")
    w(f"| Files scanned ({', '.join(SCAN_DIRS)}) | {len(sc.files)} |")
    w(f"| struct/union/class definitions at file scope | {len(sc.defs)} in {nfiles} files |")
    w(f"| Distinct type names | {len(by_name)} |")
    w(f"| Names defined in more than one file | {sum(1 for v in by_name.values() if len({d.file for d in v}) > 1)} |")
    w(f"| Types already in `{TYPES_DIR}` | {len(sc.shared)} |")
    multi = {k: v for k, v in groups.items() if len(v) > 1}
    w(f"| Class A groups (same name, same members, 2+ files) | {len(multi)} groups, {sum(len(v) for v in multi.values())} definitions |")
    ready = {k: [d for d in v if sc.movable(d) is None] for k, v in multi.items()}
    ready = {k: v for k, v in ready.items() if len(v) > 1}
    w(f"| ... of which movable right now | {len(ready)} groups, {sum(len(v) for v in ready.values())} definitions |")
    w(f"| Definitions whose byte layout the tool can compute | {sum(len(v) for v in lay_groups.values())} (not computable: {nolayout}) |")
    # class B: same name, same layout, different key
    b = defaultdict(set)
    for lk, v in lay_groups.items():
        for d in v:
            if d.name and not d.skip:
                b[(d.name, lk)].add(d.key())
    nb = {k: v for k, v in b.items() if len(v) > 1}
    w(f"| Class B (same name, same layout, different member spelling) | {len(nb)} name/layout pairs, {sum(len(v) for v in nb.values())} spellings |")
    c = {lk: v for lk, v in lay_groups.items()
         if len({d.name for d in v}) > 1 and lk[1] >= 16 and len(lk[2]) >= 3}
    w(f"| Class C (same layout of 16+ bytes and 3+ fields, different names) | {len(c)} layouts, {sum(len(v) for v in c.values())} definitions |")
    w("")
    w("## Why a definition is not movable yet")
    w("")
    reasons = defaultdict(int)
    for d in sc.defs:
        r = sc.movable(d) if d.members is not None or d.skip else d.skip
        if r:
            r = re.sub(r"needs \w+", "needs another type", r)
            reasons[r] += 1
    w("| Reason | Definitions |")
    w("|---|---|")
    for r, n in sorted(reasons.items(), key=lambda x: -x[1]):
        w(f"| {r} | {n} |")
    w("")
    w("## Most duplicated names")
    w("")
    w("| Name | Definitions | Distinct member lists | Largest identical group | Movable now |")
    w("|---|---|---|---|---|")
    top = sorted(by_name.items(), key=lambda x: -len(x[1]))[:60]
    for name, v in top:
        keys = defaultdict(list)
        for d in v:
            if d.members is not None and not d.skip:
                keys[d.key()].append(d)
        big = max((len(x) for x in keys.values()), default=0)
        mv = max((len([d for d in x if sc.movable(d) is None]) for x in keys.values()), default=0)
        w(f"| {name} | {len(v)} | {len(keys)} | {big} | {mv} |")
    w("")
    w("## Class C: largest same-layout sets with different names (candidates only)")
    w("")
    w("| Size | Fields | Definitions | Names |")
    w("|---|---|---|---|")
    for lk, v in sorted(c.items(), key=lambda x: -len(x[1]))[:40]:
        names = sorted({d.name or '(anon)' for d in v})
        w(f"| 0x{lk[1]:X} | {len(lk[2])} | {len(v)} | {', '.join(names[:8])}{' ...' if len(names) > 8 else ''} |")
    w("")
    out = os.path.join(ROOT, args.out)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w") as f:
        f.write("\n".join(lines))
    print("\n".join(lines[:22]))
    print(f"... written {args.out}")


def build_groups(sc):
    groups = defaultdict(list)
    for d in sc.defs:
        if d.skip or d.members is None or not d.name:
            continue
        groups[d.key()].append(d)
    return groups


def cmd_groups(args):
    sc = Scan()
    groups = defaultdict(list)
    for d in sc.defs:
        if d.name == args.name:
            k = d.key() if d.members is not None else ("?", d.body.strip()[:60])
            groups[k].append(d)
    for k, v in sorted(groups.items(), key=lambda x: -len(x[1])):
        d0 = v[0]
        print(f"== {len(v)} definitions: {d0.kind} {d0.name}")
        if d0.members is not None:
            for m in d0.members:
                print(f"     {m.type} {m.decl};")
        for d in v:
            print(f"   {d.file}:{d.line}  {sc.movable(d) or 'movable'}")


def header_text(d, shared):
    guard = "GAME_TYPES_" + re.sub(r"\W", "_", d.name).upper() + "_H"
    lines = [f"#ifndef {guard}", f"#define {guard}", ""]
    deps = sorted(d.deps())
    for dep in deps:
        lines.append(f'#include "{shared[dep]}"')
    if deps:
        lines.append("")
    lines.append(f"typedef {d.kind} {d.name} {{")
    for m in d.members:
        decl = m.decl.replace(" [ ", "[").replace(" ]", "]").replace("[ ", "[")
        decl = re.sub(r"\* (?=[\w*(])", "*", decl)
        decl = decl.replace("( *", "(*").replace(" )", ")").replace("( ", "(").replace(" ,", ",")
        decl = decl.replace(" : ", " : ")
        lines.append(f"    {m.type} {decl};")
    lines.append(f"}} {d.name};")
    lines += ["", f"#endif /* {guard} */", ""]
    return "\n".join(lines)


def open_claim_paths():
    """configure.py paths under an open unit-claim (needs GH access; best effort)."""
    p = os.path.join(ROOT, "build", "open_claims.txt")
    if os.path.exists(p):
        with open(p) as f:
            return {x.strip() for x in f if x.strip()}
    return set()


def cmd_apply(args):
    sc = Scan()
    groups = build_groups(sc)
    claimed = open_claim_paths()
    cands = []
    taken_names = set(sc.shared)
    for k, v in groups.items():
        name = k[1]
        if args.name and name not in args.name:
            continue
        if name in taken_names:
            continue
        mv = [d for d in v if sc.movable(d) is None]
        mv = [d for d in mv if d.file.replace("src/", "", 1) not in claimed]
        if len({d.file for d in mv}) < args.min_files:
            continue
        cands.append((len(mv), name, mv))
    # one group per name: the largest
    best = {}
    for n, name, mv in sorted(cands, key=lambda x: (-x[0], x[1])):
        best.setdefault(name, mv)
    order = sorted(best.items(), key=lambda x: (-len(x[1]), x[0]))
    if args.max_groups:
        order = order[:args.max_groups]
    edits = defaultdict(list)
    made = []
    for name, mv in order:
        hdr = f"{TYPES_DIR}/{name}.h"
        made.append((name, len(mv)))
        if not args.dry:
            os.makedirs(os.path.join(ROOT, TYPES_DIR), exist_ok=True)
            with open(os.path.join(ROOT, hdr), "w") as f:
                f.write(header_text(mv[0], sc.shared))
        for d in mv:
            edits[d.file].append(d)
    nrep = 0
    for f, ds in edits.items():
        with open(os.path.join(ROOT, f), encoding="latin-1", newline="") as fh:
            text = fh.read()
        if len(text) != len(sc.text[f]):
            print(f"skip {f}: length changed by decoding", file=sys.stderr)
            continue
        for d in sorted(ds, key=lambda x: -x.start):
            inc = f'#include "{TYPES_INC}/{d.name}.h"'
            # keep the line count of the file so __LINE__ users (asserts) do not move
            nl = text.count("\n", d.start, d.end)
            text = text[:d.start] + inc + _pad_lines(text, d, nl) + text[d.end:]
            nrep += 1
        if not args.dry:
            with open(os.path.join(ROOT, f), "w", encoding="latin-1", newline="") as fh:
                fh.write(text)
    for name, n in made:
        print(f"{name}: {n} definitions -> {TYPES_DIR}/{name}.h")
    print(f"{len(made)} types, {nrep} definitions replaced in {len(edits)} files"
          + (" (dry run)" if args.dry else ""))


def _pad_lines(text, d, nl):
    """What follows the #include: nothing, or a line break when more code
    follows the definition on its last line.  (Line numbers are not kept:
    nothing under the scanned directories uses __LINE__.)"""
    eol = text.find("\n", d.end)
    trailing = text[d.end:eol if eol >= 0 else len(text)].strip()
    return eol_of(text) if trailing else ""


def eol_of(text):
    return "\r\n" if "\r\n" in text else "\n"


def obj_files():
    base = os.path.join(ROOT, "build", "GNLJ82", "src")
    res = []
    for dp, _, fns in os.walk(base):
        for fn in fns:
            if fn.endswith(".o"):
                res.append(os.path.join(dp, fn))
    return sorted(res)


def cmd_hashes(args):
    p = os.path.join(ROOT, "build", "struct_dedup_hashes.json")
    cur = {}
    for f in obj_files():
        with open(f, "rb") as fh:
            cur[os.path.relpath(f, ROOT)] = hashlib.sha1(fh.read()).hexdigest()
    if args.mode == "save":
        with open(p, "w") as f:
            json.dump(cur, f)
        print(f"saved {len(cur)} object hashes")
        return
    with open(p) as f:
        old = json.load(f)
    changed = sorted(k for k in cur if k in old and old[k] != cur[k])
    missing = sorted(k for k in old if k not in cur)
    new = sorted(k for k in cur if k not in old)
    for k in changed:
        print("CHANGED", k)
    for k in missing:
        print("MISSING", k)
    print(f"{len(cur)} objects: {len(changed)} changed, {len(missing)} missing, {len(new)} new")
    if args.revert and changed:
        srcs = []
        for k in changed:
            base = k.replace("build/GNLJ82/", "", 1)[:-2]
            for ext in (".c", ".cpp"):
                if os.path.exists(os.path.join(ROOT, base + ext)):
                    srcs.append(base + ext)
        subprocess.run(["git", "checkout", "--"] + srcs, cwd=ROOT, check=True)
        print("reverted: " + " ".join(srcs) + "  (rerun ninja and `hashes diff`)")
    sys.exit(1 if changed or missing else 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("scan")
    p.add_argument("--out", default="docs/reports/struct_dedup.md")
    p.set_defaults(fn=cmd_scan)
    p = sub.add_parser("groups")
    p.add_argument("name")
    p.set_defaults(fn=cmd_groups)
    p = sub.add_parser("apply")
    p.add_argument("--name", action="append")
    p.add_argument("--max-groups", type=int, default=0)
    p.add_argument("--min-files", type=int, default=2)
    p.add_argument("--dry", action="store_true")
    p.set_defaults(fn=cmd_apply)
    p = sub.add_parser("hashes")
    p.add_argument("mode", choices=["save", "diff"])
    p.add_argument("--revert", action="store_true",
                   help="git checkout the sources of objects that changed")
    p.set_defaults(fn=cmd_hashes)
    args = ap.parse_args()
    args.fn(args)


if __name__ == "__main__":
    main()
