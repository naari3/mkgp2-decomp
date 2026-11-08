# steering-ring-native

Source: Codex worker cxc_u16_e40c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 744 B.

E4824 native erase-range matches text/extab/index with GC/2.7, end-index helper (identical conditional returns preserve dead compare), normal aliasing, and *--out=*--last. E4544 assign uses four-word const iterators; E4AF4 insert n; E5454 push_back; E5724 push_front. Four NonMatching drafts share length_error cleanup identity mismatch: target retains separate string member pointer while source folds it into enclosing exception+4. Existing Scene_8016219CPrivate.h has a single-pointer ClStr, which does not fit target two-pointer shared string, so private RingShared model used.

## c3_n7_801046c4_20261105
Source: Codex worker c3_n7_801046c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Insert n 801E4AF4: a private std::RingString wrapper containing RingShared, constructed by logic_error, preserves independent r24 member base, unlike direct RingShared member. All owned EH PC ranges and native DESTROYMEMBER 0(r24)/DESTROYBASE 0(r23) actions match after destructor/name bridges. end().index-position.index retains target dead capacity compare, and suffix guard is before<count. Remaining iterator/GPR/stack residual prevents native promotion. Independent begin()+n iterator expressions fixed parameter homes but expanded frame 1C0->1F0; rejected.

## c3_u2_801def94_20261105
Source: Codex worker c3_u2_801def94_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_u2 verified partial: fn_801DEF94 lacked 13 queue/ring definitions despite listing 98 target functions. Adding native drafts restores all 98 definitions and raises object text 77.35281% -> 93.44997% with no primary-function regression. fn_801E0998 matches 100% with sine/fraction/spin/radius FP-local declaration order, compound named angle products, separate compound multiply/add, and explicit lbl_806DA30C spin constant. fn_801E10BC matches 100% when Lerp updates its t parameter in place and the first lateral ratio uses Mul2. dtor_801E2BD0, compiler-emitted QueueBlockMap dtor_801E3200 and fn_801E3260 are text-exact. Entire reversed EH group stays NonMatching; no native gain. Existing postprocess_sdata2.py aligns anonymous constants by instruction offset without the value check described in its docstring: baseline fn_801E0998 spin literal was mapped to pi. Explicit existing constant reference avoids that in this function. No tool code modified.

## c5_s16_anon8021f088_20261105
Source: Codex worker c5_s16_anon8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 392 B.

E4544: existing SteeringRingInsertPrivate RingString wrapper restores independent r25 member base and exact 116-byte EH. A reference-taking inline AssignDistance wrapping by-value RingDistance4 restores all target iterator stack slots. Residual only stw data before/after first last.ring load (98.91304%); combined allocation/copy and restrict forms regress and were reverted.

## c16_u15_20261106
Source: Codex worker c16_u15_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u15 fn_801E5724: existing SteeringRingInsertPrivate.h RingString wrapper restores independent r27 shared member/frame and EH identity. A TU-local const-reference min with two mutable locals (0xffffffffUL/sizeof(int), 0xffffffffUL) replaces artificial volatile RingMax and restores exact target compare/prologue: 732B text +116B EH +12B index all100 after name bridges. Native promotion fails because compiler throw type string emits 55B .data retained (+64B section growth), while original lbl_803BD228 lies in shared .rodata. Explicit placement construction plus __throw suppresses type string but regresses to744B/89.016396; reverted. Final NonMatching fallback DOL SHA1 exact, zero native gain. No padding or tool-code edits.

## c16_u25_20261106
Source: Codex worker c16_u25_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u25 fn_801E5454 push_back: reuse existing SteeringRingInsertPrivate.h RingString and canonical RingMinRef/RingMaxSize from E5724. Fresh87.55 ->98.97222, 720B exact instruction/stack skeleton. Own @128/@130/@131 and standard exception/vtable bridges added. Residual s/exception-capacity r28/r30 exchange (35 rows), EH three base-register bytes only; capacity helper98.77778 regresses. 55B compiler throw type-name .data remains, as documented for push_front. Single function stays NonMatching; full fallback-linked DOL SHA1 exact, zero native gain.

## c17_u113_20261107
Source: Codex worker c17_u113_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 736 B.

