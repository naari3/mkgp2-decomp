#include "game/DNStartCameraPrivate.h"

static inline void UpdateFlash(clDNStartCamera *self, int i) {
    FlashPart *fp = &self->flashes[i].fp;
    if (!fp->active) {
        if (--self->flashes[i].timer > 0) {
            return;
        }
        if (self->hidden == 1) {
            self->flashes[i].timer = 60;
            return;
        }
        HSD_JObj *j = self->flashJoints[i];
        JObjSetupMatrix(j);
        self->flashes[i].pt.pos.x = j->mtx[0][3];
        self->flashes[i].pt.pos.y = j->mtx[1][3];
        self->flashes[i].pt.pos.z = j->mtx[2][3];
        self->flashes[i].fp.Start(&self->flashes[i].pt);
    } else {
        fp->Tick();
        if (!fp->active) {
            self->flashes[i].timer = rand() % 60;
        }
    }
}

void clDNStartCamera::Update() {
    KartRender *k;
    if ((k = g_playerRenderObj) == 0) {
        hidden = 0;
        return;
    }
    hidden = 1;
    const float *m = KartDriver_GetKartRootMtx(k);
    float a;
    float x = m[3];
    float z = m[11];
    if (x >= DNStartCamera_nm1_rodata_803D0CF8[0] && x <= DNStartCamera_nm1_rodata_803D0CF8[2] && z >= DNStartCamera_nm1_rodata_803D0CF8[1] && z <= DNStartCamera_nm1_rodata_803D0CF8[3]) {
        hidden = 0;
        for (int i = 0; i < 10; i++) {
            a = JObjGetTranslationX(men[i]) - x;
            a = atan2(a, JObjGetTranslationZ(men[i]) - z);
            JObjSetRotationY(men[i], lbl_806DB4F0 + a);
        }
    }
    for (int i = 0; i < 6; i++) {
        UpdateFlash(this, i);
    }
    if (hidden == 0) {
        clNormal3D_Exec(cam);
        Object_DriveAnimMatrix(cam);
    }
}

