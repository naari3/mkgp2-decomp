---
description: 明示依頼で新規dispatchを停止し、許可された既存workerの完了統合を行う。
---

`docs/orchestrator_ops.md` と `prompts/cycle.md` を読み、exact repo/state/実workerを照合する。
明示依頼でdrain.flagを作り、開始時刻をlogに記録する。新規編成・dispatchはしない。
既存workerの完了hookは個別の独立build/commit/push/公開確認で処理する（mergeはCASE2ではない）。
active=0かつ未merge残務なしになったらdrain完了を報告し、実際に使っている対象schedulerだけ停止する。
scheduler/Goalの既存PAUSEDを勝手に解除しない。新sessionを理由に停止を推測しない。
drain解除は明示依頼時だけ。WT一括削除やstate再初期化は行わない。
