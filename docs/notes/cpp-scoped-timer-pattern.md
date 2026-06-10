# C++ scoped object with cross-TU dtor: matching hurdle (2026-05-19)

Observed while attempting to match `MemoryManager_TimedFree` @ 0x8003AFB8 (asm_fn retreat committed in b37d247).

Update: `MemoryManager_TimedFree` was later promoted from asm_fn to C++ and
matched in commit `871c087` (`Match MemoryManager_TimedFree in C++`). The
canonical out-of-line `ScopedTimer::~ScopedTimer()` at 0x8002CCD8 was then
promoted from asm_fn to a C++ destructor definition in commit `b8f8bf4`
(`Implement ScopedTimer destructor in C++`). The structural diagnosis below
still matters, but the final implementation uses small codegen shims inside the
`ScopedTimer` destructor body rather than a fully natural destructor spelling.

The function originally is C++ and uses a stack-allocated `ScopedTimer` instance to time the free operation. The class destructor (`ScopedTimer_End` @ 0x8002CCD8, named `dtor_8002CCD8` in symbols.txt before this analysis) is **defined in a different TU** but called from MemoryManager_TimedFree's scope cleanup.

## Why matching is hard

The target asm has three constructs that plain C cannot synthesize and pure-C++ in a single isolated TU also cannot reproduce:

1. **DESTROYLOCAL extab entry** referencing `dtor_8002CCD8` @ 0x8(FP). This requires a C++ class with a non-trivial destructor on a stack-local; CW1.3.2 auto-emits the extab entry only for such classes.

2. **SPECIFICATION + ACTIVECATCHBLOCK extab entries** @ 0x10(FP). These come from `throw(...)` exception-spec restrictions plus a `catch (...)` landing pad. No plain-C surface form.

3. **Inlined dtor body in both `if (ptr)` branches**. Target shows the metric calc + Profiler_RecordFrame call duplicated in both the `ptr==NULL` and `ptr!=NULL` paths. This is CW inlining `ScopedTimer_End` at end-of-scope. For the inlining to work, the dtor body must be **defined inline** in the class declaration of `ScopedTimer`.

4. **Out-of-line dtor copy at 0x8002CCD8**. The same dtor body must also exist out-of-line at 0x8002CCD8 (referenced by the DESTROYLOCAL extab action as a function pointer). This is the "key function" emitted in a different TU that hosts the canonical non-inline copy.

## The structural contradiction

For MemoryManager_TimedFree.cpp to match standalone, ScopedTimer must be:
- **Inline-defined dtor** (for body inlining in the call sites)
- **Out-of-line dtor at exactly 0x8002CCD8** (for extab DESTROYLOCAL reloc to point there)

If the .cpp emits its own out-of-line copy, it lands somewhere in the new TU's .text — NOT at 0x8002CCD8. The extab reloc then points to the wrong address. SHA-1 fails.

The only way around this is to put `ScopedTimer::~ScopedTimer()` in a TU that **physically owns the 0x8002CCD8 address range**. That TU must come earlier in the link order (since 0x8002CCD8 < 0x8003AFB8).

## What was tried (3 attempts)

| # | Source form | .text match | notes |
|---|---|---|---|
| 1 | plain C, single if/else with duplicated metric blocks | 65.4% | r31 not as FP, no extab |
| 2 | plain C + `#pragma exceptions on` | 43.7% | extab partial but body diverged |
| 3 | .cpp with inline ctor, declared dtor (no def) | 34.2% | dtor call site emitted but bytes wrong; `mr r31, r3` vs target's `or r31, r1, r1` (FP) |

All worse than asm_fn. Retreated to asm_fn (commit b37d247).

## Path to a real match (future work)

The cleanest approach requires **claiming both 0x8002CCD8 (ScopedTimer_End) and 0x8003AFB8 (MemoryManager_TimedFree) under a single .cpp TU** with disjoint .text ranges:

```
game/MemoryManager.cpp:
    .text  start:0x8002CCD8 end:0x8002CD7C   # ScopedTimer::~ScopedTimer
    .text  start:0x8003AFB8 end:0x8003B120   # MemoryManager_TimedFree (uses ScopedTimer)
```

