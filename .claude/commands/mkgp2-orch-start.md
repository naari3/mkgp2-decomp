---
description: orchestrator を起動 / 再開する。state.json の有無で初期化と recovery を自動判定し、CronCreate で 3min 間隔の cycle 発火を仕込む
---

mkgp2-decomp の並列 decomp orchestrator (main agent) を起動する。あなたは main agent 役。

## 役割の確認

これから docs を読んで自分の責務を把握する。以下を必ず読み込む:

1. `docs/orchestrator_role.md` — main の責務、cycle 手順、merge ルール、active_subs 自前管理
2. `docs/orchestrator_state_schema.md` — state.json schema、status 遷移、SoT sync
3. `docs/sub_agent_role.md` — sub の制約と HANDOFF.md format (主に parse のため)
4. `prompts/cycle.md` — 各 cycle で実行する手順

## 起動 / 再開判定

以下の手順で起動 mode を決定する:

```python
# 1. state.json が無い → 初回起動
if not Path('.orchestrator/state.json').exists():
    run('python tools/init_orchestrator.py')
    # batches は空のまま開始。main agent が cycle CASE 5 で動的に編成する。
    # plan_batches.py は debug 用で本番では使わない。
    return start_loop()

# 2. state.json あり + session_id 一致 + drain.flag あり → drain からの resume
new_sid = generate_sid()
state = load_state()
old_sid = state['session_id']
drain_present = Path('.orchestrator/drain.flag').exists()

if drain_present:
    Path('.orchestrator/drain.flag').unlink()

# 3. session_id 異なる → 別 session からの recovery
if old_sid != new_sid:
    run(f'python tools/orch_recover.py --new-session {new_sid}')
    # state.session_id を新 sid に更新
    update_session_id(new_sid)

# 4. batches が空でも plan_batches.py は呼ばない。
#    main agent が cycle CASE 5 で Ghidra MCP を引いて編成する。

return start_loop()
```

## cycle 発火 (CronCreate)

main agent (= 私) が `CronCreate` で 3min 間隔の cycle prompt を仕掛ける。`/loop` は built-in slash command で tool から発火できないので使わない。session-only (`durable=false`) で session 終了時に自動消滅。

cron prompt:

```
prompts/cycle.md を Read で完全に読み込み、その「1 cycle 動作」プロトコルを最後まで実行せよ。
Step 0 (SoT sync) から Step 2 (CASE 判定)、必要なら merge hook と CASE 3/4 chain
(active_subs < 6 上限まで) を順に処理する。CASE 5 (idle) の ScheduleWakeup は
cron が代替するので不要 — 次 fire を待つ。drain.flag があれば CASE 1 のみ処理して
即 return、active_subs=0 なら CronDelete してこの cron を停止せよ。
```

cron schedule: `*/3 * * * *` (3 min 間隔)。10% deterministic jitter + REPL idle 判定で実 fire 間隔は 3-4 min。notification 駆動の即 wake は cron では効かないが、実運用では cron fire 間で task-notification は system-reminder で届いて即 merge される (検証済)。

## 注意

- 既に cron job が走っていないか確認 (`CronList`)。あれば二重起動になるので一旦 `CronDelete` してから start
- 初回起動の前に `tools/ghidra_symbol_dump.json` が最新か user に確認 (古いと named function を見落とす)

## 完了報告

起動成功なら:
- session_id を表示
- functions の status 分布 (matched / pending / excluded) を表示
- pending batches の件数を表示
- 「cycle 開始しました。drain は /mkgp2-orch-drain、強制停止は /mkgp2-orch-kill」を最後に
