# grounded-movement-unlock

Source: Codex worker c14_u9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u9: KartPhysics_GroundedMovement 801EED14 remains singleton NM. Move lateral pointer declaration before pair declaration, assigning it only in nearestKart>=0 body, fixes target pair r26/lateral r25, raising remeasured94.39141 to94.43771 with unchanged source4748B and EH8/index12 scores100/91.66667. Direct explicit if-return singleton accessor is byte-invariant, cached accessor also misses bne-over-li shape. Literal constants improve FP scheduling but full literal conversion shifts offsets and existing postprocess_sdata2 then maps some constants incorrectly; reject reported96.61869. Separate distance/heading/side declarations do not solve saved FP homes. Remaining accessor branches, FP callee webs, constant reload CSE and matrixYaw FMA require new structural evidence; no blind permutations. Source fallback fullDOL SHA1 exact; genuine native gain0.

## c18_u141_20261107
Source: Codex worker c18_u141_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 148 B.

c18_u141 fresh baseline94.43771/4748B. Approved SINGLETON_INSTANCE(g_courseData) fixes old getter polarity,95.35354/4700B. random*magnitude plus named slipYaw product before adding yaw restores multiply order and separate fmuls/fadds,95.37037/4704B. groundedApproach helper with heading/distance output references regresses95.28872, reverted. Residual constant reload CSE, heading/distance/side saved FPR homes, vector/remainder scratch homes and scheduling. EH100/index91.66667. No literals/pools/flags/splits/bridges changed. Single function cannot B-split. Kept NM improvement; coordinator full fallback DOL SHA1 exact; native gain0.

## c19_u28_20261107
Source: Codex worker c19_u28_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u28 fresh95.37037/source4704B improves95.702866 by declaring only TU-local sdata2 float externs const; writable sbss806D1930/193C remain mutable. No new literals/data/bridges/ranges. Return-value groundedAngle regresses95.253365/4716B; independent slip/travel speed locals95.64815/4704B. Both reverted. Remaining heading/distance/side saved FPR homes, constant reload CSE, early zero-copy extra fmr, vector/remainder GPR homes and scheduling. EH100/index91.66667 unchanged. Three hypotheses exhausted; singleton TU cannot B-split. Final coordinator fallback-linked DOL SHA1 exact; native gain0.

## c21_u22_20261108
Source: Codex worker c21_u22_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u22: current-main baseline96.02694/4776B (includes preexisting opt_common_subs off). Explicit GroundedWaypoint* record=candidate+j before component loads raises96.36784/4768B: +408..4A8 segment now exact, candidate r29/count r26 plus +4/+8/+10 loads. static inline groundedTargetSpeed(angle,max,min) restores min-before-max argument evaluation and raises96.377945/4768B. Captured towardZ reused across atan2/distance/side regresses96.11448, reverted. Remaining FP saved homes, first path scratch registers, field reload/store schedules; EH100/index91.66667. Pool803BD920..803BDED4 owned by fn_801ECA14.c outside claim, no merge. One-function TU cannot B-split. Best native draft retained NonMatching; full fallback-linked DOL SHA1 exact; native gain0.

## c21_p47_20261108
Source: Codex worker c21_p47_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p47: baseline 96.377945/4768 B. Explicit currentPath/previousPath locals at four branch sites eliminate four redundant loads under existing opt_common_subs off -> 96.748314/4752 B, EH/index 100/100. Named retainedTurn products preserve float rounding before subtraction/addition and remove inappropriate fnmsubs/fmadds -> 97.30808/4760 B, EH/index 100/91.66667 (same section scores as baseline). Reverse wander product operand form is byte-invariant. Retained best draft NM. Pool OTHER: matched fn_801ECA14.c owns rodata803BD920..803BDED4; no pool/split edits. Full fallback DOL SHA1 exact, native gain0.

