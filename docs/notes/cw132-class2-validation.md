# CW 1.3.2 class-2 loop-copy recipe: in-TU validation (2026-06-11, batch_promote_class2_validation)

Phase 2b SOLVED recipe (docs/notes/cw132-frsp-storeforward-phase2b-research.md) applied to the
two real class-2 sites in src/game/auto_ONKARTHIT_block.c: ItemEffect_Dispatch 0x80050410
(canonical specimen, 86.34% draft) and KartItem_ApplyImpactImpulseAndRumble 0x8004B49C (83.66%
draft). Neither reached 100%; the class-2 mechanism itself is now REPRODUCED byte-exact or
near-exact in both, and the remaining residue in both fns is the documented source-closed
fp-register-identity tie-break family, NOT class 2. Best states: Dispatch 86.34% -> 97.07%
(7 builds), ApplyImpactImpulse 83.66% -> 94.24% (6 builds). Both reverted to asm_fn,
SHA-1 green. Paste-ready C in the batch HANDOFF appendix
(docs/drafts/Class2_validation_nearmatches.handoff.md).

## Observations (facts, build-by-build)

### ItemEffect_Dispatch (target partition: 5 frsp + 1 real reload on m2)

1. f35 recipe verbatim (plain struct, for-loop copy, named dir0-2/dx-dz, separate dot temps):
   95.06%, 340/340 instructions. The frsp web family came back exactly as the research note
   predicted: f30/f31 saves, frame 0x80->0xa0, fctiwz slot 0x60, prologue/epilogue all
   self-corrected (draft residues (a),(b),(d) gone). Generated 6 frsp + 0 reloads vs target
   5 frsp + 1 reload (m2).
2. Permuting the consume-read source order (dx,dy,dir0,dir1,dz,dir2): output byte-identical
   to build 1. Pure decl/read reordering of independent plain reads is DAG-canonicalized.
   The research note's "consume read order is a lever" hypothesis is FALSIFIED for plain
   reorderings (but see 5: order matters once a volatile read splits the DAG).
3. `dir2 = *(volatile float *)&s.mtx[2];` (volatile-cast read of just that slot) REPRODUCES
   the target partition exactly: raw stfs to 0x28(r1) + real `lfs fN, 0x28(r1)` reload, m2's
   raw register freed early (taken by the posZ load), 5 frsp on the others. This is a
   reliable, slot-precise lever for the reload mode.
4. Named `ref` local for the strPcb speed clamp (`sp = K * mov->speed; ref = tbl.refSpeed;
   if (sp > ref) sp = ref;`) fixed the sp/ref f0/f1 swap - the CarObject_OnItemHit spd/ref
   idiom transfers.
5. dy-computed-before-dx source order (with the volatile dir2 read present) changed the
   schedule substantially and gave the best state 97.07%: load order, frsp order (m12 first),
   fsubs order (dy first) all matched target. Note contrast with (2).
