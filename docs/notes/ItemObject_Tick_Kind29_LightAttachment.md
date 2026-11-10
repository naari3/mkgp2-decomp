# ItemObject_Tick_Kind29_LightAttachment

Source: Codex worker c15_u54_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Remeasured original 95.57522% with exact production compile/postprocess command. Scalar zero-target interpolation must pass through a general static inline helper returning a*t+b*(1-t); direct 0.0f*t is folded away. This makes 0x800E0598..0x800E05B4 exact and raises function to 97.10177%. Remaining curve loop differs structurally: target fixed curve base + byte index + branch-local add; source has two pointer recurrences. Whole-loop helper, segment helper and independent time cursor did not reproduce target. Final source 896 B, target 904 B; extab payload exact, extabindex differs in size word. No TU split/native gain possible with this one-function TU.

## c18_u69_20261107
Source: Codex worker c18_u69_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u69: fresh production baseline 97.10177/896B -> 99.557526/904B by one ScaleCurve *segment=(ScaleCurve *)((char *)c+i*sizeof(float)) in branch, using segment x/y/z[0..1]. Using explicit &ItemObject_Tick_Kind29_LightAttachment_data_80420ED8 instead of c rematerializes global and regresses92.11947. Corrected shared-local form gives exact target operation/order and EH8/index12. Remaining15 rows are base/cursor/index r3/r4/r5 vs r4/r5/r3 and initializer FP const/scale/frame f1/f2/f0 vs f2/f0/f1. Decl index-before-c is invariant; corrected whole-loop inline helper97.42478; separate frame99.38053; explicit float/struct time cursors98.26549/99.11504; external80 literal is invariant. Keep NonMatching; singleton TU no B cut. Final coordinator fallback DOL SHA1 exact; native gain0.

## c19_u116_20261107
Source: Codex worker c19_u116_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u116 retry: 99.557526 -> 99.73451% by static inline Vec_SetUniform(Vec*,float), called instead of three direct F(0xC4) assignments. Fixes all initializer FP homes without changing text904/extab8/index12. Remaining eight rows only curve base/cursor/index target r3/r4/r5 vs source r4/r5/r3. Unsigned index folds recurrences, regresses96.89823/896B; segment-only accessor99.40266/904B; table-address getter, const views, and file-static table ownership are invariant99.73451. Only uniform-vector helper retained; no ranges/flags changed. Final coordinator fallback DOL SHA1 exact; native gain0.
