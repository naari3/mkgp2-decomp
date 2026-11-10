# C++ ctor retrofit + mangled-name bridge (2026-07-19, ServiceMenu_Init)

ServiceMenu_Init (0x80073C70, 0x1B0) を asm_fn park (C 99.35%、register-identity
残差) から**本物の C++ constructor として 100% match** に昇格させた手法。初の
class retrofit 実証で、同 family の park 全部に適用できる見込み。

## 観察 → 確定した事実

- plain C + `-Cpp_exceptions off` では `new` 相当の pointer web が r31 に落ちて
  source-closed (approachB-exceptions-off-regalloc-hardblock 参照)
- target extab の action (DELETEPOINTER rN → operator delete / DESTROYBASE →
  base dtor) は **実際の C++ 構文 (new 式の guard、base ctor 後の cleanup
  region) からの auto-emit でしか自然に出ない**
- 本物の ctor + new 式で書くと、EH web が pointer を r29 に**強制**する =
  register 残差が構文レベルで解決する。extab も byte-identical に auto-emit
  された (手動 emit 機構は丸ごと撤去)

## 手法: mangled 名の橋渡し

C++ 構文を使うと参照が mangled 名になるが、既存 symbols.txt / 他 TU は C 名。
`tools/postprocess_extab_user.py` の `--redefine-sym` (flat map、
`tools/extab_user_renames.json` から) で **.o 内の mangled 名を既存 C 名に
rename** して橋渡しする。ServiceMenu_Page.c の実例:

```
__ct__11ServiceMenuFi     -> ServiceMenu_Init        (ctor 定義自体)
__ct__12GameModeBaseFv    -> GameMode_BaseInit       (暗黙の base ctor call)
__dt__12GameModeBaseFv    -> dtor_8002CDF4           (DESTROYBASE の dtor 参照)
__vt__11ServiceMenu       -> CardCreate_Page_data_803FDE64            (vtable store)
__ct__14DisplayContextFv  -> DisplayContext_Init     (new DisplayContext)
__ct__6SpriteFiiff        -> fn_801A08B8             (new Sprite(...))
__nw__FUl                 -> Alloc                   (operator new)
__dl__FPv                 -> MemoryManager_TimedFree (operator delete)
```

前提: TU に `extab_padding=` を指定 (postprocess chain が走る条件) +
`extra_cflags=["-Cpp_exceptions on", "-lang=c++"]`。

## 個別テクニック

1. **vtable を emit させない**: class に「declared だが全 repo で未定義の
   non-inline virtual」(key function) を 1 つ置く。CW は key function の定義
   TU に vtable を emit するので、未定義なら参照は external のまま →
   redefine-sym で元 binary の vtable symbol (lbl_*) に解決させる
2. **base class モデル**: `struct Base { Base(); virtual ~Base(); }` で
   vptr が offset 0、derived member は +4 から。base ctor / dtor は宣言のみ
   (extern 実体に rename で解決)
3. **new 式の再現**: `struct Payload { char _opaque[SIZE]; Payload(args); }` +
   `p = new Payload(args)` で `li r3, SIZE; bl Alloc; mr. rN, r3; beq; bl ctor`
   の null-guard 付き列がそのまま出る。SIZE は new が渡す即値
4. **virtual call**: slot +0x8 = 2-word header + slot 0。
   `struct X { virtual void f(int); }` の `p->f(1)` で r12/r12 dispatch
5. **混在**: 同 TU 内で matched 済みの plain 関数は extern "C" +
   C struct view のまま触らない。ctor だけ class を使う (型ビュー 2 本立て)

## 制約 / 注意

- renames json は **flat map で全 extab_padding TU に適用**される。mangled 名は
  一意なので実害は無いが、同じ mangled 名を別 TU で別の先に rename したく
  なったら仕組みの拡張が要る
- SJIS 制約: source に Unicode ダッシュ等を入れると sjiswrap が encoding error
  を出す。ASCII のみで書く
- 適用候補 (同 family の park): SeqMenuScene_Init (register-identity),
  VolumeCalibration_Tick / DrawOverlay (後者は RTTI も必要),
  TransparentDraw_DestroyEntry, TripleBladeRing_SetWorldYaw (fp-numbering は
  別 family、効かない可能性あり)

## 適用実績 (2026-07-19 第 2 波)

- **Jyugemu_Flag_Ctor ✓** (2 iteration): free function 形だと return path の
  branch-over-branch (`bne/b`) と per-return-site の `mr r3, r30` が出ない。
  **本物の ctor + 早期 `return`** に書き直すと implicit `return this` が
  その形を自然に生成して 100%。「returns が分離 materialize されてる関数は
  ctor の兆候」と覚える
- **DMAChannelManager_Init ✓** (3 iteration): ループ内 `new TDrawEntry`
  (ctor = TransparentDraw_ResetEntry)。`-use_lmw_stmw on` が必要 (target が
  stmw/lmw)。cursor 変数は `addi→r0→mr` の余分 copy を出すので
  **typed struct 配列の global-index spelling** (`lbl[i].field`) にすると
  walker が addi を直接持って 100%
- **ItemObjectManager_Init ✗ park 維持** (6 probe): ループの i/walker
  callee-saved 割付が target と swap したまま source-closed (for/while/
  do-while/register/struct-index/Pool-struct すべて invariant)。
  **real C++ 化しても register-identity park family が解けない場合がある**。
  EH web (DELETEPOINTER の pointer) は正しい register に固定されるが、
  EH に関与しないループ web の順序は別問題

## 多 fn TU での制約 (2026-07-19 実験で確定)

**実験**: all-auto の ServiceMenu_Page.c で中間 fn (Tick) だけ manual emit に
戻す → SHA-1 fail。object 内の extab section は「auto 一括 (定義順) →
.extab_user 一括 (定義順)」で並び、**fn address 順への interleave は起きない**。
推定ではなく検証済みの事実。

## (旧記述: ONKARTHIT mega bundle で確認)

manual emit の extab を持つ多 fn TU では、**一部の fn だけ** real C++ 化して
auto-emit に切り替えると、object 内の extab section 並び (auto 一括 → manual
一括) が target の address 順と食い違って SHA-1 が壊れる。
auto_ONKARTHIT_block.c の dtor 11 連隊 + KartItem/CarObject 大物はこのため
**TU 丸ごと C++ 変換が前提** (別プロジェクトとして計画する)。単独 fn TU
(Jyugemu_Flag_Ctor 等) にはこの制約は無い。

## cxc_u12_f9aac_20261105
Source: Codex worker cxc_u12_f9aac_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2084 B.

fn_801FA024 factory: canonical SceneListImpl + VHolder<FlowSceneList> and FlowFaderI generate exact 496-byte primary text and exact 180-byte primary EH. Compiler spells VHolder<FlowFaderI> destructor with length 21, despite old reference maps containing length 20. Bridge length 21 to dtor_801F2724. Extra weak destructor EH must be judged on owned ranges and full-link discard.

## c2_i2_8020007c_20261105
Source: Codex worker c2_i2_8020007c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 752 B.

Countdown TU 8020007C has reversed EH ordering from ctor 80200240 through tail weak dtors 80201E8C..802020B8: their EH entries sit at 80018274, 8001829C, 800184E4, 8001856C, 80018594. Only first factory/dtor pair is a safe leading cut. Yes/no exact Draw/delete/factory functions isolate cleanly. Existing FlowYesNo/FlowCountdown declarations also emit unmatched vtable/RTTI data when relevant method definitions or dynamic_cast are present; a 100% text score is insufficient to promote those TUs.

## c2_b2_popups_20261105
Source: Codex worker c2_b2_popups_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

CW GC/2.6 selects an earlier defined non-inline virtual as vtable key even when an undefined _key is declared last. Moving the undefined derived _key before other declarations suppresses extra vtable/RTTI emission while preserving inherited virtual slots and exact text (RacePopups, SpeedHud). SpeedHud ctor requires ResCtrl rc to remain alive through new GaugeMark(layer); moving that statement into rc scope preserves text and exactly reproduces nested EH cleanup ordering.

## c2_b2_popups_20261105
Source: Codex worker c2_b2_popups_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RacePopups/SpeedHud rescue resume: 100% individual function objdiff plus exact owned EH/data does not prove physical primary function order. Coordinator ELF revealed reversed definitions linking at wrong addresses. Reorder native definitions to target address order; verify every symbols.txt function is defined and primary object-offset order matches target order, ignoring only weak copies known to discard. Refresh anonymous compiler IDs in bridges afterward.

## c2_b3_8021550c_20261105
Source: Codex worker c2_b3_8021550c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 20 fn / 6360 B.

For these native rescue TUs, placing the undefined virtual key declaration before the first defined non-inline virtual suppresses derived vtable emission without changing inherited dispatch slots or primary text. Explicit scopes around sequential ResCtrl locals reproduce target constructor EH lifetimes while empty destructors preserve all instruction bytes. Owned EH is exact even though objdiff whole-section scores fall due to appended weak destructor copies.

## c2_b1_banner_20261105
Source: Codex worker c2_b1_banner_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 22 fn / 8604 B.

ItemBanner RTTI names are clRubDisp/clRubBack/clRubMark. Text-identical generic VHolder deleting dtors can hide incorrect type-to-address bridges: EH cleanup identifies canonical FlowFaderI/F dtors vs TU-owned clRubBack/clRubMark holder dtors. The ResCtrl local in clRubMark ctor stays alive through the final sprite activation loop; narrowing that lifetime preserves text but changes EH.

## c2_b1_banner_20261105
Source: Codex worker c2_b1_banner_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 22 fn / 8604 B.

Rescue of existing NonMatching TUs must check retained function emission order, not only per-symbol objdiff percentages. The first link of this batch failed despite 100% functions/EH because source order differed. GC/2.6 -inline deferred emits ordinary out-of-line definitions in reverse source order. Private whole-class VHolder specializations with out-of-line destructors plus deferred inlining preserved exact inlined delete bodies while placing owned dtors at the target TU tail.

## c2_b5_80207324_20261105
Source: Codex worker c2_b5_80207324_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 33 fn / 8244 B.

Rescue of anon_801FEBD8 / anon_80202148 / anon_80207324: correct VHolder<FlowFaderF/I> mangled length is 21. Map implicit FlowFaderI destructor to fn_801F26C8 (target vtable FlowFaderI_vtable_804E5284). Append weak destructor EH after owned entries in extab_order. Local synthetic RTTI can retain duplicate .data/.sdata even when text objdiff is 100%; explicit calls to the same CW dynamic-cast runtime with external target RTTI records removed all such sections while preserving every function at 100%. Full-link acceptance remains pending.

## c2_b5_80207324_20261105
Source: Codex worker c2_b5_80207324_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 33 fn / 8244 B.

Resume 1: an owned weak inline constructor can match objdiff 100% yet link at its caller emission position. fn_80202148 was emitted after fn_80202780, shifting the first five functions -0x38 with unchanged section sizes. An opt-in header declaration and genuine out-of-line ctor definition first in the assigned TU preserves exact text and restores source order. Add owned symbol placement checks; object matching percentages do not prove placement. Coordinator rebuild pending.

## c2_i3_80216568_20261105
Source: Codex worker c2_i3_80216568_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 30 fn / 8312 B.

Per-function objdiff 100% plus primary EH equality do not prove TU text placement. CW may defer functions and emit weak inline array constructors in the middle of strong functions. Compare surviving strong function order/sizes to target, and ensure surviving weak functions have intended target location. anon_80216568 resume isolates two row methods and leaves final 52-byte ctor in target fallback, retaining 30 native functions.

## c2_i6_8020bd68_20261105
Source: Codex worker c2_i6_8020bd68_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 28 fn / 6940 B.

Rescue of these four near-exact TUs: preserve exact runs, isolate NM bodies at accepted extab boundaries, bridge actual VHolder length 21 destructors, declare owned extab/index order with weak copies last, and map compiler @ symbols to target @etb/@eti. An undefined first-declared virtual key in a derived private class suppresses vtable emission without changing inherited virtual slots; a key declared after the destructor did not suppress emission. Popup inline helper dynamic_cast expressions emit RTTI even when unused, so restrict those helpers to the NM TU that uses them. DNFlash rodata string symbol sizes must match target sizes, with final zero gap kept in .rodata; bytes and all sections then match 100%.

## c2_b6_8020d1c0_20261105
Source: Codex worker c2_b6_8020d1c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 10276 B.

FaceEffect GC/2.6 needs -rostr and -inline deferred for target vtable-before-jumptable ordering. Deferred emits out-of-line definitions in reverse order, so reverse source definitions verbatim; verify linked text layout after weak destructor discard, not just symbol objdiff percentages. Pencil resource must be an expression string literal so it emits after RTTI name. Identify packed resource tables separately in symbols.txt.

## c2_b6_8020d1c0_20261105
Source: Codex worker c2_b6_8020d1c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 10276 B.

A bridged named const array can remain locally defined despite postprocess_sdata2 externalizing compiler literals. FaceEffect kGlowOffset[2] must be extern so lbl_806DB6E0 resolves to target-owned shared pool. A local initialized copy produces +8 .sdata2 growth and two text refs to its appended address; per-function objdiff remains 100 because symbolic relocations conceal final placement. Audit UND/defined symbol status.

## c2_i1_mapeffect_20261105
Source: Codex worker c2_i1_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 43 fn / 17296 B.

mapeffect rescue: fn_80179F60 has EH at 0x800117E0, preceding fn_80179650. dtk rejects a split at fn_80179F60, accepts 0x80179650. Prefix ranges in this HANDOFF yield 43 exact functions / 17296 bytes. Its data and RTTI partition cleanly at .rodata 0x80371DC8, .data 0x804915DC, .sdata 0x806CFB10. Default objdiff inferred pool references can give 99.95143% text despite exact instructions; ppc_calculate_pool_relocations=false compares actual instructions and relocations at 100%.

## c2_i1_mapeffect_20261105
Source: Codex worker c2_i1_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 43 fn / 17296 B.

When splitting a C++ TU, an anonymous-namespace class vtable reference can become STB_LOCAL SHN_UNDEF. llvm-objcopy symbol rename preserves binding, so a global fallback definition cannot resolve it. For mapeffect, naming the private namespace MapEffectPrivate and bridging its new mangled vtable names makes references global while preserving all prefix text/EH/data bytes. Audit all local undefined ELF symbols after any split.

## c2_i1_mapeffect_20261105
Source: Codex worker c2_i1_mapeffect_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 43 fn / 17296 B.

After a C++ split, compiler RTTI symbols can stay STB_LOCAL even for external-linkage classes. A fallback TU cannot resolve such definitions by global name. Existing postprocess bridge supports global:<target> values; mapeffect uses __RTTI__11clMapEffect -> global:mapeffect_data_806CFAD0. Audit the intersection of fallback undefined names and source local defined names; payload bytes stay unchanged.

## c2_b4_8020f44c_20261105
Source: Codex worker c2_b4_8020f44c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 15 fn / 7744 B.

CW GC/2.6 emits a strong derived vtable when its first non-inline virtual is defined, even if a later undefined key virtual exists (or the key is inherited). Redeclaring the inherited undefined key as the first virtual of each derived demo class suppresses that table. KartAlertPanel similarly needs its existing undefined key before its destructor; this TU contains no panel virtual dispatch. All 15 assigned functions retain 100% text. DemoBase weak dtor must bridge to clCGameDemo_Dtor for owned constructor EH; KartAlertPanel holder cleanup targets dtor_801F4A80, not dtor_80250668.

## c2_b4_8020f44c_20261105
Source: Codex worker c2_b4_8020f44c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 15 fn / 7744 B.

TU rescue must check primary function PHYSICAL order as well as per-function objdiff. KartAlertPanel had every function 100% and exact owned EH, but source definition order was reversed, which moved link addresses and made MWLD sort extabindex to the wrong function order. Moving definitions verbatim to address order preserves 100% text and fixes the placement cause. A source object can contain interspersed weak destructor text; evaluate final order after weak discard.

## c2_i10_8021f088_20261105
Source: Codex worker c2_i10_8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 19 fn / 7620 B.

anon_8021F088 isolation: empty inline TextSprite destructor mapped to dtor_800869D0 restores DESTROYMEMBER EH without changing text; map Own<Sprite> dtor to dtor_8015E8AC, FadeObj to dtor_80145DB0, SceneBase to dtor_8007D0D4, PtrVec<FadeObj*> to dtor_80145F9C. Retain trailing #pragma inline_max_size(240) with CoinResultScene_Init so NextWnd ctor remains out of line and exact. Vtable-bearing destructors remain NonMatching: target vtables have RTTI pointers, whereas original RTTI-off source has zero; enabling RTTI after splitting duplicates base type records. Data order also prevents independently owning both the scene jump table (804EDE5C) and earlier-text line vtable (804EDE8C).

## c2_i5_802253ec_20261105
Source: Codex worker c2_i5_802253ec_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 25 fn / 7356 B.

TU rescue: anon_802253EC uses canonical RTTI names clCSSceneNextRaceBT / clSceneInterface. RTTI-on + -rostr and owned rodata 803C6E80..803C6EA8, data 804EDF30..804EDF54, sdata 806D0520..806D0530 yield section-level 100% without changing method bodies. Add bridges @246/@248/@247 and RTTI class names to existing labels. ContinueScene needs two C702 padding sites and explicit EH order with weak dtor last. CardModeRoot can safely rescue CC04..CEE8 only, avoiding dynamic_cast/vtable RTTI emissions.

## c2_i5_802253ec_20261105
Source: Codex worker c2_i5_802253ec_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 25 fn / 7356 B.

Rescue verification must check physical .text function order as well as symbol-level objdiff. ContinueScene individual text symbols were 100%, yet emitted in original source-definition order; main.elf placed fn_8024E05C at 8024D764. Explicit EH ordering cannot correct .text layout, and the linker sorts EH index by actual function address. Move strong definitions into target-address order, preserve inline helpers, and verify cumulative native offsets after weak-copy discard.

## c2_i11_dn_20261105
Source: Codex worker c2_i11_dn_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 31 fn / 11788 B.

For a derived class overriding inherited slots, declare an undefined new virtual BEFORE the override declarations to make it the CW key function without changing inherited slot indices. This suppresses emitted vtable; an ordinary native pointer table can retain an existing RTTI pointer while RTTI is off. Verified JobRunnerMode primary text and data 100%. Shared rodata visibility can control MWCC hoisted-base generation: DNStartDino tail requires all original rodata definitions in the same TU. Its full raw rodata and normalized relocations are exact although objdiff section scoring is 99.99344 due padded symbol boundaries.

## c2_i11_dn_20261105
Source: Codex worker c2_i11_dn_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 31 fn / 11788 B.

With MWCC GC/2.6 -inline deferred, physical emission order can be reverse source-definition order even while every per-function objdiff score is 100%. Verify actual primary-function order/sizes in source .o against target .o, excluding discardable weak copies. In anon_80209FA4.cpp prefix and tail, reversing the out-of-line definitions restores target order without changing function bodies. Initial full-link failure had exactly 473 changed words inside permuted functions and 247 branch references to them, plus vtable/rodata/EH index references.

## c2_r5_80205dcc_20261105
Source: Codex worker c2_r5_80205dcc_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 21 fn / 5584 B.

Rescue c2_r5: Matrix4RotZ and HudManagerHide need flag promotion only. CardMenuRoot and MenuModeBase require first-declared undefined virtual keys to suppress duplicate tables; clCSSceneChangeSingle likewise. Bridge SceneBase dtor to dtor_8007D0D4; order owned EH before weak copies and bridge compiler @etb/@eti names. ItemDisplay can isolate the exact Start/Draw/Update tail by retaining the original hide routine as a static inline helper, preserving target Update inlining. Selector 8020688C..80206BC8 is a clean exact 828-byte run; private declaration copy suppresses its vtables without modifying shared FlowYesNo.h.

## c2_r3_8021a7c8_20261105
Source: Codex worker c2_r3_8021a7c8_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 24 fn / 5988 B.

c2_r3 rescue (coordinator acceptance pending): HudManager requires ownership of 0x804F20B4..0x804F2110 jump table, @59 bridge and DATA_ALIGN4_TUS. anon_801FD320 requires genuine .ctors pointer, VHolder<FlowFaderI> length 21 bridge, implicit FlowFaderI destructor to fn_801F26C8 and owned EH before discarded weak copies. Safe cuts at 801FD5FC/801FD800, 8021ABFC, 80229398/802296C4 all accepted by dtk. All resulting Matching owned sections and primary physical order after known weak discard are exact.

## c2_r1_texpdag_20261105
Source: Codex worker c2_r1_texpdag_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 15 fn / 6212 B.

c2_r1_texpdag rescue candidate (full link pending): FlowYesNo RTTI references can reuse external original records through fn_80271340 while a private first-declared undefined key suppresses derived vtables. anon_80204474_nm2 owned constructor EH references YesNoButton destructor dtor_802070EC; bridge __dt__11YesNoButtonFv accordingly. Mapping owned compiler @etb/@eti symbols exposes 100% owned EH in objdiff despite appended weak entries. texpdag exact assign_reg/order_dag own the .sbss2 zero initializers; preserve with their leading split. CalcRange and HSD_TExpSimplify2 isolate exactly; HSD_TExpSchedule is coupled to the original .data group base.

## c2_r4_802161c4_20261105
Source: Codex worker c2_r4_802161c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 36 fn / 5948 B.

c2_r4 rescue: FIRST CHECK found all 45 symbols defined. Explicit inline on coin private helpers removes 160 bytes of unused out-of-line helper emission while all 12 primary functions and EH remain exact. GC/1.3.2 InputObj_ReadRawInput needed -Cpp_exceptions on plus normal extab postprocess; all text/EH then 100%.

## c2_r4_802161c4_20261105
Source: Codex worker c2_r4_802161c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 36 fn / 5948 B.

FlashFx: an explicit empty destructor makes deleting singleton fn_8021A2B4 emit before factory fn_8021A354, matching target physical order. OwnPtr<AnimSprite> cleanup bridges to dtor_8015E8AC. However an isolated delete-only leading EH triggers the overbroad existing patch_memorymanager_timedfree_extab (it checks symbol presence, not definition/TU identity), changing 10180000 to 101A0000. This batch leaves Update+delete NonMatching and promotes the factory independently. No tool code changed.

## c2_r4_802161c4_20261105
Source: Codex worker c2_r4_802161c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 36 fn / 5948 B.

Popup rescue: opt-in suppression of unused Open/Close dynamic_cast helpers avoids emitted RTTI even with -RTTI on. Exact Close wrapper uses the same runtime call fn_80271340(t,0,MsgPopup_RTTI_806D0268,FlowTask_RTTI_806D0260,0) with external target RTTI records. First-declared SceneListImpl _key2 suppresses its vtable. Tail MsgPopupCoin dtor needs primary EH order before appended weak FlowFaderI/F and ResCtrl EH. A split with only two leaf getters has no extab, so omit extab_padding while retaining original compiler flags; dtk extab clean otherwise fails.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

MinimapHud ctor 80219B24: separate sequential scopes for ResCtrl a/b/c/d reproduce exact 196-byte primary EH while all 1232 instruction bytes stay exact. Canonical VHolder mangled length is 21; bridge MapBase destructor to dtor_8021617C. Owned ctor jump table is .data 804EDC60..804EDC84.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

No-EH C++ leaf split: extab_padding invokes dtk extab clean, which errors when no extab exists. For MinimapHud Start/Draw, use ordinary compile rule and rename owned target symbols to actual CW mangled names (Start__10MinimapHudFi, Draw__10MinimapHudFv); definitions remain verbatim. Full-link acceptance pending.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

EnemyFace 8022BEB4 text/EH is exact but emitted clEFace3D vtable under RTTI-off has null at +0 whereas target 804EE134 references data_804EE0EC_data_806D0618. Leave destructor NonMatching and isolate exact Trigger 8022BF2C; do not promote based solely on 100% text.

## c3_u7_8021bc44_20261105
Source: Codex worker c3_u7_8021bc44_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

anon_8021BC44: NameEntry begins with KeyBoard (0x28), containing KeyVec<KeyGroup> at +4 through KeyVecMid/KeyVecBase. Replacing fake NameEntryHead/NameEntryBase inheritance with this canonical member layout restores six destructor guards: fn_8021BC44 100% text, Update 96.737625%. dtk rejects split at 8021C560 due reversed EH group; no native gain.

## c3_u12_8020007c_20261105
Source: Codex worker c3_u12_8020007c_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 476 B.

c3 unlock: FadeLogo safe cuts are E3D0/E4C4 and F02C/F080/F18C/F220; DTK accepts. Factory private TaskListBase external destructor suppresses duplicate RTTI/vtable while primary text and 100-byte EH stay exact. Bridge @78/@79 to target EH names. Generic VHolder<TaskListImpl> weak dtor EB04 migrates to factory and is exact, while strong fallback nm2 retains final target ownership. Sort no-EH split uses actual CW name and omits extab_padding. Residual loop cursor/end r4/r5 and r6/r7 swaps resist iterator/direct-End spellings; Draw retains stack-slot and assignment-copy mismatch.

## c3_u18_carobject_20261105
Source: Codex worker c3_u18_carobject_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 24 fn / 6588 B.

TitleSelect fn_800AC9AC at 800AC9AC is semantically counter > 180 ? -1 : -2 after increment; the old counter < 180 ternary looked like a mere five-row register residual (97.5%). SelectBase + inline derived constructors with real new expressions preserve exact text and naturally generate DELETEPOINTER and DESTROYBASE. Explicit original vtable stores avoid emitting extra RTTI. EH order stage factory, character factory, character dtor/tick/draw, stage dtor/debug, title dtor/debug gives text/extab/extabindex all 100%.

## c3_u8_resultscene_20261105
Source: Codex worker c3_u8_resultscene_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Resultscene partial: CoinPopupDetail ctor 80161914 matches 1556 text bytes and its full 288-byte EH including 13 relocations using real new/member initializers. sprites member must use existing ResultBuf2 dtor 80162138, bufs ResultBuf1 dtor 801620D4. ResultSub ctor 8015FD40 matches 908 bytes and all 140 EH bytes/7 relocations with ResultMid bridge to dtor_801419C8, a 0x58 ResCtrlR view, one cached TitleTracker query and character-id argument evaluation before title lookup. Original fn_8016039C remains exact after the size correction. Popup layout 80160A90 needs four direct operations; a helper hoists 12.0 across calls and adds an FP save. RYEntry_Draw extraction fixes all GPR colors in DEBC (99.61539, FP temporaries remain). The existing whole group cannot split at 80161914: dtk explicitly rejects it. Do not promote these symbol matches while source_input is false.

## c3_u19_8021f088_20261105
Source: Codex worker c3_u19_8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 3224 B.

c3_u19: Coin StateCoins 80220ECC becomes exact when gravity/angle-limit use ordinary 0.8f/360.0f literals rather than named external const floats. ItemWnd ShowKart 80221C94 requires cached bool input comparison and truth test. Open 802230C0 requires existing 803C6BC4 aggregate initializer and units-to-thousands calculation order. Update 8022134C owns jump table .data 804EDE5C..804EDE80 and DATA_ALIGN4_TUS. All four have 100% owned text/EH/data and source main.elf inputs; full-build acceptance pending. Layout copies require implicit ResCtrl padding and scalar tail fields. fn_8019FF8C writes 0x30-byte sprite node record, not two floats.

## c3_n4_80205dcc_20261105
Source: Codex worker c3_n4_80205dcc_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1884 B.

c3_n4: YesNoButton Animate +0x58 multiply resolves by naming the appearance call result a, then a *= pulse before storing scale. Genuine out-of-line YesNoButton::~YesNoButton() resolves a wrapper null-branch mismatch: target null skips both member destruction and delete. Private first-key declaration suppresses vtables. Owned EH 80019148..80019210 and index 80029960..80029978 compare 100% after bridge @138/@139/@226/@227; weak Fader I/F copies remain appended and must discard. Full-link acceptance pending.

## c3_u3_dbgmenu_20261105
Source: Codex worker c3_u3_dbgmenu_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

DbgMenu partial: real new/derived ctor fixes 01,07,08,10,12,13,RaceStart factory text; Reset (800D040C) is a real ctor. A separate inline ResetParticlePool loop restores four distinct hoisted zero webs and implicit this return, yielding 100% Reset text. Cache Sprite* before two position stores to eliminate alias reload. Global-index spelling fixes ScrollList_Update. All still NonMatching because six residuals and inseparable reversed EH group remain.

## c3_n8_enemyface_20261105
Source: Codex worker c3_n8_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1840 B.

c3_n8: Minimap Update 80218F5C cached resId web reaches target r30 only when its declaration is function-scoped; block-scoped before cup/round stays r29. Isolate 80218F5C..80219538 with its 28-byte jump table and DATA_ALIGN4_TUS. TitleNameHud safe split is 80252EE4. Prefix factory/dtor text/EH exact after factory-first source order, removal of the old dont_inline scope (otherwise member dtors are called out of line), private undefined vtable keys, and owned @ EH bridges. Only appended weak TweenInterp_Dtor remains. Full-link acceptance pending.

## c3_u1_801baa88_20261105
Source: Codex worker c3_u1_801baa88_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_u1 partial: fn_801BAA88.cpp is missing fn_801C1C14 in baseline. Native pointer assignments from external sdata2 constants into the shared keyboard table and sbss pointers emit exact 108-byte text; __declspec(section ".ctors") static function pointer gives exact 4-byte ctor entry. KeyBoard::Navigate 801BF09C matches exactly when vertical movement is expressed as explicit if (dx != 0) vert=0; else vert=btn==3 ? 1 : 0; replacing only with bool equality leaves extrwi instead of srwi. Same source form improves NameEntry::Update. TextNode::SetSpacing(int) inline member retaining this through spacing conversion/refresh removes three redundant loads (12 bytes), taking CardEntry ctor to exact size 2436 and 99.36781%; table-index and FP web residuals remain. Read all 64 target extabindex entries: no legal internal split among 66 boundaries; first conflict BAA88 etb132C4 vs BB6D4 etb131AC, last C1B78 etb13D94 vs C1EB4 etb13C90. No native gain or flag flip.

## c3_a1_astra_20261105
Source: Codex worker c3_a1_astra_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_a1 partial: CoinChallengeUpdate sprite slide/cull extraction into a static inline helper removes an extra position-base move and improves text 97.209946 to 98.24586 while extab remains 100 and extabindex 91.66667. Remaining primary body is 1452 bytes versus target 1448 with input-result copy and GPR color residuals. All five single-function TUs remain NonMatching; no native gain. PlayStats aggregate regrouping does not move the 0x198..0x1A4 scheduling boundary; KartChoice changed flag still shares dead status r31 rather than independent r28.

## c5_s2_dnstartdinonm_20261105
Source: Codex worker c5_s2_dnstartdinonm_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 520 B.

DNStartDino Draw 80229E0C: extracting Hinoko ember rendering verbatim into a static inline DrawHinoko(Hinoko*) helper resolves the monolithic Draw loop-register residual. Original GC/2.6 flags and existing EH mappings suffice; text 520 B, extab 40 B and extabindex 12 B all 100%. Full coordinator build SHA-1 OK; source .o appears on main.elf input edge.

## c5_m2_8021f088_20261105
Source: Codex worker c5_m2_8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2104 B.

c5_m2: NextWnd Update 80221674 requires case 0 early return; Count 802218A4 caches bool held==1 before its float/color work. Both text/EH 100%. ItemWnd ShowTicket 80222564 reaches exact text by passing fn_8021691C result to inline SetTicketText, removing r3->r0->r30 extra copy. DTK accepts independent splits at 80222564 and 80222968. Promoted +3 fn / 2104 B, coordinator SHA-1 ea30f3b1 OK; actual main.elf addresses checked. ShowItem stack arrays need pos before buf; inline formatting/sprite helpers improve to 97.54256%, still NonMatching due colors/conversions and GPR webs.

## c5_s4_draweffectrel_20261105
Source: Codex worker c5_s4_draweffectrel_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 736 B.

c5_s4: EnemyFace_nm4 8022BEB4 rescued by a TU-private minimal class view with undefined first virtual key, suppressing RTTI-off duplicate vtable. Text/extab/extabindex remain 100%; Matching full link source input and DOL SHA-1 verified. DrawEffect ReleaseCallbackResources 800B542C reaches 100% by inline trail-group helper at self+0xD0 and centered -1..1 loop over group+0x98+i*4; reproduces target group base reuse.

## c5_s9_terrainwalled_20261105
Source: Codex worker c5_s9_terrainwalled_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 380 B.

TitleNameHud ctor 80252EE4: real empty GlyphText destructor must remain alive through final activation/cull loop. Bridge GlyphText dtor to dtor_800869D0, HudPart dtor to dtor_8021617C, VHolder<FlowFaderF> (length 21) to dtor_801F4A80. Owned EH 128 bytes and index 12 bytes become exact with @140/@141 bridges. Naming cached width w and half-count span fixes fnmsubs operand order; final retained source differs only at +0x358 (mr r23,r22 vs li r23,0). Keep NonMatching.

## c5_s10_anon801fd320_20261105
Source: Codex worker c5_s10_anon801fd320_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c5_s10 partial: MsgPopup::Tick 80203224 improves 98.234566 -> 99.06584 with named px/py temporaries before each ResCtrl::Show and a separate float yy=s*(base+(float)dy) before y+yy. This restores exact 972-byte primary size and all owned EH/index bytes; extra weak ResCtrl dtor EH remains. FP/GPR allocation is still non-exact. A future promotion also needs .data 804EC3C4..804EC3E0 jump-table ownership/bridge; current source emits @85 while old bridge expects @106. fn_80203C24 explicit pending-busy early return fixes one branch (98.816795 -> 98.854965), but direct pending-r30 hoisting/missing mr and duplicate RTTI/data remain. CardEjectTask body cached pool must precede base call in target; moving array allocation into member initialization or removing the pool cache regresses. No flag flips/native gain.

## c5_m4_802052e0_20261105
Source: Codex worker c5_m4_802052e0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 896 B.

TitleNameHud Update 802529E4: extract only sprite positioning into static inline helper, retain cull loop in caller, and reuse x for badge/glyph positions to resolve GPR and FPR webs. Own jump table 804F2044..804F2060, DATA_ALIGN4_TUS, bridge @116 table / @117 EH / @118 EH index. Define SetDelay, Draw, Update in target order: symbol-level and section objdiff can report 100 even with reversed physical order. Final full DOL SHA-1 OK; 3 fn / 896 B native.

## c5_m5_enemyface_20261105
Source: Codex worker c5_m5_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 1440 B.

c5_m5 EnemyFace: Update requires unsigned-byte hidden helper with (bits & 0x8000000000ULL)==0 ? 0 : 1 to preserve the target branch island, inline model position/scale helpers to preserve receiver webs, and exact external scale constant lbl_806DB5B4 (1.2240002155303955, not rounded 1.224f). Sort uses plain eye output storage but a genuine three-float Vec3c loop temporary with inline empty dtor; this reproduces exact 24-byte DESTROYLOCAL at SP+0xC. Inline camera depth-range helper fixes camera r30 web. Queue manager accessor and explicit SetPath output-byte stride match; safe cuts at 8022B150 and 8021984C accepted. Full source-linked SHA-1 OK, +4 fn/1440B.

## c5_s11_anon80203ea0_20261105
Source: Codex worker c5_s11_anon80203ea0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 588 B.

c5_s11: fn_80203F5C popup open needs explicit else return 0 when both cur and pending are occupied. TU-local copy plus external target RTTI runtime fn_80271340(t,0,MsgPopup_RTTI_806D0268,FlowTask_RTTI_806D0260,0) gives 340 bytes and all owned sections 100%, no emitted data. Cursor destructor 802051E8 promotes unchanged text with weak FlowFaderI bridge to fn_801F26C8; extra EH discards. YesNoCursor Update declaration px before py fixes FP homes (99.72603 to 99.863014), but list/visible r30/r31 swap remains after scope/helper attempts. Full DOL SHA-1 and ELF positions verified for two promoted functions.

## c5_s12_anon8020aad4_20261105
Source: Codex worker c5_s12_anon8020aad4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 668 B.

c5_s12: BattleMenu ctor 8020BACC cached list r28->r30 resolves by extracting fn_801F4DF0(l,fn_80201A48(0),2) into static inline AddInitialTask(FlowSceneList *l). Exact 668-byte text, 52-byte data and owned 96-byte EH/12-byte index after bridging @106 jump table, @107/@108 EH names; append weak copies in extab_order and add DATA_ALIGN4_WEAK_TUS. Coordinator full build SHA-1 OK; main.elf fn at 8020BACC size668 with source input true. Same helper fixes GrandPrix list but leaves cup r29 vs r30 (99.77401%). AAD4 switch/if forms fail to retain target branch-over-branch. ItemShowcase aggregate-reference or aggregate-part representation leaves same extra base move.

## c5_s13_anon8020c974_20261105
Source: Codex worker c5_s13_anon8020c974_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 728 B.

c5_s13: CardModeRoot::OnTaskDone text/extab/index were 100%, but dynamic_cast emitted extra local RTTI (.data 76 B/.sdata 24 B). Explicitly calling existing fn_80271340(task,0,CardMenuRoot_RTTI_806D0310,SceneBase_RTTI_806D0308,0) with canonical extern 8-byte RTTI records preserves all text and removes duplicate data; full-link SHA-1 OK. fn_8020F220 needs flag flip only. Draw Remove named result assignment restores return/argument stack slot order, 96.55224 to 96.61194; iterator SP+10 vs +14, missing assignment copy and r4 caching persist. ScoreDisplay scoped scale and explicit x/y/z/scale locals both leave final-three-block FP coloring unchanged; original retained.

## c5_s15_anon8021f088_20261105
Source: Codex worker c5_s15_anon8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1044 B.

Coin mileage rescue: first-declared undefined derived virtual key suppresses clCSSceneCoinMilage/clGetSumLine emitted RTTI-off vtables without altering inherited slots or destructor text. Own EH bridge @231/@232 -> etb8001B554/eti8002A50C and @165/@166 -> etb8001B71C/eti8002A554 makes owned EH exact; extra weak dtor EH discards. clGetCoinLine Update uses 3.0f/360.0f literals to reproduce FP colors. All three source-linked, DOL SHA-1 OK.

## c5_s17_fn801f8668_20261105
Source: Codex worker c5_s17_fn801f8668_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1108 B.

