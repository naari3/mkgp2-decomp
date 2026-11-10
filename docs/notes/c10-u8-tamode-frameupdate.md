# c10-u8-tamode-frameupdate

Source: Codex worker c10_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

TaMode_FrameUpdate 800A2B90 native draft: explicit reverse/normal table bases with cached cup/round improves 98.55361 -> 98.70979. accel = ((float *)TaMode_FrameUpdate_bss_806D1388)[TaMode_FrameUpdate_bss_806D1394 * 4] prevents struct-pointer CSE and matches target lfsx plus following ghost-frame load scheduling (98.996506). Function-scope coins declared before started puts coins at target r27 (99.013985), but started moves to r28 instead of target r26. Residual r3 vs r0 zero flag store, started register identity, and record table base/index association/load scheduling remain; native3428 vs target3432. Three approaches exhausted; retained NonMatching. EH8 exact, index12 91.66667 due text length. Full fallback-linked DOL SHA passes; native gain0. Do not repeat these same hypotheses blindly.

## c17_u89_20261107
Source: Codex worker c17_u89_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u89: fresh baseline99.013985 (3428B). SelectTaRecord(battle,cup,reverse,round) inline selector regresses98.80536; generic typed LookupTaRecord(table,cup,round) invariant99.013985. Byte-strided lookup summing cup*sizeof(row)+round*sizeof(record) restores3432B/extabindex100 but regresses98.81119: backend still distributes base+constant and does not preserve target base+540 followed by summed offset. All probes reverted. Six started r28/r26 and two zero r3/r0 differences remain. Canonical SINGLETON_INSTANCE getters are instruction-identical. Singleton TU prevents B; no native gain.

## c18_u131_20261107
Source: Codex worker c18_u131_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2608 B.

c18_u131: owning .data8040EA58..8040F0A4 as typed BATTLE prefix(48 race params+16 records), static normal[16][2]/reverse[8][2] records and member-function descriptor restores native3432B and base+540/base+340 address construction. All1612 data bytes/relocations and8/12 EH/index100. SelectTaRecord(round,reversed,cup) inline helper improves99.013985 ->99.4289(default),99.46387(no inferred pools); fixes recordr6. Reversed snapshot and bool selector invariant; ternary selector wrong default/polarity. int flag/rank reuse adds copies, whole player-item helper adds transfer, separating player/ghost flags fixes playerr26 but swaps time-low/coins and leaves ghostr28. Keep NM; remaining zero r3/r0, startedr28/r26, reverse/round load/compare scheduling. One function prevents B. Full fallback DOL SHA1 exact, zero native gain.

## c21_u11_20261108
Source: Codex worker c21_u11_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u11: fresh baseline99.60839 (inherited opt_propagation off). Output-reference SelectTaRecord improves99.62588 with unchanged3432B/data1612/EH8/index12 exact; selector round shift destination becomes targetr3, record pointerr4 remains versusr6. No-pool scoring identical. Vec copy ctor emits floats (98.64569), full controls helper remains non-inline (54.34149), bool idle latch invariant, explicit Vec snapshots duplicate copies/frame (98.84383), input-state aggregate spills (94.51282). Keep output-reference draft, all other probes reverted. Current residual additionally includes Vfx by-value copy source base r3/r4 and stack-address scheduling, alongside idle zeror3/r0, startedr28/r26 and selector homes. Single function prevents B. Final coordinator fallback DOL SHA1 exact, native gain0.

## c23_u29_20261109
Source: Codex worker c23_u29_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u29: unsigned long long now plus explicit signed conversion of modular elapsed ticks before signed division fixes idle-reset li/stb at800A2DB0/2DB8 to targetr0. Direct99.62588->99.63753 (report99.638695), unchanged3432B/EH8/index12/data1612 exact. Only these2 instructions change; inherited opt_propagation off remains unchanged and no native credit claimed. Diagnostic default optimization99.46387->99.475525. Argument-order correction and bit-preserving Vec copy ctor invariant; bool/cached selector99.45222; promoted flag98.95688/3440B; signed-byte named producer99.21329/3440B. All other edits reverted. OWN-SELF pool complete; one-function TU prevents B. Final coordinator fallback DOL SHA1exact.

## c25_u4_20261110
Source: Codex worker c25_u4_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u4 merged TaMode TU: Init99.66216 unchanged; FrameUpdate99.63753->99.649185 by removing SelectTaRecord round parameter and reading g_longRoundFlag inside helper. Only11 instructions in800A36B0..36EC change; target roundr0 and recordr6 now exact, cup/default-base/columnr3/r4 swap remains. Based on inline-arg frontend temp versus backend load numbering (mwcc_internals allocate_local_vregs). Init6 bounded probes (typed nested accessors, CcClass_Get, shared selector, direct typed fields, signed canonical params, actual TaRecord ghost) invariant or worse. Frame consumer helper, canonical Vec bit copy under inherited pragma, direct selector/captured locals/nested field-return regress or invariant. Retain final minimal selector change only. All other functions/sections unchanged, honest NonMatching, no ranges/flags changed, fallback-linked DOL SHA1ea30f3b1 exact, zero native gain.

## c26_u16_20261110
Source: Codex worker c26_u16_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u16: TaMode_Init 99.80574 -> 99.88176 by conditional const-reference selection of normal/reverse ghost record. Removes all six ghost r26 vs target r27 instruction differences without changing opcode count, siblings, or nontext sections. Residual: reverse/class r4/r5 swap and six params base/index-chain register differences. Named-local row accessor 99.86487; named-local class getter and later class-variable reuse invariant99.88176; cached bool class test98.116554; long reverse99.85642. All but conditional reference reverted. TU remains NM; zero native gain; coordinator build req1 SHA1 exact.
