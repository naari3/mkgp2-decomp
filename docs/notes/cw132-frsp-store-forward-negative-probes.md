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

## 訂正 (2026-06-11, batch_research_frsp_phase2b)

上の結論「plain C から到達不能 / 原文は C++ reference semantics の可能性」は **否定 (OVERTURNED)**。
copy block を **for-loop (variable-index store)** で書くと CW front-end forwarding を逃れ、
-O4,p の full unroll 後に late pass が constant-index read-back を `frsp fN, fM` として解決する —
target 形が plain C で再現する。C++ 仮説は原因として negative (10 form 全滅、-lang=c++ は中立)。
本 ledger の個々の negative 観察 (probe 1-6) 自体は全て有効のまま (再 probe で再現確認済み)。
recipe・37-form matrix・mechanism は `cw132-frsp-storeforward-phase2b-research.md` を参照。
precan の指示は「park」から「loop-copy recipe 適用 (frsp/reload partition に 1-2 build 予算)」に変更。
