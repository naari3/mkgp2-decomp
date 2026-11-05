# asm2c-retrofit

Source: Codex worker c6_oa_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 2516 B.

asm_fn -> C retrofit (c6, 2026-11-05): in -Cpp_exceptions off TUs with manual extab, put '#pragma exceptions on/reset' around the C bodies and delete the manual extab for converted functions; compiler extab bytes matched (0x224A.., 0x080A.., 0x100A.., 0x408A..). A mixed TU (one asm left) needs a tools/extab_order.json entry. 'extern const float' for shared sdata2 constants lets MWCC hoist loop invariants (plain externs are reloaded after each call). postprocess_sdata2 renames the anonymous int->float magic double automatically.

## c7_od_asm2c_20261105
Source: Codex worker c7_od_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 604 B.

c7_od_asm2c_20261105: ParticleBurst_Draw: colour bytes read from a u8[6][3] table must be held in int locals and passed to a GXColor4u8(u8..) inline to get the target r28/r27/r26 (u8 locals reverse the coloring). A C TU without -use_lmw_stmw needs '#pragma use_lmw_stmw on/reset' around the body to get stmw. fn_80141990 (LogoAnim, cplusplus TU): 'delete p' on a class with an undefined virtual dtor reproduces the null-checked vtable+0x8 call with flag 1, and no vtable is emitted. Kept as asm: ParticleBurst_DrawCb (redundant p?p:0 select, a fakematch in C), ParticleBurst_Update (99.64 %, callee-saved FPR rank of loop-invariant constants) and fn_80141454 (~95 %, volatile compare-constant coloring plus block temp coalescing).
