/*
 * 0x8016CEA0..0x8016D2D0: item box update (hop animation between two
 * points, shadow particle spawns) and the item box set destructor.
 */

struct Vec3f {
    float x, y, z;
};

struct BoxShadow {
    Vec3f pos;
    float scale;
};

struct ItemBoxSlot {
    char pad00[0x4];
    float peakY;
    char pad08[0x4];
    Vec3f start;
    Vec3f end;
    Vec3f pos;
    float rotX;
    float rotY;
    char pad38[0x4];
    float t;
    int delay;
    unsigned char visible;
    char pad45[0x3];
    BoxShadow shadows[10];
    int cooldown;
    int randIdx;
};

struct ItemBoxSet {
    void *vtable;
    void *sound;
    void *modelA;
    void *modelB;
    void *archive;
    void *nodes;
    int selected;
    ItemBoxSlot *slots;
    int count;
};

extern "C" {
extern char lbl_8049110C[];
extern char lbl_80490FE0[];
extern char lbl_8036D5A8[];
extern const float lbl_80495A94[];
void fn_801712E4(void *, float, float, float, float);
void Vec3_Subtract(Vec3f *, Vec3f *, Vec3f *);
void fn_8025E2AC(Vec3f *, Vec3f *, float);
void fn_8025E264(Vec3f *, Vec3f *, Vec3f *);
float LookupSin(float);
double atan2(double, double);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

void fn_8016CEA0(ItemBoxSet *set) {
    ItemBoxSlot *it;
    int i;
    int spawned;
    Vec3f d;

    if (set->count == 0) {
        return;
    }

    for (it = set->slots; it <= &set->slots[set->count - 1]; it++) {
        if (it->delay > 0) {
            it->delay--;
            if (it->delay == 0) {
                it->t = 0.0f;
            }
        } else {
            if (0.0f == it->t && set->sound) {
                fn_801712E4(set->sound, it->start.x, it->start.y, it->start.z, 5.0f);
            }
            if (it->t >= 1.0f) {
                if (set->sound) {
                    fn_801712E4(set->sound, it->end.x, it->end.y, it->end.z, 5.0f);
                }
                it->delay = 60;
            }
            Vec3_Subtract(&it->end, &it->start, &d);
            fn_8025E2AC(&d, &it->pos, it->t);
            fn_8025E264(&it->start, &it->pos, &it->pos);
            it->pos.y += (it->peakY - it->pos.y) * LookupSin(3.1415927f * it->t);
            it->rotY = 1.5707964f - (float)atan2(d.z, d.x);
            it->rotX = 3.1415927f * LookupSin(1.5707964f * it->t) + 1.5707964f;
            it->t += 0.008333334f;
        }

        if (it->cooldown > 0) {
            it->cooldown--;
        }

        spawned = 0;
        for (i = 0; i < 10; i++) {
            if (it->shadows[i].scale > 0.0f) {
                it->shadows[i].scale = it->shadows[i].scale - 0.1f;
                if (it->shadows[i].scale < 0.0f) {
                    it->shadows[i].scale = 0.0f;
                }
            } else if (it->delay == 0 && spawned < 1 && it->cooldown == 0) {
                it->shadows[i].scale = 0.5f * lbl_80495A94[it->randIdx] + 1.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.x = 20.0f * lbl_80495A94[it->randIdx] + it->pos.x - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.y = 20.0f * lbl_80495A94[it->randIdx] + it->pos.y - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                it->shadows[i].pos.z = 20.0f * lbl_80495A94[it->randIdx] + it->pos.z - 10.0f;
                if (++it->randIdx >= 48) {
                    it->randIdx = 0;
                }
                spawned++;
                it->cooldown = 3;
            }
        }
    }

    set->selected++;
    if (set->selected >= 15) {
        set->selected = 0;
    }
}

ItemBoxSet *fn_8016D208(ItemBoxSet *self, short flag) {
    if (self) {
        self->vtable = lbl_8049110C;
        if (self->modelA) {
            Object_DtorWithGXSync(self->modelA, 1);
        }
        if (self->modelB) {
            Object_DtorWithGXSync(self->modelB, 1);
        }
        if (self->archive) {
            Object_DtorWithGXSync(self->archive, 1);
        }
        if (self->slots) {
            MemoryManager_Free(self->slots);
        }
        DebugPrintf(lbl_8036D5A8);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
