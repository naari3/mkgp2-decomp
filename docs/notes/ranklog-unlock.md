# ranklog-unlock

Source: Codex worker c3_u6_ranklog_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RankLog is a single indivisible reversed-EH group (DTK cut at 800A8208 rejected). Correct format extern sizes 5 and 7 restore SDA21. PackedWords requires byte packing for target words 1BA/1BE/1C2/1C6/1CA/1CE. Real C++ synthesized PlayerData assignment remains out of line at default flags; memberwise native C copy improves InitStartRace substantially but register-pressure scheduling remains. No ASM/manual EH/padding used.

## c19_u80_20261107
Source: Codex worker c19_u80_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u80: own .data80411458..80411B18 as three contiguous mutable tables of 8x3x2 12-byte TitleTarget records {signed char score; float limitA; float limitB}. First table remains global lbl80411458, next two static tables at80411698/804118D8. Native typed initializers and implicit alignment produce exact1728B; named static arrays restore shared base+0/240/480 and make both score predicates100% (default starts82.73077/82.94936). No manual payload/padding. Natural static-inline DetermineCurrentNameId helper improves DetermineTitle97.02105->98.47369 at760B. Loop reuse96.88947 and caller-score-pointer97.336845 worse. C++ snapshot prefix/tail wrapper remains out of line; global title helper and explicit offset helper worsen lookups. All70 exact functions stay in indivisible reversed EH group; no B split/native gain. Full coordinator fallback DOL SHA1 exact.

## c20_u133_20261108
Source: Codex worker c20_u133_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1432 B.

c20_u133: CurrentNameScore returns score only; capture character in DetermineTitle before scanning, then call DetermineNameId(score,chara). 98.47369->98.947365 with unchanged size/EH and exact dispatch homes. Separate mode index for first three all-course scans from i used in per-course scans: NewClearedRecord_Race 98.188156->99.87805; only six first-loop index r24/r28 rows remain. First-scan split99.756096, initial-mode capture/do-while invariant99.87805, tail-inline helper97.5784. Whole native rodata ownership probe reproduces anchor offsets but does not cache title multiply, so not retained. Matching CardSetupFlowResult inline_max_size(1000) recipe permits C++ assignment inline but still flat scalar grouping64.920456; nested header/index layouts worse. All70 exact functions preserved; no native gain due indivisible reversed EH group; full fallback DOL SHA1 OK.
