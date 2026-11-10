#!/usr/bin/env python3
"""shapediag.py: diagnose a near miss whose INSTRUCTION SEQUENCE differs.

    python3 tools/shapediag.py fn UNIT FN [--ours OBJ] [--json] [-v]
    python3 tools/shapediag.py objs TARGET.o OURS.o FN [--ours-fn NAME]
    python3 tools/shapediag.py batch [--min 0] [--md docs/reports/shapediag_census.md]
    python3 tools/shapediag.py classes          # the class -> lever table
    python3 tools/shapediag.py selftest

`tools/regfix.py diag` explains register-only diffs with a model of the
allocator. This tool needs no model: it reads the two disassemblies
(objdump -dr of the target object and ours), aligns them with registers
abstracted away, and puts every difference into a class with the source
levers that fixed that class before (docs/regalloc_patterns.md sections,
docs/matching_rules.md). `regfix diag` calls it by itself when the diff is
not register-only, so one command covers every near miss.

How a diff is read
  1. Each instruction becomes a key: mnemonic + operands with rN/fN replaced by
     R/F (r1, r2, r13 kept), immediates and relocation symbols kept.
  2. difflib aligns the key sequences. Equal runs are checked pairwise for
     register-level facts (commutative operand swap). Unequal runs are hunks.
  3. A hunk with the same key multiset on both sides is a reordering. Other
     hunks are aligned again on the mnemonic alone, which leaves 1:1 pairs
     (same opcode, another immediate / symbol / stack slot, or another opcode)
     and target-only / ours-only instructions.
  4. Detectors turn those into findings (CLASSES below). Function-level facts
     (frame size, number of saved registers, call list) are compared as well.

The output is a ranked list of classes, each with the place in the function
and the levers to try. It is a clue for a hand rewrite, not a rewriter.
New pattern landed? Add a detector or a lever line to CLASSES and a case to
`selftest` (docs/regfix_coverage.md lists which sections are covered).
"""
import argparse, collections, difflib, json, os, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EXE = ".exe" if os.name == "nt" else ""
OBJDUMP = ROOT / "build" / "binutils" / f"powerpc-eabi-objdump{EXE}"
VERSION = "GNLJ82"

