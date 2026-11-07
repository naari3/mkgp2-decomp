# pcbcomm-phase5-c15-20261106

Source: Codex worker c15_u41_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

PCB phase5: caller-owned unsigned char idle updated by PublishValue(float,char*,unsigned char*) removes nested helper duplicate idle=1, reduces text912 to target908, improves fresh objdiff98.09692 to98.20705; EH8/index12 become100. Publication r4/r5 swap remains alongside phase-base coalescing and hostRole/output r5/r6 residuals. Passing initial idle by value is unchanged; inline phase-base/first+2 getters are unchanged. Retained NonMatching; full DOL SHA-1 OK with target fallback, native gain0.

## c19_u151_20261107
Source: Codex worker c19_u151_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u151: flatten both nested publication helpers into PCBComm_UpdateSyncPhase5, use function-scope i for publication, and declare cursor/output inside a block after timer snapshot. 98.20705 ->98.537445, source908B/EH8/index12 exact sizes, EH100. Timer-publication +0x290..end instructions now exact. Explicit timer pointer and early cursor/out declarations hoist table loads and regress94.78854 (source912); reject. HostRole-before-out declarations and per-slot PublishHostRole helper are instruction-invariant. Remaining phase SDA reload versus mr/scheduling at+0x90..A4 and hostRole/output r6/r5 vs targetr5/r6; timestamp low relocation alias same address. No singleton or pool rescue; one function prevents B. Remains NonMatching; coordinator full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65, zero native gain. Relevant previous c18 PCB handoff is u37.
