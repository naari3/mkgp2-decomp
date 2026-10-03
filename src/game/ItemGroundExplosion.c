/* Observed Item/effect fields only; authoritative PowerPC ASM ABI reconstruction. */
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ItemExplosionView {
    unsigned char pad00[0xA0];
    Vec3 position;
    unsigned char padAC[4];
    float yaw;
    unsigned char padB4[4];
    Vec3 direction;
    unsigned char padC4[0xC0];
    void* driver;
    unsigned char pad188[8];
    Vec3 orientation;
} ItemExplosionView;
typedef struct ExplosionEffectView {
    unsigned char pad00[0x8C];
    Vec3 position;
    unsigned char pad98[0xC];
    Vec3 velocity;
    unsigned char padB0[0x6C];
    void* driver;
    Vec3 localPosition;
    unsigned char pad12C[0x65];
    unsigned char active;
} ExplosionEffectView;

extern const float lbl_806D5AB8, lbl_806D5AC8, lbl_806D5ADC, lbl_806D5B08;
extern const float lbl_806D5B18, lbl_806D5B28, lbl_806D5B2C, lbl_806D5B30;
extern float Vec3_ToYaw(const Vec3*);
extern void GetSpawnPosition(Vec3*, float, float, float);
extern void Vec2_RotateY(Vec3*, const Vec3*, float);
extern void Vec2_RotateX(Vec3*, const Vec3*, float);
extern signed char ItemObject_GetGroundTypeAt(Vec3*, float*, int);
extern void Vec3_Add_DestFirst(Vec3*, const Vec3*, const Vec3*);
extern void Vec3_Subtract_DestFirst(Vec3*, const Vec3*, const Vec3*);
extern float Vec3_Magnitude_Wrapper(const Vec3*);
extern void Vec3_Scale(Vec3*, const Vec3*, float);
extern void Vec3_Copy(Vec3*, const Vec3*);
extern float Rand_RangeFloat(float, float);
extern void Effect_ExplosionPiece_Update(void);
extern void Effect_KartJoint12_3Stage_Update(void);
extern ExplosionEffectView* DrawEffect_SpawnDirect(void (*)(void));
extern const void* KartDriver_GetKartRootMtx(void*);
extern void Mtx_TransposeToMtx44(float [4][4], const void*);
extern void Mtx44_Inverse_GaussJordan(float [4][4], const float [4][4]);
extern void Mtx44_TransformVec3(Vec3*, const float [4][4], const Vec3*);
extern void SoundMgr_PlaySE_Positional(int, const Vec3*, int);

void Item_SpawnGroundExplosionAndFX(ItemExplosionView* self)
{
    float inverseMatrix[4][4];
    Vec3 origin, transformPosition, soundPosition, secondPosition, firstPosition, probe;
    float secondHeight, firstHeight;
    float yaw;
    ExplosionEffectView* effect;
    int i;
    if (self != 0) {
        self->yaw = Vec3_ToYaw(&self->orientation);
        yaw = self->yaw;
        origin = self->position;
        GetSpawnPosition(&self->direction, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5ADC);
        Vec2_RotateY(&self->direction, &self->direction, yaw);
        firstPosition = origin;
        if (ItemObject_GetGroundTypeAt(&firstPosition, &firstHeight, 0) != 0) {
            GetSpawnPosition(&probe, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5B18);
            Vec2_RotateY(&probe, &probe, yaw);
            Vec3_Add_DestFirst(&probe, &origin, &probe);
            secondPosition = probe;
            if (ItemObject_GetGroundTypeAt(&secondPosition, &secondHeight, 0) != 0) {
                firstHeight = origin.y - firstHeight;
                probe.y = secondHeight + firstHeight;
                Vec3_Subtract_DestFirst(&self->direction, &probe, &origin);
                Vec3_Scale(&self->direction, &self->direction,
                    lbl_806D5ADC * (lbl_806D5AB8 / Vec3_Magnitude_Wrapper(&self->direction)));
            }
        }
        firstHeight = Vec3_ToYaw(&self->direction);
        Vec2_RotateY(&self->direction, &self->direction, -(double)firstHeight);
        Vec2_RotateX(&self->direction, &self->direction, lbl_806D5B28);
        Vec2_RotateY(&self->direction, &self->direction, firstHeight);
        for (i = 0; i < 6; ++i) {
            effect = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
            if (effect != 0) {
                Vec3_Copy(&effect->position, &self->position);
                GetSpawnPosition(&effect->velocity, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5AB8);
                Vec2_RotateX(&effect->velocity, &effect->velocity,
                    lbl_806D5B08 * Rand_RangeFloat(lbl_806D5B2C, lbl_806D5B30));
                Vec2_RotateY(&effect->velocity, &effect->velocity,
                    lbl_806D5B08 * Rand_RangeFloat(lbl_806D5B2C, lbl_806D5B30));
                effect->active = 1;
                effect->driver = self->driver;
                GetSpawnPosition(&effect->localPosition, lbl_806D5AB8, lbl_806D5AB8, lbl_806D5AB8);
            }
        }
        effect = DrawEffect_SpawnDirect(Effect_KartJoint12_3Stage_Update);
        if (effect != 0) {
            Mtx_TransposeToMtx44(inverseMatrix, KartDriver_GetKartRootMtx(self->driver));
            Mtx44_Inverse_GaussJordan(inverseMatrix, inverseMatrix);
            transformPosition = self->position;
            Mtx44_TransformVec3(&effect->localPosition, inverseMatrix, &transformPosition);
            effect->driver = self->driver;
        }
        soundPosition = self->position;
        SoundMgr_PlaySE_Positional(0x62, &soundPosition, 0);
    }
}
