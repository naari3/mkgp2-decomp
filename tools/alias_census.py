#!/usr/bin/env python3
"""Find data that a unit owns under one name while other units use another.

symbols.txt gives every object an address-derived or chosen name. A unit's C
source may define the object at that address under a different name (often a
`static`), or define one large object that covers several named addresses.
With MWCC that still links when the owning unit is NonMatching (the target
object is linked, and it carries the symbols.txt names) or when the user is
(its object is never linked). On another compiler every unit is compiled from
C, so the name the users refer to has no definition: the PC port sees two
different objects where the game has one.

This tool lists, from the compiled objects (build/GNLJ82/src) and
config/GNLJ82/{symbols,splits}.txt:

    name used by other units | unit that owns the address | what the owner's
    C defines there (symbol, offset into it, binding)

    python3 tools/alias_census.py              # summary by class
    python3 tools/alias_census.py --list       # every pair
    python3 tools/alias_census.py --unit game/Foo.c
    python3 tools/alias_census.py --tsv out.tsv

Classes:
  static     owner defines a local (static) object exactly at that address
  postbuild  owner defines the object under a source name that
             tools/postprocess_extab_user.py renames to the shared name after
             compiling (tools/extab_user_renames.json); MWCC links, a
             compiler without that step has no definition
  unnamed    the same, but the renamed symbol is compiler-generated (string
             literal pool, vtable, RTTI record): the source has no object to
             put the name on
  renamed    owner defines a global object at that address under another name
  inside     the address lies inside a larger object of the owner
  undefined  the owner's compiled object has nothing there (e.g. .bss that no
             C file defines, or data the owner only has as asm)
  unowned    no unit's split range contains the address (only with --unowned)

Pairs the owner already defines once for other compilers, with the SHARED_*
storage classes of include/game/types/shared_data.h, are counted separately
and left out of the list.

Not seen by this tool: float literals that tools/postprocess_sdata2.py names
after compiling and another unit reads by that name, and code that reaches an object through another object's
name plus an offset (for example CardUnpackLegacy.cpp, which MWCC makes
address its messages from the start of the previous unit's .rodata).
"""
import argparse, collections, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VER = 'GNLJ82'
CFG = os.path.join(ROOT, 'config', VER)
SRC = os.path.join(ROOT, 'build', VER, 'src')


def read_elf(path):
    """-> (sections {index: name}, symbols [(name, shndx, value, size, bind, type)])"""
    d = open(path, 'rb').read()
    if d[:4] != b'\x7fELF':
        return {}, []
    shoff, = struct.unpack_from('>I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', d, 0x2E)
    secs = []
    for i in range(shnum):
        secs.append(struct.unpack_from('>IIIIIIIIII', d, shoff + i * shentsize))
    strtab = secs[shstrndx]

    def name_at(tab, off):
        s = tab[4] + off
        return d[s:d.index(b'\0', s)].decode('latin-1')
    names = {i: name_at(strtab, s[0]) for i, s in enumerate(secs)}
    syms = []
    for s in secs:
        if s[1] != 2:   # SHT_SYMTAB
            continue
        st = secs[s[6]]
        for k in range(s[5] // 16):
            n, value, size, info, other, shndx = struct.unpack_from('>IIIBBH', d, s[4] + k * 16)
            syms.append((name_at(st, n), shndx, value, size, info >> 4, info & 15))
    return names, syms


def load_symbols():
    out = {}
    for l in open(os.path.join(CFG, 'symbols.txt'), encoding='utf-8'):
        m = re.match(r'(\S+) = (\S+):0x([0-9A-Fa-f]+);(.*)', l)
        if m:
            sz = re.search(r'size:0x([0-9A-Fa-f]+)', m.group(4))
            out[m.group(1)] = (m.group(2), int(m.group(3), 16), int(sz.group(1), 16) if sz else 0,
                               'type:function' in m.group(4))
    return out


def load_splits():
    """-> [(start, end, section, unit)] sorted"""
    out = []
    unit = None
    for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8'):
        m = re.match(r'(\S+):\s*(?:comment:.*)?$', l)
        if m and not l.startswith(('\t', ' ')):
            unit = m.group(1)
            continue
        m = re.match(r'\s+(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', l)
        if m and unit and unit != 'Sections':
            out.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1), unit))
    out.sort()
    return out


def obj_path(unit):
    return os.path.join(SRC, os.path.splitext(unit)[0] + '.o')


def load_postbuild():
    """-> {unit: {name after the build: source name}} from the rename table"""
    import json
    out = collections.defaultdict(dict)
    path = os.path.join(ROOT, 'tools', 'extab_user_renames.json')
    # the file has duplicate keys; keep every pair
    for tu, m in json.load(open(path, encoding='utf-8'), object_pairs_hook=lambda p: p):
        if not isinstance(m, list):
            continue
        for k, v in m:
            if isinstance(v, str) and not v.startswith(('@', 'extern:', 'active:')):
                # a "global:" rename of a name to itself still turns a static into a global
                out[tu[4:] if tu.startswith('src/') else tu][v.split(':', 1)[-1]] = k + ('\0' if v.startswith('global:') else '')
    return out


_text_cache = {}


def unit_text(unit):
    """source of a unit plus the project files it includes directly"""
    if unit not in _text_cache:
        path = os.path.join(ROOT, 'src', unit)
        text = open(path, encoding='latin-1').read() if os.path.isfile(path) else ''
        for inc in re.findall(r'#include [<"]([^">]+)[">]', text):
            for c in (os.path.join(ROOT, 'include', inc), os.path.join(ROOT, inc),
                      os.path.join(os.path.dirname(path), inc)):
                if os.path.isfile(c) and '/types/' not in c:
                    text += open(c, encoding='latin-1').read()
                    break
        _text_cache[unit] = text
    return _text_cache[unit]


