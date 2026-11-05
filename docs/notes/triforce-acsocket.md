# triforce-acsocket

Source: Codex worker c3_u14_acsocket_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 12 fn / 3040 B.

acSelect target captures exOff/wrOff/rdOff before null-pointer short-circuit checks. wrResult/exResult precede sem/k declarations to reproduce register reuse; sign-bit result test produces rlwinm rather than signed cmpwi. The parser delimiter must be a named const char object in sdata2; unqualified string literals otherwise emit sdata. The 23-function range has no extab/extabindex constraint and can be split at all function boundaries. Shared BSS remains target fallback in acsocket_nm7.c. Further missing addi-zero address operations likely require the original helper shape; accumulator and pointer-offset variants did not reproduce them.

## c14_u13_20261106
Source: Codex worker c14_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

acInetAddr: static inline clear-and-return helper (u8* p=BufPtr(0); memset(p,0,0x40); return p;) used before memcpy retains staging buffer in r27 and reproduces target buffer address/move shape. Objdiff improves 93.60274 to 95.61644. Source stays 288 vs target 292 bytes; addi-zero in board offset address and related load/add scheduling remain. Local pointer alone gives 95.20548. Aggregate first-member and pointer-typed base experiments still fold zero offset; no flags changed.