fn_801FA310 becomes exact by declaring case-4 count then pointer at function scope before CardInput; fixes r29/r30 coloring without changing case-5 locals. All text/EH/jump-table sections 100%; full SHA-1 OK.

## c5_s14_anon80218b80_20261105
Source: Codex worker c5_s14_anon80218b80_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 752 B.

c5_s14: clGetCoinLine dtor 80220780 can be rescued without owning its vtable: opt-in undefined virtual key before its destructor suppresses duplicate RTTI-off vtable and weak Draw emission; primary 224-byte text and 40-byte EH remain exact. Bridge compiler @167/@168 to @etb_8001B3D4/@eti_8002A44C. Appended weak ResCtrl dtor is discarded. CreditHud Update 80218B80 only needed Matching plus @26/@27 EH-name bridges. Coordinator full build and DOL SHA-1 verified, expected main.elf addresses checked.

## c5_s16_anon8021f088_20261105
Source: Codex worker c5_s16_anon8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 392 B.

Coin destructors 802246A4/80224800 unlock with existing undefined Update override declared before destructor (opt-in header declaration ordering). This suppresses incorrect RTTI-off vtables without changing inherited virtual slots or text. Owned compiler EH symbol bridges give text/extab/extabindex 100%; source inputs and exact main.elf addresses plus coordinator DOL SHA-1 verified. Native gain 2 / 392 bytes.

## c6_nt8_playerdata_20261105
Source: Codex worker c6_nt8_playerdata_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 756 B.

c6 NT8: PlayerData fn_801D6558 matches 436B text/8B EH/12B index with a genuine 0x1DC-byte snapshot and CupRank inline validation. Initialize normalized=cup, then initialized cc=g_ccClass, then normalize 9..16; this gives exact load scheduling (a deferred cc assignment or helper extraction left residuals). fn_801D6DF0 becomes exact 320B when the 1..8 loop lives in AllCupsComplete inline helper, with a signed int rank temporary before >=4 comparison. Source inputs and ELF ranges verified; full DOL SHA-1 OK.

## c7_s2_20261105
Source: Codex worker c7_s2_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1692 B.

ServiceButton_Handler 8002D0B0: new ServiceMenu(11), size 0x28C, private virtual slots Tick/Draw/dtor, and per-TU ctor bridge give exact text and DELETEPOINTER EH. ServiceMode +8..+10 must be represented as a two-word aggregate member so its implicit copy emits load/load/store/store rather than scalar load/store/load/store. One shared inline ServiceFrame reproduces both target loops exactly; full source-linked DOL SHA-1 verified.

## c7_s3_20261105
Source: Codex worker c7_s3_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1464 B.

c7_s3: LakituStart_Init 8003DB40 is a real 0x58-byte constructor whose new clNormal3D(const void*,0) produces exact 404-byte text and 24-byte DELETEPOINTER EH via the existing mangled bridge. ObjectChain_RenderInZRange 80046960 matches with four explicitly nested native stages: inline NeedsEval/SetupMatrixSub, JObj_NeedsEval/SetupMatrixSub, JObj_EvalIfDirty, JObj_EvalIfDirtyAndGetMtxPtr, then recursion. Initialize the inline NeedsEval boolean after its null assertion; initializing before the assertion extends it across the call and changes its GPR. Both source inputs passed full DOL SHA-1 and linked address/size checks.

## c7_m3_20261105
Source: Codex worker c7_m3_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 9 fn / 4324 B.

clDrawMan 80079CDC..8007ADC0: both timer20/timer42 locals must live together in inline DrawBucket::Dispatch to reproduce SP+8/+10. Inner timer-only extraction fixes node/end r24/r25 but leaves stack order reversed. AllocateNode must cache nodes+nodeCount before ++nodeCount to restore the target count/stride webs. New array EH uses padding C6 02 twice; owned extab order starts with trailing base dtor, then getter/dispatch/three sort methods. Implicit uint-to-float double cookie owns 806D2F38..806D2F40.

## c7_s4_20261105
Source: Codex worker c7_s4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 976 B.

KartItemSubObject ctor: vptr+owner form the 8-byte base; the Vec at +8 is a derived member. Putting it inside the base preserves text but loses one DESTROYMEMBER per new site (60 EH bytes total). Distinct owning pointer template instantiations are necessary for separate inline throw() specifications in multi-member destructors; one repeated member type merges specification records despite exact text.

## c7_m4_20261105
Source: Codex worker c7_m4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

SpecialFaceMesh 8007BE70..8007CC9C new-TU partial: canonical SpecialFaceMeshPrivate types and real new expressions yield exact AddFace/factory plus array-holder dtor, wrapper, empty ctor, pointer-vector dtor and base dtor (seven text-exact symbols). Explicit inline FaceRaySegment ctor/dtor reproduces __construct_array/__destroy_arr and DESTROYLOCAL; nontrivial SpecialFaceVec temporaries restore otherwise optimized-away stack stores in ray segment. Group remains NonMatching: Raycast 92.09091, Segment 81.41053, InsertFill 96.05944, Reserve 91.79412. EH order starts dtor_C5E0,dtor_CC54 before Raycast; cannot isolate exact seven due reversed group. Compiler defers RaycastSegment/weak holder dtors, so physical text ordering must also be repaired before promotion.

## c7_m7_20261105
Source: Codex worker c7_m7_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c7_m7: PanelCda40 native model uses CdaSpriteSlot::~ throw() and CdaHolder::~ throw() to reproduce both __unexpected islands and exact owned EH. Color packing in an inline four-u8 helper changes fn_801CDB00 from 96.73913 to 100%; direct packed expression adds a move and changes color register. List destructor retains r7 versus target r0 for end iterator after three hypotheses. Entire reversed EH group remains NonMatching. Warp Reserve canonical user-defined corner-copy model reaches 82.94%; implicit corner-copy falls to 60.05% via bulk-copy loop, so best restored.

## c7_s10_20261105
Source: Codex worker c7_s10_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c7_s10: WarpZone_CalcEdgeVectors is naturally modeled as a constructor of a 0x50-byte value with four nontrivial WarpCorner members. Modeling it as a returned WarpZoneValue produced a copy and two __destroy_arr cleanups (912B); a declared derived constructor produces the single 528B body with target-shaped local cleanup. Table index CSE and loop web coloring still prevent exactness.

## c7_m8_20261105
Source: Codex worker c7_m8_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

New Menu801F0CC0 reconstruction: final helper fn_801F2690 owns extab 80016E94, before the first method extab 80016E9C. This reversed dependency spans all 25 functions through 801F26C8; no safe positive subset split. A real destructor with delete[] sprites, context cleanup and VHolder<FlowFaderI> member reproduces fn_801F25BC text exactly. Native source remains NonMatching; no linked gain claimed.

## c7_s13_20261105
Source: Codex worker c7_s13_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1284 B.

c7_s13: fn_8015BF18 matches 1284-byte text and owned 356-byte EH/12-byte index with genuine ResultAward/ResultIntro inline ctors and canonical ResCtrl. A small inline sprite ctor loading size then alpha before Sprite_CreateWithParams fixes reversed FP common-value load order without changing call timing. Bridge primary compiler @164/@165 to @etb_8000F2F8/@eti_80025A00. Appended weak ResCtrl destructor is discarded; source-input link and full DOL SHA-1 verified.

## c7_s15_20261105
Source: Codex worker c7_s15_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2120 B.

fn_8016F158 draw: moving asserted root-matrix setup into an inline pointer-returning GetMatrix helper removes an extra lwz-r0/mr-r27 copy. Naming alphaFactor=self->alpha before partAlpha=constant*channel.x restores f2/f3 assignments; both changes together give exact 1068B text and 8B EH/12B index. fn_8016F584 state/keyframe update matches first native compile. fn_8016FA50 constructor has exact owned EH and size but independent loop-web register identities remain; preserve NonMatching.

## c7_m9_20261105
Source: Codex worker c7_m9_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c7_m9 partial: NamCamFlow group 801F2B70..801F4D3C has no safe internal EH cut. Genuine ownership hierarchy reproduces dtors 3970/402C/480C/490C/498C/4A24/4A80/4B10 exactly with GC/1.3.2 and -use_lmw_stmw on. Scalar-byte holder needs explicit if(p) before delete p to preserve target null guards; a raw delete char* calls free unconditionally. fn3198 uses open external position array (large data), calls isJapanese before initializing the default resource variable, then branches to the alternate. These yield exact text/owned EH. Whole TU stays NonMatching (14 exact, four partial, four pending), no native gain. Native source definition/emission order and emitted helper ctors also need resolution before eventual promotion.

## c7_m10_20261105
Source: Codex worker c7_m10_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

MenuModeLane 801F5BF4: inline MenuScene constructor must be visible before the owning MenuMode constructor. Add an undefined first-declared virtual key to suppress synthetic MenuScene vtable emission. Use inline MenuWidget::SetPosition(x,y) to capture each pointer once: direct widgets[i]->x/y writes caused three extra pointer reloads; method form gives exact 956-byte text and all owned EH. fn_801F6178 remains NonMatching after three hypotheses, despite the other seven functions and owned EH being exact. Reversed EH group 801F5A9C..801F6454 cannot be split to promote the exact subset.

## c7_s21_20261105
Source: Codex worker c7_s21_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1432 B.

c7_s21: bitread 8018A8D4 six inline ReadBits loops match exactly with float literals 0/60/10/100/1000; external const divisor caches across inline loops and changes scheduling. 8018B14C needs int fn_801F8DB0 argument, out[i] rather than postincrement, and i<5 && i<5 for exact bottom branch pair. Both text/EH/index 100, linked source ranges and DOL SHA-1 verified. SoundProp ctor 8018A70C genuine C++ with CourseMarkerBase/new clNormal3D gives exact EH; explicit case0 retains EH PCs but remaining prologue/switch tree differs. Kept NonMatching.

## c7_m12_20261105
Source: Codex worker c7_m12_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

CardCreditFlow (80241C1C..80242DE0): GC/1.3.2 real C++ using canonical FlowScene yields nine exact functions and exact complete EH/data. Two singleton ternary new expressions must finish in a local pointer initializer before the subsequent float setter call; putting new directly inside the call argument extends EH regions and emits conditional flag resets. Inline CreditUnavailable helper gives target register homes, unlike the equivalent open-coded local predicate. lbl_806D1A98 is viewed const after startup initialization to reproduce legal invariant-load scheduling. Final fn_80241C88 AND operand commutation remains; keep whole group NM. No codegen byte patches were used.

## c7_s23_20261105
Source: Codex worker c7_s23_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1308 B.

fn_8018E108 and fn_8018EDE0 match exact native text/EH with inline base vptr construction and new clNormal3D. Null-safe child/next accessors must spell `if (p == 0) return 0; return p->child/next;`; ternaries select inverse branches and a return-through-r0 temporary. Early returns remove these differences and produce 100%.

## c7_s29_20261105
Source: Codex worker c7_s29_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

CollisionUpdate 8019B080 standalone split owns extab 80012668..800126B0 and index 80027428..80027434. It has six DESTROYLOCAL Vec slots: contact 24, normal 30, hit point 3C, up 48, forward 54, previous position 78. Value-argument constructors and a nontrivial normal temporary recover target stack layout. In-place 4x4 matrix multiplication plus aggregate copies increases native text similarity from 70.70 to 81.33%; TU remains NonMatching after three structural hypotheses. No exact native subset exists within this one large function.

## c7_m2_20261105
Source: Codex worker c7_m2_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

CourseEnvironment 80046D84..8004893C: real C++ draft yields 15/17 text-exact and 100% owned EH. CourseScene_Load new-expression allocation pointer r22 and all 11 DELETEPOINTER PC intervals are exact. Explicit cached rodata/data bases and branch-local table additions improve load 92.11 -> 98.70. JObj_EvalIfDirty requires the early-return condition (!joint || !NeedsEval(joint)) to retain the branch-over-branch; NeedsEval public int result with byte inline predicate retains clrlwi. Complete reversed EH span ties the first dispatch functions to trailing JObj functions and dtor; no native partial promotion.

## c7_m14_20261105
Source: Codex worker c7_m14_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RaceDigits 80246DE4..80247B8C: genuine VHolder/FlowFader/ResCtrl model gives six text-exact functions and 99.84561% primary ctor. ResCtrl temporaries must each occupy a separate scope to get exact primary ctor EH (function-wide scopes yielded 0x1C4 instead of target 0x1F4). Put Init inside inline DigitListMid ctor, rather than final DigitList ctor, to get DESTROYBASE dtor_80247B1C and target r3/r26 setup. Resource before loop-index declaration fixes the plain local register swap in Update. Literal float constants avoid f31 hoisting from immutable externs. Primary ctor still loads coordinate y before x at two sites; no promotion. Physical text order also needs attention before future promotion because compiler emits shared weak copies between current strong definitions.

## c7_m15_20261105
Source: Codex worker c7_m15_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 1380 B.

c7_m15: 802483B4..802488FC native group matches all text (1352 B), EH (76 B), EH index (60 B), switch tables (56 B). Use true derived ctor/new expression for DESTROYBASE/DELETEPOINTER. Target base-dtor call in free deleting wrapper passes flag 0; direct C++ explicit dtor expression passes -1 and differs. Final delete wrapper must invoke a virtual destructor (delete through private virtual view), not a virtual ordinary Destroy method: this generates hidden flag 1 and exact 56 B. EH order begins with final delete wrapper, then first four methods; index stays address order. Switch tables 804EEB4C..804EEB84 need DATA_ALIGN4_TUS; existing 4-byte gap at 804EEB84 remains unowned, no filler added. Full source-linked SHA-1 OK.

## c8_s36_20261105
Source: Codex worker c8_s36_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1240 B.

c8_s36: fn_801B7CD0 matches via canonical Sprite/new, coin quotient/remainder pair before cost pair, and inline SetPosition capturing the sprite pointer once. VoiceBrowser draw 801B70EC matches when string-pool base is captured before context null guard. 801B739C retains a localized FP clamp register residual at 99.496124%.

## c8_s39_20261105
Source: Codex worker c8_s39_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c8_s39: clFlowClass_Update native reconstruction reached 99.81191% with exact 88-byte allocation EH. Declaring externally referenced rodata bytes const let MWCC hoist loop aggregate-table loads into saved registers (r21-r31/frame C0); mutable extern restored per-iteration loads and target r26-r31/frame A0. An inline interpolate(start,end,frame,duration) helper reproduced the target FP computation/register sequence. Still NonMatching: one input-selection reload is absent, leaving later text four bytes early. No native gain.

## c8_s38_20261105
Source: Codex worker c8_s38_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1492 B.

c8_s38: clFlowEntry_Update 801BA380 matches native 804B text + 24B DELETEPOINTER EH + 12B index. For inline boolean equality predicates, explicit int finished=(unsigned char)card->Done() and int held=(unsigned char)(input->held==1) produce target cntlzw/extrwi materialization; direct if(Done()) folds to cmpwi, whereas Done()==1 adds a comparison. Preserve the nested else-return structure for its branch-over-branch. fn_801C1F88 688B and all EH/index match using mutable extern aggregate animation tables and one captured input pointer for clearing fields. Full DOL SHA-1 and actual ELF addresses verified.

## c8_s42_20261105
Source: Codex worker c8_s42_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 2180 B.

c8_s42: fn_801CCAAC real new SelectClosing plus declared SelectTween array ctor bridged to fn_801CDA7C gives exact DELETEPOINTER EH. Put vt/sprite/delay in member initializer list before array construction. Call an inline Fade method before passing &p to list insertion: its this parameter preserves the cached pointer and original SP+10 p slot; open-coded field writes caused repeated stack pointer reloads. fn_801CCDA4 needs outer end local plus inline TickSelectEntries(node,end) for exact self/end/entry/node GPR partition. fn_801CB818 compares float constant against (float)--countdown to match conversion before member store. All three GC/2.6 text/EH/index exact and source-linked full DOL SHA-1 OK.

## c8_s44_20261105
Source: Codex worker c8_s44_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2160 B.

c8_s44: fn_801CE918 and fn_801CEB78 match 2160B text plus 160B EH, 24B index and 32B switch data using canonical AnimSprite new expressions. Declare RowAnimation * before RowLayout * inside each switch case to get target base-load/register scheduling. Inline SetPos and SetRowScale capture the sprite once. Single-function blobs split independently. Constructor clFlowTaPlease_Init remains NM at 93.340836%; constant table-base caching/lifetime differs, no filler or manual EH used.

## c8_s45_20261105
Source: Codex worker c8_s45_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 272 B.

fn_801D1D9C (272B) matches natively with a nontrivial copy constructor on its single-pointer iterator: CW then uses the hidden return destination for DoublyLinkedList_EraseRange and emits exact stack argument slots. Trivial aggregate iterator returns use a register instead and diverge. Three nested list null checks reproduce the inlined destructor chain. Text and 8B/12B EH sections are 100%, full DOL SHA-1 OK.

## c8_s49_20261105
Source: Codex worker c8_s49_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2356 B.

c8_s49: PathFollower_Init 801DC320 matches 320B native text plus 108B owned EH using canonical PathCursor as a base view, real new FollowerCursor, and a throw() owning pointer member. Weak owner dtor bridges to existing dtor_801DC460 and discards. Update 801DBAA8 uses inline ResetFollower expanded seven times; cooldown global lbl_806D1898 read-only declaration permits load before requested-state store and completes exact 2036B text/272B EH. Both source-linked, ELF addresses/sizes and DOL SHA-1 verified.

## c8_s52_20261105
Source: Codex worker c8_s52_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c8_s52: AI_SystemInit genuine member-owner constructor/new AIKart gives exact 700-byte operation/branch layout and exact EH PC intervals; remaining this/flag/index/cup register homes prevent promotion. RankingMgr_UpdatePositions uses inline FindLast/FindFirst/Notify to improve 86.79 to 99.13 with exact EH; only final-loop register homes differ. Per-frame scalar Vec initialization avoids CW zero-template rodata copies and improves 83.51 to 89.35; flattening pair loop and retaining driver alongside rank record reaches 93.77. All three retained NonMatching after three hypotheses; full DOL SHA-1 remains exact.

## c8_s51_20261105
Source: Codex worker c8_s51_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 496 B.

fn_801E81D8 (AIKart deleting wrapper) matches 496 B text plus 264 B EH and 12 B index using canonical AIKart/AIOwn<T>, explicit reverse-order holder destruction, and real throw() destructor EH. A nullable cast from AIKart* to its secondary AIWarpResponder base added three instructions even inside the outer self guard; passing &self->AIWarpResponder::vptr to the existing C ABI base destructor avoids that adjustment and gives exact output. No manual EH or opcode emission is used. Full source-linked DOL SHA-1 verified.

## c8_s53_20261105
Source: Codex worker c8_s53_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c8_s53 candidate 801EE36C: using canonical CollisionVec with float constructor and empty destructor in all three branch scopes retains the target temporary stores/frame; using PhysicsPlainVec/set removes stores. Numeric sqrt constants 0.5/3.0 recover target FP allocation better than external double declarations. Boolean if(length) recovers target fcmpu operand order, unlike explicit comparison with literal zero. Best native text 99.81315%, exact primary 24-byte EH, remaining sqrt scratch-slot swap and transit FP web allocation. No promotion.

## c8_s56_20261105
Source: Codex worker c8_s56_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c8_s56 partial: independent sprite texture/draw functions 801F6D58/7198/7344/7604 reconstructed as four honest NM TUs. Existing DrawDesc801F supplies canonical prefix, extended privately with blend modes and matrix at +0x64. Three scoped draw-node subclasses with inline vptr-setting destructors reproduce DESTROYLOCAL kind/stack offsets and primary 56-byte EH shape for 7604; its primary text remains four bytes long and 97.693665%. No native gain.

## c8_s60_20261105
Source: Codex worker c8_s60_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 636 B.

c8_s60: SpriteAnimHandle ctor 8023F320 matches native 292B plus 24B DELETEPOINTER EH using canonical AnimSprite new and simple for(i=0;i<50;++i) sentinel copy. GC/1.3.2 naturally emits target five-way unroll, including apparently dead li/addi induction register. Standalone flush needs explicit handle cursor plus i (rather than indexed inline Flush) for exact cursor/index register identities. Native Destroy indexed inline Flush already matches. 3 fn / 636B source-linked full DOL SHA-1 OK.

## c8_s62_20261105
Source: Codex worker c8_s62_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 428 B.

c8_s62: fn_802437AC new RivalMarker with nested new RivalOther yields exact 428B text, 48B DELETEPOINTER EH and 12B index using GC/1.3.2 + use_lmw_stmw. Cache render slot before GetDisplayBufferIndex to preserve pre-call load; declare kart pointer before loop index for target r29/r28 allocation. Full source-linked DOL SHA-1 and 802437AC..80243958 ELF range verified. Other independent singleton TUs remain NonMatching at 99.08/98.20635/99.14286 percent.

## c8_s67_20261105
Source: Codex worker c8_s67_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 1056 B.

HudSelection 802457E0/80245850/80245AC4/80245B10: canonical FlowFaderF::Step/Done and VHolder<FlowFaderF> explicit reverse-order destruction produce exact native bodies and owned EH. Two holders of the same type share one SPECIFICATION action, matching target. Compare constants on the left of final equality tests for exact fcmpu operands. Update switch table 804EE854..804EE870 requires DATA_ALIGN4_TUS. Full source-linked SHA-1 and all four ELF addresses/sizes verified.

## c8_s69_20261105
Source: Codex worker c8_s69_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 544 B.

c8_s69: isolated AdvanceCard ctor 8024629C uses canonical DigitHudBase, two VHolder<FlowFaderF> members and ResCtrl local. All 452B text and owned 84B EH match with GC/2.6. Real new DigitHud factory 80246B78 matches 92B text and 24B EH. Whole ctor EH section scores below 100 only from discarded weak destructors. Full DOL SHA-1 exact, source link edges and ELF addresses verified.

## c8_s40_20261105
Source: Codex worker c8_s40_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 676 B.

c8_s40: fn_801C3AA4 draw pass matches native text/EH exactly with a private virtual dispatch view (Draw at +0xC, Finish at +0x10). FigureSlot_Tick uses real sprite new expressions and inline SetPos/SetScale: evaluate both coordinates before stores and capture the pointer once for two scale stores; this improves 87.78% to 99.42% with exact owned EH. Floating interpolation cookie stack order and FP homes remain, so retained NonMatching.

## c8_s54_20261105
Source: Codex worker c8_s54_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c8_s54: EnemyRun_BaseInit 801F0644 is a genuine constructor with VHolder<EnemyRunPath> at +4 and seven canonical PhysicsCollisionVec members (+4C,+58,+A8,+B4,+CC,+D8,+12C). VHolder::Reset(new EnemyRunPath(owner,kart)) reproduces exact 176-byte owned EH, including throw() Reset specification island and DELETEPOINTER r24. Scalar 0.0f/1.0f literals remove alias-induced reloads; native text 98.08%, 1300B. Explicit pointer matrix loop caused unwanted unrolling and r29/r30 swap; retained indexed form NonMatching.

## c8_s63_20261105
Source: Codex worker c8_s63_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 792 B.

c8_s63: fn_80243A24 native new ItemListHud(layer) using existing HudPart and VHolder<FlowFaderF> yields exact 340B text and 56B owned EH. Its reverse-loop destructor fn_80243B78 is exact 248B with -use_lmw_stmw on; canonical throw() holder generates specification EH. Three exact independent blobs give 792B native gain with source-linked DOL SHA-1 OK. fn_80243C70 Draw uses canonical ResCtrl scopes plus real new PanelItem: 99.96689%, exact size and owned EH. Inline DrawPanelItem recovers GPR homes, captured SetPos helpers remove reloads; final f30 vs target f28 range remains, so kept NonMatching after three structural hypotheses.

## c8_s64_20261105
Source: Codex worker c8_s64_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 1020 B.

c8_s64: 80244128 native 592B and owned 60B EH match using real GaugePulse/FlowFaderI new, canonical VHolder/ResCtrl, captured SetPosition and ShowYX(r,y,x,z) to evaluate x before y. Ordinary Show(x,y,z) leaves a 99.91892% FP-coordinate swap. Concrete nonvirtual GaugePulse dtor with an undefined virtual key suppresses extra vtable data; polymorphic delete uses canonical VObject view. Native 80244378 (264B) and 80244480 (164B) also match. All actual ELF addresses/sizes checked, source edges verified, full DOL SHA-1 OK.

## c8_s65_20261105
Source: Codex worker c8_s65_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 3040 B.

c8_s65: four new singleton ItemUseEffect TUs at 80244840..80245420 match 3040 B native text plus 372 B owned EH and 48 B EH index. Reuse canonical FlowFaderF/I and VHolder. Constructor member initializer ordering and inline ItemUseBurst new expression naturally reproduce DESTROYMEMBER/DELETEPOINTER payloads. Update must retain explicit no-op switch states 4/5, and use a literal 1.5f in the category fallback arm while earlier arms use the captured comparison constant: this reproduces a fresh target lfs instead of fmr. Actual source link inputs, final addresses/sizes, and full DOL SHA-1 verified.

## c8_s66_20261105
Source: Codex worker c8_s66_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 956 B.

c8_s66: fn_802455EC text can match with one VHolder<T> type, but EH then incorrectly merges all SPECIFICATION actions. A distinct byte-tween type for the final member versus shared float-tween type for the first two reproduces exact 92-byte EH. ResCtrl Show(self->x,self->y,z) evaluates y before x; staging x and y locals restores target load order in fn_80245420/fn_80245704. Native source-linked 4 fn/956 B and full DOL SHA-1 verified.

## c8_s70_20261105
Source: Codex worker c8_s70_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 552 B.

c8_s70: Race digit HUD deleting destructor 80246BD4 matches 528B text +180B EH +12B index. Use canonical DigitOwner and VHolder plus a private list facade with nontrivial iterator copies. Initial body call requires named end iterator before begin iterator; member list destructor uses inline Begin()/Finish() return expressions. This preserves target cached sentinel and hidden-return/argument stack slots. Scalar/class placement-copy variants for 80247C3C do not reproduce its FP/exception bookkeeping; retain NonMatching.

## c8_s73_20261105
Source: Codex worker c8_s73_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 728 B.

RaceHud 80249054/80249130/80249274 native text/EH exact. Update input processing needs branch-local InputState *in=g_pInputState followed by CGameCoin_ProcessInput(in == 0 ? (InputState *)0 : in), matching existing CardModeRoot idiom. Direct GetInput() argument collapses a branch. Destroy uses canonical HudDisplayFlags::SetOther(0) to avoid zero constant hoisting across singleton accessor, recovering exact r30/r31/frame10. Draw ternary new ItemMsgWnd uses extab padding C6 02. Adjustment thunk 8024904C retained NM.

## c8_s71_20261105
Source: Codex worker c8_s71_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 472 B.

fn_80247CFC float-list insert: inline RAII allocation guard + real placement new of float produces the target stack anchor (stw r1) and unreachable cleanup call without manual EH. Guard must die before the loop decrement. The guard first field is a pointer to the allocator/sentinel member (&list->last), not the list pointer or a node pointer: this distinction preserves the otherwise missing mr r0,r30. GC/2.6 with -use_lmw_stmw on matches the 176-byte primary function. Extra weak guard destructor EH discards cleanly at full link.

## c9_L1_20261106
Source: Codex worker c9_L1_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

BootDispatcher 8002DD58..8002F640: genuine C++ reconstruction reaches 96.16123% and exact 6376-byte primary text size. Shared inline frame helper requires inline_max_size(10000)/inline_max_total_size(100000) to expand FinishFrame. CopyFrame must return early from alignment and capacity error branches: this duplicates each scoped timer cleanup naturally, restores the target 208-byte EH action/PC-interval structure, and improves text from 87.83814% to 96.16123%. Remaining register-save range, stack locations, scheduling, and PC offsets differ, so the singleton stays NonMatching; no native gain.

## c9_s3_20261106
Source: Codex worker c9_s3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 880 B.

EffectSpeed_Init 800650E0 matches 300B text +100B owned EH via genuine owner ctor, two inline derived virtual action constructors, tag/line placement new with no placement delete, and two distinct declared owning-holder destructors at +20/+24. Placement allocation avoids spurious DELETEPOINTER actions; inline base/derived ctors reproduce DESTROYBASE around virtual reset, owning members reproduce DESTROYMEMBER. Full source-linked DOL SHA-1 OK.

## c9_s7_20261106
Source: Codex worker c9_s7_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 992 B.

HudResultFlow 80248904..80248CE4: reuse canonical HudRoot/HudChild/HudSmall from HudFlowPrivate.h; plain vptr assignment in genuine derived constructor reproduces DESTROYBASE and real new HudSmall reproduces DELETEPOINTER. Native 992B text, 76B EH, 60B index, 56B switch tables exact on first approach. Reversed extab order places final virtual-delete helper first; per-TU extab_order and DATA_ALIGN4_TUS preserve full DOL SHA-1.

## c9_s9_20261106
Source: Codex worker c9_s9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 49 fn / 9760 B.

c9_s9_20261106: CardTaskChecks matches 49 fn / 9760 B, all owned EH and final DOL SHA-1. A timer local must be default-constructed BEFORE its explicit OSGetTick reset to reproduce EH PC 0x18; an OSGetTick-calling ctor delayed EH to PC 0x28 with identical text. Direct vs inlined ResCtrl locals change stack allocation order: final welcome frame must be direct while inner frame is inlined; printer left-choice resource is inlined while right-choice is direct. A plain C factory view preserves WaitInput_New before its real C++ virtual destructor when the compiler otherwise defers new-expression factory emission. Verify physical addresses after weak-copy discard.

## c10_u12_20261106
Source: Codex worker c10_u12_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u12: GpPleaseInit 801CD030 retained NonMatching. Inline GpPanelBase::Fade restores cached tween receiver for the second label and improves 99.298134 to 99.352486 with identical 2576B size and unchanged 468B EH/12B index. Loop-member extraction regresses to 99.21429 and moves stack slots; explicit C ABI Append regresses to 99.31056. Remaining list/sentinel/index/new-pointer register partition and active/end scratch swap are unresolved. Do not repeat these three hypotheses. Full fallback-linked DOL SHA-1 OK; no native gain.

## c10_u17_20261106
Source: Codex worker c10_u17_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u17 ShowItem 80222968: unsigned char SetItemLabels alpha preserves separate packed white colors and restores exact 1880-byte size/EH. Direct sprintf(... fn(first), fn(second)) in FormatItemNames restores kind=r25 and name=r30; named helper local instead gives kind=r26/name=r25. Combined text 98.78723%, extab/extabindex 100%. Residual: Case 1/3 timer conversion: high-word stw scheduled before li instead of after; xoris/store uses r0 instead of r3; second white constant is li r5,-256 instead of mr r5,r4. Case 3 conversion additionally uses f0/f2/f3 instead of f2/f3/f4. Float helper re-conversion introduces duplicate stack stores; explicit white color argument swaps text/label registers. Remains NonMatching; full coordinator build SHA-1 OK.

## c10_u19_20261106
Source: Codex worker c10_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u19: Object_DriveAnimAndSkin 800331E0 improved 98.521645 -> 99.02597, retained NonMatching. Private int HasDObj branch-return (if(flags&0x4020) return 0; return 1) consumed as condition emits target andi./cntlzw/srwi./beq; original bool helper == true emits extrwi 8-bit/cmp and adds 4B. Direct !mask condition collapses cntlzw/srwi (8B short); int !mask with ==1 still emitted extrwi/cmp. Vec3 declared before Quat recovers target SP+30 Vec3/SP+3C Quat and exact conversion tail. Separate save/restore inline helpers improve loop GPR allocation but not all. Exact 1848B primary text size; owned EH 88B and index12B bytes exact, extra weak timer destructor metadata accounts for whole-section 95.65/66.67. Remaining differences are GPR argument fields in preparation/request/animate loops; no native unlock.

## c10_u20_20261106
Source: Codex worker c10_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u20: Scene_8015AFCC genuine C++ ctor improved 99.55173 to 99.93104 by using one function-scope index through all preload loops and track selection. Exact 1740B size, extab 196B and extabindex 12B. Residual first preload loop 8015B320..8015B338 uses r28 instead of target r29 (five instructions). Lexical independent indices regressed to 99.45977; inline first-loop helper regressed to 99.83908. Retained NonMatching; no safe subset split in single-function TU.

## c10_u27_20261106
Source: Codex worker c10_u27_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u27: EnemyRun_BaseInit explicit RHS column cursor (const float *column=b.m; j++,column++) with indexed LHS and result preserves 1300-byte text and exact owned 176-byte EH/12-byte index, improving 98.08 to 98.23385. This removes world+0xE4 folding in inner loads, but result-base materialization remains inside inner loop and GPR/FP scheduling differs. Static inline float-pointer helper gave unchanged 98.08 text and shifted anonymous EH IDs; commutative product reversal was invariant. Retained NonMatching, full build SHA-1 OK, native gain zero.

## c10_u28_20261106
Source: Codex worker c10_u28_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u28: RankingFlowView::Update singleton 801D1890 retains NM at 97.993805% (1292 B), owned EH 95%, index100. Inline list-insert wrapper slightly improves stack layout vs97.990715 baseline. Player-loop helper regresses97.35604; hoisting node/entry declarations before self is byte-invariant. Remaining param/self r28 vsr30, loop/new pointer partition and iterator stack slots. Both EH DELETEPOINTER bytes encode r29 vs targetr28. All three hypotheses used; final fallback DOL SHA-1 OK.

## c10_u29_20261106
Source: Codex worker c10_u29_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c10_u29: RaceDigitUpdate 80246484 state 6 must break into common update tail, not return; jump table becomes exact. Scalar 0/1/1.2/220/599.999 literals remove extra sum constant fmr and FP constant-home differences. Remove stale per-TU @191 jump-table rename because @191 is now the 599.999 literal and postprocess_sdata2 must map it normally. Text 97.90966 -> 98.76636, .data/extab/extabindex 100%; retain NonMatching. Sentinel-based begin reload and shared function-scope loop index fail to recover remaining GPR homes. Full fallback-linked DOL SHA-1 exact.

## c11_a3_20261106
Source: Codex worker c11_a3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 4068 B.

c11_a3: SpriteSlot_SetTransform 800D6C20 exact native C requires by-value Vec3 inline setter calling a scalar XYZ inline setter; the latter owns the joint null guard. Direct vector-field call under the null guard changes copies/load scheduling (73.31373%). Nested scalar helper matches text204/EH8/index12 exactly. HUD_RegisterOverlay 80253B14 first lazy-create/early-exit/switch native C trial exact208/EH8/index12. Both source-linked, full coordinator DOL SHA-1 OK. MJObj float conversion remains parked due mr r3,r27 scheduling; CourseTables remains parked because subtable addi folds into load displacement; SceneList insert remains parked due catch/rethrow cleanup and GPR residuals.

## c11_a6_20261106
Source: Codex worker c11_a6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 716 B.

c11_a6: Jyugemu_Flag_Tick 80080748 (716 B) matches text/EH/index with an inline Flag::Tick member behind extern C wrapper, using pragma cplusplus on and automatic EH. Plain free C body reached 99.52514% but allocated self/desc/matrix as r30/r31/r29; inlined member naturally yields target r31/r29/r30. JObj dirty boolean must be initialized after the assertion/flags load, as in the canonical inline, to avoid an extra callee-saved boolean. No symbol rename or configure change required. Full source-linked DOL SHA-1 OK.

## c11_a35_20261106
Source: Codex worker c11_a35_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 780 B.

c11_a35: 80125948 draw (444 B) and 80126728 teardown (336 B) convert within original Matching TU using canonical DemoKartScene.h, existing extab_order key and automatic EH. For teardown, directly typed self parameter matches r30 self/r31 free flag; a local self initialized from void* instead gives opposite homes. Native 80125B04 best 99.54311% has exact size/EH but residual FP coordinate ordering/homes and anchor register; inline member-wrapper hypothesis regresses to 95.2278%. No new bridges or metadata edits.

## c11_a37_20261106
Source: Codex worker c11_a37_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 648 B.

c11_a37: BiribiriLand_Destroy 80134D68 (648 B) matches in existing .c via pragma cplusplus on, compiler EH and use_lmw_stmw. Canonical HSD ref_DEC should keep its byte-sized retained boolean when ported into a C++ island: builtin C++ bool introduced extra normalization; unsigned char local with int return reproduces target extrwi sequence. Inline obstacle teardown naturally restores loop/light register homes. Whole TU text/extab/extabindex 100%; source-linked DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c12_u2_20261106
Source: Codex worker c12_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1844 B.

c12_u2: fn_801EE36C transit vector construction before scale calculation fixes initial-X f2 -> f4 and improves native draft 99.81315 -> 99.83045. Extracted sqrt inline helper and named previous-X local leave same 12-instruction residual. Scratch SP+0x0C/+0x10 swapped; transit previous-X f9 vs target f2, coefficient f2 vs f3, scale f10 vs f9. Single-function TU remains NonMatching.

## c12_u6_20261106
Source: Codex worker c12_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 17 fn / 6824 B.

c12_u6: PanelCda40 dtor_801CDC68 sentinel r7/r0 residual resolves by begin(){return CdaIter(head.next);} rather than ++end(). Explicit iterator copy ctor alone is invariant; remove it. Direct first-node access removes sentinel CSE/live dependency and yields r0 addi/store, all seven functions / 900B exact. Refresh per-TU anonymous EH bridges (@36/37, @50/51, @70/71, @98/99, @120/121, @147/148); existing extab order suffices. Opt-in private-header branch preserves GpPleaseInit consumer. Full source-linked DOL SHA-1 OK; actual seven ELF addresses/sizes verified.

## c12_u11_20261106
Source: Codex worker c12_u11_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 516 B.

c12_u11: fn_801B739C length decrement clamp uses literal 0.0f instead of captured external lbl_806D986C. External compare/assignment without capture is byte-invariant at 99.496124%; numeric literal gives exact target FP temporary allocation and 100% text516/EH8/index12. postprocess_sdata2 maps literal to existing lbl_806D986C. Matching promotion source-linked; actual ELF 801B739C/516 and full DOL SHA-1 verified.

## c12_u19_20261106
Source: Codex worker c12_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 592 B.

c12_u19: fn_801D4FF4 diagnostic DebugPrintf needs direct nested calls for used bytes, used bits, and 0x228 - used bits. Explicit used/version locals yield swapped r25/r26 plus extra mr through r0 (99.189186%). Nested arguments naturally reproduce exact 592-byte text and 24-byte EH/12-byte index. Existing new-expression bridge is sufficient; Matching promotion passes source-linked DOL SHA-1.

