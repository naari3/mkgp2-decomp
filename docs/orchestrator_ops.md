# Orchestrator 運用ガイド (user 向け)

並列 decomp orchestrator の起動 / 停止 / 再開 / 確認の操作手順。

関連:
- `docs/orchestrator_role.md` — main agent の責務
- `docs/sub_agent_role.md` — sub-agent の制約
- `docs/orchestrator_state_schema.md` — state.json schema

## 前提

- **Windows Terminal で 1 タブを open のまま** 維持して main agent を常駐させる (タブを閉じると `claude` プロセスが死に、`/loop` も止まる)
- main agent は `/loop` dynamic mode で自走する
- sub-agent は main から最大 6 並列で起動される
- `.orchestrator/` と `.worktrees/` は `.gitignore` 済み、commit されない

PC をスリープさせると Windows がプロセスを中断するので、長時間自動運用したいなら電源設定で「スリープしない」 or 「タブの間はスリープしない」を有効化しておく。Screen lock 単独ではプロセスは生き続ける。

## 初回起動

```powershell
# 1. Ghidra dump を最新化 (Ghidra MCP で named function 一覧を取り直す)
#    別 Claude Code セッションで /mkgp2-ghidra 経由で実行
#    → tools/ghidra_symbol_dump.json 更新

# 2. Windows Terminal で新タブを開き、リポジトリへ
cd C:\Users\naari\src\github.com\naari3\mkgp2-decomp

# 3. Claude Code を起動
claude

# 4. orchestrator を開始
/mkgp2-orch-start
```

このタブは作業終了まで閉じない。

`/mkgp2-orch-start` が以下を自動実行:

1. `.orchestrator/state.json` の有無を確認
2. なければ `python tools/init_orchestrator.py` で初期化 (functions セクションのみ生成、batches は空)
3. あれば `session_id` 比較で resume / recovery 判定
4. `python tools/orch_recover.py --new-session <new_sid>` で orphan recovery
5. `/loop` を dynamic mode で発火

その後 main agent は cycle を回し続ける。3 sub まで並列で dispatch する。

**batch 編成は main agent が cycle 内で動的に行う** (Ghidra MCP の xref / callees / namespace を引いて関連関数を grouping)。`tools/plan_batches.py` は **使わない** — 機械的に「1 関数 = 1 batch」を作るだけの fallback / debug ツールで、main の判断責務を奪うため本番では起動禁止。

## 停止パターン

### graceful drain (推奨デフォルト)

> 「もう新規 dispatch しないでほしい、走ってる sub は完了まで待ってほしい」

```
/mkgp2-orch-drain
```

挙動:
- `.orchestrator/drain.flag` を立てる
- 現在 active な sub が完了するまで cycle は merge 処理のみ実行
- 全 sub 完了 → `/loop` CronDelete → main agent も `/exit` で抜けて OK
- state.json は完全に整合した状態で残る

再開は `/mkgp2-orch-start` を再実行するだけ。

### immediate stop (緊急)

> 「いま走ってる sub も含めて全部止めたい」

```
/mkgp2-orch-kill
```

挙動:
- `state.active_subs` の各 agent_id に `TaskStop`
- `/loop` CronDelete
- 各 sub の worktree は **残す** (途中まで書いた C source を保護)
- state.json の `in_progress` batch は `interrupted` にマーク
- HANDOFF_TO_USER.md に interrupted 一覧を append

10-15 秒 kill propagation 遅延あり (sub の child process が完全に死ぬまで)。

再開時に `tools/orch_recover.py` が `.worktrees/<batch_id>/HANDOFF.md` の有無で処理を分岐する。

### タブ強制 close (最終手段)

> 「main agent ごと殺したい」

Windows Terminal のタブを ✕ で閉じる、または `Ctrl-C` で `claude` を抜けて `exit`。

副作用:
- main session が die → 全 sub も連動 kill (Agent tool の lifecycle が親 session に紐付くため)
- `/loop` の cron job は残る → 次回 wake 時に noop or 失敗 (新 session で `/cron list` 確認 → `CronDelete`)
- state.json は最後の cycle 終了時点でフリーズ

**再開**: Windows Terminal で新タブを開き `claude` → `/mkgp2-orch-start`。orphan recovery が走り、宙ぶらりんの batch を以下のいずれかに振り分ける:

- worktree が無い → `cancelled` → 関数は `pending` に戻る
- worktree あり + HANDOFF.md あり → `completed` → main の merge キューへ
- worktree あり + HANDOFF.md 無し → `interrupted` → HANDOFF_TO_USER.md にエスカレーション (手動確認待ち)

## 再開パターン

### 同セッションで resume (drain 後)

main agent が tmux 内でまだ生きている場合:

```
/mkgp2-orch-start
```

`drain.flag` が削除されて cycle 再開。

### 新セッションで resume (タブ close 後 等)

Windows Terminal で新タブを開く:

```powershell
cd C:\Users\naari\src\github.com\naari3\mkgp2-decomp
claude
```

そして:

```
/mkgp2-orch-start
```

