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
