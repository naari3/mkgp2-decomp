# voice-pool-addressing

Source: Codex worker c7_oc_801a6538_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Voice module TU (0x801A....) used MWCC data pooling: .data tables addressed as lbl_80496C38+off and local array initialisers as lbl_803810A8+0x2C18.. (r30/r31 loaded at function entry). Extern struct + local base pointers reproduce the entry hoist and most code; members that the original treated as separate pooled globals (g_voicePlayCountTable at +0x1534, goal lines at +0xF8C) still fold differently. Local `short list[N] = {...}` inside a loop leaves a hoisted dead temp copy plus an in-loop copy; reproduced with a declared outer copy plus per-iteration struct assignment, with declaration order controlling stack slots. (u16)(v - 0x26A) <= 1 reproduces subi/clrlwi 16/cmplwi range check.

## c10_u2_20261106
Source: Codex worker c10_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u2: fn_801A6538 literal 1000.0f divisor removes undesired saved f31 and makes simple owned extab exact. Final time guard must be !(elapsed >= 12 threshold) to retain target cror/bne unordered semantics; previous < form omitted cror. Fresh baseline 97.25574%, retained 97.65049% (6096 vs 6100 B), index section 91.66667%. Inline clip/goal accessors do not preserve pooled subtable bases (97.65705%, discarded); open-coded spin loop worsens to 97.530495% (discarded). TU stays NonMatching, source_input false; full coordinator DOL SHA-1 passes.

## c19_u6_20261107
Source: Codex worker c19_u6_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 11 fn / 6328 B.

c19_u6: fn_801A6538 direct objdiff97.65049->97.72918, unchanged6096vs6100B/EH100/index91.66667. TU-local DriverCharacter(data,driver) snapshots character then id, with id declared before character; fixes all16 spinning selector volatile-register rows. Typed RaceVoice_Item(playerIndex) plus block-local item fixes all4 boost setup rows. Every changed instruction now target-exact; all other instruction spellings/EH unchanged. Removing spinning data parameter rematerializes a pool base97.40131; CountRivals helper is byte-invariant97.72918 and removed. Prior c18 pool cycle not repeated, no config/range/bridge/header edits. Whole fallback-linked coordinator build SHA1ea30f3b1 OK; singleton stays NM, zero native gain.

## c19_u260_20261107
Source: Codex worker c19_u260_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u260 VoiceSystem_Init: integer-derived entry base (RaceVoiceEntry*)((unsigned int)state+0x190) and clip base (VoiceClip*)((unsigned int)data+0x1534) prevent aggregate-root folding and improve fresh85.58273 to88.81295 at exact1112B/EH8/index12. Preserve signed canonical OSTime: unsigned removes4B and index falls91.66667. Timestamp union81.431656 and typed speaker pointer with target-order stores76.960434 regress; these also caused postprocess_sdata2 to bridge conversion double to float symbol, so both discarded. Best final raw conversion bits4330000080000000 map correctly to lbl806D9840. BSS80678D90..80679260 already owned by fn801A7D0C; data pool split has c18_u84 documented cycle with matched fn801A1798. No out-of-scope pool changes. Singleton NM, full fallback DOL SHA1 exact, zero native gain.

## c21_p33_20261108
Source: Codex worker c21_p33_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p33: Assigned .rodata 803810A8..80383CF8 to fn_801A6538.c, emitted 649 real tables/strings without explicit padding, and split oversized kVoiceMidRaceCheckpointByTotalLaps at 80383CC0 into four commentary lists. .rodata 100%; dtk split and full DOL SHA-1 pass without cycle. Text remains 97.960655% (6096 vs6100B), extab100/index91.66667. Queue-head snapshot helper and final entry block-local lifetime both code-invariant. Remaining folding/scheduling residual is in shared .data 80496C38..8049A060, requiring coordinator-owned multi-TU merge. TU stays NonMatching, native gain0.