def is_shared(unit, name, src):
    """the owner already gives other compilers one external definition
    (include/game/types/shared_data.h)"""
    text = unit_text(unit)
    for n in {name, src}:
        if n and re.match(r'\w+$', n) and re.search(
                r'(SHARED_(STATIC|BSS|EXTERN)\b[^;=(]*\b%s\b|#define\s+\w+\s+%s\b|#define\s+%s\b)' % (n, n, n), text):
            return True
    return False


def census():
    symbols = load_symbols()
    splits = load_splits()
    starts = [s[0] for s in splits]
    import bisect

    def owner(addr):
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0 and splits[i][0] <= addr < splits[i][1]:
            return splits[i]
        return None

    units = sorted({s[3] for s in splits})
    defined = set()                              # global definitions over all compiled objects
    users = collections.defaultdict(set)         # undefined name -> units
    objs = {}
    for u in units:
        p = obj_path(u)
        if not os.path.isfile(p):
            continue
        names, syms = read_elf(p)
        objs[u] = (names, syms)
        for n, shndx, value, size, bind, typ in syms:
            if not n:
                continue
            if shndx == 0:
                users[n].add(u)
            elif bind in (1, 2) and shndx < 0xFF00:
                defined.add(n)
    rows = []
    post = load_postbuild()
    seen = set()
    for ounit in sorted(post):
        for n, src in sorted(post[ounit].items()):
            made_global = src.endswith('\0')
            src = src.rstrip('\0')
            us = sorted(users.get(n, set()))
            if n in symbols and not symbols[n][3] and us and not n.startswith('@') and (src != n or made_global) \
                    and not re.search(r'_p\d+$', src):   # per-unit copies of one object, a separate matter
                kind = 'postbuild' if re.match(r'[A-Za-z_]\w*$', src) and not src.startswith(('__vt__', '__RTTI__')) else 'unnamed'
                rows.append((n, symbols[n][1], symbols[n][0], ounit, kind, src, 0, us))
                seen.add(n)
    for n in sorted(users):
        if n in defined or n not in symbols:
            continue
        sec, addr, size, is_fn = symbols[n]
        if is_fn or sec in ('.text', '.init', 'extab', 'extabindex'):
            continue
        own = owner(addr)
        if not own:
            rows.append((n, addr, sec, '', 'unowned', '', 0, sorted(users[n])))
            continue
        start, end, osec, ounit = own
        hit = None
        if ounit in objs:
            names, syms = objs[ounit]
            off = addr - start
            best = None
            for sn, shndx, value, ssize, bind, typ in syms:
                if not sn or shndx == 0 or shndx >= 0xFF00 or typ in (3, 4) or names.get(shndx) != osec:
                    continue
                if sn.startswith(('@', '...')) and ssize == 0:
                    continue
                if value == off:
                    k = ('static' if bind == 0 else 'renamed', sn, 0)
                    if best is None or best[0] == 'inside' or (best[1].startswith('@') and not sn.startswith('@')):
                        best = k
                elif value < off < value + ssize and best is None:
                    best = ('inside', sn, off - value)
            hit = best
        if hit:
            rows.append((n, addr, sec, ounit, hit[0], hit[1], hit[2], sorted(users[n])))
        else:
            rows.append((n, addr, sec, ounit, 'undefined', '', 0, sorted(users[n])))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--list', action='store_true')
    ap.add_argument('--unit', help='only names owned by this unit')
    ap.add_argument('--tsv')
    ap.add_argument('--unnamed', action='store_true', help='also list compiler-generated objects (vtables, RTTI, literal pools)')
    ap.add_argument('--unowned', action='store_true', help='also list names whose address no unit owns (linker and SDK symbols)')
    args = ap.parse_args()
    rows = census()
    done = [r for r in rows if r[3] and is_shared(r[3], r[0], r[5])]
    rows = [r for r in rows if r not in done]
    if not args.unowned:
        rows = [r for r in rows if r[4] != 'unowned']
    unnamed = [r for r in rows if r[4] == 'unnamed']
    if not args.unnamed:
        rows = [r for r in rows if r[4] != 'unnamed']
    if args.unit:
        rows = [r for r in rows if r[3] == args.unit]
    cls = collections.Counter(r[4] for r in rows)
    print('pairs already shared through SHARED_* definitions: %d' % len(done))
    print('compiler-generated objects named after the build (--unnamed): %d' % len(unnamed))
    print('names used by a unit that the owner defines under another name: %d' % len(rows))
    for k in ('static', 'postbuild', 'renamed', 'inside', 'undefined', 'unowned'):
        print('  %-10s %d' % (k, cls.get(k, 0)))
    if args.list or args.unit:
        for n, addr, sec, ounit, k, sn, off, us in rows:
            print('%-44s %-7s %-9s %-40s %s%s  <- %s' % (n, sec, k, ounit, sn, ('+0x%X' % off) if off else '', ', '.join(us[:3]) + (' ...' if len(us) > 3 else '')))
    if args.tsv:
        with open(args.tsv, 'w') as f:
            f.write('name\taddress\tsection\towner\tclass\towner_symbol\toffset\tusers\n')
            for n, addr, sec, ounit, k, sn, off, us in rows:
                f.write('%s\t0x%08X\t%s\t%s\t%s\t%s\t0x%X\t%s\n' % (n, addr, sec, ounit, k, sn, off, ','.join(us)))


if __name__ == '__main__':
    main()