## c22_u8_20261109
Source: Codex worker c22_u8_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c22_u8: fresh97.30808/4760B ->97.7298/4756B by reading forward=toward.z AFTER toward.set, reusing it for atan2 and side, and spelling horizontal length as x*x followed by forward*forward+distance. This differs from c21_u22 before-set capture: target +C2C..+C78 vector/atan2 setup is now exact, including fsubs/fmr/stfs f31; side uses retainedf31 without reload, and z*z is the fused term as in target. Existing opt_common_subs off remains inherited, no new pragma. Removing it gives95.698654/4704B; startZ/directionZ loop snapshots give96.8367/4752B and exact extabindex but worse FPR homes; both rejected. Three hypotheses exhausted. EH100/index91.66667 unchanged, no new data. OTHER pool owner fn_801ECA14.c owns803BD920..803BDED4; a contiguous merge through GroundedMovement spans11 TUs/text801ECA14..801EFFA4, extab80016C4C..80016D64/index80028B20..80028B98. No foreign edits. Full coordinator fallback DOL SHA1 exact, source_input false, nativegain0.

## c23_u28_20261109
Source: Codex worker c23_u28_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u28: baseline97.7298/4756B ->97.73485/4756B via groundedHorizontalDistance(x,z) return-value inline, distinct x-square and final length locals. First-square scratch restored, FPR homes remain wrong; sqrt volatile spill moves+c to+8, marginal net score gain only. Splitting first/next waypoint indices is byte-invariant. Follower-path inline argument boundary regresses97.71801, reverted. OTHER pool owner fn_801ECA14.c owns803BD920..803BDED4; coordinator merge spans11TUs/text801ECA14..801EFFA4, EH80016C4C..80016D64/index80028B20..80028B98. Singleton B impossible. No added pragma, config, range or shared-header edits. Final coordinator full build SHA1ea30f3b1 exact; source_inputfalse/nativegain0.

## c25_u8_20261110
Source: Codex worker c25_u8_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1124 B.

c25_u8: baseline97.73485/4756B ->97.73821/4756B via inline-matched-sibling travel tail adapted from matched KartPhysics_UpdateSmoothing, keeping extern constants. Both sqrt spills now match target (+C horizontal, +8 travel). Global value-returning sqrt97.43098/4764B rejected. Exact sibling literals nominal97.90236 add unmapped .sdata2 (24B), rejected; 3.0-only97.73401 adds8B, rejected. EH100/index91.66667 unchanged. Inherited opt_common_subs off unchanged. OTHER pool merge remains coordinator action: ownerfn_801ECA14.c rodata803BD920..803BDED4, contiguous11TU text801ECA14..801EFFA4/EH80016C4C..80016D64/index80028B20..80028B98. Singleton cannot B. Full service SHA1ea30f3b1 exact; source_inputfalse/nativegain0.

## c26_u10_20261110
Source: Codex worker c26_u10_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c26_u10: baseline97.73821/4756B ->98.43687/4756B. Name zero/fullBlend snapshots before path-blend stores and zero before slip-strength stores:98.06566. TU-local const view of inherited .sdata2 floats/doubles (zero,one,angle constants and sqrt doubles) restores constant-load/store schedule:98.43687. All are verified .sdata2 in symbols.txt; no shared header edit. Rule real-definition-type / cse-const-into-local. Steering/slip inline boundary regresses82.85522 and EH, reverted. EH100/index91.66667 unchanged. Residual first-path scratch homes, follower load order, post-loop reload/store order, heading/distance/side FPRs and missing fmr. Pool owner remains fn_801ECA14; no foreign ranges touched. Singleton B impossible. Coordinator full SHA1ea30f3b1 exact; source_inputfalse/nativegain0.

## c27_u12_20261111
Source: Codex worker c27_u12_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c27_u12: baseline98.43687/4756B ->98.463806/4756B by computing pathSide before previousSelectedPath store (stmt-order, pattern3). Post-loop arithmetic/store schedule improves; extra start.z/direction.z loads remain. Horizontal-distance caller-owned output reference is function-byte-invariant; __restrict self regresses96.008415, both reverted. EH100/index91.66667 unchanged; one-function NM cannot B-split. No flags, data, bridges, ranges, shared headers or new pragmas. Coordinator full build exit0/SHA1ea30f3b1 exact; source_inputfalse/nativegain0.
