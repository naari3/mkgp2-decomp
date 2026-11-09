# HANDOFF batch_promote_80052508_stllistfinal

Mega-bundle TU (src/game/auto_ONKARTHIT_block.c) final 8 fns, address order
0x80052508..0x80052F20. 4 matched, 3 parked (asm_fn kept, paste-ready C below),
1 skipped (EH scaffolding). SHA-1 OK, no regressions (CarObject_Init 98.18% /
ItemEffect_SelectAndDispatch 99.38% are the known cosmetic artifacts).

```json
{
  "batch_id": "batch_promote_80052508_stllistfinal",
  "sub_summary": "mega-bundle final 8: InitEmpty + 3 dtors matched; RemoveByValueField/EraseRange/UpdateBoostVisualBlend parked 94-99% (class-1 / prologue-load-interleave / fp tie-break); InsertBefore skipped (EH scaffolding)",

  "results": [
    {
      "addr": "0x80052508",
      "name": "StlList_RemoveByValueField",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 94.51% C (4 probes). Two blockers: (1) class-1 branch-over-branch at the erase-range guard (target cmplw;bne unlink;b merge - CW folds every form to beq merge; a res-merge local materializes as a real r0 web instead of coalescing, so the res trick does NOT defeat the fold); (2) callee-saved group partition: target ranks params on top (key=r31,l=r30) above locals (end=r29,cur=r28,run=r27), CW puts locals on top under flat decls, block-scoped decls, AND param-to-local copies (copies coalesce into the param webs, decl order ignored). Body otherwise instruction-identical. Paste-ready C appendix A."
    },
    {
      "addr": "0x800525D4",
      "name": "StlList_EraseRange",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 95.23% C (2 probes). Single blocker: target slots lwz r5,0x0(r5) (first=*beg) between the r30 and r29 callee-save pairs; CW 1.3.2 never schedules a load above remaining callee-save stores (smallrun prologue-load-hoist family). #pragma exceptions on probe produced identical body -> not approach-B class. All 36 body instructions AND all register picks match. Paste-ready C appendix B."
    },
    {
      "addr": "0x80052684",
      "name": "StlList_InsertBefore",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "skipped, 0 probes: -Cpp_exceptions on EH scaffolding class without bl __unexpected - FP prologue mr r31,r1, back-chain epilogue, EH state store stw r1,0x24(r31), dead cleanup island bl MemoryManager_TimedFree behind a b (frees the Alloc'd node if the obj copy throws). Approach B cannot emit this; approach A excluded by 14.1 mix rule. The precan grep for bl __unexpected misses this fn - FP prologue (mr rX,r1 + back-chain epilogue) must be checked too."
    },
    {
      "addr": "0x8005272C",
      "name": "StlList_InitEmpty",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first try. count=0 store then sentinel next/prev self-links via (StlListNode *)&l->head cast."
    },
    {
      "addr": "0x80052744",
      "name": "dtor_80052744",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first try. Single-guard deleting dtor with vtable demote to lbl_803F7690 (CarObjectManager base subobject); flag stays in r4 (tested before the call)."
    },
    {
      "addr": "0x80052808",
      "name": "dtor_80052808",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first try. Owned-pointer holder dtor: unconditional MemoryManager_TimedFree(*(void **)self) then flag>0 self free; flag lives in r31 across the call."
    },
    {
      "addr": "0x8005285C",
      "name": "dtor_8005285C",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first try. Byte-identical sibling of dtor_80052808."
    },
    {
      "addr": "0x80052DBC",
      "name": "KartMovement_UpdateBoostVisualBlend",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 98.88% C (3 probes). Scratch-fp tie-break cascade in the lerp block: target gives the first table temp t[5] f0, CW picks f4, five transient regs cascade; schedule and instruction content fully identical, named webs sat=f1/one=f8/s=f9/inv=f10 all match. Probes: lane addend order swap (s-first regresses load schedule to 89%), one-local elimination (zero effect). ItemEffect_Explosion 88.99% family. Win inside the park: (float)t int-to-float DOES work in this manual-extab TU - CW emits the canonical xoris/0x4330 sequence with an anonymous sdata2 cookie and tools/postprocess_sdata2.py renames it to lbl_806D2790 (verified byte-exact vs target incl. li r3,0x78 scheduling). Caveat: the rename aligns by .text reloc offset against the target object, so it silently fails or MIS-renames while upstream fns in the TU have wrong sizes - only trust it when the whole TU is size-correct. Paste-ready C appendix C."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "rename": [] },

  "docs_notes": [
    {
      "path": "docs/notes/cw132-stllistfinal-batch-idioms.md",
      "content": "# StlList-final batch idioms (2026-06-11, batch_promote_80052508_stllistfinal)\n\nMatched in src/game/auto_ONKARTHIT_block.c (commit 2d8b6fc): StlList_InitEmpty, dtor_80052744, dtor_80052808, dtor_8005285C.\n\nWin idioms:\n\n1. (float)int conversion IS available in the manual-extab mega-bundle TU: plain `(float)t` emits the canonical xoris/lis 0x4330/stw pair/lfd/fsubs sequence and tools/postprocess_sdata2.py renames CW's anonymous sdata2 cookie to lbl_806D2790 (byte-exact, including the li r3,0x78 scratch reuse the manual stack-pair spelling could not reproduce - manual `((u32*)&cvt)[..]` gives fsub+frsp instead of fsubs, 2 instr penalty). CAVEAT: the rename aligns my-side .text reloc offsets against the target object, so while any UPSTREAM fn in the TU has a wrong size the rename silently skips or picks the WRONG symbol (observed `@1104 -> lbl_806D26FC` mis-rename) - only trust it when the TU is size-correct, and expect transient objdiff noise on the fn during iteration.\n2. lerp lane shape `inv * t[i] + s * t[i+4]` (fuse-first-addend rule): CW computes the SECOND product (s*t[i+4]) as the fmuls and fuses the first into fmadds, which reproduces the target load schedule (0x14,0x18,0x1c,0x10 row loaded before 0x4,0x8,0xc,0x0). Writing `s*hi + inv*lo` flips the whole load schedule (89%).\n3. Owned-pointer deleting dtor pair (dtor_80052808/5C): `if (self) { Free(*(void **)self); if (flag > 0) Free(self); } return self;` - no inner null guard on the payload (contrast dtor_80052200 which guards), flag web r31, self r30.\n4. Vtable-demote dtor (dtor_80052744): `*(void **)self = (void *)lbl_803F7690;` with the flag>0 test AFTER the store reproduces the lis/extsh./addi/stw/ble interleave; flag never needs a callee-saved (tested before the call).\n\nHard-block instances (existing families, new data points):\n\n- StlList_RemoveByValueField 94.51%: class-1 branch-over-branch WITHOUT value materialization (bne unlink / b merge at the erase guard; KartItem_OnKartHit family, first non-li instance) PLUS a callee-saved partition the allocator will not give up: params must sit on top (key=r31,l=r30) above locals; flat decls, nested block scoping and param-to-local copies all leave locals on top (copies coalesce into param webs, decl order ignored). A `res = run` merge local in both branches materializes as a real r0 web (mr r0,r29 in BOTH arms) instead of coalescing - does not defeat the fold and adds 2 instrs.\n- StlList_EraseRange 95.23%: prologue load interleave (target lwz between save pairs) - smallrun prologue-load-hoist family; exceptions on/off probe identical, so the interleave is not an EH artifact either. Everything else (all 36 instrs, all reg picks) reproduced.\n- StlList_InsertBefore: exceptions-on EH scaffolding WITHOUT `bl __unexpected` - FP prologue + back-chain epilogue + dead `bl MemoryManager_TimedFree` cleanup island + EH state store `stw r1,0x24(r31)`. The documented precan grep (bl __unexpected) misses this; add FP-prologue (mr rX,r1 right after the saves) to the 0-probe skip check.\n- KartMovement_UpdateBoostVisualBlend 98.88%: scratch-fp tie-break cascade (first table temp f0 vs f4), ItemEffect_Explosion family; 2 source probes did not move the pick.\n"
    }
  ],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": null,
  "user_attention": null
}
```

