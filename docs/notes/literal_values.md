# Float literal values are not checked by the build (2026-11-11)

`tools/postprocess_sdata2.py` renames an anonymous literal (`1.0f` in the
source, `@123` in the object) to the target's `lbl_806Dxxxx` by code position
only. The link then takes the number from the original pool, so `main.dol`
matches whatever the source wrote. A wrong literal in a Matching unit is
invisible here and changes behaviour in every other build of the sources
(the PC port drew special-kart tyres 1000 times too big).

## Audit

    rm -rf build/GNLJ82/src
    MKGP2_LIT_LOG=/tmp/lit.log ninja
    python3 tools/literal_value_audit.py /tmp/lit.log

The hook in `postprocess_sdata2.py` logs every renamed use (unit, function,
offset, target symbol, bytes the source produced); the tool compares the bytes
with the original and exits 1 when a Matching unit differs. For a Matching
unit the position is exact, so every line is a real source error. Run it
after writing literals in a unit that does not own its `.sdata2`.

## Found and fixed on 2026-11-11 (11084 uses checked)

| Unit | Function | Source had | Program has |
|---|---|---|---|
| game/KartTireFX.cpp | ctor | spin 1.0, scale 1000.0 | 0.0, 1.0 |
| game/ItemBox_8016CC04.cpp | fn_8016CC04 | radii 3.0, 1.0 | 20.0, 10.0 |
| game/fn_801B7EF8.c | fn_801B8BD8 | sprites 0x1B12/0x1B13 x 0.0 | 320.0 |
| game/Scene_801706C8.cpp | fn_80170B5C | scale 1.0 | 2.0 |
| include/game/FlowKartPosition_private.h | FKPositionIcon::SetPosition (fn_801D8E28) | z 0.0 | 1.0 |
| game/DNBress_nm2.cpp, DNBress_update2.cpp | fn_802271A4, fn_80227490 | speed floor 0.0 | 0.1 |
| game/DrawEffect_Cb_MutekiStar_VfxA.c, VfxB.c | | yaw step 0.008726646 | 0.034906577 |

Plus literals one or two units in the last place off in 39 files
(`0.017453292f` -> `0.017453289f`, `0.2617993f` -> `0.26179934f`,
`0.08726645f` -> `0.087266445f`, `1.3f` -> `1.3000001f` and similar): the
program computed them in single precision.

## Pitfall: a new distinct literal shifts the `@N` numbers

Changing `1.0f` to `2.0f` in Scene_801706C8.cpp added one anonymous symbol,
the later `@N` names moved, the extab rename step picked the wrong symbols
and the link failed. Reading the value through the named constant
(`extern const float lbl_806D8D0C; /* 2.0f */`) keeps the numbering.

## Left for a hand read

The position is not exact in NonMatching units, so these lines may only be a
different load order (HSD_LObjSetupInit was read: its code is shifted by 0xC
and the values agree):

- game/AI_UpdatePerFrameState +0x528: source int-to-float bias, target lbl_806DA3E0
- game/AI_CalcRivalAvoidance +0x11c, +0x13c (2pi vs pi, -pi), +0x21c (0.7 vs lbl_806D1934 in .sbss)
- sysdolphin/baselib/lobj_nm1 HSD_LObjSetupInit +0x880, +0xb38, +0xb40

`game/SpriteHandle` `__dt__11ScopedTimerFv` is a weak inline copy the link
discards; the tool skips it.
