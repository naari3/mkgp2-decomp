# Class-1 recipe: batch-4 verification (2026-06-11, batch_promote_phase1_class1batch4)

KartItem_PerFrameStep 0x8004C320 site 0x8004C8CC: u64 family (mask 0x10000000ULL, hi=0), plain if/else recipe over direct bus->flags byte-exact from first build (register-for-register incl. r4 zero-web coalesce). **Ledger: 14/14 u64-family sites across 4 batches.** Fn itself parked at 97.87% on the fp-scratch later-first-use->lower-reg numbering family (NOT class-1; paste-ready C + 91-row residue in docs/drafts/KartItem_PerFrameStep_98pct.handoff.md).

New verified idioms (full detail in the HANDOFF):

1. CW132 stack layout rule: locals sorted size-DESCENDING allocated top-down, ties by decl order (first = higher). Split aggregates to put small scalars at the frame bottom.
2. CW132 never hoists pointer loads above stack stores: target scheduler-looking patterns are SOURCE patterns. 16-float copy 8-deep pipeline reproduced with 8 named temps (t0..t7 load block, then m[i]=ti; ti=mtx[8+i] alternation, then 8 stores). Byte-exact except web numbering.
3. Registerization matrix: plain local array w/ 3 of 16 elements read across a call -> copy deleted, f29-f31 keep values; struct-wrap without address-take does NOT stop SROA of array members; volatile array -> serialized lfs/stfs pairs; escaping-struct member array -> pinned + source-pipelinable.
4. volatile unsigned int scalar pair = target cross-call int snapshot codegen (lwz r5/r0 batch + stw pair); non-volatile struct members serialize, plain locals take callee-saved.
5. volatile Vec3 + cast-stripped struct copy (G.pos = *(Vec3*)&v) blocks whole-object copy-propagation while keeping the canonical word-copy.
6. Escaping Vec3-group struct keeps dead y-overwrite stores AND register forwarding (separate fmuls for the zeroed-member square, no fmadds).
7. 30-label binary-search switch deterministic; source case-body order = memory order.

## fp-scratch NUMBERING family: consolidated target list (Phase 2a input)

Same allocator behavior (target numbers simultaneously-live scratch webs DESCENDING / later-first-use -> lower reg; CW 1.3.2 emits ASCENDING by def order) now blocks 4 fns, all content-identical:

| fn | best % | residue |
|---|---|---|
| ItemEffect_Explosion 0x80051648 | 88.99% | vx/const f3-f4 swap + cascade |
| KartMovement_UpdateBoostVisualBlend 0x80052DBC | 98.88% | t5 temp f0 vs f4, 6 transients |
| KartItem_TickStatusEffectsByFlag 0x80050CF0 | >99% | 23 instrs, 3 web clusters |
| KartItem_PerFrameStep 0x8004C320 | 97.87% | 91 rows, 3 fp regions + 2 sched |

Negative probes accumulated across the 4 fns: decl order (block/fn scope), def/assignment reorder, volatile-free restructure, struct wrap, named const hoists, volatile-cast loads, assignment-in-expression, compound +=, static inline wrap, K&R vs prototyped, exceptions on/off (all codegen-identical), #pragma opt_propagation off. NOT yet tried systematically: compiler-variant sweep + full pragma/-opt suboption sweep with an automated numbering-direction classifier (= the Phase 0 method that solved class 1).
