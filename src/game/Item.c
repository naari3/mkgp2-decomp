typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct KartDriverView {
    char pad0[0x1F4];
    int mode;
    char pad1F8[0x40];
    int finalLapJump;
    char pad23C[0xCC];
    void *itemDispatcher;
} KartDriverView;

typedef struct ItemView {
    char pad0[8];
    int alias;
    char padC[0x94];
    Vec3 velocity;
    float yaw;
    float pitch;
    char padB4[4];
    Vec3 position;
    float tetherAlpha;
    char padC8[0xC0];
    KartDriverView *driver;
} ItemView;

extern void *KartDriver_GetKartRootMtx(KartDriverView *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, void *mtx);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern float Vec3_Magnitude_Wrapper(Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern const float lbl_806D5AB8;
extern const float lbl_806D5AC8;
extern const float lbl_806D5AD0;
extern u8 g_finalLapCoinJumpEnabled;
extern int ItemAlias_HitRemapLookup(int alias);
extern int ItemAlias_DestToSource(int alias, int zero);
extern u8 ItemAliasTable_LookupSlotIndex(u8 source);
extern void *KartDriver_GetJointByIdx(KartDriverView *driver, int index);
extern float BuildOrientationFromYaw(float angle);
extern const float lbl_806D5AD4;

void Item_PrepareHitRebound(ItemView *item, Vec3 *rebound, Vec3 *oldPosition,
                            int *state)
{
    Vec3 kartPosition;
    int allowed;
    int finalLap;

    if (item == 0) {
        return;
    }

    Mtx44_GetTranslation_RowMajor(
        &kartPosition, KartDriver_GetKartRootMtx(item->driver));
    Vec3_Subtract_DestFirst(&item->velocity, &item->velocity, &item->position);
    Vec3_Subtract_DestFirst(&item->velocity, &item->velocity, &item->position);
    Vec3_Copy(oldPosition, &item->position);
    GetSpawnPosition(&item->position, lbl_806D5AC8, lbl_806D5AC8,
                     lbl_806D5AC8);
    Vec3_Subtract_DestFirst(rebound, &item->velocity, &kartPosition);
    Vec3_Scale(rebound, rebound,
               lbl_806D5AD0 * (lbl_806D5AB8 / Vec3_Magnitude_Wrapper(rebound)));

    if (item->driver == 0) {
        allowed = 0;
    } else {
        switch (item->driver->mode) {
        case 0: allowed = 1; break;
        case 1: allowed = 1; break;
        case 2: allowed = 1; break;
        case 3: allowed = 1; break;
        default:
            allowed = 0;
            break;
        }
    }
    if (allowed != 0) {
        *state = 6;
    } else {
        *state = 0;
    }

    if (item->driver == 0) {
        finalLap = 0;
    } else {
        if (item->driver == 0) {
            finalLap = 0;
        } else if (item->driver->finalLapJump != 0) {
            finalLap = 1;
        } else {
            finalLap = 0;
        }
        if (finalLap != 0) {
            if (g_finalLapCoinJumpEnabled != 0) {
                finalLap = 1;
            } else {
                finalLap = 0;
            }
        } else {
            finalLap = 0;
        }
    }
    if ((u8)finalLap != 0) {
        *state = 0;
    }
}

#pragma cplusplus on
class ItemDispatcher {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void dispatch(int alias, int zero);
};

extern "C" {

int Item_AdvanceTetherToJoint13(ItemView *item, float *progress,
                                float tetherScale, float yawStep,
                                float pitchStep)
{
    Vec3 jointPosition;
    KartDriverView *driver;
    int alias;
    void *dispatcher;

    if (item == 0) {
        return 1;
    }
    if (lbl_806D5AB8 == *progress) {
        return 1;
    }

    *progress += lbl_806D5AD4;
    if (lbl_806D5AB8 < *progress) {
        *progress = lbl_806D5AB8;
        item->tetherAlpha = lbl_806D5AC8;
        alias = ItemAlias_HitRemapLookup(item->alias);
        driver = item->driver;
        if (driver != 0 && alias != -1) {
            if (ItemAliasTable_LookupSlotIndex(
                    (u8)ItemAlias_DestToSource(alias, 0)) < 0x44) {
                dispatcher = driver->itemDispatcher;
                ((ItemDispatcher *)dispatcher)->dispatch(alias, 0);
            }
        }
        return 1;
    }

    Mtx44_GetTranslation_RowMajor(
        &jointPosition, KartDriver_GetJointByIdx(item->driver, 13));
    Vec3_Subtract_DestFirst(&item->position, &jointPosition, &item->velocity);
    Vec3_Scale(&item->position, &item->position, *progress);
    item->tetherAlpha = tetherScale * (lbl_806D5AB8 - *progress);
    item->yaw = BuildOrientationFromYaw(item->yaw + yawStep);
    item->pitch = BuildOrientationFromYaw(item->pitch + pitchStep);
    return 0;
}

}
#pragma cplusplus off
