# grounded-movement-unlock

Source: Codex worker c14_u9_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u9: KartPhysics_GroundedMovement 801EED14 remains singleton NM. Move lateral pointer declaration before pair declaration, assigning it only in nearestKart>=0 body, fixes target pair r26/lateral r25, raising remeasured94.39141 to94.43771 with unchanged source4748B and EH8/index12 scores100/91.66667. Direct explicit if-return singleton accessor is byte-invariant, cached accessor also misses bne-over-li shape. Literal constants improve FP scheduling but full literal conversion shifts offsets and existing postprocess_sdata2 then maps some constants incorrectly; reject reported96.61869. Separate distance/heading/side declarations do not solve saved FP homes. Remaining accessor branches, FP callee webs, constant reload CSE and matrixYaw FMA require new structural evidence; no blind permutations. Source fallback fullDOL SHA1 exact; genuine native gain0.

## c18_u141_20261107
Source: Codex worker c18_u141_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 148 B.

c18_u141 fresh baseline94.43771/4748B. Approved SINGLETON_INSTANCE(g_courseData) fixes old getter polarity,95.35354/4700B. random*magnitude plus named slipYaw product before adding yaw restores multiply order and separate fmuls/fadds,95.37037/4704B. groundedApproach helper with heading/distance output references regresses95.28872, reverted. Residual constant reload CSE, heading/distance/side saved FPR homes, vector/remainder scratch homes and scheduling. EH100/index91.66667. No literals/pools/flags/splits/bridges changed. Single function cannot B-split. Kept NM improvement; coordinator full fallback DOL SHA1 exact; native gain0.
