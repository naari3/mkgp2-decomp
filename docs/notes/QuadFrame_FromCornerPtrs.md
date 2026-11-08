# QuadFrame_FromCornerPtrs

Source: Codex worker c21_u152_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u152: current 93.967155% baseline source is 1084 B versus target 1096 B, same 0xE0 frame and f24..f31 saves. Old source comment incorrectly called it register-only with two extra saves. Target midpoint slots ab=0x50, cd=0x44, ac=0x38, bd=0x2C; current source ac=0x50, ab=0x44, cd=0x38, bd=0x2C. Simply changing construction order worsens to91.60584/1116B. Member-wise return objects: subtraction93.74818, cross93.875916, combined80.00365; vector multiply/add midpoint66.175186. No pool-owner mechanism; singleton function cannot B-split. Next retry should investigate proper normalization ownership/API and temporary lifetimes rather than assuming register-only residue: norm(ab-cd) returns a reference to a temporary whose full expression ends at initialization.
