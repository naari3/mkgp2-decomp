# KartItem_QueryEffectStateFromIse

Source: Codex worker c15_u70_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 216 B.

Observation: first u64 flag test uses byte-returning helper merge (bne, unconditional branch, li 1, clrlwi), while later flags use direct u64 tests. A static inline unsigned-char helper returning 0 for masked value == 0 and 1 otherwise yields 100% with GC/1.3.2 production flags. Explicit XOR with a zero local emits redundant XORs and separates the boolean register (92.22%). This is source-shape evidence for an inline helper, not proof of original helper naming.
