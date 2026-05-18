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
- cycle 全体を 1 script にまとめる (judgment を script に閉じ込める; light chain 可は「main が同 cycle 内で連続判断」する話で、script 化とは別)
- judgment を tool に閉じ込めて conflict / 失敗時に user に手動 revert を押し付ける

## 鉄則 2: conflict resolution は main の手で

並列 sub dispatch 後の merge で `git apply --3way` が conflict を返したら:

1. tool は当該 batch の apply を中断 + 状況を report (rollback しない)
2. main が patch / 該当ファイルの diff を読む
3. main が Edit tool で resolve (典型: 両 sub が同 `lbl_xxx` extern を `[]` open array にしたい / 同 struct に offset 衝突しない field を追加したい、等)
4. main が次の batch 処理を continue (tool 再起動 or 残処理を手で)

**なぜ tool に rollback を入れないか**: conflict の semantic intent は dispatch 時点で main が把握済み (誰に何をやらせたか覚えている)。実際の conflict は「同意図の独立編集」が大半で、main が数行 Edit するだけで resolve できる。tool が atomicity を保証しようとすると main の判断余地を奪う。

参考実績: Round 3 (commit f9b22bb) で 7 sub の merge を main が 7 round 手動 Edit で完了。これが正しいモデル。

## 鉄則 3: merge は通知 hook (cycle 制約の対象外)

sub からの `<task-notification>` (status=completed) を受信したら、cycle / heavy action カウントを問わず **即 merge** を実行する。pending merge を後続 cycle に積まない。

| 種類 | trigger | 1 cycle あたり |
|---|---|---|
| **merge (hook)** | sub completion notification | 受信した数だけ即実行 (cycle counter 対象外) |
| dispatch / 編成 / 再編成 / cleanup | cycle (/loop fire) | active_subs < 6 上限まで chain |

理由:
- completed batch を「pending merge」として積むと active_subs slot が空いても dispatch hesitate しがち
- merge は notification 駆動が自然 (sub 完了 → 即 main checkout 取り込み)
- 同 recipe の merge を 1/cycle に絞ると loop 待ちが累積、user に空白を与える

旧ルール (「1 cycle 1 heavy action」「heavy + light 混在禁止」) は 2026-05-18 に撤回。`docs/orchestrator_role.md` Cycle 動作 / `prompts/cycle.md` も同方針。

### notification hook の実装

`<task-notification>` を受信したら (cycle 中 / wake 中問わず):

1. HANDOFF.md + `git -C <worktree> log -1 --format=full HEAD` を即 Read (worktree cleanup 前)
2. `python tools/merge_promote.py --batch <id> --no-build --no-state --no-cleanup` で patch apply
3. configure.py / splits.txt / symbols.txt を Edit (HANDOFF 指示通り)
4. `python configure.py && ninja build/GNLJ82/ok` で SHA-1 verify
5. commit + worktree+branch cleanup
6. state.json flip (fn → matched, batch → merged, active_subs から sub 削除)
7. 知見反映 (次節「知見反映: 各 merge で必須」参照)

複数 notification が同時/連続で来た場合は **順番に処理して構わない**。各 merge は ~30s-2min で context bloat 軽微。同 cycle に dispatch / 編成も chain 可能。

### merge hook 後の chain (必須)

merge hook の 7 ステップが完了したら、**turn を閉じる前に必ず以下をチェックする**:

```
全 pending notification 処理後:
  if drain.flag 無し and active_subs < 6:
    if pending batch あり or pending fn (batch_id 未割当) あり:
      → 同 turn 内で CASE 4 編成 → CASE 3 dispatch を chain
      → active_subs を 6 まで埋める
```

「merge hook → active_subs 減 → そのまま turn 終了」は **anti-pattern**。pending work があるのに ScheduleWakeup heartbeat (1500s) を待つ状態は cycle 設計上発生してはいけない。

**この rule は cycle の中ではなく hook 後の必須 cleanup として動く** (cycle 制約外、鉄則 3 の延長)。実装上は merge hook 7 ステップを「7+1 ステップ」と見て最後の +1 で chain check する形。

### parallel dispatch の原則 (anti-pattern 防止)

dispatch cycle は active_subs を**上限 (6) まで埋める**ことを目標にする。`while len(active_subs) < 6 and 編成可能 fn あり: 編成 + dispatch を繰り返す`。

