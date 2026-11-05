# asm-retrofit-c11-a2

Source: Codex worker c11_a2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 532 B.

GetKartParamBlock: separate default/case0 and case1 switch bodies plus pointer-to-three-element-row table reproduce exact 140 B. ResetIOPorts: unsigned-char 1+7 bitfield layout reproduces hoisted li/rlwimi and lbzu chain; cache role in an explicit local to restore pointer/role registers. ISESlot_Init: 0.0f literal rather than named external float produces exact store scheduling; remove Init manual EH, add per-TU extab order [Init,Dtor,Toggle]. Full-link DOL SHA-1 OK; +3 true C / 532 B.
