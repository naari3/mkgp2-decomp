/*
 * 0x8016D79C..0x8016D920: marker model draw over a JObj chain, exec, and
 * the deleting destructor (vtable lbl_80491134, base vtable lbl_80490FE0).
 */

struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[0x8];
    HSD_JObj *next;
    char pad0C[0x2C];
    Vec3f translate;
};

struct MarkerChain {
    void *vtable;
    void *model;
    HSD_JObj *chain;
};

extern "C" {
extern char lbl_806D8B48[7];
extern char lbl_806D8B50[5];
extern char lbl_80491134[];
extern char lbl_80490FE0[];
extern char lbl_8036D640[];
void __assert(char *, int, char *);
unsigned char fn_801379F0(Vec3f *, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_RenderJObjTree(void *, int);
void clNormal3D_Exec(void *);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *out) {
    if (jobj == 0) {
        __assert(lbl_806D8B48, 0x3E4, lbl_806D8B50);
    }
    out->x = jobj->translate.x;
    out->y = jobj->translate.y;
    out->z = jobj->translate.z;
}

extern "C" {

void fn_8016D79C(MarkerChain *self) {
    HSD_JObj *jobj;
    Vec3f pos;

    if (self->model == 0) {
        return;
    }
    for (jobj = self->chain; jobj != 0; jobj = jobj->next) {
        HSD_JObjGetTranslation(jobj, &pos);
        pos.y += 8.0f;
        if (fn_801379F0(&pos, 10.0f)) {
            Object_SetJObjPositionVec(self->model, &pos);
            Object_RenderJObjTree(self->model, 7);
        }
    }
}

void fn_8016D864(MarkerChain *self) {
    if (self->model) {
        clNormal3D_Exec(self->model);
    }
}

MarkerChain *fn_8016D890(MarkerChain *self, short flag) {
    if (self) {
        self->vtable = lbl_80491134;
        if (self->model) {
            Object_DtorWithGXSync(self->model, 1);
        }
        DebugPrintf(lbl_8036D640);
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
