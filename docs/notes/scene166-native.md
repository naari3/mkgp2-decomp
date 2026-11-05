# scene166-native

Source: Codex worker cxc_r_u5_scene166_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1588 B.

801670FC native exact: spell fn_801698B4 call as (ctx, float x, float y, int id, unsigned flags) to reproduce load scheduling; PPC ABI matches existing canonical alternate parameter ordering. 80166BE8: separate named get_title_name result temporary gives extra mr r0/mr r5 needed. 801661FC: new ParamModel(ItemRes_LookupByKey_Thunk(id),1) generates exact DELETEPOINTER action and pointer r27, but remaining non-EH register partition resists function-scope declaration restructuring and C++ member method. Do not trust NM sdata2 relocation names after the missing icon move; source literals are correct, postprocessor offset correspondence is shifted.

## c3_n3_scene16_20261105
Source: Codex worker c3_n3_scene16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 5568 B.

2026-11-05 c3_n3_scene16: fn_801661FC 98.71% with icon8 as if/else; the only residual is a 3-way callee-saved rotation (target strings=r31, p=r30, this=r29). Alias, free-function and direct-global variants do not move it; it likely needs a TU-owned rodata pool base.
