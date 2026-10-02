/*
 * Ground-following item motion, .text [0x800D957C, 0x800D9A44).
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

/* Minimal view of the fields used by the ground-following item helpers. */
typedef struct ItemMotionView {
    char pad0[0xA0];
    Vec3 position;
    char padAC[0xC];
    Vec3 velocity;
    float scale;
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
