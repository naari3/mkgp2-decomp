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

## c16_u70_20261106
Source: Codex worker c16_u70_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 2276 B.

c16_u70: TObjMakeTExp needs boolean repeat normalization and canonical assertion lines1540/1598. AssignResources needs inline PT texture matrix switch, reflection wrap_s/wrap_t=GX_REPEAT under tobj_unk_flag, and final traversal consuming input parameter. Both exact and native after splitting Setup at802BFD08; jump-table data32 exact. Setup legacy DifferentTluts contains a self-comparison; do not promote it as a native match. Removing it causes CW to shorten the boolean materialization by16B; direct inequality, early returns and explicit local all collapse. Genuine strings can be exact-length arrays10/21: splitting target symbols at real boundaries yielded data100 with trailing linker alignment, no filler needed. Pool changes were exploratory and reverted with Setup retained verbatim NonMatching. Full source-linked DOL SHA-1 OK; gain2fn/2276B.

## c17_u1_20261107
Source: Codex worker c17_u1_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u1: Setup802BFD08 legacy self-comparison can be removed while retaining target boolean materialization by static inline void CompareTlutEntries(t0,t1,int* different) assigning 1 then setting0 on n_entries equality. Inline return inequality collapses16B, but output parameter does not. Correct named assertion filename/small strings plus native local default-LOD/assert strings yields primary732B/text99.65574/data97.0297 (source49 target52, final3 alignment bytes). Residual walker/result r4/r5 swap and local data base versus original hsdTObj base+298/2A8/2B4. Canonical casts, byte-array and structured external pool views hoist three individual addresses into callee-saved registers and expand744B; do not repeat those forms. No native gain; NonMatching fallback DOL SHA1 exact.
