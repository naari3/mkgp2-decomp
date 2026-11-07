# amjvs-near-miss-matching

Source: Codex worker c5_s25_amjvsnm2_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 228 B.

fn_8028AE64 (228B): extracting the semaphore-protected read into static inline ReadSwitch changed saved homes to target sem=r31 and ret/count=r30. Helper declarations u8* p before u8 bytes fixed remaining r6/r7 swap: .text 100%, source linked, full DOL SHA-1 OK. nm2 stays 99.55224% with node-pointer/channel r3/r5 inversion; explicit channel, direct indexing and split validation did not fix it. nm5 measured baseline was 96.58784% (assignment listed 97.25%); using st->count and manager-first loop increment fixed tail scheduling, 98.75%; initial clear still emits r3 base plus mr r31,r3. nm6 inline command helper and ternary experiments failed to reproduce nine target Boolean-result mr copies; retained original 95.70552%.

## c12_u8_20261106
Source: Codex worker c12_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1248 B.

c12_u8: fn_8028BAD0 1248B: NEXT_STATE state++ before timer clear, and case9 flags assignment before timer clear, resolve pure scratch-register coloring from 99.551285 to 100%. Inline NEXT_STATE alone unchanged; inline with explicit state local worsens to 99.42308. MWCC emits these tentative sbss definitions in reverse order: define lbl_806D1E3C before lbl_806D1E38 to obtain target Node offset0 / Timer offset4. Objdiff reports sbss 100% even with these zero-content symbol locations swapped, so inspect symbol addresses and full-link SHA. Matching flag, source link, full DOL SHA-1 verified.

## c18_u11_20261107
Source: Codex worker c18_u11_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 592 B.

c18_u11_20261107: fn_8028B180 (592 B) promoted from 98.75% to 100%. Pointer-walking initial clear is byte-identical to old indexed source, so does not remove extra mr r31,r3. Factoring the entire semaphore-protected operation into static inline UpdateErrorStats(BOOL), with fn_8028B180 as a passthrough wrapper, removes the initial clear base-register copy. The helper initially gives m=r29, sem=r30, n=r31; swapping only m/n declaration positions produces target m=r31, sem=r30, n=r29. Body otherwise unchanged, no new flags/data/EH. Matching flag, source main.elf input, symbol 0x8028B180 size 592, full DOL SHA-1 verified.

## c18_u116_20261107
Source: Codex worker c18_u116_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u116: fn_8028B48C BOOL r -> u8 r improves 95.70552 to 96.809814 and source text 1268 to exact target 1304 bytes. Nine target mr r27,r26 positions instead emit clrlwi r26,r26,24; accumulator/manager/node/index saved homes still rotate. Entire-function inline helper exceeds inline budget (32-byte wrapper); explicit reuse of node for result and loop index is invariant at baseline. No native gain; retain NonMatching one-line draft.
