#!/usr/bin/env python3
"""Post-process a CW-built .o so manual extab/extabindex emissions land where
dtk expects them.

Two steps via llvm-objcopy:

1. Section rename:
     .extab_user      -> extab
     .extabindex_user -> extabindex
   mwcceppc reserves the bare names extab/extabindex and rejects
   __declspec(section "extab"). Emitting into ".extab_user" sidesteps the
   compiler check; renaming here merges the user entries into mwldeppc's
   default extab/extabindex output sections.

2. Symbol redefine (per-TU mapping):
   dtk dol split regenerates symbols.txt on every build and writes the
   anonymous local extab/extabindex symbols it observes in the target as
   `@etb_<addr>` / `@eti_<addr>` (scope:local hidden). dtk's dol diff then
   asserts these symbols exist at those addresses. C source can't declare
   identifiers starting with `@`, so we rename our user-side named symbols
   into the @-prefixed names llvm-objcopy expects.

   Mappings are read from a sibling json file `tools/extab_user_renames.json`
   (one entry per TU). Format:
     {
       "src/game/HeapStats.c": {
         "extab_dtor_8002F910":          "@etb_80005858",
         ...
         "extabindex_fn_8002F640":       "@eti_8001F490",
         ...
       }
     }
   The TU is identified by `.file` (-MMD or the first STT_FILE symbol);
   we fall back to scanning all rename keys against the object's local
   symbols if `.file` is missing.

Idempotent: if no .extab_user/.extabindex_user sections are present and no
mapped symbols match, this is a no-op.
"""
from __future__ import annotations

import json
import shutil
import struct
import subprocess
import sys
from pathlib import Path

LLVM_OBJCOPY_CANDIDATES = [
    "llvm-objcopy",
    r"C:\Program Files\LLVM\bin\llvm-objcopy.exe",
]

RENAMES_JSON = Path(__file__).resolve().parent / "extab_user_renames.json"


def patch_memorymanager_timedfree_extab(obj: Path) -> None:
    """Patch CW's auto extab flag for MemoryManager_TimedFree.

    The target extab has 0x101A0000 while mwcceppc GC/1.3.2 emits
    0x10180000 for the otherwise byte-identical entry. Keep this scoped to the
    one object that defines MemoryManager_TimedFree.
    """
    data = bytearray(obj.read_bytes())
    if data[:4] != b"\x7fELF" or data[5] != 2:
        return

    def u16(off: int) -> int:
        return int.from_bytes(data[off:off + 2], "big")

    def u32(off: int) -> int:
        return int.from_bytes(data[off:off + 4], "big")

    shoff = u32(0x20)
    shentsize = u16(0x2E)
    shnum = u16(0x30)
    shstrndx = u16(0x32)
    if shoff == 0 or shentsize == 0 or shstrndx >= shnum:
        return

    sections: list[dict[str, int | str]] = []
    shstr_hdr = shoff + shstrndx * shentsize
    shstr_off = u32(shstr_hdr + 0x10)
    shstr_size = u32(shstr_hdr + 0x14)
    shstr = data[shstr_off:shstr_off + shstr_size]

    def cstr(buf: bytes | bytearray, off: int) -> str:
        end = off
        while end < len(buf) and buf[end] != 0:
            end += 1
        return bytes(buf[off:end]).decode("ascii", errors="replace")

    for i in range(shnum):
        hdr = shoff + i * shentsize
        sections.append({
            "name": cstr(shstr, u32(hdr)),
            "type": u32(hdr + 0x04),
            "off": u32(hdr + 0x10),
            "size": u32(hdr + 0x14),
            "link": u32(hdr + 0x18),
            "entsize": u32(hdr + 0x24),
        })

    extab = next((s for s in sections if s["name"] == "extab"), None)
    symtab = next((s for s in sections if s["type"] == 2), None)
    if extab is None or symtab is None:
        return

    strtab_index = int(symtab["link"])
    if strtab_index >= len(sections):
        return
    strtab_sec = sections[strtab_index]
    strtab = data[int(strtab_sec["off"]):int(strtab_sec["off"]) + int(strtab_sec["size"])]
    sym_off = int(symtab["off"])
    sym_size = int(symtab["size"])
    sym_entsize = int(symtab["entsize"]) or 16
    has_timed_free = False
    for off in range(sym_off, sym_off + sym_size, sym_entsize):
        name = cstr(strtab, u32(off))
        if name == "MemoryManager_TimedFree":
            has_timed_free = True
            break
    if not has_timed_free:
        return

    extab_off = int(extab["off"])
    if data[extab_off:extab_off + 4] == bytes.fromhex("10180000"):
        data[extab_off:extab_off + 4] = bytes.fromhex("101A0000")
        obj.write_bytes(data)


