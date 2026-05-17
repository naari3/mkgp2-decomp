# Large extab-group strategy (Phase 3)

> **Status: DRAFT (2026-05-18)**. wall-clock budget の見積もり (特に Section 2.2 の「1 sub で 1 batch 完了は budget 的に無理」) は **empirical 根拠が弱い推定**。Phase 3a-small (11-20 fn group の 1 件) を実行して以下を計測した後 refine する予定:
>
> - 1 sub の wall-clock budget で何 fn 処理できるか
> - asm_fn 退避だけの scaffold-only batch なら 1 sub で何 fn 行けるか
> - mega-bundle pattern を main 側 vs sub 側どちらでやる方が筋がよいか
>
> 計測後の refine 想定箇所: Section 2.2 (Phase 3b mega-bundle pattern の役割分担)、Section 3.1 (`batch_type` enum 候補に `scaffold_only` 追加するか)、Section 5 (Phase 順)。

`docs/per_fn_matching_strategy.md` Phase 3 の詳細展開。**>10 fn の dtk reversed-extab group** にどう取り組むかの設計。

関連:
- `docs/per_fn_matching_strategy.md` — Phase 1 で導入した per-fn asm_fn 退避 (この doc の前提)
- `docs/orchestrator_state_schema.md` — state schema (拡張点を本 doc で提案)
- `tools/build_extab_map.py` — extab group 識別 (.orchestrator/extab_groups.json 生成)
- `tools/setup_worktree.py` — worktree scaffold (この doc で大 TU 対応を要する場合 patch)

## 1. データと問題定義

`.orchestrator/extab_groups.json` (2026-05-18 snapshot) の multi-fn group 分布:

| size bucket | groups | total fns | % of multi-fn fns | named pending* |
|---|---:|---:|---:|---:|
| 2-5 fn   | 164 | 461  | 9.5%  | 〜existing bundle 戦略で対応済 |
| 6-10 fn  |  49 | 365  | 7.5%  | T9-3 で対応、Phase 1 で asm_fn 退避追加 |
| 11-20 fn |  27 | 364  | 7.5%  | Phase 3a ターゲット |
| 21-50 fn |  14 | 423  | 8.7%  | Phase 3a ターゲット |
| 51-100 fn|   7 | 533  | 10.9% | Phase 3b ターゲット |
| 101-300 fn|  5 | 597  | 12.2% | Phase 3b ターゲット |
| 301+ fn  |   3 | 2134 | 43.8% | Phase 3c (特別扱い) |

\* named pending = orchestrator が C 化を狙う対象。placeholder (`fn_*` / `lbl_*` / `FUN_*`) は `excluded` で並列 decomp 対象外だが、TU 構成上は asm_fn として TU に含める必要がある (extab group 内 = 必ず同 TU)。

トップ 10 group (named pending 含む):

| size | group | placeholder | named (= pending) |
|---:|---|---:|---:|
| 937 | auto_03_802731B4_text          | 847 | 90 |
| 613 | auto_03_802557B4_text          | 374 | 239 |
| 584 | auto_03_80255964_text          | 366 | 218 |
| 135 | auto_03_802D7CA0_text          | 131 | 4 |
| 125 | auto_03_802BD0FC_text          | 114 | 11 |
| 116 | auto_03_802CDB80_text          | 111 | 5 |
| 114 | auto_03_802CDF38_text          | 111 | 3 |
| 107 | auto_fn_8004A238_text          | 67  | 40 |
| 98  | auto_fn_801DEF94_text          | 84  | 14 |
| 89  | auto_03_802C3C00_text          | 88  | 1 |

これらは extab group の indivisibility 制約で **全関数を 1 TU に取り込まないと dtk split error** になる。Phase 1 の asm_fn schema で「TU 内に C 関数と asm 関数を混在」が可能になったので、TU をまず asm_fn で埋めてしまうのが起点になる。

## 2. 戦略 (size 帯別)

### 2.1 Phase 3a: 11-50 fn (41 groups, 787 fns)

**通常 bundle + asm_fn 退避** の延長。1 sub に dispatch、budget を 60-90 min から拡張 (~2-3 hr) するか、関数数で section 分けて複数 sub に逐次 dispatch。

実装側の差分は:
- sub への budget 通知 (現在 prompt の「60-90 min」を group size に応じて変える)
- HANDOFF.md の results 配列が長い (最大 50 件)
- main の merge は変わらず

