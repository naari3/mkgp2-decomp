# Register-allocation fixes that worked (mined from git history)

Source: commits on main from 2026-10-25 to 2026-11-08 whose message names a
register-only (or register + schedule) diff that the change fixed. 82 commits
matched the keyword scan; the ~60 that describe a concrete fix are grouped
below, most frequent first. Commit ids let you read the before/after source
(`git show <id> -- src include`).

The checks assume the usual loop: `ninja build/GNLJ82/src/<tu>.o`, then diff
the function against `build/GNLJ82/asm/<tu>.s` (objdiff or a dtk disasm diff).
`tools/pragmasweep.py` already automates patterns 1 and 4 (compiler x pragma x
decl order); try it first, then go down this list by hand.

## 1. Turn one optimisation pass off for the function (about 18 commits)

`#pragma push` / `#pragma opt_common_subs off` / ... / `#pragma pop` around
the function.
- `opt_common_subs off`, the most common fix, often together with a decl-order
  change: fn_801F7F50 f4d48738, BackupWriteRecord 72618d23 (+ GC/1.3),
  MinimapHud dtor c43e2b7a, fn_8029121C ad7cde78, fn_80291134 e9b8ded1,
  TransitionEffect_Tick f5794532, Terrain_GetSlipFactor ddea2657,
  FrameUpdate b2d2c8c2, ClSound_InitSoundSystem 52fc7340.
- `opt_lifetimes off`: fn_80243C70 faec04c4, acModifyMyIPaddr 13b9e455,
  fn_8022CE34 ab1308c7, fn_8020615C 2d1f58a7,
  clItemBoxManager_Update_Inner 3443a77c.
- `opt_propagation off`: fn_8021E0FC 52fc7340, AI_CalcVSTargetSpeed hint
  dc4a7882.
- `opt_dead_assignments off`: CourseScene_Load hint (docs/gave_up.md).

**Check:** `python3 tools/pragmasweep.py fn <TU> <FN> --set all` (add
`--objdiff` for C++ TUs). If a single pragma takes the diff from N lines to a few
lines, keep it and work the rest with patterns 2 to 6.

## 2. Declaration order of locals (about 12 commits)

MWCC colors the callee-saved registers partly by declaration order, so moving
a declaration moves which variable gets r31/r30/... (or f31/f30).
- CharaSelect_SetupCharacterDisplay 664ab806, fn_801F95A0 (cursor before
  self) 0050d41c, BackupWriteRecord (hdr before size) 72618d23, MinimapHud
  dtor (cursor before i) c43e2b7a, CoinSystem_Init (i, offset, cursor)
  6ddad36c, SpeedCurve_UpdateSpeedCap 4b96aa3c, ItemEffect_OnHit 172d1d76,
  ItemSelectState_Init (clamp declared first, as `long`) fba4ebd7,
  fn_801F7F50 f4d48738 (11 floats reordered), fn_8020615C (row offset local
  declared before oy) 2d1f58a7.

**Check:** sweep every permutation of the locals that sit in the swapped
registers (`declsweep.py`, or a 5040-order sweep for 7 locals). Locals of an
inline helper are a separate sweep (acReadResponse: the inline's 120 orders,
memory note decl-order-sweep). If no order moves the swap, the variable is
probably a compiler temporary (strength-reduced pointer, CSE value); use
patterns 3 to 6 instead.

## 3. Introduce or remove a temporary, or load it earlier (about 11 commits)

Where a value is first read decides its register and its schedule slot.
- __THPDecodeBlock: DC selector loaded into a `u8` temp between the two
  `dcbz` dca6dee8.
- CardEntry ctor: button coords in locals, `by` loaded before `bx`
  7ee5ac5a.
- ItemEffect_TornadoLift: read z, y, x into locals before the stores
  ee8b2935.
- GameBoot_Init: load the cabinet byte before taking the table address
  7fb6aea5.
- DbgScene04/06 ctors: PaletteSet::NextColor index temp 0a3931c6.
- clItemBoxManager_UnregisterResponder: named binder2nd predicate local
  d56e168e.
- Terrain_GetSlipFactor: one cup-id local shared with the helper ddea2657.
- JvsInput_PollAndUpdate: per-player pointer taken once 3aac5e5d.
- fn_8020615C: row offset as a local 2d1f58a7.
- ShadowBillboard_LerpMtx4x4: row offset into a local before the call, all
  elements indexed through one int a0a302cd.

