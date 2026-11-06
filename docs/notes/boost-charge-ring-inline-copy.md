# boost-charge-ring-inline-copy

Source: Codex worker c15_u3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 772 B.

EffectVfx84_85_BoostChargeRing_Tick residual 99.93782% was entirely stack offsets for three Vec copies. Replacing the explicit position local with a value-taking static inline helper that calls VfxSlot_SetPositionFromVec(slot, &pos) restored target temporary order: transform1 sp+0x20, transform2 sp+0x14, position sp+0x08. Native .text/extab/extabindex 100%, full DOL SHA-1 verified. This is evidence of an inlined value-copy setter, not a register allocation problem.
