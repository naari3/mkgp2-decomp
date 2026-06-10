# approach A 完遂ロードマップ (auto_ONKARTHIT_block.c)

2026-06-11 開始。ゴール: TU 先頭から address 順に approach A (exceptions-on auto-extab) 区間を伸ばし、
EH scaffolding 関数 (KartItem_Dtor 0x8004E2B0 ほか) を C で promote する。
各 phase は前 phase の結果に依存する。観察 (事実) と仮説 (推論) を分けて時系列で追記すること。
結論が覆った場合も古い項目を消さず「訂正」を追記する。

背景: docs/per_fn_matching_strategy.md 14.1 (extab approach A/B, mix-failure rule) /
docs/notes/exceptions-on-eh-scaffolding-unpromotable.md (EH class, unlock 条件)

## Phase 一覧

| phase | 内容 | 状態 |
|---|---|---|
| 0 | class 1 の最終 probe (compiler patch rev / 未試行 pragma) | **SOLVED (2026-06-11)** |
| 1 | class-1 10 fn の回収 (salvage draft 適用) | **完了 (2026-06-11)** — recipe 14/14、promote 2 fn、残りは他 family park |
| 2a | fp-scratch numbering family の研究 (4 fn が 89-99% で待機) | **PARTIAL-SOLVED (2026-06-11)** — 検証 batch 進行中 |
| 2 | 先頭区間 index 0-17 の残り idiom 解決: class 2 (OnKartHit) / flavor 5 (MainUpdate) / flavor 4 (ProcessWarpAndDash) / ScopedTimer (FrameUpdate) | 未着手 |
| 3 | index 0-17 の manual extab 削除 + exceptions-on 再コンパイル (A 化)、1 fn ずつ SHA-1 検証 | 未着手 |
| 4 | KartItem_Dtor (index 18) ほか EH fn の A promote | 未着手 |

## 制約 (再確認)

- auto-extab は .extab_user より常に前に link される (14.1)。よって A 区間は TU 先頭から
  extab 持ち fn が欠けなく連続している必要がある
- index 0-17 はほぼ全て extab 持ち (KartItem_Dtor precan で「17 manual-extab fns precede」確認済み)
- 末尾 dtor 11 個の回収は Trap/Projectile (class 2) を含む TU ほぼ全域の A 化が前提 —
  Phase 4 の現実的な到達点は KartItem_Dtor + (InsertBefore) まで

## Phase 0 詳細

未試行として 14.2 に記録されている 2 手段の消化:

1. 手持ち mwcc の patch revision 違い (同 1.3.2 系の別ビルド含む) での
   branch-over-branch invert 挙動の差
2. 未 probe の pragma (peephole off 系、branch folding 系、CW 1.3.2 の pragma 全列挙から)

判定対象 shape (class 1, KartItem_OnKartHit 0x8004A238 ほか TU 内 9 fn / 19 sites):

```
or.  r0, rA, r0     # u64 flag test の結果
bne  L1
b    L2             # 空 fall-through
L1:
li   rD, 0x1
L2:
```

CW が全既知 form で emit するのは 1 命令短い `beq L2; li rD,1; L2:` (invert 形)。

go/no-go gate: 解けなければ class-1 10 fn + EH 13 fn は恒久 park、Phase 1 以降は中止。

## 時系列ログ

- 2026-06-11: roadmap 作成、Phase 0 dispatch。
- 2026-06-11: **Phase 0 SOLVED** (91 probes, 45 min)。class 1 は compiler variant/pragma の問題ではなく
  source form: 明示的 `== 0` 比較 + then=0/else=1 arm 順序で target 形が出る (§14.2 更新済み)。
  compiler patch rev 軸と pragma 軸は全 negative で closed。probe harness は tools/compiler_probe/ に保存。
  - 観察 (事実): probeE/probeH が GC/1.3 以降で TARGET 形、1.2.5 以前は other、3.0/Wii は branchless。
  - 仮説 (推論): then=0 が full diamond を作り folding を阻止、li 0 が zero reg に coalesce されて消える。
  - Phase 1 の注意: coalesce 前提 = bool が u64 mask hi の zero register を共有できること。site ごとに要確認。
- 2026-06-11: Phase 1 開始。対象 9 fn (OnKartHit は class 2 併発のため Phase 2 送り、
  StlList_RemoveByValueField は arm-order 原理の応用候補として後段で retry)。
  batch 1 = UpdateShadowBillboardAndViewport / UpdateCoinSpeedBonus / ApplyImpactReflectAndDampVelocity。
- 2026-06-11: Phase 1 batch 1 完了 — **recipe 実 TU 検証 OK** (両 zero-half polarity で byte-exact、tuning 不要)。
  - UpdateCoinSpeedBonus: **matched 100%** (class-1 解法による初の実戦 promote)。
  - ShadowBB: 97.95% park。class-1 site は解けた。唯一の残差 = mr-SR-init (GetMaxSpeedWithBonus 94.35% と同一 block)。
    これが解ければ 2 fn 同時 unlock。`#pragma opt_propagation off` は bit-identical no-op (axis closed)。
  - ApplyImpactReflect: 95.19% park。**訂正: この fn の site は u64 family ではなく int-equality-chain 変種**
    (li 0 の削除には独立 zero web との coalesce が必要 = chain には無い。4 probe negative)。
    class-1 残対象の site 形状は precan で u64 family / chain 変種を判別する必要あり。
  - 新 idiom: volatile-cast const load dedup / in-place sqrtf / outer-const-local split (note 参照)。
  - batch 2 = CarObject_OnItemHit + KartItem_ApplyImpactImpulseAndRumble。
