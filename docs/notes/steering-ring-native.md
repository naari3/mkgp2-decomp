# steering-ring-native

Source: Codex worker cxc_u16_e40c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 744 B.

E4824 native erase-range matches text/extab/index with GC/2.7, end-index helper (identical conditional returns preserve dead compare), normal aliasing, and *--out=*--last. E4544 assign uses four-word const iterators; E4AF4 insert n; E5454 push_back; E5724 push_front. Four NonMatching drafts share length_error cleanup identity mismatch: target retains separate string member pointer while source folds it into enclosing exception+4. Existing Scene_8016219CPrivate.h has a single-pointer ClStr, which does not fit target two-pointer shared string, so private RingShared model used.

## c3_n7_801046c4_20261105
Source: Codex worker c3_n7_801046c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Insert n 801E4AF4: a private std::RingString wrapper containing RingShared, constructed by logic_error, preserves independent r24 member base, unlike direct RingShared member. All owned EH PC ranges and native DESTROYMEMBER 0(r24)/DESTROYBASE 0(r23) actions match after destructor/name bridges. end().index-position.index retains target dead capacity compare, and suffix guard is before<count. Remaining iterator/GPR/stack residual prevents native promotion. Independent begin()+n iterator expressions fixed parameter homes but expanded frame 1C0->1F0; rejected.

## c3_u2_801def94_20261105
Source: Codex worker c3_u2_801def94_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c3_u2 verified partial: fn_801DEF94 lacked 13 queue/ring definitions despite listing 98 target functions. Adding native drafts restores all 98 definitions and raises object text 77.35281% -> 93.44997% with no primary-function regression. fn_801E0998 matches 100% with sine/fraction/spin/radius FP-local declaration order, compound named angle products, separate compound multiply/add, and explicit lbl_806DA30C spin constant. fn_801E10BC matches 100% when Lerp updates its t parameter in place and the first lateral ratio uses Mul2. dtor_801E2BD0, compiler-emitted QueueBlockMap dtor_801E3200 and fn_801E3260 are text-exact. Entire reversed EH group stays NonMatching; no native gain. Existing postprocess_sdata2.py aligns anonymous constants by instruction offset without the value check described in its docstring: baseline fn_801E0998 spin literal was mapped to pi. Explicit existing constant reference avoids that in this function. No tool code modified.
