# Per-function matching strategy

bundle (extab group 必須 bundle) の中で **関数単位** に matching / asm-fn 退避を切り替えるための規約。

関連:
- `docs/sub_agent_role.md` — sub の制約と HANDOFF.md format (この doc で schema 拡張)
- `docs/orchestrator_role.md` — main の merge ルール (この doc で per-fn 反映を追加)
- `docs/orchestrator_state_schema.md` — functions[].status の state machine (`asm_fn` 追加)
- `~/.claude/skills/mkgp2-match/SKILL.md` — 撤退判定と asm-fn 書き方を反映予定
- T9 verify gist (2026-05-17, 6-fn bundle `batch_text_8002f640_bundle`): https://gist.githubusercontent.com/naari3/9d78fc3972f7cc3dcf77d9d0c6a9945c

## 1. 背景

dtk reversed extab group 制約により、`auto_*_text*.s` blob は **1 indivisible bundle** として 1 TU に取り込む必要がある。1 関数だけ抜くと dtk が split error を出す。

現状の bundle 戦略は **all-or-nothing**:
- `Object(Matching, "...")` → bundle 内全関数を C で書く、全部 100% でないと SHA-1 fail
- `Object(NonMatching, "...")` → bundle 全体を asm から build (= 全関数 byte-identical だが C は捨てる)

T9 verify (上記 gist) で観測した failure mode:

- 6-fn bundle のうち 1 関数 (fn_8002F640: timing + 0x60 byte 構造体 copy + 連鎖 magic 定数除算) が難易度天井
- sub が 4 byte diff まで詰めて以降、Granlund-Montgomery 定数 0x431BDE83 の手計算で 1 instruction 差を埋めようとし続けた
- 残り 5 関数 (isJapanese 3 instr 等) は **未着手**
- 29 分経過、6/6 matching に届く見込みなし
- bundle 制約で部分 skip 不可 → 全体止まる

## 2. 解決方針

mwcc native の `asm void fn() { nofralloc ... blr }` を使い、1 TU 内で C 関数と asm 関数を混在させる。

mkgp2-decomp で既に採用済の pattern:
- `src/init/__flush_cache.c`
- `src/init/__init_hardware.c`
- `src/Runtime.PPCEABI.H/__init_cpp_exceptions.cpp`

これを bundle 内の per-fn 撤退手段として規約化する。

利点:
- `Object(Matching, ...)` 維持 (extab group 制約 OK、SHA-1 verify 通る)
- 1 関数だけ asm に逃げて他は C で書ける
- 退避した関数は byte-identical 保証 (dtk 生成 asm をそのまま貼る)
- 後日その関数だけ C 化リトライ可能 (asm fn を C fn に置き換える単純な差分)

欠点:
- 「真の C 化率」と「TU 経由化率」が乖離 (report で別カウントが要る)
- asm fn は decomp 価値ゼロ (読みづらい raw asm のまま)

## 3. asm function 書き方規約

### 雛形

```c
asm void fn_8002F640(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    ...
    blr
}
```

- `asm` keyword + `nofralloc` で mwcc が prolog/epilog 生成を抑制
- body は raw PowerPC asm
- signature は `void fn_XXX(void)` で OK (引数 / 戻り値の型は asm body 内のレジスタ使用で決まる、C 側 signature は呼び出し側の型強制のみ)
- section 指定は基本不要 (`.text` default)。`.init` / `.dtor` 等別 section に置く関数だけ `__declspec(section ".init") asm void fn() { ... }`

### asm body の取得元

dtk が `build/GNLJ82/asm/auto_<group>_text.s` を生成する。その中の対象関数の `.fn <name>` 〜 `.endfn` 間の **命令行のみ** を取り出して `nofralloc` の後ろに貼る。

切り出しに含めない:
- `.fn <name>, <addr>` / `.endfn <name>` ヘッダ行
- `.global <name>` / `.local <name>`
- セクション切り替え (`.section .text`)
- 関数 entry の `entry .fn` 行 (もしあれば)
- 末尾のラベル (`.endfn` 直前の `.size` 等)

そのまま貼って良い:
- 命令行 (`stwu r1, -0x20(r1)` 等)
- local label (`.L_8002F66C:` 等)、ただし 1 TU 内で重複しない名前に手動 rename しても OK
- relocation 表記 (`lis r4, lbl_802E8F48@ha` 等)

### 補助 tool (任意)

