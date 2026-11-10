# staritem-native-retrofit-c15

Source: Codex worker c15_a96_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 712 B.

c15_a96_20261106: FallRecoveryTick converted (712 B), exact production compiler command and all owned sections 100%; full build SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Reused game/objview/item_state_private.h Item/Vec3; added private StarWork layout. Typing the payload velocity member (instead of a byte-offset cast) corrected mr/addi argument scheduling. Pragmas exceptions on/reset replace only this function's manual EH pair. Added src/game/StarItem.c key in extab_order.json in address order. No symbols/splits/flags/renames changes.

History: only 74c837bde58bdf309f380bb43edf1b6d5441aa56 (Match Tornado StarItem and MukadeItem units), containing extracted asm with no recorded C blocker. No StarItem-specific docs/notes result.

BoundToVictimTick best natural C 99.933334%, same 1500 B and owned EH 100%. Residual at function offset 0x144: target fdivs f2,f1,f2, ours fdivs f1,f1,f2; limit consequently occupies f2 instead of target f1, affecting five rows. Explicit step/limit locals did not move the residue. A double FAbs return hypothesis worsened to 99.37334%; actual float signature is better. Keep original asm. Best C below uses canonical Item/Vec3 and StarWork plus private StarDriver { pad[0x304]; flags*; } whose flags view has pad[0x10], unsigned long long bits. Required prototypes are the ordinary Vec3/Matrix/Sprite helpers; FAbs_FloatAsDouble returns float. StarItem_BoundToVictimTick_rodata_80330374 is Vec3; all referenced lbl_806D constants are extern const float. The zero-weight term is the ordinary interpolation formula, with external constants retained to reproduce original runtime loads.

```c
void StarItem_BoundToVictimTick(Item *item, StarWork *work)
{
    float joint[4][4], inverse[4][4], orientation[4][4], spriteMtx[4][4];
    Vec3 endpoint, root, fallingRoot, initialPosition, rotatedEndpoint, rotatedPosition, localPosition;
    float yaw;
    switch (item->subphase) {
    case 0:
        item->x3c = 0;
        item->subphase++;
        item->step = 0;
    case 1:
        Mtx_TransposeToMtx44(joint, KartDriver_GetJointByIdx(work->target, 15));
        endpoint = StarItem_BoundToVictimTick_rodata_80330374;
        switch (item->step) {
        case 0:
            GetSpawnPosition(&item->velocity, lbl_806D63F8, lbl_806D63F8, lbl_806D63F8);
            Mtx44_Inverse_GaussJordan(inverse, joint);
            initialPosition = item->pos;
            Mtx44_TransformVec3(&work->delta, inverse, &initialPosition);
            Vec3_Copy(&work->velocity, &work->delta);
            work->height = lbl_806D63F8;
            work->lift = lbl_806D6430 / (FAbs_FloatAsDouble(Vec3_ToYaw(&work->delta)) / lbl_806D6440);
            if (lbl_806D6444 < work->lift) work->lift = lbl_806D6444;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 3, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6448 / (lbl_806D6430 / work->lift));
            work->timer2 = 0;
            work->timer3 = 10;
            item->step++;
        case 1:
            yaw = Vec3_ToYaw(&work->delta);
            Vec2_RotateY(&work->delta, &work->delta, -yaw);
            rotatedPosition = work->delta;
            rotatedEndpoint = endpoint;
            Vec3_Lerp(&work->delta, &rotatedEndpoint, &rotatedPosition, work->height);
            Vec2_RotateY(&work->delta, &work->delta, yaw * (lbl_806D6430 - work->height) + lbl_806D63F8 * work->height);
            work->height += work->lift;
            if (lbl_806D6430 < work->height) {
                Vec3_Copy(&work->delta, &endpoint);
                Vec2_RotateY(&work->delta, &work->delta, lbl_806D63F8);
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 4, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                item->step++;
            }
            break;
        case 2:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 5, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                item->step++;
            }
            break;
        case 3:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 6, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                work->timer = 20;
                item->step++;
            }
            break;
        case 4:
            if (work->timer == 0) {
                item->scale -= lbl_806D644C;
                if (item->scale < lbl_806D63F8) {
                    item->visible = 0; item->phase = 3; item->subphase = 0;
                    return;
                }
            }
            break;
        }
        localPosition = work->delta;
        Mtx44_TransformVec3(&item->pos, joint, &localPosition);
        Mtx_TransposeToMtx44(orientation, KartDriver_GetJointByIdx(work->target, 15));
        item->rotation.x = Mtx44_GetPitchOfPosZ(orientation);
        item->rotation.y = BuildOrientationFromYaw(lbl_806D63F8 + (lbl_806D6450 + Mtx44_GetYawOfPosZ(orientation)));
        Item_DecayVelocityScalar(item, lbl_806D63FC * KartFxParam_GetConst1p5(work->target));
        if (item->step == 3 && work->timer2 == 0) {
            Item_SpawnHitBurstParticles(item, work, 3, lbl_806D63F8);
            work->timer2 = 10;
        }
        if (work->timer3 == 0 && (((StarDriver *)work->target)->flags->bits & 0x10000ULL)) {
            if (work->target != 0) Mtx44_GetTranslation_RowMajor(&work->delta, KartDriver_GetKartRootMtx(work->target));
            JointByName_GetMatrix4x4Transposed(spriteMtx, item->sprite, lbl_80330380);
            Mtx44_GetTranslation_ColMajor(&item->pos, spriteMtx);
            item->rotation.x = Mtx44_GetPitchOfPosZ(spriteMtx);
            item->rotation.y = Mtx44_GetYawOfPosZ(spriteMtx);
            item->rotation.z = lbl_806D63F8;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(work->target));
            Vec3_Subtract_DestFirst(&work->delta, &item->pos, &root);
            GetSpawnPosition(&work->velocity, lbl_806D63F8, lbl_806D6454, lbl_806D63F8);
            item->subphase = 2; item->step = 0;
            return;
        }
        break;
    case 2:
        item->scale -= lbl_806D644C;
        if (item->scale < lbl_806D63F8) {
            item->visible = 0; item->phase = 3; item->subphase = 0;
            return;
        }
        work->velocity.y += lbl_806D6458;
        Vec3_Add_DestFirst(&work->delta, &work->delta, &work->velocity);
        Mtx44_GetTranslation_RowMajor(&fallingRoot, KartDriver_GetKartRootMtx(work->target));
        Vec3_Add_DestFirst(&item->pos, &fallingRoot, &work->delta);
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D6440);
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(work->target)) item->visible = 0;
    else item->visible = 1;
}
```