「1 batch 編成 → 1 dispatch → return」を 1 cycle とするのは **明確な anti-pattern**。次 cycle まで parallel slot を遊ばせて user に約 20 min の空白を与える結果になる (実例: 2026-05-18 セッション初回 cap=3 時代、`batch_init_80003140_bba` の dispatch cycle で 1 sub のみ起動して 2 slot 余らせた。cap=6 ならさらに損失が大きい)。

### conflict 発生時の例外

merge が conflict / SHA-1 fail を返した場合は hook 即実行から離脱し、cycle 内で resolve する (鉄則 2 「conflict resolution は main の手で」参照)。conflict 解決中は他の hook を pause (state.json の active_subs 整合性のため)。

## sub-agent dispatch の実装パターン

新規 batch を dispatch するとき、main が決める要素:

1. **batch 構成**: どの fn を 1 batch にまとめるか
   - dtk reversed-extab group 内なら group 全 pending member を bundle (= 1 indivisible TU 制約、`prompts/cycle.md` CASE 5 参照)
   - 同 group 内でも asm_fn 状態の fn を 1 つずつ別 sub に promote させる pattern (Round 3 / main wave で実証、本 skill の「同 TU 内多 sub 並列 promote」項参照)
   - **struct-driven seeding** (2026-05-18 採用、本 skill の「struct-driven TU grouping」項参照): Ghidra MCP で seed fn の引数型 (struct 名) を確認、同 struct を触る pending fn を cluster として 1 batch にまとめる。ライブな struct 情報は Ghidra DataTypeManager (`run_script_inline`) が SoT、repo 内 header は遅延コピー
2. **worktree 用意**: `python tools/setup_worktree.py <batch_id>` で `.worktrees/<batch_id>/` を作成
3. **prompt 構築**: sub に何をやらせるか
   - 担当 fn の addr / name / size / asm 行範囲
   - 必読 docs (`docs/sub_agent_role.md`, `~/.claude/skills/mkgp2-match/SKILL.md`)
   - 直近の参考 commit (典型例の git show)
   - 制約 (同 TU 他 fn は touch 不可、30 min / 3 試行、100% 不可なら asm_fn 退避)
   - HANDOFF.md JSON schema (status / src_path / build_verified)
   - **Ghidra decompile の callee 名は信頼しない**: prompt に `mcp__ghidra__decompile_function` の生出力をそのまま貼ると、Ghidra annotation / placeholder name (例: `MemoryManager_TimedFree`) が実 binary の symbols.txt 名 (例: `dtor_8003AFB8`) と乖離していて sub に誤情報を渡すケース多発 (2026-05-18, dtor pair 3 batch で発覚)。sub に「callee 名は `build/GNLJ82/asm/auto_*_text.s` の bl 先で必ず確認せよ」と明示するか、main 側で predict callee 名を symbols.txt と cross-check してから prompt に書く
4. **Agent tool 起動**: `Agent(subagent_type='general-purpose', run_in_background=True, prompt=...)`
5. **state.active_subs に記録**: 通知受信用 (TaskList には現れない、main の self-bookkeeping)

## struct-driven TU grouping (2026-05-18 採用)

**前提**: Phase 1/2 で 34 struct + 元から存在の 18 struct + 未着手の ~40 struct が Ghidra で高確度に解析済み (KartItem 0x380 / 50+ fn、PathManager_Partial 0x4DC、ItemDisplay 0x14、HeapStats 12B 等)。repo 内 header より Ghidra DataTypeManager の方がライブで分厚い情報を持つ。

**main 側 (cycle CASE 4 編成時)**:

1. pending fn から seed を pick (size 小 / 命名済み優先)
2. `mcp__ghidra__get_function_variables` + `mcp__ghidra__decompile_function` で seed の引数型 (struct 名 / size) を確認
3. 同 struct を引数 / local 型として touch する pending fn を抽出:
   - `mcp__ghidra__list_functions_enhanced` の signature filter
   - もしくは 既知 cluster (KartItem 全 method 等) を Phase 1/2 doc から逆引き
4. cluster を 1 batch にまとめる (size <= 5 関数 / 0x200 byte 上限は維持、超えるなら struct 内のサブ機能で分割)
5. tu_hint を `<struct名>.c` 推測 (`game/ItemDisplay.c`, `game/KartItem.c` 等。Phase 1/2 doc に既存 TU 名があればそれを優先)

