# Orchestrator cycle prompt

`/loop` dynamic mode で main agent が 1 cycle ごとに実行する手順。

このファイルは prompt として直接 `/loop` に渡す内容。`/mkgp2-orch-start` から発火する。

---

あなたは mkgp2-decomp 並列 decomp orchestrator の main agent。これから 1 cycle 動作する。

**1 cycle = 1 action 原則**: 以下の CASE のうち高優先度なものを 1 つだけ実行して return する。複数走らせない。

## Step 0. SoT sync (毎回必ず)

```python
# 1. configure.py を parse → Object(Matching|NonMatching, "...") から各関数の status を re-derive
# 2. config/GNLJ82/symbols.txt を読み name / scope を更新
# 3. config/GNLJ82/splits.txt を読み tu_hint を range lookup で更新
# 4. build/GNLJ82/report.json があれば fuzzy_match_percent を更新
# 5. atomic write で state.json 更新
```

実装は (まだ tools/orch_sync.py が無ければ) `tools/init_orchestrator.py` の各 load 関数を import して走らせる:

```bash
python -c "
import sys; sys.path.insert(0, 'tools')
from init_orchestrator import load_symbols, load_splits, load_configure_objects, load_report_fuzzy, derive_status, is_placeholder_name, find_tu, atomic_write_json
# ... (省略: state.json を読み、functions を SoT で上書き、atomic_write_json で書き戻す)
"
```

SoT sync で `Object(Matching, ...)` declared 関数が自動 matched に昇格する。手動編集の drift をここで解消する。

## Step 1. 通知の取り込み

直前の system-reminder に `<task-notification>` があれば parse:
- `<task-id>` → state.active_subs から該当 entry を引く
- `<status>` (`completed` | `killed` | `failed`) → batch.status と active_subs を更新

```python
# Pseudocode
for notification in pending_notifications():
    sub_key = find_sub_by_agent_id(notification.task_id)
    if not sub_key: continue
    batch_id = state['active_subs'][sub_key]['batch_id']
    state['active_subs'][sub_key]['last_notification_status'] = notification.status
    if notification.status == 'completed':
        state['batches'][batch_id]['status'] = 'completed'  # awaiting merge
    elif notification.status == 'killed':
        state['batches'][batch_id]['status'] = 'cancelled'
    elif notification.status == 'failed':
        state['batches'][batch_id]['status'] = 'failed'
    del state['active_subs'][sub_key]
atomic_write_state()
```

## Step 2. CASE 判定

```
CASE 1 (最優先): drain.flag が立っている
CASE 2: 'completed' or 'cancelled' な batch あり (merge / cleanup 処理)
CASE 3: 'failed' な batch あり (再編成)
CASE 4: active_subs < 3 かつ 'pending' な batch あり (dispatch)
CASE 5: pending batch 無く pending function あり (main が新規 batch 編成)
CASE 6: 該当なし (idle)
```

CASE 4 と CASE 5 を分けているのは「1 cycle 1 action 原則」のため。
batch 編成と dispatch を同 cycle で連続実行すると、context 圧迫 + 失敗時
の rollback 範囲が広くなる。編成だけを 1 cycle、dispatch を次 cycle に分ける。

## CASE 1: drain mode

`.orchestrator/drain.flag` が存在:

```python
active = len(state['active_subs'])
if active == 0:
    # 全 sub 完了済み → /loop 終了
    log_event({'event': 'session_end', 'reason': 'drain_complete'})
    # /cron list で該当 cron id を見つけて CronDelete
    return
else:
    # まだ sub が走っている → 通知待ち、CASE 2 を継続実行
    print(f"drain mode: waiting for {active} sub(s)")
    # → CASE 2 へ fall through
```

## CASE 2: merge / cleanup 処理

`status='completed'` な batch を 1 つ pick して merge:

```python
for batch_id, batch in state['batches'].items():
    if batch['status'] != 'completed': continue
    if batch.get('handoff_path') is None:
        # worktree から HANDOFF.md を探す
        handoff = Path(batch['worktree_path']) / 'HANDOFF.md'
        if not handoff.exists():
            # incomplete - escalate
            batch['status'] = 'failed'
            batch['blocked_reason'] = 'HANDOFF.md missing after completion'
            continue
        batch['handoff_path'] = str(handoff)
    # parse HANDOFF.md yaml block
    handoff_data = parse_handoff(batch['handoff_path'])
    # apply changes (詳細は docs/orchestrator_role.md "Merge ルール")
    apply_handoff(handoff_data, batch)
    # build verify
    if not build_verify():
        batch['status'] = 'failed'
        continue
    # commit + worktree remove
    git_commit(batch)
    git_worktree_remove(batch['worktree_path'])
    batch['status'] = 'merged'
    batch['completed_at'] = now_iso()
    log_event({'event': 'merge', 'batch_id': batch_id, 'result': 'merged'})
    atomic_write_state()
    return   # 1 cycle 1 action
```

`status='cancelled'` な batch (TaskStop 由来) は worktree を削除して terminal:

```python
for batch_id, batch in state['batches'].items():
    if batch['status'] != 'cancelled': continue
    if batch.get('worktree_path') and Path(batch['worktree_path']).exists():
        # 15 秒 wait (kill propagation) は cycle 跨ぎで暗黙 OK
        try:
            git_worktree_remove(batch['worktree_path'], force=True)
        except Exception:
            # busy → 次 cycle で retry
            return
    log_event({'event': 'cleanup', 'batch_id': batch_id})
    atomic_write_state()
    return
```

## CASE 3: failed batch の再編成

```python
for batch_id, batch in state['batches'].items():
    if batch['status'] != 'failed': continue
    reason = batch.get('blocked_reason', '')
    # 判定 (詳細は docs/orchestrator_role.md):
    if 'sha1_fail' in reason or 'build_fail' in reason:
        # NonMatching で隔離するか blocked にエスカレーション
        if can_isolate_as_nonmatching(batch):
            new_batch = make_nonmatching_batch(batch)
            state['batches'][new_batch['id']] = new_batch
        else:
            batch['status'] = 'blocked'
            escalate_to_user(batch)
    elif 'split_too_large' in reason:
        # batch を分割して 2 新 batch に
        split_batch(batch)
    else:
        # 単純 retry はしない (前回判断)。 blocked に格上げ
        batch['status'] = 'blocked'
        escalate_to_user(batch)
    log_event({'event': 'replan', 'batch_id': batch_id})
    atomic_write_state()
    return
```

## CASE 4: dispatch

```python
if Path('.orchestrator/drain.flag').exists():
    return   # drain 中は新規 dispatch しない
active = len(state['active_subs'])
if active >= 3:
    return   # 上限
# 次の batch を pick (size 小、依存解決済み優先)
candidates = sorted(
    [b for b in state['batches'].values() if b['status'] == 'pending'],
    key=lambda b: state['functions'][b['function_addresses'][0]].get('size') or 0xFFFFFFFF
)
if not candidates:
    return   # pending batch 無し → CASE 5 が次 cycle で動く
batch = candidates[0]
batch_id = next(k for k, v in state['batches'].items() if v is batch)

# Ghidra MCP で pre-fetch (限界に注意: limit 必須)
fn_info = []
for addr in batch['function_addresses']:
    fn = state['functions'][addr]
    decomp = mcp__ghidra__decompile_function(program='main.dol', address=addr)
    fn_info.append({
        'addr': addr,
        'name': fn['name'],
        'size': fn['size'],
        'decompile': decomp,
    })

# worktree 作成 + orig/ populate (.gitignore で worktree から漏れる
# orig/GNLJ82/sys/main.dol を main checkout から copy する。これを
# やらないと sub の最初の `ninja build/GNLJ82/main.dol` が
# "orig/GNLJ82/sys/main.dol not found" で失敗する)
worktree_path = Path(f'.worktrees/{batch_id}').resolve()
branch = f'orch/{batch_id}'
run(f'python tools/setup_worktree.py {batch_id}')

# sub-agent 起動 (prompt に function info を inline)
prompt = render_sub_prompt(batch_id, worktree_path, branch, fn_info)
agent_id = Agent(
    description=f'decomp {batch_id}',
    subagent_type='general-purpose',
    run_in_background=True,
    prompt=prompt,
)

# state 更新
sub_key = f'sub_{agent_id[:8]}'
state['active_subs'][sub_key] = {
    'agent_id': agent_id,
    'batch_id': batch_id,
    'worktree_path': str(worktree_path),
    'started_at': now_iso(),
    'last_notification_at': None,
    'last_notification_status': None,
}
batch['status'] = 'dispatched'
batch['assigned_sub'] = sub_key
batch['worktree_path'] = str(worktree_path)
batch['branch'] = branch
batch['dispatched_at'] = now_iso()
log_event({'event': 'dispatch', 'batch_id': batch_id, 'sub': sub_key})
atomic_write_state()
return
```

