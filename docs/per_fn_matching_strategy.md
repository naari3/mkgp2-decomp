# Per-function matching strategy

bundle (extab group 必須 bundle) の中で **関数単位** に matching / asm-fn 退避を切り替えるための規約。

関連:
- `docs/sub_agent_role.md` — sub の制約と HANDOFF.md format (この doc で schema 拡張)
- `docs/orchestrator_role.md` — main の merge ルール (この doc で per-fn 反映を追加)
- `docs/orchestrator_state_schema.md` — functions[].status の state machine (`asm_fn` 追加)
- `~/.kimi-code/skills/mkgp2-match/SKILL.md` — 撤退判定と asm-fn 書き方を反映予定
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

`~/.kimi-code/skills/mkgp2-match/SKILL.md` に以下を追記:

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

## 14. Phase 3a-small main wave 知見 (2026-05-18, auto_800A8F4C bundle)

12 並列 sub で auto_800A8F4C bundle (16 fn) を asm_fn → matched promote 試行 (pilot 1 + main wave 12)。**結果: 4 matched (pilot GetInstance + dtor 2 + OnEnter) / 9 asm_fn 退避 (3 not attempted; bundle 内の他 fn は触らない原則のため、各 sub は 1 fn だけ touch)**。各 sub の 5-20 min ぶんの探索結果から、CW 1.3.2 codegen の限界点と既知の通る idiom を抽出する。

### 14.1 bundle 内 fn promote の extab handling: approach A / B / mix

CW が plain C 関数に対して extab/extabindex を **自動 emit する** ため、bundle の既存 manual emit (`__declspec(section ".extab_user")` + objcopy rename) と **二重化して `_eti_init_info` が 0x14 byte シフトし SHA-1 fail** する問題が出る。

2 つの解決策が独立に発見された (`dtor_800A9CC8` / `dtor_800A9D2C`):

- **Approach A** (`dtor_800A9CC8`): C 関数の `extab_<fn>` と `extabindex_<fn>` の手動 emit を **削除** する。CW が自動 emit するのに任せる
- **Approach B** (`dtor_800A9D2C`): C 関数の body を `#pragma exceptions off` / `#pragma exceptions reset` で囲み、CW の auto-emit を抑制。手動 emit を **そのまま残す**

**mix の動作性** (auto_800A8F4C bundle で実証): 同 bundle 内に approach A の fn と approach B の fn が共存しても SHA-1 OK (各 fn が exactly 1 個の extab/extabindex を生成すれば extab section の linear order は変わらない)。

**mix の失敗条件** (2026-06-10, game/ISESlot_Lifecycle.c, commit 64f38a9): mix が成立するのは **A 群が address 順で B 群より前** にあるときだけ。mwcc は auto-emit extab を obj の `extab` section、manual emit を `.extab_user` (rename 後の同名別 section、`unique, 1` 付き) に置き、link 順は **必ず auto 分が先**。ISESlot_Lifecycle では fn address 順が Init(B 必須・asm_fn)→Dtor だったため、Dtor を A にすると final extab が Dtor→Init の順になり target (address 順) と逆転して SHA-1 fail。**asm_fn (= 強制 B) より後ろの address に C fn がいる TU では、その C fn も B に統一する** こと。

選択基準:
- 既存 promoted fn が全部 A → A で統一が無難 (mix は section order が予測しづらい)
- bundle が C++ scoped object を抱える (extab body に `&dtor_*` ref がある) なら B が向く (`#pragma exceptions off` が C++ 例外 semantics をきっちり切るため)
- **TU 先頭側の fn が asm_fn (manual extab) なら後続 fn も B に統一** (上記 mix 失敗条件)

実績 (2026-08-11, game/GabyouTripleChild.c, batch_text_800f3b20_gabyoutriplechild): address 順 A (TickHitResolve plain C + `-Cpp_exceptions on` auto-emit) → B (TickActive asm_fn manual) → B (Update C + `#pragma exceptions off` + manual emit) の構成で SHA-1 OK。**`#pragma exceptions off` で Update の codegen は不変** (exceptions on で 100% 達成済の C をそのまま囲むだけで objdiff 100% 維持) だったので、「先に A 相当で書いて後から B に包む」手順が取れる。また同 batch で sparse switch の **重複 exit branch** (target は join への無条件 `b` を 2 連、CW は 1 個しか出さない) が新しい closed class として確認された (詳細: `docs/notes/cw132-sparse-switch-duplicate-exit-branch.md`。outer switch で包み構造を変えると消えた例あり、retry の手がかり)。

### 14.2 main wave で発見された hard-block patterns (CW 1.3.2)

C source から target asm を再現できなかった idiom。**再試行の前にこれらを reference しないと同じ罠にハマる**。

**2026-06-11 register-identity family MODEL-FOUND (重要)**: 表中の「callee-saved web の register identity / partition / tie-break / fp-numbering」系の park は、CW 1.3.2 の graph-coloring colorer を frida で実行時観測して機構が確定した (`docs/notes/cw132-allocator-phase2f-research.md`)。**規則: colorer は web を web-birth key 降順で着色し、各 callee-clique web に r31 から降順で reg を割当てる。web-birth key = value-numbered IR の web 生成順 = plain local では宣言/定義順**。merged/CSE/param-merge web は遅く生まれる→低 key→最後着色→低位 reg (merged-web-last)。inline splice は spliced web の key を振り直す (two-regime)。**lever: target の高位 reg owner を source で先に定義する** (def/decl-order)。GetMaxSpeedWithBonus はこの model-guided 手法で promote 済み (blind ~60 variant 床 → 3 build)。これらの park は「source 制御不能」ではなく「web-birth 順の操作問題」に再分類された。

