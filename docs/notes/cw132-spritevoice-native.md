# cw132-spritevoice-native

Source: Codex worker c6_nt1_801a1714_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 9560 B.

fn_801A24B8 (3588 B) matches using canonical SpriteVoice helpers and priority 14: first current-player even voice is 0x1E2, first odd 0x1D1; other-player even 0x1E3, odd 0x1E4. fn_801A32BC (5972 B) needs g_bgmStateId=0 before current=&g_raceEntryArray[lbl_806D1775] to reproduce the target zero web/prologue schedule; all later logic and all EH then match. These two singleton groups are independently split-safe. The current countdown/goal NonMatching sources expose persistent base-register and pooled table-address differences; do not promote on fuzzy similarity.

## c14_u61_20261106
Source: Codex worker c14_u61_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u61: fn_801AECF4 native draft improves raw objdiff 89.88308 -> 98.45942 with TU-local Goal_Select(base,character,id), capturing normal=base+14 and special=base+94 before range checks. Removes eight extra instructions / 32 B; now exact 2908 B text size and extab8/index12 100%. Residual goal-line base+0x98C association/ccClass stride plus volatile rank/distance GPR homes. Multidimensional line view 98.39752; large inline rank-switch helper not inlined (12.984869), both reverted. Singleton remains NM; full fallback-linked DOL SHA-1 OK.

## c16_u13_20261106
Source: Codex worker c16_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u13 fn_801A4F38: fresh 88.909676 -> 97.15161%. TU-local Goal_SelectOther(base,char,id) capturing normal=base+14 and special=base+94 restores pooled lhax access. First selection helper normal=base/special=base+42 improves but zero-offset normal pointer still folds into r31; struct-array representation is byte-invariant. Indexed Goal_Progress helper with shared base g_raceEntryArray+0x44 restores first progress comparison instructions; second retains scratch/scheduling differences. Final source3688 vs target3720B, extab100/index91.66667. Singleton remains NM; full fallback-linked DOL SHA1 OK.

## c18_u84_20261107
Source: Codex worker c18_u84_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u84 fn_801A4F38: explicit signed byte offset playerOffset = g_goalFanfarePlayerIndex * (int)sizeof(SpriteVoiceRaceEntry), used both for the player field and Goal_ProgressOffset(playerOffset), fixes player setup and second progress comparison, 97.15161 -> 98.07635, source3684 vs target3720, EH100/index91.66667. Nine remaining missing addi-zero instructions are caused by external base-pointer folding. Six real short array definitions in target .data order (14,14,14,52,52,52 entries) restore pooled addi base,0; together with offset reuse the diagnostic is3720B with all instruction mnemonics/registers/order exact, objdiff99.98387 with ppc_calculate_pool_relocations=false (base ...data.0 vs lbl_80496C38 and timestamp +4 aliases only), EH/index100. Actual pool split80496C38..80496DC4 fails: fn_801A1828 -> 19FC -> 1BD0 -> 1D98 -> 24B8 -> 32BC -> 4A10 -> 4F38 -> auto_07_80496DC4_data -> fn_801A1798. fn_801A1798 text801A1798..1828 owns later .data jumptable8049A060..A094, pinning opposite order. Need coordinated broader TU/pool-boundary work including that existing matched owner; cannot solve within this claim. Pool/header/split experiment fully reverted; only offset improvement retained. Full coordinator build fallback DOL SHA-1 exact, native gain0. Diagnostic source/build outputs remain under build/c18_pool_offset.*, not acceptance sources.

## c18_u166_20261107
Source: Codex worker c18_u166_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u166: fn_801A7D0C90.07249->99.621086. Real adjacent BSS definitions g_voiceQueue[64], VoiceSpeaker g_raceCurrentSpeakerId, g_raceEntryArray[8], with ownership80678D90..80679260, restore original compiler BSS pool base r31, cached speaker r29, full0x20 frame and repeated addi(base,0). This is the structural difference missed by c14 extern-only/pointer probes. TU-local byte-returning Push and separate flag store then head++ restore every enqueue instruction. Text2428/EH8/index12/BSS1232 sizes exact, owned EH/BSS100. Remaining item lookup801A8308..831C forms +0x40 in scaled index instead of item-column base, r3/r4 homes differ. Typed strided-array accessor invariant; full item-active helper adds bool branches; typed field view gives best99.621086. Six hypotheses exhausted, honest singleton NonMatching, no B split. BSS split succeeds without cycles and full coordinator fallback-linked DOL SHA1 exact. No filler/asm/shared-header/EH bridge edits.

## c19_u31_20261107
Source: Codex worker c19_u31_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 152 B.

c19_u31 fn801AECF4: fresh raw98.45942/2908B/EH8/index12 exact. Correct Race_CompareKartProgress args to int participant indices using canonical MidRaceVoicePrivate/MidRaceKart and RaceVoice_Kart; instruction-invariant but semantically correct, retained. Inline arithmetic-return Goal_DistanceSum for pair/total sums also instruction-invariant, removed. Stopped after2 invariant experiments. Actual previous sprite archive is c18_u23, not c18_u31. Remaining line association +48..94, rank +18C/+190, distance homes +400..414/+48C/+77C..79C/+814/+81C unchanged. Pool ownership cannot be retried in isolation without addressing c18_u84 known link cycle with matched fn801A1798 data8049A060..A094; requires coordinated broader ownership work. Single fn prevents B. Full coordinator fallback DOL SHA1ea30f3b1 exact, native gain0.

## c20_u15_20261108
Source: Codex worker c20_u15_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u15 fn801A4F38: canonical MidRaceVoicePrivate.h confirms kart+2AC is int participantIndex and Race_CompareKartProgress consumes int indices. Reuse that view and RaceVoice_FindByRank, use canonical unsigned participant byte, and access first table as lbl_80496C38.f0. Retained semantic type correction is instruction-invariant98.07635/3684B. Const table access probe also invariant and reverted. Owned EH100/index91.66667 unchanged. Known nine addi-zero residual remains a genuine pool mechanism, with prior c18 cycle through matched fn801A1798 jump table outside claim. Do not redispatch this single-TU pool retry without resolving broader ownership. No A/B promotion, flags/ranges/maps/shared-header edits, or native gain.

## c20_u24_20261108
Source: Codex worker c20_u24_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u24: fn_801AECF4 natural rank type/scope correction int rankIndex + signed char rank resolves +18C/+190 lbzx/extsb input homes. Raw98.45942 ->98.473175, text2908/extab8/index12 exact sizes; EH100. Exactly these two source rows change, all other instructions unchanged. Reversing third-distance/pair-sum expression regresses98.45942; small inline Goal_Distance(rank) is invariant98.473175. Three hypotheses exhausted. NonMatching remains; single fn prevents B. Do not retry isolated pool ownership: c18_u84 cycle requires broader coordination with matched fn801A1798. Full coordinator fallback-linked DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Native gain0.
