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
| **Phase 3: 大規模 group** | >10 fn group への適用検討。partial coverage (例: 100 fn 中 30 matched + 70 asm_fn で 1 TU 完成) の現実性検証。`tools/build_extab_map.py` の `>10 fn` グループ (621 関数) が対象 | 大 |

T9-2 と T10 は Phase 1-3 の中に解消される (個別 ticket としては閉じる)。

## 10. open question

- mkgp2-decomp の cflags に `-Cpp_exceptions off` がある状態で、bundle 内の関数 (auto extab を持つ) を C + asm_fn 混在で書くとき、`-Cpp_exceptions on` を per-TU で付ける必要がある (extab/extabindex section を mwcc に出させるため)。Phase 1 検証で確認。
- asm function の body 内で参照する extern symbol (`lbl_802E8F48@ha` 等) は C 側の `extern` 宣言を要求するか? mwcc の asm function はおそらく独立 reloc を出すので不要のはず。Phase 1 検証で確認。
- bundle 内 N 関数すべてが asm_fn になった場合と `Object(NonMatching, ...)` で全体を asm から build した場合とで、生成 .o は byte-identical か? 後者の方が configure.py が短いので、全関数 asm_fn なら NonMatching に倒す方が筋。Phase 1 で「全 asm_fn なら自動 NonMatching 提案」を sub の振る舞いに入れる。
