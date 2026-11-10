# tornado-native-c26-partials

Source: Codex worker c26_a5_20261110 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

NOT LANDED: bounded scratch C for Flight (best 99.50241%, after normal sdata2 target-aware postprocessing; raw 99.374%) and Hold (98.63424%). The checked-in guarded C/asm bodies remain original. Rules consulted: allocate_local_vregs and IRO_SplitLifetimes naming/order; Coloring.c simplifygraph/colorgraph (already obtained saved-register preference); InterferenceGraph.c coalescenodes (named-vs-temp copies). These are explanatory rules from docs/mwcc_internals.md, not a native trace; debugger and build/mweppc unavailable. Flight residual: f0/f1/f2 permutations in phase wrap, 0.5/1.0 phase offset, sx f1 instead of target f3 and scale constant f3 instead of f1, opacity 1.0/0.5 register/order; last loop preheader mr/li order. Hold residual: first cursor r27 vs target r29, first counter r29 vs target r27, final counter r28 vs target r29, sub addi scheduled before pool addi. Do not retry blind declaration permutations.

Flight scratch preconditions: real Item_AdvanceFallingDrop(void*,void*,void*,float), Item_AdvanceTetherToJoint13(void*,void*,float,float,float); #pragma use_lmw_stmw on/reset around these functions; existing declarations/macros/float labels from TU.
```c
static inline void TornadoFlight_Shrink(char *self, char *sub)
{
    switch (TI_S8(self, 0xc9)) {
    case 0:
        TI_F32(sub, 0x18) = lbl_806D6268;
        TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
        /* fall through */
    case 1:
        TI_F32(self, 0x2c) = TI_F32(self, 0x2c) - 0.05f;
        if (TI_F32(self, 0x2c) < 0.0f) {
            TI_F32(self, 0x2c) = 0.0f;
            TI_U32(sub, 4) = 0x78;
            TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
            break;
        }
        Vec3_Scale(self + 0xb8, self + 0xb8, lbl_806D6270);
        if (Item_AdvanceFallingDrop(self, 0, 0, 0.0f) != 0) {
            TI_F32(self, 0xbc) = TI_F32(self, 0xbc) + lbl_806D6274;
        } else {
            TI_F32(self, 0xbc) = 0.0f;
        }
        TI_F32(sub, 0x18) = TI_F32(sub, 0x18) * lbl_806D6278;
        TI_F32(sub, 0x20) = TI_F32(sub, 0x20) + TI_F32(sub, 0x18);
        break;
    case 2:
        if (TI_U32(sub, 4) == 0) {
            TI_U8(self, 0xc8) = 3;
            TI_U8(self, 0xc9) = 0;
        }
        break;
    }
}

static inline void TornadoFlight_UpdateSprites(char *self, char *sub)
{
    TIVec3 rotation;
    TIVec3 position;
    char *slot;
    float phase;
    float sx;
    float sy;
    float oscillation;
    int spriteIndex;
    slot = sub;
    for (spriteIndex = 0; spriteIndex < 3; spriteIndex++, slot += 4) {
        if (TI_PTR(slot, 0x5c) == 0) {
            continue;
        }
        Vec3_Copy((float *)(TI_PTR(slot, 0x5c) + 0xa0), (float *)(self + 0xa0));
        position = *(TIVec3 *)(TI_PTR(slot, 0x5c) + 0xa0);
        SpriteSlot_SetPositionFromVec(TI_PTR(slot, 0x5c) + 0x14, &position);
        phase = TI_F32(sub, 0x1c);
        if (spriteIndex == 2) {
            phase += lbl_806D6294;
            if (lbl_806D6260 < phase) {
                phase -= lbl_806D6260;
            }
        }
        Vec3_Copy((float *)(TI_PTR(slot, 0x5c) + 0xac), (float *)(self + 0xac));
        switch (spriteIndex) {
        case 0:
            TI_F32(TI_PTR(slot, 0x5c), 0xb0) = BuildOrientationFromYaw(lbl_806D6298 * phase + TI_F32(TI_PTR(slot, 0x5c), 0xb0));
            break;
        case 1:
            TI_F32(TI_PTR(slot, 0x5c), 0xb0) = BuildOrientationFromYaw(lbl_806D629C * phase + TI_F32(TI_PTR(slot, 0x5c), 0xb0));
            break;
        case 2:
            TI_F32(TI_PTR(slot, 0x5c), 0xb0) = BuildOrientationFromYaw(lbl_806D629C * phase + TI_F32(TI_PTR(slot, 0x5c), 0xb0));
            break;
        }
        rotation = *(TIVec3 *)(TI_PTR(slot, 0x5c) + 0xac);
        SpriteSlot_SetRotationQuatFromVec(TI_PTR(slot, 0x5c) + 0x14, &rotation);
        TI_F32(TI_PTR(slot, 0x5c), 0xc4) = TI_F32(self, 0xc4);
        sy = TI_F32(TI_PTR(slot, 0x5c), 0xc4);
        sx = sy * TI_F32(sub, 0x20);
        if (spriteIndex != 0) {
            sy = sy * (lbl_806D6278 * phase + lbl_806D6268);
        }
        SpriteSlot_SetScaleXYZ(TI_PTR(slot, 0x5c) + 0x14, sx, sy, sx);
        TI_F32(TI_PTR(slot, 0x5c), 0x2c) = TI_F32(self, 0x2c);
        if (spriteIndex != 0) {
            oscillation = (float)sin(lbl_806D62A0 * (lbl_806D62A8 * phase + lbl_806D62A4));
            TI_F32(TI_PTR(slot, 0x5c), 0x2c) = TI_F32(TI_PTR(slot, 0x5c), 0x2c) *
                ((lbl_806D6260 + oscillation) * lbl_806D6294);
        }
    }

}

void Tornado_FlightTick(char *self)
{
    TIVec3 startPos;
    TIVec3 updatePos;
    char *sub = self + 0xec;
    char *slot;
    int i;

    switch (TI_S8(self, 0xc8)) {
    case 0:
        TI_U32(self, 8) = 0x4f;
        SpriteSlot_InitNonLoop(self + 0x14, 0x50);
        TI_U8(self, 0x28) = 0;
        TI_U8(self, 0x8c) = 5;
        TI_U8(self, 0x8d) = 0;
        TI_F32(sub, 0x1c) = lbl_806D6264;
        TI_F32(sub, 0x20) = lbl_806D6260;
        *(int *)(sub + 0x30) = -1;
        slot = sub;
        for (i = 0; i < 3; i++, slot += 4) {
            TI_PTR(slot, 0x5c) = ItemObject_AllocFromPool(fn_800D748C);
            if (TI_PTR(slot, 0x5c) != 0) {
                SpriteSlot_InitNonLoop(TI_PTR(slot, 0x5c) + 0x14, 0x50);
                if (i == 0) {
                    SpriteSlot_SetTranslateDxDy(TI_PTR(slot, 0x5c) + 0x14, lbl_806D628C, lbl_806D6264);
                }
                if (i == 0) {
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, lbl_8032FE74, 0x10, 0);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, Tornado_FlightTick_rodata_8032FE8C, 0x10, 1);
                } else {
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, lbl_8032FE74, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, Tornado_FlightTick_rodata_8032FE8C, 0x10, 0);
                }
            }
        }
        TI_U8(self, 0xc8) = 1;
        TI_U8(self, 0xc9) = 0;
        /* fall through */
    case 1:
        Tornado_LockOnHomingTick(self, sub);
        break;
    case 2:
        switch (TI_S8(self, 0xcb)) {
        case 3:
            switch (TI_S8(self, 0xc9)) {
            case 0:
                GetSpawnPosition(self + 0xb8, lbl_806D6264, lbl_806D6264, lbl_806D6264);
                TI_F32(sub, 0x14) = lbl_806D6264;
                TI_F32(sub, 0x18) = TI_F32(self, 0xc4);
                TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
                /* fall through */
            case 1:
                if (Item_AdvanceTetherToJoint13(self, sub + 0x14, TI_F32(sub, 0x18), lbl_806D6264, lbl_806D6264) != 0) {
                    TI_F32(self, 0x2c) = lbl_806D6264;
                    TI_U32(sub, 4) = 0x78;
                    TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
                }
                break;
            case 2:
                if (TI_U32(sub, 4) == 0) {
                    TI_U8(self, 0xc8) = 3;
                    TI_U8(self, 0xc9) = 0;
                }
                break;
            }
            break;
        case 4:
            TornadoFlight_Shrink(self, sub);
            break;
        case 7:
            TornadoFlight_Shrink(self, sub);
            break;
        case 9:
            TornadoFlight_Shrink(self, sub);
            break;
        case 5:
            TornadoFlight_Shrink(self, sub);
            break;
        }
        break;
    case 3:
        slot = sub;
        for (i = 0; i < 3; i++, slot += 4) {
            SpriteSlot_Container_Free(TI_PTR(slot, 0x5c));
            TI_PTR(slot, 0x5c) = 0;
        }
        if (*(int *)(sub + 0x30) >= 0) {
            SoundMgr_StopSE_OrSpecial(0x82, *(int *)(sub + 0x30));
            *(int *)(sub + 0x30) = -1;
        }
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)(self + 0xa0), (float *)(self + 0xb8));
    if (*(int *)(sub + 0x30) < 0) {
        *(int *)(sub + 0x30) = SoundMgr_CountActiveSEInstances(0x82);
        if (*(int *)(sub + 0x30) >= 0) {
            startPos = *(TIVec3 *)(self + 0xa0);
            SoundMgr_PlaySE_Positional(0x82, &startPos, *(int *)(sub + 0x30));
        }
    } else {
        updatePos = *(TIVec3 *)(self + 0xa0);
        SoundMgr_PlaySE_WithChannel(0x82, &updatePos, *(int *)(sub + 0x30));
    }

    TI_F32(sub, 0x1c) = TI_F32(sub, 0x1c) + lbl_806D6290;
    if (lbl_806D6260 < TI_F32(sub, 0x1c)) {
        TI_F32(sub, 0x1c) = TI_F32(sub, 0x1c) - lbl_806D6260;
    }

    TornadoFlight_UpdateSprites(self, sub);

    if (TI_U32(sub, 4) != 0) {
        TI_U32(sub, 4) = TI_U32(sub, 4) - 1;
    }
    if (TI_U32(sub, 8) != 0) {
        TI_U32(sub, 8) = TI_U32(sub, 8) - 1;
    }
    if (TI_U32(sub, 0xc) != 0) {
        TI_U32(sub, 0xc) = TI_U32(sub, 0xc) - 1;
    }
    if (TI_U32(sub, 0x10) != 0) {
        TI_U32(sub, 0x10) = TI_U32(sub, 0x10) - 1;
    }
}
```

