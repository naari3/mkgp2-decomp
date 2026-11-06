# hsd-tu-rescue

Source: Codex worker c2_i14_tobj_state_mobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 66 fn / 10176 B.

Object-level objdiff can match anonymous literal content while fallback objects require the original named global export. Audit selected definitions and undefined references across the cut. BSS section 100% can mask different symbol offsets: check ELF st_value and st_size per symbol. CW/1.3.2 aligned the tested union and char[3]/char[7] wrappers to four bytes even under packed layout; scalar byte state plus separate scalar padding reproduced target offsets. Preserve padding with force_active where link stripping could remove it.

## c2_i14_tobj_state_mobj_20261105
Source: Codex worker c2_i14_tobj_state_mobj_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 66 fn / 10176 B.

Even 100% object text/data and a source link edge do not ensure every static function survives MWLD. HSD_TexMapID2PTTexMtx (148 B) was unreferenced after isolation, so MWLD dropped it and its 32 B jump table. Actual main.elf had MakeTextureMtx at 0x802BE15C instead of 0x802BE1F0. Keeping the helper in an honest target fallback partition restores its original Active 0x8 retention; preserve the neighboring six native functions separately.

## c5_s24_tobjresetnm_20261105
Source: Codex worker c5_s24_tobjresetnm_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 372 B.

tobj_reset native rescue: reverse chained float stores; separate genuine named zero constant into native tobj_reset_consts.c so existing sdata2 postprocessor maps the reset literal to exported lbl_806DCB88. tobj_texmap isolated static helper retained with established force_active pragma; source-linked final ELF address/size and full DOL SHA-1 verified.

## c16_u55_20261106
Source: Codex worker c16_u55_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u55: MObjInfoInit802C3A74 target keeps material-block base hsdMObj in r31, strings at +148/+160 and separate addi-zero class pointer for callback stores. Char-base reuse improves directly measured76.931816 to91.818184 (172/176B). Canonical global info expressions lose across-call base (82.931816); indexed zero-offset and typed aggregate subobject views fold address copies too (91.818184). Remains NonMatching; avoid repeating these shapes. Full fallback DOL SHA1 exact, native gain0.

## c16_u64_20261106
Source: Codex worker c16_u64_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

TObjInfoInit @802C0894 uses hsdTObj @804FB960 as shared pool base for library @804FBE08 (+0x4A8) and classname @804FBE20 (+0x4C0). Original separate addresses measure 75.48781% with current GC/1.3.2 build (assignment report said 79.02%). Canonical typed base rematerializes after call (81.92683%); an extern byte-array pool view retains r31 (91.70731%, 160 vs target164 bytes). Remaining target addi-zero member-address copies are missing; typed aggregate/first-member-array pool views rematerialize instead. Retained NonMatching, data100%, fallback full DOL SHA-1 OK. No new padding objects.
