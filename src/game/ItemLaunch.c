/* Observed Item launch fields and complete target/callee assembly provenance.
 * These views do not establish the full runtime Item or KartDriver layouts. */
typedef struct Vec3 { float x, y, z; } Vec3;
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
extern double Vec3_ToYaw(const Vec3 *v);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *out, const Vec3 *in, float scale);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern void Vec3_Subtract_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void Vec3_Add_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern signed char ItemObject_GetGroundTypeAt(Vec3 *position, float *height, int mode);
extern const float *KartDriver_GetJointByIdx(void *kart, int index);
extern const float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const float *matrix);
extern void Vec3_Copy(Vec3 *out, const Vec3 *in);
extern void Mtx_TransposeToMtx44(float *out, const float *in);
extern void Mtx44_Inverse_GaussJordan(float *out, const float *in);
extern void Mtx44_TransformVec3(Vec3 *out, const float *matrix, const Vec3 *in);

/* Bounded complete C draft: 95.01798%, 1096B versus target 1112B.
 * Distance and derived length share f30 instead of target f28/f29; both
 * yaw spills retain rounded f0, the known Item ground-bend residue.
 * The original object, not this source object, supplies the exact DOL. */
void Item_InitLaunchFromKart(ItemLaunchView *self, const Vec3 *origin,
                             float distance, float bend)
{
    float inverse[16];
    float matrix[16];
    Vec3 jointRelative;
    Vec3 positionWith;
    Vec3 positionWithout;
    Vec3 positionFinal;
    Vec3 groundWithB;
    Vec3 groundWithA;
    Vec3 probeWith;
    Vec3 groundWithoutB;
    Vec3 groundWithoutA;
    Vec3 probeWithout;
    Vec3 transformCopy2;
    Vec3 transformCopy1;
    Vec3 localPosition;
    float heightWithB;
    float heightWithA;
    float heightWithoutB;
    float heightWithoutA;

    if (self != 0) {
        self->launchScalar = lbl_806D5AB8;
        self->yaw = Vec3_ToYaw(&self->direction);
        if (origin != 0) {
            float yaw;
            float length;
            double velocityYaw;
            Mtx44_GetTranslation_RowMajor(&jointRelative,
                KartDriver_GetJointByIdx(self->kart, 12));
            Vec3_Subtract_DestFirst(&jointRelative, &jointRelative, origin);
            Vec2_RotateY(&jointRelative, &jointRelative, -self->yaw);
            if (jointRelative.z < lbl_806D5AC8)
                jointRelative.z = lbl_806D5AC8;
            yaw = self->yaw;
            length = distance + jointRelative.z;
            positionWith = self->position;
            GetSpawnPosition(&self->velocity, lbl_806D5AC8, lbl_806D5AC8, length);
            Vec2_RotateY(&self->velocity, &self->velocity, yaw);
            groundWithA = positionWith;
            if (ItemObject_GetGroundTypeAt(&groundWithA, &heightWithA, 0) != 0) {
                GetSpawnPosition(&probeWith, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5B18);
                Vec2_RotateY(&probeWith, &probeWith, yaw);
                Vec3_Add_DestFirst(&probeWith, &positionWith, &probeWith);
                groundWithB = probeWith;
                if (ItemObject_GetGroundTypeAt(&groundWithB, &heightWithB, 0) != 0) {
                    float reciprocal;
                    heightWithA = positionWith.y - heightWithA;
                    probeWith.y = heightWithB + heightWithA;
                    Vec3_Subtract_DestFirst(&self->velocity, &probeWith, &positionWith);
                    reciprocal = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(&self->velocity);
                    Vec3_Scale(&self->velocity, &self->velocity, length * reciprocal);
                }
            }
            velocityYaw = Vec3_ToYaw(&self->velocity);
            heightWithA = velocityYaw;
            Vec2_RotateY(&self->velocity, &self->velocity, -(float)velocityYaw);
            Vec2_RotateX(&self->velocity, &self->velocity, bend);
            Vec2_RotateY(&self->velocity, &self->velocity, heightWithA);
        } else {
            float yaw = self->yaw;
            double velocityYaw;
            positionWithout = self->position;
            GetSpawnPosition(&self->velocity, lbl_806D5AC8, lbl_806D5AC8, distance);
            Vec2_RotateY(&self->velocity, &self->velocity, yaw);
            groundWithoutA = positionWithout;
            if (ItemObject_GetGroundTypeAt(&groundWithoutA, &heightWithoutA, 0) != 0) {
                GetSpawnPosition(&probeWithout, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5B18);
                Vec2_RotateY(&probeWithout, &probeWithout, yaw);
                Vec3_Add_DestFirst(&probeWithout, &positionWithout, &probeWithout);
                groundWithoutB = probeWithout;
                if (ItemObject_GetGroundTypeAt(&groundWithoutB, &heightWithoutB, 0) != 0) {
                    float reciprocal;
                    heightWithoutA = positionWithout.y - heightWithoutA;
                    probeWithout.y = heightWithoutB + heightWithoutA;
                    Vec3_Subtract_DestFirst(&self->velocity, &probeWithout, &positionWithout);
                    reciprocal = lbl_806D5AB8 / Vec3_Magnitude_Wrapper(&self->velocity);
                    Vec3_Scale(&self->velocity, &self->velocity, distance * reciprocal);
                }
            }
            velocityYaw = Vec3_ToYaw(&self->velocity);
            heightWithoutA = velocityYaw;
            Vec2_RotateY(&self->velocity, &self->velocity, -(float)velocityYaw);
            Vec2_RotateX(&self->velocity, &self->velocity, bend);
            Vec2_RotateY(&self->velocity, &self->velocity, heightWithoutA);
        }
        {
            void *kart = self->kart;
            positionFinal = self->position;
            Vec3_Copy(&localPosition, &positionFinal);
            Mtx_TransposeToMtx44(matrix, KartDriver_GetKartRootMtx(kart));
            Mtx44_Inverse_GaussJordan(inverse, matrix);
            transformCopy1 = localPosition;
            Mtx44_TransformVec3(&localPosition, inverse, &transformCopy1);
            localPosition.x = lbl_806D5AC8;
            transformCopy2 = localPosition;
            Mtx44_TransformVec3(&self->position, matrix, &transformCopy2);
        }
    }
}
