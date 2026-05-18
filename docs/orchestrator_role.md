# Orchestrator (main agent) role

並列 decomp 体制の main agent (orchestrator) の責務、cycle 手順、merge ルール、lock 戦略をここで規定する。

関連:
- `docs/orchestrator_state_schema.md` — state.json schema
- `docs/sub_agent_role.md` — sub-agent の制約と HANDOFF.md 仕様
- `docs/orchestrator_ops.md` — user 向け運用手順
- `prompts/cycle.md` — `/loop` で発火する main の 1 cycle prompt

## 責務

main agent は以下を**専任**する (sub-agent には任せない):

1. `state.json` / `log.jsonl` / `locks.json` の更新
2. `configure.py` / `config/GNLJ82/splits.txt` / `config/GNLJ82/symbols.txt` の編集
3. `docs/` の更新 (sub からの知見追記提案を反映)
4. **batch 編成の判断**: Ghidra MCP で xref / callees / namespace を引いて、pending function から関連関数群を grouping する (詳細は `prompts/cycle.md` CASE 5)
5. sub-agent の dispatch (`Agent` tool with `run_in_background`)
6. sub-agent の TaskStop (graceful drain / immediate kill)
7. worktree の作成と削除
8. main ブランチへの commit
9. SoT (configure.py / report.json / symbols.txt / splits.txt / Ghidra dump) からの state.json sync
10. HANDOFF_TO_USER.md への escalation

batch 編成は **tool に押し付けない**。`tools/plan_batches.py` は fallback / debug 専用で、本番 cycle では使わない。Ghidra MCP の情報を見ながら main が判断する。

sub の作業範囲との境界は `docs/sub_agent_role.md` 参照。

## Cycle 動作 (1 cycle = 1 heavy action 原則)

`/loop` dynamic mode で発火する。各 cycle で **heavy action (CASE 2 merge) は 1/cycle 上限**、light action (CASE 3 再编成 / CASE 4 dispatch / CASE 5 编成) は同 cycle 内で chain して複数実行してよい。ただし heavy + light の混在は避ける (merge した cycle で続けて編成・dispatch しない、context が重くなる)。

```
CASE 1 (最優先): drain.flag が立っている
  drain mode の処理:
    - active_subs が 0 → /loop CronDelete、session_end ログ、return
    - active_subs ≠ 0 → 各 sub の通知を待つだけ。新規 dispatch しない
    - 通知を受けたら CASE 2 へ
  
CASE 2: 通知済み or HANDOFF.md 待ちの batch あり
  merge 処理 (詳細は次節):
    - HANDOFF.md を parse
    - configure.py / splits.txt / symbols.txt を apply
    - build verify (ninja build/GNLJ82/ok)
    - SHA-1 OK ならば main commit、worktree 削除、state.json 更新
    - SHA-1 fail / parse 不能 ならば batch を failed にして再編成

CASE 3: 失敗 batch の再編成
  - 単純 retry はしない (前回判断による)
  - 失敗理由を読んで:
    - 関数を分割 → 別 batch を新規作成
    - NonMatching で隔離 commit (skill 7.5節 制約C)
    - blocked 化 → HANDOFF_TO_USER.md にエスカレーション

CASE 4: active_subs < 3 かつ pending batch あり → 1 つ dispatch
  dispatch 処理:
    - 次の batch を pick (status=pending、size 小、依存解決済み優先)
    - Ghidra MCP で関数情報を pre-fetch (decompile / xref / 構造体)
    - worktree 作成: .worktrees/<batch_id>/、branch orch/<batch_id>
    - Agent tool run_in_background で sub 起動
    - state.active_subs に entry 追加
    - state.batches[<bid>].status = dispatched
    - log.jsonl に dispatch event

CASE 5: pending batch 無く pending function あり → main が新規 batch 編成
  編成処理 (extab-aware):
    - pending function から seed を 1 つ pick (size 小 + extab_group_size <= 10 で絞る)
    - seed.extab_group が非 null なら、その group の全 pending member を bundle 必須
      (= dtk reversed-extab group 制約。1 関数だけ抜くと split-error)
    - seed.extab_group が null なら singleton として Ghidra MCP の callees / namespace
      で近傍関数を最大 5 個まで bundle
    - tu_hint を推定 (sub が最終決定するので任意)
    - state.batches に追加 (status=pending)
    - 同 cycle 内で CASE 4 へ fall through して即 dispatch (light chain)
  大規模 group (>10 fn) は別レーン: HANDOFF_TO_USER.md に escalate して放置
  (詳細ルールは prompts/cycle.md CASE 5、extab map は tools/build_extab_map.py 参照)

CASE 6 (該当なし): "no action" を 1 行 print して return
  ScheduleWakeup で 1200-1800s 後の fallback wake を予約
  (sub 完了通知が来れば即 wake するので fallback は安全網)

完了判定:
  pending=0 かつ in_progress=0 かつ active_subs=0 かつ全 batch terminal
  → HANDOFF_TO_USER.md に "全 batch 完了" 書き、/loop CronDelete
  これ以外で /loop を停止してはならない
```

## SoT sync (cycle 冒頭)

