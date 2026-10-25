/*
 * 0x8016B0A0..0x8016B32C: holder for a refcounted HSD object kept in
 * lbl_806D15B8 (field setters, release, (re)create).
 */

typedef struct HSDObjMethods {
    char pad[0x30];
    void (*release)(void *);
    void (*destroy)(void *);
} HSDObjMethods;

typedef struct HSDObj {
    HSDObjMethods *methods;
    unsigned short ref_count;
    char pad06[2];
    int mode;
    char pad0C[4];
    float f10;
    float f14;
} HSDObj;

extern HSDObj *lbl_806D15B8;
extern void fn_802DA5B0(HSDObj *);
extern HSDObj *fn_802DA8B8(void *);
extern HSDObj *fn_802DA86C(void);

static inline int ref_DEC(HSDObj *o) {
    unsigned char ret = o->ref_count == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    ret = o->ref_count-- == 0;
    return ret;
}

static inline void HSDObj_Destroy(HSDObj *o) {
    if (o) {
        o->methods->release(o);
        o->methods->destroy(o);
    }
}

static inline void HSDObj_Release(HSDObj *o) {
    if (o) {
        if (ref_DEC(o)) {
            HSDObj_Destroy(o);
        }
    }
}

static inline void Holder_Release(void) {
    if (lbl_806D15B8) {
        fn_802DA5B0(0);
        HSDObj_Release(lbl_806D15B8);
    }
    lbl_806D15B8 = 0;
}

static inline void Holder_SetF14(HSDObj *o, float v) {
    if (o) {
        o->f14 = v;
    }
}

static inline void Holder_SetF10(HSDObj *o, float v) {
    if (o) {
        o->f10 = v;
    }
}

static inline void Holder_SetMode(HSDObj *o, int v) {
    if (o) {
        o->mode = v;
    }
}

#pragma exceptions on

void fn_8016B0A0(void) {
    fn_802DA5B0(0);
}

void fn_8016B0C4(void) {
    if (lbl_806D15B8) {
        fn_802DA5B0(lbl_806D15B8);
    }
}

typedef struct RGBA8 {
    unsigned char r, g, b, a;
} RGBA8;

extern const RGBA8 lbl_806DCF40;

static inline RGBA8 RGBA8_Make(unsigned char r, unsigned char g, unsigned char b) {
    RGBA8 c = lbl_806DCF40;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

static inline void Holder_SetColor(HSDObj *o, RGBA8 c) {
    if (o) {
        RGBA8 *dst = (RGBA8 *)((char *)o + 0x18);
        dst->r = c.r;
        dst->g = c.g;
        dst->b = c.b;
        dst->a = c.a;
    }
}

void fn_8016B0F0(unsigned char r, unsigned char g, unsigned char b) {
    HSDObj *o = lbl_806D15B8;
    if (o) {
        RGBA8 c = lbl_806DCF40;
        c.r = r;
        c.g = g;
        c.b = b;
        Holder_SetColor(o, c);
    }
}

void fn_8016B148(float v) {
    if (lbl_806D15B8) {
        Holder_SetF14(lbl_806D15B8, v);
    }
}

void fn_8016B160(float v) {
    if (lbl_806D15B8) {
        Holder_SetF10(lbl_806D15B8, v);
    }
}

void fn_8016B178(int v) {
    if (lbl_806D15B8) {
        Holder_SetMode(lbl_806D15B8, v);
    }
}

void fn_8016B190(void) {
    Holder_Release();
}

void fn_8016B248(void *desc) {
    if (lbl_806D15B8) {
        Holder_Release();
    }
    if (desc) {
        lbl_806D15B8 = fn_802DA8B8(desc);
    } else {
        lbl_806D15B8 = fn_802DA86C();
    }
}

#pragma exceptions reset
