# Orchestrator cycle — current procedure

毎回このファイル、`.claude/skills/mkgp2-orch/SKILL.md`、その必読指定を実ファイルから完全に読む。同じ cycle 内で既読の不変ファイルを重複して読まない。出力が切れたら未読範囲のみ読む。

## Scope and authority

- 主体は main。unit 選択、claim、batch 編成、dispatch、conflict 解決は main が判断する。`plan_batches.py` と cycle 全体の自動判断スクリプトは禁止。
- worker は最大 **3**。周期は **15分**。実際の scheduler と Goal の状態は別々に確認する。
- PAUSED はユーザーの正常な停止設定。調査・運用修正・手動1 cycle は自動再開の許可ではない。再開・周期変更は明示依頼時だけ。drain 中は新規編成・dispatch なし。
- Git 前に exact repo root を解決・照合。既存変更、他 checkout、他 worker を保全する。

## Step 0 — every cycle

`python tools/orch_sync.py` で configure/symbols/splits/report から atomic sync。結果と時刻を記録する。宣言上の Matching / state の matched は、独立検証済みの genuine C と同義ではない。

## Immediate completion hook — cycle count outside

完了通知、または state に残った terminal HANDOFF を検出したら待ち行列に記録し、順番に直ちに処理する。通常 cycle では後回しにしない。ユーザーが別の作業だけを指定した場合は無断で merge に範囲を広げず、未処理を報告する。

1. worker の実在・終了と owned foreground handles の terminal exit を確認。通知受信時刻を記録し HANDOFF 全文・commit message・source を読む。
2. HANDOFF を raw のまま archive。source patch と必要な SoT、docs_notes を scoped apply。NonMatching や mixed result も捨てない。`merge_promote.py` は matched-only helper であり汎用 acceptor ではない。
3. conflict は main が両意図を読み解決。rollback/reset/stash で消さない。解決中の他 merge/state write は直列化する。
4. **1 merge ごと**に main で configure、`ninja all_source progress build/GNLJ82/report.json build/GNLJ82/ok` を foreground 実行し、同じ handle を実 exit まで追う。複数 patch を最後に一括 build しない。
5. direct objdiff の text/data/EH/index と対象全関数、実 main.elf の source/fallback input、full DOL SHA-1 を確認。genuine gain は native source + 実 source link + 必要 payload の一致だけ。ASM、NM fallback、source-only 部分一致は別記する。
6. source/SoT/知見を scoped commit。accept 時刻・commit・独立検証結果を atomic state と log に記録。batch merged はローカル統合であって配信成功ではない。
7. **各 merge ごとに** `git push origin main`。失敗は HANDOFF_TO_USER に記録し、再現情報と未push SHAを残す。
8. raw archive と push を確認後、担当の exact WT/branch だけ cleanup。未処理・foreign WT は削除しない。
9. 配信確認は `python tools/verify_publication.py --sha <pushed-sha>`。Build と deploy-pages 成功、公開 HTML の full SHA 一致を確認し、run URL・公開 SHA・確認時刻を記録。成功前は「公開済み」と言わない。
   - CI 待ちで次の完了 merge や枠補充を止めない。各 push の run を追跡し、cycle末尾に最新の配信を確認する。
   - 新しい push に置き換わった公開は、古い SHA の確認成功と偽らず superseded として後継 SHA/run を記録。
   - 失敗は原因を調べ HANDOFF_TO_USER に追記。改修を含まない依頼では修正候補を提示するだけ。継続中の CI は pending と明示し、許可された次 cycle で追う。

## CASE selection and refill

- CASE 1: drain — merge hook のみ。worker がなくなれば drain 完了を記録。既存の停止設定は勝手に変更しない。
- CASE 2: failed — 原因・既往試行を読み、main が分割/NM隔離/blockedを判断。単純 retry しない。
- CASE 3: pending batch + 空き枠 — dispatch。
- CASE 4: pending batch がなく pending function あり — main が unit-first 編成して **同 cycle 内で CASE 3**。
- CASE 5: 安全に編成できない — idle 理由を報告。

通常の実行許可があり drain がなければ、CASE 4→3 を利用可能な **3枠まで** chain。merge 後も同じ確認をする。1 dispatch だけで止めない。scheduler PAUSED を無視して将来の実行を約束しない。

## Main selection and worker contract

- `docs/unit_first_strategy.md` を読み、進行中 unit を優先。claim は open issue/assignee を確認。
- address 連続性、foreign range、既存 TU、全 extab member と **実 group text containment** を確認。`extab_group=null` だけでは孤立と判定しない。大 group は専用方針を読むまで dispatch しない。
- 各 batch に選択理由、全 address、TU/flags、claim、既往試行、参考 source/callee ABI を残す。同 TU を複数 worker が編集するなら担当境界を main が固定する。
- worker に `docs/sub_agent_role.md`、matching skill と必要技術資料の実読、worktree 内限定、3構造的試行/30分、foreground build、actual handle exit、atomic HANDOFF、scoped commit を明示。
- native C/C++ + automatic EH が既定。ASM/manual EH/payload patch に逃げて genuine progress と扱わない。既存 ASM は保全。型/構造を変えない blind permutation や exhausted budget のリセットは禁止。
- 2回連続で識別的新事実なし、同 family の低収率が続く場合、次 wave 前に main が仮説・予測・棄却条件と別方針を記録。待ち時間に診断範囲を無制限に広げない。

## End audit and reporting

drain、scheduler/Goal（実確認した場合のみ）、active_subs と実 worker、全 batch status、terminal HANDOFF 残務、CI/public SHA、main dirty/ahead/behind を確認。
dispatch/通知/merge/build/push/publication 時刻を log し、不明な時間は推測しない。空き枠待ちと CI 待ちを区別する。

完了は pending=0/in_progress=0/active=0/全batch terminal/未mergeなし/独立SHA一致/push/public確認。NM/blocked/ASM残務があれば project の真C完了ではない。
短報順: Step0、即merge、CASE、dispatch/active、検証/push/公開、blocked/HANDOFF、次の許可された状態。
