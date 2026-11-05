# ai-new-tu-lane

Source: Codex worker c6_nt4_ai_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c6_nt4_ai: nine new singleton NonMatching splits preserve full DOL SHA-1. AI_PerKartUpdate (99.797295) and fn_801E9CBC (99.72727) have exact text lengths/EH but item-pointer/result register coalescing differs. AI_SystemDtor (98.21568) differs only in 0/-1 constant registers in the reset loop; direct-body and nested-helper probes did not resolve it. AI_UpdateItemUseLogic -proc 750 reproduces scalar-only FPR save and exact 0x30480000 extab; GC/2.6 generated identical tested output to GC/1.3.2. No manual EH, new asm, forced sections, embedded opcode data, or padding objects were introduced.