c17_u113: fn_801E4544 closes 98.91304% to 100% by TU-local inline int *AssignAllocate(unsigned long n) { return (int *)Alloc(n * sizeof(int)); }. This allocator boundary schedules last.ring load before s->data store after Alloc. Control retaining natural min-reference max_size but direct allocation restores residual. Natural max_size replaces volatile RingMax without instruction regression. Rescue the compiler exception type string with -rostr and own .rodata 803BD228..803BD260; add @129 -> global:lbl_803BD228, @132 -> @etb_800162B0, @133 -> @eti_80028790. Same technique already exists in matched WarpZoneVector_Insert. Text736/EH116/index12/rodata all100; source .rodata is55 bytes with natural one-byte final alignment. Matching source input and actual main.elf fn801E4544/736 plus type string803BD228/55 confirmed. Coordinator full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact. Native gain1 function/736B; no fillers or tool-code edits.

## c18_u168_20261107
Source: Codex worker c18_u168_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u168 fn_801E4AF4: fresh94.865 ->98.53833, exact2400B/EH116/index12. TU-local InsertAdvance(const Iter&,n) makes local copy and returns InsertPlusAssign(copy,n) by reference; use it for lvalue start expressions only, keeping RingAdvance(s->end(),n) by-value. This restores target iterator arithmetic/load-store skeleton, unlike direct local-copy math (2272B) or reference helper at end (2364B). Natural min-reference max_size removes volatile RingMax without regression. Backward-copy const-ref wrapper95.99333/2404B rejected. Remaining whole callee-saved cycle, iterator temporary stack homes, grow prefix index reload/mr. No new pool/bridges/flag changes; single-function NM remains; full fallback DOL SHA1 exact, zero native gain.

## c19_u46_20261107
Source: Codex worker c19_u46_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u46 fn801E4AF4 fresh98.53833 ->98.94666 (report98.96333),2400B/EH116/index12 all unchanged-size,EH/index100. Correct position parameter from const Iter& to by-value Iter (same PPC aggregate-pointer ABI) restores post-Alloc position.index reload,98.863335. Real member method with implicit this gives identical600 instructions/no home change. Raw-pointer fill_n inline helper restores fill q=r5,n=r4 and suffix capacityr4,98.94666. Remaining callee home cycle, iterator stack temp permutation;55B throw type data remains. SingletonNM/noB cut/no native gain; full fallback SHA1 exact. Three distinct hypotheses exhausted.

## c19_u70_20261107
Source: Codex worker c19_u70_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u70: canonical SteeringRingInsertPrivate RingString wrapper reused through new TU-owned SteeringQueueMatchPrivate header improves queue push-front54.503597->62.532375, fill90.54263->98.23256, reserve90.375->99.93056. Typed reserve(SteeringRing*,unsigned long) recovers all GPRs and stack homes; residual only compiler-local throw type-name vs lbl803BD228, already owned by Matching E4544. Iterator range assignment needs by-value iterator conversions plus generic category dispatch in r6: growth72.995125->90.380486, removing original32-byte aggregate templates; still828 vs820B and stack/copy/tag residual. Const queue iterator accessor86.790695->87.25581. ResizeEnd returning through const ref73.92453->91.679245. Move3A4C/4504 behind callers and keep4504 before411C to avoid unintended auto-inlining while preserving both exact wrappers. Native compiler EH is mostly already exact: declare55-entry target order and110 compiler metadata bridges plus std exception/shared destructors.49/55 raw EH records exact; full EH96.587/index99.455. Entire98-function reversed group still blocksB; no flag/range changes, native gain0. Full fallback DOL SHA1exact. Next investigation: nested uninitialized-fill/construct try scopes may explain two missing stw-r1 anchors in fill; not probed beyond this function budget.

## c20_u37_20261108
Source: Codex worker c20_u37_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u37 fn801E4AF4 fresh98.94666 ->99.08833 (report99.105),2400B/EH116/index12. Declare int*p before newCount, assign at original Alloc; growth p/newCount/cap/before become exactr26/r25/r24/r23. Parameter alias invariant; named inplace backward advance96.85333, named return98.91167, const-ref/direct-local-copy end helper97.305 rejected. Remaining parameter home cycle and iterator stack permutation;55B throw type string belongs to MatchingE4544 outside claim. Single function noB cut, no flags/maps/ranges changed. Full coordinator fallback DOL SHA1ea30f3b1 exact; native gain0.
