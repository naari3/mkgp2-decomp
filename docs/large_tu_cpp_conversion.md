# 大 TU の C++ 変換手順 (project レーン設計、2026-07-19)

`scan_extab_actions.py --retrofit` の project レーン (auto_ONKARTHIT_block.c /
KartTireFX.c / auto_800A8F4C_block.c) を C++ 昇格するための手順設計。

関連:
- `docs/notes/cpp-ctor-retrofit-mangled-bridge.md` — per-fn retrofit のレシピと制約
- `docs/large_extab_group_strategy.md` — reversed extab group bundle の背景
- `docs/unit_first_strategy.md` §4.6 — retrofit レーンの運用

## 前提事実 (検証済み)

1. **extab 並び制約 (2026-07-19 実験で確定)**: object 内の extab section は
   「auto-emit 一括 (定義順) → .extab_user 一括 (定義順)」で並ぶ。
   fn address 順への interleave は起きない (ServiceMenu_Page で中間 fn だけ
   manual に戻す実験 → SHA-1 fail)。
   → 多 fn TU の **per-fn 変換は現状不可能**。変換済み fn 群が TU の extab
   address 順の先頭 prefix を成す場合のみ漸進可能だが、ONKARTHIT の先頭は
   KartItem_OnKartHit (1664B、最難関級) なので実質詰み
2. asm void 関数には CW は extab を auto-emit しない → park が 1 本でも
   残る限り manual emit は消えない (all-or-nothing にできない)
3. real C++ 化しても解けない register-identity が存在する
   (ItemObjectManager_Init 実例) → 大 TU 内で「全部 C++ 化」は保証できない

1+2+3 の帰結: **「TU 丸ごと一括変換」も「per-fn 漸進」も、そのままでは
成立しない**。並び制約そのものを外す基盤が必要。

## Phase 1: extab reorder postprocess (基盤、最優先) — 実装済み 2026-07-19

**訂正 (実装中の発見)**: 当初案の「fn address 順にソート」は誤り。
auto_800A8F4C_block で **target の extab 並びが fn address 順でない**実例を
観測した (最後の fn の entry が section 先頭。原 TU 境界 / 原 link 順の
名残りが binary に残る)。address 順仮定でソートすると既存 matched TU を
壊す (v1 実装で実際に壊れた)。

確定した実装 (`tools/reorder_extab.py`):

- 並び順は推定しない。**TU ごとに目標順を `tools/extab_order.json` で宣言**
  (rename 後の関数名リスト = extab entry の並び)。宣言が無い object は
  section 構成に関わらず絶対に触らない (安全側)
- 処理: 宣言に一致する object の extab / extabindex entry を host section に
  統合して宣言順に並べ、entry symbol の移動と reloc (r_offset / addend /
  section symbol 参照) を付け替える。ELF32 BE の全書き直し
- 検証済み:
  - 全 TU regression (宣言なし = 全 no-op) で SHA-1 OK
  - 受入テスト: ServiceMenu_Page を auto 3 + manual 1 (中間位置) の mixed に
    して宣言 → reorder 発動 → **SHA-1 OK** (並び制約の除去を実証)
- 運用: mixed 化する TU は、変換前の manual emit 順 (= target 一致実績の順)
  をそのまま extab_order.json に宣言してから per-fn 変換を始める

これで並び制約が消え、**任意の TU で per-fn retrofit が可能**。大 TU は
「ただの promote queue」に化け、retrofit レーンの dispatch/project 区分も
実質不要になる (大 TU は物量の問題だけが残る)。

## Phase 2: ~~TU-wide -lang=c++ checkpoint~~ → 不要 (2026-07-19 撤回)

**`#pragma cplusplus on/off` が CW 1.3.2 で動く**ことを確認した。.c ファイル内の
island だけを C++ にできる (mangled symbol / real ctor/dtor が出る) ので、
TU 丸ごとの -lang=c++ 切替も extern "C" wrap も不要になった。
10.7k 行 / open prototype 155 個の変換リスクが丸ごと消えた。

