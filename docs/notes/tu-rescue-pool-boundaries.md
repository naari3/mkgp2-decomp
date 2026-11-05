# tu-rescue-pool-boundaries

Source: Codex worker c2_i13_texp_lobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 37 fn / 10572 B.

texp/lobj isolation: inspect cross-object pool references before promoting a text-exact run. Keep shared assertion/string pools in a fallback TU and use correctly sized extern declarations in native wrappers. Keep actual large pools large (>8-byte declaration) so MWCC emits LIS/ADDI; small strings need sized <=8-byte declarations for SDA21. objdiff direct diff synthesizes R_PPC_NONE string-pool relocations; use -c ppc_calculate_pool_relocations=false to compare actual instructions and real relocations, and report that setting. A typed GXTevAlphaArg[4] global at lbl_804FDBC4 bridges the inline alpha allocator table to the native texp_assign TU. lobj default_class was renamed lobj_default_class because other TUs have local symbols with the same name.

## c3_u13_mapeffect_20261105
Source: Codex worker c3_u13_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1740 B.

c3_u13: TExpAssignReg 802E04C0..802E0B8C is an independent exact 1740-byte TU when AssignAlphaReg is static inline using existing canonical global lbl_804FDBC4[4], __FILE__ uses existing lbl_806D0F38[7], and val>=0 assertions use existing lbl_804FDC64[9]. Keep full data 804FDC64..804FDCF0 and sdata2 806DCED0..806DCEE0 with tail fallback. Its leading string must remain present in native draft tail as ordinary char lbl_804FDC64[]="val >= 0". Source prefix emits no local out-of-line helper. All named functions present. Full-link acceptance pending.
