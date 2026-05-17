#!/usr/bin/env python3
"""Extract dtk-generated extab-group asm into C source skeleton for the
manual-emit asm_fn pattern.

Input: `build/<config>/asm/<group>.s` produced by `dtk dol split`. Each such
file is a single dtk reversed-extab group containing:
  - `.section extab, "a"`      / `.obj "@etb_<addr>"` ... raw bytes
  - `.section extabindex, "a"` / `.obj "@eti_<addr>"` ... 12-byte structs
  - `.text` / `.fn <name>, <scope>` ... instruction lines per function

Output: C source fragments that reproduce the same `.text` / `extab` /
`extabindex` layout when fed through:
  - `#pragma section R ".extab_user"` + `#pragma section R ".extabindex_user"`
  - `tools/postprocess_extab_user.py` (section + symbol rename via llvm-objcopy)
  - `Object(Matching, ..., extab_padding=b"\x00\x00")` build rule
See `docs/per_fn_matching_strategy.md` §12 and `src/game/HeapStats.c`.

Sections emitted in target layout order (extab / extabindex inside the asm
file are not necessarily in fn address order — they're whatever order the
target binary placed them). asm bodies are emitted in `.text` address order.

Renames JSON snippet: one TU entry mapping the C-side names this tool emits
(`extab_<fn>` / `extabindex_<fn>`) to the dtk-anonymized targets
(`@etb_<addr>` / `@eti_<addr>`) — merge into `tools/extab_user_renames.json`.

Out of scope (Phase A): writing the .c file in-place, editing configure.py /
splits.txt / state.json. Caller (orchestrator main or human) copies the
fragments into a hand-prepared TU.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ASM_DIR = REPO_ROOT / "build" / "GNLJ82" / "asm"
DEFAULT_SYMBOLS_TXT = REPO_ROOT / "config" / "GNLJ82" / "symbols.txt"

# `<name> = .<section>:0x<addr>; ...` (dtk symbols.txt format)
SYMBOLS_LINE_RE = re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_@]*)\s*=\s*\.([A-Za-z0-9_]+)\s*:\s*0x[0-9A-Fa-f]+\s*;')

# Sections whose symbols are accessed via the sda1 base (r13).
SDA1_SECTIONS = {'sdata', 'sbss'}
# Sections whose symbols are accessed via the sda2 base (r2).
SDA2_SECTIONS = {'sdata2', 'sbss2'}

INSTR_LINE_RE = re.compile(r"^\s*/\*[^*]*\*/\s*(.*\S)\s*$")
SECTION_RE = re.compile(r'^\.section\s+(\S+?)(?:,.*)?$')
OBJ_RE = re.compile(r'^\.obj\s+"([^"]+)"\s*,\s*(\S+)\s*$')
ENDOBJ_RE = re.compile(r'^\.endobj\s+"([^"]+)"\s*$')
FN_RE = re.compile(r'^\.fn\s+(\S+)\s*,\s*(\S+)\s*$')
ENDFN_RE = re.compile(r'^\.endfn\s+(\S+)\s*$')
BYTE4_RE = re.compile(r'^\s*\.4byte\s+(.+)\s*$')

# mwcc inline-asm syntax fixups (docs/per_fn_matching_strategy.md §11)
SDA21_RE = re.compile(r'\b([A-Za-z_][A-Za-z0-9_]*)@sda21\(r0\)')
# `li rD, sym@sda21` -> mwcc rejects this form; rewrite to `addi rD, 0, sym@sda21`
# (mwcc accepts the addi form and emits the sda21 reloc).
SDA21_LI_RE = re.compile(r'\bli\s+(r\d+)\s*,\s*([A-Za-z_][A-Za-z0-9_]*)@sda21\b')
CR_FIELD_RE = re.compile(r'\b(crclr|crset)\s+cr(\d)(lt|gt|eq|so|un)\b')
_CR_BIT_OFFSET = {'lt': 0, 'gt': 1, 'eq': 2, 'so': 3, 'un': 3}

# Identifier classification (run on the post-rewrite instruction line).
LOCAL_LABEL_DECL_RE = re.compile(r'^\s*(\.L_[0-9A-Fa-f]+):\s*$')
# .L_<addr> reference anywhere in a line (e.g. `bne .L_8002F66C`, `b .L_8002F6DC`).
LOCAL_LABEL_REF_RE = re.compile(r'\.L_([0-9A-Fa-f]+)')
# bl/b targeting a named symbol (not a .L_ local label, not a register).
BRANCH_CALL_RE = re.compile(r'\b(?:bl|b|ba|bla)\s+([A-Za-z_][A-Za-z0-9_]*)\b')
# Data ref via @ha / @l / @h relocs.
DATA_REL_RE = re.compile(r'\b([A-Za-z_][A-Za-z0-9_]*)@(?:ha|h|l|lo|hi)\b')


@dataclass
class ExtabEntry:
    label: str                                       # "@etb_80005858"
    addr: int                                        # 0x80005858
    # Each .4byte slot is either a numeric immediate (int, None) or a symbol
    # reference (None, "dtor_8003AFB8"). cwextab embeds destructor pointers
    # and typeids as symbolic .4byte entries; emitting these as raw bytes
    # would lose the link-time relocation.
    fields: list[tuple[Optional[int], Optional[str]]] = field(default_factory=list)

    @property
    def is_symbolic(self) -> bool:
        return any(f[1] is not None for f in self.fields)

    @property
    def raw_bytes(self) -> bytes:
        """Flatten numeric-only entries to big-endian bytes; raises if any
        field is symbolic (caller must check `is_symbolic` first)."""
        if self.is_symbolic:
            raise ValueError(f"extab {self.label} has symbolic refs — render as struct")
        out = bytearray()
        for val, _ in self.fields:
            out += val.to_bytes(4, 'big')
        return bytes(out)


@dataclass
class ExtabIndexEntry:
    label: str           # "@eti_8001F490"
    addr: int            # 0x8001F490
    fn_name: str         # "fn_8002F640"
    fn_size: int         # 0x000001BC
    extab_label: str     # "@etb_80005868"


@dataclass
class FnAsm:
    name: str
    scope: str
    instructions: list[str] = field(default_factory=list)


@dataclass
class GroupData:
    extab: list[ExtabEntry] = field(default_factory=list)
    extabindex: list[ExtabIndexEntry] = field(default_factory=list)
    functions: list[FnAsm] = field(default_factory=list)


def _parse_addr_from_label(label: str, prefix: str) -> int:
    if not label.startswith(prefix):
        raise ValueError(f"expected label starting with {prefix!r}, got {label!r}")
    return int(label[len(prefix):], 16)


def _parse_4byte_operand(operand: str) -> tuple[Optional[int], Optional[str]]:
    """Return (int_value, None) for numeric literal or (None, symbol) for label.
    Quoted "@etb_..." / "@eti_..." labels are unquoted to plain symbol."""
    s = operand.strip()
    if s.startswith('0x') or s.startswith('0X'):
        return int(s, 16), None
    if s.startswith('"') and s.endswith('"'):
        return None, s[1:-1]
    if s.lstrip('-').isdigit():
        return int(s, 0), None
    return None, s  # bare identifier (fn name etc.)


def parse_group(asm_path: Path) -> GroupData:
    data = GroupData()
    current_section: Optional[str] = None
    current_extab: Optional[ExtabEntry] = None
    current_eti: Optional[dict] = None  # {label, addr, fields:[(val,sym), ...]}
    current_fn: Optional[FnAsm] = None

    with asm_path.open(encoding="utf-8") as f:
        for raw in f:
            line = raw.rstrip('\n')
            stripped = line.strip()
            if not stripped or stripped.startswith('#'):
                continue

            # Instruction line (/* addr off bytes */ <TAB> asm) must be matched
            # before the block-comment skip below — both start with "/*".
            if current_fn is not None and current_section == '.text':
                m_ins = INSTR_LINE_RE.match(line)
                if m_ins:
                    current_fn.instructions.append(m_ins.group(1))
                    continue
                # Bare local-label declaration (`.L_<addr>:`) — no comment prefix.
                if LOCAL_LABEL_DECL_RE.match(stripped):
                    current_fn.instructions.append(stripped)
                    continue

            # Block-comment lines (e.g. " * Flag values: ...") — skip.
            if stripped.startswith('/*') or stripped.startswith('*'):
                continue

            if stripped == '.text':
                current_section = '.text'
                continue
            m_sec = SECTION_RE.match(stripped)
            if m_sec:
                current_section = m_sec.group(1)
                continue
            if stripped.startswith('.balign') or stripped.startswith('.include') \
                    or stripped.startswith('.file') or stripped.startswith('.hidden'):
                continue

            m_obj = OBJ_RE.match(stripped)
            if m_obj:
                label = m_obj.group(1)
                if label.startswith('@etb_'):
                    current_extab = ExtabEntry(
                        label=label,
                        addr=_parse_addr_from_label(label, '@etb_'),
                    )
                elif label.startswith('@eti_'):
                    current_eti = {
                        'label': label,
                        'addr': _parse_addr_from_label(label, '@eti_'),
                        'fields': [],
                    }
                continue

            m_endobj = ENDOBJ_RE.match(stripped)
            if m_endobj:
                if current_extab is not None:
                    data.extab.append(current_extab)
                    current_extab = None
                elif current_eti is not None:
                    fields = current_eti['fields']
                    if len(fields) != 3:
                        raise ValueError(
                            f"extabindex {current_eti['label']} expected 3 fields, got {len(fields)}"
                        )
                    fn_field = fields[0]
                    size_field = fields[1]
                    etb_field = fields[2]
                    fn_name = fn_field[1]
                    fn_size = size_field[0] if size_field[0] is not None else 0
                    etb_label = etb_field[1]
                    data.extabindex.append(ExtabIndexEntry(
                        label=current_eti['label'],
                        addr=current_eti['addr'],
                        fn_name=fn_name,
                        fn_size=fn_size,
                        extab_label=etb_label,
                    ))
                    current_eti = None
                continue

            m_fn = FN_RE.match(stripped)
            if m_fn:
                current_fn = FnAsm(name=m_fn.group(1), scope=m_fn.group(2))
                continue

            m_endfn = ENDFN_RE.match(stripped)
            if m_endfn:
                if current_fn is not None:
                    data.functions.append(current_fn)
                current_fn = None
                continue

            # .4byte inside extab / extabindex blocks
            if (current_extab is not None or current_eti is not None):
                m_b4 = BYTE4_RE.match(line)
                if m_b4:
                    val, sym = _parse_4byte_operand(m_b4.group(1))
                    if current_extab is not None:
                        current_extab.fields.append((val, sym))
                    else:
                        current_eti['fields'].append((val, sym))
                    continue

    return data


def load_sda_base_map(symbols_path: Path) -> dict[str, str]:
    """Build sym -> 'r2' | 'r13' map from dtk symbols.txt.

    Symbols in .sdata2 / .sbss2 use the sda2 base (r2); .sdata / .sbss use
    sda1 (r13). Other sections fall outside the small-data area and don't
    appear here (sda21 reloc not applicable).
    """
    out: dict[str, str] = {}
    if not symbols_path.is_file():
        return out
    with symbols_path.open(encoding="utf-8") as f:
        for line in f:
            m = SYMBOLS_LINE_RE.match(line)
            if not m:
                continue
            sym, section = m.group(1), m.group(2)
            if section in SDA1_SECTIONS:
                out[sym] = 'r13'
            elif section in SDA2_SECTIONS:
                out[sym] = 'r2'
    return out


def _rewrite_instruction(line: str, sda21_syms: set[str], fn_name: str,
                          sda_base_map: dict[str, str]) -> str:
    """Apply mwcc inline-asm syntax fixups and collect sda21 symbols.

    - `lbl@sda21(r0)` -> `lbl(r2)` or `lbl(r13)` based on the symbol's
      section in symbols.txt (.sdata2/.sbss2 -> r2, .sdata/.sbss -> r13).
      mwcc emits the corresponding sda{2,1} reloc which the linker resolves.
      Unknown symbols default to r2 (sda2 base) with a warning.
    - `crclr/crset crNcond` -> `crxor/creqv N*4+bit, N*4+bit, N*4+bit`.
    - `.L_<addr>` -> `<fn_name>_L_<addr>` (mwcc `.`-prefix is a directive).
    """
    def _sda21_sub(m: re.Match) -> str:
        sym = m.group(1)
        sda21_syms.add(sym)
        base = sda_base_map.get(sym, 'r2')
        return f'{sym}({base})'
    line = SDA21_RE.sub(_sda21_sub, line)

    def _sda21_li_sub(m: re.Match) -> str:
        reg = m.group(1)
        sym = m.group(2)
        sda21_syms.add(sym)
        return f'addi {reg}, 0, {sym}@sda21'
    line = SDA21_LI_RE.sub(_sda21_li_sub, line)

    def _cr_sub(m: re.Match) -> str:
        op = m.group(1)
        field = int(m.group(2))
        bit = field * 4 + _CR_BIT_OFFSET[m.group(3)]
        new_op = 'crxor' if op == 'crclr' else 'creqv'
        return f'{new_op} {bit}, {bit}, {bit}'
    line = CR_FIELD_RE.sub(_cr_sub, line)

    line = LOCAL_LABEL_REF_RE.sub(lambda m: f'{fn_name}_L_{m.group(1)}', line)

    return line


def _format_byte_array(b: bytes, indent: str = "    ", per_line: int = 8) -> str:
    if not b:
        return "{}"
    parts = [f"0x{x:02X}" for x in b]
    lines = []
    for i in range(0, len(parts), per_line):
        lines.append(indent + ", ".join(parts[i:i + per_line]))
    return "{\n" + ",\n".join(lines) + "\n}"


def _label_to_c_name(label: str, kind: str, fn_name: str) -> str:
    """C-side identifier this tool emits for an extab/extabindex entry.

    kind in {"extab", "extabindex"}. We prefer per-fn names so the link
    between extab and its fn is readable; the rename mapping turns these
    into @etb_<addr> / @eti_<addr> at objcopy time.
    """
    return f"{kind}_{fn_name}"


def emit_c_source(group_id: str, data: GroupData, sda_base_map: dict[str, str]) -> str:
    """Build the C source fragment in target section-layout order."""
    # Map etb_label -> fn_name via extabindex entries.
    etb_to_fn: dict[str, str] = {}
    for eti in data.extabindex:
        if eti.extab_label in etb_to_fn:
            raise ValueError(
                f"extab {eti.extab_label} referenced by multiple extabindex entries"
            )
        etb_to_fn[eti.extab_label] = eti.fn_name

    # Apply mwcc fixups to all instructions, collecting sda21 syms. Local
    # label rewrite is per-fn so labels stay scoped.
    sda21_syms: set[str] = set()
    rewritten: list[FnAsm] = []
    for fn in data.functions:
        new_fn = FnAsm(name=fn.name, scope=fn.scope)
        new_fn.instructions = [
            _rewrite_instruction(ins, sda21_syms, fn.name, sda_base_map)
            for ins in fn.instructions
        ]
        rewritten.append(new_fn)

    # Classify referenced identifiers into callees / data refs / locals.
    # After rewrite, local labels have form `<fn_name>_L_<addr>`.
    local_label_decl_re = re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_]*_L_[0-9A-Fa-f]+):\s*$')
    local_labels: set[str] = set()
    callee_syms: set[str] = set()
    data_syms: set[str] = set()
    own_fn_names = {fn.name for fn in rewritten}
    for fn in rewritten:
        for ins in fn.instructions:
            m_local = local_label_decl_re.match(ins)
            if m_local:
                local_labels.add(m_local.group(1))
                continue
            for m in BRANCH_CALL_RE.finditer(ins):
                callee_syms.add(m.group(1))
            for m in DATA_REL_RE.finditer(ins):
                data_syms.add(m.group(1))
    # Drop refs to local labels, to our own asm fns (covered by forward decls),
    # and to sda21 syms (covered by the sda21 extern block).
    callee_syms -= local_labels | own_fn_names | sda21_syms
    data_syms -= local_labels | own_fn_names | sda21_syms

    out: list[str] = []
    out.append(f"/* === extracted from {group_id} === */")
    out.append("/* Copy into the TU between forward decls and function bodies; */")
    out.append("/* keep emit order = target section layout (do not sort). */")
    out.append("")

    # extern decls. Type is mostly arbitrary — mwcc picks sda21 vs large-data
    # from the symbol's section, not its C type. We split into 3 groups so the
    # generated file is greppable; user can refine types later.
    if callee_syms:
        out.append("/* --- extern decls: branch callees (bl/b targets) --- */")
        out.append("/* Open prototype (`extern void Foo();`) accepts any call signature; */")
        out.append("/* refine if the real prototype matters for header consumers. */")
        for sym in sorted(callee_syms):
            out.append(f"extern void {sym}();")
        out.append("")
    if sda21_syms:
        out.append("/* --- extern decls: sda21-referenced data --- */")
        for sym in sorted(sda21_syms):
            out.append(f"extern unsigned int {sym};")
        out.append("")
    if data_syms:
        out.append("/* --- extern decls: large-data refs (@ha/@l pairs) --- */")
        out.append("/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */")
        out.append("/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */")
        for sym in sorted(data_syms):
            out.append(f"extern unsigned int {sym}[];")
        out.append("")

    # Forward decls of the asm fns so the extabindex initializers can take
    # their address. mwcc accepts function pointer initializers only if the
    # callee is declared first.
    out.append("/* --- forward decls --- */")
    for fn in rewritten:
        out.append(f"asm void {fn.name}(void);")
    out.append("")

    # Collect any extab-referenced symbols (cwextab dtor/typeid refs) that
    # aren't already covered by the asm-body extern groups. Emit as branch-callee
    # `extern void <sym>();` so they appear in the existing extern block above.
    extab_symbolic_refs: set[str] = set()
    for entry in data.extab:
        for _, sym in entry.fields:
            if sym is not None:
                extab_symbolic_refs.add(sym)
    extab_new_externs = extab_symbolic_refs - callee_syms - sda21_syms - data_syms - own_fn_names
    if extab_new_externs:
        out.append("/* --- extern decls: extab symbolic refs (dtors / typeids) --- */")
        for sym in sorted(extab_new_externs):
            out.append(f"extern void {sym}();")
        out.append("")

    # extab emit (skip if the group has no extab entries — sda1/text-only groups).
    # Two render shapes:
    #   - numeric-only entries:  `unsigned char [N]` with hex byte literals
    #   - entries containing symbolic .4byte: anonymous struct with
    #     `unsigned int` / `void *` fields so the linker resolves the refs.
    if data.extab:
        out.append('/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */')
        out.append('#pragma section R ".extab_user"')
        for entry in data.extab:
            fn_name = etb_to_fn.get(entry.label, f"orphan_{entry.addr:08X}")
            c_name = _label_to_c_name(entry.label, "extab", fn_name)
            if not entry.is_symbolic:
                b = entry.raw_bytes
                out.append(f'__declspec(section ".extab_user") static const unsigned char {c_name}[{len(b)}] = '
                           f'{_format_byte_array(b)};')
            else:
                field_decls = []
                inits = []
                for i, (val, sym) in enumerate(entry.fields):
                    if sym is not None:
                        field_decls.append(f'void *f{i};')
                        inits.append(f'(void *)&{sym}')
                    else:
                        field_decls.append(f'unsigned int f{i};')
                        inits.append(f'0x{val:08X}')
                fields_str = ' '.join(field_decls)
                inits_str = ', '.join(inits)
                out.append(f'__declspec(section ".extab_user") static const struct '
                           f'{{ {fields_str} }} {c_name} = {{ {inits_str} }};')
        out.append("")

    if data.extabindex:
        # Index extab entries by label so we can pick the right C cast: array
        # names decay to their address (`(void *)arr`), struct names don't
        # (`(void *)&obj`). mwcc rejects the latter as "illegal explicit
        # conversion from 'const struct' to 'void *'".
        extab_by_label = {e.label: e for e in data.extab}
        out.append('/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */')
        out.append('#pragma section R ".extabindex_user"')
        for eti in data.extabindex:
            c_name = _label_to_c_name(eti.label, "extabindex", eti.fn_name)
            etb_c_name = _label_to_c_name(eti.extab_label, "extab", eti.fn_name)
            etb_entry = extab_by_label.get(eti.extab_label)
            etb_ref = f'&{etb_c_name}' if (etb_entry and etb_entry.is_symbolic) else etb_c_name
            out.append(f'__declspec(section ".extabindex_user") static const struct '
                       f'{{ void *fn; unsigned int fn_size; void *extab; }} {c_name} = ' '{')
            out.append(f'    (void *)&{eti.fn_name}, 0x{eti.fn_size:08X}, (void *){etb_ref}')
            out.append("};")
        out.append("")

    # asm bodies in .text order (= fn definition source order).
    out.append("/* --- asm function bodies (.text order = fn address order) --- */")
    for fn in rewritten:
        out.append(f"asm void {fn.name}(void) {{")
        out.append("    nofralloc")
        for ins in fn.instructions:
            out.append(f"    {ins}")
        out.append("}")
        out.append("")

    return "\n".join(out)


def build_renames_snippet(data: GroupData, tu_path: Optional[str]) -> dict:
    etb_to_fn = {eti.extab_label: eti.fn_name for eti in data.extabindex}
    mapping: dict[str, str] = {}
    for entry in data.extab:
        fn_name = etb_to_fn.get(entry.label, f"orphan_{entry.addr:08X}")
        mapping[_label_to_c_name(entry.label, "extab", fn_name)] = entry.label
    for eti in data.extabindex:
        mapping[_label_to_c_name(eti.label, "extabindex", eti.fn_name)] = eti.label
    if tu_path:
        return {tu_path: mapping}
    return mapping


def resolve_group_path(group_id: str, asm_dir: Path) -> Path:
    candidate = Path(group_id)
    if candidate.is_file():
        return candidate
    name = group_id if group_id.endswith(".s") else group_id + ".s"
    p = asm_dir / name
    if p.is_file():
        return p
    raise SystemExit(f"asm file not found: tried {candidate} and {p}")


def main(argv: Optional[list[str]] = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("group", help="group id (e.g. auto_fn_8002F640_text) or path to .s")
    ap.add_argument("--asm-dir", type=Path, default=DEFAULT_ASM_DIR,
                    help=f"dtk asm dir (default: {DEFAULT_ASM_DIR})")
    ap.add_argument("--symbols-txt", type=Path, default=DEFAULT_SYMBOLS_TXT,
                    help=f"symbols.txt for sda1/sda2 base selection (default: {DEFAULT_SYMBOLS_TXT})")
    ap.add_argument("--out-c", type=Path, help="write C source fragment here (default: stdout)")
    ap.add_argument("--out-renames", type=Path,
                    help="write extab_user_renames.json snippet here (default: stdout if --tu given)")
    ap.add_argument("--tu", help='TU path key for renames snippet (e.g. "src/game/HeapStats.c")')
    args = ap.parse_args(argv)

    asm_path = resolve_group_path(args.group, args.asm_dir)
    data = parse_group(asm_path)
    sda_base_map = load_sda_base_map(args.symbols_txt)

    c_src = emit_c_source(asm_path.stem, data, sda_base_map)
    if args.out_c:
        args.out_c.write_text(c_src + "\n", encoding="utf-8")
    else:
        sys.stdout.write(c_src + "\n")

    snippet = build_renames_snippet(data, args.tu)
    snippet_json = json.dumps(snippet, indent=2, ensure_ascii=False)
    if args.out_renames:
        args.out_renames.write_text(snippet_json + "\n", encoding="utf-8")
    elif args.tu:
        sys.stdout.write("\n/* --- renames snippet (merge into tools/extab_user_renames.json) --- */\n")
        sys.stdout.write(snippet_json + "\n")

    return 0


if __name__ == "__main__":
    sys.exit(main())
