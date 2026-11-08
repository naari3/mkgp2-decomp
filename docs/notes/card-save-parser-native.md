# card-save-parser-native

Source: Codex worker c18_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u89: CardSaveData_Parser 8008FA2C/1864B improves report97.023605->97.72103 (objdiff96.35408->97.07296), owned extab8/index12 both100. Only modeled declaration reorder in five existing blocks retained. Shared whole-function loop locals95.377686/1856B; shared indices+table with block-local cursor94.71245/1856B; reusable inline DecodeByteMatrix96.49356/1860B: all reverted due text/size/EH-index regression. Residual name/unlock/selection/counter homes, award scratch rotation and loop scheduling. Single-function TU cannot use mechanism B. No pool/symbol/flag/EH changes; fallback-linked SHA-1 OK, no native gain.

## c19_u64_20261107
Source: Codex worker c19_u64_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u64: Parser8008FA2C/1864B fresh objdiff97.07296->97.11588 (report97.72103->97.76395), EH8/index12 both100. Inline StoreCardRaceResult(u8* row,u8* flags,const u32* rank/wins/cleared/visited/award) fixes regular-race flags base r4->r5 and three byte stores; award progress r5->r4 still differs from targetr3, bool scratchr3 vsr4 remains. Direct ternary award regresses93.11373/1872B; selective alternating-role index sharing94.776825/1856B. Stride/return helper refinement invariant; early progress declarations without helper lose gain. Retain minimal inline store helper, honestNM; singleton TU cannot B split, no A changes. Full coordinator fallback SHA1exact; zero native gain.

## c21_u47_20261108
Source: Codex worker c21_u47_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u47: fresh direct objdiff97.11588 ->97.957085 (report97.76395 ->97.96137), unchanged1864B/EH8/index12 exact. H1 name cardName[i] replaces separate u16 cursor and restores cursor r29 (index remainsr30 vs targetr24),97.1588. H2 nested cup/grid/extra/counter comma-update order row+=stride,group++,fields++ restores pointer increment scheduling,97.957085; retained with H1. H3 inline u8 MergeCardFlag(flags,value) invariant,removed. Remaining award progress/scratch4/3 vs3/4, packed-byte scratch4 vs6,name/unlock/counter/selection saved homes and several preheader/cursor-copy schedules. Shared rodata80315378..803175A0 is already Card_VerifyChecksum-owned outside Parser claim; base addressing exact, no merge attempted. Singleton function cannot B split. Full coordinator fallback SHA1OK,zero native gain.