## CASE 5: 新規 batch 編成 (main の判断責務)

`pending` batch が枯渇していて、かつ `pending` function がまだ残っているとき。
main が **Ghidra MCP の xref / callees / namespace** を引いて、関連関数を 1 batch にまとめる。

```python
# 1. pending function から先頭候補を pick (size 小、section 等で優先)
pending_fns = sorted(
    [(addr, fn) for addr, fn in state['functions'].items()
     if fn['status'] == 'pending' and fn.get('batch_id') is None],
    key=lambda kv: (kv[1].get('size') or 0xFFFFFFFF, int(kv[0], 16))
)
if not pending_fns:
    # CASE 6 へ fall through
    pass
else:
    seed_addr, seed_fn = pending_fns[0]

    # 2. Ghidra MCP で seed の関連関数を引く
    decomp = mcp__ghidra__decompile_function(program='main.dol', address=seed_addr)
    # callees: bl で呼んでる関数のアドレス
    callees = extract_callees_from_decomp(decomp)  # 'FUN_XXX' / 名前付き両方
    # xref: 隣接アドレス + 同じ namespace の関数
    namespace = mcp__ghidra__get_function_by_address(
        program='main.dol', function_address=seed_addr
    ).get('namespace')

    # 3. batch grouping 判定 (main の核心ロジック)
    batch_members = [seed_addr]
    for addr, fn in pending_fns[1:]:
        if len(batch_members) >= 5: break
        # 以下のいずれかを満たせば同 batch に入れる候補:
        # (a) seed の callee で、かつ pending (= 依存解決のため一緒に作る)
        # (b) Ghidra 上で同じ namespace (= 同じ概念的グループ)
        # (c) seed と隣接 address かつ同 section かつ size 小 (= 同 TU の可能性高い)
        if is_related(addr, fn, seed_addr, seed_fn, callees, namespace):
            batch_members.append(addr)

    # 4. tu_hint 推定 (任意 — sub が最終決定するので main は hint のみ)
    tu_hint = guess_tu_hint(batch_members, namespace, seed_fn)
    # 例: namespace="HSD::Fobj" + section=".text" → "sysdolphin/baselib/fobj_xxx.c"
    # 推定できなければ None でよい

    # 5. batch を state に追加 (status=pending、まだ dispatch しない)
    batch_id = f"batch_{short_section(seed_fn['section'])}_{int(seed_addr, 16):08x}"
    state['batches'][batch_id] = {
        'status': 'pending',
        'tu_hint': tu_hint,
        'function_addresses': batch_members,
        'assigned_sub': None,
        'worktree_path': None,
        'branch': None,
        'created_at': now_iso(),
        'dispatched_at': None,
        'completed_at': None,
        'retry_count': 0,
        'blocked_reason': None,
        'handoff_path': None,
        'planning_notes': {
            'seed': seed_addr,
            'namespace': namespace,
            'related_by': [...],  # どのルールで bundle したかの記録
        },
    }
    for addr in batch_members:
        state['functions'][addr]['batch_id'] = batch_id
    log_event({'event': 'plan', 'batch_id': batch_id, 'members': len(batch_members)})
    atomic_write_state()
    return   # 次 cycle で CASE 4 が dispatch
```

### grouping 判定 (`is_related`) の推奨ルール

優先度高い順:

1. **seed の callee で、かつ pending**: seed が `bl X` で呼んでる X が pending なら、X も一緒に作らないと link 時に未定義参照になる (X が `excluded` の placeholder なら不要、placeholder symbol への参照で link は通る)
2. **同じ Ghidra namespace**: `HSD::Fobj`, `Kart::Movement` 等。HSD やゲーム本体は namespace が TU 境界とほぼ一致
3. **隣接 address + 同 section + 両方 size 小 (<0x80 bytes)**: callback / helper の典型パターン
4. **seed の callers にも該当**: A が B を呼んで B が A を呼び返すなら同 TU の可能性高い (cyclic dep 防止)

