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
- 試した形 (Inner に operator delete 無し / global delete / 明示 `m->~Inner(); free(m)` 等) は
  いずれも scope を割れず。free を Inner deleting-dtor ではなく Outer の body 側に出す nesting が要る。
  → 次 step で「Inner を非 deleting ~Inner で破棄 + 別 expression で free」の clean form を詰める。

**重要**: 0x7C 標準形 (9 dtor) は step1 で完全一致済。0xB0 は 1 fn (dtor_800529A8) のみの変種で、
構造は出ており scope nesting の詰めだけ。tooling 全体の viability は確定。次の本丸は KartItem_Dtor
(12 island / 404B extab) の多 member class 再現。
2. **KartItem_Dtor (0x8004E2B0)**: 12 island + 404B SPECIFICATION extab の大物。
   多 member class の本体 dtor。
3. **StlList_InsertBefore**: MSL std::list::insert 相当。クラス+template の再現 or
   手書き同形 class が要る。
4. **統合 (mix-failure 制約)**: auto-extab は .extab_user より前に link されるため、
   A 化区間は TU 先頭から連続が必須。末尾 dtor 群の回収は手前の extab 持ち fn
   (大型関数含む) の clean C/C++ 化が前提 ([approachA-roadmap.md](approachA-roadmap.md))。
   isolation 証明 ≠ 即統合可。順序: Phase 3 (index 0-17 A 化) → KartItem_Dtor →
   大型関数で区間拡張 → 末尾 dtor。
