# FrameSelection native retry (2026-10-25)

TU `src/ui/FrameSelection_Methods.c` (extab group singletons, .text 0x801C4EA8..0x801C5C34).
Prior attempt (2026-08, worktree `batch_text_801c4ea8_frameselection`, base 45b7edf) parked
all four at Init 98.4 / Confirm 95.1 / Update ~99.9 and kept asm. That attempt was cut off
by API quota; its C++ bodies were the starting point here.

## Result

| fn | addr | size | state |
|---|---|---|---|
| FrameSelection_Init | 0x801C4EA8 | 0x4F8 | asm kept; native candidate 99.906% (in `#if 0`) |
| FrameSelection_Confirm | 0x801C53A0 | 0x2FC | native C++, 100% |
| FrameSelection_Draw | 0x801C569C | 0x1F4 | native C++, 100% |
| FrameSelection_Update | 0x801C5890 | 0x3A4 | native C++, 100% |

TU is compiled with `-Cpp_exceptions on -lang=c++ -use_lmw_stmw on`. Confirm/Draw/Update
extab entries are CW auto-emitted; Init keeps the manual `.extab_user` emit
(`tools/extab_order.json` declares the address order). Full DOL SHA-1 OK.

## Log (chronological)

### 1. Draw (observation)
The prior C body for Draw is instruction-identical. Its only objdiff residue was the
`lfd DOUBLE_INT2FLOAT_MAGIC` reloc staying an anonymous `@NNN` .sdata2 local.
Cause (observed): `tools/postprocess_sdata2.py` aligned our SDA21 relocs with the target
object by raw `.text` offset; any extra function in our `.text` (here the weak
`__dt__6TexMgrFv` copy that the native ctor emits between Init and Confirm, discarded at
link) shifts every later function. Fix: the tool now also keys relocs by
(containing function, offset in function) and prefers that match. Full clean rebuild of all
744 source objects still gives DOL SHA-1 OK.

### 2. Confirm (observation)
With `u16` parameters in the `DrawNamCamImage` prototype instead of explicit `(u16)` casts at
the call site, the prior "list scheduler" residue (95.1%) disappeared; what remained was a
pure GPR coloring swap: target self=r30 / player=r31 / confirmed=r29 / cfgX=r31 / cfgY=r29,
ours self=r31 / player=r30 / cfgX=r29 / cfgY=r30.
- `--colorer` dump: the `self` web (key 34, degree 17) is popped first and takes r31.
- No effect: member function (`this`), `self = this` alias at the top or after the early
  return, input-poll part split into an inline helper.
- 100%: everything after `if (field_0x2c != -1) return field_0x2c;` moved into a
  `static inline int ConfirmTick(clFlowNamcamRec *self)` called from Confirm.
- Side effect: Confirm became small enough that `-inline auto` inlined it into Update
  (Update 22%). `#pragma auto_inline off` / `reset` around the Confirm definition keeps the
  `bl FrameSelection_Confirm` in Update while the explicit inline helper is still expanded.
  (`#pragma dont_inline on` around Confirm blocks the helper too; auto_inline off placed
  around Update instead of Confirm does not stop the inlining.)

Hypothesis: the spliced helper parameter is a new, later-born web, so `self` is no longer the
first-popped node; consistent with phase2f "inline splice renumbers web keys"
(`docs/notes/cw132-allocator-phase2f-research.md`, regime B).

### 3. Update (observation)
Prior residue: namcam pointer r29 vs target r30 (4 instructions). Both of these give 100%:
the capture pump as a `static inline` helper taking `NamCamObj *`, or as an inline member
`NamCamObj::Pump()` (adopted). Stack slots (handle 0x8, out 0xC) unchanged.

### 4. Init (observation)
- With extern overlays for the tables (`extern struct {...} g_charaStatTable`), CW does not
  hoist the two table bases into the prologue: 84.3%. The target addresses .data
  0x8049AA58..0x8049AC90 and .rodata 0x8039AA40..0x8039B05C through CSE'd bases
  (`...data.0` / `...rodata.0` pool symbols), so the TU must own those ranges.
- Defining them in the TU (split lines below, data generated from the original DOL, section
  bytes 100% in objdiff): 98.396%.
- `int f = GetFrameIdxFromVisualIdx(this, i); if (f == (s8)g_playerData[0x1b8])` fixes the
  `cmpw r3, r0` operand order (writing the call directly in the condition gives
  `cmpw r0, r3` in either operand order).
- The third loop written with a block-scoped `for (int k = 0; ...)` instead of reusing the
  function-scope `i` gives the target `li r27, 0 / li r28, 0` (the prior attempt's `mr r28,
  r27` residue). 99.906%.
- Remaining: prologue `lis r5, g_charaStatTable@ha / lis r4, lbl_8039AA40@ha` vs ours with
  .data and .rodata swapped (r4/r5 only; the addi destinations r30/r29 match).
  - Reordering the data definitions (.data before/after .rodata) does not change it.
  - Defining the .rodata objects after the functions: worse (92.5%, rodata not pooled).
  - Our object creates `...data.0` (symtab index 8) before `...rodata.0` (index 9).
  - A probe function defined before the ctor with five .rodata-pool uses across calls makes
    the ctor 100.0% (probe only; it adds code and is not a solution).
- Target: `clFlowChara_Update` (0x801C3D48, separate TU `game/clFlowChara_Update.c`) loads
  `lbl_8039AA40` in its prologue (0x801C3D50) before any .data-pool reference.

Hypothesis: CW emits the pool-base loads in the order the pool symbols were created, i.e.
the first pooled reference anywhere earlier in the TU. In the original TU clFlowChara_Update
(and the other clFlowChara functions) preceded the ctor, so the native ctor can only be
exact when it shares a TU with those functions. Not tried: forcing an earlier codegen
reference through a discarded weak inline copy (would need a body that is not genuine).

## To promote Init later
1. Enable the `#if 0` block in FrameSelection_Methods.c (drop the asm include), and remove
   the Init-only extern decls that conflict with the definitions.
2. splits.txt for this TU:
   ```
   	.rodata     start:0x8039AA40 end:0x8039B05C
   	.data       start:0x8049AA58 end:0x8049AC90
   ```
3. extab_user_renames.json for this TU: `__ct__14FrameSelectionFv -> FrameSelection_Init`,
   `__ct__10clFlowBaseFv -> InitializeFrameSelection`, `__dt__10clFlowBaseFv -> dtor_801BA14C`,
   `__ct__7ResCtrlFv -> ResCtrl_Init`, `__dt__7ResCtrlFv -> dtor_80082960`,
   `__ct__6TexMgrFv -> TexMgr_Init`, `__dt__6TexMgrFv -> dtor_800869D0`,
   `__ct__6SpriteFiiffffff -> Sprite_CreateWithParams`, `__ct__7Scene3DFPCc -> Scene3D_Init`,
   `__ct__10SceneModelFPCci -> SceneModel_Init`; drop the two manual Init extab names.
4. extab_order.json: append `dtor_800869D0` (weak TexMgr dtor copy) to the TU list.
5. Resolve the pool-base order (see hypothesis above).
