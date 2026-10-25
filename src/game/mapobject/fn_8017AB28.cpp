struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[0x38];
    Vec3f translate;
};

struct AnimDef {
    char pad00[0x8];
    float radius;
    char pad0C[0x4];
    unsigned int flags;
};

struct AnimObj {
    void *next;
    AnimDef *def;
    HSD_JObj *jobj;
    float frame;
    Vec3f offset;
};

extern "C" {
extern char lbl_806D8EA8[7];
extern char lbl_806D8EB0[5];
extern float lbl_806D15F0;
void __assert(char *, int, char *);
void HSD_JObjReqAnimAll(HSD_JObj *, float);
void fn_802CF244(HSD_JObj *);
void fn_802CF3B0(HSD_JObj *, int, int, int);
void PSVECAdd(const Vec3f *, const Vec3f *, Vec3f *);
unsigned char fn_80137718(Vec3f *pos, Vec3f *view, float radius);
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *translate) {
    if (jobj == 0) {
        __assert(lbl_806D8EA8, 0x3E4, lbl_806D8EB0);
    }
    *translate = jobj->translate;
}

extern "C" void fn_8017AB28(AnimObj *self) {
    HSD_JObj *jobj = self->jobj;
    Vec3f pos;
    Vec3f view;
    if (jobj == 0) {
        return;
    }
    if (self->def->flags & 2) {
        if (self->def->flags & 1) {
            HSD_JObjReqAnimAll(jobj, self->frame);
            fn_802CF244(self->jobj);
        }
        fn_802CF3B0(self->jobj, 0, 7, 0);
        return;
    }
    HSD_JObjGetTranslation(jobj, &pos);
    PSVECAdd(&pos, &self->offset, &pos);
    if (fn_80137718(&pos, &view, self->def->radius)) {
        if ((self->def->flags & 1) && view.z > self->def->radius * lbl_806D15F0) {
            HSD_JObjReqAnimAll(self->jobj, self->frame);
            fn_802CF244(self->jobj);
        }
        fn_802CF3B0(self->jobj, 0, 7, 0);
    }
}
