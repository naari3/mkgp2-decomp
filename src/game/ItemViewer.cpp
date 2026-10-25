/*
 * clItemViewer @ 0x80254398..0x80255000 (vtable lbl_804F211C): debug item
 * model viewer scene. The stick edits the selected field (position,
 * rotation, scale, light color, or the item number itself), Y toggles the
 * field list and B leaves.
 *
 * Base class clSceneInterface has vtable lbl_803FE0C8 (dtor dtor_8007D0D4).
 * The longer strings sit in this unit's .rodata pool at lbl_803F1208 and are
 * referenced as lbl_803F1208 + offset, the way the compiler addressed them.
 */

#include "game/FlowScene.h"

struct ShowModel {
    ShowModel(void *res, int flag);
    virtual ~ShowModel();
    virtual void Render();
    virtual void _keyM();
    char pad[0x20 - 0x4];
};

struct ShowXform {
    float pos[3];
    float rot[3];
    float scale;
};

struct ViewerEntry {
    const char *file;
    ShowXform xf;
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

struct InfoText {
    char pad00[0x20];
    unsigned int color;
    char pad24[0x230 - 0x24];
    InfoText();
    TextManager *tm() { return (TextManager *)this; }
};

extern "C" {
extern const char lbl_803F1208[];
extern const ViewerEntry lbl_803F1234[];
extern float lbl_806D0A70;
extern float lbl_806D0A74;
extern float lbl_806D0A78;
extern const char lbl_806DC1E8[2];
extern const char lbl_806DC218[8];
void *ItemRes_LookupByKey_Thunk(int key);
ShowXform *fn_8013BE98(int item);
void fn_8013D59C(ShowModel *m, float x, float y, float z);
void fn_8013D608(ShowModel *m, float x, float y, float z);
void fn_8013D634(ShowModel *m, float x, float y, float z);
void fn_8013D660(ShowModel *m, float x, float y);
void fn_8013D738(ShowModel *m, float a, float b);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
const char *fn_8023DAA8(int item);
void DebugPrintf(const char *fmt, ...);
void fn_8011FAFC(ResCtrl *rc, int a);
void fn_8011F994(int mode);
void fn_8011FAB8(void);
void *fn_801F8E58(void);
void fn_801F8A34(void *ctx, InfoText *text, int a);
}

struct clSceneInterface {
    clSceneInterface() : done(0) {}
    virtual ~clSceneInterface() {}
    virtual void Release() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void _keyS();
    unsigned char done;
};

struct clItemViewer : clSceneInterface {
    int item;
    ShowModel *model;
    int field;
    unsigned char showInfo;
    int printWait;
    float pos[3];
    float rot[3];
    float scale;
    float color[3];

