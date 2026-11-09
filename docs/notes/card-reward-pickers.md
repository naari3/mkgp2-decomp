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

## c21_p36_20261108
Source: Codex worker c21_p36_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

c21_p36: pool ownership was already OWN-SELF and real arrays were present. C88 reference-formal helper96.95477, same-width long output index97.231155 invariant, explicit pointer cursors96.92965; all reverted to baseline97.231155 (792/796B). DTK permits splitting at80209C88 with matching8B extab/12B index per function. AC4 remains100 with extern lbl_804EC568[32] while all tables and32B initializer rodata move verbatim to NonMatching anon_80209330_nm2_tail.cpp. Mechanism B unlocks AC4 452B; source-link edge checked; full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK. C88 residual remains independent filter-pd copy/register partition.

## c21_u160_20261108
Source: Codex worker c21_u160_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u160 fn_80209338: baseline94.38389/848B ->97.44076/844B, extab/index100. New MakeShuffledItems helper ONLY for 65-item fallback, with allocation and shuffle body at same inline depth, removes extra second allocation copy and restores inner GPR homes (97.18009). pd declared before result fixes outer r31/r30 (97.44076). Returning a chosen/marked random index from TakeUnused is instruction-invariant. Residual only both shuffle tails: source shifts index into r0 before flag mark (constant r4), target marks with r0 then shifts; compare/lwzx schedule differs. Classifier 76->10 diff rows; no saved-reg residual. Keep improved honest NonMatching. One-function TU cannot mechanism B; no pool-base residual or claim-authorized neighbour merge. Full fallback DOL SHA1 exact; native gain0.

## c22_u127_20261109
Source: Codex worker c22_u127_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 844 B.

c22_u127 fn_80209338: semantics/type correction closes the 10-row r0/reg+sched shuffle-tail residual. The real table is int lbl_804EC5E8[65], defined in anon_80209330_nm2_tail.cpp; the old shared header declared extern const and Shuffle/MakeShuffledItems used const int*. New TU-private CommonRewardPickerPrivate.h declares the actual mutable array, and TU-local Shuffle plus MakeShuffledItems take int*. Both tails now emit target li r0,1; flag stbx; slwi; cmpwi/lwzx schedule. 97.44076 ->100%, 844B, extab/index100. Shared header unchanged; no pool-range, EH bridge/order or compiler-flag changes. Existing TU flipped Matching, source-link edge and ELF 80209338/844B verified; full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Native gain1/844B.

## c23_u130_20261109
Source: Codex worker c23_u130_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1460 B.

c23_u130: fn_80209C88 direct baseline97.231155/792B ->100/796B. Pool ownership already correct. Moving FillSpecialItems verbatim into caller-local scope restores independent filter-player copy and target size/EH (99.447235). Swap filter pd and i declarations to correct saved r23/r28 (99.64824); move result/pd initialization before list[4] initializer to correct shared player-address and list-copy scratch homes (100%). Mutable tbl/Shuffle view invariant; nested eligibility predicates add bool materialization and regress. Existing TU promoted Matching; all text/data/rodata/extab/index100, source object in main.elf, symbol80209C88/796B exact; full coordinator DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK. Native gain1/796B. No range, bridge, flag-recipe or shared-header edits.