## c12_u21_20261106
Source: Codex worker c12_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c12_u21: RankingMgr_UpdatePositions 801EB99C improves 99.12791 to 99.30232 via one-slot static inline UpdateKart(self,i), with original indexed outer loop and nested Notify. coll becomes exact r29; residual index=r26 vs targetr27, cursor=r28 vsr26, ctrl=r27 vsr28. Whole-loop helper invariant; explicit cursor adds mr and regresses98.139534/348B. Exact344B/EH8/index12 retained, NonMatching. Full fallback-linked DOL SHA-1 OK; no native gain.

## c12_u23_20261106
Source: Codex worker c12_u23_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c12_u23: fn_80242E80 inline RivalItems captures directly into case-3 loop improves 99.08 to 99.40 with exact 500 B and extab8/index12. Direct global argument expressions regress to 92.08/480B because loads are delayed past GetEnemyParam. Hoisting capture declarations outside loop gives 99.16. Residual retained: item index r30 vs target r31 / round r31 vs target r30; tail marker index r28 vs target r29 / cursor r30 vs target r28. Singleton stays NonMatching; final fallback-linked DOL SHA-1 OK.

## c12_u25_20261106
Source: Codex worker c12_u25_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 292 B.

c12_u25: CardModeRoot ctor 8020D00C remains 99.06542%, extra li r3,1 in state=3 branch. Hoisted shared int value 98.97196%, byte value97.850464%, ternary93.97196% all rejected. Safe dtk split at8020D00C isolates exact292B destructor. Private canonical declaration copy with Destroy override before CardModeRoot dtor and inherited Destroy redeclared before inline MenuModeBase dtor suppresses all duplicate vtable/RTTI/weak text; bridge @38/@39 to owned EH. All destructor sections100%, source-linked DOL SHA-1 OK. Thunk8020D1B8 is deliberately auto fallback after constructor range ends8020D1B8.

## c12_u32_20261106
Source: Codex worker c12_u32_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RaceDigitLap 80246988: numeric clamp literals plus independent local value remove frsp; local declaration order value/where/result produces SP+10/+0C/+08 and exact 496B size, owned 164B EH/index12. Text improves 98.59677 to 99.82258. Remaining x/y load scheduling is reversed; by-value coordinate helper adds copies, nested scalar helper and reversed plain-local declarations are invariant. Retain NonMatching.

## c12_u34_20261106
Source: Codex worker c12_u34_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c12_u34: fn_801F7198 improved 98.58878 to 98.92523 by retaining a TU-local copy of SelectSpriteTexture801F with height captured before width. This fixes f8/f9 and conversion scratch SP+08/SP+10 ordering without shared-header edits. Bounds-check cast-to-unsigned-char ==1 still emits srwi/cmplwi/bne rather than target srwi./beq, leaving source432 vs target428B. Direct predicate, branch-return int helper, and removing cast all collapse to cmplw and 412B (92.65-93.27%). Three hypotheses exhausted; singleton remains NonMatching. Full fallback-linked DOL SHA-1 OK.

## c12_u36_20261106
Source: Codex worker c12_u36_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 544 B.

c12_u36: SpritePairOwner::Tick/Reset 8023CDA8/8023CEB4 improve 98.731346/98.478264 to 100% using numeric float literals 1.0f/0.0f/0.0165f/255.0f instead of captured external const floats. Clamp FPR homes become exact; Reset naturally inlines Tick. Existing EH bridges suffice, no split or metadata changes. Whole TU text544/extab16/extabindex24 exact, Matching promotion source-linked, actual main.elf addresses/sizes and full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified.

## c12_u35_20261106
Source: Codex worker c12_u35_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 400 B.

c12_u35: FlashFx Update 8021A1C4 resolves FP clamp allocation (98.583336 -> 100%) by replacing external float const references with ordinary 0.0f, 1.0f, 0.0165f literals. Existing postprocess_sdata2 maps to lbl_806DAF60/64/70; Update + delete TU now text400/extab68/index24 all exact, existing bridges suffice. Keeping Update before delete avoids previously documented delete-only leading EH patch issue. Full Matching source-linked DOL SHA-1 exact; ELF addresses 8021A1C4/240 and 8021A2B4/160 verified.

## c13_u1_20261106
Source: Codex worker c13_u1_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 428 B.

c13_u1: CardModeRoot ctor 8020D00C extra li r3,1 resolves by static inline SelectCardMode(CardConfig*) returning a local int initialized to1 and conditionally set2. Inline helper gives 100% text428; previous same-body local was432B/99.06542. Reusing existing CardModeRootUnlock_private.h suppresses duplicate RTTI/vtable data. Bridge @57/@58 to @etb_800197B4/@eti_80029D14 yields exact owned EH. Weak MenuModeBase dtor/EH discards at link. Matching source-linked ELF8020D00C/428 and full DOL SHA-1 exact.

## c13_u3_20261106
Source: Codex worker c13_u3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u3: fn_801CDF10 improves 97.9235 to 98.68852. Inline EnterRace(VSMode_SeedRandomItemSequence(...)) removes extra r0 seed copy; nested InitPlayerSlot(seed, g_characterId) restores seed r30 / character r29 target homes. Size 736 -> exact 732 B, EH8/index12 exact. Residual input bool r29 vs r30 and player-character tail value/base/flag scratch registers remain. Hoisted function-scope declarations + direct global byte assignment regress97.86885/736B. Typed player view/accessor/member setter does not resolve tail. Singleton stays NonMatching; fallback-linked DOL SHA-1 OK.

## c13_u10_20261106
Source: Codex worker c13_u10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 348 B.

c13_u10: TextRow layout fn_8021713C reaches 100% with inline Advance(TextSprite*,float): named delta = gap - width; return delta + spacing. This restores target width f1/spacing f0 and fadds operand order. Safe split at 8021713C isolates leaf alpha fn_802170F0 (97.63158%, sprite/alpha/color GPR homes r5/r4/r7 vs target r7/r6/r5). Single SetAlpha and nested SetColor helper probes invariant; original alpha source retained. Original two-function object emitted reversed strong function order; standalone Matching layout owns EH8001A53C/index8002A0B0. Full source-linked SHA-1 and ELF8021713C/348 verified.

## c13_u13_20261106
Source: Codex worker c13_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u13: SwitchList ctor 8017A68C inline AppendSwitchPair(list,ResolveJointByName(second),ResolveJointByName(first),messages) removes two r3->r0->r26 copies under production MWCC right-to-left argument evaluation. Text 97.56917 ->98.39921, size1020->1012 and EH40/index12 exact. Remaining bge vs blt switch direction and two lwz-before-stw scheduling pairs. Separate declarations/case placement invariant; empty case2 adds compare; single six-float bounds aggregate introduces subobject-address saved web and regresses94.87352. Retained NonMatching, no safe subset in singleton.

## c13_u16_20261106
Source: Codex worker c13_u16_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u16: CharaSelect_SetupCharacterDisplay 801C3470 improves fresh97.18343 to97.89349. Capture external FLOAT_FULL_ALPHA then FLOAT_SPRITE_INIT_TIME before alternate-normal call for exact FP order; cursor-before-stat and k-before-stat3 fix most loop homes (do not hoist i). Numeric literals fixed FP but remain anonymous when source text is4B short; final captures avoid extra sdata2. Inline scale/texture accessors are invariant. Residual scale-base addi folded away, third stat pointer r25 vsr26, texture-table base folded into lwz displacement. Single-function TU remains NM; full fallback DOL SHA-1 OK.

## c13_u18_20261106
Source: Codex worker c13_u18_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u18: SceneListOperations insertion801F4DF0 matches136B with canonical ListIter n/end locals, accesses through.node and position.node=n.node; raw ListNode* cursor/sentinel were r7/r6 instead of targetr6/r7. Shutdown801F4D3C98.93939 and lookup801F4DC097.083336 retain swapped cursor/sentinel registers after declaration swap, aggregate iterators and begin-before-end construction. No-gain edits reverted there. EH24B/index36B exact. Reversed extab order(delete800173C0, shutdown800173C8, insert800173D0) crosses whole801F4D3C..801F4EB0 range; no safe exact subset split. TU remains NM; full fallback DOL SHA-1 OK; zero native gain.

## c13_u29_20261106
Source: Codex worker c13_u29_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u29: fn_801D680C improves 96.61273 to 97.554375 by moving the final 1..8 rank loop into AllCupsComplete inline helper as in fn_801D6DF0. Still saves r26-r31 instead of r27-r31 because cc*8 survives calls in r31; draft 1504 B vs 1508 B target. Snapshot/rank-update helper regresses to 96.08223; nested canonical CupRank helper regresses to 94.034485. Remains honest NonMatching; one-function TU offers no split rescue.

## c13_u32_20261106
Source: Codex worker c13_u32_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u32: CourseEnvironment UpdateAndCullZones fresh96.197845 ->99.06475: independent object-loop index restores saved r30 offset; direct reset loop with independent reset scope restores all reset-loop homes; semantic final-edge inline helper restores FP f6/f7 homes. Remaining zone index/object walker r5/r6 swap and missing mfcr/extrwi boolean (1104 vs1112B). CourseScene_Load remains98.7021, zone r26/r28 swap, debug byte-count homes and two bool normalization triplets (3212vs3236B). Boolean return spelling/declaration probes reverted. Full reversed EH span blocks rescue split; TU staysNonMatching, native gain0. Own anonymous EH rename keys after update shifted -3 and refreshed; owned extab all100/index99.28571 unchanged. Coordinator full build SHA-1OK.

## c13_u33_20261106
Source: Codex worker c13_u33_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u33: fn_801B4548 singleton fresh96.02687 ->96.06223 using TU-local typed map/clip inline scopes. C++ table member helpers emit identical output; const int& id/character helper worsens92.785. Remaining saved r23 vsr24, stride/entry/index GPR homes, folded subobject-base addi, timestamp/return scheduling. Text5616 vs target5656, EH87.5/index83.333/.data0. No safe subset; retained NonMatching, fallback-linked DOL SHA-1 OK; native gain0.

## c13_u34_20261106
Source: Codex worker c13_u34_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u34: BootDispatcher 8002DD58 improves 96.16123 to 98.645546. Inline SetBootColor(BootColor color) restores four 4-byte stack copies, moving RAII locals and conversion scratch to target offsets. Captured BootConfig* plus int disabled before ternary restores configuration-base lifetime and most GPR homes. Done()!=1 recovers mfcr but keeps an extra cmplwi; int Done plus !predicate regresses to98.281685. Nested 20-byte BootState channel assignment is output-invariant. Best source6412 vs target6376 B, saves r20 vs r21 and retains subobject-base, global reload, BootNotice and conversion-cookie relocation residuals. Singleton stays NonMatching. Full fallback-linked DOL SHA-1 OK; no native gain.

## c13_u37_20261106
Source: Codex worker c13_u37_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u37: debug viewer fn_8015B790 95.6958 ->96.12937 via block-local ModelEntry* models before selected-model call and early return if either viewer pointer is null. This restores explicit model base +0x10c and indexed resource load; early guard restores bne/b pair. Array-argument inline helpers still fold bases; function-scope array pointers add r29/r30 saves. Remaining step base +0x304 and icon base +0x10c folded addressing, icon FP/load scheduling; 1140 vs1144B. Singleton NonMatching; no safe subset. Full fallback-linked DOL SHA-1 OK.

## c13_u38_20261106
Source: Codex worker c13_u38_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u38: fn_80244524 rendering uses separate block-local size variables for two sequential ResCtrl render passes. Reusing one size variable creates four saved FPRs and812B; scopes reproduce three saved FPRs and796B. Explicit switch case2/default goto draw reproduces target direct exits. Text95.698494->98.190956. Residual three li(-256)/or pairs compile as oris/ori; pre-call initialized color shifts GPRs, const-reference mask emits constant-pool loads. Singleton stays NM; final fallback-linked DOL SHA-1 OK.

## c13_u43_20261106
Source: Codex worker c13_u43_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u43: fn_801F7344 fresh95.44886 ->99.03409 using a TU-local zero-texture helper: height-before-width fixes FP f8/f9 and conversion scratch slots; count then local index=0 fixes r29/r30. Bounds remains cmplwi/bne vs target cntlzw/extrwi./beq (source700 vs target704B). Inline unsigned-char empty-bank predicate invariant. Local conversion cookie @84 remains vs target lbl_806DA720. Three hypotheses exhausted; singleton stays NonMatching. Full fallback-linked DOL SHA-1 OK; native gain0.

## c14_u11_20261106
Source: Codex worker c14_u11_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

EnemyFace_nm3 ctor 8022BBC8: target clEFace3D +8 is destructible Vec3c; face selection and model allocation belong within inline clEFace3D ctor EH lifetime, not caller post-new initialization. FaceIcon sizeof=0x28, FaceRing sizeof=0x24. TU-private view raises text 94.35 to 98.72 and matches owned EH exactly after FaceHolder->dtor_8020EB04/base->dtor_8021617C bridges. Residual is local initialization register/scheduling; stop after unchanged member-initializer/default-vector probes. TU remains NonMatching.

## c14_u12_20261106
Source: Codex worker c14_u12_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Scene_80170B5C GrowSet ctor: TU-local inline GetJointPObj(j) wrapping GetPObj(HSD_JObjGetDObj(j)) fixes first face extraction sequence from mr. r4,r3 / early mr r3,r24 to target cmplwi r3,0 / lwz r4,0xC(r3) / late mr r3,r24. Current objdiff rises 94.08 to 95.257774 with EH 100%. Explicit componentwise Vec3 snapshot scalarizes across new into preserved f29-f31; returning vector by value produces target float snapshot plus unwanted extra aggregate copy. Retain original vector spelling until canonical vector lifetime/type is recovered.

## c14_u16_20261106
Source: Codex worker c14_u16_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u16: AI_CalcRivalAvoidance 801EE7F0 singleton text94.092354 ->94.808914 with candidate default distance1200000000.0f and position20000.0f in owned header; own EH IDs shift @158/@159 to@159/@160. Broad literal conversion raw97.468155 but1252B, helper/fieldwise94.89809, scalar candidate with late vector view96.92038 all retain early position base hoist and were rejected. Remaining early r30 position base at+80 (target+28C) shifts self/helper GPR homes; normalize and amount FP webs differ, waypoint lacks fmr. Owned extab97.22222/index100 unchanged. NM fallback full SHA1OK; zero native gain.

## c14_u21_20261106
Source: Codex worker c14_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u21 AI_UpdatePerFrameState: inline pointer Vec subtract + separate squared-length helper and AIFramePosition proximity temporary restore target non-fused arithmetic/intermediate stores. Moving pair scan into a static inline helper restores first-loop FP homes, vector slots 8/14/20/2c and primary 24-byte EH payload. Text improves reproducibly 93.765205 to 96.175674, remains NonMatching due pair/proximity scan GPR cycles, nearest-distance FP home, rank-search base loads/result coalescing and lap homes. Singleton TU gives no mechanism B cut. Full fallback DOL SHA-1 OK.

## c14_u23_20261106
Source: Codex worker c14_u23_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u23: singleton NetJoin ctor 80225C2C baseline measured 93.824745%. Capturing lbl_806D1A78+1 before all body field stores yields 94.46907% (same 776B). Member initializer list and unsigned global access unchanged baseline. Residual initial vptr/global-load scheduling and r5/r6 zero homes, plus ResCtrl f1/f2 swap at +16C..+19C. Owned extab232/index12 raw prefixes remain exact; weak copies grow to248/36. TU stays NonMatching after three hypotheses.

## c14_u25_20261106
Source: Codex worker c14_u25_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u25: clFlowTaPlease_Init fresh baseline 93.340836% /1248B; replacing flattened table casts with existing C8TaTables multidimensional indexes yields 93.58521% /1244B and extabindex 100%, extab 97.64151%. Direct global inline typed accessors lose cached base (92.2926%). Byte-stride inline lookup reaches 94.14791% but regresses owned EH/index; rejected. Prologue table-base hoisting remains unresolved; no native gain.

## c14_u28_20261106
Source: Codex worker c14_u28_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u28 WarpDashMgr_Init: fresh baseline 92.791046 (assignment report 93.57). Casting each pool table to const WarpZoneSource *const (*)[2] and indexing [course][alternate != 0] prevents combined-offset CSE, restores separate r29/r30 stride webs, self r26, r21-r31 saves, frame 0xE0, and improves text to93.731346/owned EH97.22222. Own EH IDs shift @90/@91 -> @91/@92. Remaining folded base/stride association, first-loop GPR homes, second-loop cursor coalescing leave532 vs536B. Flat inline lookup88.76119 and shared population helper90.89552 regressed; reverted. Singleton stays NonMatching; coordinator full build SHA1OK, zero native gain.

## c14_u35_20261106
Source: Codex worker c14_u35_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u35: TaMode_Init fresh92.60642 ->93.5946 (2376 vs2368B). Inline RegisterGhost(matrix,CarObject_GetRenderObj(...)) removes extra r3->r0->r8 copy; inline CreatePlayerPath is invariant. Keeping one-based cup index in params pointer then reading params[-6] yields target -0x48/-0x44/-0x40 field offsets and removes early cup subtraction. Bonus captured before time gives target FP homes but reversed load order. Typed multidimensional ghost indexing regresses92.16216 and folds table base incorrectly. Residual prologue derived-vptr BATTLE+658 CSE, first2 log rematerializations, allocation/argument GPR webs, ghost table association and scheduling. Refresh TU-only anonymous keys to @92/@93/@91. Text93.5946/extab94.897964/index95/data50. Singleton staysNM; fallback DOL SHA1OK.

## c14_u44_20261106
Source: Codex worker c14_u44_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1060 B.

clGetCoinSum::Layout (802249FC) matches all 1060 text bytes and both EH sections with existing COIN_RESCTRL_IMPLICIT_PADDING opt-in. Explicit pad arrays generated __copy and padding stores; implicit padding and separate tail members restore native memberwise assignment and CTR loop, resolving apparent register residuals. Full source-linked DOL SHA-1 OK.

## c14_u45_20261106
Source: Codex worker c14_u45_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 820 B.

EName3D ctor target EH identifies destructible Vec3c at +8. Empty inline ctor/dtor plus canonical dtor_80036E40 bridge restores member cleanup. GC/2.6 -rostr and -inline deferred, with reversed source definitions, restores pooling across name tables/vtable, saved registers and all 452B ctor instructions. Shared short SJIS strings must reference existing lbl_806DB680..B6B0 rather than emit duplicates. Default objdiff pool inference shows 99.91151% for second 13-entry table although actual relocations compare 100% with ppc_calculate_pool_relocations=false. Entire source-linked DOL SHA-1 exact, four original function addresses/sizes verified.

## c14_u56_20261106
Source: Codex worker c14_u56_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u56: ranking_display 801D1EAC fresh90.60096 (2500B vs2496 target). Nontrivial iterator-return helper boundaries and separate UI-construction scopes each emit identical output; both reverted. Genuine nullable title-source getter replaces pre-existing no-op null assignment, byte-invariant. Residual shared name-table/vptr base pooling, iterator stack slots, allocation GPR webs and final panel flag/conversion scheduling. Singleton stays NonMatching; full fallback DOL SHA1 OK, zero native gain.

## c14_u57_20261106
Source: Codex worker c14_u57_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u57 fn_8018B31C: fresh native baseline90.33684; name loop i<5 && i<5 restores target guard/branch pair and improves to90.64771 (6456B vs target6472B). Generic pointer-taking bit/text/clear inline helpers emit identical output; mask-first explicit assignment regresses90.63226. Remaining long-lived GPR webs, inline bit-writer scratch allocation and checksum mask/load scheduling; BSS84 vs target88 pre-existing. One function only, no mechanism-B split. Honest NonMatching; final coordinator build SHA-1 OK, zero native gain.

## c14_u58_20261106
Source: Codex worker c14_u58_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1008 B.

Terrain_RaycastWall80035AE4: existing declaration omitted three FindTriangle float args, hiding semantic bug as FP regalloc. Initial query belongs in inline stepper ctor (target PC180 cleans timer only); endpoint query needs captured x/y/z. Correct prototype/lifetime plus __restrict from/to permits target y-first aggregate copies and stepper scheduling, reaching100% text1008 and owned EH72/index12. Own @68/@69 bridge restores EH names; full native-linked DOL SHA1 exact.

## c15_a10_20261106
Source: Codex worker c15_a10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 168 B.

c15_a10_20261106: ItemObjectManager_Init (800D81E0,168B) now reaches native100. Real new clNormal3D plus a static inline ResetSlots(unsigned char *slot) helper containing int i=0; do { memset(slot,0,0x1EC); ++i; slot+=0x1EC; } while(i<256); restores target counter r31/walker r30 with no entry copy. Flattening this loop in the caller gives correct homes but extra addi-to-r0/mr; indexed array loop gives exact size but swapped homes. Inline parameter boundary resolves the previously parked loop register residual. Owned text168/extab24/extabindex12 all100; coordinator source-linked DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Existing ObjViewA70C_private.h supplies matching clNormal3D(void*,int),sizeof0x5C; no shared edits. Add-only TU bridges @20->@etb_8000B334,@21->@eti_800239FC,__ct__10clNormal3DFPvi->clNormal3D_Construct,__nw__FUl->Alloc,__dl__FPv->MemoryManager_TimedFree.

## c15_a42_20261106
Source: Codex worker c15_a42_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 924 B.

c15_a42: Jyugemu_ReverseFlag_Tick 80080C10 (924B) native100. Mirror Jyugemu_Flag_Tick JObj setter/dirty helpers with ReverseFlag assertion labels. Native free function already has correct GPR homes. Use explicit float phase temporary before storing/clamping to avoid two phase reloads; declare camera target before eye for target stack slots. Direct compound vertical-height expressions produce fadds f31,f30,f0 independent of operand spelling; natural static inline FlagHeight(float y,float bob){return y+bob;} restores fadds f31,f0,f30. Inline member experiment exceeds auto-inline threshold, leaving a wrapper, so retain free function. Automatic pragma exceptions on gives exact extab8/index12. All text/EH 100; coordinator full source-linked DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No configure/symbol/split/rename changes. Original d254aff introduced this as extracted asm; subsequent history fixed symbol relocations and callee names, with no documented native-C blocker found.

## c15_u8_20261106
Source: Codex worker c15_u8_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 292 B.

PcbDebugOverlay: DrawLinkErrorOverlay has exact C text but target DESTROYLOCAL TexMgr unwind metadata. External FKTex default ctor mapped to TexMgr_Init plus empty inline destructor mapped to dtor_800869D0 yields target PC54..10C, local8, exact24B EH. Inline ctor wrapping setup+position shifts EH start to58; explicit TexMgr_Init after trivial local starts34. Isolating Draw in its own TU and referring to shared pool via one external base preserves text100%; weak dtor discards at full link. Dump listener r27 vs r25 unchanged by targeted declaration order or inline listener helper.

## c15_u15_20261106
Source: Codex worker c15_u15_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2184 B.

c15_u15: CardDataTransfer_UI 8006D308/2184B matches fully by extracting natural inline Begin(TestPage*, int initialStatus) around initialization and six card-status checks, using the parameter for STEP and STATUS then returning error status. Flat local constant duplicates li 1. TU-local DrawItems(TestPage*,int) mirrors TestPage_DrawItems but declares MenuItem* it=CardDataTransfer_UI_data_803FCC00 locally instead of passing the table as an inline parameter; target walker r30/index r27/selection r29 restored. Combined native text/EH100 and source-linked full DOL SHA1 exact; no EH bridges or split changes.

## c15_u24_20261106
Source: Codex worker c15_u24_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 572 B.

CardUnpackLegacy 8009060C: explicit version=552-get_used_bits(pack); used=get_used_bits(pack); DebugPrintf(...get_used_bytes(pack),used,version) caused r26/r27 reversal and extra r3->r0->r26 move. Direct DebugPrintf(format,get_used_bytes(pack),get_used_bits(pack),552-get_used_bits(pack)) restores right-to-left argument expression temporaries, all 572 text bytes and owned EH40/index12 exact. Existing real new expressions/EH bridge unchanged; full source-linked DOL SHA-1 exact.

## c15_u38_20261106
Source: Codex worker c15_u38_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

EffectFA ctor fn_8016FA50 unlock: move the complete three-model creation loop into static inline InitModels() with local global-array references. Keep six-part loop in ctor, but declare int i before MapEffectDef *defs and initialize i in for. This fixes both r26/r27/r28 cycles and preserves all scheduling, 452B text and 40B/12B EH exact. Putting parts loop in helper also fixes registers but shares zero stores and hoists defs, yielding448B; widening that helper is invariant. Existing bridges/flags suffice; full native-linked DOL SHA1 exact.

## c15_u64_20261106
Source: Codex worker c15_u64_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u64: ItemEffectImpact_TryArmInit target cross product is normalized projected velocity v cross projected up, not up cross v. Correcting three expressions raises fresh text93.69586 to93.771286, source1636 vs target1644B, owned extab98.4375/index95 unchanged. Natural vector pointer helper probe91.7056 and scalar axis-angle/quat-matrix helper probe93.73966 regress and were reverted. Remaining projection reload and FP scheduling/homes; singleton stays NonMatching. Full fallback-linked DOL SHA1 exact; zero native gain.

## c15_u66_20261106
Source: Codex worker c15_u66_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u66 CardSetupFlowInitial fn_8024AD8C singleton: explicit int duration=lbl_806D1AB0 before state=2 in first service and receipt paths improves fresh93.29949 to95.878174, preserving788B and EH. Target li2/lwz/stw/li0 vs source lwz/li2/li0/stw remains in both blocks; inline BeginFade state helper and explicit short frames snapshot emit identical output. Primary EH raw176/index12 bytes exact, extra four weak dtor EH entries; anonymous @96/@97 bridges still absent. Remains NonMatching; fallback full DOL SHA1OK; zero native gain.

## c16_u3_20261106
Source: Codex worker c16_u3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u3 fn_801D8E28: direct native baseline89.443924 ->90.09813 by computing y before x in TU-local offset helper for first two text placements of each mode branch. Same856B and owned EH100; icon FP homes unchanged. Scalar staging returns baseline, canonical vector operator+ regresses39.182243, local position constructor/setter89.2757. Residual streaming aggregate copies via r0 and volatile FP coloring; singleton remains NonMatching. Full fallback-linked DOL SHA1OK, zero native gain.

## c16_u9_20261106
Source: Codex worker c16_u9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u9 Menu801F0CC0: no missing functions. Declaring offset before index makes 0E3C/115C/15D4/190C/1BC8/1FE4 text100 (1040 B). Unsigned getter result + four-unsigned RGBA packer removes redundant clrlwi; 1EE0/2400 improve to99.53846/99.48276 with shared explicit offset loops, residual color/offset r29/r30 exchange. Pure WithAlpha slightly improves four crossfade methods; reference setter invariant and bitfield union spills. Input handlers retain target two-stage base+element adds versus folded source addi; pointer-return and call-containing helpers are invariant. Existing full-TU reversed EH grouping still blocks subset rescue. TU remains NonMatching; fallback full DOL SHA1 exact, zero native gain.

## c16_u12_20261106
Source: Codex worker c16_u12_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u12 ExplosionTumble_Init 800532D4 singleton: baseline89.013824/1704B. Separate rounded Dot products plus pointer Scale/Subtract helpers restore target1736B and improve89.82258; scalar AxisAngle/QuaternionMatrix helpers restore axis z/y/x evaluation order and improve89.89171. Add @262/@263 bridges to owned etb800071AC/eti800205AC: owned EH48/index12 exact100, extra weak dtor entries remain. Residual initial vector squared-load x/y order, Dot/Scale redundant up reloads and FP root/quaternion matrix webs/scheduling. No B cut; remains NonMatching. Full fallback-linked DOL SHA1 exact; zero native gain.

## c16_u14_20261106
Source: Codex worker c16_u14_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

SpecialFace_Init 8007B944 (452B): old GC/1.3.2 compiled aggregate assignment as two-word load/store pairs, leaving 88.89381% while all constructor and bounds-loop code was exact. Existing native constructor under GC/2.6 pipelines the 52-byte copy exactly and reaches 100%; bridge @89/@90 to @etb_80008688/@eti_800214DC. Matching promotion source-links at original address/size, all owned text/EH/index100%, full DOL SHA-1 exact. No C++ source or shared header edits needed.

## c16_u16_20261106
Source: Codex worker c16_u16_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u16 ItemWnd::Setup 8021F508: fresh baseline88.15076 vs report88.83. A TU-private typed view of shared pool lbl_803C6610 with poses at+428 and explicit entry-scope pool pointer restores cached r30 prologue/base and allocation GPR homes, improves92.41708 (784 vs796B). Merely replacing external labels with casts to common root gives88.25126. Multidimensional float[6] accessor is invariant to typed struct access. Residual target base+428 then index association/rematerialization vs folded source field offsets; itemId comparison r0/r3. Owned EH still not exact; singleton stays NonMatching. Full fallback DOL SHA1 exact; zero native gain.

## c16_u20_20261106
Source: Codex worker c16_u20_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u20 fn_80225124 singleton destructor: canonical DeleteSprite(spr) fixes target conditional null assignment and improves fresh88.304344 to89.5 (176 vs184 B). Target zero r31 live across Sprite_Destroy remains absent; replacement-parameter helper invariant, pointer-return helper88.41304. Existing compiler emits unowned24B clCSSceneBanner vtable, another blocker for promotion. EH87.5/index91.66667 unchanged. Remains NonMatching after3 hypotheses; full fallback DOL SHA1 exact; zero native gain.

## c16_u21_20261106
Source: Codex worker c16_u21_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u21 PhysicsState_KartCollisionCheck 801ECB88 singleton: scalar previous-position set versus trivial aggregate copy restores lfs/stfs; fieldwise matrix-position stores and early hit=1 improve 88.084305 to91.46221. Per-car inline output-reference helper regresses89.88663 with changed stack slots/additional hit test, rejected. RelativeHitYaw(float angle,float heading) containing separate inline radians/degrees wrappers evaluates heading before atan2 and incidentally restores all target callee-saved GPR homes, reaching92.14535. Primary1356B versus target1376B; residual movement FP webs/store scheduling, 64-bit immune branch island, repeated yaw constant loads, EH PC intervals. Remains NonMatching, no B cut/native gain; full fallback-linked DOL SHA1OK.

## c16_u24_20261106
Source: Codex worker c16_u24_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u24 CourseData_LoadPathTable singleton 800ABAE8: fresh baseline86.89759 (report87.8), native656B vs target664. Separate LoadMemoryTable and LoadFileTable static inline path helpers yield89.09638; memory source/size and first counting-loop homes now match. Typed full-pool arrays87.75301/648B rejected; common InitializePaths helper is invariant89.09638. Remaining table-base CSE/hoist/asymmetric branch layout, prologue scheduling, memory fixup r22/r23 and file-population GPR homes. Add-only own @90/@91 aliases maintain extab93.75/index95. Singleton remainsNonMatching; full fallback DOL SHA1OK, zero native gain.

## c16_u27_20261106
Source: Codex worker c16_u27_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 204 B.

SpecialFaceMesh_Ctor 8007B878/204B: GC/2.6 alone invariant87.54902; src __restrict under2.6 permits target source count load before member zero stores, reaching98.43137 (1.3.2 remains87.54902). Keep assignments data,i,count,offset in original order, declare locals count,data,offset,i to restore count r31,data r30,offset r29,index r28 and source parameter reuse r29. All204 text bytes exact. Natural inline loop helper regresses93.882355 and is unnecessary. Add TU anonymous @41/@42 bridges to etb80008648/eti800214D0. Owned text64B EH/12B index all100; source-linked main.elf constructor at8007B878 size204; full DOL SHA1 exact.

## c16_u28_20261106
Source: Codex worker c16_u28_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 332 B.

RoundResult 8024F43C: changing static inline ShouldShowResult(PlayerData &pd) called with global to no-argument helper with local PlayerData *pd=&g_playerData restores cached r30 prologue/address and all saved GPRs, 86.90164 ->100% (244B). Move 8024F530 after it and split before 8024F588; DTK accepts forward EH cut. Prefix text332/EH16/index24 exact with @42/@43/@55/@56 bridges; full source-linked SHA1 exact. Getter original placement new text144 exact but missing DELETEPOINTER; standard class new emits EH but extra r5->r31 move,148B/95.27778%. Corresponding global placement delete gives catch/rethrow; out-of-class inline ctor is invariant. Getter remains NM; gain2fn/332B.

## c16_u30_20261106
Source: Codex worker c16_u30_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 352 B.

fn_801F9DA4: passing a typed resource-pool pointer from getter entry scope into inline CourseObjSet constructor replaces separate hoisted extra/joint addresses and final pool rematerialization with target r31 base; fresh86.170456 ->99.375, source368 ->352B, owned EH exact. Declaring output cursor before entry cursor restores target r22/r23 and reaches100. Own @135/@136 bridges plus Matching promotion give full source-linked DOL SHA1 exact.

## c16_u32_20261106
Source: Codex worker c16_u32_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u32 fn_8018E6FC singleton: fresh86.22194 ->97.188774; verified scalar literals plus inline updateParticle and compound age comparisons restore target1568B/two-way final unroll/EH8/index12 exact. Separate initializeMatrix(o,index) and updateMatrices(o) improve volatile pointer/search webs. Remaining initialization stride/scene/joint r30/r29/r31 vs r29/r31/r30; point/free result r9/r7 vs r7/r9; tail offset/pointer r3/r4 vs r4/r3; delay/speed/maxAlpha FP homes. Three hypotheses exhausted, staysNonMatching, full fallback DOL SHA1OK, zero native gain.

## c16_u33_20261106
Source: Codex worker c16_u33_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 636 B.

c16_u33: RaceDigitPositions fn_80247DAC (636B) fresh84.949684 ->100% by replacing extern const float references with numeric literals 11/7/24/18/12/16.8. This restores target FP homes and arithmetic/store scheduling; existing postprocess_sdata2 maps literals back to all six shared pool labels. Genuine .ctors startup pointer restores owned registration at802E8960. Text636/EH8/index12/ctors4 all100; Matching source-linked final ELF80247DAC/636, full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c16_u42_20261106
Source: Codex worker c16_u42_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 524 B.

c16_u42: HudManagerModes fn_80253C40 (80253C40,52B) baseline84.61539 has only lwz list-pointer prologue scheduling residual. HudManager *__restrict self lets GC/2.6 load before LR store, reaching100%; all four functions/524B and extab80B/index48B exact. Existing bridges suffice; Matching promotion full DOL SHA1 exact, actual ELF addresses/sizes verified.

## c16_u49_20261106
Source: Codex worker c16_u49_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u49 ItemEffect_TornadoLift80053AE0: fresh82.47 ->86.44 by replacing aggregate TLVec cast-copy with explicit z/y/x loads then x/y/z stores. Restricted public args, restricted inline state initializer and restricted scalar float-copy helper all retain paired matrix loads/stores. Native432B vs target400B; target retains last8 floats across second matrix copy. EH8B100%, index12B91.66667 due size word. Three approaches exhausted; singleton remains NonMatching; full fallback DOL SHA1 exact, native gain0.

## c16_u46_20261106
Source: Codex worker c16_u46_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u46: canonical FlowFaderI out-of-line ctor at 80218B28 emits exact 52B including r6 base vtable. Existing bridge needs extab_padding routing, but dtk extab clean fails with No extab section found for this leaf ctor. No build logic changed per worker contract. Bridge-only postprocess support would unlock this TU without changing native constructor semantics; requires coordinator/owner decision. Reproduction evidence retained in build/c16_fader_a1.json and .s. Final allowed C ABI-view initializer is 98.46154%, register-only base-vtable residual, NonMatching.

## c16_u47_20261106
Source: Codex worker c16_u47_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Warp Reserve: placement new without its placement-delete counterpart loses CW's per-construction SP save/FP and turns pointer traversal into a CTR count loop. Adding standard inline placement delete restores those naturally. A string wrapper owning the SharedPtr-like member restores exception cleanup member r27 and base r28, reaching 536-byte native body shape and exact owned EH. Remaining 99.92538 is solely descriptor relocations; current raw @119 collides with an old @eti_80022658 bridge. Primary object order also differs, so do not flip Matching merely from percentages.

## c16_u52_20261106
Source: Codex worker c16_u52_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u52 CollisionUpdate8019B080: fresh81.33437 ->82.11667 with separate rounded LengthSquared helper (existing-family fp_contract off), then87.22083 with row-local a0/a1/a2/a3 and sequential matrix accumulator. Numeric constant/local-root probe87.1375 reverted. Primary3720B vs3840B. Matrix loop still strength-reduces out stores rather than target slwi/stfsx; extra f21 save/frame+16 and GPR home shift remain. EH88.15789/index61.11111 unchanged. Singleton staysNonMatching, no rescue cut; full fallback-linked SHA1 exact, zero native gain.

## c16_u50_20261106
Source: Codex worker c16_u50_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u50: GC/2.6 raises SpecialFace_RaycastSegment fresh81.41053 to85.98947 while preserving seven exact symbols and all EH/index scores. Move Raycast delta subtraction after endpoint copies ->92.242424. Declare InsertFill old before size ->96.28671, and Reserve end before p ->92.62745. FacingDot typed helper yields92.617546 under2.6 with target0xA0 frame, but changes deferred anonymous IDs: after moving definition last, raw @375=0, @376=1, @377=0.5, @378=3 collide with existing @377/@378 EH bridges; raw segment EH @381 also collides with old dtor bridge. Rejected under add-only mapping contract; header changes restored. Restrict self/ray regresses77.57895. Full reversed group staysNonMatching, physical Segment/dtor emission deferred; full fallback-linked DOL SHA1 exact; zero native gain.

## c16_u51_20261106
Source: Codex worker c16_u51_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1792 B.

c16_u51 WarpZoneVector_Insert 800A9D84/1792B: standard empty inline placement operator delete(void*,void*) paired with placement new restores six stw r1 cleanup markers, frame D0, frame pointer and ordinary loops; baseline missing counterpart produced frame40/CTR loops and81.372765%. TU-private string with contained storage ctor (external SharedPtr_Init) restores r25 cached member pointer and DESTROYMEMBER EH; inheritance yields identical text but wrong DESTROYBASE action. Cache count+n before capacity branch; source cursor before destination declaration and pointer increment before count decrement restore remaining scheduling/homes. Add @267->global:lbl_803284C0,@269->etb80009ED0,@270->eti80022640. -rostr plus owned rodata803284C0..803284F8 necessary: without it type-name copy adds64 data bytes; without global bridge other TUs have undefined string. All owned text1792/EH64/index12/rodata56 exact; extra weak dtors discarded. Matching full source-linked DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c16_u65_20261106
Source: Codex worker c16_u65_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 716 B.

