# triforce-random-unlock

Source: Codex worker c16_u41_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 8 B.

c16_u41: GC/1.2.5n original nonvolatile seed already emits target reload pattern; volatile adds two extra loads per generator. Swapping multiply/add operands leaves baseline assembly unchanged. Explicit u64 random intermediate changes frame and product registers (fn B8 56.86%, fn 864 88.29%); reverted because another function regressed. Mechanism B isolates setter as native 8B; generators remain original percentages. Target seed split 806D0C18..806D0C20 includes 4 zero bytes at 806D0C1C..20 beyond emitted u32. Likely trailing alignment, not established second semantic field; no padding object added. Data stays in NonMatching TU.
