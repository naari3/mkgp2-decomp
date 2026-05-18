# Orchestrator cycle prompt

`/loop` dynamic mode で main agent が 1 cycle ごとに実行する手順。

このファイルは prompt として直接 `/loop` に渡す内容。`/mkgp2-orch-start` から発火する。

---

あなたは mkgp2-decomp 並列 decomp orchestrator の main agent。これから 1 cycle 動作する。

## 初動: 責務と原則の確認 (新規セッション / compact 直後は必ず)

memory / compact summary に頼らず、以下を実ファイルから Read で確認 (drift していたら原則を見失う):

- `docs/orchestrator_role.md` — main agent の責務、CASE 詳細、Merge ルール、Lock 戦略
- `docs/orchestrator_ops.md` — 運用全体像、起動 / drain / kill、`plan_batches.py` 禁止理由
- `docs/sub_agent_role.md` — sub の制約、HANDOFF.md JSON spec、status field 要件マトリクス
- `.claude/skills/mkgp2-orch/SKILL.md` — judgment vs tool 分担鉄則、失敗パターン集 (skill auto-load 済みなら skip 可)

最重要原則 (本 prompt と上記 docs / skill で繰り返し言及):
- **judgment は main の責務、tool は mechanical part のみ**: batch 編成 / dispatch / conflict resolution は main が判断、tool は extract / apply / state.json flip / cleanup の機械作業のみ
- **merge は通知 hook (cycle 制約の対象外、2026-05-18 旧ルール撤回)**:
  - sub の `<task-notification>` (status=completed) を受信したら、cycle / heavy action カウントを問わず **即 merge** を実行
  - 同時/連続 notification は順番に処理して構わない (各 merge ~30s-2min、context bloat 軽微)
  - cycle (= dispatch / 編成 / 失敗 batch 再編成 / cleanup) は merge と独立に進行、active_subs < 3 上限まで chain
  - 詳細は `.claude/skills/mkgp2-orch/SKILL.md` 鉄則 3
- **conflict 解決は main の手で**: merge tool が conflict 検出したら abort、main が Edit で resolve (rollback 自動化は tool に入れない)。conflict 中は他の hook を pause

## 1 cycle 動作

merge は cycle 制約外の通知 hook (上記原則 / `.claude/skills/mkgp2-orch/SKILL.md` 鉄則 3 参照)。cycle は dispatch / 編成 / 失敗 batch 再編成 を担当し、active_subs < 3 上限まで連続実行 (chain) してよい。

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
CASE 2 (旧 CASE 3): 'failed' な batch あり (再編成)
CASE 3 (旧 CASE 4): active_subs < 3 かつ 'pending' な batch あり (dispatch)
CASE 4 (旧 CASE 5): pending batch 無く pending function あり (main が新規 batch 編成)
CASE 5 (旧 CASE 6): 該当なし (idle)
```

旧 CASE 2 (merge) は cycle から削除。**merge は通知 hook で随時実行** (cycle と独立)。
'completed' な batch が存在するのは notification hook の処理途中だけで、cycle 開始時に
残っていれば即 hook 実行 (= cleanup 残務扱い)。'cancelled' な batch は CASE 3/4 の前に
cleanup する (worktree 削除のみ、heavy ではない)。

CASE 4 (编成) → CASE 3 (dispatch) は **同 cycle 内 chain 可** (state.json 編集 +
Agent invocation のみで context 圧迫は浅い)。CASE 2 (失敗 batch 再编成) → CASE 3
(dispatch) も chain 可。CASE 3 自体も active_subs < 3 の上限まで連続 dispatch して構わない。

**parallel 化の原則**: cycle では **active_subs を上限まで埋める** ことを目標にする:
1. active_subs を確認
2. **`while len(active_subs) < 3 and (pending batch あり or pending fn あり)`**:
   - pending batch あれば CASE 3 dispatch
   - pending batch 無ければ CASE 4 編成 → 直後に CASE 3 dispatch (chain)
3. 上限到達 or 編成可能な fn 枯渇で return

「1 batch 編成して 1 dispatch して終了」は **明確な anti-pattern** (parallelism を
諦めて user に約 20 min の空白を与える結果になる)。

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
    # まだ sub が走っている → 通知待ち。新規 dispatch (CASE 3/4) しない
    # merge hook は通常通り動く (drain でも completed batch は即 merge する)
    print(f"drain mode: waiting for {active} sub(s)")
    # cancelled cleanup だけ pass 通して return
```

