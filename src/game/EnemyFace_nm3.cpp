#include "game/EnemyFace_private.h"

clEnemyFace::clEnemyFace(void *path, int p) : state(1), param(p), holder(0) {
    for (int i = 0; i < 4; i++) {
        karts[i] = 0;
        faces[i] = 0;
        icons[i] = 0;
        rings[i] = 0;
        order[i] = 0;
    }
    if (path == 0) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        PathEntry *e = PathManager_GetEntrySubStruct(path, i);
        karts[i] = 0;
        if (e && e->id != -1) {
            int slot = e->kart->slot;
            if (slot != GetDisplayBufferIndex(e->kart) && slot != 6) {
                karts[i] = e->kart;
                clEFace3D *f = new clEFace3D(e->kart, param);
                if (f) {
                    if (g_gameMode == 2 && !fn_80231644(&f->b, &f->a, &f->c, f->slot, e->kart->course)) {
                        f->a = fn_80231BD4(6, e->kart->course, 0);
                    }
                    f->model = new clEFaceModel(e->kart, f->a, f->b, f->c);
                }
                faces[i] = f;
                icons[i] = new FaceIcon(e->kart, param);
                rings[i] = new FaceRing(e->kart, param);
            }
        }
        dist[i] = 0.0f;
        order[i] = i;
        iconScale[i] = 1.0f;
        lbl_80679CA0[i].kart = 0;
        lbl_80679CA0[i].arg = 0;
    }
}
