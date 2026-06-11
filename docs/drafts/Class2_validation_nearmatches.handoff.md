# HANDOFF batch_promote_class2_validation

Class-2 (frsp store-forward interleave) loop-copy recipe in-TU validation on the two
draft fns. **Recipe core verified on both** - every class-2 symptom (missing frsp webs,
DSE'd copy block, frame/callee-saved cascade) is reproduced by the recipe under real TU
pressure, and the frsp/reload partition turned out to be per-slot controllable. Neither
fn reached byte-identical: both park on fp/GPR **register-identity tie-breaks** (the
documented source-closed fp-numbering family), with content/offsets/opcodes fully
matching in the affected regions. asm bodies restored, build green.

## Trial matrix

### ItemEffect_Dispatch 0x80050410 (target: 5 frsp + 1 reload(m2)) - 7 builds

| build | change | % | finding |
|---|---|---|---|
| 1 | f35 recipe verbatim | 95.06 | frsp web + frame cascade restored; 6 frsp / 0 reload |
| 2 | consume-read reorder (plain) | 95.05 | byte-identical to b1 - plain read order is canonicalized (lever falsified) |
| 3 | dir2 read store-pinned + spd/ref clamp pair | 95.09 | clamp fixed (OnItemHit idiom transfers); dir2 wrongly into f30 |
| 4 | dir2 via volatile-cast read | 93.74 | **partition reproduced: 5 frsp + real lfs 0x28 reload** |
| 5 | + dy-before-dx | **97.07** | schedule matches; residue = register identity only |
| 6 | unnamed dir0/dir1 (CSE w/ dir stores) | 93.70 | dir webs flip to descending (target direction), schedule regressed |
| 7 | b6 + dy-first | 94.79 | first-half schedule register-for-register; dx/dy scratch-vs-f31 mirror persists both orders |

### KartItem_ApplyImpactImpulseAndRumble 0x8004B49C (target: 3 frsp, no in-block reload) - 6 builds

| build | change | % | finding |
|---|---|---|---|
| 1 | recipe + volatile-cast (VF) all post-copy traffic | 88.08 | copy block structurally exact incl. 3-frsp partition; volatile-cast sqrtf slot works |
| 2 | named sum; rumble compare-on-copy-target; rumble2 | 88.61 | **fmr coalesce solved both sites**; sum tie-break fixed |
| 3 | block-B reads plain + dotA/dotB chain | 91.16 | block B byte-exact - post-call reads must be plain |
| 4 | block-A dx/dy/dz unnamed read-back form; block-C plain | 93.91 | **block A byte-exact** (descending f6/f5/f3); C order fixed |
| 5 | v-trio plain, v1-first | 94.23 | v regs right, load order wrong (named = source-def ascending) |
| 6 | v-trio product-folded reads | **94.24** | load order + read regs right; product webs rotate f2/f1/f0 vs in-place f1/f0/f2 |

Residual diff rows at best: Dispatch 53 (all fp reg identity + cascade), ApplyImpactImpulse 46
(v-trio rotation cascade ~34 + bus/zero GPR mirror 12).

## Recipe addendum (transfers to OnKartHit / Tick / Trap / Projectile)

1. Copy block: `for (i = 0; i < 16; i++) s.m[i] = t[i];`, plain struct - confirmed in-TU, both fns.
2. Partition lever: slots the target RELOADS (real lfs from the scratch frame inside the block)
   -> read via `*(volatile float *)&s.m[k]`; frsp slots -> plain reads. Precan the partition
   from the target asm before writing C.
3. Post-call scratch reads: plain (volatile pins the schedule and misnumbers webs).
4. Same-BB read-after-write of non-loop slots: read-back form `s.d[0] = expr; use s.d[0]`
   (raw forward + descending unnamed webs).
5. Dead-store slots / in-place sqrtf: volatile-cast member stores+reads.
6. Kept-copy fmr: `copy = src; if (copy < K) copy = ...;` - compare the copy target; copy-prop
   re-extends the source web and blocks coalescing.
7. Expect the remaining residue class to be register-identity tie-breaks; park per family rule
   if residue is reg-only after the partition matches.

```json
{
  "batch_id": "batch_promote_class2_validation",
  "sub_summary": "Class-2 loop-copy recipe in-TU validation: recipe core CONFIRMED on both fns (frsp webs, dead stores, frame cascade all reproduce; frsp/reload partition controllable per-slot via volatile-cast read). Neither fn reached 100%: Dispatch 97.07% / ApplyImpactImpulse 94.24%, both parked on the source-closed fp-register-identity tie-break family (NOT class 2). 5 new verified levers + access-discipline addendum recorded; both asm bodies restored, SHA-1 green.",
  "results": [
    {
      "addr": "0x80050410",
      "name": "ItemEffect_Dispatch",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Recipe validation: 86.34% -> 97.07% best over 7 builds (asm_fn restored). Class-2 frsp web fully reproduced by the loop-copy recipe on build 1 (340/340 insns, frame/f30/f31/fctiwz cascade self-corrected). New levers verified: volatile-cast single-slot read reproduces the target 5-frsp+1-reload partition exactly; dy-first compute order fixes the schedule; spd/ref named-pair clamp idiom transfers; unnamed dir reads flip web numbering to descending. Residual is register identity only (named dx/dy scratch-vs-f31 mirror + dir web off-by-one) = source-closed fp-numbering family. Paste-ready 97% C in HANDOFF appendix A. Needs splits.txt .data widen to 0x803F7640 when promoted."
    },
    {
      "addr": "0x8004B49C",
      "name": "KartItem_ApplyImpactImpulseAndRumble",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Recipe validation: 83.66% -> 94.24% best over 6 builds (asm_fn restored). Copy block (3-frsp partition) byte-exact on build 1; blocks A/B/C all byte-exact by build 4 (unnamed read-back dx/dy/dz, plain post-call reads, dotA/dotB chain). Draft residual (d) rumble/dist fmr SOLVED (compare-the-copy-target form, both sites). Residual: block-E v-trio register rotation + bus/zero GPR mirror = allocator tie-break family, not class 2. Class-1 site still byte-exact. Paste-ready 94% C in HANDOFF appendix B."
    }
  ],
  "configure_py": {
    "add_objects": []
  },
  "splits_txt": {
    "add_entries": []
  },
  "symbols_txt": {
    "set_scope": [],
    "set_attr": [],
    "rename": []
  },
  "docs_notes": [
    {
      "path": "docs/notes/cw132-class2-validation.md",
      "content": "# CW 1.3.2 class-2 loop-copy recipe: in-TU validation (2026-06-11, batch_promote_class2_validation)\n\nPhase 2b SOLVED recipe (docs/notes/cw132-frsp-storeforward-phase2b-research.md) applied to the\ntwo real class-2 sites in src/game/auto_ONKARTHIT_block.c: ItemEffect_Dispatch 0x80050410\n(canonical specimen, 86.34% draft) and KartItem_ApplyImpactImpulseAndRumble 0x8004B49C (83.66%\ndraft). Neither reached 100%; the class-2 mechanism itself is now REPRODUCED byte-exact or\nnear-exact in both, and the remaining residue in both fns is the documented source-closed\nfp-register-identity tie-break family, NOT class 2. Best states: Dispatch 86.34% -> 97.07%\n(7 builds), ApplyImpactImpulse 83.66% -> 94.24% (6 builds). Both reverted to asm_fn,\nSHA-1 green. Paste-ready C in the batch HANDOFF appendix.\n\n## Observations (facts, build-by-build)\n\n### ItemEffect_Dispatch (target partition: 5 frsp + 1 real reload on m2)\n\n1. f35 recipe verbatim (plain struct, for-loop copy, named dir0-2/dx-dz, separate dot temps):\n   95.06%, 340/340 instructions. The frsp web family came back exactly as the research note\n   predicted: f30/f31 saves, frame 0x80->0xa0, fctiwz slot 0x60, prologue/epilogue all\n   self-corrected (draft residues (a),(b),(d) gone). Generated 6 frsp + 0 reloads vs target\n   5 frsp + 1 reload (m2).\n2. Permuting the consume-read source order (dx,dy,dir0,dir1,dz,dir2): output byte-identical\n   to build 1. Pure decl/read reordering of independent plain reads is DAG-canonicalized.\n   The research note's \"consume read order is a lever\" hypothesis is FALSIFIED for plain\n   reorderings (but see 5: order matters once a volatile read splits the DAG).\n3. `dir2 = *(volatile float *)&s.mtx[2];` (volatile-cast read of just that slot) REPRODUCES\n   the target partition exactly: raw stfs to 0x28(r1) + real `lfs fN, 0x28(r1)` reload, m2's\n   raw register freed early (taken by the posZ load), 5 frsp on the others. This is a\n   reliable, slot-precise lever for the reload mode.\n4. Named `ref` local for the strPcb speed clamp (`sp = K * mov->speed; ref = tbl.refSpeed;\n   if (sp > ref) sp = ref;`) fixed the sp/ref f0/f1 swap - the CarObject_OnItemHit spd/ref\n   idiom transfers.\n5. dy-computed-before-dx source order (with the volatile dir2 read present) changed the\n   schedule substantially and gave the best state 97.07%: load order, frsp order (m12 first),\n   fsubs order (dy first) all matched target. Note contrast with (2).\n6. Unnamed dir0/dir1 (consume via `t0 = dx * s.mtx[0];` CSE'd with `s.dir[0] = s.mtx[0];`):\n   dir webs flip from ascending f10/f11 to DESCENDING f3/f2 - target's direction (f4/f3),\n   off by one. Schedule half regressed in that build (dx-first); combining with dy-first\n   (build 7) recovered the schedule (register-only diffs through the first half) at 94.79%.\n7. Final residue at best state: (a) named dx/dy pair: CW assigns first-def->scratch(f13) /\n   second-def->f31 in BOTH source orders; target has first-def dy=f31, dx=f5 - the mirror is\n   source-closed across the orderings probed. (b) dir-web numbering off-by-one (f3/f2 vs\n   f4/f3) and reload register f12 vs f2. All content/offsets/opcodes match.\n\n### KartItem_ApplyImpactImpulseAndRumble (target partition: 3 frsp, no in-block reload)\n\n1. Recipe + plain struct + volatile-CAST accesses (VF macro) for all post-copy scratch\n   traffic: 88.08% on first build (from 83.66%). Copy block structurally exact: 3 frsp on\n   m12/m13/m14 (the only in-block consumes), raw d stores, no reload - consistent with the\n   partition model (m0/m1/m2 are consumed post-call only). The in-place MSL sqrtf slot works\n   with a volatile-CAST member (`*(volatile float *)&s.sqD`), volatile struct not needed.\n2. Post-call reads must be PLAIN, not volatile: dead registers already force real reloads,\n   and volatile pinning wrecks the schedule and the accumulator numbering. Switching the\n   block-B dot to plain reads + single-def chain temps (dotA/dotB/dot) made block B\n   byte-exact (chain lands f0/f0/f1 like target).\n3. Block-A dx/dy/dz UNNAMED via store + read-back (`s.d[0] = x - s.m[12];\n   p0 = s.d[0] * s.d[0];`): the read-backs forward RAW onto the fsubs results (probe-f32\n   behavior holds in-TU) and the unnamed webs number DESCENDING f6/f5/f3 = target exactly.\n   BLOCK A BYTE-EXACT. (Named dx/dy/dz had given ascending f11/f12/f13.)\n4. rumble/dist kept-copy fmr (draft residual (d)) SOLVED: compare the COPY TARGET, not the\n   source - `rumble = K - dist; dist = rumble; if (dist < 0) dist = vol_1.0f;`. Copy-prop\n   rewrites the compare back to rumble's register, which extends rumble across the copy and\n   blocks coalescing -> `fsubs f1; fmr f31,f1; fcmpo f1` as in target. Verified at both\n   sites (second site needs a fresh name rumble2 to keep the webs separate).\n5. Named `sum` temp for the dist accumulation picks the dying second operand's register\n   (f1) like target; the unnamed two-def `dist` chain had picked the first's (f2).\n6. Final residue at best state 94.24%: (a) block-E v-trio: target loads d0,d1 with regs\n   f1,f0 and products coalesce in-place; named reads give source-def-order ascending regs\n   (first->f0, both orders probed), unnamed product-folded reads give the right load order\n   and read regs but the named product webs then take f2,f1,f0 instead of coalescing. ~25\n   cascade rows (tA/tB dead-store drift, k-const placement). (b) bus/zero GPR pair r4/r5\n   mirror (draft's documented negative, reconfirmed). Class-1 site itself still byte-exact.\n\n## Hypotheses / model updates\n\n- The class-2 recipe core is CONFIRMED TRANSFERABLE: loop copy + plain struct restores the\n  frsp web, the 22+ dead stores at exact offsets, the frame/callee-saved cascade, in real\n  TU pressure, in both fns. The frsp-vs-reload partition is per-slot controllable\n  (volatile-cast read = reload mode). What the recipe does NOT control is fp register\n  IDENTITY of the consume webs - that falls into the known fp-numbering tie-break family\n  (named = source-def-order ascending; unnamed/FE = descending; in-place reuse only via\n  web continuation), and both fns ended parked on exactly that family.\n- Access discipline derived (likely generalizes to the other class-2 fns):\n  (a) in-block consumes: plain reads (frsp) or volatile-cast (reload), per target partition;\n  (b) post-call scratch reads: plain; (c) same-BB read-after-write of non-loop slots:\n  read-back form (raw forward + descending unnamed webs); (d) dead-store slots and in-place\n  sqrtf slots: volatile-cast member stores/reads.\n- Outlook for KartItem_OnKartHit / KartItem_Tick / ItemEffect_Trap / Projectile: the class-2\n  block itself should reproduce in 1-2 builds with the recipe + partition lever. Whether each\n  fn reaches 100% depends on its OTHER webs hitting the same register-identity tie-breaks;\n  given 2/2 fns here parked at 94-97% on that family, expect high-90s parks rather than\n  matches unless the fn's consume webs happen to be unnamed-shaped. Precan: mark which slots\n  reload (real lfs from the scratch frame inside the block) vs frsp before writing C.\n"
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": null,
  "user_attention": "per_fn_matching_strategy.md sec 14.2: the class-2 row and the ItemEffect_Dispatch row should be updated to point at docs/notes/cw132-class2-validation.md - recipe verdict changes from 'apply recipe, residues self-correct' to 'recipe core reproduces (frsp web/partition/frame); fn-level 100% blocked by the fp-numbering tie-break family in both validated fns (97.07% / 94.24% parks)'. The 4 remaining class-2 fns (OnKartHit/Tick/Trap/Projectile) should be dispatched with the access-discipline addendum and the expectation of high-90s parks."
}
```

## Appendix A: ItemEffect_Dispatch best-state C (97.07%, build 5)

```c
/* ItemEffect_Dispatch 0x80050410 - BEST (build 5, 97.07%). Replaces the volatile
 * scratch block of docs/drafts/ItemEffect_Dispatch_86pct.handoff.md appendix C.
 * Forward decl: void ItemEffect_Dispatch(ItemEffectLaneRun *lane, KartItemOpsView *owner,
 * unsigned char kind, void *effectState, void *mediaReq, const ItemEffectDesc *desc,
 * int itemId, void *itemObj, int arg4, float intensity);
 * splits.txt: widen the TU .data range to start:0x803F7640 (Dispatch jumptable).
 * Rest of the fn = the 86% draft body verbatim EXCEPT the strPcb clamp (see below). */
    struct {                       /* plain - NO volatile */
        float dir[3];
        float d[3];
        float mtx[16];
    } s;
    ...
    if (lane->desc->kind14 == 1) {
        if (lane->itemObj != 0) {
            KartMovementSpeedView *mov;
            ItemObjectPosView *obj;
            float *t;
            int i;

            obj = (ItemObjectPosView *)lane->itemObj;
            mov = owner->movement;
            t = mov->transform;
            for (i = 0; i < 16; i++) {
                s.mtx[i] = t[i];
            }
            {
                float dir0 = s.mtx[0];
                float dir1 = s.mtx[1];
                float dir2 = *(volatile float *)&s.mtx[2];  /* reload-mode slot */
                float dy = obj->posY - s.mtx[13];           /* dy BEFORE dx */
                float dx = obj->posX - s.mtx[12];
                float dz = obj->posZ - s.mtx[14];
                float t0, t1, sum, t2, dot;
                s.d[0] = dx;
                s.d[1] = dy;
                s.d[2] = dz;
                s.dir[0] = dir0;
                s.dir[1] = dir1;
                s.dir[2] = dir2;
                t0 = dx * dir0;
                t1 = dy * dir1;
                sum = t0 + t1;
                t2 = dz * dir2;
                dot = t2 + sum;
                if (dot < lbl_806D26EC) {
                    lane->blend = lbl_806D26E4;
                } else {
                    lane->blend = lbl_806D26FC;
                }
            }
        } else {
            lane->blend = intensity;
        }
        ...
    }
    /* strPcb clamp fix (build 3): */
        sp = lbl_806D2718 * mov->speed;
        ref = mov->table[mov->tableIdx].refSpeed;   /* float ref; decl after sp */
        if (sp > ref) {
            sp = ref;
        }
        mov->speed = sp;

/* build-7 variant (94.79%, alternative if chasing the dir webs): drop the dir0/dir1
 * locals, store s.dir[0] = s.mtx[0]; s.dir[1] = s.mtx[1]; s.dir[2] = dir2; and consume
 * t0 = dx * s.mtx[0]; t1 = dy * s.mtx[1]; -> dir webs go DESCENDING f3/f2 (target f4/f3)
 * and the first-half schedule matches register-for-register. dx/dy mirror persists. */

```

## Appendix B: KartItem_ApplyImpactImpulseAndRumble best-state C (94.24%, build 6, full drop-in)

```c
#define VF(x) (*(volatile float *)&(x))
#pragma exceptions off
void KartItem_ApplyImpactImpulseAndRumble(KartItemOpsView *self, int mode, float x, float y, float z) { /* 0x8004B49C size:0x520 */
    struct ImpactScratch {
        float sqB;     /* sp+0x08: 3rd in-place sqrtf slot */
        float sqA;     /* sp+0x0c: 2nd in-place sqrtf slot */
        float sqD;     /* sp+0x10: 1st in-place sqrtf slot */
        float tA[3];   /* sp+0x14 */
        float tB[3];   /* sp+0x20 */
        float d[3];    /* sp+0x2c */
        float m[16];   /* sp+0x38 */
    } s;
    KartMovementSpeedView *mv;
    unsigned char b;
    ItemBusFlagsView *bus;
    float sel;      /* f30 */
    float dist;     /* f31 */
    double guess;
    float invD;
    float dot;
    float v1;
    float v0;
    float ratio;
    float rumble;
    float rumble2;
    float fwdDot;
    float impZ;     /* f2 */
    float k;        /* f2 */
    float aZ;       /* f2 */
    float v2;
    float negInv;   /* f3 */
    float impY;     /* f3 */
    float c1;       /* f3 */
    float n0;       /* f3 */
    float impX;     /* f4 */
    float magSq;    /* f4 */
    float c2;       /* f4 */
    float n2;       /* f4 */
    float scale;    /* f5 */
    float c0;       /* f5 */
    float n1;       /* f5 */
    float dx;       /* f6 */
    float aY;       /* f6 */
    float aX;       /* f7 */
    float rumZ;     /* f8 */
    float w2;       /* f9 */
    float dy;
    float rumY;     /* f10 */
    float w1;       /* f11 */
    float rumX;     /* f12 */
    float w0;       /* f13 */
    float dz;
    float p0;
    float p1;
    float p2;
    float sum;
    float dotA;
    float dotB;
    float *t;
    int i;

    mv = self->movement;
    t = mv->transform;
    for (i = 0; i < 16; i++) {
        s.m[i] = t[i];
    }
    s.d[0] = x - s.m[12];
    s.d[1] = y - s.m[13];
    s.d[2] = z - s.m[14];
    p0 = s.d[0] * s.d[0];
    p1 = s.d[1] * s.d[1];
    sum = p0 + p1;
    p2 = s.d[2] * s.d[2];
    dist = p2 + sum;
    if (dist > lbl_806D26EC) {
        guess = __frsqrte(dist);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        VF(s.sqD) = (float)(dist * guess);
        dist = VF(s.sqD);
    }
    if (EffectState_HasContent(self->effectState44) == 0) {
        dotA = s.d[1] * s.m[1];
        dotB = s.d[0] * s.m[0] + dotA;
        dot = s.d[2] * s.m[2] + dotB;
        if (self->strPcbGate20 == 1) {
            if (dot > lbl_806D26EC) {
                sel = lbl_806D2734;
            } else {
                sel = lbl_806D2738;
            }
            StrPcb_SetTimer3c40(StrPcb_GetInstance(), sel, 12);
        }
    }
    bus = self->ownerDriver->itemBus;
    invD = lbl_806D26FC / dist;
    negInv = -invD;
    dx = VF(s.d[0]) * negInv;
    dy = VF(s.d[1]) * negInv;
    dz = VF(s.d[2]) * negInv;
    VF(s.d[0]) = dx;
    VF(s.d[1]) = dy;
    VF(s.d[2]) = dz;
    if ((bus->flags & 0x10000000ULL) == 0 || (unsigned char)mode == 0) {
        scale = lbl_806D273C * dist;
        mv = self->movement;
        impX = s.d[0] * scale;
        impY = s.d[1] * scale;
        impZ = s.d[2] * scale;
        VF(s.d[0]) = impX;
        mv->impact1ac = mv->impact1ac + impX;
        VF(s.d[1]) = impY;
        mv->impact1b0 = mv->impact1b0 + impY;
        VF(s.d[2]) = impZ;
        mv->impact1b4 = mv->impact1b4 + impZ;
        magSq = mv->impact1b4 * mv->impact1b4 + (mv->impact1ac * mv->impact1ac + mv->impact1b0 * mv->impact1b0);
        if (magSq > lbl_806D26EC) {
            guess = __frsqrte(magSq);
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            VF(s.sqA) = (float)(magSq * guess);
            magSq = VF(s.sqA);
        }
        if (magSq > mv->impactCap1b8) {
            ratio = mv->impactCap1b8 / magSq;
            mv->impact1ac = mv->impact1ac * ratio;
            mv->impact1b0 = mv->impact1b0 * ratio;
            mv->impact1b4 = mv->impact1b4 * ratio;
        }
        rumble = lbl_806D2740 - dist;
        dist = rumble;
        if (dist < lbl_806D26EC) {
            dist = *(volatile const float *)&lbl_806D26FC; /* defeat CSE with the invD 1.0f load */
        }
        dist = dist * lbl_806D273C;
    } else {
        /* class-1 recipe: explicit ==0 compare, then=0 / else=1 arm order */
        if ((bus->flags & 0x10000000ULL) == 0) {
            b = 0;
        } else {
            b = 1;
        }
        if (b == 1) {
            rumble2 = lbl_806D2740 - dist;
            dist = rumble2;
            if (dist < lbl_806D26EC) {
                dist = *(volatile const float *)&lbl_806D26FC;
            }
            dist = dist * lbl_806D273C;
        }
    }
    c0 = VF(s.m[8]);
    c1 = VF(s.m[9]);
    c2 = VF(s.m[10]);
    v0 = c0 * s.d[0];
    v1 = c1 * s.d[1];
    fwdDot = v0 + v1;
    v2 = c2 * s.d[2];
    fwdDot = v2 + fwdDot;
    w0 = VF(s.d[0]);
    w1 = VF(s.d[1]);
    mv = self->movement;
    w2 = VF(s.d[2]);
    rumX = w0 * dist;
    rumY = w1 * dist;
    rumZ = w2 * dist;
    mv->rumbleX310 = rumX;
    mv->rumbleY314 = rumY;
    mv->rumbleZ318 = rumZ;
    k = lbl_806D2744 * -fwdDot;
    mv = self->movement;
    VF(s.tA[0]) = c0;
    VF(s.tA[1]) = c1;
    VF(s.tA[2]) = c2;
    aX = c0 * k;
    aY = c1 * k;
    aZ = c2 * k;
    VF(s.tB[0]) = rumX;
    VF(s.tB[1]) = rumY;
    VF(s.tB[2]) = rumZ;
    n0 = w0 + aX;
    n1 = w1 + aY;
    n2 = w2 + aZ;
    mv->impact1ac = mv->impact1ac + n0;
    mv->impact1b0 = mv->impact1b0 + n1;
    mv->impact1b4 = mv->impact1b4 + n2;
    VF(s.tA[0]) = aX;
    VF(s.tA[1]) = aY;
    VF(s.tA[2]) = aZ;
    VF(s.d[0]) = n0;
    VF(s.d[1]) = n1;
    VF(s.d[2]) = n2;
    magSq = mv->impact1b4 * mv->impact1b4 + (mv->impact1ac * mv->impact1ac + mv->impact1b0 * mv->impact1b0);
    if (magSq > lbl_806D26EC) {
        guess = __frsqrte(magSq);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        VF(s.sqB) = (float)(magSq * guess);
        magSq = VF(s.sqB);
    }
    if (magSq > mv->impactCap1b8) {
        ratio = mv->impactCap1b8 / magSq;
        mv->impact1ac = mv->impact1ac * ratio;
        mv->impact1b0 = mv->impact1b0 * ratio;
        mv->impact1b4 = mv->impact1b4 * ratio;
    }
}
#pragma exceptions reset
#undef VF
```
