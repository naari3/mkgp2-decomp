/*
 * Ground-following and wall-response item motion, .text [0x800D957C, 0x800D9D50).
 * Reconstructed from dtk target disassembly; no live Ghidra decompile was
 * available. The warp helpers take manager in r3 and coordinates in f1-f3;
 * ItemObject_GetGroundTypeAt returns a signed byte and takes a copied Vec3.
 *
 * CW 1.3.2 matching notes:
 * - Gravity/FallingDrop use a shared null-item exit returning the known-null
 *   pointer as an integer. This preserves r3 == 0 without an extra li or an
 *   undefined bare return. Simple intentionally uses an explicit return 0.
 * - Keep the reciprocal in its own temporary before scaling: putting it in
 *   the multiply expression reverses the fmuls operands.
 * - FallingDrop evaluates the candidate Y before assigning minimumY in the
 *   comparison; this preserves the original load/fused-multiply-add order.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Minimal view of the fields used by the item motion helpers. */
typedef struct ItemMotionView {
    char pad0[8];
    int alias;
    char padC[0x94];
    Vec3 position;
    char padAC[0xC];
    Vec3 velocity;
    float scale;
    char padC8[0xA0];
    unsigned int wallResponseMode;
    char pad16C[0x18];
    void *voiceDriver;
} ItemMotionView;

extern void *WarpDashMgr_GetInstance(unsigned char side);
extern int WarpZone_FindContaining(void *manager, float x, float y, float z);
extern int WarpZone_FindContainingOBB(void *manager, float x, float y, float z);
extern signed char ItemObject_GetGroundTypeAt(Vec3 *position, float *groundY, int mode);
extern void Vec3_Add_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern float Vec3_ToPitch(const Vec3 *v);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;
extern const float lbl_806D5AEC;

int Item_AdvanceProjectileGravity(ItemMotionView *item, float *height,
                                  float targetHeight, float heightStep,
                                  float gravity)
{
    Vec3 nextPosition;
    Vec3 groundPosition;
    float groundY;
    void *manager;
    float pitch;
    float speed;
    float inverseLength;

    if (item == 0) {
        goto null_item;
    }
    manager = WarpDashMgr_GetInstance(0);
    if (WarpZone_FindContaining(manager, item->position.x, item->position.y,
                               item->position.z) != -1) {
        return 0;
    }
    if (WarpZone_FindContainingOBB(manager, item->position.x, item->position.y,
                                  item->position.z) != -1) {
        return 0;
    }
    Vec3_Add_DestFirst(&nextPosition, &item->position, &item->velocity);
    groundPosition = nextPosition;
    if (ItemObject_GetGroundTypeAt(&groundPosition, &groundY, 0) != 0) {
        if (*height < targetHeight) {
            *height += heightStep;
            if (targetHeight < *height) {
                *height = targetHeight;
            }
        } else {
            *height -= heightStep;
            if (*height < targetHeight) {
                *height = targetHeight;
            }
        }
        nextPosition.y = groundY + *height;
        Vec3_Subtract_DestFirst(&nextPosition, &nextPosition, &item->position);
        pitch = Vec3_ToPitch(&nextPosition);
        if (Vec3_ToPitch(&item->velocity) < pitch) {
            item->velocity.y += gravity;
            if (lbl_806D5AC8 < item->velocity.y) {
                item->velocity.y *= lbl_806D5AEC;
            }
        } else {
            speed = Vec3_Magnitude_Wrapper(&item->velocity);
            inverseLength = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(&nextPosition);
            Vec3_Scale(&item->velocity, &nextPosition,
                       inverseLength * speed);
        }
        return 1;
    }
    return 0;
null_item:
    return (int)item;
}

int Item_AdvanceFallingDrop(ItemMotionView *item, int *landed, float *outGroundY,
                           float clearance)
{
    Vec3 groundPosition;
    float groundY;
    void *manager;
    float minimumY;

    if (item == 0) {
        goto null_item;
    }
    manager = WarpDashMgr_GetInstance(0);
    if (WarpZone_FindContaining(manager, item->position.x, item->position.y,
                               item->position.z) != -1) {
        return 0;
    }
    if (WarpZone_FindContainingOBB(manager, item->position.x, item->position.y,
                                  item->position.z) != -1) {
        return 0;
    }
    groundPosition = item->position;
    if (ItemObject_GetGroundTypeAt(&groundPosition, &groundY, 0) != 0) {
        if (item->position.y + item->velocity.y <
            (minimumY = clearance * item->scale + groundY)) {
            item->position.y = minimumY;
            if (landed != 0) {
                *landed = 1;
            }
        } else {
            if (landed != 0) {
                *landed = 0;
            }
        }
        if (outGroundY != 0) {
            *outGroundY = groundY;
        }
        return 1;
    }
    return 0;
null_item:
    return (int)item;
}

