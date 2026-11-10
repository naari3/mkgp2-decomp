#include "game/singleton.h"

/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7B0C[1];
/*
 * 0x80144430..0x80146160: time attack ranking panel and its entry vector.
 */
#pragma cplusplus on

extern "C" void MemoryManager_TimedFree(void *p);
extern "C" void Sprite_Destroy(void *s, int flag);

struct SpriteObj {
    char pad0[4];
    int mode;
    char pad8[4];
    float fC, f10, f14, f18, f1C, f20;
};
struct Tween {
    unsigned char on;
    char pad1[3];
    float from, to, speed, t, value;
    Tween();
    float Get() { return value; }
    void Start(float a, float b, float s) {
        from = a;
        to = b;
        speed = s;
        t = 0.0f;
        value = a;
        on = 1;
    }
    void Update() {
        if (on == 1) {
            value = from * (1.0f - t) + to * t;
            t += speed;
            if (t > 1.0f) {
                t = 1.0f;
            }
        }
    }
};
class PanelItem {
public:
    PanelItem(SpriteObj *s, int d) : sprite(s), delay(d) {
        active = 0;
        flag85 = 0;
        for (int i = 0; i < 5; i++)
            tw[i].on = 0;
    }
    virtual ~PanelItem();
    virtual void Update();
    virtual void Draw();
    SpriteObj *sprite;
    int delay;
    Tween tw[5];
    unsigned char active;
    unsigned char flag85;
};

/* resource label (vtable lbl_8048EF20) */
class PanelIcon : public PanelItem {
public:
    PanelIcon(float x, float y, short id, int layer_, int delay = 0, unsigned char flip_ = 0)
        : PanelItem(0, delay), resId(id), layer(layer_), flip(flip_) {
        tw[3].Start(x, x, 1.0f);
        tw[4].Start(y, y, 1.0f);
    }
    virtual ~PanelIcon();
    short resId;
    char pad8A[2];
    int layer;
    unsigned char flip;
};
struct PanelEntry {
    char pad0[0xc];
    unsigned char on;
    char padD[3];
    float f10, f14, f18, f1c, f20;
};
struct PtrVecStorage {
    int cap;
    int size;
    PanelItem **data;
    ~PtrVecStorage() { if (data) MemoryManager_TimedFree(data); }
};
struct PtrVecBase : PtrVecStorage {
    ~PtrVecBase() {}
};
struct EntryVec : PtrVecBase {
    ~EntryVec() {}
    PanelItem **begin() { return data; }
    PanelItem **end() { return data + size; }
    void push_back(PanelItem *const &x);
};
struct Cursor {
    SpriteObj *sprite;
    unsigned char on;
    unsigned char state;
    char pad6[2];
    int timer;
};
struct CursorPtr {
    Cursor *p;
    Cursor *operator->() { return p; }
    ~CursorPtr() throw() {
        Cursor *c = p;
        if (c) {
            Sprite_Destroy(c->sprite, 1);
            MemoryManager_TimedFree(c);
        }
    }
};
struct RankPanel {
    char pad0[0x14];
    void **vt14;
    unsigned char visible;
    char pad19[3];
    float f1c;
    int state;
    unsigned char b24;
    char pad25[3];
    float xs[0x26];
    EntryVec vec;
    CursorPtr cursor;
};
struct Pair { char pad[0xc]; float a, b; };
struct SpriteHolder { void **vt; void *sprite; };
struct VecHolder { int pad0; int pad4; void *data; };

/* TOP-END */

