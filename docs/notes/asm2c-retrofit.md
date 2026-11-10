# asm2c-retrofit

Source: Codex worker c6_oa_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 2516 B.

asm_fn -> C retrofit (c6, 2026-11-05): in -Cpp_exceptions off TUs with manual extab, put '#pragma exceptions on/reset' around the C bodies and delete the manual extab for converted functions; compiler extab bytes matched (0x224A.., 0x080A.., 0x100A.., 0x408A..). A mixed TU (one asm left) needs a tools/extab_order.json entry. 'extern const float' for shared sdata2 constants lets MWCC hoist loop invariants (plain externs are reloaded after each call). postprocess_sdata2 renames the anonymous int->float magic double automatically.

## c7_od_asm2c_20261105
Source: Codex worker c7_od_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 604 B.

c7_od_asm2c_20261105: ParticleBurst_Draw: colour bytes read from a u8[6][3] table must be held in int locals and passed to a GXColor4u8(u8..) inline to get the target r28/r27/r26 (u8 locals reverse the coloring). A C TU without -use_lmw_stmw needs '#pragma use_lmw_stmw on/reset' around the body to get stmw. fn_80141990 (LogoAnim, cplusplus TU): 'delete p' on a class with an undefined virtual dtor reproduces the null-checked vtable+0x8 call with flag 1, and no vtable is emitted. Kept as asm: ParticleBurst_DrawCb (redundant p?p:0 select, a fakematch in C), ParticleBurst_Update (99.64 %, callee-saved FPR rank of loop-invariant constants) and fn_80141454 (~95 %, volatile compare-constant coloring plus block temp coalescing).

## c8_og_asm2c_20261105
Source: Codex worker c8_og_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 2968 B.

c8_og_asm2c_20261105 (Opus): (a) A function whose top level inlines a sibling that now lives in another TU, while the once-inlined self-recursion still calls it (ObjectTree_BlendOrCopy -> Object_CopyFieldsRotPosScale): declare the sibling 'extern inline' with its body. MWCC inlines it but emits no definition, so the remaining call binds to the global. (b) Inlining a cross-TU helper (SpriteSlot_SetAnimFrameAndApplyScale in SpriteSlot_TickAnim): float literals instead of 'extern const float' labels changed FPR coloring to the target; postprocess_sdata2 renames them. A signed char parameter (not int) avoids the extsb copy when the caller passes an s8 field. Direct tbl[i].anims[j].f indexing versus a pointer local in an accessor chooses 'add + lfs d(r)' versus 'addi + lfsx'. (c) fn_80116DD0 parked at 99.86 %: load+compare+call-arg in r3 then 'mr r29' (live-range split); no source form tried reproduced it.

## c16_o22_asm2c_20261106
Source: Codex worker c16_o22_asm2c_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 2276 B.

c16_o22 (Opus): (a) fn_80116DD0's split live range (value loaded into r3 and compared, then mr r29,r3 before the first call) is reproduced by assigning the local inside the call argument: `if (ctx->anim) { void *a; AnimState_Step(a = ctx->anim); ...uses of a... }`. (b) Variadic panel-text helpers: `char buf[256] = {0}` copies a 0x100 zero template from .rodata, so give the TU that rodata range in splits.txt. (c) The PreviewModel ctor and base dtor compile to 100 % text in C++, but the base dtor copy lands right after the ctor. In the original it came from vtable emission at TU end (clCSModelInterface_vtable_8048EAE8 = {RTTI,0,dtor_8013DCBC,fn_8013DD04}), so the vtables must be in TU-owned .data. (d) clFlowKart_UpdateDisplay: the threshold tables are static arrays in clFlowKart_Init.c's pooled .rodata, addressed as addi base+0x3FC; lwzx. A struct view gives add + lwz 0x3FC. Blocked until those TUs are merged.
