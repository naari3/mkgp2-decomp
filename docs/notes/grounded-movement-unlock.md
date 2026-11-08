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
