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
