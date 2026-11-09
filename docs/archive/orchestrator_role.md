# Orchestrator role — current

実行正本は [prompts/cycle.md](../prompts/cycle.md)。この文書は責務と証拠を定め、CASE手順を複製しない。

## Ownership

main 専有: state/log/locks、main SoT、batch判断、claim、dispatch、conflict解決、main受入commit/push/公開確認、担当cleanup、知見反映。
worker: 割当WTの担当sourceとbuild用SoTだけ。docs/.orchestrator/main/foreign WTは編集しない。
全ての state 更新は `orch_sync.atomic_write_json`。root照合、既存変更と foreign WT保護、foreground handle寿命を守る。
merge と state write は直列。locks.jsonを使う場合は既存holderを確認し、終了時に自分のlockだけ解放する。

## State is not delivery

`matched` の SoT derive は configure の宣言。genuine判定には対象payload、native source、実main.elf source input、独立foreground fullSHAを照合する。
raw objdiff の低値はrelocation表現差のこともあるため、無条件でstatusを書き換えない。
`asm_fn`/NM/blocked/skipped/in_progress の保護を維持。HANDOFFを見ず matchedへ一律flipしない。

batchの `merged` はローカル受入。配信は別途 commit SHA、push結果、CI run/conclusion、deploy結果、public SHA、確認時刻で示す。
失敗/未確認は pending/failed と明記し、mergedから勝手にpublic成功を推測しない。
raw HANDOFF と main の受入差分・根拠を担当WT削除前に保存する。push失敗時はWTを保持。

## Recovery and latency

実 worker一覧とactive_subsを照合。通知を取り逃しても、state管理下のWTのterminal HANDOFFを毎cycle確認する。
新sessionだからといって他の稼働workerをorphan扱いしない。既存session_idも根拠なく変更しない。
dispatch、通知受信、merge開始/終了、build終了、push、公開確認をUTCで記録し、人への時刻はJST。
単純な15分待ちをmergeの前提にしない。compile/CI待ちは短いstatus確認に分け、その間は安全な独立作業・枠補充を行う。

## Progress and escalation

genuine関数/bytes、ASM、NM成果、source-only一致、aggregate reportを別々に報告。
直近waveのgenuine gainと試行/時間を比較し、低収率familyは新しい構造的根拠なしに再試行しない。
push失敗、再現するbuild失敗、blocked、判断要、公開失敗は `.orchestrator/HANDOFF_TO_USER.md` に原因/証拠/残務を追記。
PAUSEDは障害ではなく、自動再開もしない。周期・Goal・drainは独立状態として扱う。
