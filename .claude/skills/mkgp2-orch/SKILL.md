---
name: mkgp2-orch
description: mkgp2-decomp 並列 decomp orchestrator の main agent 責務分担を保つための skill。`/loop` で cycle を回す、sub-agent を dispatch する、HANDOFF.md を merge する、`merge_promote.py` / `scaffold_mega_bundle.py` を呼ぶ、新規 batch を編成する、conflict を resolve する、といった場面で trigger。judgment は main の責務、tool は mechanical part のみという原則と、その失敗パターン (judgment を tool に閉じ込めて user に押し付ける) の予防策を提供する。
---

# mkgp2-decomp 並列 decomp orchestrator: main agent の責務分担

## 必読 docs (cycle 開始 / orchestrator work の初動で必ず Read)

新規セッションで初めて orchestrator work に入るとき、または compact 直後にこの skill が trigger したときは、以下を **memory / summary に頼らず実ファイルから** Read:

- `docs/orchestrator_ops.md` — user 向け運用全体像、起動 / 停止 / drain の手順
- `docs/orchestrator_role.md` — main agent の責務、cycle 動作 (CASE 1-6)、Merge ルール、Lock 戦略
- `docs/sub_agent_role.md` — sub の制約と HANDOFF.md JSON spec、status field 要件マトリクス
- `prompts/cycle.md` — `/loop` で発火する main の 1 cycle prompt 本体
- `docs/per_fn_matching_strategy.md` — asm_fn 退避 / 1.5 節 bundle 内 partial matching / asm_fn → matched promote 手順
- `docs/large_extab_group_strategy.md` — dtk reversed-extab group bundle 戦略

`prompts/cycle.md` は main 自身が `/loop` で実行する手順書。それ以外は方針 / 規範。

## 鉄則 1: judgment vs tool 分担

**judgment は main の責務、tool は mechanical part に閉じ込める**。

| 役割 | 担当 |
|---|---|
| batch 編成 (どの fn を 1 batch にまとめるか) | **main** (Ghidra MCP の xref / namespace / extab_group を見て判断) |
| sub-agent dispatch (`Agent` tool 呼び出し) | **main** (どの sub に何を振るかの判断込み) |
| HANDOFF.md merge 時の conflict resolution | **main** (Edit tool で手で resolve) |
| 失敗 batch の再編成判断 (retry / 分割 / NonMatching 隔離 / blocked) | **main** |
| 完了判定 / loop 停止判断 | **main** |
| asm の機械的抽出、extab struct emit | tool (`tools/extract_fn_asm.py`) |
| `git diff base → git apply --3way`, state.json flip, worktree cleanup | tool (`tools/merge_promote.py`) |
| 新規 TU scaffold (extract + configure.py 編集 + splits.txt 編集 + renames merge) | tool (`tools/scaffold_mega_bundle.py`) |
| worktree 作成 + orig/ populate | tool (`tools/setup_worktree.py`) |

**禁止事項**:
- `tools/plan_batches.py` 的な「1 fn = 1 batch」自動化を本番 cycle で起動する (`docs/orchestrator_ops.md` L46-48 明示)。判断責務を奪う
- merge tool に rollback / pre-flight `git apply --check` / `--resume` mode 等の高度な conflict-handling robustness を入れる (main の resolve 余地を奪う)
- cycle 全体を 1 script にまとめる (1 cycle 1 action 原則を破る、judgment を script に閉じ込める)
- judgment を tool に閉じ込めて conflict / 失敗時に user に手動 revert を押し付ける

## 鉄則 2: conflict resolution は main の手で

並列 sub dispatch 後の merge で `git apply --3way` が conflict を返したら:

1. tool は当該 batch の apply を中断 + 状況を report (rollback しない)
2. main が patch / 該当ファイルの diff を読む
3. main が Edit tool で resolve (典型: 両 sub が同 `lbl_xxx` extern を `[]` open array にしたい / 同 struct に offset 衝突しない field を追加したい、等)
4. main が次の batch 処理を continue (tool 再起動 or 残処理を手で)

**なぜ tool に rollback を入れないか**: conflict の semantic intent は dispatch 時点で main が把握済み (誰に何をやらせたか覚えている)。実際の conflict は「同意図の独立編集」が大半で、main が数行 Edit するだけで resolve できる。tool が atomicity を保証しようとすると main の判断余地を奪う。

参考実績: Round 3 (commit f9b22bb) で 7 sub の merge を main が 7 round 手動 Edit で完了。これが正しいモデル。

## 鉄則 3: 1 cycle 1 action

`prompts/cycle.md` の CASE 1-6 のうち、最高優先度の 1 つだけを 1 cycle で実行する。
- 編成 (CASE 5) と dispatch (CASE 4) は別 cycle
- merge (CASE 2) と次の dispatch (CASE 4) は別 cycle
- 複数 batch を 1 cycle で merge してもよい (mechanical) が、merge と編成を混ぜない

理由: 失敗時の rollback 範囲を狭める + context 圧迫を防ぐ + cycle 単位で停止判断できる。

