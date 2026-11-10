#include "../src/game/mapeffect/mapfx16a_private.h"
extern "C" void fn_8016A854(Jungle16A *self) {
    const Desc16A *d;
    int i;
    unsigned char hit;
    hit = 0;
    for (i=0; i<8; ++i) {
        void *kart = GetKartSlotKartVariant(i);
        if (kart) {
            Vec3f p;
            p.x = KartDriver_GetKartRootMtx(kart)[3];
            p.y = KartDriver_GetKartRootMtx(kart)[7];
            p.z = KartDriver_GetKartRootMtx(kart)[11];
            if (fn_80123480(self->zone, &p)) hit = 1;
        }
    }
    for (i=0; i<2; ++i) {
        Motion16A *m = &self->motions[i];
        d = &((const Desc16A *)Jungle16AUpdate_rodata_8036CE88)[i];
        switch (m->state) {
        case 0:
            if (hit) m->state = 1;
            break;
        case 1:
            m->frame += 1.0f;
            if (m->frame > 25.0f) {
                float t = lbl_806D8A54 - fn_80186960(lbl_806D8A5C * ((m->frame - 25.0f) / lbl_806D8A60));
                m->pos.x = t * (d->end.x - d->start.x) + d->start.x;
                m->pos.y = t * (d->end.y - d->start.y) + d->start.y;
                m->pos.z = t * (d->end.z - d->start.z) + d->start.z;
            }
            if (m->frame > lbl_806D8A64) self->motions[i].state = 2;
            break;
        case 2:
            if (!hit) {
                void *cam = GetCourseScene3D();
                if (cam) {
                    Vec3f p, dir;
                    CObj_LoadProjMatrix(cam, &p);
                    Vec3_Subtract(&d->start, &p, &p);
                    dir.x = CObj_GetViewMatrix_Cached(cam)[2];
                    dir.y = CObj_GetViewMatrix_Cached(cam)[6];
                    dir.z = CObj_GetViewMatrix_Cached(cam)[10];
                    if (Vec3_Dot(&p, &dir) < lbl_806D8A68) {
                        self->motions[i].pos = d->start;
                        self->motions[i].rot = d->rot;
                        self->motions[i].state = 0;
                        self->motions[i].unused = lbl_806D8A68;
                        self->motions[i].frame = lbl_806D8A68;
                    }
                }
            }
            break;
        }
    }
}
