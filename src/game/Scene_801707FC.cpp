/*
 * 0x801707FC..0x801709FC: triggered grow-in entries (a kart entering the
 * trigger volume starts the entry; once its sub-object reports done, its
 * faces are added to the special face mesh and it scales in).
 */

struct Vec3f {
    float x, y, z;
};

struct GrowSub {
    char pad00[0x10];
    unsigned char started;
    unsigned char done;
};

struct GrowFace {
    char pad00[0x34];
};

struct GrowEntry {
    void *jobj;
    GrowFace *faces;
    int faceCount;
    void *trigger;
    int state;
    float t;
    float scale;
    GrowSub *sub;
};

struct GrowSet {
    char pad00[0x8];
    GrowEntry *entries;
    int count;
};

struct KartDriver {
    char pad00[0x240];
    int lap;
};

extern "C" {
extern int g_totalLaps;
extern void *lbl_806D1138;
KartDriver *GetKartSlotKartVariant(int);
float *KartDriver_GetKartRootMtx(KartDriver *);
unsigned char fn_80123480(void *, Vec3f *);
void fn_8016F584(GrowSub *);
void SpecialFaceMesh_AddFace(void *, GrowFace *);
float LUT_Sin12Bit(float);

void fn_801707FC(GrowSet *self) {
    int i;
    GrowEntry *e;

    for (i = 0; i < self->count; i++) {
        e = &self->entries[i];
        if (e->state == 0 && e->trigger) {
            int k;
            for (k = 0; k < 8; k++) {
                KartDriver *kart = GetKartSlotKartVariant(k);
                if (kart && kart->lap < g_totalLaps) {
                    Vec3f p;
                    p.x = KartDriver_GetKartRootMtx(kart)[3];
                    p.y = KartDriver_GetKartRootMtx(kart)[7];
                    p.z = KartDriver_GetKartRootMtx(kart)[11];
                    if (fn_80123480(e->trigger, &p)) {
                        e->state = 1;
                        e->sub->started = 1;
                        break;
                    }
                }
            }
        }
        fn_8016F584(e->sub);
        switch (e->state) {
        case 1: {
            unsigned char done = e->sub->done;
            e->sub->done = 0;
            if (done) {
                void *mesh;
                int f;
                e->state = 2;
                mesh = lbl_806D1138 == 0 ? 0 : lbl_806D1138;
                for (f = 0; f < e->faceCount; f++) {
                    SpecialFaceMesh_AddFace(mesh, &e->faces[f]);
                }
            }
            break;
        }
        case 2:
            e->t += 0.05f;
            if (e->t < 1.0f) {
                if (e->t <= 0.75f) {
                    e->scale = 1.5f * LUT_Sin12Bit(120.0f * e->t);
                } else {
                    e->scale = 0.5f * LUT_Sin12Bit(360.0f * (e->t - 0.75f) + 90.0f) + 1.0f;
                }
            } else {
                e->state = 3;
                e->t = 0.0f;
                e->scale = 1.0f;
            }
            break;
        }
    }
}

}