これは Phase 1 で導入した asm_fn 退避がそのまま使える。新規 schema 追加なし。

### 2.2 Phase 3b: 51-300 fn (12 groups, 1130 fns)

1 sub で 1 batch 完了は budget 的に無理。**mega-bundle pattern** を導入:

1. **main 側 (scaffold)**:
   - `tools/extract_fn_asm.py` で全 N fn の asm body を抽出
   - 1 つの `.c` ファイル (`src/<lib>/large_block_<addr>.c` のような ad-hoc 命名) に **全関数を asm function として書き込む**
   - `configure.py` に `Object(Matching, "...")` 1 件追加
   - `splits.txt` に 1 entry 追加
   - `python configure.py && ninja build/GNLJ82/ok` で **SHA-1 OK 確認**
   - mega-bundle scaffold として commit (1 commit、関連 file まとめ)
   - 結果: TU 内全 fn は `asm_fn` status、build は通る、bundle 制約解消
2. **sub 側 (per-fn promote)**:
   - 普通の 1-fn batch として dispatch (tu_hint が既存 TU を指す)
   - 関数 1 つを `asm void fn() { nofralloc ... blr }` から C 実装に置換
   - 同 TU 内の他関数は触らない (constraint: 担当関数以外は変更禁止、既存 sub 制約と同じ)
   - build verify + HANDOFF.md `results[].status = "matched"`
   - main merge で asm_fn → matched 遷移

これにより:
- bundle 制約 (extab group indivisibility) は scaffold で一度に解消
- 以後の作業は 1-fn batch の並列スケジューリングに乗る (T9-3 以前と同じ skeduling)
- named 関数だけが promote ターゲット (placeholder は asm_fn のまま放置で OK)

### 2.3 Phase 3c: 301+ fn (3 groups, 2134 fns)

`auto_03_802731B4_text` (937)、`auto_03_802557B4_text` (613)、`auto_03_80255964_text` (584)。合わせて 547 named pending。

mega-bundle pattern が動作するなら Phase 3b と同じ手順で済む。ただし以下が懸念:

- **TU サイズ**: 937 fn の asm body = 数万行。mwcc コンパイル時間が長くなる可能性あり (実測必要、~5 min なら受容)
- **scaffold debug**: 1 関数の asm body 抽出ミスで SHA-1 fail。937 fn から犯人特定するには bisect tool 必須
- **placeholder の C 化**: 847 placeholder は本来 `excluded` なので C 化対象外だが、ユーザが個別解析で named 化する可能性あり (ghidra 側で rename → orch_sync で `has_named_symbol=true` 化)。promote batch のスケジューリング条件に「`has_named_symbol=true` になった時点で pending」を含める

3 group しかないので、各 group の中身を見てから個別に design する余地もある。中規模 (Phase 3b) で手順を固めてから Phase 3c に移るのが筋。

## 3. state schema 拡張

### 3.1 `batches[].batch_type` 追加

新 field (optional、default `fresh_match`):

```json
"batch_text_NNNN": {
  "batch_type": "fresh_match",  // 既存 (新規 TU 作成、Object 追加)
  "status": "pending",
  ...
}
```

- `fresh_match` — 既存の batch 型。新規 TU を作る、配置 (configure.py + splits.txt) も含む
- `mega_scaffold` — 大規模 group の TU を 1 ファイルで作る。main がこの type の batch を生成して **main 自身が処理** (sub に渡さない)
- `promote_asm_fn` — 既存 TU 内の 1 関数を asm_fn → matched 昇格。sub に dispatch、tu_hint が既存 TU を指す、configure.py / splits.txt 変更なし

### 3.2 `batches[].mega_scaffold_state` 追加 (mega_scaffold 用)

```json
"batch_mega_802731B4": {
  "batch_type": "mega_scaffold",
  "status": "pending",
  "extab_group": "auto_03_802731B4_text",
  "function_addresses": [937 件全部],
  "mega_scaffold_state": {
    "tu_path": "src/game/large_block_802731B4.c",
    "asm_body_extracted": false,
    "tu_written": false,
    "configure_added": false,
    "splits_added": false,
    "sha1_verified": false,
    "committed_sha": null
  }
}
```

main の cycle で進めるとき、各 stage を sequential に処理する。fail したら blocked、user 介入。