必要な TU 側変更は `-Cpp_exceptions on` を extra_cflags に足すだけ
(既存 C fn は元から `#pragma exceptions off` で包まれており codegen 不変。
flag が off のままだと pragma exceptions on でも extab action が emit されない)。

## Phase 3: per-fn promote queue (通常運転に合流) — 1 本目実証済み 2026-07-19

**dtor_8005278C を ONKARTHIT 内で real C++ dtor 化して SHA-1 OK**。手順の実物:

1. TU の extab / extabindex emit 順を `tools/extab_order.json` に宣言
   (ONKARTHIT は 76 entry。抽出 regex は struct 型と array 型の両方の
   `__declspec(".extab_user")` 定義を拾うこと — 取りこぼすと宣言不一致で
   reorder が発火しない)
2. configure に `-Cpp_exceptions on` を追加 (これが無いと pragma exceptions on
   でも extab action が出ない)
3. 対象 fn の asm body + manual extab/extabindex struct を削除し、
   `#pragma cplusplus on` island 内に real C++ 定義を書く
4. **dtor は `throw()` 指定が必須**: 元コードの dtor は exception
   specification 付きで、0x8F/0x8D の SPECIFICATION action record と
   `__unexpected` island はここから出る。`~Holder() throw() { delete p; }`
   で target extab 40B が byte 一致した
5. mangled 名 (`__dt__14Holder8005278CFv` 等 — length prefix は文字数を
   正確に) を extab_user_renames.json で橋渡し
6. build → reorder 発火を確認 → SHA-1

残りの dtor 連隊 (800528B0/8005292C/800529A8/80052A58/80052AD4/80052B50/
80052BCC/80052C48/80052CC4/80052D40) は同型 (member 型名と rename 対だけ
差し替え)。その後 中物 → 大物 5 本。

Phase 1+2 が済めば、park 25 本 (ONKARTHIT) は既存の
「同 TU 内多 sub 並列 promote」パターン + retrofit claim で回せる:

1. **dtor 11 連隊から** (dtor_8005278C 系 + dtor_800529A8):
   全部 `struct Holder { T *p; ~Holder() { delete p; } }` の同型。
   class 定義 1 波で 10 本、member 型の __dt__ rename ~10 対を flat map に追加
2. **中物**: Bitset_Init / ItemEffect 4 本 / WarpDashMgr_GetOrCreate 等
3. **大物 5 本** (KartItem_Tick/PerFrameStep/OnKartHit, CarObject_Init/
   MainUpdate): KartItem (0x380) / CarObject の class layout を Ghidra から
   取り込みつつ。CarObject_Init の extab 412B = member ctor 多数 =
   class 定義が一番育つ場所。dtor 連隊で確定した member 型定義を再利用する
   ため、**連隊 → 中物 → 大物の順序に意味がある**
4. claim は TU 単位 (`retrofit:game/auto_ONKARTHIT_block.c`) で排他し、
   fn 単位の分担は main の dispatch 管理に任せる (claim 粒度を細かくしない)

## Phase 4: 残りの project TU

KartTireFX.c (asm 13) / auto_800A8F4C_block.c (asm 12) に同じ手順の縮小版。
KartTireFX は onmokoworks の完食 unit なので着手前に claim で声かけ。

## 失敗時の退路

- Phase 1 の reorder tool が難航 → prefix 漸進 (先頭 extab fn から順に変換)
  が唯一の代替だが、ONKARTHIT では先頭が最難関のため実質保留になる。
  その場合 project レーンは凍結し、dispatch レーンの供給が枯れるまで放置で損はない
- Phase 3 で解けない fn (register-identity 等) は asm_fn のまま残してよい —
  reorder があれば混在が許されるので、解けた分だけ真 C 化が進む
