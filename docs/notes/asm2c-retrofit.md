# asm2c-retrofit

Source: Codex worker c6_oa_asm2c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 2516 B.

asm_fn -> C retrofit (c6, 2026-11-05): in -Cpp_exceptions off TUs with manual extab, put '#pragma exceptions on/reset' around the C bodies and delete the manual extab for converted functions; compiler extab bytes matched (0x224A.., 0x080A.., 0x100A.., 0x408A..). A mixed TU (one asm left) needs a tools/extab_order.json entry. 'extern const float' for shared sdata2 constants lets MWCC hoist loop invariants (plain externs are reloaded after each call). postprocess_sdata2 renames the anonymous int->float magic double automatically.