Note on funcs_matched_delta: asm_fn bodies in this TU already count as matched in
dtk PROGRESS (397/7614 both before and after this batch, verified by stash
rebuild), so promotes inside the bundle do not move the counter. The decomp gain
is 4 fns of real C replacing inline asm.

## Appendix A: StlList_RemoveByValueField 94.51% paste-ready C

Drop-in for the asm body (forward decl becomes
`void StlList_RemoveByValueField(StlList *l, StlListValRef *key);`).
StlListValRef typedef is already in the TU. Blockers: see results notes.

```c
#pragma exceptions off
/* erase every node whose obj equals key->val (consecutive runs unlinked and
 * freed in one splice); list sentinel is the head/tail pair embedded at l+4 */
void StlList_RemoveByValueField(StlList *l, StlListValRef *key) { /* 0x80052508 size:0xCC */
    StlListNode *end;
    StlListNode *cur;
    StlListNode *run;
    end = (StlListNode *)&l->head;
    cur = l->tail;
    while (cur != end) {
        SweepCarObj *v;
        if (cur->obj == (v = key->val)) {
            run = cur->next;
            while (run != end) {
                if (run->obj != v) {
                    break;
                }
                run = run->next;
            }
            if (cur == run) {
            } else {
                StlListNode *last = run->prev;
                cur->prev->next = last->next;
                last->next->prev = cur->prev;
                while (cur != run) {
                    StlListNode *n = cur;
                    cur = cur->next;
                    MemoryManager_TimedFree(n);
                    l->count -= 1;
                }
            }
            cur = run;
            if (cur == end) {
                break;
            }
        }
        cur = cur->next;
    }
}
#pragma exceptions reset
```

