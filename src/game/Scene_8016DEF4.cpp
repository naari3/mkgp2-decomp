/*
 * 0x8016DEF4..0x8016E064: debris burst group queries and destructor.
 */

struct Debris;

struct DebrisGroup {
    void *root;
    unsigned char active;
    char pad05[0x3];
    Debris *items;
};

struct SoundEmitter {
    virtual ~SoundEmitter();
};

struct DebrisBurst {
    void *model;
    DebrisGroup *groups;
    SoundEmitter *sound;
    int randIdx;
};

extern "C" {
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void Object_DtorWithGXSync(void *, int);

int fn_8016DEF4(DebrisBurst *self) {
    int n = 0;
    unsigned int g;

    for (g = 0; g < 4; g++) {
        if (self->groups[g].active == 1) {
            n++;
        }
    }
    return n;
}

int fn_8016DF50(DebrisBurst *self) {
    unsigned int g;

    for (g = 0; g < 4; g++) {
        if (self->groups[g].active == 0) {
            return 0;
        }
    }
    return 1;
}

DebrisBurst *fn_8016DFAC(DebrisBurst *self, short flag) {
    unsigned int g;

    if (self) {
        for (g = 0; g < 4; g++) {
            MemoryManager_Free(self->groups[g].items);
        }
        MemoryManager_Free(self->groups);
        Object_DtorWithGXSync(self->model, 1);
        delete self->sound;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
