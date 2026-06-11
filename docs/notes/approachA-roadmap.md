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
| 3 | index 0-17 の manual extab 削除 + exceptions-on 再コンパイル (A 化)、1 fn ずつ SHA-1 検証 | **保留 (2026-06-11 訂正)** — 「断念」は撤回。inline-composition probe で partition が動き、残差は param-class flip 1 点。flip 条件特定 (OFOD-CAE matrix) が次の鍵 |
| 4 | KartItem_Dtor (index 18) ほか EH fn の A promote | 保留 (Phase 3 依存) |

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
- 2026-06-11: **CarObject_Init 98.23% park** (14 builds、docs/notes/cw132-carobject-init-park.md)。
  - 観察 (事実): ScopedTimer recipe は 0x7BC fn 内でも build 1 で byte-exact (転移性 3 連続実証)。
    新検証 lever 9 種 (volatile aux-pointer hoist ×3 / u8-typed prototype で clrlwi 除去 /
    inline-init preload / addi-CSE defeat / stack locals 逆宣言順 / new-expr trivial-guard 形 等)。
  - 観察 (事実): 新 precan class = **new-expr guarded-ctor の r0-join**。非自明な pre-ctor code が
    ある場合、target の `mr. r0,r3` join を CW C は全 spelling で r3 join に copy-prop し
    **構造的 -1 命令** (size 不一致なので in-place park も不可)。自明 guard の 6 sibling は
    plain C で再現する。register-web tie-break (ch/blk/sub/mgr) も併発。
  - 仮説 (推論): r0-join は C++ new-expression の compiler temp 由来 — C からは到達不能の可能性が
    高い (adjustor thunk と同種の言語機構ギャップ)。
  - prefix への影響: CarObject_Init は -1 insn の構造差を持つため、**A 化 (Phase 3) では
    asm_fn のまま跨ぐ必要がある** — fp-numbering park 群と同じ扱い。
  - 次: Phase 2e (chain 変種 / flavor 4 / flavor 5 / dead-counter — 各 1-2 fn、最難)。
    その後 Phase 3 の実行可否を prefix park 状況込みで再評価する。
- 2026-06-11: **Phase 2e 前半 — dead-counter SOLVED、mtx-loop は機構絞り込み**
  (docs/notes/cw132-phase2e-research.md)。
  - 観察 (事実): dead-counter は **dead ではなかった** — counter は後続 call の余分な引数
    (無視される) として渡され、regalloc の coalescing で命令ゼロの invisible use になる。
    K&R empty-paren extern + `IsActive(guard, i)` で再現、HandleItemEffect 98.62→**99.93%**
    (残 7 行 = `handled` web の色のみ)。binary 全体 76 件の同形も全て hidden use 持ち。
    旧 hardblock note は SUPERSEDED。
  - 観察 (事実): 新 lever = **one-home-per-variable** (fn-scope 変数は全 live range で単一
    home、block-local の interference で home を強制できる) + per-site block decl-order。
  - 訂正: mrsrinit note の「const-prop は splice 後に再走しない」仮説を narrowing —
    **post-splice の iterative DCE は存在する** (probe g1/g2 で実証)。FE-only なのは
    copy/const folding のみ。dead な spliced web は必ず消える。
  - 観察 (事実): MainUpdate の mtx loop は「O2 形の loop body + O4 形の late backend」という
    シルエット。source lever 未発見。**同 loop が 14+ unmatched fns に存在** (header-inline
    MtxConcat 系 helper と推定) — 解ければ大量 unlock の最重要未解決 idiom に昇格。
  - P3 (chain 変種) / P4 (flavor 4) は予算切れで未着手。P3 は invisible-use lens での再検討が
    次の一手 (chain の li-0 は hidden use を持つ変数かもしれない)。
  - 次: Phase 2e 後半 batch — HandleItemEffect の handled-r22 lever hunt (99.93% からの一押し) +
    P3 chain 変種 (invisible-use lens) + P4 flavor 4 の見切り probe。
