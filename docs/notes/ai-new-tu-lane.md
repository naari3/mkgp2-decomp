# ai-new-tu-lane

Source: Codex worker c6_nt4_ai_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c6_nt4_ai: nine new singleton NonMatching splits preserve full DOL SHA-1. AI_PerKartUpdate (99.797295) and fn_801E9CBC (99.72727) have exact text lengths/EH but item-pointer/result register coalescing differs. AI_SystemDtor (98.21568) differs only in 0/-1 constant registers in the reset loop; direct-body and nested-helper probes did not resolve it. AI_UpdateItemUseLogic -proc 750 reproduces scalar-only FPR save and exact 0x30480000 extab; GC/2.6 generated identical tested output to GC/1.3.2. No manual EH, new asm, forced sections, embedded opcode data, or padding objects were introduced.

## c13_u8_20261106
Source: Codex worker c13_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u8: AI_CalcVSTargetSpeed 801E93AC improves97.70492->98.85246 via TU-local literal10.0f/1000.0f scaling helpers, in-place initial scale multiplies, record declared before controller and lap before rank. All FPR instructions now exact, text488/EH8/index12 preserved. Direct NormalSpeed body in caller worsens94.81967 and adds f29/frame. Remaining self/initial ctrl/cup/round/index and normal table/rank/lap GPR identities; retained singleton NonMatching. Full fallback DOL SHA-1 OK.