# --------------------------------------------------------------------------
# class -> (title, levers). Section numbers are docs/regalloc_patterns.md
# unless they say "rules" (docs/matching_rules.md) or "tips" (docs/thread_tips.md).
CLASSES = {
    "order:const": ("constants are created in another order", [
        "constants are numbered in the order the expressions that use them are generated: put the first use inside the later expression, `f(..., dist = K)` (78, 79)",
        "float literal instead of `extern const float` or the reverse (12, 61, 83 lever 1; rules 5); doubles too (87)",
        "pass the zero/constant into the inline as a parameter, or load constants once through reverse-declared locals (61)",
        "both values as named locals, the one that needs the higher register declared first (63)",
    ]),
    "order:args": ("call arguments are loaded in another order", [
        "arguments are evaluated in PROTOTYPE order: redeclare the callee with the float params before/after the ints, sweep the positions (74, 37, 91 lever 1)",
        "a sum/expression argument scheduled early: load the operand into a local, then `yy = dy + yy` in place (82)",
        "one argument loaded first: fetch it through a getter WITH a local (`T *r = p; return r;`) (91 lever 2)",
        "inline ctor/setter: take only the owner, declare locals in colour order and load them in statement order (91 lever 3)",
        "globals kept in saved registers and passed: assign inside the call, `f(p, cup = g_cup)` (rules 7.8)",
        "one small inline per scalar argument (`RankingPlacementY()`, fn_801D2F0C); literal constants instead of extern loads (KartFx_DriftSparkParticleTick); right-to-left evaluation of a `Show(...)` call with py declared before px (fn_802064D8)",
    ]),
    "order:store": ("stores (or a load and a store) are in another order", [
        "store order is statement order: reorder the assignments / member initialisers (7); in a ctor the base-class initialiser is generated first: store the base vtable in the derived ctor body (36)",
        "a local array initialiser vs element-wise assignments (clFlowKart merge)",
        "a load moved ABOVE a store in the target: the compiler knew they cannot alias: `__restrict` on the pointer params, a `const` view of the global, `extern const T tbl[N]` (30; rules 7.8, rules 5)",
        "a load stuck BEHIND stack stores: the pointer runs outside its object (31, 90); declare the real objects",
        "loads hoisted over stores everywhere / `lfs; lwz; lfs` interleaved: the TU is GC/2.6 (rules 4)",
        "long straight-line copy runs: the scheduler works in 26-statement regions (8)",
        "evaluation/source order of the assignment (`g = f(...)` vs temp then store, fn_801CDF10); `frsp` result vs original stored: keep the query in the outer function (Item_BendVelocityByGroundProbe); string/rodata ownership, `-rostr` (fn_801E4544)",
    ]),
    "order:copyrun": ("a struct/array copy has another load/store interleave", [
        "load-load-store-store-load-store vs three loads then three stores: the source is read outside its object; declare the real objects and let the compiler pool them (90)",
        "repeated point copies as ONE unrolled constant-trip loop (75), or a real loop where the target reloads (21)",
        "`lwz,lwz,stw,stw` of two adjacent ints is one 8-byte struct copy; stack aggregates are placed by ascending size (rules 7.9)",
    ]),
    "order:other": ("same instructions, another order (scheduler)", [
        "`python3 tools/mwsched.py explain UNIT FN --run` and `regfix diag --sched` show which dependency differs",
        "a pure reordering with identical registers: the block was scheduled twice (dead truncation `(int)x` to u8, 69)",
        "one `mr` and one `lfs` swapped in a loop preheader, or loads above `stw r0,0x14(r1)`: compiler version, try GC/2.0 / GC/2.6 (rules 4); GC/1.2.5: unscheduled block (33)",
        "statement order inside the block; a value computed before the local that holds it is declared (23)",
    ]),
    "copy:direction": ("a copy runs the other way, or sits at another place (`mr rA,rB` vs `mr rB,rA`)", [
        "the register that is DEFINED first belongs to the variable/temp that is created first: `lwz r29,g; mr r4,r29` = the local is loaded and then passed; `lwz r4,g; mr r29,r4` = assigned inside the call, `f(p, cup = g_cup)` (rules 7.8)",
        "copy of a CSE temp into a named local: `prev = (T = E)` puts the `mr` at the definition, `prev = (T *)(void *)E` puts it in the branch (76)",
        "`addi rBase,..; mr rWalker,rBase` vs the reverse: the base must be a second lifetime range of a reused variable (57); pointer local declared before the value local (59)",
        "`li rA,K; mr rB,rA` / `lfs fA,K; fmr fB,fA` direction: which of the two is an inline local (67, 79)",
    ]),
    "order:regswap": ("two registers are exchanged in a run of otherwise equal instructions (colouring, not scheduling)", [
        "this is a register diff: `python3 tools/regfix.py diag UNIT FN` (colouring order, declaration order)",
        "two strength-reduction walkers: they are numbered in creation order; touch the one that needs the lower register first, `record = &base[i]; f(record, ...)` (63 lever 3); index the array in the inline (77)",
        "pointer local vs shared loop counter: make the pointer a CSE temp (73); block-local counters (46)",
        "compute the pointer before assigning the indexed descriptor (fn_8016A854); one inline helper per child `updateChild(row, group, effect, i)` (Effect_KartJoint12_3Stage_Update)",
    ]),
    "order:load": ("loads are scheduled in another order", [
        "a global/member load moved UP in the target: the compiler knew no store in between can alias: `__restrict` on pointer params, `const` view, read-only table as `extern const` (30; rules 7.8, rules 5); loads hoisted everywhere: GC/2.6 (rules 4)",
        "evaluation order: the first operand of an expression is loaded first (64); load a value into a local earlier / later (3, 23, 82)",
        "which value is a named local and which a temp decides who is loaded first (declaration order does not): inline getter with a local (91 lever 2), value-parameter inline (87)",
        "`python3 tools/mwsched.py explain UNIT FN --run` names the dependency that differs",
        "const-qualify the pointee as well: `const char *const tbl[]` for a .rodata table (fn_80201BE8); native local aggregate initialisers (DrawEffect_Cb_RalySmokeVariant_Tick); declaration order of the two values (fn_801F7F50)",
    ]),
    "order:expr": ("arithmetic of one expression is emitted in another order", [
        "sub-expressions are emitted in evaluation order: swap operands / regroup; a three-term sum has 12 groupings, brute-force them (84; `leversweep.py fn UNIT FN --levers sum3-regroup`)",
        "first operand = first evaluated (64); read the creation order off the registers and write it as ONE expression (58)",
        "an assignment inside the expression fixes which constant/term is created first (78)",
    ]),
    "order:loopstep": ("the increments at the end of a loop body are in another order", [
        "loop step order: the target bumps the pointer before the count: walk with a separate index, `while (t[i].name) { i++; count++; }` (rules 7.8, CollisionFile_Load)",
        "order of the `for (...; a++, b++)` clause; which of the two is the declared loop variable and which a strength-reduction walker (60, 63 lever 3)",
    ]),
    "order:epilogue": ("the register restores of the epilogue are in another order (`lwz r0` position)", [
        "the last block is scheduled a second time (or not) after regalloc: `python3 tools/mwsched.py resched UNIT FN` (docs/mwcc_internals.md 'Post-RA scheduling')",
        "make regalloc delete or insert something in the last block: a copy that coalesces, a dead truncation (69), the callee's real return type (fn_8017EFFC: `unsigned char f(int)`)",
    ]),
    "order:blocks": ("basic blocks are laid out in another order", [
        "swap the if/else arms or negate the condition; move the early `return`; order of switch cases",
        "`if (a || b == X) return;` for `cmpwi; bne body; b end`; empty `case N: break;` for an extra switch node (rules 7.5)",
    ]),
    "copy:target-extra": ("the target keeps a copy (`mr`/`fmr`) that ours does not have", [
        "a named local assigned from a temp is never coalesced: the target has a NAMED local here; add it",
        "`mr rSaved,rTemp` inside a branch after the load: copy a CSE temp through a cast, `prev = (T *)(void *)E`, or define the local at the first occurrence, `prev = (T = E)` (76)",
        "a base-address local survives only with two uses (44); pointer local declared before the value local (59)",
        "`li rA,K; mr rB,rA`: two variables with the same initial value that are locals of an INLINED function (67); `lfs; fmr` (79)",
        "`mr` of an argument: the callee is an inline taking the value by value, or `unsigned long uk = k;` used for both store and call (90)",
        "`python3 tools/mwsched.py coalesce UNIT FN --run` lists the copies the allocator kept",
    ]),
    "copy:ours-extra": ("ours has a copy (`mr`/`fmr`) the target does not have", [
        "ours has a named local the original did not: use the expression directly, or reuse an existing variable (3, 26)",
        "`x += y` gives result-in-place plus `fmr`: `t = y; t = x + t;` (82)",
        "an inline parameter copied: pass by reference / const reference, or write the body in place (5, 38)",
        "a call result that takes the wrong dying register: name it inside the inline (16)",
        "`fmr` of a constant argument: literal `0.0f` instead of the extern constant (Item_SpawnHitBurstParticles); read the member directly in the compare instead of through a local (setupTopHalfCamera)",
        "keep the computation local to its inline helper instead of a caller local (GameTestTopMenu_Page, card_unpack_legacy_dispatch)",
    ]),
    "operand-order": ("a commutative instruction has its operands swapped", [
        "the first operand is the first EVALUATED: swap the source operands (`a * b` -> `b * a`) (64)",
        "`add rT,rBase,rT` vs `add rT,rT,rIdx`: `base[i]` vs `*(base + i)`, cast form of the index (85); member offset added after the index (42)",
        "a three-term index sum: brute-force the 12 groupings, the frontend rotates them (84); `python3 tools/leversweep.py fn UNIT FN --levers sum3-regroup`",
        "wrap just that product/sum in a small static inline (`static inline float Row(float row, float origin) { return row + origin; }`): the parameter order fixes the operands (Codex: fn_8020579C, fn_801F6C2C)",
        "a literal instead of an extern constant inside the product, `(10.0f * scale) * k` (ItemObject_CheckKartCollision); declaration order / lifetime of the accumulator (KartFx_BurnoutChargeTick)",
    ]),
    "load:target-reloads": ("the target loads a value AGAIN that ours keeps in a register", [
        "do not cache it in a local: write the member / global expression again at the second use",
        "stack vector loaded twice in one block: an access through a neighbouring object (`&mtx[-3]`), fakematch (87)",
        "a store in between that may alias in the target: drop `__restrict`/`const`, store through the real (non-char-safe) pointer type; unrolled store run that reloads = write the loop (21)",
        "reload after a call: the value is not a local in the original (global or member read each time)",
        "`#pragma opt_common_subs off` for the function (1, 29), then re-create the CSEs you still need by hand",
        "a CONSTANT reloaded (`lfs fN,lbl@sda` twice): literal vs `extern const float` decides whether it is kept in a register (rules 5; KartPair3ArmUpdate: `c->yaw[i] *= -1.0f`)",
        "cached values through axis/scale inline helpers, scale-first multiply (fn_802064D8)",
    ]),
    "load:ours-reloads": ("ours loads a value again that the target keeps in a register", [
        "cache it in a named local (snapshot before the stores / calls)",
        "the stores in between cannot alias in the target: `__restrict` on the input pointers (30), `const` view (rules 7.8), read-only table as `extern const T tbl[N]` (rules 5)",
        "the pointer walks outside a sized array so the compiler cannot prove no alias (31)",
        "take the address once: `float *rp = &self->movement->x;` for several stores through one pointer load (87)",
    ]),
    "load:const-vs-copy": ("a constant is loaded (`lfs`/`li`) on one side and copied (`fmr`/`mr`) on the other", [
        "`lfs fA,K; fmr fB,fA` direction between a named accumulator and an inline local with the same initial constant (79)",
        "`li rA,0; mr rB,rA`: both variables are locals of an inlined function (67)",
        "literal vs `extern const float` (12; rules 5); read constants directly and turn CSE off (29)",
        "`mr r30,r29` where ours has `li r30,0`: the search loop is a static inline returning the pointer, so its zero init is copied from the caller's (fn_80226B20, fn_80170B5C)",
    ]),
    "address:pool": ("data is addressed through another base (pooled anchor vs one `lis/addi` per object)", [
        "target uses ONE base + offsets: the original TU owns that data section; give the TU the range in splits.txt and define the objects in order (rules 5 'Pooled base registers', 13, 40)",
        "offset reaches a neighbouring TU's data: over-split TUs, merge them (`tools/merge_tus.py plan`, 32, 9); check `tools/pool_audit.py` first",
        "every distinct N in the target's `addi rX,anchor,N` starts a real object: split symbols.txt there and name the object (40, 90); `python3 tools/leversweep.py detect`",
        "ours pools but the target does not: the objects are not defined in this TU (extern), or fewer than 3 objects of the section are touched",
    ]),
    "address:materialise": ("an address/constant is built into a register on one side only", [
        "target hoists `&local` / `&member` into a saved register: name it as a local (of the inline) (14, 52); a base local needs two uses (44)",
        "ours has the extra `addi`: write `&obj` at each use and let the compiler hoist it (90), or index the object directly instead of `base + CONST` (40)",
        "first access folded, the rest through a pointer: static object behind the section anchor (13)",
        "`addi rX,rY,0` instead of `mr` in a leaf: GC/1.2.5n (rules 4)",
        "an extra `li rN,0/1`: let the code reuse an earlier constant (selection in a static inline, fn_8020D00C; loops in a shared inline that use the initialised counter, fn_801807E0); declaration order of the zero/index locals (card_unpack_v1)",
        "extra `addi` + `mr` for a table base: file-static typed arrays referenced directly, no cached base pointer (fn_8020B234, fn_801903D0); native string literals instead of an extern message-base pointer (ClStream_UpdateAll)",
    ]),
    "address:sda": ("small-data (`r13`/`r2`) addressing on one side, `lis/addi` on the other", [
        "the object's declared size/section differs: `extern T x[]` (unknown size) is never SDA; give the real size, or declare it as an array to force `lis/addi`",
        "const data <= 8 bytes goes to .sdata2 (`r2`); check `const` and the element type; s64 split into Hi/Lo in symbols.txt (rules 5)",
    ]),
    "reloc:symbol": ("same instruction, another symbol or addend", [
        "identical bytes but the target's object is one big symbol where the source defines several (or the reverse): split/merge in symbols.txt (rules 5 'Identical instruction'); `python3 tools/reloc_only_detect.py`",
        "another float constant label: two identical constants exist, use `extern const float lbl_X` for the second (rules 5)",
        "string pool offsets: order / duplicates of string literals, count the `%d` of debug strings (49); `python3 tools/fmt_args_detect.py`",
        "pool ownership: `python3 tools/pool_audit.py` (an OTHER/UNOWNED row is an ownership bug)",
    ]),
    "reloc:callee": ("a call goes to another function", [
        "another overload / wrapper / weak inline copy: check the callee name and whether the original called a thin inline",
        "`new T(args)` instead of `Alloc(); if (p) ctor(p, args)` (43)",
    ]),
    "stack:offset": ("same instructions, other stack offsets", [
        "stack aggregates get slots in ASCENDING SIZE order, declaration order only breaks ties (rules 7.9): reorder declarations, or change a size (pad member)",
        "an extra/missing stack temp: a struct passed or returned by value, an iterator kept in a stack slot (15), `&local` taken",
        "inline locals: each inlined copy gets its own slots; block-scoped locals share",
    ]),
    "stack:frame": ("frame size differs", [
        "a local aggregate too many / too few, or another size; struct returned by value through a temp",
        "a float<->int conversion uses an 8-byte scratch slot: one cast more or less",
        "more saved registers also grow the frame: see `saved-regs`",
    ]),
    "saved-regs": ("another number of callee-saved registers", [
        "ours uses MORE: a value lives across a call that the original recomputed or kept in one variable: in-place `x = x / N` recomputed at first use -> `#pragma opt_propagation off` (55); reuse one variable for two values (26, 57)",
        "ours uses FEWER: the target keeps a named copy (76), `&local` in a saved register (14), a hoisted `&member` (52), or a separate loop counter per loop (34, 46)",
        "`_savegpr`/`_restgpr` calls vs `stmw`/`lmw`: GC/2.6 + `-use_lmw_stmw on` (rules 4)",
    ]),
    "extend": ("an extension/mask (`extsb`, `extsh`, `clrlwi`, `rlwinm`, `andi.`) on one side only", [
        "integer type of the local / parameter / return value: char vs int, signed vs unsigned (17); inline RETURN TYPE (71)",
        "a dead truncation: `(int)x` assigned to a u8 (69); narrow-cast toggle: `python3 tools/leversweep.py fn UNIT FN --levers narrow-cast-toggle`",
        "byte stores of a shifted word: write the mask, `PUT((v >> 8) & 0xFF)` (rules 7.8)",
        "a `long` index passed as `int` (49); bool vs int flag",
        "`rlwimi` vs `clrlwi; or`: bitfield insert (`x = (x & ~m) | v` / struct bitfield) vs separate mask and or; fade/colour packing expression shape (fn_801D9B70)",
    ]),
    "select:signedness": ("signed vs unsigned instruction selection", [
        "`cmpwi` vs `cmplwi`, `srawi(+addze)` vs `srwi`, `mulhw` vs `mulhwu`, `lha` vs `lhz`, `xoris 0x8000` in int->float: change the signedness of the variable / field / constant (17)",
        "enum vs int; `size_t`/`u32` loop bounds; char signedness of a struct member",
        "`cmpwi`/`cmplwi` against 0 on a flag: bool/u8 fields with explicit control flow instead of a mask select (fn_801DABFC)",
    ]),
    "select:compare": ("another compare / branch condition", [
        "`<` vs `<=` with constant +-1, `!=` vs `<` as the loop test, operands swapped (`a < b` vs `b > a`)",
        "unsigned range check `(unsigned)(x - lo) <= hi - lo` vs two compares: write the `&&` form or a switch",
        "`cror` + `beq`/`bne`: float `<=`/`>=`; negate the test to flip it",
        "a byte predicate: `== 1` gives `srwi; cmplwi; bne`, `> 0` gives `srwi.; beq` (fn_801F7198)",
    ]),
    "select:fused": ("`fmadds`/`fmsubs` on one side, `fmuls` + `fadds` on the other", [
        "target does NOT fuse where ours does: multiply through an inline helper so the product is a separate temp (39)",
        "target fuses: write it as one expression, no named product local; `-fp_contract on` is the group default",
    ]),
    "select:bool": ("a boolean is computed by arithmetic on one side and by branches on the other", [
        "`neg/or/srwi`, `cntlzw/srwi`, `subfic/adde`: `x != 0`, `!x`, `a == b` as an EXPRESSION (assigned or returned); branches + `li 0/1`: if/else or `? 1 : 0`",
        "return type bool/u8 vs int; `!!x`; a compare result stored in a variable then tested",
        "`bne; b` after a flag test: the shared `Test(...) == 1` inline with a result variable (87)",
    ]),
    "select:muldiv": ("multiply/divide/shift idiom differs", [
        "`mulli` vs `slwi`+`add`: element size / struct type of the indexed array; index type",
        "`srawi; addze` = signed `/ 2^n`; `mulhw` magic = signed `/ N`; `rlwinm` = unsigned or `>>`/`&`",
        "in-place division recomputed (extra saved register): `#pragma opt_propagation off` (55)",
    ]),
    "select:update": ("update-form load/store (`lwzu`, `stwu`, `lbzu`, `stfsu`) on one side only", [
        "pointer walk `*p++` / `*++p` vs indexed access `a[i]`: write the other one (4, 28); loop step order: bump the pointer before the count (rules 7.8)",
    ]),
    "select:indexed": ("indexed (`lwzx`/`stwx`) vs base+displacement access, or `add` per iteration vs a walker", [
        "target keeps `add rP,rBase,rOff` per iteration: the byte offset is a NAMED `int off` added in the integer domain, `(T *)((unsigned long)c + off)` (60)",
        "index the array and turn strength reduction off, `#pragma opt_strength_reduction off` (28); index access in an inline loop (77)",
        "`slwi; addi rI,rI,OFF; lhzx`: add the member offset after the index (42)",
        "target walks, ours indexes: explicit pointer walker (`p++`), required under opt_propagation off (55)",
    ]),
    "select:structcopy": ("a struct copy uses another instruction form", [
        "`lwz/stw` pairs = struct assignment `a = b`; `lfs/stfs` = member-wise float copy: write the other one",
        "`lfd/stfd` or `psq_l/psq_st` for 8 bytes: copy of an 8-byte struct (two floats / double); check the struct size and alignment",
        "the copy shape also depends on whether the source lies inside its object (90)",
    ]),
    "select:other": ("another instruction is selected (same count)", [
        "types and signedness first, then per-function pragmas (`opt_common_subs`, `opt_propagation`, `opt_strength_reduction`, `peephole`) (1), then compiler version (rules 4)",
        "`python3 tools/asmgrep.py similar UNIT FN --src` shows how matched functions wrote the same shape",
    ]),
    "loop:ctr": ("a CTR loop (`mtctr`/`bdnz`) on one side only", [
        "target has it, ours is unrolled or hand-written: write the real loop with a constant trip count (21, 62, 75); `#pragma opt_unroll_instr_count 16` / `opt_unroll_loops off`",
        "ours has it, target does not: the counter is used in the body or after the loop, the bound is not a constant, or the original is a `do {} while`; repeated statements were hand-unrolled in the original (unlikely) vs an unrolled inline copy (75)",
        "dead `b` after an early return = an unrolled 1-iteration loop (tips)",
    ]),
    "loop:shape": ("loop / branch structure differs", [
        "`for` (test at top, guard + bottom test) vs `do {} while` (no guard) vs `while (1) { if () break; }`",
        "one shared counter over several loops vs block-local counters (34, 46, 73); loop inside an inline (47, 68)",
        "early return vs `goto end` / single exit; `if (a || b == X) return;`; empty `case N: break;` (rules 7.5)",
        "a hand-expanded recursion or an already matched function's body: call the real function and let it inline (20, 25)",
        "a missing or unreachable `b`/branch in a switch: spell out the full case domain, leading with the case the target tests first (Effect_Cluster16_Update, ItemObject_Tick_Kind28); nested pointer validation inside an inline (roll2upvec, upvec2roll)",
    ]),
    "call:inline": ("a function is called on one side and inlined on the other", [
        "target calls, ours inlines: define the callee AFTER the caller, `-inline noauto` on the TU (rules 4), or `#pragma dont_inline on` around it",
        "target inlines, ours calls: the callee is a `static inline` / defined earlier in the same TU (TU boundary, `tools/tu_audit.py`); inline depth for recursion (25)",
        "part of the function is an already-matched function's body: call it and let it inline (20)",
        "`crclr 6`/`crxor 6,6,6` before `bl`: the prototype is variadic (or missing)",
    ]),
    "length:other": ("instructions without a counterpart (mixed)", [
        "read the hunk in objdiff; `python3 tools/asmgrep.py similar UNIT FN --src` for matched functions with the target's sequence",
        "then the generic list: docs/matching_rules.md section 7",
    ]),
    "imm": ("same instruction, another immediate", [
        "struct member offset / array element size (wrong struct layout or type), or a literal constant",
        "a shift/mask pair folded differently: write the mask explicitly",
    ]),
}

