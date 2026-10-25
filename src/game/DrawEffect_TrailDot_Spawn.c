typedef struct TrailDot {
    unsigned char pad000[0x8C];
    float pos[3];                /* 0x08C */
    unsigned char pad098[4];
    float yaw;                   /* 0x09C */
    unsigned char pad0a0[0x190 - 0xA0];
    signed char kind;            /* 0x190 */
} TrailDot;

extern unsigned char lbl_805DF3D0[];
extern float fn_800D3184(const float *a, const float *b);
extern TrailDot *DrawEffect_SpawnDirect(void (*callback)(TrailDot *));
extern void DrawEffect_HitFlash_Update(TrailDot *);
extern void Vec3_Copy(float *dst, const float *src);
extern float Vec3_ToYaw(const float *v);
extern float BuildOrientationFromYaw(float angle);

void DrawEffect_TrailDot_Spawn(const float *pos, void *unused, signed char kind, const float *dir)
{
    TrailDot *e;

    if (kind != 0) {
        if (!(500.0f < fn_800D3184((float *)(lbl_805DF3D0 + 0x80), pos))) {
            e = DrawEffect_SpawnDirect(DrawEffect_HitFlash_Update);
            if (e != 0) {
                Vec3_Copy(e->pos, pos);
                e->yaw = BuildOrientationFromYaw(3.141592f + Vec3_ToYaw(dir));
                e->kind = kind;
            }
        }
    }
}
