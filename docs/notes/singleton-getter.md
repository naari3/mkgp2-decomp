# Singleton defensive getter (`SINGLETON_INSTANCE`)

Approved by the repo owner on 2026-11-07.

## Shape in the target

```
lwz    r3, lbl_806D10AC(r13)   ; or r0, then mr r3,r0
cmplwi r3, 0
bne    L
li     r3, 0
L: ...
```

Sites (2026-11-07):

| Global | Sites |
|---|---|
| lbl_806D10AC (DrawManager) | 41 |
| lbl_806D109C | 39 |
| lbl_806D10A0 | 12 |
| lbl_806D10D0 | 6 |
| g_pInputState | 3 |
| g_carObjectList | 2 |

## Investigation
Compilers tested: GC/1.3.2, 2.6, 1.2.5 and 3.0a5, with the repo cflags.

No other construct produces this shape:
- Upcasts and downcasts at offset 0: the check is dropped.
- Casts at a non-zero offset: these give `beq skip; addi`.
- Virtual bases, references, `operator T*` wrappers and CRTP: either no check is emitted or the shape differs.

Only a source-level "null → return null" accessor reproduces it byte-for-byte:

```c++
static T* GetInstance() { if (ms_pInstance == 0) return 0; return ms_pInstance; }
```

`p == 0 ? 0 : p` gives the same code. The opposite polarity `p ? p : 0` gives `beq; b; li 0` instead. The identical shape across 100+ sites therefore points to one defensive accessor per manager class in the original source.

## Rule
- Write the read as `SINGLETON_INSTANCE(global)` from `include/game/singleton.h`.
- Do not hand-write ad-hoc null re-tests at call sites.
- Other no-op null checks remain rejected.

Precedents written before this rule:
- `src/game/anon_80211B10.cpp`
- `src/game/BtMode_RenderFrame.c`
