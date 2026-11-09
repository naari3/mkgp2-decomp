# HANDOFF batch_promote_8004edd4_shadowbb

## Result: skipped at precan (0 attempts, no C written) - Class 1 hard-block present

KartItem_UpdateShadowBillboardAndViewport @ 0x8004EDD4 (size 0x204, mega-bundle index 20)
contains ONE instance of the established Class 1 hard-block (branch-over-branch bool
materialization), at 0x8004EF18..0x8004EF28:

```
or.    r0, r3, r0          # u64 flag test result
bne    L_8004EF24
b      L_8004EF28          # empty fall-through (no real instruction)
L_8004EF24:
li     r4, 0x1
L_8004EF28:
clrlwi r0, r4, 24
cmplwi r0, 0x1
```

This is byte-for-byte the KartItem_OnKartHit precan class (per_fn_matching_strategy.md
section 14.2): r4 pre-seeded with `li r4, 0x0`, u64 mask test (here mask =
0x0000200000000000ULL: hi word ANDed with 0x2000 at bus+0x10, lo word ANDed with 0 at
bus+0x14, and/and/xor/xor/or. shape identical to the verified ItemEffectBus flags idiom),
then bool materialized via branch-over-branch. CW 1.0..2.7 x all opt levels and ~20 C/C++
source forms (incl. the 2026-06-10 CarObject_OnItemHit elimination round) all invert this
to the 1-instruction-shorter `beq L2; li r4,1; L2:` form. Unsolvable at source level with
current knowledge -> per dispatch instructions, immediate skip without writing C.

### Precan detail (all classes checked)

- Class 1 (branch-over-branch bool): PRESENT, 1 site (0x8004EF18). -> skip.
- Class 2 (16-float copy frsp interleave): absent (no float-block copy in fn).
- EH scaffolding (`bl __unexpected` / `mr r31, r1` FP prologue): absent (prologue is
  plain stwu/mflr + psq_st f31 + r28-r31 saves).
- ScopedTimer pair swap (`subi rX, rY, 0x217d`): absent.
- Flavor 5 (loop SR coalescing): only a small search loop at 0x8004EE48..0x8004EEAC with
  r5 counter + r6 = 8*i byte offset (dual induction but tiny); moot given Class 1.
- Class 3 / Flavor 4: not reachable (no C attempt made).

### Notes for future retry (when/if Class 1 is solved)

The rest of the function looks LOW difficulty and should fall quickly once Class 1 has a
source-level solution:
- Shape: if (ItemStateGuard_IsActive(self->guard->composite /*0x40->0x4*/) == 1)
  { ShadowBillboard_StepSimple(self->billboard /*0x38*/, arg2, arg3); } else { big path }.
- Big path: f31 speed-threshold search loop over movement(0x28) table
  (entry = base(0x24) + idx(0x8)*0x18, count at +0x4, keys at *(+0x0) + i*8, threshold at
  +0x8, hit -> f31 = *(table + i*8 + 4)); then optional floor to lbl_806D276C when
  byte +0x22 == 1 (fcmpo + cror eq,gt,eq = `>=` test); KartMovement_CalcSpeedWithCoinBonus;
  fdivs by (lbl_806D2770 * f31); Saturate_Double(x, 0.0f, 1.0f); the Class-1 u64 flag test
  selecting f4 = lbl_806D2708 vs 0.0f; int coinCount(0xc8) -> float via the standard
  lis 0x4330 / xoris / lfd / fsubs magic-number idiom, fdivs by lbl_806D27B0,
  Saturate_Double(f4 + coinTerm, f4 + speedTerm?... exact arg wiring: f3 = f1 + f4 computed
  BEFORE the int->float block, f1 = f4 + f0 after); ShadowBillboard_SetTargetSaturation(r28
  = self->billboard cached BEFORE the bl); ShadowBillboard_Tick(self->billboard, arg2, arg3);
  SceneRender_SetViewportRect(g_raceCamera /*sda21 r13*/, mv+0x88, mv+0x8c, mv+0x90,
  mv+0x78, mv+0x7c, mv+0x80) with mv = self->movement(0x28).
- Struct views already exist in-TU (CarObjMainView family from CarObject_MainUpdate draft):
  0x28 movement, 0x2c renderObj->bus(0x304) u64 flags @+0x10, 0x38 billboard, 0x40 guard,
  0xc8 coinCount all consistent with the existing view structs.
- Sibling note: KartItem_GetMaxSpeedWithBonus (0x8004F040) and CarObject_CalcSpeedRatio
  (0x8004EFFC) reuse the SAME movement-table search-loop shape (lwz 0x8 / mulli 0x18 /
  lwz 0x24 base / lfsx key / fsubs+fabs+frsp+fcmpo) but WITHOUT the Class-1 site, so they
  remain promotable independently.
- Unlock chain: solving Class 1 unlocks this fn + KartItem_OnKartHit + CarObject_OnItemHit
  (and program-wide siblings).

No SoT files were touched; worktree restored state = HEAD (nothing to revert). Full
`ninja build/GNLJ82/ok` re-verified green after precan (no changes).

```json
{
  "batch_id": "batch_promote_8004edd4_shadowbb",
  "sub_summary": "KartItem_UpdateShadowBillboardAndViewport precan-skipped: Class 1 branch-over-branch bool materialization present at 0x8004EF18 (u64 flag test 0x0000200000000000ULL -> bool r4), identical to KartItem_OnKartHit hard-block; 0 C attempts per dispatch precan rule",

  "results": [
    {
      "addr": "0x8004EDD4",
      "name": "KartItem_UpdateShadowBillboardAndViewport",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Precan Class 1 hit (1 site @ 0x8004EF18: or./bne L1/b L2/L1: li r4,1/L2:, empty fall-through, bool seeded li r4,0). No C written. Other classes absent (no EH scaffolding, no ScopedTimer, no frsp interleave copy). Rest of fn is low difficulty; full retry roadmap + offset map in HANDOFF body. Siblings KartItem_GetMaxSpeedWithBonus 0x8004F040 / CarObject_CalcSpeedRatio 0x8004EFFC share the movement-table loop shape WITHOUT Class 1 (independently promotable). Solving Class 1 unlocks this + KartItem_OnKartHit + CarObject_OnItemHit."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },

  "docs_notes": [],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": "Precan Class 1 hard-block: branch-over-branch bool materialization (or. r0,r3,r0; bne L1; b L2; L1: li r4,1; L2:) at 0x8004EF18 inside a u64 ItemEffectBus flag test (mask 0x0000200000000000ULL). Established unpromotable class (KartItem_OnKartHit, section 14.2): all CW versions/opt levels/source forms emit the inverted beq form, 1 instruction shorter. Skipped with 0 attempts per dispatch precan rule.",
  "user_attention": null
}
```
