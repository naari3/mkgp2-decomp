---
description: orchestrator を graceful stop する。既存 sub の完了を待って cycle cron を停止する
---

main orchestrator agent に対する graceful drain 指示。

## 実行内容

1. `.orchestrator/drain.flag` を作成 (空ファイルで OK)
   ```python
   Path('.orchestrator/drain.flag').touch()
   ```

2. log.jsonl に drain 開始 event を append:
   ```jsonl
   {"ts": "<ISO>", "event": "drain_requested", "session_id": "<current>"}
   ```

3. state.json を読み、active_subs の件数を user に報告:
   - 0 件 → 「即 cycle cron 停止します」と伝えて `CronList` から該当 cron を `CronDelete`
   - 1 件以上 → 「<N> 件の sub の完了を待ちます。完了通知の都度 merge 処理 → 全件終わったら cycle cron 自動停止」

4. drain mode の挙動:
   - 以降の cycle は `prompts/cycle.md` の CASE 1 が拾い、新規 dispatch をしない
   - sub からの通知が来たら CASE 2 (merge 処理) のみ実行
   - active_subs=0 になった cycle で `CronDelete` (cycle cron 停止) + session_end ログ

## 注意

- drain.flag が既に存在する場合 → 「既に drain 中です」と user に伝える
- main agent が動いていない (state.session_id が古い session) 場合 → 「main は既に停止しています。/mkgp2-orch-start で再開」と案内

## キャンセル方法

drain を取り消すには `.orchestrator/drain.flag` を delete:

```python
Path('.orchestrator/drain.flag').unlink(missing_ok=True)
```

次の cycle から通常モードに戻る。`/mkgp2-orch-start` を再実行しても同じ効果 (slash command 内で drain.flag を unlink する)。
