---
description: orchestrator の現状を read-only で表示する。state.json summary、active sub、最近の log
---

state.json の summary を表示する。**read-only**。state を一切変更しない。

## 実行内容

1. `.orchestrator/state.json` が存在するか確認
   - なければ「orchestrator 未起動。/mkgp2-orch-start で起動」と表示して終了

2. state.json を読み、以下を表示:

   ```
   === Orchestrator status ===
   session_id:           <sid>
   synced_from_sot_at:   <ts>
   ghidra_dump_mtime:    <ts>
   drain.flag:           <present|absent>
   
   === Functions ===
   total:        <N>
   matched:      <N>  (cumulative)
   pending:      <N>  (ready for batch)
   in_progress:  <N>  (currently being decomp'd)
   interrupted:  <N>  (recovery candidate)
   nonmatching:  <N>
   blocked:      <N>
   excluded:     <N>  (placeholder name)
   
   === Batches ===
   total:       <N>
   pending:     <N>
   dispatched:  <N>
   completed:   <N>  (awaiting merge)
   merged:      <N>
   failed:      <N>
   cancelled:   <N>
   interrupted: <N>
   blocked:     <N>
   
   === Active sub-agents ===
   <agent_id>  batch=<bid>  worktree=<path>  started=<ts>
   <agent_id>  batch=<bid>  worktree=<path>  started=<ts>
   (or "none")
   
   === Recent log (last 10 events) ===
   <ts> <event> <details>
   ...
   
   === HANDOFF_TO_USER ===
   (file present, last modified <ts>, <N> entries — review needed)
   or (none)
   ```

3. 実装は Python one-liner で十分:

   ```python
   import json
   from pathlib import Path
   from collections import Counter
   s = json.loads(Path('.orchestrator/state.json').read_text())
   print('session_id:', s['session_id'])
   print('functions by status:', Counter(f['status'] for f in s['functions'].values()))
   print('batches by status:', Counter(b['status'] for b in s['batches'].values()))
   print('active_subs:', len(s['active_subs']))
   for k, sub in s['active_subs'].items():
       print(f'  {k}: batch={sub["batch_id"]} since={sub["started_at"]}')
   ```

   そして `Get-Content -Tail 10 .orchestrator/log.jsonl` で recent log。

## 注意

- 一切の write 操作をしない
- main agent が動いてる最中でも安全に呼べる (state.json は atomic write されているので read は consistent)
- 表示後に「次の action はこのコマンド」のような提案は不要 (status 表示に専念)