c16_u65: anon_80209FA4_nm1 safely cuts at A6CC/A734/A788. Reverse prefix out-of-line definition order under GC/2.6 -inline deferred, and retain Tween::Set verbatim as inline helper in prefix so Update and ctor stay exact. Prefix A454/A584/A5C8 plus isolated Set A734 text/EH/index all 100%; linked primary addresses/sizes exact, DOL SHA-1 OK. Value float and integer return coalescing residuals unaffected by conditional-vs-if returns and addition operand reversal; keep both NM.

## c16_u76_20261106
Source: Codex worker c16_u76_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u76: clCSOrgKartModel ctor 8021ABFC was semantically incomplete: only 4 of 28 target tire hide calls present (missing kaku/oil tire/oil grid/punk grid/punk tire/snow groups, 24 calls). Restoring them and typed foreign lbl_803C4E60 pool (anim IDs at+0, strings +180..548) raises fresh72.58707 to95.21559, removes emitted duplicate strings/IDs. switch(character) restores target case3 branch-over-branch. Cached foreign pools retain r29/r30 swapped; direct-symbol aggregate references regress72.95357. Own base dtor bridge targets dtor_8013DCBC; @172/@173 identify primary EH. Singleton remainsNonMatching after3 hypotheses; full fallback DOL SHA1 exact.

## c16_u77_20261106
Source: Codex worker c16_u77_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 168 B.

c16_u77 RaceDigitListInsert 80247C3C: pair existing placement new with standard inline empty placement delete(void*,void*) to restore CW frame pointer, frame40 and construction SP marker (72.7619 ->98.690475). Extract splice/count/iterator result to static inline InsertNode(self,at,node), invoked with position.node and guard.Release(), to restore at=r5/node=r6 (100% text168). Reordering local declarations alone invariant. Own @41/@42 bridges to etb8001DA3C/eti8002B2F8 give all owned sections100; Matching source-linked ELF address/size exact, full DOL SHA1 exact.

## c16_u78_20261106
Source: Codex worker c16_u78_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u78 fn_801ED798: nested ApplyYaw/Multiply helpers with product local in Multiply, shared accumulator outside loops and flat output[index+col] recover target sequential fmadds/stfsx and temporary stack slots. Flat16 Copy helper and scalar translation setter improve fresh72.73358 to87.84991. Numeric constants give95.21576 but introduce28B sdata2 and unsafe offset-based postprocessor mapping (0.1f -> lbl_806DA42C); rejected, extern constants restored. Remaining matrix operands/GPR homes, identity diagonal store order, FP saves/frame, frame9 export and EH PC/name residuals. Singleton remains NonMatching; no rescue cut.

## c16_u82_20261106
Source: Codex worker c16_u82_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u82 RaceScene_Init 800A1D80: actual 99.97931% residual is clrlwi. destination r26 vs target r3 and following mr direction, not copy scheduling described in old source comment. PreloadItem helper inside caller guard is invariant; lookup+guard helper and guarded PreloadItem helper both regress to 99.93793% via i r26/item r28 instead of i r27/item r26. All reverted. Single function TU cannot isolate exact subset.

## c16_u106_20261106
Source: Codex worker c16_u106_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 528 B.

c16_u106: PcbDebugOverlay DebugOverlay_DumpPcbState 80085E3C/528B resolves prior listener r27-vs-r25 residual by static inline int PcbConn_GetPortCycle(const PcbConnView*) and PcbConn_GetCloseCount(const PcbConnView*) accessors used only for the two cached loads in the primary+secondary branch. Native text528/rodata1400/extab8/index12 all100. Pending ring-count helper regressed to98.333336 with loop register rotation and listener unchanged (reverted). Matching source object in main.elf; ELF symbol80085E3C size528; full DOL SHA1 exact.

## c16_u105_20261106
Source: Codex worker c16_u105_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 584 B.

c16_u105: YesNoCursor Update 80204F68/584B reaches 100% by keeping the cached visible local bool, matching its canonical member type; unsigned char produces the persistent list/visible r30/r31 swap. A separately named allocation result with the old unsigned-char local is invariant. TU-owned private declaration view with undefined Cursor _key2 before Update suppresses duplicate vtable/RTTI while reusing canonical FlowScene types and verbatim YesNoSpark ctor. Add @73/@74 owned EH/index bridges and FlowFaderF dtor -> TweenInterp_Dtor. Owned text/EH104/index12 all100; extra weak dtors discarded. Matching source-linked ELF 80204F68 size584 and EH80018DEC/index800298AC verified; full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c16_u111_20261106
Source: Codex worker c16_u111_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u111: AI_SystemInit 801EBC8C 700B improves 99.828575 to 99.88571 by moving round/cup captures and GetKartTuningEntry into static inline GetSlotTuning(i). Character home becomes exact r27. Four round/cup instructions still swap r26/r27. Direct globals in nested helper call regress95.38857 (save set changes); helper cup/round capture arguments are invariant at99.88571. Retained NonMatching, owned EH payload and section scores unchanged; full fallback DOL SHA-1 OK. Singleton prevents mechanism B.

## c16_u112_20261106
Source: Codex worker c16_u112_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u112 fn_801EE36C: native99.83045 ->99.9135, remains singleton NonMatching. MovementInverseLength(const CollisionVec&) returning1.0f/MovementLength(v), with speed multiplication retained in caller, fixes scratch slot14/0C/10/08 order. Extracting entire ScaleMovement(delta,speed) hoists speed load and regresses97.99308. Inline ScaleTransit(delta,0.0125f*(float)timer+1.0f), after delta subtraction, restores scale f9 (previous f10). Residual five instructions: previous-X f10 vs targetf2; coefficient f2 vs targetf3. Inline typed vector subtraction adds previous-X reload,1160B/98.14187; rejected. Exact owned24B EH/index12 preserved; extra weak destructor EH unchanged. No flags/splits/bridges modified; no full build requested, no native gain.

## c16_u127_20261106
Source: Codex worker c16_u127_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u127 TitleNameHud ctor: redundant final k/n counter pair is unnecessary; a fresh block-local single k emits identical primary instruction JSON and exact owned EH (99.745766 text). Reusing function i or static inline final-loop helper generates mr for byte-offset initialization but final count web becomes r24 rather than target r22; anonymous constant/EH IDs also shift. Function-scoped fresh k leaves original li residual. No flag flip or native gain.

## c17_u3_20261107
Source: Codex worker c17_u3_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u3: fn_8020A788 accumulator spelling (int value=rate*t; value >>=16; value +=from; return value) improves 92.05882 to93.82353 under unchanged GC/2.6 flags. All target instructions through srawi match; target final add r0,r3,r0 + mr r3,r0 remains versus source add r3,r3,r0. Static inline fixed-multiply helper is baseline-identical; separate origin accumulator reverts to baseline. Keep NM; one-function TU offers no rescue split.

## c17_u8_20261107
Source: Codex worker c17_u8_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 104 B.

c17_u8: MWRTTI __dynamic_cast NULL target and equal-type cases must share a short-circuit return (!totype || strcmp(...) == 0): separate early returns add one branch. bad_cast::what returning external existing lbl_803F1CBC avoids pooled-literal extra addi. Safe forward-EH split at 802715A4 promotes dtor+what 104B using an undefined first virtual key (inherited slots preserved) and @15/@16 EH bridges; all sections100, source-linked DOL SHA1 exact. Remaining dynamic-cast offset/strcmp r12/r31 swap is invariant under moving offset declaration before count and removing named offset for direct member references; do not repeat these probes.

## c17_u5_20261107
Source: Codex worker c17_u5_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u5: fn_8020A6CC 104B float Value draft improves 78.65385 -> 92.88461 with direct extern-C const Tween *__restrict parameter and int duration cache. Restrict moves elapsed load before stwu; int duration removes extra extsh. Inline restricted whole-body helper regresses74.23077; double return type is invariant78.65385. Remaining elapsed/duration GPR and float-return coalescing residuals leave source100B vs target104B. Keep singleton NonMatching. Add owned @61/@62 EH bridges; full fallback DOL SHA-1 exact, no native gain.

## c17_u7_20261107
Source: Codex worker c17_u7_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 240 B.

clItemBoxManager: the target Update_Inner has DESTROYLOCAL dtor_80036E40 for its vector at SP+0x14. A three-float C++ constructor plus empty destructor restores the exact FP load/store/arithmetic sequence; plain aggregate copy emits lwz/stw and loses cleanup. Named node/sentinel traversals bring text to 99.73684%, leaving only the final countdown loop r31/r30 reuse. Direct next/sentinel construction in a private three-level list destructor hierarchy gives exact 120-byte dtors at 8005F778 and 8005F7F0. Isolate those two with EH CCC..CDC / index C9C..CB4; tail base dtor 8005FF74 has early EH at 80007CDC, binding the remaining tail as a reversed-order group. No padding or manual EH was used.

## c17_u15_20261107
Source: Codex worker c17_u15_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u15: fn_80202E78 text176: preserve read-only line parameter and normalize separate selectedLine local to restore incoming-r4 compares and all prologue scheduling. Fresh objdiff59.295456 ->82.5, EH8/index12 remain100. Flat indexing53.886364; inline table lookups invariant baseline. Residual table-base+index association: target addi base then lwzx, source index-add then displacement lwz. Singleton remainsNonMatching, no native gain.

## c17_u10_20261107
Source: Codex worker c17_u10_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 872 B.

c17_u10: SpecialFace_BuildPlaneAndEdges 8007BB08/872B: plain Vec3f locals scalarize target stack vectors (fresh64.004585). Canonical SpecialFaceVec locals restore frame30 and vector stores/reloads (95.30275). Inline scalar SetVector and x=y=z=0 restore difference argument scheduling, edge FP homes and z/y/x zero stores (99.701836). Alias-safe inline CrossVector with x/y/z temporaries before output writes resolves remaining f5/f6/f7/f8 rotation (100%). Bridge @112/@113 to owned EH800086C0/index800214E8 and weak SpecialFaceVec dtor to dtor_80036E40. Owned text872/EH8/index12 all100; Matching source-linked exact main.elf ranges and full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No split/data/header/flag-recipe changes.

## c17_u14_20261107
Source: Codex worker c17_u14_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 352 B.

c17_u14: fn_80202CC0/80202D70 had correct table semantics but an extern aggregate view generated add/add/lwz rather than the original compiler pool addi/lwzx. A checkedLine local separate from the input restores cmpwi r4 prologue scheduling. Reconstructing the real TU-owned pool 803C0390..803C24C8 as native string literals and pointer/int arrays restores all table offsets and two-dimensional index shifts without compiler tricks or padding. Entire text352, rodata8504, extab16, index24 object sections and source-linked ELF ranges are exact; full DOL SHA1 OK.

## c17_u21_20261107
Source: Codex worker c17_u21_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u21 PhysicsState_WallCollisionCheck 801ED0E8: target matrix product is copied without transpose (SP70->B0, SP68->A8). Correcting baseline transpose to flat16 copy improves fresh52.324768 to56.565422, EH86.53847/index61.11111 unchanged. Native matrix constructor/nested helper/canonical PhysicsGroundMatrix probes reach71.81309/78.794395/79.23364 but regress EH84.61539/index55.555557 and are rejected. Target has two-row unrolled sequential multiply, whole aggregate GPR copy, r22-r31/f30-f31 saves; retained draft has four-row loop, r28-r31/f29-f31 saves and1604B vs1712B. Single function remains NM, no A/B rescue/native gain; full fallback-linked DOL SHA1OK.

## c17_u22_20261107
Source: Codex worker c17_u22_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u22 STLContainer: reversing default-ctor locals to STLPolicy then STLCompare makes GlobalInit_854 (80038934/76B) exactly match; target policy SP+8, compare SP+C. HeaderInit remains 49.875%: early p.tag snapshot reverses zero/tag register homes; restrict policy pointer is invariant; real member-initializer ctor still loads tag after clearing count/root. DisposeRecursive remains 99.02892%, tree r30/node r31 vs target tree r31/node r30. Whole-body inline wrapper changes recursion expansion cutoff; explicit extern-C tree/node function is invariant. Whole 80038934..80038F54 reversed EH group prevents rescue split. Auto sinit is physically last in native object, another future promotion constraint. Owned EH/index/ctors/bss exact; final fallback-linked DOL SHA1 exact; no native gain.

## c17_u26_20261107
Source: Codex worker c17_u26_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u26_20261107 partial: ShadowAreaMgr_BuildFromArchive (800AAAC4,400 B) reaches 100% text with real new 0x5c model, scoped pointer owner with inline throw() dtor bridged to dtor_80080444, per-function use_lmw_stmw, entries[count] nested induction, root/count/DObj/PObj declaration order, and native nullable inline DObj/PObj getters. Scope owner after null archive return. Empty-dtor vector locals plus direct construction restore normalization stack temporaries; aggregate 0x120 snapshot assignment restores two-word copy loop (normals 96.28485%). TU stays NonMatching: QueryPoint 81.52381%, reversed trailing base-dtor EH spans all eight functions, and compiler defers normals after trailing ctor/stub/dtor. Full fallback DOL SHA-1 OK; +0 native.

## c17_u27_20261107
Source: Codex worker c17_u27_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 42 fn / 19520 B.

c17_u27 texpdag unlock: HSD_TExpSchedule correct alpha source field is a_dst, not c_dst. SimplifySrc omitted IMM cases; target alpha IMM intentionally falls through into TEV handling, and TEV substitution is blocked only for final slot with clamp nonzero/range1. Fix raster swap compare/assignment to ras_swap. SimplifyThis omitted A=0/B=1 reduction; separate a_op==0||==1 preserves target branches, and index-first declaration fixes volatile slot-index colors. The original data pool has filename10 + alignment2, assertion36, max19 + alignment1, then register tables16/16/20. Export genuine arrays and give pool184 plus clear HSD_TEArg8 to the contiguous Schedule/Src/This Matching TU. No filler objects or EH work. MakeDag improves with direct sp94 accesses but still has sort r7/r8 residual. SimplifyByMerge draft2564 vs target6088 omits early color A/D merges, scale composition and constant conflict logic; target has no HSD_TExpGetType calls. Reconstruct those stages before allocator work.

## c17_u39_20261107
Source: Codex worker c17_u39_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 8 fn / 2608 B.

c17_u39: FadeLogo nm2 was missing dtor_8020EB04 in its source object. TU-private native TaskListOwner throw() destructor plus own bridge emits exact144B without changing existing exact callers. MarkTasksFinished(TaskNode *n,TaskNode *end) inline helper fixes KillAll ED30 cursor/end homes,98.93939->100%. Decl-order probes unchanged. EC70 still has first EraseRange result/end stack-slot mismatch; named-end probe regresses EB94. Add EDB4 retains r7/r6 cursor/end and extra iterator store; FindTaskPosition+named iterator95.35294 and defaulted assignment95.82353 do not fix it. DTK rejects cut atED30 (reversed extab group); all staysNonMatching, text99.80137, EH/index0, no native gain. Future promotion must also fix deferred EC70 physical order and owned EH names/order. Full fallback-linked DOL SHA1 exact.

## c17_u37_20261107
Source: Codex worker c17_u37_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u37: NamCamFlow had four missing definitions (2BC8/43F8/4BA0/4C7C). New native update82.63441%; defining it after3198 causes CW auto-inlining of3198 (source1732 vs1488 and frame180 vs120). Capture draw96.32184%/1044B uses -(160-left) and -(120-top) before float conversion; direct left-160/top-120 gives80.206894%/1040B. Genuine three-level list storage plus shared EraseAll helper keeps sentinel r31 live across both erases and yields list dtors99.89091%/220B,99.875%/192B, exact owned EH/index; remaining return/finish iterator stack-slot swaps. Cached countdown list text99.0728% shifts generated EH names +1 and collides with existing @160/@161 bridge contract, reverted. Color union/bitfields regress. All22 functions now defined, prior14 exact unchanged, no safe EH cut; remainsNonMatching with full fallback SHA1exact and zero native gain.

## c17_u43_20261107
Source: Codex worker c17_u43_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u43: RaceHudAdjust 8024904C remains honest NM. Production C emits 36 B vs 8 B target. A genuine two-base C++ class with +8 secondary base and out-of-line override generates the exact subi/b adjustment thunk shape; declarations-only explicit template instantiation or unused inline override emit nothing. Future rescue should claim the primary HudAlternate destructor 80248F48 and its vtable together with the thunk, then reconstruct native virtual inheritance/dispatch and bridge names. This batch did not edit those matched owners. Corrected draft forwards the short deletion flag and returns HudRoot*; output remains identical to baseline.

## c17_u38_20261107
Source: Codex worker c17_u38_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 17 fn / 11136 B.

c17_u38: anon_801FC1E0 initial 0% methods were absent definitions. Reconstructed four; cursor method 801FCF58 is exact on first compile. Manager getter call must be a separate statement before light constant assignment to avoid callee-saved constant web; this restores 801FC644 text1416 (table ownership gives all100). Constructor 801FC364 needs timer global snapshot before input edge clear, subState store before timer store. Prefix 801FC1E0..801FC614/EH179D8..17AEC/index2924C..29270 safely promotes 3 fn1076B. Delete helper801FD2E8 owns earlier EH17AEC and binds remaining eight functions. C702 conditional-new padding fixes original 0000 mismatch. Owned prefix text/EH/index and actual ELF bytes exact; weak holder dtors discard. Save/eject residual remains duration-load/constant scheduling; duration snapshot improves 94.x->96.x, restrict probe does not resolve. DOL SHA1 exact.

## c17_u49_20261107
Source: Codex worker c17_u49_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 112 B.

c17_u49: fresh clFlowClass_Update object is 99.81191%, EH88 exact. Approved SINGLETON_INSTANCE spelling is instruction-equivalent to the old input getter. Compound selection += input()->delta and static inline addSelection(self,input()->delta) both leave exactly the prior missing lwz r3,0xc(r31) at target801C2860; no new information after two probes, stopped. Original selection source restored, only getter spelling normalized. Text3420 vs target3424 shifts switch-table relocations and prevents postprocess_sdata2 mapping of the later int-to-float double. Single-function TU cannot use mechanism B; no range/flag/bridge changes and no native gain.

## c17_u51_20261107
Source: Codex worker c17_u51_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u51 CoinChallengeUpdate: replacing handwritten transition getter with SINGLETON_INSTANCE is instruction-identical. Return/local/argument byte-vs-int type variants do not remove r3->r0->r27 started-result copy. Nesting IsRaceStarted and virtual steering as ApplyInput arguments reverses call order and regresses to94.939224/EH87.5. Inline whole input phase removes one copy and restores target1448B/index100 but changes FP homes and hoists virtual vptr load, text97.776245; rejected. Retain original98.24586/1452B draft. Broad self/before/after/sprites/tens GPR rotation remains. No singleton/data unlock here; single fn prevents rescue split.

## c17_u55_20261107
Source: Codex worker c17_u55_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u55_20261107: fn_801B9928 baseline 92.59424%. All defensive g_pInputState sequences already emitted via GetInput; canonical SINGLETON_INSTANCE replacement is byte-equivalent. Residual is array-subobject base materialization, not singleton reads or a shared constant pool. Target top[1]/top[2] maintain r29/r28 = base+0; bottom[1]/bottom[2] maintain r27/r26 = base+0xC. New-result registers then need r26/r25, source uses r29. Simple wrapper operator[] (member-array and cast-based forms) both fold to unchanged output. Both reverted. A pointer-returning accessor shape was not tested because two-no-information stopping rule triggered.

## c17_u56_20261107
Source: Codex worker c17_u56_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u56 ranking_display: fresh90.60096/2500B. Approved SINGLETON_INSTANCE getter removes opposite-polarity extra branch (90.777245/2496B). Native separate name pointer arrays owning .data8049B4A8..8049B510 yield exact104B data and91.104164/2492B text, EH91.32653/index91.66667 unchanged from baseline. Defining intervening RTTI base record and generated-name ABI vtable array does not pool compiler-internal vptr reference; reverted. Signed flag local changes comparison to xor/srawi/and and regresses91.00801; reverted. Still needs compiler-level persistent pool r30 for vtable+tables, iterator stack slots, allocation webs and panel scheduling. Single function remains NM, full fallback DOL SHA1OK, zero native gain.

## c17_u65_20261107
Source: Codex worker c17_u65_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1224 B.

c17_u65: FigureSlot_Tick fn_801C6744 closes 99.424835% -> 100% by factoring x/y interpolation as static inline float InterpolateFigurePosition(float start,float delta,int ticks) { return start + delta * (float)ticks / 12.0f; }. External-divisor helper first fixes X/Y conversion scratch cookie order SP+08/+10 and yields99.86928%; literal12.0f fixes final bias/divisor/start FP homes. Direct full SetPos argument expressions are byte-invariant. Text1224/extab40/index12 all exact under unchanged GC1.3.2 flags and existing EH bridges. Matching promotion, source main.elf input, actual801C6744/1224 and full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified. No split/header/EH-map changes.

## c17_u72_20261107
Source: Codex worker c17_u72_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u72: GpPleaseInit 801CD030 remains 99.352486 text / 99.1453 extab / 100 extabindex, exact sizes2576/468/12. Append discarded return vs named result and grouping index/x/ID increments in for clause are output-invariant. Distinct typed text/color panel locals regress99.31677 by adding converted-reference stack slots, retaining GPR residual. Four owned EH bytes at offsets14F/15B/167/1CB encode r25 vs targetr24. Residual list/sentinel/index/new-pointer partition plus repeated active/end r0/r7 swap remains. All experiments reverted; only approved SINGLETON_INSTANCE(g_pInputState) spelling retained, with identical final instruction output. No safe single-function TU split or native gain.

## c17_u87_20261107
Source: Codex worker c17_u87_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u87 MsgPopup::Tick 80203224: fresh 99.06584 -> 99.415634 with TU-local inline LayoutPopupTexts(popup,s), declaring ox before base. Exact 972B size and primary 24B EH/12B index payloads preserved; s=f31, text scale=f27, base=f29, x-offset=f28 and dy=r29 now correct. Remaining sx/sy f29/f30 swapped, index/stride r28/r27 versus target r27/r28, index zero coalesced into mr and opposite dy/stride increment scheduling. Per-line nested helper leaves residual unchanged. Scale aggregate also leaves register residual unchanged and makes raw conversion-double @106 collide with stale table bridge; reverted. Final helper emits table @98, EH @101/@102, weak ResCtrl EH @105. Future promotion still needs .data804EC3C4..804EC3E0 ownership and add-only bridges/EH order, plus existing unowned emitted sdata2 audit. No missing functions or legal positive subset in singleton TU. Remains NonMatching; coordinator full fallback-linked DOL SHA1 exact; native gain zero.

## c17_u92_20261107
Source: Codex worker c17_u92_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u92: fn_801F7344 fresh99.03409 ->99.34659 by explicitly comparing the unsigned-char empty-bank predicate with 1. This exposes cntlzw/extrwi but retains cmplwi r0,1 and bne, rather than target recording extrwi. and beq. Text708 vs target704; conversion-cookie @84 unresolved at shifted offset. Inverted nonempty predicate ==0 and inline assertion helper taking unsigned char both produce baseline700B/99.03409. Extab100/index91.66667 unchanged. Three hypotheses exhausted, one-function TU prevents split rescue; remains honest NonMatching with zero native gain. No full build requested; direct exact-command object compile succeeds.

## c17_u93_20261107
Source: Codex worker c17_u93_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u93: Object_DriveAnimAndSkin 800331E0 improved 99.02597 -> 99.123375 with unchanged 1848-byte body and exact owned 88-byte EH/12-byte index. SaveRotations(self) now obtains savedRotation locally, with loop index declared before it, restoring save index r29. TU-local RequestDrive(JObj **cursor,int count,float frame) replaces receiver-based Request; further improves request GPR homes. Flattening Save/Restore into PrepareRotations and sharing i regresses to 98.90693; do not repeat. Residual is entirely GPR identity in prep/request/animate; conversion tail exact. Whole EH scores95.652176/66.66667 are unchanged appended weak timer metadata. One-function TU cannot mechanism-B split. Three structural hypotheses exhausted; kept NonMatching, no native gain. Coordinator fallback full build SHA-1 OK.

## c17_u107_20261107
Source: Codex worker c17_u107_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u107: ItemGridState_Init 8023A7AC/608B fresh98.947365 ->99.07895 by extracting only the nested text-grid creation loop into a static inline CreateGridTexts(GridInitState*). Row counter becomes exact r27, but row base/new-pointer/cell-base/col-counter still rotate; fallback search cursor/ordinal/candidate r3/r5/r6 vs target r5/r6/r3 remains. Explicit named new result and col-before-row declarations do not fix allocation homes; per-cell reference helper is baseline-equivalent; inline membership predicate regresses96.94079. Retain whole-grid helper, EH90.38461/index66.66667 unchanged; native gain0. Primary EH still needs DELETEPOINTER r29 rather than r24 plus future anonymous bridges (@77/@78 in retained current compile); weak ResCtrl dtor has extra8B EH/12B index. Singleton prevents rescue split.

## c17_u116_20261107
Source: Codex worker c17_u116_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u116: MinimapHud dtor 8021995C improves 98.90351 -> 99.07895 with explicit MinimapHud *cursor=this, cursor->sprites[0], and byte-stride sizeof(int) cursor increment. Both index loops now use target r28; 456B unchanged, owned 92B EH and 12B index raw bytes exact. Remaining target/source coloring: this r30/r29, cursor r29/r27, deleting flag r27/r30 (19 instruction rows). Ref-index first-loop helper is byte-identical negative; whole resource cleanup helper regresses 98.85965 and puts second loop in r27. Three approaches exhausted; one-function TU stays NonMatching. Full fallback-linked coordinator DOL SHA-1 OK, zero native gain. Current compiler EH names @114/@115 are not bridged; no metadata added.

## c17_u119_20261107
Source: Codex worker c17_u119_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u119: fn_80203C24 remains98.854965 (520B vs524B). Explicit fn_80271340(t,0,MsgPopup_RTTI_806D0268,FlowTask_RTTI_806D0260,0) removes duplicate68B data+24B sdata with unchanged primary instruction rows and95/91.66667 EH/index. Dispatch helper taking pending by value changes pending/layer rank to r31/r30 but retains early callee-saved load (98.54962); inline queue-take return and OpenMsgPopup const-int-reference snapshot are invariant negatives. Original by-value source retained. Residual is absent target +E0 mr r30,r4 caused by early coalescing; owned EH PCs are -4 and function size is -4. Single function cannot split. No flag/split/bridge edits, fallback full DOL SHA1 OK, native gain0.

## c17_u117_20261107
Source: Codex worker c17_u117_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2604 B.

c17_u117: StateLines 8021FC4C/2604B closes 98.88633 -> 100 by indexing lbl_803C6A24 with hasBonus2==1 ? 3 : 4 (instead of (-1:0)+4), then declaring final-loop line pointer before counter. The first fixes both addi/slwi/lfsx table lookups; the second fixes volatile r6/r7 homes. Approved singleton macro reads preserve text but shift generated EH labels from @381/@382 to @379/@380. Add owned EH/index bridges for latter, retain flags/splits unchanged, flip Matching. Text2604/EH220/index12 all100; final source-linked DOL SHA1 exact. Native gain1fn2604B.

## c17_u124_20261107
Source: Codex worker c17_u124_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u124 ShowItem 80222968: inline ratio helper is instruction-identical at 98.78723%. Packed RGBA object copied to a by-value label helper produces target xoris r3 and mr r5,r4, distinguishing object-copy color formation from scalar PackColor, but introduces stack object copies (+24 text bytes; 94.06383%) and swaps text/label registers. Whole-fade helper returning alpha remains 1880B and exact EH but scores 98.53191% with additional color r0/r3 and FP scratch differences. All experiments reverted; existing best draft retained with approved SINGLETON_INSTANCE read. Single-function TU cannot rescue an exact subset.

## c17_u125_20261107
Source: Codex worker c17_u125_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 344 B.

c17_u125: DrawEffect_TickAndCull 800AF904/344B improves 98.77907 to100% by moving the original pool loop and view/count locals verbatim into static inline TickDrawEffectPool(), leaving ScopedTimer timer(26) in the exported caller. Baseline target cursor/counter r30/r31 were swapped. Explicit cursor adds mr through r0 (97.558136); per-entry helper is baseline-equivalent (98.77907). Whole-loop helper restores exact registers and all344 text bytes. Append own @51->@etb_8000A4D8 and @52->@eti_80022970 bridges, preserve old keys. Owned text/extab24/index12 all100; existing weak ScopedTimer copy discarded at link. Matching flag and actual main.elf ranges verified; full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No split/header/data edits.

## c17_u128_20261107
Source: Codex worker c17_u128_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1440 B.

c17_u128: ItemWnd::ShowOther 80221FC4 reaches exact 1440-byte text and 24/12-byte EH/index by spelling case-2 fn_8021A4B8 alpha as 1.0f rather than external lbl_806DB194. External memory CSE had kept the scale initializer in f4, added fmr f1,f4 and altered timer-conversion scratch registers. Moving the scale declaration after fade is byte-invariant and was reverted. Canonical SINGLETON_INSTANCE is equivalent. Existing bridges/flags suffice; Matching source-linked at 80221FC4/1440, actual owned bytes exact and full DOL SHA-1 ea30f3b1 OK. No split/header/EH map edits.

## c18_u10_20261107
Source: Codex worker c18_u10_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 6088 B.

c18_u10: SimplifyByMerge 802E34EC/6088B unlocked from 33.365967% to 100%. Previous draft omitted four-stage color/alpha A/D merge structure, constant-input conflict guards, range checks, scale composition and Ref/Unref replacement paths. Static inline bias/scale/constant/order helpers reproduce all target branches. Declare result/merged/bias/scale in that order for r31/r30/r29/r28. Color-D stage needs a block-local type cached before child pointer and selector acquisition; this restores lwz/cmplwi/lbz scheduling. Target alpha swap guard checks HasAlphaConstant(child) twice (original behavior retained). Existing text-only split suffices; flip Matching, no pools/EH/splits/padding. Full source-linked DOL SHA-1 OK.

## c18_u16_20261107
Source: Codex worker c18_u16_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u16: fn_801CDF10 improves98.68852->98.74317 with static inline void UpdateFade(self) containing input singleton read, pressed local, timer increment/100 trigger and complete fade-start action. This fixes both pressed r29->r30 instructions while preserving732B/EH8/index12. A bool-return policy helper also fixes pressed home but adds16B predicate materialization; keep side effects in helper. Extra SetPlayerCharacter wrapper and direct typed field assignment are byte-invariant. Residual tail character/base/gate scratch homes and gate-store/li scheduling remain. No split/flag/pool changes, singleton TU remains NonMatching.

## c18_u9_20261107
Source: Codex worker c18_u9_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u9: clItemBoxManager_nm1 retains NM improvements RemoveByKey94.5098->97.64706 using a raw-node inline erase helper (iterator-reference/value helpers spill); exact204B/branch shape leaves r27/r28 walker swap invariant under search-iterator earlier declaration. PushBefore77.42857->93.666664 by giving private NodeHolder<void*> a real RAII destructor; exact168B now stores owner/node on stack and clears released pointer. Remaining try-region SP-store placement and position/node r5/r6 swap. Removing explicit try gives72.5; declaration/evaluation-order probes invariant. Existing 100% functions unchanged; all11 owned EH payloads/relocations exact. Tail base dtor EH at80007CDC binds full reversed group, preventing B. No Matching flip/native gain; fallback DOL SHA1 exact.

## c18_u20_20261107
Source: Codex worker c18_u20_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 328 B.

c18_u20: fn_8015BCC4 98.65854 -> 100% by moving SetupCamera inline body into the main function and using a real function-level early return when either viewer is null. Guard inside inline helper remains byte-invariant (324 B): it emits beq exit. Direct main-function guard emits target bne setup / b exit and 328 B. text328/extab40/index12 all100, existing EH bridges unchanged, Matching source-linked full DOL SHA-1 OK; ELF 8015BCC4/328 verified.

## c18_u21_20261107
Source: Codex worker c18_u21_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u21 CopyStatsBlock 8008DE60 retry: baseline is 98.63666%, not source comment 99.7%. Four instruction positions differ: +334/+338 delay load19C past store198; +344/+348 hoist load1A4 before store1A0. Whole-block assignment emits 48-byte loop (1.96463%). Restricted scalar copies over-hoist loads and spill (38.758842%); large static inline section helpers remain calls (0.109325%). Small inline pair-copy helper reproduces baseline identically. No flags/ranges changed; single-function TU stays NonMatching. Native gain 0.

## c18_u36_20261107
Source: Codex worker c18_u36_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u36: SceneListImpl::Draw 80204218 baseline98.35821/264B vs268B target. TU-local inline RemoveTask(DoublyLinkedList*,ListIter) with named result assigned from entries->Erase fixes Erase result/argument stack order (SP+8/+C), improving98.41791. Still lacks target store at802042E8: intermediateSP+10 then loopSP+14 versus source loopSP+10. Return-assignment spelling is byte-identical; explicit private iterator copy ctor regresses80.029854/244B and is reverted. Task logic/registers otherwise agree. Single-function TU staysNonMatching; no singleton/pool mechanism or B cut, no native gain.

## c18_u35_20261107
Source: Codex worker c18_u35_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u35: SwitchList ctor 8017A68C remains 98.39921% (1012B) after three structural hypotheses. Owning .rodata 80371E98..80371F28 as typed static SwitchConstantPool array reproduces all 144B and base-register relocations, but leaves bge-versus-blt dispatch and both first-lwz-before-hidden-stw scheduling differences unchanged. case0 return adds compare and 12B, drops97.19367%; memcpy bounds copies emit calls, drops85.46245%; both reverted. Keep exact pool acquisition, existing NonMatching flag, text/EH unchanged. Only one function in TU, no B split. Final fallback-linked coordinator full build SHA-1 exact; native gain0.

## c18_u39_20261107
Source: Codex worker c18_u39_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u39 EnemyRun_BaseInit 801F0644: explicit LHS row cursor plus named invariant RHS base and indexed output improves 98.23385 to99.08, same1300B and owned176B EH/12B index100. Unlike c8 full-pointer-loop trial, inner loop remains counted and all FP arithmetic now follows target. Remaining n/index/row/column GPR colors and outer increment scheduling differ. Output-argument helper is instruction-invariant; returning a matrix adds128B aggregate copy. Add own @144/@145 bridges; existing @148 now names an extra weak8B EH record too, so future promotion must inspect discard/linked ranges. Single function stays NonMatching; no mechanism-B cut. Final fallback DOL SHA-1 OK; native gain0.

## c18_u103_20261107
Source: Codex worker c18_u103_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u103: fn_801B4548 fresh96.06223->96.06577 by extracting whole nearest-kart search into static inline FindNearestVoiceKart801B. Text5616 vs5656, EH87.5/index83.33333/data0 unchanged. Identity record-pointer helper regresses94.734795/5552B; explicit id/character address lifetimes restore both category-5 pre-loop addi instructions but worsen register pressure and tail reloads,95.901695/5620B. Both reverted. Residual includes folded map/clip subobject bases, saved GPR range, identity reloads and timestamp/return scheduling. Singleton TU cannot B split. NonMatching, fallback full DOL SHA1 exact; native gain0.

## c18_u85_20261107
Source: Codex worker c18_u85_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u85 fn_8018E6FC: caller-owned named scene declared after index and passed to initializeMatrix(o,scene,index) restores target initialization joint r31/stride r30/scene r29, improving 97.188774 to97.35459 with unchanged1568B and exact8B EH/12B index. Moving whole selection into helper invariant; passing unnamed scene97.29082; reversing helper parameter order invariant. External coefficient constants and affine scaledVariation helper invariant97.35459, as is spawnParticle(o,p,point) helper. UpdateMatrices now swaps index/stride r31/r30; point/free-result and final-loop pointer/offset swaps plus FP homes persist. Single function prevents B isolation; remainsNonMatching; coordinator full fallback SHA1 exact.

## c18_u74_20261107
Source: Codex worker c18_u74_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u74: fn_801D680C 97.554375 ->99.4695 under unchanged flags. RankReached validates cc 0..2 then indexes cupRank[(unsigned int)cc][cup]; differing signedness prevents CSE of earlier signed cc*8 across calls, removing extra callee-saved web and restoring target r27-r31, 1508-byte text and exact8/12-byte EH/index. Block-local status=fn_8024F588(); *status=1 restores post-call li r0,1. Sole residual is initial g_ccClass load: source lwz/li/stw versus target li/stw/lwz at offsets58..60. cc-before-award and inline getter swap cc/award; award-before-snapshot moves li too early; separate copy assignment invariant. Six hypotheses exhausted. NonMatching retained; full fallback DOL SHA-1 OK; no single-function split rescue.

## c18_u106_20261107
Source: Codex worker c18_u106_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u106 AI_UpdatePerFrameState: direct rank scans with initialized result + break restore per-match mr instructions missing with early-return helper. Explicit lap subtraction then a=a*count/laps=laps*count restores target multiply operand order and volatile homes. Text 96.175674 ->97.34122 (strong function2376 vs2368B), owned24-byte EH unchanged. Caller-owned reference result/shared base probe96.998314 changes EH and is discarded. Remaining pair/proximity GPR cycles, f29 vsf31 nearest distance, rank base reload/result homes, speed-mode/state swap. Shifted conversion-cookie load causes offset-based postprocess_sdata2 to infer lbl_806DA3E0 instead of lbl_806DA400; do not promote until corrected by allowed means. Single-function TU prevents B rescue. Retained NonMatching; coordinator build request1 full fallback DOL SHA-1 OK; no native gain.

## c18_u49_20261107
Source: Codex worker c18_u49_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 48 B.