手動切り出しが面倒な場合、後で `tools/extract_fn_asm.py <addr>` を追加する想定 (Phase 2)。Phase 1 では手で切り出す。

## 4. 撤退判定 (sub-agent 側)

`/mkgp2-match` skill 内で 1 関数あたりの試行ループを回す。以下のいずれかを満たしたら `asm_fn` に退避:

| 条件 | 閾値 | 理由 |
|---|---|---|
| **edit→build→diff のサイクル回数** | **6 回** で `objdiff_percent == 100.0` に届かない | 試行カウント (approach の質的変更回数) ではなく、ビルド回数の通算。深堀り傾向の早期検出 |
| **diff バイト数の停滞** | **3 サイクル連続** で同じバイト数残 (例: 4 byte diff が 3 連続) | 「あと 1 命令」の罠で同じ箇所を粘る pattern を切る |
| **個別判断** | sub が「これは時間使う割に低 ROI」と判断 | 早期退避 OK。理由を notes に書く |

sub-agent は **wall clock を能動的に見る contract を持たない** ため、分単位の判定は採用しない。サイクル回数とバイト残量の自己観測可能な指標のみ。

### 撤退後の処理

1. dtk 生成 asm から body を切り出す
2. C ファイル内に `asm void fn_NAME(void) { nofralloc <body> blr }` として埋め込む
3. 該当関数の `results[].status = "asm_fn"` で HANDOFF.md に記録
4. build verify は他の matching/asm_fn 関数と一緒に 1 回回す (SHA-1 OK 期待)

### bundle 全体が matching に届かない場合

- bundle 内 N 関数中 M 関数を matched + (N-M) 関数を asm_fn にしても、TU は `Object(Matching, ...)` で SHA-1 OK になる想定 (Phase 1 検証必須)
- 全関数が asm_fn になる場合は、結果として `Object(NonMatching, ...)` と同じ (decomp 価値ゼロ)。素直に NonMatching 隔離する方が configure.py が短い

## 5. HANDOFF.md schema 拡張

### 5.1 `results[].status` enum 追加

| 旧 | 新 |
|---|---|
| `matched` / `nonmatching` / `skipped` / `failed` | `matched` / `asm_fn` / `nonmatching` / `skipped` / `failed` |

意味:

| status | 意味 | C 化価値 |
|---|---|---|
| `matched` | C で書いて 100% match | 高 (今後さらなる解析が不要) |
| `asm_fn` | C TU 内に `asm void fn() { nofralloc ... blr }` で inline 化、byte-identical | ゼロ (後日 retry 可能) |
| `nonmatching` | TU 全体を `Object(NonMatching, ...)` で asm から build | 中 (C ソースは残る、別 batch で再挑戦可) |
| `skipped` | 試行せず保留 | - |
| `failed` | 試行したが build さえ通らない | - |

### 5.2 field 要件マトリクス追加列

`sub_agent_role.md` の status マトリクスに `asm_fn` 列を追加:

| field | `matched` | `asm_fn` | `nonmatching` | `skipped` | `failed` |
|---|---|---|---|---|---|
| `results[].src_path` | 実 path 必須 | **実 path 必須 (matched と同 TU)** | 実 path 必須 | null 推奨 | null |
| `results[].objdiff_percent` | 100.0 必須 | **100.0 必須 (byte-identical)** | 0-99.99 | null | null |
| `configure_py.add_objects[]` | 必須 (Matching) | **不要 (bundle 全体で 1 件、matched と同 TU)** | 必須 (NonMatching) | 空配列 | 空配列 |
| `splits_txt.add_entries[]` | 必須 | **不要 (matched と同 TU)** | 必須 | 空配列 | 空配列 |
| `symbols_txt.set_scope[]` | 必要なら | **必要なら** | 必要なら | 空配列 | 空配列 |
| `build_verified.sha1_ok` | true 必須 | **true 必須** | true 必須 | true 必須 | false 可 |
| `blocked_reason` | null | **任意 (なぜ asm に逃げたか 1 文)** | null/optional | 必須 | 必須 |
| commit 動作 | ✓ | **✓ (同 TU で 1 commit)** | ✓ | × | × |

`asm_fn` 関数のための個別 `configure_py.add_objects` / `splits_txt.add_entries` は不要。bundle 全体の TU が 1 `Object(Matching, ...)` で登録され、その中に matched 関数と asm_fn 関数が共存する。

## 6. main 側 merge ルール