def find_llvm_objcopy() -> str:
    for c in LLVM_OBJCOPY_CANDIDATES:
        if shutil.which(c) or Path(c).is_file():
            return c
    sys.exit(
        "llvm-objcopy not found. Install LLVM (provides llvm-objcopy.exe) or "
        "add a candidate path to tools/postprocess_extab_user.py."
    )


def load_tu_renames(obj: Path) -> dict[str, str]:
    """Collect rename pairs for the TU that produced `obj`.

    Keys in tools.extab_user_renames.json are `src/...` source paths
    (.c/.cpp). The object path is build/<ver>/src/.../<name>.o, so the TU
    key is derived by stripping everything up to and including "src" and
    trying both source extensions.

    The special `_shared` key holds renames that apply to every TU
    (e.g. `__nw__FUl` -> Alloc, the operator-new mapping used by all
    C++ TUs). It is always merged in.

    Passing only shared + this TU's pairs (instead of a flat map of
    every TU) keeps the llvm-objcopy argv below the Windows
    CreateProcess limit (WinError 206) now that the rename table has
    ~900 entries.
    """
    if not RENAMES_JSON.is_file():
        return {}
    data = json.loads(RENAMES_JSON.read_text(encoding="utf-8"))
    renames: dict[str, str] = {}
    shared = data.get("_shared")
    if isinstance(shared, dict):
        renames.update(shared)
    parts = obj.parts
    if "src" not in parts:
        return renames
    rel = Path(*parts[parts.index("src") + 1 :]).with_suffix("")
    for ext in (".c", ".cpp"):
        key = "src/" + rel.as_posix() + ext
        mapping = data.get(key)
        if isinstance(mapping, dict):
            renames.update(mapping)
    return renames



