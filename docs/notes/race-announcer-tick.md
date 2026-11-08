# race-announcer-tick

Source: Codex worker c9_L8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RaceAnnouncer_TickAndEnqueue owns singleton extab 80012AB8..80012AC0 / index 800276BC..800276C8. Reuse RaceVoiceRivalPrivate.h types and data block. TickPush with local index=g_voiceQueueHead++ produces target sthx-based fill; pointer=&queue[head++] produces a different form. Remaining-time helper matches most code but compiler folds clips base offset 0x1534 and length offset 4 into 0x1538, losing target separate base instruction. At 99.510956% text, unlinked native .o must not be counted as matched.

## c10_u4_20261106
Source: Codex worker c10_u4_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u4: In TickRemaining, *(float *)((unsigned int)clips + g_voiceQueue[i].id * sizeof(VoiceClip) + 4) preserves separate +0x1534 base, restores exact 5840-byte size and automatic EH/index 100%, improves text 99.510956 -> 99.61644. Retained honest NonMatching; 78 remaining instruction rows differ in register identity (clip-base/loop rotation, character/queue-fill scratch homes, rank-pointer loads). Named integer base and integer helper parameter/grouped offset did not solve remaining homes. Full fallback-linked DOL SHA-1 OK, zero native gain.

## c18_u129_20261107
Source: Codex worker c18_u129_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u129: baseline99.61644/78 register-only rows. Commute/reassociate three-distance test to (byRank[3]->distance + byRank[2]->distance) + byRank[1]->distance:99.62329/76 rows, rank2 pointer target r5 fixed. Text5840/extab8/index12 all exact sizes, EH/index100. Inline clip-length accessor and leader-enqueue helper invariant. Direct global clip access99.229454/5848B; offset-first grouped arithmetic98.938354; named rank pointers99.60959. Retain one-line improvement, honestNonMatching. Remaining clip-loop rotation, solo enqueue homes, rank1/rank3 swap and two tail-character swaps. No singleton/pool mechanism applies; singleton TU cannot B split. Six hypotheses exhausted. Full fallback DOL SHA1 exact, native gain0.

## c19_u4_20261107
Source: Codex worker c19_u4_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u4: fresh99.62329 ->99.69863 by TU-local short TickCharacter accessor with voice declaration before normal/special table pointers (same semantics as RaceVoice_Character). Both tail character/table/enqueue r5/r6 clusters become exact; 76 ->60 register-only rows. Text5840/extab8/index12 unchanged, EH/index100. Explicit signed clip offset invariant; int return adds extsh/5896B (98.33562); entry-pointer accessor swaps character/id homes (99.39726); pointer distance-sum helper99.6815; solo short output-parameter getter+enqueue wrapper invariant. All six snapshots under build/w. Remaining clip-loop rotation, solo case1 enqueue homes, rank1/rank3 loads. No A/B rescue for singleton, retained NonMatching; full fallback DOL SHA1 exact, native gain0.

## c21_u3_20261108
Source: Codex worker c21_u3_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u3: improve RaceAnnouncer_TickAndEnqueue99.69863->99.76028 by extracting TickWriteQueue(int index,short id), which writes id/priority4/flag0 and returns index+1; TickPush assigns that result to g_voiceQueueHead. This fixes all12 solo-case enqueue register rows; 60->48 rows, text5840/extab8/index12 unchanged, owned EH100. Typed short loop ID, output accumulator, dedicated solo getter and queued-duration-only helper invariant; generic rank-array accessor96.646576/5864B regresses. Keep only queue writer helper in sole-includer private header. Remaining44 clip-loop rotation plus4 rank1/rank3 homes. No singleton/pool-address mismatch, no claim-safe merge or singleton function B cut. Full coordinator build exit0/DOL SHA1ea30f3b1 exact; source remains NonMatching/fallback-linked, native gain0. Six hypotheses exhausted.
