# `.orchestrator/` state schema

並列 decomp orchestrator の永続化ファイル群の仕様。`tools/init_orchestrator.py` が初期生成、`tools/orch_recover.py` が修復、main agent (orchestrator) の cycle が随時更新する。

`.orchestrator/` は `.gitignore` 対象。ローカル状態であり commit しない。

## ファイル構成

```
.orchestrator/
├── state.json       # SoT-derived な作業状態。cycle 毎に再 sync
├── log.jsonl        # append-only イベントログ
├── locks.json       # 短命な mutex 状態 (現在 lock 中のリソース)
└── drain.flag       # 存在すれば graceful stop 中 (空ファイル)
```

### 役割

| ファイル | 寿命 | 書き手 | 用途 |
|---|---|---|---|
| `state.json` | 永続 | main のみ | 関数 / batch / active_subs の現在状態 |
| `log.jsonl` | 永続 | main のみ | dispatch / merge / kill 等のイベント履歴 |
| `locks.json` | 永続 | main のみ | configure.py / splits.txt / symbols.txt 編集中のロック |
| `drain.flag` | graceful stop の間のみ | main / slash command | 存在すれば新規 dispatch 停止 |

## state.json schema

### Top-level

```json
{
  "version": 1,
  "session_id": "sess_2026-05-17T18-30-00",
  "synced_from_sot_at": "2026-05-17T18:42:11Z",
  "ghidra_dump_path": "tools/ghidra_symbol_dump.json",
  "ghidra_dump_mtime": "2026-05-17T17:00:00Z",
  "functions": { ... },
  "batches": { ... },
  "active_subs": { ... }
}
```

- `version` — schema のメジャーバージョン。breaking change で繰り上げ
- `session_id` — main agent 起動時に発行 (`sess_<UTC ISO>`)。recovery で「前 session の残骸」を判別する
- `synced_from_sot_at` — 最後に SoT (configure.py / report.json / symbols.txt) と sync した時刻
- `ghidra_dump_*` — Ghidra dump JSON のパスと最終更新時刻。これが変わったら functions を再構築

### `functions`

key は 16 進アドレス文字列 (`"0x80003100"`)。

```json
"0x80003100": {
  "name": "__check_pad3",
  "section": ".init",
  "size": 64,
  "has_named_symbol": true,
  "ghidra_named": true,
  "tu_hint": "init/__check_pad3.c",
  "status": "matched",
  "batch_id": "batch_0001",
  "dependencies": ["0x80003200"],
  "callers": ["0x800050a0"],
  "fuzzy_match_percent": 100.0,
  "last_attempt_at": "2026-05-17T18:30:00Z",
  "notes": ""
}
```

- `name` — symbols.txt 上の current name (`fn_xxx` / `FUN_xxx` / `lbl_*` placeholder の場合あり)
- `has_named_symbol` — symbols.txt の name が placeholder でないか。**orchestrator 対象判定はこの field を使う**。name の由来 (Ghidra / mkgp2docs / externals.txt / 手動) を問わない
- `ghidra_named` — `tools/ghidra_symbol_dump.json` に当該アドレスがあるか。informational only (rename 同期の cross-check 用)
- `tu_hint` — 推定 TU パス。configure.py の `Object(...)` で既に declared なら確定値、未配置なら splits.txt range lookup の結果。auto blob 内なら null
- `status` — 後述の state machine 参照
- `batch_id` — 現在 assigned されている batch (なければ null)
- `dependencies` — この関数が `bl` で呼ぶ他関数のアドレス (= callee)。init では空、後で sync スクリプトが populate
- `callers` — この関数を呼ぶ関数のアドレス (xref)。同上
- `fuzzy_match_percent` — objdiff の最新 fuzzy match (% 単位、未測定なら null)

#### `functions.<addr>.status` state machine

```
pending → in_progress → matched
                     ↘  nonmatching (NonMatching として隔離 commit)
                     ↘  interrupted (sub kill / crash で中断)
                     ↘  blocked (3 回以上失敗 or 依存未解決)

excluded                  ← 並列 decomp の対象外 (ghidra_named=false 等)
skipped                   ← user が手動 skip
```

