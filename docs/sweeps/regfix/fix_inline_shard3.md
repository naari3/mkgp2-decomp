# regfix fix shard 3/4 (2026-11-09, main a5c9b61)

13 fns, 0 matches, ~25 min wall. metric = (opcode diffs, mismatching vregs, flips, graph-edit-known).
Move counts are from /tmp/regfix/FN.log.jsonl (diagnosed variants only, 12-24 per fn).

| fn | start -> best lines | best metric | best moves | note |
|---|---|---|---|---|
| AI_DecideAndUseItem_PairTracking | 34 -> 34 | 0,4,4,1 | declmove use->0 | |
| DetermineTitle | 16 -> 16 | 0,1,20,1 | hoist-front | flips capped (20) |
| FlashFadeOverlay_Draw | 24 -> 22 | 0,2,1,0 | wrap-fwd/wrap-loc + propoff | only improvement; best in shard3_best/ |
| PCBCheck_ProcessLinks | 4 -> 4 | 0,1,20,1 | declmove base->0 | known dead end (base/walker copy) |
| TitleCheck_NewClearedRecord_Race | 28 -> 28 | 0,1,20,1 | declmove mode->0 | |
| clNormal3D_SetScale | 22 -> 22 | 0,4,20,1 | propoff | |
| fn_801826F8 | 190 -> 190 | 0,8,20,1 | - | variants all broke opcodes (129 opc diffs) |
| fn_801B9928 | 42 -> 42 | 0,7,20,0 | - | variants all broke opcodes (101 opc diffs) |
| fn_801F2BC8 | 42 -> 42 | 0,5,20,1 | hoist-front | |
| fn_80203C24 | 14 -> 14 | 0,2,1,0 | - | graph edit unknown |
| fn_8023DCEC | 110 -> 110 | 0,1,20,1 | hoist-back | |
| fn_8028A3EC | 22 -> 22 | 0,5,20,0 | hoist-front | |
| result_screen_update | 20 -> 20 | 0,2,1,0 | - | graph edit unknown |

No `inline[...]` or `boolnorm` move reached the diagnosed set of any fn.
