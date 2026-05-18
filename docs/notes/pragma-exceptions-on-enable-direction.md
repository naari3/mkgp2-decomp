# `#pragma exceptions on` as enable-direction (Approach B inverse)

`docs/per_fn_matching_strategy.md` §14.1 documents Approach B as using
`#pragma exceptions off / reset` to SUPPRESS CW's auto-emit of
extab/extabindex inside a lib compiled with `-Cpp_exceptions on`.

The inverse also works: inside a lib compiled with `-Cpp_exceptions
off`, wrapping a single function with `#pragma exceptions on / reset`
opts THAT FUNCTION into auto-emit. Verified at `Rand15` (commit in
`orch/batch_text_800a06d0_rand15`).

## When to use

- A single function (or small group) in a `-Cpp_exceptions off` lib
  has its own extab/extabindex entries in the target binary
- You want to avoid the manual extab_user emit machinery
  (`extab_padding` configure flag, `__declspec(section
  ".extab_user")` arrays, postprocess_extab_user.py routing) because
  the function is small (e.g. tail-call wrapper) and a full extab
  scaffold is overkill

## Usage

```c
#pragma exceptions on
ReturnT MyFn(Args...) { ... }
#pragma exceptions reset
```

CW will emit `extab` + `extabindex` entries for `MyFn` even though the
lib-level cflags say `-Cpp_exceptions off`. splits.txt must include the
extab + extabindex ranges for the TU; configure.py needs no
`extab_padding=...` flag (single-fn auto-emit goes straight to the
`extab` / `extabindex` sections, not `.extab_user` / `.extabindex_user`).

## Caveat

The pragma only matters for fns whose target asm has an extab entry.
For an asm group with mixed extab / no-extab fns, the asm fns without
extab still need the surrounding lib to not auto-emit, so combine with
`#pragma exceptions off` for the no-extab fns (asymmetric mix).

## Reference commit

`orch/batch_text_800a06d0_rand15` — Rand15 at 0x800A06D0.
