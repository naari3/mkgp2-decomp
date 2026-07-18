# const-float hoist vs per-site reload conflict in one TU (2026-07-19, TripleBladeRing)

Two functions in the same unit needed OPPOSITE treatments of the same sdata2 literal float (lbl_806D5034):

- Update (straight-line): target hoists the lfs above two u8 stores -> requires `extern const float` (non-const cannot cross ANY store, even u8 stores through typed struct fields; probed both char* casts and typed u8 fields, both block the motion).
- Draw (call loop): target reloads the literal at each call site inside the loop -> const would loop-invariant-hoist it into a callee-saved reg.

Resolution: keep the extern `const float` (per cw132-extern-const-float-hoist.md convention) and defeat the hoist ONLY at the loop uses with `float kv = *(volatile float *)&lbl_806D5034;` immediately before the call. The volatile read stays inside the loop; passing kv for two float args still yields the target `lfs f2 / fmr f3, f2` pattern (single load, one fmr). Verified byte-identical (TripleBladeRing_Draw + _Update both 100%).

Also re-confirmed (SetWorldYaw): compound `x -= k` inside a while body keeps the redundant re-load of the memory lvalue in the loop body (target shape); the explicit `x = x - k` spelling lets CW CSE the body load with the loop-condition load and comes out 1 instruction short per loop.