- 2026-06-11: **Phase 2e 完了 (後半 batch、promote 0)** — 研究 phase (0/1/2a-2e) 全消化。
  - 観察 (事実): handled-r22 lever は ~28 probe 全 negative (symbol 名 / decl 順 / scope /
    copy ancestry / dead-write interference の全 axis closed)。**新 invariant**: CW 1.3.2 は
    低優先 fn-scope u8 flag を fn-scope pointer sibling と**必ず同色にする** (share-pick)。
    target は handled と obj が別色 = この pairing を破る機構が source に無い。
  - 観察 (事実): chain 変種は invisible-use ではない (r6 は visible read 持ち)。goto-out 形で
    init li が初めて生存 (新事実) したが link の beq-fold は不可避。park 確定 (4+4 probe)。
    flavor 4 は未着手 (2-probe retry recipe を note に記録: inline/block restructuring のみが
    pair 配置を動かせる lever class)。
  - **Phase 2 総括**: source-form で解ける idiom は全部解けた (class 1 / class 2 / mr-SR-init /
    ScopedTimer / dead-counter の 5 family SOLVED、promote 4 fn)。残る park は全て
    **register-identity tie-break 系** (fp-numbering / GPR partition / fn-scope pair share-pick /
    coloring permutation) + 構造ギャップ 2 種 (new-expr r0-join / EH scaffolding / adjustor thunk)。
  - **Phase 3 gate 評価 (2026-06-11)**: A 区間は TU 先頭から連続が必須だが、**index 0 の
    OnKartHit 自体が 96.38% park** (register-identity)。よって Phase 3 は現状開始不能。
    残された unlock 経路は 1 つ = **register-identity family の binary-level allocator 研究**
    (colorer の web visit order の解明)。解ければ OnKartHit / Tick / ApplyImpactImpulse /
    Dispatch / GetMaxSpeedWithBonus / HandleItemEffect / fp-numbering 4 fn が連鎖 self-correct
    し、prefix が一気に揃う。これを Phase 2f として次に掲げる。
- 2026-06-11: **Phase 2f 偵察 PARTIAL — GPR coloring rule 4 本確立 + allocator dump の所在特定**
  (docs/notes/cw132-allocator-phase2f-research.md)。
  - 観察 (事実): mwcc 1.3.2 backend は graph-coloring allocator (binary 内に Coloring.c /
    InterferenceGraph.c / SpillCode.c の assert 文字列、fSpilled/fCoalesced web flag)。
    差分 probe で 4 rule 確立: **RULE1** callee-saved 判定は live range が bl を跨ぐか
    (純粋な live-range 属性) / **RULE2 (鍵)** callee-saved GPR local は **source 宣言順** で
    r31 から降順 (discriminator probe で def/use/arg 順・use-count を排除) / **RULE3** locals が
    params に優先 / **RULE4** disjoint range 間で register 再利用 (真の interference colorer)。
  - 訂正: Phase 2e の「decl-order 方向は振動する」観察は confound (volatile/callee 混在 +
    param) — 8/8 probe で r31-降順に統一。share-pick の残差も「handled が obj の decl-rank
    slot を継承」として再解釈できる。
  - 観察 (事実): per-pass dump (`Dumping function %s after %s` / `[FUNCTION-LEVEL ASM] AFTER
    REGISTER COLORING`) が binary 内に実在、.bss flag 0x5e90ec で gate。`#pragma dumpir` /
    flag の binary patch 単体では発火せず — 追加 gate (0x5e91de、IrOptimizer predicate) が残る。
    key address は note に記録済み。
  - 仮説 (推論): fp の first-use 昇順 rule は別の short-range web class — two-tier モデル
    (long-range callee-saved = 宣言順 / short-range scratch = first-use 順) が有望、未検証。
  - 次 (3 並列候補、推奨順): (1) dump 有効化 (disasm 0x55b510 / 0x433310 / 0x453820 +
    options struct) — 当たれば visit order が直接観測可能 = MODEL-FOUND。(2) two-tier モデルの
    closing probe。(3) RULE2 の in-TU 検証 — CarObject_Init (ch/blk/sub/mgr) と OnKartHit の
    owner 宣言 permutation で実 fn の色が動くか。
