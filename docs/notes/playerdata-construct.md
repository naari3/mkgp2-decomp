# playerdata-construct

Source: Codex worker c13_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u49: PlayerData_Construct 801D7160 baseline direct compile 94.89667%. Inline int RollRareItem(){return rand()%20==0;} followed by !=0 restores target double boolean normalization (srwi then neg/or/srwi) in three rare-item checks. Enclosing-scope count declaration fixes most nested-loop register homes. Retained 98.83%, 1204B vs target1200. Residual count/cursor r22/r21 vs target r21/r22 and hoisted pool+1DC8 debug format, mileage i/item colors. Inline whole mileage helper leaves same score and extra hoisted instruction; reverted. Single-function TU stays NonMatching; full fallback DOL SHA-1 OK.

## c17_u96_20261107
Source: Codex worker c17_u96_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u96: fresh GC1.3.2 direct compile is 98.83%, source1204B vs target1200B (report99.01). Narrow static inline GrantMilageItem(character,pool), containing only character-select/item-select/grant/debug, makes item r20 exact and improves98.863335% (report99.03); retained. Remaining count/cup-cursor r22/r21 vs targetr21/r22, hoisted pool+1DC8 format in r21, mileage i r22 vs targetr19. Explicit cupRanks row pointer97.27333 loses target strength reduction and rotates loop homes. Direct global pool reference inside award helper98.19666 adds duplicate pool lis/addi (1212B); both reverted. Three approaches exhausted. Text1204/EH8/index12, EH100/index91.66667 unchanged. Single-function NM has no rescue split. No data/flag/map changes, no native gain. Coordinator fallback-linked full DOL SHA1 exact.

## c18_u161_20261107
Source: Codex worker c18_u161_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 440 B.

c18_u161: GC1.3.2 fresh direct objdiff starts98.863335%,1204B. A const external ConstructPool aggregate view (defaults at+1280, mileageError array at+1DA4, grantMessage array at+1DC8), with pool=&lbl_8039C718 and direct member references, removes the hoisted format pointer and yields99.8%,1200B,EH/index100 without any data definition or split change. Reusing first mode-count parameter after copying it into modes[0] fixes count/cup-cursor r21/r22 swap, reaching99.916664%. Residual only mileage index r21 vs targetr19 at801D7568/7570/75F0/75F4. Complete progression-loop inline helper98.363335; moving count declaration after round98.54667; mileage cup-variable reuse invariant on baseline and best. Six hypotheses exhausted; retained best genuine draft NonMatching. Base pool is already owned by Matching fn_801D5F74.c, so no pool transfer allowed. One function prevents mechanism B. Final coordinator full build DOL SHA1ea30f3b1 OK; fallback input, zero native gain.

## c19_u84_20261107
Source: Codex worker c19_u84_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1200 B.

c19_u84: PlayerData_Construct 801D7160 reaches100%/1200B, EH8/index12 exact. Replace truncated MilageEntry view with canonical CoinMilestone (neutral codegen). Split mileage index from flag-fill i and move maximum/mileage into a dedicated block: declaring mileage before maximum gives99.86667 with mileage r18/max r19; declaring maximum before mileage gives target mileage r19/max r18 and100%. No pool/data transfer or EH bridge required. Matching source object confirmed on main.elf edge; coordinator full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Native gain1fn/1200B.
