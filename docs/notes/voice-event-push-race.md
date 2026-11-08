# voice-event-push-race

Source: Codex worker c14_u30_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

VoiceEvent_PushRace 0x801AD534: queue clip base initialization belongs inside nonempty queue branch (93.35526 -> 94.49671%). TU-local clone of SpriteVoice_Push with flag store and head increment as separate statements reaches 98.67105%, target text size 0x17C0 and extab/extabindex 100%. Remaining QueueTime clip base r6 vs r4 and scratch r5/r4 vs r6/r5 across seven inlines; split 64-bit time reconstruction has low/high reg swaps. Moving clips declaration to outer helper scope had no effect. No further permutation attempted. TU remains NonMatching; mechanism B cannot partition a single function. Full build SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK using target fallback.

## c20_u7_20261108
Source: Codex worker c20_u7_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1540 B.

c20_u7: True OSTime declarations for 806D17C8/D0/D8 plus direct reads and assignments remove all three high/low timestamp scratch swaps; clean natural score 98.67434% vs baseline98.67105%,6080 B,EH100. Diagnostic reads through OSTime pointer gave98.70066% but casts were replaced by correct declarations. Final remaining297 aligned rows = queue register residual plus11 low-word aliases (base+4 vs separate low symbol); physical timestamp operands match. No symbols merged: VoiceSystem_Init and fn_801B3D40 still use low labels outside claim. Queue helper clip-pointer parameter and unnamed direct clip-base expression both98.55592% with diagnostic timestamp reads; same queue output, reverted. Retained typed improvement, NonMatching, full coordinator-build SHA1 OK, native gain0.
