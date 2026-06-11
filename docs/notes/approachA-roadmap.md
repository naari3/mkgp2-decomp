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
| 2a | fp-scratch numbering family の研究 (4 fn が 89-99% で待機) | **検証 NEGATIVE / family source-closed (2026-06-11)** — recipe は const-param 前提で実 fn に不適用 |
| 2b | class 2 frsp store-forward の研究 (6 fn family) | **完遂 (2026-06-11)** — 6/6 fn sweep。recipe core は全 fn で再現、promote 0 (全残差が register-identity family: 85-99% park) |
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
  - 2c: mr-SR-init (ShadowBB / GetMaxSpeedWithBonus の 2 fn、残差 1-2 命令)。→ SOLVED、下記 2026-06-11 後段エントリ参照。
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
- 2026-06-11: **Phase 2a 検証 NEGATIVE — family は source-closed と判定** (in-TU 10 trial + 12 probe、
  docs/notes/cw132-fpnumbering-phase2a-validation.md)。promote 0。
  - 観察 (事実): direct-copy 降順 recipe は copy src が **const 修飾の top-level pointer param** のときだけ
    batch する (9-probe bisect)。chased ptr (`mv = self->movement`) / const local / cast / __restrict /
    static-inline const-param helper は全て serialize — CW inliner は param の no-alias 属性を落とす。
    PerFrameStep 級 (src を struct member から取る fn) は recipe 域外。
  - 観察 (事実): named-temp pipeline を **昇順 def** (t0=mtx[0] 先頭、refill/store も昇順) に直すと
    copy 領域の emission は byte-exact になり、残差は純粋な 8-register mirror (t0..t7=f0..f7 vs
    target f7..f0) のみ。decl 順 / def 順 / 変数名の全 permutation で色は不変 —
    **named-web coloring は first-USE (store) 順で昇順**、store 順は target 形で固定なので mirror は
    source から到達不能。683/785 = 87.0% strict (objdiff-fuzzy ~98%)。
  - 観察 (事実): TickStatusEffectsByFlag は 4 trial 全部 byte-identical object — CSE'd const web
    (2+ uses) は別の immune sub-family。single-use temp batch は既に降順 = match 済み。
    na/nb def-order swap も in-fn では no-op (最小再現の lever は転移しない)。
  - 仮説 (推論): unlock には binary-level の allocator 研究が要る可能性が高い。source form 軸は全閉。
  - **roadmap リスク**: この family 4 fn (Explosion 88.99% / UpdateBoostVisualBlend 98.88% /
    TickStatusEffectsByFlag >99% / PerFrameStep 87.0% strict) のうち PerFrameStep は
    prefix (index 0-17) 内 — Phase 3 の A 化はこの fn を asm_fn のまま跨げるか要検討
    (asm_fn は extab を manual 保持するため A 区間連続性を壊す)。
  - 次: **Phase 2b dispatch** — class 2 frsp store-forward の C++ reference semantics 仮説
    (最後の未試行軸、6 fn family)。
- 2026-06-11: **Phase 2b SOLVED** (37 probes, ~25 min) — class 2 は plain C で到達可能だった。
  - 観察 (事実): copy block を `for (i = 0; i < 16; i++) s.mtx[i] = t[i];` (plain struct、
    volatile 不要) で書くと target 形が出る。variable-index store は CW の front-end
    store-to-load forwarding (constant-index lvalue のみ match) を逃れ、-O4,p が loop を
    full unroll、late pass が read-back を frsp (lfs 由来・live) / raw (演算由来) /
    real reload (evicted) に解決 — target の 5-frsp+1-reload partition を再現。
    GC 1.3-2.7 で hit、-O3/-O4/-O4,p 必須、exceptions/RTTI/inline/lmw 中立。
  - 観察 (事実): C++ 固有 form 10 種は全 negative — **本 batch の動機だった C++ 仮説は
    原因としては否定**。-lang=c++ は recipe に中立 (邪魔もしない)。
    旧 ledger「plain C 到達不能」は訂正済み (negative-probes note に訂正追記)。
  - 仮説 (推論): m2 の real reload は周辺 register pressure による自然な eviction。
    in-TU で出なければ consume 順 / temp decl 順が lever。
  - 次: **in-TU 検証 batch dispatch** — ItemEffect_Dispatch (86.34% draft、canonical specimen) +
    KartItem_ApplyImpactImpulse (83.66% draft)。成功すれば OnKartHit / Tick / Trap / Projectile に展開。
- 2026-06-11: **Phase 2b 検証完了 — recipe core は 2/2 fn で CONFIRMED、ただし promote 0**
  (Dispatch 86.34→97.07% / ApplyImpactImpulse 83.66→94.24%、docs/notes/cw132-class2-validation.md)。
  - 観察 (事実): loop-copy recipe は実 TU pressure 下で class-2 症状を全て再現 (frsp web /
    22+ dead store の exact offset / frame・callee-saved cascade)。frsp/reload partition は
    per-slot 制御可能 — reload にしたい slot だけ `*(volatile float *)&s.m[k]` で読む。
    新 lever 5 件 (dy-first schedule / compare-the-copy-target fmr coalesce / unnamed read-back
    降順 web / post-call plain read / named-sum dying-operand pick) も検証済み。
  - 観察 (事実): 両 fn の最終残差は register identity のみ (内容・offset・opcode 全一致) =
    **2a で source-closed 判定済みの fp-numbering tie-break family**。class 2 とは別問題。
  - 仮説 (推論): 残り 4 fn (OnKartHit / Tick / Trap / Projectile) も class-2 block 自体は
    1-2 build で再現するが、fn 到達点は high-90s park が濃厚 (consume web が unnamed 形なら
    match の可能性あり)。
  - **roadmap への含意**: fp-numbering family が prefix の実質的な最終 blocker に昇格した。
    Phase 3 (A 化) は対象 fn が C (matched) であることが前提なので、prefix 内の
    OnKartHit / ApplyImpactImpulse / PerFrameStep / Tick が 97-94% park のままだと A 区間が
    そこで途切れる。選択肢: (i) fp-numbering の binary-level allocator 研究 (2a で示唆)、
    (ii) prefix を park fn の手前まで縮めた部分 A 化、(iii) park を許容して Phase 4 断念。
  - 次: 2b 残り 4 fn への展開 batch (OnKartHit + Tick は prefix 内で Phase 3 直結、
    Trap / Projectile は TU 完遂用)。
