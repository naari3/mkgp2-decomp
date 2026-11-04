# KartChoiceFinish / item-select choice (0x8023AA0C..0x8023C8B0) — 2026-11-05

Source: Codex worker cxc_u3_kartchoice23a_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, SHA-1 OK, actual main.elf ranges).

## Native (source-linked): game/KartChoiceFinish.cpp, 5 fn / 1308 B
- fn_8023C394, fn_8023C3C8, fn_8023C5A4, fn_8023C6A8, fn_8023C878: inline setters remove extra constant loads and fix register lifetimes; text 100 %, owned EH payloads exact.
- Target places fn_8023C878's extab entry first → per-TU entry in tools/extab_order.json is required (added). Remaining object-level extab/extabindex difference = two compiler-emitted weak destructor entries discarded at link; the coordinator flipped the TU to Matching and verified by full build + DOL SHA-1 + linked ranges.

## Honest NonMatching drafts
- fn_8023AA0C 98.12 % (game/ItemSelectChoiceStep.cpp): column-load CSE / global-pointer register difference; occupancy inline boundary helped, item getter boundary did not.
- fn_8023AC14 94.59 % (game/ItemSelectChoiceUpdate.cpp): sprite-node output must be 0x30 bytes; flat table / Color helper variant worse.
- fn_8023B1A8 98.42 % (game/ItemSelectChoiceInit.cpp): canonical TextManager automatic DESTROYLOCAL; remaining global-pointer setup differences.
