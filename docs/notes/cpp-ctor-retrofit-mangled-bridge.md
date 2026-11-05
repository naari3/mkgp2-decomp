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
__vt__11ServiceMenu       -> lbl_803FDE64            (vtable store)
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

Rescue of anon_801FEBD8 / anon_80202148 / anon_80207324: correct VHolder<FlowFaderF/I> mangled length is 21. Map implicit FlowFaderI destructor to fn_801F26C8 (target vtable lbl_804E5284). Append weak destructor EH after owned entries in extab_order. Local synthetic RTTI can retain duplicate .data/.sdata even when text objdiff is 100%; explicit calls to the same CW dynamic-cast runtime with external target RTTI records removed all such sections while preserving every function at 100%. Full-link acceptance remains pending.

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

After a C++ split, compiler RTTI symbols can stay STB_LOCAL even for external-linkage classes. A fallback TU cannot resolve such definitions by global name. Existing postprocess bridge supports global:<target> values; mapeffect uses __RTTI__11clMapEffect -> global:lbl_806CFAD0. Audit the intersection of fallback undefined names and source local defined names; payload bytes stay unchanged.

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

Popup rescue: opt-in suppression of unused Open/Close dynamic_cast helpers avoids emitted RTTI even with -RTTI on. Exact Close wrapper uses the same runtime call fn_80271340(t,0,lbl_806D0268,lbl_806D0260,0) with external target RTTI records. First-declared SceneListImpl _key2 suppresses its vtable. Tail MsgPopupCoin dtor needs primary EH order before appended weak FlowFaderI/F and ResCtrl EH. A split with only two leaf getters has no extab, so omit extab_padding while retaining original compiler flags; dtk extab clean otherwise fails.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

MinimapHud ctor 80219B24: separate sequential scopes for ResCtrl a/b/c/d reproduce exact 196-byte primary EH while all 1232 instruction bytes stay exact. Canonical VHolder mangled length is 21; bridge MapBase destructor to dtor_8021617C. Owned ctor jump table is .data 804EDC60..804EDC84.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

No-EH C++ leaf split: extab_padding invokes dtk extab clean, which errors when no extab exists. For MinimapHud Start/Draw, use ordinary compile rule and rename owned target symbols to actual CW mangled names (Start__10MinimapHudFi, Draw__10MinimapHudFv); definitions remain verbatim. Full-link acceptance pending.

## c2_r2_enemyface_20261105
Source: Codex worker c2_r2_enemyface_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 32 fn / 5952 B.

EnemyFace 8022BEB4 text/EH is exact but emitted clEFace3D vtable under RTTI-off has null at +0 whereas target 804EE134 references lbl_806D0618. Leave destructor NonMatching and isolate exact Trigger 8022BF2C; do not promote based solely on 100% text.

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

c5_s11: fn_80203F5C popup open needs explicit else return 0 when both cur and pending are occupied. TU-local copy plus external target RTTI runtime fn_80271340(t,0,lbl_806D0268,lbl_806D0260,0) gives 340 bytes and all owned sections 100%, no emitted data. Cursor destructor 802051E8 promotes unchanged text with weak FlowFaderI bridge to fn_801F26C8; extra EH discards. YesNoCursor Update declaration px before py fixes FP homes (99.72603 to 99.863014), but list/visible r30/r31 swap remains after scope/helper attempts. Full DOL SHA-1 and ELF positions verified for two promoted functions.

## c5_s12_anon8020aad4_20261105
Source: Codex worker c5_s12_anon8020aad4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 668 B.

c5_s12: BattleMenu ctor 8020BACC cached list r28->r30 resolves by extracting fn_801F4DF0(l,fn_80201A48(0),2) into static inline AddInitialTask(FlowSceneList *l). Exact 668-byte text, 52-byte data and owned 96-byte EH/12-byte index after bridging @106 jump table, @107/@108 EH names; append weak copies in extab_order and add DATA_ALIGN4_WEAK_TUS. Coordinator full build SHA-1 OK; main.elf fn at 8020BACC size668 with source input true. Same helper fixes GrandPrix list but leaves cup r29 vs r30 (99.77401%). AAD4 switch/if forms fail to retain target branch-over-branch. ItemShowcase aggregate-reference or aggregate-part representation leaves same extra base move.

## c5_s13_anon8020c974_20261105
Source: Codex worker c5_s13_anon8020c974_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 728 B.

c5_s13: CardModeRoot::OnTaskDone text/extab/index were 100%, but dynamic_cast emitted extra local RTTI (.data 76 B/.sdata 24 B). Explicitly calling existing fn_80271340(task,0,lbl_806D0310,lbl_806D0308,0) with canonical extern 8-byte RTTI records preserves all text and removes duplicate data; full-link SHA-1 OK. fn_8020F220 needs flag flip only. Draw Remove named result assignment restores return/argument stack slot order, 96.55224 to 96.61194; iterator SP+10 vs +14, missing assignment copy and r4 caching persist. ScoreDisplay scoped scale and explicit x/y/z/scale locals both leave final-three-block FP coloring unchanged; original retained.

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
