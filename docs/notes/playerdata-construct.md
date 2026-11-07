# playerdata-construct

Source: Codex worker c13_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u49: PlayerData_Construct 801D7160 baseline direct compile 94.89667%. Inline int RollRareItem(){return rand()%20==0;} followed by !=0 restores target double boolean normalization (srwi then neg/or/srwi) in three rare-item checks. Enclosing-scope count declaration fixes most nested-loop register homes. Retained 98.83%, 1204B vs target1200. Residual count/cursor r22/r21 vs target r21/r22 and hoisted pool+1DC8 debug format, mileage i/item colors. Inline whole mileage helper leaves same score and extra hoisted instruction; reverted. Single-function TU stays NonMatching; full fallback DOL SHA-1 OK.

## c17_u96_20261107
Source: Codex worker c17_u96_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u96: fresh GC1.3.2 direct compile is 98.83%, source1204B vs target1200B (report99.01). Narrow static inline GrantMilageItem(character,pool), containing only character-select/item-select/grant/debug, makes item r20 exact and improves98.863335% (report99.03); retained. Remaining count/cup-cursor r22/r21 vs targetr21/r22, hoisted pool+1DC8 format in r21, mileage i r22 vs targetr19. Explicit cupRanks row pointer97.27333 loses target strength reduction and rotates loop homes. Direct global pool reference inside award helper98.19666 adds duplicate pool lis/addi (1212B); both reverted. Three approaches exhausted. Text1204/EH8/index12, EH100/index91.66667 unchanged. Single-function NM has no rescue split. No data/flag/map changes, no native gain. Coordinator fallback-linked full DOL SHA1 exact.