- state.json の `session_id` と新 session が異なる → orphan recovery 走る
- 必要なら HANDOFF_TO_USER.md を確認して手動介入
- recovery 後 cycle 再開

### フルリセット (state を捨ててやり直す)

```powershell
# 1. drain or kill で必ず止める

# 2. worktree を全削除
git worktree list |
  Select-String '\.worktrees[\\/]' |
  ForEach-Object { ($_ -split '\s+')[0] } |
  ForEach-Object { git worktree remove --force $_ }

# 3. state を退避 (削除でもよい)
$ts = Get-Date -Format 'yyyyMMdd-HHmm'
Move-Item .orchestrator ".orchestrator.bak.$ts"

# 4. 必要なら ghidra dump 更新

# 5. 再起動 (新タブで claude → /mkgp2-orch-start)
```

## 個別介入

### 状態確認

```
/mkgp2-orch-status
```

state.json サマリと active sub 一覧 (read-only)。

直接 file を覗くなら (PowerShell):

```powershell
python -c @"
import json
s = json.load(open('.orchestrator/state.json'))
from collections import Counter
print('functions by status:', Counter(f['status'] for f in s['functions'].values()))
print('batches  by status:', Counter(b['status'] for b in s['batches'].values()))
print('active_subs:', len(s['active_subs']))
"@
```

ログ確認:

```powershell
Get-Content .orchestrator/log.jsonl -Tail 50 |
  ForEach-Object { $_ | ConvertFrom-Json | ConvertTo-Json -Depth 5 -Compress }
```

### 特定 sub の kill

`/mkgp2-orch-status` で `agent_id` を確認してから:

```
main に向けて: 「<agent_id> を kill して、batch を pending に戻して」
```

main が `TaskStop` + state 更新する。

### state.json を手で直す

drain してから直接編集:

```
/mkgp2-orch-drain      # 待つ
# 全 sub 完了後
vim .orchestrator/state.json
/mkgp2-orch-start      # 再開
```

main が動いてる最中の直接編集は **絶対禁止** (atomic write が衝突する)。

## HANDOFF_TO_USER.md の監視

`.orchestrator/HANDOFF_TO_USER.md` は user の介入が必要なときに main が append する。以下を定期的に確認 (PowerShell):

```powershell
# 直近 1 時間に書かれたか
$f = '.orchestrator/HANDOFF_TO_USER.md'
if ((Test-Path $f) -and ((Get-Item $f).LastWriteTime -gt (Get-Date).AddHours(-1))) {
  Write-Output "HANDOFF_TO_USER.md updated within last hour:"
  Get-Content $f
}
```

主な escalation 理由:
- batch が 3 回連続 fail で `blocked` に格上げ
- recovery で `interrupted` を検出
- build verify が再現性ある fail
- 全 batch 完了 (session 終了の signal)

確認後 user が対応 (手動 commit / blob 分割 / skip 指示 等) → main に「対応完了」を伝えて continue。

## 想定運用フロー (典型例)

```
09:00  Windows Terminal 新タブ → claude → /mkgp2-orch-start
09:00-12:00  自走、~10 batch 完了
12:00  user 昼休憩 (タブはそのまま、PC sleep にしないこと)
13:00  HANDOFF_TO_USER.md を確認 → 2 件介入要
13:10  介入完了、main に continue 指示
13:10-17:00  自走
17:00  /mkgp2-orch-drain
17:30  全 sub 完了、/loop 終了
       → タブを残したまま帰宅、または exit でタブ閉じる
翌朝   新タブで claude → /mkgp2-orch-start で再開
```

**長時間放置するときの注意**:
- Windows の電源設定で「ディスプレイ off は OK、スリープ never」にする
- Screen lock (Win+L) は OK (プロセスは生き続ける)
- リモートデスクトップ切断は注意: 一部の Windows 設定で session が suspend される

## トラブルシューティング

### sub が dispatch されない

- `.orchestrator/drain.flag` が立ってないか確認 → あれば delete (or `/mkgp2-orch-start` で自動削除)
- `state.batches` に `status=pending` の batch があるか確認 → なければ `python tools/plan_batches.py`
- `state.active_subs` が 6 未満か確認 → 上限に達してれば待つ

### worktree がディスクを圧迫

- `git worktree list` で件数確認
- 完了済み (`status=merged`) batch の worktree は cycle が自動削除するが、`interrupted` 残骸は手動削除
- `git worktree prune` で broken worktree を一括清掃

### main agent が応答しない

- `/loop` cron が動いてるか: `/cron list`
- 動いてなければ `/mkgp2-orch-start` で再発火
- main agent 自体が hung → Windows Terminal タブで `Ctrl-C` → `exit` → 新タブで `claude` → `/mkgp2-orch-start`

### state.json が壊れた

```powershell
# atomic write の途中ファイルが残ってないか確認
Get-ChildItem .orchestrator/.*.tmp -ErrorAction SilentlyContinue

# 最悪、フルリセットで再構築
Move-Item .orchestrator .orchestrator.broken
python tools/init_orchestrator.py
# 手作業で完了済み batch を補完
```
