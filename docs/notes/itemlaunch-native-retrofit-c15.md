# itemlaunch-native-retrofit-c15

Source: Codex worker c15_u56_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1112 B.

Item_InitLaunchFromKart 800DA1E4 reaches exact1112B C under unchanged GC/1.3.2 flags by recovering inline ground-bend and local-space-clamp helpers. Vec3_ToYaw returns float; inline heightA reuse emits frsp f0,f1 followed by stfs f1 before fneg, whereas open-expanded C loses that shape or a double prototype adds an unwanted initial frsp. Ground query takes Vec3 by value. Tail helper must use caller-loaded kart snapshot and declare localPosition,transformCopy1,transformCopy2 in target order. Literal0.0f clamp prevents named external zero reuse, restoring compare homes and helper reload. All owned EH exact; Matching source-linked main.elf 800DA1E4/1112B equals target and full DOL SHA-1 OK.
