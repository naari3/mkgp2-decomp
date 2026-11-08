# ItemSelect child sprite (anon_8023DCEC) native C++ — 2026-11-04

Source: Codex worker cx_a1_itemselsprite_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

## Observed
- E154/E19C/E1E4/E2F8 (ItemSelectChildSpriteMethods.cpp) and E324 (ItemSelectChildSpriteUpdate.cpp): native text/extab/extabindex/.data exact.
- E1E4 must use float literals, not extern constants, to avoid CSE across endpoint checks.
- E324 color constant is 0x7F7F7FFF; declare the overlay local before the enabled byte to get the target r28/r29 identity.
- Ctor EA80 / Dtor E808: real C++ `new` expressions, canonical FlowFaderF/I, VHolder throw() members, ResCtrl and ItemAliasSprite compile to exact 1208/632 bytes. Mangled names are bridged per TU in `tools/extab_user_renames.json` (same recipe as `cpp-ctor-retrofit-mangled-bridge.md`). Object-level extab/extabindex % are < 100 because the object also carries EH for the weak canonical destructors; the linker discards them and the actual main.elf owned extab/extabindex ranges equal the original (full DOL SHA-1 exact).
- Draw DCEC: best 86.024826% after 3 structural approaches (scalar direct fields 81.13%, inline position/scale setters with corrected FP declarations 86.02% kept, vector-value helpers 69.54% discarded: more frame/copies). Kept honest NonMatching; do not retry without new type/control-flow evidence.
- No manual assembly or EH.

## c16_u29_20261106
Source: Codex worker c16_u29_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u29: fresh DCEC86.024826. Explicit const float originX/originY pointers before ResCtrl, stride2 indexing, explicit pair cursor incremented inside body, and (unsigned char)active condition restore F0 frame/r23-r31 save/selfr27/activer28 and improve93.40426. TU-local ResCtrl ctor/dtor and @132/@133 EH bridges improve93.42199, extab92.85714/index95. Source1108 vs target1128B. Residual hoisted origin bases, folded offset addressing, x/y FP webs and effect/pair/pulse homes; singleton remainsNM. No B cut. Fallback DOL SHA1OK.

## c18_u220_20261107
Source: Codex worker c18_u220_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u220: own rodata803E5878..803E5CE8 as separate native scales[3], curves[18][7][2], origins[4][2], effect positions[2][2], genuine zero positional offsets[4], and three class-name strings. Direct origin references restore late section-base calculations vs c16 column pointers. Canonical1.0f symbol plus late explicit Y column gives direct objdiff93.42199->95.21277 (report95.2305), EH96.428566/index95/rodata100. Source1132 vs1128B; first origin base coalescing, setter FP scratch order, effect/pair and overlay/pulse GPR homes remain. Reversed setter args, scalar placement helpers and pair-first effect-helper boundary do not solve DAG/register residuals. One source rodata tail byte is natural string alignment, no filler. NonMatching, no B cut, full fallback-linked DOL SHA1 ea30f3b1 OK; zero native gain.

## c21_p51_20261108
Source: Codex worker c21_p51_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p51: existing opt_dead_assignments off plus direct childOrigins[variant][0/1] (remove cached originY) restores first origin materialization and all setter FP/scheduling rows, 96.64893 -> 99.14893. Parent-receiver inline DrawEffect with position declared before effect, plus parent-receiver DrawOverlay with pulse declared before overlay, reaches99.53901/1128B. Only overlay receiver r24 vs targetr26 remains (26 rows +2AC..410); effect and pulse homes exact. Add own @136/@137 primary EH/index aliases, both sections100; rodata100 already owned803E5878..803E5CE8 unchanged. Outer named overlay receiver99.48582 (r29/pulse24), late declaration invariant; combined child-tail helper fails auto-inline23.195036; separate pulse predicate invariant99.53901. Best H3 kept NonMatching; singleton no B cut. Coordinator final fallback DOL SHA1ea30f3b1 exact; zero native gain.