## merge hook (cycle 制約外)

**sub の `<task-notification>` を受信したら、cycle 状況に関わらず即実行**。

各 merge は次の 7 ステップ:
1. `git -C <worktree> log -1 --format=full HEAD` + `Read worktree/HANDOFF.md` で **sub の commit msg / notes / docs_notes / blocked_reason を全部読む** (worktree cleanup 前のみ可)
2. `python tools/merge_promote.py --batch <id> --no-build --no-state --no-cleanup` で patch apply
3. HANDOFF 指示通り configure.py / splits.txt / symbols.txt を Edit (機械的)
4. conflict 出たら main で Edit resolve (skill 「conflict resolution 標準手順」)
5. `python configure.py && ninja build/GNLJ82/ok` で SHA-1 verify
6. commit + worktree+branch cleanup
7. state.json flip (fn → matched, batch → merged, active_subs から sub 削除) + log
8. **知見を即追記** (skill 「知見反映」表に従って `~/.claude/skills/mkgp2-match/SKILL.md` / `docs/per_fn_matching_strategy.md` / `docs/large_extab_group_strategy.md` / 本 cycle.md / 本 mkgp2-orch skill のいずれかへ)

複数 notification を受信したら順番に処理 (1 件ずつ build verify する。`--no-build` で apply して最後に集約 build する変則は build fail 時の責任所在が曖昧になるので避ける)。

`status='cancelled'` な batch (TaskStop 由来) は cycle 内 cleanup で worktree を削除して terminal:

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

## CASE 2: failed batch の再編成

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

## CASE 3: dispatch

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
    return   # pending batch 無し → CASE 4 が次 cycle で動く
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

## CASE 4: 新規 batch 編成 (main の判断責務)

`pending` batch が枯渇していて、かつ `pending` function がまだ残っているとき。
main が **(a) extab group bundle 制約**、**(b) Ghidra MCP の xref / callees / namespace** を考慮して、関連関数を 1 batch にまとめる。

**最重要**: pending 関数の ~64% は dtk reversed-extab group 内にいる (4877/7614)。そういう関数を singleton dispatch すると `Conflicting splits within reversed extab group` でほぼ確実に失敗する (iter0 / iter1 で実証済み)。よって seed の `extab_group` を最初に確認して bundle を組む。

