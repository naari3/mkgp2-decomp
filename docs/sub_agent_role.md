# Sub-agent (worker) role

並列 decomp 体制で main から `Agent` tool 経由で起動される sub-agent (worker) の制約、HANDOFF.md 仕様、作業手順をここで規定する。

関連:
- `docs/orchestrator_role.md` — main agent の責務
- `docs/orchestrator_state_schema.md` — state.json schema
- `~/.claude/skills/mkgp2-match/SKILL.md` — 1 関数を matching に持っていく workflow

## 性格と寿命

- sub-agent は **使い捨て**: 1 batch 完了で task return → terminated
- 次の batch は別の sub-agent が担当 (main が新規 dispatch)
- 親 (main) との通信は (a) 起動時の prompt、(b) HANDOFF.md (戻り)、(c) `SendMessage` (追加指示) のみ
- main session が die すると sub も連動 kill される (Spike 検証済み)

## 制約 (絶対遵守)

1. **作業範囲は割り当て worktree 内のみ**: `cd` して入った後、相対 path で操作。worktree の外のファイルを編集してはならない
2. **担当 batch の関数以外の `.c` ファイルを変更しない**: 隣接関数を「ついでに」matching しない (TU 境界の暗黙仮定が壊れる)
3. **`configure.py` を直接編集しない**: 追加希望は HANDOFF.md の `configure_py` セクションへ
4. **`config/GNLJ82/splits.txt` を直接編集しない**: 追加希望は HANDOFF.md の `splits_txt` セクションへ
5. **`config/GNLJ82/symbols.txt` を直接編集しない**: 追加希望は HANDOFF.md の `symbols_txt` セクションへ
6. **`docs/` を直接編集しない**: 知見追加希望は HANDOFF.md の `docs_notes` セクションへ
7. **`.orchestrator/` を一切触らない**: state は main の専有領域
8. **`main` ブランチに直接 commit しない**: 自分の worktree の `orch/<batch_id>` ブランチにのみ commit する
9. **完了基準**: `build.sha1: OK` + objdiff で対象関数の `match_percent == 100.0`

## 作業手順

### 1. オリエンテーション

worktree に入ったら、必ず以下の順で読む:

```
docs/orchestrator_state_schema.md   (自分が属する batch 構造の理解)
docs/sub_agent_role.md              (この文書)
~/.claude/skills/mkgp2-match/SKILL.md  (matching workflow)
```

main が渡した prompt に Ghidra decompile / disasm / xref / 構造体定義の **inline 情報** が含まれていれば、それを優先で参考にする。

### 2. 担当関数の状態確認

main が prompt に書いた batch_id / function_addresses / worktree_path / branch を確認。`state.json` は読まない (main の専有領域)。

### 3. Decomp 試行

`/mkgp2-match` skill の step 1-12 を順に実行。1 関数あたり:

- **最大 3 試行** (3 試行で 100% match に到達しなければ NonMatching として隔離)
- **最大 30 分** (時間切れの場合は NonMatching 隔離)

100% match に到達したら src/ に commit (自分の worktree 内、`orch/<batch_id>` ブランチ)。

### 4. Ghidra MCP の使用