判定結果は `planning_notes.related_by` に記録して、後の merge 失敗時の rollback / 再編成判断に使う。

### batch サイズと安全策

- **最大 5 関数**: TU 境界の暗黙仮定が外れたとき、broken batch を捨てるコストを抑えるため
- **合計 0x200 byte 上限**: 1 sub の 30 分予算と context window の両方を考慮
- 上限に達したら、残りの関連 function は次 cycle で別 batch にする (seed を変える)

### main が Ghidra 情報を引きすぎないコツ

- 1 cycle で `mcp__ghidra__decompile_function` を呼ぶのは **seed 関数のみ** (callee は名前だけ確認、必要なら次 cycle で展開)
- `mcp__ghidra__list_functions` 全件は禁止 (197KB、context 圧迫)
- `mcp__ghidra__get_function_variables` 等の重い call は dispatch 時の prompt 構築フェーズに回す

## CASE 6: no action

```python
print("no action this cycle")
# ScheduleWakeup で fallback wake を予約 (1200-1800s)
ScheduleWakeup(
    delaySeconds=1500,
    reason='idle: no pending batches and no notifications',
    prompt='<このファイルの内容>',  # 次 cycle で同じ prompt を再発火
)
# completion check
if all_terminal(state):
    escalate_to_user('全 batch 完了。orchestrator 終了します。')
    # CronDelete /loop
    return
```

## sub-agent prompt template (CASE 4 で使う)

```markdown
あなたは mkgp2-decomp 並列 decomp の sub-agent (worker)。
担当 batch を 1 つ完了したら return する使い捨てワーカー。

最初に以下を必ず読み込め:
1. docs/sub_agent_role.md  (制約と HANDOFF.md 仕様)
2. ~/.claude/skills/mkgp2-match/SKILL.md  (matching workflow)

## 担当 batch

batch_id:   {{batch_id}}
worktree:   {{worktree_path}}
branch:     {{branch}}

担当関数:
{{for fn in fn_info}}
- addr: {{fn.addr}}
  name: {{fn.name}}
  size: {{fn.size}} bytes
  section: ...
  
  ### Ghidra decompile (pre-fetched)
  ```c
  {{fn.decompile}}
  ```
{{endfor}}

## 制約 (docs/sub_agent_role.md 必読)

- 作業範囲は {{worktree_path}} 内のみ
- configure.py / splits.txt / symbols.txt を直接編集しない (HANDOFF.md で提案)
- 1 関数 30 分上限、3 試行上限
- 完了基準: build.sha1 OK かつ objdiff 100%
- 完了したら HANDOFF.md (atomic write 必須) を書いて "batch_<id>: done, see HANDOFF.md" を return
```

## エラー処理

cycle 内で例外が起きた場合:

```python
try:
    cycle()
except Exception as e:
    log_event({'event': 'error', 'cycle_phase': '<phase>', 'message': str(e)})
    # state.json を破壊していないか確認
    # ScheduleWakeup で次回 retry
```

state.json への書き込みは必ず `atomic_write_json` を経由する。途中で die しても破損しない。

## 完了判定

cycle 末尾で以下を確認:

```python
all_fns = state['functions'].values()
all_batches = state['batches'].values()
remaining = sum(1 for f in all_fns if f['status'] in ('pending', 'in_progress', 'interrupted'))
in_flight = len(state['active_subs'])
non_terminal_batches = sum(1 for b in all_batches if b['status'] in ('pending', 'dispatched', 'completed', 'failed'))

if remaining == 0 and in_flight == 0 and non_terminal_batches == 0:
    escalate_to_user('全 batch 完了。/loop を終了します。')
    cron_delete()
```

## 留意点

- 1 cycle 1 action を厳守。複数 dispatch / 複数 merge を 1 cycle で詰め込まない
- 完了通知 (`<task-notification>`) は cycle 開始時点で必ず process
- prompt cache は 5 分 TTL。ScheduleWakeup delay は 1200s 以上推奨
- main agent の context が圧迫されたら、tool 出力をファイル経由で参照する (`Bash` で head/tail）
