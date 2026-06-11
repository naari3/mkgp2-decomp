# CW 1.3.2 frsp store-forward interleave (class 2): SOLVED by loop-written copy block (2026-06-11, batch_research_frsp_phase2b)

Phase 2b research on the class-2 "16-float copy block frsp store-forward interleave"
(ItemEffect_Dispatch 0x80050410 kind14 branch; same family flagged in sec 14.2 for
KartItem_OnKartHit / KartItem_Tick / ApplyImpactImpulse / Trap / Projectile).
Batch mission was the C++ axis; the actual solution turned out to be reachable from
plain C and works identically under -lang=c++. Harness: tools/compiler_probe/frsp_min.c
+ probe_frsp.py + run_frsp_axis1.py (results_frsp_axis1.tsv).

## VERDICT: SOLVED. The trigger is a LOOP-WRITTEN (variable-index) copy block.

### Recipe (machine-applicable)

```c
typedef struct Scratch { float dir[3]; float d[3]; float mtx[16]; } Scratch;

Scratch s;                       /* plain auto struct -- NO volatile */
float *t = mov->transform;
int i;
for (i = 0; i < 16; i++) {       /* MUST be a loop: variable-index stores */
    s.mtx[i] = t[i];
}
{
    float dir0 = s.mtx[0];       /* constant-index read-backs as named locals */
    float dir1 = s.mtx[1];
    float dir2 = s.mtx[2];
    float dx = obj->posX - s.mtx[12];
    float dy = obj->posY - s.mtx[13];
    float dz = obj->posZ - s.mtx[14];
    float t0, t1, sum, t2, dot;
    s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
    s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
    t0 = dx * dir0;              /* separate statements -> fmuls/fadds, no fmadds */
    t1 = dy * dir1;
    sum = t0 + t1;
    t2 = dz * dir2;
    dot = t2 + sum;
    if (dot < kZero) { ... } else { ... }
}
```

Observed output of this exact form (f35_recipe, CW 1.3.2 production flags): the
16-iteration loop is FULLY UNROLLED into 16 raw lfs + 16 raw stfs (no loop, no
frsp feeding the stores); each consumed read-back materializes as `frsp fN, fM`
where fM is the still-live raw lfs register; the dir slots are stored from the
FRSP'D registers; the d slots are stored from the fsubs results and consumed raw;
the dot is fmuls/fmuls/fadds/fmuls/fadds exactly as in the target. All 22 dead
stores survive at exact offsets without volatile.

Preconditions (all observed, see flag matrix):
- the copy MUST be written as a loop (or pointer-walk loop). Fully-unrolled
  manual stores get front-end forwarded (raw) and then DSE'd.
- optimization level must unroll the loop: -O3, -O4, -O4,p all hit; -O2 and
  -O4,s do NOT (loop survives as 6-store/6-reload shape, classifier 'degenerate').
  Production TU flags are -O4,p -> OK.
- compiler >= GC 1.3 (1.3, 1.3.2, 1.3.2r, 2.0, 2.5, 2.6, 2.7 all hit;
  1.0 / 1.1 / 1.2.5 forward the read-backs RAW -> no frsp).
- insensitive to: -lang c/c++, -Cpp_exceptions on/off, -RTTI on/off,
  -inline auto/noauto, -fp_contract on/off, -use_lmw_stmw on/off.

### frsp vs real-reload partition (target has 5 frsp + 1 reload on m2)

Observation: the minimal recipe yields 6 frsp. The reload mode appears whenever the
stored register is dead/evicted at the read point: in the target, m2's register (f7)
is reused for the posZ load before the dir2 use -> real `lfs f2, 0x28(r1)`; probe
f37 (2D-indexed loop) reproduced 3 frsp + 3 real reloads from the same mechanism.
Hypothesis: in the real fn the surrounding register pressure (f30/f31 webs, posY/posX/
posZ loads) produces the m2 eviction naturally from the same source; needs in-TU
verification (next batch). If it does not, the lever is consume-read order / temp decl
order, not the recipe itself.

## Probe matrix (37 forms, CW 1.3.2 -O4,p unless noted)

TARGET = raw 16+ stfs copy block + >=3 frsp copies of lfs-derived regs.