`docs/orchestrator_role.md` の Merge ルール (CASE 2) に追加:

- HANDOFF.md の `results[].status == "asm_fn"` の関数も `state.functions[addr].status = "matched"` 相当に **昇格しない** (区別保持)
- 新規 status: `state.functions[addr].status = "asm_fn"` を追加 (functions[] state machine 拡張)
- `state.functions[addr].notes` に asm fn として inline 化された旨を 1 行記録 (auto)
- SoT sync (`tools/orch_sync.py`) で `Object(Matching, ...)` 由来の自動 matched 昇格 logic を変更:
  - 従来: `tu_hint + Matching` なら `matched`
  - 変更: `tu_hint + Matching` でも、HANDOFF.md 由来で `asm_fn` を保持していたら **その値を維持** (preserve)
  - 実装: `PROTECTED_STATUSES` set に `asm_fn` を追加

state.json の進捗 report (`tools/orch_report.py` 等で集計時) は `matched` と `asm_fn` を別カウントする。「真の C 化率」と「TU 取り込み率」の区別を残す。

## 7. orchestrator_state_schema.md 変更点

`functions[addr].status` enum:

```
pending
in_progress
matched
asm_fn         (NEW)
nonmatching
skipped
excluded
blocked
interrupted
```

`asm_fn` の遷移:
- `pending` / `in_progress` → `asm_fn`: HANDOFF.md `asm_fn` を main が apply
- `asm_fn` → `pending`: user が後日「C 化リトライしたい」と指示したとき手動で戻す (rare)
- `asm_fn` → `matched`: 後日 retry が成功 (rare、HANDOFF.md status 上書き)

PROTECTED_STATUSES (orch_sync が SoT-derive で上書きしない set):
```
in_progress, interrupted, blocked, skipped, asm_fn   (asm_fn 追加)
```

## 8. mkgp2-match skill 修正点

`~/.claude/skills/mkgp2-match/SKILL.md` に以下を追記:

### 撤退判定セクション (新規)

> 1 関数に対し以下のいずれかを満たしたら、C matching を諦めて asm function 退避を選ぶ:
>
> - **6 サイクル ルール**: edit → build → objdiff の通算サイクルが 6 回を超え、objdiff_percent が 100.0 に届かない
> - **diff 停滞ルール**: 3 サイクル連続で同じバイト数の diff が残る
> - **個別判断**: 残り作業の ROI が低いと判断したら早期退避してよい
>
> 退避は失敗ではない。bundle 内の他関数を優先するため。

### asm function 書き方セクション (新規)

> `build/GNLJ82/asm/auto_<group>_text.s` の `.fn <name>` 〜 `.endfn` 間から命令行のみを取り出し、以下の形で C ファイルに埋める:
>
> ```c
> asm void fn_NAME(void) {
>     nofralloc
>     <命令行をそのまま貼る>
>     blr
> }
> ```
>
> - section 指定は不要 (`.text` default)
> - 既存例: `src/init/__flush_cache.c`, `src/init/__init_hardware.c`
> - signature は `void fn(void)` で OK (asm body のレジスタ使用で実 ABI が決まる)

7.5 節 (NonMatching 隔離) の前に「asm function 退避を優先検討」の note を追加。

## 9. Phase 計画

| Phase | 内容 | 工数感 |
|---|---|---|
| **Phase 1: 規約と実証** | この doc 承認 → schema 拡張実装 (parse_handoff / apply_handoff / orch_sync) + sub_agent_role.md / orchestrator_role.md 更新 + skill 更新 → T9 verify 再実行 (今の 6-fn bundle を asm_fn 混在で通す) | 中 |
| **Phase 2: tool 補助** | `tools/extract_fn_asm.py` 追加 (asm 自動切り出し) + report 集計 (matched / asm_fn 別カウント) | 小 |
| **Phase 3: 大規模 group** | >10 fn group への適用検討。詳細は `docs/large_extab_group_strategy.md` (Phase 3a small/large + 3b small/large + 3c の 5 段階に細分化、`tools/extract_fn_asm.py` / `scaffold_mega_bundle.py` 等の補助 tool 設計含む) | 大 |

T9-2 と T10 は Phase 1-3 の中に解消される (個別 ticket としては閉じる)。

## 10. open question (Phase 1 verify 前の仮置き、§11 で更新)

