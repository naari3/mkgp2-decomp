# card-reward-pickers

Source: Codex worker c16_u69_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 8 B.

c16_u69: missing-function check passed. Snapshot found[4] initializer loop removes an unwanted literal-pool copy and restores extab100. Explicit integer category instead of bool subscript avoids clrlslwi truncation, and direct repeated table field access restores post-allocation items load: snapshot91.70703->97.14844. Reward lookup row-pointer/column association and separate class/group temporaries give79.469025->93.9823. C88 entry-scope table root, round snapshot, independent item/row/column pointers and inline filter local player pointer give87.8995->96.28643. Validity normalization and GPR/frame residuals remain; preserve honest NM. DTK allows the EH-free8B getter prefix to be source-linked independently; full SHA1 exact.

## c17_u6_20261107
Source: Codex worker c17_u6_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1088 B.

c17_u6: CardOK must use an explicit if(IsCardValid()) return true; return false; body to preserve CW's integer normalization before caller branches. Direct returns/type casts collapse to byte tests or branchless masks. Snapshot direct HasAllItems(snaps[i]) removes an outer-local register rank; extracting inline CountOwners(snaps,item) reproduces the remaining owner-scan register partition. Snapshot1024B and getter64B become exact including EH and can be split as one contiguous Matching TU. Packed card scratch data is 0x45 bytes (existing PCB/Sci2 callers); this restores C88's 0xA0 frame but its register/root-coalescing residuals remain NonMatching.

## c18_u5_20261107
Source: Codex worker c18_u5_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u5: direct baseline objdiff AC4 97.20354 / C88 96.31658. Owning .data 804EC568..804EC754 as separate real arrays plus compiler initializer .rodata 803C2820..803C2840 gives .data/.rodata100 and C88 96.47739 without reducing AC4. Data ownership restores the zero-offset table addi and removes external-pool entry mr. C88 still lacks independent filter-pd copy (target r8->r23 at 80209D68), is 792 vs796 bytes, and coalesces base/rows/table into r31. Passing filter pd as a parameter rematerializes its address; ItemList return helper adds stack stores/frame. AC4 whole helper/query helper/switch helper do not solve a/b/row cycle; switch helper with expression row sinks row past first call. Keep NonMatching; full fallback DOL SHA1 exact, native gain0.

## c19_u160_20261107
Source: Codex worker c19_u160_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u160: exact production objdiff baseline AC4 97.20354 / C88 96.47739. C88 FillSpecialItems reverse target-order declarations (i,cols,k,rows,items,pd) and pd/items/cols/rows initializations before k=0 improve C88 to97.00503, text97.07692; data/rodata/extab100, index95.83333 unchanged. Pool/rows=r25, items=r24, outer pd=r29, result=r30, loop/table=r28 and shuffle flags=r31 now exact. Remaining filter pd=r26 vsr23 missing mr, column cursor=r31 vsr27, output offset=r27 vsr26 and setup schedule; still792 vs796 B. PickUnowned final-tail helper95.29146; reference-output table selection96.45226 reverted. AC4 unsigned row/named selector invariant97.20354; validation-outside reversed-parameter select helper96.76106; normalize parameter preserving one-based local89.56637, all reverted. Neither function exact, no B subset; unchanged NonMatching flag. Coordinator full fallback DOL SHA1 exact, no native gain.
