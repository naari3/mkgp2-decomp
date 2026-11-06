# newtu-c13-u35

Source: Codex worker c13_u35_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801F6C2C: numeric float literals 1/.5/0 restore half/invHeight allocation (95.933334 ->96.4). Declaring x before height restores x=f3 / height=f9 and all arithmetic scheduling, yielding 99.73333 with exact 300B text and EH8/index12. Residual only two fmuls operand-order swaps at 801F6CB4/801F6CBC. Staged += normalization perturbs webs (94.666664); reversing direct multiply operands is invariant. Single-function TU remains NonMatching, full fallback-linked DOL SHA-1 OK.

## c16_u131_20261106
Source: Codex worker c16_u131_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 300 B.

c16_u131 resolves the two remaining fmuls operand-order swaps by extracting static inline float TextureScaleCoordinate(float coordinate, float inverseSize) { return coordinate * inverseSize; }, used only for left/top near-edge expressions. Direct expression reversal was invariant in c13; the inline parameter boundary restores f3*f7 and f1*f5 with every other instruction unchanged. Native text300/extab8/index12 all100; Matching source object in main.elf, symbol801F6C2C/300; full DOL SHA1 exact.
