/*
 * Orthographic HSD camera wrapper and its ref-counted singleton
 * (0x8013BA90..0x8013BE98). HSD_CObjSetFrustum takes (cobj, top, bottom, left,
 * right) like HSD_CObjSetOrtho.
 */

typedef struct HSDClassInfo {
    char pad[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
} HSDClassInfo;

typedef struct HSDObj {
    HSDClassInfo *info;
    unsigned short ref_count;
} HSDObj;

typedef struct CamView {
    unsigned char active;
    void *cobj;
    float a;
    float b;
    float c;
    float d;
} CamView;

typedef struct CamHolder {
    int pad0;
    HSDObj *obj;
} CamHolder;

extern float lbl_806D74A0;
extern float lbl_806D74A4;
extern float lbl_806D74A8;
extern float lbl_806D74AC;
extern float lbl_806D74B0;
extern float lbl_806D74B4;
extern float lbl_806D74B8;
extern float lbl_806D74BC;
extern unsigned int lbl_806D1550;
extern CamView *lbl_806D1554;
extern char lbl_8048E510[];

extern float HSD_CObjGetNear(void *cobj);
extern double atan(float x);
extern double tan(float x);
extern void HSD_CObjSetFrustum(void *cobj, float a, float b, float c, float d);
extern void HSD_CObjGetPerspective(void *cobj, float *a, float *b);
extern void *HSD_CObjLoadDesc(void *desc);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetupInit(void *cobj);
extern void HSD_CObjSetCurrent(void *cobj);
extern void *Alloc(unsigned int size);
extern void MemoryManager_TimedFree(void *p);

float fn_8013BA90(CamView *v) {
    if (v->cobj == 0) {
        return lbl_806D74A0;
    }
    return lbl_806D74A4 * (float)atan(v->c / HSD_CObjGetNear(v->cobj));
}

float fn_8013BAE8(CamView *v) {
    if (v->cobj == 0) {
        return lbl_806D74A0;
    }
    return (v->a - v->b) / (v->d - v->c);
}

void fn_8013BB1C(CamView *v, float x, float y) {
    float dx;
    float dy;
    if (v->cobj) {
        dx = ((x - lbl_806D74A8) / lbl_806D74AC) * (v->a - v->b);
        dy = ((y - lbl_806D74B0) / lbl_806D74B4) * (v->c - v->d);
        HSD_CObjSetFrustum(v->cobj, v->c + dy, v->d + dy, v->a + dx, v->b + dx);
    }
}

void fn_8013BB9C(CamView *v) {
    if (v->active) {
        HSD_CObjEndCurrent();
        if (v->cobj) {
            HSD_CObjSetFrustum(v->cobj, v->c, v->d, v->a, v->b);
        }
        v->active = 0;
    }
}

void fn_8013BBFC(CamView *v) {
    if (v->cobj && v->active) {
        HSD_LObjSetupInit(v->cobj);
    }
}

int fn_8013BC38(CamView *v) {
    void *cobj = v->cobj;
    if (cobj == 0) {
        return 0;
    }
    if (v->active) {
        return 1;
    }
    HSD_CObjSetCurrent(cobj);
    v->active = 1;
    return 1;
}

CamView *fn_8013BC98(void) {
    return lbl_806D1554;
}

static inline int HSDObj_RefDec(HSDObj *o) {
    unsigned char ret = o->ref_count == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return (unsigned char)(o->ref_count-- == 0);
}

static inline void HSDObj_Release(HSDObj *o) {
    if (o) {
        o->info->release(o);
        o->info->destroy(o);
    }
}

static inline void HSDObj_Unref(HSDObj *o) {
    if (o == 0) {
        return;
    }
    if (HSDObj_RefDec(o)) {
        HSDObj_Release(o);
    }
}

static inline void CamHolder_Free(CamHolder *h) {
    if (h) {
        if (h->obj) {
            HSDObj_Unref(h->obj);
        }
        MemoryManager_TimedFree(h);
    }
}

void fn_8013BCA0(void) {
    if (lbl_806D1550 != 0) {
        if (--lbl_806D1550 == 0) {
            CamHolder_Free((CamHolder *)lbl_806D1554);
            lbl_806D1554 = 0;
        }
    }
}

#pragma cplusplus on

void *operator new(unsigned long size);
void operator delete(void *p);

struct OrthoCamObj {
    unsigned char active;
    void *cobj;
    float a;
    float b;
    float c;
    float d;

    OrthoCamObj() {
        float sx;
        float sy;
        float aspect;
        active = 0;
        cobj = HSD_CObjLoadDesc(lbl_8048E510);
        if (cobj) {
            HSD_CObjGetPerspective(cobj, &sx, &sy);
            aspect = HSD_CObjGetNear(cobj);
            sx = tan(lbl_806D74B8 * (lbl_806D74BC * sx));
            b = aspect * (sx * sy);
            c = aspect * sx;
            a = -b;
            d = -c;
            HSD_CObjSetFrustum(cobj, c, d, a, b);
        }
    }
};

extern "C" int fn_8013BD7C(void) {
    if (lbl_806D1550 == 0) {
        OrthoCamObj *v = new OrthoCamObj;
        lbl_806D1554 = (CamView *)v;
        if (v == 0) {
            return 0;
        }
    }
    lbl_806D1550++;
    return 1;
}

#pragma cplusplus reset
