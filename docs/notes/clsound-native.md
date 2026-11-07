# clsound-native

Source: Codex worker c7_s24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 488 B.

ClSound_PlayBgmStream 0x80190B3C (488 B): native C matches GC/1.3.2 with exceptions and use_lmw_stmw on. Inline unsigned-char StopBgm(id, resources) reproduces the redundant initialization check; declare local const ClBgmFiles* files and assign resources+0x3D1C before files[id].right. Repeated casts to table[id] fold 0x3D20 into the load (97.28689%); named files pointer matches 100%. Full source-linked DOL SHA-1 verified. Spatial functions 801913B0/80192F04 remain at 95.03597%/97.39286%; explicit listener base keeps r30 but adds a move and generates mr at offset-zero rather than target addi 0.

## c10_u22_20261106
Source: Codex worker c10_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u22: fn_80190D24 fresh C compile 96.70644%/1660 B (assignment report 97.62%). Inline adjacent-entry SwapQueued(index), with local a/b pointers and a struct tmp, restores 1676 B and exact extab/index, reaches 98.324585%. Named gain/level/setting floats improve to 98.40811%, gain f0 and final multiply operand order exact. Queue GPR homes and predecessor copy scheduling plus FP bias/intermediate product homes remain. C++ struct copy trial reaches weighted 98.81384% but drops three tmp stack stores, shrinks frame 0x50->0x40 and text to 1664 B; rejected. Kept NonMatching; fallback full DOL SHA-1 OK; no native gain.

## c14_u49_20261106
Source: Codex worker c14_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u49: ClSound_InitSoundSystem prebuilt objdiff baseline 91.298134% (assignment report 91.78%). Removing LoadSoundFile pathname local and recomputing strings+offset removes a call-crossing register and restores target 0x120 frame/r26-r31 saves, 94.26087% text and exact extab. Typed ResetEvents/PrepareEffects/ResetStreams inline boundaries give 94.29192%, but subobject addresses still fold. Byte-array workspace and signed length delta yield identical residual and were discarded. Retained typed C NonMatching, 1912 vs target 1932 bytes; bases r30/r31 swapped, file-end add/sub association, subobject address materialization, ARInit result shuffle remain. Single function prevents rescue B. Full fallback DOL SHA-1 OK.

## c18_u27_20261107
Source: Codex worker c18_u27_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u27 fn_80190D24: fresh retained baseline98.40811, final99.689735 (1676B, extab8/index12 exact). Replace only SwapQueued *a=*b with a->id=b->id; a->state=b->state; a->delay=b->delay; keep aggregate tmp=*a and *b=tmp. This restores target sequential predecessor load/store schedule and tmp r5/r4/r3, base r6/index r7. Remaining current/predecessor r9/r8 vs targetr8/r9 invariant under pointer helper params, reversed params, helper-local pointers and explicit caller induction cursor. FP setting-accumulator/full-expression/gain-accumulator alternatives regress. Keep original index-helper plus fieldwise copy. Colorer unavailable (frida absent); no install. Singleton NonMatching, no rescue B. Coordinator fallback full DOL SHA1 exact, zero native gain.

## c18_u95_20261107
Source: Codex worker c18_u95_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 532 B.

c18_u95 unlocks fn_80193624 96.65414 ->100% text532/extab8/index12. Entire event scan in static inline UpdateSoundEvents restores initial mr and queue walker r12/destination r11 (98.233086). Declaring SoundEvent *next before int i,j inside that helper restores next=r10/i=r9/j=r8 and makes queue exact (99.66165). Separate inline UpdateActiveStreams restores counter=r30/walker=r29 for final seven differences. Named per-element current/destination pointers were byte-invariant. Earlier c13 deletion-only and copy-only helper probes did not cover whole event-loop boundary. Existing flag promoted to Matching; source object in main.elf edge, final ELF symbol80193624/532, coordinator full DOL SHA1 exact. No data/split/symbol/EH bridge/shared header changes.

