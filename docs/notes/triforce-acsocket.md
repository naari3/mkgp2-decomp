# triforce-acsocket

Source: Codex worker c3_u14_acsocket_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 12 fn / 3040 B.

acSelect target captures exOff/wrOff/rdOff before null-pointer short-circuit checks. wrResult/exResult precede sem/k declarations to reproduce register reuse; sign-bit result test produces rlwinm rather than signed cmpwi. The parser delimiter must be a named const char object in sdata2; unqualified string literals otherwise emit sdata. The 23-function range has no extab/extabindex constraint and can be split at all function boundaries. Shared BSS remains target fallback in acsocket_nm7.c. Further missing addi-zero address operations likely require the original helper shape; accumulator and pointer-offset variants did not reproduce them.
