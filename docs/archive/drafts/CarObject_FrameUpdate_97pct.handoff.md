# HANDOFF batch_promote_8004decc_frameupdate

## Result: skipped (97.10% reached; blocked on the documented ScopedTimer subi/lwz scheduler pair swap)

CarObject_FrameUpdate (0x8004DECC, 0x114, real extab w/ __dt__11ScopedTimerFv ref ->
approach B mandatory) was taken from asm to 97.10% / 69-instr C. EVERYTHING reproduces
byte-exactly (prologue/frame 0x30, r30=self / r31=arg->movement reuse, f31=maxSpd,
ScopedTimer ctor stores at sp+0x8/0xc, cam-in-r3 title-tracker idiom, nested-call
tachometer block, u32->float conversion cookie at sp+0x10/0x14, fsubs/fdivs tail)
EXCEPT one adjacent instruction pair in the inlined ScopedTimer dtor:

  target: 0x8004DF7C  subi r6, r4, 0x217d   (1/125000 magic lo)
          0x8004DF80  lwz  r7, 0x8(r1)      (ScopedTimer.start)
  mine:   lwz before subi (one scheduler slot)

### This is a KNOWN hard-block, not a new flavor

`docs/notes/cpp-scoped-timer-pattern.md` documents the exact same pair swap for the
canonical out-of-line `__dt__11ScopedTimerFv`: flag probes (-O4,p / -O4,s / -O3,p /
-O2 / -inline auto,deferred / `-schedule off`) all failed to flip it, and the matched
canonical dtor in `game/FlowDispatcher_ScopedTimer.c` pins the arithmetic with raw
`opword`s. The dtor is inlined into ~30 callers; this fn is one of them.

### Precan results (step 0)

- No Class 1 (the `bne; li r3,0` at 0x8004DF14 is the cam-in-r3 idiom, real code on the path).
- No Class 2 (no float-copy blocks). No loops (no Flavor 5).
- Flavor 3 ruled out by probe: removing `#pragma exceptions off` produces byte-identical
  codegen for this fn.
- Flavor 4 ruled out: callee-saved webs land exactly on target (self=r30, arg=r31,
  movement reuses r31, maxSpd=f31) with no coaxing.

### Why the FlowDispatcher opword shim does NOT rescue this caller (verified)

Embedding the pinned `asm { opword ... }` block (the exact technique that matched
`__dt__11ScopedTimerFv`) inside this C function poisons the rest of the fn:
- prologue loses `psq_st f31, 0x28(r1)` (f31 saved with stfd only) and the GPR save
  layout shifts (r30@0x20/r31@0x24/f31@0x28 vs target r30@0x18/r31@0x1c/f31@0x20+psq@0x28)
