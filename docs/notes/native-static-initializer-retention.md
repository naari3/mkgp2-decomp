# native-static-initializer-retention

Source: Codex worker c8_s58_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1096 B.

c8_s58_20261105: fn_8021ED1C natural C++ static initializer generated exact 108-byte __sinit_fn_8021ED1C_cpp and exact .ctors entry. Renaming target symbols.txt alone leaves local sinit discarded despite FORCEACTIVE linker entry. Adding #pragma force_active on at EOF after static empty instance retains compiler-generated sinit; empty instance sbss is dead-stripped. Native source input, ELF range 8021ED1C..8021ED88, .ctors and DOL SHA-1 verified via coordinator request 2. No section placement, manual ctor entry, or symbol postprocessor required.
