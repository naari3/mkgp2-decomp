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

## c14_u43_20261106
Source: Codex worker c14_u43_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u43: fn_801681E8 RGBA packing grouped as ((r<<8)|g)<<16 | ((b<<8)|a) improves fresh 92.162964 to 97.881485 (536 vs target540B). Constant literal conversion invariant; byte aggregate + setter adds stack stores and regresses88.95556. Residual conversion/FP/GPR scheduling remains; singleton NonMatching, no split rescue. Full fallback build SHA1 OK.

## c14_u51_20261106
Source: Codex worker c14_u51_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u51 fn_801685A4 singleton: grouped RG/BA pair expression (((cr<<8)|cg)<<16)|((cb<<8)|ca) improves fresh91.536 to97.712, primary492->496B vs target500B. Target red/green/blue/alpha conversion schedule and per-channel rlwimi packing remain different from pair expression. Left-associated repeated shift8 emits500B but91.232; unsigned-int promotions are invariant91.536. Owned EH/index section scores unchanged82.14286/61.11111. Existing ctor/dtor bridges retained. No singleton split rescue, NonMatching retained; full fallback-linked DOL SHA1OK, native gain0.

## c14_u52_20261106
Source: Codex worker c14_u52_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u52: fn_80168B90 grouped RG/BA packing improves fresh 91.536 to 97.712% (496 vs target500B). Typed inline byte pack is identical to flat baseline; explicit unsigned-short pairs identical to grouped expression. Residual color conversion/spill scheduling, FP/GPR homes and word insertion shape; owned EH range length remains one instruction short. Singleton retained NonMatching. Coordinator fallback build DOL SHA-1 OK; native gain0.

## c14_u54_20261106
Source: Codex worker c14_u54_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u54: fn_801695E0 alpha-only singleton improves 91.07692 ->92.61539 by removing unsigned-char cast before OR with 0xFFFFFF00 (upper bits forced to one). Text 264->260B and primary EH PC 0xD4->0xD0. Target early li(-256)/rlwimi remains oris/ori plus scheduling differences. Union RGB24/alpha8 spills to stack (90.215385); inline generic color-mask helper is invariant (91.07692). Three hypotheses exhausted, remains NonMatching, no split rescue. Coordinator full fallback-linked DOL SHA1 OK.
