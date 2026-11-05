# race-announcer-tick

Source: Codex worker c9_L8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RaceAnnouncer_TickAndEnqueue owns singleton extab 80012AB8..80012AC0 / index 800276BC..800276C8. Reuse RaceVoiceRivalPrivate.h types and data block. TickPush with local index=g_voiceQueueHead++ produces target sthx-based fill; pointer=&queue[head++] produces a different form. Remaining-time helper matches most code but compiler folds clips base offset 0x1534 and length offset 4 into 0x1538, losing target separate base instruction. At 99.510956% text, unlinked native .o must not be counted as matched.
