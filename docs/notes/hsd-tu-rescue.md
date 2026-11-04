# hsd-tu-rescue

Source: Codex worker c2_i14_tobj_state_mobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 66 fn / 10176 B.

Object-level objdiff can match anonymous literal content while fallback objects require the original named global export. Audit selected definitions and undefined references across the cut. BSS section 100% can mask different symbol offsets: check ELF st_value and st_size per symbol. CW/1.3.2 aligned the tested union and char[3]/char[7] wrappers to four bytes even under packed layout; scalar byte state plus separate scalar padding reproduced target offsets. Preserve padding with force_active where link stripping could remove it.

## c2_i14_tobj_state_mobj_20261105
Source: Codex worker c2_i14_tobj_state_mobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 66 fn / 10176 B.

Even 100% object text/data and a source link edge do not ensure every static function survives MWLD. HSD_TexMapID2PTTexMtx (148 B) was unreferenced after isolation, so MWLD dropped it and its 32 B jump table. Actual main.elf had MakeTextureMtx at 0x802BE15C instead of 0x802BE1F0. Keeping the helper in an honest target fallback partition restores its original Active 0x8 retention; preserve the neighboring six native functions separately.
