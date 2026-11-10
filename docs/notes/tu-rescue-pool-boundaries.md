# tu-rescue-pool-boundaries

Source: Codex worker c2_i13_texp_lobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 37 fn / 10572 B.

texp/lobj isolation: inspect cross-object pool references before promoting a text-exact run. Keep shared assertion/string pools in a fallback TU and use correctly sized extern declarations in native wrappers. Keep actual large pools large (>8-byte declaration) so MWCC emits LIS/ADDI; small strings need sized <=8-byte declarations for SDA21. objdiff direct diff synthesizes R_PPC_NONE string-pool relocations; use -c ppc_calculate_pool_relocations=false to compare actual instructions and real relocations, and report that setting. A typed GXTevAlphaArg[4] global at TExpAssignReg_data_804FDBC4 bridges the inline alpha allocator table to the native texp_assign TU. lobj default_class was renamed lobj_default_class because other TUs have local symbols with the same name.

## c3_u13_mapeffect_20261105
Source: Codex worker c3_u13_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1740 B.

c3_u13: TExpAssignReg 802E04C0..802E0B8C is an independent exact 1740-byte TU when AssignAlphaReg is static inline using existing canonical global TExpAssignReg_data_804FDBC4[4], __FILE__ uses existing lbl_806D0F38[7], and val>=0 assertions use existing texp_data_804FDC64[9]. Keep full data 804FDC64..804FDCF0 and sdata2 806DCED0..806DCEE0 with tail fallback. Its leading string must remain present in native draft tail as ordinary char texp_data_804FDC64[]="val >= 0". Source prefix emits no local out-of-line helper. All named functions present. Full-link acceptance pending.

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

c16_u40: DNBress ctor 80227B98 is a single-function NonMatching TU. Target strings use DNBress_nm3_rodata_803C6ED0+0x10000 retained across calls; actual strings are addressed with negative offsets. Retain spawn/update FireFuncs view at DNBress_nm3_data_804EDF80+0x18 to reproduce tail offsets and new-expression pointer r26. These two changes improve default objdiff84.09267->93.413124 (service report93.683395), primary size1080->1040 vs target1036. Remaining independent implicit vtable load (target derives vtable from same data base+0x54), prologue schedule and self/string register partition prevent promotion. Literal zero/one probe93.316605 reverted. No flags/splits changed; full build SHA-1 OK with fallback, native gain0.

## c16_u75_20261106
Source: Codex worker c16_u75_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u75: LObjInfoInit 802C63B0 uses persistent hsdLObj data base, class-name strings at +0x13C/+0x154. Shared-base C improves default objdiff69.53125->91.25 (service report73.59->93.125); reconstructing lbl_804FC43C[0x44] and lbl_804FC480[0x48] string pools makes .data100. Residual: target addi-zero copies for call/store base versus compiler mr/direct r31 stores, producing124 vs128 bytes. Parent-member address and base+0 probes byte-invariant; reverted. Remains NonMatching, no native gain. Pool-disabling objdiff92.78125. Future promotion should check 4-byte data alignment at804FC43C.

## c16_u125_20261106
Source: Codex worker c16_u125_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 972 B.

c16_u125: DNBress Update 80226B20 baseline99.75309 has one instruction residual: zero initialization li r30,0 vs target mr r30,r29. Extract unchanged kart search into static inline KartRender *FindActiveKart(), return selected/null kart and retain player fallback in caller. This restores target shared zero initialization; native text972/EH8/index12 all100. Signed long loop index alone is invariant. Existing bridges and compiler flags suffice; Matching full source-linked DOL SHA1 exact.

## c17_u23_20261107
Source: Codex worker c17_u23_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u23: lobj_init_nm SpecularInit97.701866->99.347824 by fabs (not fabsf); explicit cursor leaves extra initial mr and was reverted. SetupInit49.189655->98.93236 by alpha-inclusive flags (0x1c/0x14), active-array second pass, epsilon clamps, external position/interest getters, inline vector and light upload bodies, and separate upload index. Target3016/source3024: extra active base lis/addi plus GPR partitions. Actual assertion pools restored (.data100) and real double-half/255 constants retained; all owned section percentages nonregressing. No exact function, so no A/B promotion; no native gain. Avoid repeating the three recorded structure probes without new evidence.

## c18_u225_20261107
Source: Codex worker c18_u225_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u225: DNBress ctor 80227B98 improves93.413124->98.74517 direct (report98.78378) and primary1040->1036 bytes by TU-private explicit vtable-field ABI view (same approach as AI_KartInit/clDrawMan), retaining real C++ inheritance/new/EH, plus one named data base used for vtable+0x54 and FireFuncs+0x18. Source self r30 and data r31 now exact. Inline new-expression factory helpers are byte-invariant and removed. Residual six prologue instructions plus strings/new-expression r26/r27 swap (26 instruction differences total), owned EH DELETEPOINTER register differs. Three hypotheses exhausted below99; remains NonMatching, no A/B split, zero native gain. Whole fallback-linked build SHA1 exact. No data range, flag, or bridge edits.

