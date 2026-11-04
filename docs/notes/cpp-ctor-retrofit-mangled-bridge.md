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
