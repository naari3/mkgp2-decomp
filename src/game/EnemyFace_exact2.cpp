#include "game/EnemyFace_private.h"

void EnemyFace_Request(KartRender *kart, int arg) {
    if (kart == 0) {
        return;
    }
    if (*((unsigned char *)kart + 0x2D0) == 1) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (lbl_80679CA0[i].kart == 0) {
            lbl_80679CA0[i].kart = kart;
            lbl_80679CA0[i].arg = arg;
            return;
        }
    }
}

void clEnemyFace::Enable(int on) {
    if (state < 2) {
        state = 2;
    }
}

void clEnemyFace::Draw() {
    if (!IsRaceStarted()) {
        return;
    }
    if (state >= 3) {
        return;
    }
    Sort();
    GetCourseScene3D();
    for (int i = 0; i < 4; i++) {
        int k = order[i];
        if (faces[k]) {
            icons[k]->Reset();
            rings[k]->Reset();
            *(Vec3c *)&faces[k]->x = world[k]; /* struct copy into x/y/z */
            icons[k]->Place(&screen[k]);
            rings[k]->Place(&screen[k]);
            faces[k]->scale = faceScale[k];
            icons[k]->scale = iconScale[k];
            rings[k]->scale = iconScale[k];
        }
    }
    for (int i = 0; i < 4; i++) {
        if (faces[order[i]]) {
            faces[order[i]]->model->Draw();
        }
    }
}