| 関数 | パターン | 再現できない理由 | 救済 hypothesis |
|---|---|---|---|
| `WarpZone_CalcExitPosition` | DSE が初期 Vec3 stores を消す (target は保持) | CW 1.3.2 dead-store elimination は volatile / address-take でも回避できなかった (4 試行) | 構造体引数 + escape semantics の組合せ未踏 |
| `WarpZone_FindContaining` | `stwu 0x20` frame + 3 float arg を `0x8/0xc/0x10` に dead-spill + `frsp` で `f5/f6` 生成 | Vec3 値渡し → ABI で pointer に degrade。3 float arg + dead local Vec3 → DSE で消える | `float pos[3]` の address-take index access (未試行)。sibling `fn_800A8F4C` も同 pattern なので解明すれば 2 fn unlock |
| `WarpDashMgr_Cleanup` | 2x redundant `addic. r0,r30,0xc; beq` + 2x redundant `cmplwi r30,0; beq` (inlined-then-deduplicated smart-ptr dtor chain) | mwcc は C source の `if (x) { if (x) ... }` 二重 guard を即 dedup。3 試行で 90% 止まり、+12 byte 残差 | **2026-06-10 解法発見 (CarObjectManager_Dtor で実証)**: 同一変数の literal 二重 guard ではなく、**nested static inline helper の引数として渡して各レベルで `if (l)` を再 guard** すると dedup されず 3 連 addic. が再現する (`docs/notes/cw132-sweepbitset-batch-idioms.md` idiom 2)。本 fn の retry 価値あり |
| `WarpDashMgr_GetOrCreate` | `stmw r25, 0x14(r1)` inline prologue (`_savegpr_25` helper でない) | `-Cpp_exceptions on` + GPR 7 個保存だと CW は default で `_savegpr_25` 経由になる。extab body の `0x8A800019 / &dtor_8003AFB8` は scoped C++ object を示唆 | bundle 全体を `.cpp` + `class WarpDashMgr { ~WarpDashMgr(); }` に retrofit する必要。1 fn promote の scope を超える |
| `WarpAutoRun_Init` | `li r0, 0` を lfs base + stw + 直後の `li r0, -1` で reuse | CW 1.3.2 は `r5=0` / `r0=-1` の別レジスタを選ぶ。6 C 変形で 3 byte 一定 diff | r0 を強制的に reuse させる C idiom 未発見 |
| `DashZone_ProcessAutoRun` | `mgr→r4` register choice + `0.0` re-load at L_xxx | 7 cycles で 13 byte 残差 (4 byte size + register choice + load reissue) | budget 切れ。3-5 cycle 追加で届く可能性 |
| `WarpAutoRun_GetParam` | `lwz r4, 0x4(r3)` での `r4` reuse + `fmuls f2/f1/f3` の operand 順 | source-level の rewrite で micro register-allocator を control できない。`-use_lmw_stmw on` は sibling fn の percent を regress させた | TU 単位の extra_cflags は副作用大、per-fn flag 機構が無いので諦め |
| `WarpZone_CheckEntry` | unused float local に `stfs` 単発 (frsp 吸収済み)、target は frsp 2 つ、C source は frsp 3 つ | CW 1.3.2 で `frsp + stfs` を 1 命令の `stfs` に潰す trigger 未特定 (volatile / non-volatile / address-take 全部 probe 済み) | CW idiom catalog が欲しい case |
| `WarpZone_CalcEdgeVectors` | 804-byte loop body の register allocation | 4 cycle で 78% 止まり、残り 22% は loop register allocation chase | ROI 低 (大規模 fn)、TU-level retrofit 候補 |
| `KartItem_OnKartHit` (auto_ONKARTHIT 2026-06-10) | branch-over-branch bool materialization: `or. r0,r3,r0; bne L1; b L2; L1: li r4,1; L2:` が 7 箇所 | CW 1.0/1.1/1.2.5/1.2.5n/1.3.2/2.0/2.5/2.6/2.7 × -O1..-O4,p/,s/nopeephole の全組合せが 1 命令短い `beq L2; li r4,1; L2:` に invert する。試行 C form: if / if-else / ternary / !=0 / !=var / >0 / s64 / register / goto-pair / inline-helper / `\|\|0` / `&&1` / `!!` / C++ bool (-lang=c++)。value-context は branchless (subic/subfe) 化。**追加消し込み (CarObject_OnItemHit 試行 2026-06-10)**: while-break / for-break (loop rotation で body が test の前 = block 順逆転)、explicit goto-pair、inverted goto、C++ inline member fn returning bool、member fn → bool local — 全て invert 形に潰れる | **2026-06-11 SOLVED (Phase 0 probe, batch_research_class1_phase0)**: `u8 b; if ((flags & MASK_ULL) == 0) { b = 0; } else { b = 1; }` — **明示的 `== 0` 比較 + then=0/else=1 の arm 順序**。CW は `!` 否定を正規化するが `== 0` の arm 順序は保存する。then=0 で full diamond が emit され branch folding が collapse できず、`li 0` arm が mask-hi の zero register に coalesce されて消えるため target 形が残る (レジスタ割付込み byte-identical 確認、ternary `((f&m)==0)?0:1` も同等)。前提: bool の register が既存 zero (u64 mask hi) と coalesce できること。compiler patch rev (1.1p1/1.3/1.3.2r/2.0p1/3.0a*/Wii*) と 1.3.2 の 62 pragma prelude は全 negative で消化済み — 詳細 matrix と probe harness は `docs/notes/cw132-class1-solved-probe-matrix.md` / `tools/compiler_probe/`。**実 TU 検証済み (2026-06-11 batch 1)**: 両 zero-half polarity で byte-exact (`docs/notes/cw132-class1-batch1-verification.md`)。UpdateCoinSpeedBonus が解法で matched。**前提条件 2 (2026-06-11 expansion batch で発見): bool が volatile reg に live すること** — callee-saved bool (OnKartHit b27/b28) では li-0 coalesce が失敗し 4 li 残差 (Tick の volatile-reg site は matched)。**注意: int-equality-chain 変種** (ApplyImpactReflect の `cmpw; bne; b` ×4 chain) には recipe 不転移 — li 0 削除は独立 zero web との coalesce が前提で chain には無い (4 probe negative、95.19% park)。precan で u64 family / chain 変種を判別せよ。**2026-06-10 main sweep (tmp/scan_class1.py、bne/b/L1:/li 1/L2: の 5 行 pattern grep)**: TU 内 class-1 持ちは 9 fn = OnKartHit(7 sites) / CarObject_OnItemHit(1) / ApplyImpactReflect(1) / ApplyImpactImpulse(1) / KartItem_Tick(1) / KartItem_PerFrameStep(1) / UpdateCoinSpeedBonus(1) / UpdateShadowBillboardAndViewport(1, 残部は低難度・roadmap は docs/drafts/KartItem_UpdateShadowBB_precan.handoff.md) / **KartItem_TickStatusEffectsByFlag(7, 未試行・事前 block 済)** |
| 〃 | 16-float copy block の frsp store-forward interleave (= class 2) | target は copy と演算を interleave し読み返しに `frsp f0,f7` を挟む。生成側は register 保持で frsp が出ない (`WarpZone_CheckEntry` frsp family) | **2026-06-11 SOLVED (Phase 2b probe, batch_research_frsp_phase2b)**: copy を **for-loop (`for (i=0;i<16;i++) s.mtx[i]=t[i];`、plain struct・volatile 不要)** で書く。variable-index store は CW front-end forwarding (constant-index lvalue のみ match) を逃れ、-O4,p が loop を full unroll して raw lfs+stfs block 化、late pass が constant-index read-back を `frsp fN,fM` (lfs 由来・reg live) / raw (演算由来) / real reload (reg evicted) に解決 — target の 5-frsp+1-reload partition そのもの。consume は constant-index named local + separate dot temps (f35_recipe)。GC 1.3-2.7 で再現、-O3/-O4/-O4,p 必須 (-O2/-O4,s 不可)、exceptions/RTTI/inline/lmw 中立。37-form matrix と recipe は `docs/notes/cw132-frsp-storeforward-phase2b-research.md`。旧「plain C 到達不能 / park」判断は否定済み。**in-TU 検証済み (2026-06-11, 2/2 fn)**: recipe core (frsp web / dead stores / frame cascade) は実 TU pressure 下で再現、partition は per-slot 制御可 (**reload にしたい slot だけ `*(volatile float *)&s.m[k]` read、frsp slot は plain read**)。access discipline: post-call read は plain / 同 BB read-after-write は read-back 形 (unnamed 降順 web) / dead-store・in-place sqrtf slot は volatile-cast。**ただし fn-level 100% は 2/2 とも fp-numbering tie-break family で park** (97.07% / 94.24%) — class-2 適用後の残差が register identity のみなら family rule で park。詳細 `docs/notes/cw132-class2-validation.md` |
| `ItemEffect_Dispatch` (auto_ONKARTHIT 2026-06-10) | class 2 の新 instance: kind14 branch の 22-float scratch block で dot product 消費 5 値だけ frsp copy + 1 real reload。86.34% → **97.07% (2026-06-11 検証後)** | class 2 自体は SOLVED・再現済み (5-frsp+1-reload partition は volatile-cast dir2 read で byte-exact、dy-first で schedule 一致)。残差は named dx/dy の scratch-vs-f31 mirror + dir web off-by-one = **fp-numbering tie-break family (source-closed) で park** | 97% paste-ready C は `docs/drafts/Class2_validation_nearmatches.handoff.md` appendix A (promote 時は splits.txt .data を 0x803F7640 まで widen)。fp-numbering family が解ければ self-correct |
| `CarObject_HandleObstacleHit` (auto_ONKARTHIT 2026-06-10) | approach-B `#pragma exceptions off` が late fresh callee-saved web の register pick を変える (target r24 / 生成 r31)。99.76% (188/188 命令、9 命令が 1 register 違いのみ) | real extab 持ち fn (= 元が -Cpp_exceptions on compile) は approach B でしか promote できない (asm_fn manual emit 群の後ろに extab が並ぶため A は順序破壊) のに、exceptions off では CW 1.3.2 が late web に highest-free reg を選ぶ。~11 source form で固定 | 詳細: `docs/notes/approachB-exceptions-off-regalloc-hardblock.md`。**症状検出: ~99% + 単一 register 差なら即この class を疑え**。解法候補: TU を extab 順で先頭から連続 promote して A に切替できる区間を作る (要 extab layout 分析) |
| `CarObject_ProcessWarpAndDash` (auto_ONKARTHIT 2026-06-10) | callee-saved web の **tie-break swap** (target self=r31/mov=r30、生成は逆)。94.6%、命令内容は全一致 + 2 scheduler slot | **exceptions on/off probe で codegen 同一 = 上の approach-B class とは別物**。allocation が block 構成で flip する (bisect: warp-only ✗ / warp+dash ✓ / +mgr ✗ / -CalcExitPosition ✓) = allocator 内部 ordering artifact。decl order / register kw / copy local / folded guard / early-return / unused param 全て無効 | 94.6% paste-ready C + view structs + extern 精密化一式を `docs/drafts/CarObject_ProcessWarpAndDash_94pct.handoff.md` に保存済み。**成功 idiom も同 file**: 多用途 out-param array は struct offset 0 に置く (interior member だと `&s.member` が callee-saved web に CSE される) / `cam = g; if (cam != g) {} else if (cam == 0) cam = 0;` で r3 直割付 / fp temp は decl 逆順で f2..f5 昇順 |
| adjustor thunk 6 fn (auto_ONKARTHIT 2026-06-10) | **C++ this-adjust thunk** (`subi r3, r3, N; b target` の 2 命令): CW 1.3.2 は C から sibling tail call (`b`) を一切 emit しない (probe: stwu/mflr + bl + epilogue になる) | C 言語機構の不在 (構造的・恒久) | **permanent asm_fn**。probe 不要、形状 (2 命令 subi+b) を見たら即 park。fn_8005249C / 800524A4 / 800524AC / 800524B4 / 800524BC / 800524C4 |
| `ItemEffect_TryStartByCategory` (auto_ONKARTHIT 2026-06-10) | **category-table addressing reassociation**: target は `addi rScratch, rBase, K` (symbol+const の table base) + `add rE, rScratch, prod` で group し、calls 越しには idx<<4 のみ callee-saved 保持。CW 1.3.2 -lang=c は 7 probe 全てで K を displacement か積に reassociate し、cross-call CSE は full pointer を保存 | symbol+const base は opaque loaded base (mov->table[idx] の add+lfs 形が効く例) と違い、定数畳み込みを止める手段が C に無い。原文は C++ accessor の this-temp と推定 (table-base init split と同族) | ~95% salvage C + probe ledger を `docs/drafts/ItemEffect_TryStartByCategory_95pct.handoff.md` と TU 内 asm body 上のコメントに保存。**precan: symbol+const base の const-offset table walk (addi scratch + add) を見たら 2 probe (named-off / cast-index) で park**。**一部訂正 (2026-06-11 expansion batch)**: cross-call で積 (mulli idx*stride) のみ callee-saved 保持 + table base を call 後に lis/addi で rematerialize する形は、plain `tbl[idx].field` spelling が自然に出す — この sub-pattern は hard-block ではない (Trap/Projectile で確認、`docs/notes/cw132-class2-expansion.md`)。Vec3 z,y,x fill の解法 (named float 3 連) は `docs/notes/cw132-onapplyrun-batch-idioms.md` idiom 1 |
| `CarObject_HandleItemEffect` (auto_ONKARTHIT 2026-06-10) | **dead-counter-in-ctr-loop** → **2026-06-11 SOLVED (Phase 2e)**: counter は dead ではなく **invisible use** を持つ — 後続 call の余分な (無視される) 引数として渡され、regalloc が counter を arg register に coalesce して命令ゼロで live になる (`ItemStateGuard_IsActive(guard, i)` + K&R empty-paren extern)。binary 全体の「dead」ctr-counter 76 件も全て同種の hidden use (最頻: break path の return 値として r3 coalesce) | 旧「hard block / DCE 不可避」判断は SUPERSEDED (note に追記済み)。**precan 更新: read されない addi rX,rX,1 を見たら、rX が次の bl の arg slot か exit path の return register かを確認 → ignored extra arg / returned counter で再現、park するな** | fn は 98.62→**99.93%** (残 7 行 = `handled` web の r29 vs r22 のみ)。新 lever: **one-home-per-variable** (fn-scope 変数は全 live range で単一 register home、interference で home を強制) / per-site block decl-order tuning。patch は `tools/compiler_probe/p2e_handleitemeffect_9993.patch`。詳細 `docs/notes/cw132-phase2e-research.md` |
| smallrun batch 4 fn (auto_ONKARTHIT 2026-06-10) | (1) wrapper の **prologue load hoist**: target が `lwz rX,off(r3)` を LR-save `stw r0,0x14(r1)` より上に置く (AdvanceAnim3c 77.8% / GetCurrentSpeedWithBonus 80.0%、後者は左→右 arg emission も)。(2) **return-pinned f1 への dying divisor coalesce** (CalcSpeedRatio 97.65%)。(3) **SR init の mr-vs-li const-fold** — **2026-06-11 SOLVED (Phase 2c)**: `mr rOFF, rI` init は loop が **static inline helper から inline された場合のみ** 生成される (front end は standalone な定数 copy を全 spelling で fold、~60 probe)。recipe: dual-induction loop を `static inline` helper に包む (定義は call site より前、`static inline` は prod flags で emit されない = layout 安全、plain `static` は emit される)。helper の local 宣言順で GPR coloring を調整 (ShadowBB は `(e, off, i)` で target-exact)。ShadowBB matched 済み。**GetMaxSpeedWithBonus も 2026-06-11 matched (Phase 2f model-guided)**: mv<->e park は param-merge 由来だった — **merged web は最後に色付けされる** corollary (Phase 2f RULE3 refinement) を使い、tail (cap + coinBonus 積) を helper 内に入れて wrapper を `return helper(self);` の passthrough にすると merge が消え、decl `(e,off,mv,i)` が leaf volatile pool の r7 降順で target 一致。FP 残差は accumulator 形 (`max=K*key; max=max*(1+bonus); return max;`) で f1 return web に coalesce。詳細 `docs/notes/cw132-mrsrinit-phase2c-research.md` + `cw132-allocator-phase2f-research.md`。(4) **lbz の load-over-store + r3 coalesce 両立不能** (GetBoostArmedAndTimer) | CW 1.3.2 は load を store より上に scheduling しない (alias 非分析) + return coalescing は named local で消える。probe battery は note 参照 | `docs/notes/cw132-prologue-load-hoist-unreproduced.md` に詳細 + **precan rule** (wrapper で hoisted load + compare 無し → 1 probe で見切る) + 勝ち idiom 4 種 (condition-assign entry / compound f1 chain / `(float)__fabs` / explicit off induction) |
| `KartItem_Dtor` (auto_ONKARTHIT 2026-06-10) | **-Cpp_exceptions on の EH scaffolding** (precan class): FP prologue `mr r31,r1` + back-chain epilogue + `addi r3,r31,0xNN; bl __unexpected; b .` の dead island ×12 + 404-byte SPECIFICATION extab | approach B (`#pragma exceptions off`) はこの機構を一切 emit しない = 構造的に到達不能。approach A は §14.1 mix-failure rule で除外 (manual extab 17 fn が先行)。加えて 13× `addic. r0,r29,off; beq` の smart-ptr dtor chain (WarpDashMgr_Cleanup family) も併発 | **precan grep 式: fn range に `bl __unexpected` があれば dispatch しない** (0 試行 skip)。TU 全 sweep で 12 fn 該当 (KartItem_Dtor + 末尾 dtor 群 11 個、`docs/notes/exceptions-on-eh-scaffolding-unpromotable.md` に一覧)。unlock は TU-level のみ: 先頭から address 順に promote して leading run を approach A 化、or .cpp + class retrofit |
| `CarObject_FrameUpdate` (auto_ONKARTHIT 2026-06-10) | **ScopedTimer inline-dtor の subi/lwz scheduler pair swap** (既知 hard-block の caller 文脈再現)。target `subi r6,r4,0x217d` → `lwz r7,0x8(r1)` 順、CW は全 C spelling で逆順 → **2026-06-11 SOLVED + matched (Phase 2d)** | **解法: dtor tail の ticks→µs 変換を整数 temp 無しの単一式で書く** (`us`/`diff`/`end` temp が 1 つでもあると lwz-first に flip、float temp は無害)。16 probe matrix で確定、C/C++ front end 無関係、static-inline-helper 軸はこの flavor には negative。target 内に lwz-first site (0x8008C468) も実在 = 順序は原文の temp 有無を encode する | **CarObject_FrameUpdate matched 済み**。recipe は program 全体 113 canonical dtor sites / 60 fn (BootDispatcher ×9 等) に適用可。TU 内 CarObject_Init 0x8004E618 が最近接 sibling (recipe そのまま適用可、full matching job として未着手)。canonical `__dt__11ScopedTimerFv` の opword shim も置換可能と判明 (要専用 batch)。詳細 `docs/notes/cw132-scopedtimer-phase2d-research.md`。**注意: `unsigned int t = lbl_806D10A0;` (pointer→int 暗黙変換) は CW 1.3.2 C で hard error — `void *t` + call site cast で書く** |
| `CarObject_Init` (auto_ONKARTHIT 2026-06-11) | **new-expr guarded-ctor の r0-join** (新 precan class): `p = Alloc(...); if (p) { <非自明な flag 計算 ~8 insns>; p = Ctor(p, flag); }` で target は join を r0 に持つ (`mr. r0,r3 ... bl ctor; mr r0,r3; L: stw r0` = C++ new-expr temp)。CW 1.3.2 C は全 spelling で join を r3 に copy-prop し **1 命令短い** (構造的 size 差、in-place park 不可能な -1 insn) | guard body が自明な 6 sibling sites は plain C で target 形が出る — blocker は test と ctor call の間に非自明 code がある場合のみ。7 spelling probe 全滅 | **precan: guarded-ctor site に非自明 pre-ctor code + target が mr.-r0 join → -1 insn 確定、park**。fn は 98.23% park (register-web tie-break も併発)。98% C + 検証済み新 lever 9 種 (volatile aux-pointer hoist / u8-typed prototype / inline-init preload / addi-CSE defeat / 逆順 stack layout 等) は `docs/notes/cw132-carobject-init-park.md` + `docs/drafts/CarObject_Init_98pct.handoff.md` |
| fp-scratch numbering family 4 fn (auto_ONKARTHIT 2026-06-11) | **fp scratch register numbering** (later-first-use→lower-reg): target は同時 live な scratch web を降順番号、CW 1.3.2 named web は **first-USE (store) 順で昇順** — store 順は target 形で固定なので mirror 到達不能。Explosion 88.99% / UpdateBoostVisualBlend 98.88% / TickStatusEffectsByFlag >99% / PerFrameStep 87.0% strict (内容差ゼロ、register 置換のみ) | **source-closed (Phase 2a 研究 132 probe + in-TU 検証 22 trial/probe)**: (1) direct-copy FE-temp 降順 path は copy src が const top-level pointer PARAM のときのみ (inliner が no-alias を落とす、chased ptr 不可) — 実 fn 全滅。(2) CSE'd const web (2+ uses) は別 immune sub-family (4 source form byte-identical)。(3) decl/def/name 全 permutation no-op。compiler/pragma/-opt 軸も全閉 | unlock は binary-level allocator 研究のみと推定。**precan: ~98%+ で残差が fp register 置換のみなら即この class、probe 不要で park**。昇順 def pipeline で emission は byte-exact にできる (PerFrameStep 87.0% 形、`docs/notes/cw132-fpnumbering-phase2a-validation.md`)。4 fn は lever 発見時に同時 self-correct |
| `CarObject_MainUpdate` (auto_ONKARTHIT 2026-06-10) | **loop strength-reduction coalescing** (flavor 5): target の 4x4 mtx-multiply loop は 3 独立 induction web (integer k via `slwi`+`stfsx` / row pointer r26 const-offset / dead i counter) を保持、CW 1.3.2 は 5 source form 全て (for+ptr / ptr reset / fully-indexed k,j / per-iter row ptr / do-while manual counters+out ptr) を単一 `&s`-base SR pointer (`stfs f0,0x34(r3)` 形) に潰す。~150 命令 + 下流 regalloc cascade で 82.05% 止まり | SR の coalescing decision を source から制御する手段未発見。`&s.mA` interior-member CSE (WarpAndDash class) も併発、mA は stack layout 固定 (sp+0xc0) で offset-0 回避不可 | 未試行: inline fn `(float *out, const float *a, const float *b, int k)` 化 / 2 重明示 loop nest / `#pragma opt_*` toggle。82% paste-ready C + **12 検証済み idiom** (MSL sqrtf inline / `(float)(double)` で frsp 強制 / quat→mtx product-locals / `static inline` 必須 — plain static は stray extab pair で global +4 shift / switch lowering 形状 / u64 mask ULL 定数) を `docs/drafts/CarObject_MainUpdate_82pct.handoff.md` に保存済み |

