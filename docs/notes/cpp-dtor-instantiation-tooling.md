# C++ dtor instantiation tooling: EH-class dtor の byte-identical 再現 (検証ログ)

ゴール: OnKartHit TU の EH-class 13 fn (KartItem_Dtor + 末尾 dtor 11 + StlList_InsertBefore) を
「real classes + throw() spec の C++」で回収する tooling の確立。
[exceptions-on-eh-scaffolding-unpromotable.md](exceptions-on-eh-scaffolding-unpromotable.md) の
unlock path「retrofit the bundle as .cpp」の実証フェーズ。
観察 (事実) と仮説 (推論) を分け時系列で追記。

## 2026-06-12: step 1 — 0x7C 標準形 dtor の isolation 検証 → **code + extab とも byte-identical**

probe: `tools/compiler_probe/onkarthit_dtor_cpp/holder.cpp`

```cpp
extern "C" void *MemoryManager_TimedFree(void *ptr);
struct Pointee {
    char pad;
    ~Pointee() throw();   /* 定義は別 TU (target では Free_IfOwnedShort 等) */
    static void operator delete(void *p) { MemoryManager_TimedFree(p); }
};
struct Holder {
    Pointee *p;
    ~Holder() throw();
    static void operator delete(void *q) { MemoryManager_TimedFree(q); }
};
Holder::~Holder() throw() { delete p; }
```

flags: game lib 標準 (`-Cpp_exceptions on`, `-lang=c` **なし** = C++)。

結果 (観察):
- emit された `__dt__6HolderFv` (size 0x7C) は **dtor_8005278C と全命令一致**
  (prologue FP frame `mr r31,r1`、`mr. r29,r3` null check、`lwz r3,0x0; li r4,1; bl <member __dt>`、
  `extsh. r0,r30; ble`、`bl MemoryManager_TimedFree`、`bl __unexpected` island、back-chain epilogue)。
- **SPECIFICATION extab 40 bytes も完全一致** (manual `extab_dtor_8005278C[40]` と同値:
  `18180000 00000034 00040018 00000054 00000024 00000000 8F000000 0000004C 00000008 8D000008`)。
  extabindex entry も自動 emit。
- リポジトリ初: 「`__unexpected` island 持ち fn は C から match した前例なし」
  (exceptions-on note) を C++ で破った。

機構の対応 (観察 → 確立):
- CW 1.3.2 dtor 規約 = `void *__dt(this=r3, flags=r4:short)`。null check は callee 内。
  `delete p` → `__dt__<Pointee>(p, 1)` の直接 bl (非 virtual)。
- `flags > 0` (`extsh.;ble`) で self を class operator delete (インライン展開 =
  `bl MemoryManager_TimedFree`) で解放。
- `throw()` (empty exception spec) が SPECIFICATION extab + `__unexpected` island +
  ACTIVECATCHBLOCK action を生む。
- 残り 0x7C 同形 9 dtor (TwoSubDtor/EffectSteering/KartEffectFadeTransit/PlayCamera/
  VisualEffectHolder/InputCmd/KartDriver/CarObject/AudioChannel の各 *_Dtor callee) は
  member dtor の bl 先 reloc が違うだけで、同じ class 形で出る (仮説、ほぼ自明)。

シンボル名の扱い (統合時): emit 名は mangled (`__dt__6HolderFv`)。symbols.txt の
`dtor_8005278C` / `Free_IfOwnedShort` 等は自前ラベルなので、採用する class 名から決まる
mangled 名へ rename すればよい。

## 2026-06-12: step 2 — dtor_800529A8 (0xB0) 二段変種を sweep → 構造一致、scope nesting 1点のみ残

probe: `tmp/dtorcpp/twolevel{,2,3,4,5}.cpp` (二段 ownership form の探索)。

確立 (観察):
- **size 0xB0 / island 2個 / SPECIFICATION extab 2スコープ / prologue(r28-r31 save)・epilogue 一致**。
- twolevel2 (`Outer{Inner* m}; Inner{int x; SubHolder h@+4; ~Inner throw(){}}`;
  `SubHolder{Sub* sub; ~SubHolder throw(){delete sub;}}`、各 class operator delete) が、
  target の distinctive な **`addic. r0,r30,0x4; beq` (embedded sub-object の調整付き null check)** +
  `lwz r3,0x4; li r4,1; bl <Sub __dt>` + 二重 TimedFree + 二重 island を再現。
