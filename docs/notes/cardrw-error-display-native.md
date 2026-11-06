# cardrw-error-display-native

Source: Codex worker c15_a60_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1452 B.

CardRW_ErrorDisplay (0x80066350, 0x5AC) now matches naturally using its existing error-code if chain. A const char *strings = lbl_8030E598 local at entry preserves the shared pool base in r31 and self in r30; repeating lbl_8030E598 + offset directly instead produces separate HA/LO references (1628 B, 76.41047%). Reuse CardRWTestPage from CardRW_TestTopMenu_Private.h; #pragma cplusplus on supports its canonical header, while the body uses ordinary C. Existing -Cpp_exceptions on emits exact 8-byte extab and 12-byte extabindex after removal of manual objects. No extra pragma/metadata entries needed. Original cce13b4c introduced generated asm directly; no failed C explanation in that commit, and targeted docs/notes search found no prior note.
