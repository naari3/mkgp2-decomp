# itemlaunch-native-retrofit-c15

Source: Codex worker c15_u56_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1112 B.

Item_InitLaunchFromKart 800DA1E4 reaches exact1112B C under unchanged GC/1.3.2 flags by recovering inline ground-bend and local-space-clamp helpers. Vec3_ToYaw returns float; inline heightA reuse emits frsp f0,f1 followed by stfs f1 before fneg, whereas open-expanded C loses that shape or a double prototype adds an unwanted initial frsp. Ground query takes Vec3 by value. Tail helper must use caller-loaded kart snapshot and declare localPosition,transformCopy1,transformCopy2 in target order. Literal0.0f clamp prevents named external zero reuse, restoring compare homes and helper reload. All owned EH exact; Matching source-linked main.elf 800DA1E4/1112B equals target and full DOL SHA-1 OK.

## c18_u45_20261107
Source: Codex worker c18_u45_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 432 B.

c18_u45: standalone Item_BendVelocityByGroundProbe 800DBD48 improves98.14815->100%, text432/EH8/index12 exact. Correct Vec3_ToYaw return is float. A static inline BendInYawFrame(vel,pitch,float *yaw) containing *yaw=Vec3_ToYaw(vel), RotateY(-*yaw), RotateX(pitch), RotateY(*yaw), called with &groundY, reproduces target frsp f0,f1 then stfs original f1 before fneg. Leave ground queries in outer function to retain reverse-order implicit Vec3 argument-copy slots. Factoring entire body instead reaches99.82407 with wrong slots; outer probe/height storage passed to whole helper reaches99.92593 with position-copy slots swapped. This is a different structural lever from c15_u42 direct precision probes; no incompatible angle prototype needed. Matching source-linked final ELF text/EH/index bytes and full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified.