各 cycle の冒頭 (CASE 判定の前) で SoT から state.json を再 derive:

1. `config/GNLJ82/symbols.txt` を読み、各 function の `name` / `section` / `size` / `has_named_symbol` を更新
2. `config/GNLJ82/splits.txt` を読み、各 function の `tu_hint` を range lookup で更新
3. `configure.py` を読み、`Object(Matching|NonMatching, ...)` から `status` を derive
4. `build/GNLJ82/report.json` を読み、`fuzzy_match_percent` を更新
5. `tools/ghidra_symbol_dump.json` の mtime が state の `ghidra_dump_mtime` より新しければ、`ghidra_named` と (将来) `dependencies` / `callers` を再 fetch

3 によって `Object(Matching, ...)` で declared された関数は `matched` に **自動昇格** する。手動編集による drift を毎 cycle 解消する仕組み。

実装は `tools/orch_sync.py` (将来追加) に分離する。

## Merge ルール (CASE 2 詳細)

HANDOFF.md の format は `docs/sub_agent_role.md` 参照。

main は以下の順で処理する:

1. **Lock 取得**: `locks.json` に `configure.py` lock を holder="main" で記録
2. **HANDOFF.md parse**: yaml block を抽出
3. **新規 src ファイル merge**: sub の worktree から `git diff main -- src/` を取り、main へ apply。`Bash` で `cd <worktree>; git format-patch main..HEAD --stdout | git -C <main> am`
4. **configure.py 編集**: `configure_py.add_objects[]` を該当 lib の `objects[]` に追記
5. **splits.txt 編集**: `splits_txt.add_entries[]` を追記
6. **symbols.txt 編集**: `symbols_txt.set_scope[]` 等を反映
7. **build verify**: `python configure.py && ninja build/GNLJ82/ok`
8. **Progress 確認**: `build/GNLJ82/report.json` の matched_functions が増えているか確認 (skill 9 節「偽 match の検出」)
9. **commit**: 関連ファイルをまとめて 1 commit
10. **worktree 削除**: `git worktree remove --force <path>`
11. **state.json 更新**: batch.status=merged。functions[].status は以下のルールで:
    - HANDOFF.md `results[].status == "matched"` の関数 → SoT sync で `matched` に自動昇格 (`Object(Matching, ...)` 由来)
    - HANDOFF.md `results[].status == "asm_fn"` の関数 → **明示的に `asm_fn` に設定** (SoT からは derive できない、HANDOFF 由来のみ)。`PROTECTED_STATUSES` に入っているので次 cycle の SoT sync で上書きされない
    - HANDOFF.md `results[].status == "nonmatching"` の関数 → SoT sync で `nonmatching` に自動昇格
12. **Lock 解放**

`asm_fn` 関数の詳細 (退避判定、bundle 内 partial matching の扱い) は `docs/per_fn_matching_strategy.md`。

build verify が fail した場合:
- diff を保存して batch.status=failed、blocked_reason に出力 head を記録
- worktree は保持 (user 確認用)
- HANDOFF_TO_USER.md にエスカレーション

## Lock 戦略

main は基本 single-threaded なので locks.json は冗長だが、以下の状況で意味を持つ:

- main の中で複数の sub からの merge を**順次**処理する間、他の cycle 行動 (SoT sync 等) と競合しないため
- 将来、merge を async 化する場合の予約

現状は `configure.py` / `splits.txt` / `symbols.txt` の 3 つに対して single lock を取れば十分。

## エスカレーション (HANDOFF_TO_USER.md)

以下のケースで `.orchestrator/HANDOFF_TO_USER.md` に append:

| 条件 | 内容 |
|---|---|
| batch が `blocked` に遷移 | batch_id、失敗理由、worktree path、推奨対応 |
| recovery で `interrupted` を検出 | batch_id、worktree path、`HANDOFF.md` 不在の事実 |
| build verify が再現性ある fail | エラー head、diff snippet |
| ghidra_dump が古い (>7日) | sync を促す |
| 全 batch 完了 | session 終了の signal |

user に届ける手段は (a) tmux 内 main agent の console 表示、(b) HANDOFF_TO_USER.md の git status での確認、(c) 将来的に `PushNotification` (現在は手動確認)。

## active_subs の自前管理

`TaskList` ツールは `TaskCreate` で作ったタスクのみ表示し、`Agent` で起動した background sub は対象外。よって main は以下を **state.active_subs に必ず記録** する:

- dispatch 時: `Agent` ツールの return から取った `agent_id`
- 通知受信時: 即 entry を削除し batch.status を遷移
- TaskStop 時: `TaskStop` 呼び出し後 entry を削除

agent 完了/kill の通知は `system-reminder` 内の `<task-notification>` で来る。main の cycle prompt はこれを parse して active_subs を更新する。

## kill propagation

`TaskStop` 呼び出し後、sub の child process (Python / ninja / mwcceppc) が実際に死ぬまで **最大 10-15 秒** の遅延あり (Spike 検証済み)。よって:

- immediate stop 直後に worktree を `git worktree remove --force` するときは 15 秒 wait を挟む
- もしくは `--force` でなく retry-on-EBUSY を 3 回まで試す