- 2026-06-11: **Phase 2f model-guided 検証 — GetMaxSpeedWithBonus promote (matched)、model 境界も精密化**
  (docs/notes/cw132-allocator-phase2f-research.md の In-TU validation 節)。
  - **KartItem_GetMaxSpeedWithBonus 0x8004F040 matched** (~60 variant 床だった mv<->e park を
    model-guided 3 build で解決)。鍵 = **merged web は最後に色付けされる** corollary: wrapper-local
    mv / mv param が param-merge で r7 に pin されていたのが床の原因。tail を helper 内に入れて
    wrapper を passthrough 化 → merge 消滅 → decl `(e,off,mv,i)` が leaf volatile pool の r7 降順で
    target 一致。RULE2 の scratch-pool 方向 gap (leaf volatile = r7 降順) も同時に閉じた。
    **blind permutation で 2 batch 床だった park が model から 3 build で解けた = model-guided の
    威力を実証**。promote 計 5 fn 目。
  - 観察 (事実): HandleItemEffect は two-regime coloring を精密 mapping (5 build)。helper-splice
    regime は handled=r22 ✓ だが obj も r22 に demote ✗、open-block regime は obj=r29 ✓ だが
    handled=r29 ✗。target は「obj 早 + handled 遅」の混合で source 形では未到達。per-site の
    decl-visit 方向は (regime, site 序数) の決定的関数 (旧「振動」の正体)。
  - 訂正: RULE3 を「param は locals の次」→「**param/merged web は最後に色付け**」に精密化
    (standalone CancelActiveEffect の self=r24 が根拠)。HIE の param r31/r30 配置は未解決矛盾
    として明記 (degree-based 順序だと build-0 handled を誤予測)。
  - 次: dump 有効化 batch (走行中) の結果待ち。dump が出れば two-regime / merged-last / share-pick を
    観測で確定でき、残り park (Init / ProcessWarpAndDash / OnKartHit / HandleItemEffect) を
    model から一括攻略できる見込み。
- 2026-06-11: **Phase 2f-2 dump 有効化 PARTIAL** (Ghidra + byte scan、docs/notes/
  cw132-allocator-phase2f-research.md の Dump enablement 節)。
  - 観察 (事実): mwcc 1.3.2 には dump system が 2 つある。(1) per-pass **listing** dump
    (`AFTER REGISTER COLORING`) は emit fn FUN_004ffdb0 が single-RET stub = **release build で
    本体が削除済み、どの flag でも復活不能**。Phase 2f の「0x5e90ec=1 patch で無出力」の正体
    (stub を呼ぶだけ)。(2) IR-optimizer per-pass dump (gate DAT_005e9409、`<basename>.log` 出力) は
    生きていて、1-byte patch (private copy) で 53 pass 全ての named IR (flowgraph + 変数名を
    宣言順で含む式木) を取得できた。
  - 仮説 (推論): (2) は pre-codegen なので colorer が consume する web は見えるが物理 register /
    visit order は見えない。colorer visit order を直接観測するには **frida で colorer
    FUN_00579cf0 を hook** する経路が残る (entry point 確定済み、home-reg field offset の特定が
    残課題)。scaffold は tools/compiler_probe/frida_colorer_probe.js。
  - shipped compiler は無傷 (SHA-1 検証済み)。
  - **Phase 2f 総括 (現時点)**: listing dump 経路は閉じた。残る観測経路は frida (colorer の
    web struct を実行時に walk)。ただし **model-guided 検証で既に GetMaxSpeedWithBonus が
    解けている** ので、dump が無くても black-box model の精緻化 + 各 fn の merged-web 操作で
    park を 1 つずつ落とせる実績がある。frida 経路は「model の裏取り + 一括攻略」の上振れ手段、
    本線は model-guided promote の継続。
  - 次: (A) frida colorer hook batch (上振れ)、(B) model-guided で Init / OnKartHit /
    ProcessWarpAndDash を merged-web-last + RULE2 で攻略 (本線)。並列可。
