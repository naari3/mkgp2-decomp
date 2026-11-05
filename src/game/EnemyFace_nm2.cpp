#define ENEMYFACE_INLINE_VEC_DTOR
#include "game/EnemyFace_private.h"

extern "C" const float lbl_806DB5B4;

static inline unsigned char FaceHidden(KartRender *k) {
    return (k->flags->bits & 0x8000000000ULL) == 0 ? 0 : 1;
}

static inline void FaceScale(clEFaceModel *model, float scale) {
    model->scale = scale;
    model->sub->scale = scale;
}

static inline void FacePosition(clEFaceModel *model, clEFace3D *face) {
    model->x = face->x;
    model->y = face->y;
    model->z = face->z;
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

static inline void FaceDepthRange(void *scene) {
    void *cobj = *(void **)((char *)scene + 4);
    HSD_CObjGetNear(cobj);
    HSD_CObjGetFar(cobj);
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
