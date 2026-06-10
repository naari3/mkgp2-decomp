# SweepBitset batch idioms (2026-06-10, batch_promote_80051dec_sweepbitset)

Matched in src/game/auto_ONKARTHIT_block.c (commit d02557e): dtor_80052200, Bitset_TestBit, Bitset_SetBit, Bitset_MaxSize, dtor_800524CC.

Win idioms:

1. volatile-field proxy pair (NEW, answer to the inlined vector<bool>::reference dead ctor stores): `typedef struct { Bitset * volatile b; volatile unsigned long i; } BitsetRef;` + per-site `ref.b = p; ref.i = idx;` immediately before the direct Bitset_SetBit(p, idx, v) call reproduces the dead {ptr,idx} stack-pair stores the original C++ proxy ctor leaves behind. Plain struct stores (even read back through a static inline that forwards them into the call) are fully DSE'd. The volatile stores read the HOME register; one target site stores the latch-scheduled arg copy (stw r4) instead - 1-instr residue, no C lever found (a plain copy local gets copy-propagated).
2. Triple `addic. r0,rX,0x4; beq` guard chain (CarObjectManager_Dtor) REPRODUCES from nested static inline list-dtor helpers each re-guarding `if (l)` on the member-pointer param: dtor->clear->erase 3 levels deep, inlined to 3 recomputed addic. tests. Contrast WarpDashMgr_Cleanup (sec 14.2) where literal same-variable `if (x) if (x)` was deduped - passing the address through an inline PARAMETER at each level defeats the dedup.
3. Bitset_SetBit decl-order: the word-index local (w = idx >> 5) must be declared BEFORE the mask local; then srwi schedules between li r0,1 and slw while r0/r5 are busy -> w=r6 (target). mask-first decl gives w=r0 emitted after slw.
4. fn_802D6618 scratch out-vec is float[4] not Vec3 (slot layout: 0x74/0x4c with 4-byte tails at 0x80/0x58 in the sweep frame).
5. Vec3 fill statement order (extends effectsrun idiom 5): `half = cfg->half; half.x/y/z = K*scr[i]; center = cfg->center; center.x/y/z = mt[12..14];` (copy then fill per vec) locks products to f3/f2/f0 with K=f4 and keeps the dead 12-byte blob copies in target store order. Interleaving the two copies first (copyA, copyB, fillA, fillB) shifts the whole fp pool (f5/f4) and store schedule.
6. Adjustor thunks (`subi r3; b target`) are not expressible in C: CW 1.3.2 never emits sibling tail calls, probe gives stwu/mflr + bl + epilogue. Keep as asm_fn permanently.
7. In-place asm signature retype scales further: Bitset_Init / KartItem_Dtor / StlList_EraseRange retyped so promoted C can call them, bodies untouched, all stay 100%.

Hard-block instances (existing families, new data points):

- CarObjectManager_RunKartKartCollisionSweep 98.95%: 6-web callee-saved PERMUTATION with two webs (cfg = blob base ptr, i = outer counter) PINNED to r31/r30 across all decl orders and block scoping; remaining 4 webs follow decl order descending below them. Allocator intrinsic ranking not controllable from source (ProcessWarpAndDash family). Routing deep-site &bs refs through the cached ptr does NOT remat (CW keeps mr from the callee-saved) - made it worse (96%).
- CarObjectManager_Dtor 99.76%: single scratch-web tie-break (end-iterator value target r7 vs CW r0). beg-first assignment order or comma-arg materialization churns the whole schedule (89%); end-first always picks r0.
- Bitset_Init 81%: approach-B exceptions-off class (HandleObstacleHit family). The original -Cpp_exceptions on compile pins the exception object pointer webs (r28=&e, r27=&e.str, stmw r27); with #pragma exceptions off CW remats both to sp-relative addi and drops to stw r28-r31 saves. ep->vt vs e.vt spelling makes zero difference (identical output both probes). Unlockable only by TU-level approach-A switch (impossible here: manual-extab asm fns precede it in address order, sec 14.1 mix rule). Positive finding: 3 dead vtable stores DO survive plain C; throw-inline structure fully decoded.