**Check:** in the diff, find the first instruction whose destination register
differs. Its source expression is the value to pull into (or out of) a named
local, or to read one statement earlier or later.

## 4. Loop shape: index arithmetic and counter scope (about 10 commits)

Strength reduction creates hidden pointer/offset registers. The source shape
decides how many there are and in which order they get colored.
- Compute the position from the index instead of a running counter:
  NameEntry::BuildKeys `x = 0x3C + g*0xBB` d235bdf7, ItemSelectState_Init
  `idx = row*11 + col` plus `table[col]` fba4ebd7, PCBCheck_ProcessLinks
  `slot` indexed by i d36e6953.
- One shared function-scope `int i` for all loops (Effect_KartAuraCompound
  032ddaca, clFlowItemSelect_Init i/j 12dc847f), or the opposite, a
  separately scoped counter per loop (clFlowItem_Draw a9587bac, MinimapHud
  dtor c43e2b7a). Try both.
- A real loop instead of a hand-unrolled search: PathManager_RegisterCarObject
  d9ab74b8.
- A chained `= j = 0` store gives the zero the counter's register
  (PowItem_TickActive e7d2a980, fakematch).

**Check:** if the swapped register is an `addi rX, rX, size` walker or an
offset that is added to a base each iteration, rewrite the loop as `p = &a[i]`,
as `p++`, as `base + i*size`, and with shared or separate counters.

## 5. Move code into or out of a static inline helper (about 6 commits)

An inlined body gets its own temporaries and a deeper allocation priority.
That changes the strength-reduction init and which dying register a walker
reuses.
- Menu801F0CC0: the loop in a static inline gives the target's `mr` SR init
  2ed893f, applied to the other loops in 9dba1c04.
- clFlowItem_Draw: per-subobject inline draw helpers a9587bac.
- PowItem_TickActive: the first burst as an inline, the other two written out
  e7d2a980.
- Stack-slot order follows inline depth (TIPS.md "Stack-slot order").

**Check:** a near miss where only one of several identical blocks has other
registers usually means some copies were inline expansions and others were
written out (acReadResponse, PowItem).

## 6. Compiler version (about 6 commits)

- GC/2.6: CharaSelect_SetupCharacterDisplay and fn_801F7604 aa88ab45,
  ItemEffect_TornadoLift ee8b2935, ItemEffect_OnHit 172d1d76,
  ItemEffectDamp_TryArm 7fb6aea5. Game C++ near 0x801F..0x8020 is often GC/2.6
  with `-use_lmw_stmw on` (memory note mkgp2-compiler-gc26).
- GC/1.3: StrPcb_WaitForState1 228e2981, BackupWriteRecord 72618d23.
- GC/1.2.5n: offset-0 member address as `addi rX, rY, 0` instead of `mr`.

**Check:** pragmasweep tries every version. The prologue style tells 1.2.5n
(`mflr; stw r0,4(r1); stwu`) from the rest (tools/tu_audit.py CC section).

## 7. Expression form, evaluation and store order (about 9 commits)

- Order of vector component stores: up vector stored y, z, x (fn_8019C15C
  b853d71e); pose read z, y, x (ee8b2935).
- One `return` of a value assigned on every branch (fn_8020A788 0050d41c).
- Assign inside the cast (`(u8)(f = ...)`, fn_80220A54 2bca5fd5, fakematch).
- Shift each step result before masking (random_nm1 5ab64ecc).
- In-place `x *= a` (SpeedCurve 4b96aa3c).
- Pass the running value as a parameter of the inline (BackupWriteRecord sum
  in r4 2411307c).
- The call's arguments evaluated right to left as one call (GabyouTripleChild
  3aa37c0d).
- Float literals instead of `extern const float` (fn_801BD744 591e742d,
  ItemSelectState_Init fba4ebd7); postprocess_sdata2 maps them back.
- `const` on the pointer or array (ItemEffect_TornadoLift const pose
  ee8b2935).

**Check:** these change the expression DAG, not the variables. Try them when
the swap is in the f-registers of one expression or in the value of a return.

## 8. Scheduling-region boundaries in long copy runs (2 commits)

MWCC schedules a block of up to 26 statements as one region.
- PlayStats_CopyStatsBlock 4493f6f8: one 16-byte struct copy instead of a pair
  plus two words moved the region break to the target's place.
