# ai-new-tu-lane

Source: Codex worker c6_nt4_ai_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c6_nt4_ai: nine new singleton NonMatching splits preserve full DOL SHA-1. AI_PerKartUpdate (99.797295) and fn_801E9CBC (99.72727) have exact text lengths/EH but item-pointer/result register coalescing differs. AI_SystemDtor (98.21568) differs only in 0/-1 constant registers in the reset loop; direct-body and nested-helper probes did not resolve it. AI_UpdateItemUseLogic -proc 750 reproduces scalar-only FPR save and exact 0x30480000 extab; GC/2.6 generated identical tested output to GC/1.3.2. No manual EH, new asm, forced sections, embedded opcode data, or padding objects were introduced.

## c13_u8_20261106
Source: Codex worker c13_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u8: AI_CalcVSTargetSpeed 801E93AC improves97.70492->98.85246 via TU-local literal10.0f/1000.0f scaling helpers, in-place initial scale multiplies, record declared before controller and lap before rank. All FPR instructions now exact, text488/EH8/index12 preserved. Direct NormalSpeed body in caller worsens94.81967 and adds f29/frame. Remaining self/initial ctrl/cup/round/index and normal table/rank/lap GPR identities; retained singleton NonMatching. Full fallback DOL SHA-1 OK.

## c13_u12_20261106
Source: Codex worker c13_u12_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u12:fn_801E96BC388B improves97.57732 to98.81443 under unchanged flags. Extracting reset+nearest-kart scan into static inline helper eliminates extra li by sharing zero with inner loop counter; caller-owned Vec3 scratch preserves stack layout. Helper other-before-j and px,py,pz declarations restore target GPR/FPR homes. Remaining array base addi r0;mr r28,r0;mr r29,r0 vs target addi r28;mr r29,r28 adds4B. Direct global array in inner helper worsens86.793816 and base-return inline accessor is invariant. Singleton staysNonMatching; full fallback DOL SHA-1OK.

## c13_u46_20261106
Source: Codex worker c13_u46_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u46: fn_801E66B4 improves 95.375 to 96.328125 by unsigned-char flag helper `if ((flags & mask) == 0) return 0; return 1;`, restoring both branch-over-branch islands. Passing status pointer instead is invariant. In-place pointer Length helper worsens to92.96875. Remaining cached status vs target reload (-4B), first-check GPR identities and f5/f6 length/constant swap. Singleton retained NonMatching; fallback full DOL SHA-1 OK.

## c16_u8_20261106
Source: Codex worker c16_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u8: AI_CalcLapSpeedBonus 801DD480 recompiled baseline88.96797 (assignment report89.34) improves90.03203 by expressing pointer-table row/column strides in bytes before pointer dereference. Nested arrays89.836296 shorten text1108; typed aggregate pool view82.08541 changes extab and text1148, both reverted. Retained text1120 vs target1124, extab100/index91.66667. Residual table-base grouping/scheduling, first scan cc/table r29/r30 swap, later cursor/index homes, common-table success add+lfs versus target addi+lfsx. Singleton staysNonMatching; full fallback DOL SHA-1 OK; zero native gain.

## c17_u121_20261107
Source: Codex worker c17_u121_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u121: fn_801E96BC outer indexed spelling for(i=0;i<8;++i){record=&base[i];...} removes prior r0 base materialization plus extra mr, improves 98.81443->99.84536, exact 388-byte text and extab8/index12 100%. Only initial base/walker copy direction differs (target addi r28;mr r29,r28 vs source addi r29;mr r28,r29), all later instructions exact. Full outer inline traversal regresses 82.06186/412B and rematerializes inner base; indexed PairAt helper invariant. Best indexed source kept NonMatching; singleton cannot split, native gain0. Final fallback DOL SHA-1 OK.

## c18_u124_20261107
Source: Codex worker c18_u124_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u124 AI_UpdateItemUseLogic 801EA2FC: genuine inline void Decrement(int input,int& result){result=input;if(input>0)result=input-1;} with caller-owned load/store restores both missing timer input/result moves and all r27/r29 difference/rank/hitTimer/use homes. Improves95.46512->97.62791, emitted504 vs target516B, EH8 exact/index83.33333. Only target switch cmpwi8/beq/bge trio is missing; the source goes straight to cmpwi5/bge. Calls in each case group with break duplicate blocks (94.06977/544B); shared goto tail is H1-byte-equivalent. Retain helper improvement, leave existing NM. No singleton/pool/B rescue. Coordinator full fallback-linked DOL SHA1 ea30f3b1 OK; no native gain.

## c18_u221_20261107
Source: Codex worker c18_u221_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u221: AI_CalcLapSpeedBonus 801DD480 fresh90.03203->94.35587. Own the complete native semantic AI .rodata pool8039FD90..803BD08C (119548B), preserving five exported parameter symbols and file-static lap rules/pointer tables. Named tables plus byte-stride pointer lookup restore target base-register grouping and1124B text. Flat/nested indexed pool views regress. Scanner cc-before-table parameter order restores first-scan r30/r29 homes. Separate common-table helper invariant. Owned rodata/extab/extabindex all100; residual second/common scan GPR webs, common add+lfs vs addi+lfsx, final nonrace lookup scheduling. BattleTimeAttack symbol contains24 BaseSpeed pairs then24 symbolic item-list pointers. RemainsNonMatching; singleton cannotB-split; native gain0. Coordinator full fallback build SHA1 ea30f3b1 OK.

## c19_u207_20261107
Source: Codex worker c19_u207_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u207 fn_801E9CBC improves99.72727->99.86364 by wrapping only indexed item load in static inline int ItemAt(const int *items,unsigned int index). Selected load becomes target r4 and following copy becomes target mr r27,r4; remaining three rows use list base r27 instead of r28. Exact440B/EH8/index12 preserved. Unsigned random-cursor signature invariant; whole Tick helper regresses99.63636; float literals10/1000 and indexed sentinel count invariant at99.86364; reference-return accessor regresses99.72727. Retain value accessor only. Singleton offers no B split, no A rescue needed/applicable; remainsNM, full coordinator fallback DOL SHA1exact, native gain0.
