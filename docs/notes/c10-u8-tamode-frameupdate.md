# c10-u8-tamode-frameupdate

Source: Codex worker c10_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

TaMode_FrameUpdate 800A2B90 native draft: explicit reverse/normal table bases with cached cup/round improves 98.55361 -> 98.70979. accel = ((float *)lbl_806D1388)[lbl_806D1394 * 4] prevents struct-pointer CSE and matches target lfsx plus following ghost-frame load scheduling (98.996506). Function-scope coins declared before started puts coins at target r27 (99.013985), but started moves to r28 instead of target r26. Residual r3 vs r0 zero flag store, started register identity, and record table base/index association/load scheduling remain; native3428 vs target3432. Three approaches exhausted; retained NonMatching. EH8 exact, index12 91.66667 due text length. Full fallback-linked DOL SHA passes; native gain0. Do not repeat these same hypotheses blindly.

## c17_u89_20261107
Source: Codex worker c17_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u89: fresh baseline99.013985 (3428B). SelectTaRecord(battle,cup,reverse,round) inline selector regresses98.80536; generic typed LookupTaRecord(table,cup,round) invariant99.013985. Byte-strided lookup summing cup*sizeof(row)+round*sizeof(record) restores3432B/extabindex100 but regresses98.81119: backend still distributes base+constant and does not preserve target base+540 followed by summed offset. All probes reverted. Six started r28/r26 and two zero r3/r0 differences remain. Canonical SINGLETON_INSTANCE getters are instruction-identical. Singleton TU prevents B; no native gain.

## c18_u131_20261107
Source: Codex worker c18_u131_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2608 B.

c18_u131: owning .data8040EA58..8040F0A4 as typed BATTLE prefix(48 race params+16 records), static normal[16][2]/reverse[8][2] records and member-function descriptor restores native3432B and base+540/base+340 address construction. All1612 data bytes/relocations and8/12 EH/index100. SelectTaRecord(round,reversed,cup) inline helper improves99.013985 ->99.4289(default),99.46387(no inferred pools); fixes recordr6. Reversed snapshot and bool selector invariant; ternary selector wrong default/polarity. int flag/rank reuse adds copies, whole player-item helper adds transfer, separating player/ghost flags fixes playerr26 but swaps time-low/coins and leaves ghostr28. Keep NM; remaining zero r3/r0, startedr28/r26, reverse/round load/compare scheduling. One function prevents B. Full fallback DOL SHA1 exact, zero native gain.