- mkgp2-decomp の cflags に `-Cpp_exceptions off` がある状態で、bundle 内の関数 (auto extab を持つ) を C + asm_fn 混在で書くとき、`-Cpp_exceptions on` を per-TU で付ける必要がある (extab/extabindex section を mwcc に出させるため)。Phase 1 検証で確認。 → **§11 で部分回答 (cflags はそれ自体動くが、asm-void fn が extab を発出しないので bundle 不成立)**
- asm function の body 内で参照する extern symbol (`lbl_802E8F48@ha` 等) は C 側の `extern` 宣言を要求するか? mwcc の asm function はおそらく独立 reloc を出すので不要のはず。Phase 1 検証で確認。 → **§11: mwcc inline asm は `@sda21(r0)` syntax を parse 不可、workaround は sym が sdata 居住なら `lbl(r2)` で auto reloc 付与**
- bundle 内 N 関数すべてが asm_fn になった場合と `Object(NonMatching, ...)` で全体を asm から build した場合とで、生成 .o は byte-identical か? 後者の方が configure.py が短いので、全関数 asm_fn なら NonMatching に倒す方が筋。Phase 1 で「全 asm_fn なら自動 NonMatching 提案」を sub の振る舞いに入れる。 → **§11: 1 個でも asm_fn にすると extab 不整合で SHA-1 fail、全 asm_fn を Matching で通すのは原理的に不可。Phase 1b 救済 candidate 待ち**

## 11. Phase 1 verify outcome (2026-05-18)

batch `batch_text_8002f640_bundle` (6-fn auto_fn_8002F640_text group) を Phase 1 verify として dispatch した結果 (sub agent_id `a636ac0f26c2e0cee`、25.6 min、HANDOFF.md は worktree `.worktrees/batch_text_8002f640_bundle/` に保存):

### 達成

- (a) `results[].status = "asm_fn"` の HANDOFF.md parse 経路は `isJapanese` (3 instr asm body) で exercise → parse 成功
- (c) `tools/orch_sync.py` `PROTECTED_STATUSES` の保護動作 (asm_fn が SoT-derive で上書きされない) は仕組み上問題なし

### 未達成 — 構造的制約 3 つ

(b) `Object(Matching, ...)` の TU 内で C 関数 + asm 関数共存 + bundle 全体 SHA-1 OK は **以下の制約で達成できなかった**:

1. **mwcc inline asm が `lbl@sda21(r0)` syntax を parse 不可**
   - workaround: `lbl(r2)` と書くと sym が `.sdata` / `.sdata2` 居住なら mwcc が自動で sda21 reloc を付与 (sub 検証済、動く)
   - 制約は表面的、書き換えコスト軽
2. **mwcc inline asm が `crclr cr1eq` / `crset cr1eq` mnemonic を parse 不可**
   - workaround: `crxor 6,6,6` / `creqv 6,6,6` (bit-position 表記) で書き直し
   - 制約は表面的、書き換えコスト軽
3. **致命的: `-Cpp_exceptions on` でも asm-void fn が extab/extabindex section に entry を発出しない**
   - bundle で N 関数中 M 関数を asm_fn にすると、TU の extab entries が N-M 個になり target の N 個と layout が合わず `_eti_init_info` の位置が約 0x14 byte ずれて SHA-1 fail
   - asm_fn 退避を **extab group bundle 内で機能させる前提が崩壊**

### 救済 candidate (未試行、Phase 1b で empirical 検証する想定) → **§12 で検証成功**

C 側から手動 extab entry を発出する:

```c
__declspec(section "extab") static const unsigned char extab_<fn>[] = { ... };
__declspec(section "extabindex") static const struct {
    void *fn_addr;
    void *extab_addr;
    /* ... layout per target */
} extabindex_<fn> = { &<fn>, extab_<fn>, ... };
```

これが動けば asm fn が extab entry を持つことになり SHA-1 通る可能性。1 関数あたり extab body byte 配列 (典型 0x10-0x40 bytes) + extabindex struct (12 bytes 程度) を target asm から手抽出する必要、tool 化可能。

### 結論と影響範囲 (§12 で更新)

現状の asm_fn schema が valid な使用範囲:

- **extab group 外 (singleton fn)** の単独関数で C-matching 困難ケース → 使える
- **extab group bundle 内** → ~~Phase 1b 救済 candidate (上記 `__declspec(section "extab")` 手法) が動作実証されるまで使えない~~ → §12 で動作実証、ただし mwcc は `extab`/`extabindex` 予約名を reject するため `.extab_user`/`.extabindex_user` 経由 + llvm-objcopy rename が必要

