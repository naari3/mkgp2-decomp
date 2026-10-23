---
description: state、実worker、未統合HANDOFF、Git/CI/公開状態をread-onlyで照合する。
---

`docs/orchestrator_ops.md` のstatus手順に従い、変更せずに表示する。
stateが無ければ未初期化と報告し、勝手に作らない。
state分布（matched/asm_fn/NM/blocked等）、activeと実workerの対応、管理下terminal HANDOFF残務を表示。
exact repo root照合後、main dirty/ahead/behindを確認する。
scheduler/Goal/drainは別状態。実確認できないものは不明、PAUSEDは正常な停止設定。
local merged、push、CI/deploy、公開SHAを混同しない。必要なら `tools/verify_publication.py --sha <full-sha>`。
genuine gainとaggregate reportを分ける。status依頼だけでmerge/dispatch/再開しない。
