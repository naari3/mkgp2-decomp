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

1. **作業範囲は割り当て worktree 内のみ**: `cd` して入った後、相対 path で操作。worktree の外のファイルを編集してはならない (main checkout / 他 worktree / `~/` 配下の repo はすべて禁止)
2. **担当 batch の関数以外の既存 `.c` ファイルを変更しない**: 隣接関数を「ついでに」matching しない (TU 境界の暗黙仮定が壊れる)。ただし **新規 `.c` の追加・削除は OK** — 担当関数のための新 TU、NonMatching scaffold (skill 7.5 節 制約C)、dtk auto blob 分割実験用の placeholder TU を含む。試行で作って捨てた scaffold は HANDOFF.md に記録しなくてよい (worktree 削除で消える)
3. **`configure.py` / `config/GNLJ82/splits.txt` / `config/GNLJ82/symbols.txt` は worktree 内では編集してよい**: build verify のために必須 (`/mkgp2-match` skill の手順 6-9 通り)。**ただし**、その変更は `orch/<batch_id>` branch 限定で main branch には反映しない — 同じ変更を HANDOFF.md の `configure_py` / `splits_txt` / `symbols_txt` セクションにも必ず記述すること。main はそれをもとに main branch に再適用する (sub の orch/* commit は worktree 削除と同時に捨てられる)
4. **`docs/` を直接編集しない**: 知見追加希望は HANDOFF.md の `docs_notes` セクションへ
5. **`.orchestrator/` を一切触らない**: state は main の専有領域
6. **`main` ブランチに直接 commit しない**: 自分の worktree の `orch/<batch_id>` ブランチにのみ commit する
7. **完了基準**: `build.sha1: OK` + objdiff で対象関数の `match_percent == 100.0`

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
    ],
    "rename": [
      {"old": "lbl_806D0F95", "new": "vblank_flag"}
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
- `results[]`: 必須。担当関数 1 件ずつ。`status` は `matched` / `asm_fn` / `nonmatching` / `skipped` / `failed` のいずれか (`asm_fn` の詳細: `docs/per_fn_matching_strategy.md`)
- `results[].src_path`: 推奨は **`src/` prefix なし** (configure.py / splits.txt 都合と整合、`init/debug_bba.c` 形式)。`src/init/debug_bba.c` 形式でも main の `merge_promote.py` は worktree 内に該当 file がある側を自動採用するので両方動く。混在を避けるため新規 batch では `src/` 無しを推奨
- `configure_py.add_objects[]`: option。空配列なら main は configure.py を編集しない。`object` は `Object(...)` の Python リテラル文字列そのまま。**`add_libs[]` は現状未対応** — 新規 lib block 追加が必要な場合は HANDOFF の自由記述部分か `user_attention` で明示し、main が手で configure.py を編集する (sub が worktree で編集した lib block は main が参照できる)
- `splits_txt.add_entries[]`: option
- `symbols_txt.set_scope[]` / `symbols_txt.set_attr[]`: option
- `symbols_txt.rename[]`: option。`{old, new}` の pair。placeholder symbol (`lbl_XXX`, `fn_XXX`, `data_XXX`) を意味的な名前に rename するときに使う。rename は set_scope/set_attr より先に適用されるので、同 batch 内で rename した new 名に対して scope を設定できる
- `docs_notes[]`: option。各 entry は `{"path": "docs/notes/foo.md", "content": "..."}` で append される
- `build_verified`: 必須。`sha1_ok: true` なら main が再 verify、false なら failed として merge skip
- `blocked_reason`: 失敗時のみ
- `user_attention`: user 判断要 (例: 「この関数は WIP の理解が必要、放置すべき」) なら

main の parse 実装は `tools/parse_handoff.py`。stdlib `json` のみ依存。

### status ごとの field 要件マトリクス

`results[].status` によって、関連 field の意味と要件が変わる:

| field | `matched` | `asm_fn` | `nonmatching` | `skipped` | `failed` |
|---|---|---|---|---|---|
| `results[].src_path` | 実 path 必須 | 実 path 必須 (matched 関数と同 TU) | 実 path 必須 | **null 推奨** (sub の試行 path は main で参照不可) | null |
| `results[].objdiff_percent` | **100.0 必須** | **100.0 必須** (asm body 貼付なので byte-identical) | 0-99.99 (達成値) | null | null |
| `configure_py.add_objects[]` | 必須 (Matching) | 不要 (bundle 全体で 1 件、matched と同 TU を共有) | 必須 (NonMatching) | **空配列** | 空配列 |
| `splits_txt.add_entries[]` | 必須 | 不要 (matched 関数と同 TU を共有) | 必須 | **空配列** | 空配列 |
| `symbols_txt.set_scope[]` / `set_attr[]` / `rename[]` | 必要なら | 必要なら | 必要なら | **空配列** (sub が worktree で編集した scope/rename は捨てる、main に反映しない) | 空配列 |
| `build_verified.sha1_ok` | true 必須 | true 必須 | true 必須 (NonMatching 隔離後の sha1) | **true** (元 sha1 維持の確認) | false 可 |
| `blocked_reason` | null | optional (なぜ asm に逃げたか 1 文書ければ将来 retry の手がかり) | null/optional | **必須** (なぜ skipped か 1-2 文) | **必須** |
| commit 動作 | ✓ `orch/<batch_id>` に 1 commit | ✓ matched と同 commit に含む | ✓ 1 commit (NonMatching として) | × no commit | × no commit |

`asm_fn` の詳細 (退避判定、asm body の書き方、bundle 内 partial matching の仕様) は `docs/per_fn_matching_strategy.md`。

特に重要 (iter 0 baseline で曖昧と判明した点):

- **skipped 時**: sub が試行中に touch した SoT 編集 (symbols.txt の scope 等) は **HANDOFF.md に反映しない**。main は HANDOFF.md だけ見て決めるので、`symbols_txt.set_scope` に書くと main 側で適用されて drift する。worktree の編集は捨てられる (worktree remove で消える) ことを前提に、skipped で main に持ち込みたいものは 0 件にする
- **`funcs_matched_delta`**: 「main が apply_handoff + ninja を回した後、PROGRESS line の `funcs_matched / total_functions` で増える数」。複数関数 batch なら matched 関数数 (例: 3 関数中 2 matched なら 2)
- **`results[].objdiff_percent` と `status` の整合**: `matched` で 100.0 未満は assertion 違反 (sub のミス)。`nonmatching` で 100.0 ちょうども assertion 違反 (なぜ NonMatching にしたか不明)

### 試行カウント (results[].notes など任意 field に書く場合)

「試行」 = **approach の質的変更回数**。同じ approach での compile 失敗 retry は試行に含めない。例:

- approach A (extern array open `[]`) で 1 回 compile して 80% → approach B (sized array `[2]`) に切り替えて 100% → 2 試行
- approach A で compile error → 同じ approach A の syntax fix で compile → match まで 100% → 1 試行

### 自由記述部分について

```json``` フェンスの外の markdown 本文は **parser が無視する**。人間が読む / 次の sub が読む / debug 用のメモを自由に書ける (構造的限界の発見、再 dispatch の risk 通知など)。

複数 ```json``` ブロックがある場合は **最初の 1 つ** だけ採用される (それ以外は無視)。

## 失敗時の振る舞い

3 試行 / 30 分で 100% に到達できなければ、以下のいずれかを選ぶ:

| 選択 | 条件 | HANDOFF.md `results[].status` |
|---|---|---|
| **asm function 退避** | bundle 内の他関数の matching 進捗を守りたい / extab group 制約で TU 分割不可 / 1 関数だけ複雑 | `asm_fn` + C TU 内に `asm void fn() { nofralloc ... blr }` で inline (`docs/per_fn_matching_strategy.md`) |
| **NonMatching 隔離** | 80% 以上の fuzzy match を達成、C ソースに価値あり、TU 全体を C で書く方針 | `nonmatching` + `Object(NonMatching, ...)` を提案 |
| **skipped** | Ghidra 情報不足 / 構造体未解明 / 外部依存未解決 | `skipped` + `blocked_reason` に理由 |
| **failed** | 上記いずれにも該当しない (例: 環境問題で build さえ通らない) | `failed` + `blocked_reason` に詳細 |

extab group bundle の中で 1 関数だけ天井難度な場合は **asm function 退避を最優先**。bundle 全体の matching 進捗を守れる。`/mkgp2-match` skill 10.5 節も参照。

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
