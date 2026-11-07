# displaycontext-flush-shared-pool

Source: Codex worker c17_u109_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

DisplayContext_Flush 801DB278: external kDbgColorPalette pointer causes extra initial mr and mr r4,r31 instead of target addi r4,r31,0. Define three file-static typed arrays: 9 RGBA4 u16 colors, four GX descriptor pairs, four GX format records (3 enums + u8 frac). Compiler naturally emits one .rodata base plus offsets 0x14/0x34 and restores 720B text; own 8039FD18-8039FD8C, leave trailing alignment bytes in auto. Text improves 98.888885 to99.833336, EH8/index12/rodata116 exact. Residual count r30/byteoffsetr31 vs target r31/r30; count-before-font declaration and inline indexed entry accessor are both invariant. Remains NonMatching, zero native gain. Final coordinator build SHA-1 OK.

## c18_u189_20261107
Source: Codex worker c18_u189_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1552 B.

c18_u189: Starting c17 pool-owning draft 99.833336/720B had count r30 versus target r31, strength-reduced byteoffset r31 versus target r30. Full loop inline extraction regresses98.25, so reverted. Explicit int offset declared before count/i, indexed via (DebugTextEntry *)((char *)self->entries + offset), and increment offset += sizeof(DebugTextEntry) before i++ fixes all homes and update order. All text720/rodata116/extab8/index12 100%; existing TU promoted Matching. No split/header/EH metadata changes. Source input confirmed in main.elf edge; owned linked DOL ranges and full SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 exact; +1 fn/+720B.
