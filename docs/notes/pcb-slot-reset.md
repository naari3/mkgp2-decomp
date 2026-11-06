# pcb-slot-reset

Source: Codex worker c15_u59_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 196 B.

c15_u59: PcbSlot_ResetScratchAreas 800851BC/196B unlocked 94.69388 -> 100%. Typed PcbScratchSlot[4] global with &array[index] inside inline reset removes extra addi r0/mr r29,r0. Unsigned-char local:1 flags member matches target extrwi versus raw byte >>7 yielding srwi. Cursor declared before row fixes r30/r31 swap. Existing Cpp_exceptions on emits exact EH8/index12; no EH actions/bridge required. Matching source input and coordinator full DOL SHA-1 exact; native gain1fn/196B.
