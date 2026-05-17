---
description: orchestrator を即停止する。全 active sub に TaskStop、worktree は保持、state を interrupted マーク
---

main orchestrator の immediate stop 指示。緊急時用。

## 実行内容

1. state.json を読み、`active_subs` の `agent_id` 一覧を抽出

2. 各 sub に対して `TaskStop`:
   ```
   TaskStop(task_id=<agent_id>)
   ```
   各 TaskStop は kill 通知 (`status: killed`) を即返すが、child process が実際に死ぬまで 10-15 秒の propagation 遅延あり

3. `/loop` の cron を `/cron list` で確認して `CronDelete`

4. state.json を更新:
   - 各 active_sub に紐付く batch.status を `interrupted` に
   - 各 in_progress function.status を `interrupted` に
   - active_subs を全 clear
   - atomic write (`tools/orch_recover.py` の `atomic_write_json` を呼ぶか、その実装を inline で再現)

5. `log.jsonl` に kill event を append:
   ```jsonl
   {"ts": "<ISO>", "event": "kill_all", "session_id": "<sid>", "killed_count": <N>}
   ```

6. HANDOFF_TO_USER.md に append:
   ```markdown
   ## Immediate kill <ISO>
   
   <N> sub(s) killed. Worktrees preserved at `.worktrees/<batch_id>/`:
     - batch_xxx → .worktrees/batch_xxx/
     - ...
   
   Inspect for partial work. Use /mkgp2-orch-start to recover.
   ```

7. **15 秒待ってから** worktree のディスク状態を確認すること (kill propagation のため)。worktree 自体は **削除しない** (user 確認待ち)

## 報告

user に以下を伝える:
- killed sub の件数
- worktree path の一覧 (.worktrees/<batch_id>/)
- HANDOFF_TO_USER.md を確認するよう促す
- 再開方法: `/mkgp2-orch-start` (recovery が走る)

## 注意

- active_subs が 0 件なら kill は noop、`/loop` CronDelete のみ実行
- 強制終了は user が「いますぐ止めたい」と明示した場合のみ。drain で十分なら drain を推奨