c18_u49: EnmyFaceEffect UpdBanana target EH requires destructible local/member vectors. POD Vec3 plus Vec3c base-copy ctor and inline empty Vec3c dtor raises 98.0083 to 99.39834 without lowering other functions. Vec3c-specific matrix helper, r.x *= 0.9f, and RotMtxVec reference helper with rz/rx/ry locals reach 99.81328 (1928 bytes exact size); remaining FP identities differ at four inline sites. Leading CE04 48-byte wrapper splits safely and is source-linked with full SHA-1 OK. Larger six-way split can produce 11 exact native candidate functions, but moving shared bss regresses destructor/initializer; preserve the safe 1-function split until storage ownership is solved.

## c18_u50_20261107
Source: Codex worker c18_u50_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u50: fn_801D1890 improves 97.993805 -> 99.990715; extab 95 -> 100%, index 100%, text size 1292 unchanged. Canonical RankingFlowIter loop with TU-local !=/++ changes new pointer to r28; wrapping whole list traversal as static inline RankingAdvanceFlow(RankingFlowList*) returning end fixes all GPR homes. Per-animation helper alone is invariant. Void insertion helper taking const RankingFlowIter& and explicit temporary RankingFlowIter(end) improves stack layout to three residual instructions (0x2B4 hidden-return SP+0x0C vs target+0x10; 0x448/0x468 second iterator SP+0x10 vs target+0x0C). Returning iterator from that insertion helper regresses to six differences. Whole-Update helper exceeds auto-inline threshold. Retained NonMatching; full fallback DOL SHA-1 OK; zero native gain.

## c18_u108_20261107
Source: Codex worker c18_u108_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u108 fn_801FB778 retry improves96.139275->99.387184. Full SetPanelTextPosition/offset call expressions repair FP scheduling; addressing first group as p->pad+4 instead of raw (char*)p+4 prevents group-base CSE, removes4B and fixes allocation/EH r29/r30. Literal0.5f fixes center scratch homes. Inline StepSaveFade(self,input) fixes case6 input/fader r5/r4. Exact1436B and owned EH44/index12/data40 all100. Remaining final input read usesr3 instead ofr4 and delays kart load until after null check. Decl-before-input, direct Step, direct tail singleton argument and SetKartInput helper are invariant negatives. Single function remainsNM; full fallback DOL SHA1 OK, native gain0. No pool/range/bridge/flag edits.

## c18_u90_20261107
Source: Codex worker c18_u90_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u90: ItemBoxConstruct8016D2D0/1228B improves96.87296->99.93485. Direct(root==0?0:root->child) loop initializers reproduce target null-first branch; helper ternaries introduce mr. Declare outer j before i, initialize i first, to fix r28/r29 swaps; hoist j/i/p/k/d after resources to put DObj walk in target r24 instead of r26.124B EH and12B index exact. Sole residual four initial address-setup rows: pool high scratch r7/source r3, base-vtable low/store r3/source r6. Whole DObj helper and out-of-class inline base ctor invariant. Typed pool direct fields add24B; explicit pool base retains scratch choice; reverted. Single-function TU remains NonMatching. Full fallback DOL SHA1 exact; zero native gain.

## c18_u62_20261107
Source: Codex worker c18_u62_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u62 fn_801F7604: own .rodata 803BEDC0..803BF020 and define separate native GX descriptor/format arrays, not an aggregate accessed through a formats pointer. This removes the extra pool-base mr and restores constant-offset address arithmetic, text1140->1136 B, fresh97.693665->99.753525 default /99.92958 without inferred pool relocations. All608 rodata bytes and primary56B extab/12B index plus relocations exact. Remaining real differences are offset r28 vs targetr29 at801F79DC/79F0/7A08/7A20. Direct format block and function-scope offset are invariant; ternary adds24B; whole-body inline helper does not inline. Keep honest NM; singleton prevents B; full fallback-linked DOL SHA1 exact, native gain0.

## c18_u61_20261107
Source: Codex worker c18_u61_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u61: fn_80221104 Draw remains single-function NM584B. New TU-local inline DrawNodes(PtrVec<FadeObj*>&), owning full traversal and existing Render calls, improves97.73972->97.77397; node-object home becomes targetr29 but iteratorr28 vs targetr27. Whole-window-states and whole-coin-loop helper boundaries are baseline byte-invariant. ItemWnd/NextWnd and coin cursor/index color differences remain; all owned EH8/index12 exact. Keep slight genuine draft improvement, no flag/split/data/shared-header changes, zero native gain. Coordinator final fallback-linked DOL SHA1 exact.

## c18_u54_20261107
Source: Codex worker c18_u54_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u54: CharaSelect_SetupCharacterDisplay improves 97.89349 -> 99.94083 (99.49704 before re-split pool relocation inference). Own rodata 8039AA40..8039B1F4 as distinct typed static arrays/strings; preserve 3-float table at AED8 and separate 4-float scale table at AEE4. This restores target scale addi r5,r31,4a4 + lfs 4(r5), texture addi r3,r31,464 + lwzx, exact676-byte text, EH56/index12 and rodata1972 all100. Remaining only addi/lbz third-stat pointer r25 versus targetr26. Signed-byte/void cursor reuse moves it to r29; typed stat struct and earlier declaration/narrowed second-loop scope are invariant; third-loop inline helper shifts many homes and removes addi. Six hypotheses exhausted; singleton remains NM, zero native gain. Full fallback DOL SHA-1 OK and no other report function regressions. Trailing4-byte gap B1F4..B1F8 remains auto.

## c18_u111_20261107
Source: Codex worker c18_u111_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 516 B.

c18_u111: CardEjectTask fn_801FD5FC 516B resolves95.93023->100 by owning .rodata803BFE48..803BFEF8 as separate static const char arrays for original type names and localized messages, using direct string refs. MWCC GC/2.6 automatically hoists section-base r31 before base ctor, matching target lis r5/mr r30/addi r31/bl instead of late external cache. Previous c5 member-allocation/cache-removal probes were unnecessary. Add own @34/@35 EH bridges and globalize original string symbols through per-TU mappings for fallback RTTI references. Text516/EH44/index12/rodata176 all100; no padding objects or flag changes beyond Matching. Full source-linked target DOL SHA1 exact; main.elf801FD5FC/516 confirmed.

## c18_u82_20261107
Source: Codex worker c18_u82_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 292 B.

c18_u82: TireSprite_Load 8022B278 (292B) indexed inline helper had every instruction/control edge correct but generated array induction webs occupied r25..r28, while k/n occupied r31/r30. Native explicit typed cursors declared textures, palettes, resources, tluts, i, n, k restore target GPR homes. Initialize i and then cursors after DebugPrintf; use separate real early-return guards for textures/palettes and natural cursor increment order. Text/extab/extabindex all 100%; Matching source input, final main.elf address/size and full DOL SHA-1 verified. No section ownership, bridge, flag recipe or shared-header changes needed.

## c18_u80_20261107
Source: Codex worker c18_u80_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 1724 B.

c18_u80: fn_801FDDA4 97.336845 ->100% by replacing hand-built if/goto dispatch with native switch and explicitly grouping protocol result6 with case2/default (same known result6 handling pattern as neighboring fn_801FE030). Cases1,2,3,4,5,103 alone choose pivot4 and376B; adding case6 restores target pivot5, cmp103/beq/bge/b sequence and380B. Duplicate case2/default error bodies regress87.28421%. Existing text380/extab8/index12/data28 all100; Matching source-linked actual ELF ranges exact; full DOL SHA1 ea30f3b1 OK. No bridge/pool/range changes.

## c18_u70_20261107
Source: Codex worker c18_u70_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 76 B.

c18_u70 fn_802170F0: c13 alpha leaf 97.63158 ->100%/76B. PackColor four unsigned-char parameters instead of int first reaches98.42105 (sprite r7 fixed). Stage sprite/alpha/packed-color once per iteration to fix alpha r6/color r5; block-local sprite swaps iterator/sprite r7/r8 (97.89474). Move only sprite declaration to function scope to obtain iterator r8/sprite r7, all19 instructions exact. Existing one-function text split needs only Matching flag. No EH/data, bridges, pragmas or padding. Full source-linked DOL SHA1 exact; linked fn802170F0/76 bytes equal target.

## c18_u132_20261107
Source: Codex worker c18_u132_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2900 B.

c18_u132 RaceScene_Init 800A1D80: 99.97931 ->100% by correcting TU-local ItemSelect_GetSlotItemId declaration unsigned char -> int, matching actual definition in ItemSelect.c. Keep unsigned-char loop item: int-return narrowing emits target clrlwi. r3 then mr r26,r3 instead of mask into r26/copy back. Int local alone regresses99.93793, explicit byte-to-int second-call copy invariant99.97931. Text2900/data36/extab556/index12 all100; existing TU promoted Matching without new ranges/EH bridges. main.elf source edge and symbol800A1D80/2900 verified; full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c18_u91_20261107
Source: Codex worker c18_u91_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 464 B.

c18_u91: fn_801D878C c13 retry unlocks96.85345->100%. Secondary white-alpha packing uses accepted presentation-family __rlwimi(0xFFFFFF00U,(int)(lbl_806DA190*self->alpha),0,24,31), matching FlowPanelUpdate/c18_u41 precedent. Explicit loop-local white block restores464B but swaps TextManager stack slots and changes loop GPR/FPR homes (99.034485). TU-local FKDrawWhiteText with original y/x/text/local order restores every instruction and both EH cleanup slots/PC ranges. Full source-linked DOL SHA1 exact; ELF symbol801D878C/464 and text464/extab40/index12 byte-exact. Object EH90.909096/index66.66667 due discarded weak dtor copies. No new bridges/order/splits/data/shared headers; native gain1fn464B.

## c18_u133_20261107
Source: Codex worker c18_u133_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 556 B.

c18_u133 fn_8018B31C: raw baseline90.64771 ->91.12670 (report91.25835), text6456 versus6472. Static inline PackedChecksum returning unsigned char restores checksum byte narrowing before >>2 (target six-bit extrwi instead of previous eight-bit shifted extract). Rotation loop-local byte pointer regresses90.05439/text6480; value-first WriteBits argument order is byte-invariant. Shared rodata/BSS base pools already emit and are owned, so no pool rescue needed. Residual name/class/base GPR webs, first writer base coalescing, swap subarray base folding, rotation address shape and final checksum writer scheduling remain. BSS84 versus88 unchanged, no filler added. Single function cannot use mechanism B. Honest NonMatching and full fallback-linked DOL SHA1 OK; zero native gain.

## c18_u136_20261107
Source: Codex worker c18_u136_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1016 B.

c18_u136: fn_802124FC resolves99.76378->100 with literal1.0f/360.0f in final spin block. Safe split at802128F4 yields1016 native bytes, owned8B EH/12B index100 and full SHA1 exact. fn_802128F4 target cleanup begins0x64, source ctor-after-matrix lookup begins0xC0. Default KartPos before lookup plus inline Set(px,py,pz) restores target RTL coordinate loads and exact24B owned EH while retaining99.86264 text. Remaining two speed scaling FP scratch/coalescing residues persist through direct RHS, separate product, setter helper and factor-before-speed declarations. Keep nm1 NonMatching; no blind further permutations.

## c18_u147_20261107
Source: Codex worker c18_u147_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u147: Object_DriveAnimAndSkin improves 99.123375 -> 99.43723, same 1848B. Extract entire callback-init/AnimateDrive/callback-invoke block into AnimateAllDrive(self) with timer in caller, then declare explicit JObj *joint before rotation in SaveRotations/RestoreRotations. Restore and conversion match exactly; residual40 GPR-only rows: save19, clear3, request14, animate4. Whole-function inline exceeds budget; shared open-coded request locals98.93939, DriveTable getter97.943726, count-before-table decl99.166664. Owned88B EH and12B index payload bytes exact; weak timer adds8/12B. No flag/splits/maps changed; final fallback full DOL SHA-1 exact. Single function cannot mechanism-B split.

## c18_u149_20261107
Source: Codex worker c18_u149_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 20 fn / 4964 B.

c18_u149 Scene_8015AFCC retry: fresh baseline99.93104, five first-preload-loop r28 vs targetr29 differences. Full resource-phase inline helper regresses99.45977; reuse i in earlier unrolled member init is byte-invariant. Declare i before itemId (int i; int itemId; int extra;) with all code otherwise unchanged: text1740/EH196/index12 all100. Existing name bridges/flags suffice; flip Matching. Full source-linked DOL SHA1 exact, ELF fn8015AFCC/1740 verified; +1 native fn/1740B.

## c18_u148_20261107
Source: Codex worker c18_u148_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 948 B.

c18_u148: YesNoButtonL DrawLabel802064D8 reaches100%/948B via explicit px/py values for highlight, English px-before-py and Japanese py-before-px declarations, and final placement via separate static inline ButtonX/ButtonY(const YesNoButton*,float) transforms with scale-first multiply. The axis helper boundary restores target scale reloads after ResCtrl SetScaleXY; direct field-expression Place cached them and lost8B. Split extab902C..9044/index2993C..29948/text2064D8..20688C into Matching _m2. Owned EH24/index12 exact, weak ResCtrl dtor entries discarded; full native DOL SHA1 exact. Update95.56579 and DrawCredits99.77579 remain baseline NM after bounded invariant/regressing probes.

## c18_u162_20261107
Source: Codex worker c18_u162_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u162 fn_801EE36C remains99.9135%/1156B, zero native gain after six probes. External coefficient, whole interpolation inline helper, and coefficient return helper are instruction-invariant. Scalar mutating coordinate helper regresses99.84429 (previous-Xf9/scalef10); const-reference scale regresses99.740486 (scalef7/yf8/zf9). Canonical PhysicsGroundState fields replace raw STEP macros and char* with identical baseline primary instruction output and unchanged exact owned24B EH/index12; retained for semantic clarity. Residual previous-Xf10 vsf2 and coefficientf2 vsf3 remains five rows. No singleton/shared pool pattern or mechanism-B subset; no flags/splits/bridges changed and no full build requested.

## c18_u159_20261107
Source: Codex worker c18_u159_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 132 B.

c18_u159 RaceDigitUpdate fn_80246484: typed inline LapBegin/LapEnd/LapNext/LapValue using existing DigitIter improves98.76636->98.89097, exact1284B and data32/extab8/index12 all100. Main receiver/node register pair becomes targetr4/r3; remaining diff rows62->56. Full lap-tail helper plus cached end->next regresses98.83178; grouped main+other-panel HideHudPanels helper regresses98.82866. Keep H1, honest NonMatching. Residual multi-loop GPR homes and sentinel r0 vs targetr27 across panel-update call remain; source begin reload self+3C vs target sentinel+4. No singleton/pool mechanism applicable; one-function TU prevents B. Full fallback DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact, zero native gain.

## c18_u171_20261107
Source: Codex worker c18_u171_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u171 MsgPopup::Tick: replacing extern layout-base lbl_806DAAC8 with original literal -40.0f fixes sx/sy f29/f30 swap and raises fresh 99.415634 -> 99.49794, exact 972B primary text and owned 24B EH preserved. Explicit offset+scoped loop changes GPR homes but regresses; short index adds extsh/branch; smaller control-render inline helper adds position FP swap. Remaining i/stride r28/r27 vs target r27/r28, index-zero coalescing, dy/stride scheduling. New table @99, primary EH @102/@103; existing @106 table bridge now collides with weak dtor extab. Retained .sdata2 grows8->16 due literal+alignment although references externalized; future promotion must audit final section placement. No flags/ranges/maps changed, no native gain; six hypotheses exhausted.

## c18_u170_20261107
Source: Codex worker c18_u170_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u170: TaMode_Init fresh93.5946 ->94.20946 by declaring BATTLE as external TaModeRaceTables{RaceParams cups[8][3][2]} and using &BATTLE.cups[cup][cc][round] rather than casted byte-base indexing; keep one-based params[-6]. No-inferred-pool scores93.945946 ->94.40034 confirm real instruction improvement. Native grows2376->2384B vs target2368; EH94.897964/index95/data50 unchanged. Explicit ghost if/else regresses92.994934 and duplicates index arithmetic; full inline CreatePlayerCar regresses91.140205/2416B. Revert both. BATTLE pool8040EA58..8040F0A4 already belongs to TaMode_FrameUpdate.cpp, preventing in-scope vtable+658 pool coalescing; no ownership change attempted. Remaining first2 log rematerializations, player/PathManager GPR webs, ghost address/scheduling and parameter tail base/load-order differences. Singleton function staysNM, no B split; final coordinator fallback DOL SHA1 exact, native gain0.

## c18_u183_20261107
Source: Codex worker c18_u183_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 812 B.

c18_u183: DNStartCamera Update 80229398/812B resolves99.75369->100% by extracting ONE flash iteration into static inline UpdateFlash(clDNStartCamera*,int), leaving six-iteration loop in caller. Early helper returns replace original continue paths. Whole-loop helper still rotates second-loop GPRs (99.45813); per-cameraman helper regresses FP scheduling86.52217. Per-element flash boundary restores all203 instructions including first-loop walker/index r27/r30, with text812/EH8/index12 all100. Existing EH bridges suffice; only source+Matching flag changed, no pools/splits/header edits. Full source-linked DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact; actual ELF fn80229398/812 byte-identical.

## c18_u191_20261107
Source: Codex worker c18_u191_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 708 B.

c18_u191: GrandPrixMenu ctor fn_8020C38C 708B resolves99.77401->100 by expanding the existing Factory body into a constructor-local block, then declaring id, mode, chara in that order. Expansion first fixes cup r29->targetr30 but swaps final id/chara homes (99.85876); declaration refinement restores target idr30/charar29. Shared-local selection and whole-switch helper regress99.66102; returned normalize value and CupSelection aggregate invariant99.77401; ternary clamp adds4B. Add own @159 jump-table and @160/@161 EH bridges plus own extab-order key with four weak dtors last. Existing DATA_ALIGN4_WEAK_TUS entry reused. Text708/data52/ownedEH96/index12 all100, Matching source-linked ELF fn8020C38C/708 and all owned ranges equal target, full DOL SHA1ea30f3b1 OK. No split/range/header changes; native gain1fn708B.

## c18_u196_20261107
Source: Codex worker c18_u196_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u196: ItemEffectImpact_TryArmInit fresh93.759125 ->93.86131 with scalar ArmLengthSquared(x,y,z), yy then xx then zz products, used only by matrix-row/up NormalizeCopy. Exactly four source instructions change: Y/X loads and squared-product ordering at +1B8/+1BC/+1C0/+1C8 now match target. Using it for projected-position normalization regresses to93.79562. Literal0/1/2/60 probe93.38443/1648B rejected; alias-safe staged Cross helper is invariant93.86131. Retained1636B vs1644 target; projection pos.x reload, cross/quat FP webs/scheduling remain. Add-only @216/@217 bridges preserve EH98.4375/index95. Singleton stays NonMatching; full fallback DOL SHA1 exact; zero native gain.

## c18_u202_20261107
Source: Codex worker c18_u202_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 500 B.

c18_u202: YIState fn_80179F60 fresh default92.90566 / no-inferred-pool94.41779 improves96.81671 /97.690025 using one existing mapeffect_rodata_80370870 base plus offsets408/448/428. Header prefix already owns the table pool, so do not claim it from another Matching TU. Explicit extern lbl_806D8E90 avoids postprocess_sdata2 mapping a newly numbered0.005 literal to1.0 under changed source shape. Typed edge helper regresses88.1752; explicit vertex/position locals97.463615. Native1472 vs target1484: three quad addi r3 instructions folded away, plus FPR/load-order differences. All other function scores/data sections unchanged, extab99.34211->100. Reversed EH starts with tail fn80179F60 at800117E0; mechanism B blocked (prior c2 proven). Keep whole NM; no native gain.

## c18_u207_20261107
Source: Codex worker c18_u207_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u207 retry ItemGridState_Init 8023A7AC/608B: static inline int GridFallbackCandidate(int index) returning ItemGridState_Init_rodata_803DC174[index], used for both candidate loads in fallback search, fixes cursor/index/value source r3/r5/r6 to exact target r5/r6/r3. Text improves99.07895->99.47369. Grid GPR rotation persists (source rowBase29,row27,col26,cursor28,new24 vs target26,27,28,24,29); eleven text instructions differ. Row helper regresses98.947365; inline new factory and actual GridInitState ctor are invariant99.07895; function-scope named new result/counters and setter helper taking new result are invariant99.47369. Retain only accessor improvement, NonMatching. Primary EH still DELETEPOINTER24 vs29 and anonymous @82/@83 need future bridges; extra weak ResCtrl dtor EH8/index12. Full fallback DOL SHA1 exact; native gain0.

## c18_u209_20261107
Source: Codex worker c18_u209_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u209 PhysicsState_KartCollisionCheck 801ECB88 fresh92.14535 ->92.23256. Typed output/position/previous ApplyHitMovement helper reaches92.15988; moving default movement declaration earlier and passing scale explicitly is invariant. Reference-mutating radians/degrees normalization gives92.23256; unsigned-char flags getter regresses90.70349, reverted. Main remains1356B versus1376B, missing five yaw constant reloads; immunity r9-vs-r5/branch island, movement FP/store schedule and owned EH PC intervals persist. Singleton stays NonMatching; no A/B rescue. Full fallback-linked DOL SHA1 exact; zero native gain.

## c18_u210_20261107
Source: Codex worker c18_u210_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 552 B.

c18_u210: R-button Update/DrawLabel 802055F4/8020579C improve 90.462265/97.791306 to98.962265/99.95652. Local const YesNoButton axis helpers with scale-first multiply restore scale reloads after SetScaleXY (same mechanism as matched L-button DrawLabel); target sizes424/920 restored from408/912. DrawLabel keeps original English py-before-px, uses Japanese py-before-px declarations, declares tx near f/oy, and reuses oy for text origin. Sole text residual is 80205AA8 fadds f2,f2,f30 vs source fadds f2,f30,f2. Converted-row inline helper/direct dy temporary flips operand order but changes9 FPR identities (99.695656). Update retains layer/color GPR and placement FPR identities plus EH PC span0x4A vs target0x46, indicating ResCtrl scope should end before DrawLabel/Animate. Both remain NonMatching, no native gain.

## c18_u215_20261107
Source: Codex worker c18_u215_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1132 B.

c18_u215: owning real static-array pool .rodata 8039B470..8039B96C (3 scales, 18x7x2 graph coordinates, labels[8][2][2], symbols[8][2], rounds[8][2]) recovers early lis/addi pool base before base ctor and target base+offset table addressing. Pool bytes 100%; text 93.58521->98.85852%, but 1248 vs1244B/index95% prevents retaining per no-regression rule. Pair struct invariant. Explicit byte-stride inline label lookup CSEs combined pointer,1236B/97.89389%, rejected. Best array draft residual round*8 rematerialization at +248, cup/stride colors and EH +60 word00CA00AC vs00C900AC. All pool/split/symbol/bridge probes reverted. Retained approved SINGLETON_INSTANCE macro only; final original text93.58521/EH raw bytes invariant/index100. No native gain; full fallback SHA1OK.

## c18_u217_20261107
Source: Codex worker c18_u217_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u217 RaceDigitLap 80246988: private CopyPosition(DigitPanel*,const DigitPosition&) captures x,y then assigns destination y before x. Improves 99.82258 to 99.90323 with exact 496B and unchanged owned EH164/index12. Residual is x=f1/y=f0 plus y-before-x stores (target x=f0/y=f1 and x-before-y stores), four argument differences. Direct aggregate assignment 98.30645; restrict pointer helper 96.55645 (DigitPosition* versus DigitPanel* destination invariant); scalar y,x helper arguments reproduce99.82258; whole CreateLapPanel helper97.3629; aggregate local initialization90.241936. Keep honest NonMatching. Full coordinator fallback-linked DOL SHA1 exact, native gain0.

## c18_u214_20261107
Source: Codex worker c18_u214_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u214: AI_CalcRivalAvoidance 801EE7F0 safe source-only improvement 94.808914 ->95.828026,1256B, extab97.22222/index100. Declare sdata2 E0/E8/EC/F0 const; leave E4 declaration as in baseline. Scalar output refs do not move early candidate.position r30 (+80 rather than target+28C); whole path/wall inline helper exceeds MWCC auto-inline budget, even with nested subhelpers. Smaller nearest-yaw helper does not restore target fmr. Literal-angle probes can fool offset-based postprocess_sdata2 mapping when instructions have shifted: check original bytes and defined-vs-UND data symbols, not just raw text %. Per-TU numeric renames of literal names leave defined local data and were rejected/reverted. Final tree has no new literals, bridge keys, owned ranges or config changes. Native gain0; coordinator build service request2 SHA1OK.

## c18_u199_20261107
Source: Codex worker c18_u199_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 26 fn / 8128 B.

c18_u199: anon_8020007C_nm1 fn_80201BE8 reaches100% by correcting lbl_803C0064 from extern const char *[4] to extern const char *const[4], consistent with target .rodata. This resolves only two scheduled lwz positions (g_ccClass/name); body reordering and member initialization wrongly move stw early, local snapshot and inline getter/init helpers are invariant. Entire25-function7944B TU unlocked with native C++ destructors. Private declarations suppress synthetic vtables; five full VHolder specializations supply explicit out-of-line cleanup. Three destructor-only views use native member destructors and explicit target vptr assignment so their definitions stay independently placeable. -inline auto,deferred plus reverse source definitions preserves all25 instruction matches and produces target physical order. EH bytes were already exact but old Banner/Gauge holder bridges were cyclically mislabeled: private CountdownPartB->dtor80201E8C, CountdownPartA->dtor80201F1C, CountdownGaugePart->dtor80201FAC correct them add-only; normal3D holder bridges to80080444. Declare target EH/index order and named metadata bridges. Text/ownedEH/index100, no data emission or range change, all25 actual main.elf addresses/sizes exact, source-linked full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65.

## c18_u226_20261107
Source: Codex worker c18_u226_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 428 B.

c18_u226: fn_801F7198 resolves98.92523/432B to100%/428B by changing (unsigned char)(index >= count) ==1 to >0. This preserves the arithmetic unsigned comparison and folds its final srwi into srwi./beq, removing only the extra cmplwi. All later instructions already exact. C-mode unsigned-char producer truth-test regresses93.27103/412B; explicit unsigned local initialized1 and conditionally cleared gives branch-materialization93.64486/428B. Both reverted. Final text428/extab8/index12 all100, Matching flag promoted; no split/pool/EH bridge/alignment changes. Full source-linked DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact; actual ELF text/EH/index ranges equal original DOL. +1native function/428B.

## c18_u223_20261107
Source: Codex worker c18_u223_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 440 B.

c18_u223 Camera_Create8003AACC/440B unlocks99.818184->100 by owning shadow.cpp static string arrays and using direct array references, letting MWCC construct one section-pool base r9 and derived-vtable address r3. Merely defining arrays while retaining explicit base+offset is instruction-invariant. Six strings at offsets0/C/18/24/34/48 produce83B rodata; split802E9D38..802E9D8B leaves existing trailing5B alignment auto, avoiding filler. Shrink lbl802E9D44 from76 to11 and name four following strings; globalize lbl802E9D38 and callback_name->lbl802E9D44 for external RTTI sdata references. Default objdiff text440/rodata83/EH28/index12 all100. Matching source edge true, linked ELF address/size and all owned ranges byte-exact, full DOL SHA1ea30f3b1 exact. +1 native fn440B; no B split.

## c18_u231_20261107
Source: Codex worker c18_u231_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 136 B.

c18_u231_20261107: CalcEarnedCoins near miss was structural. Actual pool 803C3F50..803C4B4C can be restored as typed const arrays without filler. Original CoinRodata parTime ended at offset 0x4F0, not 0x530, making both table copies 0x40 early. Time tables are 16-byte {int course,const char* file,int frames,float time} records, not four floats. Four target symbols of size 0x110 were filename[16] followed by records[8][2]. Pool+records now match 100%; function 928 bytes, extab/extabindex 100%, text objdiff 97.844826/report fuzzy 98.663795, remains NonMatching. Cleared flags are [course][reverse][long]. An unsigned-char inline accessor preserves explicit cup-1 but register/add association remains different. Whole bonus inline extraction worsened allocation/stack order; do not repeat unchanged.

## c18_u238_20261107
Source: Codex worker c18_u238_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 420 B.

c18_u238 DNFlash retry: Check802281F0/420B unchanged100% isolated at80228394 with EH8001BB90..98/index8002A728..734; all sections100 and native linked bytes/full DOL SHA exact. Spawn fresh91.32->93.545 via explicit pointer-walk area loops and inline FindSpawnPoint with forward j<count loop; extra Min-result decrement disappears, primary792vs800. List-builder helper invariant. Remaining table-address folding and GPR webs; shared pool803D0390..803D08A8 already owned by Matching DNFlash_tail, left untouched. Keep Spawn in new NonMatching_nm2. Explicit own EH bridges nm1@83/@84, nm2@168/@169. Native gain1fn420B.

## c19_u5_20261107
Source: Codex worker c19_u5_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u5 BootDispatcher fresh98.645546 ->98.780426. Two real prototype errors: StrPcb_SetIntensityMode takes int (matched StrPcb_Commands.c), restoring caller extsb; DrawText fixed float precedes format (reuse TestMenuPage.h), fixing notice draw scheduling and vararg semantics. Own static ten-pointer .data803F5670..803F5698, exact40B; no text benefit from ownership alone. Typed BootDisplay singleton/member and inline Get factory both invariant; narrow service predicates change signed comparison opcode or add sign extension. Retained original service expression, all EH scores unchanged (extab62.15278/index27.777779), primary6416 vs target6376. Remaining r20/r21 partition, wait extra cmplwi1, calibration base rematerialization, channel-base stores, notice cached guard, conversion-cookie reloc. Singleton NonMatching; no mechanism B. Coordinator full fallback DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; zero native gain.

## c19_u15_20261107
Source: Codex worker c19_u15_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 896 B.

c19_u15: clFlowClass_Update missing selection reload is solved by inline selection(const ClassUpdate*) accessor used for CURRENT selection only: keep int old=self->selection; int delta=input()->delta; self->selection=selection(self)+delta. Fresh99.81191/source3420 ->99.939255/source3424; data52/EH88/index12 all100; conversion double automatically maps lbl806D9B50 once offset restored. Old-value accessor99.71378 creates reload but swaps pointer/old GPRs; delta-before-old declarations invariant. Volatile selection causes source3476/96.65187, rejected. Direct expression selection(self)+input()->delta and explicit current snapshot give99.76636 with current load hoisted before singleton branch. Best retained residual10rows: inputr3/oldr4 vs targetr4/r5, current-vs-delta load order. HonestNM, one function prevents B; full fallback DOL SHA1exact, no native gain.

## c19_u17_20261107
Source: Codex worker c19_u17_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u17: explicit (unsigned char)InsideLastEdge(...) > 0 truth-test restores final mfcr/extrwi./beq and exact1112B; UpdateAndCullZones99.06475->99.802155. Remaining9 rows are zone offsetr5/object walkerr6 versus targetr6/r5. C-mode predicate, declaration swap, pointer-reference helper and reset/zone index reuse invariant; value-pointer count helper regresses99.55036/1116B. Same byte-positive truth-test for both IsReverseRound call arguments improves CourseScene_Load98.7021->98.998764 via scheduling, still3212vs3236B and missing second bool normalizations. C-mode getter and typed zone accessor invariant. Retain only3 source-line changes plus20 add-only EH bridges (compiler IDs after update shift+5); ownedEH100, index99.64286, text99.5124, all other functions100. Complete reversed EH span blocks B; whole TU remainsNM/no native gain. Coordinator full fallback-linked DOL SHA1ea30f3b1 exact.

## c19_u19_20261107
Source: Codex worker c19_u19_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u19 fn_801B4548 semantic audit improves default CLI96.06577->96.57497: signed state-byte declarations (existing VoiceItemEventPrivate precedent) give96.544556; separate timestamp words low-then-high give96.54809; canonical VoiceItemData/ItemVoice arrays give96.57497. Text remains5616vs5656, EH87.5/index83.33333/data0. Stride now targetr24 but source savesr22-r31 vsr23-r31; entry/nearest/index homes, folded map/clip bases, identity loads and scheduling/jump-table residuals persist. Three hypotheses exhausted; singleton cannot B split. New TU-owned private header reuses VoiceItemEventPrivate without editing shared headers. NonMatching full fallback DOL SHA1 exact; native gain0.

## c19_u25_20261107
Source: Codex worker c19_u25_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 420 B.

c19_u25: GpPleaseInit improves 99.352486 to 99.83696 text and 100 extab/extabindex (sizes 2576/468/12). Explicit textEnd declared before ids/x and textList after x/before i restores sentinel=r29, ids=r28, x=r27, list=r26, index=r25, new pointer=r24; initializes sentinel via textList->End().node. New private InsertAt(where,p) inline wrapper restores original iterator temporary stack slots; direct ctor-scope Insert moved them. Source ids++; x+=202 yields target x-before-ids update scheduling. Remaining 21 rows are tween active/end scratch r0/r7 swap only. Bool active, typed sentinel, Enable helper and enable default arguments are invariant; named Append position worsens stack slots. All attempts archived build/w. Remains honest NonMatching; coordinator full fallback build SHA-1 OK, zero native gain.

## c19_u21_20261107
Source: Codex worker c19_u21_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u21: ConvertKana(unsigned short,unsigned short,void*) with unsigned-short buffer stores resolves NameBuf::Add801BF35C81.935486->100%, exact744B and own EH0808000000000000; typed KanaOut* scalarized SP+8 output and removed28B. Generic output restores all target reloads/GPRs. CardEntry cursor0.5f and explicit byte offsets declared X,scale,spacing recover cursor FPRs and all language GPRs (99.36781->99.655174 with own bridges); remaining text x=f30 vsf31 and quote-block scheduling. NameEntry Draw integer selected ternary+ReadNameCharacter void-buffer accessor92.79812->93.30986; Update literals99.37906->99.47834. Separate placement construction/assignment lifts KeyVec init91.91358->92.22222 with unchanged EH. Nine add-only compiler-label bridges make five relocation-only functions exact.59/67 exact, no regressions, owned EH raw-byte exact53->54/64. Entire67-function range has zero legal EH cuts; staysNM, native gain0. Full fallback DOL SHA1ea30f3b1 exact.

## c19_u33_20261107
Source: Codex worker c19_u33_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 3340 B.

c19_u33: late named CoinPopupDetail *popup = detail.p after SetInput fixes SetRect receiver r30->r29 and makes CoinContinue ctor 8021E714 text100%. Blink alpha ternary restores target branch order and FP conversion islands, Update96.737625->99.49133; cc/cup/rev/lng declarations with rev/lng/cup/cc loads plus StripNameSpaces inline helper reach99.60272. Refresh @749->jumptable_804EDDB0 and @751->lbl_806DB0C0 (raw double4330000080000000); offset-based postprocessor otherwise incorrectly picks lbl806DB07C. Digit SetPos inline receiver removes x/y pointer reload, DrawResult81.82258->83.01613. Remaining Update shared webs23/24 vs25/26, one name-buffer base move and coin add order. Whole reversed EH group prevents B; nine exact text functions remain unlinked. Full fallback DOL SHA1 exact; zero native gain.

## c19_u43_20261107
Source: Codex worker c19_u43_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u43: EnmyFaceEffect destructor improves98.40741->99.111115 (540B) by extracting the complete sLoaded/global palette release block into static inline ReleaseFacePalettes. Final slots loop becomes exact; remaining model walker/slot pointer and palette index/cursor homes differ. Six destructor hypotheses exhausted. UpdBanana remains99.81328 after six scope/capture/helper probes; const Vec3c::RotationMatrix member form is instruction-equivalent and preserves all other function/section scores with the palette helper. Explicit pooled BSS probe regresses destructor85.71111/UpdSlide94.04145 and loses generated initializer, so no B split/flag change. All14 functions present, no regressions, no native gain. Full coordinator fallback-linked DOL SHA1ea30f3b1 exact.

## c19_u47_20261107
Source: Codex worker c19_u47_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u47 AI_UpdatePerFrameState: baseline97.34122 ->97.40878. Whole-body static-inline wrapper does not inline at production limit (32-byte public thunk), discarded. Enclosing pair declaration scope leaves pair GPR cycle invariant, but moving nearest distance declaration before main coordinate locals gives target f31 (97.375). Sharing driver/record/cursor/index across both disjoint rank scans yields97.40878, same2376B strong text and exact24B owned EH. Existing conversion-cookie wrong relocation lbl_806DA3E0 vs lbl_806DA400 persists; no singleton/pool pattern applies. One-function TU has no B cut. NonMatching retained; coordinator build service SHA-1 OK, 0 native gain.

## c19_u58_20261107
Source: Codex worker c19_u58_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 3112 B.

c19_u58: fn_802128F4 resolves99.86264->100 with inline const KartRender::GetSpeed() plus static inline MultiplySpeed(float factor,float speed){return factor*speed;} at both scaling sites. Getter alone99.94505 fixes speed/conversion scratch ordering but leaves factor/result coalescing; product helper resolves remaining4rows. Native text1456/ownedEH24/index12 all100 after add-only @92/@93 metadata bridges. Existing KartPos weak empty dtor copy discarded; final source-linked ELF ranges and full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Matching promotion; no pool/split/flags/shared-header changes. Gain1nativefn1456B.

## c19_u62_20261107
Source: Codex worker c19_u62_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1436 B.

c19_u62 fn_801FB778 unlocks99.387184->100%. Actual fn801D9B70 second arg is unsigned char; correcting declaration alone is invariant. Receiver-only static inline UpdateKart(void *kart), with singleton lookup and dir!=0 normalization INSIDE helper, moves receiver load before null branch and gives singletonr4/kartr3 exactly. Prior two-argument helper/direct-expression negatives do not imply receiver-only boundary is closed. Text1436/EH44/index12/data40 all100. Existing alignment/EH settings reused, only Matching flag promoted. Source-linked ELF symbol and all owned ranges exact; full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. +1native fn1436B.

## c19_u72_20261107
Source: Codex worker c19_u72_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u72 EnemyRun_BaseInit: declaration order row,column,output,right,n with column assignment inside outer loop fixes all matrix-loop colors (n=r5,i=r4,row=r9,column=r8). Move row+=4 into body before n+=4 to restore target outer scheduling. Text99.08->99.36616,1300B; owned EH176B/index12B100. Only target mr r9,r29 vs source addi r9,r31,0x70 remains. This-pointer cast and pointer-to-float[4] row type are invariant; reusing mutable row for copyback loses long-lived r29; rotateY helper swaps saved FP homes without fixing base. Retained simpler declaration/scope change, no metadata edits, NonMatching. Single function precludes B; final fallback DOL SHA1 exact.

