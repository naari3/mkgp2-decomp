typedef struct Vec3 { float x, y, z; } Vec3;

extern void JointByName_GetWorldPosition(void *out, void *slot, const char *name);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Effect_ExplosionPiece_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern char lbl_80331698[];

void fn_8010BF20(unsigned char *self, unsigned char *ctx)
{
    Vec3 pos;
    Vec3 vel;
    Vec3 spos;
    int i;
    unsigned char *e;
    char *names = lbl_80331698;

    switch (*(int *)(self + 0x8)) {
    case 0x71:
        JointByName_GetWorldPosition(&pos, self + 0x14, names + 0x484);
        break;
    case 0x72:
        JointByName_GetWorldPosition(&pos, self + 0x14, names + 0x4A0);
        break;
    case 0x73:
        JointByName_GetWorldPosition(&pos, self + 0x14, names + 0x4BC);
        break;
    }
    switch (*(int *)(self + 0x8)) {
    case 0x71:
        GetSpawnPosition(&vel, 0.6000000238418579f, 0.6000000238418579f, 0.699999988079071f);
        break;
    case 0x72:
        GetSpawnPosition(&vel, 1.0f, 1.2000000476837158f, 1.5f);
        break;
    case 0x73:
        GetSpawnPosition(&vel, 0.699999988079071f, 0.800000011920929f, 1.0f);
        break;
    }
    for (i = 0; i < 4; i++) {
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e) {
            Vec3_Copy(e + 0x8C, &pos);
            GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, Rand_RangeFloat(0.699999988079071f, 1.2999999523162842f));
            Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453288659453392f * Rand_RangeFloat(-180.0f, 180.0f));
            Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453288659453392f * Rand_RangeFloat(-180.0f, 180.0f));
            e[0x190] = 1;
            e[0x191] = 2;
            e[0x192] = 0;
            *(void **)(e + 0x11C) = *(void **)(ctx + 0x9C);
            Vec3_Copy(e + 0x120, &vel);
            e[0x193] = 1;
        }
    }
    spos = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0x87, &spos, 0);
}