`KartItem_OnKartHit` promote 試行 (73.6% 到達) で**検証済みの構造知見** (再試行時に再発見不要):
- frame 0x2a0 / `stmw r25` は **単一 scratch struct** `{ float d[3]; float mB[16]; float mA[16]; HitEvent ev /*0x1EC*/; }` @ sp+0x8 で再現 (`&s.ev` が escape するので全 dead store が保持される)
- この TU の promote には Object 行に `extra_cflags=["-use_lmw_stmw on"]` が必要 (`stmw r25` vs `_savegpr_25`)
- signature は `unsigned char KartItem_OnKartHit(KartItem *self, KartDriver *victim)`、`ok = IsRaceStarted(); if (!ok) return ok;` で r3 reuse
- flags は aux(+0x304)+0x10 の **u64** field、全 flag test が 64-bit 演算
- 内積は `dx*m[0] + dy*m[1] + dz*m[2]` の source 順で target の fmuls 順を再現

### 14.3 main wave で確立した successful idioms

| 関数 | idiom | 説明 |
|---|---|---|
| `dtor_800A9CC8` / `dtor_800A9D2C` | `if (this) if (this) { ... }` (2 重 guard) | C++ deleting-destructor で inner subobject が offset-0 にあると、MWCC 1.3.2 は `mr. r31, r3; beq; beq` (重複した cr0.eq 分岐) を emit。C source 側で literal `if (this) if (this)` を書くと dedup されず byte-identical 再現 |
| `WarpAutoRun_OnEnter` | 7-float-arg force `(self, f1, f2, f3, f4, vx, vy, vz)` | leaf 関数で `stfs f5/f6/f7` を出すために 7 個の float 引数を要求。先頭 4 つは unused だが signature 上必要 |
| `dtor_800A9D2C` | `#pragma exceptions off` で extab auto-emit 抑制 | §14.1 approach B 参照 |
| `dtor_800A9CC8` | extab manual 削除で CW auto-emit に委譲 | §14.1 approach A 参照 |
| `lbl_806CF238[2]` open array | `extern void *lbl_806CF238[2];` (`WarpDashMgr_instances`) | sdata 上の 2-entry pointer array、`(u8 idx != 0) ? 1 : 0` indexing で `lwzx` reproduce — `WarpDashMgr_GetInstance` (pilot) |

### 14.4 sibling pattern unlock の活用

bundle 内に同じ codegen pattern を持つ fn が複数あることがある (例: `WarpZone_FindContaining` + `fn_800A8F4C` の frame-spill idiom)。1 つを解明すれば複数を unlock できる。HANDOFF.md の `notes` に「sibling X is also asm_fn for same reason」と書いておくと、次回 retry の対象が明確になる。

### 14.5 並列 sub dispatch + immediate merge で確立した orchestrator pattern

- 12 並列 sub を 1 wave で dispatch (wall-clock ~21 min、最遅 sub の duration)
- 各 sub 完了通知ごとに即 `merge_promote.py --batch <id> --no-build` (累積待ち禁止、`.kimi-code/skills/mkgp2-orch/SKILL.md` 「即時 merge」)
- conflict は `dtor_800A9CC8` + `dtor_800A9D2C` で forward decl 衝突 1 件 (両 approach A / B の forward decl 差) → main が Edit で resolve、両 fn を C prototype に統合
- 9 asm_fn worktree は merge_promote.py がスキップ (`status != "matched"`) → main が **HANDOFF.md harvest 後** に手動 cleanup (worktree 削除前に notes / blocked_reason を必ず読む、cleanup で context 消失)

### 14.6 PROGRESS 影響

- Round 3 base: 52 / 7614 matched
- Pilot GetInstance: +1 → 53
- Main wave (OnEnter + dtor 2): +3 → 56
- 累計 main wave 試行コスト: ~21 min wall-clock (並列)、~150 min CPU time (12 sub)
- 結論: bundle 内 1 fn ずつの並列 promote は **C++ scoped object 起因の hard-block 多数** に直面、ROI は singleton dispatch より低い。残り 9 fn は §14.2 の hard-block を 1 つでも解明すれば連鎖的に解ける可能性

## 15. wedge pattern: 隣接 2 fn を 1 TU にまとめると dtk cyclic dep が出るケース (2026-05-18, batch_text_8003907c_input)

`InputMgr_GetPlayer` (0x80039020, size 0x1C) と `GetInputManager` (0x8003907C, size 0x8) を 1 TU `game/InputMgr.c` にまとめようとしたら splits 段階で:

```
Cyclic dependency encountered while resolving link order:
  auto_fn_8003903C_text -> game/InputMgr.c
```

原因: 両 fn の **間に** `fn_8003903C` (size 0x40、extabindex entry 持ち、別 batch 管轄、auto_fn_8003903C_text として dtk reversed-extab group 入り) が挟まる。

1 TU で disjoint .text range を 2 entry split.txt に書くと、dtk が:
1. wedge の reversed-extab group `auto_fn_8003903C_text` を 1 unit と仮定
2. その unit と前後の 2 entry を含む単一 TU `game/InputMgr.c` の link order を決めようとする
3. wedge 入る前 (0x80039020-0x8003903C) → wedge unit (0x8003903C-) → wedge 出た後 (0x8003907C-) という 3-way 順序を要求
4. group → TU → group のループになり cyclic dep

**回避策 (= 採用方針)**: 2 fn を **個別 TU** に分割する。

```
splits.txt:
game/InputMgr_GetPlayer.c:
    .text  start:0x80039020 end:0x8003903C
game/InputMgr.c:
    .text  start:0x8003907C end:0x80039084
```

それぞれ単一 .text range なので wedge との order は trivial に解ける。

### 適用条件

- 隣接して matching したい 2 fn の間に extabindex / extab entry を持つ別 fn (wedge) があるとき
- wedge が現 batch の管轄外 (= 別 batch に dispatch する or 既に asm_fn / matched で touch 不可)

### sub-agent が踏むべき検証手順

1. seed 関数の前後 ±0x20 程度の addr range で、`mcp__ghidra__list_functions(start=..., limit=10)` 等で隣接 fn を確認
2. extabindex 持ちの fn (= reversed-extab group メンバー) があれば wedge 候補
3. splits.txt に 2 entry の disjoint range を書く前に必ず 2 TU に分割する

main 側で wedge を予測できれば dispatch prompt にヒントを書ける (`fn_XXXX が wedge なので別 TU に分けること`)。

### tu_hint との関係

main が提案する `tu_hint: input/InputMgr.c` のような単一 TU 想定は wedge 存在で破綻する。sub-agent の HANDOFF で複数 TU に分割する場合、`results[].src_path` を fn 単位で分け、`configure_py.add_objects[]` / `splits_txt.add_entries[]` も TU 分けて記述する (HANDOFF schema は既にこの形を許容)。

## 16. CW 1.3.2 branchless equality idiom (2026-05-18, batch_text_801e9070_itemholder)

`ItemHolder_HasItem` (`return (x == 1) ? 1 : 0;` で u32 比較を bool 化) を matching する際、CW 1.3.2 は branchless な `subfic / cntlzw / srwi r3, r0, 5` 3 命令 idiom に展開する:

```
lwz   r0, 0x20(r3)      # x = self->field
subfic r0, r0, 1         # r0 = 1 - x  (carry-set if x <= 1)
cntlzw r0, r0            # r0 = leading zeros of (1 - x). 32 if x == 1, else < 32
srwi  r3, r0, 5          # r3 = r0 >> 5. 1 if x == 1, else 0
blr
```

Ghidra decompile は同じ asm を `cntlzw(1 - x) >> 5` の C 形式で表示する。これは「1 - x がゼロなら cntlzw が 32 を返し、32 >> 5 = 1」という属性を利用した SDK 慣用句。

### C 側 idiom 選択

| C source | CW 1.3.2 出力 | 結果 |
|---|---|---|
| `return (x == 1) ? 1 : 0;` | subfic/cntlzw/srwi (branchless) | ✓ byte-identical (推奨) |
| `return x == 1;` | 同上 (`?:` 不要、自動) | ✓ |
| `return !((x - 1));` | subfic 経由しないので別 asm | × |
| inline asm / `__cntlzw` | 同上の手動展開 | △ 不要 |

**推奨**: `return x == n;` を最初に試す (CW が自動で branchless 展開)。失敗したら `?: 1 : 0` で明示。それでも 100% 不可なら asm_fn 退避。

### 同種 idiom の派生

