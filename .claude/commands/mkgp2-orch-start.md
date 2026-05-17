---
description: orchestrator を起動 / 再開する。state.json の有無で初期化と recovery を自動判定し、/loop dynamic mode を発火する
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

## /loop の発火

```
/loop /mkgp2-orch-cycle
```

dynamic mode (interval 指定なし) で `mkgp2-orch-cycle` skill (= prompts/cycle.md の内容) を発火する。

`mkgp2-orch-cycle` が登録されていない場合は、直接 prompts/cycle.md の内容を inline で `/loop` に渡す:

```
/loop
<prompts/cycle.md の中身全部>
```

## 注意

- 既に `/loop` が走っていないか確認 (`/cron list`)。あれば二重起動になるので一旦削除してから start
- tmux 内で実行することを user に確認 (誤って通常 session で /loop すると user が気付かない)
- 初回起動の前に `tools/ghidra_symbol_dump.json` が最新か user に確認 (古いと named function を見落とす)

## 完了報告

起動成功なら:
- session_id を表示
- functions の status 分布 (matched / pending / excluded) を表示
- pending batches の件数を表示
- 「cycle 開始しました。drain は /mkgp2-orch-drain、強制停止は /mkgp2-orch-kill」を最後に
