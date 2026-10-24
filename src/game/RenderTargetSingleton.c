/*
 * Ref-counted render-target singleton used by the kart preview
 * (0x8013C334..0x8013C4A4), same shape as OrthoCam.
 */

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad18[0x44 - 0x18];
    unsigned char anim[1];
} HSD_JObj;

typedef struct RenderTargetHolder {
    unsigned char active;
    void *rt;
} RenderTargetHolder;

typedef struct CharacterData {
    int pad0;
    void *driver_model;
    void *kart_model;
    int pad0C[4];
    float anim1C;
    float pad20;
    float anim24;
} CharacterData;

typedef struct KartPreview {
    void *vtbl;
    void *kart;
    void *obj8;
    void *driver;
    void *obj10;
    void *anims14[4];
    void *obj24;
    HSD_JObj *jobj28;
    HSD_JObj *jobj2C;
    HSD_JObj *jobj30;
    HSD_JObj *jobj34;
    HSD_JObj *jobj38;
    HSD_JObj *jobj3C;
    HSD_JObj *jobj40;
    HSD_JObj *jobj44;
    int chara;
    int anim_state;
    float frame;
    float end_frame;
    unsigned char pad58[0x88 - 0x58];
    float view_x;
    float view_y;
} KartPreview;

extern unsigned int lbl_806D1558;
extern RenderTargetHolder *lbl_806D155C;
extern char lbl_8048EA78[];
extern char lbl_806D76D0[];
extern char lbl_806D76D8[];
extern float lbl_806D76E0;
extern float lbl_806D76E4;
extern char lbl_8048EAD8[];
extern char lbl_8048EAE8[];

extern void fn_802C5674(int);
extern void fn_802C53C8(void *rt);
extern void fn_802C5A5C(void *rt);
extern void *RenderTarget_Create(void *desc);
extern void *Alloc(unsigned int size);
extern void MemoryManager_TimedFree(void *p);
extern void Object_SetColorAlphaOnly(void *obj, int, float a);
extern void Object_SetColorRGBA(void *obj, int, float r, float g, float b, float a);
extern void Object_SetJObjRotationY(void *obj, float r);
extern void Object_SetJObjRotationX(void *obj, float r);
extern void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
extern void *fn_8013BC98(void);
extern void fn_8013BB1C(void *cam, float x, float y);
extern unsigned char fn_8013BC38(void *cam);
extern void fn_8013BBFC(void *cam);
extern void fn_8013BB9C(void *cam);
extern void fn_8013BCA0(void);
extern void Object_RenderJObjTree(void *obj, int flags);
extern void __assert(char *file, int line, char *expr);
extern void fn_802D1E34(HSD_JObj *jobj);
extern void Object_SetAnimBinding(void *obj, void *anim, int);
extern void Object_DriveAnimMatrix(void *obj);
extern void clNormal3D_SetScale(void *obj, void *anim, float frame, float a, float b, float c);
extern void *Archive_GetRootJObj(void *obj);
extern void ObjectTree_BlendOrCopy_Timed(void *obj, void *a, void *b, int, float t);
extern void clNormal3D_Exec(void *obj);
extern CharacterData *GetCharacterDataEntry(int chara);
extern void fn_802D0B48(HSD_JObj *jobj, int flags);
extern void fn_802D07D4(HSD_JObj *jobj, int flags);
extern void Object_DtorWithGXSync(void *obj, int flag);

void fn_8013C334(RenderTargetHolder *h) {
    if (h->active) {
        h->active = 0;
    }
}

int fn_8013C34C(RenderTargetHolder *h) {
    if (!h->rt) {
        return 0;
    }
    if (h->active) {
        return 1;
    }
    fn_802C5674(0);
    fn_802C53C8(h->rt);
    h->active = 1;
    return 1;
}

RenderTargetHolder *fn_8013C3B8(void) {
    return lbl_806D155C;
}

static inline void RenderTargetHolder_Free(RenderTargetHolder *h) {
    if (h) {
        if (h->rt) {
            fn_802C5A5C(h->rt);
        }
        MemoryManager_TimedFree(h);
    }
}

void fn_8013C3C0(void) {
    if (lbl_806D1558 != 0) {
        if (--lbl_806D1558 == 0) {
            RenderTargetHolder_Free(lbl_806D155C);
            lbl_806D155C = 0;
        }
    }
}

#pragma cplusplus on
void *operator new(unsigned long size);
void operator delete(void *p);
struct RenderTargetObj {
    unsigned char active;
    void *rt;
    RenderTargetObj() {
        active = 0;
        rt = RenderTarget_Create(lbl_8048EA78);
    }
};

extern "C" int fn_8013C428(void) {
    if (lbl_806D1558 == 0) {
        RenderTargetObj *h = new RenderTargetObj;
        lbl_806D155C = (RenderTargetHolder *)h;
        if (h == 0) {
            return 0;
        }
    }
    lbl_806D1558++;
    return 1;
}
#pragma cplusplus reset