### 3.3 `batches[].source_tu` 追加 (promote_asm_fn 用)

```json
"batch_promote_8002fxxx": {
  "batch_type": "promote_asm_fn",
  "status": "pending",
  "function_addresses": ["0x8002fxxx"],
  "source_tu": "src/game/large_block_802731B4.c"
}
```

sub への prompt で「この TU の中の関数を 1 つ matching に昇格してほしい」と伝える。configure.py / splits.txt は触らない、symbols.txt の scope 変更は普通通り。

### 3.4 `functions[].batch_type_hint` (informational)

各関数が次に dispatch される batch の type を hint として持つ。derive ロジック:

- `extab_group is None` または `extab_group_size <= 10` → `fresh_match`
- `extab_group_size in [11, 50]` → `fresh_match` (Phase 3a、サイズが大きい bundle)
- `extab_group_size in [51, 300]` → mega_scaffold 未完了なら `mega_scaffold`、完了済なら `promote_asm_fn`
- `extab_group_size > 300` → 同上 (Phase 3c)

mega_scaffold 完了の判定は `state.batches` 内に該当 group の mega_scaffold batch が `merged` 状態で存在するか。

## 4. tools 計画

### 4.1 `tools/extract_fn_asm.py` (必須、Phase 3a 着手前)

```
python tools/extract_fn_asm.py <addr> [--worktree <path>]
  → stdout に nofralloc <body> blr 形式で出力
python tools/extract_fn_asm.py --group <gid> --output <path>
  → group 全関数を 1 ファイルに asm function 形式で出力
```

入力:
- `build/<config>/asm/<group>.s` の `.fn <name>` 〜 `.endfn` パース
- 命令行のみ抽出、ヘッダ / セクション切り替え / `.size` 行は捨てる

出力:
```c
asm void <name>(void) {
    nofralloc
    <命令行...>
}
```

エッジケース:
- 関数の最後が `blr` でない (例: tail call ジャンプ) → そのまま出力 (asm function は `blr` 強制ではない)
- nested label (`.L_xxxxxxxx:`) → そのまま保持
- relocation 表記 (`@ha` / `@l` / `@sda21`) → そのまま保持

### 4.2 `tools/scaffold_mega_bundle.py` (Phase 3b 着手前)

```
python tools/scaffold_mega_bundle.py <group_id> --tu-path <path>
```

実行内容:
1. group の全 fn を extract_fn_asm.py で抽出
2. ターゲット `.c` ファイルを生成 (asm function 並べる)
3. configure.py / splits.txt に entry 追加 (apply_handoff.py の logic 再利用)
4. `python configure.py && ninja build/GNLJ82/ok` で verify
5. 結果を stdout + state.json 更新

失敗時は state.json の `mega_scaffold_state` に途中段階を保存して resume 可能に。

### 4.3 `tools/bisect_mega_bundle.py` (Phase 3b SHA-1 fail 時)

scaffold で SHA-1 OK が出なかったとき、どの関数の asm body 抽出が間違ってるかを binary search で特定する tool。

```
python tools/bisect_mega_bundle.py <tu_path>
  → 関数を半分ずつ Object(NonMatching, ...) に倒して再 build、SHA-1 OK になる方を残す
  → 1 関数まで絞り込んで犯人特定
```

実装: 関数を 2 分割した片方を `asm` から `__attribute__((weak))` などで disable して build。

### 4.4 `tools/orch_promote.py` (Phase 3b)

main の cycle 内で promote_asm_fn batch を生成する補助。group 全 fn が asm_fn 状態の TU を見つけて、その中で named pending な関数を 1-fn batch として state.batches に追加。

## 5. ROI 優先順位と Phase 順

ROI = `named pending / 関連 group size` (= C 化価値の比率)。表 1 のトップ 10 から計算すると:

| group | named | total | ROI |
|---|---:|---:|---:|
| auto_03_802557B4_text | 239 | 613 | 0.39 |
| auto_03_80255964_text | 218 | 584 | 0.37 |
| auto_fn_8004A238_text | 40  | 107 | 0.37 |
| auto_03_8009BEF4_text | 24  | 42  | 0.57 |
| auto_03_802731B4_text | 90  | 937 | 0.10 |

ROI 0.5 超は手をつける価値高い。一方 937 fn group は ROI 0.10 と低い (placeholder 比率高、整地のコスト大、C 化のリターン小)。