extern "C" {
void fn_8011FAB8(void);
void fn_801A0004(void *s);
extern unsigned char IsCardValid(void);
extern void Sprite_AdvanceAnim(SpriteObj *s, float dt);
extern void fn_801699D8(int a, int b);
extern int g_reverseRoundFlag;
extern const float lbl_806D7AE0;
extern const float lbl_806D7AE4;
extern unsigned int lbl_806D7AE8;
extern unsigned int lbl_806D7AEC;
extern const float lbl_806D7AF0;
extern unsigned int lbl_806D7AF4;
extern const float lbl_806D7AF8;
extern unsigned int lbl_806D7B00;
extern const float RankPanel_80144430_rodata_80361DCC[2][3];
extern const float lbl_806D7B08;
void MemoryManager_TimedFree(void *p);
void Sprite_Destroy(void *s, int flag);
extern void __unexpected();
extern unsigned int lbl_8048EB44[];
extern unsigned int clCSPartsResultRecord_vtable_8048EEF4[];
extern void Alloc();
extern void Sprite_InitWithAnim();
extern void __construct_array();
extern int g_cupId;
extern int g_longRoundFlag;
extern void *lbl_806D10A0;
extern const float lbl_806D7B10;
extern const float lbl_806D7B14;
extern const float lbl_806D7B18;
extern const float lbl_806D7B1C;
extern const float lbl_806D7B20;
extern const float lbl_806D7B24;
extern const float lbl_806D7B28;
extern const float lbl_806D7B2C;
extern const float lbl_806D7B30;
extern const float lbl_806D7B34;
extern const float lbl_806D7B38;
extern const float lbl_806D7B3C;
extern const short RankPanel_80144430_rodata_80361D60[][2];
extern void *lbl_8048EF20[];
extern void *lbl_8048EF34[];
extern void ResCtrl_Init();
void fn_8011FAFC(struct ResCtrl *ctrl, int layer);
extern const float lbl_806D7B4C;
extern void dtor_80082960();
void *FUN_8003b120(unsigned long n);
void SharedPtr_Init(void *sp, void *p);
extern unsigned int lbl_803F5700[];
extern unsigned int lbl_803F5710[];
extern unsigned int lbl_8048EF68[];
extern void dtor_80038DD4();
extern void dtor_80038E30(struct ExcString *s, int flag);
void fn_80144430(RankPanel *self);
asm void fn_80144500(void);
void fn_801449D4(RankPanel *self);
void fn_80144ADC(RankPanel *self);
RankPanel *fn_80144AF0(RankPanel *self, short flag);
void fn_80144C1C(RankPanel *self);
void fn_801458A4(Pair *p);
SpriteHolder *fn_80145D34(SpriteHolder *self, short flag);
void fn_80145DA8(void);
void fn_80145DAC(void);
SpriteHolder *dtor_80145DB0(SpriteHolder *self, short flag);
void fn_80145E14(struct PanelIcon *self);
struct SpriteBoxPtr *dtor_80145F04(struct SpriteBoxPtr *self, short flag) throw();
VecHolder *dtor_80145F9C(VecHolder *self, short flag);
struct PanelEntry **fn_80146000(struct EntryVec *v, unsigned long id);
struct ExcObj *fn_801460D0(struct ExcObj *self, short flag);

#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_fn_80144500[8] = {
    0x39, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};













#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80144500 = {
    (void *)&fn_80144500, 0x000004D4, (void *)extab_fn_80144500
};













}

/* C++ view of the record panel for its constructors (fn_801458B4, fn_80145AF4). */
void *operator new(unsigned long size);
void operator delete(void *p);

