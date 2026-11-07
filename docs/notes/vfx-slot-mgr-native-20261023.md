
## VfxSlotMgr bounded native pass (2026-10-23)
Shutdown 0x800AFA5C/140B matches via typed global-index512-slot array (stride0x1CC), VfxSlot_Release at+0x14, active clear, and unconditional real C++ virtual delete (explicit if adds redundant null branch). Pointer iteration adds r0/mr initialization. Update 0x800AFAE8/496B: existing ScopedTimer single-expression destructor with volatile slot25 reproduces timer tail and owned24B automatic DESTROYLOCAL record (SP8, PC78..148), canonical __dt__11ScopedTimerFv relocation exact. Three attempts: trivial Vec camera95.59677%; native copy-constructor/index array98.6371%; reordered camera parameter boundary/local rotation-first99.01613%. Size496B correct; camera argument/local stack slots and r30/r31 loop identities remain. No further same-axis exploration absent new structural evidence. Independent actual singleton auto groups allow shutdown Matching TU and Update NonMatching TU, preserving140B gain. Weak ScopedTimer dtor adds8B EH/12B index in draft source; not genuine progress.

## c15_u26_20261106
Source: Codex worker c15_u26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c15_u26: nested inline BuildCamera(Vec origin,const Vec& target), called by SetCamera(Vec target,Vec position), reproduces origin SP+40 and matrix argument copies SP+28/SP+34 naturally, improving Update 99.01613 -> 99.145164 (496 B). Residual outer argument copies SP+4C/SP+58 reversed, ToYawPitch setup r5/r3/r4 vs target r3/r4/r5, and loop r30/r31 swap. Value-parameter Update plus trivial Vec worsens to90.21774; retained integer-copy Vec with position-first SetCamera worsens98.66936. No native gain; TU remains NM.

## c17_u84_20261107
Source: Codex worker c17_u84_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u84: Update improves99.145164->99.79032/496B by static inline UpdateSlots(Slot *slot) { int i=0; do { original active/tick/render body; ++i; ++slot; } while(i<512); }. Parameter walker=r30/local counter=r31 gives exact full loop without extra mr. Remaining outer SP+4C/SP+58 copy swap8rows and ToYawPitch setup r5/r3/r4 vs target r3/r4/r5 3rows. Reference-taking outer helper with named snapshots regresses99.3871; pointer-boundary DirectionToRotation is byte-invariant. Best H1 retained, NM stays, singleton cannot split. EH/index unchanged85.71429/66.66667 including appended weak dtor entries; owned payload unchanged. Coordinator fallback-linked DOL SHA1 exact; zero native gain.

## c18_u218_20261107
Source: Codex worker c18_u218_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u218: separate trivial EulerAngles {float x,y,z;} local rotation plus ABI-equivalent Mtx44_FromEulerXYZTrans third value parameter fixes ToYawPitch setup order r5/r3/r4 -> target r3/r4/r5, improving99.79032->99.935486 with unchanged496B primary text and owned EH24/index12. Retained source only. Eight rows remain for outer position/target copies SP4C/SP58 swapped. Out-of-class inline Vec copy ctor, Vec member ToYawPitch wrapper, value-return copying helper, nontrivial by-value Update parameters, and explicit float-pointer Vec construction were invariant and reverted. No singleton/pool opportunity, no split possible. Whole fallback-linked coordinator build SHA-1 exact, zero native gain.

## c19_u193_20261107
Source: Codex worker c19_u193_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 496 B.

c19_u193 unlock: CameraInputs { Vec target; Vec position; } local snapshots position first, then target; BuildCamera consumes its position by value and target by reference. Default assignment gets the desired outer layout but introduces float copies/reloads (89.53226%,508B). Giving Vec copy assignment the same bit-preserving three-word operation as its existing copy constructor produces text496B100%; SP+4C target/SP+58 position now exact. Removing the custom copy ctor alone was invariant99.935486. Owned automatic EH24/index12 and relocations100; aggregate85.71429/66.66667 only appended weak ScopedTimer records discarded at link. Flip Matching, no ranges/bridges/order changes. Full coordinator source-linked build SHA1ea30f3b1 exact, actual main.elf owned text/EH/index bytes exact. +1 native function/+496B.
