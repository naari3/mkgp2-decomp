# playerdata-construct

Source: Codex worker c13_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u49: PlayerData_Construct 801D7160 baseline direct compile 94.89667%. Inline int RollRareItem(){return rand()%20==0;} followed by !=0 restores target double boolean normalization (srwi then neg/or/srwi) in three rare-item checks. Enclosing-scope count declaration fixes most nested-loop register homes. Retained 98.83%, 1204B vs target1200. Residual count/cursor r22/r21 vs target r21/r22 and hoisted pool+1DC8 debug format, mileage i/item colors. Inline whole mileage helper leaves same score and extra hoisted instruction; reverted. Single-function TU stays NonMatching; full fallback DOL SHA-1 OK.