Then:

```cpp
class ScopedTimer {
public:
    inline ScopedTimer(int slot) : m_startTick(OSGetTick()), m_slot(slot) {}
    ~ScopedTimer();   // out-of-line, defined below
private:
    unsigned int m_startTick;
    int m_slot;
};

// Source order matters: dtor must be defined BEFORE MemoryManager_TimedFree
// so its .text address (0x8002CCD8) precedes MemoryManager_TimedFree (0x8003AFB8).
ScopedTimer::~ScopedTimer() {
    /* mirror dtor_8002CCD8 disasm */
}

void MemoryManager_TimedFree(void *ptr) {
    ScopedTimer timer(0x13);
    /* body */
}
```

Risks:
- dtk may reject disjoint .text ranges in one TU with a cyclic dep error (§15 wedge pattern variant).
- CW1.3.2 inlining policy may decide NOT to inline the dtor (out-of-line dtor + bl from call site) which would not match the target's inlined-in-both-branches body.
- Other callers of `dtor_8002CCD8` exist (`Alloc`, `MemoryManager_AllocTagged`, `MemoryManager_Free`, `MemoryManager_TimedFree`, `FUN_8003b120`) — they'd all need to be matched together as a unit (`MemoryManager.cpp` covering 0x8003ADFC..0x8003B2D8) or carefully co-existed with the rest via partial promotion.

## Symbol naming note

The CW1.3.2 mangled name for `ScopedTimer::~ScopedTimer()` is `__dt__11ScopedTimerFv` (`__dt` = destructor, `11ScopedTimer` = class name with length prefix, `F` = function, `v` = void args). If pursuing the .cpp approach, rename `dtor_8002CCD8` to `__dt__11ScopedTimerFv` in symbols.txt.

## Post-match gap: natural C++ vs current shim

Commits `871c087` and `b8f8bf4` prove the H1 structure was fundamentally right:

- A canonical strong `__dt__11ScopedTimerFv` owns the original
  `0x8002CCD8..0x8002CD7C` address range, and is now a C++ destructor
  definition in `src/game/FlowDispatcher_ScopedTimer.c`.
- `MemoryManager_TimedFree` is a C++ function with a stack-local
  `ScopedTimer`.
- The function has target-like C++ exception cleanup metadata and duplicated
  destructor cleanup in both normal exit branches.

The canonical dtor promotion uses the same practical compromise as
`MemoryManager_TimedFree`: C++ owns the destructor, delete path, null guard,
call sites, and epilogue, while raw `opword` pins the small elapsed-time
arithmetic sequence that CW1.3.2 otherwise schedules differently. The canonical
definition is wrapped in `#pragma exceptions off` so CW does not emit a second
auto extab/extabindex pair; the existing manual target extab for
`FlowDispatcher_ScopedTimer.c` remains authoritative.

However, the matched source is not yet the likely original, natural C++ source.
The remaining gap is local to `ScopedTimer`'s destructor body and its surrounding
stack layout:

- The timer arithmetic is emitted through raw PPC `opword` / inline asm.
- `char buf[0x204]` is used while the runtime size passed to
  `fn_80276D30` remains `0x200`.
- `tools/postprocess_extab_user.py` patches this TU's auto-extab first word
  from `0x10180000` to target `0x101A0000`.

This should be treated as a matching shim, not evidence that the original
source used inline asm. The original source was probably closer to:

```cpp
void MemoryManager_TimedFree(void *ptr) throw()
{
    ScopedTimer timer(0x13);
    char buf[0x200];

    if (lbl_806D0FA1 == 0) {
        fn_80276D30(buf, 0x200, lbl_802E9DD0);
        DebugPrintf(buf);
        DebugPrintf(lbl_802E9DB0);
        for (;;) {}
    }

    if (ptr != 0) {
        OSFreeToHeap(lbl_806CF010, ptr);
    }
}
```

with a simple `ScopedTimer::~ScopedTimer()` equivalent to:

```cpp
ScopedTimer::~ScopedTimer()
{
    unsigned int endTick = OSGetTick();
    unsigned int ticksPerUnit = ((*(volatile unsigned int *)0x800000F8) >> 2) / 125000;
    unsigned int elapsed = endTick - m_startTick;
    unsigned int elapsedUnit = (elapsed << 3) / ticksPerUnit;

    Profiler_RecordFrame(m_slot, (float)elapsedUnit / lbl_806D24D8);
}
```

Pure C++ attempts get close but miss CW1.3.2's target register allocation:

- The reciprocal/divide block picks different GPRs.
- Partial asm gets `mulhwu r0,r6,r4` right, but CW chooses `r8` for the
  `0x4330` int-to-double high word instead of target `r0`.
- A union-cookie local creates the desired conversion flavor but shifts the
  stack layout and grows the function.
- Full inline asm including the `Profiler_RecordFrame` call makes CW preserve
  `r29`, growing the function and changing the caller register plan.

The likely reason is missing original compilation context rather than different
game logic: exact TU/header layout, inline budget, surrounding declarations,
local stack pressure, and exception-spec metadata all affect CW1.3.2's
allocator and extab encoder. The current source restores the C++ control
structure and exception structure, but pins the last unstable codegen details.

Future cleanup target:

1. Move `ScopedTimer` to a shared header once another caller is ready to promote.
2. Compare the 30 inline-dtor callers that reference `__dt__11ScopedTimerFv`
   only from extab, looking for a caller where natural C++ emits the destructor
   body without raw `opword`.
3. Identify the original TU or header context that makes CW choose `r0` for the
   `0x4330` conversion naturally.
4. If that context is found, replace the destructor shim and remove the scoped
   extab first-word patch.

## Follow-up: natural dtor probes

Additional scratch probes in `tmp/cw_scoped_timer_natural_dtor_*` refined the
gap:

- The canonical out-of-line destructor can be expressed very closely as natural
  C++ if the elapsed-unit expression is written as one expression:

  ```cpp
  endTick = OSGetTick();
  Profiler_RecordFrame(
      m_slot,
      (float)(((endTick - m_startTick) << 3) /
              (((*(volatile unsigned int *)0x800000F8) >> 2) / 125000)) /
          lbl_806D2280);
  ```

- The class likely has a class-specific delete path equivalent to:

  ```cpp
  static void operator delete(void *ptr) { MemoryManager_TimedFree(ptr); }
  ```

  Without this, CW emits `bl __dl__FPv`; target `__dt__11ScopedTimerFv` calls
  `MemoryManager_TimedFree` in the deleting-dtor tail.

- With the one-expression form plus class-specific delete, natural C++ emits
  the target register family for the canonical dtor:
  `lis r5,0x8000`, `lis r4,0x431c`, `lis r0,0x4330`,
  `mulhwu r0,r6,r4`, `divwu r0,r4,r0`.

- Remaining canonical dtor differences:
  - CW schedules `lwz r7,0x0(r30)` before `subi r6,r4,0x217d`; target has
    `subi` first.
  - CW emits the `0x43300000,0` conversion cookie as an anonymous `.sdata2`
    local (`@N`). This is probably addressable with the existing
    `postprocess_sdata2.py` mechanism, as in `fobj.c`.
  - The `lfs lbl_806D2280` relocation is already a normal named sdata2
    reference; only obj-level placeholder bytes differ before link.

Follow-up after `b8f8bf4`: the natural one-expression canonical dtor was tried
again in the real `FlowDispatcher_ScopedTimer.c` TU with `lbl_806D2280`
declared as `float`. `postprocess_sdata2.py` correctly rewrote the anonymous
cookie (`@19 -> lbl_806D2288`), but the arithmetic register allocation still
missed target (`mulhwu r4,r4,r5` / `divwu r0,r5,r0` instead of target
`mulhwu r0,r6,r4` / `divwu r0,r4,r0`). This confirms the next blocker is GPR
allocation, not sdata2 naming.

- Flag probes did not find a compiler option that fixes the `subi`/`lwz`
  schedule while keeping target code shape:
  - `-O4,p` and `-inline auto/deferred` keep the same order.
  - `-O4,s`, `-O3,p`, and `-O2` change the arithmetic pattern too much.
  - `-schedule off` did not change this natural dtor order in the probe.