| status | 意味 |
|---|---|
| `pending` | 並列 decomp 対象、まだ batch 未 assign |
| `in_progress` | 現在 sub が作業中 |
| `matched` | `Object(Matching, ...)` で declared 済み |
| `nonmatching` | `Object(NonMatching, ...)` で隔離済み |
| `interrupted` | sub の kill / crash で中断、recovery 待ち |
| `blocked` | 失敗が積み重なって blocked。user 介入待ち |
| `excluded` | `has_named_symbol=false` (`fn_*` / `FUN_*` / `lbl_*` 等の placeholder) で対象外 |
| `skipped` | user が `tools/orch_skip.py` 等で除外 |

derive ルール (`tools/init_orchestrator.py` 参照):

1. `tu_hint` あり + `Object(NonMatching, ...)` → `nonmatching`
2. `tu_hint` あり + `Object(Matching, ...)` → `matched`
3. `has_named_symbol` が false → `excluded`
4. それ以外 → `pending`

`matched` / `nonmatching` は cycle 冒頭で **SoT (configure.py + report.json) から再 derive** する。手動編集禁止。

### `batches`

`batches` の追加は **main agent が cycle 内で動的に行う** (prompts/cycle.md CASE 5)。
Ghidra MCP で xref / callees / namespace を引いた上で関連関数を grouping する判断責務は
main の専有領域。`tools/plan_batches.py` は fallback / debug 用で、本番 cycle 中は呼ばない。

```json
"batch_0001": {
  "status": "completed",
  "tu_hint": "init/__check_pad3.c",
  "function_addresses": ["0x80003100"],
  "assigned_sub": null,
  "worktree_path": null,
  "branch": null,
  "created_at": "2026-05-17T18:00:00Z",
  "dispatched_at": "2026-05-17T18:10:00Z",
  "completed_at": "2026-05-17T18:30:00Z",
  "retry_count": 0,
  "blocked_reason": null,
  "handoff_path": null,
  "planning_notes": {
    "seed": "0x80003100",
    "namespace": "...",
    "related_by": ["callee_of_seed", "same_namespace", ...]
  }
}
```

- `planning_notes` — main が CASE 5 で grouping した根拠の記録。merge 失敗時の rollback / 再編成判断に使う

- `status` — `pending` / `dispatched` / `completed` / `failed` / `blocked` / `merged` / `cancelled`
- `function_addresses` — この batch でまとめて作業する関数群 (1 TU 仮定)
- `assigned_sub` — `active_subs` の key (なければ null)
- `worktree_path` — `.worktrees/<batch_id>/` を絶対パスで
- `branch` — `orch/<batch_id>` 形式
- `retry_count` — 再 dispatch 回数 (今回は retry なし設計だが、フィールドは予約)
- `blocked_reason` — blocked 時の理由文字列
- `handoff_path` — 完了時の `worktree_path/HANDOFF.md` 絶対パス

`status` 遷移:

```
pending → dispatched → completed → merged
                    ↘ failed → (再編成で別 batch を新規作成、この batch は terminal)
                    ↘ cancelled (TaskStop / user 介入)
                    ↘ blocked   (user 判断待ち)
```

### `active_subs`

main が知っている、現在 background 動作中の sub-agent 一覧。Agent tool の `TaskList` には出ないため自前管理が必須。

```json
"sub_a83e1915": {
  "agent_id": "a83e19155bc2404ee",
  "batch_id": "batch_0042",
  "worktree_path": "C:/Users/naari/src/github.com/naari3/mkgp2-decomp/.worktrees/batch_0042/",
  "started_at": "2026-05-17T18:30:00Z",
  "last_notification_at": null,
  "last_notification_status": null
}
```

- key は `sub_<agent_id 先頭 8 文字>`
- `agent_id` — Agent tool の return value から取った id (完全形)
- `last_notification_status` — 自動通知の status (`completed` / `killed` / `failed`)。null なら未着信 = 動作中とみなす
- 通知着信時に main が即 entry を削除し、batch.status を `completed` / `cancelled` に遷移

## SoT との sync

state.json は **SoT から derive される ephemeral cache** である。SoT は以下に分散して存在:

