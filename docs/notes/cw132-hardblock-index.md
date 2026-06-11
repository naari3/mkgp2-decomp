# CW 1.3.2 既知パターン索引 (hardblock / recipe / 未決)

目的: subagent / main が objdiff で壁に当たったとき、**症状から既知パターンを引き、6 サイクル
焼く前に「即 park (出典付き)」「この recipe を試す」「cheap probe 後 park」を即決**できるようにする
一枚索引。詳細は各ノートへ。新パターンを確定したらここに 1 行追加し、該当ノートへリンクすること。

規律: verdict は各ノートの結論に忠実に。根本原因の「観察(事実)/仮説」区別を保つ。verdict が後で
覆ったら行を消さず「訂正」を追記。**この索引は当時の結論の要約** — 行動前に出典ノートで最新を確認。

使い方 (subagent):
1. objdiff 残差が出たら、まず **A/B/C** を症状で引く。
2. **A 群 (即 park)** に症状一致 → 追加サイクルを焼かず asm_fn 退避。HANDOFF notes に該当 pattern 名と
   出典を書く (例: `park: register-identity-gpr-partition, see cw132-allocator-phase2f-research.md`)。
3. **B 群 (recipe あり)** に一致 → park せず recipe を試す。
4. **C 群 (未決)** に一致 → cheap probe 1 回だけ試し、駄目なら park。深堀りは main 指示時のみ。
5. どれにも当たらない新規症状 → 通常の撤退判定 (6 サイクル/diff 停滞) に従い、park 時に症状を
   HANDOFF に残す (新パターン候補として後で索引化)。

---

## A 群: 即 park 可 (source 非制御が実証済み)

命令列・shape は一致するのに source からは到達できないと実証されたもの。サイクルを焼かず退避。

| pattern | 症状 (objdiff で見えるもの) | 根本原因 | 出典 |
|---|---|---|---|
| **register-identity-gpr-partition** | 命令列・shape 完全一致、callee-saved GPR が target と別レジスタ (特に param が target で最下位/top に来る)。reg-mask すると diff 消滅 | 観察+frida実測: colorer は web-birth key 降順で着色、**param web の key は hard-pin** (最小 key + 最大 degree → 最下位)。local 短命化・宣言順・degree 操作いずれも key を動かせない。※param-top の到達可否そのものは厳密には未決 (閉は撤回) だが、reg-only 残差は実務上 park 対象 | [cw132-allocator-phase2f-research.md](cw132-allocator-phase2f-research.md), [approachA-roadmap.md](approachA-roadmap.md) Phase 2e Part2 (handled/obj pair-share), Phase 2f |
| **fp-numbering-partition (named-temp pipeline)** | float の load/store 順が target と mirror (target 降順 f7..f0、source 昇順)、内容差なし、87-99% で park | 観察: Global Optimizer の web coloring は **first-USE (store) 順**で決まり、def/decl order・pragma・-opt 全軸で不変 (132-probe closed)。CSE'd multi-use const web も別経路で色付け。※const TOP-LEVEL pointer param を src にした direct-copy のみ降順誘発可 → その場合は B 群へ | [cw132-fpnumbering-phase2a-research.md](cw132-fpnumbering-phase2a-research.md), [-validation](cw132-fpnumbering-phase2a-validation.md), [cw132-fp-decl-order-regalloc.md](cw132-fp-decl-order-regalloc.md) |
| **vn-fold (定数0/bool 統合)** | target は 64bit `(flags&MASK)!=0` 比較で `li rBool,0` 1個を `and`/`xor` の 0 源に兼用 (callee-saved bool 常駐 block)、分岐 `bne;b`。source は `li 0` が 2個 (bool用 + 比較用) + 分岐 `beq` | 機構: fold = ValueNumbering の operand 置換で、対象は **copy-backed 代表を持つ web のみ**。bool-init/比較-0 は別々の immediate `li 0` 定義で copy リンクされず統合されない。最小ケース全滅 / 7000中2関数 / C・C++不問 / `!=bool` 否定 | [cw132-allocator-phase2f-research.md](cw132-allocator-phase2f-research.md) (VN 節) |
| **chain-variant-li-deletion** | `if(x==K1)…; if(x==K2)…` の int-equality chain で一部 `li 0` が削除される期待に反し残る | 観察: chain 変種は u64 class-1 family と違い **zero web が非 coalesce**、source から zero coalesce を再現できない (4 probe negative) | [cw132-phase2e-research.md](cw132-phase2e-research.md) |
| **new-expr-r0-join (guarded ctor)** | guarded-ctor site の target が `mr. r0,r3` join、C は全 spelling で r3 join に copy-prop → **構造的 -1 命令** (サイズ不一致、in-place park も不可) | 仮説: C++ new-expression compiler temp 由来の言語機構ギャップ (adjustor thunk と同種)、C 到達不能の可能性大 | [cw132-carobject-init-park.md](cw132-carobject-init-park.md) |
| **exceptions-on-eh-scaffolding** | `bl __unexpected` island / full EH prologue (`mr r31,r1`, back-chain epilogue, EH state store) が target に存在 | 観察: approach B (`#pragma exceptions off`) でも C source で complete EH scaffolding を再現できない。解放は TU-level (approach A 先頭から連続 or .cpp 化) | [exceptions-on-eh-scaffolding-unpromotable.md](exceptions-on-eh-scaffolding-unpromotable.md), [approachA-roadmap.md](approachA-roadmap.md) Phase 4 |