- the cam-in-r3 idiom un-folds (`cmplw r3, r3` + extra bne appear)
- symbolic asm loads (`lwz r7, tmStart`) get DCE'd because their consumers are opaque
  opwords (the canonical dtor avoided this by using opwords for the loads too, possible
  there because `this` lives in r30; here the loads must be r1-based with offsets that
  depend on CW's local layout)
So the shim works only in fns simple enough to have no surrounding optimization to lose.

### Verified idioms discovered this batch (do NOT rediscover)

1. volatile-member memory forcing: a local struct with ONE volatile member stays in
   memory wholesale; non-volatile members keep normal schedulable loads. Plain struct,
   whole-volatile struct, and static-inline ctor/dtor pointer forms all get SROA'd /
   const-propagated (`tm.id = 0x28` becomes `li r3, 0x28` at the use site; `tm.start`
   takes a r31 web). The volatile-id form reproduces the target ctor stores byte-exact.
2. u32->float conversion + postprocess_sdata2: `(float)us` auto-emits the 2^52
   magic double as an anonymous `@N` .sdata2 local; `tools/postprocess_sdata2.py`
   (active in the mwcc_sjis_extab rule) renames it to lbl_806D27D0 (UND) once the
   .text reloc offset aligns with the target obj. No manual extern for the magic needed
   (and none is possible). `lbl_806D27C8` (1000.0f) retyped `extern const float` works.
3. OSTicksToMicroseconds macro shape confirmed: `us = ((OSGetTick() - start) * 8) /
   ((*(unsigned int *)0x800000F8 / 4) / 125000)` reproduces the whole arithmetic
   (lis/lwz busclock, srwi 2, lis/subi 0x431BDE83 magic, mulhwu, srwi 15, divwu) with
   target registers.
4. Nested-call argument form `Tachometer_UpdateDisplaySpeed(KartMovement_CalcCurrentSpeed(mov, 1), maxSpd)`
   reproduces the f1-return-in-place + `fmr f2, f31` shape.
5. Same-TU asm fn signature refinement used: `asm void CarObject_MainUpdate(void *self, void *arg)`
   (decl + def header) lets the promoted C call it naturally; asm body unaffected.
6. The report.json scores seen mid-iteration for CarObject_Init (98.18%) /
   ItemEffect_SelectAndDispatch (99.38%) are PRE-EXISTING objdiff scoring artifacts
   (raw `subi rX, r2, imm` sda21 forms in asm bodies lack relocs vs target obj);
   dol bytes identical, SHA-1 green. Do not chase them.

### Sibling unlock

The identical inlined-dtor block lives in CarObject_Init (same TU, ~0x8004ECAC) and
~30 callers TU-wide. Any pure-C solution to the subi/lwz pair swap unlocks all of them
plus lets the canonical dtor drop its opword shim. Conversely, until it is solved,
every ScopedTimer-bearing caller will stall at ~97-99%.

Worktree was restored with `git checkout` (TU only; configure.py/splits/symbols never
needed changes - all extern retypes were TU-internal, listed in the appendix) and full
`ninja build/GNLJ82/ok` is green.

```json
{
  "batch_id": "batch_promote_8004decc_frameupdate",
  "sub_summary": "CarObject_FrameUpdate promote: skipped at 97.10% - single adjacent-pair scheduler swap (subi 0x431BDE83-magic vs lwz ScopedTimer.start) in the inlined ScopedTimer dtor; same documented hard-block as the canonical __dt__11ScopedTimerFv (docs/notes/cpp-scoped-timer-pattern.md), where flag probes incl. -schedule off already failed; the FlowDispatcher opword shim is not transplantable into this caller (poisons psq f31 save + cam idiom + DCEs symbolic asm loads)",
  "results": [
    {
      "addr": "0x8004DECC",
      "name": "CarObject_FrameUpdate",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 97.10% (69 instrs; 67 byte-identical, residual = one adjacent instruction pair swapped at 0x8004DF7C/0x8004DF80). Precan: no class-1/2/5; flavor-3 ruled out (exceptions on/off probe byte-identical); flavor-4 absent (r30/r31/f31 webs land on target naturally). Hard-block = ScopedTimer-dtor subi/lwz scheduler pair, pre-documented in docs/notes/cpp-scoped-timer-pattern.md (canonical dtor needed raw opwords; -schedule off etc. already probed there). Spellings tried this batch: plain struct (SROA), full-volatile struct, volatile-id member (best), single-expression macro form, denominator-first reorder (permutes scratch regs, swap persists), static inline Ctor/Dtor via pointer (re-SROA), opword pin (whole-fn codegen damage: psq_st f31 dropped, save layout +0x8, cam idiom unfolds, symbolic loads DCE'd). Sibling: same inlined dtor block in CarObject_Init (same TU) and ~30 callers TU-wide; solving the pair swap in pure C unlocks all. Paste-ready 97% C + extern retypes + CarObjFrameView in HANDOFF appendix. New verified idioms: volatile-member memory forcing; postprocess_sdata2 auto-renames the u32->float 2^52 anon @N local to lbl_806D27D0 once .text offsets align (works under mwcc_sjis_extab)."
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
      "path": "docs/notes/cpp-scoped-timer-pattern.md",
      "content": "## CarObject_FrameUpdate (0x8004DECC) inline-dtor caller probe (2026-06-10, batch_promote_8004decc_frameupdate)\n\nNew data points for the ScopedTimer subi/lwz scheduler pair swap, gathered in an\ninline-dtor CALLER context (not the canonical dtor):\n\n- Caller context reproduces the identical swap: target 0x8004DF7C `subi r6,r4,0x217d`\n  before 0x8004DF80 `lwz r7,0x8(r1)`; CW 1.3.2 emits the inverse pair order for every\n  C spelling tried. All other 67 of 69 instructions byte-match (97.10% fuzzy).\n- exceptions on/off probe: byte-identical codegen -> NOT the approach-B regalloc class.\n- Spellings probed (all produce lwz-before-subi): two-statement diff/us; single\n  expression (OSTicksToMicroseconds macro form); denominator-first statement order\n  (this also permutes r4-r7 scratch assignment, swap persists); plain struct (gets\n  fully SROA'd: start -> r31 web, id const-propagated to `li r3,0x28`); whole-struct\n  volatile; volatile-id-member only; static inline Ctor/Dtor via this_ pointer\n  (re-SROA'd, address-take does not survive inlining).\n- volatile member is the working memory-forcing idiom: a struct with ONE volatile\n  member stays in memory wholesale, non-volatile members keep normal (schedulable)\n  loads, and the ctor store order `li r0,0x28; stw 0xc(r1); bl OSGetTick; stw r3,0x8(r1)`\n  reproduces exactly.\n- The FlowDispatcher opword-shim is NOT transplantable into a complex caller: an\n  `asm {}` block inside this fn (a) drops the psq_st half of the f31 callee save and\n  shifts the GPR save layout (+0x8), (b) un-folds the cam-in-r3 idiom into\n  `cmplw r3,r3; bne`, (c) DCE's symbolic asm loads (`lwz r7, tmStart`) because their\n  consumers are opaque opwords. Whole-fn optimization degrades; only works in simple\n  fns like the canonical dtor.\n- postprocess_sdata2.py confirmed working in the mwcc_sjis_extab rule for the\n  u32->float conversion magic: the anon `@N` double in .sdata2 is renamed to\n  lbl_806D27D0 (UND) once the .text reloc offset aligns with target (it silently\n  does NOT rename while the instruction stream is offset-shifted relative to target).\n- Sibling impact: the same inlined dtor block (with identical subi/lwz order) appears\n  in CarObject_Init (same TU, around 0x8004ECAC) and per this note's main section in\n  ~30 callers. Solving the pair swap in pure C unlocks all of them.\n"
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": "CW 1.3.2 scheduler pair swap in the inlined ScopedTimer dtor arithmetic: target emits subi r6,r4,0x217d (0x8004DF7C) before lwz r7,0x8(r1) (0x8004DF80); CW emits the inverse for every C spelling. Identical to the documented canonical-dtor hard-block (docs/notes/cpp-scoped-timer-pattern.md); the opword-pin workaround used there degrades whole-fn codegen in this caller (psq f31 save, cam idiom, DCE of symbolic asm loads). 97.10%, all else byte-identical.",
  "user_attention": null
}
```

## Appendix: best-attempt C (97.10%) - paste-ready for retry

In-TU extern retypes (replace the open prototypes; asm bodies are unaffected by C types):

```c
extern float KartMovement_CalcCurrentSpeed(void *mov, int flag);
extern float KartMovement_CalcMaxSpeed(void *mov, int flag);
extern unsigned long OSGetTick(void);
extern void Profiler_RecordFrame(unsigned int id, float ms);
extern void Tachometer_SetCoinCount(int count);
extern void Tachometer_UpdateDisplaySpeed(float current, float max);
extern void TitleTracker_Empty_PreFinalizeHook(unsigned int tracker, int kartSlot);
extern const float lbl_806D27C8; /* 1000.0f (us -> ms divisor) */
```

Same-TU decl changes:

```c
asm void CarObject_MainUpdate(void *self, void *arg);  /* decl + asm def header */
void CarObject_FrameUpdate(CarObjFrameView *self, void *arg);  /* replaces asm fwd decl */
```

View struct (add next to KartItemRenderView):

```c
typedef struct CarObjFrameView {
    char pad_0x0[0x10];
    int kartSlot;                   /* 0x10 */
    char pad_0x14[0xc];
    unsigned char isPlayer;         /* 0x20 */
    char pad_0x21[0x7];
    void *movement;                 /* 0x28 */
    char pad_0x2c[0x9c];
    int coinCount;                  /* 0xc8 */
} CarObjFrameView;
```

Function body (replaces the asm_fn body in place; keep the manual extab/extabindex
emits, approach B):

```c
#pragma exceptions off
/* inline-expanded ScopedTimer (id 0x28): ctor stores id + OSGetTick at
 * sp+0xc/0x8, dtor converts elapsed ticks to microseconds and reports ms. */
void CarObject_FrameUpdate(CarObjFrameView *self, void *arg) { /* 0x8004DECC size:0x114 */
    struct {
        unsigned int start;        /* sp+0x8 */
        volatile unsigned int id;  /* sp+0xc */
    } tm;
    unsigned int t;
    unsigned int us;

    tm.id = 0x28;
    tm.start = OSGetTick();
    CarObject_MainUpdate(self, arg);
    t = lbl_806D10A0;
    if (t != lbl_806D10A0) {
    } else if (t == 0) {
        t = 0;
    }
    if (t != 0) {
        TitleTracker_Empty_PreFinalizeHook(t, self->kartSlot);
    }
    if (self->isPlayer == 1) {
        void *mov;
        float maxSpd;
        mov = self->movement;
        maxSpd = KartMovement_CalcMaxSpeed(mov, 1);
        Tachometer_UpdateDisplaySpeed(KartMovement_CalcCurrentSpeed(mov, 1), maxSpd);
        Tachometer_SetCoinCount(self->coinCount);
    }
    us = ((OSGetTick() - tm.start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(tm.id, (float)us / lbl_806D27C8);
}
#pragma exceptions reset
```

The ONLY residual vs target: `subi r6, r4, 0x217d` and `lwz r7, 0x8(r1)` swap places
(target 0x8004DF7C/0x8004DF80). 67/69 instructions byte-identical, all registers and
stack offsets correct.