## c19_u13_20261107
Source: Codex worker c19_u13_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u13: SpecularInit802C457C fresh99.347824->99.62733 by reusing existing inline LObjGetActiveByIndex in place of the caller-level range check. Light pointer becomes targetr31; remaining count/cursor r29/r30 swap affects five operand rows, plus six owned literal relocation names. Declaration reversal byte-invariant; result-local accessor97.701866; whole-loop inline helper94.11801/648B; explicit cursor accessor98.416145 retains extra initial mr and swapped increments. SetupInit retained98.93236/3024B: ClearActive helper98.28249; explicit shared active base98.129974/3016B adds copies/_savegpr_23 and removes ambient materialization too; delaying base initialization98.401855/3024B. All reverted except accessor improvement. No exact functions or A/B promotion; owned section percentages unchanged.

## c19_u51_20261107
Source: Codex worker c19_u51_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u51: texp_nm1 canonical __FILE__ reference lbl_806D0F38[7] slightly improves direct TExp2TevDesc97.69531->97.79297 and SetReg97.73354->97.749214; sections unchanged. TEUndef macro70.21484 confirms cached u8 input matters. Canonical external type-assert string adds8B and regresses96.58594 despite data99.64158. HSD_TETev parameter/union local does not change allocation; removed. SetReg RGB inline helper97.61755 changes pointer ranks and color-copy stack slot; shared post-switch scalar clamp92.18495 shrinks1276->1192, so preserve separate per-case clamps. Prior c5/c18 pool-view/index probes not repeated. Both functions remain NM, zero native gain.

## c20_u22_20261108
Source: Codex worker c20_u22_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 148 B.

c20_u22: Preserve whole-file lobj pool context when applying B. A broad split gives prefix736/setup+spec1000/tail4072 object-exact, but class registration loses pooled hsdLObj+13C/+154 addressing; final no-regression cut is six getters802C4010..40A4 (148B) native, rest lobj_nm1. Mirror the original count getter with a static inline local accessor to keep SpecularInit100. SetupInit98.262596/3048 unchanged: fabs helper and checked/unchecked factoring invariant; a dedicated unchecked light-vector initializer worsens95.17639/2996 and duplicates aggregate templates. All non-text section percentages unchanged. Full source-linked DOL SHA1 exact.

## c20_u113_20261108
Source: Codex worker c20_u113_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u113: current single-function SetReg baseline default96.043884/1288B improves96.60815/1276B (service96.80878) with caller-local const pool and two small inline hardware-upload helpers, Tev helper defined before K helper. One combined upload helper96.59561 removes repeated pool materialization but swaps color-copy stack slots; independent table parameters are byte-invariant; separate helpers restore target slots. Color-conversion body exact, sdata2 stays100. Residual external pool/table-base folding, entry pool-through-r0 move and upload-loop register partition. Original804FD988..804FDCF0 pool belongs to Matching texp.c outside claim, so no transfer/merge; single function cannot use mechanismB. Full fallback-linked build SHA-1 exact; native gain0.

## c21_u99_20261108
Source: Codex worker c21_u99_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u99: SetReg802E0F8C explicit pointer cursors in both existing upload helpers improve direct96.60815->97.67712/report96.80878->98.36677; sdata2 stays100. Removes initial pool-through-r0 move and restores table-base ADDI. Source1272 vs target1276: target Tev strength reduction keeps ADDI table,+0x10 and lwz-0x10; walker uses lwz0. Initial li/addi order and upload saved-register homes remain. Shared caller index plus single-upload wrappers97.42633 gives target second indexr31 but regresses overall; mixed pointer/index tables97.31661 folds Tev external pool again. Retain best pointer walk; no conversion edits. Original pool belongs to Matching texp.c outside claim; no merge/data transfer and no sole-function B cut. Full fallback-linked DOL SHA-1 exact; zero native gain.

## c22_u47_20261109
Source: Codex worker c22_u47_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u47: DNBress ctor80227B98 improves direct98.74517->99.13127/report99.16988 via static inline DNBressStrings() with a named const-char-pointer result. Fixes strings/new r26/r27 swap and makes primary160B EH/12B index payload+relocations exact; extra weak dtor60B/EH8/index12 remains. Partial own-self data804EDF80..804EDFF0 (112B100): extents24, explicit ABI member records48, RTTI/base record12, vtable28. Original combined symbol80 split at98; D4 reduced34->1C. Unknown zero tailEDFF0..EE008 (24B) remains fallback, no filler. Ownership alone invariant; global native member-pointer initializers emit unwanted sinit, explicit ABI records avoid it. Three named referenced static objects produce automatic section anchor, but variant-record split adds two address instructions (97.945946/1044B). Late strings96.96525, inline base accessor invariant, initial zero literal invariant. Remaining six prologue address-materialization instructions/r4-r5-r6 cycle only. Six hypotheses exhausted, singleton cannot B, staysNM/nativegain0. Full fallback-linked DOL SHA1 exact.

## c22_u82_20261109
Source: Codex worker c22_u82_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u82: scalar-only A rescue uses new native lobj_constants.c for .sdata2806DCBE0..806DCC08: double0.5; floats0,1,255,0.5,-1,50,1048576,36 initialized bytes plus4 natural alignment. In lobj_nm1 setup_spec_lightobj, extern const f32 lbl_806DCBFC replaces literal50.0F; raw SetupInit98.262596->98.26923, report98.27586,3048B; other18 functions100. Same-TU const definition emits/folds duplicate50 and is rejected. Separate constants TU .sdata2100, actual source-linked40B equals target and two coordinator builds SHA1OK. No function native gain. Separate null guards regress97.440315/3072 and standalone vector97.16216; reused final i invariant; spot flatten98.15252 repeats c21_u24 and reverted. No new safe text B cut; class pool and shared aggregate context remain constraints.
