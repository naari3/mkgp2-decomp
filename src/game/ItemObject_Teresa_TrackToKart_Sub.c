/* ItemObject_Teresa_TrackToKart_Sub (0x800E3C30): Teresa (Boo) item that
 * flies to the target kart's joint 13 and follows it. It plays its laugh
 * animations, then fades out. If the target becomes invincible (status
 * flag 0x10000) it bursts into six pieces and vanishes; while the target
 * is not in the stolen state its lifetime is cut short. */
typedef struct Vec { float x, y, z; } Vec;

extern const char lbl_8032E630[];
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_ExplosionPiece_Update(unsigned char *self);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateX(Vec *out, const Vec *in, float angle);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Vec3_Subtract_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void Vec3_Scale(Vec *out, const Vec *in, float s);
extern void Vec3_Add_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern float Vec3_HorizontalYawTo(const Vec *from, const Vec *to);
extern float AngleStepTowards_Shortest(float current, float target, float step);
extern float KartFxParam_GetConst1p5(void *driver);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

typedef struct KartStatus {
    unsigned char pad[0x10];
    unsigned long long flags;
} KartStatus;

static inline unsigned char has_flag(KartStatus *st, unsigned long long mask)
{
    unsigned char result;

    if ((st->flags & mask) == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void ItemObject_Teresa_TrackToKart_Sub(unsigned char *self, unsigned char *sub)
{
    float root[4][4];
    Vec trans;
    Vec target;
    Vec diff;
    Vec se1;
    Vec se2;
    Vec local;
    Vec se3;
    Vec jpos;
    unsigned char *e;
    int i;

    switch (S8(0xC9)) {
    case 0:
        GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
        self[0x3C] = 0;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        SU32(0x4) = 1800;
        SU32(0xC) = 10;
        SF(0x14) = 0.0f;
        se1 = *(Vec *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0x88, &se1, 0);
        S8(0xC9)++;
    case 1:
        if ((int)self[0x1E] == 1) {
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
        }
        if (SU32(0x4) == 0 && (int)self[0x1E] == 2) {
            se2 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x88, &se2, 0);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            SU32(0x8) = 40;
            S8(0xC9)++;
        }
        break;
    case 2:
        if (SU32(0x8) == 0) {
            F(0x2C) -= 0.05f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
                return;
            }
        }
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(SP(0x9C))) {
        self[0x14] |= 2;
    } else {
        self[0x14] &= ~2;
    }
    if (SP(0x9C) != 0 && SU32(0xC) == 0) {
        KartStatus *st = *(KartStatus **)(SP(0x9C) + 0x304);
        if (has_flag(st, 0x10000ULL)) {
            JointByName_GetWorldPosition(&jpos, self + 0x14, lbl_8032E630);
            for (i = 0; i < 6; i++) {
                e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
                if (e != 0) {
                    Vec3_Copy((Vec *)(e + 0x8C), &jpos);
                    GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f, 0.6f * Rand_RangeFloat(0.7f, 1.3f));
                    Vec2_RotateX((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
                    Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
                    e[0x190] = 1;
                    e[0x191] = 2;
                    e[0x192] = 1;
                    *(void **)(e + 0x11C) = SP(0x9C);
                    GetSpawnPosition((Vec *)(e + 0x120), 1.0f, 1.0f, 1.0f);
                    e[0x193] = 1;
                }
            }
            se3 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x87, &se3, 0);
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        } else if (!(st->flags & 2ULL)) {
            SU32(0x4) = 0;
        }
    }
    if (SP(0x9C) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetJointByIdx(SP(0x9C), 13));
        Mtx44_GetTranslation_ColMajor(&trans, root);
        GetSpawnPosition(&target, 0.0f, 0.0f, -0.1f);
        local = target;
        Mtx44_TransformVec3(&target, root, &local);
        SF(0x14) += 0.05f;
        if (1.0f < SF(0x14)) {
            SF(0x14) = 1.0f;
        }
        if (1.0f == SF(0x14)) {
            Vec3_Copy((Vec *)(self + 0xA0), &target);
        } else {
            Vec3_Subtract_DestFirst(&diff, &target, (Vec *)(self + 0xA0));
            Vec3_Scale(&diff, &diff, SF(0x14));
            Vec3_Add_DestFirst((Vec *)(self + 0xA0), (Vec *)(self + 0xA0), &diff);
        }
        F(0xB0) = AngleStepTowards_Shortest(F(0xB0), Vec3_HorizontalYawTo((Vec *)(self + 0xA0), &trans), 0.785398f);
    }
    Item_DecayVelocityScalar(self, 0.6f * KartFxParam_GetConst1p5(SP(0x9C)));
}
