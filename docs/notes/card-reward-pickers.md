# card-reward-pickers

Source: Codex worker c16_u69_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 8 B.

c16_u69: missing-function check passed. Snapshot found[4] initializer loop removes an unwanted literal-pool copy and restores extab100. Explicit integer category instead of bool subscript avoids clrlslwi truncation, and direct repeated table field access restores post-allocation items load: snapshot91.70703->97.14844. Reward lookup row-pointer/column association and separate class/group temporaries give79.469025->93.9823. C88 entry-scope table root, round snapshot, independent item/row/column pointers and inline filter local player pointer give87.8995->96.28643. Validity normalization and GPR/frame residuals remain; preserve honest NM. DTK allows the EH-free8B getter prefix to be source-linked independently; full SHA1 exact.

## c17_u6_20261107
Source: Codex worker c17_u6_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1088 B.

c17_u6: CardOK must use an explicit if(IsCardValid()) return true; return false; body to preserve CW's integer normalization before caller branches. Direct returns/type casts collapse to byte tests or branchless masks. Snapshot direct HasAllItems(snaps[i]) removes an outer-local register rank; extracting inline CountOwners(snaps,item) reproduces the remaining owner-scan register partition. Snapshot1024B and getter64B become exact including EH and can be split as one contiguous Matching TU. Packed card scratch data is 0x45 bytes (existing PCB/Sci2 callers); this restores C88's 0xA0 frame but its register/root-coalescing residuals remain NonMatching.
