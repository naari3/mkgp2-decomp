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

Target shape (CSPartsHolders fn_8014D038, anchor `lbl_80362D90` in r31):

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
matching_rules). For CSPartsHolders that means the pool `lbl_80362D90`
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
(`lbl_8032A348` became `lbl_8032A348` + `lbl_8032A354[2]`) and copy member by
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

The same shape probably explains KartMovement_CollisionUpdate (`&contact` in
r31, an onmokoworks claim). It did not help for `&rotation` inside the
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

MWCC splits a named local into webs. Only the first web keeps the named-local vreg number (low, coloured last); every later assignment of the same variable gets a frontend temp number. In fn_801F1244/fn_801F140C the target colours both fade colours (`0xFFFFFF00 | v`, then `0xFFFFFF00 | (u8)(255 - v)`) into the same register below the loop counter/offset, but with one `c` assigned twice the second colour was a temp coloured first (27 lines off). Fix: give each assignment its own named local (`c`, `c2`) and let the decl-order solver pick the order (`c, c2, offset, i, v`).

The same family: a local whose value comes straight from an inline return (`c = MenuRGBA(v, v, v, 255)`) is copy-propagated away and the colour stays an inline temp. Write the expression in place (`c = (v << 24) | ((v & 255) << 16) | ((v & 255) << 8) | 255`) so `c` survives as a named local, then sweep the decl order (fn_801F2400, fn_801F1EE0: `c, offset, i`).

How to spot it: `regfix.py diag` asks for "temp @N must be numbered after <named local>" and @N is the def of a variable that is already a named local earlier in the function, or the value of an inline call assigned to a local.

## Still open (same shape, no fix found yet)

- r0 coloring quirk with a `0xFFFFFF00` rlwimi colour: clFlowCourse,
  clFlowGpPlease_Init (try pattern 11 first; both are onmokoworks claims).
- Value and table pointer swapped r4/r5 in two lookup loops:
  NameCheck_CardName. Tried 120 decl orders, temps, cmp swap, pragmasweep and
  20 minutes of cperm.
- Quad-ctor FPR coloring: fn_801F8404/fn_801F8728 (the fn_801F7F50 recipe
  f4d48738 plus `fabs(h)` before `fabs(w)` leaves pure f-register coloring),
  wip/audit.
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
| `Items_ResolveOwnedAlias` | game/Items.cpp | 98.89 | Resolved: redundant mr r5,r4 between alias-table base and induction walker, making source 384 B vs target 380 B. | Use &lbl_80315AA8[i] rather than a separately initialized/incremented row pointer; compiler strength reduction forms target walker directly: 100.0%. Removing the now-unused row declaration preserves 100%. | 1b170b0c |
| `upvec2roll` | sysdolphin/baselib/cobj_nm2.c | 98.87 | Resolved: initial validation emitted beq plus an extra unconditional b instead of target bne into valid body; +4 text bytes also shifted constant relocation... | Keep camera/eye-object validation in the outer if/else and place the output-pointer failure return inside the valid-camera branch: 100.0%. | 59485ee9 |
| `acReadResponse` | triforce/acsocket_m8.c | 98.83 |  | Order case 1 locals addr,len,base,lenOff,n to match the two named register pairs: 100.0. | 8544fc12 |
| `fn_801FC364` | game/anon_801FC1E0.cpp | 98.77 | none; exact | Capture initialTimer before input edge reset and set subState before timer assignment: 98.76744 -> 100.0. | aaa29b32 |
| `fn_8023B1A8` | game/ItemSelectChoiceInit.cpp | 98.75 | Resolved: table base addi to r0 plus extra mr r29,r0; player address addi destination r4 versus target r0. Extra instruction shifted EH start D8 versus... | Remove both explicit pointer cursors and read lbl_803DC180[row][column]; compiler strength reduction now gives row r29 / item r30 and exact global-address setup: 100%. | 9200c6fe |
| `DrawEffect_KartDustRing_Update` | game/DrawEffect_KartDustRing_Update.c | 98.11 | Resolved: external aggregate pointer materialization added mr r30,r4 and used mr instead of addi r4,r30,0 for tier 1. | Integration visibility correction within the same approach: static vectors caused unresolved neighboring ItemHitBurst/ItemHitOriented references in request 1; exporting the vectors preserves 100% text/EH/index/data... | 6668a75d |
| `Effect_TwoChildRotate_FromPhase150` | game/EffectRotatePair.cpp | 97.30 | Resolved: FP scratch identities in alpha clamp/phase wrap; addi group and lbz enable scheduling at +0x40/+0x44. | Enable belongs to the group view at +0xC4 (parent +0x190); express access through group, restoring addi-before-lbz, 100%. | 3fc53253 |
| `fn_8022B278` | game/EnemyFace_nm1.cpp | 97.26 | Resolved GPR partition: target textures/palettes/resources/tluts r31/r30/r29/r28, outer i r27, count n r26, inner k r25. Initial indexed inline helper... | Keep natural textures/palettes/resources/tluts increment order: 100.0%, all owned sections exact. | c928fb29 |

