# C++ scoped object with cross-TU dtor: matching hurdle (2026-05-19)

Observed while attempting to match `MemoryManager_TimedFree` @ 0x8003AFB8 (asm_fn retreat committed in b37d247).

Update: `MemoryManager_TimedFree` was later promoted from asm_fn to C++ and
matched in commit `871c087` (`Match MemoryManager_TimedFree in C++`). The
structural diagnosis below still matters, but the final implementation uses a
small codegen shim inside the inline `ScopedTimer` destructor rather than a
fully natural destructor body.

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

Commit `871c087` proves the H1 structure was fundamentally right:

- A canonical strong `__dt__11ScopedTimerFv` owns the original
  `0x8002CCD8..0x8002CD7C` address range.
- `MemoryManager_TimedFree` is a C++ function with a stack-local
  `ScopedTimer`.
- The function has target-like C++ exception cleanup metadata and duplicated
  destructor cleanup in both normal exit branches.

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

## Related

- `docs/per_fn_matching_strategy.md` §14.1 (Approach A / B for extab handling) — basic patterns, doesn't cover this case
- `docs/notes/pragma-exceptions-on-enable-direction.md` — per-fn opt-in for auto-emit
- `docs/notes/sdata-deleting-dtor-idiom.md` — `if (this) if (this) { ... }` doubled-guard CW C++ pattern
- `src/game/dtor_801FEA70.c` — has similar `SPECIFICATION + ACTIVECATCHBLOCK + fn_8027248C` (`__terminate`) cleanup pattern, also asm_fn retreat
