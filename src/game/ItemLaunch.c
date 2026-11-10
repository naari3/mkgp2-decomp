/* Observed Item launch fields and complete target/callee assembly provenance.
 * These views do not establish the full runtime Item or KartDriver layouts. */
#include "game/types/Vec3.h"
typedef struct ItemLaunchView {
    unsigned char pad00[0x2C];
    float launchScalar;
    unsigned char pad30[0x70];
    Vec3 position;
    unsigned char padAC[4];
    float yaw;
    unsigned char padB4[4];
    Vec3 velocity;
    unsigned char padC4[0xC0];
    void *kart;
    unsigned char pad188[8];
    Vec3 direction;
} ItemLaunchView;

extern const float lbl_806D5AB8, lbl_806D5AC8, lbl_806D5B18;
extern float Vec3_ToYaw(const Vec3 *v);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void Vec3_Add_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
#ifdef __MWERKS__
extern signed char ItemObject_GetGroundTypeAt(Vec3 position, float *height, int mode);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(Vec3 *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(Vec3 position, float *height, int mode) { return ItemObject_GetGroundTypeAt(&position, height, mode); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
extern const float *KartDriver_GetJointByIdx(void *kart, int index);
extern const float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const float *matrix);
extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern void Mtx_TransposeToMtx44(float *out, const float *in);
extern void Mtx44_Inverse_GaussJordan(float *out, const float *in);
extern void Mtx44_TransformVec3(Vec3 *out, const float *matrix, const Vec3 *in);

static inline void BendLaunchVelocity(Vec3 *velocity, Vec3 position,
                                      float yaw, float length, float bend)
{
    Vec3 probe;
    float heightA, heightB;
    GetSpawnPosition(velocity, lbl_806D5AC8, lbl_806D5AC8, length);
    Vec2_RotateY(velocity, velocity, yaw);
    if (ItemObject_GetGroundTypeAt(position, &heightA, 0) != 0) {
        GetSpawnPosition(&probe, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5B18);
        Vec2_RotateY(&probe, &probe, yaw);
        Vec3_Add_DestFirst(&probe, &position, &probe);
        if (ItemObject_GetGroundTypeAt(probe, &heightB, 0) != 0) {
            float reciprocal;
            heightA = position.y - heightA;
            probe.y = heightB + heightA;
            Vec3_Subtract_DestFirst(velocity, &probe, &position);
            reciprocal = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(velocity);
            Vec3_Scale(velocity, velocity, length * reciprocal);
        }
    }
    heightA = Vec3_ToYaw(velocity);
    Vec2_RotateY(velocity, velocity, -heightA);
    Vec2_RotateX(velocity, velocity, bend);
    Vec2_RotateY(velocity, velocity, heightA);
}

static inline void ClampLaunchPosition(ItemLaunchView *self, void *kart, Vec3 position,
                                       float *matrix, float *inverse)
{
    Vec3 localPosition;
    Vec3 transformCopy1;
    Vec3 transformCopy2;
    Vec3_Copy(&localPosition, &position);
    Mtx_TransposeToMtx44(matrix, KartDriver_GetKartRootMtx(kart));
    Mtx44_Inverse_GaussJordan(inverse, matrix);
    transformCopy1 = localPosition;
    Mtx44_TransformVec3(&localPosition, inverse, &transformCopy1);
    localPosition.x = lbl_806D5AC8;
    transformCopy2 = localPosition;
    Mtx44_TransformVec3(&self->position, matrix, &transformCopy2);
}

/* The ground-bend and local-space clamp helpers are inlined at both launch
 * sites. Keep their by-value position snapshots and local declaration order:
 * these reproduce the target stack copies and float yaw rounding/spill. */
void Item_InitLaunchFromKart(ItemLaunchView *self, const Vec3 *origin,
                             float distance, float bend)
{
    float inverse[16];
    float matrix[16];
    Vec3 jointRelative;

    if (self != 0) {
        self->launchScalar = lbl_806D5AB8;
        self->yaw = Vec3_ToYaw(&self->direction);
        if (origin != 0) {
            Mtx44_GetTranslation_RowMajor(&jointRelative,
                KartDriver_GetJointByIdx(self->kart, 12));
            Vec3_Subtract_DestFirst(&jointRelative, &jointRelative, origin);
            Vec2_RotateY(&jointRelative, &jointRelative, -self->yaw);
            if (jointRelative.z < 0.0f)
                jointRelative.z = 0.0f;
            BendLaunchVelocity(&self->velocity, self->position, self->yaw,
                               distance + jointRelative.z, bend);
        } else {
            BendLaunchVelocity(&self->velocity, self->position, self->yaw,
                               distance, bend);
        }
        {
            void *kart = self->kart;
            ClampLaunchPosition(self, kart, self->position, matrix, inverse);
        }
    }
}