    clItemViewer() : item(1), model(0), field(0), showInfo(1), printWait(0) {
        color[0] = lbl_806D0A70;
        color[1] = lbl_806D0A74;
        color[2] = lbl_806D0A78;
        LoadModel();
    }
    ~clItemViewer();
    void Release();
    void Update();
    void Draw();
    void LoadModel();
    virtual void _key();
};

/* Wraps an angle into [0, 360). */
static inline float WrapAngle(float v) {
    if (v >= 360.0f) {
        v -= 360.0f;
    }
    if (v < 0.0f) {
        v += 360.0f;
    }
    return v;
}

/* Wraps a color channel into [0, 1). */
static inline float WrapUnit(float v) {
    if (v >= 1.0f) {
        v -= 1.0f;
    }
    if (v < 0.0f) {
        v += 1.0f;
    }
    return v;
}

extern "C" clItemViewer *fn_80254F74(void) {
    return new clItemViewer;
}

void clItemViewer::Release() {
    delete this;
}

clItemViewer::~clItemViewer() {
    if (model) {
        delete model;
        model = 0;
    }
}

void clItemViewer::Update() {
    const char *strs = lbl_803F1208;
    InputPlayer *pad;
    float d;
    if (done == 1) {
        return;
    }
    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    d = pad->StickLeft();
    d = pad->StickRight() - d;
    if (pad->Pressed(0x800)) {
        field++;
        if (field > 10) {
            field = 0;
        }
    }
    if (pad->Pressed(0x2000)) {
        showInfo = showInfo != 1;
    }
    if (pad->Pressed(0x400)) {
        done = 1;
    }
    if (printWait > 0) {
        printWait--;
    }
    if (0.0f != d) {
        switch (field) {
        case 0:
            pos[0] += 0.1f * d;
            break;
        case 1:
            pos[1] += 0.1f * d;
            break;
        case 2:
            pos[2] += 0.1f * d;
            break;
        case 3:
            rot[0] += 3.0f * d;
            rot[0] = WrapAngle(rot[0]);
            break;
        case 4:
            rot[1] += 3.0f * d;
            rot[1] = WrapAngle(rot[1]);
            break;
        case 5:
            rot[2] += 3.0f * d;
            rot[2] = WrapAngle(rot[2]);
            break;
        case 6:
            scale += 0.01f * d;
            break;
        case 7:
            color[0] += 0.01f * d;
            color[0] = WrapUnit(color[0]);
            break;
        case 8:
            color[1] += 0.01f * d;
            color[1] = WrapUnit(color[1]);
            break;
        case 9:
            color[2] += 0.01f * d;
            color[2] = WrapUnit(color[2]);
            break;
        case 10:
            if (printWait <= 0) {
                printWait = 10;
                DebugPrintf(lbl_806DC1E8);
                DebugPrintf(strs + 0x90); /* "[ItemTrans]\n" */
                DebugPrintf(strs + 0xA0, fn_8023DAA8(item)); /* "ItemName = %s\n" */
                DebugPrintf(strs + 0xB0, pos[0]);
                DebugPrintf(strs + 0xBC, pos[1]);
                DebugPrintf(strs + 0xC8, pos[2]);
                DebugPrintf(strs + 0xD4, rot[0]);
                DebugPrintf(strs + 0xE0, rot[1]);
                DebugPrintf(strs + 0xEC, rot[2]);
                DebugPrintf(strs + 0xF8, scale);
                item += d > 0.0f ? 1 : -1;
                if (item >= 0xA1) {
                    item = 0;
                }
                if (item <= 0) {
                    item = 0xA0;
                }
                LoadModel();
            }
            break;
        }
    }
    if (model) {
        float s = 0.02f * scale;
        fn_8013D634(model, 0.02f * pos[0], 0.02f * pos[1], 0.02f * pos[2]);
        fn_8013D59C(model, 0.017453292f * rot[0], 0.017453292f * rot[1], 0.017453292f * rot[2]);
        fn_8013D608(model, s, s, s);
    }
}

void clItemViewer::Draw() {
    const char *strs = lbl_803F1208;
    ResCtrl rc;
    unsigned int c;
    rc.mode = 2;
    rc.SetSize(640.0f, 480.0f);
    rc.Show(320.0f, 240.0f, 1.0f);
    c = ((unsigned char)(int)(255.0f * color[0]) << 24) |
        ((unsigned char)(int)(255.0f * color[1]) << 16) |
        ((unsigned char)(int)(255.0f * color[2]) << 8) | 0xFF;
    rc.SetColor(c);
    fn_8011FAFC(&rc, 0);
    fn_8011F994(0);
    if (model) {
        model->Render();
    }
    if (showInfo == 1) {
        void *ctx = fn_801F8E58();
        InfoText text;
        text.color = 0xFFFFFFFF;
        fn_801F93EC(text.tm(), 20.0f, 20.0f * field + 50.0f);
        TexMgr_SetTexture(text.tm(), lbl_806DC218);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 50.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x104, pos[0]); /* "Pos   x=%3.1f" */
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 70.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x114, pos[1]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 90.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x124, pos[2]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 110.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x134, rot[0]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 130.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x144, rot[1]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 150.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x154, rot[2]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 170.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x164, scale); /* "Scale  =%2.2f" */
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 190.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x174, color[0]); /* "Color r=%1.2f" */
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 210.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x184, color[1]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 230.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x194, color[2]);
        fn_801F8A34(ctx, &text, 7);
        fn_801F93EC(text.tm(), 50.0f, 250.0f);
        TexMgr_SetTexture(text.tm(), strs + 0x1A4); /* "Next Item" */
        fn_801F8A34(ctx, &text, 7);
    }
    fn_8011FAB8();
}

void clItemViewer::LoadModel() {
    float s;
    if (model) {
        delete model;
        model = 0;
    }
    if (item < 0x9F) {
        ShowXform *xf = fn_8013BE98(item);
        s = 0.02f * xf->scale;
        model = new ShowModel(ItemRes_LookupByKey_Thunk(item), 0);
        fn_8013D738(model, 0.0f, 1.0f);
        fn_8013D660(model, 320.0f, 240.0f);
        fn_8013D634(model, 0.02f * xf->pos[0], 0.02f * xf->pos[1], 0.02f * xf->pos[2]);
        fn_8013D59C(model, 0.017453292f * xf->rot[0], 0.017453292f * xf->rot[1], 0.017453292f * xf->rot[2]);
        fn_8013D608(model, s, s, s);
        pos[0] = xf->pos[0];
        pos[1] = xf->pos[1];
        pos[2] = xf->pos[2];
        rot[0] = xf->rot[0];
        rot[1] = xf->rot[1];
        rot[2] = xf->rot[2];
        scale = xf->scale;
    } else {
        const ViewerEntry *e = &lbl_803F1234[item - 0x9F];
        s = 0.02f * e->xf.scale;
        model = new ShowModel((void *)e->file, 0);
        fn_8013D738(model, 0.0f, 1.0f);
        fn_8013D660(model, 320.0f, 240.0f);
        fn_8013D634(model, 0.02f * e->xf.pos[0], 0.02f * e->xf.pos[1], 0.02f * e->xf.pos[2]);
        fn_8013D59C(model, 0.017453292f * e->xf.rot[0], 0.017453292f * e->xf.rot[1], 0.017453292f * e->xf.rot[2]);
        fn_8013D608(model, s, s, s);
        pos[0] = e->xf.pos[0];
        pos[1] = e->xf.pos[1];
        pos[2] = e->xf.pos[2];
        rot[0] = e->xf.rot[0];
        rot[1] = e->xf.rot[1];
        rot[2] = e->xf.rot[2];
        scale = e->xf.scale;
    }
}
