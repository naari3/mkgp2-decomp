---
name: mkgp2-orch
description: mkgp2-decomp の並列 decomp cycle、完了 HANDOFF 統合、unit-first 編成と独立検証・公開確認を行う main agent 用。一般的な repo 調査では cycle を勝手に開始しない。
---

# mkgp2 orchestration

## Read routing

毎 cycle の必読正本は次の **3ファイルだけ**。全て実ファイルから完全に読む。

1. `prompts/cycle.md` — 実行順と受入・公開条件
2. この `SKILL.md` — routing と権限境界
3. `docs/orchestrator_role.md` — 主体・state・証拠の責務

同 cycle 内の既読内容を重複ロードしない。compact 後は上記を実読し直す。全文出力が切れたら未読範囲だけ読む。
過去知見は削除せず **該当時にだけ**読む:

- 起動/停止/recovery: `docs/orchestrator_ops.md`
- 新規編成: `docs/unit_first_strategy.md`、担当関数の過去 HANDOFF/notes
- dispatch/受入: `docs/sub_agent_role.md`、`docs/orchestrator_state_schema.md`
- worker の matching: `.claude/skills/mkgp2-match/SKILL.md` とそこで指定された資料
- extab/ASM混在・promote: `docs/per_fn_matching_strategy.md` の該当節。全履歴を毎回読む必要はない。
- 大 extab group: `docs/large_extab_group_strategy.md`
- C++ retrofit: `docs/notes/cpp-ctor-retrofit-mangled-bridge.md`、必要なら `docs/large_tu_cpp_conversion.md`

## Invariants

main が unit/claim/extab/TU/過去試行を見て選定・編成・dispatch・conflict解決する。
tool は patch/apply、atomic state、read-only report、検証補助のみ。
自動 batch planner、cycle 全体の判断 script、conflict rollback は使わない。

worker 上限3、周期15分。PAUSED は正常なユーザー設定。手動実行と自動再開を混同しない。
drain なら新規 dispatch なし。完了 hook は許可された実行中に直列処理し、個別 main build/commit/push/archive/担当cleanupを行う。
詳しい順序は cycle 正本だけに置く。二重の疑似コードや別の cap を追加しない。

`merge_promote.py` の --no-build は patch 段階を分けるためで、独立 build を省く許可ではない。
matched-only helper で NM/mixed HANDOFF を黙って捨てない。
local commit、push成功、CI成功、public SHA一致は別の証拠。公開確認には `tools/verify_publication.py` を使う。

native source と実 source link を確かめ、ASM/NM/source-only部分一致を genuine C と混同しない。
3試行/30分を守り、同じ register permutation を名前だけ変えて続けない。
知見は `docs/notes/` の担当 family に記録し、巨大な毎回必読資料には積み増さない。
