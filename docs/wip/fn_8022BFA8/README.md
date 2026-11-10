# fn_8022BFA8 (enemy face draw, game/EnmyFaceEffect.cpp) parked 2026-11-10 04:30Z

Parked at the 7512 stop line. main has the 534-line state (d8b9a7c1,
97.6 %). Two further states are saved here as diffs against that commit;
neither is a match yet.

| file | diff lines left | what it is |
|---|---|---|
| `propagation_off_120.diff` | 120 | best: `opt_lifetimes off` + `opt_propagation off` |
| `propagation_on_192.diff` | 192 | `opt_lifetimes off` only, `f = f;` in the plain quad writer |

Apply with `git apply docs/wip/fn_8022BFA8/<file>` on top of d8b9a7c1.

## What is solved (both files)

- uv load order and FPR colours of the quad writers: one variable per value
  (`float f, u, v` reused for the four vertices, `f = p[k].x; f = x + f;`),
  live ranges not split (`#pragma opt_lifetimes off`).
- `overlay` and `anim` are ONE variable (`kind`): it becomes a high-degree
  node and takes r27 before `self`.
- The three vertex transforms are inlines. Their pointer locals are inline
  temps (coloured before every named local); the caller's `draw`, `i`, `j`
  stay named locals and go in by reference (`TransformQuads(draw, quads,
  world, i, j)`), `tex` is a by-value parameter of `DrawPlainQuads` /
  `DrawQuads`.
- `BuildFaceQuads`: top-level locals declared matrix, standard, alternate,
  normal, out, s, a, n, i; `j` and `q` declared inside the outer loop body.
  That gives q r25, n r24, a r23, s r22, out r21 ... matrix r17, j r27, i r29.
- Statement order sets the emitted order of independent `addi`s: for the
  increments the emitted order is the source order rotated left by one
  (`out+=4; src+=4; ++matrix;` is emitted src, matrix, out).

## What is left

1. Overlay loop (`BuildOverlayQuads`): the target has `li r21,0; mr r20,r30;
   mr r19,r21` (offset counter copied from `i`, regalloc_patterns 94). That
   copy needs propagation ON; with `opt_propagation off` we get `mulli`.
   Wanted colours: q r17, p r18, offset temp r19, dstRow r20, i r21, j r22.
2. With propagation ON the quad writers lose `x`/`z` as variables (they are
   CSE temps f41/f58 whatever the declaration says) and x/z come out f4/f3
   instead of f3/f4. Next idea: pass x and z as by-value parameters or keep
   them in the caller inline.
3. Third and fourth `FillFaceUV` (the ones next to `offset.x += offset.x`):
   target rect[1] f4, rect[3] f6, rect[0] f5, factor f3; ours f6/f4/f3/f5.
   The first two expansions match, so the doubling statements probably sit
   at a different place relative to the fill.
4. `DrawCachedQuads`: counter must be coloured before `color` (i r17,
   color r18): done in the diffs, check again after 1-3.
