#!/usr/bin/env python3
"""Compile a C file with mwcc and compare each function against main.dol.

usage: cmp.py file.c [--cc GC/1.2.5n] [--preset runtime|dolphin|hsd|base] [-v] [extra mwcc flags...]
"""
import os, re, struct, subprocess, sys, argparse
from elftools.elf.elffile import ELFFile

ROOT = os.environ.get("MKROOT", "/home/claude/mkgp2-decomp")
OUT = os.environ.get("CMPOUT", "/home/claude/work/out")
os.makedirs(OUT, exist_ok=True)

BASE = ['-nodefaults', '-proc', 'gekko', '-align', 'powerpc', '-enum', 'int', '-fp', 'hardware',
        '-Cpp_exceptions', 'off', '-O4,p', '-inline', 'auto', '-pragma', 'cats off', '-pragma',
        'warn_notinlined off', '-maxerrors', '1', '-nosyspath', '-RTTI', 'off', '-fp_contract', 'on',
        '-str', 'reuse', '-multibyte', '-i', 'include', '-i', 'build/GNLJ82/include', '-DNDEBUG=1']
PRESETS = {
    'base': [],
    'runtime': ['-use_lmw_stmw', 'on', '-str', 'reuse,pool,readonly', '-common', 'off', '-char', 'signed',
                '-func_align', '4', '-inline', 'deferred,auto', '-DMSL_USE_INLINES=1'],
    'dolphin': ['-fp_contract', 'off', '-char', 'unsigned'],
    'hsd': [],
}


def load_dol():
    d = open(f"{ROOT}/orig/GNLJ82/sys/main.dol", "rb").read()
    offs = struct.unpack(">18I", d[0:72])
    addrs = struct.unpack(">18I", d[72:144])
    sizes = struct.unpack(">18I", d[144:216])
    return d, list(zip(offs, addrs, sizes))


DOL, SECS = load_dol()


def read_va(addr, size):
    for o, a, s in SECS:
        if a <= addr < a + s:
            return DOL[o + addr - a:o + addr - a + size]
    raise KeyError(hex(addr))


def load_symbols():
    m = {}
    for line in open(f"{ROOT}/config/GNLJ82/symbols.txt"):
        mm = re.match(r"(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)", line)
        if mm:
            m[mm.group(1)] = (int(mm.group(2), 16), int(mm.group(3), 16))
    return m


def target_asm(addr):
    """Return list of asm lines for function at addr from dtk asm dir."""
    out = []
    import glob
    for f in glob.glob(f"{ROOT}/build/GNLJ82/asm/**/*.s", recursive=True):
        pass
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--cc", default="GC/1.2.5n")
    ap.add_argument("--preset", default="dolphin")
    ap.add_argument("-v", action="store_true")
    ap.add_argument("--map", action="append", default=[], help="name=0xaddr")
    ap.add_argument("--only", default=None)
    args, extra = ap.parse_known_args()
    src = os.path.abspath(args.src)
    obj = os.path.join(OUT, os.path.basename(src).rsplit(".", 1)[0] + ".o")
    cmd = [f"{ROOT}/build/tools/wibo", f"{ROOT}/build/compilers/{args.cc}/mwcceppc.exe", *BASE,
           *PRESETS[args.preset], *extra, "-c", src, "-o", obj]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout, r.stderr)
        sys.exit(1)
    syms = load_symbols()
    for kv in args.map:
        k, v = kv.split("=")
        syms[k] = (int(v, 16), None)
    elf = ELFFile(open(obj, "rb"))
    symtab = elf.get_section_by_name(".symtab")
    secs = list(elf.iter_sections())
    relocs = {}
    for s in secs:
        if s.header.sh_type == "SHT_RELA":
            tgt = secs[s.header.sh_info]
            st = elf.get_section(s.header.sh_link)
            for rel in s.iter_relocations():
                relocs.setdefault(tgt.name if True else None, {})
                rs = st.get_symbol(rel["r_info_sym"])
                relocs.setdefault(s.header.sh_info, {})[rel["r_offset"]] = (rel["r_info_type"], rs.name)
    total = ok = 0
    for sym in symtab.iter_symbols():
        if sym["st_info"]["type"] != "STT_FUNC":
            continue
        name = sym.name
        if args.only and name != args.only:
            continue
        shndx = sym["st_shndx"]
        sec = elf.get_section(shndx)
        data = sec.data()[sym["st_value"]:sym["st_value"] + sym["st_size"]]
        total += 1
        if name not in syms:
            print(f"  ?? {name}: not in symbols.txt (size {sym['st_size']:#x})")
            continue
        addr, tsize = syms[name]
        tsize = tsize or sym["st_size"]
        tgt = read_va(addr, tsize)
        rl = relocs.get(shndx, {})
        bad = []
        n = max(len(data), len(tgt)) // 4
        for i in range(n):
            a = data[i * 4:i * 4 + 4]
            b = tgt[i * 4:i * 4 + 4]
            if len(a) < 4 or len(b) < 4:
                bad.append(i); continue
            if (sym["st_value"] + i * 4) in rl or (sym["st_value"] + i * 4 + 2) in rl:
                if a[0] >> 2 != b[0] >> 2:
                    bad.append(i)
                continue
            if a != b:
                bad.append(i)
        status = "OK" if (not bad and len(data) == tsize) else "XX"
        if status == "OK":
            ok += 1
        print(f"  {status} {name} @{addr:#x} size my={len(data):#x} tgt={tsize:#x} diffs={len(bad)}")
        if bad and args.v:
            # show side-by-side disasm
            show_diff(obj, sec.name, sym["st_value"], len(data), addr, tsize, set(bad))
    print(f"{ok}/{total} match")


def disasm_bytes(b, addr):
    p = "/tmp/claude-0/_d.bin"
    open(p, "wb").write(b)
    r = subprocess.run([f"{ROOT}/build/binutils/powerpc-eabi-objdump", "-D", "-b", "binary", "-m", "powerpc:common",
                        "-EB", f"--adjust-vma={addr:#x}", p], capture_output=True, text=True).stdout
    lines = []
    for l in r.splitlines():
        mm = re.match(r"\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} ){4})\s*(.*)", l)
        if mm:
            lines.append(mm.group(3))
    return lines


def show_diff(obj, secname, off, size, addr, tsize, bad):
    elf = ELFFile(open(obj, "rb"))
    data = elf.get_section_by_name(secname).data()[off:off + size]
    a = disasm_bytes(data, 0)
    b = disasm_bytes(read_va(addr, tsize), 0)
    for i in range(max(len(a), len(b))):
        x = a[i] if i < len(a) else ""
        y = b[i] if i < len(b) else ""
        mark = "*" if i in bad else " "
        print(f"   {mark}{i*4:4x}  {x:40s} | {y}")


if __name__ == "__main__":
    main()