- → 0xB0 変種は「m = Inner* を delete、Inner が +4 に embedded SubHolder を持ち、その dtor が
   delete sub する二段構造」で出る、と確定的に近い。

残る 1 点 (観察 → 仮説):
- target は **island1 が「sub-dtor の bl」と「inner free (TimedFree m)」の間**にある
  (`bl SubObject_Dtor; b →free(island skip); island1; free`)。mine は両方が同一 spec scope で
  **island が free の後**。
- 意味: target では inner free が **outer (Outer::~Outer) の spec scope** (island2 側) に属し、
  SubHolder の spec (island1) は sub-dtor だけを覆う。mine は free まで SubHolder scope に入る。
## 2026-06-12: step 2b — 0xB0 scope nesting を 4 variant で sweep → source 制御不可と判定 (観察)

extab raw byte を target と word 単位で diff (twolevel2):
- 差は PC-action table の w2/w3/w5/w6 と action body の w11 (island1 PC) のみ。
- target: range1 = (PC 0x4C, n=0, action island1-SPEC)、free(m) は +0x60 で **island1 の後** → island2(Outer spec 0x20)帰属。
- mine : range1 = (PC 0x4C, n=2) が `mr;free` を含む、free(m) +0x50 は **island1 の前** → island1(0x8)帰属。
- 構造差は emission 順だけ: target `[sub-dtor][island1][free(m)][free(this)][island2]`、mine `[sub-dtor][free(m)][island1][free(this)][island2]`。

variant 結果 (`tmp/dtorcpp/twolevel{6,7,8}.cpp`、compile = `tmp/dtorcpp/build.sh` = shipped mwcceppc.exe を実行のみ + dtk disasm):
- **twolevel6** (明示 `if(m){m->~Inner(); MemoryManager_TimedFree(m);}`): 2-island が**崩れ単一 scope に collapse** (size 0x9C)。明示 ~Inner(complete dtor 呼出) + 空 body が SubHolder spec と Outer spec を merge。
- **twolevel7** (per-class delete を外し global `operator delete`): Outer dtor 0xB0 は維持だが free(m) は island1 のまま、かつ余計な `__dl__FPv` fn が emit (target は free を直接 inline、不一致)。
- **twolevel8** (Inner の explicit `~Inner(){}` 削除 = implicit dtor): size 0xA0、**1-island に collapse**。implicit ~Inner は独自 spec scope を作らず全部 merge。

判定 (観察 → 仮説): 2-island 構造の保持には Inner の **explicit `~Inner() throw()`** が必須。だが `delete m` の
operator-delete (free) を member-scope(island1) でなく function-scope(island2) に割るのは CW 内部の
EH-scope 割当ヒューリスティック (deleting-dtor inline 時の free 帰属) で、試した source 形では制御不可。
構造 (size 0xB0 / 2 island / addic.idiom / 二重 free) は完全再現済。残差は extab nesting の 5 word のみ。
→ **この 1 fn (dtor_800529A8) の byte-identical 化は保留**。tooling viability は 0x7C (9 dtor) で確定済のため
先に進む。0xB0 の EH-nesting は後日 colorer/EH-scope の trace (FUN 群未特定) で機構解明する余地あり。

## 2026-06-12: step 2c — 方法論検証「multi-member 文脈で割れるか」→ 否定 (観察)

KartItem_Dtor (0x8004E2B0) の **member 0x40** は dtor_800529A8 と同型の 2-level (`Inner*`、embedded
subobject @+4) だが、そこでは **free(m) が sub-dtor とは別 island (0xdc) に正しく入る**
(`bl KartItemSubObject_Dtor; b →free; /island 0x1c/; free(m); b; /island 0xdc/`)。
→ 「multi-member 文脈なら free が outer scope に割れる」仮説を立て `tmp/dtorcpp/multi.cpp`
(Outer{Inner* m; Other* o} で sibling 追加、逆順 `delete o; delete m`) で検証:
- **否定**。free(m) は依然 sub-dtor 直後 (0x5C) で island は後 = island1 帰属。sibling 追加では割れず。

