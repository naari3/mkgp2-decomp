# miyazakiconsole-native-20261105

Source: Codex worker cxc_u8_miyazaki17e_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 424 B.

fn_8017FD68: original function is a new-derived-mode factory, not just a free C initializer. Use canonical DemoRoot base, an 8-byte derived MiyazakiMode with an undefined key virtual, pass lbl_80376220 as ctor argument from outside new to preserve r30 across allocation, and inline ConsoleDisplay::Enable() instead of directly storing through a byte pointer: the inline method prevents li 1 being hoisted to r30 across fn_801DAEC0. Native text424/extab44/extabindex12 all100. Other six drafts retained NonMatching with per-function evidence; no asm/manual EH. DVD umbrella header pulls unavailable stdarg.h in this game recipe, so a private ABI view mirrors DVDDir and DVDDirEntry.
