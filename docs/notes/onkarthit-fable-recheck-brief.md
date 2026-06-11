# OnKartHit recheck brief (Fable セッション用、2026-06-11)

目的: `KartItem_OnKartHit` (0x8004A238, `src/game/auto_ONKARTHIT_block.c` の先頭 fn /
prefix index 0 = Phase 3 A-region gate) を 96.38% から byte-identical promote する。
これまで Opus セッションが 2 独立 run で「PINNED (source 不可)」と結論したが、その判定が
モデルの探索不足でないかを Fable で再検証する。**未試行の方向が 1 つ残っている** (下記)。

このセッションは frida を一切使わない (観測は別 batch で完了済み、以降は objdiff だけで完結する)。
frida / dynamic instrumentation / binary patch の話題に触れないこと。観測の結論は下記の数値を
信じてよい。shipped compiler (`build/compilers/GC/1.3.2/mwcceppc.exe`) は触らない。

## 確定している観測 (信じてよい数値、再現不要)

OnKartHit の callee-saved GPR partition の現状と target:

| web | 種別 | 現状 home | target home |
|---|---|---|---|
| self   | param | r26 | **r30** |
| victim | param | r27 | **r31** |
| bus    | local | r30 | r25 |
| rm     | local | r31 | r29 |
| bool/reuse webs x5 | local | r25/r28/r29 | r26..r28 |

allocator は web を **web-birth key 降順**で着色し、各 web に r31 から降順に callee reg を割当てる。
self/victim (param) は **callee 最低の web-birth key (32/33)** かつ **最大の interference degree
(関数全体に live、隣接数 ~135/137)** を持つ。最大次数ノードは simplify で最後まで残る → 最後に
着色 → 最低位 callee reg (r26/r27) に落ちる。**target は param を最上位 (r30/r31) に置く**。
つまり param が locals を outrank する必要がある = param の次数 (live range) を下げない限り動かない。

96.38% の残差はこの 1 つの partition 決定 + その下流症状 (callee-saved-bool の li-coalescing、
vcall r6-vs-r12、fp f3/f5 の swap) が全て。partition が直れば下流は self-correct する見込み。

## 既に negative の lever (再実行不要)

3 つとも web-birth **順序**を攻めただけで、全部 param home を動かせなかった:
1. **局所変数の宣言順入れ替え / def-order**: locals 同士は動く (rm key 94->65, bus r30->r28) が
   param home は r26/r27 のまま。
2. **param → 局所コピー** (`KartItemHit *self = selfP;` を最初の文に置き param を rename): **byte-identical**。
   コピーが param-merge で元の param web に coalesce され、param web identity (最低 key, 最大次数) が
   保たれる。最も直接的な「param を最初に born させる」signal が無効。
3. **局所の遅延生成** (`bus = ...` を `if(ok)` ブロック内に移動): 95.43% (bus reload が増える)、
   param は r26/r27 のまま。

## 未試行の方向 (= このタスク)

上記 3 つは全て web-birth **順序 (key)** を攻めた。だが pin の正体は key ではなく param の
**interference degree (live range の長さ)**。**degree を下げる source 構造はまだ誰も試していない**。
候補:
- param `self`/`victim` が必要とする field を関数冒頭で早期 local に退避し、以降は param 自体を
  使わない (= param の live range を冒頭だけに縮め、関数全体での interference を消す)。コピーと
  違うのは「param を以降 dead にして coalesce 先を断つ」点 — param web が関数末尾まで live でなく
  なれば次数が下がり、locals より先に simplify されうる。
- 関数の tail (param を最後に使う区間) を helper に切り出し、param の live range を呼び出し前で
  終わらせる。
- param を使う箇所を関数前半に集約し、後半 (memset/onHitEvent 系の call が並ぶ区間) で param が
  live でなくなるよう並べ替える。
狙い: self の degree を victim/locals より下げれば self が先に着色され高位 reg (r30/r31) を取る。

当たれば self=r30 / victim=r31 になり promote。外れて全部 byte-identical or 全体 repartition なら
「Opus と同じく PINNED」が Fable でも追認されたことになる (それも有益な結論)。

## 作業手順

1. `python tools/setup_worktree.py batch_fable_onkarthit_recheck2` (または好きな batch id) で worktree 作成。
   ※ Opus セッションが作った `batch_fable_onkarthit_recheck` worktree は撤去済み。自分で作り直す。
2. 96.38% の出発 C body: `docs/drafts/Class2_expansion_nearmatches.handoff.md` の Appendix B。
   これを `src/game/auto_ONKARTHIT_block.c` の OnKartHit asm body と差し替えて出発点にする。
3. 測定: `tools/compiler_probe/measure_fns.py` + `rowdiff.py` で OnKartHit の per-row diff を見る
   (asm 出発点との差を最小化)。フル検証は `python configure.py && ninja build/GNLJ82/ok` で
   `build/GNLJ82/main.dol: OK` (SHA-1 一致) を確認。
4. degree-reducing 構造を 1 つずつ試し、param home が r30/r31 に動くか objdiff で確認。
5. 完了したら worktree root に `HANDOFF.md`:
   - VERDICT: PROMOTED (SHA-1 一致) or PINNED-confirmed (Fable でも degree-reducing が効かず)。
   - promote なら最終 src 形 + commit hash + `ninja build/GNLJ82/ok` 結果。
   - PINNED confirmed なら、試した degree-reducing 構造と各々の objdiff 結果。
   - `docs_notes` 節: `docs/notes/cw132-allocator-phase2f-research.md` の round 3 への追記 prose +
     `docs/notes/approachA-roadmap.md` の 1 行 entry。
6. worktree は green (`ninja build/GNLJ82/ok` clean) のまま終える。

## メタ (このセッションへの注意)

frida を使った register-allocator の直接観測は別 batch (Opus) で完了済みで、その結論が上の数値表。
このセッションは **objdiff だけで** degree-reducing source lever を探す純粋な source 実験。frida を
持ち出す必要は無いし、持ち出さなければ Fable のまま走れる公算が高い (Opus への自動切替は frida 等の
話題が trigger だったため)。
