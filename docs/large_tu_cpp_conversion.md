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

## Phase 1: extab reorder postprocess (基盤、最優先)

`tools/postprocess_extab_user.py` に「.o の extab entry を extabindex の
fn 参照 address 順に並べ替える」step を追加する。

- 入力: compile 済み .o (auto extab + renamed .extab_user が混在)
- 処理: extabindex の各 entry (fn reloc, size, extab reloc) を fn address
  (= reloc 先 symbol の値、UND なら symbols.txt 引き) でソートし、
  extab / extabindex 両 section の内容と **section 内 reloc の r_offset** を
  並べ替え後の配置に付け替える
- ELF32 big-endian の機械操作。同 file に byte-patch の前例あり
  (patch_memorymanager_timedfree_extab)
- 導入手順: 既存の全 extab TU で **no-op であること (SHA-1 不変)** を
  regression してから有効化
- これが入ると並び制約が消え、**任意の TU で per-fn retrofit が可能になる** —
  大 TU は「ただの promote queue」に化ける。retrofit レーンの
  dispatch/project 区分も不要になる (全部 dispatch 化)

技術リスクはここに集中する (reloc 付け替えの正確性)。ただし効果は全 TU に
及ぶので、最もレバレッジが高い一手。

## Phase 2: TU-wide -lang=c++ checkpoint

対象 TU (まず ONKARTHIT) を `-lang=c++` に切替える下準備 commit:

- 既存の C 関数定義・extern 宣言を `extern "C" {}` で包む (symbol mangle 防止)
- asm fn はそのまま (extern "C" 内で合法)
- build して **SHA-1 不変**を確認 → checkpoint commit
- ここで壊れる場合は C/C++ の codegen 差 (enum 幅、prototype 等) を個別に潰す。
  この commit 単体では機能追加ゼロなので bisect しやすい

## Phase 3: per-fn promote queue (通常運転に合流)

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
