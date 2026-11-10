# triforce-jvsio-unlock

Source: Codex worker c3_u4_jvsio_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 104 B.

JVS original static cmd and tx BSS use common-section base addressing. Converting storage to external globals changes BSS emission order; extracting request builders with extern state changes stbx into add+stb and register allocation. Nested aggregate extern state did not repair it; explicit local state pointers improved shape but did not reach exact. These broad split probes were reverted. The seven leaf getters use independent named storage relocations and split exactly. Missing fn_80283154 had only a declaration in the original source; report omission concealed its absence.

## c19_u94_20261107
Source: Codex worker c19_u94_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19: direct bank/node indexing instead of a cached JvsReq pointer raises decoder 89.023 -> 90.49032 and restores 0x48 frame/r20-r31 saved set. Separate checksum-status stores and error-queue branches raise it to 92.63317; separate typed SI packet pointer raises to 92.76029 (3292 vs target 3304 bytes). Callback j-before-i declaration improves 96.09375 -> 96.52344. Exact 49 functions remain exact; no promotion. Single external base with byte-offset tx cast still regresses common-BSS consumers; do not repeat this split probe.

## c20_u71_20261108
Source: Codex worker c20_u71_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20: moving callback failure-response loops into static inline jvsFailReplies raises fn_80282F54 96.52344 -> 98.00781 after removing unused outer i/j declarations (512B retained; cleanup restores target 0x20 frame). Explicit decoder packetLength/packetStatus/payload pointers raise fn_80283154 92.76029 -> 92.89346 (3296 vs target3304B). All 49 exact functions preserved. Detached suffix extraction with external state, local state pointer and inline init helper did not preserve exact functions; no split or native promotion.

## c21_u66_20261108
Source: Codex worker c21_u66_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21: fn_80283154 late invalid-response else (success branch encloses reply-pointer setup and command dispatch) raises92.89346 ->94.94552, restoring common BSS base r28 and outer i r31. Source still3296B versus target3304B. All50 other exact functions preserved. Capacity helper, byte-put helper, nested event helper and callback inline local ordering did not improve. Separate file-static field storage regresses common-anchor/SDA consumers and was reverted. JvsCmd req is semantically three banks (bank advance wraps at2), currently represented as two banks plus padding; [3][16] has identical code/layout, but shared header restored in this batch. TU remains NonMatching, full service SHA-1 OK.

## c21_p32_20261108
Source: Codex worker c21_p32_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p32: baseline has 53/53 definitions; .bss range already OWN-SELF. Cached int command reused for default dispatch raises fn_80283154 94.94552 ->95.06659 (source3292B,target3304B). static inline BOOL jvsTxHasSpace(u16 length) { return tx.len < 0x7F-length; } raises fn_802854B0 95.918365 ->99.77551: only addi r4,base,0x50f0 and addi r8,base,0x80 exchange positions. Pointer/value helper arguments and named length views invariant; int length parameter restores the worse schedule. Callback unsigned counters regress and long counters invariant. All50 exact functions preserved; no native promotion. External state preserves only four small functions and regresses others; no split retained. Coordinator full build SHA-1 OK.

## c22_u18_20261109
Source: Codex worker c22_u18_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u18: BSS already OWN-SELF and all 53 function symbols defined. Moving failed-command reads from before the response[1] branch into each branch raises fn_80283154 95.06659 ->96.44431%; target-like branch-specific queue scheduling returns. Source is now3308B versus target3304B. Consistent packet-pointer use and deferred packet-member addresses regress. Checksum inline scope/result-parameter/local-result probes do not improve callback98.00781%. Sender capacity/body/getter/explicit-return/header-preparation inlines do not improve99.77551%; the same two address calculations remain the baseline residual. Narrow static command-buffer/state split preserves BSS byte size but regresses exact consumers; reverted. All50 exact functions preserved; no native promotion. Coordinator SHA-1 OK.

## c23_u36_20261109
Source: Codex worker c23_u36_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23: BSS already OWN-SELF, all 53 function symbols defined. Cache failed reply status as u32 to preserve original unsigned byte comparison without an extra clrlwi/reload; declare bank before node. Decoder becomes exact 3304B. Its two compiler jump tables are unowned .data 804F5630..804F56E4 (0xB4 bytes); claim them, leaving the existing 4-byte gap to 804F56E8 unowned. Correct case source order is 0x25 before 0x24, proven by the only two unequal table relocation addends. Final .data/.bss 100%, decoder96.577484 vs96.44431 baseline, TU.text99.03812. Text-only attempt_12 scores96.783295 but has case24/25 table targets reversed; saved as draft, not selected. All50 existing exact functions preserved. Callback index reuse/direct scope/per-node inline and sender remaining-capacity/cached-length/slot-reservation probes regress; see HANDOFF hypotheses. TU remains NonMatching and no new native functions. Two coordinator builds SHA-1 OK.

## c25_u11_20261110
Source: Codex worker c25_u11_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1124 B.

c25_u11: fn_80282F54 now exactly100%/512B. Rule inline-local-to-outer-ref (regalloc_patterns22): jvsFailReplies takes (u8 res,int *nodeIndex,int *commandIndex); remove its inline-owned i/j, declare int nodeIndex and commandIndex after caller checksumIndex and pass their addresses. Dereference them in the existing loops. Retained artifact build/w/c25/attempt_2_caller_indices.c; 128 instructions and zero diffs. All50 formerly exact functions and all other section/function scores unchanged; TU stays NonMatching. Full coordinator SHA-1 OK. Parser: further independent j counters97.51574, whole default inline93.50726, packet getter97.92736; revert all. Sender stream-pointer capacity helper invariant99.77551. Reverting n3 case order to25-before24 fixes .data100 but lowers parser97.6368, so left out. Existing pooled BSS ownership prevents a verified native split.

## c26_u9_20261110
Source: Codex worker c26_u9_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u9: remove packetLength/packetStatus/payload pointer locals and index canonical packet->length and packet->payload directly. Parser97.92736->98.35714 (3300B vs3304), all51 exact functions unchanged. Source raw-byte equivalent emits identical code. First-read-then-pointer and direct-first pointer-view alternatives98.00726/97.99032. Length object boundary split and narrow-cast sender probes regress; sender left99.77551. Final two exact functions extracted with canonical extern state regress80.37037/90.84906, reverted. No native promotion; coordinator SHA-1 OK. GC/1.2.5n stand-in trace caution applies.