検出: 「reg-mask すると diff が消える」「命令数一致で 1-2 レジスタだけ違う」「`bl __unexpected` を grep」
「guarded-ctor で -1 命令」が A 群の一次シグナル。

---

## B 群: 条件付きで通る recipe あり (park 前に試せ)

| pattern | 症状 | recipe 要点 | 出典 |
|---|---|---|---|
| **bne-b-invert (class-1 u64 flag→bool)** | `or. r0,rA,r0; bne L1; b L2; L1: li rD,1; L2:` が欲しいのに CW が 1 命令短い `beq L2; li 1; L2:` を出す | u8 bool で `if ((d->flags & MASK_ULL) == 0) b=0; else b=1;` (then=0/else=1 arm 順) か ternary `((f&m)==0)?0:1`。13/13 site byte-exact | [cw132-class1-solved-probe-matrix.md](cw132-class1-solved-probe-matrix.md), [approachA-roadmap.md](approachA-roadmap.md) Phase0 |
| **dead-counter-ctr-loop** | ctr loop の up-counter init (`li r,0`)/`mr` が DCE される (target には残る) | counter を **無視される追加 arg** として渡し invisible use 化 (K&R empty-paren extern, `IsActive(guard, i)`)、or return-coalesce path | [cw132-dead-counter-ctr-loop-hardblock.md](cw132-dead-counter-ctr-loop-hardblock.md), [cw132-phase2e-research.md](cw132-phase2e-research.md) |
| **duplicate-literal-equality-dead-block** | 同一リテラル K の二重 guard で `cmpwi…bne;li0;blr` の 12 byte 死コードが残る | source に重複 guard を**明示的に保つ** (`if(x==K)…; if(x==K)…`) | [cw132-duplicate-literal-equality-dead-block.md](cw132-duplicate-literal-equality-dead-block.md) |
| **bool-oob (== 1 の 3 命令展開)** | u8 flag の `if(oob==1)` が `clrlwi;cmplwi r0,1;beqlr` の 3 命令 (`if(oob)` は 2 命令) | u8-typed local に明示的に `== 1` と書く (不等値/直接条件分岐では出ない) | [cw132-bool-oob-pattern.md](cw132-bool-oob-pattern.md) |
| **class-2-frsp-store-forward** | matrix 等の loop copy で store→load forwarding の frsp/reload partition が target と合わない | copy を **variable-index for-loop** で書く (`for(i…) s.m[i]=t[i];`、plain struct)、read 側は const-index named local。`-O3` 以上 (unroll 必須) | [cw132-class2-validation.md](cw132-class2-validation.md), [cw132-class2-expansion.md](cw132-class2-expansion.md), [cw132-frsp-storeforward-phase2b-research.md](cw132-frsp-storeforward-phase2b-research.md) |
| **mr-sr-init-static-inline** | dual-induction loop の init `mr` が standalone では `li` に fold、target には `mr` 残存 | dual-induction loop を `static inline` helper に wrap (prod flags で非 emit = layout 安全)。helper local の宣言順で GPR coloring 制御 | [cw132-mrsrinit-phase2c-research.md](cw132-mrsrinit-phase2c-research.md) |
| **scopedtimer-pair-swap** | dtor tail の ticks→µs 変換で `subi`/`lwz` の順が target と swap | 変換を**整数 temp 無しの単一式**で書く (named int temp が式を 2 tree に割る)。113 canonical dtor site に適用可 | [cw132-scopedtimer-phase2d-research.md](cw132-scopedtimer-phase2d-research.md), [cpp-scoped-timer-pattern.md](cpp-scoped-timer-pattern.md) |
| **approachB-exceptions-off-late-web** | approach B (`#pragma exceptions off`) の extab fn で callee-saved reg が 1 個だけ違う (100% shape) | approach B を避け **approach A (exceptions-on auto-extab)** に切替。fn が exceptions-on で compile されている前提に合わせる | [approachB-exceptions-off-regalloc-hardblock.md](approachB-exceptions-off-regalloc-hardblock.md) |

---

## C 群: 未決 (cheap probe → park、深堀りは main 指示時のみ)

