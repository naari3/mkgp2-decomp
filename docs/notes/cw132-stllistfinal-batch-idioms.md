# StlList-final batch idioms (2026-06-11, batch_promote_80052508_stllistfinal)

Matched in src/game/auto_ONKARTHIT_block.c (commit 2d8b6fc): StlList_InitEmpty, dtor_80052744, dtor_80052808, dtor_8005285C.

Win idioms:

1. (float)int conversion IS available in the manual-extab mega-bundle TU: plain `(float)t` emits the canonical xoris/lis 0x4330/stw pair/lfd/fsubs sequence and tools/postprocess_sdata2.py renames CW's anonymous sdata2 cookie to lbl_806D2790 (byte-exact, including the li r3,0x78 scratch reuse the manual stack-pair spelling could not reproduce - manual `((u32*)&cvt)[..]` gives fsub+frsp instead of fsubs, 2 instr penalty). CAVEAT: the rename aligns my-side .text reloc offsets against the target object, so while any UPSTREAM fn in the TU has a wrong size the rename silently skips or picks the WRONG symbol (observed `@1104 -> lbl_806D26FC` mis-rename) - only trust it when the TU is size-correct, and expect transient objdiff noise on the fn during iteration.
2. lerp lane shape `inv * t[i] + s * t[i+4]` (fuse-first-addend rule): CW computes the SECOND product (s*t[i+4]) as the fmuls and fuses the first into fmadds, which reproduces the target load schedule (0x14,0x18,0x1c,0x10 row loaded before 0x4,0x8,0xc,0x0). Writing `s*hi + inv*lo` flips the whole load schedule (89%).
3. Owned-pointer deleting dtor pair (dtor_80052808/5C): `if (self) { Free(*(void **)self); if (flag > 0) Free(self); } return self;` - no inner null guard on the payload (contrast dtor_80052200 which guards), flag web r31, self r30.
4. Vtable-demote dtor (dtor_80052744): `*(void **)self = (void *)lbl_803F7690;` with the flag>0 test AFTER the store reproduces the lis/extsh./addi/stw/ble interleave; flag never needs a callee-saved (tested before the call).

Hard-block instances (existing families, new data points):

- StlList_RemoveByValueField 94.51%: class-1 branch-over-branch WITHOUT value materialization (bne unlink / b merge at the erase guard; KartItem_OnKartHit family, first non-li instance) PLUS a callee-saved partition the allocator will not give up: params must sit on top (key=r31,l=r30) above locals; flat decls, nested block scoping and param-to-local copies all leave locals on top (copies coalesce into param webs, decl order ignored). A `res = run` merge local in both branches materializes as a real r0 web (mr r0,r29 in BOTH arms) instead of coalescing - does not defeat the fold and adds 2 instrs.
- StlList_EraseRange 95.23%: prologue load interleave (target lwz between save pairs) - smallrun prologue-load-hoist family; exceptions on/off probe identical, so the interleave is not an EH artifact either. Everything else (all 36 instrs, all reg picks) reproduced.
- StlList_InsertBefore: **exceptions-on EH scaffolding WITHOUT `bl __unexpected`** - FP prologue + back-chain epilogue + dead `bl MemoryManager_TimedFree` cleanup island + EH state store `stw r1,0x24(r31)`. The documented precan grep (bl __unexpected) misses this; add FP-prologue (`mr rX, r1` right after the callee saves) to the 0-probe skip check.
- KartMovement_UpdateBoostVisualBlend 98.88%: scratch-fp tie-break cascade (first table temp f0 vs f4), ItemEffect_Explosion family; 2 source probes did not move the pick.