## c19_u77_20261107
Source: Codex worker c19_u77_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 18 fn / 16760 B.

c19_u77 ranking_display: target panel variant arithmetic at 801D2734..2754 computes flag>=2, not previous flag<2. For flag0/1/2/3, ((flag|~2)-((flag-2 unsigned)>>1))>>31 gives0/0/1/1. Correcting comparison improves fresh91.104164->91.464745, restores2496B and extabindex100; data100/EH91.581635. Genuine weak compiler-vtable emission using inline undefined virtual declarations does not restore persistent name-table/vptr pool (text invariant, extra data); reverted. Inline unsigned comparison helper invariant. No new pools/bridges/flags; singleton function stays NonMatching, fallback DOL SHA1 exact.

## c19_u78_20261107
Source: Codex worker c19_u78_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 2244 B.

c19_u78 Menu801F0CC0: native __rlwimi alpha insertion has matched FlowPanelUpdate.cpp precedent. Replacing WithAlpha bitwise OR and routing 1244/140C through it improves 1244 93.10526->95.04386, 140C93.08772->96.27193,19C891->95.3125,1AC890.96875->97.34375,20A093->95.89189,21C889.40741->92.950615; all six now target-sized. No other score/EH regression. Indexed strength-reduction-off loops, C++ member conversion, Gray getter/packer and TintSprites helper fail remaining register homes. Global/static float array ownership 804E4C28..4FA8 improves two input handlers but regresses1664; revert. Extern typed aggregate regresses. Entire25-function reversed EH group remainsNM; full fallback DOL SHA1exact/nativegain0.

## c19_u79_20261107
Source: Codex worker c19_u79_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1228 B.

c19_u79 ItemBoxConstruct8016D2D0/1228B unlocks99.93485->100 by seven independent file-static const char strings and direct references, replacing external base+offset pointer. Native section pooling fixes pool-highr7/base-vtable-lowr3 scratch residual; previous typed aggregate was not equivalent. Own rodata8036D588..8036D620 and split original D5A8 size78 into deletion/create/model/fire/drop strings at20/40/60/70/80; all seven exact-length arrays. Export D588/D594 for RTTI and D5A8 for external destructor via add-only existing TU key. Source rodata149B naturally links to exact152B including trailing3B alignment; no filler. Text1228/EH124/index12/rodata152 report100 and linked ranges byte-exact, source edge true/full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Matching,+1nativefn1228B; no B split.

## c19_u85_20261107
Source: Codex worker c19_u85_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u85 TaMode_Init94.20946->94.22973 (no inferred pools94.40034->94.42061): declare float bonus,time before assigning time=params[-6].timeLimit then bonus=params[-6].lapBonus. This preserves f2 time/f1 bonus and restores target time-before-bonus loads; exactly two emitted instructions change, all other instructions unchanged. Function-wide typed tables pointer regresses93.61487; explicit named constructor-argument locals and mutable ghost/data views byte-invariant. All rejected probes reverted; native2384vs target2368, EH94.897964/index95/data50 unchanged. BATTLE pool belongs to FrameUpdate; singleton function prevents B. Retain NM; full coordinator fallback DOL SHA1exact, native gain0.

## c19_u71_20261107
Source: Codex worker c19_u71_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u71 NamCamFlow partial: native shared rodata 803BDF20..803BE56C (1612B, 100%) restores hoisted pool base, raising 36D0 68.62595->90.64886 and ctor3BD8 84.31047->99.62455. Open external pointer arrays 806DA94C/806DA9EC restore target HA/LO loads. Same-family auto_inline off around3198 removes unintended inlining in2BC8; inline border/capture-copy helpers plus a context snapshot raise2BC8 82.63441->99.6371 and restore frame120/size1488. Draw43F8 plain literals16/12/305/140/.8/1.0666667 make FP exact; association halfWidth+x / halfHeight+y yields99.75096, leaving FIFO integer homes. Six bounded approaches for >=99 functions exhausted;32BC member-call probe invariant97.38314. All17 exact drafts unchanged. EH aliases added only within own existing key; whole TU remains indivisible NonMatching, zero native gain. Coordinator full fallback DOL SHA1 exact.

## c19_u87_20261107
Source: Codex worker c19_u87_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u87 fn_8018E6FC improves97.35459->98.890305 with text1568/EH8/index12 unchanged. Explicit matrixOffset declared after logical int i and incremented before i gives target index r30/offset r31 (97.43112). Extract final loop into updateBillboards(o), locals int k; ViewBillboardParticle*q; unsigned particleOffset; explicit offset increments before k gives ENTIRE final loop exact,98.890305. Operand reversal and named cached random floats invariant; moving particle lookup inside updater invariant; whole-loop helper alone98.418365. Flatten updater body invariant. Function-scope point/p/q declarations98.813774 (q remains9); freeParticle output parameter invariant; point-index helper98.85204. Residual: matrix loop lfs/li/li vs li/lfs/mr, point/free q target9/7 vs7/9, affine FP homes. Single function, remainsNonMatching; full fallback-linked DOL SHA1 exact. Read actual archived c16/c18 HANDOFF+worker.patch under archive/<batch>, not absent archive/drafts.

## c19_u96_20261107
Source: Codex worker c19_u96_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 252 B.

c19_u96 CoinChallengeUpdate: ABI-identical CarObject_ApplyInput declaration with floats followed by unsigned char started, unsigned-char IsRaceStarted, and direct call CarObject_ApplyInput(self->car,input->steering(),accelerator,brake,IsRaceStarted()) restore target evaluation order and remove redundant r3->r0->saved copy:98.24586->98.5221 and 1452->1448B, EH/index100. Moving count-display sprites local to inner scope invariant. Natural SetCoinSprites(CoinSprites*,int) helper raises98.78453 and restores all persistent self/before/after/sprites/tens GPR homes. Only clamp mr/cmp scheduling and first slide-loop counter/cursor r27/r30 exchange remain. Best source retained NonMatching; full fallback DOL SHA1 exact; no native gain.

## c19_u91_20261107
Source: Codex worker c19_u91_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u91 RaceDigits: inline scalar x/y getters inside a position-copy helper solve the first constructor copy load order at +31C/+324, lifting99.84561->99.922806. Retained TU-local RaceDigitsMatchPrivate.h uses canonical DigitPosition/DigitPanel types via static inline DigitPositionX/Y and SetDigitPanelPosition; no shared-header edits. Member CopyFrom and scalar const-float refs invariant; reference-return getters cache table across allocation96.53684; x-only getter99.85263 changes FP homes; explicit copy ctor99.82807 with anonymous relocation collision leaves original four load differences. Final only +438/+440 y/x load swap remains.13 add-only own-key bridges restore owned EH/index/data100 and all six other text functions100. Original reversed EH group prevents B; no singleton or unowned section-pool mechanism applies. Physical text order remains a future promotion issue. Full fallback-linked DOL SHA1ea30f3b1 exact; zero native gain.

## c19_u101_20261107
Source: Codex worker c19_u101_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1344 B.

c19_u101 unlocks R-button 802055F4/8020579C (424/920B): TextRow(row,origin){return row+origin;} around ONLY the text row sum fixes sole reversed fadds, unlike prior whole-Y helper. Complete DrawButtonSprites(receiver) inline lifetime resolves layer/color GPR swap and narrows ResCtrl EH to target span0x46. First sprite X uses offset-first multiplication, second X scale-first; both Y offset-first. Local axis helpers preserve scale reloads. TU-private YesNoButtonR declaration with undefined _key3 first suppresses extra vtable; add owned @126/@127/@196/@197 EH bridges and order Update,DrawLabel,weak ResCtrl dtor. Text/extab/index100, source-linked fn addresses/sizes exact, full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; +2 native functions/1344B.

## c19_u104_20261107
Source: Codex worker c19_u104_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u104 MsgPopup::Tick direct baseline99.49794 ->99.547325, unchanged972B primary/owned EH, by for-clause dy+=30 before i++. It restores stride-before-dy scheduling. Counter-parameter98.860085, loop-local counter99.45679, derived integer30*i99.485596, inline text accessor99.49794 invariant, inline offset helper99.485596. Remaining index/stride r28/r27 vs targetr27/r28 and index-zero mr vs li; two table relocation names remain. Six hypotheses exhausted; keep honest NM. No flag/range/bridge edits; fallback full DOL SHA1 exact, zero native gain.

## c19_u107_20261107
Source: Codex worker c19_u107_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1284 B.

c19_u107 RaceDigitUpdate fn_80246484 promoted98.89097->100 (1284B). Canonical RaceDigitList/RaceDigitIterator Begin/Finish and nontrivial copy restore sentinel r27 across panel update and sentinel+4 restart (98.94081). BeginHidePanel(DigitPanel&) with null guard at owner call site recovers almost all GPR homes (99.87539); function-scope cullIndex fixes cull (99.9377). Reference ShowHudSprites(DigitHud&,int) inline renderer recovers render counterr30; declare float x before y but compute y first thenx to recover target y=f30,x=f31 and100. Owned EH8/index12/data32 all100. Add game/RaceDigitUpdate to DATA_ALIGN4_TUS for jump table804EEAA4. Matching source object selected in main.elf; actual function80246484/1284; full coordinator DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Native gain1/1284.

## c19_u108_20261107
Source: Codex worker c19_u108_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u108 CollisionUpdate 8019B080:87.22083->88.14792. PlainDot under existing fp_contract-off needs named scalar x/y/z products before addition; a single return expression contracts after inline, while scalar product locals recover exact target dot instructions (87.73646). Typed CollisionMatrix transform plus inline member Scale(float) and Transform(const Vec3&,CollisionVec&) remove extra f21 save, restoring 0x2A0 frame and f22-f31 saves; EH improves88.15789->90.789474. By-value nontrivial vector Transform fails auto-inlining (76.8625); reference-return directly used as raycast arg is identical to void output helper. Matrix multiply indexed-store blocker persists; GPR save range and EH PC span still nonexact. No flags/ranges/bridges changed; full fallback SHA1 exact; zero native gain.

## c19_u117_20261107
Source: Codex worker c19_u117_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 912 B.

c19_u117: YesNoButtonL Update80205DCC matched912B. Separate const-button axis helpers restore the two scale reload pairs. One background-draw inline helper enclosing color/layer computation resolves r29/r30. Fixed X uses offset*scale; sliding X helper owns scale*(base+slide), resolving f6/f7. ResCtrl must be local to the background helper: target EH lifetime is PC5C..174, not through Update end36C. Split at8020615C/extab19024/index29930; Update .text and owned EH/index100%, main.elf ranges and DOL SHA1 exact. DrawCredits remains99.77579% (f29/f30 swap and row-add order), retained verbatim in NonMatching _nm2.

## c19_u125_20261107
Source: Codex worker c19_u125_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u125 retry carobject: constructor 8019E20C improves66.74848->85.87627, TU text86.88794->94.226456, while all 11 exact functions stay100 and affine helper stays85.29032. MatrixMultiply needs flat float output[16], independent output row index k+=4, and sum=a*b+sum statements: this recovers two-row unrolling (source primary ctor1964 vs target1972). Ground-query local has target EH cleanup at sp+8 and only4 bytes before matrix scratch sp+0xC; modeling as a one-float GroundHeight with real empty dtor (bridge to dtor_80036E40) fixes sp+8 drift caused by InitVec local. Ordered InitVec::Set and linear identity zero loop recover store order. Named const lbl_806D96D0/96D4 references in constructor prevent postprocess_sdata2 retargeting initial zero to g_gameMode and one to zero when offsets differ. Residual: initial bool normalization has missing neg/or/srwi versus extrwi (-8 B); matrix operand/scratch and destination register homes, retained stack pointer r30, later zero/one FP homes, owned EH and existing physical source function order. Affine Vec3-result invariant85.29032; staged outputs59.225807/84.16129 and direct cached-output40.322582 rejected. No new asm/padding/codegen flags. Entire reversed extab group cannot split; keep NonMatching, native gain0. Final coordinator full fallback build DOL SHA-1 OK.

## c19_u105_20261107
Source: Codex worker c19_u105_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u105: STLContainer_DisposeRecursive 80038A00/968B reaches 100 from 99.02892 by qualifying only DisposeBranch(STLTree*, STLNode *__restrict node). Reversing helper arguments and node-member helper boundaries were invariant; restrict on the outer node or local tree alone also invariant. All 11 symbols plus text1568/EH84/index72/ctors4/BSS32 compare100. However Matching full link fails: emitted sinit ends up80038F08 instead of80038934, other10 funcs76B early (failed SHA bcaf540602901f6b5ca2461508bcf00f3b00765f). defer_codegen leaves sinit last; explicit inline instantiations put it first but inline/drop other required functions. Whole reversed EH group prevents B. Retain only one-line restrict change, original NonMatching flag, final fallback-linked SHA ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65; native gain0.

## c19_u130_20261107
Source: Codex worker c19_u130_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u130 TryArmInit: separate float ax,ay,az declarations, then evaluate az=axis.z; ay=axis.y; ax=axis.x. Preserves homes ax=f30/ay=f31/az=f29 while restoring target Z/Y/X pre-sin load order; exactly two primary instructions change. Fresh93.86131 ->93.89051; text1636 vs1644, EH98.4375/index95 unchanged. Reverse declarations alone swaps ax/az homes. Quaternion y/z/x/w and w/x/z/y rank probes regress; explicit NR constants regress93.532845 (both) /93.338196 (three only), subtraction-only reference helper93.83698. All rejected changes reverted. Existing postprocess_sdata2 retargets lfd f2 at source+328 to lbl_806D2808/addend0 instead of target lbl_806D2810; direct ELF relocation confirmed, report for future promotion (tools unchanged). Singleton TU staysNonMatching; final coordinator fallback DOL SHA1exact, zero native gain.

## c19_u147_20261107
Source: Codex worker c19_u147_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u147 PhysicsState_KartCollisionCheck 801ECB88 fresh92.23256 ->99.360466. Plain exact float literals for zero/one/threshold and yaw constants restore five missing yaw reloads, exact1376B size and97.52907%. Delay position aggregate initializer until after angles.set =>99.273254; copy-constructing movement regresses93.875, reverted. Memberwise movement copy instead of set fixes f8/f9 =>99.360466. Residual only immunity byte r9 vs target r5 and beq vs bne/b branch island. Explicit byte if/else and byte-return helper fold test; int-return helper98.77907 coalesces zero into r6, rejected. Owned EH still284..36C/464..528 vs284..294/36C..528 and anonymous symbols unbridged. No A/B, stays NonMatching, final coordinator fallback-linked DOL SHA1 exact.

## c19_u146_20261107
Source: Codex worker c19_u146_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u146 CalcEarnedCoins: flat cleared[32], scalar CourseClearIndex(course,reverse,long){return long+(course*4+reverse*2);} passed to separate unsigned-char IsCourseCleared(index) lifts raw objdiff97.844826->98.534485 (928B), all rodata/EH100. Pointer-based flat accessor97.13362; splitting long from course/reverse across two helpers98.405174; reuse finished rank-loop i as mode is byte-invariant. Retain best separate-mode draft NM. Call sites do not provide argument; no basis for speculative receiver/signature change. Global volatile working-GPR one-low residual persists; clear index association still differs. Full fallback DOL SHA1 exact; no native gain.

## c19_u136_20261107
Source: Codex worker c19_u136_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u136: SpecialFaceMesh_Raycast TU stays NM. Cache plane normal and preserve rounded endpoint products, move vertex decrement into loop condition, normalize with x=y=z assignment: Segment fresh85.98947 ->95.357895 (1132/1140 B). Reuse canonical WarpZoneInsertPrivate WarpString wrapper instead of bare shared-storage message: InsertFill97.65734 and Reserve99.90196; source-before-end declaration plus generic backward-copy helper gives InsertFill97.84965. -rostr and owned .rodata80311BF8..80311C30 compiler exception descriptor + global @349 bridge produce Reserve100 and InsertFill97.88461. Approved singleton macro retains factory100. Add-only new EH aliases avoid c16 collisions after generic-copy boundary changes deferred emission; append weak __dt__10WarpStringFv to own EH order lists. Final text97.027565/EH99.587906/index99/rodata100; seven prior exact functions preserved, eight now text exact, but Raycast/Segment/Insert residuals and reversed EH grouping block native gain. Physical Segment/holder order and remaining anonymous sdata2 literals also preclude blind promotion. Full fallback-linked coordinator build exit0, DOL SHA1 exact.

## c19_u158_20261107
Source: Codex worker c19_u158_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u158 AI_CalcRivalAvoidance: separate inline reduceRivalAngle/raiseRivalAngle taking angle,turn,bound by value moves normalized angle into target f3, improves95.828026->96.0828 with original1256B. Keep E4 mutable; const E4 combined gives96.48089 but1252B. Candidate PhysicsCollisionVec member type leaves text invariant; typed populateCandidate direct scalar stores93.191086. All rejected variants saved build/w, reverted. Add @170/@171 own EH bridges, preserving existing @159/@160. extab97.22222/index100 unchanged; weak dtors unchanged. Early position address +80 instead+28C, normalize bound/turn loads, amount FP homes, missing waypoint fmr and distance fmr remain. TU stays NM; service request1 DOL SHA1OK; native gain0.

## c19_u161_20261107
Source: Codex worker c19_u161_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u161: clFlowTaPlease_Init93.58521->99.85531. Reconstructed c18 real static pool, then unsigned round index alone removes extra round*8 rematerialization (signed cup remains sufficient). Inline SetTrackLabels(C8TaPlease*,int,unsigned) reads sprite each call and restores label strides r28/r27; sprite-pointer helper caches sprite and regresses. Own .rodata8039B470..8039B96C: scales12B, graph18x7x2 floats1008B, label/symbol/round ids128/64/64B, all100. Add own @71/@72 and taScales bridges. Text1244B/EH212/index12 exact sizes; only8 GPR operand differences remain (original cup/round r25/r26 swap and later cup*8 r27 vsr26). Six hypotheses exhausted; retain NM improvement, no B singleton cut. Full fallback DOL SHA1ea30f3b1 OK; zero native gain.

## c19_u163_20261107
Source: Codex worker c19_u163_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 21 fn / 10836 B.

Update_Inner 8005FA34/380B reaches 100% by using ListIter<void*> for both box and responder cursors, retaining raw sentinel pointers and original direct head loads. Only a typed responder cursor swaps outer/inner homes (99.210526%); typing all sentinels promotes invariants instead (98.89474%). The paired typed cursors preserve r31 for boxes and r30 for both responder traversals. All 11 owned EH payloads, sizes and relocation targets remain exact. Four other residuals are unchanged; no A/B promotion is possible while the tail base dtor early EH entry binds the reversed group. No new flags, ranges, bridges, padding or shared-header edits.

## c19_u164_20261107
Source: Codex worker c19_u164_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 436 B.

c19_u164 fn_801C9288: isolate external +/-offset constants on the ORIGINAL hoisted-array source shape. This alone improves exact-command baseline86.98052 to91.22565 (text2380 vs target2464B); extab93.269226/index91.66667. Uses lbl_806D9D38 for +/-0, lbl_806D9D40 for +/-10; unary negation restores fneg. Retained source, NM, no native gain; full build DOL ea30f3b1 OK. Byte-base/stride association83.06007 and mixed literal-positive/external-negative88.16558 rejected. c16 combined similar constants with structural changes and missed this standalone improvement. Table range8049AE70..8049AFD0 already belongs to Matching clFlowRound.c, so do not acquire it from that TU under auto-pool permission. Residual: hoisted bases, case1 pos/anim GPR swap, extra fmr versus conditional reload, EH PC offsets.

## c19_u172_20261107
Source: Codex worker c19_u172_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u172 Scene_8015B790: owner-approved real local constant-pool ownership is discriminating, unlike prior external ViewerPool/helper probes. Claim .rodata 80367F68..803682AC and define 12 filename strings, typed 14-record table (resource is filename pointer), float steps[3], real class names and COURCE %03d format. Compiler creates shared r31 base and exact +10c/+304/+338 accesses. Refine original 204-byte table to1F8 plus actual viewerSteps at8036826C; refine class-name/format symbols at8036828C/803682A0. Text96.12937 ->98.496506,1144B; EH/index/836B rodata100. Last4 alignment bytes803682AC..803682B0 stay outside owned range; no filler. Residual only icon index/base r4/r0 vsr0/r4 and icon load before f6/fneg. Direct indexing and inline DrawViewerIcon(index) are instruction-invariant. Retain simpler H1 NonMatching. Full fallback-linked build SHA1 exact; native gain0.

## c19_u181_20261107
Source: Codex worker c19_u181_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 732 B.

c19_u181: fn_801CDF10 unlocks98.74317->100% by ordering g_rendererGateFlag=1 BEFORE GetPlayerCharacter()->SetCharacter(g_characterId) in EnterRace. Although target stores the character before the gate, MWCC schedules these independent stores that way from gate-first source. This also changes character r4->r0, player base r3->r4, gate constant r0->r3 and puts li r3,-1 after gate store. Byte-width setter parameter probe was invariant and reverted. Final text732/extab8/index12 all100; existing bridges suffice; only source statement order and Matching flag changed. Full source-linked DOL SHA1 exact; actual ELF801CDF10/732 bytes verified. Native gain1/732B.

## c19_u184_20261107
Source: Codex worker c19_u184_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1916 B.

c19_u184 fn_801ED798: preserve external nontrivial constants but use literal 0.0f/1.0f to restore target frame270, f16-f31 saves and exact EH PC interval. Reverse identity chain to m00=m11=m22=m33=1 for target descending stores; explicit nine-field frame export removes indexed loads. Fresh87.84991 ->97.94372, primary2132B exact. Final raw/processed ELF check verifies all7 literal relocation sites map correct bits to UND lbl_806DA42C/450; unlike c16 all-literal probe no incorrect remapping. Add @244->etb80016CD4/@245->eti80028B50 gives owned EH/index100. Row-local matrix operand caching regresses86.51407 by hoisting right matrix/interleaving accumulators. Remaining matrix operand loads/FP and index/row/output GPR homes, corner scaling temps and late lbl_806DA43C load. Singleton TU remains NonMatching, no rescue cut; coordinator full fallback-linked SHA1 exact.

## c19_u185_20261107
Source: Codex worker c19_u185_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 708 B.

c19_u185 unlocks ItemShowcase ctor fn_8020B234 97.54237 ->100%, 708B. Semantic root: fn_8013BE98 takes int item; prior void prototype lost the implicit r3 ID. Correct prototype and xf=fn_8013BE98(id) fixes r0/r3. Three separate static ShowAnimCommand arrays (9/19/11 records, 44B each), referenced directly, activate compiler shared .rodata base optimization: exact prologue lfs/lis and addi r30 plus addi r7,r30,0. Cached pointers/aggregate forms in c5/c18 did not. Own 803C2E50..803C3504 only; label extents18C/344/1E4, leaving existing four trailing alignment bytes in auto range. Bridge ...rodata.0->global:lbl_803C2E50, sparkleB->lbl_803C2FDC, sparkleC->lbl_803C3320. Text/EH/index/rodata all100; source-linked final DOL SHA1exact, actual ELF text708/extab104/index12/rodata1716 ranges exact. Native gain1fn708B.

## c19_u189_20261107
Source: Codex worker c19_u189_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 672 B.

c19_u189: fn_8021B68C unlocked from98.83929 to100%/672B. Explicit TeamIconRow cursor declared after icon, advanced sizeof(int), aligns cursor r30 and result/icon r31; initialize slot index before cursor for exact li/mr order (99.940475). Mirror SlotTeam in TU with int syncRole loaded before equality to cached role to fix final cmpw r0,r27 operand order (100%). Update-only opt-in declaration order puts existing undefined Draw override before Update; inherited vslots unchanged, duplicate32B vtable suppressed. No split/data/EH-map changes. Promote Matching; coordinator request1 full build SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK. Linked fn at8021B68C size672; +1 native fn/+672B. Prior archived attempts are c17_u120 and c18_u200, not same-number u189.

## c19_u192_20261107
Source: Codex worker c19_u192_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 4076 B.

c19_u192 fn_80242E80 closes99.4->100,500B. Reusing loop index raises99.56 but remains wrong. Full inline LoadRivalResources plus outer declarations int mode,cup,round,i gives99.56 with whole marker loop exact; declare int *p BEFORE those values, assign p inside item loop, and all item registers become exact (i31/round30/cup29/mode28/p28). This combines c17 resource-phase boundary with a discriminating pointer-declaration lifetime change. Existing EH8/index12 already exact; flag-only Matching promotion, no ranges/maps/data/header changes. Source-linked main.elf function80242E80/500 and both owned EH ranges byte-identical to original; coordinator full DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. +1native/500B.

## c19_u197_20261107
Source: Codex worker c19_u197_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 636 B.

c19_u197 unlocks CoursePropCtor8016E568/636B97.32704->100. Four independent file-static pointer tables normal/reverse/long/long-reverse plus actual RTTI hierarchy and vtable records, referenced directly (no retained external base local), make CW emit native ...data.0 pool base inr31 and restore resource-r29/model-offset-r28/counter-r27/self-r30; intermediate632B98.74214. Inline zero-argument SelectCourseProps() returns the arrays and restores targetr0 merge then mrr31,r0,636B/EH100; pre-split99.559746 only relocation identities. Own data80491150..804911C4, split original80-byte pointer blob into28/28/12/12 symbols; six data bridges plus own @146/@147 EH aliases. Final text636/EH52/index12/data116 all100; actual main.elf ranges exact, source edge true, DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Matching,+1native636B. No filler/DATA_ALIGN4/weak dtor/new flags. Combination of native independent objects and selector return boundary resolves earlier external aggregate/helper dead ends.

## c19_u210_20261107
Source: Codex worker c19_u210_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u210 ExplosionTumble_Init: scalar LengthSquared(x,y,z) with yy=y*y;xx=x*x;zz=z*z;return zz+(xx+yy) restores early Y-square and improves89.89171->89.99078, same1736B. Add own @279/@280 EH bridges, owned EH48/index12 remain100. Restrict Dot/Scale/Subtract gives90.36175/1740B but shifts EH+4 and still reloads up; scalar combined Project gives90.156685/1724B and EH-12; both rejected. Initial X/Z load order, FP homes, projection reloads and quaternion q.z/q.y evaluation remain. Singleton cannot use B; staysNonMatching, final coordinator fallback DOL SHA1 exact, native gain0.

## c19_u213_20261107
Source: Codex worker c19_u213_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u213 PhysicsState_WallCollisionCheck 801ED0E8 fresh56.565422 ->63.242992 using a TU-private flat16 matrix with flat copy ctor, nested applyYaw/operator*=, separate float accumulator and n+j product index, then native aggregate assignment. This recovers eight-wide initial copy grouping and two-row multiply unroll without volatile matrix storage. EH86.53847 ->88.46153 and index61.11111 unchanged; cleanup locals18/24/30/3C/dtor_80036E40 intact. Return-by-value canonical matrix46.390186 adds fourth matrix temp; in-place result[k] += terms54.32944 causes memory roundtrips. Final1768B/frame1E0 savesf22-f31/r27-r31 versus target1712B/frame170/f30-f31/r22-r31. Matrix input hoisting and cross-raycast FP liveness remain open. Singleton NM; no flag/split/bridge changes or native gain. Three approaches capped; all drafts under build/w/c19.

## c19_u221_20261107
Source: Codex worker c19_u221_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u221 retry CardSetupFlowInitial fn_8024AD8C: restrict ownership of self plus state-before-duration snapshot makes both opening fade blocks exact, improving 95.878174 to97.96954 at same788B. Remaining target global-path li0,5/li3,1/stw lbl_806D19B8/lwz list versus source li0,5/li3,1/lwz list/stw lbl. Restricted inline BeginFade with unrestricted main regresses93.29949; unrestricted inline PrepareCardScene under restricted main stays97.96954. Best minimal source retained NonMatching. Owned raw EH176/index12 unchanged/exact; existing extra weak entries and anonymous EH symbols left unchanged. Single-function TU cannot use mechanism B. Full coordinator build DOL SHA1OK, fallback linked, zero native gain.

## c19_u219_20261107
Source: Codex worker c19_u219_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u219 DNFlash Spawn: direct objdiff baseline93.545 ->94.395 (final coordinator report95.45) without native gain. Flattening FindSpawnPoint fixes point/start/tries/list callee-saved allocation (93.920); declaring n before col fixes r8/r9 list-builder swap (94.395). Explicit FlashPart** slot removes target-required reload/index instructions and regresses to90.340; reverted. Postincrement threshold spelling is invariant. Retained primary792/target800, aggregate table address folding instead of addi/lfsu/lfsx and final free-slot address/part registers remain. Pool803D0390..803D08A8 already belongs to Matching tail and was not taken. Add-only own EH bridges @148/@149 restore extab/index symbol names, sections100/95. Full DOL SHA1 OK with honest original-object fallback; no flag/split changes.

## c19_u220_20261107
Source: Codex worker c19_u220_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 796 B.

c19_u220 ItemWnd::Setup 8021F508 unlocked from fresh92.41708 to100%/796B. File-static real pool 803C6610..803C6CBC (floats, 13 ItemPose rows, existing aggregate defaults and strings) restores MWCC common .rodata base+offset addressing and table-base rematerialization; extern struct view could not. Residual r0-vs-r3 compare was a semantic prototype defect: canonical CourseTables fn_8013BE98(int id) consumes itemId, despite family header incorrectly declaring void. Private C++ overload + per-TU fn_8013BE98__Fi bridge avoids shared-header changes. Bridge owned @183/@184 EH names and pool array/string symbols, split pose/string sublabels, promote Matching. Owned text/EH/index/rodata100, source-linked function at8021F508 size796, full DOL SHA1 exact. Preserved existing zero aggregate templates are real named target data; no filler objects added.

## c19_u225_20261107
Source: Codex worker c19_u225_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u225 retry fn_80225C2C: fresh baseline94.46907 ->94.62371, 776B. Plain verified 320.0f/1.0f literals ONLY in ResCtrl Show and scaleY recover exact target +16C..19C f2=320/f1=1; external scaleX1.25 retained. Inline SetupJoinBox formal argument ordering is invariant; inline ResetJoinState field initialization boundary also invariant. Entry +C..80 still differs in zero r5/r6, derived-vptr r4/r5, nextJoin load/result r4 vs r3/r0 and scheduling. Three hypotheses exhausted; singleton stays NM. Owned EH raw prefixes unchanged; final fallback full DOL SHA1 exact. Beware postprocess_sdata2 can retarget an incorrect initial literal to target name; verify literal values directly. No new maps/flags/ranges.

## c19_u246_20261107
Source: Codex worker c19_u246_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u246: DNStartDino Spawn 80229998 reproducible direct objdiff baseline is 89.442955% (584 B emitted vs 596 B target), despite assignment summary 90.44%. Three scalar snapshots sx/sy/sz of DNStartDino_tail_data_804EE0E0 before position writes improve to 90.020134%, same extab 100% and extabindex 91.66667%. Aggregate copy adds stack traffic; while is invariant; infinite loop with guarded return worsens; inline SetEmberPosition with float scale arguments ties scalar result. Remaining target top-tested outer loop and FP loads/registers not recovered. Single-function TU cannot rescue exact subsets.

## c19_u240_20261107
Source: Codex worker c19_u240_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u240 CourseData_LoadPathTable800ABAE8: fresh89.09638 ->94.156624,664B. Real independent file-static filename strings plus nine-course [2][2] filename/source arrays and actual diagnostic/type-name strings activate ...rodata.0/r31 pooling: exact prologue and asymmetric memory selection, unlike c16 typed external pool. Separate inline LoadFileData(self,file) yields small additional improvement. Own .rodata803285C0..80328B7C; filename table144B at8032890C, source table288B at8032899C, diagnostics80328AE8/AF4/B38/B58. Full section rodata/EH/index100; final string endsB7B with normal one-byte alignment toB7C, no filler. Add-only own @93/@94 and data bridges. Remaining memory-fixup r22/r23 swap, reversed file selector island and file-loader GPR homes. Three hypotheses exhausted; keep NM singleton, no B cut/native gain. Coordinator full fallback DOL SHA1ea30f3b1 exact.

## c19_u253_20261107
Source: Codex worker c19_u253_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u253 EnemyFace 8022ACE4: current existing -O4,s baseline reproducibly 90.36042% and already retains target CTR loop. Explicit independent texture/palette/resource/TLUT cursors replace indexed loader accesses and raise text to 95.80212%; reverse cursor declarations with target init order, p-before-uv declaration and inline two-float FIFO writer reach 97.130745%; per-vertex reused tu/tv reaches 97.24381%. 1132-byte text, extab/extabindex 100%; rodata unchanged 99.74425%. Residual: four loader pointer advances reordered and vertex FP webs/UV scheduling differ. Three structural hypotheses exhausted, retained honest NonMatching draft; no native gain. Full coordinator build DOL SHA-1 OK.

## c19_u254_20261107
Source: Codex worker c19_u254_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u254 HudFlow24Ctor 80245C1C: fresh92.67376 ->99.82269/564B. Static separate 13-pointer language rows plus genuine RTTI/vtable records and TU-private manual-vptr root (CoursePropCtor precedent) restore data-base r31, this r30, manager/character r29, frame20 and all instruction words. Initialize vptr through first-member initializer helper, retaining real new/VHolder cleanup. Explicit isJapanese()==0 ternary is crucial: !isJapanese(), positive ternary and inline early-return selector all choose Japanese-first; ==0 yields target bne/international-first. Add own @77/@78 EH bridges and __dt__13HudFlow24RootFv->dtor_8021617C; owned92/12 EH/index100. However owning data804EE7C8..804EE854 fails DTK cyclic order HudSelectionUpdate -> HudSelectionCreate -> HudSelectionDestroy -> HudFlow24Ctor because Update already owns later jump table804EE854..870. Scope does not permit changing those Matching TUs. Reverted split/symbol edits; retained genuine140-byte local pool draft NonMatching; no native gain. External aggregate pool regresses91.64539 and rematerializes base. Future unlock likely needs coordinator-approved family co-residence, not more regalloc probes. Full fallback DOL SHA1 exact.

## c19_u270_20261107
Source: Codex worker c19_u270_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u270: actual base normals already100. QueryPoint81.52381 invariant under typed inline getters/restrict and mixed point/normal-base indexing; flat [2*i]/[2*i+1] regresses80.29762. Archive owner default-construction then pointer assignment gives text100 but wrong EH: cleanup active before new, extra PC30 and nonterminal DELETEPOINTER. Add inline SAArchiveOwner(SAArchiveModel*p):object(p){} and directly construct model(new SAArchiveModel(...)): text400B100 and owned EH92B100. Aggregate initialization also fixes action shape but emits static pointer temp/store +4B, rejected. Own EH bridges/order yield full156B extab100 and index99.28571 (only Query size316/336 differs); extra weak48B EH discarded only if future promotion verified. Reversed tail-dtor group prevents B cut. Normals still physically deferred after tail despite individual100. Full fallback coordinator SHA1 exact; zero native gain.

## c19_u279_20261107
Source: Codex worker c19_u279_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u279 DbgScene_PreloadResourceTree 800D24B8: fresh baseline86.70936 ->88.192116%, source768 vs target812. Explicit unsigned byte offset plus separately assigned ResNode cursor in for increment retains separate cursor webs across four self-inlined levels; sentinel baseline while restored without loss. Re-reading payload in second sentinel regresses83.69951; independent int sentinel index/char count86.6798. Remaining source pointer-addi/mr vs target base+offset-add and absent third sentinel IV cause different GPR set/frame. SelectStage99.95177 is only @1128 vs jumptable_8041C9B0 relocation identity. All67 functions defined;65 instruction-exact. EH still924/1188 and whole group reversed by final dtor->first EH. No native gain/flag/split changes. Coordinator fallback full build SHA1 exact.

## c19_u301_20261107
Source: Codex worker c19_u301_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u301 retry Draw8020F080 improves96.61194->98.13433. TaskIter assignment operand by value plus direct return entries.Erase(it) in Remove reproduces cursorSP14 and intermediateSP10 store,264vs268B; reference-return assignment unchanged. By-value assignment with old named-result Remove over-materializes four stores/frame30 (94.92538). Nontrivial copy+const-ref Remove promotes cursor to r30 (79.791046). Named memberwise result refinement96.49254 rejected. Remaining Erase result/argument slots swapped (C/8 vs8/C) and cachedr4 node instead of r3/reload on advance branch. Private Draw header only; no ranges/flags/maps changed. Three approaches exhausted; NonMatching retained, full fallback DOL SHA1 exact, zero native gain.

## c19_u311_20261107
Source: Codex worker c19_u311_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 324 B.

c19_u311: fn_801F9B64 fresh83.987656->100%/324B. Actual independently defined file-static pool floats, 18x7 AnimationKey rows, character/filename pointer tables and logs activate native ...rodata.0/r31 base pooling; external padded aggregate and prior c16 constructor-parameter/cast/helper probes could not. First ownership draft98.765434 has descriptor/inner-index r28/r29 swap; moving const void *desc declaration outside inner for and resetting inside yields exact instructions99.5679. Own .rodata803BF440..803BFB30, split existing aggregate labels at44C/848/99C/AD4/B1C, add pool/data/EH aliases under assigned key and promote Matching. All sections100%; source-linked ELF text324/EH56/index12/rodata1776 byte-identical; DOL SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Final pool alignment byte is linker-generated, no filler.

## c19_u319_20261107
Source: Codex worker c19_u319_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u319: fn_8020A6CC improves92.88461->94.03846 by int t=self->b plus if((short)t<=0). This exactly reproduces target elapsed r4/duration r5 and extsh. r0,r4; prior short t destructive extension kept elapsed in r0. Scalar interpolation-only inline helper is text-invariant94.03846. Literal coefficient0.125f is FP-invariant and shifts anonymous constants into preexisting @61/@62 EH bridges (93.84615); retain external constant. Remaining f2/f3/f1 scratch homes and final fmadds f0;fmr f1,f0 differ from direct-f1 source, source100 vs104B. No native gain; honest singleton NonMatching, all fallback-linked DOL SHA1 exact.