**sub 側 (dispatch prompt)**:

- struct 名と Ghidra fetch 手順を渡す:
  ```
  最初に mcp__ghidra__connect_instance(project="bmp_output") → open_program(/mkgp2_main.dol)
  mcp__ghidra__run_script_inline で DataTypeManager から <StructName> を dump:
    from ghidra.program.model.data import StructureDataType
    cm = currentProgram.getDataTypeManager()
    s = cm.findDataType("/<StructName>")  # or category path
    for c in s.getDefinedComponents():
        println(f"{c.getOffset():#x} {c.getDataType().getName()} {c.getFieldName()}")
  ```
- header の置き場所と forward decl 方針を指示 (`include/game/<StructName>.h`、不要な依存は forward decl で済ます)
- 既存 repo 内 header (例: `include/dolphin/types.h`) に重複する基本型 (u8/u32/f32) は再定義しない

**header の repo 配置**:

- sub が新規 emit したらそのまま `include/game/...` に置く (commit 対象)
- 同 struct を複数 sub が並列に作るリスクは main 側で排他 (1 struct は 1 batch にまとめる、複数 batch に分けないのが原則)
- struct alignment / padding の精度: 1 fn が 100% 不到達なら struct layout を疑う (CW alignment は 4B 既定、`#pragma scheduling` 等 lib 別 flag 影響あり) — HANDOFF で残差 dump 報告 → 知見化

**Phase 1/2 doc との関係**:

- Phase 1 audit が「元から存在」と記録した 18 struct (CarObject / KartDriver_Partial / KartMovement / KartParamBlock / RaceScene 等) は **Ghidra にもある = 流用可**。Phase 1/2 で扱わなかった ~40 struct (ItemDescriptor / HeapStats / PathManager_Partial / PhysicsState 等) も Ghidra fetch で取り出せる前提
- 但し `_Partial` suffix が付くものは「Phase X で確認した範囲だけ」を意味するので、後続作業で field が追加される可能性 (= header を継ぎ足す前提で書く)

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

1. **judgment を tool に閉じ込める**: 「cycle script を作って scaffold + dispatch + merge を 1 つに」と考える → dispatch judgment を script 化することで main の責務を放棄する。**正解**: script ではなく main が cycle ごとに `prompts/cycle.md` の手順を判断 + tool 呼び出しで progress。light chain (CASE 5 → CASE 4 等) は main が同 cycle 内で連続判断する形なので script 化とは別軸
2. **conflict 自動 rollback を tool に入れる**: stash-based snapshot / `--resume` mode 等を merge tool に追加したくなる → main の resolve 余地を奪う、user に「手動 revert してね」と押し付ける構図になる。**正解**: tool は abort + 詳細 dump、main が Edit で resolve
3. **compact summary だけ信じて docs 読み直さない**: summary に「タスク #N pending」とあっても、根拠 (なぜそのタスクを作ったか) が落ちている可能性。**正解**: 重要な判断分岐 (新 tool 設計 / cycle script 作成 / 大きな refactor) の前に必ず `docs/orchestrator_ops.md` と `docs/orchestrator_role.md` を Read で確認
4. **大規模 extab group (>10 fn) を 1 batch で dispatch しようとする**: dtk reversed-extab group 制約で 1 関数だけ抜くと split-error、しかし >10 fn 一括は context 圧迫で sub が破綻。**正解**: HANDOFF_TO_USER.md に escalate + 一旦保留 (大規模 group の incremental NonMatching scaffold は将来課題、`docs/large_extab_group_strategy.md` 参照)

## 関連 skill / docs

- `~/.claude/skills/mkgp2-match/SKILL.md` — 1 fn を 100% matching に持っていく workflow (sub-agent と main 共通 reference、特に 10.5 節 extab asm_fn 退避 / cache+search idiom)
- `docs/per_fn_matching_strategy.md` — asm_fn 退避戦略、bundle 内 partial matching、asm_fn → matched promote 手順
- `docs/large_extab_group_strategy.md` — dtk reversed-extab group の bundle 戦略
- `.claude/commands/mkgp2-orch-{start,drain,kill,status}.md` — orchestrator 制御の slash command
