# kartdriver-joint-matrix

Source: Codex worker c11_a26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2220 B.

KartDriver_GetJointByIdx 80040E9C (2220 B) matches natural C using ordered if returns, nullable JointMatrix wrapper, and the HSD_JObjMtxIsDirty/SetupMatrix/GetMtxPtr inline nesting also used by AnimState_UpdateEquipped. Index order is 0..9,12..16,10,11; index 16 additionally checks its pointer before entering the nullable helper. Joint slots start at +E8, skip +108 for index 8; matrix begins at JObj+44. pragma exceptions on/reset emits exact 8-byte extab and 12-byte extabindex. First approach matched 100%; coordinator build service preserved target SHA-1.
