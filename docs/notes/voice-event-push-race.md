# voice-event-push-race

Source: Codex worker c14_u30_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

VoiceEvent_PushRace 0x801AD534: queue clip base initialization belongs inside nonempty queue branch (93.35526 -> 94.49671%). TU-local clone of SpriteVoice_Push with flag store and head increment as separate statements reaches 98.67105%, target text size 0x17C0 and extab/extabindex 100%. Remaining QueueTime clip base r6 vs r4 and scratch r5/r4 vs r6/r5 across seven inlines; split 64-bit time reconstruction has low/high reg swaps. Moving clips declaration to outer helper scope had no effect. No further permutation attempted. TU remains NonMatching; mechanism B cannot partition a single function. Full build SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK using target fallback.
