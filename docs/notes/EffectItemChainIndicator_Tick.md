# EffectItemChainIndicator_Tick

Source: Codex worker c15_u14_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

2026-11-06 c15_u14: Standard postprocess_sdata2 already maps signed-char conversion literal to lbl_806D5378; old source comment was obsolete. Only residual is reversed order of addi r30,r1,0x9c and mr r31,r28 at target 0x800BF9F0. Inline whole child-update loop and explicit scoped endpoint pointer both retain cursor-before-endpoint setup while changing register/stack allocation; both reverted. extab/extabindex 100%. Single-function TU has no mechanism B opportunity.