## c20_u5_20261108
Source: Codex worker c20_u5_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u5 BootDispatcher98.780426->98.88708, primary6416->6412 B, EH62.15278/index27.777779/data100 unchanged. Retain static inline int IsServiceBoot(unsigned int) returning original byte-cast predicate: eliminates extra initial mr, puts service result in targetr21. Raw unsigned conversion double4330000000000000 is@692 in final source, bridges via own TU mapping toextern:lbl_806D2298; baseline@688 was auto-mapped incorrectly tofloat lbl_806D2294. Verify SHN_UNDEF and refresh anonymous id after source edits. Bool Done +! drops targetmfcr/extrwi (98.592224); byte Done==0 matches polling shape and reaches98.91844 but regresses extab60.069443, rejected. Literal timing/draw constants98.733376, rejected. Remaining r20 save partition, error setup, config boolean masks/calibration rematerialization, channel subobject stores and notice guard/loop registers. Singleton NonMatching, noB cut. Coordinator full fallback DOL SHA1OK, zero native gain.

## c20_u8_20261108
Source: Codex worker c20_u8_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u8: CourseEnvironment_UpdateAndCullZones 99.802155->100%/1112 B by replacing typed zone index strength reduction with explicit byte-offset induction (+=sizeof(CourseZone)). Assign z in loop condition and reuse it in body; this removes duplicate source address expression and allows 20 add-only EH bridges with no old-key conflicts. All 16 other function percentages unchanged; .text99.5124->99.5434, ownedEH100/index99.64286. Const object accessor and indexed object loop add one move; unsigned index and scoped object pointer invariant. CourseScene_Load byte-offset loop fixes r26 but shifts slot-owner/object r28/r29, lowers98.998764->98.91842; guarded assignment earlier changes order, not score; assigning before guard drops a move/4B. Reusing used for debug counts gives r23 rather than targetr24; ternary/early-return reverse getter gives byte-mask plus one normalization, not two. All load probes reverted. Full reversed EH span still prevents B; TU remainsNM/native gain0; final coordinator build SHA1ea30f3b1 exact.

## c20_u9_20261108
Source: Codex worker c20_u9_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1676 B.

c20_u9: all 49 resultscene functions are present. Four residuals remain invariant under recorded structural probes; GC/2.6 also gives same percentages as GC/1.3.2. Default objdiff pool inference reports ctor 8015C41C 99.81618, but disabling ppc_calculate_pool_relocations gives 100%; this is not a new source gain. The raw DOL value at lbl_806D86A4 is 30.0f, at lbl_806D8760 15.0f, and at lbl_806D86EC 0.1f. Prior source clamped o->fade to 15.0f while postprocessed code referenced lbl_806D86A4; source now correctly says 30.0f and all default function/section scores remain unchanged. Three existing defensive getters now use owner-approved SINGLETON_INSTANCE. Native gain 0, full fallback DOL SHA-1 OK; no split or Matching flag change.

## c20_u30_20261108
Source: Codex worker c20_u30_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u30: EnmyFaceEffect initializer fn_8023001C text100% hid missing EH. Real Vec3c(float,float,float) globals emit the exact two DESTROYLOCAL actions at PCs54/98 with SP14/SP8, preserving all 14 scores. Remove unused POD factory, use target string sizes25/19/18, make effect dtor out-of-line for primary emission order, add own EH/table bridges and weak-vector dtor-last order: owned extab364/index168 raw bytes and relocations exact, rodata/data objdiff100%. UpdBanana remains99.81328 after six new probes (double angle capture, SinCos out-refs, reused angle, aggregate trig outputs invariant; double trig outputs88.34, returned pair68.92). External typed pool still regresses dtor86.45/Slide94.07; no B split. TU stays NonMatching; fallback full DOL SHA-1 exact, native gain0.

## c20_u38_20261108
Source: Codex worker c20_u38_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u38 AI_UpdatePerFrameState: TU-private FramePairRecord corrects rankDifference void* to int, playerDistance int alias to float, inSpeedRange int alias to unsigned char plus actual opaque bytes, and types driver pointers. Improves 97.40878->97.86487, strong text2376->2372B; primary24-byte EH unchanged. Single shared typed base passed across helpers regresses97.0625/2356B and changes EH; per-record inline helper changes pair counter/walker and second-rank lap homes but scores the same 97.86487%. Keep typed view in include/game/AIFramePairPrivate.h; no shared headers edited. Pair/proximity GPR cycles, rank/base/result homes, mode/state swap, extra4B and existing misinferred conversion-cookie lbl_806DA3E0 vs806DA400 remain. One function prevents B, no singleton/pool opportunity. RetainNM; coordinator full fallback DOL SHA1ea30f3b1 exact; gain0.

## c20_u44_20261108
Source: Codex worker c20_u44_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u44 fn8018B31C: native EncodeName inline helper changes loop-counter scope and improves raw91.12670->91.13906/report91.273796; text6452vs6472 (old6456), retained. Pointer-taking RotatePackedByte inline and single-bit WriteBit inline both emit instruction-invariant baseline91.12670/6456. No further probes after3 hypotheses/two invariant results. Long-lived homes and bit-writer scratch, pool+40/index+20 swap association, rotation base+index versus cursor remain. Existing BSS84vs88 untouched. One-function TU cannot B; pools already owned/no singleton. Full fallback DOL SHA1ea30f3b1 OK; native gain0.

## c20_u45_20261108
Source: Codex worker c20_u45_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u45 fn801ED798: cache float clearance=lbl806DA43C before velocity integration and use it twice; restores early clearance load, improves97.94372->98.43152 at2132B. First Z-transform product scaled.x*matrix[0][2] fixes target fmadds multiplicand order. Natural ScaleGroundCorner(vec,float) snapshots scale; rotates y/scale/x FPRs but same match count. Retain helper variant to preserve old EH bridge keys; add-only @248->etb80016CD4/@249->eti80028B50, owned EH/index100. Matrix multiplication homes/load order and corner FPRs persist; late clearance/groundHeight f3/f2 still swapped. Seven raw literal sites verified correct bits/UND labels. No singleton/pool mechanism or B split; NonMatching fallback-linked full DOL SHA1 exact, zero native gain.

## c20_u53_20261108
Source: Codex worker c20_u53_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u53 PhysicsState_KartCollisionCheck:99.360466->99.38663. H5 moving default movement declaration to BEFORE fn_80057960 fixes EH intervals:284..294 and36C..528, unchanged text. These boundaries use call return PCs: movement must already exist when fn_80057960 can throw. Prior attempts had moved it only before push arithmetic after that call. Add @155->@etb_80016C5C/@156->@eti_80028B38 gives owned extab/index100. H6 default immunity=1 then clear on zero restores bne polarity, minor text gain. Remaining5 diff rows only r9-vs-r5 and missing branch-over-branch. Bool-return/out-reference queries fold byte check; mask-first int accumulator gives98.77907; constructor-wrapped reaction call leaves EH unchanged. Single function remains NM; full fallback SHA1 exact; zero native gain.

## c20_u62_20261108
Source: Codex worker c20_u62_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u62 fn8021ABFC: nested Archive_GetRootJObj arguments in ObjectTree_BlendOrCopy_Timed, instead of explicit dst local, fixes target r25 destination capture and removes extra mr; entire root/blend tail now exact. Fresh raw95.48093->95.65506, primary2384->2380B; report96.33->96.50414. Float literal probe95.39801 reverted; external [2][13] names view invariant95.48093 reverted. Add own @170/@171 primary EH/index bridges while keeping historical @172/@173: extab94.75309/index95.0. Remaining names/vtable pool (+0x74), seven addi-zero name-base rows, tire row addressing, animation pointer walk/counter and final SetScale scheduling. Current persistent namesr29/resourcesr30 already correct under-O4,s (old c16 swap description stale). No ranges/flags changed; original shared methods TU outside claim. Singleton remainsNM; full coordinator fallback DOL SHA1exact, gain0.

## c20_u56_20261108
Source: Codex worker c20_u56_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u56 NamCamFlow: fn_801F36D0 fresh default90.64886 ->99.580154, and100% with ppc_calculate_pool_relocations=false. Explicit isJapanese()==0 fixes localized player/mode branch ordering (99.23664), then replacing ONLY scale extern with verified0.75f fixes all FP homes. All-position literals collide old @193/@194 EH aliases; scale-only @192 externalizes correctly and preserves every EH/data/function score. Owned EH/index for36D0 remain100. Other four functions unchanged after bounded new typed-position, upload-helper, countdown factory/member and direct-FIFO probes. No B cut, flag/range/bridge changes or native gain. Full coordinator fallback DOL SHA1 exact.

## c20_u68_20261108
Source: Codex worker c20_u68_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u68 fn801F7604: GetTextureEntriesS56(const TextureBank801F *bank){return bank->textures;} used inside existing LoadTextureS56 fixes ALL four mixed-format offset operands r28->targetr29 at79DC/79F0/7A08/7A20. Primary1136B and77 relocations exactly equal target. Default objdiff99.753525->99.823944; ppc_calculate_pool_relocations=false99.92958->100. Add-only @136->@etb_80017580,@137->@eti_80028F88 restores owned56B EH/12B index100 with exact3+2 relocs. Retain NM: current .rodata803BEDC0..803BF020 is owned by Matching dtor801F8214.cpp, and assigned draft still emits duplicate608B pool. No ownership change allowed under this claim; next coordinated layout effort can start from instruction-exact draft. Unsigned index/mode accessor/full mix-state helper/typed attr fields invariant; changed-byte reuse regresses97.95775. Final coordinator fallback-link SHA1ea30f3b1 exact, native gain0.

## c20_u69_20261108
Source: Codex worker c20_u69_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u69 Menu801F0CC0: all 25 symbols defined. Fresh direct objdiff is lower than assignment report for three input methods (0ECC89.96951,1664 95.4,1C58 92.333336), stable after exact rebuild. Found real semantic error in fn_801F20A0: completion must tint sprites0..5 white (FFFFFFFF) and12..18 transparent white (FFFFFF00), opposite old source; 98.14865->98.175674. Natural separate d=d|v in140C improves97.76316->98.1579. Shared explicit i/offset loops improve1244 96.53509->96.710526. Other functions/EH unchanged, direct .text96.90216->96.942375. Gray first color/offset r29/r30 swap persists across inline-range, distinct-loop locals, scoped declaration, whole-body inline and scalar reuse probes. Direct pool spelling restores0ECC self/input homes but reloads root per call and regresses; input-before-table declaration invariant. Pool belongs to Matching fn_801F27B4.cpp (804E4C28..5248), outside current claim, so correct future mechanism5 merge requires expanded claims covering intervening fn_801F26C8 and dtor_801F2724 as well. Do not steal data from matched owner. Whole25-function reversed EH group blocks B. Full fallback SHA1 exact, no native gain.

## c20_u78_20261108
Source: Codex worker c20_u78_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u78 MsgPopup::Tick improves direct99.547325->99.69136 at972B: genuine PopupTextCursor {int dy,byteOffset,line;} with Get(base) and Next {dy+=30;++line;byteOffset+=sizeof(TextManager);} fixes index/stride homes and increment scheduling. Remaining only +298 mr r27,r29 vs target li r27,0 plus table @108 vs jumptable804EC3C4 relocations. Unsigned counter regresses99.320984; separate counter99.42387; for-clause line init and -200 literal invariant99.69136. H3 retained; all allocated section sizes/owned EH/index bytes unchanged. No A/B or flag/range/bridge edits; singleton TU staysNM. Final coordinator fallback build SHA1ea30f3b1 exact, zero native gain.

## c20_u100_20261108
Source: Codex worker c20_u100_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u100: supplied main omitted c19 SpecialFaceRaycastPrivate WarpZoneInsertPrivate include, while retaining source/bridges. Restoring private include recovers Reserve100 and EH99.587906/index99. Unsigned InsertFill tail fixes cmplwi (98.094406); separate generic forward-copy helper restores first forward-copy register sequence (98.426575), with append-only own aliases @342/343/344/353/354/431/432. Concrete helper collided with immutable @385; natural generic instantiation avoids collision. Raycast aggregate-copy and real inline ctor probes invariant92.242424. Segment normal-reference95.32281, alias-safe cross helper95.375435 but AddFace EH @128 collision, setters94.97895; all reverted. Final text97.198456/rodata100; eight exact functions, whole reversed group NM, zero native gain, full fallback DOL SHA1 exact. Header must be included when merging.

## c20_u116_20261108
Source: Codex worker c20_u116_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u116 ranking_display: direct91.464745->91.50481/2496B by one RankingAnim *entry declared before mirror branch and reused for mirror/labels/fade. Restores pos SP+68..70 and shared entry SP+64; EH91.581635/index100/data100 unchanged. Trivial iterator copy/reference ABI probe and ABI-equivalent float-prefix Init signature both instruction-invariant91.50481; discarded. Remaining pool-vptr base requires fn801D1800..ranking_display original-TU merge outside current claim, plus iterator temp slots/allocation webs/final panel conversion schedule. Single function cannot B. Final coordinator fallback DOL SHA1ea30f3b1 exact; native gain0.

## c20_u119_20261108
Source: Codex worker c20_u119_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u119 fn_801C9288: isolate case 1 declaration order on the retained c19 source: declare anim, param, pos, then calculate pos/param/anim in the original order. Fresh exact-command 91.22565 -> 91.2987%; only nine disassembly rows change (case1 anim r28->r30, pos r30->r28), all other cases/EH unchanged. Narrow RoundParams(index) inline accessor moves params/cups calculations into cases but duplicates lis/addi and changes GPR homes; 84.48864%, source2468B, EH94.230774. NegatedOffset(const float&) helper is invariant at91.2987, so removed. Retained best source2380B vs target2464B, EH93.269226/index91.66667. Still NM; no native gain. Pool8049AE70..8049AFD0 is owned by Matching clFlowRound.c outside this claim, so no merge or pool acquisition. Full fallback DOL SHA1 exact.

## c20_u89_20261108
Source: Codex worker c20_u89_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 6 fn / 3792 B.

c20_u89: Correction to c3/c19 whole-group conclusion: DTK accepts the leading cut at 8021C070. First dtor EH8001ACE8..AD78 precedes every remaining entry; only ctor-through-tail stays reversed. Move declarations/inlines to owned anon_8021BC44Types.h, put TimeAttackResult undefined key first, explicitly declare the two result-part dtors to suppress unowned weak copies. First TU text1068/EH144/index12 all100 and source-linked ranges byte-identical; full DOL SHA1 exact. DrawResult float literals restore alpha=f27,pulse=f28,k=f29,zero=f30,y=f31 and improve83.01613->87.29032, remaining13 TU NM. New per-TU literal extern aliases must follow raw compiler IDs and actual DOL bits; automatic postprocessing misassigned several values after instruction shrink. No pool ranges or padding added.

## c20_u102_20261108
Source: Codex worker c20_u102_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u102 fn8017A68C improves98.39921->99.98024 (1012B) by native lo/hi zero aggregate initializers plus four independent static joint-name strings, removing explicit SwitchConstantPool. Unlike c19 zero-init probe, this produces only the original24B initializer pool and strings; both first-lwz/hidden-stw scheduling pairs become exact. Refine owned rodata80371E98..80371F28 into vectors12/12 and strings27/28/29/30; add own aliases @4->global:E98,@5->EA4 and four string labels. Text now differs only +3C bge vs targetblt to same exit; EH40/index12/rodata100. Emptycase2 pivot, clusteredcase0/2, explicit defaultbreak/defaultreturn do not solve dispatch. Keep NM, no B singleton subset or native gain; no range/flag/other-TU edits.

## c20_u123_20261108
Source: Codex worker c20_u123_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u123 TaMode_Init direct94.22973->95.505066, native2384->exact2368B. Typed TaModeLoadingMessages view of existing lbl80321980 plus member access for first two log messages removes four base rematerialization instructions:94.84628/EH95.57823/index100/data100. Inline LoadGhostData leaves primary text invariant and emits extra EH, reverted. Flatten permission index as(cup*2+reverse)*2+round raises95.505066/EH95.7483; fixes player argument, PathManager alloc/matrix/render and ghost-matrix GPR homes globally, although the permission index local arithmetic differs. No-pool final95.60473. All3 hypotheses exhausted below99. Remaining prologue BATTLE/vtable base pooling, ghost table association/load-store ordering and tail BATTLE rematerialization/GPR homes. BATTLE owner FrameUpdate out of claim; no merge/range edits. Singleton TU staysNM, source_inputfalse, full fallback-linked DOL SHA1ea30f3b1 exact, zero native gain.

## c20_u129_20261108
Source: Codex worker c20_u129_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1432 B.

c20_u129: EnemyFace_nm3 ctor 8022BBC8 98.716576 ->100% by replacing inline clEFace3D slot = kart->slot with kart->GetSlot(), where TU-private KartRender::GetSlot is const inline returning slot. This natural accessor boundary fixes every volatile register home and li scheduling difference. Getter alone shifts anonymous numbering: zero literal @94 collides with existing @94 EH bridge, giving raw99.946526 despite exact instructions. Removing unused private KartHidden helper preserves original @91/@92 literals and @93/@94 owned EH bridges; no bridge edits needed. Owned text748/EH196/index12 all100; Matching source input confirmed at8022BBC8 in main.elf and full DOL SHA-1 OK. +1 native function/748B. No data ownership or B split required. Remove fn_8022BBC8 row from gave_up.md when merging.

## c20_u152_20261108
Source: Codex worker c20_u152_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u152: fn_80221104 improves97.77397->98.15069, text584/EH8/index12 unchanged. Expose only the state4 ItemWnd draw body, declare mgr/window then digitIndex,textIndex,spriteIndex at block start, and assign mgr after sprite traversal. Separate counters plus declaration/scope change make the entire coin loop exact; remaining40 rows are only GPR colors in ItemWnd/NextWnd/node traversal (node objectr29 exact, iteratorr30 vs targetr27). Value-type node iterator !=const-ref regresses97.5685; by-value comparison grows8B/96.061646. Reusing only sprite+digit index is invariant98.15069. Keep best natural draft NM; no A/B/pool/singleton rescue; final fallback DOL SHA1 exact, native gain0.

## c20_u150_20261108
Source: Codex worker c20_u150_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u150 fn_801B9928: native separate C++ BSS arrays top[3],bottom[4],short*handles[5] recover full1804B target skeleton, prologue/frame/saved r25..r31, allocation pointer homes, and all owned EH. Unlike sibling C native-BSS trial, C++ definitions emit correct declaration order (offsets0,C,1C). Own BSS80679280..806792B0; split lbl8067928C size2C into10 plus lbl8067929C size14, leaving B0..B8 unowned. Baseline93.736145->99.76718; BSS/EH/index100. Only remaining residual r4/r5 volatile swap in positioning block offsets284..2E4. Float-first helper, reused named sprite local, corrected handle-pointer types, explicit bottom-row alias are instruction-invariant; Vec2 struct-copy setter regresses89.49889. Keep native-pool draft NM; single fn has no B cut. Full fallback DOL SHA1exact. Future attempt should start with this owned pool, not aggregate/accessor probes.

## c21_u5_20261108
Source: Codex worker c21_u5_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 3016 B.

c21_u5: fn_8015CD74 99.5842->100% with ABI-equivalent fn_8015D4F8(self, x, y, color, text) signature/call; float/int banks unchanged, callee remains100%, and color lwz moves after x-choice branch. Original resultscene span is not wholly indivisible: extab payload ordering allows boundaries at8015E928 and8015F0FC. Three-way split isolates fn_8015E928/2004B plus exact8B EH/12B index/.ctors as Matching (full DOL SHA1ea30f3b1 exact and main.elf range verified). Types/inlines moved to resultscene_shared.h; keep primary SpriteHolder dtor in first group and matching inline body available in tail, otherwise fn_80161F28 loses member cleanup inlining. All49 funcs present/no regressions. DEBC six probes leave FP scratch colors99.61539; update six probes leave input/new-temp r29/r30 swap99.90323 including switch-table symbol inference. Remaining two groups stayNM.

## c21_u12_20261108
Source: Codex worker c21_u12_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 17 fn / 7096 B.

c21_u12: CourseScene_Load99.83931->100%/3236B. Explicit byte-offset induction with zone assigned in loop condition fixes zone r26; guarded o assignment before slotOwner fixes move order. Swap object cursor and slotOwner declaration positions to restore object r28/slotOwner r29. Direct rightmost DebugPrintf byte-count expression fixes both temporary homes to target r24. Natural PrintRendererStatistics(format,self,count,stride) inline keeps this code and permits fresh EH IDs; passing cached renderer instead adds2 moves/8B because target reloads renderers[0] across calls. Fourteen add-only bridges @591/592,693/694,702/703,725/726,738/739,750/751,768/769 restore all owned EH/index100 without modifying older keys. Existing opt_dead_assignments off region unchanged; no added pragmas/flags/data ranges. Entire17-function/7096B reversed-EH TU promoted Matching, source main.elf edge and all17 addresses/sizes checked. Full DOL SHA1ea30f3b1 exact.

## c21_u25_20261108
Source: Codex worker c21_u25_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u25: GC/2.6 NameEntry Draw improves 93.30986->96.356804 with nested static inline DrawKeyGroup/DrawKeyGroups: group resource stack slots and GPR homes now exact, 840->852 bytes. Remaining glyph pointer IV/indexed lhzx, extra halfword truncation and sel subf direction. NameEntry ctor int flag (not bool), low-byte mode test and integer-valued IsAsciiKeyboard accessor improve 98.27061->99.68896 while factory stays100; only mr r4,r30 is scheduled at loop entry instead of tail. Bool KeyBoard, fill inline, postincrements and step order do not close it. Placement new copy/default+assign/nothrow probes cannot move KeyVec init EH-state store into target copy tail. 61/67 exact, no internal legal cut across64 EH entries; owned EH54 payload-exact unchanged; source fallback DOL SHA1 OK, native gain0. Add-only current compiler-label bridges avoid modifying stale existing maps.

## c21_u31_20261108
Source: Codex worker c21_u31_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u31: fn_8022D9E4 UpdBanana natural C++ reaches100%/1928B. Make Vec3c::RotationMatrix non-const and MakeMtxVec rotation argument Vec3c&, then declare captured angles rz,ry,rx. Non-const member fixes first6 FPR rows (99.87552); directed declaration swap fixes remaining12. Changed anonymous EH IDs357/358 bridged add-only; positive0.4f/1.2f in UpdStar use actual extern labels668/66C so later IDs/bridges remain exact. All14 funcs/owned sections100%, DOL fallbackSHA1exact. IMPORTANT inherited fn_8022CE34 opt_lifetimes off is a fakematch fromab1308c7; removing it leaves99.44444/12r26-r28 operand rows. Five natural destructor probes fail; restore inherited source and keepNM rather than count it. No native gain.

## c21_u37_20261108
Source: Codex worker c21_u37_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u37 AI_UpdatePerFrameState: actual untouched baseline97.86487, cup-before-round declarations with original round-then-cup loads fix four rows (0x2D8/2E0/2EC/2F0), final97.89865/2372B. Pair decl reorder and outer proximity pointer scope had no effect and were trimmed. Removing rank base parameter97.375/2376B; caller-direct rank body97.54223/2384B; both retain rematerialized bases and are discarded. Owned24B EH unchanged. Pair/proximity GPR cycles, rank base/result homes, mode/state swap and misinferred conversion-cookie relocation remain. Single-function TU prevents B; no neighbouring pool/singleton opportunity found. Honest NM, gain0, no full request (source-only; baseline DOL hash exact).

## c21_u43_20261108
Source: Codex worker c21_u43_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u43 fn8018B31C: initial pragma baseline raw91.26576; removing opt_lifetimes/dead_assignments gives91.13906. Natural encodedClass ternary ccClass>=2 ? ccClass-1 : ccClass restores target class r29 and pool bases r27/r28, gives raw91.40173/report91.53647,6452B; retained with both opt_* pragmas removed. Moving class declaration beside seed is byte-invariant91.13906 (merged parameter web). Separate offsets/schedules reproduces c19 pool+60 correction but regresses91.11805/6448B. Remaining name/inline-counter/base coalescing, bit-writer scratch, rotation and checksum schedules; BSS84vs88 unchanged. Full fallback DOL SHA1ea30f3b1 OK; no native gain; one function cannot B.

## c21_u44_20261108
Source: Codex worker c21_u44_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u44 fn801ED798: new AccumulateGroundProduct(float&sum,float right,float left){sum+=left*right;} isolates multiply-accumulate argument evaluation and fixes matrix FP load/home residual,98.43152->99.49343. Explicit output pointer and col/index/row declarations with original 2D rotation indexing fix matrix GPR cycle,99.84991; flattened rotation indexing loses early r23 and regresses. DOL-verified0.1f clearance literal restores f2/f3 homes,99.90619; all8 raw literal sites map correct bits/UND target labels. Corner y/scale/x f0/f3/f2 vs targetf3/f2/f0 remains8 rows at801EDCB8..CE8. Caller scale snapshot, field-local snapshots, nested scalar scale helpers and fieldwise constructor initialization do not fix it. Add@262/@263 primaryEH bridges; ownedEH/index100. Onefn NonMatching; no B cut/pool/singleton mechanism. Coordinator fallback fullDOL SHA1 exact; nativegain0.

## c21_u54_20261108
Source: Codex worker c21_u54_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u54 WallCollisionCheck fresh97.689255->98.11449 (1716 vs1712B): yaw-matrix constructor fixes f31 yaw/f30 cosine homes; explicit float xx/yy/zz products and zz+(xx+yy) reproduce separately rounded length arithmetic. Owned EH48 bytes exact; aggregate EH92.30769/index61.11111 unchanged, weak dtor appended. Inherited opt_common_subs off unchanged, remains NM and acceptance blocker; best pragma-free probe97.33178. Caller-local rotation pointer does not hoist row base (targetr22 across calls, sourcer7 late). Vector scale/subtract/reference helpers97.33178 without pragma; scalar squared helper98.0514 with inherited pragma, both rejected. Missing base is stack rotation SP+A0, not data pool. No split/config/bridge/order changes; singleton cannot B rescue; source fallback links, coordinator build SHA1 exact, native gain0.

## c21_u53_20261108
Source: Codex worker c21_u53_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1292 B.

c21_u53 fn_801D1890 unlocked99.990715->100, text1292/EH40/index12, source-linked full DOL SHA1ea30f3b1 exact. Stack residual was not register/pool ownership. Baseline caller constructs RankingFlowIter(end) then passes const& to a void insertion helper; compiler groups return buffers before position temps. Accept sentinel RankingFlowNode* in RankingInsertFade, construct RankingFlowIter(end) INSIDE that helper call expression, and pass it through a standard const-reference inline facade RankingInsertAt returning DoublyLinkedList_PushBefore(list,&last,&fade). This interleaves position/result temporaries correctly: first ret10/pos14/fade1C, second ret8/posC/fade18. Named local position (earlier attempts) reverses ret/pos; caller expression temporary (baseline) groups slots. Both wrapper sites remain symmetric in retained code. Only source+Matching flag changed; no bridges, data, splits, headers or pragmas. Neighboring ranking_display may benefit from this expression-temporary ownership distinction.

## c21_u57_20261108
Source: Codex worker c21_u57_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u57 fn_8021ABFC: inherited opt_loop_invariants/opt_strength_reduction pragmas are forbidden on this lane; removed, raw95.762856->95.65506 (report96.50414). Distinct real static int IDs + individual char arrays reproduce all 1376B resource offsets and create ...rodata.0 anchor, unlike c18 aggregate probe; text95.339966/2384B due names/resources register exchange and still-indexed IDs, so reverted. Inline member animation loader94.427864/2392B; pointer postincrement inside new argument94.95854/2392B; reverted. Remaining +0x74 vtable/driver+tire table pooling documented in gave_up still needs original matched methods TU merged with ctor; neighbour outside sole claim. No flags/ranges/bridges changed; zero native gain; coordinator full fallback DOL SHA1 exact.

## c21_u61_20261108
Source: Codex worker c21_u61_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u61: fn80179F60 97.690025 ->97.98922 actual and default via static inline QuadCross(edgeX,posZ,edgeZ,posX) returning edgeX*posZ-edgeZ*posX. Right-to-left scalar argument evaluation fixes first six load/arithmetic order differences in each quad; no new instructions, native1472 vs target1484 unchanged. Pointer-based nested cross is byte-invariant. Vec2 ctor/const-reference cross regresses87.471695 and EH, reverted. All other functions/nontext sections unchanged. Pattern13 of regalloc_patterns exactly diagnoses missing three addi r3/base+offset materializations: static object behind section anchor; currently all loads fold through external lbl80370870. Needed pool is Matching mapeffect.cpp outside claim; merge requires coordinator-expanded claim. Reversed EH prevents B. Honest NM, zero native gain; no full build request.

## c21_u77_20261108
Source: Codex worker c21_u77_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u77 EnemyFace8022ACE4: inherited opt_lifetimes-off draft raw98.579506 unchanged; natural no-pragma97.24381. Typed float UV table alone leaves instructions invariant. Exact string extents803DA6C0[0x1E],803DA6EC[0x11],803DA700[0xA] make rodata objdiff100; source raw0x492-byte prefix matches target0x498, remaining6 bytes final alignment. Reusable UV aggregate96.353355; four-vertex canonical loop91.15548 (1084B) does not partially unroll. Original function restored including inherited pragma, which is not a new natural match. TU remains NonMatching, no native gain; full fallback build SHA-1 OK.

## c21_u94_20261108
Source: Codex worker c21_u94_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u94: Segment 95.357895 -> 96.077194: declare vertex before count restores target r4 cursor/r8 count and missing mr; normal-first rounded plane products and reciprocal reuse improve intersection tail. Offset-based sdata2 postprocess misassociated anonymous 3.0 with target 0.5 after instruction shift; TU-local canonical Newton sqrt uses explicit target extern 0.5/3.0 and divisions use target extern 1.0, verified from original DOL. InsertFill 98.426575 -> 99.545456 by naming suffix end before destination; suffix setup exact, only backward-copy r4/r5 swap (25 reg-only rows). Generic backward helper invariant, in-place helper regresses, result-first args add mr, explicit reverse steps invariant. Raycast reference helpers and component loop both invariant92.242424. Append 19 non-colliding owned EH/descriptor aliases; all previous aliases unchanged. Final text97.77729/EH99.587906/index99/rodata100. Eight exact functions preserved; reversed group and physical weak-holder/InsertFill order prevent native gain. Full fallback-linked DOL SHA1 exact.

## c21_u101_20261108
Source: Codex worker c21_u101_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u101: inherited tree contains opt_common_subs off + optimize_for_size on, fresh raw97.525475 (not assignment96.13). Removed these prohibited per-function pragmas; natural baseline96.0828. Separate static inline float rivalSegmentYaw(const Waypoint*,const Waypoint*) with named float angle restores target frsp f0/fmr f1,f0:96.39809/1260B. Correct read-only E4 threshold removes the redundant reload:96.79618/1256B. Float and double helper return variants are instruction-identical, so retain float matching canonical APIs. Add own @176/@177 EH aliases; owned EH97.22222/index100, weak dtors unchanged. Array position/direct scalar writes93.191086 does not fix early address; real separate position copy80.70382/1296B rejected. Pool 803BD920..803BDED4 belongs to fn_801ECA14.c outside claim; no pool/merge edits. Singleton function cannot B. Fallback full DOL SHA1 exact; native gain0. Natural draft improves 0.71338 points, but raw score is below the inherited pragma-assisted draft by0.729295.

## c21_u102_20261108
Source: Codex worker c21_u102_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u102 ranking_display: c21_u53 expression-temporary mechanism applies to all seven list insertions. TU-local void RankingAdd(list,entry) calls returning RankingInsertAt(list,RankingFlowIter(list->End()),entry), where position binds to const-reference. Retained with no header edits: all seven ret/pos slots match (50/54,48/4C,40/44,38/3C,30/34,28/2C,20/24); existing pointer temps58/60/5C and shared64 preserved. Fresh direct93.72756->93.76442; own @212 external cookie and @215/@216 EH bridges give93.77244 (final report93.958336), EH90.92921/index95/data100. Coordinate float locals and longRound assignment inside first call are invariant, reverted. Remaining persistent r30 pool-vptr ownership, allocation webs and final panel conversion schedule;2492vs2496B/frameB0vsC0. Single function remainsNM; original-TU merge requires neighbors outside claim. Final coordinator fallback DOL SHA1 exact; native gain0.

## c21_u105_20261108
Source: Codex worker c21_u105_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u105 fn_801C9288: fresh91.2987 ->91.347404 by replacing six Scale literals with canonical external lbl_806D9D3C(.7)/lbl_806D9D28(1), as sibling CupTile_StateChange does. Six relocation references change, same2380B source text and unchanged EH93.269226/index91.66667. Narrow Position+Scale inline boundary invariant; explicit if/else offset init87.9789/EH94.230774 adds branches. Retained only scales, NM, full fallback DOL SHA1ea30f3b1 OK. Pool8049AE70..8049AFD0 remains owned by out-of-claim Matching clFlowRound.c; no B cut in singleton. Census classifier r0/reg+other/multi,168 diff rows, rematerialization; anchor is the dominant mechanism, not a pure register permutation.

## c21_u125_20261108
Source: Codex worker c21_u125_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 496 B.

c21_u125 unlocks RaceDigitLap fn_80246988 (496B),99.90323->100. Two TU-local static inline value getters PositionX/PositionY returning float, consumed into named x/y captures and stored x before y, reproduce lfs f0,8(r3);lfs f1,12(r3);stfs f0,0x4C(r4);stfs f1,0x50(r4). Scalar setter/generic AssignComponent boundaries only99.83871 (pure FPR swap); CopyXAndGetY return form99.82258; reference-returning getters98.129036/500B. Temporary opt diagnostics did not solve it and none retained. Existing owned EH164/index12 bytes and relocations exact; extra two weak dtor entries discarded at link. Matching flip source-linked at0x80246988..0x80246B78, coordinator full build SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Native gain1fn/496B. docs/gave_up.md RaceDigitLap entry can be removed as resolved.

## c21_u138_20261108
Source: Codex worker c21_u138_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u138 TryArmInit: C7Vec v=self->pos; Normalize(&v) replaces default construction plus NormalizeCopy. Exactly six source rows at +2F0/+2F4/+2FC/+304/+308/+310 restore target Y/Z registers; 93.89051->93.98783, same1636B, extab98.4375/index95 unchanged after add-only @214/@215 bridges. Scalar six-arg Dot invariant. Explicit quaternion products95.277374 / scalar helper95.357666 but1620B, one fewer saved FPR/frameA0 vsB0 and worse ownedEH, so only archived. Offdiagonal-only94.3236/1616B; diagnostic CSE-off86.72019/1588B, none retained. Final service fallback DOL SHA1 exact; native gain0.

## c21_p19_20261108
Source: Codex worker c21_p19_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p19: fn_80170B5C stack-frame residual was a semantic type-size error: GrowFace was opaque 0x48 but fn_80184F24 emits DListQuadInfo (four Vec vertices, flags, two floats = 0x3C), and fn_801234F8 advances input by 0x3C. Reusing canonical DListQuadInfo fixes frame 0xB0 -> target0xA0 and all six frame operands. Include extractor declarations with C linkage and add own GrowAnim(DListQuadInfo*, int) bridge. Text99.05778 ->99.08444; only offset initializer mr r30,r29 vs li r30,0 remains. Owned EH/rodata100. Singleton NM, no safe B cut. Coordinator full build target SHA-1 OK; zero native gain.

## c21_p6_20261108
Source: Codex worker c21_p6_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p6 NamCamFlow: naming second border coordinates (float y,x; assign x then y) fixes its FPR homes and raises update 99.6371 -> 99.69086. Add-only @886 jump table, @891/@892 update EH and @947/@948 draw EH aliases preserve every other score. .data 80419DE0..80419DFC ownership probe unchanged text and explicit re-split causes a link-order cycle through earlier TUs; reverted. Pre-new list snapshots lift fn32BC to99.36015 and restore frame but shift literal into existing @193 EH alias, regressing exact36D0/EH; draft in build/w/snapshot_best.cpp, not retained source. Confirmed21 EH-bearing functions have no safe internal cut. TU remainsNonMatching, zero native gain, full coordinator fallback DOL SHA-1 exact.

## c21_p20_20261108
Source: Codex worker c21_p20_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p20: BootDispatcher pool experiment owns .rodata802E8F48..802E9650 with exact 1800-byte typed constants/strings; replacing text+offset with named objects leaves text98.88708/6412B, extab62.15278/index27.777779/data100 unchanged. Thus rodata ownership alone is not the remaining lever. Isolated BSS80598A60..8059F480 ownership with typed calibration object regresses text97.09912 and dtk reports a long cyclic link-order dependency via HeapStats and auto_08_80598568_bss; reverted. Mode-local reuse in boot-error setup is byte-invariant; reverted. Remains singleton NonMatching, zero native gain. Coordinator full fallback DOL SHA1 exact.

## c21_p26_20261108
Source: Codex worker c21_p26_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p26 Scene_8015B790: pool ownership already complete (rodata836B100%); no missing functions. Baseline98.79371 is 1148B, not target1144B: existing fp_contract off breaks target font-position fmadds into fmuls+fadds, causing extabindex91.66667. Removing it restores size/EH and exact font math but score98.496506; only icon index/base r4/r0 and lwz/fneg/f6 scheduling remain. Named index/negative-angle locals and a pool+index inline drawing helper both instruction-invariant. Retained baseline with canonical fn_80169040 pointer/unsigned-flags declaration only; no native gain or split rescue.

## c21_p41_20261108
Source: Codex worker c21_p41_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p41: Owning BOTH fn8021ABFC pools as real distinct objects improves raw95.65506 to98.48259/report98.681595. .rodata803C4E60..803C53C0 (1376B) and .data804EDC88..804EDD20 (152B) all100%; no fillers needed. Separate driver/tire arrays restore all seven addi-zero rows and tire addi/lwzx. Native explicit __vt__16clCSOrgKartModel table definition has exact data/relocations but implicit compiler vptr reference still materializes independently; identical link name does not make this reference use section anchor. Compiler weak vtable via inline virtual declarations regresses92.21 and emits null RTTI header under current flags; explicit vptr assignment retains implicit store and regresses97.46. Kept H1 NonMatching. Primary2412B, EH95.679/index100; full fallback DOL SHA1 exact.

