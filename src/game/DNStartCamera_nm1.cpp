#include "game/DNStartCameraPrivate.h"

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
    if (x >= lbl_803D0CF8[0] && x <= lbl_803D0CF8[2] && z >= lbl_803D0CF8[1] && z <= lbl_803D0CF8[3]) {
        hidden = 0;
        for (int i = 0; i < 10; i++) {
            a = JObjGetTranslationX(men[i]) - x;
            a = atan2(a, JObjGetTranslationZ(men[i]) - z);
            JObjSetRotationY(men[i], lbl_806DB4F0 + a);
        }
    }
    for (int i = 0; i < 6; i++) {
        FlashPart *fp = &flashes[i].fp;
        if (!fp->active) {
            if (--flashes[i].timer > 0) {
                continue;
            }
            if (hidden == 1) {
                flashes[i].timer = 60;
                continue;
            }
            HSD_JObj *j = flashJoints[i];
            JObjSetupMatrix(j);
            flashes[i].pt.pos.x = j->mtx[0][3];
            flashes[i].pt.pos.y = j->mtx[1][3];
            flashes[i].pt.pos.z = j->mtx[2][3];
            flashes[i].fp.Start(&flashes[i].pt);
        } else {
            fp->Tick();
            if (!fp->active) {
                flashes[i].timer = rand() % 60;
            }
        }
    }
    if (hidden == 0) {
        clNormal3D_Exec(cam);
        Object_DriveAnimMatrix(cam);
    }
}