- 2026-06-11: **Phase 2b 展開完了 — class-2 family 6/6 sweep 完遂、promote 0**
  (OnKartHit 77.9→96.38% / Tick 96.8→98.83% / Trap 44.9→85.34% / Projectile 85.4→88.40%、
  docs/notes/cw132-class2-expansion.md)。
  - 観察 (事実): class-2 recipe は全 fn で機能。新メカニズム: **escape-serialization** —
    struct member の address が call arg で escape すると同 struct の loop copy が serialize
    される (escape する vec を別 struct に分離で解決)。新 lever 多数 (join-variable coalescing /
    GPR は local 宣言順 / snd hoist / cap-up form / 名前付き temp で fmuls operand 順 など、
    note の Control-flow recipes 節)。
  - 観察 (事実): class-1 recipe の新前提 = bool が volatile reg に live すること
    (callee-saved bool は li-0 coalesce 失敗、§14.2 訂正済み)。TryStartByCategory 行の
    cross-call 積保持 sub-pattern は hard-block ではなかった (§14.2 一部訂正)。
  - 観察 (事実): 新 source-closed family instance = **fp callee-saved partition** (Tick entry の
    5 値 long-range 割付、4 probe shape で pairwise swap 不変)。Trap region-2 の batched
    3-frsp+3-muls scheduling も 5 shape で不達。
  - 残差は 4 fn とも register-identity / instruction-selection のみ。TU header 整備
    (view structs / typed prototypes / retyped externs) は main に merge 済み (codegen-neutral、
    SHA-1 検証済み)。
  - **Phase 2b 総括**: class 2 は idiom として完全解明 (recipe + access discipline + escape 則)。
    family 6 fn の promote を阻むのは全て fp/GPR register-identity tie-break 系。
    prefix 完成の最終 blocker は register-identity family 群に一本化された。
  - 次: Phase 2c (mr-SR-init、ShadowBB / GetMaxSpeedWithBonus、残差 1-2 命令)。
- 2026-06-11: **Phase 2c SOLVED — ShadowBB promote (matched)** (~60 probes + 60 in-TU variants、
  docs/notes/cw132-mrsrinit-phase2c-research.md)。
  - 観察 (事実): `mr rOFF, rI` の SR init は **static inline helper から loop が inline された
    場合のみ** 生成される。front end は standalone な定数 copy を全 13 spelling で li に fold
    (`-opt noprop` も無効 = propagation pass より前)。inliner が splice した for-init copy は
    後段で fold されず mr で残る。`static inline` は prod flags で emit されない (layout 安全)、
    plain `static` は inline されても emit される (layout breaker)。helper の local 宣言順が
    inline 先の GPR coloring を操作する。
  - **KartItem_UpdateShadowBillboardAndViewport 0x8004EDD4 matched** (97.95% → 100%、
    SHA-1 OK)。prefix 内の park が 1 つ解消。
  - GetMaxSpeedWithBonus は mr 含め 51/51 命令の構造一致まで到達したが、mv<->e の GPR coloring
    permutation (11 命令参照) で park — register-identity family の新 instance。
  - 仮説 (推論): 原文は KartMovement_CalcMaxSpeed 0x801999E0 (standalone twin) の header inline
    を消費していた。CalcMaxSpeed 自体も将来この recipe の候補。
  - 次: Phase 2d (ScopedTimer subi/lwz pair swap、FrameUpdate / Init + program-wide ~30 callers)。
- 2026-06-11: **Phase 2d SOLVED — CarObject_FrameUpdate promote (matched)** (16 probes、
  docs/notes/cw132-scopedtimer-phase2d-research.md、cpp-scoped-timer-pattern.md に訂正追記)。
  - 観察 (事実): pair swap の lever = **dtor tail の ticks→µs 変換を整数 temp 無しの単一式で
    書くこと**。named int temp (`us`/`diff`/`end`) が式を 2 つの tree に割ると lwz-first になる。
    float temp は無害。C/C++ front end・exceptions on/off は無関係。
    Phase 2c の static-inline-helper 仮説はこの flavor には negative (splice だけでは順序不変)。
  - 観察 (事実): target 内に lwz-first の site も実在 (0x8008C468、手書き timing code と推定) —
    順序は compiler artifact ではなく原文の temp 有無を encode している。
  - **CarObject_FrameUpdate 0x8004DECC matched** (97.10% → 100%、SHA-1 OK)。
    program 全体では 113 canonical dtor sites / 60 fn に recipe 適用可。
    canonical __dt__11ScopedTimerFv の opword shim も将来置換可能 (probe r1 で実証)。
  - 次: CarObject_Init 0x8004E618 promote batch (recipe 適用、prefix 内・0x7BC の full matching
    job)。その後 Phase 2e (chain 変種 / flavor 4 / flavor 5 / dead-counter)。
