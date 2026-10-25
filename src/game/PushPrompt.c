/*
 * A "push button" prompt effect on the shared sprite-effect base
 * (vtable lbl_8048ED34): it zooms in, waits for a button press (or a
 * timeout), then zooms out and finishes. The base declares a virtual
 * that is not defined here first, so neither vtable is emitted.
 *
 * Still asm: the update (float register assignment).
 */
#pragma cplusplus on

typedef struct { char c[256]; } TextBuf;
typedef struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;
extern "C" void *__va_arg(va_list v_list, int type);
#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_end(ap) ((void)0)

extern "C" {
extern char lbl_8048EB44[];
extern char lbl_8048ED34[];
extern const TextBuf lbl_803607A8;
extern const float lbl_806D7998, lbl_806D799C, lbl_806D79A0, lbl_806D79A4;
extern const float lbl_806D79A8, lbl_806D79AC, lbl_806D79B0, lbl_806D79B4;
extern const float lbl_806D79B8, lbl_806D79BC, lbl_806D79C0, lbl_806D79C4;
extern const float lbl_806D79C8, lbl_806D79CC, lbl_806D79D0, lbl_806D79D4;
extern const float lbl_806D79D8, lbl_806D79DC, lbl_806D79E0, lbl_806D79E4;
extern const float lbl_806D79E8, lbl_806D79EC, lbl_806D79F0, lbl_806D79F4;
extern const float lbl_806D79F8, lbl_806D79FC, lbl_806D7A00, lbl_806D7A04;
extern const float lbl_806D7A08, lbl_806D7A0C, lbl_806D7A10;
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_80169334(void *obj, int id, int flag, float x, float y, float sx, float sy, float a);
extern void fn_801681E8(void *obj, const char *text, float x, float y, float sx, float sy, float r, float g, float b, float a, ...);
extern int vsprintf(char *buf, const char *fmt, va_list args);
extern void fn_80167440(void *p);
extern void fn_801673A8(void *p);
extern void fn_801674AC(void *p);
extern void fn_801675A4(void *p);
extern void fn_801676AC(void *p, int flag);
extern void fn_80120A08(int id);
extern void SetRumbleMode(unsigned int ch, unsigned int mode, int duration);
}

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

extern "C" {
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *, int);
}

