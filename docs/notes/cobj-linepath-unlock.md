# cobj-linepath-unlock

Source: Codex worker c15_u61_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u61: CObj_LinePath_Step 800304E0 (1152B) improves 94.416664 to95.479164 by numeric literals, indexed recording-output loop, and dx declared before dz in second distance block. Both sqrt blocks and output loop become exact. Remaining vector-load/store scheduling and auxiliary-angle scratch FPR residual. Inline vector helpers byte-invariant; auxiliary local scope neutral. Keep singleton NonMatching. EH8/index12 exact; fallback-linked full DOL SHA-1 OK. No native gain.

## c18_u123_20261107
Source: Codex worker c18_u123_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1152 B.

c18_u123: CObj_LinePath_Step 800304E0/1152B unlocked 95.479164 ->100. Scoped const volatile float *translation used only for vector assembly restores target serial matrix loads/stores; leaving recording-distance reads unqualified preserves their established scratch FPR identities and z/x scheduling. Global qualification scores99.767365; using external lbl_806D2310/2314/2318 auxiliary constants scores99.958336; scoped qualification completes100. Inline CObj_ApplyViewport and CObj_LoadIntoGX mirror matched CObjViewport.c so ready checks are generic defensive wrappers, byte-invariant. No new data ranges/EH bridges/splits needed. Existing flags unchanged; promote Matching. text1152/extab8/index12 all100; final report complete and source main.elf edge, coordinator service request2 DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Canonical dolphin/mtx.h inclusion was tested but cannot compile under this TU flag recipe because dolphin/types.h pulls libc/stdio.h and missing stdarg.h; retained existing private point view, no shared changes.
