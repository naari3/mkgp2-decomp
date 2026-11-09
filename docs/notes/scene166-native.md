# scene166-native

Source: Codex worker cxc_r_u5_scene166_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1588 B.

801670FC native exact: spell fn_801698B4 call as (ctx, float x, float y, int id, unsigned flags) to reproduce load scheduling; PPC ABI matches existing canonical alternate parameter ordering. 80166BE8: separate named get_title_name result temporary gives extra mr r0/mr r5 needed. 801661FC: new ParamModel(ItemRes_LookupByKey_Thunk(id),1) generates exact DELETEPOINTER action and pointer r27, but remaining non-EH register partition resists function-scope declaration restructuring and C++ member method. Do not trust NM sdata2 relocation names after the missing icon move; source literals are correct, postprocessor offset correspondence is shifted.

## c3_n3_scene16_20261105
Source: Codex worker c3_n3_scene16_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 5568 B.

2026-11-05 c3_n3_scene16: fn_801661FC 98.71% with icon8 as if/else; the only residual is a 3-way callee-saved rotation (target strings=r31, p=r30, this=r29). Alias, free-function and direct-global variants do not move it; it likely needs a TU-owned rodata pool base.

## c23_u41_20261109
Source: Codex worker c23_u41_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u41: pool already OWN-SELF80369D78..8036A390; audit stale. Retained nine named static const formats atA27C,A290,A29C,A2A8,A2B4,A2C0,A2CC,A2D8,A2E4 and split target oversized lbl8036A24C to its47-byte format string plus nine true string objects. Raw98.62862->98.705284 solely from pool-symbol attribution; normalized report98.705284 and587 instructions unchanged. Receiver-free EditParamValues(p,const int&repeat,const int&cursor,float step), both switches+angle wrapping, invariant and reverted. Real Item_GetDescriptorField8/C definitions use unsigned int return/input; corrected TU-local prototypes, invariant but retained as declaration correction. All owned nontext100; all other report units JSON unchanged. Three-way receiver/row/pool target29/30/31 vs source31/29/30 persists. Single-function NM, no B/native gain. Coordinator request1 exit0,DOL ea30f3b1 exact. No config/split/header/EH-map edits.