- 2026-06-11: Phase 1 batch 2 完了。
  - OnItemHit: **matched 100%** (recipe 3 連続実証、mask 0x40ULL site が初 build で byte-exact)。
  - ApplyImpactImpulse: 83.66% park — precan で class-2 frsp interleave (16-float copy) を検出、規定通り park。
    ただし class-1 site は **CSE-reuse sub-shape** (同 mask を 2 回 test、and 半分が CSE される) でも recipe 転移を確認。
  - Phase 1 残: KartItem_Tick / KartItem_PerFrameStep / TickStatusEffectsByFlag (batch 3-4)。
    OnKartHit は class 2 併発のため Phase 2 送りのまま。
  - batch 3 = KartItem_Tick + KartItem_TickStatusEffectsByFlag。
- 2026-06-11: Phase 1 batch 3 完了 — **recipe 検証が完結 (累計 13/13 u64 site byte-exact)**。promote は 0。
  - TickStatusEffectsByFlag: 7 site 全部 recipe で解けたが、fp-scratch tie-break (Explosion family) で
    >99% park (23 命令、内容同一の register 置換のみ)。paste-ready C を drafts に保存。
    新 idiom: 隣接 2 site の CSE には named u64 local + ternary 形 / `#pragma dont_inline on`
    (同 TU 前方 callee の auto-inline 抑止、auto_inline off は効かない)。
  - KartItem_Tick: 0-probe park (entry block に class-2 frsp trio)。class-1 site は u64 family 確認済み。
    class 2 研究 batch で ItemEffect_Dispatch と束ねるのを推奨。
  - batch 4 = KartItem_PerFrameStep (Phase 1 最終)。
- 2026-06-11: **Phase 1 完了**。batch 4 (PerFrameStep 0xC44) は 97.87% park — recipe は 14/14 で検証完結、
  precan も全 class クリーン、残差は fp-scratch numbering のみ (805 命令中 91 行、内容差ゼロ)。
  Phase 1 総括: promote 2 (UpdateCoinSpeedBonus / OnItemHit)、近接 park 5 (97-99% 帯 3 + 95% 帯 2)。
  class-1 という意味では 10/10 全勝 — park の原因は全部別 family。
- 2026-06-11: **Phase 2 を family 別に再構成** (元の「index 0-17 の 4 idiom」より粒度を細かく):
  - **2a: fp-scratch numbering** (later-first-use→lower-reg)。4 fn が 89-99% で待機
    (Explosion / UpdateBoostVisualBlend / TickStatusEffectsByFlag / PerFrameStep)。
    Phase 0 方式 (最小再現 + 自動分類 + compiler/pragma 総当たり) を適用 → dispatch 済み。
  - 2b: class 2 frsp store-forward (6 fn: OnKartHit / Tick / ApplyImpactImpulse / Dispatch / Trap / Projectile)。
    C++ reference semantics 仮説の検証が未着手の最終手段。
  - 2c: mr-SR-init (ShadowBB / GetMaxSpeedWithBonus の 2 fn、残差 1-2 命令)。
  - 2d: ScopedTimer pair swap (FrameUpdate / Init + program-wide ~30)。
  - 2e: chain 変種 / flavor 4 / flavor 5 / dead-counter (各 1-2 fn、最難)。
  prefix (index 0-17) の完成には 2a-2e 全部が必要。HandleObstacleHit (class 3) のみ Phase 3 の
  A 化で自動解決する見込み。
- 2026-06-11: **Phase 2a PARTIAL-SOLVED** (132 probes, ~17 min)。機構が 2 系統と判明:
  - 観察 (事実): named local は GO web → 昇順番号 (GC 1.0-2.7 / 全 pragma / 全 -opt で不変)。
    named temp を介さない直接 member-to-member copy は FE expression temp → **pool 上端から降順** で、
    最小再現 (s8_member) が target 形 (lfs f7..f0 / stfs f7..f0) を byte-exact に再現。GPR 系も同型。
  - recipe: copy 領域は named-temp pipeline をやめて直接 copy にする (batch 幅は free-reg 数に依存、
    fn ごとに要検証)。GO-web tie (Explosion vx/const / na-nb / cross product) は最小再現で def 順が
    効いた — 実 fn では近傍 web の影響で違った可能性があり、mixed-mechanism で再試行。
  - compiler / pragma / -opt 軸は全 negative で closed。harness は tools/compiler_probe/ (fp 系列)。
  - 検証 batch dispatch: PerFrameStep + TickStatusEffectsByFlag (draft 適用 + recipe 置換)。
