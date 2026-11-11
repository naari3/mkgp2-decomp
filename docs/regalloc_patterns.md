# Register-allocation fixes that worked (mined from git history)

Source: commits on main from 2026-10-25 to 2026-11-08 whose message names a
register-only (or register + schedule) diff that the change fixed. 82 commits
matched the keyword scan; the ~60 that describe a concrete fix are grouped
below, most frequent first. Commit ids let you read the before/after source
(`git show <id> -- src include`).

The checks assume the usual loop: `ninja build/GNLJ82/src/<tu>.o`, then diff
the function against `build/GNLJ82/asm/<tu>.s` (objdiff or a dtk disasm diff).
`tools/regswap_classify.py` (output docs/reports/regswap_census.md) groups the
current near misses by the shape of their register diff; start there to find
functions that share a shape with one already fixed.
The same patterns are kept machine-readable in `tools/patterns/rules.jsonl`
(`tools/rewrite_rules.py suggest UNIT FN` ranks them for one function; see
docs/asm_to_source.md), and `tools/asmgrep.py like UNIT FN --from --to` shows
how matched functions wrote the same target shape.
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
- LakituStart_UpdateCountdown (FPR, 11-09): `const float dy = dir.y;` declared
  BEFORE `const float dx = dir.x;`, and `float height` declared after both
  (it had been at the top of the block). Swapping only dx/dy, or only moving
  height, each still left 2 FPRs swapped; it needed both at once, so sweep the
  float locals together (regfix's dump failed on this C++ TU).

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
- fn_8023A148 (landed 310a051, see §21): GC/2.6 plus
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

## 13. "First access folded, the rest through a pointer": a static object behind the section anchor (diagnosed, 11-08)

Target shape (CSPartsHolders fn_8014D038, anchor `CSSceneGetTitle_8014ADB4_rodata_80362D90` in r31):

    addi r3, r31, 0xef4        ; &rot materialised
    lfs  f29, 0xef4(r31)       ; first field folded onto the anchor
    lfs  f30, 0x4(r3)          ; the rest through r3
    lfs  f31, 0x8(r3)

This is what MWCC emits for a compiler-local object (a `static` /
`static const` local, a string, a literal table) reached through the
section anchor. The object's address gets its own register, and peephole
folds only the first load into an anchor displacement. A minimal test
reproduces it exactly (GC/1.3.2, `#pragma readonly_strings on`, two
`static const` Vec3 tables plus two strings in one function, the rot reads
loop-invariant). Without the anchor the same code gives `lfsu f29, rot@l(r3)`
followed by `4(r3)` and `8(r3)`.

Our sources reach these objects as `(T *)((char *)lbl_pool + off)`, which is
`base + constant` to the optimizer, so every access folds onto the base
register. No pragma, compiler version, pointer temp, const, inline or
struct-copy shape changes that. Checked on fn_8014D038 (11-08): const pool +
local base gets the base reuse and the hoisting right, but stays at 59 lines.

Fix: let the TU own the pooled section and define the objects as real
`static const` locals in source order, so the anchor and its offsets come
from the compiler (see [[mwcc-rodata-anchor-rule]] in memory and §5 of
matching_rules). For CSPartsHolders that means the pool `CSSceneGetTitle_8014ADB4_rodata_80362D90`
(.rodata, 0xF00 bytes) shared by RaceHud_80147470 .. CSPartsHolders
(.text 0x80147470..0x8014D540). It is a multi-TU merge, not attempted yet.
The same diagnosis covers PCBCheck_RecvLinkData, Item4SubFlame and
KartFx_BoostExhaustRayTick (KartFx's struct copy from `resources->colors` is a
copy from a static object), all onmokoworks-claimed.

Solved for KartFx_BoostExhaustRayTick (11-08): the pool owner
EffectVfx10_KartTrail_Tick sits right after it, so merging just those two
TUs into game/KartFxExhaustRay.c was enough. Other TUs that use the pool as
an extern base still link because the named objects keep their addresses.
Lessons: (1) to get `addi rX, anchor, off` + folded first access for a struct
copy, the copied object must start at that offset, so split the table
(`EffectVfx9_DriftSpark_Tick_rodata_8032A348` became `EffectVfx9_DriftSpark_Tick_rodata_8032A348` + `lbl_8032A354[2]`) and copy member by
member (`dst.entries[0] = src.entries[0]; ...`), because a whole-struct copy
folds every load into the anchor; (2) a .cpp merged into a .c owner must lose
its mid-block declarations, and the hoisted locals' order then decides the
stack layout, so sweep where each block-local goes (here `Vec offset` third).

## 14. Target keeps `&local` in a saved GPR across a loop (4d79eae, 11-08)

Target shape (PhysicsState_WallCollisionCheck, GC/2.6): `addi r31, r1, 0x3c`
in the loop preheader, then `mr r4, r31` for each `Terrain_RaycastWall` call.
Ours rematerialised `addi r4, r1, 0x3c` in the loop body. Moving the
declaration out of the loop alone does nothing. What works is declaring the
object before the loop and passing it through a pointer variable:

    PhysicsCollisionVec endpoint;
    PhysicsCollisionVec *ep = &endpoint;
    for (...) { ...; Terrain_RaycastWall(self + 0x4C, ep, &hit, &n); }

The same shape explains KartMovement_CollisionUpdate (`&contact` in r31):
applied 11-09, 951 -> 688 diff lines and the target's stmw r19. It did not help for `&rotation` inside the
inlined `applyYaw`: a pointer local in an inline function gets propagated.

## 15. Target keeps a list iterator in a stack slot (07fd50d, 11-08)

Target shape (PreviewModel fn_8013D940, GC/1.3.2): `stw r0, 0x18(r1)` and
`stw r0, 0x14(r1)` for begin, then every loop pass reloads and stores
`0x14(r1)` around the virtual call. Plain iterator classes (with or without
a user copy ctor, base class, or postfix ++) are always registerized. Two
things put it on the stack:

- A trivial `~iterator() {}` does it, but it also adds extab actions and
  stops begin()/end() from inlining. Do not use it.
- An iterator that is a derived class (`struct CIter : CBase`, ++ in the
  base) passed BY VALUE to a static inline helper does it with no extab
  change. Name the source object in the caller (`CIter b = ...;
  RenderRange(b, end);`) to get the begin slot above the parameter slot.

The `DoublyLinkedList_EraseRange` arg order (ret 0x8, first 0xc, last 0x10)
then needed the erase in its own inline helper too (`EraseFrom(l, e)`).

## 16. A call result takes the wrong dying saved register: name it in the inline (a6d0090, 11-08)

Census shape (docs/reports/regswap_census.md): `saved / reg_only / chain`, where
`after_call`, value `call_result`. One saved register differs, right after
a `bl`, and only for the value that `mr rN, r3` copies out. Several
variables died at that call (their saved registers are free), and the
result took a different one of them than the target.

AI_PerKartUpdate and fn_801E9CBC (same `ItemList` inline): the inline loads
cup/round/mode into r31/r30/r29, calls `AI_GetItemList`, and the target puts
the result in r30 (round's register). Ours used r29 with

    static inline int *ItemList(int kart) {
        int mode; int round; int cup;
        cup = g_cupId; round = g_roundIndex; mode = g_gameMode;
        return AI_GetItemList(GetEnemyParam(), mode, cup, round, kart);
    }

`return call(...)` makes the result an anonymous temporary, created after
all of the inline's locals, and no caller-side declaration moves it (24
declaration orders of the caller's `items` changed nothing). Naming the
result inside the inline and sweeping its declaration position fixed both:

    int mode; int *items; int round; int cup;
    ...
    items = AI_GetItemList(GetEnemyParam(), mode, cup, round, kart);
    return items;

Which of the dying registers the result takes depends on its position in
the declaration order relative to the variables that die at the call
(inline locals are colored in reverse declaration order, caller locals in
declaration order). It is not a simple "next to" rule, so sweep all
positions (n+1 compiles).

**Check:** when the first diff is the `mr rN, r3` after a call and the
value comes from an inline's `return f(...)`, or from a call whose result
goes straight into an expression, give the result a named local and sweep
where it is declared. When the result comes from a load instead (`lwz rN,
global` taking another dead register, fn_8017DF00), the local's name is
propagated away and its declaration position does nothing (120 orders
tried).

`tools/retname_sweep.py` automates this for every near-miss TU: each static
inline whose `return` contains a call gets a named `__ret` at every
declaration position, scored over the whole TU. It reproduces a6d0090; its
first full run (11-08, 30 TUs) found no other hit, so the shape is rare.

## 17. Integer type of a local moves its register (11-08)

`int`, `long` and `unsigned int` are different IR types to MWCC, so changing
only the declared type of a local can move it between r0 and r4 or between
saved registers with the same instructions emitted. fn_801D1684: `int alpha
= FadeAlpha(...)` -> `unsigned int` (or `long`) gave 99.16 -> 100 (R6 had
already matched it another way, db6559f). Also ItemSelectState_Init (clamp
as `long`, fba4ebd7). `tools/typesweep.py --tu SRC` tries every same-width
type for each integer local, greedily, TU-wide no-regression. Partial run
over the census (11-08, ~20 TUs before wind-down): RankLog DetermineTitle
`int i` -> `long` 98.95 -> 99.34 only. `tools/stmtsweep.py` (statement-order
sweep, R5's bc31b3a technique) is written but not validated yet.

## 18. Solve the declaration order instead of sweeping it (tools/regfix.py, 11-09)

Sweeping orders by compiling (pattern 2, ~1 s each) cannot cover 9! orders,
but the order only changes vreg NUMBERS, never the interference graph, so
`tools/regfix.py` re-runs MWCC's allocator offline on the mwcc-debugger dump
for every order (Rust, ~4 us each) and returns the one that gives the target.
Numbering rules it relies on (MWCC 2.6 dumps): named locals get the lowest
numbers in REVERSE declaration order (first declared = highest = coloured
first within a simplify level); frontend temps `@N` (inline params/locals/
returns, CSE) come next, higher `@` = lower number; backend temps last, in
codegen order. Parameters are not movable.
- Sci2Card_BuildItemGetReceiptLine 394b90b: the diagnosis said "ordinary must
  be numbered above the inline temp of `remaining`", impossible for a local vs
  a temp, so `remaining` is computed without the inline (it survives as a
  local) and the solver picks the order (inits become assignments).
- THPDec fn_8029B54C 0494e71: `hs, vs` first; 400 sampled orders had missed it.

**Check:** `python3 -I tools/regfix.py diag UNIT FN` prints the vregs that are
off, the colouring order that would fix them translated to source terms, any
one-step graph edits that would (drop/add a live-range overlap, keep a
machine register busy, swap creation order) and a solved declaration order.
`fix` adds a focused move search with the solver run on every variant.

## 19. A shared caller local across switch cases: one inline helper per case (fn_8017F538, 11-09)

`regfix diag` said "'menu' is a named local, numbered below every temp: turn
it into a temp". The function used ONE function-scope `Menu *menu` for three
cases (`menu = Create(...); if (menu != 0) <loop>`), so it was numbered below
the loop's walker temp in every declaration order. Moving each case body
(create + null check + loop) into its own `static inline` with a local
`Menu *m` (and the loop `int i` inside the inline) gave the target colouring
order; a fourth case with the same shape needed the same treatment, and the
last two named locals (`id`, `menu`) then only needed `id` moved to function
scope before `menu`. Partial wraps (only the null check + loop, or the
created pointer passed as an inline argument) put the menu ABOVE the loop
counter instead: the create call has to be inside the inline, after which the
inline locals are numbered in the right order by themselves.
Rule: `shared-local-into-inline` in tools/patterns/rules.jsonl.

## 20. Part of the function is an already-matched function's body: inline it (fn_8024D3D4, 11-09)

ContinueSceneTick fn_8024D3D4 (99.87, `credits`/`alternate` in r28/r29
swapped) ends with exactly the code of `CoinCounter::Draw`
(ContinueScene_nm1, already 100 %). regfix diag said "'credits' is a named
local, numbered below every temp: turn it into a temp (inline helper ...)".
Copying Draw's body verbatim into a `static inline` (the caller's string base
passed as a parameter) made `credits` an inline temp and matched the function
(d857cd3). Earlier attempts that only moved the caller's own code into a
helper, or changed decl order/types, did not move it: the sibling's exact
statement shape (`idx = x ? 1 : 0;`, `if (done != 1) { ... }`) mattered.

**Check:** look for a matched function whose whole body appears inside the
near miss: `tools/asmgrep.py similar UNIT FN --src`, or grep the near miss's
distinctive globals/strings in `src/` and read the matched hits. Rule
`inline-matched-sibling` in tools/patterns/rules.jsonl.

## 21. An unrolled store run that the target reloads for: write it as a loop (fn_8023A148, 11-09)

fn_8023A148 (99.79) stores two colours into 12 `texts[i][j]` text managers
from a static inline called twice. After GC/2.6 + the natural
`0xffffff00 | (unsigned char)a` (§11), one site still differed: before the
call it reads the current alpha from `texts[0][0]`, and ours kept that
pointer in r3 for the first store (so the alpha went to r4), while the
target reloads it (`lwz r3, 0x20(r29)`). Writing the 12 stores as
`for (int i = 0; i < 3; i++) { [i][0] = title; [i][1..3] = color; }` gives
the same unrolled code but the backend unrolls after the frontend CSE, so the
pointer is not reused: 100 % (310a051).

**Check:** a hand-unrolled run of stores to `a[0..N]` where the target
re-loads an element pointer that ours keeps from an earlier statement. Rule
`rolled-loop-blocks-cse`.
## 22. An inline local created too late: declare it one level up, pass by reference (CourseData_LoadPathTable, 11-09)

`regfix diag`: "create temp @71 (size, a local of the inner inline
LoadFileData) after temp @51 (its `file` parameter)". Frontend temps are
numbered in reverse creation order, so `size` had to be created before the
inner inline was expanded. Declaring `unsigned long size;` in the outer
inline LoadFileTable right after `const char *file;` and passing it as
`unsigned long &size` to LoadFileData gave 99.70 -> 100 (declared before
`file` it did nothing). This is the shape the earlier "merge LoadFileData
into LoadFileTable" attempts were circling. Rule:
`inline-local-to-outer-ref`.

## 23. Compute a value before the local that holds it is declared (PtrVec_InsertFill, 11-09)

`regfix diag` wanted the copy-loop walker temp of an inline
(`FaceCopyBackward(position, end, end + n)`) numbered just above the named
locals, and decl-order/naming the `end + n` argument did nothing (copy
propagation). Computing `tail` from the expression BEFORE declaring `end`,
`unsigned int tail = (s->data + s->count) - position;` then
`SpecialFaceNative **end = s->data + s->count;`, makes the address a CSE temp
created earlier, and the copy loop's registers swap into place: 99.55 -> 100.
Statement order of two uses of one expression decides which of them owns
the CSE temp; try it when a named local is "propagated away". Rule:
`stmt-order` (evidence added).

## 24. A local must be coloured just before a later inline's temps: read it through a nested inline (fn_8018DAD0, 11-09)

Inline locals and parameters become frontend temps (`@N`) when the inline is
expanded, and MWCC expands inlines level by level: every inline called
directly from the function body first (in statement order), then the inlines
those bodies call, and so on. Lower `@` = higher vreg number = coloured
earlier. So the nesting depth of an inline decides where its temps land in
the colouring order, independently of where it sits in the source.

fn_8018DAD0 (99.94): the final loop (inline `UpdateParticles`, level 1) has a
byte-offset IV temp (`mr r26, r28` in the target, r30 in ours). regfix diag:
"'joint' is a named local, numbered below every temp: turn it into a temp",
and the edits that fixed it all put `joint` just above the IV, i.e. after
UpdateParticles' own locals. A level-1 inline `Joint *GetJoint(e)` (or
`GetJointPos(e, &pos)` with a `joint` local) moved `joint` before every
other temp and broke 20 lines. Reading it through TWO levels,
`CopyPos(&pos, GetJoint(e));` (GetJoint's local and return are level-2
temps, created after all level-1 inline locals) gave 100 % (3fddd78).

**Check:** a regfix diag that wants a named local "numbered above" a temp of
an inline called later in the function. Wrap the local's computation in an
inline that is called from another inline (or as an argument of one), so its
temps are created one level deeper than the later inline's. If a level-1
inline puts it too early, go one level deeper. Rule `nested-inline-level`.

## 25. Hand-expanded recursion: write the real recursive functions, set the inline depth (fn_801893BC, 11-09)

fn_801891C4 (Hide), fn_80189394 (HideList) and fn_801893BC (Visible) were three
TUs: Hide written as seven hand-nested loops ending in calls to HideList and to
itself, Visible as Visible1..3 + Hide0..6 inlines (98.64, saved-register swaps
that no decl order fixed). They are one TU of three short natural functions
(`Visible: if (visible) { list; for c: Visible(c); } else Hide(box);`,
`Hide: HideList(box); for c: Hide(c);`). MWCC auto-inlines the self and
cross calls; `#pragma inline_depth(7)` gives exactly the target's expansion
depth (6 gave one level less, the default one more), and `-inline deferred`
lets Hide inline HideList defined after it and emits the functions in reverse
source order (source Visible, HideList, Hide -> text Hide, HideList, Visible).
All three 100 % with the natural code.

**Check:** an unmatched function whose body repeats the same block N times with
deeper and deeper pointers and ends in calls to itself or to a neighbouring
function that holds the same block: write the recursion, sweep
`#pragma inline_depth(N)` (count `bl` targets against the target), and try
`-inline deferred` if the out-of-line copies must come before their caller.
Also fn_801826F8 (mobjclass JObj walk, 4-TU C++ merge, inline_depth(3), d9220c1). Rule `recursive-auto-inline`.

## 26. A named local re-assigned later becomes a temp: one named local per assignment (fn_801F140C, 11-09)

The backend never splits a named local into webs (§34), but the frontend IR optimiser can take a later assignment away from it: in fn_801F140C regfix diag showed the second colour as a frontend temp (`@358`, defined by the `or`) feeding the loops directly, while `c` kept only the first value. So the second value got a temp number (high, coloured early) instead of the named-local number (low, coloured last). In fn_801F1244/fn_801F140C the target colours both fade colours (`0xFFFFFF00 | v`, then `0xFFFFFF00 | (u8)(255 - v)`) into the same register below the loop counter/offset, but with one `c` assigned twice the second colour was a temp coloured first (27 lines off). Fix: give each assignment its own named local (`c`, `c2`) and let the decl-order solver pick the order (`c, c2, offset, i, v`).

The same family: a local whose value comes straight from an inline return (`c = MenuRGBA(v, v, v, 255)`) is copy-propagated away and the colour stays an inline temp. Write the expression in place (`c = (v << 24) | ((v & 255) << 16) | ((v & 255) << 8) | 255`) so `c` survives as a named local, then sweep the decl order (fn_801F2400, fn_801F1EE0: `c, offset, i`).

How to spot it: `regfix.py diag` asks for "temp @N must be numbered after <named local>" and @N is the def of a variable that is already a named local earlier in the function, or the value of an inline call assigned to a local.

## 27. A CSE'd constant load is numbered after the inline's locals: load it into an inline local first (fn_801F8404, 11-09)

`if (lbl_806DA718 == d->angle) { dx = lbl_806DA718; ...}` inside an inline ctor: common-subexpression elimination turns the two loads into one temp that is created late (high @, low vreg number), so it was coloured after `h` and got f10 where the target has f4 (8 lines). Reading it into an inline local right before the test (`float zero = lbl_806DA718; if (zero == d->angle) { dx = zero; ...}`) creates the temp at that point; the remaining w/h swap was the decl order `float h, w, ...` (inline locals: decl order sets @ order). regfix diag says "swap the creation order of temp @A (the `lfs` of the constant) and @B". Same TU: fn_801F8728 matched by reusing the matched sibling's quad class (DrawQuad7F50 from fn_801F7F50) instead of a hand-made copy.

## 28. A loop offset coloured below a hoisted constant: index the array and turn strength reduction off (SpecialFaceMesh_Dtor, 11-09)

SpecialFaceMesh_Dtor (99.46, parked since 11-07 after 40 min of permuter):
target keeps the byte offset of a `delete data[i]` loop in r31 and the
hoisted `__destroy_arr` dtor address in r30; ours the other way round.
`regfix diag` on the original `offset` variable said "'offset' is a named
local, numbered below every temp"; written as `faces.data[i]` it said
"frontend temp @47 must become a backend temp". Pointer walkers, `i * 4`,
inline wrappers at level 1 and 2 did not help. `#pragma
opt_strength_reduction off` around the natural loop
(`for (unsigned int i = 0; i < faces.count; i++) delete faces.data[i];`)
gives 100 %: the offset is then the backend's index temp, created after the
hoisted dtor address.

**Check:** a loop over `p[i]` whose byte-offset register is swapped with a
loop-invariant value (a function or table address hoisted out of the loop),
and diag naming the offset as a named local or a frontend temp: index the
array directly and try `opt_strength_reduction off` before anything else.
Rule `pragma-opt-off`.

## 29. Constants held in FPRs across an unrolled loop: read them directly and turn CSE off (TripleBladeRing_SetWorldYaw, 11-09)

TripleBladeRing_SetWorldYaw (99.33 after a 720-order decl sweep and 15 min
of cperm): the wrap limits and `1.0f` are loaded once and kept in f1..f4
across a fully unrolled three-arm loop, and two pairs of FPR homes were
swapped. The source had named locals `amp`, `limit`, `one`, `wrap` for the
constants. `regfix diag` called each of them "a named local, numbered below
every temp". With the locals dropped (read `lbl_806D513C` etc. directly) it
said the constant loads were frontend CSE temps (`@25`, `@29`) that "must
become backend temps (no CSE)". `#pragma opt_common_subs off` around the
function then gives 100 %: the loads are still hoisted, but by the backend,
so they are numbered after the phase/stagger loads.

**Check:** FPR swaps between hoisted `extern const float` values and loads
from `self`, where diag names the constants as named locals or as frontend
temps: drop the locals, then try `opt_common_subs off`. Together with §28
(`opt_strength_reduction off` for a loop offset), whenever diag says
"frontend temp @N must become a backend temp", try turning off the pass that
made @N. Rule `pragma-opt-off`.

## 30. Loads hoisted above stores to a possibly aliasing out: __restrict on the inputs (fn_8019EB9C, 11-09)

fn_8019EB9C (Vec3 x 4x4 matrix, called with out == v) loads every matrix
element before the first `stfs`, and its FPR homes and tail `fadds` order
come from that one scheduler DAG. Writing the result into locals and storing
at the end (the old 8-line best) or `opt_propagation`/`opt_lifetimes off`
plus a shared variable (4 lines, every register right) only imitates that
DAG; the pre-RA scheduler still ranks the z chain above `fadds x`. The
natural straight-store source matches with no pragma once the INPUT pointers
are `__restrict`:

```c++
void fn_8019EB9C(const Matrix44 *__restrict a, Vec3 *out, const Vec3 *__restrict v) {
    float vx = v->x; float vy = v->y; float vz = v->z;
    out->x = a->m[0][0] * vx + vy * a->m[1][0] + vz * a->m[2][0] + a->m[3][0];
    ...
```

`__restrict` on `out` instead (40 lines) does not remove the store->load
edges the same way. The product operand order then still had to be swept
(1024 orders, one match: `m*vx` first for x and y, `vx*m` for z).

**Check:** a function whose target does all loads before all stores even
though the output pointer may alias an input (often called with out == in):
put `__restrict` on the input pointers before trying locals or pragmas.
Scheduler rule (from the mweppc Scheduler.c decomp, via the scheduler RE
thread): ready list walked in original order; critical first, then more
uncovered successors, then height, then opcode rank, then original order.
Rule `restrict-input-ptrs`.

## 31. A load stuck behind stack stores: the pointer runs past the end of a sized array (ItemSelectState ctor, 11-09)