def make_undefined(obj: Path, names: list[str]) -> None:
    """Turn the named defined symbols into undefined globals. A data section
    left with no defined symbols is emptied (size 0), so the object no longer
    contributes those bytes to the link."""
    d = bytearray(obj.read_bytes())
    shoff = struct.unpack_from(">I", d, 0x20)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", d, 0x2E)
    secs = [list(struct.unpack_from(">10I", d, shoff + i * shentsize)) for i in range(shnum)]
    symtab = next(s for s in secs if s[1] == 2)
    strtab = secs[symtab[6]]

    def sname(off: int) -> str:
        base = strtab[4]
        return d[base + off:d.index(b"\0", base + off)].decode()

    touched = set()
    for i in range(symtab[5] // 16):
        off = symtab[4] + i * 16
        st_name, _, _, st_info, st_other, shndx = struct.unpack_from(">IIIBBH", d, off)
        if st_name and sname(st_name) in names and shndx != 0:
            touched.add(shndx)
            struct.pack_into(">IIIBBH", d, off, st_name, 0, 0, (1 << 4) | 0, st_other, 0)
    for idx in touched:
        still = False
        for i in range(symtab[5] // 16):
            _, _, _, st_info, _, shndx = struct.unpack_from(">IIIBBH", d, symtab[4] + i * 16)
            if shndx == idx and (st_info & 0xF) != 3:  # ignore the STT_SECTION symbol
                still = True
        if not still:
            struct.pack_into(">I", d, shoff + idx * shentsize + 0x14, 0)
    obj.write_bytes(d)

def force_active(obj: Path, names: list[str]) -> None:
    """Set MWCC's force_active flag (0x08 at +5 of the 8-byte per-symbol
    record in .comment, see docs/comment_section.md) on the named symbols, so
    mwld keeps an object nothing references (e.g. the string literals of a
    never-called static function, which is itself dead-stripped)."""
    d = bytearray(obj.read_bytes())
    shoff, = struct.unpack_from(">I", d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", d, 0x2E)
    secs = [struct.unpack_from(">IIIIIIIIII", d, shoff + i * shentsize) for i in range(shnum)]
    shstr = secs[shstrndx][4]
    def secname(sec):
        o = shstr + sec[0]
        return bytes(d[o:d.index(b"\0", o)]).decode()
    comment = next((x for x in secs if secname(x) == ".comment"), None)
    symtab = next((x for x in secs if x[1] == 2), None)
    if comment is None or symtab is None:
        sys.exit(f"{obj}: active: rename needs .symtab and .comment")
    strtab = secs[symtab[6]][4]
    left = set(names)
    for i in range(symtab[5] // 16):
        st_name, = struct.unpack_from(">I", d, symtab[4] + i * 16)
        o = strtab + st_name
        name = bytes(d[o:d.index(b"\0", o)]).decode()
        if name in left:
            left.discard(name)
            d[comment[4] + 0x2C + i * 8 + 5] |= 0x08
    if left:
        sys.exit(f"{obj}: active: symbols not found: {sorted(left)}")
    obj.write_bytes(d)


def main() -> int:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_extab_user.py <object.o>")
    obj = Path(sys.argv[1])
    if not obj.is_file():
        sys.exit(f"file not found: {obj}")

    objcopy = find_llvm_objcopy()
    cmd: list[str] = [
        objcopy,
        "--rename-section=.extab_user=extab",
        "--rename-section=.extabindex_user=extabindex",
    ]
    renames = load_tu_renames(obj)
    externs: list[str] = []
    actives: list[str] = []
    # "#align4": ".rodata,.data" pins those sections to 4-byte alignment
    # (tools/postprocess_data_align4_keep_comment.py) for a TU whose section
    # starts on a 4-byte boundary in the target; MWCC always emits 8.
    align4 = renames.pop("#align4", "")
    for src, dst in renames.items():
        # "active:<name>" renames a TU-local object and sets its force_active
        # flag: the target keeps it although nothing references it.
        if dst.startswith("active:"):
            dst = dst[len("active:"):]
            actives.append(dst)
        # "extern:<name>" renames a TU-local object (e.g. an RTTI type-name
        # string) and turns it into an undefined reference: the target keeps
        # that object in another TU's section.
        if dst.startswith("extern:"):
            dst = dst[len("extern:"):]
            externs.append(dst)
            cmd.append(f"--globalize-symbol={src}")
            cmd.append(f"--redefine-sym={src}={dst}")
            continue
        # "global:<name>" also gives the renamed symbol global binding, for
        # a TU-local object (e.g. a pooled string literal) that another
        # split TU references by name.
        if dst.startswith("global:"):
            dst = dst[len("global:"):]
            cmd.append(f"--globalize-symbol={src}")
        cmd.append(f"--redefine-sym={src}={dst}")
    cmd.append(str(obj))
    subprocess.check_call(cmd)
    if externs:
        make_undefined(obj, externs)
    if actives:
        force_active(obj, actives)
    for section in filter(None, align4.split(",")):
        subprocess.check_call([
            sys.executable,
            str(Path(__file__).resolve().parent / "postprocess_data_align4_keep_comment.py"),
            str(obj), section,
        ])
    patch_memorymanager_timedfree_extab(obj)
    # Mixed auto/manual extab TUs: consolidate entries into fn-address order
    # (no-op for single-pair or already-sorted objects). See
    # tools/reorder_extab.py and docs/archive/large_tu_cpp_conversion.md Phase 1.
    subprocess.check_call([
        sys.executable,
        str(Path(__file__).resolve().parent / "reorder_extab.py"),
        str(obj),
    ])
    return 0


if __name__ == "__main__":
    sys.exit(main())
