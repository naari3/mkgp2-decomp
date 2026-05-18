#!/usr/bin/env python3
"""Build ghidra_symbol_dump.json from raw Ghidra MCP output.

Inputs:
  - functions raw: outer-JSON wrapped (Bash tool-result form) of list_functions_enhanced
  - globals raw: plain text "name @ addr [Type] (DataType)" lines from list_globals

Outputs:
  - tools/ghidra_symbol_dump.json
"""
from __future__ import annotations
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
FN_RAW = Path(r"C:\Users\naari\.claude\projects\C--Users-naari-src-github-com-naari3-mkgp2-decomp\fee57a42-a9ea-4e43-a78b-7f522607616e\tool-results\mcp-ghidra-list_functions_enhanced-1779128652990.txt")
GL_RAW = HERE / "_ghidra_dump_globals.txt"
OUT = HERE / "ghidra_symbol_dump.json"

# Ghidra default (= unnamed) prefixes, case-insensitive
DEFAULT_PREFIXES = (
    "FUN_",
    "SUB_",
    "LAB_",
    "DAT_",
    "PTR_",
    "OFF_",
    "BYTE_",
    "WORD_",
    "DWORD_",
    "QWORD_",
    "caseD_",
    "switchD_",
    "switchdataD_",
)

ADDR_HEX = re.compile(r"^[0-9a-fA-F]{8}$")


def is_default_name(name: str) -> bool:
    n = name.lstrip("_")  # tolerate _FUN_xxx variants -> still default
    low = n.lower()
    for p in DEFAULT_PREFIXES:
        if low.startswith(p.lower()):
            # Cheap second test: the suffix is hex addr
            rest = n[len(p):]
            # Be tolerant: even if suffix isn't hex, treat the well-known
            # prefix as default. But warn the caller via "weird" flag higher up.
            if ADDR_HEX.match(rest) or re.match(r"^[0-9a-fA-F]{6,9}$", rest):
                return True
            # well-known prefix but odd suffix -> default-ish, drop with warning
            return True
    # Ghidra auto string label like s_some_string_8012abcd
    if low.startswith("s_") and re.search(r"_[0-9a-fA-F]{6,9}$", n):
        return True
    return False


def load_functions() -> list[dict]:
    outer = json.loads(FN_RAW.read_text(encoding="utf-8"))
    inner = json.loads(outer["result"])
    return inner["functions"]


def parse_globals() -> list[dict]:
    out: list[dict] = []
    pattern = re.compile(
        r"^(?P<name>\S+)\s+@\s+(?P<addr>[0-9a-fA-Fx]+|NO ADDRESS)\s+\[(?P<kind>[^\]]+)\](?:\s+\((?P<dtype>.*)\))?\s*$"
    )
    for line in GL_RAW.read_text(encoding="utf-8").splitlines():
        line = line.rstrip()
        if not line:
            continue
        m = pattern.match(line)
        if not m:
            sys.stderr.write(f"WARN: unparsed global line: {line!r}\n")
            continue
        out.append(
            {
                "name": m.group("name"),
                "addr_raw": m.group("addr"),
                "kind": m.group("kind"),
                "dtype": m.group("dtype"),
            }
        )
    return out


def main() -> int:
    functions_raw = load_functions()
    globals_raw = parse_globals()

    functions: dict[str, dict] = {}
    fn_warnings: list[str] = []
    fn_skipped = 0
    for fn in functions_raw:
        name = fn["name"]
        addr_hex = fn["address"].lower()
        if is_default_name(name):
            fn_skipped += 1
            continue
        addr_key = f"0x{addr_hex}"
        entry = {"name": name}
        # Note: list_functions_enhanced does not give size. Skip.
        if fn.get("isThunk"):
            entry["thunk"] = True
        if fn.get("isExternal"):
            entry["external"] = True
        if addr_key in functions:
            fn_warnings.append(
                f"duplicate function addr {addr_key}: existing={functions[addr_key]['name']!r} new={name!r} (kept existing)"
            )
            continue
        functions[addr_key] = entry

    globals_out: dict[str, dict] = {}
    gl_skipped = 0
    gl_warnings: list[str] = []
    for g in globals_raw:
        name = g["name"]
        if g["addr_raw"] == "NO ADDRESS":
            # switchD_* with NO ADDRESS — Namespace marker, always skip
            gl_skipped += 1
            continue
        if is_default_name(name):
            gl_skipped += 1
            continue
        addr_raw = g["addr_raw"].lower()
        if addr_raw.startswith("0x"):
            addr_raw = addr_raw[2:]
        addr_key = f"0x{addr_raw}"
        entry: dict = {"name": name}
        dtype = g.get("dtype")
        if dtype:
            entry["type_hint"] = dtype
        if addr_key in globals_out:
            gl_warnings.append(
                f"duplicate global addr {addr_key}: existing={globals_out[addr_key]['name']!r} new={name!r} (kept existing)"
            )
            continue
        globals_out[addr_key] = entry

    # Sort by address for deterministic output
    functions_sorted = dict(sorted(functions.items(), key=lambda kv: int(kv[0], 16)))
    globals_sorted = dict(sorted(globals_out.items(), key=lambda kv: int(kv[0], 16)))

    OUT.write_text(
        json.dumps(
            {"functions": functions_sorted, "globals": globals_sorted},
            ensure_ascii=False,
            indent=2,
        ),
        encoding="utf-8",
    )

    # Report (printed to stdout for the agent)
    print(f"raw_function_count={len(functions_raw)}")
    print(f"kept_functions={len(functions_sorted)}  skipped_default={fn_skipped}")
    print(f"raw_globals={len(globals_raw)}")
    print(f"kept_globals={len(globals_sorted)}  skipped_default={gl_skipped}")
    if fn_warnings:
        print("\n--- function duplicate warnings (max 10) ---")
        for w in fn_warnings[:10]:
            print(w)
    if gl_warnings:
        print("\n--- global duplicate warnings (max 10) ---")
        for w in gl_warnings[:10]:
            print(w)
    print(f"\nwrote: {OUT}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
