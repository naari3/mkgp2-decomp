# gameboot-init

Source: Codex worker c10_u10_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

GameBoot_Init: local int cabinet loaded through signed char* in ConfigureBootIP plus initialized BootIP table cursor, and char* final backup helper, improve 98.94334 to 99.969376. Only four r4/r5 scratch operands at 8007607C..80076088 remain. Final char-pointer helper matches target address materialization before byte store/condition; BootBackup* or direct-global helper CSEs store to r30 and sinks materialization into call branch. Removing ConfigureBootIP backup param does not change residual. Retain NonMatching; one-function TU offers no mechanism B cut. Full fallback DOL SHA-1 OK.
