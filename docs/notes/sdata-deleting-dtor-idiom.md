# sdata-loaded deleting-destructor: local-inside-outer-if idiom (2026-05-18)

Observed while matching `ItemDisplay_Destroy` @ 0x8020AE50 (commit 31033de in batch_text_8020ae50_itemdisp_bundle).

The C++ deleting-destructor offset-0 duplicate `beq` idiom (per_fn_matching_strategy.md §14.3, originally documented for `dtor_800A9D2C`) needs a variant when the singleton being torn down is **loaded from sdata** instead of being received as a `this` parameter.

## Original §14.3 idiom (this in r3 from caller)

```c
void *dtor_800A9D2C(void *this, short flag) {
    if (this) {
        if (this) {
            dtor_800AA69C(this, 0);
        }
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
```

CW emits `mr. r31, r3; beq; beq` — the combined move-and-compare exists because `this` arrives in r3.

## Variant: sdata-resident singleton

For `ItemDisplay_Destroy`, the singleton sits in `.sbss` (`g_pItemDisplay`). There is no r3 parameter; CW must `lwz` from sda21 first. The target asm is:

```
lwz r31, g_pItemDisplay@sda21(r0)   ; load directly into r31 (callee-saved)
cmplwi r31, 0x0
beq .L_outer                         ; if (self) -- skip everything
beq .L_inner_skip                    ; inner if (self) -- skip body, keep trailing NULL-store
... body ...
```

The load goes **directly** to r31, not r3. There is no `mr r31, r3`.

## Source-form that reproduces it

```c
void ItemDisplay_Destroy(void) {
    if (g_pItemDisplay) {
        ItemDisplay *self = g_pItemDisplay;   /* local declared INSIDE outer if */
        if (self) {
            if (self->sprite) Sprite_Destroy(self->sprite, 1);
            dtor_8003AFB8(self);
        }
        g_pItemDisplay = 0;
    }
}
```

Key detail: `ItemDisplay *self = g_pItemDisplay;` is declared **inside** the outer `if (g_pItemDisplay) { ... }` block, after the guard has already been evaluated against the global.

## Anti-pattern (what the Ghidra decompile naturally produces)

```c
void ItemDisplay_Destroy(void) {
    ItemDisplay *self = g_pItemDisplay;   /* declared BEFORE outer if */
    if (self) {
        if (self) {
            ...
        }
        g_pItemDisplay = 0;
    }
}
```

This form generates:

```
lwz r3, g_pItemDisplay@sda21(r0)
cmplwi r3, 0x0
mr r31, r3                            ; <-- 4 extra bytes
beq ...
beq ...
```

The extra `mr r31, r3` shifts the function by 4 bytes and breaks the SHA-1.

## Hypothesis on why CW picks r31 for the load

When the live range of `self` starts *after* the outer guard has succeeded, CW's register allocator sees:

- `self` only exists on the path where the global is non-NULL
- on that path, `self` must survive across two `bl` calls (`Sprite_Destroy`, `dtor_8003AFB8`)
- so allocate a callee-saved reg (r31) and load directly into it

If `self` is live across the early-exit branch (declared outside the guard), CW initially loads to a caller-saved scratch (r3) and only promotes to r31 if needed — producing the extra `mr`.

## Applicability

Likely applies to any function with the pattern "singleton global tear-down, deleting-destructor-style". Candidates to check during future singleton matching: similar `void X_Destroy(void)` functions that touch a sdata pointer global and call inner dtors.
