#include "game/types/bitfields.h"
#include "game/LakituStartPrivate.h"
extern "C" {
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
void CObj_ApplyScissor(void *, Vec3f *);
void Vec3_Normalize(const Vec3f *, Vec3f *);

void HSD_JObjSetMtxDirtySub(HSD_JObj *);
float Object_GetField8(clNormal3D *);
unsigned char *SyncSlot_GetHostSend();
void fn_8016C600();
void JObj_Hide(clNormal3D *, HSD_JObj *, int);
void JObj_Show(clNormal3D *, HSD_JObj *, int);
void SoundMgr_PlaySE(int);
void clNormal3D_Exec(clNormal3D *);
void Object_DriveAnimMatrix(clNormal3D *);
extern float lbl_806CEDBC, LakituStart_UpdateCountdown_data_806CEDB8, LakituStart_UpdateCountdown_data_806CEDCC;
extern const float lbl_806D2524, lbl_806D2528, lbl_806D252C, lbl_806D2530, lbl_806D2534;
extern char lbl_806D2514[7], lbl_806D251C[5], lbl_802E9F54[];
extern const char *LakituStart_UpdateCountdown_data_803F5910[6];
extern unsigned char g_lakituStartAnimDone;
}
static inline unsigned char NeedsEval(HSD_JObj *j) {
    unsigned char result;
    if (!j) __assert(lbl_806D2514, 0x25d, lbl_806D251C);
    result = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) result = 1;
    return result;
}
static inline void Dirty(HSD_JObj *j) {
    if (!(j->flags & 0x2000000) && j && !NeedsEval(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline void SetX(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D2514, 0x3b8, lbl_806D251C);
    j->translate.x = v; Dirty(j);
}
static inline void SetY(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D2514, 0x3c6, lbl_806D251C);
    j->translate.y = v; Dirty(j);
}
static inline void SetZ(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D2514, 0x3d4, lbl_806D251C);
    j->translate.z = v; Dirty(j);
}
static inline void SetYaw(HSD_JObj *j, float v) {
    if (!j) __assert(lbl_806D2514, 0x2b8, lbl_806D251C);
    if (j->flags & 0x20000) __assert(lbl_806D2514, 0x2b9, lbl_802E9F54);
    j->rotY = v; Dirty(j);
}
static inline void HideCountdown(LakituStart *self) {
    for (unsigned i = 0; i < 6; ++i)
        JObj_Hide(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[i]), 0x10);
}
struct SyncFlags { BITFIELDS2(unsigned char countdown:5, unsigned char flags:3) };
extern "C" int LakituStart_UpdateCountdown(LakituStart *self) {
    if (!self->model) return 0;
    if (self->frame >= lbl_806CEDBC) return 0;
    if (self->holdFrames > 0) {
        int hold = self->holdFrames;
        self->holdFrames = hold - 1;
        if (hold > 0) return 1;
    }
    g_lakituDropStarted = 1;
    void *cam = GetCourseScene3D();
    if (cam) {
        Vec3f offset, result;
        Vec3f eye, at, dir;
        CObj_LoadProjMatrix(cam, &eye);
        CObj_ApplyScissor(cam, &at);
        Vec3_Subtract(&at, &eye, &dir);
        dir.y = lbl_806D2510;
        Vec3_Normalize(&dir, &dir);
        offset.x = LakituStart_data_806CEDC0 + self->x;
        offset.z = LakituStart_data_806CEDC8 + self->z;
        const float dy = dir.y;
        const float dx = dir.x;
        float height;
        height = LakituStart_data_806CEDC4 + self->y;
        result.x = dx * offset.z + (-dir.z * offset.x + eye.x);
        SetX(Archive_GetRootJObj(self->model), result.x);
        result.y = height + (dir.y * offset.z + (dy * offset.x + eye.y));
        SetY(Archive_GetRootJObj(self->model), result.y);
        result.z = dir.z * offset.z + (dx * offset.x + eye.z);
        SetZ(Archive_GetRootJObj(self->model), result.z);
        Vec3f rotation;
        rotation.y = LakituStart_UpdateCountdown_data_806CEDCC + (float)atan2(dir.x, dir.z);
        SetYaw(Archive_GetRootJObj(self->model), rotation.y);
    }
    self->frame = Object_GetField8(self->model);
    if (lbl_806D2510 == self->released && self->frame >= LakituStart_UpdateCountdown_data_806CEDB8) {
        self->released = lbl_806D2524;
        SetRaceStartFlag(1);
        if (SyncSlot_GetHostSend()) {
            ((SyncFlags *)SyncSlot_GetHostSend())->countdown = 3;
        } else fn_8016C600();
    }
    if (self->frame < lbl_806D2528) {
        if (self->phase < 1) {
            self->phase = 1;
            HideCountdown(self);
        }
    }
    else if (self->frame < lbl_806D252C) {
        if (self->phase < 2) {
            self->phase = 2;
            HideCountdown(self);
            g_countdownPhase = 3;
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[0]), 0x10);
            SoundMgr_PlaySE(69);
        }
    }
    else if (self->frame < lbl_806D2530) {
        if (self->phase < 3) {
            self->phase = 3;
            HideCountdown(self);
            g_countdownPhase = 2;
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[0]), 0x10);
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[1]), 0x10);
            SoundMgr_PlaySE(69);
        }
    }
    else if (self->frame < lbl_806D2534) {
        if (self->phase < 4) {
            self->phase = 4;
            HideCountdown(self);
            g_countdownPhase = 1;
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[0]), 0x10);
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[1]), 0x10);
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[2]), 0x10);
            SoundMgr_PlaySE(69);
        }
    }
    else if (true) {
        if (self->phase < 6) {
            self->phase = 6;
            HideCountdown(self);
            g_countdownPhase = 0;
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[3]), 0x10);
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[4]), 0x10);
            JObj_Show(self->model, ResolveJointByName(self->model, LakituStart_UpdateCountdown_data_803F5910[5]), 0x10);
            SoundMgr_PlaySE(70);
        }
    }
    clNormal3D_Exec(self->model);
    Object_DriveAnimMatrix(self->model);
    if (self->frame >= lbl_806CEDBC) g_lakituStartAnimDone = 1;
    return 1;
}
