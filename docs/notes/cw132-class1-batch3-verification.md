# Class-1 recipe: batch-3 verification (2026-06-11, batch_promote_phase1_class1batch3)

Target fns: KartItem_TickStatusEffectsByFlag 0x80050CF0 (7 class-1 sites, the TU max) and KartItem_Tick 0x8004BAAC (1 site). Neither fn promoted (both parked on documented NON-class-1 hard-block families), but the class-1 recipe itself verified at ALL 8 sites - the recipe ledger is now 13/13 u64-family sites byte-exact across 3 batches.

## Site-by-site recipe results (TickStatusEffectsByFlag, all u64 family per precan)

| # | mask | zero half | form that matched | result |
|---|---|---|---|---|
| 1 | 0x0000000000200000ULL | hi | ternary `b = ((fl & M) == 0) ? 0 : 1;` over named u64 local | byte-exact (see idiom 1; plain if/else recipe did NOT coalesce here - first observed coalesce failure) |
| 2 | 0x4000000000000000ULL | lo | if/else recipe over the same named u64 local `fl` | byte-exact (CSE-reuse of site-1 flag halves) |
| 3 | 0x0000000000000008ULL | hi | if/else recipe, direct `bus->flags` | byte-exact |
| 4 | 0x0000100000000000ULL | lo | same | byte-exact |
| 5 | 0x0002000000000000ULL | lo | same | byte-exact |
| 6 | 0x2000000000000000ULL | lo | same | byte-exact |
| 7 | 0x1000000000000000ULL | lo | same | byte-exact |

KartItem_Tick site (0x8004C26C): u64 family confirmed (and/and/xor/xor/or. on bus+0x10, mask 0x30ULL, hi zero) - recipe-applicable, NOT tested in-fn (fn parked on class 2, below).

## New verified idioms

1. **Named u64 local for CSE'd adjacent flag tests**: when TWO class-1 sites test the same flags load back-to-back (site 2 nested under site 1), target keeps the halves in r5:r6 reusing the dead drv/owner scratch regs. Direct `bus->flags` x2 reproduces the CSE but mis-colors the whole prologue scratch region AND the site-1 bool refuses to coalesce in if/else form (li r0,0 arm survives). Fix that lands everything: `unsigned long long fl = bus->flags;` block-local + ternary recipe form for site 1 + if/else recipe form for site 2, both over `fl`. The u64 local takes the r5:r6 pair and the entire integer region goes byte-exact.
2. **`#pragma dont_inline on` for same-TU upstream callees**: a promoted fn placed AFTER a small matched fn it calls (ItemEffect_SelectAndDispatch_Wrap, defined earlier in file = earlier address) gets the callee auto-inlined at -O4. `#pragma dont_inline on` / `reset` around the promoted fn stops it. **`#pragma auto_inline off` does NOT stop it** (negative probe). Matched callers BEFORE the callee's definition never inline (CW only inlines already-seen bodies) - that is why this never bit earlier promotes.
3. **Volatile-cast const reload in a speculated else arm** (batch-1 ShadowBB idiom, 2nd confirmation): forces the fresh lfs where CW would CSE with the earlier fcmpo load and bridge with fmr.
4. **Param-register-reuse via variable reassignment** (itemeffect idiom 1 transfer): `ow` holds effectObj (r30) for the Tornado calls, then `ow = self->owner;` reuses r30 exactly like target.

## fn 1 park: fp-scratch tie-break (ItemEffect_Explosion family, new data point)

Final residue: 23 instructions in the color-pulse block, instruction content 100% identical, fp scratch register PERMUTATION only. Target numbers the 3 const/temp web clusters bottom-up (later-first-use -> lower reg); CW emits the top-down permutation. 8 negative probes: named const hoists (copy-propagated), volatile-cast load, assignment-in-expression, addend-first fmadds spelling, compound +=, fn-top vs block decl scoping, static inline wrap helper, prototyped vs K&R float callees (byte-neutral), exceptions on/off (identical -> NOT approach-B class). Strongest new observation: the IDENTICAL source shape (`a = a + C; if (a > C2) a = a - C2;`) produced target-style bottom-up numbering at one site (matched) but top-down at the other - the flip correlates with a multi-block const web coexisting with downstream same-block fp code. Allocator-internal; no source lever found.

Paste-ready C (>99% by content, fp renames only) at docs/drafts/KartItem_TickStatusEffectsByFlag_99pct.handoff.md. Prereqs: retype lbl_806D27B4/B8/BC/C0/C4 + lbl_806D2768 -> const float; fn_802DCA04 -> float(void); fn_8027E9E8 -> double(double).

## fn 2 park: KartItem_Tick 0x8004BAAC precan (0 probes, classes already closed)

- **class 2 frsp store-forward**: entry block loads f30/f29/f28 = movement velocity vec (callee-saved, also dead-stored to sp+0x20..0x28) AND makes frsp scratch copies for the magnitude sum - frsp of lfs-loaded singles with both versions live = the 6-probe-negative ItemEffect_Dispatch shape. Park per standing rule.
- The big sp+0x2c..0x68 block is 4x4 identity init + view-matrix copy with double-overwrite stores (volatile scratch struct family, solvable); the two other frsp are reachable idioms (in-place sqrtf, (float)__fabs) - the fn is ~95% reachable EXCEPT the frsp trio.
- No ctr loops, no bl __unexpected, no FP-prologue, no ScopedTimer, no symbol+const table walk. 1 class-1 site (u64, mask 0x30ULL).
- Unlock path: solving class 2 self-corrects this fn; recommend bundling with ItemEffect_Dispatch (86% draft) in any future class-2 research batch.
