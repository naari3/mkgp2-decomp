# KartFx dispatch native reconstruction

## Group B AuxStarBurst (2026-10-22)

The complete 432-byte function matches first-approach ordinary C++ with native
8-byte EH and 12-byte index. Keep unused r3/r5 ABI slots: payload arrives in r4
and enabled in r6. Signed active40 and unsigned timer80/previous81 have distinct
roles. Decrement the timer before the star dispatch; a zero timer does not clear
the new effect's variant. Preserve the mode2 gate after the first dispatch,
independent enabled/edge guards and all nested wing/horn loops. use_lmw_stmw on
reproduces the observed saved range without assembly. Local padded views claim
only observed fields, not a complete shared KartFx class. External callback
names and accesses were checked against actual target ASM, not live Ghidra.

Worker source-linked full DOL SHA1 and direct text/EH/index are exact; main
independently revalidates the same gates before acceptance. No opcode/manual-EH
patches, generated data ownership or fallback-based progress are involved.