int Item_AdvanceProjectileSimple(ItemMotionView *item, float *height,
                                 float targetHeight, float heightStep)
{
    Vec3 nextPosition;
    Vec3 groundPosition;
    float groundY;
    void *manager;
    float speed;
    float inverseLength;

    if (item == 0) {
        return 0;
    }
    manager = WarpDashMgr_GetInstance(0);
    if (WarpZone_FindContaining(manager, item->position.x, item->position.y,
                               item->position.z) != -1) {
        return 0;
    }
    if (WarpZone_FindContainingOBB(manager, item->position.x, item->position.y,
                                  item->position.z) != -1) {
        return 0;
    }
    Vec3_Add_DestFirst(&nextPosition, &item->position, &item->velocity);
    groundPosition = nextPosition;
    if (ItemObject_GetGroundTypeAt(&groundPosition, &groundY, 0) != 0) {
        if (*height < targetHeight) {
            *height += heightStep;
            if (targetHeight < *height) {
                *height = targetHeight;
            }
        } else {
            *height -= heightStep;
            if (*height < targetHeight) {
                *height = targetHeight;
            }
        }
        nextPosition.y = groundY + *height;
        Vec3_Subtract_DestFirst(&nextPosition, &nextPosition, &item->position);
        speed = Vec3_Magnitude_Wrapper(&item->velocity);
        inverseLength = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(&nextPosition);
        Vec3_Scale(&item->velocity, &nextPosition,
                   inverseLength * speed);
        return 1;
    }
    return 0;
}

extern void SoundMgr_PlaySE_Positional(unsigned int sound, const Vec3 *position,
                                       int mode);
extern void DrawEffect_TrailDot_Spawn(const Vec3 *position, const Vec3 *velocity,
                                     signed char effect, const Vec3 *normal);
extern void Vec3_OrthoProjectThenScaleByLen(Vec3 *out, const Vec3 *velocity,
                                           const Vec3 *normal);
extern float Vec3_ToYaw(const Vec3 *v);
extern float BuildOrientationFromYaw(float yaw);
extern double FAbs_FloatAsDouble(float value);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern unsigned char ItemObject_RaycastWallStub(Vec3 *from, Vec3 *to,
                                                Vec3 *hitPosition, Vec3 *normal);
extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern int Voice_TryEnqueueAnnouncerByPhase(void *driver);
extern const float lbl_806D5AF0;
extern const float lbl_806D5AF4;

/* Preserve value-copy order: the target passes separate stack Vec3 objects. */
void Item_BounceOffWall(ItemMotionView *item, const Vec3 *normal,
                        unsigned int sound, signed char effect,
                        float horizontalScale, float verticalVelocity)
{
    Vec3 soundPosition;
    Vec3 effectPosition;
    Vec3 effectVelocity;
    Vec3 effectNormal;
    Vec3 incomingVelocity;
    Vec3 wallNormal;
    float wallYaw;
    float yawDifference;

    if (item == 0) {
        return;
    }
    soundPosition = item->position;
    SoundMgr_PlaySE_Positional(sound, &soundPosition, 0);
    effectNormal = *normal;
    effectVelocity = item->velocity;
    effectPosition = item->position;
    DrawEffect_TrailDot_Spawn(&effectPosition, &effectVelocity, effect,
                              &effectNormal);
    wallNormal = *normal;
    incomingVelocity = item->velocity;
    Vec3_OrthoProjectThenScaleByLen(&item->velocity, &incomingVelocity,
                                   &wallNormal);
    item->velocity.y = verticalVelocity;
    item->velocity.x *= horizontalScale;
    item->velocity.z *= horizontalScale;
    wallYaw = BuildOrientationFromYaw(lbl_806D5AF0 + Vec3_ToYaw(normal));
    yawDifference = BuildOrientationFromYaw(Vec3_ToYaw(&item->velocity) - wallYaw);
    if (lbl_806D5AF4 < FAbs_FloatAsDouble(yawDifference)) {
        if (lbl_806D5AC8 < yawDifference) {
            yawDifference = BuildOrientationFromYaw(yawDifference - lbl_806D5AF4);
        } else {
            yawDifference = BuildOrientationFromYaw(lbl_806D5AF4 + yawDifference);
        }
        Vec2_RotateY(&item->velocity, &item->velocity, -yawDifference);
    }
}

int Item_CheckWallCollision(ItemMotionView *item, Vec3 *outNormal,
                             Vec3 *outHitPosition)
{
    Vec3 nextPosition;
    Vec3 normal;
    Vec3 hitPosition;
    Vec3 rayFrom;
    Vec3 rayTo;
    Vec3 incomingVelocity;
    Vec3 wallNormal;

    if (item == 0) {
        return 0;
    }
    Vec3_Add_DestFirst(&nextPosition, &item->position, &item->velocity);
    rayTo = nextPosition;
    rayFrom = item->position;
    if (ItemObject_RaycastWallStub(&rayFrom, &rayTo, &hitPosition, &normal) != 0) {
        if (item->wallResponseMode != 0) {
            wallNormal = normal;
            incomingVelocity = item->velocity;
            Vec3_OrthoProjectThenScaleByLen(&item->velocity, &incomingVelocity,
                                           &wallNormal);
            return 0;
        }
        if (outNormal != 0) {
            Vec3_Copy(outNormal, &normal);
        }
        if (outHitPosition != 0) {
            Vec3_Copy(outHitPosition, &hitPosition);
        }
        if (item->alias != 0x3E && item->alias != 0x87 && item->alias != 0x2F) {
            Voice_TryEnqueueAnnouncerByPhase(item->voiceDriver);
        }
        return 1;
    }
    return 0;
}