# --------------------------------------------------------------------------
REG = re.compile(r"^(r|f)(\d+)$")
LOADS = re.compile(r"^(l[bhw]zu?x?|lhau?x?|lf[sd]u?x?|lmw|psq_lu?x?)$")
STORES = re.compile(r"^(st[bhw]u?x?|stf[sd]u?x?|stmw|psq_stu?x?|stfiwx)$")
BRANCH = re.compile(r"^b(?!l$|la$|lrl$|ctrl$)\w*[+-]?$")
EXT = re.compile(r"^(exts[bh]|clrlwi|rlwinm|andi|extrwi|clrrwi|rotlwi)\.?$")
COMMUT = {"add", "fmuls", "fadds", "fmul", "fadd", "mullw", "and", "or", "xor", "nor", "mulhw", "mulhwu", "adde", "addc"}
SIGNED_PAIRS = [({"cmpwi"}, {"cmplwi"}), ({"cmpw"}, {"cmplw"}), ({"srawi", "addze"}, {"srwi"}), ({"srawi"}, {"srwi"}),
                ({"mulhw"}, {"mulhwu"}), ({"lha"}, {"lhz"}), ({"lhax"}, {"lhzx"}), ({"extsb"}, {"clrlwi"}),
                ({"extsh"}, {"clrlwi"}), ({"divw"}, {"divwu"}), ({"sraw"}, {"srw"}), ({"blt"}, {"bdnz"})][:-1]
BOOLARITH = {"cntlzw", "neg", "subfic", "adde", "subfe", "addic", "subic", "nor", "eqv", "xori", "addze", "subfze", "orc", "andc"}


class Ins:
    __slots__ = ("i", "addr", "mn", "ops", "reloc", "rc", "dest", "text", "key", "ckey")

    def __init__(self, i, addr, text):
        self.i, self.addr, self.text = i, addr, re.sub(r"\s+", " ", text.strip())
        parts = self.text.split(" ", 1)
        self.mn = parts[0]
        self.ops, self.reloc, self.rc, self.dest = [], None, None, None
        if len(parts) > 1:
            body = parts[1]
            m = re.search(r"\b([0-9a-f]+) <.+>\s*$", body)
            if m and (self.mn.startswith("b")):
                self.dest = int(m.group(1), 16)
                body = body[:m.start()].rstrip(", ")
            for a in [x for x in re.split(r",\s*", body) if x]:
                m = re.match(r"^(.*)\((\w+)\)$", a)
                if m:
                    self.ops += [m.group(1), "(" + (m.group(2) if m.group(2) != "0" else "0") + ")"]
                else:
                    self.ops.append(a)

    def finish(self):
        """keys, once the relocation is attached"""
        ops = list(self.ops)
        if self.reloc:
            if self.rc is None:
                self.rc = self.reloc
            typ, sym = self.rc[:2]
            tag = {"R_PPC_ADDR16_HA": "@ha", "R_PPC_ADDR16_LO": "@l", "R_PPC_ADDR16_HI": "@h",
                   "R_PPC_EMB_SDA21": "@sda", "R_PPC_REL24": "", "R_PPC_REL14": ""}.get(typ, "@" + typ)
            if self.mn in ("bl", "b") or typ in ("R_PPC_REL24",):
                ops = [sym]
            else:
                # the immediate / displacement carries the symbol
                for k, o in enumerate(ops):
                    if not o.startswith("(") and not REG.match(o) and not o.startswith("cr"):
                        ops[k] = sym + tag
                        break
                if "SDA" in typ:
                    ops = [o for o in ops if o not in ("(0)", "(r2)", "(r13)")]
        elif self.dest is not None:
            ops = [o for o in ops]  # condition register operand stays
            ops.append("fwd" if self.dest > self.addr else "back")

        def ab(o):
            p = o.strip("()")
            m = REG.match(p)
            if not m:
                return o
            if m.group(1) == "f":
                r = "F"
            elif p in ("r1", "r2", "r13"):
                r = p
            else:
                r = "R"
            return "(" + r + ")" if o.startswith("(") else r
        self.key = (self.mn.rstrip("+-"),) + tuple(ab(o) for o in ops)
        self.ckey = self.mn.rstrip("+-")

    @property
    def regs(self):
        return [o.strip("()") for o in self.ops if REG.match(o.strip("()"))]

    @property
    def base(self):
        for o in self.ops:
            if o.startswith("("):
                return o.strip("()")
        return None

    @property
    def disp(self):
        for k, o in enumerate(self.ops):
            if o.startswith("(") and k:
                return self.ops[k - 1]
        return None

    @property
    def dst(self):
        """register written (rough): first operand unless store/compare/branch"""
        if STORES.match(self.mn) or self.mn.startswith(("cmp", "fcmp", "b", "mt", "tw", "cr")) or not self.ops:
            return None
        o = self.ops[0]
        return o if REG.match(o) else None

    def show(self):
        t = self.text
        if self.reloc:
            t += f"   <{self.reloc[1]}>"
        return t


def disasm(obj):
    """{function name: [Ins]} for one object"""
    r = subprocess.run([str(OBJDUMP), "-dr", "--no-show-raw-insn", str(obj)], capture_output=True, text=True)
    fns, cur = {}, None
    for l in r.stdout.splitlines():
        m = re.match(r"^[0-9a-f]+ <(.+)>:$", l)
        if m:
            cur = fns.setdefault(m.group(1), [])
            continue
        if cur is None:
            continue
        m = re.match(r"^\s*([0-9a-f]+):\s+(R_PPC_\w+)\s+(\S+)", l)
        if m:
            if cur:
                cur[-1].reloc = (m.group(2), m.group(3))
            continue
        m = re.match(r"^\s*([0-9a-f]+):\t(.+)$", l)
        if m:
            cur.append(Ins(len(cur), int(m.group(1), 16), m.group(2)))
    return fns, symtab(obj)


def _real(name):
    return not name.startswith(("@", ".", "..."))


def _split(sym):
    m = re.match(r"^(.*?)([+-]0x[0-9a-f]+)?$", sym)
    return m.group(1), int(m.group(2), 16) if m.group(2) else 0


def unify(tseq, tst, oseq, ost):
    """Give every data relocation a token that is the same on both sides when
    it is the same object: by name when both objects name it, by position in
    the section when ours only has an anchor / `@N` there. Then build keys."""
    par = {}

    def find(a):
        par.setdefault(a, a)
        while par[a] != a:
            par[a] = par[par[a]]
            a = par[a]
        return a

    def union(a, b):
        a, b = find(a), find(b)
        if a != b:
            # keep a readable root: real names win
            if a.startswith(("T:", "O:")) and not b.startswith(("T:", "O:")):
                a, b = b, a
            par[b] = a
    onamed = {}
    for n, (sec, val) in ost.items():
        if _real(n):
            onamed.setdefault((sec, val), n)
    toks = []
    for side, seq, st in (("T", tseq, tst), ("O", oseq, ost)):
        for x in seq:
            if not x.reloc or x.reloc[0] == "R_PPC_REL24":
                continue
            name, add = _split(x.reloc[1])
            pos = None
            if name in st:
                sec, val = st[name]
                pos = (sec, val + add)
            tok = f"{name}+0x{add:x}" if add else name
            if pos:
                ptok = f"{side}:{pos[0]}+0x{pos[1]:x}"
                if _real(name):
                    union(tok, ptok)
                else:
                    tok = ptok
                if side == "O":
                    n = onamed.get(pos)
                    if n and n != name:
                        union(n, ptok)
                    # same place in the section = same object, unless ours names
                    # it with a label the target has somewhere else
                    if not (n and n in tst) and not (_real(name) and name in tst):
                        union(f"T:{pos[0]}+0x{pos[1]:x}", ptok)
            toks.append((x, tok, pos is not None))
    for x, tok, defined in toks:
        x.rc = (x.reloc[0], find(tok), defined)
    for x in tseq + oseq:
        x.finish()


