/* === extracted from auto_Tornado_LockOnHoming_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_ItemHitFx_Spawn();
extern void DrawEffect_ItemHitOriented_Spawn();
extern short ItemAlias_HitRemapLookup();
extern int ItemCollision_Check();
extern void ItemHit_Dispatch();
extern char *ItemObject_AllocFromPool();
extern void ItemTracker_AcquireLock();
extern char *ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity(void *, float, float);
extern int Item_AdvanceFallingDrop(void *, void *, void *, float);
extern int Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar(void *, float);
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern const float lbl_806D6260;
extern const float lbl_806D6264;
extern const float lbl_806D6274;
extern const float lbl_806D627C;
extern const float lbl_806D6280;
extern const float lbl_806D6284;
extern const float lbl_806D6288;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern void Tornado_HomingChildTick();

/* --- function index (1 fns, .text 0x800F9148..0x800F9618) ---
 * [  0] 0x800F9148 size:0x4D0   global Tornado_LockOnHomingTick
 */

/* --- forward decls --- */
void Tornado_LockOnHomingTick(char *self, char *sub);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tornado_LockOnHomingTick[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tornado_LockOnHomingTick = {
    (void *)&Tornado_LockOnHomingTick, 0x000004D0, (void *)extab_Tornado_LockOnHomingTick
};

/* --- asm function bodies (.text order = fn address order) --- */
void Tornado_LockOnHomingTick(char *self, char *sub)
{
    TIVec3 pos;
    TIVec3 vel;
    TIVec3 fxPos;
    TIVec3 fxVel;
    TIVec3 hitPos;
    int landed;
    float groundY;
    char *child;

    switch (TI_S8(self, 0xc9)) {
    case 0:
        TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
        TI_U8(self, 0xca) = 0;
        /* fall through */
    case 1:
        switch (TI_S8(self, 0xca)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            TI_S8(self, 0x8d) = 1;
            TI_U32(sub, 4) = 300;
            TI_U32(sub, 8) = 0;
            TI_U32(sub, 0xc) = 0;
            TI_F32(self, 0x2c) = lbl_806D6264;
            TI_F32(self, 0xc4) = lbl_806D627C;
            TI_S8(self, 0xca) = TI_S8(self, 0xca) + 1;
            /* fall through */
        case 1:
            TI_F32(self, 0xbc) = TI_F32(self, 0xbc) + lbl_806D6274;
            break;
        case 2:
            Item_DecayVelocityScalar(self, lbl_806D6260);
            Item_AccelClampVelocity(self, (int)g_ccClass == 0 ? lbl_806D6284 : lbl_806D6288,
                                    (int)g_ccClass == 0 ? lbl_806D6260 : lbl_806D6280);
            fn_801B129C(self + 0xa0);
            break;
        }
        TI_F32(self, 0x2c) += lbl_806D627C;
        if (1.0f < TI_F32(self, 0x2c)) {
            TI_F32(self, 0x2c) = 1.0f;
        }
        switch (ItemCollision_Check(self)) {
        case 1:
            fn_801B1D5C(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(TI_U32(self, 8)), 0);
            ItemHit_Dispatch(self, 0, 0, 0);
            child = ItemObject_AllocFromPool(Tornado_HomingChildTick);
            if (child != 0) {
                TI_PTR(child, 0x148) = self;
                TI_PTR(child, 0x184) = ItemTracker_GetTargetKart(self);
            }
            ItemTracker_SetTrackPhase(self, 1);
            break;
        case 3:
            fn_801B158C(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            vel = *(TIVec3 *)(self + 0xb8);
            pos = *(TIVec3 *)(self + 0xa0);
            Item_ComputeYawRelativeApproach(self + 0xb8, ItemTracker_GetTargetKart(self), &pos, &vel);
            ItemTracker_SetTrackPhase(self, 0);
            TI_U32(sub, 0xc) = 5;
            break;
        case 4:
            fn_801B14B8(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            TI_PTR(sub, 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 3;
            return;
        case 2:
            fn_801B1660(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            /* fall through */
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (TI_U32(sub, 0xc) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (TI_S8(self, 0x8d) == 2) {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 4;
            return;
        }
        if (Item_CheckWallCollision(self, 0, 0) != 0) {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            GetSpawnPosition(self + 0xb8, lbl_806D6264, lbl_806D6264, lbl_806D6264);
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 7;
            return;
        }
        if (Item_AdvanceFallingDrop(self, &landed, &groundY, lbl_806D6264) != 0) {
            if (landed != 0 || TI_S8(self, 0xca) == 2) {
                TI_F32(self, 0xa4) = groundY;
                TI_F32(self, 0xbc) = lbl_806D6264;
                if (TI_U32(sub, 8) == 0) {
                    fxVel = *(TIVec3 *)(self + 0xb8);
                    fxPos = *(TIVec3 *)(self + 0xa0);
                    DrawEffect_ItemHitOriented_Spawn(&fxPos, &fxVel, 3);
                    hitPos = *(TIVec3 *)(self + 0xa0);
                    DrawEffect_ItemHitFx_Spawn(&hitPos, self);
                    TI_U32(sub, 8) = 3;
                }
                if (TI_S8(self, 0xca) == 1) {
                    TI_S8(self, 0xca) = 2;
                }
            }
        } else {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            GetSpawnPosition(self + 0xb8, lbl_806D6264, lbl_806D6264, lbl_806D6264);
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 9;
            return;
        }
        if (TI_U32(sub, 4) == 0) {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 5;
        }
        break;
    }
}

