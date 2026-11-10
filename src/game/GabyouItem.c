#include "game/GabyouItemHandTransformPrivate.h"

extern float lbl_806D5AB8, lbl_806D5AC8, lbl_806D5ACC, lbl_806D5AEC;
extern float lbl_806D5B1C, lbl_806D5B20;
extern void *KartDriver_GetKartRootMtx(void *);
extern void *KartDriver_GetJointByIdx(void *, int);
extern void Mtx_TransposeToMtx44(float [4][4], void *);
extern void Mtx44_GetTranslation_ColMajor(Vec3 *, float [4][4]);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void Matrix4_Copy(float [4][4], float [4][4]);
extern void Matrix4_PreMultiplyTranslation(float [4][4], float [4][4], float, float, float);
#ifdef __MWERKS__
extern void Mtx44_Translate(float [4][4], float [4][4], Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float a0[4][4], float a1[4][4], Vec3 *);
static inline void Mtx44_Translate_ByValue(float a0[4][4], float a1[4][4], Vec3 a2) { Mtx44_Translate(a0, a1, &a2); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void Matrix4_Identity(float [4][4]);
extern void Matrix4_PreMultiplyRotY(float [4][4], float [4][4], float);
extern void Matrix4_Multiply(float [4][4], float [4][4], float [4][4]);
extern void Mtx44_Scale_Uniform(float [4][4], float [4][4], float);
extern void DbgScene_CopyMatrix3x4Transpose(void *, float [4][4]);
static inline void GabyouItem_Grow(GabyouHandItem *item, float rate)
{
    float maximum = 1.0f;
    item->growth += rate;
    if (maximum < item->growth) item->growth = maximum;
}
#pragma exceptions on
void GabyouItem_BuildLocalTransformFromHandJoint(GabyouHandItem *item, int mode, float height, float yaw, float scale)
{
    float root[4][4];
    float local[4][4];
    float adjust[4][4];
    Vec3 rootPos;
    Vec3 handPos;
    float factor;
    float offset;
    if (item) {
        switch (mode) {
        case 0: break;
        case 1:
            GabyouItem_Grow(item, 0.1f);
            break;
        }
        switch (item->driver->kind) {
        case 0: factor = lbl_806D5AB8; break;
        case 1: factor = lbl_806D5AB8; break;
        case 2: factor = lbl_806D5AB8; break;
        case 3: factor = lbl_806D5AB8; break;
        case 4: factor = lbl_806D5AB8; break;
        case 5: factor = lbl_806D5AEC; break;
        case 6: factor = lbl_806D5AB8; break;
        case 7: factor = lbl_806D5AB8; break;
        case 8: factor = lbl_806D5AB8; break;
        case 9: factor = lbl_806D5AB8; break;
        case 10: factor = lbl_806D5AB8; break;
        case 11: factor = lbl_806D5AB8; break;
        case 12: factor = lbl_806D5AB8; break;
        default: factor = lbl_806D5AC8; break;
        }
        item->scale = scale * factor;
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(item->driver));
        Mtx44_GetTranslation_ColMajor(&rootPos, root);
        Mtx44_GetTranslation_RowMajor(&handPos, KartDriver_GetJointByIdx(item->driver, 12));
        Matrix4_Copy(local, root);
        Matrix4_PreMultiplyTranslation(local, local, -rootPos.x, -rootPos.y, -rootPos.z);
        Mtx44_Translate(local, local, handPos);
        Matrix4_Identity(adjust);
        switch (item->driver->kind) {
        case 0: offset = lbl_806D5ACC; break;
        case 1: offset = lbl_806D5ACC; break;
        case 2: offset = lbl_806D5ACC; break;
        case 3: offset = lbl_806D5B1C; break;
        case 4: offset = lbl_806D5B1C; break;
        case 5: offset = lbl_806D5B1C; break;
        case 6: offset = lbl_806D5ACC; break;
        case 7: offset = lbl_806D5B20; break;
        case 8: offset = lbl_806D5ACC; break;
        case 9: offset = lbl_806D5ACC; break;
        case 10: offset = lbl_806D5ACC; break;
        case 11: offset = lbl_806D5ACC; break;
        case 12: offset = lbl_806D5ACC; break;
        default: offset = lbl_806D5AC8; break;
        }
        Matrix4_PreMultiplyTranslation(adjust, adjust, lbl_806D5AC8, height * item->scale + offset, lbl_806D5AC8);
        Matrix4_PreMultiplyRotY(adjust, adjust, yaw);
        Matrix4_Multiply(local, adjust, local);
        Matrix4_Identity(adjust);
        Mtx44_Scale_Uniform(adjust, adjust, item->scale);
        Matrix4_Multiply(local, adjust, local);
        DbgScene_CopyMatrix3x4Transpose(item->matrix, local);
        Mtx44_GetTranslation_RowMajor(&item->position, item->matrix);
    }
}
#pragma exceptions reset
