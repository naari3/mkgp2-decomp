# Compiler-version audit (2026-11-08)

How it was done: every NonMatching TU in configure.py (231) was compiled
unchanged under GC/1.2.5n, 1.3, 1.3.2, 2.0, 2.6 and 2.7, with the TU's
normal postprocess steps and renames, and each function was scored with
objdiff. A second pass looked for code fingerprints that only one compiler
family produces (see "Fingerprints" below).

Result: very few TUs gain from a compiler change alone. Most near-misses
are source-shape problems, not compiler problems.

## Landed

| TU | change | effect |
|---|---|---|
| game/fn_801BAA88 | GC/1.3.2 -> GC/2.6 + natural `0xFFFFFF00 \| al` colour | fn_801BDEB4 matched (ae58acb) |
| game/PhysicsState_WallCollisionCheck | GC/1.3.2 -> GC/2.6 | 80.1 -> 96.0 (f3bd68e) |

## Suggestions for onmokoworks-claimed TUs (not touched)

These are TUs under an onmokoworks unit-claim. Nothing was pushed for
them; the user relays.

| TU | claim | suggestion | measured |
|---|---|---|---|
| game/clItemBoxManager_nm1 | #2963 | GC/2.0 | DoublyLinkedList_EraseRange 95.2 -> 100, nothing else changes |
| game/ranking_display | #2880 | GC/1.3 | +2.0 summed fuzzy, no function lost |
| game/fn_8023A148 | #2801 | GC/2.6, `unsigned char alpha = value;`, colour local declared before the title local | 99.72; fixes colour/title registers at the first call site |
| game/clFlowCourse | #2778 | li -0x100 fingerprint: try GC/2.6 + `0xFFFFFF00 \| (unsigned char)a` | not measured with source change |
| game/clFlowCourse_Update | #2756 | same as above | not measured |
| game/resultscene/resultscene | #2764 | same as above | not measured |
| game/ItemSelectChoiceUpdate | #2836 | same as above | not measured |
| game/Menu801F0CC0 | #2829 | same as above | not measured |
| game/GpPleaseInit (clFlowGpPlease_Init) | #2773 | same as above | not measured |

"Same as above" = the target has `li rN, -0x100; rlwimi rN, rX, 0, 24, 31`
with rN != r0. In every matched case this is a GC/2.x TU written with the
plain `|` form (docs/regalloc_patterns.md section 11). GC/1.3.2 with
`__rlwimi` gets the instructions right but puts the constant in r0.
Check that every already-matched function in the TU stays 100 after the
flip.

## Tried, no gain

- game/clFlowRound (clFlowRound_Update WIP): 98.42 under 1.3.2, 2.0, 2.6
  and 2.7 alike. The self/pool r26/r31 swap is not a compiler issue.
- game/ItemGridState_Init: 99.47 on 1.3.2/2.0/2.6, worse on 1.3.
- game/JumpDistanceMode_Update, clFlowKart WIPs: no change.

## Matching TUs whose asm functions show the GC/2.x fingerprint

- game/RaceHud_80147470 (unclaimed at writing): asm fn_80147900,
  fn_80147AF4, fn_80147CE8, fn_80148A44 contain the li -0x100 colour.
  The TU's C functions all stay 100 on GC/2.6, so convert those asm
  functions to C with mw_version="GC/2.6".

## Fingerprints

- `li rN(!=r0), -0x100` + `rlwimi rN, ..., 0, 24, 31`: GC/2.x.
- `stmw`/`lmw` in a TU without `-use_lmw_stmw on` was only ever a
  `#pragma` effect (false positives): ItemGridState_Init, THPDec and the
  onmokoworks TUs KartController_Update, ShadowAreaMgr, bitread
  fn_8018B31C, fn_801B4548, triforce/jvsio.
