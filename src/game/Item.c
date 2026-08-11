typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct KartDriverView {
    char pad0[0x1F4];
    int mode;
    char pad1F8[0x40];
    int finalLapJump;
} KartDriverView;

typedef struct ItemView {
    char pad0[0xA0];
    Vec3 velocity;
    char padAC[0x0C];
    Vec3 position;
    char padC4[0xC4];
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