**着手順 (推奨)**:

1. **Phase 3a small (11-20 fn, 27 groups, 364 fns)** — 既存 bundle 戦略 + asm_fn 退避で手順固める。new tool 不要
2. **`tools/extract_fn_asm.py`** 実装 — Phase 3b の前提
3. **Phase 3a large (21-50 fn, 14 groups, 423 fns)** — Phase 3a small の延長
4. **`tools/scaffold_mega_bundle.py` + `bisect_mega_bundle.py`** 実装 — Phase 3b の前提
5. **Phase 3b small (51-100 fn, 7 groups, 533 fns)** — mega-bundle pattern の初回検証。ROI 高い group から選択
6. **Phase 3b large (101-300 fn, 5 groups, 597 fns)** — pattern 確立後
7. **Phase 3c (3 group)** — 個別 design

各 phase 完了後に retrospective して 1 つ前に戻る判断を残す (例: 3b で scaffold 失敗が連続したら 3a で手順再整備)。

## 6. failure modes と mitigation

| 想定失敗 | 原因 | mitigation |
|---|---|---|
| mega-bundle scaffold SHA-1 fail | 1 関数の asm body 抽出ミス (extract_fn_asm.py のバグ、エッジケース未対応) | `bisect_mega_bundle.py` で犯人特定、extract_fn_asm.py に test ケース追加 |
| 巨大 TU の mwcc コンパイルが遅すぎる (>10 min) | mwcc が asm function 大量 1 TU で線形以上の時間消費 | 1 TU を 2-3 に分割。dtk extab indivisibility との折り合いを Phase 3c で個別検討 |
| promote batch で SHA-1 fail | C 化実装の mismatch | 該当関数を asm_fn に戻して継続 (TU 自体は build 通る、他関数の matching に影響なし) |
| named/placeholder 比率の drift | ghidra rename で placeholder → named 遷移 | orch_sync で `has_named_symbol` 再 derive、新 pending → 自動 promote batch 候補 |
| extab group 内に異なる cflags 関数が混在 (例: `-Cpp_exceptions on/off`) | mkgp2 内に存在するか不明 | 検出 + per-group cflags override で対応 (Phase 3a の検証時に判明する想定) |
| 大 TU の `symbols.txt scope:global` 一括設定の漏れ | named 関数の cross-TU 参照で linker error | scaffold 時に named 関数全て scope:global 自動設定 |

## 7. open question (Phase 3 実装着手前に解消したい)

- mwcc 1.3.2 / 1.0 / 2.7 等での **asm function 大量 1 TU** の build 時間実測 (Phase 3a で 50 fn TU 作って測る)
- placeholder 関数を asm function で書く時の `void(void)` signature で C 側から呼ばれる場合の挙動 (Phase 1 では問題なし、Phase 3 で大量に発生)
- promote batch の sub への prompt 設計 (既存 TU 内の 1 関数だけ触る、という制約をどう書くか)
- `extract_fn_asm.py` で `.fn <name>` ブロック内に inline 別 fn の `.size` が混じるか (一部 mwcc TU では起こりうる) — 仕様確認要
- bisect tool の効率: 1 段階 build に 1-2 min かかる、937 fn = ~10 段階 bisect = 20 min。受容範囲

## 8. Phase 計画 summary

| Phase | 内容 | 工数感 | 前提 |
|---|---|---|---|
| 3a-small | 11-20 fn group の bundle 戦略確立 (asm_fn 退避前提) | 小 (Phase 1 完了で実行可能) | Phase 1 |
| Tool: extract_fn_asm.py | 1 関数 asm body 切り出し tool | 小 | - |
| 3a-large | 21-50 fn group の bundle | 中 | Phase 3a-small |
| Tool: scaffold_mega_bundle.py + bisect_mega_bundle.py | mega-bundle scaffold + bisect | 中 | extract_fn_asm.py |
| 3b-small | 51-100 fn group (mega-bundle 初回) | 大 | mega tool 一式 |
| 3b-large | 101-300 fn group | 大 | 3b-small |
| 3c | 3 巨大 group (個別 design) | 大 | 3b-large |

T10 (元 issue: 大規模 group 対応) はこの Phase 3 の中で完全に解消される。元の「>10 fn 大規模 group をどう扱うか」は 3a で対応開始、3b で本格的に解決、3c で巨大特殊ケースに対応する形。
