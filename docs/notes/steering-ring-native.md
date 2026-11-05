# steering-ring-native

Source: Codex worker cxc_u16_e40c0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 744 B.

E4824 native erase-range matches text/extab/index with GC/2.7, end-index helper (identical conditional returns preserve dead compare), normal aliasing, and *--out=*--last. E4544 assign uses four-word const iterators; E4AF4 insert n; E5454 push_back; E5724 push_front. Four NonMatching drafts share length_error cleanup identity mismatch: target retains separate string member pointer while source folds it into enclosing exception+4. Existing Scene_8016219CPrivate.h has a single-pointer ClStr, which does not fit target two-pointer shared string, so private RingShared model used.

## c3_n7_801046c4_20261105
Source: Codex worker c3_n7_801046c4_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Insert n 801E4AF4: a private std::RingString wrapper containing RingShared, constructed by logic_error, preserves independent r24 member base, unlike direct RingShared member. All owned EH PC ranges and native DESTROYMEMBER 0(r24)/DESTROYBASE 0(r23) actions match after destructor/name bridges. end().index-position.index retains target dead capacity compare, and suffix guard is before<count. Remaining iterator/GPR/stack residual prevents native promotion. Independent begin()+n iterator expressions fixed parameter homes but expanded frame 1C0->1F0; rejected.
