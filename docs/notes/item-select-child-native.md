# ItemSelect child sprite (anon_8023DCEC) native C++ — 2026-11-04

Source: Codex worker cx_a1_itemselsprite_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

## Observed
- E154/E19C/E1E4/E2F8 (ItemSelectChildSpriteMethods.cpp) and E324 (ItemSelectChildSpriteUpdate.cpp): native text/extab/extabindex/.data exact.
- E1E4 must use float literals, not extern constants, to avoid CSE across endpoint checks.
- E324 color constant is 0x7F7F7FFF; declare the overlay local before the enabled byte to get the target r28/r29 identity.
- Ctor EA80 / Dtor E808: real C++ `new` expressions, canonical FlowFaderF/I, VHolder throw() members, ResCtrl and ItemAliasSprite compile to exact 1208/632 bytes. Mangled names are bridged per TU in `tools/extab_user_renames.json` (same recipe as `cpp-ctor-retrofit-mangled-bridge.md`). Object-level extab/extabindex % are < 100 because the object also carries EH for the weak canonical destructors; the linker discards them and the actual main.elf owned extab/extabindex ranges equal the original (full DOL SHA-1 exact).
- Draw DCEC: best 86.024826% after 3 structural approaches (scalar direct fields 81.13%, inline position/scale setters with corrected FP declarations 86.02% kept, vector-value helpers 69.54% discarded: more frame/copies). Kept honest NonMatching; do not retry without new type/control-flow evidence.
- No manual assembly or EH.