FlightAndLockOnTick best natural C 99.98195%, same 2216 B and owned EH 100%. The sole residual is target fmuls f1,f0,f31 vs ours fmuls f1,f31,f0 at function offset 0x738 (0x800FE924). Swapping source operands, naming reciprocal factor, and accumulating the scale factor did not solve it; accumulator introduced an extra move. Stop after non-discriminating probes; no register permutation/fakematch used. ItemAlias_HitRemapLookup declared int with a short local produced the required extsh r31,r3; short return plus int local instead introduced extsh r0 + mr r31. g_ccClass must be int (cmpwi rather than cmplwi). Keep original asm.

Flight best C below assumes StarWork.contact at +0x7C (split pad4c accordingly), StarFlightConstants { pad[0x3FC]; Vec3 first,second; pad414[0xC]; char jointName[1]; }, extern StarFlightConstants StarItem_FlightAndLockOnTick_rodata_8032FF60, and extern const float labels. Vec3_HorizontalMagnitude returns float; ItemCollision_Check, Item_CheckWallCollision, Item_AdvanceProjectileSimple return int; ItemTracker_GetTargetKart returns pointer; DrawEffect_SpawnDirect returns unsigned char*. These experiment-only private additions were removed from the final source/header.

```c
void StarItem_FlightAndLockOnTick(Item *item, StarWork *work)
{
    Vec3 joint, wallNormal, wallPoint, correction, renderPos, renderRot, groundPos, hitPos, approachPos, approachVelocity, burstPos;
    StarFlightConstants *constants = &StarItem_FlightAndLockOnTick_rodata_8032FF60;
    float distance, speed;
    switch (item->subphase) {
    case 0:
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6454);
            item->visible = 1;
            item->scale = lbl_806D63F8;
            item->param = lbl_806D645C;
            item->step++;
        case 1:
            renderRot = constants->second;
            renderPos = constants->first;
            Item_RenderCharacterScaledFromJoint12(item, &renderPos, &renderRot, 1, lbl_806D6430);
            if (FinalLapCoinJump_CheckActiveForObject(work->owner)) item->visible = 0;
            else item->visible = 1;
            switch (work->action) {
            case 1:
                item->visible = 1;
                work->action = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 0);
                Item_InitLaunchFromKart(item, &work->delta, lbl_806D6460, lbl_806D63F8);
                item->subphase++;
                item->step = 0;
                return;
            case 2:
                work->action = 0;
                item->visible = 0; item->phase = 3; item->subphase = 0;
                return;
            }
            Mtx44_GetTranslation_RowMajor(&work->delta, KartDriver_GetJointByIdx(work->owner, 12));
            break;
        }
        break;
    case 2:
        switch (item->step) {
        case 0:
            ItemTracker_AcquireLock(item);
            ItemTracker_SetTrackPhase(item, 1);
            item->tracking = 1;
            item->x3c = 1;
            groundPos = item->pos;
            ItemObject_GetGroundTypeAt(&groundPos, &work->height, 0);
            work->height = item->pos.y - work->height;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 1, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6454);
            work->timer = 300;
            work->timer2 = 0;
            item->step++;
        case 1:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 2, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6454);
                item->step++;
            }
            break;
        case 2:
            Item_AccelClampVelocity(item, g_ccClass == 0 ? lbl_806D6464 : lbl_806D6468, g_ccClass == 0 ? lbl_806D6430 : lbl_806D6454);
            fn_801B129C(&item->pos);
            break;
        }
        JointByName_GetWorldPosition(&joint, item->sprite, constants->jointName);
        Item_HomingScanAndSteer(item, &item->rotation.y, 0);
        item->rotation.x = Vec3_ToPitch(&item->velocity);
        Item_DecayVelocityScalar(item, lbl_806D6430);
        switch (ItemCollision_Check(item)) {
        case 1: {
            short alias = ItemAlias_HitRemapLookup(item->id);
            fn_801B1D5C(work->owner, ItemTracker_GetTargetKart(item), alias, 0);
            work->target = ItemTracker_GetTargetKart(item);
            ItemHit_Dispatch(item, 0, 0, 0);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 0;
            return;
        }
        case 2:
            fn_801B1660(work->owner, ItemTracker_GetTargetKart(item));
            work->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->velocity.y = lbl_806D6454;
            item->velocity.x *= lbl_806D6424;
            item->velocity.z *= lbl_806D6424;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            hitPos = item->pos;
            SoundMgr_PlaySE_Positional(0x84, &hitPos, 0);
            item->phase = 2; item->subphase = 0; item->reason = 1;
            return;
        case 3:
            fn_801B158C(work->owner, ItemTracker_GetTargetKart(item));
            work->contact = 0;
            approachVelocity = item->velocity;
            approachPos = item->pos;
            Item_ComputeYawRelativeApproach(&item->velocity, ItemTracker_GetTargetKart(item), &approachPos, &approachVelocity);
            item->rotation.y = Vec3_ToYaw(&item->velocity);
            ItemTracker_SetTrackPhase(item, 0);
            work->timer2 = 5;
            break;
        case 4:
            fn_801B14B8(work->owner, ItemTracker_GetTargetKart(item));
            work->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            item->phase = 2; item->subphase = 0; item->reason = 3;
            return;
        case 5: ItemTracker_SetTrackPhase(item, 1); break;
        }
        if (work->timer2 == 0) ItemTracker_SetTrackPhase(item, 1);
        if (item->tracking == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            if (item->hit == 1) {
                Vec3_Add_DestFirst(&item->velocity, &item->velocity, &item->impulse);
                item->velocity.y = lbl_806D6454;
                item->velocity.x *= lbl_806D646C;
                item->velocity.z *= lbl_806D646C;
                Item_SpawnHitBurstParticles(item, work, 0, lbl_806D63F8);
                burstPos = item->pos;
                SoundMgr_PlaySE_Positional(0x84, &burstPos, 0);
                item->phase = 2; item->subphase = 0; item->reason = 4;
                return;
            }
            Item_SpawnHitBurstParticles(item, work, 2, lbl_806D63F8);
            item->phase = 2; item->subphase = 0; item->reason = 6;
            return;
        }
        if (Item_CheckWallCollision(item, &wallNormal, &wallPoint)) {
            unsigned char *effect;
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Subtract_DestFirst(&correction, &wallPoint, &item->pos);
            distance = Vec3_HorizontalMagnitude(&correction) - lbl_806D6470;
            speed = Vec3_HorizontalMagnitude(&item->velocity);
            Vec3_Scale(&correction, &item->velocity, (lbl_806D6430 / speed) * distance);
            Vec3_Add_DestFirst(&item->pos, &joint, &correction);
            GetSpawnPosition(&item->velocity, lbl_806D63F8, lbl_806D63F8, lbl_806D63F8);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            work->height = Vec3_ToYaw(&wallNormal);
            Item_SpawnHitBurstParticles(item, work, 1, work->height);
            effect = DrawEffect_SpawnDirect(EffectVfx82_FieldItemDropPuff_Tick);
            if (effect != 0) {
                Vec3_Copy((Vec3 *)(effect + 0x8C), &item->pos);
                GetSpawnPosition((Vec3 *)(effect + 0x98), lbl_806D63F8, lbl_806D6450 + work->height, lbl_806D63F8);
            }
            item->phase = 2; item->subphase = 0; item->reason = 7;
            return;
        }
        if (!Item_AdvanceProjectileSimple(item, &work->height, lbl_806D6474, lbl_806D6474) && item->step == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 9;
            return;
        }
        if (work->timer == 0 && item->step == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 5;
        }
        break;
    }
}
```

Tick: read target control flow and .data relocation. The dense reason switch uses jumptable_80421840 (40 B), which is owned by auto_07_804216F4_data.o, outside this TU's extab/extabindex/text split. A compiler-generated switch table would require data ownership/relocation changes beyond this assignment's allowed edits. No C compile attempt; preserved asm. This is a structural blocker inference, not proof of impossibility under broader split authorization.