- Inlining the natural dtor into `MemoryManager_TimedFree` is still harder than
  the canonical dtor:
  - With visible natural conversion locals, CW places the conversion cookie
    after the visible buffer (`0x230/0x234`) or changes the arithmetic GPRs.
  - The committed raw-opword shim keeps the invisible cookie at target
    `0x228/0x22C` and preserves the caller's `r30`/frame layout.

Current inference: the likely original source was natural C++ with a simple
one-expression elapsed conversion and a class-specific delete routed through
`MemoryManager_TimedFree`. The remaining mismatch is not game logic but
compiler scheduling/allocation context. The canonical `__dt__11ScopedTimerFv`
is no longer asm_fn, so the next cleanup target is specifically to replace its
raw arithmetic shim with the natural one-expression form plus
`postprocess_sdata2.py`. Only after that should we try to remove the inline
shim in `MemoryManager_TimedFree`.

## Related

- `docs/per_fn_matching_strategy.md` §14.1 (Approach A / B for extab handling) — basic patterns, doesn't cover this case
- `docs/notes/pragma-exceptions-on-enable-direction.md` — per-fn opt-in for auto-emit
- `docs/notes/sdata-deleting-dtor-idiom.md` — `if (this) if (this) { ... }` doubled-guard CW C++ pattern
- `src/game/dtor_801FEA70.c` — has similar `SPECIFICATION + ACTIVECATCHBLOCK + fn_8027248C` (`__terminate`) cleanup pattern, also asm_fn retreat

## CarObject_FrameUpdate (0x8004DECC) inline-dtor caller probe (2026-06-10, batch_promote_8004decc_frameupdate)

New data points for the ScopedTimer subi/lwz scheduler pair swap, gathered in an
inline-dtor CALLER context (not the canonical dtor):

- Caller context reproduces the identical swap: target 0x8004DF7C `subi r6,r4,0x217d`
  before 0x8004DF80 `lwz r7,0x8(r1)`; CW 1.3.2 emits the inverse pair order for every
  C spelling tried. All other 67 of 69 instructions byte-match (97.10% fuzzy).
- exceptions on/off probe: byte-identical codegen -> NOT the approach-B regalloc class.
- Spellings probed (all produce lwz-before-subi): two-statement diff/us; single
  expression (OSTicksToMicroseconds macro form); denominator-first statement order
  (this also permutes r4-r7 scratch assignment, swap persists); plain struct (gets
  fully SROA'd: start -> r31 web, id const-propagated to `li r3,0x28`); whole-struct
  volatile; volatile-id-member only; static inline Ctor/Dtor via this_ pointer
  (re-SROA'd, address-take does not survive inlining).
- volatile member is the working memory-forcing idiom: a struct with ONE volatile
  member stays in memory wholesale, non-volatile members keep normal (schedulable)
  loads, and the ctor store order `li r0,0x28; stw 0xc(r1); bl OSGetTick; stw r3,0x8(r1)`
  reproduces exactly.
- The FlowDispatcher opword-shim is NOT transplantable into a complex caller: an
  `asm {}` block inside this fn (a) drops the psq_st half of the f31 callee save and
  shifts the GPR save layout (+0x8), (b) un-folds the cam-in-r3 idiom into
  `cmplw r3,r3; bne`, (c) DCE's symbolic asm loads (`lwz r7, tmStart`) because their
  consumers are opaque opwords. Whole-fn optimization degrades; only works in simple
  fns like the canonical dtor.
- postprocess_sdata2.py confirmed working in the mwcc_sjis_extab rule for the
  u32->float conversion magic: the anon `@N` double in .sdata2 is renamed to
  lbl_806D27D0 (UND) once the .text reloc offset aligns with target (it silently
  does NOT rename while the instruction stream is offset-shifted relative to target).
- Sibling impact: the same inlined dtor block (with identical subi/lwz order) appears
  in CarObject_Init (same TU, around 0x8004ECAC) and per this note's main section in
  ~30 callers. Solving the pair swap in pure C unlocks all of them.
