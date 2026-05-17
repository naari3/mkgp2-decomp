#!/usr/bin/env python3
"""Insert orphan symbols into config/GNLJ82/symbols.txt by splitting the
enclosing dtk-detected blob.

dtk's `detect_objects: true` groups adjacent data into large `lbl_XXXX` blobs.
When Ghidra has identified a named symbol inside such a blob, we cannot just
add a new entry — dtk rejects overlapping symbols. Instead, we replace the
enclosing `lbl_XXXX` with:

  - a head `lbl_XXXX` of reduced size (the bytes before the first orphan)
  - one entry per orphan inside the blob
  - tail `lbl_XXXX` entries between/after orphans

Total size and address coverage are preserved, so the rebuild is still
byte-identical (SHA-1 verify must pass).

Orphans whose enclosing blob is itself a non-placeholder symbol are skipped:
splitting a meaningful symbol would change the meaning.

Run from the mkgp2-decomp project root.
"""
from __future__ import annotations
import re
import sys
from pathlib import Path

SYM_PATH = Path("config/GNLJ82/symbols.txt")

# (name, section, addr, size, data_attr_or_None)
# Note: the first 6 entries here are already in symbols.txt from a prior
# commit; the script is idempotent (no-op when the address already exists)
# so re-runs are safe.
NEW_ENTRIES: list[tuple[str, str, int, int, str | None]] = [
    # === Already committed (A subset, first pass) ===
    ("kCup0LineBinTable",                 ".rodata", 0x8032890c, 0x10,  "4byte"),
    ("kBgmDspFilenameTable",              ".rodata", 0x8037ce1c, 0xa8,  "4byte"),
    ("kAILapBonusRules_NonRaceCommon",    ".rodata", 0x803bcb48, 0x64,  None),
    ("kAILapBonusRuleTable_RaceCourse",   ".rodata", 0x803bcbac, 0x60,  "4byte"),
    ("kAILapBonusRuleTable_RaceFallback", ".rodata", 0x803bcc0c, 0x300, "4byte"),
    ("g_ammbSocketState",                 ".bss",    0x806a14dc, 0x800, None),

    # === A residual (size narrowed to match dtk blob boundary) ===
    # Ghidra said AILapBonusRule*[104] (0x1A0) but that overflows the
    # enclosing blob 0x803BCAA8..0x803BD08C by 0x20. Drop to 0x180
    # (= 96 entries) so it fits, the trailing string table is left intact.
    ("kAILapBonusRuleTable_NonRace",      ".rodata", 0x803bcf0c, 0x180, "4byte"),

    # === B: named BSS/data scalars, sizes from Ghidra batch query ===
    ("g_frameUnlockThresholds_Partial",   ".rodata", 0x8039ae3c, 0x1, None),
    ("g_frameUnlockThresholds_Full",      ".rodata", 0x8039ae70, 0x1, None),
    ("g_tierTextureIdTable",              ".rodata", 0x8039aea4, 0x1, None),
    ("g_voiceWeightTable",                ".data",   0x80498170, 0x1, None),
    ("g_jvsSteeringRaw",                  ".bss",    0x80598570, 0x2, "2byte"),
    ("g_jvsAccelRaw",                     ".bss",    0x80598572, 0x2, "2byte"),
    ("g_jvsBrakeRaw",                     ".bss",    0x80598574, 0x2, "2byte"),
    ("g_DebugPrintfEnable",               ".bss",    0x80598a8a, 0x1, "byte"),
    ("g_jvsDebounceEnable",               ".bss",    0x80598aa4, 0x4, "4byte"),
    ("g_displayOffsetY",                  ".bss",    0x80598aa8, 0x4, "4byte"),
    ("g_displayOffsetX",                  ".bss",    0x80598aac, 0x4, "4byte"),
    ("g_syncedSceneState",                ".bss",    0x805ac260, 0x1, "byte"),
    ("g_playerWinsCurrent",               ".bss",    0x805d258e, 0x2, "2byte"),
    ("g_playerLossesCurrent",             ".bss",    0x805d2590, 0x2, "2byte"),
    ("g_currentTitleId",                  ".bss",    0x805d271b, 0x1, "byte"),
    ("g_lastSelectedTier",                ".bss",    0x805d2738, 0x1, "byte"),
    ("g_playerWinsPrev",                  ".bss",    0x805d2f4e, 0x2, "2byte"),
    ("g_playerLossesPrev",                ".bss",    0x805d2f50, 0x2, "2byte"),
    ("g_raceCurrentSpeakerAux",           ".bss",    0x80678f14, 0x4, "4byte"),
    ("g_raceCurrentSpeakerFlag",          ".bss",    0x80678f18, 0x4, "4byte"),
    ("g_OSMachineCheckDMAHandler",        ".bss",    0x80679fb0, 0x4, "4byte"),
    ("g_DefaultThread",                   ".bss",    0x8067a430, 0x1, "byte"),
]

SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);(?P<rest>.*)$"
)
SIZE_RE = re.compile(r"size:0x([0-9a-fA-F]+)")


PLACEHOLDER_PREFIXES = ("fn_", "lbl_", "data_")


def is_placeholder(name: str) -> bool:
    nl = name.lower()
    return any(nl.startswith(p) for p in PLACEHOLDER_PREFIXES)


def format_entry(name: str, section: str, addr: int, size: int, data: str | None) -> str:
    base = f"{name} = {section}:0x{addr:08X}; // type:object size:0x{size:X}"
    return f"{base} data:{data}" if data else base


def format_lbl(section: str, addr: int, size: int) -> str:
    """Synthesize a tail-segment placeholder line in the dtk convention."""
    return f"lbl_{addr:08X} = {section}:0x{addr:08X}; // type:object size:0x{size:X}"


def main() -> int:
    if not SYM_PATH.exists():
        sys.exit(f"symbols.txt not found: {SYM_PATH}")

    raw_lines = SYM_PATH.read_text(encoding="utf-8").splitlines()
    # Parse each line so we can locate the enclosing blob for every orphan.
    parsed: list[dict] = []
    for line in raw_lines:
        m = SYM_LINE.match(line)
        if not m:
            parsed.append({"raw": line})
            continue
        sm = SIZE_RE.search(m.group("rest"))
        sz = int(sm.group(1), 16) if sm else 0
        parsed.append({
            "raw": line,
            "name": m.group("name"),
            "section": m.group("section"),
            "addr": int(m.group("addr"), 16),
            "size": sz,
        })

    # Group orphans by the enclosing blob they fall inside.
    # key: index of enclosing line; value: list of orphan tuples
    groups: dict[int, list[tuple]] = {}
    refusals: list[str] = []
    for name, sec, addr, size, data in NEW_ENTRIES:
        end = addr + size
        enclosing_idx = None
        for i, e in enumerate(parsed):
            if "addr" not in e:
                continue
            if e["section"] != sec or e["size"] == 0:
                continue
            if e["addr"] <= addr and end <= e["addr"] + e["size"]:
                enclosing_idx = i
                break
        if enclosing_idx is None:
            refusals.append(f"no enclosing blob: 0x{addr:08x} {name}")
            continue
        enclosing = parsed[enclosing_idx]
        if not is_placeholder(enclosing["name"]):
            refusals.append(
                f"enclosing blob {enclosing['name']} is not a placeholder: "
                f"refuse to split for 0x{addr:08x} {name}"
            )
            continue
        groups.setdefault(enclosing_idx, []).append((name, sec, addr, size, data))

    # Build new output by replacing each enclosing line with its split segments.
    inserted = 0
    new_lines: list[str] = []
    for idx, e in enumerate(parsed):
        if idx not in groups:
            new_lines.append(e["raw"])
            continue
        orphans = sorted(groups[idx], key=lambda x: x[2])
        seg_lines: list[str] = []
        cursor = e["addr"]
        blob_end = e["addr"] + e["size"]
        for name, sec, addr, size, data in orphans:
            if cursor < addr:
                seg_lines.append(format_lbl(sec, cursor, addr - cursor))
            seg_lines.append(format_entry(name, sec, addr, size, data))
            cursor = addr + size
            inserted += 1
        if cursor < blob_end:
            seg_lines.append(format_lbl(orphans[0][1], cursor, blob_end - cursor))
        new_lines.extend(seg_lines)
        print(f"split {e['name']} (size 0x{e['size']:x}) -> {len(seg_lines)} segments:")
        for sl in seg_lines:
            print(f"  {sl}")

    SYM_PATH.write_text("\n".join(new_lines) + "\n", encoding="utf-8")
    print(f"\ninserted: {inserted} orphan(s) across {len(groups)} enclosing blob(s)")
    if refusals:
        print(f"refused: {len(refusals)}")
        for r in refusals:
            print(f"  {r}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
