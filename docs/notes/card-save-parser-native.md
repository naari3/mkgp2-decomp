# card-save-parser-native

Source: Codex worker c18_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u89: CardSaveData_Parser 8008FA2C/1864B improves report97.023605->97.72103 (objdiff96.35408->97.07296), owned extab8/index12 both100. Only modeled declaration reorder in five existing blocks retained. Shared whole-function loop locals95.377686/1856B; shared indices+table with block-local cursor94.71245/1856B; reusable inline DecodeByteMatrix96.49356/1860B: all reverted due text/size/EH-index regression. Residual name/unlock/selection/counter homes, award scratch rotation and loop scheduling. Single-function TU cannot use mechanism B. No pool/symbol/flag/EH changes; fallback-linked SHA-1 OK, no native gain.

## c19_u64_20261107
Source: Codex worker c19_u64_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u64: Parser8008FA2C/1864B fresh objdiff97.07296->97.11588 (report97.72103->97.76395), EH8/index12 both100. Inline StoreCardRaceResult(u8* row,u8* flags,const u32* rank/wins/cleared/visited/award) fixes regular-race flags base r4->r5 and three byte stores; award progress r5->r4 still differs from targetr3, bool scratchr3 vsr4 remains. Direct ternary award regresses93.11373/1872B; selective alternating-role index sharing94.776825/1856B. Stride/return helper refinement invariant; early progress declarations without helper lose gain. Retain minimal inline store helper, honestNM; singleton TU cannot B split, no A changes. Full coordinator fallback SHA1exact; zero native gain.

## c21_u47_20261108
Source: Codex worker c21_u47_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u47: fresh direct objdiff97.11588 ->97.957085 (report97.76395 ->97.96137), unchanged1864B/EH8/index12 exact. H1 name cardName[i] replaces separate u16 cursor and restores cursor r29 (index remainsr30 vs targetr24),97.1588. H2 nested cup/grid/extra/counter comma-update order row+=stride,group++,fields++ restores pointer increment scheduling,97.957085; retained with H1. H3 inline u8 MergeCardFlag(flags,value) invariant,removed. Remaining award progress/scratch4/3 vs3/4, packed-byte scratch4 vs6,name/unlock/counter/selection saved homes and several preheader/cursor-copy schedules. Shared rodata80315378..803175A0 is already Card_VerifyChecksum-owned outside Parser claim; base addressing exact, no merge attempted. Singleton function cannot B split. Full coordinator fallback SHA1OK,zero native gain.

## c23_u2_20261109
Source: Codex worker c23_u2_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u2: Parser8008FA2C/1864B direct97.957085->97.97854, report97.96137->97.982834, EH8/index12both100. Natural CardUnlockRuleSlot(const CardUnlockRule*) getter fixes slot/shift r3/r0 to targetr0/r3 and reproduces assigned shapesweep Id_i diff exactly; named slot temp/full grid-index getter invariant. int/long progress probes byte-invariant. Typed regular/extended race outputs97.97425 (anchor shifts only), full prefix view96.251076/1868B/index91.66667; reverted. Pool already VerifyChecksum-owned80315378..803175A0, contiguous merge spans intervening Matching CardUnpackV1. No claim-crossing edits. Three families exhausted; singleton honestNM, full coordinator fallbackSHA1OK,zero native gain.

## c25_u22_20261110
Source: Codex worker c25_u22_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 10180 B.

c25_u22 (base5949f8a5): merged Parser unchanged99.0751%, v1 unchanged100%; Checksum96.375885->96.489365 by j=0 before expected=lbl_806D34A4. Inline accumulator ReadCardChecksum fixes raw/sum swap but CSE merges checksum0 and sum0:560B vs564B, score99.184395 yet extabindex97.22222; rejected. Whole-body inline88.05674; tail/signature inline96.38298; explicit Parser inline load names and distinct function-scope locals invariant, name-loop inline99.03219. Pool OWN-SELF already merged; no B split because both flanking nonexact functions use the same anchor pool. Full coordinator SHA1OK; zero native gain. Compiler rules: coalescenodes named/temp restriction, named/FE temp ordering, constant CSE.

## c26_u15_20261110
Source: Codex worker c26_u15_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u15: Parser99.0751->99.58154,1864B; initialize grid i before cursor with for(i=0,cursor=row;...), then counter block group declared before fields and for(group=0,fields=lbl_806D349C;...). Both supplied constant-order runs fixed, counter group/fields targetr23/r24. Other functions unchanged; data/EH100. Progress inline return/constant-parameter forms invariant; sharing outer fields across grid/extra/counter regresses99.28111. Checksum signed inline accumulator reaches99.07801 but560B (target564), zeroCSE still merges checksum0/sum0; reverted. Full coordinator fallback DOL SHA1OK,zero native gain. Rules: decl-order, regalloc_patterns7 initialization order; no need to invoke dead-truncation scheduling hypothesis for grid.

## c28_u5_20261111
Source: Codex worker c28_u5_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c28_u5: Parser99.58154->99.80687,1864B/EH/data unchanged. Independent block unlockIndex gives99.64592. Function declarations cupCursor,cupRow,cupFields,cupGroup,nameIndex,fields,cupIndex,i plus late final group fix all saved homes. Remaining18 instructions are only regular/extended progress r4 and bool load scratch r3 vs target3/4. u32/unsigned-long explicit flag load locals and shared regular/extended result-store inline invariant. Checksum accumulator with initial sum argument emits568B and copies despite raw/sum home fix; reverted. Full fallback DOL SHA1OK; zero native gain.
