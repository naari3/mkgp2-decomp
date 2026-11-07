# normal3d-scale-native-draft

Source: Codex worker c17_u32_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 19 fn / 5732 B.

c17_u32: Normal3DScale 80033918 draft was disabled with #if 0 (report 0). Reactivating yields99.27327%; int HasDObj with explicit conditional return0/return1, tested as if(HasDObj(node)), plus cursor-before-index animation-loop updates restore cntlzw/srwi. and exact1332B primary size, reaching99.8048%. Remaining11 instructions are self Request cursor/count r31/r28 vs targetr28/r31, and final Animate count/cursor r27/r30 vs targetr30/r27. Scalar-parameter Request+AnimateAll wrapper99.42943 and inline GetCount accessor99.3994 regress; reverted. All22 owned extab words match, extra weak timer EH remains. Singleton staysNonMatching; fallback main.elf input, full DOL SHA1 exact, zero native gain.
