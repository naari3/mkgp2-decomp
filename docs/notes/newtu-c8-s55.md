# newtu-c8-s55

Source: Codex worker c8_s55_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_801F52A8 has a compiler-generated 16-entry switch table at 0x804E545C..0x804E549C. A correct pointer-return signature for fn_801F98CC yields direct calls and exact text size/EH/table. Current canonical MenuModeLane_private.h discards the getter return; no shared edit was made. Register-only item-selection residual persists after local declaration and inline-helper variants. fn_801F27B4 copies two 0xA8-byte member-method table defaults at lbl_804E4C28 offsets 0x380->0x428 and 0x4D0->0x578; target .ctors registration is at 0x802E8930.
