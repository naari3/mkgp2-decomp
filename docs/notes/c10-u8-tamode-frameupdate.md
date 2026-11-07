# c10-u8-tamode-frameupdate

Source: Codex worker c10_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

TaMode_FrameUpdate 800A2B90 native draft: explicit reverse/normal table bases with cached cup/round improves 98.55361 -> 98.70979. accel = ((float *)lbl_806D1388)[lbl_806D1394 * 4] prevents struct-pointer CSE and matches target lfsx plus following ghost-frame load scheduling (98.996506). Function-scope coins declared before started puts coins at target r27 (99.013985), but started moves to r28 instead of target r26. Residual r3 vs r0 zero flag store, started register identity, and record table base/index association/load scheduling remain; native3428 vs target3432. Three approaches exhausted; retained NonMatching. EH8 exact, index12 91.66667 due text length. Full fallback-linked DOL SHA passes; native gain0. Do not repeat these same hypotheses blindly.

## c17_u89_20261107
Source: Codex worker c17_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u89: fresh baseline99.013985 (3428B). SelectTaRecord(battle,cup,reverse,round) inline selector regresses98.80536; generic typed LookupTaRecord(table,cup,round) invariant99.013985. Byte-strided lookup summing cup*sizeof(row)+round*sizeof(record) restores3432B/extabindex100 but regresses98.81119: backend still distributes base+constant and does not preserve target base+540 followed by summed offset. All probes reverted. Six started r28/r26 and two zero r3/r0 differences remain. Canonical SINGLETON_INSTANCE getters are instruction-identical. Singleton TU prevents B; no native gain.
