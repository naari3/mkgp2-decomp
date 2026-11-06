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

## c14_u8_20261106
Source: Codex worker c14_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u8: HSD_LObjGetLightVector 802C42F0 text296/rodata24 reaches objdiff100 with Vec3 position={0,0,0}; interest={0,0,0}, rather than copying exported named constants. This changes prologue schedule: lwz r9/r8 now follow saved-register stores. However anonymous aggregate templates are pooled with HSD_LObjSetupInit in fallback lobj_init_nm.o, which references HSD_LObj_803B94A0_803F2BB8 and HSD_LObj_803B94AC_803F2BC4. Full Matching link fails without exports; retained exact draft NonMatching pending approved non-EH template-symbol bridge or a broader family pool solution. Named aggregate assignments / by-value inline copying are byte invariant at94.5946. No instruction, register, rodata-byte or EH residual remains in draft.

## c16_u40_20261106
Source: Codex worker c16_u40_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u40: DNBress ctor 80227B98 is a single-function NonMatching TU. Target strings use lbl_803C6ED0+0x10000 retained across calls; actual strings are addressed with negative offsets. Retain spawn/update FireFuncs view at lbl_804EDF80+0x18 to reproduce tail offsets and new-expression pointer r26. These two changes improve default objdiff84.09267->93.413124 (service report93.683395), primary size1080->1040 vs target1036. Remaining independent implicit vtable load (target derives vtable from same data base+0x54), prologue schedule and self/string register partition prevent promotion. Literal zero/one probe93.316605 reverted. No flags/splits changed; full build SHA-1 OK with fallback, native gain0.

## c16_u75_20261106
Source: Codex worker c16_u75_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u75: LObjInfoInit 802C63B0 uses persistent hsdLObj data base, class-name strings at +0x13C/+0x154. Shared-base C improves default objdiff69.53125->91.25 (service report73.59->93.125); reconstructing lbl_804FC43C[0x44] and lbl_804FC480[0x48] string pools makes .data100. Residual: target addi-zero copies for call/store base versus compiler mr/direct r31 stores, producing124 vs128 bytes. Parent-member address and base+0 probes byte-invariant; reverted. Remains NonMatching, no native gain. Pool-disabling objdiff92.78125. Future promotion should check 4-byte data alignment at804FC43C.

## c16_u125_20261106
Source: Codex worker c16_u125_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 972 B.

c16_u125: DNBress Update 80226B20 baseline99.75309 has one instruction residual: zero initialization li r30,0 vs target mr r30,r29. Extract unchanged kart search into static inline KartRender *FindActiveKart(), return selected/null kart and retain player fallback in caller. This restores target shared zero initialization; native text972/EH8/index12 all100. Signed long loop index alone is invariant. Existing bridges and compiler flags suffice; Matching full source-linked DOL SHA1 exact.