- JumpDistanceMode_CopyKartMovement 98c46711: 209 field copies through two
  alternating temporaries per register class, in the target's load-ahead
  order.

**Check:** a long run of loads and stores whose order matches except near one
spot: count statements from the start of the block and change the grouping
(struct copies, merged or split statements) so the break lands where the
target's does.

## 9. Not register allocation: data ownership and anchors (5 commits)

When the swap comes with an extra `lis/addi` or a missing `addi rX, rBase, 0`,
the fix is TU data ownership, not source shape: StrPcb_Init .bss 2238dacb,
ResultPartY ctor .rodata b663d902, HSD_SetupChannelMode six objects 71c13d3b,
jobj merge 69cde578, tobj merge 0195f28c.

**Check:** `tools/tu_audit.py` marks these functions `[reloc]`.

## 10. A value lands in r0 but the target uses r4..r7 (1 commit)

r0 can't be a load base. If the value is used as a base before peephole folds
that load back to an offset from another register, it skips r0.
- fn_801540E0 d7c4990: a list dtor's end iterator (`addi r7, r30, 0x10;
  stw r7, ...`) got r0. Reading begin() through the anchor pointer fixed it:
  `LNode **a = &l->f4; e.n = (LNode *)a; b.n = a[1];`, not
  `e.n = &l->f4; b.n = l->head;`.

**Check:** a short-lived value in r0 where the target has r4..r7, with a nearby
load from the same struct. Rewrite that load to go through the value.

## 11. `li rN, -0x100` colour lands in r0: the TU is GC/2.x (1 commit)

Every matched function with `li rN, -0x100; ... rlwimi rN, rA, 0, 24, 31` and
rN != r0 is in a GC/2.x TU, written as `0xFFFFFF00 | (unsigned char)alpha`
(fn_801CB818, misc3d fn_80169334, KartAlertPanel, ResultFx). A GC/1.3.2 TU
that fakes the rlwimi with `__rlwimi(0xFFFFFF00, a, 0, 24, 31)` gets the
right instructions but colors the constant r0.
- fn_801BDEB4 ae58acb: TU fn_801BAA88 -> GC/2.6 (all its matched functions
  compile the same), `unsigned char al = (int)(255.0f * a);
  SetColor(0xFFFFFF00 | al)`, and the neighbouring int stores reordered.
- fn_8023A148 (onmokoworks claim, not landed): GC/2.6 plus
  `unsigned char alpha = value;` with the color local declared before the
  title local fixes the color/title registers at the first call site.

**Check:** grep the TU for `__rlwimi`. If it is there, try the TU on GC/2.6
with the natural `|` form before anything else. Check that every matched
function in the TU stays 100 (tustat).

## 12. FPR colours off around a float constant: use the literal (1 commit)

TornadoEffect_Tick (6d98b73): in `x += step; if (x > 1) { x = 1; ... }`, the
max constant took f2 instead of the target's f0 while loaded through
`extern const float lbl_806D28CC`. Writing `0.016666668f` and `1.0f` as literals
fixed it. CW can CSE and hoist literal loads freely, but treats an extern const
as a memory load. tools/postprocess_sdata2.py renames the `@N` literals,
including the int->float magic double, to the target's shared `lbl_` symbols.
So literals are fine even when the TU doesn't own .sdata2. mcmp still shows
`"@N"` vs `lbl_` name diffs, so check with a full build and report.json.
Same function: `double d = __fabs(x); a = d;` gave the target's separate
fabs/frsp registers, and `T t; ...; t = tmpl;` (assigned after the decls, not
an initializer) fixed the register order of a struct template copy.

## Still open (same shape, no fix found yet)

- r0 coloring quirk with a `0xFFFFFF00` rlwimi colour: clFlowCourse,
  clFlowGpPlease_Init (try pattern 11 first; both are onmokoworks claims).
- Value and table pointer swapped r4/r5 in two lookup loops:
  NameCheck_CardName. Tried 120 decl orders, temps, cmp swap, pragmasweep and
  20 minutes of cperm.
- Quad-ctor FPR coloring: fn_801F8404/fn_801F8728 (the fn_801F7F50 recipe
  f4d48738 plus `fabs(h)` before `fabs(w)` leaves pure f-register coloring),
  wip/audit.
- Loop offset r30 vs r26: fn_8018DAD0. base/slot r27/r28: PCBCheck_ProcessLinks.