struct Sprite {
    char pad0[0xc];
    float x, y;
    char pad14[0x1c];
    Sprite(int id, int a, int b);
    Sprite(int id, int a, float x, float y, float sx, float sy, float r, float rot);
    ~Sprite();
};
extern "C" {
extern const float lbl_806D7B40;
extern const float lbl_806D7B44;
extern short RankPanel_80144430_rodata_80361D80[];
void fn_8019FF8C(Sprite *s, int id, struct SpriteNodeInfo *out);
int isJapanese(void);
}
struct SpriteNodeInfo {
    float x, y;
    char rest[0x28];
};
struct RecCursor {
    Sprite *sprite;
    unsigned char on;
    unsigned char state;
    int timer;
    RecCursor() {
        on = 0;
        state = 0;
        timer = 0;
        sprite = new Sprite(0x9e, 1, 394.0f, 394.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    }
};
struct RecCursorPtr {
    RecCursor *p;
    RecCursorPtr(RecCursor *c) : p(c) {}
    ~RecCursorPtr() throw();
};
struct RecVec {
    int cap;
    int size;
    void **data;
    RecVec() : cap(0), size(0), data(0) {}
    ~RecVec();
};
struct clCSPartsInerface {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;
    clCSPartsInerface() {
        obj = 0;
        active = 0;
        x = lbl_806D7AE4;
        y = lbl_806D7AE4;
        alpha = lbl_806D7AF0;
    }
    virtual ~clCSPartsInerface();
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};
struct clCSPartsResultRecord : clCSPartsInerface {
    unsigned char visible;
    float f1c;
    int state;
    unsigned char b24;
    float xs[0x26];
    RecVec vec;
    RecCursorPtr cursor;
    virtual ~clCSPartsResultRecord();
    clCSPartsResultRecord();
    clCSPartsResultRecord(int a, int b, int c);
    void LoadColumns(Sprite *s) {
        for (int i = 0; i < 0x26; i++) {
            SpriteNodeInfo info;
            fn_8019FF8C(s, RankPanel_80144430_rodata_80361D80[i], &info);
            xs[i] = info.x;
        }
    }
};

static inline void DrawItem(PanelItem *p)
{
    if (p->active) {
        if (p->sprite) {
            fn_801A0004(p->sprite);
        }
        p->Draw();
        if (p->flag85 == 1) {
            fn_8011FAB8();
        }
    }
}
static inline void SetEntry(PanelEntry *e, float y)
{
    e->f10 = lbl_806D7AF0;
    e->f14 = lbl_806D7AE4;
    e->f18 = y;
    e->f1c = lbl_806D7AE4;
    e->f20 = lbl_806D7AF0;
    e->on = 1;
}



extern "C" void fn_80144430(RankPanel *self)
{
    if (self->state != 0 && self->visible) {
        for (PanelItem **it = self->vec.data; it != self->vec.data + self->vec.size; it++) {
            DrawItem(*it);
        }
        if (self->cursor->on) {
            fn_801A0004(self->cursor->sprite);
        }
    }
}

extern "C" asm void fn_80144500(void) { /* 0x80144500 size:0x4D4 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stfd f28, 0x40(r1)
    psq_st f28, 0x48(r1), 0, 0
    stmw r25, 0x24(r1)
    mr r30, r3
    lwz r0, 0x20(r3)
    cmpwi r0, 0x0
    beq fn_80144500_L_801449A0
    lbz r0, 0x18(r30)
    cmplwi r0, 0x0
    beq fn_80144500_L_801449A0
    bl IsCardValid
    lwz r0, 0x20(r30)
    clrlwi r3, r3, 24
    subfic r4, r3, 0x1
    subi r3, r3, 0x1
    cmpwi r0, 0x2
    or r3, r4, r3
    srwi r29, r3, 31
    beq fn_80144500_L_8014478C
    bge fn_80144500_L_80144580
    cmpwi r0, 0x1
    bge fn_80144500_L_8014458C
    b fn_80144500_L_8014478C
    fn_80144500_L_80144580:
    cmpwi r0, 0x4
    bge fn_80144500_L_8014478C
    b fn_80144500_L_801446A0
    fn_80144500_L_8014458C:
    li r0, 0xa
    li r5, 0x0
    li r3, 0x0
    mtctr r0
    fn_80144500_L_8014459C:
    lfs f0, 0x1c(r30)
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r0, 0xc(r1)
    cmpw r0, r3
    bne fn_80144500_L_80144630
    mulli r4, r29, 0xc
    lis r3, RankPanel_80144430_rodata_80361DCC@ha
    lfs f31, lbl_806D7AE0(r2)
    mr r29, r30
    addi r0, r3, RankPanel_80144430_rodata_80361DCC@l
    lfs f30, lbl_806D7AE4(r2)
    add r27, r0, r4
    li r25, 0x0
    mulli r26, r5, 0x26
    li r31, 0x1
    addi r28, r27, 0x4
    fn_80144500_L_801445E0:
    lfs f2, 0x28(r29)
    addi r3, r30, 0xc0
    lfs f1, 0x0(r28)
    add r4, r26, r25
    lfs f0, 0x0(r27)
    fadds f28, f2, f1
    fadds f29, f2, f0
    bl fn_80146000
    lwz r3, 0x0(r3)
    addi r25, r25, 0x1
    cmpwi r25, 0x26
    addi r29, r29, 0x4
    stfs f29, 0x58(r3)
    stfs f28, 0x5c(r3)
    stfs f31, 0x60(r3)
    stfs f30, 0x64(r3)
    stfs f29, 0x68(r3)
    stb r31, 0x54(r3)
    blt fn_80144500_L_801445E0
    b fn_80144500_L_8014463C
    fn_80144500_L_80144630:
    addi r3, r3, 0x2
    addi r5, r5, 0x1
    bdnz fn_80144500_L_8014459C
    fn_80144500_L_8014463C:
    lfs f1, 0x1c(r30)
    lfs f0, lbl_806D7AE8(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80144500_L_8014478C
    lfs f0, lbl_806D7AE4(r2)
    li r0, 0x2
    stfs f0, 0x1c(r30)
    stw r0, 0x20(r30)
    lwz r0, g_reverseRoundFlag(r13)
    cmpwi r0, 0x1
    bne fn_80144500_L_8014478C
    lwz r4, 0xcc(r30)
    lbz r0, 0x4(r4)
    cmplwi r0, 0x1
    bne fn_80144500_L_80144688
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq fn_80144500_L_8014478C
    fn_80144500_L_80144688:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stb r0, 0x5(r4)
    stw r0, 0x8(r4)
    b fn_80144500_L_8014478C
    fn_80144500_L_801446A0:
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r0, 0xa
    li r5, 0x0
    li r3, 0x0
    mtctr r0
    fn_80144500_L_801446BC:
    lfs f0, 0x1c(r30)
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r0, 0xc(r1)
    cmpw r0, r3
    bne fn_80144500_L_80144754
    mulli r4, r29, 0xc
    lis r3, RankPanel_80144430_rodata_80361DCC@ha
    lfs f30, lbl_806D7AE0(r2)
    mr r28, r30
    addi r0, r3, RankPanel_80144430_rodata_80361DCC@l
    lfs f31, lbl_806D7AE4(r2)
    add r3, r0, r4
    li r26, 0x0
    mulli r25, r5, 0x26
    li r31, 0x1
    addi r29, r3, 0x8
    addi r27, r3, 0x4
    fn_80144500_L_80144704:
    lfs f2, 0x28(r28)
    addi r3, r30, 0xc0
    lfs f1, 0x0(r29)
    add r4, r25, r26
    lfs f0, 0x0(r27)
    fadds f29, f2, f1
    fadds f28, f2, f0
    bl fn_80146000
    lwz r3, 0x0(r3)
    addi r26, r26, 0x1
    cmpwi r26, 0x26
    addi r28, r28, 0x4
    stfs f28, 0x58(r3)
    stfs f29, 0x5c(r3)
    stfs f30, 0x60(r3)
    stfs f31, 0x64(r3)
    stfs f28, 0x68(r3)
    stb r31, 0x54(r3)
    blt fn_80144500_L_80144704
    b fn_80144500_L_80144760
    fn_80144500_L_80144754:
    addi r3, r3, 0x2
    addi r5, r5, 0x1
    bdnz fn_80144500_L_801446BC
    fn_80144500_L_80144760:
    lfs f1, 0x1c(r30)
    lfs f0, lbl_806D7AEC(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80144500_L_8014478C
    lfs f0, lbl_806D7AE4(r2)
    li r3, 0x0
    li r0, 0x1
    stfs f0, 0x1c(r30)
    stw r3, 0x20(r30)
    stb r0, 0x24(r30)
    fn_80144500_L_8014478C:
    lfs f1, 0x1c(r30)
    lfs f0, lbl_806D7AF0(r2)
    fadds f0, f1, f0
    stfs f0, 0x1c(r30)
    lwz r31, 0xc8(r30)
    b fn_80144500_L_801448D0
    fn_80144500_L_801447A4:
    lwz r29, 0x0(r31)
    lwz r3, 0x8(r29)
    cmpwi r3, 0x0
    ble fn_80144500_L_801447C0
    subi r0, r3, 0x1
    stw r0, 0x8(r29)
    b fn_80144500_L_801448CC
    fn_80144500_L_801447C0:
    bgt fn_80144500_L_801447CC
    li r0, 0x1
    stb r0, 0x84(r29)
    fn_80144500_L_801447CC:
    li r0, 0x5
    mr r3, r29
    lfs f2, lbl_806D7AF0(r2)
    mtctr r0
    fn_80144500_L_801447DC:
    lbz r0, 0xc(r3)
    cmplwi r0, 0x1
    bne fn_80144500_L_80144824
    lfs f4, 0x1c(r3)
    lfs f0, 0x14(r3)
    fsubs f1, f2, f4
    lfs f3, 0x10(r3)
    fmuls f0, f0, f4
    fmadds f0, f3, f1, f0
    stfs f0, 0x20(r3)
    lfs f1, 0x1c(r3)
    lfs f0, 0x18(r3)
    fadds f0, f1, f0
    stfs f0, 0x1c(r3)
    lfs f0, 0x1c(r3)
    fcmpo cr0, f0, f2
    ble fn_80144500_L_80144824
    stfs f2, 0x1c(r3)
    fn_80144500_L_80144824:
    addi r3, r3, 0x18
    bdnz fn_80144500_L_801447DC
    mr r3, r29
    lwz r12, 0x0(r29)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x4(r29)
    cmplwi r3, 0x0
    beq fn_80144500_L_801448CC
    lbz r0, 0xc(r29)
    cmplwi r0, 0x1
    bne fn_80144500_L_80144860
    lfs f0, 0x20(r29)
    stfs f0, 0x20(r3)
    fn_80144500_L_80144860:
    lbz r0, 0x24(r29)
    cmplwi r0, 0x1
    bne fn_80144500_L_80144878
    lfs f0, 0x38(r29)
    lwz r3, 0x4(r29)
    stfs f0, 0x14(r3)
    fn_80144500_L_80144878:
    lbz r0, 0x3c(r29)
    cmplwi r0, 0x1
    bne fn_80144500_L_80144890
    lfs f0, 0x50(r29)
    lwz r3, 0x4(r29)
    stfs f0, 0x18(r3)
    fn_80144500_L_80144890:
    lbz r0, 0x54(r29)
    cmplwi r0, 0x1
    bne fn_80144500_L_801448A8
    lfs f0, 0x68(r29)
    lwz r3, 0x4(r29)
    stfs f0, 0xc(r3)
    fn_80144500_L_801448A8:
    lbz r0, 0x6c(r29)
    cmplwi r0, 0x1
    bne fn_80144500_L_801448C0
    lfs f0, 0x80(r29)
    lwz r3, 0x4(r29)
    stfs f0, 0x10(r3)
    fn_80144500_L_801448C0:
    lwz r3, 0x4(r29)
    lfs f1, lbl_806D7AF4(r2)
    bl Sprite_AdvanceAnim
    fn_80144500_L_801448CC:
    addi r31, r31, 0x4
    fn_80144500_L_801448D0:
    lwz r0, 0xc4(r30)
    lwz r3, 0xc8(r30)
    slwi r0, r0, 2
    add r0, r3, r0
    cmplw r31, r0
    bne fn_80144500_L_801447A4
    lwz r4, 0xcc(r30)
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq fn_80144500_L_801449A0
    lwz r3, 0x8(r4)
    cmpwi r3, 0x8
    bgt fn_80144500_L_80144994
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    bne fn_80144500_L_80144938
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f2, lbl_806D7B00(r2)
    stw r0, 0x8(r1)
    lfs f0, lbl_806D7AF8(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fmuls f0, f1, f0
    b fn_80144500_L_80144960
    fn_80144500_L_80144938:
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f3, lbl_806D7B00(r2)
    stw r0, 0x10(r1)
    lfs f1, lbl_806D7AF8(r2)
    lfd f2, 0x10(r1)
    lfs f0, lbl_806D7AF0(r2)
    fsubs f2, f2, f3
    fnmsubs f0, f2, f1, f0
    fn_80144500_L_80144960:
    lwz r3, 0x0(r4)
    stfs f0, 0x20(r3)
    lwz r3, 0x8(r4)
    addi r0, r3, 0x1
    cmpwi r3, 0x8
    stw r0, 0x8(r4)
    bne fn_80144500_L_80144994
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq fn_80144500_L_80144994
    li r0, 0x0
    stb r0, 0x4(r4)
    stb r0, 0x5(r4)
    fn_80144500_L_80144994:
    lwz r3, 0x0(r4)
    lfs f1, lbl_806D7AF4(r2)
    bl Sprite_AdvanceAnim
    fn_80144500_L_801449A0:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    psq_l f28, 0x48(r1), 0, 0
    lfd f28, 0x40(r1)
    lmw r25, 0x24(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

extern "C" void fn_801449D4(RankPanel *self)
{
    self->state = 3;
    self->f1c = lbl_806D7AE4;
    PanelEntry *e;
    e = *fn_80146000(&self->vec, 0x17d);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7AF8; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    e = *fn_80146000(&self->vec, 0x17e);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7B08; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    e = *fn_80146000(&self->vec, 0x17f);
    e->f10 = lbl_806D7AF0; e->f14 = lbl_806D7AE4; e->f18 = lbl_806D7B08; e->f1c = lbl_806D7AE4; e->f20 = lbl_806D7AF0; e->on = 1;
    Cursor *c = self->cursor.p;
    if (c->on && c->state != 1) {
        c->state = 1;
        c->timer = 0;
    }
}

extern "C" void fn_80144ADC(RankPanel *self)
{
    self->state = 1;
    self->f1c = lbl_806D7AE4;
}

extern "C" RankPanel *fn_80144AF0(RankPanel *self, short flag)
{
    if (self) {
        self->vt14 = (void **)clCSPartsResultRecord_vtable_8048EEF4;
        for (PanelItem **it = self->vec.begin(); it != self->vec.end(); it++) {
            delete *it;
        }
        self->cursor.~CursorPtr();
        self->vec.~EntryVec();
        if (self) self->vt14 = (void **)lbl_8048EB44;
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" void PtrVec_InsertFill(EntryVec *v, PanelItem **pos, int n, PanelItem *const *val);
inline void EntryVec::push_back(PanelItem *const &x) { PtrVec_InsertFill(this, end(), 1, &x); }

/* time attack record row (TaRecord_GetEntry_Current) */
struct TaEntry {
    unsigned short parts[5]; /* 0x00 */
    char padA[2];
    signed char chara;       /* 0x0C */
    unsigned char titleA;    /* 0x0D */
    unsigned char titleB;    /* 0x0E */
    unsigned char titleC;    /* 0x0F */
};

extern "C" {
int TaRecord_GetLastInsertedRank(void);
float TaRecord_GetTime_Current(int row);
TaEntry *TaRecord_GetEntry_Current(int row);
int fn_8013BFCC(int chara);
int fn_801F96D0(unsigned short part);
int fn_801F9628(unsigned short ch);
int fn_80167744(int digit, float time);
void PreloadResource(int res);
const char *get_title_name(void *mgr, int a, int b, int chara, int c);
void *memcpy(void *dst, const void *src, unsigned long n);
float fn_801D8D3C(int cup, int longRound);
void fn_8019FF6C(Sprite *s, int a);
}

extern "C" void fn_80144C1C(RankPanel *self)
{
    float time;
    TaEntry *entry;
    int res;
    const char *title;
    int row;
    float y;
    int rank;
    void *mgr;

    if (self->visible == 1)
        return;
    self->visible = 1;
    title = (const char *)lbl_806D7B0C;
    PanelItem *item = 0;
    mgr = SINGLETON_INSTANCE(lbl_806D10A0);
    rank = TaRecord_GetLastInsertedRank();
    y = lbl_806D7B10;
    for (row = 0; row < 10; row++) {
        time = TaRecord_GetTime_Current(row);
        entry = TaRecord_GetEntry_Current(row);
        self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[0], y, 0x1cde + row, 7));
        self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[1], y, fn_8013BFCC(entry->chara), 7));
        for (int part = 0; part < 5; part++) {
            res = fn_801F96D0(entry->parts[part]);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[2 + part], y, res, 7));
            PreloadResource(res);
        }
        if (mgr)
            title = get_title_name(mgr, entry->titleA, entry->titleB, entry->chara, entry->titleC);
        if (!IsCardValid())
            title = (const char *)lbl_806D7B0C;
        /* title: one label per character (2-byte SJIS or 1-byte ASCII), padded with blanks */
        int pos = 0;
        int n;
        for (n = 0; n < 0x16; n++) {
            const char *c = title + pos;
            unsigned short ch;
            int wide;
            if (*c == 0)
                break;
            memcpy(&ch, c, 2);
            wide = ch & 0x8000;
            if (wide)
                pos++;
            if (!wide)
                ch = *c;
            pos++;
            res = fn_801F9628(ch);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[7 + n], y, res, 7));
            PreloadResource(res);
        }
        for (; n < 0x16; n++)
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[7 + n], y, 0x1ecd, 7));
        for (int d = 0; d < 9; d++) {
            int digit = fn_80167744(d, time);
            self->vec.push_back(new PanelIcon(lbl_806D7B14 + self->xs[0x1d + d], y, 0x1ce8 + digit, 7));
        }
        y += lbl_806D7B18;
    }

    item = new PanelIcon(lbl_806D7B1C, lbl_806D7B20, RankPanel_80144430_rodata_80361D60[g_cupId - 1][g_longRoundFlag], 5);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7AE0);
    self->vec.push_back(item);

    item = new PanelIcon(lbl_806D7B24, 36.0f * rank + 90.0f, 0x1cf4, 3, 0x23, 1);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7AF8);
    item->tw[1].Start(lbl_806D7B28, lbl_806D7B28, lbl_806D7B2C);
    self->vec.push_back(item);

    Sprite *sprite = new Sprite(0x74, 1, 0);
    sprite->x = lbl_806D7B30;
    sprite->y = lbl_806D7B34;
    fn_8019FF6C(sprite, 1);
    item = new PanelItem((SpriteObj *)sprite, 0x2d);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7B08);
    self->vec.push_back(item);

    item = new PanelIcon(lbl_806D7B38, lbl_806D7B3C, 0x1872, 7, 0x2d);
    item->tw[0].Start(0.0f, 1.0f, lbl_806D7B08);
    self->vec.push_back(item);

    self->cursor->sprite->mode = 6;
    float cursorX = fn_801D8D3C(g_cupId, g_longRoundFlag);
    self->cursor->sprite->fC = cursorX;
    self->cursor->sprite->f10 = lbl_806D7B20;
    fn_801699D8(0, 1);
}

