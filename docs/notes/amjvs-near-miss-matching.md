# amjvs-near-miss-matching

Source: Codex worker c5_s25_amjvsnm2_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 228 B.

fn_8028AE64 (228B): extracting the semaphore-protected read into static inline ReadSwitch changed saved homes to target sem=r31 and ret/count=r30. Helper declarations u8* p before u8 bytes fixed remaining r6/r7 swap: .text 100%, source linked, full DOL SHA-1 OK. nm2 stays 99.55224% with node-pointer/channel r3/r5 inversion; explicit channel, direct indexing and split validation did not fix it. nm5 measured baseline was 96.58784% (assignment listed 97.25%); using st->count and manager-first loop increment fixed tail scheduling, 98.75%; initial clear still emits r3 base plus mr r31,r3. nm6 inline command helper and ternary experiments failed to reproduce nine target Boolean-result mr copies; retained original 95.70552%.

## c12_u8_20261106
Source: Codex worker c12_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1248 B.

c12_u8: fn_8028BAD0 1248B: NEXT_STATE state++ before timer clear, and case9 flags assignment before timer clear, resolve pure scratch-register coloring from 99.551285 to 100%. Inline NEXT_STATE alone unchanged; inline with explicit state local worsens to 99.42308. MWCC emits these tentative sbss definitions in reverse order: define amjvs_nm7_bss_806D1E3C before amjvs_nm7_bss_806D1E38 to obtain target Node offset0 / Timer offset4. Objdiff reports sbss 100% even with these zero-content symbol locations swapped, so inspect symbol addresses and full-link SHA. Matching flag, source link, full DOL SHA-1 verified.

## c18_u11_20261107
Source: Codex worker c18_u11_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 592 B.

c18_u11_20261107: fn_8028B180 (592 B) promoted from 98.75% to 100%. Pointer-walking initial clear is byte-identical to old indexed source, so does not remove extra mr r31,r3. Factoring the entire semaphore-protected operation into static inline UpdateErrorStats(BOOL), with fn_8028B180 as a passthrough wrapper, removes the initial clear base-register copy. The helper initially gives m=r29, sem=r30, n=r31; swapping only m/n declaration positions produces target m=r31, sem=r30, n=r29. Body otherwise unchanged, no new flags/data/EH. Matching flag, source main.elf input, symbol 0x8028B180 size 592, full DOL SHA-1 verified.

## c18_u116_20261107
Source: Codex worker c18_u116_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u116: fn_8028B48C BOOL r -> u8 r improves 95.70552 to 96.809814 and source text 1268 to exact target 1304 bytes. Nine target mr r27,r26 positions instead emit clrlwi r26,r26,24; accumulator/manager/node/index saved homes still rotate. Entire-function inline helper exceeds inline budget (32-byte wrapper); explicit reuse of node for result and loop index is invariant at baseline. No native gain; retain NonMatching one-line draft.

## c19_u154_20261107
Source: Codex worker c19_u154_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1304 B.

c19_u154: fn_8028B48C promoted 96.809814% to 100%, 1304 B. Reorder function locals to nodes, m, sem, ok, i, r: 98.34356%, every saved-register home matches, only nine clrlwi r27,r26,24 vs mr r27,r26 remain. THEN restore u8 r to BOOL r: exact 100%; with the old declaration order a full-width temporary coalesces away the nine copies. No helper/pragma/flags/data/EH changes; Matching flip, actual main.elf source input and symbol range verified; coordinator full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK. C++ bool r (94.00307%), u32 r with original declarations (95.70552%), C++ bool ok + BOOL r (91.93252%) were rejected.

## c19_u258_20261107
Source: Codex worker c19_u258_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 208 B.

c19_u258: nm3 baseline AC1C is already100% after upstream u32-channel fix, contrary to stale assignment93.71. Mechanism B moves exact208B reader verbatim into Matching triforce/amjvs_analog_read.c; full source-linked DOL SHA1 OK. AAC0 retains96.14942% /352B vs348: signed count95.574715 (wrong cmpwi), postdecrement-test invariant96.14942, inline CopyAnalog95.804596 (extra pointer move). All rejected. Residual unsigned ble vsbeq, extra count mr, count/src/dst register rotation. No EH/shared pool.

## c21_u169_20261108
Source: Codex worker c21_u169_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u169: AAC0 improved 96.14942%/352B to99.94253%/348B with the entire operation in static inline ReadAnalog and a passthrough public wrapper; p declared before n fixes r5/r6. Exactly one remaining instruction: target 8028AB6C ble versus source+AC beq, following identical cmplwi r5,0. sbss100, no EH/pool issue. Indexed copy60.770115/464B; guarded do71.54023/252B, guarded for98.793106/352B; u8 count55.402298/252B; GC2.6 invariant99.94253; n>=1 gives99.93104 with cmplwi1/blt. Retained best natural C in NonMatching TU; no config/split changes or native gain.