つまり KartItem の 0x40 member と dtor_800529A8 (同じく member offset 0 ではなく 0x40/0x0) の差は
sibling 数ではない。KartItem の各 member dtor 前には **slot-address 検査 `addic. r0,r29,0xNN; beq`**
(this+offset==0 の dead-check、非零 offset member の idiom) があり、これが EH-scope 構造を変える可能性
(仮説、未確証)。dtor_800529A8 は member offset 0 で `addic.` は embedded subobject (m+4) にのみ付く。
→ EH-scope 割当の discriminator は class shape (member offset / base / dtor spec 推論) に依存し、
minimal-repro では誤誘導する。**byte-identical には実 class 全体の再構築が要る**という方法論的結論。

## 2026-06-12: 戦略整理 — KartItem_Dtor は dtor tooling と large-fn reconstruction の hybrid

KartItem_Dtor (0x368=872B, 12 island, 404B extab) の構造を白箱化 (asm 5721-5973):
- **本体ロジック (非自明)**: vtable 設定 (lbl_803F75F8 を +0x0/+0xc に store)、g_playerCarObject=0、
  member 0x20/0x21 条件での StrPcb 4 連 (SetCmdByte2d/2e, SetCounterField14, SetCmdByte2f)、
  g_carObjectList から StlList_RemoveByValueField、g_carObjectCount 減算 + list-owner vtable 呼出。
- **member dtor 逆順** (15 個、うち 12 が throw() spec island): 0x58/0x5c=dtor_80209180、
  0x54=Free_IfOwnedShort(island 0x124)、0x50/0x4c=raw TimedFree(island なし)、
  0x48=TwoSubDtor_Pending(0x10c)、0x44=EffectSteering(0xf4)、0x40=2-level(0x1c+0xdc)、
  0x3c=KartEffectFadeTransit(0xc4)、0x38=PlayCamera(0xac)、0x34=VisualEffectHolder(0x94)、
  0x30=InputCmd(0x7c)、0x2c=KartDriver(0x64)、0x28=CarObject(0x4c)、0x24=AudioChannel(0x34)。
- **base dtor 2 個** (非 deleting flags=0): +0xc=dtor_800AA888、+0x0=dtor_80060024。self-free は最後。

→ KartItem_Dtor を byte-identical 化するには (a) 15 member + 2 base の実 class 定義、
(b) **本体の StrPcb 条件・list 操作・count 減算の byte-identical 再構築** (= large-fn reconstruction 相当) が要る。
純粋な「dtor tooling」ではなく hybrid。ユーザ指定順 (tooling 先 → large-fn 後) では本体部分が後者に該当。
**tooling phase の純 dtor 成果は 0x7C 9 fn (byte-identical 確定) で確立**。0xB0/KartItem/StlList の 3 つは
各々 large-fn 級の深掘りが要る = 方針分岐点。

**重要**: 0x7C 標準形 (9 dtor) は step1 で完全一致済。0xB0 は 1 fn (dtor_800529A8) のみの変種で、
構造は出ており scope nesting の 5 word のみ残 (source 制御不可と判定)。tooling 全体の viability は確定。
次の本丸は KartItem_Dtor (12 island / 404B extab) の多 member class 再現。
2. **KartItem_Dtor (0x8004E2B0)**: 12 island + 404B SPECIFICATION extab の大物。
   多 member class の本体 dtor。
3. **StlList_InsertBefore**: MSL std::list::insert 相当。クラス+template の再現 or
   手書き同形 class が要る。
4. **統合 (mix-failure 制約)**: auto-extab は .extab_user より前に link されるため、
   A 化区間は TU 先頭から連続が必須。末尾 dtor 群の回収は手前の extab 持ち fn
   (大型関数含む) の clean C/C++ 化が前提 ([approachA-roadmap.md](approachA-roadmap.md))。
   isolation 証明 ≠ 即統合可。順序: Phase 3 (index 0-17 A 化) → KartItem_Dtor →
   大型関数で区間拡張 → 末尾 dtor。