## c18_u184_20261107
Source: Codex worker c18_u184_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u184: measured InitSoundSystem baseline94.29192 improves to97.03313, text1928 vs1932. Replace flattened SoundWorkspace extern with native events[37], static ReverbHI/Chorus, canonical ClSoundVoice slots[32], active streams[4]. Own BSS80677F40..80678718; split original base object at806780FC/806782DC. CW BSS pooling restores target event addi0, reverb/chorus offset bases and active-stream base; BSS2008/extab8 exact. C++ semantics invariant. Typed readonly-pool/global const definitions do not pool like BSS; direct named string/path references regress83.035194 and retain call-crossing pathname; discard entire readonly experiment. Residual base r30/r31 swap, missing ARInit r0 shuffle, file-end load/add/sub order with buffer/end r26/r27 homes and group-loop homes. Remains NonMatching after3 hypotheses; no mechanism B, source_input false. Full coordinator service DOL SHA1 OK; native gain0.

## c19_u52_20261107
Source: Codex worker c19_u52_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u52 fn_80190D24 improves99.689735->99.77327 at exact1676B/extab8/index12. Use separate float product=level*setting; volume=(int)(product*gain), instead of level accumulation. This fixes all five FP bias/level/product register rows without changing instruction order. lbl806D94F8 .sdata2 declaration corrected const (instruction-invariant). Queue18rows current/predecessor r9/r8 vs targetr8/r9 remain. Pointer/FP declaration reversal, whole mark-and-bubble helper, in-place volume helper, split inner/outer indices and restrict pointers invariant. Predecrement-index swap form worsens96.88067/1684B; reverted. Retain minimal const+product draft, sole TU remainsNM, no rescueB/nativegain. Full coordinator fallback DOL SHA1exact.

## c19_u60_20261107
Source: Codex worker c19_u60_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1772 B.

c19_u60: ClSound_InitSoundSystem 97.03313 ->97.354034 with static inline ReadSoundFile(file,data,size,start,length) wrapping bounds computation, WaitIfSamePage, DVDReadPrio and RecordOpStart. Later three loaders now use target buffer r27/end r26; first remains swapped. Arithmetic still reassociates to (start+length)-1 and loads start first. Whole InitSoundSystem inline helper exceeded auto-inline budget (40-byte wrapper, out-of-line body); small ARAM reporting helper was byte-invariant. Kept only instrumented-read boundary. Text1928/1932, BSS/extab100, extabindex91.66667 due size. Bases r31/r30, ARInit shuffle and group counter/sample homes remain. No split/config/data changes. Single function, NonMatching, source_input false, full coordinator fallback DOL SHA1 exact; native gain0.

## c19_u257_20261107
Source: Codex worker c19_u257_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u257 fn_801913B0 improves95.03597->98.115105%,560->556B exact,extab8/index12 all100. Whole UpdateSpatialVoice inline helper with listener LOCAL (prior c18 passed it as parameter) removes extra r7->saved listener move. In helper, declare far before near and pan before volume, listener after outputs: target f31/f30 and listener r30/volume r29/pan r28. Explicit unsigned sound_id + const ClSoundDef* view then makes initial address setup exact. Remain far-case li ordering/copy, first Dot mr vs addi0 plus arg scheduling, surround/output-byte cursor r5/r6 vs targetr6/r5. Smaller vector-call helper invariant. Retain NM improvement; source fallback/full coordinator DOL SHA1 exact,zero native gain. Listener data80495F20..80495F48 already belongs to Matching Fog_UpdateFromCourseScene3D; cannot take pool. No singleton or rescueB subset.

## c19_u296_20261107
Source: Codex worker c19_u296_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u296 fn_801934F4 fresh baseline97.039474/308B (existing two pragmas). Whole static inline DrawSoundEvents removes event addi-r0/mr and restores i=row copy,304B/EH/index100; helper declaration order event,row,i restores target eventr28,rowr29,ir30. Final97.36842, only mr r30,r29 / lis format order at +34/+38 swapped. Explicit format pointer hoists both lis early93.75; separate inline FormatSoundEvent regresses94.3421/308B. Retain whole-loop helper and decl order, unchanged pragmas, NonMatching. Single function no rescueB. Final coordinator fallback DOL SHA1 exact; no native gain.
