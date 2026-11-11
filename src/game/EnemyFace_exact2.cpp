/* Deferred generation keeps the definitions in reverse target order.
 * RTTI name strings stay in the original renderer pool via extern bridges. */
#include "game/types/clEnemyFace.h"
extern "C" const float lbl_806DB5B4;
static inline unsigned char FaceHidden(KartRender *k) {
    return (k->flags->bits & 0x8000000000ULL) == 0 ? 0 : 1;
}

static inline void FaceScale(clEFaceModel *model, float scale) {
    model->scale = scale;
    model->sub->scale = scale;
}

static inline void FacePosition(clEFaceModel *model, clEFace3D *face) {
    model->x = face->position.x;
    model->y = face->position.y;
    model->z = face->position.z;
}

static inline void FaceDepthRange(void *scene) {
    void *cobj = *(void **)((char *)scene + 4);
    HSD_CObjGetNear(cobj);
    HSD_CObjGetFar(cobj);
}

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
                faces[i] = new clEFace3D(e->kart, param);
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

clEnemyFace::~clEnemyFace() {
    for (int i = 3; i >= 0; i--) {
        if (faces[i]) {
            delete faces[i];
            faces[i] = 0;
            delete icons[i];
            icons[i] = 0;
            delete rings[i];
            rings[i] = 0;
        }
    }
}

clEnemyFace *EnemyFace_Create(void *path, int param) {
    return new clEnemyFace(path, param);
}

void EnemyFace_Preload() {
    PreloadResource(0xC2F);
    PreloadResource(0xC30);
    PreloadResource(0xC31);
    PreloadResource(0xC29);
    PreloadResource(0xC49);
    PreloadResource(0xC32);
}

void clEnemyFace::Sort() {
    void *scene = GetCourseScene3D();
    if (scene == 0) {
        return;
    }
    const float *m;
    FaceDepthRange(scene);
    Vec3f eye;
    CObj_LoadProjMatrix(scene, (Vec3c *)&eye);
    KartRender *player = g_playerRenderObj;
    for (int i = 0; i < 4; i++) {
        if (karts[i]) {
            m = KartDriver_GetKartRootMtx(karts[i]);
            world[i].x = m[3];
            world[i].y = 60.0f + m[7];
            world[i].z = m[11];
            float w;
            Vec3c p(world[i].x, world[i].y, world[i].z);
            CObj_ProjectPoint(scene, &screen[i].x, &screen[i].y, &w, &screen[i].z, p.x, p.y, p.z);
            if (screen[i].z > 1.0f) {
                iconScale[i] = 0.0f;
                faceScale[i] = 0.0f;
            } else if (karts[i]->active == 0) {
                iconScale[i] = 0.0f;
                faceScale[i] = 0.0f;
                dist[i] = 0.0f;
            } else {
                float d = -1.0f * w;
                if (d > 3000.0f || d < 60.0f) {
                    iconScale[i] = 0.0f;
                    faceScale[i] = 0.0f;
                    dist[i] = 0.0f;
                } else {
                    faceScale[i] = (500.0f + d) / 1000.0f;
                    iconScale[i] = (2500.0f - d) / 2500.0f;
                    world[i].y = -(15.0f * iconScale[i] - world[i].y);
                    p.y = 38.0f * faceScale[i] + world[i].y;
                    CObj_ProjectPoint(scene, &screen[i].x, &screen[i].y, &w, &screen[i].z, p.x, p.y, p.z);
                    float dx = m[3] - KartDriver_GetKartRootMtx(player)[3];
                    float dz = m[11] - KartDriver_GetKartRootMtx(player)[11];
                    dist[i] = dx * dx + dz * dz;
                }
            }
        }
    }
    order[0] = 0;
    order[1] = 1;
    order[2] = 2;
    order[3] = 3;
    int t;
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (dist[i] < dist[j]) {
                t = order[i];
                order[i] = order[j];
                order[j] = t;
            }
        }
    }
}

void clEnemyFace::Update() {
    if (!IsRaceStarted()) {
        return;
    }
    switch (state) {
    case 2:
        state = 3;
        break;
    case 3:
        return;
    }
    if (state >= 3) {
        return;
    }
    int i;
    for (i = 0; i < 4; i++) {
        if (lbl_80679CA0[i].kart) {
            for (int k = 0; k < 4; k++) {
                if (faces[k] && karts[k] == lbl_80679CA0[i].kart) {
                    faces[k]->model->Trigger(lbl_80679CA0[i].arg);
                    break;
                }
            }
            lbl_80679CA0[i].kart = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        int k = order[i];
        clEFace3D *f = faces[k];
        if (f) {
            if (FaceHidden(f->kart) == 1) {
                FaceScale(f->model, 0.0f);
                f->model->Update();
            } else {
                FacePosition(f->model, f);
                float s = lbl_806DB5B4 * f->scale;
                FaceScale(f->model, s);
                f->model->Update();
            }
            icons[k]->Update();
            rings[k]->Update();
        }
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
            *(Vec3c *)&faces[k]->position.x = world[k]; /* struct copy into x/y/z */
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

void clEnemyFace::Enable(int on) {
    if (state < 2) {
        state = 2;
    }
}

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