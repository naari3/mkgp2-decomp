# pcbcheck-process-c19-u233-20261107

Source: Codex worker c19_u233_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Current base had already fixed c17 reset setup placement: fresh baseline text99.90169/extab100/index100, exact1424B. Extracting trailing slot flags/connection initialization plus ClearSlotData into static inline PCBCheck_InitSlot(PcbLinkSlot*,int) fixes final sample loop counter r29->targetr24 and improves99.95786. Only 80082DE8/DEC base copy direction remains (target addi r27;mr r28,r27; native addi r28;mr r27,r28). Six bounded hypotheses saved under build/w; explicit pointer induction adds r0 copy, ClearSamples helper/decl order/base getter invariant, direct caller ResetAll loop regresses reset homes. Best H4 retained; single-function NM so no A/B rescue/native gain.
