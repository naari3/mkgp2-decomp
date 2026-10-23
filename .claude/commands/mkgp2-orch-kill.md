---
description: 明示された即停止依頼で担当workerを停止し、途中成果とWTを保全する。
---

`docs/orchestrator_ops.md` を読み、stateと実worker/所有handleを照合する。
ユーザーが指定したworkerのみ停止（全停止依頼なら当該orchestratorの全worker）。名前だけでprocessをkillしない。
対象schedulerを確認して停止し、実handleのterminal exitを確認する。sleepだけを終了証明にしない。
担当batch/functionsをinterruptedへatomic更新し、未確認workerのactive entryを消さない。
停止時刻・実終了・未確認handleとHANDOFF_TO_USERを記録。source/WT/branchは削除しない。
Goalやschedulerの再開は別の明示依頼があるまで行わない。
