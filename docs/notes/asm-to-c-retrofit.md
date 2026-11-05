# asm-to-c-retrofit

Source: Codex worker c11_a13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1376 B.

c11_a13: BananaTriple_Dispatch_32to36 800E9934 matches 1376B native C plus 8B EH/12B index and 40B switch table. Canonical objview Item/Vec3 supports all fields; private BananaState begins item+EC. Vec3 by-value call signatures naturally produce target caller copies. Read visible through signed-char lvalue to preserve extsb.; casting canonical unsigned visible to signed char allowed CW to replace the test with cmplwi. Switch table 80421570..80421598 was unsplit and must join this existing TU. Full DOL SHA-1 OK. GXChannel remains original asm after direct/structured-copy/inline-helper hypotheses, best native91.14815%; shared rodata/assertion-base hoisting and GPR differences remain.
