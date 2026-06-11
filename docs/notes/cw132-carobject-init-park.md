# CarObject_Init 0x8004E618 promote attempt: 98.23% park (2026-06-11, batch_promote_carobject_init)

14 builds, asm body restored (build green). Best state 98.23% / 28 diff rows of 498 insns,
sizes 1976 vs target 1980 (one structural -1 insn at the WarpAutoRun site). Paste-ready full
diff in the batch HANDOFF appendix (docs/drafts/CarObject_Init_98pct.handoff.md).

## Confirmed transfers (matched on first/second build, zero residue in their regions)
- ScopedTimer Phase 2d recipe transfers as-is to the sp+0x14/0x18 flavor: volatile-id ctor
  struct + one-expression dtor tail matched byte-exact inside a 0x7BC fn on build 1.
- void*-t / uint-t null idiom (`t = g; if (t != g) {} else if (t == 0) t = 0;`) works for
  `unsigned int` globals (g_carObjectList x2, lbl_806D10A0) with casts only at use sites.
- class-1 style flag (`b = 0; if (c1 && c2 && c3) b = 1; self->f108 = b != 0;`) coalesces with
  the member-store zero/one const webs as predicted (li r5,0 shared / mr r5,r3 from const-1 web).

## New verified levers (facts)
- volatile aux-pointer hoist `x = *(void * volatile *)&self->field;` before a call whose later
  arg contains another call: forces the lwz to statement position into a callee-saved reg
  (plain spelling gets copy-propagated and reloads AFTER the inner call). Verified x3
  (soundCtrl before GetKartParamBlock, movement before GetKartStartSlot, camera38 load order
  in the FadeTransit arg block).
- u8-typed callee prototype args remove clrlwi when the source is a u8 param (16.9 inverse):
  KartAudioChannel_Init(r5/r6), PlayCamera_Init(r8), KartEffectFadeTransit_Init(r7).
- Inline-init through a may-alias pointer (tbl/sec blocks): preload self-fields into locals
  BEFORE the first store through the new object, else stores serialize the loads
  (lwz/stw ping-pong on one scratch). Preloads reproduce the batched r5/r6/r7 load head.
- Long-range addi CSE: `(char *)self + 0xc` at fn head (base ctor arg) + at the dispatcher
  store got CSE'd into an extra callee-saved reg (stmw r22 cascade). Fix: second site as
  `char *disp = (char *)self; if (self != 0) disp += 0xc;` - the += on a copy is not
  value-numbered with the original addi; target cmplwi/mr r0/addi r0 shape reproduced.
- `(int)g_gameMode == 1` cast needed for cmpwi (unsigned global gets cmplwi).
- Stack locals: 4-byte locals are laid out in REVERSE declaration order (last declared at the
  lowest offset); the 8-byte tm struct (declared last) sits above them. To get
  itRet@0x8/pos@0xc/val@0x10/tm@0x14, declare val, pos, itRet, tm.
- Double same-slot vtable store with interleaved global store: source order
  `m->vt = A; g_list = m; m->vt = B;` reproduces target store order (no DSE).
- Prototype int/float interleave moves scheduler emission of arg loads: moving the int
  isPlayer arg after the floats in TornadoEffect_Ctor moved the lfs f2 emission ahead of the
  lbz (2-row residual swap of lwz r6 / li r4 remains).
- Struct-return call via explicit out-param: StlList_InsertBefore (iterator return) callable
  from C as `asm void StlList_InsertBefore(Iter *ret, StlList *l, Iter *pos, void **val)` -
  retyping the asm fn signature is codegen-neutral and gives the addi r3,r1,8 hidden-ret shape.

## New structural blocker (precan class): new-expr guard with non-trivial pre-ctor cond
Site shape: `p = AllocTagged(...); if (p) { <flag cond, ~8 insns>; p = Ctor(p, flag != 0); }
self->f = p;`. Target joins the result in r0: `mr. r0, r3 ... bl ctor; mr r0, r3; L: stw r0`
(CW new-expr temp). CW 1.3.2 C with ANY spelling keeps the join in r3 (`cmpwi/cmplwi r3,0`,
no copies, ONE INSN SHORTER -> size mismatch, not parkable in place). Probed: 1-var, 2-var
copy (p=q), assign-in-cond, shared int w (flag+result one var, Ghidra-suggested), explicit
post-call copy, test-on-w (flips cmplwi->cmpwi, confirming the original tested an int temp),
static-inline helper for the flag. All copy-propagated. The 6 sibling sites with TRIVIAL
guard bodies reproduce the target mr.-r0 form from plain C - the blocker triggers only when
extra cond code sits between the test and the ctor call. Precan: if a guarded-ctor site has
non-trivial code before the ctor call AND the target uses the mr.-r0 join, expect -1 insn
in C; park or solve at binary level.
Side-effect: routing the flag through a static inline helper broke the OTHER site's flag
coalescing (member-init li r5,0 web) -> keep one named u8 flag var used by both sites.

## Register-web tie-break family (park reason)
Two interlocked web families: A={audio ch, movement, movement-reload}=r26,
B={sound-reload, driver, camera}=r25 in target. Merging B into one C var locks all of B
(and mov/mvL) correctly, but the ch web then flips r25<->r26 depending on UNRELATED
downstream variable binding (matrix: all-distinct -> ch ok / drv+cam wrong; A+B merged ->
only ch wrong; partial merges -> other permutations). blk/sub (target r27/r23, mine r29/r27)
and mgr (=sub home in both) never matched across decl-order, block-scope, and merge probes.
Source-closed in the same sense as the fp-numbering family; lever discovery would
self-correct ch/blk/sub/mgr (plus 11 rows of lis/addi scheduling that follow mgr's home).
