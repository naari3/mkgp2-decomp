# displaycontext-flush-shared-pool

Source: Codex worker c17_u109_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

DisplayContext_Flush 801DB278: external kDbgColorPalette pointer causes extra initial mr and mr r4,r31 instead of target addi r4,r31,0. Define three file-static typed arrays: 9 RGBA4 u16 colors, four GX descriptor pairs, four GX format records (3 enums + u8 frac). Compiler naturally emits one .rodata base plus offsets 0x14/0x34 and restores 720B text; own 8039FD18-8039FD8C, leave trailing alignment bytes in auto. Text improves 98.888885 to99.833336, EH8/index12/rodata116 exact. Residual count r30/byteoffsetr31 vs target r31/r30; count-before-font declaration and inline indexed entry accessor are both invariant. Remains NonMatching, zero native gain. Final coordinator build SHA-1 OK.
