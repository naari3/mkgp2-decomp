# CW 1.3.2 frsp store-forward interleave: negative probe ledger (2026-06-10, batch_promote_80050410_dispatchpair)

Target idiom (ItemEffect_Dispatch 0x80050410 kind14 branch, same family as KartItem_OnKartHit sec 14.2 row '16-float copy block frsp store-forward interleave'): a 22-float stack scratch block { dir[3] @+0x8; d[3] @+0x14; mtx[16] @+0x20 } where all 16 matrix copies are stfs'd RAW, while the 5 values consumed by the dot product (m0, m1, m12, m13, m14) appear as SEPARATE frsp-copies of the load registers, plus exactly one real stack reload (m2, register evicted). CW-built code, so some source form produces it - but none found:

1. memberwise float copies + read-backs: copy-prop rewrites reads to the original loads, then DSE deletes the whole block (frame shrinks 0xa0 -> 0x30).
2. struct block-assignment (s.mtx = *(Mtx16S *)mov->transform): copy RETAINED but emitted as integer lwz/stw pairs, reads become stw+lfs same-slot pairs. Useful fact: block copies survive DCE.
3. volatile struct + plain member stores (store order = source order) + assignment-expression values for the computed uses: all 22 stores reproduce at exact offsets INCLUDING the m2 store+reload, but the assignment-expression value is the RAW register - no frsp. Best result (86.3%).
4. (float)(double)x on an lfs-derived single: folded to nothing (CW tracks f32-roundedness through cast chains).
5. static inline helper with float params (hoping for param-copy rounding at the inline boundary): params bound to the raw values, no frsp.
6. read-backs through a non-volatile alias pointer into the volatile object: no frsp, and fp pressure exploded (f26-f31 saves) - strictly worse.

Conclusion: CW 1.3.2 -O4,p provably tracks single-precision roundedness of lfs-derived values and elides frsp in every reachable C path probed (n=6 incl. the sec 14.2 untried 'assignment-expression copy' salvage, now falsified). The frsp copies in target likely come from a compiler state we cannot reach from plain C (possibly C++ reference/aliasing semantics in the original). Precan: a block of raw lfs+stfs matrix copies with interleaved frsp fN,fM where fM is itself an lfs result marks this class - park as asm_fn after the volatile-block form (probe 3) is verified, do not chase frsp.

Positive salvage from the same batch: the volatile scratch struct + source-order member stores is a reliable way to materialize a fully dead spill block at exact offsets (extends strpcbrun idiom 3 from Vec3 to 22 floats), including a mid-block volatile read-back reload.

Note: the `(float)(double)` frsp-forcing idiom from CarObject_MainUpdate (works on COMPUTED doubles being narrowed) does NOT apply here - the values are lfs-derived singles, already known-rounded.