## c21_p39_20261108
Source: Codex worker c21_p39_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p39 fn_801B4548: direct96.57497->96.57850 (service96.82249), exact target extern lbl_806D9838 replaces unmapped literal2.0f; source text5616vs5656, EH87.5/index83.33333/data0 unchanged. Character snapshot helper96.016266 reverted; nearest explicit cursor invariant reverted. Pool80496C38..8049A060 remains unowned, but contiguous extension through this TU table8049A168..A204 would cross Matching fn801A1798 dataA060..A094 and VoiceIntro_PushForRaceMode A094..A134 plus fn801B1D5C A134..A168; prior c18_u84 cycle applies. Requires coordinated wider TU/pool boundaries, no in-claim A/B unlock. Full fallback DOL SHA1 exact; zero native gain.

## c22_u4_20261109
Source: Codex worker c22_u4_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u4 fn801A6538: inherited optimization_level3 removed (raw97.960655 -> natural97.72918). GoalLine/AdvanceGoalLine float** boundary exactly recovers +F8C arithmetic (98.04459); ClipPlayed/AdvanceClip VoiceClip** cursor restores base-plus-index clip loads (98.999344). Real in-loop short list initializers reproduce both compiler copies and exact rodata without explicit template copies. Independent C89 loop-local counters raise raw99.12066/report99.17246; overtake/hit indices and commentary voice home fixed. Explicit rival cursor97.90033 and bounded chasing helper98.994095/rodata99.814865 discarded; clip argument order invariant. Remaining6096vs6100B: chasing CSE-hoisted clip base, saved GPR/copy scratch homes, zero li/mr sites and aliases. Goal-line ownership is no longer required to recover that arithmetic, but genuine shared .data80496C38..8049A060 still needs coordinated merge and fn801A1798 dataA060..A094 order resolution. No flag/range/header/map changes, no native gain, full fallback DOL SHA1ea30f3b1 exact.

## c22_u70_20261109
Source: Codex worker c22_u70_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u70: VoiceSystem_Init inherited opt_lifetimes off removed (raw88.90288 -> natural88.81295). Six timestamp pairs correctly declared signed OSTime and assigned now directly remove spurious srawi r0,r3,31:89.226616/1108B. Static inline clip-reset helper raises89.31654 (service report89.91007). EH100; index91.66667 solely 1108-vs1112 size word. Speaker target-order stores76.960434 reverted (known negative). Queue BSS80678D90..80679260 belongs to Matching fn801A7D0C; voice data80496C38..8049A060 remains blocked by recorded c18_u84 cycle and later matched fn801A1798 jump table. Settings lbl80598A60 +30 addressing is already exact; its audit entry alone does not prove a card/boot merge is needed. Single fn, no B cut; flag/ranges unchanged. Full fallback-linked service DOL SHA1ea30f3b1 exact; native gain0.

## c23_u21_20261109
Source: Codex worker c23_u21_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u21: passing RaceVoiceData* into RaceVoice_ClipPlayed and selecting data->clips INSIDE that inline accessor, retaining AdvanceClip(&clip,id), restores both chasing-branch +1534 bases at target offsets14CC/1580. Remove caller clips local/assignments. Raw99.12066->99.39017, report99.17246->99.409836; source6096->6100B, extabindex91.66667->100; rodata11344/extab8 remain100. Remaining146 rows:144 argument mismatches (including6 symbol-only low-word aliases) and2 mr-vs-li replacements; saved/volatile register homes. Separate phase-local entry pointers and int->long count invariant; spinning helper i-before-pushed99.37377; rotating-list inline narrow/promoted return98.81967/98.81312 with unwanted extsh and6120/6124B. Reverted all except accessor. No pool/config/flag/symbol/header changes; singleton NM/no B/native gain0; full fallback DOL SHA1ea30f3b1 exact. Pool ownership is no longer required merely to restore chasing base materialization; coordinated larger merge remains untested for remaining registers.
