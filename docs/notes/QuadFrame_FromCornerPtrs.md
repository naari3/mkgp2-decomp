# QuadFrame_FromCornerPtrs

Source: Codex worker c21_u152_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u152: current 93.967155% baseline source is 1084 B versus target 1096 B, same 0xE0 frame and f24..f31 saves. Old source comment incorrectly called it register-only with two extra saves. Target midpoint slots ab=0x50, cd=0x44, ac=0x38, bd=0x2C; current source ac=0x50, ab=0x44, cd=0x38, bd=0x2C. Simply changing construction order worsens to91.60584/1116B. Member-wise return objects: subtraction93.74818, cross93.875916, combined80.00365; vector multiply/add midpoint66.175186. No pool-owner mechanism; singleton function cannot B-split. Next retry should investigate proper normalization ownership/API and temporary lifetimes rather than assuming register-only residue: norm(ab-cd) returns a reference to a temporary whose full expression ends at initialization.

## c22_u162_20261109
Source: Codex worker c22_u162_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22: lifetime issue fixed without codegen changes: bind const Vec &forwardDelta=ab-cd; then Vec &fwd=norm(forwardDelta). The direct binding extends the temporary through the whole function; baseline norm(ab-cd) leaves fwd dangling. Baseline-vs-final text/EH/index100%; target93.967155%. Named mutable fwd/right increases text score94.48175 but saves f23 too (frame0xF0/extab87.5), so archived only. Empty dtor57.653286 with out-of-line helpers; value-return norm70.868614/extab75. Literal constants88.43066; half alone88.357666; midpoint two-point constructor92.48175. All regressed EH and were reverted. Further progress needs an original vector/API model explaining stack temporary ownership and the cross-output reloads; blind midpoint order/FP permutations are exhausted.
