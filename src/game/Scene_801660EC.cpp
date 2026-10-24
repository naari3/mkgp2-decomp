/*
 * 0x801660EC..0x801661FC: deleting destructor of the parameter-dump scene
 * (vtable lbl_80490F0C, base chain lbl_8048ED10 -> lbl_8048ECF8). Dumps
 * the 0x115-entry parameter table before freeing it.
 */

struct VObj {
    virtual ~VObj();
};

typedef struct ParamEntry {
    float v[7];
} ParamEntry;

struct ParamDumpScene {
    void *vtable;
    char pad04[0x18];
    VObj *obj1C;
    char pad20[0xC];
    ParamEntry *table;
};

extern "C" {
extern char lbl_80490F0C[];
extern char lbl_8048ED10[];
extern char lbl_8048ECF8[];
extern char lbl_8036A210[];
extern char lbl_8036A24C[];
extern char lbl_806D8924[4];
extern void fn_8013DB9C(void);
extern void DebugPrintf(const char *, ...);
extern void MemoryManager_Free(void *);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

ParamDumpScene *fn_801660EC(ParamDumpScene *self, short flag) {
    int i;

    if (self) {
        self->vtable = lbl_80490F0C;
        fn_8013DB9C();
        if (self->obj1C) {
            delete self->obj1C;
        }
        DebugPrintf(lbl_8036A210);
        for (i = 0; i < 0x115; i++) {
            ParamEntry *e = &self->table[i];
            DebugPrintf(lbl_8036A24C, e->v[0], e->v[1], e->v[2], e->v[3], e->v[4], e->v[5], e->v[6]);
        }
        DebugPrintf(lbl_806D8924);
        MemoryManager_Free(self->table);
        if (self) {
            self->vtable = lbl_8048ED10;
            if (self) {
                self->vtable = lbl_8048ECF8;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