extern "C" {
asm void fn_80141B08(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80141B08[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80141B08 = {
    (void *)&fn_80141B08, 0x00000368, (void *)extab_fn_80141B08
};

}


struct SpriteAnim {
    void *data;
    int f4;
    int f8;
    SpriteAnim(int a);
};

struct FxData {
    void *obj;
    unsigned char active;
    float x, y;
    float alpha;
};

struct FxBase : FxData {
    FxBase() {
        obj = 0;
        active = 0;
        x = lbl_806D79A8;
        y = lbl_806D79A8;
        alpha = lbl_806D7998;
    }
    virtual ~FxBase() {}
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};

struct PushPrompt : FxBase {
    int state;
    float t;
    float px, py;
    float sx, sy;
    float px2, py2;
    float sx2, sy2;
    float fade;
    SpriteAnim *anim;

    virtual void m0C();
    PushPrompt();
    virtual ~PushPrompt();
    virtual void Draw();
    virtual void m1C();
    virtual void m20();
    void Print(float x, float y, float w, float h, float r, float g, float b, float a, const char *fmt, ...);
    void Put(int id, int flag, float x, float y, float w, float h, float r, float g, float b, float a);
};

void PushPrompt::m20() {
}

void PushPrompt::m1C() {
    fn_801674AC(anim);
}

void PushPrompt::Draw() {
    if (state != 3) {
        fn_80169334(obj, 0x57F, 0, px, py, sx, sy, fade);
        m20();
        fn_801675A4(anim);
    }
}

extern "C" asm void fn_80141B08(void) { /* 0x80141B08 size:0x368 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x3
    beq fn_80141B08_L_80141E5C
    lfs f0, 0x1c(r31)
    lfs f5, lbl_806D7998(r2)
    fadds f0, f0, f5
    stfs f0, 0x1c(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x1
    beq fn_80141B08_L_80141C60
    bge fn_80141B08_L_80141B54
    cmpwi r0, 0x0
    bge fn_80141B08_L_80141B60
    b fn_80141B08_L_80141E24
    fn_80141B08_L_80141B54:
    cmpwi r0, 0x3
    bge fn_80141B08_L_80141E24
    b fn_80141B08_L_80141D20
    fn_80141B08_L_80141B60:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D799C(r2)
    fcmpo cr0, f1, f0
    bge fn_80141B08_L_80141BCC
    lfs f0, lbl_806D79A0(r2)
    lfs f2, lbl_806D79A4(r2)
    fmuls f7, f0, f1
    lfs f5, lbl_806D79A8(r2)
    lfs f1, lbl_806D79B0(r2)
    lfs f0, lbl_806D79AC(r2)
    fmuls f6, f2, f7
    lfs f3, lbl_806D79B8(r2)
    lfs f2, lbl_806D79B4(r2)
    fmadds f4, f1, f7, f0
    lfs f1, lbl_806D79C0(r2)
    stfs f6, 0x30(r31)
    lfs f0, lbl_806D79BC(r2)
    fmadds f2, f3, f7, f2
    stfs f6, 0x34(r31)
    fmadds f0, f1, f7, f0
    stfs f5, 0x20(r31)
    stfs f5, 0x24(r31)
    stfs f4, 0x38(r31)
    stfs f2, 0x3c(r31)
    stfs f0, 0x28(r31)
    stfs f0, 0x2c(r31)
    b fn_80141B08_L_80141C28
    fn_80141B08_L_80141BCC:
    fsubs f0, f1, f0
    lfs f1, lbl_806D79C4(r2)
    lfs f2, lbl_806D79A4(r2)
    lfs f5, lbl_806D79A8(r2)
    fmuls f7, f1, f0
    lfs f1, lbl_806D79CC(r2)
    lfs f0, lbl_806D79C8(r2)
    lfs f3, lbl_806D79D4(r2)
    fnmsubs f6, f2, f7, f2
    lfs f2, lbl_806D79D0(r2)
    fmadds f4, f1, f7, f0
    lfs f1, lbl_806D79D8(r2)
    lfs f0, lbl_806D79AC(r2)
    fmadds f2, f3, f7, f2
    stfs f6, 0x30(r31)
    fmadds f0, f1, f7, f0
    stfs f6, 0x34(r31)
    stfs f5, 0x20(r31)
    stfs f5, 0x24(r31)
    stfs f4, 0x38(r31)
    stfs f2, 0x3c(r31)
    stfs f0, 0x28(r31)
    stfs f0, 0x2c(r31)
    fn_80141B08_L_80141C28:
    lfs f1, lbl_806D7998(r2)
    lfs f0, lbl_806D79DC(r2)
    stfs f1, 0x40(r31)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80141B08_L_80141E24
    li r0, 0x1
    lfs f0, lbl_806D79A8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    lwz r3, 0x44(r31)
    bl fn_80167440
    b fn_80141B08_L_80141E24
    fn_80141B08_L_80141C60:
    lfs f3, lbl_806D79A8(r2)
    lfs f2, lbl_806D79E0(r2)
    stfs f3, 0x20(r31)
    lfs f1, lbl_806D79E4(r2)
    stfs f3, 0x24(r31)
    lfs f0, lbl_806D79E8(r2)
    stfs f3, 0x30(r31)
    stfs f3, 0x34(r31)
    stfs f2, 0x38(r31)
    stfs f1, 0x3c(r31)
    stfs f5, 0x28(r31)
    stfs f5, 0x2c(r31)
    stfs f5, 0x40(r31)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    beq fn_80141B08_L_80141CF4
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x100
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne fn_80141B08_L_80141CF4
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x2000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80141B08_L_80141E24
    fn_80141B08_L_80141CF4:
    li r0, 0x2
    lfs f0, lbl_806D79A8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    lwz r3, 0x44(r31)
    bl fn_801673A8
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    b fn_80141B08_L_80141E24
    fn_80141B08_L_80141D20:
    lfs f2, 0x1c(r31)
    lfs f0, lbl_806D79EC(r2)
    fcmpo cr0, f2, f0
    bge fn_80141B08_L_80141D88
    lfs f0, lbl_806D79C4(r2)
    lfs f1, lbl_806D79A4(r2)
    fmuls f7, f0, f2
    lfs f0, lbl_806D79F8(r2)
    lfs f4, lbl_806D79A8(r2)
    lfs f3, lbl_806D79F0(r2)
    fmuls f6, f1, f7
    lfs f2, lbl_806D79E0(r2)
    lfs f1, lbl_806D79F4(r2)
    fmadds f5, f0, f7, f5
    lfs f0, lbl_806D79E4(r2)
    fmadds f2, f3, f7, f2
    stfs f6, 0x30(r31)
    fmadds f0, f1, f7, f0
    stfs f6, 0x34(r31)
    stfs f4, 0x20(r31)
    stfs f4, 0x24(r31)
    stfs f2, 0x38(r31)
    stfs f0, 0x3c(r31)
    stfs f5, 0x28(r31)
    stfs f5, 0x2c(r31)
    b fn_80141B08_L_80141DE4
    fn_80141B08_L_80141D88:
    fsubs f0, f2, f0
    lfs f1, lbl_806D79A0(r2)
    lfs f2, lbl_806D79A4(r2)
    lfs f5, lbl_806D79A8(r2)
    fmuls f7, f1, f0
    lfs f1, lbl_806D79FC(r2)
    lfs f0, lbl_806D79C8(r2)
    lfs f3, lbl_806D7A00(r2)
    fnmsubs f6, f2, f7, f2
    lfs f2, lbl_806D79D0(r2)
    fmadds f4, f1, f7, f0
    lfs f1, lbl_806D7A04(r2)
    lfs f0, lbl_806D79AC(r2)
    fmadds f2, f3, f7, f2
    stfs f6, 0x30(r31)
    fmadds f0, f1, f7, f0
    stfs f6, 0x34(r31)
    stfs f5, 0x20(r31)
    stfs f5, 0x24(r31)
    stfs f4, 0x38(r31)
    stfs f2, 0x3c(r31)
    stfs f0, 0x28(r31)
    stfs f0, 0x2c(r31)
    fn_80141B08_L_80141DE4:
    lfs f3, lbl_806D7A08(r2)
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D7998(r2)
    lfs f0, lbl_806D79DC(r2)
    fnmsubs f1, f3, f2, f1
    stfs f1, 0x40(r31)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80141B08_L_80141E24
    li r0, 0x3
    lfs f0, lbl_806D79A8(r2)
    stw r0, 0x18(r31)
    li r0, 0x1
    stfs f0, 0x1c(r31)
    stb r0, 0x4(r31)
    fn_80141B08_L_80141E24:
    lfs f0, 0x20(r31)
    lfs f2, lbl_806D7A0C(r2)
    lfs f1, lbl_806D7A10(r2)
    fadds f0, f0, f2
    stfs f0, 0x20(r31)
    lfs f0, 0x24(r31)
    fadds f0, f0, f1
    stfs f0, 0x24(r31)
    lfs f0, 0x30(r31)
    fadds f0, f0, f2
    stfs f0, 0x30(r31)
    lfs f0, 0x34(r31)
    fadds f0, f0, f1
    stfs f0, 0x34(r31)
    fn_80141B08_L_80141E5C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void PushPrompt::Print(float x, float y, float w, float h, float r, float g, float b, float a, const char *fmt, ...) {
    va_list args;
    TextBuf buf = lbl_803607A8;
    va_start(args, fmt);
    vsprintf(buf.c, fmt, args);
    fn_801681E8(obj, buf.c, x * sx + px, y * sy + py, w * sy, h * sy, r, g, b, a * fade);
}

void PushPrompt::Put(int id, int flag, float x, float y, float w, float h, float r, float g, float b, float a) {
    fn_8016918C(obj, id, flag, x * sx + px, y * sy + py, w * sy, h * sy, r, g, b, a * fade);
}

PushPrompt::~PushPrompt() {
    fn_80120A08(0x57F);
    fn_801676AC(anim, 1);
}

PushPrompt::PushPrompt() {
    state = 0;
    t = lbl_806D79A8;
    anim = new SpriteAnim(0);
    px = lbl_806D7A0C;
    py = lbl_806D7A10;
    sx = lbl_806D79A8;
    sy = lbl_806D79A8;
    px2 = lbl_806D7A0C;
    py2 = lbl_806D7A10;
    sx2 = lbl_806D79A8;
    sy2 = lbl_806D79A8;
    fade = lbl_806D79A8;
}
