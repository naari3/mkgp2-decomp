/*
 * 0x801709FC..0x80170B5C: deleting destructor of the grow-in entry set
 * (vtable lbl_8049128C, base vtable lbl_80490FE0).
 */

struct GrowEntry {
    void *jobj;
    void *faces;
    int faceCount;
    void *anim;
    int state;
    float t;
    float scale;
    void *sub;
};

struct GrowSet {
    void *vtable;
    void *model;
    GrowEntry *entries;
    int count;
};

extern "C" {
extern char lbl_8049128C[];
extern char lbl_80490FE0[];
extern char lbl_8036E674[];
void Object_DtorWithGXSync(void *, int);
void fn_80123B48(void *, int);
void *fn_8016F9A0(void *, short);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

GrowSet *fn_801709FC(GrowSet *self, short flag) {
    int i;

    if (self) {
        self->vtable = lbl_8049128C;
        if (self->model) {
            Object_DtorWithGXSync(self->model, 1);
        }
        if (self->entries) {
            for (i = 0; i < self->count; i++) {
                if (self->entries[i].faces) {
                    MemoryManager_Free(self->entries[i].faces);
                    self->entries[i].faces = 0;
                    self->entries[i].faceCount = 0;
                }
                if (self->entries[i].anim) {
                    fn_80123B48(self->entries[i].anim, 1);
                    self->entries[i].anim = 0;
                }
                if (self->entries[i].sub) {
                    fn_8016F9A0(self->entries[i].sub, 1);
                    self->entries[i].sub = 0;
                }
            }
            MemoryManager_Free(self->entries);
        }
        DebugPrintf(lbl_8036E674);
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