```python
# 1. pending function から先頭候補を pick (size 小、section 等で優先)
#    extab_group_size が極端に大きい (>10 fn) ものは保留 (現状 dispatch 不能)
pending_fns = [
    (addr, fn) for addr, fn in state['functions'].items()
    if fn['status'] == 'pending' and fn.get('batch_id') is None
    and (fn.get('extab_group_size') or 1) <= 10  # 10 fn 超は別レーン
]
pending_fns.sort(
    key=lambda kv: (kv[1].get('size') or 0xFFFFFFFF, int(kv[0], 16))
)
if not pending_fns:
    # 全部が large extab group か枯渇 — CASE 5 (idle) へ fall through
    # large group (>10 fn) は HANDOFF_TO_USER.md で user に escalate (一度だけ)
    pass
else:
    seed_addr, seed_fn = pending_fns[0]
    seed_group = seed_fn.get('extab_group')   # auto_*_text 名 or None

    # 2. extab group bundle (最優先)
    if seed_group:
        # 同 group の全 pending function を bundle
        extab_map = json.load(open('.orchestrator/extab_groups.json'))
        group_info = extab_map['groups'][seed_group]
        # group_info['function_addresses'] は dtk が確定済みの bundle メンバー
        batch_members = [
            a for a in group_info['function_addresses']
            if state['functions'].get(a, {}).get('status') == 'pending'
        ]
        # 既に matched な member が混在しているケース (一部 commit 済みの group)
        # では dtk が再 split を許す保証なし。warn but proceed.
        already_matched = [
            a for a in group_info['function_addresses']
            if state['functions'].get(a, {}).get('status') == 'matched'
        ]
        if already_matched:
            log_event({
                'event': 'warn', 'batch_seed': seed_addr,
                'msg': f'extab group {seed_group} has {len(already_matched)} already-matched members; bundle may conflict',
            })
        planning_note = {
            'seed': seed_addr,
            'extab_group': seed_group,
            'related_by': ['dtk_reversed_extab_group'],
            'group_total': len(group_info['function_addresses']),
            'group_pending': len(batch_members),
        }
    else:
        # 3. Singleton seed: Ghidra MCP で callees / namespace 取って近傍 bundle
        decomp = mcp__ghidra__decompile_function(program='main.dol', address=seed_addr)
        callees = extract_callees_from_decomp(decomp)
        namespace = mcp__ghidra__get_function_by_address(
            program='main.dol', function_address=seed_addr
        ).get('namespace')

        batch_members = [seed_addr]
        for addr, fn in pending_fns[1:]:
            if len(batch_members) >= 5: break
            # 同 extab_group なら必ず bundle、そうでなければ既存判定
            if fn.get('extab_group') == seed_group:
                batch_members.append(addr)
            elif is_related(addr, fn, seed_addr, seed_fn, callees, namespace):
                batch_members.append(addr)
        planning_note = {
            'seed': seed_addr,
            'extab_group': None,
            'namespace': namespace,
            'related_by': [...],
        }

    # 4. tu_hint 推定 (任意)
    tu_hint = guess_tu_hint(batch_members, seed_fn)

    # 5. batch を state に追加
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
        'planning_notes': planning_note,
    }
    for addr in batch_members:
        state['functions'][addr]['batch_id'] = batch_id
    log_event({'event': 'plan', 'batch_id': batch_id, 'members': len(batch_members)})
    atomic_write_state()
    # chain: そのまま CASE 3 へ fall through (active_subs < 3 なら即 dispatch)
```

### 大規模 extab group (>10 fn) の扱い

現状 mkgp2 には 269 個の multi-fn extab group があり、うち 100+ 個は 10 fn 超 (最大 937 fn)。これらは 1 batch decomp が現実的でない。

cycle CASE 4 で size > 10 を見つけたら:
- pending function はそのままにする (status 変えない)
- 1 度だけ HANDOFF_TO_USER.md に「extab group X (size N) は単独 dispatch 不可、戦略未定」を append
- 将来の対応: incremental NonMatching scaffold 戦略、または extab group 内の small subset を NonMatching として cap → 進めてから 100% match に昇格

### 既存 matched function を含む extab group の扱い

GetVBlankFlag / Archive_GetCurrent のように既に matched された singleton が extab group メンバーだった場合 (= dtk が再 split を許した稀ケース)、その group は半分 commit 済みの状態になる。新規 bundle が dtk のもとで通るかは未検証 — warn ログを出すが dispatch は試行する。失敗したら CASE 2 (failed batch 再編成) で対応。

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

## CASE 5: no action

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

## sub-agent prompt template (CASE 3 で使う)

```markdown
あなたは mkgp2-decomp 並列 decomp の sub-agent (worker)。
担当 batch を 1 つ完了したら return する使い捨てワーカー。

最初に以下を必ず読み込め:
1. docs/sub_agent_role.md  (制約と HANDOFF.md 仕様)
2. ~/.claude/skills/mkgp2-match/SKILL.md  (matching workflow)
3. Ghidra MCP を触るなら **先に** `Skill(skill="mkgp2-ghidra")` をロード
   (bmp_output project 固有の接続手順 / domain path / image_base はこちら、
    汎用の Ghidra MCP 接続作法とツール選択は transitively 参照される
    `ghidra-mcp` skill 経由)

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

- **merge は通知 hook で即実行** (cycle 制約外、2026-05-18 旧ルール撤回)。cycle (= 编成 / dispatch / 再编成) は active_subs < 3 上限まで chain 可
- 完了通知 (`<task-notification>`) は受信した順に即 merge。cycle 中でも notification wake 中でも同じ
- prompt cache は 5 分 TTL。ScheduleWakeup delay は active_subs > 0 なら 1200s fallback (通知で先に wake する)、completely idle なら 1500s heartbeat。pending work + active_subs==0 は chain で吸収されるので発生しない想定
- main agent の context が圧迫されたら、tool 出力をファイル経由で参照する (`Bash` で head/tail）
