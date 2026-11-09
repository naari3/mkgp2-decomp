# Orchestrator operations

実行正本は [cycle](../prompts/cycle.md)、責務は [role](orchestrator_role.md)、worker仕様は [sub_agent_role](sub_agent_role.md)。
現行worker上限3、周期15分。旧Claude CLIのsession-only CronCreateとCodexの保存済みheartbeatは同じものではない。実際の利用環境を確認し、schedulerを重複作成しない。

## Start / resume

明示的に依頼されたときだけ実行。exact repo rootと既存変更を確認し、既存state・実worker・管理下WT・HANDOFF・drainを照合する。
stateが無い場合のみ初期化する。新しいsession_idだけを理由に稼働workerを停止・orphan化しない。
既存schedulerを特定して再利用する。PAUSEDとGoal停止は別であり、必要な操作だけ行う。自動で再開・周期変更しない。

## Pause / drain / stop

- scheduler PAUSED: 将来のcycle発火の停止。ユーザーの正常な選択。
- Goal PAUSED: Goalの継続実行停止。scheduler状態と混同しない。
- drain.flag: 新規batch/dispatch停止、許可された完了mergeは継続。空になればdrain完了を報告。
- kill: 明示対象workerだけ停止。exact handle/PIDの実終了確認まで待ち、途中source/WTを保全してinterruptedをatomic記録。

停止や調査だけを依頼されたら新規dispatchや自動再開へ範囲を広げない。

## Status and recovery

read-onlyで state分布、実worker、管理下terminal HANDOFF、main dirty/ahead/behind、各pushのCI/public SHAを照合する。
完了HANDOFFは次の許可されたhookで統合。未処理を隠さず報告する。
`tools/verify_publication.py --sha <sha>` は公開検証のみ。失敗時にrepo/stateを変更しない。
batch選定はmain。ランキングは `plan_units.py`、claimは `claim_unit.py` を材料にするが、自動batch plannerは実行しない。

## Safety and maintenance

worktree cleanupはraw HANDOFF、独立受入、commit/push確認後に担当exact path/branchだけ実施する。
全WT削除、global prune、state全消去、cache/session削除を通常recoveryに使わない。foreign/未確認WTは残す。
dumpが古ければ記録し、当該判断が必要とする型情報の鮮度を確認する。利用可能なtarget/callee ASMで検証できる作業まで無条件に止めない。
過去の運用説明はGit履歴に残る。現行policyと歴史的な成功例/失敗例を二重の実行手順にしない。
