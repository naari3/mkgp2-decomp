# amboot-inline-save-region

Source: Codex worker c13_u15_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 532 B.

fn_80287EE4 matched by extracting the save-region validation/copy into static inline s32 SetSaveRegion(void* save, u32 size), called with size 0x100. Direct constant arithmetic emits an extra lis 0x8120; a size parameter produces shared end address in r31 and exact target schedule. Integer-cast subtraction alone did not change baseline output. No flags or pragmas required.