## sub-agent dispatch の実装パターン

新規 batch を dispatch するとき、main が決める要素:

1. **batch 構成**: どの fn を 1 batch にまとめるか
   - dtk reversed-extab group 内なら group 全 pending member を bundle (= 1 indivisible TU 制約、`prompts/cycle.md` CASE 5 参照)
   - 同 group 内でも asm_fn 状態の fn を 1 つずつ別 sub に promote させる pattern (Round 3 / main wave で実証、本 skill の「同 TU 内多 sub 並列 promote」項参照)
2. **worktree 用意**: `python tools/setup_worktree.py <batch_id>` で `.worktrees/<batch_id>/` を作成
3. **prompt 構築**: sub に何をやらせるか
   - 担当 fn の addr / name / size / asm 行範囲
   - 必読 docs (`docs/sub_agent_role.md`, `~/.claude/skills/mkgp2-match/SKILL.md`)
   - 直近の参考 commit (典型例の git show)
   - 制約 (同 TU 他 fn は touch 不可、30 min / 3 試行、100% 不可なら asm_fn 退避)
   - HANDOFF.md JSON schema (status / src_path / build_verified)
4. **Agent tool 起動**: `Agent(subagent_type='general-purpose', run_in_background=True, prompt=...)`
5. **state.active_subs に記録**: 通知受信用 (TaskList には現れない、main の self-bookkeeping)

## 同 TU 内多 sub 並列 promote の merge

12 並列 sub が同 1 TU の別 fn を編集するパターン (Phase 3a-small main wave で確立):

- 各 sub は worktree 内で `git commit` (orch/<batch_id> branch)
- main は `python tools/merge_promote.py --all` で全 batch を sequential 順次 apply
- 各 apply は `git apply --3way` (base commit が揃っていれば cleanly merge)
- conflict は extern 同時拡張 / struct field 競合のみ。main が Edit で resolve
- 全 batch merge 後に `ninja build/GNLJ82/ok` で SHA-1 verify、state.json flip、worktree cleanup

## merge_promote.py の現在の scope

`tools/merge_promote.py` は **mechanical part のみ** 担当 (鉄則 1 通り):

- 各 worktree から `git diff base -- <src_path>` で patch 抽出
- `git apply --3way` で main checkout に apply
- `ninja build/GNLJ82/ok` で SHA-1 verify
- 各 fn の `state.json` entry を `status: matched` に flip
- worktree + branch cleanup

**やらない**:
- conflict 検出時の rollback (main の resolve 余地を残す)
- pre-flight `--check` mode (over-engineering、conflict の semantic は main が既知)
- sub の HANDOFF.md format 違反検出 / 自動修正 (HANDOFF spec は sub の責任)

modes: `--batch <id>` / `--all` / `--no-build` / `--no-state` / `--no-cleanup` / `--dry-run`

## 失敗パターン集 (compact 直後 / 新規セッションで陥りやすい)

1. **judgment を tool に閉じ込める**: 「cycle script を作って scaffold + dispatch + merge を 1 つに」と考える → 1 cycle 1 action 原則を破る、dispatch judgment を script 化することで main の責務を放棄する。**正解**: script ではなく main が cycle ごとに `prompts/cycle.md` の手順を判断 + tool 呼び出しで progress
2. **conflict 自動 rollback を tool に入れる**: stash-based snapshot / `--resume` mode 等を merge tool に追加したくなる → main の resolve 余地を奪う、user に「手動 revert してね」と押し付ける構図になる。**正解**: tool は abort + 詳細 dump、main が Edit で resolve
3. **compact summary だけ信じて docs 読み直さない**: summary に「タスク #N pending」とあっても、根拠 (なぜそのタスクを作ったか) が落ちている可能性。**正解**: 重要な判断分岐 (新 tool 設計 / cycle script 作成 / 大きな refactor) の前に必ず `docs/orchestrator_ops.md` と `docs/orchestrator_role.md` を Read で確認
4. **大規模 extab group (>10 fn) を 1 batch で dispatch しようとする**: dtk reversed-extab group 制約で 1 関数だけ抜くと split-error、しかし >10 fn 一括は context 圧迫で sub が破綻。**正解**: HANDOFF_TO_USER.md に escalate + 一旦保留 (大規模 group の incremental NonMatching scaffold は将来課題、`docs/large_extab_group_strategy.md` 参照)

## 関連 skill / docs

- `~/.claude/skills/mkgp2-match/SKILL.md` — 1 fn を 100% matching に持っていく workflow (sub-agent と main 共通 reference、特に 10.5 節 extab asm_fn 退避 / cache+search idiom)
- `docs/per_fn_matching_strategy.md` — asm_fn 退避戦略、bundle 内 partial matching、asm_fn → matched promote 手順
- `docs/large_extab_group_strategy.md` — dtk reversed-extab group の bundle 戦略
- `.claude/commands/mkgp2-orch-{start,drain,kill,status}.md` — orchestrator 制御の slash command
