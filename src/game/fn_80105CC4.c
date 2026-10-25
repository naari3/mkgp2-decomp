typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct HitFlashSrc {
    unsigned char pad00[8];
    int kind;                    /* 0x08 */
    unsigned char pad0c[0x9C - 0x0C];
    int param9C;                 /* 0x9C */
    Vec3 pos;                    /* 0xA0 */
} HitFlashSrc;

typedef struct HitFlashTarget {
    unsigned char pad00[0x98];
    int param98;                 /* 0x98 */
    int param9C;                 /* 0x9C */
} HitFlashTarget;

typedef struct HitFlashEffect {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char pad014[0x8C - 0x14];
    Vec3 pos;                    /* 0x08C */
    unsigned char pad098[0xA4 - 0x98];
    Vec3 dir;                    /* 0x0A4 */
    unsigned char pad0b0[0xCC - 0xB0];
    int paramCC;                 /* 0x0CC */
    unsigned char pad0d0[0x11C - 0xD0];
    int param11C;                /* 0x11C */
    unsigned char pad120[0x190 - 0x120];
    unsigned char flag190;       /* 0x190 */
} HitFlashEffect;

extern void Effect_HitFlash_Update(void);
extern HitFlashEffect *DrawEffect_SpawnDirect(void (*callback)(void));
extern void Vec3_Copy(Vec3 *dst, const Vec3 *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern float BuildOrientationFromYaw(float yaw);

extern const float lbl_806D6654; /* 1.5f */
extern const float lbl_806D6658; /* 0.8f */
extern const float lbl_806D665C; /* 1.2f */
extern const float lbl_806D6660; /* deg->rad */
extern const float lbl_806D6664; /* -90.0f */
extern const float lbl_806D6668; /* -30.0f */
extern const float lbl_806D666C; /* -180.0f */
extern const float lbl_806D6670; /* 180.0f */
extern const float lbl_806D6674; /* 90.0f */
extern const float lbl_806D6678; /* 270.0f */

void fn_80105CC4(HitFlashSrc *src, HitFlashTarget *target, int type, float yaw)
{
    Vec3 dir;
    signed char kind = type;
    unsigned char sub = type - 3;
    int i;

    for (i = 0; i < 8; i++) {
        HitFlashEffect *e = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
        if (e != 0) {
            if (src->kind == 0x5F) {
                e->variant = 3;
            } else {
                e->variant = 4;
            }
            Vec3_Copy(&e->pos, &src->pos);
            GetSpawnPosition(&dir, 0.0f, 0.0f,
                             lbl_806D6654 * Rand_RangeFloat(lbl_806D6658, lbl_806D665C));
            switch (kind) {
            case 0:
            case 2:
            case 3:
            case 4:
                Vec2_RotateX(&dir, &dir, lbl_806D6660 * Rand_RangeFloat(lbl_806D6664, lbl_806D6668));
                Vec2_RotateY(&dir, &dir, lbl_806D6660 * Rand_RangeFloat(lbl_806D666C, lbl_806D6670));
                break;
            case 1:
            case 5:
                Vec2_RotateX(&dir, &dir, lbl_806D6660 * Rand_RangeFloat(lbl_806D6664, lbl_806D6668));
                Vec2_RotateY(&dir, &dir,
                             BuildOrientationFromYaw(lbl_806D6660 * Rand_RangeFloat(lbl_806D6674, lbl_806D6678) + yaw));
                break;
            case 6:
                GetSpawnPosition(&dir, 0.0f, 0.0f, 0.0f);
                break;
            }
            Vec3_Copy(&e->dir, &dir);
            if ((signed char)type == 0) {
                e->param11C = target->param98;
            } else {
                e->param11C = target->param9C;
            }
            if ((signed char)type == 6) {
                e->paramCC = src->param9C;
            }
            if (sub <= 1 || (signed char)type == 5) {
                e->flag190 = 1;
            }
        }
    }
}