| form | result |
|---|---|
| f0 plain memberwise copy + read-backs (= old ledger probe 1) | DSE (control reconfirmed, also in C++ mode) |
| f7 inline helper w/ Scratch* params (copy+dot) | DSE |
| f31 inline helper copy only (float* params) | DSE |
| f12 dot via inlined vec_dot((Vec3*)s.d,(Vec3*)s.dir) | TARGET 3/6 frsp (dir reads only) |
| f15/f16/f22/f24 pointer-var read-backs of dir/d slots (punned or plain float*, expression or named locals, decay or &addr) | TARGET 3/6 |
| f17/f23/f25/f28 pointer-var read-backs of MTX slots (any pointer formation) | no-frsp (reads forwarded raw, stores retained) |
| f18 punned writes + direct reads | no-frsp |
| f19 union pun read | degenerate |
| f20 Mtx44 [4][4] + Vec3 row views | no-frsp |
| f26/f27 Vec3 struct-assign from punned views | no-frsp |
| f29/f30 copy written through pointer var (manual unroll) | no-frsp |
| f32 manual copy + LOOP consume (dir/d written in loop) | TARGET 3/6 (dir reads frsp, d reads raw) |
| f33 loop copy + loop consume | TARGET 6/6 |
| **f34 loop copy + direct member read-backs** | **TARGET 6/6** |
| **f35 = f34 + separate dot temps (RECIPE)** | **TARGET 6/6, fmuls/fadds exact** |
| f36 pointer-walk copy loop (*d++ = *s++) | TARGET 6/6 |
| f37 2D [4][4] loop copy | TARGET 3 frsp + 3 real reloads |
| C++ forms f1 constref / f2 reflocal / f3 member fns / f4 accessor / f11 ref helper | DSE or no-frsp (all negative) |
| C++ f5 operator= / f9 copy-ctor of 16-float struct | integer lwz/stw copy (= old ledger probe 2) |
| C++ f6 mutable refs | no-frsp |
| C++ f8 wrapper class w/ operator float() | degenerate (frsp flood on stores, block DSE'd) |
| C++ f13 empty inline dtor / f14 extern dtor | no-frsp (+ dtor call for f14) |

## Mechanism (observation vs hypothesis)

Observations:
1. Constant-index store + constant-index read of the same member: always forwarded
   RAW by an early pass (then DSE if nothing else reads the object).
2. Variable-index (loop) stores break that early forwarding for subsequent
   constant-index reads, even after the loop is fully unrolled.
3. The surviving reads are resolved late: `frsp fN, fM` when the storing register is
   still live and was produced by lfs; RAW forward when produced by single-precision
   arithmetic (fsubs etc., f32's d reads); real lfs reload when the register is dead.
4. Pointer-variable reads of slots whose stored value was itself a forwarded
   read-back (hop-2) also survive to the late pass (f12/f15 family); hop-1 pointer
   reads do not (f17/f23 family).

Hypothesis (mechanism, not verified internally): CW's front-end store-to-load
forwarding matches lvalues syntactically (constant indices, one substitution round);
whatever escapes it survives to a post-unroll/scheduling forwarding pass that does
not track roundedness of LOADS (inserts frsp conservatively because stfs rounds)
but does know arithmetic results are already single-rounded.

## Corrections to the existing ledger

docs/notes/cw132-frsp-store-forward-negative-probes.md conclusion "the frsp copies
in target likely come from a compiler state we cannot reach from plain C (possibly
C++ reference/aliasing semantics)" is OVERTURNED: plain C reaches it via the loop
copy. The C++-axis hypothesis is closed NEGATIVE as the cause (every C++-specific
form probed negative; -lang=c++ neither helps nor hurts the loop recipe). The six
individual negative observations in that ledger all still stand and were reproduced
where re-probed (probe 1 = f0, probe 2 = f5/f9). The sec 14.2 guidance "park as
asm_fn, do not chase frsp" should be replaced by: rewrite the copy block as a
for-loop and keep constant-index named-local read-backs.

## Application outlook (class-2 sites)

- ItemEffect_Dispatch 0x80050410 (86.34% draft in docs/drafts/ItemEffect_Dispatch_86pct.handoff.md):
  replace the `volatile DispatchDotScratch s` + 22 explicit source-order stores with
  a plain struct + `for (i = 0; i < 16; i++) s.mtx[i] = mov->transform[i];` + the
  f35 consume block (named locals dir0..2/dx/dy/dz, d stores then dir stores,
  separate dot temps). Draft residues (a)-(d) are all downstream of the missing frsp
  webs (f30/f31 saves, frame 0x80->0xa0, fctiwz slot) and should self-correct.
  Risk: the m2 frsp-vs-reload partition (allocator pressure) - moderate.
- KartItem_OnKartHit / KartItem_Tick / ApplyImpactImpulse / Trap / Projectile:
  same family per sec 14.2; apply the same transform wherever a raw lfs+stfs copy
  block carries interleaved `frsp fN, fM` (fM = lfs result). Reload sites in the
  target indicate evicted registers, not source differences.
- Precan update: class-2 detection signature unchanged, but action changes from
  "park" to "loop-copy recipe; budget 1-2 builds for the frsp/reload partition".
- In-TU verification is the next batch (this batch was probe-only by mission).