| pattern | 症状 | 状態 | 出典 |
|---|---|---|---|
| **prologue-load-hoist** | wrapper/thunk の prologue で member load が LR-save より上、source 再現不可 | compare-consuming-the-load がある wrapper は matched、無い場合は未再現。cheap probe 1 回後 skip 推奨 | [cw132-prologue-load-hoist-unreproduced.md](cw132-prologue-load-hoist-unreproduced.md) |
| **mtx-loop-o2-o4-silhouette** | 4x4 matrix multiply/copy loop が O2 形 silhouette + O4 late backend 混在 (SR 無し/k+=4 unmerged/dead i `mr`)。**14+ fn 共通** (MtxConcat 系 header-inline helper 推定) | prod flags (`-O4,p`) では毎回 SR+merge+i削除を emit。source lever 未発見。最重要未解決 idiom | [cw132-phase2e-research.md](cw132-phase2e-research.md) |
| **fp-numbering two-tier** | 同 fn 内で long-range callee-saved FP web (宣言順 r31降順) と short-range scratch (first-use 昇順) が別 regime で着色 | 仮説段階 (phase2f)。binary-level allocator の web-birth key per-pass 観測が要る | [cw132-fpnumbering-phase2a-research.md](cw132-fpnumbering-phase2a-research.md), [cw132-allocator-phase2f-research.md](cw132-allocator-phase2f-research.md) |

---

## D 群: positive batch-idioms (family 別 recipe ポインタ)

「通せる」recipe 集。担当 fn が下記 family に該当しそうなら、まず該当ノートの idiom を当てる。
(各ノートに複数 idiom。ここは入口のみ)

| family / 症状 | 主な idiom | 出典 |
|---|---|---|
| ItemEffect select/dispatch、table scan | param-reg reuse for derived ptr / mtctr-bdnz scan / decl-position LIFO reg reuse / subf 等値 | [cw132-itemeffect-batch-idioms.md](cw132-itemeffect-batch-idioms.md) |
| OnApply 系、Vec3 out-param、float arg | Vec3 z,y,x load-order / K&R unprototyped float arg (単一 lfs) / ApplyFn hook ABI | [cw132-onapplyrun-batch-idioms.md](cw132-onapplyrun-batch-idioms.md) |
| EffectsRun、ctr scan w/ live counter、struct copy、sqrt | live-counter ctr scan / 12B Vec3 word-copy / 8B pair tail copy / MSL inline sqrtf / fp pool statement-order / anti-fmadds sum | [cw132-effectsrun-batch-idioms.md](cw132-effectsrun-batch-idioms.md) |
| STL list final、lerp lane、deleting dtor、(float)int | (float)int 0x4330 magic / fuse-first-addend lerp / owned-ptr deleting dtor / vtable-demote dtor | [cw132-stllistfinal-batch-idioms.md](cw132-stllistfinal-batch-idioms.md) |
| StrPcbRun、assignment-chain、sda21 singleton、volatile Vec3 | assignment-chain coalesce (`q->f = i = 0`) / sda21 GetInstance fold / volatile Vec3 DSE retention / SR lane walk / callee-saved decl-order | [cw132-strpcbrun-batch-idioms.md](cw132-strpcbrun-batch-idioms.md) |
| SweepBitset、volatile proxy pair、nested inline dtor、SetBit | volatile-field proxy pair / triple addic guard chain / SetBit decl-order / Vec3 copy+fill statement order | [cw132-sweepbitset-batch-idioms.md](cw132-sweepbitset-batch-idioms.md) |
| TwoLane、jumptable switch、callee-saved chase | jumptable switch (source order) / cmpwi-0-first 2-case / shared-li (comma-&&) / fp temp pair swap / callee-saved chase 3-step / re-test idiom / same-TU asm_fn signature retype | [cw132-twolane-batch-idioms.md](cw132-twolane-batch-idioms.md) |
| class-1 bool materialization | `(d->flags & MASK_ULL)==0` then/else arm swap or ternary | [cw132-class1-solved-probe-matrix.md](cw132-class1-solved-probe-matrix.md) |
| ScopedTimer ctor/dtor (C++) | one volatile member → wholesale memory-stay / ctor store order | [cpp-scoped-timer-pattern.md](cpp-scoped-timer-pattern.md) |
| sdata-resident singleton deleting dtor | global load 直接 r31 / inner local declare で mr スキップ | [sdata-deleting-dtor-idiom.md](sdata-deleting-dtor-idiom.md) |

**再利用頻度の高い汎用 lever** (family 問わず効きやすい):
- **decl-order LIFO register reuse**: callee-saved local は **後で宣言した方が後で freed したレジスタを取る**。
  target の register 順を読んで逆順に declare すると合わせやすい (stmw fn 全般)。
- **K&R unprototyped extern + float arg**: prototype 無し extern に float を渡すと単一 `lfs` (frsp/double penalty 無し)。
- **same-TU asm_fn signature retype**: promoted C から同 TU の asm_fn を呼ぶとき、asm body はそのままで
  signature だけ in-place で書き換える。

---

## compiler を直接追う必要が出たら

A/C 群の根拠を作る/疑うときは frida + Ghidra で mwcc 内部を実行時 trace できる。手順・ツール・
module map は [cw132-compiler-tracing-playbook.md](cw132-compiler-tracing-playbook.md)。
**これは main 主導の研究活動** — subagent の per-fn ループには組み込まない (frida 起動は重く priv copy + Ghidra 常駐が要る)。
