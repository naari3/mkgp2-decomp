#include "game/EffectFA_private.h"

struct EffectKey {
    int type;
    float duration, x, scale, y;
};
extern "C" {
extern MapEffectDef EffectFA_Update_rodata_8036E000[6];
extern Vec3f EffectFA_Update_rodata_8036E048;
extern const float lbl_806D8C34, lbl_806D8C38, lbl_806D8C3C, lbl_806D8C40;
extern const float lbl_806D8C44, lbl_806D8C48, lbl_806D8C4C, lbl_806D8C50;
extern const float lbl_806D8C54, lbl_806D8C58, lbl_806D8C5C, lbl_806D8C60;
extern const float lbl_806D8C64, lbl_806D8C68, lbl_806D8C6C, lbl_806D8C70;
float LUT_Sin12Bit(float);
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
unsigned char SoundMgr_PlaySE(int);

void fn_8016F584(MapEffectFA *self) {
    if (lbl_806D15D0 == 0) return;
    switch (self->state) {
    case 0:
        if (!self->active) return;
        self->state = 1;
        self->phase = lbl_806D8C28;
        self->timer = lbl_806D8C28;
        self->alpha = lbl_806D8C28;
        break;
    case 1:
        self->timer += lbl_806D8C30;
        self->alpha = LUT_Sin12Bit(lbl_806D8C34 * self->timer);
        self->phase = lbl_806D8C38 * self->alpha;
        if (self->timer >= lbl_806D8C3C) {
            self->state = 3;
            self->phase = lbl_806D8C40;
            self->alpha = lbl_806D8C30;
            self->parts[0].frame = 0;
            self->parts[1].frame = 0;
            self->parts[2].frame = 0;
            self->parts[3].frame = 0;
            self->parts[4].frame = 0;
            self->parts[5].frame = 0;
        }
        break;
    case 2:
        self->phase += lbl_806D8C30;
        if (self->phase > lbl_806D8C44) self->phase = lbl_806D8C48;
        break;
    case 3:
        self->phase += lbl_806D8C30;
        if (self->phase <= lbl_806D8C4C) {
            if (self->active && self->phase >= lbl_806D8C50) {
                self->released = 1;
                self->active = 0;
            }
        } else {
            self->state = 4;
            self->phase = lbl_806D8C54;
        }
        break;
    case 4:
        self->phase += lbl_806D8C30;
        self->alpha = lbl_806D8C30 - LUT_Sin12Bit(lbl_806D8C58 * (self->phase - lbl_806D8C54));
        if (self->phase > lbl_806D8C5C) {
            self->state = 0;
            self->alpha = lbl_806D8C28;
        }
        break;
    }
    void *scene = GetCourseScene3D();
    Vec3f delta = EffectFA_Update_rodata_8036E048;
    if (scene) {
        Vec3f camera;
        CObj_LoadProjMatrix(scene, &camera);
        Vec3_Subtract(&camera, &self->position, &delta);
        self->yaw = atan2(delta.x, delta.z);
    }
    if (self->state == 3 && self->phase > lbl_806D8C3C && !self->soundPlayed) {
        if (delta.x * delta.x + delta.z * delta.z <= lbl_806D8C60) {
            if (SoundMgr_PlaySE(0x35)) self->soundPlayed = 1;
        }
    }
    for (int i = 0; i < 6; i++) {
        MapEffectPart *p = &self->parts[i];
        if (p->frame >= 0) {
            for (;;) {
                EffectKey *k = (EffectKey *)EffectFA_Update_rodata_8036E000[i].animation + p->frame;
                if (k->type == 2) {
                    p->frame = -1;
                    p->time = lbl_806D8C28;
                    break;
                }
                p->time += lbl_806D8C30;
                if (p->time >= k->duration) {
                    p->frame++;
                    p->time = lbl_806D8C28;
                    continue;
                }
                if (k->type == 1) {
                    float t = p->time / k->duration;
                    EffectKey *next = (EffectKey *)EffectFA_Update_rodata_8036E000[i].animation + (p->frame + 1);
                    p->x = t * (next->x - k->x) + k->x;
                    p->scale = t * (next->scale - k->scale) + k->scale;
                    p->y = t * (next->y - k->y) + k->y;
                } else {
                    p->x = lbl_806D8C28;
                }
                break;
            }
        }
        if (p->frame < 0) {
            if (i == 0) {
                p->x = lbl_806D8C68 * LUT_Sin12Bit(lbl_806D8C6C * self->phase) + lbl_806D8C64;
                p->scale = lbl_806D8C70;
            } else {
                p->x = lbl_806D8C28;
            }
        }
    }
}
}