6. Unnamed dir0/dir1 (consume via `t0 = dx * s.mtx[0];` CSE'd with `s.dir[0] = s.mtx[0];`):
   dir webs flip from ascending f10/f11 to DESCENDING f3/f2 - target's direction (f4/f3),
   off by one. Schedule half regressed in that build (dx-first); combining with dy-first
   (build 7) recovered the schedule (register-only diffs through the first half) at 94.79%.
7. Final residue at best state: (a) named dx/dy pair: CW assigns first-def->scratch(f13) /
   second-def->f31 in BOTH source orders; target has first-def dy=f31, dx=f5 - the mirror is
   source-closed across the orderings probed. (b) dir-web numbering off-by-one (f3/f2 vs
   f4/f3) and reload register f12 vs f2. All content/offsets/opcodes match.

### KartItem_ApplyImpactImpulseAndRumble (target partition: 3 frsp, no in-block reload)

1. Recipe + plain struct + volatile-CAST accesses (VF macro) for all post-copy scratch
   traffic: 88.08% on first build (from 83.66%). Copy block structurally exact: 3 frsp on
   m12/m13/m14 (the only in-block consumes), raw d stores, no reload - consistent with the
   partition model (m0/m1/m2 are consumed post-call only). The in-place MSL sqrtf slot works
   with a volatile-CAST member (`*(volatile float *)&s.sqD`), volatile struct not needed.
2. Post-call reads must be PLAIN, not volatile: dead registers already force real reloads,
   and volatile pinning wrecks the schedule and the accumulator numbering. Switching the
   block-B dot to plain reads + single-def chain temps (dotA/dotB/dot) made block B
   byte-exact (chain lands f0/f0/f1 like target).
3. Block-A dx/dy/dz UNNAMED via store + read-back (`s.d[0] = x - s.m[12];
   p0 = s.d[0] * s.d[0];`): the read-backs forward RAW onto the fsubs results (probe-f32
   behavior holds in-TU) and the unnamed webs number DESCENDING f6/f5/f3 = target exactly.
   BLOCK A BYTE-EXACT. (Named dx/dy/dz had given ascending f11/f12/f13.)
4. rumble/dist kept-copy fmr (draft residual (d)) SOLVED: compare the COPY TARGET, not the
   source - `rumble = K - dist; dist = rumble; if (dist < 0) dist = vol_1.0f;`. Copy-prop
   rewrites the compare back to rumble's register, which extends rumble across the copy and
   blocks coalescing -> `fsubs f1; fmr f31,f1; fcmpo f1` as in target. Verified at both
   sites (second site needs a fresh name rumble2 to keep the webs separate).
5. Named `sum` temp for the dist accumulation picks the dying second operand's register
   (f1) like target; the unnamed two-def `dist` chain had picked the first's (f2).
6. Final residue at best state 94.24%: (a) block-E v-trio: target loads d0,d1 with regs
   f1,f0 and products coalesce in-place; named reads give source-def-order ascending regs
   (first->f0, both orders probed), unnamed product-folded reads give the right load order
   and read regs but the named product webs then take f2,f1,f0 instead of coalescing. ~25
   cascade rows (tA/tB dead-store drift, k-const placement). (b) bus/zero GPR pair r4/r5
   mirror (draft's documented negative, reconfirmed). Class-1 site itself still byte-exact.

## Hypotheses / model updates

- The class-2 recipe core is CONFIRMED TRANSFERABLE: loop copy + plain struct restores the
  frsp web, the 22+ dead stores at exact offsets, the frame/callee-saved cascade, in real
  TU pressure, in both fns. The frsp-vs-reload partition is per-slot controllable
  (volatile-cast read = reload mode). What the recipe does NOT control is fp register
  IDENTITY of the consume webs - that falls into the known fp-numbering tie-break family
  (named = source-def-order ascending; unnamed/FE = descending; in-place reuse only via
  web continuation), and both fns ended parked on exactly that family.
- Access discipline derived (likely generalizes to the other class-2 fns):
  (a) in-block consumes: plain reads (frsp) or volatile-cast (reload), per target partition;
  (b) post-call scratch reads: plain; (c) same-BB read-after-write of non-loop slots:
  read-back form (raw forward + descending unnamed webs); (d) dead-store slots and in-place
  sqrtf slots: volatile-cast member stores/reads.
- Outlook for KartItem_OnKartHit / KartItem_Tick / ItemEffect_Trap / Projectile: the class-2
  block itself should reproduce in 1-2 builds with the recipe + partition lever. Whether each
  fn reaches 100% depends on its OTHER webs hitting the same register-identity tie-breaks;
  given 2/2 fns here parked at 94-97% on that family, expect high-90s parks rather than
  matches unless the fn's consume webs happen to be unnamed-shaped. Precan: mark which slots
  reload (real lfs from the scratch frame inside the block) vs frsp before writing C.
