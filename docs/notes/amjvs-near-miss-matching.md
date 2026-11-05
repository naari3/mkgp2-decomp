# amjvs-near-miss-matching

Source: Codex worker c5_s25_amjvsnm2_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 228 B.

fn_8028AE64 (228B): extracting the semaphore-protected read into static inline ReadSwitch changed saved homes to target sem=r31 and ret/count=r30. Helper declarations u8* p before u8 bytes fixed remaining r6/r7 swap: .text 100%, source linked, full DOL SHA-1 OK. nm2 stays 99.55224% with node-pointer/channel r3/r5 inversion; explicit channel, direct indexing and split validation did not fix it. nm5 measured baseline was 96.58784% (assignment listed 97.25%); using st->count and manager-first loop increment fixed tail scheduling, 98.75%; initial clear still emits r3 base plus mr r31,r3. nm6 inline command helper and ternary experiments failed to reproduce nine target Boolean-result mr copies; retained original 95.70552%.
