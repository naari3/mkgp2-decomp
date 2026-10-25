/* DrawEffect_ItemHitOriented_Spawn (0x800CB8C0): spawn the ground-type
 * specific impact effect (debris, smoke ring or sparks) at a hit position
 * near the camera. */
typedef struct Vec { float x, y, z; } Vec;

extern unsigned char lbl_805DF3D0[];
extern Vec lbl_8041A4DC;
extern Vec lbl_8041A4E8;

extern float fn_800D3184(void *from, void *to);
extern void Vec3_Copy(void *dst, const void *src);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern float Item_ProbeForwardGroundPitch(Vec pos, float a, float b, float c);
extern float Item_ProbeLateralGroundPitch(Vec pos, float a, float b, float c);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern float Vec3_Magnitude_Wrapper(const void *v);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_ExplosionPiece_Update(unsigned char *e);
extern void DrawEffect_SmokeRingTimed_Update(unsigned char *e);
extern void DrawEffect_KartSparkTier_Update(unsigned char *e);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec3_Scale(void *dst, void *src, float s);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateY(void *dst, void *src, float a);

void DrawEffect_ItemHitOriented_Spawn(Vec *pos, Vec *vel, signed char kind)
{
    float m[4][4];
    Vec p;
    char ground;
    float pitch;
    float roll;
    unsigned char *e;
    int type;

    if (500.0f < fn_800D3184(lbl_805DF3D0 + 0x80, pos)) {
        return;
    }
    Vec3_Copy(&p, pos);
    ground = ItemObject_GetGroundTypeAt(p, &p.y, 0);
    if ((signed char)ground == 0) {
        return;
    }
    pitch = Item_ProbeForwardGroundPitch(p, 0.0f, 10.0f, 0.0f);
    roll = Item_ProbeLateralGroundPitch(p, 0.0f, 10.0f, 0.0f);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotX(m, m, pitch);
    Matrix4_PreMultiplyRotZ(m, m, roll);
    Vec3_Magnitude_Wrapper(vel);
    type = ground;
    switch (type) {
    case 1:
        break;
    case 2:
    case 3:
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy(e + 0x8C, &p);
            *(float *)(e + 0x90) += 1.5f;
            GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, 0.0f);
            switch (kind) {
            case 1:
                e[0x191] = 1;
                break;
            case 2:
                e[0x191] = 1;
                break;
            case 3:
                e[0x191] = 2;
                break;
            }
            switch (type) {
            case 2:
                e[0x193] = 2;
                break;
            case 3:
                e[0x193] = 0;
                break;
            }
            switch (type) {
            case 2:
                Vec3_Copy(e + 0x120, &lbl_8041A4DC);
                break;
            case 3:
                Vec3_Copy(e + 0x120, &lbl_8041A4E8);
                break;
            }
        }
        break;
    case 4:
        e = DrawEffect_SpawnDirect(DrawEffect_SmokeRingTimed_Update);
        if (e != 0) {
            Vec3_Copy(e + 0x8C, &p);
            *(float *)(e + 0x90) += 1.0f;
            e[0x190] = kind;
        }
        break;
    case 5:
        e = DrawEffect_SpawnDirect(DrawEffect_KartSparkTier_Update);
        if (e != 0) {
            Vec3_Copy(e + 0x8C, &p);
            Vec3_Copy(e + 0xA4, vel);
            Vec3_Scale(e + 0xA4, e + 0xA4, 0.9f);
            Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-10.0f, 10.0f));
            *(float *)(e + 0xA8) += 1.5f;
            e[0x190] = kind;
            e[0x191] = ground;
        }
        break;
    }
}
