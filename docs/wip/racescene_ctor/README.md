# fn_80151F08 (RaceScene ctor) C++ draft — R5, 2026-11-08

`fn_80151F08.patch` applies to game/Scene_8014E0C4.cpp at origin/main cd5ffe2. It also touches tools/extab_user_renames.json, and that file needs a clean build.

**Status:** 523 instructions, and the probe now differs by only 12 lines. The manual extab entry for this function is removed and the extab is generated automatically. Renames: `__ct__10RaceSceneCFUci`->fn_80151F08, RaceCamera/RaceDriver/RaceTornado/RaceInputManager ctors -> Camera_Create/KartDriver_New_Empty/TornadoEffect_Ctor/InputManager_Init, `__vt__10RaceSceneC`->RaceSceneC_vtable_80490010.

**Key finds:**
- ONE `char *` local holds Scene_8014E0C4_data_8048F178 (the script tables) and later walks Scene_8014E0C4_rodata_80367200 (the kart descs, +0xC) in the kart loop. Sharing it gives the target's r28. Separate locals swap the i/desc registers.
- Assign it right before the switch.
- `#pragma use_lmw_stmw on` is required.

**Left:**
1. Prologue: target `lis r8, Scene_8014E0C4_data_8048F178@ha`, with the SceneBase vtable in r3. Ours gives lis r3 and the vtable in r7.
2. Kart loop: target schedules `lbz desc->enabled` between the two uv[i] float stores. Ours puts it after both.

**Tried, no gain:** literal vs extern floats, uv store forms (ptr/struct/chained), `en` temp in several places, desc pointer types, two 9-10 min cperm runs.

## 2026-11-08 08:40 update (R5)
`fn_80151F08_v2.patch` applies to main ad4fd82, after fn_80151234 landed. It makes the probe **6 lines** off.
- The kart-loop lbz/uv order problem went away once Scene_8014E0C4_rodata_80367200 became a static defined in the TU.
- **The remaining prologue diff is a .data section anchor.** The target computes `lis/addi r28, Scene_8014E0C4_data_8048F178` at function entry, the same way fn_80151234 loads its rodata anchor (Scene_8014E0C4_rodata_80363D30) at entry. Scene_8014E0C4_data_8048F178 is the start of the TU's .data (auto_07_8048F178_data.s, 0x8048F178..0x8048FDB0). The three script tables at +0x48/+0x444/+0x840 are separate .data objects reached through that anchor.
- So matching needs the TU to own its .data (0x8048F178..), defined as statics before the functions, as R1 did for .rodata. Writing `char *scripts = (char *)Scene_8014E0C4_data_8048F178` at the declaration gives 8 lines (colouring only), but it is not the real form.
