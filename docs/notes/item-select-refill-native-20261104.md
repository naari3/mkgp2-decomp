# ItemSelect refill/setup/update (anon_802386E0, cxb_r1, 2026-11-04)

Source: Codex worker cxb_r1_itemsel386_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

- fn_80238980 setup (1052B) native exact incl. 24B automatic DELETEPOINTER extab + extabindex: genuine `new TextManager`, per-TU ctor bridge to TexMgr_Init, `-Cpp_exceptions on` + lmw/stmw. In the four-text-manager loop declare `int i` before the explicit cursor (i=r29, cursor=r28); the reversed declaration leaves a pure r28/r29 swap at 99.79%.
- Honest NonMatching after 3 approaches: fn_802386E0 refill 91.79% (direct scalar 77.38%, explicit layout pointers/top-tested wait 90.15%), fn_80238D9C update 87.94%.

## c15_u68_20261106
Source: Codex worker c15_u68_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u68: direct fresh baseline91.791664 (assignment report93.13). Adding void *playerData argument to CompleteChoice, passing g_playerData, and capturing caller playerData=g_playerData restores two distinct hoisted pointer webs, r22-r31 saves, exact672B size and extab8/index12 at100%. Text93.9881 remains NM. Localizing helper layout/resources91.89286; whole-loop helper exceeds inline threshold; item-table pointer-argument helper is invariant. Residual table base +C0 folding, self/resources/x/y/choice/player-data register homes, choice count/zero scheduling and position scratch homes. No legal singleton split; fallback full DOL SHA1OK.

## c16_u19_20261106
Source: Codex worker c16_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u19: fn_80238D9C baseline87.93535/1840B ->90.24354/1856B. Caller playerData snapshot plus separate SelectChoice pointer parameter restores hoisted caller global web; helper global still rematerializes after grid getter. Explicit float slide temporary, even with existing fp_contract pragma unchanged, restores target separate multiply/add where inline return expression fused. Bitwise alpha insert gives clrlwi/oris/ori (target li/rlwimi). Byte-stride GridItem plus resources argument improves small amount; target subarray-base materialization and GPR cycles remain. Automatic owned extab28/index12 now100; jump table0 due branch offsets. Singleton stays NonMatching; fallback full DOL SHA1 exact.
