# tu-rescue-pool-boundaries

Source: Codex worker c2_i13_texp_lobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 37 fn / 10572 B.

texp/lobj isolation: inspect cross-object pool references before promoting a text-exact run. Keep shared assertion/string pools in a fallback TU and use correctly sized extern declarations in native wrappers. Keep actual large pools large (>8-byte declaration) so MWCC emits LIS/ADDI; small strings need sized <=8-byte declarations for SDA21. objdiff direct diff synthesizes R_PPC_NONE string-pool relocations; use -c ppc_calculate_pool_relocations=false to compare actual instructions and real relocations, and report that setting. A typed GXTevAlphaArg[4] global at lbl_804FDBC4 bridges the inline alpha allocator table to the native texp_assign TU. lobj default_class was renamed lobj_default_class because other TUs have local symbols with the same name.

## c3_u13_mapeffect_20261105
Source: Codex worker c3_u13_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1740 B.

c3_u13: TExpAssignReg 802E04C0..802E0B8C is an independent exact 1740-byte TU when AssignAlphaReg is static inline using existing canonical global lbl_804FDBC4[4], __FILE__ uses existing lbl_806D0F38[7], and val>=0 assertions use existing lbl_804FDC64[9]. Keep full data 804FDC64..804FDCF0 and sdata2 806DCED0..806DCEE0 with tail fallback. Its leading string must remain present in native draft tail as ordinary char lbl_804FDC64[]="val >= 0". Source prefix emits no local out-of-line helper. All named functions present. Full-link acceptance pending.

## c4_t3_texp_20261105
Source: Codex worker c4_t3_texp_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2480 B.

c4_t3: HSD_TExpColorInSub/AlphaInSub unlock with a single local pointer initialized from the shared assertion pool lbl_804FD988 at function entry; repeating extern-base-plus-offset expressions rematerializes the base at each failure site and disrupts allocation. Use canonical small file/zero strings, preserve HSD_TExpRef inline, undefine HSD_TExpUnref to call the existing native external function. Own only compiler-generated switch tables 804FDAE8..804FDB04 and 804FDB88..804FDBA4; middle alpha strings 804FDB04..804FDB88 remain in a separate data-only NonMatching pool. Both .text/.data and default objdiff are 100%; source-linked full DOL SHA-1 OK, +2 fn / 2480 B.

## c5_m3_texp_20261105
Source: Codex worker c5_m3_texp_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 752 B.

c5_m3: DNBress UpdFire1/UpdFire2 become exact with literal 0.0f speed clamp (external named zero yields wrong FP scratch ranks). RGB aggregate Vec3f copy removes two freeSlot reloads in both SpawnFire drafts, leaving only FP register cycles (99.09574/99.207924). Safe four-way split at 80227318/80227490/8022760C accepted by dtk; only SpawnFire2 owns extab/index. Do not retain extab_padding on leaf-only TUs: dtk extab clean fails with No extab section found, preventing sdata2 normalization. Native extern C free-function definitions with explicit self preserve leaf ABI and avoid requiring the extab bridge. Full service SHA-1 OK, primary main.elf ranges exact; +2 functions/752 bytes. texp shared-base pointer, reordered helper (not inlined), and cached register-index experiments did not improve; original source restored.

## c12_u18_20261106
Source: Codex worker c12_u18_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 404 B.

c12_u18: DNBress SpawnFire2 fn_8022760C resolves the 14-instruction f6..f10 register cycle by replacing all scalar external constant uses in the function with float literals (3,1,0.4,1.2,0.1,3.141592025756836,1.570796012878418,-0.015). Existing postprocess_sdata2 maps all eight emitted constants to target labels; 404B text,8B EH,12B index exact. Flip existing TU to Matching; no split/bridge/data changes. Source-linked coordinator full build DOL SHA-1 OK.

## c12_u22_20261106
Source: Codex worker c12_u22_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 376 B.

c12_u22: DNBress SpawnFire1 fn_80227318 resolves 99.09574% FP home cycle by replacing seven external float labels with plain numeric literals; postprocess_sdata2 maps all back to existing labels. Text376 100%, leaf TU has no EH/data; flip Matching. Source-linked main.elf 80227318/376 exact and full DOL SHA-1 OK.