def symtab(obj):
    """{symbol: (section, value)} for symbols defined in a data section"""
    r = subprocess.run([str(OBJDUMP), "-t", str(obj)], capture_output=True, text=True)
    st = {}
    for l in r.stdout.splitlines():
        m = re.match(r"^([0-9a-f]{8}) (.{7}) (\S+)\t([0-9a-f]+) (.+)$", l)
        if m and m.group(3) not in ("*UND*", "*ABS*", ".text", ".init", "*COM*"):
            st[m.group(5).strip()] = (m.group(3), int(m.group(1), 16))
    return st


_REN = None


def _renames():
    global _REN
    if _REN is None:
        _REN = {}
        try:
            # duplicate keys exist in this file: keep every pair
            data = json.loads((ROOT / "tools/extab_user_renames.json").read_text(), object_pairs_hook=lambda p: p)
            for _, tu in data:
                if isinstance(tu, list):
                    for k, v in tu:
                        if isinstance(v, str):
                            _REN.setdefault(v.replace("global:", ""), []).append(k)
        except Exception:
            pass
    return _REN


def pick_fn(fns, fn, like=None):
    """the function called `fn` in a disassembly (target name, mangled name, rename)"""
    if fn in fns:
        return fns[fn]
    for k in _renames().get(fn, []):
        if k in fns:
            return fns[k]
    c = [k for k in fns if k.startswith(fn + "__")]
    if len(c) == 1:
        return fns[c[0]]
    if like and fns:
        # closest body by mnemonic sequence (methods / ctors without a rename entry)
        A = [x.mn for x in like]

        def score(v, quick=True):
            if abs(len(v) - len(A)) > max(8, len(A) // 4):
                return 0
            m = difflib.SequenceMatcher(None, A, [x.mn for x in v], autojunk=False)
            return m.quick_ratio() if quick else m.ratio()
        best = max(fns.values(), key=score)
        if score(best, False) > 0.8:
            return best
    return None


# --------------------------------------------------------------------------
class Finding:
    def __init__(self, cls, ti, oi, note, T=(), O=(), weight=1):
        self.cls, self.ti, self.oi, self.note, self.T, self.O, self.weight = cls, ti, oi, note, list(T), list(O), weight

    def as_dict(self):
        return dict(cls=self.cls, target_index=self.ti, ours_index=self.oi, note=self.note,
                    target=[x.show() for x in self.T], ours=[x.show() for x in self.O])


def loops(seq):
    """[(head index, tail index)] from backward branches"""
    by = {x.addr: x.i for x in seq}
    out = []
    for x in seq:
        if x.dest is not None and x.dest <= x.addr and x.dest in by and x.mn not in ("bl",):
            out.append((by[x.dest], x.i))
    return out


def in_loop(lp, i):
    return any(a <= i <= b for a, b in lp)


def prev_same_load(seq, x, span=80):
    """index of an earlier identical load (same slot, base not rewritten), with
    the number of stores and calls in between; None when there is none"""
    if not LOADS.match(x.mn) or x.base is None:
        return None
    st = calls = 0
    for j in range(x.i - 1, max(-1, x.i - span), -1):
        y = seq[j]
        if y.mn == "bl":
            calls += 1
        if STORES.match(y.mn):
            st += 1
        if y.dest is not None and y.mn != "bl" and y.dest > y.addr and y.mn == "b":
            pass
        if LOADS.match(y.mn) and y.mn == x.mn and y.base == x.base and y.disp == x.disp and y.rc == x.rc \
                and (x.base in ("r1", "r2", "r13", "0") or True):
            return j, st, calls
        if y.dst and y.dst == x.base and x.base not in ("r1", "r2", "r13"):
            return None
    return None


def near_call(seq, i, span=8):
    for j in range(i, min(len(seq), i + span)):
        if seq[j].mn == "bl":
            return j
        if seq[j].dest is not None:
            return None
    return None


def is_const_load(x):
    if x.mn in ("li", "lis"):
        return True
    if x.mn in ("lfs", "lfd") and (x.base in ("r2", "r13") or (x.reloc and x.reloc[0] == "R_PPC_EMB_SDA21")):
        return True
    return False


def counter(xs):
    return collections.Counter(x.ckey for x in xs)


def fam(ms, rx):
    return bool(ms) and all(re.fullmatch(rx, m) for m in ms)


def classify_reorder(T, O, tseq):
    ks = [x.ckey for x in T]
    end = T[-1].i + 1
    tmr = [x for x in T if x.mn in ("mr", "fmr")]
    omr = [x for x in O if x.mn in ("mr", "fmr")]
    for x in tmr:
        if any(y.ops == x.ops[::-1] for y in omr) and not any(y.ops == x.ops for y in omr):
            return "copy:direction", f"target `{x.text}`, ours the reverse"
    if sorted(x.text for x in T) != sorted(x.text for x in O):
        rs = sorted({r for x in T + O for r in x.regs if r not in ("r1", "r2", "r13")})
        for a in range(len(rs)):
            for b in range(a + 1, len(rs)):
                if rs[a][0] != rs[b][0]:
                    continue
                sw = {rs[a]: rs[b], rs[b]: rs[a]}
                swp = lambda t: re.sub(r"\b[rf]\d+\b", lambda m: sw.get(m.group(0), m.group(0)), t)   # noqa: E731
                if [swp(x.text) for x in O] == [x.text for x in T]:
                    return "order:regswap", f"{rs[a]} <-> {rs[b]}"
                if sorted(swp(x.text) for x in O) == sorted(x.text for x in T) and len(T) <= 4 \
                        and all(len(set(x.regs)) == 1 for x in T):
                    return "order:regswap", f"{rs[a]} <-> {rs[b]} (or the instructions are swapped)"
    if any(x.dest is not None and x.mn != "bl" for x in T):
        return "order:blocks", "the run contains branches"
    if T[-1].i >= len(tseq) - 14 and all(x.base == "r1" and x.mn in ("lwz", "lfd", "lmw") for x in T) and any(x.ops[0] == "r0" for x in T):
        return "order:epilogue", ""
    same = sorted(x.text for x in T) == sorted(x.text for x in O)
    nload = sum(1 for k in ks if LOADS.match(k))
    nstore = sum(1 for k in ks if STORES.match(k))
    c = near_call(tseq, end - 1) if end - 1 < len(tseq) else None
    argreg = sum(1 for x in T if x.dst and re.fullmatch(r"r([3-9]|10)|f[1-8]", x.dst))
    if c is not None and nstore == 0 and argreg * 2 >= len(T):
        callee = tseq[c].reloc[1] if tseq[c].reloc else "?"
        return "order:args", f"before `bl {callee}`"
    if nstore == 0 and any(is_const_load(x) for x in T) and all(is_const_load(x) or LOADS.match(x.mn) or x.mn in ("mr", "fmr") for x in T):
        return "order:const", ""
    lm = {k for k in ks if LOADS.match(k)}
    stm = {k for k in ks if STORES.match(k)}
    if nload + nstore == len(ks) and len(ks) >= 3 and len(lm) == 1 and len(stm) == 1 and fam(lm | stm, r"lwz|stw|lfs|stfs|lbz|stb|lhz|sth"):
        return "order:copyrun", f"{nload} loads / {nstore} stores"
    if nstore:
        tl = [k for k in ks if LOADS.match(k) or STORES.match(k)]
        ol = [x.ckey for x in O if LOADS.match(x.ckey) or STORES.match(x.ckey)]
        note = ""
        if tl and ol:
            if LOADS.match(tl[0]) and STORES.match(ol[0]):
                note = "target loads BEFORE the store (no alias assumed in the target)"
            elif STORES.match(tl[0]) and LOADS.match(ol[0]):
                note = "target stores first, ours loads first"
        return "order:store", note
    why = ("registers are identical too: only the schedule differs" if same else "")
    if nload and nstore == 0 and not any(x.mn == "bl" for x in T):
        tl = [x.text.split(" ", 1)[1].split(",", 1)[1] for x in T if LOADS.match(x.mn)]
        ol = [x.text.split(" ", 1)[1].split(",", 1)[1] for x in O if LOADS.match(x.mn)]
        if tl != ol or nload < len(T):
            g = next((x for x in T if LOADS.match(x.mn) and x.reloc), None)
            return "order:load", (why + ("; " if why else "") + (f"global `{g.reloc[1]}` involved" if g else "")).strip("; ")
    if all(x.mn == "addi" and len(x.ops) == 3 and x.ops[0] == x.ops[1] for x in T):
        return "order:loopstep", why
    if nload == 0 and nstore == 0 and not any(x.mn == "bl" or x.mn in ("mr", "fmr") for x in T) and len(T) <= 8:
        return "order:expr", why
    return "order:other", ("registers are identical too: the scheduler alone differs (post-RA re-scheduling, 69: "
                           "`python3 tools/mwsched.py resched UNIT FN`)" if same else "")


def classify_delta(Tx, Ox, tseq, oseq, tlp, olp):
    """Tx: target-only instructions of a hunk, Ox: ours-only. -> [(cls, note)]"""
    tm, om = counter(Tx), counter(Ox)
    allm = set(tm) | set(om)
    res = []
    if not allm:
        return res
    if fam(allm, r"f?mr"):
        if Tx and not Ox:
            x = Tx[0]
            prev = tseq[x.i - 1] if x.i else None
            note = ""
            if prev is not None and prev.dest is not None and prev.mn != "bl":
                note = "right after a conditional branch: section 76 shape"
            elif prev is not None and prev.mn in ("li", "lfs", "lis"):
                note = f"after `{prev.mn}`: section 67/79 shape"
            return [("copy:target-extra", note)]
        if Ox and not Tx:
            return [("copy:ours-extra", "")]
        return [("copy:target-extra", "both sides have unmatched copies")]
    if {"fmadds", "fmsubs", "fnmsubs", "fnmadds", "fmadd", "fmsub"} & allm and fam(allm, r"fn?m(add|sub)s?|fmuls?|f(add|sub)s?|fmr|fneg"):
        side = "target fuses, ours does not" if any(k.startswith(("fmadd", "fmsub", "fnm")) for k in tm) else "ours fuses, the target does not"
        return [("select:fused", side)]
    if {"mtctr", "bdnz"} & allm and not ("mtctr" in tm and "mtctr" in om):
        side = "target has the CTR loop" if {"mtctr", "bdnz"} & set(tm) else "ours has the CTR loop"
        res.append(("loop:ctr", side))
        return res
    if "bl" in allm:
        tc = [x.reloc[1] for x in Tx if x.mn == "bl" and x.reloc]
        oc = [x.reloc[1] for x in Ox if x.mn == "bl" and x.reloc]
        if any(re.match(r"_(save|rest)[gf]pr", c) for c in tc + oc):
            return []          # reported once at function level (saved-regs)
        if tc and not oc:
            res.append(("call:inline", "target calls " + ", ".join(sorted(set(tc))) + " here, ours does not (inlined or missing)"))
        elif oc and not tc:
            res.append(("call:inline", "ours calls " + ", ".join(sorted(set(oc))) + " here, the target does not (it inlines it)"))
        else:
            res.append(("reloc:callee", f"target {sorted(set(tc))} / ours {sorted(set(oc))}"))
        return res
    if fam(allm, EXT.pattern.strip("^$") + r"|f?mr"):
        side = "target has " + " ".join(sorted(tm)) if tm else "ours has " + " ".join(sorted(om))
        return [("extend", side + ("" if not (tm and om) else " / ours has " + " ".join(sorted(om))))]
    for a, b in SIGNED_PAIRS:
        if (a <= set(tm) and b <= set(om)) or (b <= set(tm) and a <= set(om)):
            if fam(allm - a - b, r"f?mr|li|addi") or not (allm - a - b):
                return [("select:signedness", f"target {' '.join(sorted(tm))} / ours {' '.join(sorted(om))}")]
    upd = {k for k in allm if re.fullmatch(r"(l[bhw]zu|lhau|lf[sd]u|st[bhw]u|stf[sd]u)x?", k)}
    if upd and not (upd & set(tm) and upd & set(om)):
        if not any(x.ckey in upd and x.base == "r1" for x in Tx + Ox):
            return [("select:update", ("target" if upd & set(tm) else "ours") + " uses " + " ".join(sorted(upd)))]
    idx = {k for k in allm if re.fullmatch(r"(l[bhw]z|lha|lf[sd]|st[bhw]|stf[sd])x", k)}
    if idx and not (idx & set(tm) and idx & set(om)):
        return [("select:indexed", ("target" if idx & set(tm) else "ours") + " uses " + " ".join(sorted(idx)))]
    # struct copy form
    tw, ow = {"lwz", "stw"} <= set(tm), {"lwz", "stw"} <= set(om)
    tf = bool({"lfs", "lfd", "psq_l"} & set(tm)) and bool({"stfs", "stfd", "psq_st"} & set(tm))
    of = bool({"lfs", "lfd", "psq_l"} & set(om)) and bool({"stfs", "stfd", "psq_st"} & set(om))
    if (tw and of and not ow) or (ow and tf and not tw) or ({"psq_l", "psq_st", "lfd", "stfd"} & allm and (tf != of or tw != ow)):
        return [("select:structcopy", f"target {' '.join(sorted(tm))} / ours {' '.join(sorted(om))}")]
    if (LOADS.match("lfs") and (("lfs" in tm and "fmr" in om) or ("fmr" in tm and "lfs" in om) or
                                ("li" in tm and "mr" in om) or ("mr" in tm and "li" in om))) and fam(allm, r"lfs|lfd|f?mr|li"):
        return [("load:const-vs-copy", f"target {' '.join(sorted(tm))} / ours {' '.join(sorted(om))}")]
    # loads
    if fam(allm, r"l[bhw]zu?x?|lhax?|lf[sd]x?|f?mr|addi?|lis|st[bhw]x?|stf[sd]x?"):
        tl = [x for x in Tx if LOADS.match(x.mn)]
        ol = [x for x in Ox if LOADS.match(x.mn)]
        if tl or ol:
            for side, xs, seq, cls in (("target", tl, tseq, "load:target-reloads"), ("ours", ol, oseq, "load:ours-reloads")):
                hits = [(x, prev_same_load(seq, x)) for x in xs]
                hits = [(x, p) for x, p in hits if p]
                if hits and len(hits) * 2 >= len(xs):
                    x, (j, st, calls) = hits[0]
                    slot = "stack slot" if x.base == "r1" else "memory"
                    note = (f"{len(hits)} reload(s); `{x.text}` was already loaded {x.i - j} insns earlier "
                            f"({st} stores, {calls} calls in between; {slot})")
                    if x.base == "r1" and x.mn.startswith("lf") and side == "target" and not calls:
                        note += "; stack float loaded twice: section 87 shape"
                    res.append((cls, note))
            if res:
                return res
            if len(tl) != len(ol):
                cls = "load:target-reloads" if len(tl) > len(ol) else "load:ours-reloads"
                return [(cls, f"target {' '.join(f'{k}x{v}' for k, v in sorted(tm.items())) or '-'} / ours "
                              f"{' '.join(f'{k}x{v}' for k, v in sorted(om.items())) or '-'} (no identical earlier load found: may be a different value)")]
    if fam(allm, r"lis|addis?|add|li|f?mr|subi|ori|oris"):
        tl, ol = tm.get("lis", 0), om.get("lis", 0)
        if tl != ol:
            return [("address:pool", f"target has {tl} `lis` here, ours {ol}: " +
                     ("the target reaches the data from a base it already holds" if tl < ol else "ours reuses a base, the target builds the address again"))]
        if "add" in allm and (in_loop(tlp, Tx[0].i) if Tx else in_loop(olp, Ox[0].i)):
            return [("select:indexed", ("target" if "add" in tm else "ours") + " has an `add` inside a loop (base + offset per iteration vs a walker): section 60 shape")]
        side = "target has " + " ".join(f"{k}x{v}" for k, v in sorted(tm.items())) if tm else ""
        side += (" / " if tm and om else "") + ("ours has " + " ".join(f"{k}x{v}" for k, v in sorted(om.items())) if om else "")
        return [("address:materialise", side)]
    if any(k.endswith(".") for k in allm) and any(k.startswith("cmp") for k in allm) and len(allm) <= 6 \
            and fam(allm, r"\w+\.|cmp\w+|b\w+|srwi|slwi|rlwinm|andi|extrwi|clrlwi|f?mr"):
        return [("select:compare", f"record form vs explicit compare: target {' '.join(sorted(tm)) or '-'} / ours {' '.join(sorted(om)) or '-'}")]
    if BOOLARITH & allm and any(re.fullmatch(r"b\w+|cmp\w+|li", k) for k in allm):
        ta = bool(BOOLARITH & set(tm))
        return [("select:bool", ("target" if ta else "ours") + " computes the flag with arithmetic (" +
                 " ".join(sorted((BOOLARITH & set(tm)) if ta else (BOOLARITH & set(om)))) + "), the other side branches")]
    if fam(allm, r"b\w*[+-]?|cmp\w*|fcmp\w|f?mr|li|cror|crnor|creqv|crxor|addic\.?|subic\.?"):
        return [("loop:shape", f"target {' '.join(f'{k}x{v}' for k, v in sorted(tm.items())) or '-'} / ours "
                               f"{' '.join(f'{k}x{v}' for k, v in sorted(om.items())) or '-'}")]
    if {"mulli", "slwi", "mullw", "srawi", "addze", "mulhw", "mulhwu", "divw", "divwu", "srwi"} & allm and \
            fam(allm, r"mulli|slwi|mullw|srawi|addze|mulhwu?|divwu?|srwi|add|subf|f?mr|rlwinm|li|lis|addi"):
        return [("select:muldiv", f"target {' '.join(sorted(tm)) or '-'} / ours {' '.join(sorted(om)) or '-'}")]
    if EXT.pattern and any(EXT.match(k) for k in allm) and len(allm) <= 3:
        return [("extend", f"target {' '.join(sorted(tm)) or '-'} / ours {' '.join(sorted(om)) or '-'}")]
    return [("length:other" if len(Tx) != len(Ox) else "select:other",
             f"target {' '.join(f'{k}x{v}' for k, v in sorted(tm.items())) or '-'} / ours "
             f"{' '.join(f'{k}x{v}' for k, v in sorted(om.items())) or '-'}")]


def classify_pair(t, o, tseq, oseq):
    """1:1 pair inside a hunk (same mnemonic class position). -> (cls, note) or None"""
    if t.ckey == o.ckey:
        if t.mn in ("bl",) and t.reloc != o.reloc:
            return "reloc:callee", f"target `{t.reloc[1] if t.reloc else '?'}` / ours `{o.reloc[1] if o.reloc else '?'}`"
        if t.dest is not None and o.dest is not None:
            return "order:blocks", "branch direction differs"
        if (t.reloc is None) != (o.reloc is None) or (t.reloc and o.reloc and t.reloc[0] != o.reloc[0]):
            a, b = (t.reloc or ("none",))[0], (o.reloc or ("none",))[0]
            if "SDA21" in a + b:
                return "address:sda", f"target {a} / ours {b}"
            return "reloc:symbol", f"target {a} / ours {b}"
        if t.rc and o.rc and t.rc[1] != o.rc[1]:
            if len(t.rc) > 2 and not t.rc[2] and o.rc[1].startswith(("O:", "T:")):
                return None      # ours owns anonymous data the target object only references: cannot compare here
            return "reloc:symbol", f"target `{t.reloc[1]}` / ours `{o.reloc[1]}`"
        if "r1" in (t.base, o.base) or (t.mn == "addi" and len(t.ops) > 1 and t.ops[1] == "r1"):
            if t.mn == "stwu" and t.base == "r1":
                return "stack:frame", f"target `{t.text}` / ours `{o.text}`"
            return "stack:offset", ""
        if t.mn in ("stmw", "lmw"):
            return "saved-regs", f"target `{t.text}` / ours `{o.text}`"
        return "imm", f"target `{t.text}` / ours `{o.text}`"
    tm, om = {t.ckey}, {o.ckey}
    for a, b in SIGNED_PAIRS:
        if (tm <= a and om <= b) or (tm <= b and om <= a):
            return "select:signedness", f"target `{t.mn}` / ours `{o.mn}`"
    if {t.ckey, o.ckey} in ({"li", "mr"}, {"lfs", "fmr"}, {"lfd", "fmr"}):
        return "load:const-vs-copy", f"target `{t.text}` / ours `{o.text}`"
    if {t.ckey, o.ckey} == {"addi", "mr"}:
        return "address:materialise", f"target `{t.text}` / ours `{o.text}`"
    if BRANCH.match(t.mn) and BRANCH.match(o.mn):
        return "select:compare", f"target `{t.mn}` / ours `{o.mn}`"
    if t.ckey.startswith("cmp") and o.ckey.startswith("cmp"):
        return "select:compare", f"target `{t.text}` / ours `{o.text}`"
    if LOADS.match(t.mn) and LOADS.match(o.mn) or STORES.match(t.mn) and STORES.match(o.mn):
        if t.mn.rstrip("x") == o.mn.rstrip("x"):
            return "select:indexed", f"target `{t.mn}` / ours `{o.mn}`"
        if t.mn.replace("u", "") == o.mn.replace("u", "") and t.mn != o.mn:
            return "select:update", f"target `{t.mn}` / ours `{o.mn}`"
        return "select:signedness" if {t.mn, o.mn} in ({"lha", "lhz"},) else "select:other", \
            f"access width/type: target `{t.mn}` / ours `{o.mn}` (field or variable type)"
    if EXT.match(t.mn) and EXT.match(o.mn):
        return "extend", f"target `{t.text}` / ours `{o.text}`"
    return None


def frame_facts(seq):
    f = dict(frame=None, gpr=0, fpr=0, savegpr=False)
    for x in seq[:24]:
        if x.mn == "stwu" and x.base == "r1" and f["frame"] is None:
            try:
                f["frame"] = -int(x.disp, 0)
            except (TypeError, ValueError):
                pass
        elif x.mn == "stmw":
            f["gpr"] = max(f["gpr"], 32 - int(x.ops[0][1:]))
        elif x.mn == "stw" and x.base == "r1" and REG.match(x.ops[0]) and int(x.ops[0][1:]) >= 14:
            f["gpr"] += 1
        elif x.mn == "stfd" and x.base == "r1" and int(x.ops[0][1:]) >= 14:
            f["fpr"] += 1
        elif x.mn == "bl" and x.reloc and "savegpr" in x.reloc[1]:
            f["savegpr"] = True
            m = re.search(r"_(\d+)$", x.reloc[1])
            if m:
                f["gpr"] = 32 - int(m.group(1))
    return f


def merge_moves(ops, tseq, oseq, span=48):
    """difflib reports a moved instruction as delete + equal + insert. Join such
    neighbours into one `replace` when the joined region holds the same keys on
    both sides (a reordering), so it is classified as one."""
    out, k = [], 0
    while k < len(ops):
        tag, i1, i2, j1, j2 = ops[k]
        if tag == "equal":
            out.append(ops[k])
            k += 1
            continue
        best = None
        for e in range(k + 1, min(len(ops), k + 9)):
            ei2, ej2 = ops[e][2], ops[e][4]
            if ei2 - i1 > span or ej2 - j1 > span:
                break
            if ops[e][0] == "equal":
                continue
            if ei2 - i1 == ej2 - j1 and sorted(x.key for x in tseq[i1:ei2]) == sorted(x.key for x in oseq[j1:ej2]):
                best = e
                break
        if best is None:
            out.append(ops[k])
            k += 1
        else:
            out.append(("replace", i1, ops[best][2], j1, ops[best][4]))
            k = best + 1
    return out


def analyse(tseq, oseq):
    """-> dict(findings=[Finding], reg_lines=int, n_target, n_ours, hunks=int)"""
    F = []
    tlp, olp = loops(tseq), loops(oseq)
    sm = difflib.SequenceMatcher(None, [x.key for x in tseq], [x.key for x in oseq], autojunk=False)
    reg_lines = hunks = 0
    for tag, i1, i2, j1, j2 in merge_moves(sm.get_opcodes(), tseq, oseq):
        T, O = tseq[i1:i2], oseq[j1:j2]
        if tag == "equal":
            for t, o in zip(T, O):
                if t.regs != o.regs:
                    reg_lines += 1
                    if t.mn in COMMUT and len(t.ops) == 3 and t.ops[1] == o.ops[2] and t.ops[2] == o.ops[1] and t.ops[1] != t.ops[2]:
                        F.append(Finding("operand-order", t.i, o.i, "", [t], [o]))
            continue
        hunks += 1
        if T and O and len(T) == len(O) and sorted(x.key for x in T) == sorted(x.key for x in O):
            cls, note = classify_reorder(T, O, tseq)
            F.append(Finding(cls, i1, j1, note, T, O, weight=len(T)))
            continue
        # a moved block: the same keys reappear as an insert elsewhere -> handled as plain deltas below
        s2 = difflib.SequenceMatcher(None, [x.ckey for x in T], [x.ckey for x in O], autojunk=False)
        Tx, Ox = [], []
        for tag2, a1, a2, b1, b2 in s2.get_opcodes():
            if tag2 == "equal":
                for t, o in zip(T[a1:a2], O[b1:b2]):
                    r = classify_pair(t, o, tseq, oseq)
                    if r:
                        F.append(Finding(r[0], t.i, o.i, r[1], [t], [o]))
            elif tag2 == "replace" and a2 - a1 == b2 - b1:
                for t, o in zip(T[a1:a2], O[b1:b2]):
                    r = classify_pair(t, o, tseq, oseq)
                    if r:
                        F.append(Finding(r[0], t.i, o.i, r[1], [t], [o]))
                    else:
                        Tx.append(t)
                        Ox.append(o)
            else:
                Tx += T[a1:a2]
                Ox += O[b1:b2]
        if Tx or Ox:
            # same mnemonic multiset left over = a reordering mixed with operand changes
            if Tx and Ox and sorted(x.ckey for x in Tx) == sorted(x.ckey for x in Ox) and len(Tx) >= 2:
                cls, note = classify_reorder(Tx, Ox, tseq)
                F.append(Finding(cls, i1, j1, (note + "; " if note else "") + "operands differ as well", T, O, weight=len(Tx)))
            else:
                for cls, note in classify_delta(Tx, Ox, tseq, oseq, tlp, olp):
                    F.append(Finding(cls, i1, j1, note, T, O, weight=max(len(Tx), len(Ox))))
    # moved code: a target-only run that is an ours-only run elsewhere
    # function-level facts
    tf, of = frame_facts(tseq), frame_facts(oseq)
    if tf["gpr"] != of["gpr"] or tf["fpr"] != of["fpr"] or tf["savegpr"] != of["savegpr"]:
        note = f"target saves {tf['gpr']} GPR / {tf['fpr']} FPR, ours {of['gpr']} / {of['fpr']}"
        if tf["savegpr"] != of["savegpr"]:
            note += "; one side calls _savegpr, the other uses stmw/stw"
        F.append(Finding("saved-regs", 0, 0, note, weight=3))
    if tf["frame"] != of["frame"] and tf["gpr"] == of["gpr"] and tf["fpr"] == of["fpr"]:
        if not any(f.cls == "stack:frame" for f in F):
            F.append(Finding("stack:frame", 0, 0, f"target frame {tf['frame']}, ours {of['frame']}", weight=2))
    elif tf["frame"] != of["frame"]:
        F[:] = [f for f in F if f.cls != "stack:frame"]
    # stack offsets that only follow from a frame/saved-register change are noise
    if any(f.cls in ("saved-regs", "stack:frame") for f in F):
        n = sum(1 for f in F if f.cls == "stack:offset")
        if n:
            F[:] = [f for f in F if f.cls != "stack:offset"]
            F.append(Finding("stack:offset", 0, 0, f"{n} stack offsets differ, probably only because the frame differs: fix that first", weight=0))
    # instructions that only moved further than the alignment window: one finding
    lo = [f for f in F if f.cls == "length:other"]
    if len(lo) >= 2:
        tm = collections.Counter(x.key for f in lo for x in f.T)
        om = collections.Counter(x.key for f in lo for x in f.O)
        if tm == om:
            F[:] = [f for f in F if f.cls != "length:other"]
            F.append(Finding("order:other", lo[0].ti, lo[0].oi,
                             f"{sum(tm.values())} instructions sit at another place (moved further than a local reordering)",
                             lo[0].T, lo[0].O, weight=sum(tm.values())))
    tcalls = collections.Counter(x.reloc[1] for x in tseq if x.mn == "bl" and x.reloc)
    ocalls = collections.Counter(x.reloc[1] for x in oseq if x.mn == "bl" and x.reloc)
    for c in (tcalls, ocalls):
        for k in [k for k in c if re.match(r"_(save|rest)[gf]pr", k)]:
            del c[k]
    if tf["savegpr"] != of["savegpr"]:
        F[:] = [f for f in F if not (f.cls == "length:other" and all(x.mn in ("lmw", "stmw", "addi") for x in f.T + f.O))]
    if tcalls != ocalls and not any(f.cls in ("call:inline", "reloc:callee") for f in F):
        d1, d2 = tcalls - ocalls, ocalls - tcalls
        F.append(Finding("call:inline", 0, 0, f"call counts differ: target-only {dict(d1)} / ours-only {dict(d2)}", weight=2))
    net = collections.Counter(x.ckey for x in tseq)
    net.subtract(collections.Counter(x.ckey for x in oseq))
    net = {k: v for k, v in net.items() if v}
    return dict(findings=F, reg_lines=reg_lines, n_target=len(tseq), n_ours=len(oseq), hunks=hunks, net=net)


def summarise(res):
    """[(cls, total weight, [Finding])] most important first"""
    by = collections.OrderedDict()
    for f in res["findings"]:
        by.setdefault(f.cls, []).append(f)
    # structural classes first: they usually cause the others
    prio = ["saved-regs", "call:inline", "loop:ctr", "loop:shape", "address:pool", "address:sda", "stack:frame",
            "select:structcopy", "select:fused", "select:bool", "select:indexed", "select:update", "select:muldiv",
            "select:signedness", "extend", "load:target-reloads", "load:ours-reloads", "copy:target-extra",
            "copy:ours-extra", "load:const-vs-copy", "address:materialise", "select:compare", "order:blocks",
            "copy:direction", "order:copyrun", "order:args", "order:const", "order:store", "order:load", "order:expr", "order:loopstep", "order:regswap", "order:epilogue", "order:other", "operand-order",
            "reloc:callee", "reloc:symbol", "imm", "stack:offset", "select:other", "length:other"]
    rows = [(c, sum(f.weight for f in fs), fs) for c, fs in by.items()]
    rows.sort(key=lambda r: prio.index(r[0]) if r[0] in prio else 99)
    return rows


def render(fn, res, verbose=False, maxex=3, out=print):
    F = res["findings"]
    out(f"== shapediag {fn}: {res['n_ours']} insns ours / {res['n_target']} target, {res['hunks']} differing run(s), "
        f"{res['reg_lines']} aligned line(s) differ in registers only ==")
    if res.get("net"):
        out("  opcode counts, target minus ours: " + " ".join(f"{k}{v:+d}" for k, v in sorted(res["net"].items())))
    if not F:
        if res["reg_lines"]:
            out("  the instruction sequence is the same: this is a register-only diff (regfix diag explains those)")
        else:
            out("  no difference in .text instructions (check relocations/data: tools/reloc_only_detect.py)")
        return
    for cls, w, fs in summarise(res):
        title, levers = CLASSES.get(cls, (cls, []))
        out(f"\n[{cls}] {title}  ({len(fs)} place(s))")
        for f in fs[: (len(fs) if verbose else maxex)]:
            where = f"target +0x{f.T[0].addr:x}" if f.T else (f"ours +0x{f.O[0].addr:x}" if f.O else "function")
            out(f"  at {where}" + (f": {f.note}" if f.note else ""))
            lim = 12 if verbose else 6
            if f.T or f.O:
                for x in f.T[:lim]:
                    out(f"      target  {x.show()}")
                if len(f.T) > lim:
                    out(f"      target  ... {len(f.T) - lim} more")
                for x in f.O[:lim]:
                    out(f"      ours    {x.show()}")
                if len(f.O) > lim:
                    out(f"      ours    ... {len(f.O) - lim} more")
        if len(fs) > maxex and not verbose:
            out(f"  ... {len(fs) - maxex} more place(s) (-v)")
        for l in levers:
            out(f"  try: {l}")
    if res["reg_lines"]:
        out(f"\n  {res['reg_lines']} more line(s) differ only in registers; fix the classes above first, "
            f"then `python3 tools/regfix.py diag` applies")


def run_objs(tgt_obj, ours_obj, fn, ours_fn=None):
    (tf, tst), (of, ost) = disasm(tgt_obj), disasm(ours_obj)
    return run_fns(tf, tst, of, ost, fn, ours_fn, tgt_obj, ours_obj)


def run_fns(tf, tst, of, ost, fn, ours_fn=None, tgt_obj="target", ours_obj="ours"):
    t = pick_fn(tf, fn)
    if t is None:
        return None, f"{fn} not found in {tgt_obj}"
    o = of.get(ours_fn) if ours_fn else pick_fn(of, fn, like=t)
    if o is None:
        return None, f"{fn} not found in {ours_obj}"
    unify(t, tst, o, ost)
    return analyse(t, o), None


def report(tgt_obj, ours_obj, fn, ours_fn=None, verbose=False, out=print):
    """entry point for regfix diag: print the diagnosis, return the result dict (or None)"""
    res, err = run_objs(tgt_obj, ours_obj, fn, ours_fn)
    if err:
        out(f"== shapediag: {err} ==")
        return None
    render(fn, res, verbose=verbose, out=out)
    return res


def unit_paths(unit):
    u = unit.split("/", 1)[1] if unit.startswith("main/") else unit
    return ROOT / f"build/{VERSION}/obj/{u}.o", ROOT / f"build/{VERSION}/src/{u}.o"


# --------------------------------------------------------------------------
def cmd_batch(a):
    rep = json.load(open(ROOT / f"build/{VERSION}/report.json"))
    rows = []
    cache = {}
    for u in rep["units"]:
        for f in u.get("functions", []):
            p = float(f.get("fuzzy_match_percent", 0))
            if p >= 100 or p < a.min:
                continue
            tgt, ours = unit_paths(u["name"])
            if not tgt.exists() or not ours.exists():
                continue
            for o in (tgt, ours):
                if o not in cache:
                    cache[o] = disasm(o)
            res, err = run_fns(*cache[tgt], *cache[ours], f["name"])
            if err:
                rows.append(dict(unit=u["name"], fn=f["name"], pct=p, error="not found"))
                continue
            rows.append(dict(unit=u["name"], fn=f["name"], pct=p, n_target=res["n_target"], n_ours=res["n_ours"],
                             reg_lines=res["reg_lines"],
                             classes=[(c, len(fs), next((x.note for x in fs if x.note), "")) for c, w, fs in summarise(res)]))
    rows.sort(key=lambda r: -r["pct"])
    cnt = collections.Counter()
    for r in rows:
        for c, n, _ in r.get("classes", []):
            cnt[c] += 1
    regonly = [r for r in rows if not r.get("classes") and not r.get("error")]
    L = ["# shapediag census: what kind of diff every non-matching function has", "",
         f"Generated by `python3 tools/shapediag.py batch --md docs/reports/shapediag_census.md` "
         f"({len(rows)} functions below 100%). One function can be in several classes.",
         "Class meanings and levers: `python3 tools/shapediag.py classes`; details per function: "
         "`python3 tools/shapediag.py fn UNIT FN`.", "",
         "| class | functions | meaning |", "|---|---|---|"]
    for c, n in cnt.most_common():
        L.append(f"| {c} | {n} | {CLASSES.get(c, (c,))[0]} |")
    L.append(f"| (register-only) | {len(regonly)} | same instruction sequence: `regfix diag` |")
    L += ["", "| % | unit | fn | insns t/o | reg lines | classes (places) | first note |", "|---|---|---|---|---|---|---|"]
    for r in rows:
        if r.get("error"):
            L.append(f"| {r['pct']:.2f} | {r['unit'].replace('main/', '')} | `{r['fn']}` | | | error: {r['error']} | |")
            continue
        cl = ", ".join(f"{c} ({n})" for c, n, _ in r["classes"]) or "register-only"
        note = next((f"{c}: {nt}" for c, n, nt in r["classes"] if nt), "")
        note = note.replace("|", "\\|")
        if len(note) > 160:
            note = note[:157] + "..."
        L.append(f"| {r['pct']:.2f} | {r['unit'].replace('main/', '')} | `{r['fn']}` | {r['n_target']}/{r['n_ours']} | "
                 f"{r['reg_lines']} | {cl} | {note} |")
    text = "\n".join(L) + "\n"
    if a.md:
        Path(a.md).write_text(text)
    if a.json:
        Path(a.json).write_text(json.dumps(rows, indent=1))
    for c, n in cnt.most_common():
        print(f"{n:4d} {c}")
    print(f"{len(regonly):4d} (register-only)")
    print(f"{len(rows)} functions")


# --------------------------------------------------------------------------
# replay: functions that a known lever solved, rebuilt from the source just
# before the fix. (commit of the fix, function, classes of which one must fire,
# regalloc_patterns section or rule).
REPLAY = [
    ("bb1c347d", "SwitchTest_Page", ["saved-regs"], "55 in-place division, opt_propagation off"),
    ("72a7a0be", "ItemObject_Tick_Kind29_LightAttachment", ["select:indexed"], "60 named int offset"),
    ("683d7049", "fn_801E9E74", ["order:regswap"], "63 two loop-long FPRs"),
    ("f8ddff04", "GabyouItem_Tick_HeldAndHoming_2Eto31", ["copy:target-extra", "copy:direction"], "76 copy of a CSE temp in a branch"),
    ("be6dc44c", "fn_8023A148", ["loop:ctr", "load:target-reloads"], "21 unrolled store run -> loop"),
    ("fa1d62e0", "fn_8019EB9C", ["order:store", "load:ours-reloads"], "30 __restrict"),
    ("0cc21dbf", "RankLog_OnMatchEnd", ["order:store", "order:load"], "rules 7.8 __restrict"),
    ("298b2043", "fn_80219538", ["operand-order"], "64 fmuls operand order"),
    ("3bf2c6aa", "CalcEarnedCoins", ["operand-order", "order:expr"], "84 three-term index sum"),
    ("f181244f", "fn_801BDB60", ["operand-order", "select:indexed", "order:other"], "42 offset after index"),
    ("e49afc3c", "FlashFadeOverlay_Draw", ["order:const", "load:const-vs-copy", "reloc:symbol"], "12 float literals"),
    ("42b56e76", "AI_CalcGPTargetSpeed", ["copy:target-extra", "order:args", "order:other"], "rules 7.8 assign in call"),
    ("fdae2b8b", "CollisionFile_Load", ["order:loopstep"], "rules 7.8 loop step order"),
    ("dd116647", "VoiceSystem_Init", ["address:materialise", "address:pool", "order:other"], "40 / 69"),
    ("2ce9db9b", "KartMovement_RotateByYaw", ["load:target-reloads", "load:ours-reloads", "order:store"], "vector via input copy"),
    ("99318d87", "PtrVec_InsertFill", ["order:other", "order:store"], "23 compute before declaring"),
    ("40145c56", "fn_8021C070", ["select:bool", "extend", "loop:shape"], "94 bool parameters"),
    ("dae93cc1", "DetermineTitle", ["reloc:symbol", "order:args", "imm", "copy:target-extra"], "49 long index / printf args"),
]


def _cmd_for(unit_obj):
    r = subprocess.run(["ninja", "-t", "commands", f"build/{VERSION}/src/{unit_obj}.o"], capture_output=True, text=True, cwd=ROOT)
    lines = [l for l in r.stdout.strip().splitlines() if "mwcceppc" in l]
    return lines[-1].split(" && ")[0].replace(" -MMD", "") if lines else None


def replay_one(commit, fn, tmp):
    """-> (result dict | None, message)"""
    r = subprocess.run(["git", "show", "--name-only", "--format=", commit], capture_output=True, text=True, cwd=ROOT)
    paths = [p for p in r.stdout.split() if p.startswith("src/") and p.endswith((".c", ".cpp", ".cp"))]
    old = None
    for p in paths:
        t = subprocess.run(["git", "show", f"{commit}^:{p}"], capture_output=True, cwd=ROOT)
        if t.returncode == 0 and fn.encode() in t.stdout:
            old = (p, t.stdout)
            break
    if not old:
        return None, "no earlier source with this function in the fix commit"
    path, text = old
    rep = json.load(open(ROOT / f"build/{VERSION}/report.json"))
    owner = next((u["name"] for u in rep["units"] for f in u.get("functions", []) if f["name"] == fn), None)
    if not owner:
        return None, "function not in report.json"
    owner = owner.split("/", 1)[1]
    cmd = _cmd_for(os.path.splitext(path)[0][4:]) or _cmd_for(owner)
    if not cmd:
        return None, "no compile command"
    ext = os.path.splitext(path)[1]
    src = ROOT / os.path.dirname(path) / f"zz_shapediag_replay_{os.getpid()}{ext}"
    src.write_bytes(text)
    try:
        c = re.sub(r"-c \S+ -o \S+", lambda _: f"-c {src.relative_to(ROOT)} -o {tmp}", cmd)
        cp = subprocess.run(c, shell=True, capture_output=True, text=True, cwd=ROOT)
    finally:
        src.unlink(missing_ok=True)
    obj = Path(tmp) / (src.stem + ".o")
    if not obj.exists():
        return None, "old source does not compile with today's headers: " + (cp.stdout + cp.stderr).strip()[:160].replace("\n", " ")
    res, err = run_objs(ROOT / f"build/{VERSION}/obj/{owner}.o", obj, fn)
    obj.unlink(missing_ok=True)
    return res, err or ""


def compile_alt(unit, src_file, tmp):
    """compile SRC_FILE with UNIT's command (no postprocess steps) -> object path"""
    u = unit.split("/", 1)[1] if unit.startswith("main/") else unit
    cmd = _cmd_for(u)
    if not cmd:
        raise SystemExit(f"no compile command for {u}")
    orig = re.search(r"-c (\S+) -o", cmd).group(1).replace("\\", "/")
    ext = os.path.splitext(orig)[1]
    src = ROOT / os.path.dirname(orig) / f"zz_shapediag_alt_{os.getpid()}{ext}"
    src.write_bytes(Path(src_file).read_bytes())
    try:
        c = re.sub(r"-c \S+ -o \S+", lambda _: f"-c {src.relative_to(ROOT)} -o {tmp}", cmd)
        cp = subprocess.run(c, shell=True, capture_output=True, text=True, cwd=ROOT)
    finally:
        src.unlink(missing_ok=True)
    obj = Path(tmp) / (src.stem + ".o")
    if not obj.exists():
        raise SystemExit("compile failed:\n" + (cp.stdout + cp.stderr)[:2000])
    return obj


def cmd_replay(a):
    import tempfile
    tmp = tempfile.mkdtemp(prefix="shapediag_")
    ok = n = 0
    for commit, fn, want, what in REPLAY:
        if a.only and a.only not in fn:
            continue
        res, msg = replay_one(commit, fn, tmp)
        if res is None:
            print(f"skip {fn} ({commit}, {what}): {msg}")
            continue
        # the replay object skips the postprocess renames, so symbol names are not comparable
        got = [c for c, _, _ in summarise(res) if not c.startswith("reloc:")]
        n += 1
        hit = [c for c in got if c in want]
        ok += bool(hit)
        state = "HIT " if hit else ("reg " if not got else "MISS")
        print(f"{state} {fn} ({commit}, {what}): {res['n_target']}/{res['n_ours']} insns, reg lines {res['reg_lines']}, classes {got}")
        if a.verbose:
            render(fn, res)
    print(f"replay: {ok}/{n} fire an expected class")


def _mk(lines):
    """test helper: instructions from text lines; `text | RELOC sym` attaches a relocation"""
    seq = []
    for k, l in enumerate(lines):
        t, _, r = l.partition("|")
        x = Ins(k, k * 4, t.strip().replace(" ", "\t", 1))
        if r.strip():
            x.reloc = tuple(r.split())
        seq.append(x)
    for x in seq:
        x.finish()
    return seq


SELFTESTS = [
    # (name, expected class, target, ours)
    ("76 copy inside a branch", "copy:target-extra",
     ["lwz r3,772(r3)", "lwz r28,8(r3)", "cmplwi r28,0", "beq 40 <f+0x40>", "mr r27,r3", "bl 14 <f+0x14> | R_PPC_REL24 g"],
     ["lwz r3,772(r3)", "lwz r28,8(r3)", "cmplwi r28,0", "beq 40 <f+0x40>", "bl 10 <f+0x10> | R_PPC_REL24 g"]),
    ("87 stack vector loaded twice", "load:target-reloads",
     ["lfs f1,8(r1)", "lfs f0,12(r1)", "fmuls f1,f1,f3", "fmuls f0,f0,f4", "lfs f13,8(r1)", "lfs f11,12(r1)", "fmuls f13,f13,f5", "fmuls f11,f11,f5"],
     ["lfs f1,8(r1)", "lfs f0,12(r1)", "fmuls f2,f1,f3", "fmuls f6,f0,f4", "fmuls f13,f1,f5", "fmuls f11,f0,f5"]),
    ("90 struct copy interleave", "order:copyrun",
     ["lwz r7,0(r4)", "lwz r6,4(r4)", "lwz r0,8(r4)", "stw r7,8(r1)", "stw r6,12(r1)", "stw r0,16(r1)"],
     ["lwz r7,0(r4)", "lwz r6,4(r4)", "stw r7,8(r1)", "stw r6,12(r1)", "lwz r0,8(r4)", "stw r0,16(r1)"]),
    ("91/74 argument load order", "order:args",
     ["lfs f1,0(0) | R_PPC_EMB_SDA21 data_804E5248_data_806D0000", "li r4,1", "lwz r5,4(r31)", "lwz r6,8(r31)", "bl 10 <f+0x10> | R_PPC_REL24 ctor"],
     ["lwz r5,4(r31)", "lwz r6,8(r31)", "lfs f1,0(0) | R_PPC_EMB_SDA21 data_804E5248_data_806D0000", "li r4,1", "bl 10 <f+0x10> | R_PPC_REL24 ctor"]),
    ("82 sum argument scheduled early", "order:args",
     ["lfs f0,4(r3)", "fadds f2,f31,f0", "lfs f1,0(r3)", "fmr f4,f30", "bl 10 <f+0x10> | R_PPC_REL24 spr"],
     ["lfs f0,4(r3)", "lfs f1,0(r3)", "fmr f4,f30", "fadds f2,f31,f0", "bl 10 <f+0x10> | R_PPC_REL24 spr"]),
    ("55 extra saved register", "saved-regs",
     ["stwu r1,-32(r1)", "mflr r0", "stw r0,36(r1)", "stmw r27,12(r1)", "subf r28,r4,r3", "srawi r0,r28,6", "addze r28,r0", "bl 20 <f+0x20> | R_PPC_REL24 g"],
     ["stwu r1,-32(r1)", "mflr r0", "stw r0,36(r1)", "stmw r26,8(r1)", "subf r26,r4,r3", "bl 14 <f+0x14> | R_PPC_REL24 g", "srawi r0,r26,6", "addze r28,r0"]),
    ("60 add per iteration vs walker", "select:indexed",
     ["li r5,0", "mr r4,r3", "add r6,r3,r5", "lfs f0,0(r4)", "addi r4,r4,4", "addi r5,r5,4", "cmpwi r5,16", "blt 8 <f+0x8>"],
     ["li r5,0", "mr r4,r3", "lfs f0,0(r4)", "addi r4,r4,4", "addi r5,r5,4", "cmpwi r5,16", "blt 8 <f+0x8>"]),
    ("63 constant load order", "order:const",
     ["lfs f30,40(r1)", "lfs f31,0(0) | R_PPC_EMB_SDA21 zero", "li r30,0"],
     ["lfs f31,0(0) | R_PPC_EMB_SDA21 zero", "lfs f30,40(r1)", "li r30,0"]),
    ("64 operand order", "operand-order",
     ["fmuls f1,f2,f3", "blr"], ["fmuls f1,f3,f2", "blr"]),
    ("39 fmadds", "select:fused",
     ["fmuls f0,f1,f2", "fadds f1,f0,f3", "blr"], ["fmadds f1,f1,f2,f3", "blr"]),
    ("pooled base", "address:pool",
     ["addi r4,r31,516", "lwz r3,0(r4)"],
     ["lis r4,0 | R_PPC_ADDR16_HA lbl_A", "addi r4,r4,0 | R_PPC_ADDR16_LO lbl_A", "lwz r3,0(r4)"]),
    ("67 li/mr", "load:const-vs-copy",
     ["li r30,0", "mr r29,r30", "blr"], ["li r30,0", "li r29,0", "blr"]),
    ("signedness", "select:signedness",
     ["cmpwi r3,4", "blr"], ["cmplwi r3,4", "blr"]),
    ("extension", "extend",
     ["lbz r3,0(r4)", "extsb r3,r3", "blr"], ["lbz r3,0(r4)", "blr"]),
    ("ctr loop", "loop:ctr",
     ["li r0,4", "mtctr r0", "stw r4,0(r3)", "addi r3,r3,4", "bdnz 8 <f+0x8>", "blr"],
     ["stw r4,0(r3)", "stw r4,4(r3)", "stw r4,8(r3)", "stw r4,12(r3)", "blr"]),
    ("symbol split", "reloc:symbol",
     ["lfs f1,0(0) | R_PPC_EMB_SDA21 lbl_806DA000", "blr"], ["lfs f1,0(0) | R_PPC_EMB_SDA21 lbl_806DA004", "blr"]),
    ("stack slot order", "stack:offset",
     ["stwu r1,-32(r1)", "lfs f1,8(r1)", "blr"], ["stwu r1,-32(r1)", "lfs f1,20(r1)", "blr"]),
    ("inlined call", "call:inline",
     ["mr r3,r31", "bl 4 <f+0x4> | R_PPC_REL24 Helper", "blr"], ["lwz r3,4(r31)", "stw r3,8(r31)", "blr"]),
]


def cmd_selftest(a):
    bad = 0
    for name, want, T, O in SELFTESTS:
        res = analyse(_mk(T), _mk(O))
        got = [c for c, _, _ in summarise(res)]
        ok = want in got
        bad += not ok
        print(f"{'ok  ' if ok else 'FAIL'} {name}: want {want}, got {got}")
    print("selftest:", "all ok" if not bad else f"{bad} failed")
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("fn")
    p.add_argument("unit")
    p.add_argument("fn")
    p.add_argument("--ours", help="our object (default build/GNLJ82/src/UNIT.o)")
    p.add_argument("--src", help="compile this source with the unit's command and diagnose that instead")
    p.add_argument("--ours-fn")
    p.add_argument("--json", action="store_true")
    p.add_argument("-v", "--verbose", action="store_true")
    p = sub.add_parser("objs")
    p.add_argument("target")
    p.add_argument("ours")
    p.add_argument("fn")
    p.add_argument("--ours-fn")
    p.add_argument("--json", action="store_true")
    p.add_argument("-v", "--verbose", action="store_true")
    p = sub.add_parser("batch")
    p.add_argument("--min", type=float, default=0)
    p.add_argument("--md")
    p.add_argument("--json")
    p = sub.add_parser("replay", help="rebuild solved functions from the pre-fix source and check the class fires")
    p.add_argument("--only")
    p.add_argument("-v", "--verbose", action="store_true")
    sub.add_parser("classes")
    sub.add_parser("selftest")
    a = ap.parse_args()
    if a.cmd == "classes":
        for c, (t, lv) in CLASSES.items():
            print(f"[{c}] {t}")
            for l in lv:
                print(f"  try: {l}")
        return 0
    if a.cmd == "selftest":
        return cmd_selftest(a)
    if a.cmd == "batch":
        return cmd_batch(a)
    if a.cmd == "replay":
        return cmd_replay(a)
    if a.cmd == "fn":
        tgt, ours = unit_paths(a.unit)
        ours = Path(a.ours) if a.ours else ours
        if a.src:
            import tempfile
            ours = compile_alt(a.unit, a.src, tempfile.mkdtemp(prefix="shapediag_"))
    else:
        tgt, ours = Path(a.target), Path(a.ours)
    res, err = run_objs(tgt, ours, a.fn, a.ours_fn)
    if err:
        print(err, file=sys.stderr)
        return 1
    if a.json:
        print(json.dumps(dict(fn=a.fn, n_target=res["n_target"], n_ours=res["n_ours"], reg_lines=res["reg_lines"],
                              findings=[f.as_dict() for f in res["findings"]]), indent=1))
    else:
        render(a.fn, res, verbose=a.verbose)
    return 0


if __name__ == "__main__":
    sys.exit(main())