extern "C" void fn_801458A4(Pair *p)
{
    p->a = lbl_806D7AE4;
    p->b = lbl_806D7AE4;
}

clCSPartsResultRecord::clCSPartsResultRecord() : visible(0), f1c(lbl_806D7AE4), state(0), b24(0), cursor(new RecCursor)
{
    Sprite *s = new Sprite(0x1c5, 0, 0);
    LoadColumns(s);
    if (isJapanese()) {
        float x = xs[7];
        for (int i = 0; i < 0x16; i++) {
            xs[7 + i] = x;
            x += lbl_806D7B40;
        }
    } else {
        xs[0x12] = lbl_806D7B44 + xs[0x11];
    }
    delete s;
}

clCSPartsResultRecord::clCSPartsResultRecord(int, int, int) : visible(0), f1c(lbl_806D7AE4), state(0), b24(0), cursor(new RecCursor)
{
    Sprite *s = new Sprite(0x1c5, 0, 0);
    LoadColumns(s);
    if (isJapanese()) {
        float x = xs[7];
        for (int i = 0; i < 0x16; i++) {
            xs[7 + i] = x;
            x += lbl_806D7B40;
        }
    } else {
        xs[0x12] = lbl_806D7B44 + xs[0x11];
    }
    delete s;
}

extern "C" SpriteHolder *fn_80145D34(SpriteHolder *self, short flag)
{
    if (self) {
        self->vt = lbl_8048EF20;
        if (self) {
            self->vt = lbl_8048EF34;
            Sprite_Destroy(self->sprite, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" void fn_80145DA8(void) {}

extern "C" void fn_80145DAC(void) {}

extern "C" SpriteHolder *dtor_80145DB0(SpriteHolder *self, short flag)
{
    if (self) {
        self->vt = lbl_8048EF34;
        Sprite_Destroy(self->sprite, 1);
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

struct ResCtrl {
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    char pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

extern "C" void fn_80145E14(PanelIcon *self)
{
    ResCtrl rc;
    rc.resId = self->resId;
    rc.Show(self->tw[3].Get(), self->tw[4].Get(), 1.0f);
    if (self->tw[0].on == 1) {
        rc.SetColor(0xFFFFFF00 | ((int)(255.0f * self->tw[0].Get()) & 0xFF));
    }
    float sx = 1.0f;
    float sy = 1.0f;
    if (self->tw[1].on == 1) {
        sx = self->tw[1].Get();
    }
    if (self->tw[2].on == 1) {
        sy = self->tw[2].Get();
    }
    rc.scaleX = sx;
    rc.scaleY = sy;
    if (self->flip) {
        rc.tail[0] = 1;
        rc.tail[1] = 4;
        rc.tail[2] = 1;
    }
    fn_8011FAFC(&rc, self->layer);
}

struct SpriteBox { void *sprite; };
struct SpriteBoxPtr { SpriteBox *p; };

/* deleting destructor of a sprite owner pointer: ~SpriteBoxPtr() throw() { delete p; } */
extern "C" SpriteBoxPtr *dtor_80145F04(SpriteBoxPtr *self, short flag) throw()
{
    if (self) {
        SpriteBox *box = self->p;
        if (box) {
            Sprite_Destroy(box->sprite, 1);
            MemoryManager_TimedFree(box);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" VecHolder *dtor_80145F9C(VecHolder *self, short flag)
{
    if (self) {
        if (self) {
            if (self) {
                if (self->data) MemoryManager_TimedFree(self->data);
            }
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" {
unsigned long strlen(const char *s);
char *strcpy(char *d, const char *s);
extern const char lbl_80361E40[];
}

struct ExcStrRef {
    char *ptr;
    unsigned long *refs;
    ExcStrRef(void *p) { SharedPtr_Init(this, p); }
    ~ExcStrRef();
};
struct ExcStr {
    ExcStrRef value;
    ExcStr(const char *s) : value(FUN_8003b120(strlen(s) + 1)) {
        strcpy(value.ptr, s);
    }
    ~ExcStr();
};
struct exception {
    exception() {}
    virtual ~exception();
};
struct logic_error : exception {
    ExcStr msg;
    logic_error(const char *s) : msg(s) {}
    virtual ~logic_error();
};
struct out_of_range : logic_error {
    out_of_range(const char *s) : logic_error(s) {}
    virtual ~out_of_range();
};

extern "C" struct PanelEntry **fn_80146000(struct EntryVec *v, unsigned long id) {
    if (id >= v->size) {
        throw out_of_range(lbl_80361E40);
    }
    return (struct PanelEntry **)&v->data[id];
}

struct ExcString { char *p; };
struct ExcObj { void **vt; ExcString str; };

extern "C" ExcObj *fn_801460D0(ExcObj *self, short flag)
{
    if (self) {
        self->vt = (void **)lbl_8048EF68;
        if (self) {
            self->vt = (void **)lbl_803F5700;
            if (&self->str) dtor_80038E30(&self->str, -1);
            if (self) self->vt = (void **)lbl_803F5710;
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