`optimizer/Alias.c make_alias` returns no alias (so the access becomes
worst case) when the offset is past `object->type->size`, unless the object
is an array of unknown size (`extern char x[]`). A pointer built as
`(char *)ItemSelectState_rodata_803DC0C0 + 0x1dc` into a defined `const int ItemSelectState_rodata_803DC0C0[15][3]`
(size 0xB4) therefore "may alias" every store to an address-taken local, and
the scheduler keeps its load after them. The same source matched as a
split TU only because there the object was `extern char ItemSelectState_rodata_803DC0C0[]`.

Fix: address the object that really holds the data (`choiceY`,
`ItemSelectState_rodata_803DC180`, the message strings as `static const char[]` defined in
pool order). Inside the pool-owning TU every one of them comes off the same
section anchor, which is the target's single base register. String
literals go to .data, so rodata strings in a pool are named static arrays.

**Check:** a load that the target hoists above stores to a stack struct, while
yours waits for them, and the pointer is "base symbol + offset beyond that
symbol's size": point it at the real object instead. Rule `alias-in-range`.

## 32. Over-split TUs that share one .rodata pool: merge them into the pool owner (item select, 11-09)

fn_80238D9C (item select update, ~95 %) and the ctor only match with the
grid tables and strings defined in the same TU, because the target reaches
them all off one section anchor. Ten files (0x802386E0..0x8023B1A8) went into
`game/ItemSelectState.cpp`. What had to change on the way:

- one compiler (GC/2.6) for all; every matched part still matched there;
- one copy of each struct and `extern "C"` prototype (the split headers had
  conflicting `fn_801F93EC` argument orders and `TextManager` layouts);
- `#pragma auto_inline off` around `fn_8023AA0C`: once it is defined in the
  same TU, -inline auto inlines it into `fn_8023AC14`;
- `extab_padding=b""` on the merged Object, or the extab rename step
  (tools/extab_user_renames.json) does not run at all;
- the rodata split grows to the strings the ctor uses (0x803DC318), with the
  two class-name strings kept as named globals because sdata refers to them.

## 33. GC/1.2.5: an independent op before the first of two pointer stores means the block is unscheduled (__THPGetBit, 11-09)