Hold scratch preconditions: #pragma use_lmw_stmw on/reset; existing TU declarations/macros and constants.
```c
void TornadoItem_HoldTick(char *self)
{
    float handMtx[16];
    float m[16];
    int i;
    char *sub = self + 0xec;
    char *names = (char *)TornadoItem_HoldTick_rodata_8032FA78;
    char *slot;
    char *shot;

    switch (TI_S8(self, 0xc8)) {
    case 0:
        slot = sub;
        for (i = 0; i < 3; i++, slot += 4) {
            TI_PTR(slot, 0x5c) = ItemObject_AllocFromPool(fn_800D748C);
            if (TI_PTR(slot, 0x5c) != 0) {
                SpriteSlot_InitNonLoop(TI_PTR(slot, 0x5c) + 0x14, 0x4f);
                TI_U8(TI_PTR(slot, 0x5c), 0x14) = 4;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(TI_PTR(slot, 0x5c) + 0x14, 1);
                switch (i) {
                case 0:
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, names + 0x42c, 0x10, 0);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, names + 0x450, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(slot, 0x5c) + 0x14, names + 0x474, 0x10, 1);
                    break;
                case 1:
                    /* the target really addresses slot 0 here and slot 1 in case 2 */
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x42c, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x450, 0x10, 0);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x474, 0x10, 1);
                    break;
                case 2:
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x42c, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x450, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x474, 0x10, 0);
                    break;
                }
                TI_F32(TI_PTR(slot, 0x5c), 0x100) = lbl_806D6264;
            }
        }
        TI_F32(self, 0x2c) = lbl_806D6264;
        TI_U8(self, 0xc8) = 1;
        break;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(TI_PTR(sub, 0x98)) != 0) {
        TI_U8(self, 0x28) = 0;
    } else {
        TI_U8(self, 0x28) = 1;
    }

    if (TI_S8(sub, 0xa0) != 0) {
        if (TI_S8(sub, 0xa0) == 1) {
            shot = ItemObject_AllocFromPool(Tornado_FlightTick);
            if (shot != 0) {
                TI_U8(shot, 0x1dc) = TI_U8(sub, 0xf0);
                TI_U32(shot, 0x1e0) = TI_U32(sub, 0xf4);
                Mtx44_GetTranslation_RowMajor((float *)(shot + 0xa0), KartDriver_GetJointByIdx(TI_PTR(sub, 0x98), 12));
                Vec3_Copy((float *)(shot + 0x190), (float *)(sub + 0xa4));
                TI_U32(shot, 0x180) = TI_U32(sub, 0x94);
                TI_U32(shot, 0x184) = TI_U32(sub, 0x98);
                Item_InitLaunchFromKart(shot, sub + 0x34, lbl_806D6260, lbl_806D6264);
            }
        }
        for (i = 0; i < 3; i++, sub += 4) {
            SpriteSlot_Container_Free(TI_PTR(sub, 0x5c));
            TI_PTR(sub, 0x5c) = 0;
        }
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Mtx44_GetTranslation_RowMajor((float *)(sub + 0x34), KartDriver_GetJointByIdx(TI_PTR(sub, 0x98), 12));
    GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D6264, lbl_806D6264, lbl_806D62AC);
    Mtx_TransposeToMtx44(handMtx, self + 0x48);
    slot = sub;
    for (i = 0; i < 3; i++, slot += 4) {
        if (TI_PTR(slot, 0x5c) == 0) {
            continue;
        }
        switch (i) {
        case 0:
            TI_F32(TI_PTR(slot, 0x5c), 0x100) = BuildOrientationFromYaw(lbl_806D62B0 + TI_F32(TI_PTR(slot, 0x5c), 0x100));
            break;
        case 1:
            TI_F32(TI_PTR(slot, 0x5c), 0x100) = BuildOrientationFromYaw(lbl_806D62B4 + TI_F32(TI_PTR(slot, 0x5c), 0x100));
            break;
        case 2:
            TI_F32(TI_PTR(slot, 0x5c), 0x100) = BuildOrientationFromYaw(lbl_806D62B8 + TI_F32(TI_PTR(slot, 0x5c), 0x100));
            break;
        }
        Matrix4_Identity(m);
        Matrix4_PreMultiplyRotY(m, m, TI_F32(TI_PTR(slot, 0x5c), 0x100));
        Matrix4_Multiply(m, m, handMtx);
        DbgScene_CopyMatrix3x4Transpose(TI_PTR(slot, 0x5c) + 0x48, m);
        Mtx44_GetTranslation_ColMajor(TI_PTR(slot, 0x5c) + 0xa0, m);
        TI_F32(TI_PTR(slot, 0x5c), 0xc4) = TI_F32(self, 0xc4);
        TI_F32(TI_PTR(slot, 0x5c), 0x2c) = TI_F32(self, 0x2c);
        TI_U8(TI_PTR(slot, 0x5c), 0x28) = TI_U8(self, 0x28);
        SpriteSlot_TickAnim(TI_PTR(slot, 0x5c) + 0x14);
    }
}
```
