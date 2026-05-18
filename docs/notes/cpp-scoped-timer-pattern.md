# C++ scoped object with cross-TU dtor: matching hurdle (2026-05-19)

Observed while attempting to match `MemoryManager_TimedFree` @ 0x8003AFB8 (asm_fn retreat committed in b37d247).

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

## Related

- `docs/per_fn_matching_strategy.md` §14.1 (Approach A / B for extab handling) — basic patterns, doesn't cover this case
- `docs/notes/pragma-exceptions-on-enable-direction.md` — per-fn opt-in for auto-emit
- `docs/notes/sdata-deleting-dtor-idiom.md` — `if (this) if (this) { ... }` doubled-guard CW C++ pattern
- `src/game/dtor_801FEA70.c` — has similar `SPECIFICATION + ACTIVECATCHBLOCK + fn_8027248C` (`__terminate`) cleanup pattern, also asm_fn retreat
