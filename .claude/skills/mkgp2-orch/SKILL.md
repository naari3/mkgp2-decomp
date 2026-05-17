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

## 即時 merge & 知見反映 workflow (同 TU 内多 sub 並列 promote)

12 並列 sub が同 1 TU の別 fn を編集するパターン (Phase 3a-small main wave で確立)。**累積待ちでマージしない** — 完了通知ごとに即処理。理由は次節「累積待ち vs 即時 merge」。

### 即時 merge の流れ (sub 完了通知ごと)

1. **通知受信 → HANDOFF.md と commit message を即 Read** (worktree cleanup 前):
   - `worktree/HANDOFF.md` の json blob + 自由記述 markdown 両方
   - `git -C <worktree> log -1 --format=full HEAD` (sub の commit msg は知見の宝庫、cleanup 前にしか読めない)
2. **`python tools/merge_promote.py --batch <batch_id> --no-build`** で apply (build verify は最後にまとめる、累積防止)
3. **conflict が出たら次節「conflict resolution 標準手順」**、出なければ自動で state.json flip + cleanup
4. **知見反映を同 cycle 内で実施** (次節「知見反映: 各 merge で必須」)
5. 全 sub 完了後、`ninja build/GNLJ82/ok` を 1 度だけ実行して SHA-1 verify

### 累積待ち vs 即時 merge

| 戦略 | pros | cons |
|---|---|---|
| 累積待ち (`--all` を最後に 1 回) | build verify が 1 度で済む | conflict が複数同時発生 → resolve 順序が複雑、main の context 一気に圧迫、各 sub の HANDOFF / commit msg を後でまとめて読むため知見が薄まる |
| **即時 merge (推奨)** | conflict を context-fresh で resolve、sub の知見を直後に拾える、dispatch との overlap | build verify を `--no-build` で skip + 最後に 1 度 (この工夫で cons はほぼ消える) |

### 知見反映: 各 merge で必須

各 sub が 5-15 min かけて発見した知見 (HANDOFF notes / blocked_reason / commit message に詰まっている) を、worktree cleanup や cycle 跨ぎで失わない。次 cycle で再発見するコストは初回の数倍。

**手順**:
1. HANDOFF.md `notes` / `blocked_reason` / `docs_notes` を Read
2. `git log -1 --format=full HEAD` (sub commit msg)
3. 知見をカテゴリ分類し、**同 cycle で追記** (commit に含める):

| 知見の種類 | 追記先 |
|---|---|
| 1 fn matching idiom (例: `if (this) if (this)` for C++ dtor / cache+search 4 分岐 / `> -1` for `>= 0` / `&& early return` 形式 / 7-float-arg force) | `~/.claude/skills/mkgp2-match/SKILL.md` (10 節以降の項目 add) |
| extab / extabindex 制御 (manual 削除 = approach A / `#pragma exceptions off` = approach B / mix での SHA-1 影響) | `docs/per_fn_matching_strategy.md` (extab section) |
| bundle 内 promote pattern (forward decl 統合、struct extend、open array extern、approach A/B mix の動作性) | `docs/per_fn_matching_strategy.md` (1.5 節 partial matching) |
| orchestrator 運用 (3-way merge resolve pattern / worktree base mismatch / parse error trigger 条件) | `.claude/skills/mkgp2-orch/SKILL.md` (本 skill) |
| Hard-block (CW 1.3.2 register allocator quirk / C++ + exceptions の C 単体不可 / frame-spill idiom 未解明) | `docs/per_fn_matching_strategy.md` 「known hard-block」セクション |
| TU レベル構造 (bundle を `.cpp` + class に retrofit する必要 / `game_extab` lib の C++ scoped object 要求) | `docs/large_extab_group_strategy.md` |

4. 重複検出: 既存 doc に同 idiom あれば update (追加 commit ref を例文として add)、新規なら append
5. 「知見反映の追記」を merge commit に含めるか、または直後に別 commit (どちらでも可、cycle を跨がない)

**最大の失敗**: 知見反映を「後でまとめてやる」と先送り → cycle 跨ぎで context 薄れ + worktree cleanup で commit msg / docs_notes が消える → 知見ロス。**absolutely 同 cycle で実施**。

### conflict resolution の標準手順

`merge_promote.py` が conflict 検出 → abort + state.json は flip されない + worktree は残る。main の手で:

1. `git status` で conflict file 確認 (`UU <file>`)
2. file 内 `<<<<<<<` marker 周辺を Read、両 sub の意図を HANDOFF / commit msg と照合
3. Edit で resolve (典型パターン):
   - forward decl 衝突 → 両 sub の C prototype を統合 (例: `void *dtor_XXX(void *this, short flag);` の 2 行に集約)
   - struct field 衝突 → offset 衝突しない field を merge、同 offset なら片方を捨てて他方に統一
   - extern signature 衝突 → より specific な signature (引数型あり) を採用
   - extab approach 衝突 → mix が SHA-1 OK ならそのまま、不可なら片方の approach に統一
4. `python configure.py && ninja build/GNLJ82/ok` で SHA-1 verify
5. fail → 両 sub の approach が semantic-conflict → 片方を asm_fn 退避に格下げ (main で C body を asm body に書き戻す、forward decl を `asm void X(void);` に戻す)
6. OK → `git add` + commit (commit msg に解決の選択理由を必ず記載 — 後の cycle でなぜそれを選んだか追跡可能に)
7. **手動で merge_promote.py の post-processing を補完**:
   - state.json の該当 fn を `matched` に flip:
     ```bash
     python -c "import json; from datetime import datetime,timezone; p='.orchestrator/state.json'; d=json.load(open(p,encoding='utf-8')); d['functions']['0xXXXX']['status']='matched'; d['functions']['0xXXXX']['last_attempt_at']=datetime.now(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ'); d['functions']['0xXXXX']['notes']='<conflict resolve 詳細>'; open(p,'w',encoding='utf-8').write(json.dumps(d,indent=2,ensure_ascii=False)+'\n')"
     ```
   - worktree + branch cleanup: `git worktree remove --force .worktrees/<batch_id> && git branch -D orch/<batch_id>`
8. **知見反映**: conflict の解決方法と approach mix の動作性を `docs/per_fn_matching_strategy.md` に追記 (次回の自分への引き継ぎ)

**将来の tool 改善余地**: `merge_promote.py` に `--skip-apply <batch_id>` mode を追加すれば 7 の手動 state flip + cleanup を機械化できる。現状は main の自由演算 (頻度低いので未実装)。

## merge_promote.py の現在の scope

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
