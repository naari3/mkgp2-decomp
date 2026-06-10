# CW 1.3.2 scheduling/allocation idioms unreproduced in the smallrun batch (2026-06-10, batch_promote_8004efd8_smallrun)

CW 1.3.2 (game lib flags) never schedules a pointer load above the prologue LR-save store (`stw r0, 0x14(r1)`) nor above any store (no alias disambiguation).

Target fns exist with BOTH shapes for near-identical wrapper sources:
- `CarObject_ResetPhysics`: stw-then-lwz, matched.
- `KartItem_AdvanceAnim3c` 0x8004EFD8 / `KartItem_GetCurrentSpeedWithBonus` 0x8004F0F8: lwz-then-stw, unreproduced after probes (local arg, register local, static-inline getter arg, unprototyped callee, exceptions on - all copy-propagate to identical IR).

Known matched fns with the hoisted shape (AI_GetItemType, AI_GetLapDifference) all have a compare consuming the load, i.e. latency-driven hoist; wrapper-with-no-compare + hoisted load remains an open scheduling idiom. 0x8004F0F8 additionally shows left-to-right arg emission (lwz then li) vs CW right-to-left.

Precan rule for wrapper/thunk fns: if the target prologue has a member load (`lwz rX, off(r3)`) ABOVE the `stw r0, 0x14(r1)` LR-save and no compare consumes the load, expect this class; skip after 1 cheap probe.

Related allocator findings from the same batch:

- (a) fp: CW coalesces a dying fdivs divisor into the dest web only when the dest is NOT return-pinned f1; target (`CarObject_CalcSpeedRatio` 0x8004EFFC, best 97.65%) coalesces into the pinned multi-def web.
- (b) GPR: explicit second-induction local (`off = i` in for-init, `off += 8` in for-inc) + condition-assign entry pointer reproduces a dual-induction search loop except the init: source `off = i` const-folds to `li rN,0`; target (`KartItem_GetMaxSpeedWithBonus` 0x8004F040, best 94.35%) has `mr r6,r4` reg-copy init that escaped const-prop.
- (c) 4-instr out-param getter (`KartItem_GetBoostArmedAndTimer` 0x8004F14C): needs lbz->r3 return-coalescing AND the lbz positioned between lfs and stfs; direct form gets the coalesce but the load lands after the store (no load-over-store hoist), named-local form loses the coalesce (r0 + mr) and flips the load order. Mutually exclusive in all forms tried.

Win idioms verified (reuse these):

- condition-assign `i < (e = &mv->table[idx])->count` for per-iteration entry recompute with body CSE of `e`
- compound `scaled = C1 * x; scaled = scaled * (C2 + m->f); return scaled;` to chain a multi-def f1 return web
- `(float)__fabs(a - b)` for fsubs/fabs/frsp
- explicit `int off` second induction (`off = i`, `off += 8`) + byte-offset key read `*(const float *)((const char *)e->pairs + off)` for dual-induction GPR webs (i/mv/off/e all landed on target registers)
