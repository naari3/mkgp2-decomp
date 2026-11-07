# race-announcer-tick

Source: Codex worker c9_L8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RaceAnnouncer_TickAndEnqueue owns singleton extab 80012AB8..80012AC0 / index 800276BC..800276C8. Reuse RaceVoiceRivalPrivate.h types and data block. TickPush with local index=g_voiceQueueHead++ produces target sthx-based fill; pointer=&queue[head++] produces a different form. Remaining-time helper matches most code but compiler folds clips base offset 0x1534 and length offset 4 into 0x1538, losing target separate base instruction. At 99.510956% text, unlinked native .o must not be counted as matched.

## c10_u4_20261106
Source: Codex worker c10_u4_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u4: In TickRemaining, *(float *)((unsigned int)clips + g_voiceQueue[i].id * sizeof(VoiceClip) + 4) preserves separate +0x1534 base, restores exact 5840-byte size and automatic EH/index 100%, improves text 99.510956 -> 99.61644. Retained honest NonMatching; 78 remaining instruction rows differ in register identity (clip-base/loop rotation, character/queue-fill scratch homes, rank-pointer loads). Named integer base and integer helper parameter/grouped offset did not solve remaining homes. Full fallback-linked DOL SHA-1 OK, zero native gain.

## c18_u129_20261107
Source: Codex worker c18_u129_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u129: baseline99.61644/78 register-only rows. Commute/reassociate three-distance test to (byRank[3]->distance + byRank[2]->distance) + byRank[1]->distance:99.62329/76 rows, rank2 pointer target r5 fixed. Text5840/extab8/index12 all exact sizes, EH/index100. Inline clip-length accessor and leader-enqueue helper invariant. Direct global clip access99.229454/5848B; offset-first grouped arithmetic98.938354; named rank pointers99.60959. Retain one-line improvement, honestNonMatching. Remaining clip-loop rotation, solo enqueue homes, rank1/rank3 swap and two tail-character swaps. No singleton/pool mechanism applies; singleton TU cannot B split. Six hypotheses exhausted. Full fallback DOL SHA1 exact, native gain0.