| SoT | 反映先 state field |
|---|---|
| `configure.py` の `Object(Matching, "X")` | `functions.<X の関数 addr>.status = matched` (要 report.json 確認) |
| `configure.py` の `Object(NonMatching, "X")` | `functions.<X の関数 addr>.status = nonmatching` |
| `build/GNLJ82/report.json` | `functions.<addr>.fuzzy_match_percent` |
| `config/GNLJ82/symbols.txt` | `functions.<addr>.name`, `tu_hint` |
| `config/GNLJ82/splits.txt` | `functions.<addr>.tu_hint` (range lookup) |
| `tools/ghidra_symbol_dump.json` | `functions.<addr>.ghidra_named` |
| Ghidra MCP (live) | `functions.<addr>.dependencies`, `callers` (cycle 中 sync) |

cycle の各 iteration で **冒頭** に sync する。orchestrator 固有のフィールド (`batch_id`, `last_attempt_at`, `notes`, `active_subs`, `batches`) のみ persist 由来。

`tools/orch_sync.py` (将来追加予定) が sync 専任。

## atomic write 規約

state.json / locks.json / log.jsonl は **`.tmp` 経由 rename** で atomic write する:

```python
import os, json, tempfile
def atomic_write_json(path, data):
    dir_ = os.path.dirname(path)
    fd, tmp = tempfile.mkstemp(prefix='.', suffix='.tmp', dir=dir_)
    with os.fdopen(fd, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
    os.replace(tmp, path)  # Windows でも atomic
```

理由: main が cycle 中に kill されても破損しない。

`log.jsonl` は append-only なので fsync 後 close で十分 (rename 不要)。

## session_id と recovery

main agent は起動時に `session_id` を発行し state.json に書き込む。

```
sess_<UTC ISO 8601, ファイル名安全>  例: sess_2026-05-17T18-30-00
```

recovery 時の判定:

| state.json.session_id | drain.flag | 含意 | recovery action |
|---|---|---|---|
| 現セッションと一致 | あり | 直前 drain 中で再開 | `drain.flag` 削除 → continue |
| 現セッションと一致 | なし | 同セッション内 resume | continue |
| 異なる | なし | 前 session が graceful 終了せず死亡 | `tools/orch_recover.py` で orphan recovery 実行 |
| 異なる | あり | 前 session が drain 中に kill | drain.flag 削除 + orphan recovery |

`orch_recover.py` の判定:

```
state.json.active_subs の各 entry について:
  worktree が存在しない              → batch.status=cancelled, function.status=pending
  worktree あり + HANDOFF.md あり    → batch.status=completed, main の取り込みキューへ
  worktree あり + HANDOFF.md なし    → batch.status=interrupted, HANDOFF_TO_USER.md にエスカレーション
```

active_subs はすべて clear (どの sub も生きていないと仮定)。

## locks.json

main が複数 sub の HANDOFF.md を順次取り込む際の lock。基本的に main は single-threaded なので空に近いが、将来の拡張用に schema を確保。

```json
{
  "locks": {
    "configure.py": {
      "holder": "main",
      "acquired_at": "2026-05-17T18:30:00Z",
      "purpose": "merge batch_0042"
    }
  }
}
```

## log.jsonl

1 行 1 JSON。`tools/orch_log.py` (将来追加) で集計可能に。

```jsonl
{"ts": "2026-05-17T18:00:00Z", "event": "session_start", "session_id": "sess_..."}
{"ts": "2026-05-17T18:10:00Z", "event": "dispatch", "batch_id": "batch_0001", "sub": "sub_a83e1915"}
{"ts": "2026-05-17T18:30:00Z", "event": "notify", "sub": "sub_a83e1915", "status": "completed"}
{"ts": "2026-05-17T18:30:05Z", "event": "merge", "batch_id": "batch_0001", "result": "matched"}
{"ts": "2026-05-17T18:35:00Z", "event": "kill", "sub": "sub_b12...", "reason": "drain"}
```

event 種別: `session_start`, `session_end`, `sync`, `dispatch`, `notify`, `merge`, `kill`, `recover`, `blocked`, `error`.

## 関連 docs

- `docs/orchestrator_role.md` — main agent の責務と cycle 手順
- `docs/sub_agent_role.md` — sub-agent の制約と HANDOFF.md 仕様
- `docs/orchestrator_ops.md` — user 向け運用手順 (start / drain / kill / status)
