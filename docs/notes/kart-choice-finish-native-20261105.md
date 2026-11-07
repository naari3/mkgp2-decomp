# KartChoiceFinish / item-select choice (0x8023AA0C..0x8023C8B0) — 2026-11-05

Source: Codex worker cxc_u3_kartchoice23a_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, SHA-1 OK, actual main.elf ranges).

## Native (source-linked): game/KartChoiceFinish.cpp, 5 fn / 1308 B
- fn_8023C394, fn_8023C3C8, fn_8023C5A4, fn_8023C6A8, fn_8023C878: inline setters remove extra constant loads and fix register lifetimes; text 100 %, owned EH payloads exact.
- Target places fn_8023C878's extab entry first → per-TU entry in tools/extab_order.json is required (added). Remaining object-level extab/extabindex difference = two compiler-emitted weak destructor entries discarded at link; the coordinator flipped the TU to Matching and verified by full build + DOL SHA-1 + linked ranges.

## Honest NonMatching drafts
- fn_8023AA0C 98.12 % (game/ItemSelectChoiceStep.cpp): column-load CSE / global-pointer register difference; occupancy inline boundary helped, item getter boundary did not.
- fn_8023AC14 94.59 % (game/ItemSelectChoiceUpdate.cpp): sprite-node output must be 0x30 bytes; flat table / Color helper variant worse.
- fn_8023B1A8 98.42 % (game/ItemSelectChoiceInit.cpp): canonical TextManager automatic DESTROYLOCAL; remaining global-pointer setup differences.

## c15_u35_20261106
Source: Codex worker c15_u35_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u35: fn_8023B1A8 fresh98.42391% (372B vs368). Initializing typed rowItems in outer for header restores global lis order, improves98.75%, preserves EH section percentages. Residual address setup destinations and extra mr r29,r0 remain; owned EH PC start D8 vs D4. Natural inline preload loop helper gives368B but changes self/loop GPR homes and player addressing (91.304344%); flat row cursor gives same98.75%. Retain small source improvement, singleton staysNonMatching; no native gain.

## c17_u53_20261107
Source: Codex worker c17_u53_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u53: fn_8023AC14 fresh94.593834 ->97.85714% (1428 B) by owning real shared rodata 803DC0C0..803DC2C0 as palette/default/item/X/Y/resource tables, plus target-derived cursor/xs/ys/i declarations. Actual arrays restore target base+C0 and lwzx; rodata512/EH8/index12 all100. Use SINGLETON_INSTANCE(g_pInputState). ChoiceItem(self) is invariant; alpha OR overlay worsens96.955185/1432 B, restore addition. Resource/display helper extraction rematerializes player addresses and worsens94.42577/1416 B. Residual column-load CSE, player pointer addi->r0->mr, resource r27/r28 coalesce, alpha li/rlwimi vs clrlwi/subi. Singleton remains NM; no B cut; full fallback-linked DOL SHA1 exact, native gain0.