## c21_p44_20261108
Source: Codex worker c21_p44_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p44: AI_CalcRivalAvoidance 801EE7F0 improves fresh baseline96.79618 to96.98726,1256B. H1 reverse normalization helper bound/turn parameter order restores turn-before-bound load evaluation96.8121. H3 small inline rivalAvoidanceAmount(distance,lower), sequential subtract/subtract/divide/add then scale multiply, restores arithmetic operand FPRs96.98726; amount saved home still f31 vs targetf30. Direct sequential expressions shift literal IDs into stale EH aliases and are unsafe; helper pushes literals to@182/@183 (postprocessed UND D8/DC), add own primary EH bridges@184/@185. Owned EH97.22222/index100 unchanged. Pool OTHER: matched fn_801ECA14.c owns803BD920..803BDED4; untouched. Contiguous owner-to-function merge interval801ECA14..801EECD8 spans9 TUs, so coordinate rather than merge two disjoint sources. Early candidate.position address lifetime and normalization/tail register residual persist; B impossible singleton. Full service SHA1OK, source_input false, native gain0.

## c21_p45_20261108
Source: Codex worker c21_p45_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p45 Menu801F0CC0: SetAlphaRange with helper-local int i declared before color computes alpha inside the inlined loop boundary and makes 19C8/1AC8/20A0/21C8 text100 (1132 B), no other function regressions. Paired explicit-offset SetAlpha2 improves1244 97.54386->98.42105 and140C98.1579->98.46491. EH order must put2690 first in extab, normal address order in index, and extra weak fn26C8 last: owned232B payload/relocations exact; index still has1664/1C58 length mismatches. All25symbols present. Pool remains owned by Matching fn27B4 and whole25fn reversed group prevents B; coordinated contiguous merge also needs fn26C8 and dtor2724. Full fallback DOL SHA1 exact, nativegain0.

## c21_p52_20261108
Source: Codex worker c21_p52_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p52: TaMode_Init owns previously unowned rodata80321980..80322120 with natural float scale/curve pool and exact-size ghost filenames/loading strings. Message blob80321FB0 partitioned into17 actual string symbols. Every rodata object100%; direct text stays95.505066 (report95.63176), EH95.7483/index100/data100; no missing functions. Local restrict ghost pointer byte-invariant and discarded. Full coordinator fallback DOL SHA1exact. Core unlock still requires owner-coordinated merge of FrameUpdate+Dtor+Init (text800A2B90..800A4578), .data EA58..F0E8 including currently unownedF0A4..F0C4 vtable suffix. No foreign edits, no native gain.

## c21_p55_20261108
Source: Codex worker c21_p55_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p55 ranking_display: unowned .data8049B510..B530 contains genuine RTTI base record + 3-slot dispatch table. Owning it and defining typed native records plus a private explicit scene-base dispatch view restores persistent r30 pool anchor, allocation registers, and target C0 frame without merging matched neighbors. C-language inline character lookup restores r3 return/name capture. Direct93.77244->96.07692, text2488vs2496, data136B100, EH99.11504/index95. Residual indexed-table base folding (two instructions), longRound capture, second-label r7/r8 webs, final panel bitfield/float argument scheduling. bool-parameter conversion probe invariant, reverted. Source remains NonMatching; coordinator final fallback SHA1 exact; zero native gain.

## c21_u158_20261108
Source: Codex worker c21_u158_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u158 ExplosionTumble_Init: replace scalar QuaternionMatrix args with const C7Quat* plus explicit float products yy/zz/xy/wz/xz/wy/xx/yz/wx. Restores Y-first matrix load and separately rounded target products, raises89.99078->92.81567 at1736B with owned EH48/index12 exact100. Direct pointer expressions fuse products89.129036/1724B. Typed pointer LengthSquared shared with Normalize92.70507/1736B changes first velocity load to X, reverted. All literal math94.1129/1748B, normalization-only literals93.40323/1760B change size/EH, reverted. No pool anchor or B cut, stays NM. Existing bridges suffice, only source changed. Full coordinator fallback build SHA1ea30f3b1 exact; zero native gain.

## c21_u154_20261108
Source: Codex worker c21_u154_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u154 carobject: scalar TransformComponent inline raises affine85.29032->89.48387, versus by-value Vec3 helper40.258064/component loop67.80645/inline accumulator87.548386. Constructor prefix belongs to an inline control/settings subobject: mode/config args evaluated before stores. MovementSettings initializer-list ctor89.23124 emits1972B including redundant int-to-bool normalization; explicit ordered stores of22/24/28 then0c/14/10/08/18/1c/20/21 improve91.08925 but1960B and eliminate double normalization again. Matrix44 yaw ctor89.119675 does not retain r30 stack pointer. Crucial shared-header dependency: carobject_private.h is used by KartMovement_PhysicsStep; keep old MovementInit intact and use CarMovementInit in new carobject_init_private.h, with own add-only bridge __ct__15CarMovementInitFPvPUcPvfff->KartMovement_Init. Eleven exact functions preserved; text96.32763/EH0/index0, physical order not exact, indivisible reversed group staysNM. Final all_source/full-link fallback SHA1 exact; zero native gain.

## c21_u162_20261108
Source: Codex worker c21_u162_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u162 Draw8020F080 improves98.13433->99.9403/268B through natural TaskIterBase with node/operator->/prefix++ and derived TaskIter retaining value-operand assignment; Draw uses it-> and ++it. Restores target r3 node use and reload in advance branch, exact EH8/index12 and target size. Remaining only Erase result/argument slots source C/8 versus target8/C at offsets B8,C0,C4,CC. Remove const-ref invariant; base-return conversion regresses; implicit derived assignment loses intermediate copy; public value Erase wrapping mutable-ref EraseAt invariant. All maps restored. Single fn staysNonMatching, zero native gain; full fallback-linked DOL SHA1 exact.

## c21_u161_20261108
Source: Codex worker c21_u161_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u161 DbgMenu: all67 functions present; direct baseline preload93.5468%,796/812B. Sentinel loops are already exact including dead offset IV. Remaining outer node step loses base+offset IVs, shifts saved-register set/frame. Signed offset invariant93.5468; loop-head current record73.21182; offset-reference step helper92.43842/812B but adds24B out-of-line helper at recursive inline depth limit. All rejected, source restored. Partial A owns compiler switch table8041C9B0..8041C9D4 and adds own @1128->jumptable8041C9B0 bridge: SelectStage99.95177->100,data100,all others unchanged. EH924/1188 and whole reversed group prevent promotion/B. Final full fallback DOL SHA1 exact; native gain0.

## c21_u182_20261108
Source: Codex worker c21_u182_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u182: Fresh baseline98.41791%/264B has optimization pragmas; removing them is byte-identical. A TU-private SceneDrawIter : canonical ListIter with operator=(ListIter other) plus direct entries.Erase(it) produces268B/99.9403%, exact extab8/index12, loop atSP14 and target postcall storesSP10 thenSP14. Residual only four swapped return-buffer/argument offsetsSP8/SPC at802042CC,D4,D8,E0. No opt pragmas retained. Named-result helper or named caller result adds a third postcall store and loopSP18; const-reference assignment removes needed intermediate store. Fully private consistent base/derived list model does not resolve slot order. Six hypotheses exhausted; best draft retained NonMatching, no A/B rescue or native gain.

## c21_u193_20261108
Source: Codex worker c21_u193_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u193 fn_8020A6CC: double result local (arithmetic stays float, API stays float) gives95.0%/104B, EH/index100, vs baseline94.03846%/100B. Common frsp f1,f0 replaces target fmr, early result homes f0 vs target f1; FP conversion/rate/coefficient cycle remains. This is a fuzzy extent improvement, not proof of original double result type. Output-reference inline90.19231%/100B changes FP webs but no copy. Unsuffixed0.125 gives91.53846%/104B, lfd/fmadd/frsp plus existing bridge collision, rejected. Retain highest genuine double-result draft NonMatching; no pool residual or valid B subset; coordinator fallback DOL SHA1 exact, zero native gain.

## c21_u192_20261108
Source: Codex worker c21_u192_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u192 ShadowAreaMgr_QueryPoint81.52381->86.64286% (324vs336B). Point lookup through mgr->entries[index].edges[i].point in a native point accessor, while normals remain through entry parameter, retains independent point/normal IVs; deriving entry inside same helper collapses back to81.38%. Postincremented edge iterator81.58; GC2.6 invariant86.58. Diagnostic opt_common_subs off80.36, removed. Retained helper uses both manager/index and entry context, no no-op checks or junk temps. New inline syntax shifts anonymous IDs;12 add-only ownTU bridges preserve156B EH100 and index99.28571, all seven other functions100. Target still second normal addi r4,r6,0x148 and two0x18 cursor advances; source folds normal loads and increments0x30, plus count/prologue and GPR partition differences. No pool anchor. Reversed tail-dtor group blocks B; TU staysNM. Full fallback build SHA1exact; zero native gain.

## c22_u9_20261109
Source: Codex worker c22_u9_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u9 NamCamFlow: natural inline NamCamAddCountdown(FlowSceneList*,id,number) snapshots list before new; removes existing opt_propagation off pragma, fn32BC97.5364->99.0728 with exact1044B/frame30/ownedEH/index. Unlike explicit-list-local draft, helper shifts scale literal to an unclaimed anonymous ID, so 37 add-only own-key EH/jumptable aliases restore every other symbol unchanged. Overall extab97.5931->99.04098, index99.7619->100; ctor3BD8 EH96.77419 remains. .data80419DE0..80419DFC first-check still fails direct dtk split with a global link-order cycle; range reverted. No safe EH cuts across22functions/21entries. Whole TU NonMatching, zero native gain, full coordinator DOL SHA1 exact. Remaining32 residual is saved-GPR cycle and id/time decrement order; avoid repeating prior input/border/upload and localized-position invariant probes.

## c22_u27_20261109
Source: Codex worker c22_u27_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u27 fn8018B31C: int payload parameters in WriteBits/WriteField retain all explicit call-site byte conversions and raise direct91.40173->91.59023/report91.53647->91.72497,6452vs6472B.31 target-aligned checksum/tail rows become exact with zero new mismatching rows; diff985->954. Byte coordinate start/n regresses70.99444/6440B; explicit width-then-offset locals90.71570/6452B, both reverted. Pools already OWN-SELF/defined; no ownership edits. EH100,rodata100,index91.66667,BSS81.818184 unchanged (84vs88B; no filler). Singleton prevents B; NonMatching, nativegain0. Coordinator full fallback DOL SHA1exact.

## c22_u35_20261109
Source: Codex worker c22_u35_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u35 ranking_display: baseline96.07692 ->96.10096 by natural bool RankingIsLongRound accessor and bool local. Exactly two emitted rows change: +114 srwi r23,r0,31 and +118 mr r4,r23 now exact. Typed packet accessors regress94.410255, C table-index accessor instruction-invariant; both reverted. Direct bool local shifts cookie/EH IDs into immutable @222 collision; natural boolean accessor yields free @223 cookie and @226/227 EH IDs, bridged add-only. Owned136B data100 and EH99.11504/index95 unchanged; source2488vs2496. Pool ownership/persistentr30 already fixed by c21p55, no merge/ranges needed. Residual table-address folding, second-labelr7/r8 swap and panel conversion schedule. Single fnNM, zero native gain, full coordinator DOL SHA1exact.

## c22_u67_20261109
Source: Codex worker c22_u67_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u67: DoublyLinkedList_PushBefore 8005FEB4/168B improves94.97619->100% with real ListValueCopy<T> node member whose inline constructor has a function-try-block, initializes value(v), and on construction failure calls operator delete(h.release()). Placement-new guard now encloses constructor try-entry saved-SP store, exactly target lwz/stw-SP/stw sequence. TU-private list layout avoids changing shared manager/list destructor types. All other functions invariant; all11 owned EH payloads/index lengths/relocation targets exact, including PushBefore8B EH28180000/0. Data ownership .data803F9CE4..803F9D00 was tested first and reverted after invariant text; target uses separate vtable lis/addi pairs. Sound99.416664 r30/r31 and Remove97.64706 r27/r28 swaps remain; tail base dtor early EH binds reversed group. Keep honest NonMatching; native0; final coordinator DOL SHA1ea30f3b1 OK.

## c22_u74_20261109
Source: Codex worker c22_u74_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u74: NameEntry::Draw 96.356804 -> 97.3615% (852 B) with unsigned-int character return/local, unsigned-long accessor index, and g == board.group equality operands. Removes redundant clrlwi and fixes subf direction; unsigned index changes pointer IV into byte-offset IV but target still recomputes (i+1)*2+0x28 at lhzx. Other five residuals unchanged after bounded type/inline/scope/loop/EH probes. Own add-only @3151->lbl_8039A498 and @3182->lbl_8039A50C bridges preserve other function scores. All 64 owned EH payloads/relocations unchanged (54 raw-byte exact); 61/67 text-exact, no legal internal EH cut, TU remains NonMatching. Coordinator full fallback build SHA-1 ea30f3b1 OK; native gain 0.

## c22_u76_20261109
Source: Codex worker c22_u76_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u76: split three oversized rodata target symbols into the 17 existing source-static tables/strings (6314..6364,63A0..63F8,6408..65E0). Raw RecordBanner ctor99.902916->100; ctor96.091774->96.20253, DrawResult98.129036->98.518814, whole text99.2042->99.274254; normalized report unchanged99.328545. Source probes restored; zero native gain. Shared debug/digit counter fixes ctor +31C mr but shifts anonymous IDs and breaks existing EH bridges. Existing raw DrawResult literals @854=1.0,@855=3.0,@856=320,@857=154,@858=1.25 are currently bridged to wrong labels. Correct destinations would be @854->extern:lbl_806DB07C,@855->extern:lbl_806DB14C,@856->extern:lbl_806DB09C,@857->extern:lbl_806DB150,@858->extern:lbl_806DB154. Worker left them untouched because authorization was add-only; do not trust normalized score to establish literal relocation correctness. Full fallback DOL SHA1 exact.

## c22_u87_20261109
Source: Codex worker c22_u87_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u87 AI_UpdatePerFrameState: reversing rank-search result direction (return retained record, matched driver via reference) fixes record home to r25 and improves direct objdiff97.89865 ->98.13513 (report98.0 ->98.244934), still2372B vs2368. Canonical AIPairRecord union aliases remove reinterpret cast and fix selected-address scratch rows at98.16892, but change AI_CalcRivalAvoidance EH scores despite unchanged text/full fallback SHA; fully reverted, do not land shared aliases without owning dependent bridge repair. Explicit pointer walkers in pair/proximity loops regress93.60473/2400B and owned EH. Final source-only helper preserves24B owned EH, all other report units byte-for-byte JSON identical, coordinator request2 SHA-1 OK. Pair/proximity GPR cycles, rank remat/driver/lap homes, speed mode/state swap and existing conversion-cookie misrename remain. One function prevents mechanism B; no singleton/pool lever; 0 native gain.

## c22_u91_20261109
Source: Codex worker c22_u91_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u91 fn8018E6FC inherited opt_dead_assignments off removed:99.01786->99.06888 direct/report,1568B/EH8/index12 exact sizes; all FP operands now exact. Residual only matrix preheader lfs/li/li vs li/lfs/mr and point/q targetr9/r7 vsr7/r9. Long types invariant. Named search return invariant; break+merged exit96.234695 adds saved register. Complete per-matrix inline98.99235 changes p/point/q to7/8/9. Particle-array search79.45918 removes ten-way unroll. Scope q beside point both orders invariant. Caller-expanded matrix loop98.265305 restores independent zero lis/point9 but disrupts i/offset/p/q/search scratch. Retain only pragma removal; single-function NM, no pool/singleton/B route. Full fallback DOL SHA1 exact.

## c22_u96_20261109
Source: Codex worker c22_u96_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u96 WallCollisionCheck98.11449->98.67523 with NO optimisation pragma: literal zeroes in matrix identity, correction.y and CollisionLength allow ordinary CSE; extern one retained because literal one leaves wrong anonymous relocation. Removes inherited opt_common_subs off, restores1712B and owned raw EH48/index12 exact; object EH92.30769/index66.66667 includes extra weak dtor and anonymous-symbol differences. Yaw+source product constructor is invariant98.65187, cannot hoist rotation pointer. By-value vector scaling adds frame1A0 and temps90.09346; rejected. Z transform scaled.x*m[2] fixes one operand98.67523. Missing base is stack SP+A0, not pool. Three approaches stopped; singleton NM, no A/B/native gain. Full fallback-linked build SHA1OK.

## c22_u124_20261109
Source: Codex worker c22_u124_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u124: retain scoped offset normalization with yy declared before xx and named xy; Segment 96.077194 -> 96.16491, all other functions and owned sections unchanged (text97.80485/EH99.587906/index99/rodata100). Scalar setters raise Raycast92.242424->92.41414; dedicated normalize helper raises Segment96.41053, but immutable old anonymous EH aliases collide, so higher text-only drafts are not retained source. Const backward source iterators invariant; counted backward loop98.37412 and named end accessor98.475525 regress from99.545456. Whole reversed EH group remains NonMatching, zero native gain; full fallback-linked DOL SHA1 exact.

## c22_u142_20261109
Source: Codex worker c22_u142_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u142 fn_80203C24:removed existing opt_common_subs pragma while preserving99.73283% text and100%ownedEH/index with long req (helper parameter remains int). Without pragma/int req98.854965%,520B;long req restores target524B and+E0 mr via distinct signed32 type web. Parameter-long alone invariant98.854965. Remaining7rows now pendingr5/openr4 vs targetr4/r5;base r6 exact. Aggregate MsgPopupState snapshot93.05344/532B;ReserveMsgPopup inline98.89313/528B adds branch;long req function-scope invariant;named outer int pending99.580154 shifts pending/base/flag to6/5/4;uchar open invariant. All attempts archived build/w. No range/flag/bridge edits, single fn cannot B-split;full fallback SHA1 exact,native gain0.

## c22_u149_20261109
Source: Codex worker c22_u149_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u149: fn80221104 improves98.15069->98.904106, same584B/EH8/index12 exact, 40->25 saved-GPR-only rows. Remove DrawNodes and hoist FadeObj** iterator to Draw scope98.18493; explicit caller-scope FadeObj* node98.39041. Narrow DrawItemTexts(ItemWnd*) with its own manager/loop98.83562; declare int i before mgr in helper98.904106. Retained. Hoist ItemWnd* before caller iterator/node regresses98.869865, reverted. Manager now targetr30, NextWnd base and digit loop exact; node objectr29 and whole coin loop exact. Residual ItemWnd base/counters, Next sprite count, node iteratorr28 vs targetr27. No pool/singleton or single-function B rescue. Full fallback DOL SHA1 exact; zero native gain.

## c22_u165_20261109
Source: Codex worker c22_u165_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u165 carobject: scalar coordinates into TransformComponent fix one load ordering, affine89.48387->89.96774,124B. Dot3 translation split86.90323 and output-ref/vector-first84.96774 rejected. Private MovementState grouping at1AC (CarTrivial vector+two floats, scalar initialization before vector writes) gives ctor91.09939 vs91.08925 and preserves264B primary EH after own weak dtor bridge __dt__13MovementStateFv->dtor_8019EB60. Neighbor fn8019A9BC AccumulateProduct(float&,right,left) transfers for matrix FPR operand partition: with original float out[16] nested loops ctor92.17647,1960B. Matrix44 scratch or explicit named output pointer+hoisted j/index/i loses outer unrolling77.263695/1724B; reject. Bool-only initializer-list invariant91.08925. Eleven exact functions stay100; TUtext96.756424/EH0/index0, primary EH unchanged from baseline plus one extra weak dtor entry. Still missing double-bool normalization, retained rotation r30, volatile loop GPR homes, scalar load schedule and physical/EH order. No pool-base residual, no B cut. Full coordinator fallback DOL SHA1ea30f3b1 exact; native gain0.

## c22_u173_20261109
Source: Codex worker c22_u173_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 1080 B.

acLib 802554DC: word/pair/word request copy becomes exact when port/arg are an 8-byte struct copied in a static inline C helper, with state and length member assignments around it. C++ implicit aggregate assignment scalarizes to serial word transfers and defers the enclosing function to TU end. C helper region restores exact copy and emission order. Contiguous mechanism B splits at 80255154 and 802554DC retain pooled .bss/.sbss in the tail; all five exact functions plus owned EH/data match 100%, and full DOL SHA-1 is exact. 80255154 improved85.82743->93.79204 through explicit board narrowing and inverse service branch; residual is loop base/coalescing and cur-2 hoisting.

## c23_u3_20261109
Source: Codex worker c23_u3_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u3 AI_CalcRivalAvoidance direct96.98726->97.242035/report97.257965,1256B. Natural nearestRivalWaypoint(path,const PhysicsPlainVec&) with named result and two-float RivalProbeOffset constructor replace diagnostic shape Id/Mul wrappers. Add own primary EH bridges@193/@194; extab97.22222/index100 unchanged, weak dtors identical. In-place normalization refs96.97134 rejected; literal1000/const distance98.23248/98.26433 but1252B and worse EH/index rejected (literal additionally unmapped). 45 aligned mixed register/other rows remain, early position base and normalization second turn load. Pool OTHER fn801ECA14 owns803BD920..803BDED4; safe merge interval801ECA14..801EECD8 spans9TUs and remains coordinator task. Singleton B impossible. Source fallback-linked; coordinator request1 full DOL SHA1ea30f3b1 exact, nativegain0.

## c23_u10_20261109
Source: Codex worker c23_u10_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u10 WallCollisionCheck 98.67523->99.15187/1712B: mutate a local length via void CollisionLength(float&) instead of returning a distinct inline value, giving target squared/Newton/clamp register web with no join branch (99.060745). Then scalar setTranslation(x,y,z) at both sites gives target RTL component evaluation/load/store ordering (99.15187). Outer hoisted squared temp alone fixes Newton webs but adds8B; do not retain it. Early-row/multiplyRows helper invariant; explicit table cursor adds initial r0 copy/EH regression; scalar vector ctor/default+set invariant, vector scale set worse; corner-loop helper exceeds inline budget; fully typed state invariant. Remaining32 aligned formatted rows are rotation pointer r22 vs late r7, endpoint/table r31/r30 swap, scaled x/z raw scratch and push y/z ordering. Primary EH48 bytes/dtor relocations exact, index12 raw exact with anonymous EH-symbol name. Aggregate EH92.30769/index66.66667 unchanged. Single function NM, no A/B/native gain; no config/range/shared-header changes or final full-link request.

## c23_u24_20261109
Source: Codex worker c23_u24_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u24 NamCamFlow: all22 functions present, no safe internal EH cut. New root cleanup bridge __dt__10NamCamRootFv->dtor_8007D0D4 fixes two ctor EH relocations; weak root body independently100% against existing72B target. Last ctor EH mismatch is array-construction failure cleanup: target MemoryManager_Free, old global __dla__ alias MemoryManager_TimedFree. Private allocation-specialized NamCamText plus class new[]/delete[] bridges and explicit ::delete[] for normal destruction gives all owned EH/extabindex100% without changing any function text score. Constructor/dtor bridges reuse canonical TextManager ABI/layout; no shared header changes. All4 text residuals remain (update99.69086, countdown99.0728, ctor99.76895/default99.841156 normalized, draw99.75096), and pre-existing physical function emission order still differs. .data80419DE0..80419DFC ownership again creates global dtk link-order cycle, reverted. .bss80598A60..80598AB0 requires coordinator merge across named TUs. TU honestNonMatching, zero native gain; coordinator full fallback DOL SHA1 exact.

## c23_u39_20261109
Source: Codex worker c23_u39_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u39: Pools already owned at base38aa69a1. Explicit const int* ID cursor with for step id++,i++ restores full target animation loop, raw98.48259->98.89718/report99.01327. Pointerr23/countr26 and pointer-before-output-offset increments now exact. Final scale literal1 and inline binding helper invariant; reverted. Source now2416vs2412B because separate implicit vtable lis/addi still extra; EH95.37037/index95 reflect PC/length regression (baseline95.679/index100). Retained higher-text NM draft per coaching; no native gain. Coordinator merge with Matching game/anon_8021A7C8.cpp still needed for implicit vtable pool anchor. Both pools remain100%; no config/range/bridge edits. Service fallback DOL SHA1 exact.

## c23_u82_20261109
Source: Codex worker c23_u82_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u82: Name quote-caption PtrVec receiver before layer/fade setup plus pScale-before-pX declarations makes CardEntry ctor801BC2EC text100%/2436B. Signed byte-offset character accessor improves Draw801BDB60 97.3615->99.41315/852B and fixes protected PC0x88->target0x8C. Explicit unsigned group stride plus outer group-address local and index-before-stride declarations improves Update801BE17099.487366->99.68411/2216B. Only second stride zero copy and final Tick receiver r28/r26 remain in Update; Draw has3 address-formation rows. Six own add-only current anonymous label bridges preserve all other scores.62/67 text exact; own EH relocations/sizes unchanged across64 entries and no legal internal EH cut. Whole TU remains NonMatching; coordinator full fallback DOL SHA1ea30f3b1 exact, native gain0.

## c23_u94_20261109
Source: Codex worker c23_u94_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u94 AI_UpdatePerFrameState: direct canonical lbl_806793D8[self->selectedKart].waypoint read avoids the FramePairRecord reinterpret view for an already correctly typed member. Fixes three scratch rows at +0x1EC/+0x1F4/+0x1F8, direct objdiff98.13513 ->98.16892 (report98.27872), strong2372B. Unlike c22 union-alias probe, no shared headers change. Whole speed-pass inline97.78885; rank-result aggregate94.5625/2412B; broad canonical per-record accessor98.109795, all discarded. Final owned EH unchanged and coordinator full fallback DOL SHA1 exact. Pair/proximity/rank/mode residuals and conversion-cookie misrename remain. Single-function TU cannot use B; no eligible pool ownership; native gain0.

## c23_u107_20261109
Source: Codex worker c23_u107_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u107 fn_801F27B4: merged pool already owned correctly. Split coarse symbol lbl804E4D30 size278 into20 plus six real object boundaries4D50/C8,4E18/20,4E38/30,4E68/70,4ED8/70,4F48/60 and export each existing static object through own bridge. Direct input handlers0ECC/1664/1C58 become100 without instruction changes. Added 28 own EH/index aliases and own order2690-first / address-sorted index / extra weakFlowFaderI-last: owned extab/index/data/ctors all100, text99.7887. Removing1244 propagation pragma is byte-invariant. Gray long-offset/inline-loop/direct-packer/cursor/color-class/reference-output trials do not improve99.53846/99.48276. Alpha shared-caller-locals/one-helper/gap-advancement do not improve98.42105/98.46491. Best initial source retained. Reversed first25 EH span and common data anchor block B; TU remainsNM. Full coordinator fallback build SHA1ea30f3b1 exact; nativegain0.

## c23_u129_20261109
Source: Codex worker c23_u129_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u129 ItemGridState_Init improves99.47369->99.70395/608B. Complete saved-GPR grid cycle RESOLVED: expand grid into caller with function-scope int row;int col; and move only one item-resolution iteration into static inline InitializeGridItem(self,player,ids,i), keeping ids snapshot/player/i/loop in caller. Original depth-two GridFallbackCandidate accessor now hurts; use direct ItemGridState_Init_rodata_803DC174[j] loads inside per-item helper. Declare unsigned-char found before int candidate, but compute candidate before found=0. All grid homes26/27/28/24/29 and 48-byte owned EH payload exact. Only eight fallback volatile rows remain: walker7/found5 vs target5/7; candidate3/index6 exact. Reference-output membership helper invariant. Final primary anonymous EH/index @84/@85 need future bridges; extra weak dtor remains. Singleton NM, no B cut/native gain; no new full-link request. Correct prior retry IDs c19_u167,c21_u109,c22_u132; archives use per-batch directories.

## c23_u128_20261109
Source: Codex worker c23_u128_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1636 B.

c23_u128: resultscene DEBC remains99.61539/624B after six bounded scale-lifetime, opacity-return/reference-inline, extern-scale, explicit-age/fraction and complete-subparticle-inline probes. Return/reference and explicit fraction change scratch colors but regress99.551285; other probes instruction-invariant. All source restored. Added35 own aliases (34 EH/index IDs plus SceneBase dtor->dtor8007D0D4) and own19-entry extab/index order; all544 owned EH bytes and15 relocs exact, extab/index/rodata100. Last text dtor8015E8AC owns first EH8000F45C, blocking every B cut. TU remainsNM, native0; coordinator full fallback DOL SHA1ea30f3b1 exact. Raw .text99.97469, all22 other functions100. Future source edits must account for the newly recorded anonymous EH aliases.

## c23_u142_20261109
Source: Codex worker c23_u142_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u142 ExplosionTumble_Init: Root(float&) in-place caller length, following fn_801E68B4/2102b089, improves92.81567->93.695854 at1736B; initial Z-before-X schedule now agrees. Add own @269/@270 bridges, owned EH48/index12 exact100. Identity inline with named zero/one92.73502 (zero f10), boundary alone invariant92.81567. Explicit Y/Z/X NormalizeCopy snapshots92.804146 (Y f13), reverted. Identity zero f3 vs f4, pose-copy shift, first root f9 vs f10, projection/cross/root and quaternion homes remain. Single function staysNonMatching; no pool residual/B cut; coordinator full fallback DOL SHA1 exact; zero native gain.

## c23_u145_20261109
Source: Codex worker c23_u145_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 29 fn / 8460 B.

c23_u145 TryArmInit: projection subtraction/scale rolled loops compile text invariant93.98783. Narrow literal0 cross comparison94.09489/1644B adds redundant comparison; consistent literal0 in TU-local axis Root/Normalize94.411194/1640B restores cross zero reload, but existing offset-based postprocessor adds third-NR wrong 3.0->0.5 relocation. Named doubles only in new axis Root avoid that additional misretarget, retaining94.253044/1640B with ownedEH98.4375/index95 unchanged after add-only@227/@228 bridges. Wider allzero94.313866 rejected; scalar fallback setter93.97567 rejected. Remaining projection reload and FP cross/fallback/quaternion webs. Existing secondNR source+328 wrong relocation remains; tools untouched. Singleton staysNM, native gain0; service fallback DOL SHA1 exact.

## c23_u157_20261109
Source: Codex worker c23_u157_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u157 acLib fn_80255154 improves 93.79204->94.37168 (912->908 B), extab100/index91.66667 unchanged. Replace peeled first sample + six with one seven-iteration wrap/read/decrement loop; long cur keeps cur-2 in preheader while int k controls history traversal. Rolled int-only 93.63717/900 B; baseline long-cur 91.24779/916 B; rolled int cur/long k invariant94.37168; explicit scan/output pointer walkers94.31858/908 B rejected. Remaining94 aligned rows largely volatile GPRs, with final pulse-loop extra mr and wrong counts base/coalescing. No data-pool anchor residual, no A/B rescue for single-function TU. Full fallback DOL SHA1 exact; native gain0.

## c23_u174_20261109
Source: Codex worker c23_u174_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3488 B.

c23_u174 fn_8020A6CC 95 -> 100%/104B: restore float output and name the intermediate float step = rate*t; then step = from + coefficient*step; value = step. This changes FP allocation and preserves the target fmadds f0;fmr f1,f0, all 26 instructions exact. Remove copied unused scaffolding and reuse canonical FlowFaderF x/y/z to avoid bias @61 colliding with prior add-only EH bridges; bias becomes @31, add own @32/@33 -> etb19420/eti29B1C. Matching flag, text/EH/index100, source main.elf input at8020A6CC size104, coordinator full DOL SHA1 exact. Inline coefficient helper split the FMA; double API/result coalesced the final copy, both rejected. No new ranges/shared headers/build logic.

## c25_u3_20261110
Source: Codex worker c25_u3_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u3: BootDispatcher 99.31995 -> 99.35759 via C static inline int BootOptionDisabled(unsigned char), which returns option==0. C frontend int comparison restores cardDisabled srwi5; C++ bool lowering had extrwi8,19. otherDisabled still extrwi. Primary text size6376 unchanged; extab67.36111/index33.333336/rodata100/data100 unchanged. Second wait ==0 (99.354454) and C error-init helper (99.31179) rejected for EH regressions. Pool merge needs coordinator scope across nine TUs; prior isolated .bss ownership cycle already recorded. Full fallback DOL SHA-1 OK; no native gain.

## c25_u17_20261110
Source: Codex worker c25_u17_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 7 fn / 10180 B.

c25_u17 fn_8018B31C: counter-scope rule46 retains one-line block-local int i in rotation loop. Raw94.276886->94.35414, report94.41471, text6472 unchanged;16 differing aligned rows fixed/no new mismatches (rotation counter r10 and rotation amount r8; nearby scratch reuse also aligns). Explicit WriteField n/start locals93.56613 reverted; flattened writer94.276886 invariant. Pool ownership already correct. BSS81.818184/84vs88 unchanged;EH/index/rodata100. One function cannot B; remains NonMatching. Coordinator build SHA1ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 OK; nativegain0.

## c25_u30_20261110
Source: Codex worker c25_u30_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2024 B.

c25_u30: CalcEarnedCoins 98.534485 -> 99.80604 with ONLY return type void -> int, implicit valueless exit (valueless-return-keeps-r3 / pattern54). No arguments added. MWCC emits return value expected warning. Working volatile registers now exact except four course-clear index shift/add rows +2E0..+2EC: target (course*4+reverse*2)+long; ours (reverse*2+long)+course*4. Reversing inner sum99.69827, nested sum helper/unsigned intermediate/long-last99.80604, direct cleared[8][2][2]98.72845; all discarded. Pool already owned/exact. Remains NonMatching, no A/B unlock/native gain. Full fallback build SHA1 exact.

## c25_u38_20261110
Source: Codex worker c25_u38_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 12 fn / 1876 B.

c25_u38: clItemBoxManager_nm1 freshly compiles all12 bodies100 at646e8b00 (pattern52 already present). Promotion needed22 own EH aliases plus18-entry order incl7 discardable weak dtors. First Matching link permuted functions despite100 objdiff. Deferred,auto + reverse ordinary definitions/helpers first fixes strong order; explicit void* ListImpl remove_if/erase/insert/ctor specializations and out-of-line private base dtor put retained tail Remove/Erase/Insert/Init/dtor in target order. No data/split edits. Owned text1876/EH204/index132 all100; final source-linked main.elf all12 addresses/sizes exact, DOL SHA1ea30f3b1 exact.

## c25_u48_20261110
Source: Codex worker c25_u48_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 452 B.

c25_u48: resultscene_nm1 all25 symbols present; result_screen_update unchanged direct99.90323 after six bounded source probes (see handoff). Reverted all source. Added50 @etb/@eti aliases plus SceneBase dtor bridge, own extab/index order with7 extra weak dtors last, and extab_padding C702 twice (stream, not once). Owned852B EH now differs only register byte8000F6F1:1D vs target1E; all25 owned index rows exact, other24 functions remain100. Every24 internal cut crosses reversed EH ordering; no B rescue. Full coordinator build SHA1ea30f3b1 exact; native gain0.

## c25_u55_20261110
Source: Codex worker c25_u55_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u55 fn_8018E6FC: 99.06888 -> 99.73214, text1568/EH8/index12. Keep updateMatrices inline but move int matrixIndex and unsigned matrixOffset to caller and pass references. Inverse of regalloc_patterns 67: optimizer/ValueNumbering.c isCSEop limits aggressive equal-li merging to compiler temps, so named caller locals retain independent li instructions. Unlike c22 full-loop expansion this fixes +22C lfs f31;+230 li r30,0;+234 li r31,0 without perturbing remaining matrix/search webs. Remaining21 operand rows point r7/q r9 vs targetr9/r7. Point through inline or caller ref fixes point but moves p r8->r7; free search result by ref/name invariant, expanded break search regresses. All EH exact; no A/B rescue for singleton TU. Full fallback build SHA1 exact.

## c25_u56_20261110
Source: Codex worker c25_u56_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 67 fn / 23644 B.

c25_u56: base already contained the fn_80179F60 pattern45 fix, but merged split-era source was not layout-correct. Restore 4a1f4f60 original unsplit declaration layout/anonymous namespace, retain current QuadCross and named InQuad locals plus explicit lbl_806D8E90, use canonical HSD_JObjSetMtxDirtySub, and keep YIState::UpdateT as a generic inline member template rather than an explicit specialization. The specialization emits before MR dtor; generic inline template instantiates last. All 65 functions, 61 owned EH payloads+relocations and linked addresses exact; Matching full DOL SHA-1 OK. No data padding or bridge-map edits needed.

## c25_u100_20261110
Source: Codex worker c25_u100_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u100: recovered documented endpoint-first Raycast form from gave_up (both endpoints copied before delta=*to then delta-=*from), independently verified 92.242424->94.252525/.text98.16759. All ten other function scores, extab95.83333/index89.393936/rodata100 unchanged. Canonical nontrivial vector input types invariant; endpoint-component loop92.30303 discarded. Segment direct-facing fields96.04211, extern-zero94.79649, uncached normal member reads96.04211 all reverted. No new 100% mechanism; whole reversed group stays NM. Build service exit0/SHA1ea30f3b1 exact, source not linked, native gain0.

## c25_u109_20261110
Source: Codex worker c25_u109_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u109 acLib fn_80255154: 94.37168 -> 97.76106%, 908 -> 904 B (target exact size). Separate pulse-loop counter (95.22124) then move complete history-update + pulse-generation block into one UpdateCoinHistory(coin,service) static inline returning pressed. This makes counts base an inline temp and removes the extra final-loop pointer copy; final pulse registers now match except zero setup li vs mr and order. EH extab/index both 100%. Scan still rotates cur/n/k/walker/i/mask (source r30/r8/r9/r12/r11/r10 vs target r9/r30/r12/r8/r10/r11). Inline getter alone invariant; hoisting k/j/n within helper invariant. No pool ownership residual or A/B rescue. NonMatching retained; full fallback DOL SHA-1 exact. Compiler explanation is documented coalescenodes temp/temp eligibility vs unmergeable named/temp copy; no debugger trace available.

## c25_u115_20261110
Source: Codex worker c25_u115_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c25_u115 DNStartDino Spawn 80229998: direct objdiff 90.020134 -> 95.48993 (584B vs target596). Retained float vz = scale*(Rand()-half)+dir[i].z; then sx/sy/sz snapshots; then embers[k].vel.z=vz before position writes. This places scale XYZ loads before vel.z stfs as target. Early-continue search guard invariant90.020134. Small inline InitEmberPosition including snapshots/Z store invariant95.48993. Named half refinement93.66443 regressed. Residual outer-loop initial jump/continuation island plus FPR webs/address r9/r10; exact target instruction ordering improved but no100/no native gain. Rule temp-to-local. No compiler-source rule verified because source/debugger unavailable; do not treat as a traced diagnosis.