このため:

- ~~`docs/large_extab_group_strategy.md` (Phase 3) は asm_fn による mega-bundle pattern を前提に設計されているため、Phase 1b 結果待ちで **設計全体保留** 状態。doc 冒頭に DESIGN SUSPENDED 注記を追加~~ → §12 で前提解消、DESIGN SUSPENDED は降ろせる
- Phase 2 の `tools/extract_fn_asm.py` は依然有用 (singleton 用途と Phase 1b 検証用)、実装計画は維持
- Phase 1a (extab group 外 singleton への asm_fn 適用) は通常運用に即組み込み可能

### Phase 1b 検証の dispatch 仕様 (案) → 実際は main 側で手動検証 (§12)

- 小規模 extab group (2-3 fn、各 fn が shallow body) を 1 つ選定
- 1 関数を C で書き、もう 1 関数を asm_fn + 手動 extab/extabindex で書く
- bundle 全体を `Object(Matching, ...)` として SHA-1 OK 達成を目標
- 失敗時 (extab byte 配列推定ミス / extabindex struct layout 違い等) は HANDOFF.md notes で原因記録
- 候補 group: `tools/build_extab_map.py` 出力 + extab_group_size==2 で検索

target extab raw bytes は dtk 出力 `build/GNLJ82/asm/auto_*_text.s` 末尾の `.section "extab"` / `.section "extabindex"` ブロックから取れる。tool 補助は Phase 1b 実装後に検討。

## 12. Phase 1b verify outcome (2026-05-18)

Phase 1b は別 sub 検証ではなく main 側で `src/game/HeapStats.c` (6 fn bundle、全 asm_fn) を完全 scaffold して empirical 検証。**SHA-1 OK 達成**。

### 採用手法

1. **mwcc の section 予約名回避**:
   - mwcc 1.3.2 は `__declspec(section "extab")` / `__declspec(section "extabindex")` を「unknown section name」で reject
   - workaround: `#pragma section R ".extab_user"` + `#pragma section R ".extabindex_user"` で別 section 作成 → build 後 llvm-objcopy `--rename-section=.extab_user=extab` / `.extabindex_user=extabindex` で merge
2. **dtk dol split の `@etb_*` / `@eti_*` symbol auto-regen 対応**:
   - dtk は build 毎に `symbols.txt` を regenerate し、target の anonymous local extab/extabindex symbol を `@etb_<addr>` / `@eti_<addr>` の形で auto-emit。dtk dol diff はこの symbol が該当 addr に存在することを assert
   - C source は `@` 始まりの identifier を持てない → C 側で `extab_<fn>` / `extabindex_<fn>` の名前で emit して build 後 llvm-objcopy `--redefine-sym` で `@etb_*` / `@eti_*` に rename
   - per-TU mapping は `tools/extab_user_renames.json` で管理 (TU 単位の dict)
3. **build chain 統合** (`tools/project.py`):
   - 順序: `mwcc` → `tools/postprocess_extab_user.py` (section + symbol rename) → `dtk extab clean`
   - `dtk extab clean` が `extab`/`extabindex` section を要求するため、rename はその前に実行する必要あり
   - postprocess は `.extab_user` section も rename target symbol も無い TU では no-op
4. **mwcc inline asm の制約回避** (§11 で既知):
   - `lbl@sda21(r0)` syntax 不可 → `extern unsigned int lbl_xxx;` 宣言 + `lbl_xxx(r2)` で auto sda21 reloc
   - `crclr cr1eq` / `crset cr1eq` 不可 → `crxor 6,6,6` / `creqv 6,6,6` bit-position 表記
5. **section ordering の独立保証**:
   - `.text` ordering: 関数定義順 (mwcc は source order 通りに emit) を target の `.text` address 順に並べる
   - `extab` ordering: 手動 emit 順を target の `extab` 順 (HeapStats では fn address 順とは異なる) に並べる
   - `extabindex` ordering: 手動 emit 順を target の `extabindex` 順 (HeapStats では fn address 順) に並べる
   - 3 つの section は独立に order 制御可能 (`__declspec(section "...")` の emit 順 = section 内 layout 順)
6. **`Object(Matching, ...)` 配線** (`configure.py`):
   - `extab_padding=b"\x00\x00"` を渡して `mwcc_sjis_extab` build rule (postprocess chain 入り) に routes