- `(x == 0) ? 1 : 0` も branchless 展開される (`cntlzw(x) >> 5`)
- `(x != 0) ? 1 : 0` → `(unsigned)(x | -x) >> 31` 系 (= sign bit、Hacker's Delight)
- `x < n` で n が小定数なら subfic + carry 系 idiom (詳細は MWCC オプティマイザ依存)

これらは leaf bool getter で頻出する。Ghidra 側で cntlzw / subfic 系 asm を見つけたら、まず `return x == const;` を試すこと。

### 16.1 `(-x) & ~x` `andc` idiom (operand order matters) (2026-05-18, batch_text_80087a40_timer)

`IsGlobalTimerExpired` で発見。target asm は `andc r3, r0, r3; ...` (1 命令)。

| C source | CW 1.3.2 出力 | 命令数 |
|---|---|---|
| `((-x) & ~x) >> 31` | `andc r3, r0, r3; ...` | 1 (andc 1 命令) |
| `(~x & (-x)) >> 31` | `nor r3, r3, r3; and r3, r0, r3; ...` | 2 (nor + and、byte 差) |

CW は `~x & y` (NOR + AND) と `y & ~x` (ANDC) で別パターン展開する。`andc` (= `a & ~b`) を出したい時は **negation 因子を後ろに** 書く: `a & ~b` 形式。

頻出シーン: sign-bit-bool / "is non-zero" idiom (`((-x) & ~x) >> 31`)。Ghidra decompile が `((-x) & ~x)` の順で出すなら、C もその順で書く。

### 16.2 `if (x <= 0)` vs `if (x < 1)` signed compare (2026-05-18, batch_text_80087a40_timer)

`Timer_Decrement` で発見。`if (x <= 0) return;` を guard とする loop counter pattern。

| C source | CW 1.3.2 出力 |
|---|---|
| `if (x <= 0) return;` | `cmpwi r3, 0; blelr` (compare to 0, branch-if-less-or-equal-to-link-reg) |
| `if (x < 1) return;` | `cmpwi r3, 1; bltlr` (compare to 1, branch-if-less-than-to-link-reg) |

意味的には等価 (signed int) だが asm 上は 1 命令分の immediate value とブランチ条件が違う、結果 byte-different。target asm の `cmpwi rN, M` の M 値 (0 or 1) を確認して C を選ぶ。

### 16.3 `write_u32` ghost symbol name (2026-05-18, batch_text_80087a40_timer)

`g_globalTimer` (sbss @ 0x806D11D0) は元々 `write_u32` という placeholder name で symbols.txt に存在していた。これは Ghidra 解析の analysis artifact が dtk symbol dump に leak した可能性 (Ghidra で memo / annotation として書かれた文字列がそのまま symbol 名として fetch された)。

対策:
- 意味のある名前への rename を HANDOFF `symbols_txt.rename[]` で行う
- 「`write_u32`」「`read_u32`」「`memcpy_4`」等の **動詞 + サイズ** 形の symbol 名を見つけたら、Ghidra annotation の leak を疑う (game-side の実体は別の意味)

### 16.4 store-loop partial-unroll hard-block (2026-05-18, batch_text_800a0b34_racescene)

`RaceScene_ClearPlayerSlotPointers` (12 個の global を 0 で zero clear) を 4 cycle 試行したが C で 100% 再現不可。**asm_fn 退避**で bundle 維持。

target asm の特徴 (key insight):
- main base reg (r6 = &g_carObjects) を `lis + addi` で構築 (`stwu` で fuse しない)
- 3 個の derived base regs (r5 = r6+0, r4 = r6+0x10, r3 = r6+0x20) を事前計算
- i=0 の 3 store は **main base + bare `stw r0, disp(r6)`** (disp 0/0x10/0x20)
- i=1..3 の 9 store は **3 個の derived bases + bare `stw r0, disp(rN)`**
- 4 player × 3 array kind の 2D loop の **partial unroll** 形態

| 試行 | C 形 | 結果 |
|---|---|---|
| 1 | 3 別 extern array + 12 個別 write (full manual unroll) | 3 base regs、3 `stwu` (fused) + 9 `stw`、size 0x44 vs target 0x4C |
| 2 | 3 別 extern array + `for (i=0; i<4; i++)` loop | 同上 (CW が full-unroll) |
| 3 | 1 struct + 3 sub-arrays + member access | 1 base reg + `stwu` + 11 `stw r0, disp(r3)`、size 0x3C |
| 4 | struct + 3 local pointer aliases + for-loop | 同上 (CW が local alias を optimize away) |

CW 1.3.2 の選択肢は **full unroll** (3 base + fused stwu) or **single base** (1 base + sequential stws) の 2 択で、間の **partial unroll** (1 base no-fuse + pre-computed derived bases for outer loop) を出す source 形が見つからなかった。

### 16.5 accumulator-into-memory: intermediate local で add destination reg を flip (2026-05-18, batch_text_80216540_addcoins_extra)

`AddCoinsFromExtraStage` (`g_earnedCoins += g_extraCoinsToAdd;`) で発見。target asm は `lwz r3, ...; lwz r0, ...; add r3, r3, r0; stw r3, ...` (LHS reg = r3 を destination として再利用)。

| C source | CW 1.3.2 出力 |
|---|---|
| `g_earnedCoins = g_earnedCoins + g_extra;` | `lwz r3, lhs; lwz r0, rhs; add r0, r3, r0; stw r0, lhs;` (RHS reg = r0 が destination) |
| `g_earnedCoins += g_extra;` | 同上 (compound assignment は register allocation を変えない) |
| `int total = g_earnedCoins; total += g_extra; g_earnedCoins = total;` | `lwz r3, lhs; lwz r0, rhs; add r3, r3, r0; stw r3, lhs;` (LHS reg = r3 が destination) — **byte-identical** |

CW 1.3.2 はメモリ operand 同士の add では **RHS-side register** を destination として選ぶ。target が LHS-side reuse (`add r3, r3, r0`) を要求するときは、明示的な intermediate local 変数 (`int total = lhs;`) を導入すると CW が局所変数を LHS reg に allocate して flip する。

頻出シーン: 単純な global accumulator (`g_total += delta;`)、struct field 更新 (`obj->count += n;`)。target asm の `add rA, rA, rB` の rA が load-reg と一致しているなら、intermediate local pattern を試す。

### 16.6 vtable indirect-call thunk は C++ virtual fn idiom 必須 (2026-05-18, batch_text_8002cdc8_vtable_callslot2)

`Vtable_CallSlot2` (0x8002CDC8, size 0x2C, `(**(code**)(*self+8))();` 形式の thunk) を matching。

target asm: `lwz r12, 0(r3); lwz r12, 0x8(r12); mtctr r12; bctrl;` (vtable ptr → +0x8 slot を一度 r12 経由で chain)。

| C source | CW 1.3.2 出力 | 結果 |
|---|---|---|
| `(*(void(**)())(*(int*)self + 8))();` (plain C fn-ptr chain) | `lwz r3, 0(r3); lwz r12, 8(r3); ...` (r3-then-r12 chain) | × byte-diff |
| `void(**vtbl)(void) = (void(**)(void))*(int*)self; vtbl[2]();` (intermediate local) | 同上 (CW が local を optimize) | × |
| C++ virtual fn (`struct VT { virtual void f0(); }; self->f0();`) | `lwz r12, 0(r3); lwz r12, 0x8(r12); ...` (r12-only chain) | ✓ byte-identical |

**mkgp2 vtable layout** (Itanium-like): `+0x0` offset_to_top, `+0x4` typeinfo (metadata 2 slot), `+0x8` 最初の user virtual fn。よって `*self + 0x8` で呼ばれているのは class の **1 個目の virtual fn**。関数名の "Slot2" は byte offset 2 ではなく **0/4/8 の 3 slot 目** (= 1st user virtual fn) を指す。

**実装手順**:
1. `.cpp` ファイルとして書く (拡張子だけで CW MWCC は C++ コンパイラに切替、`game` lib の C cflags でも OK)
2. `struct ClassName { virtual void method(); };` で local class 定義 (vtable は TU 内自動生成)
3. C symbol name 維持のため `extern "C"` で wrap
4. extab/extabindex 自動 emit は CursorSound 系と同じ `#pragma exceptions on / reset` でも、または `.cpp` の C++ exceptions default ON でも自動

実例: `src/game/Vtable_CallSlot2.cpp` (commit TBD)。同じ pattern で vtable +0xC / +0x10 を呼ぶ thunk が他にも存在する場合は同 idiom 適用可能 (Slot3/Slot4 等)。

### 16.7 cmplwi (unsigned) vs cmpwi (signed): Ghidra `int` hint を上書きする (2026-05-18, batch_text_800302ec_scene3d_getcampos)

`Scene3D_GetCameraPos` で発見。target asm が `cmplwi r0, 0` (compare logical word immediate, **unsigned**) を出していたが、Ghidra decompile は `if (*(int *)(self + 0x28) != 0)` で **signed** を hint。

| C source | CW 1.3.2 出力 |
|---|---|
| `if (*(int *)(p + 0x28) != 0)` | `cmpwi r0, 0` (signed) |
| `if (*(unsigned int *)(p + 0x28) != 0)` | `cmplwi r0, 0` (unsigned) |

**判定方法**: target asm の compare 命令の opcode を読む:
- `cmpwi` / `cmpw` → signed (`int`)
- `cmplwi` / `cmplw` → unsigned (`unsigned int`)

Ghidra の decompile は struct 解析で型を推定するが、boolean 用途の field では `int` を選びがち。target asm の `cmpl*` を見つけたら `unsigned int` に書き換える。

頻出シーン: pointer-validity check (`if (ptr) ...`)、flag check、reference count、enum-like。これらは意味的には符号無しが自然。

### 16.8 assign-in-condition idiom: load を target reg に直接 (2026-05-18, batch_text_800a0bac_coursedata_safe)

`CourseData_GetDefaultPathKey_Safe` で発見。NULL-guard semantic-NOP wrapper:

```c
void f(void) {
  void *ptr = g_x;
  if (g_x == 0) ptr = 0;   // semantic NOP (g_x が 0 なら ptr も 0、非 0 ならそのまま)
  callee(ptr);
}
```

| C source | CW 1.3.2 出力 |
|---|---|
| `void *ptr = g_x; if (g_x == 0) ptr = 0; callee(ptr);` | `lwz r0, g_x; cmpwi r0, 0; mr r3, r0; bne L; li r3, 0; L: bl callee` (extra `mr r3, r0`) |
| `void *ptr = g_x; if (ptr == 0) {} callee(ptr);` | 条件無効化されて optimize out、guard が消える |
| `void *ptr; if ((ptr = g_x) == 0) ptr = 0; callee(ptr);` | `lwz r3, g_x; cmpwi r3, 0; bne L; li r3, 0; L: bl callee` ✓ byte-identical |

target asm が要求するのは `lwz r3, g_x; cmpwi r3, 0; bne L; li r3, 0; L: bl callee` 形 (load を r3 に直接 + 不要な branch-skip li r3,0)。**inline assign-in-condition** (`if ((ptr = g_x) == 0)`) で load を r3 から始める + 後続 `li r3, 0` を意味的 dead だが reachable な形で残せる。

頻出シーン: defensive NULL-guard wrapper、`if (auto = ...; ...)` 系の旧 C89 で書かれた idiom (mkgp2 game コードに頻出するっぽい)。

### 16.9 bool / unsigned char 引数: int に書き換えて clrlwi 除去 (2026-05-18, batch_text_801fe150_ui_playsetoggle)

`UI_PlaySeToggle(bool flag)` で発見。Ghidra decompile が `bool flag` で表示しても、target asm が `cmpwi r3, 0` の直接比較を出していたら C source は **`int flag`** に書き換える。

| C source | CW 1.3.2 出力 |
|---|---|
| `void f(bool flag)` または `void f(unsigned char flag)` | `clrlwi. r0, r3, 24; cmpwi cr0, r0, 0; beq L` (lower-byte を抽出してから比較) |
| `void f(int flag)` | `cmpwi r3, 0; beq L` (直接比較) |

ABI 上 r3 には呼び出し側で zero/sign extension 済みの値が arrive する想定なので、callee 側で `int` で受けて直接比較するのは安全。Ghidra の `bool` 推定は decompiler の artifact (lower-byte が non-zero かを見る形式)。

**判定方法**: target asm に `clrlwi.` や `extsb` が無く、引数 r3 を直接 `cmpwi` してるなら `int` で書く。

頻出シーン: flag 引数を取る短い wrapper / dispatch fn (UI_PlaySeToggle 系の 2-way thunks)。

### 16.10 return loaded-NULL idiom: r3 reuse で li r3, 0 を回避 (2026-05-18, batch_text_801240b4_suikaballobj_render)

`SuikaBallObj_Render` で発見。NULL-guard conditional tail-call wrapper:

```c
bool f(int *param_1) {
  bool result = false;
  if (*param_1 != 0) {
    result = callee(*param_1, 7);
  }
  return result;
}
```

| C source | CW 1.3.2 出力 |
|---|---|
| `return false; ... return result;` (literal 0) | `... li r3, 0; b .Lret` (extra 2 instr / 8 bytes) |
| `return (int)jobj;` ここで jobj は直前で load した NULL ptr | `... b .Lret` (r3 reuse、目的 reg 既に 0) |

target asm が `bne L; b .Lret; L: ...; bl callee; .Lret: epilogue` 形 (false branch も直接 epilogue へ) なら、`return 0` を avoidance するために **直前で load した null pointer 自体を return value にキャスト**して r3 reuse する。

C source 形:
```c
bool f(int *param_1) {
  void *jobj = (void *)*param_1;
  if (jobj == NULL) return (int)jobj;   // jobj は null、r3 既に 0
  return callee(jobj, 7);
}
```

頻出シーン: pointer NULL-guard + tail-call wrapper、bool/int 返り値の guard 系。`return 0` を見たら `return (loaded_var)` で reuse できないか確認。

### 16.11 stwu vs lwz prologue scheduling hard-block (2026-05-18, batch_text_801e6c94_ai_kartcontroller)

CW 1.3.2 が NULL-guard wrapper の prologue で **stw-first** か **lwz-first** のどちらを出すかが C source からは決定できない widely-seen hard-block。

| 形式 | 順序 |
|---|---|
| **stw-first** (再現可能) | `stwu r1, -0x10(r1); mflr r0; stw r0, 0x14(r1); lwz r3, off(r3); cmplwi` |
| **lwz-first** (再現不能) | `stwu r1, -0x10(r1); mflr r0; lwz r3, off(r3); stw r0, 0x14(r1); cmplwi` |

`AI_GetYaw` / `AI_HasItem` は stw-first → 100% matched。同 batch の `AI_GetLapDifference` / `AI_GetItemType` は target が lwz-first で、10+ C source variant (`int`/`unsigned int`/struct arg、ternary vs if、local var vs inline deref、per-object `-Cpp_exceptions on`、register hint 等) で reproduce 不可。

### 影響範囲

mkgp2 全体で **20+ auto_* groups** に同 lwz-first pattern が見られる (`stwu r1, -0x10(r1) / mflr / lwz r3, off(r3) / stw r0, 0x14(r1)` を grep)。NULL-guard wrapper 系小関数の大量 unblock 候補。

### 未試行の experimentation paths (project-wide focused investigation 候補)

1. **C++ TU wrap** (`.cpp` + `extern "C"`): C++ language flag で scheduler 動作が変わるか
2. **CW flag deltas**: `-O3,p` vs `-O4,p`、`-inline off`、`-sym on`、`-fp_contract off`
3. **Source-level inlining hints**: mwcc が支持する場合
4. **TU-wide function ordering**: 同 TU 内に複数 fn を並べた時の register pressure 差で scheduler が変化する可能性
5. **mwcc-2.x compilers**: 1.3.2 固定の確証は確認済みだが、game lib の一部 TU は別 CW 版の可能性 (調査要)

### 16.12 SDA21 trap: 4-byte pointer extern を `[4]` で large-data に追いやる (2026-05-18, batch_text_801ec568_enemyrun_init)

`EnemyRunType1_Init` / `EnemyRunType2_Init` で発見。.data 居住の vtable pointer を `extern void *lbl;` (4-byte single ptr) で宣言すると CW が SDA21 reloc 経路を選ぶが、symbol が `.data` にあって sdata threshold (8B) を超える可能性あり → linker error:

```
Small data relocation (109) requires that symbol be in a small data section but is in .data
```

**回避**: extern 宣言で **配列サイズを明示** (sdata threshold > 8B にする) と CW が large-data path (lis/addi base 計算) に切替:

| C source | CW codegen | 結果 |
|---|---|---|
| `extern void *lbl_804E4BEC;` | SDA21 reloc (109) | × linker error |
| `extern void *lbl_804E4BEC[4];` | large-data lis/addi | ✓ target asm 一致 |

`FrameSelection.c` の `extern char lbl[]` と同 idiom。.data / .rodata 居住の symbol を C TU から参照する際は **必ず array form (`[]` または `[N]`)** で書く。

頻出シーン: vtable pointer 参照 (C++ ctor で `*self = &vtable;`)、global pool table reference、constant table reference。`Small data relocation (109)` を見たら array form に切り替える。

### 適用パターン (asm_fn 退避を即決すべきケース)

以下の特徴を target asm に見つけたら、C 化試行 1-2 回で限界判断し asm_fn 退避を選ぶ:
- N 個の隣接 store / load を outer-inner loop に近い形で展開している (`stw r0, disp(rA); stw r0, disp+0x10(rA); stw r0, disp+0x20(rA);` パターン)
- base reg の `addi` が `stwu` と分離している (fused でない)
- derived base regs (r3 = main+0x10 等) が事前計算されている

これらは CW 1.3.2 の loop unroller heuristic に強く依存し、C source 形からの再現が極めて難しい。bundle 内 1 fn 退避なら他 fn の matching 進捗を守れる。

## 17. Ghidra struct pre-definition path (2026-05-18, batch_text_8020aa98_itemdisp_stop)

Ghidra の decompile が typed `T *self` arg + named field access を既に提示している場合 (= Ghidra 側で struct が apply 済み)、その layout を repo 内 `include/<lib>/<Type>.h` に **事前に書いてから** C source を書く。実例として ItemDisplay_Stop (singleton 60-byte fn + extab 8B + extabindex 12B) は **1 compile cycle で byte-identical** に到達。

### Workflow

1. Ghidra decompile output で struct 名 / field offset / 型を読む (`mcp__ghidra__decompile_function` の生出力で十分。DataTypeManager dump は補助、`run_script_inline` が PyGhidra script provider の class-not-found で失敗するケースあり)
2. `include/<lib>/<StructName>.h` を作成:
   - 触れる field だけ named member で記述 (例: `Sprite *sprite; int state; int pendingItemId;`)
   - **未知 gap は byte array で pad** して total size を Ghidra 計と一致させる (`unsigned char _pad08[0x08];`)
   - 依存型は forward decl で済ます (`typedef struct Sprite Sprite;`)
3. C source は `self->field` で field アクセス、offset cast (`*(int*)(p + 0x04)`) は使わない
4. extab/extabindex を伴う TU なら `#pragma exceptions on / reset` の JObj_Visibility pattern を併用 (CW auto-emit)

### 適用基準

- Ghidra が typed signature を出している (= struct apply 済み)
- struct size と field offset の主要部分が信頼できる
- bundle 内の全 fn が同 struct を touch する (header 共有のメリット)

### 利点

- opaque ptr + offset cast より readable
- 後続の同 TU fn が同じ header を再利用可能
- field rename / type 修正が 1 箇所で済む
- struct alignment 起因の不一致が起きにくい (CW が struct definition から正しい alignment を計算する)

### 注意

- 未知 field の padding を `_pad08[N]` のような byte array で埋める。`int _pad08;` のような guess type を入れると alignment が変わる可能性
- `_Partial` suffix が Ghidra 側にある struct は後続作業で field が追加される前提 — header に「+0x14 以降は未確認」コメントを残す
- src/ / include/ の C source / header コメントに em-dash 等の非 ASCII を入れると sjiswrap が SJIS encoding error を吐く (build は通るが warning)。ASCII に限定する

## 18. 3-arg pass-through forwarding idiom (2026-05-18, batch_text_80049afc_iseslot_stop)

`ISESlot_StopEffect` (0x80049AFC) で発見。target asm が `lwz r3, ofs(r3); bl <callee>` を吐くのに、自分の C source は `lwz r0, ofs(r3); bl <callee>` を吐いて 100% 不到達 (8 試行同 r0)。

### 原因

- Ghidra decompile は callee を no-arg (`FUN_xxx()`) として表示
- 実際の callee body (`build/GNLJ82/asm/auto_*_text.s`) では `r4` / `r5` を caller stored なしで参照 → callee は wider signature (3-arg `r3, r4, r5`)
- wrapper を `(void *self)` 1-arg として書くと、CW register allocator は load 結果の使い先が「cmp + branch」だけと見て r0 (scratch) を割り当てる

### 修正

wrapper と callee の両方を **callee の wider signature** で declare し、wrapper が受け取った r4 / r5 を literally callee に forward する:

```c
extern void callee(void *handle, int a4, unsigned char a5);

int wrapper(void *self, int a4, unsigned char a5) {
    void *handle;
    if (*(unsigned char *)((char *)self + 4) == 0) return 0;
    handle = *(void **)((char *)self + 0x18);
    if (handle != 0) callee(handle, a4, a5);
    return 1;
}
```

`bl callee(handle, ...)` が handle を r3 で消費するので、register allocator は load destination を r3 に pin する → target codegen と一致。

### 検出方法

1. 自分の o と target の差分が `lwz r0, ofs(r3)` vs `lwz rN, ofs(r3)` (N != 0)
2. 該当 bl 先 callee の asm body で r4 / r5 が unset state で読まれている (= callee の args)
3. wrapper signature を callee と同じ wide signature に揃える

### 適用基準

- wrapper が「コンディション 1 + bl + return」程度の単純 thunk
- 100% 不到達かつ残差が 1 命令の reg 番号違い (r0 vs rN)
- Ghidra decompile の callee signature を疑う (Ghidra は no-arg として表示しがち)

### CW register allocator の性質まとめ

- load 結果が cmp + branch のみで消費される → r0 (scratch / use-once)
- load 結果が直後の bl call で同 reg argument として消費される → 該当 arg reg (r3, r4, …)
- これは src 表現の問題ではなく **使用パターンの問題** — 同じ load を C で 8 通り書いても、その後 cmp + branch しかしない限り r0 が出続ける

## 19. clFlowItem unit 完食からの知見 (2026-07-19, unit-first claim #32)

4 fn (Draw/Update/Dtor/Init) を 1 TU `src/game/clFlowItem.c` の C++ retrofit
(ServiceMenu_Page.c 型) で処理。Dtor/Init は real C++ で 100%、Draw/Update は
byte-identical 手前の register-coloring 残差で asm_fn 退避 (C body は `#if 0`
保存、SHA-1 OK)。

### 19.1 extab_padding は「pad site 順に消費される byte stream」

`dtk extab clean --padding <hex>` の padding は **TU 内の全 pad site に先頭から
順番に充当される** (site 1 つ 2 byte)。DELETEPOINTERCOND action は dtor pointer
の直前 2 byte に CW junk `C7 02` を持ち、target はこれを保存している。
COND action を持つ TU は `extab_padding=b"\xc7\x02" * <site数>` を指定する
(clFlowItem: 6 site。site 数は `dol diff` の extab mismatch か target asm の
`.4byte 0x00XXC702` を数える)。従来の b"\x00\x00" は「pad 1 site が 0000」の
TU だっただけ。

### 19.2 singleton lazy-Get は ternary 形が DELETEPOINTERCOND を生む

```c
return g ? g : (g = new T);   /* ItemMsg_Get */
```
- new 式が「条件式の枝」に居ることで CW が ctor-in-progress cond flag
  (`li rN, 0` / `li rN, 1`) を割り、extab が **DELETEPOINTERCOND** になる。
  文 (`if (!g) { g = new T; }` + return) で書くと plain DELETEPOINTER で
  flag が出ない (extab 不一致)
- branch 形も ternary 固有: `beq .alloc; b .end` (値保持 early-return 形)。
  結果を捨てる呼び出し (`ItemMsg_Get();`) では自動的に `bne .end` 1 本に縮む
- null 済みポインタ返しの inline (`GetInput`) は **逆条件** ternary
  `g == 0 ? (T *)0 : g` が target の `bne .Lvalue; li rX, 0` 配置を生む
  (正条件だと beq/b の 2 branch になる)

### 19.3 delete の二重 beq は typed pointer + 明示二重 if

- `delete p` は p が **typed** (struct*) のとき自身の null check を emit する。
  `void *` への delete は check を出さない
- member slot の解放 `if (p) { if (p) free(p); p = 0; }` の明示二重 if は
  §14.3 の doubled-guard idiom と同じく両 beq が同 cr0 で残る (今回は
  ~ItemGridState() の cells 解放で使用)

### 19.4 別 TU 所有 dtor を DESTROYLOCAL から参照する空 dtor local

ResCtrl (stack local, ctor=ResCtrl_Init, dtor=dtor_80082960):
- class に **inline 空 dtor** `~ResCtrl() {}` を定義 → 通常 path は inline
  で消滅 (target に dtor call 無し ✓)、extab 参照用に CW が weak
  out-of-line copy を emit
- weak copy は redefine-sym で `dtor_80082960` に rename → link で auto blob
  の strong 定義に負けて **本体・extab entry ごと破棄される**
  (MemoryManager_TimedFree.o の ScopedTimer weak copy と同じ機構)
- 注意: weak copy 自身も extab/extabindex entry を持つので、
  `tools/extab_order.json` の宣言リストに **末尾で含める** 必要がある
  (含めないと name-set 不一致で reorder_extab.py が黙って skip する)

### 19.5 register-identity 残差 2 件 — phase2f の既知 closed class に該当

allocator 残差の分類台帳の**正本は
`docs/notes/cw132-allocator-phase2f-research.md`** (frida で colorer 実測済みの
機構モデル + negative-lever 台帳)。今回の 2 件はどちらも同 note で
source-closed と確定済みの class の再出現で、**着手前に突合せていれば
brute force (~60 build) を省けた** (反省点。SKILL の CW132 節に突合せ手順を
導線化済み):

- **Draw**: strength-reduction walker が死にゆく base pointer に合流しない
  (mr 2 本過多)。= phase2f の「move-coalescer は global interference graph
  駆動で source から動かせない」class (HandleItemEffect handled-web と同型)。
  decl order 34 perm / member fn 化 / destructive-walk 全て不発。
  destructive-walk (`p = (T *)((char *)p + 4)`) は命令数は合うが web が
  1 本増えて frame が +0x10 する (新観測、台帳に追記済み)
- **Update**: 1 変数に統一しても代入点で live-range split が起き、split
  range が独立に色付けされて別色 (r31/r24) になる。単一変数 + cast 別名 =
  phase2f で REFUTED 済みの variable-merge lever (CarObject_Init ch=o1) の
  再燃焼だった
- どちらも「命令列は完全一致、色だけ違う」形。この形は 2〜3 probe で
  phase2f 台帳と突合せ → 該当なら即 asm_fn 退避が正解 (C body は #if 0 で
  保存済み、将来の allocator 研究の題材)

### 19.6 mixed TU (asm_fn + real C++ 同居) の実運用確認

- manual emit 2 fn (Draw/Update) + auto emit 2 fn (Dtor/Init) + weak dtor
  entry の 5 entry を extab_order.json で並べ替えて SHA-1 通過。
  大 TU 以外でも per-fn park/promote が普通に使えることを確認
- extract_fn_asm.py の sdata アドレス materialize (`subi r4, r13, ...`) は
  **正しい bytes を出す** (r13 = _SDA_BASE_ = 0x806D6D20)。objdiff がそこを
  diff 表示するのは「reloc 有り vs raw offset」の表示差で、bytes は一致
  している。dol diff / SHA-1 が最終裁定

### 19.7 volatile-cast read as a local FP scheduling barrier (2026-08-11)

`KartItem_GetCarVelocityVec3` (commit pending in merge cycle) reached 100% by
combining a `volatile Vec3` spill with a volatile-cast read of only `velZ`.
The volatile local preserves target dead stack spills; the isolated volatile read
pins the target z/y/x `lfs` order without changing the emitted load instruction.
When a small Vec3 copy is otherwise byte-identical except for independent FP load
order, first keep the spill object volatile, then apply the volatile cast only to
the load that must act as the scheduling barrier. Avoid marking all source fields
volatile because that can over-constrain unrelated loads.

### 19.8 EffectSteering destructor recovery (2026-10-03)

Recovered the completed `unit_effectsteering_dtor` handoff: the 56-byte
`ActionLock_Reset` bridge is exact inline assembly, not a C promotion.
`EffectSteering_Dtor` itself remains auto-asm. Three C++ shapes peaked at
71.826385%; eight address-guarded virtual deletes and the 0x108-byte EH table
were not reproduced. A retry needs evidence for the eight distinct action-owner
member types and their exception specifications, not another flattened delete
sequence. Preserve this distinction in state and progress reports.

### 19.9 Card factory and Item orbit recovery (2026-10-03)

`card_task_manager_create` (0x8008A0A0, 512 bytes) is an exact asm singleton,
not a real-C success. Loop, explicit initialization, and reordered-count probes
peaked at 54.265625%. The target repeatedly reloads the manager entry pointer and
count around a four-entry factory table, then uses a genuine virtual slot 0x10.
A retry must establish the full ABI and aliasing model before register tuning.

`Item_OrbitAnchorKart` (0x800D9340, 572 bytes) was skipped with no source retained.
The recorded best was 98.81119%; unresolved differences were radius-clamp FP
comparison control flow and orbitFade FPR identity. ABI evidence from that run:
r3 Item pointer, r4 offset-vector pointer, r5 unsigned active flag, f1 yaw step,
f2 pitch step. These are observations, not proof that all C forms are impossible.

### 19.10 Item ground-following helpers: complete C match (2026-10-03)

Gravity (0x800D957C, 492 bytes), FallingDrop (0x800D9768, 324 bytes), and Simple
(0x800D98AC, 408 bytes) match as real C in `game/ItemMotion.c`. Their three
singleton extab groups form one contiguous TU without crossing the skipped
Orbit function. Use an explicit null-exit label and return the already-null
item pointer cast to int where the target preserves r3, rather than introducing
another zero materialization. For magnitude-preserving velocity scaling, a
separate reciprocal local before multiplication preserves the target `fmuls`
operand order. FallingDrop's threshold assignment inside the comparison
preserves the target expression schedule. Direct objdiff: 3/3 at 100%; worker
full DOL SHA-1 exact. Callee ABIs were independently checked from target asm;
no Ghidra decompile was available in this session.

### 19.11 EffectSteering Delay/reset real-C recovery (2026-10-03)

InitForDelay (436 bytes), ActionDelay_Reset (84 bytes), and ActionLock_Reset
(56 bytes) now match as real C/C++. Delay's old function-pointer ceiling is
resolved by the genuine two-slot virtual interface already used by Scale/Shake:
reset is the second virtual member, emitting the r12/r12 slot +0x0C chain.
A plain int sample-count field preserves the reload/clamp without added
volatility. The compiler-generated switch table requires extending the TU's
.data start to 0x803F99E0 and refreshing its anonymous-table rename mapping.
Existing exceptions-off flags retain manual EH ordering. All 15 functions and
.text/.data/extab/extabindex match; source-level gain is three functions/576
bytes, while aggregate linked-object counts stay unchanged (asm was exact).
If editing only the rename JSON, explicitly rebuild the source object: that
metadata is not currently an object dependency in the generated build graph.

### 19.12 Card command partial C match (2026-10-03)

`card_rw_kick_state_machine` and `card_read_tick` match as real C (244 bytes).
Unsigned-byte callee returns reproduce `clrlwi`, while signed status words
reproduce `cmpwi`. Both matched on the first implementation. The following
112-byte initializer remains asm_fn; three control-flow approaches reached
96.07% at best. Its switch C draft is preserved under `#if 0`, not counted as C.
The initial probes used exceptions off, while the verified hybrid TU uses on:
a later retry should first check explicit `== 0` branching under final flags.
This is a bounded-search result, not evidence of fundamental impossibility.
Two leading automatic extab records followed by the manual initializer record
preserve the target section order without an extab_order override.

### 19.13 Card early-return command wrappers (2026-10-03)

The unused read initializer (108 bytes) and eject initializer (116 bytes)
match on the first real-C approach. Their early-return error paths differ from
the parked shared-footer initializer in section 19.12; do not transfer its
branch-layout blocker to these siblings. Byte-valued latch results reproduce
the target truncation, and the eject wrapper uses the existing compatible
`unsigned int card_eject(int *)` declaration before narrowing the stored result.
The two disjoint ranges require separate singleton TUs, each using automatic
exception records with exceptions enabled. Both source objects are linked and
their text/extab/extabindex sections are exact; no manual EH mappings are needed.

### 19.14 Item wall helpers: ABI-led contiguous extension (2026-10-03)

BounceOffWall (440 bytes) and CheckWallCollision (340 bytes) both match on the
first C approach, extending ItemMotion's contiguous text end to 0x800D9D50.
All three earlier helpers remain exact and unchanged. Separate ordered stack
Vec3 copies preserve the positional-sound, trail, reflection and raycast ABIs.
FAbs_FloatAsDouble returns double: a float declaration would introduce an
unwanted rounding before comparison. The raycast returns an unsigned byte;
the response-mode field at +0x168 is unsigned, while the alias at +0x8 is signed.
Singleton automatic exception records append in target order without renames.
These minimal field names describe observed accesses, not a complete Item class.

### 19.15 EffectSteering remaining reset callbacks (2026-10-03)

ActionShake_Reset (76 bytes), ActionSplit_Reset (80 bytes), and
ActionVibrate_Reset (56 bytes) are now real C in their existing include fragments.
Split/Vibrate match immediately with the typed owner/output view. Shake's first
89.47% result differed only in the initial lfs scheduling: a 0.0f literal emits
the target early prologue load, while reading the mutable shared declaration
loads later. Existing sdata2 postprocessing binds that literal to lbl_806D297C,
whose target value is confirmed zero. Added declarations shift the viscosity
table alias from @153 to @162. All 15 TU functions and four payload sections
remain exact with manual EH; only InitForSplit remains asm in this TU.
Real-C gain is three functions/212 bytes, not an aggregate linked-match increase.

### 19.16 Item acceleration and bounded flying-render draft (2026-10-03)

Item_AccelClampVelocity matches as real C (204 bytes) on the first approach.
The separate reciprocal idiom also applies here. GetSpawnPosition's actual
ABI is a three-float vector setter, despite its name; target/callee instructions
establish this before source reconstruction. The independent singleton avoids
crossing the pending Homing/Launch functions.

Item_RenderFlyingFromKart is retained as NonMatching C at 99.61539% (260 bytes).
An empty switch case 0 restores the missing dispatch branch. Three approaches
leave five f1/f2 register substitutions in the blend increment/clamp; named
clamp temporaries did not change them. The complete matrix/attachment body and
callee ABIs are preserved for a future evidence-led retry. Its target object
supplies the verified link: this draft is not counted as a C promotion.

### 19.17 Card ping initializer (2026-10-03)

The 128-byte ping initializer matches on its first C approach. Both early
returns and the unsigned-byte pending flag reproduce the target branch layout.
Sci2Card_SendCmdPing consumes only the singleton pointer; argument constants
are set by that callee. Automatic singleton exception records and the linked
source object reproduce the full target without manual EH or symbol mappings.

### 19.18 Card cleaning initializer (2026-10-03)

The 204-byte cleaning initializer matches on the first C approach. Preserve
branch-specific status-store ordering and acquire the singleton before testing
the second byte guard. Sci2Card_ForceFailState consumes only r3; the preceding
r4/r5 constants are store temporaries, not forwarded arguments. Automatic
exception records, direct payload comparisons and the linked C object are exact.

### 19.19 Card cleaning body: bounded join residue (2026-10-03)

The complete 540-byte cleaning state machine reached 99.18519% in three
approaches (four compiles), but output is 544 bytes: an extra li r5,1 and
r5 rather than r4 at the retry completion join. Byte/int width and local-scope
changes did not resolve it. Preserve the disabled body in CardCleaningCommand.c
without expanding its singleton boundaries or declaring the shared TU NonMatching:
the existing 204-byte initializer must remain exact and source-linked.
Predicates return normalized bytes; the signed retry counter decrements before
the <=0 test; retry initialization ignores the command return and stores 1.
This is a bounded-search blocker, not proof of a source-closed compiler class.
No matched or genuine-C increase is attributed to this preserved draft.

### 19.20 Card ping body: scalar response locals and bounded join (2026-10-03)

The complete 880-byte body reached 99.47727% after three approaches. Six scalar
byte locals in reverse declaration order reproduce the two response triplets
at stack +0xB/+0xC/+0xD and +8/+9/+0xA; three-byte arrays misplace them.
Keep status checks independent: later predicates intentionally overwrite codes.
Inline command setup ignores the ping return and stores 1, unlike the standalone
initializer. Remaining output is 884 bytes: result in r3 rather than r0 adds
one constant load at the shared join. Combining assignments did not resolve it.
Retain the disabled body with original boundaries; the 128-byte initializer
remains unchanged, source-linked and exact. No matched gain is claimed.

### 19.21 Item homing complete near-match: table mutability and moves (2026-10-03)

The complete 932-byte homing scan is retained NonMatching at 99.29185%,936B.
Mutable open-array declarations keep six table words inside the probe loop;
incorrect const promises hoist them and disturb the saved-register set.
Explicit cursor lifetimes align all128-slot scan/control-flow and three avoidance
probes, stack vectors, GPR/FPR homes and 0x120 frame with stmw r25.
Remaining: target fmr f30,f1 becomes an f0 intermediary plus extra fmr;
scan zero init uses li r28,0 instead of mr r28,r29. Three approaches exhausted.
Field +0x168 is a target driver here, not the wall-response mode of other helpers;
FAbs returns double. The original object remains linked, source only compiles
under all_source. SHA-1 proves fallback preservation, not C promotion.

### 19.22 Item symmetric ground probes (2026-10-03)

Lateral and forward ground-pitch probes are complete real C, 420 bytes each,
source-linked and 100% exact including automatic EH. Their first argument is
a Vec3 origin, not Item. Signed-byte ground results and separate integer-copied
stack vectors preserve both hit branches and reversed fallback subtraction.
Three approaches reached exactness: an initial verified 0.0f literal loads
directly into f31, whereas the same-value named external zero used f2 plus a
copy. Existing pool postprocessing binds the literal; no instruction patch.
This adds two genuinely matched functions and 840 bytes, not asm scaffolding.

### 19.23 Card eject body: inline return propagation (2026-10-03)

The 836-byte eject state machine now matches as real C; the existing 116-byte
initializer stays unchanged and exact. Hand-expanded initialization produced
an extra constant-one load at the pending/status join (99.47369%,840B).
Branch-scoped locals worsened it. A genuine static inline initializer returning
one preserves all target effects but lets inline return propagation remove
dead eject-result stores at forcing sites; retry sites ignore its return.
This third approach reaches 100% with automatic EH and no emitted helper.
The shared join resembles the parked ping/cleaning bodies: this is new concrete
evidence for a narrowly bounded inline-composition retry, not blind local tuning.

### 19.24 Character-scaled render tail scheduling (2026-10-03)

Complete 336-byte C is retained NonMatching at 92.78571%; EH and 13-entry
jump table are exact. Separate case arms preserve each table destination;
an empty mode-zero arm preserves dispatch, and a literal clamp fixes FP homes.
Three approaches leave tail scheduling at +0xE4..+0xFC: vector-copy loads,
argument-address calculation and scale store order. Actual compiled C is not
linked, so full SHA-1 verifies fallback preservation and adds no matched bytes.
Retry requires concrete aggregate-copy scheduling/ABI evidence.

### 19.25 Ground-bend yaw spill (2026-10-03)

Complete 432-byte ground-bend C is preserved disabled at 98.14815%, without
changing the existing two exact 420-byte functions or TU boundaries. The caller
needs a double Vec3_ToYaw declaration despite the callee's frsp. Independent
probe copies/heights and reciprocal-first normalization reproduce the body.
Three approaches leave one spill web: target stores original f1 before argument
moves, while CW stores rounded f0 after fneg. Existing EH/source link and full
SHA-1 stay exact; there is no matching gain. Retry needs new spill-provenance
evidence, not more declaration permutations.

### 19.26 Ping inline-composition retry (2026-10-03)

New concrete evidence from the matched eject body justified one bounded retry.
A genuine static inline CardPing_Begin returns one and the caller assigns it
to pending; inline propagation removes the overwritten command-result store
and shares the target r0 constant join. First approach matches all 880 bytes.
The existing 128-byte initializer is unchanged; both functions, automatic EH
and actual source link are exact, with full-DOL SHA-1 verified. This adds one
function and 880 real-C bytes, resolving the prior 99.47727% disabled draft.

### 19.27 Cleaning inline-composition retry (2026-10-03)

The same new inline-return evidence resolves the 540-byte cleaning body on
the first approach. Its restart helper deliberately omits the standalone
active-cleaning guard. Consuming return one at forcing-pending sites removes
dead command-result stores and emits the exact r4 completion join. The 204-byte
initializer is unchanged; both functions and automatic EH are 100%, actual C
is linked, and full-DOL SHA-1 is exact. Gain is one function and 540 real-C
bytes, not the already-matched initializer or assembly scaffolding.

### 19.28 Card backup scalar snapshot bounded draft (2026-10-03)

The complete 904-byte target is preserved as NonMatching C at 57.123894%.
Two genuine C++ assignment forms emit an out-of-line helper; explicit two-phase
C snapshots retain the full accesses but produce 824 bytes, a smaller frame and
different destination-pointer lifetimes and 20-word spill scheduling. Three
approaches exhausted. Packed tail words at +1BA..+1CE preserve actual unaligned
word accesses; padding is not copied. The byte-copy callee takes three arguments;
card_backup consumes no incoming argument registers. Full SHA-1 verifies the
original fallback, not source acceptance. No matching gain; retry needs concrete
aggregate-copy/inlining evidence rather than another scalar permutation.

### 19.29 Tracked homing partial C promotion (2026-10-03)

Yaw-relative approach matches all224 bytes and automatic EH on its first C
approach. This caller needs a float Vec3_ToYaw result without a caller frsp;
do not transfer the double declaration required by the ground-bend caller.
Three stack vectors and the intentionally ignored magnitude call are retained.
The adjacent updater remains complete NonMatching C at99.41747%,412 bytes,
after three approaches: initial targetY/lowSpeed FP homes and multiplication
operand order differ. Separate adjacent singleton TUs preserve the exact yaw
source link and updater original fallback. Full SHA-1 exact; gain+1/+224B.

### 19.30 Hit propagation classifier bounded pair (2026-10-03)

Complete AllDrivers/Radius C is retained NonMatching at89.942856%/92.86487%.
Nested inline byte return restores the explicit zero/one full diamond when a
direct local or macro folds it. Separate radius product/add assignments preserve
float rounding; matrix/vector stack copies are exact. Three structural approaches
leave the outer-kind decision tree, scratch webs, effect-bus reload CSE and dead
duplicate classifier exit branch. Actual dispatch ABI consumes the fourth r6
driver argument. Both original objects supply the exact DOL: zero matching gain.
Main resolved independent split insertions by retaining all three non-overlapping
TUs in address order; no rollback or deletion of the earlier yaw/state ranges.

### 19.31 Localized Item asset rows (2026-10-03)

Item_GetLocalizedAsset matches as genuine C,184 bytes, on its first approach.
The signed ID threshold is hexadecimal0x147 (327), with fallback0x146 (326),
not decimal147/146. Alias lookup takes a truncated byte ID and writes a byte
through its optional output pointer; an eight-byte scratch array preserves the
target stack+8 address. Open pointer arrays[][3] reproduce the12-byte row and
four-byte variant strides without an inappropriate small-data relocation.
Automatic exceptions-on EH/index and actual source linkage were independently
verified on main, including exact full-DOL SHA-1. Gain+1/+184B; runtime/CI and
Ghidra verification remain unavailable, with full target/callee asm used instead.

### 19.32 Handheld render independent FP roles (2026-10-03)

Complete812B handheld render C is retained NonMatching at99.729065% after two
approaches; data104B and automatic EH/index are exact. Separate13-arm switches
preserve distinct destinations even when values repeat. The two owned tables
are8041E918..8041E980, distinct from the preceding CharacterRender table.
Named renderScale repairs later height/scale allocation, but eleven initial
scale/blend instructions retain different FP identities. Park this observed
identity residue rather than burn declaration permutations; no matched gain.
All matrix/vector ABI evidence and independent main source diff are archived.
Exact full-DOL SHA-1 uses the original fallback, not the compiled C draft.

### 19.33 Card v1 unpack zero-web residue (2026-10-03)

Complete C is retained NonMatching at98.98693%,608B vs612B target, after three
approaches. First-loop index-before-cursor initialization reproduces its dual
induction setup. Actual bitpack reader has four arguments and can leave its
output untouched; preserve only target initializations, not guessed clearing.
Remaining normalization at800902F8..8009031C merges the output-zero and loop
index-zero webs, losing one instruction and changing scratch registers. A
genuine static inline nonzero helper did not change this. No fourth attempt.
Main independently confirmed EH100%, index91.66667%, source-only linkage and
exact original-fallback DOL SHA-1. No matched gain; runtime/CI unverified.

### 19.34 Hit burst bounded argument-forwarding draft (2026-10-03)

Complete C is retained NonMatching at98.71681%,456B vs452B target after three
approaches. Splitting Rand out of the third vector-setter argument avoids an
unnecessary cross-call zero lifetime and restores frame50 and saved f31.
Residual count/kind r28/r29 homes and extra f0 forwarding remain; genuine
inline composition repairs the FP move but changes the entry extsb web.
Stop rather than combine untested permutations beyond the budget. Actual
rotation helpers consume full Vec3 pointers; orientation helper returns float.
Main independently verified EH100%, index91.66667%, source-only compilation
and exact original-fallback DOL SHA-1. Zero matched gain; runtime/CI unverified.

### 19.35 EffectSteering genuine constructor ownership (2026-10-03)

The600B constructor and automatic176B EH/index match as genuine C++.
Seven distinct four-byte owner members with declared external throw() dtors
generate exact DESTROYMEMBER actions; flattening them into pointers loses EH.
Inline derived constructors retain both base and derived vptr stores without
emitting new vtables. The last Delay new[] requires natural DESTROYBASE and
DELETEPOINTER actions. Independent ascending-offset zero statements fix the
only first-approach store reversal. TU-scoped mangled bridges preserve external
strong dtors. Main source link/text/EH/index100% and fullSHA1 verified; gain
one function/600B. Observed-layout types only, runtime/CI/Ghidra unverified.

### 19.36 Card legacy natural EH and bounded move residue (2026-10-03)

Complete real C++ draft is NonMatching99.05595%,576B vs572B, three approaches.
Two genuine new/inline constructors generate exact automatic40B DELETEPOINTER
EH with actionsC0/13C. Signed32 field>=1 naturally emits the target signed
comparison tail; an explicit signed64 cast unnecessarily adds instructions.
Preserve both raw copies, overwritten scratch and original overflow-before-free
path. Remaining version/used r26/r27 identities and extra r0 forwarding move
need new evidence, not declaration permutations. Main EH100%, index91.66667%,
source-only linkage and fallback SHA1 verified. Zero matched gain.

### 19.37 CObj viewport actual SDK ABI (2026-10-03)

ApplyViewport, LoadIntoGX and SetWorldMatrix all match on the first approach,
248B text plus24B automatic EH and36B index. Camera wrapper callees consume
r4 as an input source pointer; downstream setter copies three source words
to destination+0C/10/14. Do not omit the wrapper's second argument. Matrix
copy consumes r3 source and r4 destination, camera+54. Unsigned ready+28,
camera+4 and flags+8 preserve target guard and OR80000002. Explicit7/5-byte
assert strings retain SDA21 references. Main independently verified actual
source linkage, all sections100% and full DOL SHA1; gain3 functions/248B.
Runtime, CI and Ghidra remain unverified; actual target/callee asm was used.

### 19.38 CObj cached getters and output ABI (2026-10-03)

Four cached-tail wrappers match232B on the first approach, with automatic32B
EH and48B index100%. Unlike viewport setters, fn_802C7240/7318 retain r4
as a writable output pointer: downstream fn_802DA350 copies three words OUT
of camera subobject+0C/10/14. Do not infer direction from wrapper names.
Cached projection getter returns camera+88 allocation; view getter refreshes
and returns camera+54. Main independently verified source link, all sections
and full DOL SHA1. Genuine gain4 functions/232B; runtime/CI/Ghidra unverified.

### 19.39 CObj unprojection stack and alias ABI (2026-10-03)

UnprojectPoint matches236B and automatic EH/index100% on the first approach.
Declare48B matrix before12B vector to obtain vector stack+8/matrix+14.
Matrix copy uses source r3/destination r4; transform uses matrix r3/input r4/
output r5 and supports identical input/output vectors. Keep three independent
optional output stores and the null-source copy path when ready is zero;
an invented early return changes original behavior. Main retained both cached
and unproject Object entries when resolving their independent insertion conflict.
Actual source link and full DOL SHA1 verified; gain1/236B, runtime/CI unverified.

### 19.40 CObj perspective update and projection bounded layout (2026-10-03)

UpdatePerspParam200B requires signed projection-type getter, float aspect/FOV
getters and an18-float buffer at+3034 preceding near/far+307C/3080.
ProjectPoint's complete296B draft reaches91.27027% in three approaches;
frameA0, FP/GPR homes, stack arrays and automatic EH/index match, but both
nullable getter joins remain non-null-first unlike target null-first layout.
Aggregate Vec3 assignment naturally preserves the overwritten integer-copy
initialization; this is not the literal-float DSE blocker. Separate adjacent
TUs with a local source selector preserve exact update link and projection
fallback. Retain all three non-overlapping split entries when resolving
independent additions. No fourth probe; runtime/CI/Ghidra remain unverified.

### 19.41 CObj whole leaf bundle (2026-10-03)

The complete three-member88B blob is genuine C, not a getter-only wedge.
Signed1/2/4 checks and unsigned-byte return retain cntlzw/extrwi normalization.
Writing mode == global, rather than global == mode, preserves subf operands.
Minimal observed padded views keep byte+0A and buffer+3034; no guessed class.
Main independently verified text100%, no target/source EH, actual source link
and exact full DOL SHA1. Gain3/88B; runtime/CI/Ghidra remain unverified.

### 19.42 CObj debug and render camera ABI (2026-10-03)

Both64B/68B wrappers match on the first approach. Camera setup/getter/render
consume only r3; debug flush consumes matrix r3 and projection r4, not r5.
Unsigned ready and int-return nonzero normalization reproduce the render guard.
Main independently verified source-linked text/EH/index100% and full DOL SHA1.
Gain2/132B, with runtime/CI/Ghidra still unverified.

### 19.43 CObj LinePath bounded full draft (2026-10-03)

Complete1152B C is retained NonMatching94.416664%, two material approaches.
Double trig returns and float rounding, genuine inline MSL sqrtf, count reloads
and deliberately odd idle x stores are preserved. Mixed short-range FP homes,
vector scheduling and debug cursor residuals remain; early ROI stop is not
proof of source-closed impossibility. Main verified automatic EH/index100%,
source-only compilation and exact original-fallback DOL SHA1. Zero gain.
Retry requires a concrete vector-access/inline-composition lever; runtime/CI
and Ghidra remain unverified.

### 19.44 InputCmd complete leaf closure (2026-10-03)

Five functions44B match as genuine C on the first approach. Keep the anonymous
sample constructor with all four named accessors in the indivisible blob.
Sample live+10 is not InputCmd mode+10; use the appropriate observed view.
The constructor's unchanged self return preserves the external r3 ABI without
instructions. The8B SDA global is represented at full width, using only word0;
its semantic config type is not yet established by these accessors alone.
Main source text100%, no EH/index, actual link and full DOL SHA1 verified.
Gain5/44B; runtime/CI/Ghidra remain unverified.

### 19.45 InputCmd natural array ownership (2026-10-03)

The96B destructor and172B constructor match as genuine C++ on the first
approach. A20B sample with external nontrivial ctor and trivial dtor emits
new[] construction and delete[] cookie-minus16 naturally. The deleting-owner
flag is signed short; no manual EH or assembly is needed. Natural new[] emits
DELETEPOINTERCOND with r29 pointer/r28 flag and PC48..6C; its target junk
padding is C602, not the C702 of other families. TU-local mangled bridges
bind the external sample constructor, allocator, array helper and free calls.
Main resolved independent split insertion by retaining lifetime then leaf
in address order. Main text/EH/index100%, source link and full DOL SHA1 exact;
gain2/268B. Worker baseline child-Python alias failure was resolved by a
process-local venv Scripts PATH; final actual build exit0, no repo changes.
Runtime/CI/Ghidra remain unverified.

### 19.65 Debris Spawn bounded natural lifetime draft (2026-10-04)

Debris Spawn796B complete C++ draft is parked at93.77889% after three
approaches. Natural298B allocation/15 nontrivial44B particles and Vec3 local
generate DELETEPOINTER/DESTROYLOCAL, but cleanup pointer r30/r31, FP/GPR
roles and one extra move shift the local interval by4B. Aggregate-copy and
early-publication alternatives regress. Preserve disabled full draft and exact
original fallback; no matching gain. Main fallback text/EH/index100%, source
link and full SHA1 independently verified; retry requires new structural
evidence. Saturate_Double here actually consumes/returns floats.

### 19.66 JumpDistance timer bounded ResCtrl lifetime draft (2026-10-04)

Complete756B C++ draft is parked at80.677246% after three approaches with
identical output. Empty inline ResCtrl destructor naturally reproduces owned
24B DESTROYLOCAL; weak duplicate metadata is discarded. Scale/x/y/z FP
homes differ and signed tens computation sinks after reset rather than
remaining in r29 across it. Named scalar and inline-helper alternatives do
not move this output. Preserve full disabled draft and unchanged exact asm;
main fallback text/EH/index100%, source link and full SHA1 verified. Gain0,
new scheduling/aggregate evidence required before retry; runtime/CI unverified.

### 19.64 DemoWC constructor virtual base-this lifetime (2026-10-04)

The644B constructor is genuine C++ with automatic196B EH/12B index100%.
Five natural new expressions and nested root/base construction preserve all
cleanup actions. Declaring the observed virtual root/base destructors restores
the target redundant base-this copies; this is class semantics, not register
forcing. An inherited polymorphic Scene root places vptr0, and an inline
Driver wrapper captures character before the display getter. Three approaches.
Main independently verified owned text/EH/index100%, actual source linkage
and full DOL SHA1. Genuine gain1/644B; aggregate report gain0 because prior
assembly was already counted. Runtime/CI/Ghidra remain unverified.

### 19.63 FlowItemSelect natural destructor member specification (2026-10-04)

The488B owner destructor is genuine C++ with automatic40B EH/12B index.
The E8 member's throw() destructor naturally generates SPECIFICATION and
unexpected cleanup; do not apply that specification to the entire owner.
Empty-destructor allocation types retain redundant guarded deletes, and a
null-first inline input accessor preserves both guards. Two approaches.
Main independently verified owned text/EH/index100%, actual source link and
full DOL SHA1 exact. Genuine and aggregate gain1/488B. Observed layouts only;
runtime/CI/Ghidra remain unverified.

### 19.46 InputCmd sample clear inline composition (2026-10-03)

Tick/clear216B and PushSample148B match as genuine C with automatic EH.
The sdata2 zero must be declared const: mutable zero introduces alias reloads
around stores. Direct duplicated reverse loops retain two extra counter-copy
instructions; a genuine static inline clear helper removes them at both call
sites on the third approach. Push matches on its first approach. Sample stride
is20B, with xyz/code/live at0/4/8/C/10; signed WrapInRange consumes value/low/high
and detector returns signed int without hidden r4/r5 inputs. The immutable
shared observed-layout header is unchanged. Main retains samples, lifetime
and leaf split entries in address order. Actual source linkage, text/EH/index
100% and full DOL SHA1 verified; gain2/364B, not a fallback. Runtime/CI/Ghidra
remain unverified.

### 19.47 InputCmd detector inline result joins (2026-10-03)

The1136B detector matches as genuine C with automatic8B EH and12B index.
Signed int inline helpers assigned to one outer result preserve four r0-to-r3
joins; direct returns or byte helpers retain mismatches. Config at14 is an
integer mode bit-pattern, not a pointer to dereference. Mode2 starts at write,
has no live guard, resets its budget on each phase transition and returns one
on the default phase. Actual WrapInRange is inclusive one-step wrapping, not
modulo. Main retained detector/samples/lifetime/leaf splits in address order.
Object text/EH/index100%, actual source linkage and full DOL SHA1 verified;
gain1/1136B. Runtime/CI/Ghidra remain unverified.

### 19.48 JvsInput buffer clearing (2026-10-03)

ClearBuffers matches68B on its first ordinary C approach. Both globals are
32-byte unsigned-short[16] arrays: full sizes avoid inappropriate SDA21
relocations and sizeof supplies the exact memset length. Actual memset and
fill_mem consume destination/fill/unsigned length; return values are ignored.
Main independently verified text/EH/index100%, actual source linkage and full
DOL SHA1. Gain1/68B; runtime/CI/Ghidra remain unverified.

### 19.49 JvsInput reset bounded pool-base residue (2026-10-03)

Complete156B reset draft is NonMatching56.974358%, source164B, after three
material approaches. Target retains the message-pool base in r31 across three
variadic logs; direct C, size-informed extern and genuine inline composition
all rematerialize it per call. No fourth blind permutation. Six calibration
stores and actual variadic DebugPrintf ABI are retained. Main preserved reset
then clear split ranges when resolving independent insertion conflict. Main
EH87.5/index91.66667 and original-fallback full SHA1 verified; zero matched
gain. Retry requires new cross-call pool-base evidence, runtime/CI unverified.

### 19.50 JvsInput polling bounded alias residue (2026-10-03)

Complete692B poll C remains NonMatching63.231213%, source664B, after three
material approaches. Named edge fields, index arrays and flat halfword views
do not retain target alias reload/store ordering; an extra persistent player
base shifts the saved range to r21 rather than r22. Actual callee ABI requires
byte player/channel/counter arguments and independent output counts. Main
retained reset/poll/clear ranges and both Object entries in insertion conflicts.
Main EH87.5/index91.66667, original-object linkage and full fallback SHA1
verified; zero matched gain. Retry needs concrete alias/base-web evidence,
not more declaration permutations. Runtime/CI/Ghidra remain unverified.

### 19.51 JvsInput natural deleting lifetime (2026-10-03)

The72B destructor matches on the first genuine C++ approach, with automatic
8B EH and12B index100%. An undefined preceding key virtual leaves the target
vtable external; the empty virtual destructor naturally emits self preservation,
vptr restoration, signed-short deleting flag and self return. No throw()
specification is needed for this plain EH record. Scoped mangled bridges bind
the existing vtable and deleting destructor, using the shared operator-delete
bridge. Main independently verified source linkage, all payloads100% and full
DOL SHA1; gain1/72B. Runtime/CI/Ghidra remain unverified.

### 19.52 JvsInput EH-free metrics closure (2026-10-03)

All three members match as genuine C/C++,308B, on the first source approach.
An empty real constructor with undefined virtual key destructor keeps the
external vtable; the table has49 floats but reset clears only48. Signed index
guards normalize through an unsigned-byte diamond and divide only positives.
The existing extab rule cannot clean an EH-free object. A TU-only normal-SJIS
clone applies the existing symbol bridge without changing flags or instructions.
On a fresh split, the first configure has no Metrics source edge: defer the
hook until Ninja SPLIT regenerates the build, then require the expected rule.
Main retained Lifetime then Metrics entries in both insertion conflicts.
Independent source link, text/all symbols100%, no EH/index, full DOL SHA1
verified; genuine gain3/308B, no fallback gain. Runtime/CI/Ghidra unverified.

### 19.53 ItemBox constructors and ObjectTree timer (2026-10-03)

Main independently verified genuine C++ XYZ280B, GroundSnap324B and timed
blend316B: owned text/extab/index100%, actual source-object link and full
DOL SHA1 unchanged. Both constructor manual EH blocks are removed.
The immutable sdata2 zero must be declared const: XYZ otherwise reloads it
16 times and shifts cleanup PCs. GroundSnap's observed 0/-1/function triple
is a natural CW member-function pointer; a generic word struct changes copy
scheduling. Nontrivial Vec3 member and new debris with15 particle elements
naturally emit DESTROYMEMBER and DELETEPOINTER. Only observed layouts claimed.
ObjectTree's ScopedTimer uses the established single-expression conversion
and canonical strong destructor; generated weak copy is discarded. Separate
inline JObj predicates preserve nested guards. TU-only generated metadata
bridges do not rewrite instructions or EH bytes. Runtime/CI/Ghidra unverified.
Genuine gain3/920B; measured report989/309584 to990/309900 (+1/316B), not3/920.

### 19.54 KartDriver scoped timer retrofit (2026-10-04)

RenderTimed184B now uses genuine ScopedTimer C++ and automatic24B EH/12B
index. The single-expression conversion retains target scheduling; slot23
is volatile at stack+C and start tick at+8. Preserve the observed forwarded
r4/r5 arguments. TU-only automatic record names replace manual EH mappings.
The weak destructor duplicate is discarded: synthetic duplicate-section diffs
are not the owned target records, which independently match100% on main.
Actual source link and full DOL SHA1 verified. Genuine gain1/184B; aggregate
report gain0 because the previous asm was already counted. Runtime/CI/Ghidra
remain unverified.

### 19.55 SpriteSlot loop natural allocation (2026-10-04)

InitLoop396B is genuine C++, including automatic24B DELETEPOINTER EH and12B
index. An observed92B class with external constructor models natural new;
only this TU's constructor bridge is added. Keep20B model rows,12B animation
rows and signed row byte. The final start load uses row-byte-offset+4; a named
accumulator initialized from start then compound-added with frameOffset fixes
the last FP role difference in three approaches. Immutable sdata2 declarations
avoid alias reloads. Main independently verified source link, all payloads100%
and full DOL SHA1. Genuine gain1/396B; report gain0. Runtime/CI/Ghidra unverified.

### 19.56 ItemObjectManager controls whole-TU lifetime (2026-10-04)

Render/Reset/Update436B now match as genuine C++, with owned56B EH/36B index.
Both timed wrappers use the established single-expression ScopedTimer recipe.
Reset models256 static0x1EC elements with inline destructors; a genuine static
inline DestroySlots retains the target zero-copy initialization and pointer
homes. Keep an explicit null guard around typed delete of the manager object.
Scoped metadata bridges external destructor ABI and automatic EH record names;
declare owned records first and generated weak timer destructor last with the
existing order mechanism. Weak duplicate records disappear at final link.
Main independently verified all owned symbols/payloads100%, actual source link
and full DOL SHA1. Genuine gain3/436B; report gain0. Runtime/CI/Ghidra unverified.

### 19.57 SpriteSlot nonloop natural allocation (2026-10-04)

InitNonLoop388B matches genuine C++ on its first approach by transferring the
verified Loop natural92B new and row-start accumulator idiom. Keep active0,
state1 and omit the Loop-only initial JObjUpdate call. Signed row index and
const sdata2 preserve accesses; automatic DELETEPOINTER r29 at PC60 emits
exact24B EH/12B index without manual records. Main independently verified
all payloads100%, actual source link and full DOL SHA1. Genuine gain1/388B;
report gain0 because prior assembly was counted. Runtime/CI/Ghidra unverified.

### 19.58 HUD constructor nested ownership (2026-10-04)

HUD_Init276B matches as a genuine constructor on its first approach. Natural
new16B derived list preserves both base and derived vptr stores; a four-byte
nontrivial owner with external throw() destructor generates DESTROYMEMBER0.
Automatic44B EH includes DELETEPOINTER r30 at PC44 and member cleanup r29
at PC9C..F4. Undefined virtual key functions keep vtables external. Immutable
999/zero pools and signed cup9..16/mode2 retain target order. TU-only generated
name bridges replace manual records. Main independently verified text/EH/index
100%, actual source link and full DOL SHA1. Genuine gain1/276B, report gain0;
runtime/CI/Ghidra and complete HUD layout remain unverified.

### 19.59 ItemSelect explicit exception state (2026-10-04)

Init296B now matches genuine C++ child ownership; the other four exact C
definitions stay unchanged. Preserve its ordinary self/vtable/mode C ABI,
not an implicit owner-constructor signature. Natural new44B child calls the
external mode constructor and retains pointer r29. After the earlier Dtor's
exceptions reset, capability flag alone did not enable automatic cleanup:
explicit exceptions on in the island restores target frame20 and PCAC
DELETEPOINTER. TU-only generated-name aliases replace manual Init EH. Main
independently verified all five symbols/text788B/EH40B/index36B100%, actual
source link and full DOL SHA1. Genuine gain1/296B; report gain0. Runtime/CI/
Ghidra remain unverified.

### 19.61 Owner destructor complete closure (2026-10-04)

The three360B members of dtor_801FEA70 are genuine C++ deleting destructors.
Two offset-zero nonvirtual owners use typed virtual delete and throw(),
generating their unexpected islands and40B specification EH naturally.
The empty72B virtual lifetime restores its external vptr. Required EH order
AB8,B48,A70 differs from text/index. Declaring both order lists in EH order
forces the existing helper past its index-only early return without changing
the helper; final linker canonicalizes index. Main all named owned entries
and section metrics100%; raw synthetic index aggregate20% is not hidden.
Actual source link and full DOL SHA1 exact establish final acceptance.
Genuine gain3/360B, report gain0. Runtime/CI/Ghidra remain unverified.

### 19.60 ReverseFlag constructor aggregate provenance (2026-10-04)

ReverseFlag368B now matches genuine C++ with natural92B new and automatic
24B DELETEPOINTER EH/12B index. Implicit return-this and nested inline JObj
predicates preserve early returns and redundant guards. A float-only Vec3
copy scalarizes into saved f29..31 across root lookup; a float/word union
aggregate retains the observed integer stack copy then float loads on the
second material approach. No register forcing, manual EH or instruction
patching. Main independently verified owned text/EH/index100%, actual source
link and full DOL SHA1. Genuine gain1/368B; aggregate report also+1/368B.
Observed views only; runtime/CI/Ghidra remain unverified.

### 19.62 CourseData lookup allocation and inline base lifetime (2026-10-04)

MiyoshiCard factory148B and destructor144B now use genuine C++ lifetime,
natural DELETEPOINTER/DESTROYBASE and ordinary deleting destructor without
throw(). Preserve the NULL-only context destruction guard. Main genuine
members/EH/index100%, actual source link and full DOL SHA1 exact. Draw's
unchanged assembly scores98.26923% from six literal SDA relocation operands;
do not claim raw TU text100%. Draw84.63%/Tick97.87% complete disabled drafts
remain parked; Tick's generated44B jump table is outside immutable ownership.
Genuine gain2/292B, aggregate gain0; runtime/CI/Ghidra unverified.

FlowKart display retrofit follow-up: complete disabled560B draft reached
97.85714% in three material approaches. Natural three Sprite allocations
already produce exact56B EH/index; threshold indexed addressing and mode/
loop register webs remain. Original assembly remains source-linked100% and
main full SHA1 exact. Zero genuine gain; retry needs new structural evidence.

The 124B derived destructor and 160B factory now match genuine C++ with
natural typed destruction and ignored new12B constructor result. The
constructor stores the global internally; retaining that behavior preserves
the null allocation join and automatic DELETEPOINTER register home. The
derived destructor frees values before keys and inlines the base vptr store.
All six owned functions and text472B/extab40B/index36B independently match
100% on main, with source linked and full DOL SHA1 exact. Existing three C
accessors remain unchanged. The standalone72B base destructor remains
original assembly: strong emission prevents required derived inlining,
while inline emission omits its standalone body. Three approaches exhausted;
do not count that fallback as C++. Genuine gain2/284B; report delta0.
Runtime/CI/Ghidra remain unverified.

### 19.67 NokoNoko natural new and cleanup composition (2026-10-04)

Init808B is genuine C++ with automatic88B EH and12B index100%. Four92B
Normal3D allocations and one64B entity generate the five target DELETEPOINTER
actions naturally. A nontrivial empty entity destructor retains the nullable
delete guard; a trivial destructor incorrectly removes8B. A genuine pointer-first
inline cleanup preserves walker r31/counter r30 where an indexed loop swaps
homes. Preserve signed seconds modulo64 after unsigned clock division and the
full16B spawn rows. Main independently verified text/EH/index100%, actual source
link and full DOL SHA1. Genuine gain1/808B; aggregate gain0 since prior assembly
was counted. Only observed layouts claimed; runtime/CI/Ghidra unverified.

### 19.68 CoinSystem bounded natural row initialization (2026-10-04)

Complete C++ draft is disabled at99.20784%,1016B vs target1020B after three
material approaches. Natural three92B allocations recover DELETEPOINTER PCs
F4/114/134; caller null guards and genuine inline row composition retain the
192B row/global reload schedule. Explicit dual induction removes an extra
branch, but incoming table/new-temp and index/walker homes still differ; the
target mr r30,r29 initializer is missing. Automatic EH94.64286/index91.66667
are not acceptance. Original exact assembly is retained; main independently
verified fallback text/EH/index100%, source link and full SHA1. Gain0; retry
requires new coupled-web/strength-reduction evidence. Runtime/CI unverified.

### 19.69 FlowKart constructor independent matrix draft (2026-10-04)

Complete disabled C++ constructor reaches93.42437%,948B vs952B after three
material approaches. Natural base/ResCtrl member and five new expressions
produce the right184B cleanup kinds/owners/registers. Separate matrix arrays
remove aggregate interior-address CSE, but scale/translation placement reverses,
pool initialization stays after ResCtrl rather than in the prologue, and table/
position address reassociation loses4B. EH95.652176/index91.66667 are not
acceptance. Original assembly unchanged; main independently verified fallback
text/EH/index100%, actual source link and full SHA1. Gain0; retry requires
new structural pool-hoist/stack-address evidence. Runtime/CI/Ghidra unverified.
