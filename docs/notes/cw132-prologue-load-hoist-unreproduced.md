# CW 1.3.2 scheduling/allocation idioms unreproduced in the smallrun batch (2026-06-10, batch_promote_8004efd8_smallrun)

CW 1.3.2 (game lib flags) never schedules a pointer load above the prologue LR-save store (`stw r0, 0x14(r1)`) nor above any store (no alias disambiguation).

Target fns exist with BOTH shapes for near-identical wrapper sources:
- `CarObject_ResetPhysics`: stw-then-lwz, matched.
- `KartItem_AdvanceAnim3c` 0x8004EFD8 / `KartItem_GetCurrentSpeedWithBonus` 0x8004F0F8: lwz-then-stw, unreproduced after probes (local arg, register local, static-inline getter arg, unprototyped callee, exceptions on - all copy-propagate to identical IR).

Known matched fns with the hoisted shape (AI_GetItemType, AI_GetLapDifference) all have a compare consuming the load, i.e. latency-driven hoist; wrapper-with-no-compare + hoisted load remains an open scheduling idiom. 0x8004F0F8 additionally shows left-to-right arg emission (lwz then li) vs CW right-to-left.

Precan rule for wrapper/thunk fns: if the target prologue has a member load (`lwz rX, off(r3)`) ABOVE the `stw r0, 0x14(r1)` LR-save and no compare consumes the load, expect this class; skip after 1 cheap probe.

Related allocator findings from the same batch:

- (a) fp: CW coalesces a dying fdivs divisor into the dest web only when the dest is NOT return-pinned f1; target (`CarObject_CalcSpeedRatio` 0x8004EFFC, best 97.65%) coalesces into the pinned multi-def web. **解決 (2026-06-12)**: FP colorer (FUN_00507a30, lowest-available) を白箱化。別 web の divisor は result(pinned f1)と interfere → f0。**in-place 除算** (`r = mv->...refSpeed; r = speed / r;`) で divisor を return 変数に load すれば被演算子 web と result web が単一化し `fdivs f1,f2,f1`。byte-identical promote 済。詳細 [cw132-fdivs-coalesce-pinned-f1.md](cw132-fdivs-coalesce-pinned-f1.md)。
- (b) GPR: explicit second-induction local (`off = i` in for-init, `off += 8` in for-inc) + condition-assign entry pointer reproduces a dual-induction search loop except the init: source `off = i` const-folds to `li rN,0`; target (`KartItem_GetMaxSpeedWithBonus` 0x8004F040, best 94.35%) has `mr r6,r4` reg-copy init that escaped const-prop.
- (c) 4-instr out-param getter (`KartItem_GetBoostArmedAndTimer` 0x8004F14C): needs lbz->r3 return-coalescing AND the lbz positioned between lfs and stfs; direct form gets the coalesce but the load lands after the store (no load-over-store hoist), named-local form loses the coalesce (r0 + mr) and flips the load order. ~~Mutually exclusive in all forms tried.~~ **訂正 (2026-06-12): 解決済。両立は可能だった。**この sweep は volatile **store** は試したが、float read を `*(volatile float*)&self->boostTimer` で pin する volatile **read** を欠いていた。load-first source (store を最後に回す aliasing エッジ) + volatile-read pin (lfs を byte-load より先に emit) の組合せで EXACT 一致。byte-identical promote 済 (`main.dol: OK`)。機構は [cw132-scheduler-store-load.md](cw132-scheduler-store-load.md)。

## 2026-06-12: scheduler trace — leaf の volatile-pin レバーは forwarder に転用不可 (観察)

leaf store/return-read を crack した volatile-read pin レバーが forwarder の prologue-load-hoist に効くか検証 → **効かない** (`tmp/getcur/fwdsweep.py`)。volatile-pin arg / vol-self / named / reg / compare-consuming (double-use) 全て naive (`stw r0,0x14(r1)` が `lwz r3,0x3c(r3)` より先) のまま。

`tmp_probe/probe_sched_ops.js` で `KartItem_AdvanceAnim3c` の naive 形をスケジューラ trace:
- pre/post-coloring の両 run で 4 node が**厳密な線形依存チェーン** (各 node の pred = 直前 node、cycle 毎に eligible は 1 つだけ)。tie-break の自由度ゼロ。
- つまり LR-save store (`stw r0,0x14(r1)`) と member load (`lwz r3,0x3c(r3)`) の順は tie-break ではなく**依存エッジ**で固定。これは line 3 の「no alias disambiguation: load を store より上に上げない」と整合 (CW は r1-stack store を後続 load の memory barrier 扱い)。

**機構的差 (仮説):** leaf の volatile-pin は「同一 cycle で ready な独立 2 node」(lfs vs lbz) の emission 順を変えるレバー。forwarder は store→load の**保守的エッジ**そのものが障害で、pin では**エッジを消せない**。hoist 済 target (AI_GetItemType 等) は compare-driven の別 codegen 経路で生じると推測。forwarder を crack するには「LR-save store→member load の保守的エッジを除く / load の priority でエッジを跨ぐ」レバーが要るが未発見。volatile-pin family では到達不能。詳細機構: [cw132-scheduler-store-load.md](cw132-scheduler-store-load.md) §3-4 (エッジ vs tie-break の区別)。

Win idioms verified (reuse these):

- condition-assign `i < (e = &mv->table[idx])->count` for per-iteration entry recompute with body CSE of `e`
- compound `scaled = C1 * x; scaled = scaled * (C2 + m->f); return scaled;` to chain a multi-def f1 return web
- `(float)__fabs(a - b)` for fsubs/fabs/frsp
- explicit `int off` second induction (`off = i`, `off += 8`) + byte-offset key read `*(const float *)((const char *)e->pairs + off)` for dual-induction GPR webs (i/mv/off/e all landed on target registers)
