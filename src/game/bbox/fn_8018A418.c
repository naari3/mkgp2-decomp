#include "game/ObjViewA418_private.h"
extern unsigned char fn_8016C360(int);
extern unsigned char SoundMgr_PlaySE(int);
extern void fn_8016C240(int, Vec *, int);
extern void *GetKartSlotKartVariant(int);
extern float *KartDriver_GetKartRootMtx(void *);
extern void Vec3_Subtract(Vec *, Vec *, Vec *);
extern float PSVECSquareMag(Vec *);
extern unsigned char fn_8016C318(int);
extern unsigned char fn_8016C0A4(int, Vec *, unsigned char *, unsigned char *, unsigned char *);
extern void fn_8016C1B0(int, unsigned char);
extern void fn_8016C168(int, unsigned char);
extern void fn_8016C120(int, unsigned char);
static inline float AdvanceFrameTime(Frame *frame, float step) {
    step = frame->time + step;
    frame->time = step;
    return step;
}
void fn_8018A418(ObjView *o) {
    unsigned int triggered;
    int i;
    if (o->count == 0) return;
    if (!fn_8016C360(40)) SoundMgr_PlaySE(40);
    fn_8016C240(40, o->pos, o->count);
    triggered = 0;
    for (i=0; i<o->count; i++) {
        Frame *f = &o->frames[i];
        void *kart;
        int j;
        if (f->active == 0) {
            float time = AdvanceFrameTime(f, 1.0f);
            if (time > 44.0f) f->time = 0.0f;
        } else {
            float time = AdvanceFrameTime(f, 1.0f);
            if (time > 90.0f) { f->time = 0.0f; f->active = 0; }
        }
        for (j=0; j<8; j++) {
            kart = GetKartSlotKartVariant(j);
            if (kart) {
                Vec p;
                p.x = KartDriver_GetKartRootMtx(kart)[3];
                p.y = KartDriver_GetKartRootMtx(kart)[7];
                p.z = KartDriver_GetKartRootMtx(kart)[11];
                Vec3_Subtract(&p, &o->pos[i], &p);
                if (PSVECSquareMag(&p) < 90000.0f) {
                    if (f->active == 0) {
                        f->active = 1;
                        triggered |= 1 << i;
                        f->time = 45.0f;
                    }
                    break;
                }
            }
        }
    }
    if (triggered && fn_8016C318(41)) {
        unsigned char best=0, pan, pitch;
        int k;
        for (k=0; k<o->count; k++) {
            if (triggered & (1 << k)) {
                unsigned char volume, p, q;
                if (fn_8016C0A4(41, &o->pos[k], &volume, &p, &q) && volume > best) {
                    pan=p; best=volume; pitch=q;
                }
            }
        }
        if (best && SoundMgr_PlaySE(41)) {
            fn_8016C1B0(41,best); fn_8016C168(41,pan); fn_8016C120(41,pitch);
        }
    }
}