sub から `mcp__ghidra__*` ツールは利用可能 (Spike #1 で検証済み)。ただし以下を遵守:

- **`mcp__ghidra__list_functions` は必ず `limit` を指定**: 全件 (~7600) で 197KB 返り context を圧迫
- **`mcp__ghidra__decompile_function` は対象 1 関数のみ**: 一括 batch decompile は使わない
- **rename / save_program は禁止**: Ghidra への write は main の `ghidra-rename` skill 領域

### 5. HANDOFF.md を書く

完了 (または失敗 / NonMatching 隔離) したら、worktree 直下に `HANDOFF.md` を書く。**atomic write** を厳守:

```python
# 推奨: tempfile + rename
import os, tempfile
fd, tmp = tempfile.mkstemp(prefix='.', suffix='.tmp', dir='.')
with os.fdopen(fd, 'w', encoding='utf-8') as f:
    f.write(handoff_content)
os.replace(tmp, 'HANDOFF.md')
```

main が読んでる最中に kill されると incomplete file 化するため。

### 6. return value

prompt の return は **1 行のみ**:

```
batch_<id>: done, see HANDOFF.md
```

詳細を return value に含めない (main の context を圧迫する)。

## HANDOFF.md format 仕様

main は HANDOFF.md の **```json ブロック** を parse する。stdlib `json` のみで処理。free-form の説明は markdown 本文に書いて構わない (parser は無視する)。

複数の `json` ブロックがあれば最初の 1 つだけ採用される。

```markdown
# HANDOFF batch_init_80003140

(free-form notes here are ignored by main's parser)

```json
{
  "batch_id": "batch_init_80003140",
  "sub_summary": "single function __set_debug_bba: matched",

  "results": [
    {
      "addr": "0x80003140",
      "name": "__set_debug_bba",
      "status": "matched",
      "src_path": "init/__set_debug_bba.c",
      "objdiff_percent": 100.0,
      "notes": ""
    }
  ],

  "configure_py": {
    "add_objects": [
      {"lib": "init", "object": "Object(Matching, \"init/__set_debug_bba.c\")"}
    ]
  },

  "splits_txt": {
    "add_entries": [
      {
        "path": "init/__set_debug_bba.c",
        "sections": [
          {"section": ".init", "start": "0x80003140", "end": "0x8000314C"}
        ]
      }
    ]
  },

  "symbols_txt": {
    "set_scope": [
      {"name": "__set_debug_bba", "scope": "global"}
    ]
  },

  "docs_notes": [],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 1
  },

  "blocked_reason": null,
  "user_attention": null
}
```
```

### Field 仕様

- `batch_id`: 必須。main が dispatch 時に渡した値そのまま
- `results[]`: 必須。担当関数 1 件ずつ。`status` は `matched` / `nonmatching` / `skipped` / `failed` のいずれか
- `configure_py.add_objects[]`: option。空配列なら main は configure.py を編集しない。`object` は `Object(...)` の Python リテラル文字列そのまま
- `splits_txt.add_entries[]`: option
- `symbols_txt.set_scope[]` / `symbols_txt.set_attr[]`: option
- `docs_notes[]`: option。各 entry は `{"path": "docs/notes/foo.md", "content": "..."}` で append される
- `build_verified`: 必須。`sha1_ok: true` なら main が再 verify、false なら failed として merge skip
- `blocked_reason`: 失敗時のみ
- `user_attention`: user 判断要 (例: 「この関数は WIP の理解が必要、放置すべき」) なら

main の parse 実装は `tools/parse_handoff.py`。stdlib `json` のみ依存。

## 失敗時の振る舞い

3 試行 / 30 分で 100% に到達できなければ、以下のいずれかを選ぶ:

| 選択 | 条件 | HANDOFF.md `results[].status` |
|---|---|---|
| **NonMatching 隔離** | 80% 以上の fuzzy match を達成、C ソースに価値あり | `nonmatching` + `Object(NonMatching, ...)` を提案 |
| **skipped** | Ghidra 情報不足 / 構造体未解明 / 外部依存未解決 | `skipped` + `blocked_reason` に理由 |
| **failed** | 上記いずれにも該当しない (例: 環境問題で build さえ通らない) | `failed` + `blocked_reason` に詳細 |

NonMatching 隔離は `/mkgp2-match` skill 7.5節 制約C の手順。

## SendMessage 経由の追加指示

main が `SendMessage` で追加指示を送ってきた場合 (例: 「configure.py への追加を撤回したい」「別の関数も batch に追加して」)、それに従って HANDOFF.md を更新してから return する。

ただし main は基本 fire-and-forget で sub を扱うので、SendMessage はレアケース (drain / kill 通知や、緊急の追加情報のみ)。

## 子プロセスの寿命

worktree 内で `ninja` / `python` 等を起動する場合、長時間ブロックする処理は避ける:

- `ninja build/GNLJ82/ok` は 1-2 分 OK
- objdiff の interactive UI は起動禁止
- watch / tail -f / interactive shell は禁止

TaskStop で kill されると child process も連動 kill されるが、**最大 10-15 秒の propagation 遅延** がある (Spike 検証済み)。HANDOFF.md 書き込み中に kill されると incomplete になるので atomic write 厳守。
