# セッション引き継ぎ (2026-06-11)

新セッションの自分へ。前セッションは frida 使用で safety measures が flagged になった
(ユーザー判断: 偽陽性) ため切り替えた。作業内容・方針は何も変わっていない。続行せよ。

## まず読む順 (最初の一手)

1. **このファイル** (現在地と次の一手)
2. `docs/notes/approachA-roadmap.md` の末尾の時系列ログ (詳細な進捗。SoT)
3. `docs/notes/cw132-allocator-phase2f-research.md` (最重要 breakthrough = colorer MODEL-FOUND)
4. orchestrator として動くなら `.claude/skills/mkgp2-orch/SKILL.md` + state.json から復帰
   (`/mkgp2-orch-start` で state.json から認識される)

## 現在地 (確定事項)

- 作業対象: `src/game/auto_ONKARTHIT_block.c` (107-fn mega-bundle) の register-identity park 攻略。
  approach-A roadmap の Phase 0〜2f まで消化済み。
- **promote 済み 5 fn**: UpdateCoinSpeedBonus / OnItemHit (class-1 SOLVED) /
  UpdateShadowBillboardAndViewport (mr-SR-init) / FrameUpdate (ScopedTimer) /
  GetMaxSpeedWithBonus (Phase 2f model-guided)。
- SOLVED idiom family: class-1 / class-2 (loop-copy) / mr-SR-init (inline helper) /
  ScopedTimer (one-expression dtor tail) / dead-counter (invisible-use)。
- **最大の breakthrough = register-identity family MODEL-FOUND** (Phase 2f-3, frida):
  CW 1.3.2 colorer は web を **web-birth key 降順**で着色し r31 から降順に reg 割当。
  web-birth key = value-numbered web 生成順 = plain local では **定義/宣言順**。
  merged/CSE/param-merge web は遅生まれ→低 key→最後着色→低位 reg。
  inline splice は spliced web の key を振り直す (two-regime)。
  → 「source 制御不能」だった park が「web-birth 順の操作問題」に再分類された。

## 確定した promote lever (次の挑戦先)

`docs/notes/cw132-allocator-phase2f-research.md` の Frida colorer observation 節 + roadmap 末尾参照。
- **CarObject_Init 0x8004E618** (98.23%、ch/blk/sub/mgr): 4 owner-object の source 定義順を
  「target の r31-owner を最初に定義、r30 を 2 番目...」と並べる (high-confidence)。
  ただし別 blocker = new-expr r0-join (構造的 -1 命令、C 機構不在の疑い) があり 100% は別途要解決。
- **OnKartHit 0x8004A238** (96.38%、GPR partition): 同じ def/decl-order lever。prefix index 0 = Phase 3 の鍵。
- **HandleItemEffect 0x8004F858** (99.93%、handled web): obj を open-code のまま (early-born) +
  handled に independent late-born call-crossing web を与える。残 1 web。
- **ProcessWarpAndDash 0x8004D1A8** (94.6%) / **ApplyImpactReflect 0x8004B140** (95.19%): 走行中 batch で attack 中 (下記)。

## Phase 3 の gate

A 区間は TU 先頭から連続必須。index 0 の OnKartHit が register-identity park。
これを frida lever で解けば prefix が揃い、Phase 3 (manual extab 削除 + exceptions-on 再 compile) に進める。
fp-numbering 4 fn (Explosion/UpdateBoostVisualBlend/TickStatusEffectsByFlag/PerFrameStep) と
CarObject_Init の new-expr r0-join は構造的に prefix を跨ぐ可能性があり、A 区間の連続性で要検討。

## 走行中だった batch (前セッション最後の dispatch)

- batch_id: `batch_promote_modelguided_init` (sub_af81e94b, agent af81e94bcd32da750)
- 対象: CarObject_Init / ProcessWarpAndDash / ApplyImpactReflect の model-guided promote
  (frida 観測**前**の Phase 2f model で動いている)
- worktree: `.worktrees/batch_promote_modelguided_init`、branch `orch/batch_promote_modelguided_init`

### 結果 (処理済み)

**0 promote。処理完了済み (state flip / cleanup / push 済み)**。重要な統合知見:
- decl-order / merged-web lever は **実 fn では効かないことが多い** — param-interference /
  liveness graph が web home を既に pin しているため。frida 最小 probe で lever が効いたのは
  web が under-constrained だったから。GetMaxSpeed が解けたのは merge を消せた (制約緩和) ため。
- **source lever が効くのは under-constrained case のみ** という適用限界が確定した。
- CarObject_Init は coloring とは別に structural -1 命令 (new-expr r0-join) を持つ。
- ProcessWarpAndDash の param rank は callee-web-set 構成で flip する (固定でない)。

### 次の一手 (新セッション)

1. **OnKartHit 0x8004A238 に frida lever を当てて under-constrained か pin されているか判定**
   (prefix index 0 = Phase 3 の鍵)。under-constrained なら def 順 lever で promote、
   pin されていれば source からの prefix 完成は不可 → 下記の代替へ。
2. pin の場合の代替: (a) frida で web 生成順を直接動かす source 構造を更に探す、
   (b) 部分 A 化 (park fn 手前まで)、(c) Phase 4 断念の判断。
3. HandleItemEffect (99.93%、残 1 web) は frida lever「obj open-code + handled に late-born
   call-crossing web」を試す価値あり (under-constrained 寄り)。

## 標準 per-batch 手順 (リマインド)

dispatch → task-notification 受信 → worktree の HANDOFF.md + git log を read →
`git cherry-pick <src commit>` (or `git apply` で src patch のみ) → `python configure.py && ninja build/GNLJ82/ok`
で SHA-1 検証 → docs notes / roadmap / §14.2 更新 → `tmp/flip_*.py` で state.json flip (fn→matched/asm_fn,
batch→merged, active_subs から sub 削除) → `git worktree remove --force` + `git branch -D` → commit + push。
research batch は HANDOFF の docs_notes を該当ファイルに書き出す。tmp/*.py の print は ASCII only。

## ツール環境メモ

- Ghidra: bmp_output project に `/mwcceppc_132.exe` (CW 1.3.2 compiler) import + analyze 済み (3711 fns)。
  接続は `connect_instance(project="bmp_output")`。import が `Database is closed` で落ちたら
  run_script_inline + ProgramLoader (Java 構文) で回避 (`~/.claude/skills/mkgp2-ghidra/SKILL.md`)。
- frida: ユーザー許可済み。mwcceppc.exe の colorer hook 用 (FUN_00507a30/FUN_00507b50, home-reg node[+0x14])。
  scaffold = `tools/compiler_probe/frida_colorer_probe.js` + `frida_colorer_run.py`。
  **shipped compiler は触らない、private copy + lmgr326b.dll 同梱で hook**。ASLR off (ImageBase 0x400000)。
- probe harness: `tools/compiler_probe/` (probe.py に mwcceppc.exe path、各 idiom の probe + classifier)。