GC/1.2.5 has no alias analysis: its scheduler orders any two accesses
through pointers, whatever the offsets (docs/mwcc_internals.md, "GC/1.x
backend"). With the store->store edge the first store is always higher than an
`addi` that only feeds the second store, so neither scheduling pass can put
the `addi` first. The target block is code-generation order.

`__THPGetBit` (80.9 -> 100 %): `#pragma scheduling off` (with
`optimization_level 2`, `opt_propagation off`), then source order gives every
block: `t = 26` before `b = *p` for `li` before `lbz`, `n = p + 1` before the
stores for `addi` first, and an out-of-place `q = p + 3` in the loop, because
peephole-forward sinks an in-place `p += 3` below the `cmplwi`.

**Check:** 1.2.5 unit, target order that the 604/750 model cannot give (an
`addi`/`li` ahead of a ready store to the same pointer): try
`#pragma scheduling off` and write the statements in target order.

## 34. One counter reused by many loops in a big switch: give each loop its own variable (jvsio fn_80283154, 11-09)

MWCC does not split a named local into separate webs: `int j` used by ten
independent loops across a large packet switch is one vreg (mwccdbg: `li r49,0`
coloured first, "target varies {r6, r7, r5}"), so it holds one register for the
whole function and pushes everything else around. The target gives the loops
different registers, i.e. separate variables in the original. A greedy search
over which loops get their own counter (declared together after the shared
ones, order kept) took fn_80283154 from 730 to 412 diff lines (97.03 ->
97.93); splitting the other five loops made it worse.

**Check:** mwccdbg shows one loop counter coloured first with "target varies":
rename the loops' counters one by one and keep the ones that help. Rule
`split-loop-counter`.

## 35. A long-lived temp coloured too early because it is pushed in the 2nd simplify sweep: give it low-numbered neighbours (fn_8023AC14, 11-09)

Simplify (mweppc Coloring.c `simplifygraph`) walks the vregs in ascending
number and repeats the sweep until nothing changes; a node pushed in a later
sweep is coloured BEFORE every node of an earlier sweep. A temp that is live
across several calls (all 12 volatile GPRs + every temp of the region as
neighbours) can sit just above K=29 when its sweep-1 turn comes; only
neighbours with a LOWER vreg number that were already pushed in that sweep
lower its degree. It is then pushed in sweep 2, coloured early, and hands out
a saved register (r27) before an unrelated sweep-1 temp elsewhere in the
function is coloured, so that temp takes r27 instead of r28.

`fn_8023AC14`: the phase==40 `player` (g_playerData, live across four
fn_8019FF8C/fn_801F93EC pairs) had degree 30 at its visit, so it took r27
before ChoiceAdvanceRow's `resource` (`li r28,5154`). Two source changes in
that block each add one low-numbered (named-local) neighbour that is pushed
before it, so it goes in sweep 1 and resource keeps r28; the code is identical:
- read `row` / `column` into named locals of the function and pass them to the
  ChoiceItem inline (the column local is pushable, the row one coalesces to r4);
- load `self->groups[0]` for the 2nd..4th calls through one named
  `RefillGroup *group` (assigned 3 times; frontend range splitting makes the
  later assignments a low-numbered @temp). Using it for the 1st call too swaps
  the r3/r4 of the first `lwz`/`lis` (the named var is coloured after the lis
  temp).

**Check:** `mwtrace --only IGNODE,COLOR`: the vreg that takes the wrong saved
register is coloured long before its number would say (sweep 2), its degree
is K+1 or K+2, and few of its neighbours have lower numbers. Add named locals
(numbered below the temps) in its live range that are themselves cheap to
push; re-run until it is pushed in sweep 1. A quick simulator of the sweep
order on the IGNODE dump tells how many neighbours must go.

## 36. Address constants coloured in the wrong order because a base-class initializer is generated first: store the base vtable in the derived ctor body (fn_80227B98, 11-09)

Vreg numbers follow codegen order, and simplify/colour gives the HIGHEST
number first pick (Coloring.c `simplifygraph`/`colorgraph`). In a derived ctor
the base initializer (`clMapEffectParts() : vtable(lbl_80490FE0)`) is
generated before the body, so the `lis` of the base vtable gets the lowest
vreg of the prologue address constants and is coloured last. In
clDNBress::clDNBress the target has base vtable r4, data r6, strings r5, i.e.
the base vtable numbered ABOVE the body's `data`/`strings` bases. The
`lis` order in the final code follows the registers (r4, r6, r5 both ways),
so objdiff showed it as a "lis order" diff with masked symbols, and regfix
diag reported no GPR difference.

Fix: give the base an empty ctor and store the base vtable in the derived ctor
body, after the locals that load the other bases:

    clMapEffectParts() {}
    ...
    const char *data = ...; const char *strings = ...;
    *(const void **)this = lbl_80490FE0;   /* base vtable, kept: not dead */
    vtable = data + 0x54;

**Check:** dump both objects with relocations (`objdump -dr`), map each
`lis`/`addi` to its symbol and compare the registers; `mwtrace` PCODE pre
shows the vreg numbers per symbol and COLOR shows who is coloured first.

## 37. Call arguments scheduled in the wrong order: the prototype interleaves int and float parameters differently (fn_8021ABFC, 11-09)

`call_function` (optimizer/FunctionCalls.c) generates the arguments in
PARAMETER order (calls first), and the pre-RA scheduler breaks ties by that
order. PowerPC assigns int and float registers independently, so
`f(Obj *, void *anim, float t, ...)` and `f(Obj *, float t, void *anim, ...)`
put the values in the same registers (r3, r4, f1, ...) but load them in a
different order. In the clCSOrgKartModel ctor the target loads `anims[0]`
(r4) after the 30.0f literal (f1); with `(n, anim, t, ...)` ours loads it
before. Literals, locals, inline wrappers, pragmas and -O4,s all left the 4
lines; declaring `clNormal3D_SetScale(clNormal3D *, float frame, void *anim,
float, float, float)` matched at once.

**Check:** only argument loads of ONE call change places, and the moved pair is
an int and a float argument. Swap their order in the prototype (keeping each
class's order) and at every call site in the TU.

## 38. Named locals must be numbered between inline temps: write the inline bodies directly and let the per-branch reuse split (DrawEffect_ItemHitBurst_Spawn, 11-09)

`regfix diag` said "pitch/roll are named locals numbered below every temp;
target colours them before the helper temps". Two `static inline` helpers
(one per switch case) held `yaw`/`spread`; their locals are frontend temps
and always sit above the caller's locals. Fix: paste both helper bodies into
the caller, declare every float in the wanted colouring order (later
declaration = lower vreg = coloured later), and give the second case its own
`yaw2`/`spread2` (the frontend splits a reused local per branch anyway, and
the split copies become temps). The clamp was also written directly so
`speed` stays a named local. Declaration order that matched:
`spread2, spread, pitch, roll, speed, yaw2, yaw`. Stack objects are the
opposite case: a `Vec local = *v;` copy that must sit below the by-value
argument temps has to stay in a tiny inline (`TransformVelocity`), because
inline locals are created after the caller's temps.

## 39. Unfused `fmuls; fmuls; fadds` where other code in the function fuses: multiply through an inline helper (JumpDistanceMode_Update, 11-09)

Target (the rest of the function has `fmadds`, so `fp_contract off` is not it):

```
lfs f0,x; lfs f2,z; fmuls f1,f0,f0; fmuls f2,f2,f2; fadds f4,f1,f2
```

- `x*x + z*z` (named or direct) fuses into `fmadds`.
- `float xx = x*x; float zz = z*z; xx + zz` does not fuse, but the loads come
  out in the other order / other registers (3 to 5 lines off in ~80 variants).
- `#pragma fp_contract off` around an *inline* does nothing: the pragma state
  of the function the inline lands in decides.

Fix: `static inline float mul(float a, float b) { return a * b; }` and
`sqrtf(mul(d.x, d.x) + mul(d.z, d.z))` with the members passed directly (no
named x/z locals). The inline results are temps that are not fused, and their
numbering gives the target order. An inline `sq(float v)` or named locals as
arguments stay 3 lines off.

## 40. `addi rX,anchor,N` marks the start of a real object: split the pool there and index the object directly (Voice merge, 11-09)

MWCC never folds a constant offset into the address of an anchored object.
With the pool anchor in r31:

- `&obj[i]` where `obj` starts at anchor+N gives `addi rX,r31,N` followed by
  the index arithmetic.
- `(char *)base_obj + CONST` (a pointer into a bigger object, or a struct of
  the whole pool) gives two `addi`, or folds CONST into the load displacement.

So every distinct N in the target's `addi rX,r31,N` is the first byte of an
object of the original source. Read them off the target before writing the
pool: in the race voice unit that gave 0x80497BC4 (`addi r3,r31,3980`) and
0x804975C4 (`addi r8,r31,2444`) inside what looked like one 0xE00 float
table, and the item map at 0x80497DC4. An `addi rX,r31,N; lbz D(rX)` pair
with a large D is the opposite sign: a constant element index of the object
at N, not another object.

Once the objects are split and typed, the natural expression matches and
the Advance-pointer style inline helpers written to imitate the base+offset
form can go:

```c
return &lbl_80497BC4[(g_cupId - 1) * 16 + g_longRoundFlag * 8 + g_reverseRoundFlag * 4];
```

Related details from the same three functions (fn_801AC208, fn_801AECF4,
fn_801B1D5C):

- A single named static used in a function is not anchored (it gets its own
  `lis/addi`), so convert every pool use of the function at once; converting
  one use makes the diff worse first.
- `&(&obj[a * 128])[b]` keeps `a*128*4` and `b*4` as two shifts added
  separately (`slwi r5,r9,9` + `slwi r3,r3,2`); `&obj[a * 128 + b]` merges
  them into one index.
- A table pointer kept in a saved register across a call, copied for the
  first search loop (`mr r4,r29`) and walked in place by the second
  (`addi r29,r29,6`): a block local `VoiceItemMap *maps = table; int item = v;`
  passed by value to the first inline and by address (`&maps`) to the second.

## 41. A per-slot pointer that must be numbered below the `this`/self parameter: compute it inside a static inline taking (self, index) (fn_801502AC, 11-09)

Target keeps `self` in r27 and `slot = (char *)self + mode * 4` in r26; a named
local in the function itself gives the swap (slot r27, self r26), in every
declaration order. `regfix.py diag` says "create slot after r32 (temp)": the
slot must sit among the inline-expansion temps, below the parameters.

Fix: move the block that uses the slot into a `static inline` that takes the
ORIGINAL arguments and computes the slot itself:

```cpp
static inline void LoadCam_(RaceScene *self, int mode, const char *path) {
    RaceScene *slot = (RaceScene *)((char *)self + mode * 4);
    if (slot->objs[0] == 0) { ... }
}
```

Passing the computed slot as the inline's argument does not work: the argument
expression is propagated and the accesses turn into `lwzx/stwx`. Also in this
function: `lwzu r0,4(rN)` on a table field comes from using
`table[mode].id` directly at every use (CSE pointer temp), not from a named
pointer local. Rule: `shared-local-into-inline`.

## 42. `slwi; addi rI,rI,OFF; lhzx rBase,rI` (member offset added to the index): add the offset after the index (fn_801BDB60, AI_CalcLapSpeedBonus, 11-09)

Target folds a constant into the index register and loads indexed; ours forms
`add rP,rBase,rI; lhz OFF(rP)`. Every member/array spelling (`name.c[i + 1]`,
inline getters, `base + (idx + OFF)` with parentheses or an int local) gives
ours: the frontend folds or reassociates them the same way. What gives the
target is the constant added LAST, without parentheses:

```c
ch = *(unsigned short *)((char *)this + (i + 1) * 2 + 0x28);   /* (this + index) + offset */
bonus = ((const float *)table)[i * 5 + 4];                    /* float view: element index carries the offset */
```

Both are fakematch-marked: the natural source is not known. Found by
`leversweep.py detect` (the addi is not an anchor here; the detect heuristic
also catches this shape).
## 43. `x = new T(args)` vs `x = Alloc(); if (x) ctor(x, args)`, and three small shape levers (clFlowRound_Update, 11-09)

clFlowRound_Update went from 243 differing lines to 0 with these, no pragma:

- **new-expression.** A hand-expanded `p = Alloc(0x30); if (p) Sprite_InitWithAnim(p, ...)` stored into a
  member gives the result a backend temp that is coloured early. The real `self->slots[j].spr = new Sprite(anim, 0, 0)`
  gives a temp that is coloured late, and that moved `self` to r31 and shifted every saved register into place.
  Symptom: the pool base or a loop pointer holds r31 and `self` sits several registers lower. If the view struct
  lives in a namespace, write `(T *)new ::Sprite(...)` so the ctor symbol stays the global one.
- **for-scope counters.** `for (int i = 0; ...)` in each loop instead of one function-level `int i` (C++ scoping
  gives each loop its own vreg, declared later = lower number).
- **`a - -b`** compiles to `fadds a,b` in source order. `a + b` and `b + a` both get canonicalised the other way.
  Fakematch; use it only for the last operand-order line.
- **switch value reused after the switch.** Target `beq +8; b L+4` where L is `lwz r0,N(self)` and the branch
  lands on the compare after it: the source is `next = self->st; switch (next) { case -1: ...; next = self->st; break; }
  if (next != -1)`. objdiff shows this only as a 99.99% branch-target diff.

Diagnostic used: `#pragma opt_lifetimes off` cut the diff 243 -> 82, which showed that one more level-1 node
interfering with `self` was all that was missing. The pragma is not in the final source.

## 44. A base-address local survives only with two uses, and the first copy of an unrolled loop picks it up (Race_PerFrameTickAndAudio, 11-09)

Target, inside an inlined helper followed by a fully unrolled 8-way search:

```
addi r5,r30,400        ; base = &g_raceEntryArray (anchor + 400)
mulli r0,r0,104
add  r4,r5,r0          ; &base[idx]
...                    ; first unrolled copy
mulli r0,r3,104
add  r3,r5,r0          ; reuses r5
...                    ; copies 2..8
addi r3,r30,400        ; fresh address every time
add  r3,r3,r0
```

Rules read off the experiments (mweppc frontend, IroPropagate + CSE):

- `base = &g; entry = &base[idx];` with ONE use of `base` in the block is propagated away: the base
  address is folded into `entry` and the first copy gets its own `addi` (one instruction too many).
- With TWO uses of `base` the assignment stays a real variable, and a later direct `&g[...]` in the
  same extended block is replaced by that variable. Only the first unrolled copy is in that block,
  so copies 2..8 keep the fresh `addi`.
- The natural source is "no cached element pointer": `if (!base[idx].kart->finished) { if (base[idx].rank != 0)`.
  CSE builds the element pointer itself (r4), and `base` has two uses.
- A base passed into the search inline as a parameter is used by all eight copies (no `addi` at all).
  A base assigned before an earlier branch (other block) also survives, but its `addi` sits before
  that branch.

Other levers the same function needed, all register-only symptoms:

- **Inner search loop indexed, not walked.** `for (j...) if (entries[j].id != -1 && entries[j].rank == ...)`
  instead of a named `other++` pointer: the walking pointer becomes a strength-reduction temp that is
  coloured before the hoisted `&entry->rank` temp and the counter (target r5/r6/r7 vs ours r7/r5/r6).
- **Walk the base local itself in the last loop.** `for (k = 0; k < 8; entries++, k++) { entry = entries; ... }`
  when the target's last loop steps the register that held the base all function long. A copy
  (`entry = entries` before the loop) coalesces to the same register but leaves the base local with a
  lower cost than the section anchor, and the two swap r30/r31 everywhere.
- **Block-scoped counter for a `li rN,0` that ours turns into `mr rN,rZero`.** The last loop's counter
  as its own `{ int k; for (k = 0; ...) }` keeps its own `li`; the shared function-level `i` was
  value-numbered to the zero already held for the stores before the loop (rule `split-loop-counter`).
- **Increment order** `entry++, i++` vs `i++, entry++` swaps the two `addi` of one unrolled copy.
- **`signed char` lvalue for `extsb` from the raw byte**: field typed `signed char`, or
  `*(signed char *)&g_var`; an inline getter or a cast of an `unsigned char` read gets CSE'd differently.
- **Duplicated `li rX,1` for a result flag**: the if/else chain is an inline with `return 1` / `return 0`.

## 45. Locals of an inlined function are numbered in FORWARD declaration order (fn_80179F60, 11-09)

Symptom: instructions identical, only the registers of values loaded inside an
inlined helper rotate (here four `lfs` in `InQuad`: q[1] f6 / q[3] f9 / pos.z
f10 / q[5] f12, target f12 / f6 / f9 / f10), and `regfix diag` finds no
depth-2 edit. With the loads written inline in the call expressions they are
CSE temps whose numbers you cannot steer.

Fix: give every loaded value a named local in the inline, declare them all
WITHOUT initialisers at the top, and assign each at its first use (so no load
moves). The declaration order then sets the vreg numbers, and for the locals
of an inlined function the order is forward: first declared = lowest number =
coloured last (the caller's own locals are the other way round: last declared
= lowest). Read the wanted colouring order off the target: the value that
holds the lowest free register is coloured first, so it is declared LAST.

```cpp
static unsigned char InQuad(const float *q, const Vec3f *p) {
    float z0, x3, z3, x2, z2, pz, px, x1, z1, x0;   // target colours x0, z1, x1, px, pz, z2, x2, ..., z0
    x0 = q[0]; px = p->x; z0 = q[1]; z1 = q[3]; x1 = q[2]; pz = p->z;
    if ((QuadCross(x1 - x0, pz - z0, z1 - z0, px - x0) <= 0.0f) == 0) return 0;
    z2 = q[5]; x2 = q[4];
    ...
```

fn_80179F60 99.15 -> 100 (15 FPR vregs, three inlined copies at once).

## Still open (same shape, no fix found yet)

- r0 coloring quirk with a `0xFFFFFF00` rlwimi colour: clFlowCourse,
  clFlowGpPlease_Init (try pattern 11 first; both are onmokoworks claims).
- Value and table pointer swapped r4/r5 in two lookup loops:
  NameCheck_CardName. Tried 120 decl orders, temps, cmp swap, pragmasweep and
  20 minutes of cperm.
- Table base vs loop walker, copy direction reversed (11-08 diagnosis):
  ClRomTable_PurgeAll, fn_801E96BC, PCBCheck_ProcessLinks. The final registers
  per role are the same; the target materialises the base (`addi rB, sym@l`)
  and copies it into the walker (`mr rW, rB`), ours materialises the walker
  and copies it into the base. A minimal test (`base = tbl; for (i) { rec =
  &base[i]; ... f(rec, base); }`) always gives ours; walker forms, `&tbl[i]`,
  const base, scoped/inline loops, all opt_* pragmas: no change.
- Inline loop counter vs a colour computed before the loop, swapped saved
  registers: Menu801F0CC0 fn_801F1EE0, fn_801F2400, fn_801F20A0 (the colour is
  `MenuRGBA`/`WithAlpha` inline output). Decl orders, named inline results,
  open-coded vs SetColorRange loops: no change.

## onmokoworks Codex fixes (near miss -> 100 %, 2026-11-05..08)

140 functions that onmokoworks's Codex workers took from 97-99.x % to 100 % and that landed on main.
Our merge commits were named "Merge Codex worker batches", so the keyword scan above did not pick them up.
"Residual" is the remaining diff the worker saw before the fix; "Fix" is its last (successful) hypothesis, trimmed.
Grouped by a keyword guess at the lever, so read the fix text. `git show <commit> -- src include` shows the change.
No codegen pragmas, asm or fakematches were used (onmokoworks's workers are not allowed them).

### Local lifetimes / lexical blocks / variable reuse (25)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `PathManager_UpdateAll` | game/PathManager_UpdateAll.c | 99.95 | None: all 13 baseline feedback GPR rows resolved; all instructions, relocations, text size and owned EH/index exact. | H3 accumulator reuse inside distance helper: declare dx,dy,dz and reuse dy for squared-distance/Newton/result instead of separate distance. Nested boundaries preserve pointer scheduling; 100%, text5908/EH8/index12.... | 761816ab |
| `fn_8015AFCC` | game/Scene_8015AFCC.cpp | 99.93 | Resolved all five first-preload-loop register differences at 8015B320/324/32C/334/338: target r29 versus initial source r28. | Declare the existing function-scope index i before itemId, retaining every expression, loop and call: 100.0%; retained. Plain local declaration ordering fixes r29 without changing other instructions or EH. | 192e1cee |
| `PlayerData_Construct` | game/PlayerData_Construct.c | 99.92 | Resolved: mileage counter r21 instead of target r19 at 801D7568/7570/75F0/75F4. | 3. Directed declaration order: declare maximum before mileage in that dedicated block; 100%, counter becomes r19 and maximum r18. All other instructions and owned sections remain exact. | 22a15504 |
| `DrawEffect_KartWheel_TripleChildUpdate` | game/DrawEffect_KartWheel_TripleChildUpdate.c | 99.91 | Resolved two FPR operand rows at 0x800C2C88/8C: offset*inverse result f2 rather than target f1 and downstream operand difference. | H2 (same helper approach, accumulator refinement): Reuse helper offset for both intermediate products: offset*=inverseLength; offset=childScale*offset; return factor*offset. 100.0%, 900 B; both EH sections 100%. | 0d0eff15 |
| `KartShellRibbonDraw` | game/KartShellRibbonDraw.c | 99.91 | Resolved: hoisted half constant f30 / half-width f31 swap plus prelude dims/inverse64 f1/f0 scratch homes (seven initial operand rows). | {"attempt": 6, "family": "inline helper boundary and parameter reuse", "hypothesis": "Inline Ribbon_ScaledHalfWidth(half,width), accumulate the first product into width, and return the second product.", "percent":... | aedc2922 |
| `fn_801869F8` | game/objview/fn_801869F8.cpp | 99.89 | Resolved nine operand differences at +0x4EC/+0x4F0/+0x510/+0x52C/+0x534/+0x53C/+0x598/+0x59C/+0x630: final path pointer source r27 versus target r26. | H4 separate function-scope const Path186 *renderPath for final pass, keeping existing p for first two loops: 100.0%, exact 1676-byte text and 8/12-byte EH/index. Retained. | f089a13c |
| `DebugOverlay_DumpPcbState` | game/PcbDebugOverlay.c | 99.85 | Resolved four listener-register operand differences: source r27 versus target r25 at offsets 0x24, 0x28, 0x30, 0x40. | Extract primary portCycle/closeCount loads into static inline const-pointer accessors: 100%; listener reuses target r25 and all other instructions remain exact. | b91c40bf |
| `MObjMakeTExp` | sysdolphin/baselib/mobj_nm1.c | 99.84 | Resolved: lighting alpha_vtx flag used r28 versus target r24, while diffuse-stage exp_2 used r24 versus target r28; 20 operand-only differences at offsets... | Extract alpha_src & RENDER_ALPHA_VTX into static inline u32 MObjAlphaVtx(u32): creates a distinct inline result web and resolves the r24/r28 swap; 100.0%, exact 2508 bytes. | 7a5fd3e0 |
| `fn_8020C38C` | game/anon_8020BD68_nm1.cpp | 99.77 | Resolved seven cup-selection instructions using r29 instead of target r30. Expanding Factory exposes a final id/chara register swap; declaring id before... | Expand Factory into a constructor-local scope: 99.85876%, cup fixed and final id/chara homes swapped; directed declaration-order refinement (id, mode, chara) reaches 100.0% (retained). | 9edc94fe |
| `JObjUpdateFunc` | sysdolphin/baselib/jobj_tail.c | 99.76 | Resolved: type r28 versus target r27, path joint r27 versus target r28, callback walkers r27/r31 versus target r28; then unowned switch table relocation. | Inline path-point helper scopes the referenced joint pointer independently: 99.94098 -> 99.97471%; all register/instruction differences disappear. Owning the emitted jump table then yields100% text/data. | 5624a366 |
| `fn_80229398` | game/DNStartCamera_nm1.cpp | 99.75 | Resolved: eight first-loop register operands; target walker/index r27/r30 versus previous source r30/r31. All 203 instructions now exact. | Per-element UpdateFlash(self,i) helper, keeping six-iteration loop in Update: 100.0%; changes inline variable lifetime boundary without moving induction loop, restores both loops and all EH exactly. Retained. | 5b52c4d0 |
| `KartFx_BurnoutChargeTick` | game/KartFxBurnout.cpp | 99.75 | Resolved: owner/charging r29/r30; camera/character r28/r29; child cursor/count r28/r29/r30; camera-distance f0/f1 and character-scale multiply operand order. | Model-guided declaration lifetime/rank: owner before charging ->99.86224. Explicit function-scope camera/cursor/count declarations first probe ->99.82653, revealing flag sharing and cursor/count rank. Final order... | aabe6516 |
| `Effect_SparkPlain_Update` | game/EffectSparkPlain.cpp | 99.69 | Resolved: target lifetime f4 and pulse f2 versus source lifetime f2 and pulse f4/f3 at 800C5968..800C5980, five instruction rows. | Single compound lifetime * pulse expression with /2.0f half operations after float-rounded sin result: 100%; target lifetime f4, pulse f2, and arithmetic operand order restored. Retained. | a0bee72b |
| `dtor_801CDC68` | game/PanelCda40.cpp | 99.67 | Sentinel address addi/store used r7 instead of target r0 at 0x801CDC90/0x801CDC98; resolved. | H2: begin() reads head.next directly instead of incrementing end() temporary, shortening sentinel lifetime/CSE web: 100%; retained. | 744056e3 |
| `DebugOverlay_Dispatch` | game/DebugOverlay_Dispatch.cpp | 99.61 | Case 9 FP accumulator used f30 instead of target f28 across 19 instructions; all other instructions and owned sections were exact. | Give case 9 its own lexical block, accumulator and draw-time local instead of reusing case 1 other/draw variables. Distinct case-local lifetimes restore f28 accumulator and retain f31 drawTime: 100.0%. | 4a374555 |
| `fn_801987C4` | game/objview/fn_801987C4.cpp | 99.55 | Resolved all16 GPR operand differences: source resource r28/positions+counter r27 become target resource r27/positions+counter r28. | 2. Declaration/coalescing: declare the reused int i before resource and positions, so the counter/placement coalesced web gets r28 and resource gets r27: 100% text760/EH88/index12/rodata464; retained... | 7f37c8a0 |
| `fn_80173FA4` | game/ZoneVisibilityUpdate.cpp | 99.49 | Resolved: mask and compiler-generated array byte offset had r28/r29 swapped across five instructions. | Inline Zone::GetMask() const accessor produces a distinct inline-return web: 100% text with exact owned EH/index. | 39062fac |
| `ServiceMode_UpdateScheduleGate` | game/ServiceMode_UpdateScheduleGate.c | 99.44 | Resolved pure volatile GPR three-cycle: baseline weekday r9 vs target r11, hour-base r10 vs r9, minute-base r11 vs r10; nine operand differences at... | 3. Variable reuse family: cache time->wday in one int day, use it for current-day lookup, then day -= 1 and wrap -1 to 6 for previous-day lookup; 100% text320/extab8/extabindex12; retained. | ba36dd17 |
| `fn_80242E80` | game/fn_80242E80.cpp | 99.40 | Resolved: initial 12 GPR-only rows (item index/round r30/r31 versus target r31/r30; marker index/cursor r28/r30 versus target r29/r28). Final no instruction... | H3 pointer lifetime/declaration: in H2 declare int *p before mode/cup/round/i, assign p inside the loop: 100%, 500 B; all nine residual rows resolved, extab8/index12 remain exact. Retained. | 43e91654 |
| `fn_8020D00C` | game/anon_8020C974_nm2.cpp | 99.07 | Resolved extra li r3,1 in state=3 branch (baseline function 432B versus target 428B). | A static inline selection helper isolates the default mode local and permits reuse of the earlier constant 1: 100.0%, 428B. | d8d47578 |
| `card_unpack_legacy_dispatch` | game/CardUnpackLegacy.cpp | 99.06 | Resolved: checksum version and usage values had r26/r27 homes reversed; second used-bits result moved through r0, adding 4 bytes. | Direct DebugPrintf argument expressions restore right-to-left call evaluation and compiler temporary lifetimes; 100.0% text, extab, extabindex. | fb43691e |
| `DrawEffect_TickAndCull` | game/DrawEffect_TickAndCull.c | 98.78 | Resolved: target cursor=r30, counter=r31; baseline cursor=r31, counter=r30. No control-flow, timer-tail or instruction-count mismatch in baseline. | Whole pool loop plus view/count locals in static inline TickDrawEffectPool(), ScopedTimer retained in caller: 100%; exact 344-byte text and owned EH after new symbol bridges. | 441bcd34 |
| `fn_80221FC4 / ItemWnd::ShowOther` | game/anon_8021F088_nm_80221C94_nm1.cpp | 98.76 | Resolved: case-2 scale/alpha constant CSE hoisted lbl_806DB194 into f4, inserted fmr f1,f4, swapped timer-conversion r0/r4 and FP scratch homes, and removed... | H2: Spell the invariant alpha argument as native literal 1.0f so it is distinct from the externally loaded scale initializer. 100% text/extab/index; retained. Original declaration order restored and remains 100%. | ff34c519 |
| `SceneModel_Init` | game/SceneModel_Init.cpp | 98.67 | Resolved: chain prev/index/base r6/r4/r5 vs target r4/r5/r6; separate-loop count/output/stride r28/r29/r30 vs target r30/r28/r29 (19 differing register... | C: natural inline light-loading helpers give independent compiler variable scopes. Separate chain/separate helpers fix both register groups but bool return emits +20B (94.45744%). Enclosing LoadSceneLights owns... | e4d5f6b6 |
| `fn_802170F0` | game/anon_80216568_row_nm.cpp | 97.63 | None. Source and linked ELF function bytes equal target bytes. | H3, declaration scope: move only the sprite local from loop scope to function scope, keeping H1/H2; 100%, iterator/sprite become target r8/r7 and every instruction matches. | 8c1a9897 |

### Declaration order (8)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `fn_801F7F50` | game/fn_801F7F50.cpp | 99.92 | Resolved: six initial instruction rows at +1C/+20/+24/+28/+44/+48. Baseline computes height before width and exchanges fabs-result input registers during... | H2 targeted declaration-order lever: with H1 products retained, declare h before w (all other locals unchanged). Fixes the isolated f5/f6 swap; 100.0%, 708 bytes. Retained. | 8258c4ef |
| `DisplayContext_Flush` | game/DisplayContext_Flush.c | 99.83 | Initial: count r30 and compiler-generated byte offset r31 instead of target count r31 / offset r30 at 801DB490/498/4A8/4B0/4B8. Final: none. | H2: Represent byte offset as explicit int offset declared before count/i, keep self->entries reload in each iteration, advance by sizeof(DebugTextEntry). 99.87778%; count/offset homes become exact. Refinement:... | 12e68d9b |
| `GameTestTopMenu_Page` | game/GameTestTopMenu_Page.cpp | 99.35 | Resolved: extra mr r28,r0 for cabinet-2 table setup; then standard-loop index/selection r30/r31 swap. | 3. Keep standard selection calculation local to its helper: initially unchanged 99.78395%; targeted index-before-selection declaration order for these plain local webs resolves the observed swap: 100%. | ac5be6a6 |
| `fn_80201BE8` | game/anon_8020007C_nm1.cpp | 99.29 | Resolved: g_ccClass and model-name lwz instruction order; readonly pointer-element qualification was missing. | {"hypothesis": "H6: declare the .rodata table as const char *const rather than const char *", "percent": 100.0, "result": "Restores g_ccClass load before the name-pointer load without moving the member store; retained."} | 4a39829f |
| `card_unpack_v1` | game/CardUnpackV1.c | 98.99 | Resolved. Initially 0x800902F8..0x8009031C used r4/r0 for boolean normalization and merged scratch-zero initialization with index r24, omitting li r0,0 (608... | H3 declaration order: on H2 declare u16* cursor before name-loop int i. 100% text612/extab8/index12. Retained. build/w/attempt_3.c and attempt_3.json. | e5223334 |
| `fn_801807E0` | game/miyazakiconsole/fn_801807E0.cpp | 98.97 | None. Baseline had two extra li r0,0 instructions before buffer-clear stores; each target store uses the initialized column counter instead. | H2: Extract both row/column loops plus line draw into shared inline DrawBorderFrame. Initial text 99.248825%, now only plain row/column local swaps. Declare col before row per allocator model: text/extab/extabindex... | 10f7f8cf |
| `fn_80246484` | game/RaceDigitUpdate.cpp | 98.89 | None. All text instructions and owned data/EH/relocations exact. | H6 reference render helper: ShowHudSprites(DigitHud&, int) inlines loop, recovering all GPR homes. Initial 99.9377% with four FP x/y swap rows. Within this helper, declare x before y while computing y first, then x:... | a33ca3a2 |
| `fn_8021FC4C` | game/anon_8021F088_nm_8021FC4C.cpp | 98.89 | Resolved: total-line table index bias folded into displacement at +0x594/+0x8D4; final unrolled loop counter/line pointer r6/r7 swap at +0x934..+0x9F0. | Declare clGetCoinLine *l before int i outside final loop: restores line pointer r6 and counter r7, 99.7619 -> 100%. | 854e9a5e |

### Literal vs extern constant (24)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `GabyouItem_Update` | game/GabyouItemUpdate.cpp | 99.88 | Initial: eight operand rows at +0x314/+0x31C/+0x320/+0x32C and +0x3E0/+0x3E8/+0x3EC/+0x3F8, velocity.y f1 versus target f2 and turn f2 versus target f1.... | 3. Float constant representation: use literal -0.1f for gravity and literal 0.087266445f for turn argument. Exact 100% text/data/EH/index, unchanged 1308B. Retained. | 262a1b67 |
| `ItemObject_CheckKartCollision` | game/ItemObject_CheckKartCollision.c | 99.83 | Initial: fmuls multiplicand operands reversed at 0x800D798C and 0x800D7990 (f4,f1 / f4,f0 instead of f1,f4 / f0,f4). Final: none. | Use literal scaled radii (10.0f * scale) * k and (40.0f * scale) * k: 100%; standard sdata2 postprocess maps literals to existing target labels. | 0db1f33a |
| `KartFx_Slot5C_TripleStreakTick` | game/KartFxBoost.cpp | 99.82 | Resolved. Start: seven FPR identity rows in fade at 800B9DF4/9DF8/9DFC/9E00/9E08/9E0C/9E14; target current f2, decrement/result f1, minimum f0, reload f1.... | H4 separate genuine float faded = current - decrement temporary on H2, then effect->opacity = faded. 100%, 1004 B, extab/extabindex100. Correct non-accumulator result coalescing with literal minimum; retained. | 68edb7ca |
| `fn_80197130` | game/objview/fn_80197130.cpp | 99.77 | Baseline has only four mismatching instructions: height f31 vs target f30, width f30 vs target f31, at function offsets 0x64, 0x70, 0xDC, 0xEC. Final... | Replace external float objects with exact float literals (0.5f, 0.01745329238474369f, 0.0f, 0.1f) so compiler creates native literal expression webs; 99.76852 -> 100.0. | 8b38cd7c |
| `fn_802124FC` | game/anon_802124FC.cpp | 99.76 | Resolved final spin-update volatile FP register cycle: target current f2 / increment f1 / limit f0, source f1/f0/f2. | Use plain 1.0f and 360.0f literals only in final spin update: 100.0%; no other function changes. | d0ef33f3 |
| `KartFx_DriftSparkParticleTick` | game/KartFxDriftSparkParticle.cpp | 99.74 | Resolved 10 FP rows: initializer zero first loaded into f3 instead of f1 (800BBD50/58/5C); bounds position f0 and upper bound f2 instead of position f2 and... | External constant loads have different compiler value-numbering provenance from literal constants. Use 0.0f/-0.1f velocity arguments and -1.1f/1.1f bounds; ordinary postprocess_sdata2 restores canonical references:... | d6ad24eb |
| `fn_80167A24` | game/misc3d/fn_80167A24.cpp | 99.62 | Initially nine instructions with f10/f11/f12 constant/product register cycle; final residual none. | Use ordinary float literals instead of external named constant loads, changing compiler constant representation before register coloring: 99.61539 -> 100.0. | 465f5bae |
| `fn_801B739C` | game/fn_801B739C.cpp | 99.50 | Resolved nine FP register operand mismatches at 0x801B74D0..0x801B74F4 in length decrement / lower-bound clamp. Baseline difference: delta f1 vs f2, scale... | H2: Express numeric lower bound as 0.0f literal; compiler constant web differs from external symbol load, producing target f0 minimum/f1 length/f2 delta/f3 scale; 100%. Existing postprocess_sdata2 maps literal to... | e22223a0 |
| `fn_801C6744` | game/FigureSlot_Tick.cpp | 99.42 | None. All 1224 text bytes and owned 40-byte EH / 12-byte index exact. | 3: Use target-verified ordinary 12.0f literal for scalar helper divisor: 100.0%; fixes bias/divisor/start FPR homes. Existing postprocess_sdata2 maps literals to target labels. | 8d6ecb4f |
| `ClStream_UpdateAll` | game/clstream/ClStream_UpdateAll.c | 99.41 | Explicit external message-base pointer introduced extra addi before stmw and mr instead of addi at first DebugPrintf. +4 text offset also prevented shared... | Native string literals with readonly_strings and owned .rodata: exact 1708B instructions; split string symbols resolve remaining R_PPC_NONE identity differences; 100.0%. | 5be85896 |
| `fn_8022760C` | game/DNBress_spawn2_nm.cpp | 99.21 | Resolved f6..f10 cycle: scale f9 vs target f10, alpha/random f6 vs f7, speed coefficient f7 vs f8, grow coefficient f10 vs f6, position scratch f8 vs f9 (14... | Replace external scalar constants with exact float literals; compiler constant webs recover target FPR allocation. 99.207924 -> 100.0; extab/index unchanged at 100%. | ecfa0ed6 |
| `ItemObject_Tick_Kind28_BananaTrioSpawner` | game/ItemObject_Tick_Kind28_BananaTrioSpawner.c | 99.14 | Resolved: missing switch branch at target 0x800E0B74 and f0/f1 exchange in blend-factor calculation 0x800E0C80..0x800E0CA8. | Use native 1.0f literal for blend upper clamp rather than external constant: correct constant provenance restores short-lived FP register homes, 100% all owned sections. | 63337f83 |
| `fn_80227318` | game/DNBress_spawn1_nm.cpp | 99.10 | Resolved FP home cycle: grow constant f8 vs target f4; scale f6 vs f7, alpha/random f4 vs f5, speed multiplier f5 vs f6, position scratch f7 vs f8 (15... | Use plain numeric float literals instead of named external constants, allowing compiler constant webs and postprocess_sdata2 mapping: 100.0%. | 79144624 |
| `setupTopHalfCamera` | sysdolphin/baselib/cobj_nm1.c | 99.08 | None. Initial residual was an extra fmr f0,f2 in first scissor bottom clamp and f0 versus f2 phi destination, causing 616 B instead of 612 B and shifted... | H4: Read viewport.ymax directly in comparison and true arm of ternary instead of preloading bottom: 100.0%, 612 B; removes extra move, all constant relocations bind through existing postprocess. Retained. | d9840645 |
| `Effect_Cluster16_Update` | game/EffectCluster16.cpp | 99.05 | Resolved: FP register allocation across growth/limit/scale/alpha and missing unreachable branch at 0x800C63DC in alpha switch. | 3. Spell full variant domain in alpha switch, leading with case 2: break; case 3: break; followed by cases 0/1 multipliers; 100%. Reproduces unreachable branch and restores literal externalization at correct offsets. | 241aa816 |
| `KartPair3ArmUpdate` | game/KartPair3ArmUpdate.c | 98.79 | Resolved: lower-bound constants were kept in f2, eliminating two target reloads (-8 bytes); line-table/yaw aggregate stack slots differed; character and... | 3. Express reflection as c->yaw[i] *= -1.0f: 100%; fixes both constant/yaw FP load-register pairs. | b9c1e40d |
| `fn_8023CDA8` | game/SpritePairOwnerTick.cpp | 98.73 | Resolved: clamp FP temporaries/constants had wrong FPR homes; target upper=f0, alpha=f2/f1, lower=f0. | Use numeric float literals (1.0f, 0.0f, 0.0165f, 255.0f), removing the captured external upper bound; result 100%. | 5599c7c2 |
| `Item_SpawnHitBurstParticles` | game/ItemHitBurst.c | 98.72 | Resolved: count/signedKind r28/r29 swap and extra fmr f3,f0 after Rand_RangeFloat (456-byte baseline object vs 452-byte target). | H2: Use literal 0.0f for the two constant arguments, allowing post-call loads, and swap count/signedKind declarations according to observed local register homes. 100% text/extab/extabindex. | 9539ff84 |
| `fn_8022BBC8` | game/EnemyFace_nm3.cpp | 98.72 | None. Baseline inline clEFace3D parameter r5/r4, sentinel r4/r0, slot result r0/r3 and li scheduling residual resolved. | H1 metadata refinement: remove unused TU-private KartHidden helper (no emitted use), preserving original anonymous literal @91/@92 and EH @93/@94 numbering without modifying existing bridge entries.... | e00946db |
| `fn_8021A1C4` | game/anon_80219FF4_nm1.cpp | 98.58 | Resolved: FP register homes in alpha sum/clamp (+0x58..+0x98), external const loads used f1/f0/f2 instead of target f2/f1/f0. | Use ordinary float literals 1.0f, 0.0f, 0.0165f for limits and animation step; existing sdata2 postprocess maps to original external labels: 100%. | 5d8cb49b |
| `fn_8023CEB4` | game/SpritePairOwnerTick.cpp | 98.48 | Resolved: clamp FP temporaries/constants had wrong FPR homes; target upper=f0, alpha=f2/f1, lower=f0. | Use numeric float literals (1.0f, 0.0f, 0.0165f, 255.0f), removing the captured external upper bound; result 100%. | 5599c7c2 |
| `Item_ComputeBiasedTargetPos` | game/Item_ComputeBiasedTargetPos.c | 98.43 | Resolved: zero-horizontal fallback passed z=0 instead of scaled reach in f3; reciprocal multiplication operand order; extern constants changed FP... | 3. Use native float literals with existing sdata2 postprocess: 99.69879%; natural if(mag) restores target compare operand order, 99.819275% with only unowned jump-table relocation differences. Assign emitted table... | 01cbf4b9 |
| `fn_801D9B70` | game/FlowPanelUpdate.cpp | 98.21 | None: text, automatic extab payload/relocation, and extabindex are exact. | Match fade constant provenance/expression shape: all-external fade-in 99.503815%; explicit elapsed/fraction staging byte-invariant at99.618324%; keep fade-in 8/1 literals and external0.125, use fade-out1/0 literals... | 22b824dc |
| `setupBottomHalfCamera` | sysdolphin/baselib/cobj_bottom.c | 97.01 | None; owned text is 100%. | Round tan argument to float: 99.748604%; canonical shared constant pool and B isolation: 100%. | e47c9d05 |

### Inline helper / function boundary (36)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `fn_8017CE1C` | game/mapobject/fn_8017CE1C.cpp | 99.98 | Resolved: at +0x514/0x524 target mode r30 versus original source r31 (srwi/mr). Final instructions, relocations and all owned sections exact. | H3: Retain H2 and extract selection-7 menu construction into nested inline SelectCharacterMenu(base): 100.0%; restores menu pointer r30 and preserves mode r30, all sections exact. | f0eee4e5 |
| `fn_8020579C` | game/anon_802052E0_nm1.cpp | 99.96 | none | Wrap ONLY converted-row plus origin in static inline TextRow(float row,float origin), returning row+origin: 100%; fixes fadds f2,f30,f2 to target fadds f2,f2,f30 with all other instructions preserved. | 484e8743 |
| `GabyouItem_ReturnToHandTick` | game/GabyouItemReturn.cpp | 99.95 | Resolved: target lfsx f31 at +0x1C4 and fmuls f1,f0,f31 at +0x1E0 versus draft f30 in both instructions. | H6: Inline indexed radius and reciprocal directly into Vec3_Scale argument: 100%; no named length or helper parameter. MWCC evaluates the right operand first, preserving index call, radius load, magnitude call and... | faa5b902 |
| `EffectVfx84_85_BoostChargeRing_Tick` | game/EffectVfx84_85_BoostChargeRing_Tick.c | 99.94 | Resolved: three Vec copies used cyclically displaced stack slots. Target transform argument copies at sp+0x20 and sp+0x14, setter copy at sp+0x08; baseline... | Replace explicit top-level Vec pos local with a static inline setter taking Vec by value and forwarding its address: 100.0%. Compiler-created argument temporary follows the two transform argument temporaries and... | f2932431 |
| `CardDataCheck_UI` | game/CardDataCheck_UI.cpp | 99.90 | Resolved eight drawing-loop cursor/index register differences, then four index/selection differences; no semantic or instruction-count residual. | H6: Make selection a helper local, declared between index and cursor, and compute from self->sub: 100% text/extab/extabindex. All four remaining instructions exact. | 0ee9be05 |
| `fn_801AF850` | game/fn_801AF850.c | 99.88 | Resolved all 15 instructions: raw course-ID sum / queue-byte-offset swapped r8/r9 in cups 6/7 and r7/r8 in cup 8. | Extract only base+round arithmetic into static inline int CourseVoiceId(int base, int round), retaining caller int voice and existing short-parameter push; inline return web resolves homes: 100.0%, 2976 B. | 5ebf4a73 |
| `fn_802128F4` | game/anon_802124FC_nm1.cpp | 99.86 | Resolved: two speed-scaling sites had FPR scratch/coalescing differences. Initial 7 rows: step load/product f28 vs f1; speed f2 vs f0; int conversion... | 2. Keep getter and compute both products through static inline MultiplySpeed(float factor,float speed), returning factor*speed. Separate inline argument/result webs resolve all four rows: 100.0%, 1456 bytes. | 4f389ea7 |
| `fn_801D2F0C` | game/anon_801D2F0C.cpp | 99.83 | Resolved: target +0x150 lfs f3,z then +0x154 lfs f2,y; baseline had y then z. Also resolved baseline constants accidentally renamed to EH symbols. | Inline scalar RankingPlacementY/RankingPlacementZ getters inside PSMTXTrans arguments preserve canonical float field types and right-to-left argument evaluation: 100.0%; retained. Unlike prior reversed-argument... | 88ce6cad |
| `ItemCollision_Check` | game/ItemCollision_Check.cpp | 99.83 | Resolved: owner team ID target r29 versus source r27; RankLog pointer target r27 versus source r29, across nine instruction rows. No control-flow or EH... | H1: read owner team through static inline ItemCollision_GetTeam to reproduce getter inline boundary/web formation; text/extab/extabindex all 100%. | 23b5409f |
| `DriveBehavior_HandleWpType` | game/DriveBehavior_HandleWpType.c | 99.82 | Resolved five post-sin FPR rows at 801DEA44/48/4C/50/54: complement f0 -> target f4, first result f3 -> f0, second result f0 -> f1 and matching stores. No... | H1: Extract phase-to-wave conversion into static inline float DriveWave(float phase), returning sin(pi_float * phase), while preserving the existing caller accumulator sequence. This puts float rounding at the helper... | fc669dcf |
| `fn_80162D90` | game/Scene_80162D90.cpp | 99.82 | Resolved all six final tracker-pointer operands (+0x248/+0x254/+0x25C/+0x260/+0x268/+0x270), source r31 versus target r30. No remaining object differences. | H2 early inline boundary: static inline unsigned char HasNoCredits(const CreditPanel162*) returns panel->credits <= 0; use its result for cached noCredits. 100%, 684 B text / 8 B EH / 12 B index; retained. | b460fd81 |
| `fn_8018A418` | game/bbox/fn_8018A418.c | 99.80 | Resolved six FP result operands: baseline timer sums/compare/store used f2, target f1 at 8018A494/498/49C and 8018A4BC/4C0/4C4. | H1: static inline AdvanceFrameTime(Frame *frame, float step) reads frame->time, assigns step = frame->time + step, stores step and returns it; both caller paths pass 1.0f. Result 100.0%, preserving old-time f2 and... | bc52d53d |
| `fn_80190D24` | game/clsound/fn_80190D24.c | 99.77 | None. All target instructions and owned EH match. | 1. After verifying queue fields against the storage owner, mirror the existing matched sibling queue idiom: base q, current cursor e, explicit predecessor k=i-1, aggregate tmp=*e, decrement i before fieldwise q[k]... | 5ea11949 |
| `fn_8021713C` | game/anon_80216568_row_layout.cpp | 99.77 | Resolved: width f0/spacing f1 versus target width f1/spacing f0, and final fadds operand order. | Advance(sprite,gap) inline helper with named delta = gap - width and return delta + spacing: 100%. | f20cfdfc |
| `fn_80226B20` | game/DNBress_nm1.cpp | 99.75 | Resolved: target 80226B94 mr r30,r29 vs original li r30,0; every other instruction already exact. | Move unchanged kart search loop into static inline FindActiveKart returning KartRender*: restores shared zero initialization, 100.0%. | c0588a33 |
| `fn_801FBE14` | game/fn_801FBE14.cpp | 99.74 | Resolved input/creditOnly r30/r31 swap (12 instructions); no remaining residual. | Small unsigned-char-returning IsCreditOnly inline helper: target register identities restored, 100% text/extab/extabindex. | fc86b78f |
| `Sci2Card_BuildScoreReceiptLine` | game/Sci2Card_BuildScoreReceiptLine.c | 99.73 | Resolved: title inline helper emitted an extra branch; wins-label/cursor r24/r26 swap; final helper-parameter wins r24 versus target r25. | H3: isolate number conversion in static inline helper: 99.97345% with int wins argument; read wins as a helper-local instead to restore target local web: 100%. | b0571482 |
| `fn_801F6C2C` | game/fn_801F6C2C.cpp | 99.73 | Initial: fmuls multiplicands reversed at 0x801F6CB4 and 0x801F6CBC; final: none. | Extract multiplication of the near-edge coordinate and reciprocal size to a static inline float helper, called for left/top only: 100.0%, both operand orders fixed with no other instruction changes. | e4054d04 |
| `CardDataTransfer_UI` | game/CardDataTransfer_UI.cpp | 99.54 | Resolved: duplicate li 1 for default status vs step/status initialization, menu walker/index/selection GPR homes; extra instruction shifted literal... | Natural inline Begin(self, initialStatus) plus TU-local DrawItems(self, selection) with local table: 100% text/extab/extabindex. Helper boundaries share initial value in r30 and give menu walker r30/index... | 403477fe |
| `fn_801E68B4` | game/fn_801E68B4.cpp | 99.53 | Resolved: squared length/result f3 instead of target f4, Newton half constant f4 instead of target f3. | Use caller-local squared length with a void inline float-reference in-place square-root helper instead of a by-value parameter/return helper: 100.0%. | 2102b089 |
| `GameModeBase_Dtor` | game/GameModeBase.cpp | 99.47 | Resolved: player-data base/value r3/r4 versus target r4/r3 at 800A0900..800A0914. | Use signed remaining field and inline member decrement, consistent with CardPrintFlowUpdate view: 100%. | 4ad04c9b |
| `fn_801FB778` | game/fn_801FB778.cpp | 99.39 | Resolved: final singleton pointer used r3 instead of r4 and kart load occurred after the singleton null branch rather than before it. Final residual none. | 2. Inline receiver boundary: UpdateKart(void *kart) receives the panel first and performs SINGLETON_INSTANCE plus dir normalization inside its body, instead of computing input in the outer function. 100%; target r4... | 51bf09aa |
| `Item_HomingScanAndSteer` | game/ItemHoming.c | 99.29 | Resolved: f0 intermediary and extra fmr on direct yaw; li r28,0 instead of mr r28,r29 in scan initialization. Final residual: none. | 3. Recover inline ItemHoming_FindTarget for candidate selection while retaining caller scanOrigin copy: 99.67811%, 932 B; stack offsets and zero-copy instruction become exact, leaving only scan GPR/FPR swaps.... | 18c3dd0f |
| `roll2upvec` | sysdolphin/baselib/cobj_nm2.c | 99.19 | Resolved: same folded output-pointer validation branch (+4 bytes); restored offsets allow normal sdata2 postprocessing to map every literal relocation... | Use the same nested output-pointer validation in the inline eye-vector helper: 100.0%. | 59485ee9 |
| `ClStream_PlayStereo` | game/clstream/ClStream_PlayStereo.c | 98.97 | Resolved: baseline saved r24-r31 instead of r25-r31; left/s r28 vs r29, i byte offset r29 vs r28, file r24 vs r25, j byte offset r25 vs r30, t r30 vs r26.... | Route stream address lookup through static inline GetStream(index), matching an accessor boundary and changing inline-spliced register webs: text/extab/extabindex all 100%. | 9a96e99b |
| `fn_8028B180` | triforce/amjvs_nm5.c | 98.75 | Resolved: initial clear used volatile r3 plus extra mr r31,r3 (596 B), whereas target materializes the manager directly in saved r31 (592 B). | H2c refinement: swap manager/count declaration positions in inline helper, as indicated by inline-splice allocation model; 592 B / 100.0%, manager r31, semaphore r30, count r29. | 3b57ea13 |
| `fn_8016FA50` | game/mapeffect/EffectFA_Ctor.cpp | 98.58 | Resolved: both loops had a three-way r26/r27/r28 identity cycle. Model loop target source walker r27, counter r28, destination walker r26; baseline... | H3: Retain model-loop helper; restore parts loop in constructor with its counter declared before MapEffectDef pointer. Counter takes target rank without helper scheduling changes: text 100%, 452 B; extab and index... | 2a9667a6 |
| `Effect_KartJoint12_3Stage_Update` | game/EffectKartJoint12.cpp | 98.52 | Resolved: second-loop child/table r29/r28 versus target r28/r29, and fraction/alpha-base f1/f2 versus target f2/f1. Final residual none. | H5: Per-child updateChild(row,group,effect,i) inline helper, called by original indexed loop; 100%, 756B, restores table r29/child walker r28 without changing counter, schedule or EH. Retained. | 72b7c448 |
| `fn_8023B318` | game/KartChoiceSelect.cpp | 98.52 | Eliminated: source flag initialized in volatile r5 and copied into dead status r31; target retains independent r28 from flag initialization through... | Small static inline ChoiceChanged(status, choice) owns BOTH TestChoiceFlag and conditional choice != -1 validation, then returns unsigned char: 100% text, extab and extabindex. This differs from c18 output-reference... | 7fc26664 |
| `fn_802086AC` | game/anon_80207E3C_nm1.cpp | 98.50 | Resolved: baseline a/b=r28/r29 instead of target r30/r31 and pa/pb=r31/r30 instead of r29/r28; missing nested type lwz/cmpwi pairs at offsets 0x2DC/0x2E0... | {"idea": "Use a TU-local static inline int Col_GetType(const CollisionObject*) accessor for the generic Col_Support type check only.", "result_percent": 100.0, "result": "Restores both reload/compare pairs and all... | d55a1da8 |
| `Item_BendVelocityByGroundProbe` | game/Item_BendVelocityByGroundProbe.c | 98.15 | Resolved yaw-result precision/store: target frsp f0,f1 at +0x148 and stfs original f1 at +0x14C; original draft stored rounded f0 at +0x158. Inline... | H3: Keep ground queries in outer function and factor only final yaw-frame rotation into static inline BendInYawFrame(vel,pitch,&groundY). 100%, 432B; all stack slots, instructions and relocations exact; EH/index 100%. | 5c70d00c |
| `Terrain_GetTractionFactor` | game/Terrain_FlagsToTypeId_nm1.c | 97.59 | None. | H2: move only factor selection into static inline Terrain_TractionForFlags after caller normalization: 100%, 116B. Restores andis. mask and all target homes. | 73eae11a |
| `fn_802064D8` | game/anon_80205DCC_m2.cpp | 97.56 | Resolved: right-to-left Show argument evaluation, cached scale loads, and FP coordinate homes. | Scale-first multiply in axis helpers plus Japanese py-before-px declarations: 100.0. | 354e45b4 |
| `fn_8016E568` | game/mapeffect/CoursePropCtor.cpp | 97.33 | Resolved: early redundant table addi/mr, pool/resource/model-offset register partition, and pointer-selection merge; owned EH PC spans now exact. | {"id": 2, "family": "inline helper return boundary", "hypothesis": "SelectCourseProps() returns the native array for the round flags; retain traversal local in constructor.", "percent": 99.559746, "size": 636,... | d328db64 |
| `fn_80287EE4` | triforce/amboot.c | 97.26 | Duplicate lis 0x8120 in save-region fallback: address subtraction used r3, then end was loaded separately into r31; extra instruction and differing argument... | Extract a static inline save-region helper with a size parameter: 100%; compiler shares end in r31 and emits target argument schedule. | 3ec6135e |
| `CardSnapshot_ResolveCommonItems` | game/CardRewardSnapshot.cpp | 97.15 | None. | Extract real inline CountOwners(snaps,item) helper: 100%; restores target owner-count scan register partition and instruction schedule. | 004deaaa |

### Types / signedness / const / struct shape (21)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `RaceScene_Init` | game/RaceScene_Init.cpp | 99.98 | Resolved: first slot loop target clrlwi. r3,r3,24 then mr r26,r3; original declaration emitted clrlwi. r26,r3,24 then mr r3,r26. | H3 actual callee type: ItemSelect.c defines int ItemSelect_GetSlotItemId, so correct the TU-local unsigned-char declaration to int and retain byte local narrowing. 100.0%; exact all four owned sections. | 988f4d42 |
| `VfxSlotMgr_Update` | game/VfxSlotMgr.cpp | 99.94 | Resolved eight outer-copy stack offsets: target at SP+4C, position at SP+58; no primary instruction residual remains. | H3 copy semantics: retain H2 snapshot and provide Vec copy assignment with the same bit-preserving three-word copies as its existing copy constructor. 100.0%, 496B; all text and owned EH/index exact; retained. | 563dd718 |
| `fn_8017EFFC` | game/miyazakiconsole/fn_8017EC90.cpp | 99.90 | Resolved: target 0x8017F1D4 lwz r0,0x64(r1) then 0x8017F1D8 lwz r28,0x50(r1); old declaration emitted these in reverse order. Root cause: unsigned-int... | H4: Match the real callee signature unsigned char fn_801915DC(int), established by src/game/clsound/fn_801915DC.c and target lbz return. 100%; fixes LR/r28 epilogue scheduling and preserves both other functions.... | 055c08da |
| `fn_80204F68` | game/anon_80204474_nm3.cpp | 99.86 | Resolved four register-argument differences: cached list r30 vs target r31 and visible r31 vs target r30, at offsets 0x58/0x68/0x18C/0x1C0. | Control experiment with original unsigned-char local and separately named allocated YesNoSpark pointer before list insertion: 99.863014%, invariant; reverted. | 359f90e4 |
| `fn_8016C94C` | game/mapeffect/PointListConstruct.cpp | 99.84 | Initial residual: two adjacent Z lfs instructions at function offsets +0x70/+0x74 reversed. Final residual: none. | {"id": 6, "family": "alias information / types", "description": "Qualify constructor spawn parameter and walking cur pointer with __restrict.", "percent": 100.0, "result": "Corrects adjacent Z-load scheduling,... | 9f025c5c |
| `Camera_Create` | game/Camera_Create.cpp | 99.82 | Resolved: +0x38/+0x50 pool HA/LO r3 instead of target r9; +0x40/+0x54 derived-vtable LO/store r7 instead of target r3. | H2: Reference each owned static array directly and remove the obsolete explicit pointer/offset interface. Actual instructions and relocations reach 100%; target string boundaries plus the exact 83-byte split make... | 4c3ace93 |
| `Effect_KartOrbitSpark_Update` | game/EffectKartOrbitSpark.cpp | 99.71 | Resolved: half constant f2 vs target f1, amplitude f1 vs target f2, and first two pulse multiply operand identities (five instructions at offsets... | H2: express both half scalings as division by 2.0f so reciprocal lowering retains left accumulator operand: 100.0%; both multiply instructions exact. | 4e10fffb |
| `dtor_8005F778` | game/clItemBoxManager_ListDtors.cpp | 99.67 | None in the produced Matching TU. | Direct sentinel/next construction in the real three-level C++ destructor hierarchy: 100%; isolated private layout avoids affecting the manager destructor. | 3832c94e |
| `dtor_8005F7F0` | game/clItemBoxManager_ListDtors.cpp | 99.67 | None in the produced Matching TU. | Direct sentinel/next construction in the real three-level C++ destructor hierarchy: 100%; isolated private layout avoids affecting the manager destructor. | 3832c94e |
| `fn_8024A2F0` | game/CardSetupFlowResult.cpp | 99.67 | Resolved: aggregate-copy destination base r18 vs target r17; unlockIdx temporary r17 vs target r18, 31 formatted instruction differences with identical... | Model +0x18C unlock index as a four-byte nested value object in a TU-private snapshot: 100%, including after giving the value object a named type and adding size checks. | fe646cad |
| `fn_801A9D58` | game/sprite/fn_801A9D58.c | 99.66 | Resolved: 12 differing instruction rows at offsets 0x9E0..0x9F0, 0xC50..0xC60, 0xD1C..0xD20: kart scratch homes and prematurely hoisted global ranking-path... | H2 correct actual data types: callee src/game/Race_CompareKartProgress.c consumes integer participant indices, not pointers. TU-private MidRaceKart participantIndex at +0x2AC and int call arguments yield 100%, 4620... | 28da83ed |
| `fn_801F52A8` | game/fn_801F52A8.cpp | 99.63 | Resolved: cases 13-15 player/direction, down/held and loop-bound constants had r27/r28/r29 partition differences. | Use bool rather than unsigned int for all three relational direction results; exact 100.0% text, data, extab and extabindex. | f7657d3f |
| `fn_80184F24` | game/dlistutil/fn_80184F24.c | 99.38 | Resolved all 52 differing instruction rows. Start: target jobj/out/capacity/offset = r23/r24/r25/r22 versus source r22/r23/r24/r25; final exact. | H1 (semantics / induction ownership): replace manually maintained byte offset and casted base+offset with quad = &out[count] in both primitive branches. MWCC strength-reduces the array index into the target 60-byte... | 96bd5d83 |
| `DrawEffect_Cb_RalySmokeVariant_Tick` | game/DrawEffect_Cb_RalySmokeVariant_Tick.c | 99.03 | Resolved: entry addi r3,r4,joint-table@l was after lwzu r26,direction-table@l(r5); both native local aggregate initializers reproduce original scheduler order. | H6 native local direction AND joint aggregate initializers: 99.80676% before section ownership, all instruction opcodes/registers/order exact with only table relocations unpaired. Function-local const joint-name... | c6d5adb8 |
| `fn_801903D0` | game/objtable/fn_801903D0.cpp | 98.98 | Resolved external-byte-block base: source addi r3,r3,lo + mr r31,r3 and first-site mr r4,r31 versus target addi r31,r3,lo and addi r4,r31,0; extra... | Reconstruct eleven real file-static typed geometry arrays and refer to each directly, allowing compiler-managed rodata pooling: text648 and EH184/index12 exact instructions; 99.59876% before pool symbols/ranges were... | 8884fae7 |
| `fn_801F7198` | game/fn_801F7198.cpp | 98.93 | Resolved: byte-valued bounds predicate ==1 emitted srwi / extra cmplwi r0,1 / bne; >0 emits exact srwi. / beq and removes 4 bytes. No residual. | {"idea": "Numeric predicate consumption: retain unsigned-char comparison result but test >0 instead of ==1.", "percent": 100.0, "source_size": 428, "result": "Exact unsigned compare materialization, srwi./beq, saved... | 7adf129d |
| `fn_801E4544` | game/fn_801E4544.cpp | 98.91 | Closed: after Alloc, source stored s->data before loading last.ring; target loads last.ring then stores s->data. Separate rescue needed for emitted 55-byte... | Mechanism A: -rostr, ownership of original exception type-name range and add-only bridges resolve remaining relocations and data placement: 100% text/EH/index/rodata. | 9e3b6b51 |
| `fn_8016A854` | game/mapeffect/Jungle16AUpdate.cpp | 98.57 | Resolved: descriptor r31 / generated motion stride r30 were swapped against target r30 / r31 (22 differing instruction rows). | H5: Compute Motion16A pointer before assigning indexed descriptor pointer in original loop; 100%. Reverses induction-web creation order and gives target descriptor r30 / stride r31 without any other instruction... | da7cd059 |
| `fn_801F8A34` | game/fn_801F8A34.cpp | 98.16 | Resolved: loop-condition glyph load was CSE-reused in body, deleting target +0x12C lhz and hoisting cmplwi / changing FP scheduling; source 800 B vs target... | Byte-pointer sentinel load with existing typed body glyph access separates address-expression provenance without a second iterator: 100%, 804 B. Replacing raw 0x24 with canonical offsetof(TextDraw801F, glyphs)... | 5034e3f5 |
| `fn_80183CC4` | game/dlistutil/fn_80183CC4.c | 97.69 | None. Initial residuals: zero constant hoisted outside vertex loop (f3 vs f1), missing billboard-mode early exit and reversed component stores,... | H3: TU-local ExtendBounds with numeric 0.0f instead of extern const zero restores in-loop lfs and FPR operands: 100%, source1712B, extab/index100. | b8029062 |
| `fn_8020B234` | game/anon_8020AF08_nm1.cpp | 97.54 | None. Constructor and all owned sections exact. | H2 section-base ownership: three separate file-static typed command arrays referenced directly, without aggregate/cached pointer. 99.85876 before ownership; 99.943504 after base bridge; 100 after annotating the three... | 2bd015cc |

### Expression form / operand order (4)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `fn_801972E0` | game/objview/fn_801972E0.c | 99.95 | Resolved: initial four final-loop operands swapped count r30/stride r28 versus target count r28/stride r30 at +0x7D4,+0x964,+0x968,+0x96C. Final object has... | H2 refinement: initialize j before offset while preserving offset-first increment expression. 100.0%; li r28,0; mr r30,r28 and all loop operands exact. Retained. Unlike earlier c18 declaration probe, this reverses... | 106d0e73 |
| `GabyouItem_FlightAndLockOnTick` | game/GabyouItemFlight.cpp | 99.22 | Resolved: flight-phase switch decision tree, lock-byte signed comparisons, particle counter zero coalescing, pitch-result f0/f31 staging; later alias... | H6 call expression: anonymous (short)ItemAlias_HitRemapLookup(item->alias) notification argument, as in matched Gabyou Active, resolves alias r27/r28, 100% text3724/EH8/index12. | 6e750f17 |
| `fn_801D4FF4` | game/fn_801D4FF4.cpp | 99.19 | Resolved diagnostic argument temporaries: remaining-bit value used r26 instead of r25; used-bit value used r25 instead of r26 with extra mr via r0. | Direct nested DebugPrintf arguments restore compiler expression-temporary allocation and right-to-left call evaluation: 100% text/extab/extabindex. | 2130431f |
| `fn_8021B68C` | game/anon_8021B568_nm1.cpp | 98.84 | Resolved. Start: first-loop cursor target r30/source r31, classification-result/icon target r31/source r30, and role comparison target cmpw r0,r27/source... | H2 value materialization: mirror canonical SlotTeam as TU-local QuerySlotTeam and read promoted sync-table byte into int syncRole before comparing it with cached local role. This resolves cmpw operands: 100.0%, 672... | 2bdf2844 |

### Loop / control-flow shape (4)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `fn_801DABFC` | game/fn_801DABFC.c | 99.20 | Resolved: two cmpwi r0,0 versus target cmplwi r0,0 at 0x801DADAC and 0x801DADC4. Final 150 instructions all match. | H3 explicit control-flow joins: retain bool fields and replace switch mask selection with if(!out) goto off; on /= mask; goto done; off: off /= mask; done:. 100%, 600 B; all register homes and compare opcodes exact.... | fea84a21 |
| `fn_801CDF10` | game/fn_801CDF10.cpp | 98.74 | Resolved: tail +0x298..+0x2AC character r4/base r3/gate r0 versus target character r0/base r4/gate r3; li r3,-1 previously preceded gate store. | H2 (evaluation/source order): assign g_rendererGateFlag=1 before GetPlayerCharacter()->SetCharacter(g_characterId), consistent with neighboring race-entry sources. MWCC schedules the independent character store... | e9bb50f9 |
| `fn_8015BCC4` | game/Scene_8015BCC4.cpp | 98.66 | Resolved: target second viewer null test is bne to setup followed by unconditional exit branch; baseline emitted one beq and was 324 bytes instead of 328. | Move camera setup verbatim into fn_8015BCC4 with function-level early return if either viewer is null: 100%, 328 bytes; target bne/b restored. | 8db7c72f |
| `fn_801FDDA4` | game/anon_801FD924_nm1.cpp | 97.34 | Resolved: baseline hand-written branch tree reordered the second dispatch and omitted 4 bytes (376 versus target 380). Target pivots at code 5, then... | A3: enumerate known protocol result 6 with case 2/default, as neighboring fn_801FE030 does; 100%, 380 B. Restores target switch pivot and all owned sections. | bc0de938 |

### Other (18)

| Function | TU | from % | Residual | Fix | commit |
| --- | --- | --- | --- | --- | --- |
| `fn_8016D2D0` | game/ItemBoxConstruct.cpp | 99.93 | Resolved four setup rows at +0x24/+0x28/+0x30/+0x34: native pool high scratch r7, base-vtable low/store r3. No remaining instruction/relocation or... | 1 Semantic pool ownership: replace external base+offset access with seven original file-static strings and direct references. Unwired probe99.90228 solely due pool relocation naming, all four scratch rows exact;... | f77e48f6 |
| `fn_801D3118` | game/anon_801D2F0C.cpp | 99.90 | Resolved: three 1.0f relocation references had been renamed to @etb_800151E4 by a stale existing bridge. | No body probe: anonymous-name change from the coordinate getters clears stale collisions, producing 100.0%. | 88ce6cad |
| `KartFx_FlashOrbitTick` | game/KartFxFlash.cpp | 99.86 | Resolved: phase f4 vs target f5 and multiplier 2.0 f3 vs target f4 at 800BA828/838/83C/840/848. Root cause was omitted third floating-point call argument,... | H3: Correct VfxSlot_SetScaleVec3 to three float arguments and pass effect->scale as Z: 100.0, all 700B text plus EH8/index12 exact. Supported by other callers and cLNormal3DWrap_Slot_SetScaleVec3 definition. | c80e7e87 |
| `HSD_TExpSchedule` | sysdolphin/baselib/texpdag_unlock.c | 99.84 | None. | Correct alpha selection from child c_dst to a_dst; restore canonical diagnostic filename and genuine data symbol boundaries: 100%. | edb11fbf |
| `DrawEffect_Cb_KartWheel_DualSpawn` | game/DrawEffect_Cb_KartWheel_DualSpawn.c | 99.83 | Resolved eight child-cursor/phase-cursor r30/r31 operand differences. Originally target child r31/phase r30 versus source child r30/phase r31; now every... | H4 private WheelPairState with children[2], driver, angle/speed and timers[4]; replace raw CP cursor with d->children[i]: 100% text/extab/extabindex; retained and promoted. | 273e3b46 |
| `fn_8028BAD0` | triforce/amjvs_nm7.c | 99.55 | Initially pure GPR coloring: NEXT_STATE zero r4/r5 vs target r0 and increment result r0 vs target r3/r4; case9 mulli/base/zero r0/r4/r5 vs target r4/r5/r0.... | H3: move Mgr.state++ before InitTimer=0 in NEXT_STATE and move case9 flags store before InitTimer=0: 100.0% all owned sections. | 4e83eb39 |
| `Effect_FourSpark_Res65_68_Update` | game/EffectFourSpark.cpp | 99.52 | Resolved: 25 FP identity rows in resource65/67 phase arithmetic, resource65 threshold, and resource67 growth envelope. Control flow, GPRs and stack were... | Direct (phase-start)/duration initializers and direct (0.6f*(1.0f+2.0f*t))*scale envelope avoid assigning intermediates to named persistent webs: 99.65565 -> 100.0, all sections exact. | 52ee4f4c |
| `fn_80187084` | game/objview/fn_80187084.c | 99.36 | Resolved: 15 argument-mismatch instructions in three wrapped point lookups. Target wrapped index r3/count r0; original draft index r0/count r3 or r4. No... | H3: pass Path186 pointer, count and index independently, defer path->points load inside CyclicPoint until after wrapping; target index r3/count r0 and load order restored; 100.0%. Retained. | fd33dad6 |
| `fn_802055F4` | game/anon_802052E0_nm1.cpp | 98.96 | none | Use scale-first ButtonX for second sprite only, retaining offset-first first sprite and both Y products: 100%; exact 424-byte text and owned EH. | 484e8743 |
| `fn_8023D710` | game/ItemUnlockGridResolve.c | 98.95 | Initial outer row base r31 / inner element cursor r30 were exchanged against target r30 / r31. Final residual: none. | Remove manual inner element cursor and use lbl_803E56B0[row][column], allowing compiler strength reduction to generate both induction pointers: 100% text/extab/extabindex. | 3a3f1b0b |
| `Items_ResolveOwnedAlias` | game/Items.cpp | 98.89 | Resolved: redundant mr r5,r4 between alias-table base and induction walker, making source 384 B vs target 380 B. | Use &Items_rodata_80315AA8[i] rather than a separately initialized/incremented row pointer; compiler strength reduction forms target walker directly: 100.0%. Removing the now-unused row declaration preserves 100%. | 1b170b0c |
| `upvec2roll` | sysdolphin/baselib/cobj_nm2.c | 98.87 | Resolved: initial validation emitted beq plus an extra unconditional b instead of target bne into valid body; +4 text bytes also shifted constant relocation... | Keep camera/eye-object validation in the outer if/else and place the output-pointer failure return inside the valid-camera branch: 100.0%. | 59485ee9 |
| `acReadResponse` | triforce/acsocket_m8.c | 98.83 |  | Order case 1 locals addr,len,base,lenOff,n to match the two named register pairs: 100.0. | 8544fc12 |
| `fn_801FC364` | game/anon_801FC1E0.cpp | 98.77 | none; exact | Capture initialTimer before input edge reset and set subState before timer assignment: 98.76744 -> 100.0. | aaa29b32 |
| `fn_8023B1A8` | game/ItemSelectChoiceInit.cpp | 98.75 | Resolved: table base addi to r0 plus extra mr r29,r0; player address addi destination r4 versus target r0. Extra instruction shifted EH start D8 versus... | Remove both explicit pointer cursors and read ItemSelectState_rodata_803DC180[row][column]; compiler strength reduction now gives row r29 / item r30 and exact global-address setup: 100%. | 9200c6fe |
| `DrawEffect_KartDustRing_Update` | game/DrawEffect_KartDustRing_Update.c | 98.11 | Resolved: external aggregate pointer materialization added mr r30,r4 and used mr instead of addi r4,r30,0 for tier 1. | Integration visibility correction within the same approach: static vectors caused unresolved neighboring ItemHitBurst/ItemHitOriented references in request 1; exporting the vectors preserves 100% text/EH/index/data... | 6668a75d |
| `Effect_TwoChildRotate_FromPhase150` | game/EffectRotatePair.cpp | 97.30 | Resolved: FP scratch identities in alpha clamp/phase wrap; addi group and lbz enable scheduling at +0x40/+0x44. | Enable belongs to the group view at +0xC4 (parent +0x190); express access through group, restoring addi-before-lbz, 100%. | 3fc53253 |
| `fn_8022B278` | game/EnemyFace_nm1.cpp | 97.26 | Resolved GPR partition: target textures/palettes/resources/tluts r31/r30/r29/r28, outer i r27, count n r26, inner k r25. Initial indexed inline helper... | Keep natural textures/palettes/resources/tluts increment order: 100.0%, all owned sections exact. | c928fb29 |

## 46. A loop counter reused by later loops takes the newest saved register: give the later loops block-local counters (TitleCheck_NewClearedRecord_Race, 11-09)

Symptom: register-only diff; the FIRST loop of a variable sits in the lowest saved register
(ours `li r24,0`, target `li r28,0`), and the same low register is the counter of later,
unrelated loops (`i` in loops 4 and 5).

Why: `IRO_SplitLifetimes` keeps the name only on the earliest range of a variable; every later
range is a `SplitOffRange` temp, and temps are coloured before all named locals. `colorgraph`
gives a node the lowest free saved register already handed out, else a new one (r31 downward).
With one function-level `i` for loops 4 and 5, the loop-5 range is a temp, is coloured early and
is the first to allocate r24; the named loop-1 `mode`, coloured late, then finds r24 free and takes
it. In the target r24 does not exist yet when `mode` is coloured, so it takes r28 (r25..r27 are held
by j/cur/prev, which must be coloured before it).

Fix: each later loop gets its own block-scoped counter (`{ int i; for (i = 0; ...) }`): a
single-range named local declared later than everything else, so it is coloured last and is the one
that allocates the new register. Declare the first loop's counter AFTER the locals whose registers it
must not take (`int j; int cur; int prev; int mode;`). 12 lines -> 0. Diagnose with
`tools/mwtrace.py --only COLOR,VREG`: find which node first allocates the low register and whether
it is a temp (`@9xx` from SplitOffRange) or a named local.


## 47. Loop over a global object's members: put the loop in an inline that takes the pointer (fn_8013DA00, 11-09)

Target loads the global straight into the LOWEST saved register and walks it, while the counter
gets the highest: `lwz r29,g; cmplwi r29,0; li r31,0; ... addi r31,r31,1; addi r29,r29,12`.
Writing the loop in the function itself (`T *p = g; if (p) for (i...) p->lists[i]`) gives the
pointer r31 and the counter r30. Moving the loop into an inline whose parameter is the pointer
(`if (g) RenderAll(g);`) gives the target's order: the inline's parameter copy is a later virtual
register than the loop's own locals. Explicit `l++` pointer walks are worse (one extra insn).

Same function, stack slots: `CIter b = l.begin(); RenderRange(b, l.end());` (named iterator passed
by value) puts `b` below the by-value parameter copy; the target has them the other way round,
which is `RenderRange(l.begin(), l.end())` with the temporary as the argument.
Rule name in hits.jsonl: `loop-in-inline-param`.

## 48. Big update function with several loops: which locals must be inline temps, and a table loop driven by the function-level counter (fn_80154304, 11-09)

`fn_80154304` (CourseScene update, 3244 bytes, `src/game/Scene_8014E0C4.cpp`)
went 98.8 % -> 100 % with four source-shape levers. None needed a pragma.

1. **A loop whose walkers must be coloured AFTER the other saved registers
   goes into a `static inline` helper.** Locals of an inlined function are
   inline temps (high vreg numbers), named locals of the outer function are
   always low, even when block-local. `CourseScene_UpdateJoints(self)` (the
   6-joint loop) and `VObjPair::Update()` fixed two groups this way.
2. **HSD-style nested accessor keeps the object in one register.**
   `PSMTXCopy(JObjGetMtxPtr(self->jobjs[i]), self->mtx[i])` with
   `static inline void *JObjGetMtxPtr(void *j) { JObjSetupMatrix(j); return (char *)j + 0x44; }`
   removed a reload of `self->jobjs[i]`. Passing the destination matrix as a
   second inline parameter evaluates it too early (worse).
3. **Mixed case: one variable low, the others high.** The sprite-cache sweep
   needs the end sentinel `e` as an outer named local but `spr` and the node
   walker as inline temps. `static inline void SprScene_Sweep(CourseScene *self, SprNodeBase *&e)`
   with `e` declared in the caller (right after `int i;`) and the helper
   locals declared in the order `n2, spr` gives exactly that. A named `e`
   inside the helper, a hoisted `&spr->cache.end`, or `spr` as a parameter all
   swap registers.
4. **Loop-invariant constant loaded BEFORE the table pointer** (`lfs f31, 0.0f`
   then `addi r30, rAnchor, off`; ours had the two swapped): the original
   indexes the table with the function-level counter,
   `for (i = 0;; i++) { if (tbl[i].time < 0.0f) break; ... tbl[i].x ... }`.
   Strength reduction creates the pointer after the constant is hoisted. A
   walking pointer (`for (ev = tbl;; ev++)`), a block-local `int k` index, a
   named `float zero`, and an inline helper all keep the wrong order;
   `while (!(ev->time < 0.0f))` fixes the order but rotates the loop.

Also: a class-specific `operator delete` that only forwards to the global one
is emitted out of line (weak `__dl__5ClassFPv`) as soon as a `new Class`
expression needs it for its DELETEPOINTER extab action. If the target's action
names the global delete, drop the class operator.

Speed tip for a 15 kLoC TU (2.5 min per compile): take the compile command
from `ninja -t commands <obj>`, write each variant to its own directory, add
`-i src/<dir>` so the `.inc` files resolve, and run all variants in parallel;
compare `dtk elf disasm` bodies with symbols normalised.

## 49. A `long` loop index passed as an `int` argument gets a hoisted copy that is numbered late; and count the `%d` of debug strings (DetermineTitle, 11-09)

Two independent fixes, 18 lines -> 0:

- Inlined `CurrentNameScore`: the outer index of a nested loop is passed to a call in the inner
  loop. Declared `long`, the `(int)` conversion is a loop-invariant expression, so `IRO_FindLoops`
  hoists it into a temp (`MR @536,i` in the preheader, seen with `tools/mwtrace.py`) and the index
  is coalesced into that temp: its node takes the LOW number of the FindLoops temp and is coloured
  after the other inline locals. Declared `int`, there is no copy and the node keeps the inline
  local's number. The target had the first loop's `i` late (r20, `long`) and the second loop's `cup`
  early (r21, `int`). After that, inline locals are numbered in forward declaration order (§45), so
  `int j; int k;` vs `int k; int j;` picks which of the two takes the register freed by `cup`.
- `addi r5,r3,0x2d; stw r5,...; cmpw r5,r0` where ours computes into r3: the value is also the third
  argument of the following `DebugPrintf`. Read the format string from the DOL
  ("Fixed TitleID loop No : %d, id : %d") and pass every argument it names.

## 50. Pointer fetched through an inline getter is coloured after the temps of the inline that uses it; make it a directly loaded local of that inline (WarpZone_CheckEntry, 11-09)

Target `i` r5, `mgr` r6, zone pointer r7. Ours (99.2 %, a 24-line plateau since 11-07)
had `mgr` r7 and the zone pointer r6 with

    WarpDashMgr *mgr = WarpDashMgr_GetInstance(self->mgrId);   // inline getter
    if (mgr == 0) return 0;
    int zone = WarpZone_FindContainingOBB(mgr, x, y, z);       // inlined

`regfix diag` said: the two vregs are level with each other, and `mgr` (the getter's return
temp, `@364`) is numbered after the zone pointer (the reference parameter of the inner
`Contains` inline, `@354`) because the search inline is expanded before the getter's result
temp is made. About 40 forms that keep `mgr` as a parameter or a getter result do not move
it (reference / `this` / wrapper inline / local copy `m = mgr` in any decl order / defining
`Contains` after its caller): the copy is coalesced back into the late temp. A named local of
the function itself (`mgr = table[id != 0]` at function level) is numbered below everything
and gets r8.

What works: the whole body is one `static inline` whose **own local** `mgr` is loaded
straight from the table (no getter inline, no parameter), declared **before** `i`:

    static inline unsigned char FindZone(WarpAutoRun *self, float x, float y, float z) {
        WarpDashMgr *mgr; int i; int zone;
        mgr = g_warpDashMgrs[self->mgrId != 0];
        ...
            for (i = 0; i < mgr->obbCount; i++)
                if (Contains(zoneAt(mgr, i), p) == true) { zone = i; goto done; }
            zone = -1;
        ...
    done:
        self->zone = zone;
        return zone != -1;
    }

Inline locals are coloured latest-declared first (`mgr; i` gives i r5, mgr r6; `i; mgr`
swaps them), and both come before the parameter temps of inlines expanded inside. The
`{ zone = i; goto done; }` exit reproduces the `bne next; b found` pair of an inlined
`return i`; `goto found; ... found: zone = i;` gives a single `beq`.

Also: when an asm function with a manual `.extab_user` entry becomes C++ with a
destructible local, delete its manual extab/extabindex entries (the compiler emits them;
keeping both grows main.dol by 0x14).
Rule name in hits.jsonl: `inline-own-local-direct-load`.

## 51. Saved registers of two disjoint blocks: declare every block temp at function scope under its own name, in colouring order (fn_80141454 LogoAnim, 11-09)

Target, two unrelated `else if` blocks that each keep floats across calls:

    block A (t < 105):   a f30, sy f29, sx f28      (t itself sits in f31)
    block B (t >= 105):  y f31, a f30, sy f29, sx f28

With block-scope locals ours gave block A `sx` f31 (3 lines off; 960 decl orders and 22 min of
cperm did not move it). Sharing one function-scope `a/sx/sy` between the blocks is much worse.

Why, from the allocator model (`Graph.colour` in tools/regfix.py, which reproduced the real
colouring here): named locals are numbered in reverse declaration order over the whole
function, and vregs are coloured highest number first. A vreg that needs a saved register takes
the **lowest-numbered saved register already in use** that its neighbours do not hold, and only
then opens a new one, from f31 down. Block-scope locals of A are declared before those of B,
so A is coloured first: `sx` reuses f31 (free, `t` is dead), `a` opens f30, `sy` opens f29.
The target has B coloured first (y reuses f31, then a/sy/sx open f30/f29/f28) and A afterwards,
each taking the lowest used register: sx f28, sy f29, a f30.

So B's temps must be declared before A's, which block scope cannot express. Fix: seven
distinct locals at function scope, in exactly the colouring order

    float t; float a; float s;
    float splitY, splitT, splitSy, splitSx, outSx, outSy, outT;   // B's four, then A's three

How to read the order off the target: list the saved registers per block; the block whose
registers were opened in descending order (f31, f30, f29, f28 = declaration order) comes
first; a later block fills from the lowest register up (f28 first = declared first).
`python3 tools/regfix.py diag` prints one line ("f31 -> want f28") and finds no edit, because
the fix is a renumbering across two groups; print `Graph.colour()` order with keys to see it.

Also in this TU: the C body must stay after the empty `fn_80141450` (text order), the float
literals need the `.sdata2` range in splits.txt (0x806D7900..0x806D7998, the ctor's 0.0f
included), and the manual extab entry and its two extab_user_renames go away.
Rule name in hits.jsonl: `fn-scope-distinct-temps-order`.

## 52. Loop-invariant `&member` hoisted by the backend takes the newest saved register: name it as a local of the inline (SoundDriver_GetOrCreate, 11-09)

Diff: two saved registers swapped between a loop cursor and a hoisted
address (`mr r31,r28; addi r30,r29,4` in the target, r30/r31 the other way
round in ours). mwtrace shows the address (`&list.head`, written inline as
`insert(end(), v)`) is a *backend* temp (`ADDI r53!,r36,4`, off=-1, moved to
the preheader after code generation). Backend temps are numbered above every
IRO temp and named local, so it is coloured first and takes r31.

Fix: give the address a name inside the inline, so it is an inline local
(numbered with the IRO temps, below the caller's cursor):

```cpp
void push_back(const T &v) { Node *n = (Node *)&head; insert(iterator(n), v); }
```

`iterator e = end(); insert(e, v)` and a `ListHead *` local do NOT work (the
first changes the stack temps, the second stays a backend temp); the local
must have the exact type the iterator constructor takes.

## 53. List walker / sentinel saved registers swapped: `begin()` as `iterator(((Node *)&head)->next)` instead of `++end()` (clItemBoxManager_Dtor, 11-09)

Diff: `for (it = l.begin(); it != l.end(); ++it)` gives walker r28 / sentinel
r29, the target has walker r29 / sentinel r28 (`addi r28,r30,0x14;
lwz r29,0x18(r30)`). With `begin() { return ++end(); }` the walker starts as
a copy of the sentinel temp, so the sentinel is the later-numbered value and
is coloured first. Loading `head.next` directly in `begin()` makes the walker
independent of the sentinel:

```cpp
iterator begin() { return iterator(((Node *)&head)->next); }
```

Same family as section 52 (who names / creates the `&head` value decides the
saved register). Naming the sentinel in `end()` alone made it worse (50 lines).


## 54. Volatile temps after a call start at r4 instead of r3: the block leaves through a valueless `return;` (fn_801B4548, 11-09)

Diff: after a call near the end of a block (here `OSGetTime`), ours puts the
following short temps in r3, r4, .. while the target uses r4, r5, .. and never
touches r3 until the shared epilogue; the opcodes are identical.

Cause: the original source leaves the block with `return;` (no value) in a
function that returns `int` (MWCC C accepts it with a warning). A valueless
return emits no `li r3,N`, but the exit block still "uses" r3 as the return
register, so physical r3 stays live from its last definition (the call) to the
exit and interferes with every temp in between. With `return 1;` or a `goto`
to the shared `return 1;` r3 is free and the temps take it.

Fix: write `return;` for those exits and keep the final `return 1;` of the
function (dropping that one too removes the `li r3,1` and shifts the length).
Returning the call's own value (`return (int)hi;`) is not the same shape.

Not fixed in the same function (16 lines left): saved registers of four
vregs. regfix diag: entry temp @9778 r25 (want r28), FindNearest result r28
(want r26), its counter r26 (want r25), `maps` r23 (want r25). In
simplifygraph (Coloring.c) all of them fall into the second round and are
pushed in ascending vreg order, so the inline local (170) is coloured before
the optimizer temps 65..67; the target needs it coloured between 66 and 65.
Tried without change: inline local orders, `maps` at function scope, entry in
an inline, block-local loop counter, search written in the body or with
reference parameters (adds a `mr`).

Also seen here: MWCC does not CSE two loads of the same address that have
different types. A union read as `.s` for the compares and `.u` for the call
arguments reproduces the target's reloads of the same word.

## 55. In-place `x = x / N` is recomputed at its first use (extra saved register): opt_propagation off (SwitchTest_Page, 11-09)

Diff: the target computes a difference straight into a saved register and
divides it in place (`subf r28,..; ...; srawi r0,r28,6; addze r28,r0`), so
difference and quotient are ONE variable. Writing `st = steer / 64` gives the
difference a volatile register; writing `steer = steer / 64` (or `/=`, or an
inline) moves the division down to the first use and costs one more saved
register (`stmw r26`). mwtrace: the SRAWI/ADDZE pair appears in the block of
the first use with a fresh destination vreg.

`#pragma opt_propagation off` keeps the division where it is written. Side
effect: inline helpers that rely on constant propagation change shape (here
the shared `for (i = 0; it[i].text; i++)` loop became `mulli` of a zero
index); write those loops as an explicit pointer walk (`it++, i++`) in a
local copy. opt_lifetimes / opt_dead_assignments off do not help.


Also fixes argument load order (fn_801C0568, 11-10, bf46559): when two argument
loads before a call come out reversed and `mwsched.py explain` says they have
equal keys (block order wins), assign the later argument to a local first
(`int dir = in->dir; f(self->panel.p, dir, press);`). Without the pragma the
local is propagated back into the call and nothing changes; with it the load
stays where the local is assigned. Fakematch-marked.

## 56. Optimizer temp takes the wrong already-used saved register: load a pointer local through an inline getter; and share float locals across switch cases (CoinSystem_UpdateAll, 11-09)

Rule observed with tools/mwccdbg.py `--all`: named locals get the lowest
vreg numbers (reverse declaration order), optimizer temps (CSE of
`&c->sparks[i]`, hoisted values) come next, inline return/parameter temps
last. Colouring runs from the highest vreg down, and a saved-register node
takes the lowest saved register already handed out before it opens a new one.

- GPR: target kept `c + i*16` in r28 (the register of `flags` from an earlier
  loop), ours in r29 (register of `p`). `flags` was a named local, so it was
  coloured AFTER the temp and opened r28 too late. `flags = CoinKart_GetFlags(kart);`
  (static inline returning `kart->flags`) turns the value into a late temp,
  coloured before the CSE temp. Declaration order of `flags` has no effect.
- FPR: target reused one saved FPR for "range" in loop 1, "t" in cases 2/3
  and one of the homing targets in cases 7/10 (x in one case, y in the other).
  Separate locals (`range`, `t`, `tx`, `ty`) gave f30 instead of f28. Two
  function-level floats `a`, `b` reused for all of them match; read from the
  target which case uses which.
- Moving the whole pickup test into an inline also fixed the GPR but its
  float local became a late temp (f30 again) and its Vec moved on the stack.

Same rule, volatile registers (KartItem_ApplyImpactReflectAndDampVelocity, 11-09): an inline
`bool IsReflectLane(Lane *lane)` called as `IsReflectLane(self->secondary)` gave lane r6 / result
flag r5, target lane r5 / flag r6. `mwccdbg --all` showed the flag (inline return temp) with a
higher vreg than the lane (argument temp), so the flag was coloured first and took the lower
register. Wrapping the call as `inline bool IsReflectItem(Self *self) { return
IsReflectLane(GetSecondary(self)); }` creates the getter's return temp after the wrapper's result
temp: the lane is coloured first and gets r5. A getter at the call site without the wrapper, a
getter inside the loop inline, an id getter and an in-body flag did not work.

## 57. `addi rBase,..; mr rWalker,rBase` versus `addi rWalker,..; mr rBase,rWalker`: the base must be a split-off lifetime range (fn_801E96BC, 11-09)

Diff: only the direction of the copy between a table base (`base = table;`,
kept for an inner loop) and the strength-reduced walker of `&base[i]`.
mwtrace (ours): `ADDI r54,..; MR base,r54; MR walker,r54`. The copy into the
NAMED local `base` is never coalesced, the walker temp merges with r54, so the
address lands in the walker. The target needs `base` itself to merge with the
address temp; then `MR walker,base` stays because the two interfere.

Only vregs in the temp range coalesce. A variable's FIRST lifetime range is
the named local; every later range is a SplitOffRange temp (mwcc_internals,
IRO_SplitLifetimes). So `base` has to be the second range of a variable that
was used for something else earlier:

```c
base = (AIPairRecord *)lbl_806D1920;            /* first range: the cap */
self->frame++;
if ((int)base < self->frame) self->frame = (int)base;
base = lbl_806793D8;                            /* second range: a temp */
```

A dead first assignment (`base = 0;` / the same assignment twice) is removed
and does not count; an inline parameter is constant-propagated and the address
is rematerialised in the loop; a named walker gives `addi r0; mr; mr`.
When a diff is exactly this copy direction, look for a variable the original
may have reused (same register in two unrelated places in the target).

## 58. Volatile FPRs of an int-to-float divide chain: read the creation order off the registers and write it as one expression (fn_8015DEBC, 11-09)

Symptom (99.62, 6 volatile FPR rows): `t = 1 - (float)n / 15; ssc = 0.035 * t` written as
separate statements gives `0.035 -> f0, bias -> f1, 15.0 -> f2, 1.0 -> f3, diff -> f4`; the target
has `15.0 -> f0, double -> f1, bias/diff -> f2, 1.0 -> f3, 0.035 -> f4`.

Volatile temps are coloured highest virtual register first and take the lowest free register, so the
register numbers give the creation order backwards: here 0.035 was created FIRST and 15.0 LAST.
That is the evaluation order of one expression, left operand first:

```c
float t;
float ssc = 0.035f * (t = 1.0f - (float)e->subs[j].n / 15.0f);
```

(0.035, then 1.0, then the conversion bias and stack double, then 15.0.) Splitting the statements
(§26) had fixed the saved pair but put the constants in statement order. Float literals, not
`extern const float`, are needed for this to work. Rule: when only volatile registers differ in a
straight-line float computation, sort the temps by target register number descending; that is the
order in which the source must create them.


## 59. `lwz rT,4(rF); mr rL,rT` where rT < rF < rL: frontend CSE temps are numbered in reverse discovery order, and the pointer must be a function-scope local declared before the value local (RivalRun_RivalTactics, 11-09)

Symptom (3 diff lines, 1 instruction short): the target has

```
lwz r4,40(r31)     ; f = self->follower
lwz r3,4(r4)       ; temp = f->lane
mr  r5,r3          ; lane = temp
...
lwz r0,4(r4)       ; SetLane re-reads f->lane
cmpwi r0,1
```

and the build either loads `lane` straight into its register (no `mr`) or puts `f` in r3.

Rules read off `mwccdbg --all --trace`:

- `lane = f->lane` only goes through a temp when the frontend shares the load with a later
  `f->lane` expression (here the `== 2`, `- 1`, `+ 1` uses). Without a shared use the load
  goes straight into the named local.
- Frontend CSE temps are numbered in reverse order of discovery: the group whose second
  occurrence comes later in the source gets the lower virtual register.
- Volatiles are coloured highest vreg first, lowest free register first. For r3/r4/r5 the order
  must be temp > f > lane, so `f` has to be a named local declared BEFORE `lane` at function
  scope (a block-scope or inline-parameter `f` is a temp numbered above the CSE temp and takes r3).
- The re-read in the inlined SetLane must not join the shared group (the backend then folds it to
  `cmpwi r3,1`). Only a different frontend expression kept it: `*(int *)((char *)f + 4) != 1`
  (fakematch; a getter inline, `self->follower` as the argument and a second SetLane type all
  lost either the reload or the register order).

```c
RRPathFollower *f;   /* before lane */
int lane;
...
f = self->follower;
lane = f->lane;
... if (*(int *)((char *)f + 4) != 1) { f->lane = 1; f->needsSearch = 1; }   /* fakematch */
... if (f->lane == 2) lane = f->lane - 1; else lane = f->lane + 1;
```

## 60. Loop with `add rP,rBase,rOff` per iteration: the byte offset is a named variable added in the INTEGER domain (ItemObject_Tick_Kind29_LightAttachment, 11-09)

Diff: three volatile registers rotated in a keyframe loop (target base r3,
`t[]` walker r4 = `mr r4,r3`, byte offset r5; ours offset r3, base r4, walker
r5). mwtrace: with `(char *)c + i * sizeof(float)` the offset is a temp the
BACKEND creates after code generation (`LI r90,0 ... ADDI r90,r90,4`), so it
has the highest vreg and is coloured first.

The target's offset is coloured last, so it is a named local. But every
pointer form (`(char *)c + off`, `&c->x[i]`, `i * 4`, unsigned `i`) is strength
reduced by IRO into a second walker (no `add`, 36 lines). Adding it as an
integer keeps both the named offset and the per-iteration `add`:

```c
int off;
...
off = 0;
for (i = 0; i < 4; i++, off += 4) {
    if (c->t[i] <= t && t <= c->t[i + 1]) {
        ScaleCurve *segment = (ScaleCurve *)((unsigned long)c + off);
```

`(int)c + off` and an `unsigned long off` do not work (walker again); it has
to be `int off` added to `(unsigned long)c`.

## 61. Shared float constant in the wrong FPR, and `fadds` with 0.0f that literals fold away: literals everywhere, the zero passed into the inline as parameters, constants loaded once through reverse-declared locals (TransitionEffect, 11-09)

Target (unrolled table loop): `lfs f6,240; lfs f5,0.0; lfs f4,320; ...; fsubs f0,f0,f4; fsubs f2,f2,f6;
fadds f0,f0,f5; fadds f2,f2,f5`. Three sources, three results:

- `extern const float` for every constant: the frontend CSEs the zero that is read twice into a
  temp (`@541` in the trace) and the FPRs come out permuted. regfix diag now prints a hint when a
  bad vreg is a frontend `@` temp.
- the same with `#pragma opt_common_subs off`: registers right, but the unrolled loop bumps the
  walker twice.
- float literals: `x + 0.0f` is folded away completely, so the `fadds` disappears.

The target keeps `fadds` with zero, so the zero reached the expression as a VALUE, not as a
literal: the quad helper took offsets. Literals everywhere plus the zero as inline parameters
matches exactly (a hybrid of externs with a literal zero does not):

```c
static inline void ScreenRouletteTableQuad(float ox, float oy)
{
    ...
    for (int i = 0; i < 16; ++i) {
        ScreenPosition((v[0].x - 320.0f) + ox, (v[0].y - 240.0f) + oy);
        ...
    }
}
... ScreenRouletteTableQuad(0.0f, 0.0f);
```

Side effects of going to literals in the rest of the TU, and their fixes:

- Literals are not CSE'd: every `ScreenPosition(-320.0f, -240.0f)` reloads its constants. Where
  the target loads each constant once, give them named locals. Block-scope locals are numbered
  in reverse declaration order, so declare them in reverse of the assignment order to get
  f3,f2,f1,f0:
  `float y1, x1, y0, x0; x0 = -320.0f; y0 = -240.0f; x1 = 320.0f; y1 = 240.0f;`
- The TU must own the constants: add its `.sdata2` range to `config/GNLJ82/splits.txt`.

## 62. Hand-unrolled segment calls with base/cursor registers swapped: write the real loop AND pass the base as an expression (EffectVfx29_30_Item4SubFlame_Tick, 11-09)

Diff: four copies of a piecewise-linear segment test; target base r3 and
`addi r4,r3,4*n` cursors, ours base r4 and cursors r3. Each lever alone fails:

- named outer `FlameCurve *curve` + hand-unrolled calls: curve is coloured
  last, r3/r4 swapped (99.42);
- curve passed as an expression + hand-unrolled calls: base r3, but the dead
  base merges into the last cursor (`lfsu f2,0xc(r3)`);
- named outer curve + real loop: strength-reduced `lfsu` walk (95%).

Both together match: with the base as a temp expression the compiler fully
unrolls the constant 4-trip loop itself and keeps one base with `addi`
cursors, the last one included.

```c
for (i = 0; i < 4; i++) {
    FlameCurve_Segment((float (*)[5])((char *)curve + i * sizeof(float)), t, &height);
}
...
int idx = I(0x10);
height = FlameCurve_Evaluate(EffectVfx29_30_Item4SubFlame_Tick_data_8041A224 + idx, F(0x150));
```

Lesson: when a row in gave_up lists "loop tried" and "expression tried"
separately, try the combination before giving up.

## 63. Two loop-long FPRs swapped (hoisted stack float vs hoisted constant), then volatile pairs in an unrolled classify loop (fn_801E9E74, 11-09)

Three separate swaps, each with its own cause in the trace:

1. `lfs f30,0x28(r1); lfs f31,zero` vs ours f31/f30. Both values live across
   the whole loop with degree >= K. `position.z` was an IRO hoist temp
   (`@121`, low vreg); the zero was hoisted by the BACKEND (highest vreg). In
   the first simplify sweep the low temp is skipped and the backend temp is
   pushed (its neighbours in between are already gone), so the low temp is
   pushed last and coloured first. Fix: both as named locals, the one that
   needs the higher register declared FIRST, and passed into the inline:
   `float zero; float pz; ... pz = position.z; zero = lbl_806DA3F4;`
   (a named zero alone flips the load order instead).
2. `range` (named, coloured after the inline's `previous`) f2 vs f1: compute
   it in a small inline so it becomes a frontend inline temp:
   `static inline float GetRangeSq(void) { float range = fn(); range *= range; return range; }`.
   A `Square(float v) { return v * v; }` helper does not do it.
3. Strength-reduction walkers for `&base[i]` and `&states[i]` r4/r5 swapped:
   they are numbered in creation order and the inline touches `*result`
   first. Assigning the record to the existing function-level local first
   (`record = &base[i]; ClassifyRecord(record, ...)`) creates its walker
   first. Swapping the inline's parameter order has no effect.

## 64. One-line `fmuls fD,fA,fB` operand swap where swapping the source operands also swaps the registers (fn_80219538, 11-09)

Diff: target `lfs f2,K; ...; lfs f3,0x10(r22); fmuls f31,f2,f3`, ours
`fmuls f31,f3,f2`. Writing `K * mi->rot` instead of `mi->rot * K` flips the
instruction AND the registers (3 lines), because the backend evaluates the
left operand first and the first-evaluated value has the lower virtual
register (coloured later, higher FPR). Literal constants, `*=` forms and
inline helpers (`Mul(a, b)`, `DegToRad(deg)`) all behave the same: first
operand = first evaluated.

The target has the SECOND operand in the lower vreg, so `rot` already was
in a register when the multiply was generated: a named local that survived.

```c
float rot = mi->rot;
float ang = lbl_806DAF54 * rot;
```

The frontend propagates the single-use local straight back into the
expression, so this needs `#pragma opt_propagation off` around the function
(`opt_dead_assignments off` works too). Marked fakematch.

## 65. Saved GPRs of a switch permuted between cases, and one case's stack objects in the wrong place: declaration order of the value locals vs block-local payload pointers; the case's setup in its own nested inline (TransitionEffect_RenderPass, 11-09)

Symptom 1: a `switch` whose cases each keep a payload pointer and a few
colour values across calls; all instructions equal, only r27/r29/r31 permuted
between cases. The colourer handles higher vregs first and gives each the
lowest free saved register already handed out, else a new one from r31 down.
Named locals are numbered by source position, so the one declared EARLIER is
coloured first. The target coloured the values before the payload pointers.
Fix: declare every case's value locals at function scope, first, each case
with its own names (`unsigned int a1; unsigned int r, g, b, a; unsigned int
r5, g5, b5, a5;`), assign them in the cases, and make the pointer a block
local in each case (`case 3: { void *payload; payload = self->flash; ...`).
One function-scope `payload` shared by all cases gives the permuted registers.

Symptom 2: the same function with the matrices/Vecs of one case at the wrong
stack offsets (the target had case 3's objects lowest although it is in the
middle of the source). Stack objects are laid out in creation order, first
created = highest address, and inline locals are created level by level. Put
that case's setup into its own inline that owns the objects, so they are
created one level later than everything else:

```c
static inline void ScreenFlashSetup(const Vec *camera)
{
    Mtx44 projection3;
    Mtx view3;
    ScreenProjection(projection3);
    ScreenCamera(view3, camera, 9, 1.5707963705062866);
}
```

The order of the two declarations inside it matters too. Wrapping the whole
case in an inline does not work: it is over the inline size limit and
`#pragma always_inline on` does not change that.

## 66. A temp avoids r3 for no visible reason near the END of a function: the function returns non-void and has no return statement (clFlowCC*::Update, 11-09)

Diff: the last loop of the function,

```
target: lwz r4,0x58(r28); cmplwi r4,0; beq skip; lwz r3,0(r4); bl Sprite_AdvanceAnim
ours:   lwz r3,0x58(r28); cmplwi r3,0; beq skip; lwz r3,0(r3); bl ...
```

The temp has three neighbours and r3 looks free, yet the target does not
use it. The same source loop gives r3 in sibling functions where more
calls follow the loop, and r4 where the loop is the last statement.

Cause: the function is declared with a return value (`virtual int Update()`)
and falls off the end. The epilogue then USES r3, so r3 is live from its
last definition to the exit. On the path that skips the call (`beq skip`)
r3 is live across the temp, they interfere, and the temp gets r4. With
unconditional calls after the loop r3 is redefined and nothing shows.

Fix: declare the function with the non-void return type and no `return`.
For a virtual, change the base and every override (mangled names do not
contain the return type, callers that ignore the value are unchanged).

Where to look: any `rX` vs r3 swap for a short-lived temp in the tail of a
`void` function, on a path that can reach the exit without a call; also
`li r3,N`-free tails where a value seems to be kept away from r3.

## 67. `li rA,0; ... mr rB,rA` for two variables that both start at zero: they are locals of an INLINED function (RivalRun_UpdatePathFollower, 11-10)

Target (search loop preheader): `li r28,0; stb r28,0(r30); mr r29,r28` for
`best = 0; i = 0`. Written as two locals of the function itself we always got
`li r28,0; li r29,0`, whatever the statements (`i = best`, `pf->flag = best`,
shared constant local).

Why (GlobalOptimizer.c `optimizelevel4`, ValueNumbering.c `isCSEop`):
constant propagation turns every `mr x,y` whose `y` has the single reaching
definition `li` back into an `li`. The later *aggressive* value numbering pass
does merge two equal `li`, but only when the destination register is a
compiler temporary (`>= first_fe_temporary_register`), never a named local of
the function being compiled. Locals of an inlined function are such
temporaries. So a surviving `li; mr` pair for two same-valued variables says
the variables live in an inline.

What else the two inlines (`RR_FindNearest(pts, count, pos)`,
`RR_Follow(pf, pts, last, pos, &rel)`) fixed, in the order the diff shrank
(124 -> 0 lines):

- Arguments copied into an inline are coalesced copies that still raise the
  interference degree of the outer locals: `pts` reaches degree >= 29 and is
  coloured before `pf` (r31 / r30 as in the target).
- Inline locals are numbered above the outer named locals, last declared =
  coloured first: declare the floats of each helper in reverse of the wanted
  f31, f30, ... order.
- `count - 1` passed as the argument (not `last = count - 1` inside the helper)
  puts `last` in r29.
- A stack object declared in the outer function and passed by pointer
  (`RRVec3 rel`) sits above the helper's own stack objects (d at 8(r1), rel at
  20(r1)).
- The table row read through an inline getter (`RR_Routes(pf->lane)[pf->route].pts`)
  becomes a late temp, which fixes a volatile r4/r5 swap (same idea as §56).
- The last two lines were the compiler version, not the source: see
  matching_rules §4 (preheader `mr`/`lfs` order, GC/2.0 or later).

Rule name in hits.jsonl: `li-cse-inline-locals`.

## 68. Loop counters take the LAST volatile registers in the target: the loop is not inside an inline (clFlowCCBattle::Update, 11-09)

Diff: a 5x20 grid shift loop with five volatile registers rotated. Target
y=r9, x=r10, walkers r6/r7/r8; ours x=r6, y=r7, walkers above.

Reading: in the target the two counters are coloured after every temp, so
they are named locals of the function (lowest virtual registers). In ours
the loop lived in a `static inline ShiftBattleGrid(page)`, which turns its
locals into frontend inline temps (highest numbers, coloured first).

Fix: write the loop straight into the function body (66 -> 17 lines). The
remaining walker swap (dst `x + y*20` vs src `x + (y-1)*20`) follows
creation order of the strength-reduction temps: name the destination index
first (`int dst = x + y * 20;` before `src`), 17 -> 0.

Rule of thumb: counters in the highest volatile registers = plain locals;
counters in the lowest = an inline's locals.


## 69. Dead truncation makes a block get scheduled twice (VoiceSystem_Init)

Symptom: two independent instructions swapped inside one long straight-line
block (here `lfd f0,8(r1)` / `or r0,r0,r6`), everything else identical.
`python3 tools/mwsched.py log UNIT FN` shows the pre-RA schedule of that block
already equals the target, and the post-RA pass (`scheduleinstructions(TRUE)`,
Scheduler.c) schedules it again with one instruction fewer and flips the pair
(`selectinstruction`: `or` uncovers 2 successors against 1 for the load). A
block is only scheduled again when its `fScheduled` flag was cleared, i.e.
something was deleted or inserted in it after the first pass (see
mwcc_internals "Post-RA scheduling: which blocks are scheduled twice").

Find the instruction the pre-RA block has and the post-RA block lacks. Here it
was `rlwinm r139,r4,0,24,31`, the dead `(unsigned char)` truncation produced by

```c
lbl_806D1750 = (int)now;      /* s64 -> int -> u8: emits rlwinm, deleted later */
```

Writing the conversion in one step emits no rlwinm, so nothing is deleted, the
block keeps its first schedule, and the function matches:

```c
lbl_806D1750 = now;           /* s64 -> u8 directly (also `(unsigned char)now`) */
```

`(unsigned int)now`, `(char)now` and a `*(char *)&` store all keep the dead
instruction. General form: when the post-RA schedule is the wrong one, remove
whatever dies in that block (dead truncations/extensions from chained casts,
copies that coalesce) rather than trying to change the dependences.

Two companion levers from the same function (54 -> 4 -> 2 -> 0 diff lines):

- Anchor addressing (§40) only appears when the function names enough distinct
  defined objects of the section. A base-pointer local plus offsets
  (`data + 0x1534`) gives per-symbol `lis/addi`. Split the pool object into its
  real pieces (symbols.txt and source) and name each piece directly.
- A loop counter that must be `li rN,0` rather than a copy of an existing zero
  register needs its own block-local variable (`{ int j; for (j = 0; ...) }`,
  see §46), not the reused function-level `i` and not an inline.

## 70. Saved register chosen "too low" for a value in one branch: where the vreg sits among ALL inline locals decides it (AI_CalcVSTargetSpeed, 11-09)

Two facts measured with mwtrace on this function:

- A saved-register candidate takes the LOWEST-numbered free register among
  the saved registers already in use, and only opens a new one (r31
  downward) when none is free. So "target r27, ours r24" for a value with
  three neighbours means: the target coloured it when exactly r27..r31 were
  in use, i.e. its virtual register sits between two specific locals.
- Locals of an inlined function are numbered in REVERSE declaration order
  (last declared = coloured first). Block-scoped locals inside the inline
  come before all of them.

The start-of-race branch (`VSInitialSpeed`) and the normal branch were two
inlines; the target's `kart * 4` of the first branch is coloured between
`param` and `ctrl` of the second. That is only possible when both branches
share one local list: one inline with `if/else`, `int off` declared between
them, the first branch's `ctrl/cup/round` declared last (so they colour
first and take r31/r30/r29), and the distance rank as a listed local
instead of a nested inline's local (fixes `lwz r28` vs r24 too).

Recipe: read the COLOR lines in order, write the saved registers as a
sequence, and place each declaration so that the list reads backwards.

Follow-up (AI_CalcTargetSpeed_PairTracking, same shape): two more rules were
needed there.

- Which nodes survive the FIRST simplify sweep decides who gets r31/r30. A
  high-degree local that is declared late in the inline (high vreg) sees its
  lower neighbours already removed and is pushed in sweep 1, so the
  arguments end up in r31/r30 instead. Declaring `record`/`ctrl` FIRST in
  the list (low vregs) keeps them for sweep 2, after `self`/`kart`, and they
  are coloured first.
- `cup = g_cupId` is propagated into a CSE temp (lowest vreg, coloured last)
  unless the file has `#pragma opt_propagation off`; then cup/round stay
  locals at their declared position.


Third use (fn_8017DF00, map debug path editor, 11-10, 99.85 -> 100): one
local `node` r28 where the target has r29. `regfix diag` printed the
colouring sequence `@242 r29, @243 r28, ..., node r28->want r29` and the
solver asked for `node` to be numbered right above `@243`. `@241..@243` are
the locals `i, node, point` of the path-printing inline, so the editing
`node` had to sit BETWEEN two locals of that inline: the `else if (left)`
print branch and the final `else` edit branch are one inline
(`if (left) { print } else { edit }`) whose locals are declared
`point, sel, node, i`. Function-scope positions for `node`, an inline for
the edit branch alone, or the print loop written out in the function never
put it there.

## 71. Inline RETURN TYPE as a lever: u8 flag coloured one slot off, and `li r0,-1 / addi r0,n,K / mr rX,r0` (fn_80159BD0, option menu item page, 11-09)

fn_80159BD0 (game/SceneList_80157EA8, 0xB14) went 97.2 -> 100 % with literal
floats. The draft cannot land until the TU owns its .sdata2 (see gave_up.md),
it is kept in docs/wip/notes/r1/fn_80159BD0_match_literals.cpp. Levers, each
worth 0.1 to 1 %:

- `unsigned char special` read after several calls: assign it from an inline
  that returns **int** (`static inline int Item_IsSpecial(int id) { return
  id >= 0x9f; }`). The u8 truncation then happens at the assignment and the
  flag is coloured before the int-to-float conversion constant (r29 vs r28).
  The same inline returning `unsigned char` swaps the two; `bool` and no
  inline are worse.
- Target `li r0,-1; blt; addi r0,n,0x4f3; mr r25,r0` (value built in r0, then
  copied to the saved register): the inline returns **unsigned int** and is
  assigned to an `int` local, or the caller uses a block temp
  (`int t; if (n < 0) t = -1; else t = n + 0x4f3; spr = t;`). Ternary,
  if/return and an int-returning inline all coalesce the copy away.
- Function-level loop ints in the order `idx, j, i, page` (reverse of the
  natural order) give the loop GPRs.
- Block-level floats: the declaration order decides the saved FPRs and even
  HOW MANY are saved (frame 0xe0 vs 0xf0). Declare all of them at the top of
  the block and reorder (§70 rule: last declared colours first, lowest free
  used register). A temp only used as a call argument can be assigned inside
  the call (`f(..., tx = K + px, ...)`).
- A product used only inside the innermost `if` is written there; the
  compiler hoists it itself. Hoisting it by hand changes the FPR.
- `d / 4.0f`, not `d * 0.25f`, when the target loads 0.25 late.

## 72. Two split-lifetime temps in a fixed colour order (RankingMgr_UpdatePositions, 11-09)

Follow-up to 57: two values had to be
split temps coloured in a given order (`box` before the table walker, both
r26). Measured: split ranges of ONE variable are created last range first
(the later range is coloured first); split ranges of two variables follow
declaration order, first declared first. A single-use dummy first range
(`b = (void **)g_gameMode; if ((int)b == 1) return;`) is propagated away
and then the next range becomes the named one, so the function needs
`#pragma opt_propagation off`. The dummy ranges cost nothing (r0 / r3).

Three in a row (ClRomTable_PurgeAll, 11-09): target colours walker, path,
table (r29, r28, r27) and has `addi table; mr walker,table`. Named `table`
never merges with the address temp, and a named walker is coloured last.
All three as second ranges, declared `e, path, table`, with a chain of zero
dummies that folds into the existing `li count,0`:
`e = 0; path = (const char *)e; table = (ClRomEntry *)path; count = (int)table;
table = lbl; for (i = 0, e = table; ...) { path = e->path; ... }` under
`#pragma opt_propagation off`. The `table[i]` form fails under that pragma
(walker init becomes `slwi; add` because `i = 0` is not propagated), so the
walker has to be explicit.

## 73. Pointer local vs shared loop counter in the SECOND loop: make the pointer a CSE temp (fn_8018E538, 11-10)

Two loops share `int i`; in the second loop the target has the element
pointer in r30 and `i` in r29, ours the reverse. Trace: the second range of
`i` is a split-off temp (created after every IRO temp), and a named pointer
`q` is always coloured after it. Split temps are created in the order of
their defining statements, so `q` cannot be made an earlier split temp
(`i = 0` always precedes the loop body). What works: spell the element out
once more next to the named pointer,
`q = &o->particles[i]; if (!(o->particles[i].age < x) && f(&q->pos, ...))`.
IRO_CommonSubs then holds the address in a CSE temp, `q` is propagated into
it, and CSE temps are numbered above split temps. Keeping the shared `i`
matters: only a multi-def counter keeps the `li rI,0; mr rIV,rI` IV init (a
fresh single-def `j` propagates to `li rIV,0`).

Side effect on the FIRST loop: named locals take the lowest free saved
register already in use (see 70), and r29 was opened by the split temp, so
whichever of `p` / `i` is coloured first now gets r29. Declare `i` before
`p` to give `i` r29 and `p` r30.

Same rule the other way round (fn_80170B5C, clKPTrap ctor, 11-10): the
target has `li r29,0; mr r30,r29` (bit counter, then the strength-reduced
`entries[used]` offset) and ours `li r30,0`. The earlier clear loop was
written `for (int i = 0; ...)`; sharing the later loop's counter
(`for (bit = 0; bit < count; bit++)`) makes `bit` multi-def and the `mr`
appears. Diagnostic: `li rA,0; mr rB,rA` at a loop preheader = the loop
counter is reused from an earlier loop.

## 74. Float arguments evaluated BEFORE an int argument: redeclare the callee with the floats first (fn_80158CE4 / fn_8015915C, option menu record pages, 11-09)

Symptom: everything matches except the order in which the arguments of one
call are computed. The target computes the float arguments (`fsubs`, `fadds`,
int -> float conversion with `xoris` / `0x4330`) first and the int sprite id
(`slwi` / `add` / `addi r4,r0,0x7e4`) last; ours computes the id first. In
fn_8015915C the same thing showed up as `xoris r3` / `addi r0` swapped inside
the digit loops.

Cause: MWCC evaluates arguments in prototype order. GPR and FPR arguments are
numbered independently (r3.. and f1..), so `f(int, int, float, float, float,
int)` and `f(int, float, float, float, int, int)` pass exactly the same
registers. The prototype guessed from the asm (ints first) is therefore not
the only possible one, and the order of int versus float parameters is a free
lever for scheduling and for vreg creation order.

Fix: declare the same symbol a second time with another parameter order and
call that. In C++ with C linkage this can be done without changing the other
callers:

```cpp
namespace alt { extern "C" void fn_801695E0(int, float, float, float, int, int); }
...
alt::fn_801695E0(layer, x, y, alpha, 0x7e4 + self->course[i] * 2 + self->mode[i], 0);
```

A cast function pointer does NOT work (it becomes an indirect `bctrl` call).
When every caller turns out to want the float-first order, change the real
prototype instead.

Other levers that were needed in the same two functions:

- fn_8015915C: a named float (`baseX`) took a saved FPR one off. regfix diag
  said "turn the named local into a temp via inline argument": the digit loops
  went into `static inline void DrawDigits(int layer, signed char *digits,
  float x, float y, float alpha)` and the value is passed as an expression.
- fn_8015915C: `float colX; float gridY;` declared first at function level,
  `rowY` as a block local in each branch (colX f25 / gridY f24).
- fn_80158CE4: `#pragma opt_loop_invariants off` around the function, and the
  id written as `0x7e4 + course * 2 + mode` (`(course << 1) + mode + 0x7e4`
  gives 98.39 %).
- Float constants the target reloads per call must be literals, not
  `extern const float` (postprocess_sdata2.py maps the anonymous literals back
  to the shared `lbl_806D....` symbols, so the TU need not own .sdata2).

Landing note: when the last asm function with a manual `.extab_user` /
`.extabindex_user` entry becomes C, delete the manual entries and their lines
in tools/extab_user_renames.json; otherwise the compiler-generated entries are
duplicated and main.dol fails.

## 75. Repeated inline copies use a "busy-avoiding" register where nothing is busy: the copies are one unrolled loop (fn_8017BCF8, clModelM ctor, 11-10)

Three inlined `pN = Point(index + N)` struct copies. The target uses r4 / f1
for the temporaries in all three; ours r3 / f0 in the first two and r4 / f1
only in the third, where r3 (`mr r3,r30` for the return) and f0 (a constant
kept for a later store) really are live. A register that is avoided where
nothing interferes means the temporaries of all copies are ONE variable
whose interference is the union over the copies, i.e. the source is a
constant-trip loop that the compiler unrolled:
`for (int k = 0; k < 3; k++) (&p0)[k] = Point(index + k);`.
The other user of the same inline (Update, fn_8017BF90) has no interference
in any copy and stays matched. Check: the first copy has no `addi`
(`index + 0`), the others reload the member and add 1, 2.

## 76. Target copies a CSE temp into a saved register INSIDE a branch (`lwz r3; ...; beq; mr r27,r3`), ours keeps one register (GabyouItem_Tick_HeldAndHoming_2Eto31, 11-10)

```
lwz r3, 0x304(r3)      ; T = context->target->effects
lwz r28, 0x8(r3)       ; nextTarget = T->nextTarget
cmplwi r28, 0 ; beq
mr r27, r3             ; previousBus = T   (first call below still uses r3)
```
Source shape: `nextTarget = E->nextTarget; if (nextTarget) { previousBus = E; f(E); g(previousBus); ... }`.
Written plainly, IRO turns the second `E` into a copy of the CSE temp and
then propagates that copy away: one saved register, no `mr`. A copy survives
propagation when it is not a plain `local = temp` statement:
- the local's definition is the FIRST occurrence of the expression (the CSE
  temp is created inside it: `previousBus = (T = E)`), which puts the `mr`
  where the local is defined (before the `if` here: 2 lines left), or
- the copy goes through a cast node: `previousBus = (HeldEffectBus *)(void *)E`,
  `void *previousBus = E`, `(T *)((char *)E + 0)` all keep it. This is the one
  that puts the `mr` inside the branch.
The first call may name the local; it still takes the temp (r3) without a reload.
Tried and useless here: reusing a multi-def variable, an inline for the three
calls, assignment in the condition, `#pragma opt_propagation off` (breaks 30+
lines elsewhere in a big function).

## 77. Two instances of one search inline: walking pointers coloured AFTER both instances' counters: index the array in the inline (RivalRun_CalcPathDistance, near miss 100 -> 4 lines, 11-10)

Target (two calls of the same nearest-point inline) colours `i1, best1, i2,
best2` first and only then the two pointers that walk the point array, so the
second counter reuses the first one's register and the second `best` opens a
new one. With a pointer local in the inline (`RRVec3 *p = pts; ... p++`) the
locals are numbered `p < best < i` per instance, so `p1` is coloured before
`i2` and every saved GPR of the second search is off.

Lever: no pointer local in the inline; index instead.

```c
for (i = 0; i < count; i++) {
    d.x = pts[i].x - px;   /* not: p->x - px; p++ */
    ...
}
```

Strength reduction turns `pts[i]` into a walking pointer, but that pointer is
a backend temp created after every frontend local of BOTH inline instances,
hence coloured last. Same instructions, 100 -> 4 register diff lines. The
function is still asm (docs/gave_up.md, draft
docs/wip/RivalRun_CalcPathDistance_regonly.patch); the rest is one `lfs`/`fmr`
direction of a shared zero load.

## 78. Two float constants swap registers (`1.0f` and `255.0f`): the order the constants are CREATED follows expression order, so put the first use inside the later expression (fn_80147AF4 / fn_80147CE8, RaceHud intro fade, 11-10)

Target (GC/2.6): `lfs f2,1.0; ... lfs f3,255.0; fsubs f2,f2,f4; fmadds f1,f1,f2,f0; fmuls f0,f3,f2`.
Ours had f2/f3 swapped with

```c
float t = (o->timer - 30) / 15.0f;
t = 1.0f - t;
int a = (int)(255.0f * t);
float s = 0.2f * t + 1.1f;
```

`regfix diag` said: "backend temp (1.0f load) must be generated AFTER the 255.0f load". Constants are backend
temps, numbered in the order the expressions are walked; the load instructions are scheduled later, so the
instruction order tells nothing. 36 variants of statement order, operand order and inline helpers stayed at
99.72. What matches is the assignment written inside the product, so `255.0f` is walked first:

```c
float t = (o->timer - 30) / 15.0f;
int a = (int)(255.0f * (t = 1.0f - t));     /* fn_80147AF4 */
float s = 0.2f * t + 1.1f;
```

In the sister function fn_80147CE8 (the same `1.0f` is also the scale offset) the ratio has no local at all
and the frontend shares it:

```c
int a = (int)(255.0f * (1.0f - (o->timer - 30) / 15.0f));
float s = 0.2f * (1.0f - (o->timer - 30) / 15.0f) + 1.0f;
```

(`float t; a = (int)(255.0f * (t = 1.0f - (o->timer - 30) / 15.0f));` matches too.) The same repeated form
is 99.6 in AF4 and the AF4 form is 99.1 in CE8, so try both. When diag asks for "constant X generated after
constant Y", move the statement that uses X into the expression that uses Y.

## 79. `lfs fA,K; fmr fB,fA` direction between a named accumulator and an inline local with the same initial constant (RivalRun_CalcPathDistance, 11-10)

Target `lfs f31,K` (dist) + `fmr f27,f31` (the inline's bestDist), ours the
reverse. Mechanism: IRO forwards `dist = K` into the inline's `bestDist = K`,
CSEs the two loads into a temp T, and the first coalescible copy
(`bestDist <- T`, temp-temp) takes T; `dist <- T` is named and stays a copy.
Fix (the 78 lever): give the inline an `init` parameter and write the
assignment inside the argument, `a = Find(pts, count, from, dist = K);`.
Then dist is defined by the load itself and bestDist is the copy.
Things that do NOT work: passing `dist` after a separate `dist = K;`
(forwarded), casts (76 is for pointers), `#pragma opt_propagation off`
(fixes the pair, breaks 220 lines).
Follow-up: the change renumbers the float locals of the SECOND inline
instance; that instance needed its own copy of the inline with the float
declarations in the order `pz, py, px, bestDist` (24 orders swept, one hit).

## 80. Several expansions of one big inline in one function: wrapper level fixes `self`, per-copy local order fixes the rest (CarObject_HandleItemEffect, asm -> C, 214 -> 0 lines, 11-10)

Function: three switch case groups each expand the same "cancel active
effect" routine (7 saved-register locals plus `self`), and three cases expand
the small boost routine. Instruction stream identical, only r22..r29 differ
per expansion.

What the trace (`tools/mwtrace.py ... --only VREG,COLOR`) shows:

- Inline temps are created level by level. All parameter temps of the
  inlines called directly from the function body are created first, for
  every call site; the locals of an inline that is called from inside
  another inline come later. Later created = lower vreg = coloured later.
- The first node that needs a new saved register takes the next fresh one
  (r29 after the two arguments). Every later node takes the LOWEST already
  handed-out register that is free for it.
- Locals of one inline body are created in REVERSE declaration order.
- So the first coloured expansion gets its locals descending from the fresh
  end (creation order = r28, r27, ... r22) and every later expansion gets
  them ascending (creation order = r22, r23, ...).

Two levers follow:

1. Target has the same register (r29) for `self` in every expansion, also in
   the small boost inlines that have no other locals: call the big body
   through a one-line wrapper inline (`static inline int Cancel(T *self)
   { return CancelBody(self); }`). The wrapper's parameter temps are level 1,
   created together with the boost parameter temps, so all of them are
   coloured before any body local and all take r29. With the body called
   directly, `self` is coloured with the body locals and lands on r22 in
   every expansion but the first (214 lines -> 172).
2. Remaining per-expansion order: read each expansion's registers from high
   to low. For the first expansion that list is the creation order, so
   declare the locals in the reverse of it. For the later expansions the
   list read from LOW to high is the creation order. If the three lists do
   not come from one declaration order (here they did not), the function
   only matches with one copy of the inline per expansion, each with its own
   declaration order. That is a fakematch and is marked so in the source;
   the more likely original is three different member functions or a deeper
   inline nesting that nobody found yet.

Also in this function: the two table scans must be written as loops in the
function body (as inlines they share the `li` and take other registers), and
the result flag is `unsigned char` (int gives `clrlwi` instead of `mr`).

## 81. A pointer returned by a search inline is coloured after every other inline local: return it through a reference out-parameter (fn_8018E6FC, 99.07 -> 100, 11-10)

Target `q` (free particle slot) r7, `p` r8, `point` r9; ours `point` r7, `p` r8,
`q` r9 whatever the declaration order. mwtrace: `q = freeParticle(o)` makes the
value live in the inline's RETURN temp (`@197`, created by `CInline_Expand`
when the nested inline is expanded, i.e. after all locals of the outer inline),
and temps created later get lower vregs and are coloured later. The outer
inline's own locals are numbered in declaration order and coloured
last-declared first.

Fix: let the search inline write the result itself and order the outer locals
by the wanted colouring, last-declared = first coloured:

```c
static inline void freeParticle(ViewEmitter *o, ViewBillboardParticle *&out) {
    for (int i = 0; i < 60; i++) {
        if (o->particles[i].age < 0.0f) { out = &o->particles[i]; return; }
    }
    out = 0;
}
...
    unsigned int point;          /* r9, coloured last  */
    ViewMatrixParticle *p;       /* r8 */
    ViewBillboardParticle *q;    /* r7, coloured first */
    ...
    freeParticle(o, q);
```

Sign: a value assigned from an inline's return sits one or two volatile
registers too high and no declaration order moves it.

## 82. Sum passed as a float argument is scheduled after the other argument loads: load the operand into a local, then add in place (fn_8014ADB4, asm -> C, 96.9 -> 100, 11-10)

Target computes `dy + pos.y` (`lfs f0; ...; fadds f2,f31,f0`) before the
`lfs f1` / `fmr f4` of the neighbouring arguments, and keeps `dy` in f31.
Writing the sum inside the call, in a fresh local (`yy = dy + pos.y`), or
in an inline all gave the same late `fadds`; `dy += pos.y` put the result
in f31 plus an extra `fmr`. What matched:

```c
yy = sRankPortraitPos[kart][i].y;
yy = dy + yy;
SPR(0, voice, 0, pos.x, yy, k, k, self->t);
```

The same function needed two more things: the section 74 prototype lever
(all five float params declared before `obj, id, flag`, so `id` is loaded
last), and float literals instead of `extern const float` for the
`t += 0.05f; if (t > 1.0f) t = 1.0f;` clamp (extern constants numbered the
FPRs t=f1/step=f0/max=f2, literals give t=f2/step=f1/max=f0).


## 83. Float register order of a "copy vector, take length, scale" block: literal constant, multiplier through a pointer inline, and which reused local holds the sum (ItemEffect_Projectile, 98.9 -> 100, 11-10)

Same instructions as the target, only f-registers permuted (48 lines). Four
levers were needed together; each alone moved the count up or sideways
(48 -> 50 -> 44 -> 38 -> 0), so do not judge them one at a time (see §62).

1. `extern const float lbl_806D2730` (1/60) -> the literal `1.0f / 60.0f`.
   The extern load is a frontend CSE temp; the literal load is a backend temp
   and is coloured before the products (target f1). `postprocess_sdata2.py`
   renames the anonymous `@N` literal to the target symbol, no split needed.
2. The multiplier goes through a small pointer inline, also for the table
   value: `static inline void Proj_scale(float *v, float k) { v[0] = v[0] * k; ... }`.
3. Named locals: first declared = highest vreg = coloured first. Declare
   `vx; vy; mv; vz; s;` and write the LOADS in the order the target schedules
   them (`vy = obj->velY;` before `vx = obj->velX;`).
4. Second block (velocity copy + length): reuse existing locals instead of
   fresh ones, and choose the roles: `s, vy, vx` take the three loads, `vz`
   takes the sum `p[2]*p[2] + (p[0]*p[0] + p[1]*p[1])`. The sum must be the
   local coloured after the y and z values, and it must stay coalesced with the
   sqrt inline's argument; a fresh local (or reusing the result local) for the
   sum breaks the coalescing and adds an `fmr`.

Do not replace the hand-written copies by `Proj_cpy`/`Proj_len` style inlines:
stores and `frsp` disappear (70-200 lines).

Sign: vector math block at 98-99% with only f0-f7 permuted, constants loaded
from `extern const float`.

Addendum (ItemEffect_Trap, 98.5 -> 100, same day): the same two levers
(literal 1/60 passed to `Proj_scale(v, k)`) fix the float half (36 -> 20
lines). The integer tail needed the id/flag pair copied as ONE struct
assignment (`*(Pair *)&self->activeId = *(const Pair *)&tbl[idx].valC;`)
instead of two int locals: the struct copy's temps are backend temps, coloured
before the owner chain (target valC r3, valD r0, chain r4/r5).

## 84. Add tree of a three-term index is wrong whatever grouping you pick: enumerate all 12 groupings, the frontend rotates them (CalcEarnedCoins, 99.81 -> 100, 11-10)

Symptom: only the two `add`s (and the order of the two `slwi`s) of an index
`a*4 + b*2 + c` differ. Target `r0 = a*4 + b*2; r4 = c + r0`, ours
`r0 = b*2 + c; r4 = a*4 + r0`. Writing the grouping the target shows
(`c + (a*4 + b*2)`) does NOT give it: MWCC's frontend re-associates the sum
before codegen, so the emitted tree is a rotation of the source tree.

What produced the target here:

```c
static inline int CourseClearIndex(int course, int reverse, int isLong) {
    return isLong + course * 4 + reverse * 2;   /* (isLong + course*4) + reverse*2 */
}
```

Measured table (diff lines; 0 = match), terms a=`course*4`, b=`reverse*2`, c=`isLong`:

| source | lines |
| --- | --- |
| `(c + a) + b`, `(a + c) + b` | 0 |
| `c + (a + b)`, `(a + b) + c` | 4 |
| `a + (b + c)`, `a + (c + b)` | 5 |
| every form starting with `b` or ending in `+ a` | 9-10 |

Rule of thumb: the term that the target adds LAST (here `c`) must sit in the
inner sum together with the first-shifted term in the source, and the term
with the smaller shift goes outside. Do not reason about it; a 12-form sweep
takes one minute (script shape: replace the return expression, `ninja` the
object, count diff lines).

## 85. `add rT, rBase, rT` vs `add rT, rT, rIdx`, a u8 parameter coloured first, and an aligned buffer that must be coloured before the address (fn_8028C1B8, 98.37 -> 100, 11-10)

Three independent levers in one function (triforce/amnet_nm3.c), each found
with `tools/mwtrace.py --only COLOR,PCODE`:

1. **u8 parameter wants r31, a `u32 ch = channel;` local gets the last saved
   register.** The named local has a low vreg number and is pushed first.
   Use the `u8` parameter directly where the integer promotion happens
   (`channel << 16`, `channel == 0xFF`): the `clrlwi` result is then a backend
   temp numbered above the .bss anchor and is coloured first. Uses that would
   re-extend the raw parameter after a call (u8 inline parameters, later
   compares) get an explicit `(u32)channel`, otherwise the raw parameter stays
   live and takes one more saved register.
2. **A loop-invariant expression passed to an inline is numbered last.**
   `DevWaitIdle(addr, ALIGN32(raw))` hoists the align out of the inline's
   loop into a late IRO temp (lowest number, coloured after `addr`). Wrapping
   it in a one-line inline (`AlignPacket(raw)`) in the argument creates the
   temp at expansion time, before the callee's parameter temps; it is then
   coloured before `addr` and shares the register of the later `pkt`.
   Calling a nested search inline directly (`FindDev(ChannelDeviceId(ch))`
   written as two statements instead of through a wrapper inline) moves its
   walker one expansion level up in the same way.
3. **`&table[n & 7]` always computes the base into the destination**
   (`addi rT,anchor,0; add rT,rT,rIdx`), whatever the C form (`t += i`,
   `&t[i]`, `(u8 *)t + i * size`). The target had the scaled index in the
   destination and the base in a scratch (`add r8, r3, r8`). Only the integer
   accumulate form gives that: `u32 i = (n & 7) * sizeof(T); i += (u32)table;
   t = (T *)i;` (fakematch). The same change fixed three trace-buffer copies in
   fn_8028C644.

## 86. Scratch registers of a small search inline: declaration order sets the frontend temps, and the masked index must be a real variable (fn_8028C644, 99.88 -> 100, 11-10)

`HandlerFor` (table walk `while ((fns = d->fns) != NULL)`, then
`fns[idx]`): target `fns` r3, `d` r4, `cmd` r5, `idx` r4; ours `cmd` r3,
`idx` r3, `fns` r5. `tools/regfix.py diag` named both edits:

- inline locals are coloured in reverse declaration order (last declared
  first), so `u16 cmd; const NetDispatch* d; const NetHandler* fns;` gives
  `fns` r3;
- with `s32 idx = (u8)cmd;` in the inner block the variable disappears and
  the `clrlwi` is a backend temp, coloured before every frontend temp (it took
  r3). Declared first at inline scope and written `idx = cmd & 0xFF;` it stays
  a variable with the lowest number, is coloured last and reuses `d`'s r4.

## 87. A local vector loaded twice in one block: MWCC only keeps two load sets when one access goes through another object (KartItem_ApplyImpactImpulseAndRumble, asm -> C, 92.4 -> 100, 11-10)

Target: the dot product `row . d` loads `d` (f1, f0, f2, multiplied in place),
and `r = d * len` / `d += w` load `d` again (f13, f11, f9), with no store in
between. In C every spelling of `d[i]` is merged into one load set (351
instead of 354 instructions): pointer locals, struct casts, integer casts,
putting w/r/d/mtx in one struct, named scalar copies, a different statement
order, stores through an unknown pointer (locals are never killed by those).
What keeps the loads apart:

- `volatile float *pd = d;` gives the count but the wrong registers and
  schedule (products not in place), a dead end;
- an access through a neighbouring object: `float *pd = &mtx[-3];` (d sits
  right below mtx on the stack). The instruction selection is then the natural
  one and only the statement order was left: r, rumble store, row copy into w,
  dot (row through `q = &mtx[8]`), k, `w *= k`, `d += w`.

Marked fakematch; the original is probably a C++ Vec3/matrix-row expression we
cannot spell in this C TU. Other levers of the same function:

- `x - q[12]` etc. through a value-parameter inline
  (`KI_sub3(out, x, y, z, q)`) followed by a pointer length inline: the
  differences are coloured before the 16 unrolled matrix copy temps (250 ->
  164 lines). Written in the body they come last (f11-f13).
- sqrt inline with LITERAL `0.5` / `3.0` instead of the extern doubles: sum
  f4, constants f3/f2 as in the target (§83 lever 1 for doubles, 164 -> 76).
- `bne; b` after the 64-bit flag test = the shared `ItemBus_TestFlags(...) == 1`
  inline (result variable with if/else), not an open-coded test.
- three stores to `self->movement->...` with one pointer load: take
  `float *rp = &self->movement->rumbleX310;` first.

Sign: instruction count 3 short in a vector block and the target has two
`lfs` runs from the same stack slots.

## 88. Named locals must be coloured in the middle of an inline's temporaries: the surrounding code belongs to the same inline (fn_8019C6B4, 99.79 -> 100, 11-10)

Symptom (regfix diag / `tools/mwtrace.py`): the target equals our interference
graph, but a function-level named local (`angle`) must be coloured BETWEEN two
temporaries of an inlined helper (the `y` and `z` of QuatMatrix), and backend
temps of an argument expression (`target.z*scale`) must be coloured after an
earlier call-result temp. No function-level spelling can do that: named locals
of the function always have the lowest vregs (coloured last), and locals of an
OUTER inline are created before those of a nested inline (coloured first).

Rules read from the trace (`VREG`, `TEMPNEW`, `COLOR` lines) and Coloring.c:

- `colorgraph` takes the lowest-numbered register in "volatile + already
  obtained nonvolatile" that no coloured neighbour holds; a new nonvolatile
  (f31, f30, ...) is obtained only when that mask is empty. So WHEN a node is
  coloured relative to the nodes that obtain new nonvolatiles decides its
  register (here: angle = f28 needs f29/f28 obtained, f27/f26 not yet).
- Locals of ONE inline become frontend temps created in REVERSE declaration
  order (last declared = created first = highest vreg = coloured first).
- A single-use local of an inline survives as its own temp (a single-use named
  local of the function is propagated away), so `qz = target.z*scale;` in the
  inline gives a frontend temp numbered below every backend temp.

Fix: the `if (angle != 0)` block, the quaternion set and the hand-expanded
matrix build are one inline (`Turn(k, target, q, z + (x+y))`), with all locals
in one list: `float half, scale, sw; float w, z, angle, y, x; float xx, ...,
wz; float qz, qy, qx;` and the products assigned in the order z, y, x, stored
x, y, z, w. The inline is too big for the default limit: `#pragma
inline_max_size(100000)` (marked fakematch; a whole-body inline also expands
with it). 11 -> 7 (angle) -> 0 lines (products).

Sign: the diag says "must be numbered between inline temps @N and @M".
## 89. Saved registers r20..r24 permuted over many short loops: read the colouring order, then move each value to the right side of the first hand-out (VSMode_Init, 99.60 -> 100, 11-10)

Big init function, `stmw r19`, 879 instructions all equal, 112 lines of
r20..r24 renumbering over ten loops. A 6144-variant `for (int i)` x declaration
order sweep had found nothing. What worked was reading the order from the
trace and using the colour rule (lowest free register among those already
handed out, a new one r31 downward only when none is free):

    python3 tools/tracesweep.py trace UNIT FN --want \
      "print([(v,T.phys.get(v)) for v in T.order if 19 <= T.phys.get(v,0) <= 24]) or True"

Order is: high-degree nodes first, then everything else by DESCENDING vreg
(inline temps > FindLoops temps > CSE temps > SplitOffRange temps > named
locals, first declared = highest). Five separate fixes, each read off that list:

1. Three block locals of one loop in swapped saved registers (target slot r21,
   cameraPeer r22, human r24; ours reversed): they are coloured in declaration
   order, each taking a NEW register. Declare them without initializers in the
   order of descending target register (`human; cameraPeer; slot; lap;`) and
   assign below in the order of the target's loads. A function-level `slot`
   shared with another loop had to become two block locals. 112 -> 88.
2. Everything that wants the last register (r20) got r21+: r20 was first
   handed out too late. Its first holder in the target is the value live
   across the widest point (`cc` during `new VSCar(...)`). A named local is
   coloured after all temps; a trivial getter `static inline int VS_cc()
   { return g_ccClass; }` makes it an inline temp, coloured before them. 88 -> 50.
3. Loop counter must take the register ABOVE three loop-body locals (target
   round r20, cup r21, mode r22, i r23): the counter must be a named local
   declared AFTER them. `{ int round, cup, mode; ...; for (int i = 0; ...)
   { round = ...; cup = ...; mode = ...; } }`. The function-level `i` is a
   split-range temp there and is always coloured first. 50 -> 14.
4. `clrlwi. r3,r3,24; beq; mr r20,r3` (target) vs `clrlwi. r20,r3,24; beq;
   mr r3,r20`: the local holding a u8 call result is `unsigned int`, not
   `unsigned char`. 14 -> 8.
5. Volatile pair swapped between a named table-row pointer and the CSE temp
   of `flag * 12` (row r4 in target): the row comes from an inline
   (`VS_row(g_cupId)`), so it is coloured before the CSE temps. 8 -> 0.

All five were found with tracesweep templates on the native compiler (4 s per
24 variants; the real GC/1.3.2 compile of this TU takes 2 min), then confirmed
once with the real compiler.

Sign: `stmw r19/r20`, many loops, only r20..r24 differ, regfix diag lists
"want r20" for several unrelated temps.

## 90. 12-byte struct copy comes out as load-load-store-store-load-store: the source is read out of bounds of its object (CarObjectManager_RunKartKartCollisionSweep, asm -> C, 98.95 parked -> 100, 11-10)

Target copies each `Vec3` start value with three loads then three stores
(`lwz r7/r6/r0 ... stw r7/r6/r0`, interleaved with the next copy and with the
float multiplies). Ours gave `lwz, lwz, stw, stw, lwz, stw` with two
registers, and the multiplies were scheduled after it. Source was the same
`half = cfg->halfA;` in both cases. Cause: `cfg` was a struct view laid over
`lbl_802EBA18[255]` and the fields sat at +0x41c, past the end of that array
(inside the next object). For a load the compiler cannot place inside the
object, the stack stores become dependencies of the third load (mwtrace:
`LWZ ... preds=2`), which fixes the pairwise order.

Fix = the real data layout: the values are separate `static const Vec3`
objects (symbols.txt split of the neighbouring float table), referenced by
name. Four objects in one function are addressed from the pooled `.rodata`
base, so the code still uses `lbl_802EBA18 + 0x41c..`, as the target does.
A `base + big offset` access in asm is usually this pooling, not a struct
view of the first object.

Other levers of the same function:

- `lwz r12,0(r3); lwz r12,0x3c(r12)`: real virtual call, a base struct with
  the virtuals inside `#pragma cplusplus on` (matching_rules 6).
- loop counter `i` coloured second instead of last: it was coalesced with
  the frontend CSE temp of `(unsigned long)i` shared by two call sites (mwtrace
  `COALESCE r48 <- r38 named`). Passing `i` as int (function pointer cast for
  those calls) removes the temp and `i` is coloured as a plain named local.
  The first loop needs the opposite: `unsigned long uk = k;` used for both the
  store and the call (target stores the argument copy r4).
- `bp2 = &bs` as a local took a callee-saved register before the pool base;
  writing `&bs` at each use lets the compiler hoist it itself (r31 first).

Sign: struct copies in a different shape from an otherwise identical
standalone probe; check whether the pointer really points inside its object.

## 91. Argument load order at three call sites of a big C++ ctor (CarObject_Init, asm -> C++, 99.4 -> 100, 11-10)

All three were "same instructions, loads in another order / other argument
registers". Each needed a different lever:

1. `new Tornado(1, driver, character, isPlayer, x, 0.0f, y)`: target emits the
   float constant and `li r4,1` BEFORE the two member loads. §74 again: the
   arguments are evaluated in prototype order, so the callee prototype
   interleaves ints and floats: `(int, Driver *, float, float, int, int, float)`.
   Sweep all 35 positions of the three floats; several match, take the most
   natural one. The mangled name changes: update `extab_user_renames.json`.
2. `new Fade(movement.p, tornado.p, camera.get(), isPlayer)`: target loads the
   camera first. `get()`, `.p`, conversion operators and `operator->` all give
   the same code. A getter WITH A LOCAL (`T *getV() const { T *r = p; return r; }`)
   makes that argument a temp that is loaded first.
3. Inline payload ctor `Blend(this, isPlayer20, speed.p, steering.p)`: with
   parameters, the first parameter gets the lowest register AND arguments are
   loaded right to left, so register order and load order are always opposite;
   the target has both ascending (st r5, sp r6, act r7, loaded st, sp, act).
   Fix: the ctor takes only the owner and reads the values itself, with the
   declarations separated from the loads:
   `unsigned char act; Speed *sp; Steering *st; st = o->steering.p; sp = o->speed.p; act = o->isPlayer20;`
   then the member stores. Declaration order sets the colouring (last declared
   first), statement order sets the load order. Brute-force the 6 declaration
   orders.

Landing notes for a ctor converted inside an asm + manual extab TU:
`main.dol` failed with every function at 100% twice. (a) A holder dtor kept as
an `extern "C"` function next to a declared-only `~Holder()` renamed to the same
symbol was emitted after the following function; defining the real
`Holder::~Holder()` at that place fixed the order. (b) The ctor uses a
ScopedTimer, so the TU gets a weak `__dt__11ScopedTimerFv` with its own
extabindex row; `reorder_extab.py` silently skips a TU whose function set
differs from `tools/extab_order.json`, so add the weak dtor to both lists.
Check with `objdump -r -j extabindex` against the json when only extab bytes
differ.

## 92. Inline counter below the caller's named loop counter, flag coloured before backend temps, table address created after another one (fn_802353EC, 42 -> 10 diff lines, not matched yet, 11-10)

clFlowCCCharaItem ctor with the inlined SetCharaGroup; each lever read from
`tools/mwtrace.py --only COLOR` (saved registers in colouring order):

1. Target `j` (loop counter inside the inline) in the LAST saved register,
   below the ctor's named `i`: an inline local is a frontend temp and always
   outranks named locals. Declare `int j;` as a block local of the caller's
   loop body and pass it by reference (`int &j`, `for (j = 0; ...)`).
2. `unsigned char special = 0; if (cond) special = 1;` puts the flag in a
   frontend temp (coloured after the backend temps of the neighbouring index
   math, it got r4). `unsigned char special = (a && b) || c;` materialises
   the boolean in a backend temp created after them: flag in r0, the index
   temps in r3/r4 as in the target.
3. Two address computations swapped r3/r4 (`grp[i + 2]` vs
   `kCharaGroups[which][index]`): the one that must take the lower register
   has to be CREATED later. Pass the array and the slot (`groups, slot`) and
   load `Sprite **group = groups[slot];` inside the inline after the `id`
   line; keep `int group = i + 2;` as a named local in the caller or the
   `+ 2` is folded into the displacement.

Left: the special branch's `res` takes j's free register (r19) instead of
the walker's (r23). `j` has degree 29 (survives the first simplify round and
opens r19 before `res` is coloured); see docs/gave_up.md.

## 93. Inline `this` temps coloured before an address CSE temp: call the method through one reused named pointer local (fn_801B9928, 99.77 -> 100, 11-10)

Seven `arr[i]->SetPosition(x, y)` calls after `arr[i] = new Sprite(...)`. The
target keeps `&arr2[3]` (a CSE temp, reused by the 7th call) in r4 and every
sprite pointer in r5; ours the other way (40 lines). `regfix diag`: the seven
loads are the inline's `this` temps (@657..@667, frontend temps, high vreg,
coloured first, so they took r4) and the address is CSE temp @715 below them;
"they must be coloured after it".

A named local is numbered below every temp, so loading each sprite into ONE
block-local pointer and calling through it moves all seven below the CSE temp:

    { CourseSprite *s;
      s = arr[0]; s->SetPosition(x, y);
      s = arr[1]; s->SetPosition(x, y);  ... }

(the frontend forwards `s` into the inline `this`, the value keeps the named
local's number). Not the same: one local per call or a local declared at the
store (tried 11-09, no gain), direct field stores without a local or a static
inline taking the pointer (46-57 lines).

**Check:** regfix diag says a short-lived `this` / pointer temp of repeated
inline calls holds the register an address or CSE temp wants: assign the
object to one reused block-local pointer before each call. Rule
`inline-this-via-reused-named-local`.


## 94. Three small levers from TimeAttackResult's ctor (fn_8021C070, 96.27 -> 100, 11-10)

1. **`li rA,0; mr rB,rA` at a loop entry (ours `li; li`)**: rB is the
   strength-reduced offset counter of `arr[i]`, rA is `i`. The copy only
   appears when the loop sits in an INLINE (`static inline void
   TA_makeDigits(TimeAttackResult *self, int &res) { for (int i = 0; ...) }`).
   Written in the function body the two `LI` stay separate (mwtrace: source
   line vs line -1 in one block); comma inits, a second counter, `j = i`,
   declaration orders and the opt_* pragmas do not change that. A local that
   must be coloured after the inline's temps goes in as a reference parameter
   (the caller's named local, see 81).
2. **Double bool conversion** (`subfic/cntlzw/srwi 5` then `neg/or/srwi 31`
   for `x == 1` stored to a bool field; ours stored the compare directly or
   with `rlwinm ...,24,31`): the value is an `int`-returning inline
   (`return g_flag == 1 ? 1 : 0;`) passed to a `bool` PARAMETER of an inline
   MEMBER function. A static inline setter, a cast or a bool local do not
   convert twice.
3. **Volatile registers of a field-by-field fill in descending order**
   (target time r8, cup r7, ..., kart r0 with stores in field order): the
   setter's parameters are in REVERSE field order
   (`Set(int k, int ch, int c, bool rev, bool lng, int cu, int t)`), the body
   stores in field order, called on the global directly (no `T *e` local).

Also: float arguments in the wrong load order from `extern const float`
(`lfs f5` before `lfs f1`): literals (see 83), `postprocess_sdata2.py` renames
them.

## 95. Two saved parameters swapped: advance the index through a `long` local, read the base through an inline getter (fn_80243074, 36 -> 14 diff lines, not matched yet, 11-10)

**Symptom:** `index` (r4) and `position` (r5) are both kept across calls and
land in r28/r29 instead of r29/r28. Parameters are numbered in declaration
order and the higher one is coloured first, so `position` always wins; copies
of a parameter into an `int` local are propagated back onto the parameter.

**Lever:** two changes that only work together.

```cpp
static inline RivalPath *PathOf(RivalMarkerHud *self) { return self->path; }
...
RivalPath *path = PathOf(self);       /* inline temp instead of a named local */
int total = Path_GetTotalCount(path);
long i = index;                       /* long, not int */
long old = i;
i = (i + 1) % total;
a = Path_GetWaypointPtr(path, old);
b = Path_GetWaypointPtr(path, i);
```

With `long i` the advanced value is a frontend temp (numbered above every
named local and parameter) while `old` stays on the parameter; the two ranges
do not overlap. `path` as an inline temp is coloured before that temp and
reuses r31 (free after `b`), so the temp opens r29, `position` takes r28 and
the old index, coloured last, takes the lowest free register in use, r29.
With `int i` (any spelling) or with `path` as a named local nothing moves.

**Check:** regfix diag says a parameter must be numbered above a later
parameter, and the parameter is reassigned once (`index = f(index)`).

## 96. Epilogue restores in the wrong order, everything else equal: the last block must be scheduled again after register allocation (fn_801D7610, 99.94 -> 100, fakematch, 11-10)

Target epilogue `lwz r31; lwz r0; lwz r30`, ours `lwz r31; lwz r30; lwz r0`.
`mwsched.py resched` said the diff disappears when the last block is scheduled
again after register allocation (mwcc_internals "Post-RA scheduler": a block
is rescheduled when an instruction in it was deleted or inserted after the
first scheduling, for example a coalesced `mr`). About 60 source shapes of the
tail left the block untouched, because the frontend forwards every local.

What deletes an instruction there: a copy into the return register. Writing
the three `lbl_806D12E4[n] = 0` stores as
`for (p = lbl_806D12E4, i = 0; i < 3; i++) p[i] = 0;` and ending with
`return p;` (function type `unsigned char *`) emits `mr r3, p` in the last
block; allocation coalesces it away (p already wants r3), the block loses an
instruction and is scheduled again. Instructions are unchanged. Both parts are
needed: `return lbl_806D12E4;` without the loop pointer loads the address
twice (no copy), and the loop pointer in a void function is forwarded.

Marked fakematch (callers use it as void). The same symptom in
CardData_InitDefaults is not fixed by it yet (there r3 holds the zero constant
at the exit and constants are forwarded, so no copy is left).

**Check:** only the epilogue `lwz` order differs and `mwsched.py resched`
reports a match for the last block: make the function return a value that the
last block already holds in r3 through a named multi-def local. Rule
`return-copy-reschedules-last-block`.


## 97. Ordering several block values at once: outer inline parameter > nested inline locals > CSE temps > named locals (AI_CalcLapSpeedBonus, 99.88 -> 100, 11-10)

Symptom: a short block computes three or four values (an index copy that is
wrapped, two offsets, a table base) and they get the right instructions in the
wrong volatile registers. mwtrace shows the numbering: named locals lowest, then
SplitOffRange and CSE temps (with `opt_dead_assignments off` every propagated
initialiser becomes a CSE temp), then inline temps, where an EARLIER created
temp has the HIGHER number and is coloured first.

Levers, all read off `python3 tools/mwtrace.py UNIT FN` (`VREG` lines and
`PCODE pre`):

- A value that must be coloured first: make it a parameter that the inline
  modifies (`if (section >= 4) section -= 4;`). Moving the statement up instead
  changes the block shape (the `if` is emitted before the other values).
- To get it numbered above other inline temps without moving its statement,
  make it the parameter of an OUTER inline and compute the other values through
  NESTED inlines called inside it; the outer argument temp is created first.
- A single-use value survives as an inline temp only as a local of the nested
  inline (`int o = ...; return o;`). A plain `return expr;` getter is propagated
  and the value falls back to a CSE or backend temp.
- A value that must stay lowest (here `g_ccClass * 128`) stays a local of the
  outer inline; CSE replaces it with a temp below every inline temp.
- A caller local that must be assigned late (its `extsb` belongs after the
  branch join) can be written through a pointer parameter at the right place in
  the inline; pass the inline call directly as the argument so that its result
  stays a parameter temp (a named `rules` local swapped two more registers).

```c
static inline int CupOffset(int cup) { int offset = (cup - 1) * 16; return offset; }
static inline const char *Table(void) { const char *table = (const char *)kTable; return table; }
static inline const Rule *Rules(int section, int cup, signed char *cc) {
    int courseOffset; const char *courseBase; int ccOffset;
    courseOffset = CupOffset(cup);
    ccOffset = g_ccClass * 128;
    courseBase = Table();
    courseOffset = ccOffset + courseOffset;
    if (section >= 4) section -= 4;
    *cc = g_ccClass;
    return *(const Rule *const *)(courseBase + courseOffset + section * 4);
}
...
signed char cc;
FindBonus(cc, Rules(round, cup, &cc), ...);
```

Blind sweeps did not find this (24 declaration orders, 24 parameter orders, 40
statement orders); each step came from reading which value had which vreg.

## 98. One saved register off for a late inline `this` temp: move two named locals of an earlier block into a level-1 inline (fn_801BE170 = NameEntry::Update, 23 -> 0 lines, fakematch, 11-10)

Symptom: the owner pointer of `(*it)->Tick()` at the end of the function sits
in r28 where the target has r26; everything else is equal. `mwtrace`
(`Update__9NameEntryFv`, the mangled name is needed) shows the order of the
low-degree group: all temps in descending vreg, then the named locals. The
owner is the inline `this` temp of Tick; it is coloured before the named
`dx`, `btn`, `vert` and takes the lowest saved register obtained so far (r28).
Target r26 means: `dx` (r27) and `btn` (r26) are coloured BEFORE the owner and
`vert` (r25) after it, i.e. dx and btn are temps numbered above the Tick temp.

What does not work:

- A named `FadeObj *n` declared between btn and vert has the right number but
  degree 29 = available registers, so `simplifygraph` (one ascending sweep, a
  node is pushed only when degree < 29 at that moment) leaves it for round 2
  and it gets r31.
- Parameters of a nested (level-2) inline: nested inlines are expanded after
  all level-1 inlines of the function, so their temps are created after the
  Tick temp and are numbered below it.
- Two parameters of one inline: the arguments are evaluated right to left, so
  the order that numbers dx above btn loads `held` before `dir`.

What works: the whole block becomes one inline member whose ONLY locals are dx
and btn (declared `int btn; int dx;`, the later declaration is created first
and gets the higher number), assigned in the original order inside it. Every
other local of the block (vert, c, r, wrap) stays a named local of the caller
and is passed by reference, so its number and code do not change (as inline
locals c/r swap registers and the `r = 0` constant merges with another zero).
`#pragma inline_max_size(100000)` is needed for the block to expand.

**Check:** a saved register differs only for a value defined late; the trace
shows named locals of an earlier block coloured after it that the target
colours before it. Rule `named-locals-to-level1-inline-temps`.


## 99. Three stale-lever checks that finished TaMode_FrameUpdate (99.65 -> 100, 11-10)

1. **A leftover `#pragma opt_propagation off` around the function.** It had been
   added to keep a local alive; later it was the cause of a diff: the `&temp`
   of by-value struct arguments (`VfxSlotMgr_Update(vecA, vecB)`) stayed in
   `LinearizeExpr1` temps (`ADDI r84,r1,..; MR r4,r84` in `PCODE pre`), so
   `addi r3,r1,0x18` was scheduled late and the two `lis` registers swapped.
   The same statement matched in the sibling RaceScene_FrameUpdate without the
   pragma. When a block that matches elsewhere differs, check for function-wide
   pragmas first.
2. **Named local one saved register too high (`started` r28, target r26).**
   The target register was first handed out to a later block-local pointer
   (`void *camera = g_raceCamera;`, a LinearizeExpr1 temp numbered below the
   named locals). Declaring `void *camera;` at function level just before
   `started` numbers it above `started`; r26 is then already handed out when
   `started` is coloured and the lowest free register wins (section 89).
3. **`x = B; if (!c) x = A;` versus `x = !c ? A : B;`.** Both compute B first
   and branch over A, but with the conditional expression the inline arguments
   keep their evaluation order (cup, reversed, then the global read in the
   body) and `cmpwi` stays early; the assignment form loads the condition last.
   `c ? B : A` computes A first and inverts the branch.

Rule `stale-propagation-pragma-and-cond-expr`.

## 100. A constant in r4 and the loads beside it in r3 (target the other way): keep the loaded word in its own local, with opt_propagation off (CardSaveData_Parser, 99.81 -> 100, 11-11)

Diff: `li r4,2 ... lwz r3,0x34(r1); neg r0,r3; or r0,r0,r3 ... li r4,0; stw r4`
where the target has r3 and r4 exchanged, in two places (18 lines). Source:
`u32 progress = 2; flags[4] = *cleared != 0; flags[8] = *visited != 0;
if (*award == 0) progress = 0;`.

Cause (regfix diag): the loads of `cleared` / `visited` are backend temps, so
they are numbered above `progress` (a named or inline local) and coloured
first, taking r3. The target needs `progress` coloured first. Writing
`u32 flag = *cleared; flags[4] = flag != 0;` changes nothing: copy
propagation removes `flag` and the load is a backend temp again. `?:` for the
constant gives branch-free code (264 lines).

Fix, three parts that only work together:
1. `#pragma opt_propagation off` around the function, and the loaded word in
   a local declared BEFORE `progress` (`u32 flag; u32 progress = 2;`). `flag`
   now has the lower number and `progress` gets r3.
2. This only took effect inside an inline. The same statements written in the
   function body kept r3/r4 swapped in both declaration orders, so the second
   place (one record, another layout) became a second inline,
   `StoreCardTotalResult`.
3. The pragma changed two other places, which were then written by hand:
   - `cardName[nameIndex]` was no longer strength-reduced (`slwi; add`). A
     walking pointer as a named local is coloured r23 (target r29, counter
     r24). The pointer has to be an inline local while the counter stays the
     caller's named local: the loop moved into an inline that takes the
     counter by address (`int *index`). Marked fakematch.
   - `dest[(rule->group*4 + slot) + 0x23]` computed the sum the other way
     round (`add r3,r0,r3`); `int idx = rule->group*4; dest[idx+rule->slot+0x23]`
     gives the target. The inline getter for `slot` is no longer needed.

So a function-wide pragma that section 99 calls a suspect can still be the
fix; expect to repair its side effects one by one.

Rule `propagation-off-load-local-before-constant`.
