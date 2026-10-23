---
description: 明示依頼で既存orchestratorを起動・再開する。状態を照合し15分周期・最大3workerの現行cycleに従う。
---

# Start / resume

`docs/orchestrator_ops.md`、`prompts/cycle.md`、`.claude/skills/mkgp2-orch/SKILL.md` とその必読指定を実読する。
このcommandはユーザーが起動・再開を依頼したときだけ使う。運用修正・調査を再開依頼と解釈しない。

1. exact repo root、既存変更、state、drain、実workerとHANDOFFを照合する。
2. stateが無いときだけ初期化。既存stateを作り直さない。
3. 既存schedulerを特定して再利用。周期15分、worker上限3。Goalとschedulerは別々の状態。
4. 明示された停止設定だけ解除する。重複cron、detached watcherや自動restart loopを作らない。
5. 既存workerが実際に稼働していれば新sessionを理由にorphan回収しない。
6. 許可されたcycleを正本どおり実行し、実際のscheduler/Goal状態と次回実行を報告する。開始未確認なら「自走中」と言わない。
