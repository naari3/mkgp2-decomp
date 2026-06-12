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

## 未検証 (次 step)

1. **dtor_800529A8 (0xB0) 変種**: 二段構造。member (r30=this->+0x0) を null check 後、
   `addic. r0,r30,0x4; beq` の null-propagation idiom を挟んで `KartItemSubObject_Dtor(m->+0x4, 1)`
   → `MemoryManager_TimedFree(m)` → flags check。inline member-dtor 展開 + 調整付き
   null check と思われる (仮説)。empirical に C++ form を sweep して当てる。
2. **KartItem_Dtor (0x8004E2B0)**: 12 island + 404B SPECIFICATION extab の大物。
   多 member class の本体 dtor。
3. **StlList_InsertBefore**: MSL std::list::insert 相当。クラス+template の再現 or
   手書き同形 class が要る。
4. **統合 (mix-failure 制約)**: auto-extab は .extab_user より前に link されるため、
   A 化区間は TU 先頭から連続が必須。末尾 dtor 群の回収は手前の extab 持ち fn
   (大型関数含む) の clean C/C++ 化が前提 ([approachA-roadmap.md](approachA-roadmap.md))。
   isolation 証明 ≠ 即統合可。順序: Phase 3 (index 0-17 A 化) → KartItem_Dtor →
   大型関数で区間拡張 → 末尾 dtor。
