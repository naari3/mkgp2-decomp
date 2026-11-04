# misc3d helper family (0x801678FC..0x801695E0) — 2026-11-05

Source: Codex worker cxc_u2_misc3d167_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, SHA-1 OK, actual main.elf ranges).

## Native (source-linked)
- fn_801678FC, fn_8016918C, fn_80169468: canonical FlowScene.h `ResCtrl` local, empty inline dtor, per-TU bridge in tools/extab_user_renames.json. Text and primary owned EH/extabindex bytes+relocations exact; the extra weak dtor EH entry in the object is discarded at link (object-level extab reads ~86 %, linked bytes exact).
- RGBA pack: `((u8)(int)(scale*red)<<24)|...` with scale `lbl_806D8A10`.

## Honest NonMatching (12 drafts, src/game/misc3d/fn_8016*.cpp)
- Text RGBA variants need a different fctiwz scheduling and redundant masks; direct expression, inline pack helper and named byte temps all give the same output.
- Alpha-only variant: target loads -256 early and inserts alpha with rlwimi; direct OR becomes clrlwi+oris+ori, addition gives clrlwi+subi.
- Timer fn_80167A24 99.62 %: 9 instructions differing only in f10/f11/f12 identities; named constant locals and inline switch invariant.
- Text helpers keep a sibling-private 0x234 TextManager layout (FlowScene.h TextManager is 0x230 with an out-of-line dtor).
No impossibility claim.