### 達成事項

- 6 fn × 5 extab × 5 extabindex (1 fn の `isJapanese` は exception table なし、終了 blr のみ) を 100% byte-identical で 1 TU として build、SHA-1 OK
- `Object(Matching, "game/HeapStats.c")` 維持、Progress カウントは Matching に加算
- Phase 1 (a) asm_fn HANDOFF.md schema、(c) `PROTECTED_STATUSES` 保護、(b) Object(Matching) TU 内 C+asm 関数共存 + bundle 全体 SHA-1 OK の 3 つすべて構造として整備完了

### 残課題 (Phase 2 へ) → 主要部分は §13 で完了

- ~~target extab raw bytes / extabindex struct 抽出の自動化~~ → §13 `tools/extract_fn_asm.py` で完了
- ~~per-TU mapping json (`tools/extab_user_renames.json`) の生成自動化~~ → §13 で snippet 出力対応
- ~~`tools/extract_fn_asm.py` 実装 (Phase 2 既定タスク)、これに extab/extabindex emit 補助も統合~~ → §13 で完了

### 影響範囲の更新

- `docs/large_extab_group_strategy.md` の DESIGN SUSPENDED 注記を解除 (mega-bundle pattern の前提 = Object(Matching) で asm_fn 混在 + bundle SHA-1 OK が成立) → 別途 update
- Phase 1a / Phase 1b は完了。次は Phase 2 (tool 整備) と Phase 3a-small への着手

## 13. tools/extract_fn_asm.py 実装 (2026-05-18)

§12 の手順 (mwcc section 予約名回避 / dtk symbol auto-regen / inline asm 制約回避 / section ordering / extern 収集) を 1 tool に集約。dtk-generated `build/<config>/asm/<group>.s` を入力に C source skeleton を生成する。end-to-end verify: tool 単独出力で `src/game/HeapStats.c` を生成 → ninja build で SHA-1 OK 達成 (commit `634b412`)。

### tool が吸収する mwcc inline asm の制約

- `<sym>@sda21(r0)` → `<sym>(r2)` rewrite + extern 自動収集
- `crclr/crset crNcond` → `crxor/creqv N*4+bit, N*4+bit, N*4+bit` rewrite
- `.L_<addr>` ローカル label → `<fn_name>_L_<addr>` rewrite (fn 単位 namespace 化、mwcc は `.` 始まりを directive 扱い)
- `bl <fn>` / `<sym>@ha,@l` 参照から callee と data ref を抽出して `extern void Foo();` / `extern unsigned int <sym>;` 自動 emit

### 出力構造 (target 順)

1. forward decls (`asm void <fn>(void);` × N)、extabindex の `(void*)&<fn>` 参照のため
2. extern decls 3 group (branch callees / sda21 data / large-data refs)
3. extab emit (target extab section layout 順、`#pragma section R ".extab_user"` + `__declspec(section ".extab_user") static const unsigned char extab_<fn>[N] = { ... };`)
4. extabindex emit (target extabindex section layout 順、`#pragma section R ".extabindex_user"` + `__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_<fn> = { ... };`)
5. asm function bodies (.text address 順、`asm void <fn>(void) { nofralloc ... }`)

### CLI

```sh
python tools/extract_fn_asm.py <group_id> \
    --tu <src/path/to.c> \
    --out-c <src/path/to.c> \
    --out-renames <renames_snippet.json>
```

renames snippet は `{ "<tu_path>": { "extab_<fn>": "@etb_<addr>", "extabindex_<fn>": "@eti_<addr>", ... } }` 形式で `tools/extab_user_renames.json` にマージする想定。

### scope 外

- `.c` の new file 作成 / configure.py の Object 追加 / splits.txt entry / state.json 更新は tool 範囲外。caller (orchestrator main or 人手) が組む
- 関数 callee 型推論 (`extern void Foo()` 一律、戻り値・引数の specificity は user refine)
- データ extern 型推論 (`extern unsigned int` 一律、mwcc は sda21 vs large-data を section で決めるので codegen 影響なし)

### Hybrid 構成 (HeapStats.c 採用)

`src/game/HeapStats.c` は tool 出力をベースに、先頭の group 説明 comment header (再生成手順 + reference 注記) のみ手で残す Hybrid 構成。tool 再実行で header 以下は上書きされる前提、再生成手順を header 内に書いてある。
