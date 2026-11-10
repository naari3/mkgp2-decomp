# KartFx dispatch native reconstruction

## Group B AuxStarBurst (2026-10-22)

The complete 432-byte function matches first-approach ordinary C++ with native
8-byte EH and 12-byte index. Keep unused r3/r5 ABI slots: payload arrives in r4
and enabled in r6. Signed active40 and unsigned timer80/previous81 have distinct
roles. Decrement the timer before the star dispatch; a zero timer does not clear
the new effect's variant. Preserve the mode2 gate after the first dispatch,
independent enabled/edge guards and all nested wing/horn loops. use_lmw_stmw on
reproduces the observed saved range without assembly. Local padded views claim
only observed fields, not a complete shared KartFx class. External callback
names and accesses were checked against actual target ASM, not live Ghidra.

Worker source-linked full DOL SHA1 and direct text/EH/index are exact; main
independently revalidates the same gates before acceptance. No opcode/manual-EH
patches, generated data ownership or fallback-based progress are involved.

## Group D RingBurst bounded draft (2026-10-22)

The complete812B target is retained as816B ordinary C++ NonMatching93.12808%
after three structural approaches: independent lazy aggregates/signed64
comparison, one frame aggregate, then separate arrays with persistent resource
base and ordinary signed comparison. Stack aggregate placement and the i<2
lowering still differ. External resource+588 angles and+5A8 colors/order remain
external; no far-span data ownership is inferred. Keep the full eight-spark,
24-ring and cup-dependent center paths, payload r4/enabled r6 ABI.

Main independently verifies native EH100%, index91.66667% (not worker's95%),
text93.12808%, actual original-object fallback and foreground full target SHA1.
Successful source linking alone does not prove a match: worker's source-linked
DOL hash differs. Genuine gain0. Retry needs new aggregate/normalization
provenance, not a fourth permutation. Main resolves the simultaneous B/D split
insertion by retaining D then B in address order, without rollback.


Group E StateByte 0x800C0398: complete1900-byte ordinary C++ NM99.89474%, native EH/index100%. Small external aggregates must be non-const in source: const causes CW to hoist their source loads across loops/calls, creating extra callee webs and frame0x50/r20-r31; non-const restores per-loop lhz/lbz copies, frame0x40/r22-r31, and exact GPR allocation. Pair51A4 plus signed byte51A6 copied into a local three-byte union preserves exact relocation identities without owning external data. Signed state bytes and per-loop copies of51A0/51A4+51A6/51A8 are load-bearing. Preserve unconditional3x2 persistent-chain maintenance, C9 cleanup1 for state mismatch versus2 for other invalidity, post-call payload/slot reloads, independent enabled guards, cooldown bytes94/B4/B5/BC/BD, ownerDC on B0/B8/C4. Motion flags low0x100000 overrides both temporary state bytes to4; signed Rand15%2 only for first boost variant. C0/C8 growth fields are distinct; C8 decay uses DOUBLE5380 and terminal C8!=zero uses fcmpu, retaining NaN behavior. Residual is ten f1/f2 identity instructions across800C0928..0948 and800C0A48..0A68; named clamp-bound approach did not move the FP webs. Three-approach budget exhausted. Full source-linked DOL hash4c5a7650b0f3c113e2108f0fedae856bbbb68c57 fails; final NonMatching original-object fallback full target SHA1 passes, genuine gain0.


Group A complete2492B matches with native EH8B/index12B. Natural u64 masks plus inline unsigned-byte normalization (if masked==0 result=0; else result=1) reproduce full diamonds. FAbs_FloatAsDouble is double-return ABI: a named double magnitude inside the enabled block is load-bearing for fcmpu cr0,f1,f0; direct inequality and reversed operands both emit fcmpu cr0,f0,f1 (99.98395%). External two-byte aggregate lbl_806DCF30 copies via lhz/sth to stack08/09 and remains foreign-owned. FlashIndex+1 uses signed promoted modulo4. Keep enabled-independent JumpDust/Dust/Slot60/fire/status/trail/burst, immediate Slot60 tick, captured wheel edge and per-iteration WheelSpark delay3 including allocation failure. Actual source-linked full DOL SHA1 exact; genuine C gain2492B/1fn.

## c15_u67_20261106
Source: Codex worker c15_u67_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 812 B.

Group D RingBurst unlocked: previous i<2 lowering residual was actually a reversed predicate. Target subfc/adde computes i>=2 (zero for first two sparks, one thereafter). Changing that expression reduces 816B to exact 812B and makes EH/index exact, leaving only stack offsets. For the independent locals, declaration order position, color, angles, order, base produces target color08/position14/order20/angles40/base60. Ordinary native C++ text/EH/index all100%; Matching source-linked full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No new bridge, split, data or compiler flags required.

## c17_u67_20261107
Source: Codex worker c17_u67_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u67 KartTrail 800BD900/1140B: byte-offset external blob loses object identity (missing color addi, scale index folds byte offset). Owning original pool 80329E20..8032A430 with four distinct 15-float character tables at A21C/A258/A294/A2D0 and five distinct Vec at A3F4/A400/A40C/A418/A424 restores full target instruction shape and all constants; text99.82456, extab/index/rodata100. Remaining ten rows are only pool/item r30/r31 swap. Inline item accessor and targeted earlier item declaration both byte-invariant; reverted. Retain NonMatching. Full fallback-linked DOL SHA-1 OK; native gain0. Do not repeat restrict color-copy/typed external index/accessor probes.

## c22_u101_20261109
Source: Codex worker c22_u101_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u101: merged KartFxExhaustRay source already defines Vec EffectVfx9_DriftSpark_Tick_rodata_8032A348 and RayColors lbl_8032A354, but symbols.txt retained A348 size24 and no A354. Correct A348 to C and add A354/18: seven identical-formatted relocation identity rows disappear; exhaust 99.92473->100 without source/instruction change. Trail remains99.82456 r30/r31 pool/item swap after six probes (typed item, whole-tick inline too large, init-switch inline, C++ frontend, full effect/item types, static pool linkage). Typed visible must retain signed read for extsb.; unsigned view produces two extra mismatches. All source probes reverted. Shared anchor and interleaved A294/A2D0/A348/A354/A418/A424 prevent contiguous pool partition for mechanism B. Full fallback-linked DOL SHA1 exact; zero native gain.