Residual diff vs target: `beq merge` instead of `bne unlink; b merge` (1 instr
short, everything downstream shifts), and callee-saved permutation
(mine l=r27,key=r28,end=r31,cur=r30,run=r29 / target key=r31,l=r30,end=r29,
cur=r28,run=r27). The inline-erase-helper variant (static inline
EraseRangeInl(l,first,last) returning last) is WORSE (92.55%): the inline first
param gets its own callee-saved web (uncoalesced mr r31,r5).

## Appendix B: StlList_EraseRange 95.23% paste-ready C

Drop-in for the asm body (forward decl becomes
`void StlList_EraseRange(StlListNode **ret, StlList *l, StlListNode **beg, StlListNode **end);`
- callers are asm, no other change needed).

```c
#pragma exceptions off
/* std::list erase(first, last): unlink the whole range, then free node by node */
void StlList_EraseRange(StlListNode **ret, StlList *l, StlListNode **beg, StlListNode **end) { /* 0x800525D4 size:0xB0 */
    StlListNode *first;
    StlListNode *e;
    if ((first = *beg) == (e = *end)) {
        *ret = e;
    } else {
        StlListNode *last = e->prev;
        StlListNode *n;
        first->prev->next = last->next;
        last->next->prev = first->prev;
        while ((n = *beg) != *end) {
            *beg = n->next;
            MemoryManager_TimedFree(n);
            l->count -= 1;
        }
        *ret = *end;
    }
}
#pragma exceptions reset
```

Residual diff vs target: only the position of `lwz r5, 0x0(r5)` - target has it
between the r30 and r29 save pairs, CW emits it after all four pairs. Plain
decl-init form and condition-assign form produce identical output.

## Appendix C: KartMovement_UpdateBoostVisualBlend 98.88% paste-ready C

Drop-in for the asm body (forward decl becomes the typed signature below).
BoostTicksView/BoostBlendView typedefs and the float/double extern retypes
(lbl_806D1080/1084 float, lbl_806D2744/2778/27F0/27F4 const float,
lbl_806D2790 const double, lbl_802EBE14 const float[]) are already in the TU.

```c
#pragma exceptions off
/* lerp the boost visual color (m+0x2e4..0x2ec) and out scalar between the two
 * lbl_802EBE14 table rows by remaining boost ticks; t<=0 path decays via the
 * 0x78-frame counter, t>0 path re-arms it and publishes sat/s to sda globals */
void KartMovement_UpdateBoostVisualBlend(BoostTicksView *self, BoostBlendView *m, float *out, void *unused4, int *counter) { /* 0x80052DBC size:0x164 */
    int t = self->boostTicks;
    if (t <= 0) {
        float z = lbl_806D26EC;
        int n;
        lbl_806D1080 = z;
        lbl_806D1084 = z;
        n = *counter;
        if (n > 0) {
            *counter = n - 1;
            m->blendR = lbl_802EBE14[1];
            m->blendG = lbl_802EBE14[2];
            m->blendB = lbl_802EBE14[3];
            m->weight2c = lbl_806D26FC;
            *out = lbl_802EBE14[0];
        } else {
            m->blendR = z;
            m->blendG = z;
            m->blendB = lbl_806D27F0;
            m->weight2c = lbl_806D2778;
            *out = lbl_806D27F4;
        }
    } else {
        float blend;
        float sat;
        float one;
        float s;
        float inv;
        *counter = 0x78;
        blend = (float)t - lbl_806D26FC;
        sat = Saturate_Double(blend, lbl_806D26EC, lbl_806D2744);
        one = lbl_806D26FC;
        s = sat * lbl_806D2700;
        inv = one - s;
        m->blendR = inv * lbl_802EBE14[1] + s * lbl_802EBE14[5];
        m->blendG = inv * lbl_802EBE14[2] + s * lbl_802EBE14[6];
        m->blendB = inv * lbl_802EBE14[3] + s * lbl_802EBE14[7];
        m->weight2c = one;
        *out = inv * lbl_802EBE14[0] + s * lbl_802EBE14[4];
        lbl_806D1080 = sat;
        lbl_806D1084 = s;
    }
}
#pragma exceptions reset
```

The t<=0 branch, itof block, Saturate call and the GPR side are byte-exact.
Residual diff: 6 transient fp regs in the lerp block (t5 temp f4 vs target f0,
cascading); zero schedule or content diff.