- 2026-06-11: **Phase 2f-3 frida colorer 観測 — MODEL-FOUND** (docs/notes/
  cw132-allocator-phase2f-research.md の Frida colorer observation 節)。**register-identity family の
  機構が実行時観測で確定した** — roadmap 全体の最大の breakthrough。
  - 観察 (事実、frida 実測): colorer は graph-coloring。home-reg は interference-graph node の
    `[+0x14]` (u16、0xffff=未着色)、select 関数 FUN_00507a30 が書く。visit order = FUN_00507b50 が
    simplify/select stack を **web-birth key 降順**で pop、各 callee-clique web に r31 から降順で
    register を割当。**web-birth key = value-numbered IR の web 生成順 = plain local では定義 =
    宣言順** (RULE2 の「宣言順」の正体がこれ。1 つの機械的規則に還元された)。
  - 観察 (事実): merged-web-last は機構確認 (merged web は key 最低 → 最後着色 → 低位 reg)。
    two-regime も確認 (inline splice が spliced web の key を振り直し、fn-scope obj を押し下げる)。
    decl/def-order lever は colorer_declorder probe で binding が反転することを確認 (ch=r31 vs ch=r28)。
  - **promote lever 確定 (HANDOFF actionable)**:
    - **CarObject_Init ch/blk/sub/mgr**: 4 owner-object の **source 定義順**を「target の r31-owner を
      最初に定義、r30 を 2 番目...」と並べる (high-confidence lever)。
    - **OnKartHit GPR partition**: 同じ def/decl-order lever。
    - **HandleItemEffect**: obj を **open-code のまま** (early-born で高位 reg 維持) + handled に
      **independent late-born call-crossing web** を与える (substantial inline helper は obj を
      regime B で押し下げるので不可)。「obj 早 + handled 遅」を web-birth 条件として具体化。
  - binary facts: ASLR off (ImageBase 0x400000 直)、private copy は lmgr326b.dll 同梱要、
    frida 17.x。shipped compiler 無傷 (SHA-1 検証)。
  - 仮説 (推論): fp-class partition (#6) は frida 未再 probe だが、同じ web-birth key 順で
    rank すると予測 (class index != 4、未検証)。
  - **意義**: 本線 (model-guided) は既に GetMaxSpeed を解いており、今回 frida 観測で
    Init / OnKartHit / HandleItemEffect の具体的 lever が確定した。prefix の register-identity
    park は「源流で制御不能」ではなく「web-birth key を source の定義順で操作する」問題に
    なった。本線 batch (走行中) がこの lever で promote を積めば、Phase 3 (A 化) の gate が開く。
  - 次: 本線 batch の結果処理 → frida lever を反映した Init / OnKartHit / HandleItemEffect の
    promote 再挑戦 → prefix が揃ったら Phase 3 (manual extab 削除 + exceptions-on 再 compile)。
- 2026-06-11: **model-guided round 2 — 0 promote、frida lever の適用限界が判明** (3 fn 検証、
  docs/notes/cw132-allocator-phase2f-research.md の In-TU validation round 2 節)。
  frida MODEL-FOUND と統合すべき重要な反例:
  - 観察 (事実): decl-order / merged-web lever は **実 fn では効かないケースが多い**。
    CarObject_Init の ch を o1 (movement) と coalesce しても byte-identical (ch は r25 のまま) =
    merge lever 反証。ProcessWarpAndDash で arg/statement 順を変えても callee web は re-rank されず。
  - 観察 (事実): ProcessWarpAndDash の param `self`=r31 が first local `mov`=r30 の**上**に rank —
    round-1 standalone (CancelActiveEffect の param self=r24 が最後) と**矛盾**。
    param rank は固定でなく callee-web-set 構成で flip する (round-1 bisect で 3rd web mgr +
    9-arg CalcExitPosition に pin と判明済み)。
  - 観察 (事実): CarObject_Init の hard cap は coloring ではなく **structural -1 命令**
    (new-expr r0-join、494 vs 495 命令)。coloring は二次的。
  - **統合結論 (仮説含む)**: colorer 機構は MODEL-FOUND (web-birth key 降順) で「web がどこに
    着地するか」は予測できるが、**実 fn では param-interference / liveness graph が既に web home を
    pin しており、source の宣言順 lever はそれを上書きできない**。frida の最小 probe で decl-order
    lever が効いたのは web が under-constrained だったから。GetMaxSpeed が解けたのは merge を
    消せた (= 制約を緩められた) ため。**source lever が効くのは under-constrained case のみ**。
  - ApplyImpactReflect は coloring 外 (int-chain li-deletion、独立 zero web 不在で park 継続)。
  - **Phase 3 gate の見通し更新**: prefix index 0 の OnKartHit が under-constrained (lever 効く) か
    pin されているか未検証 = これが次の判定対象。pin されていれば source からの prefix 完成は不可能で、
    残る手段は (a) frida で更に深い lever (web 生成順を直接動かす source 構造) を探す、
    (b) 部分 A 化 (park fn 手前まで)、(c) Phase 4 断念。
  - 次: OnKartHit に frida lever を当てて under-constrained か判定する batch。
    + reusable objdiff harness (tools/compiler_probe/measure_fns.py, rowdiff.py) 追加済み。
- 2026-06-11: **round 3 — OnKartHit gate PINNED + HandleItemEffect PARKED (2 batch、0 promote)、Fable 再検証へ**
  (docs/notes/cw132-allocator-phase2f-research.md の round 3 + HIE 節)。
  - 観察 (事実): OnKartHit 0x8004A238 (prefix index 0) は param self/victim が最低 web-birth key
    (32/33) + 最大 interference degree (adjN 135/137) → 最後着色 → r26/r27、target は r30/r31 (param
    最上位)。3 lever (局所宣言順 / param→局所コピー [byte-identical] / 局所遅延生成 [95.43%]) 全
    negative。2 独立 run が同結論 (PINNED)。HandleItemEffect 0x8004F858 は 99.93%、残差は handled 単一
    phi-web の move-coalescer tie-break (obj は既に r29 で正しい、param r31/r30 も blocker でない)、
    6 probe 全 refute。両者とも source-movable でない。
  - 訂正: HIE の two-regime 仮説は不要だった — ApplyDriftBoost が standalone matched fn = real bl の
    ため obj は splice されず元から r29。残るは handled の coalesce 先のみ。
  - 仮説 (推論)・未解決: 3 lever は全て web-birth **順序**を攻めた。pin の正体は param の interference
    **degree** で、degree を下げる source 構造 (param を早期 local に退避して param 自体を dead にする
    等) は**未試行**。source-closed 確定前の最後の候補。
  - 方針 (ユーザー判断): この未試行 lever を **Fable で** (frida 不要、objdiff のみ) 別セッションで
    再検証する (0 promote が Opus の探索不足でないかの確認)。引き継ぎ = docs/notes/onkarthit-fable-recheck-brief.md。
  - Phase 3 gate: 結論保留。Fable recheck で degree-reducing が効けば gate が開く。効かなければ
    register-identity park family を source-closed と確定 → 部分A化は index 0=OnKartHit が pin のため
    空 prefix = 実質不可 → Phase 4 断念が濃厚、他 TU の pending fn へ軸足。
  - メタ: このセッションは frida 言及で safety classifier に flag され Fable→Opus 自動切替された
    (偽陽性)。OnKartHit/HIE batch は完了処理済み (state flip / cleanup / push)。frida 観測は完了済みで
    今後の本作業に frida 不要 = Fable 維持の見込み。
- 2026-06-11: **Fable recheck 完遂 — OnKartHit degree-reducing 4 構造全 NEGATIVE、PINNED-confirmed (0 promote)**
  (batch_fable_onkarthit_recheck2、docs/notes/cw132-allocator-phase2f-research.md 末尾の Fable recheck 節)。
  - 観察 (事実): E1 victim-tail-hoist 92.54% で param home はむしろ降下 (r25/r26)、E2 late-copy は
    baseline と byte-identical (copy 位置によらず param-merge が web identity を保持)、E3b volatile-slot で
    両 param web を関数の ~63% 地点で完全 kill (disasm 検証済) しても home r26/r27 不動 (87.36%)、
    E4 tail-helper 切り出しでも縮小 callee 集合の相対最下位のまま (52.82%)。
  - 結論: **degree は pin ではない**。param web の着色順位は identity (最低 web-birth key 32/33) で固定。
    round 3 の OPEN 仮説は否定、OnKartHit は **C の表現空間で source-closed**。
  - 未試行の最終軸 = **C++-form probe**: 元実装は C++ 確定 (extab が dtor_80036E40 を参照、vcall 残差
    r6-vs-r12 も real virtual dispatch を示唆)。Phase 2b の C++ negative は class-2 (frsp) に対してのみで、
    GPR partition への this-call method 形 / reference param / real virtual call は未 probe。
    これが negative なら register-identity family を完全 close し、Phase 3/4 断念 → 他 TU へ pivot。
  - 次: C++-form probe batch (standalone harness で OnKartHit body を C++ 形にして partition 観測)。
- 2026-06-11: **C++-form probe 完遂 — 全 negative、register-identity family は C/C++ 両空間で close 確定**
  (batch_fable_onkarthit_recheck2 follow-up、research note 末尾の C++-form probe 節)。
  - 観察 (事実): -lang=c++ / this-call method 形 / real virtual dispatch (base 無し + polymorphic base
    派生で vptr=0x0・offset 完全一致の最忠実形) / reference param の 6 変種すべてで homes
    self=r26 / victim=r27 不動 (standalone harness、P0 で in-TU 同一 stream を検証済み)。
  - 副産物: (1) real virtual は target の r12-chain vcall 形を出す — C の明示 vt-struct 形の r6 中間
    reg は C-source artifact。vcall 形だけが残差の park fn は C++ TU 化で unlock 可能性あり。
    (2) CW 1.3.2 は base 無し polymorphic class の vptr を末尾に置く → 元実装は polymorphic 基底
    からの派生と思われる (将来の C++ 再構成の layout 指針)。
  - **Phase 3/4 判定: 断念確定**。prefix index 0 (OnKartHit) の partition は source 到達不能。
    残る理論上の経路は allocator の web-birth key 採番自体を変える未知の機構のみで、費用対効果から
    本 roadmap では追わない。**軸足を他 TU の pending fn (mega-bundle promote 本流) へ pivot**。

- 2026-06-11: **訂正 — Phase 3/4 の「断念」を撤回、保留に戻す** (batch_fable_onkarthit_recheck2 follow-up 2、
  research note 末尾の「訂正 + inline-composition probe」節)。
  - 訂正: 前 entry の「C/C++ 両空間で到達不能と確定」は過大。open-coded 形に限る話で、
    **inline-composition 軸 (helper splice で locals の web key を振り直す) が未試行だった**。
  - 観察 (事実): bool quad を static inline accessor 化 (I1) しただけで partition が初めて動き、
    li-coalescing 残差も解消 (416=416 行)。I3 (+C++ method + real virtual) で vcall r12 残差も解消、
    **残差は「param 組 vs locals」の class 単位 permutation 1 点に縮約** (locals の相対順位は target 一致)。
  - 観察 (事実): target TU 18 fn の param 配置は TOP/BOTTOM/MIX 混在で、ほぼ同一コードの
    OnFallOffOrDeath (self=r31 TOP) / CancelActiveEffect (self=r24 BOTTOM) が両方 plain C で
    matched 済み = 両極とも同一 compiler で到達可能。bisect で flip lever = OFOD の sec web
    (遅生まれ call-crossing callee pointer、出生元不問) と特定。ただし OnKartHit への単純移植 (I5) は
    negative — flip 条件は web 集合構成依存。
  - 「どうやってこの binary を作ったか」への答え (仮説、高確度): 普通の C++ を普通に compile した
    もの。param 配置は per-fn の web 集合構成で決まり、原文の inline accessor 多用が我々の
    open-coded 再構成と key 構成を変えている。
  - 次: OFOD-CAE transplant matrix で param-class flip 条件を最小化 → OnKartHit I3 形に適用。
    当たれば prefix index 0 が落ち Phase 3 gate 再オープン。
