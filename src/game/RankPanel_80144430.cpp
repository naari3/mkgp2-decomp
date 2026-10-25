
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7B0C[1];
/*
 * 0x80144430..0x80146160: time attack ranking panel and its entry vector.
 */
#pragma cplusplus on

class PanelItem {
public:
    virtual void v8();
    virtual void vC();
    virtual void Draw();
    void *sprite;
    char pad8[0x84 - 8];
    unsigned char active;
    unsigned char flag85;
};
struct PanelEntry {
    char pad0[0xc];
    unsigned char on;
    char padD[3];
    float f10, f14, f18, f1c, f20;
};
struct EntryVec {
    int cap;
    int size;
    PanelItem **data;
    PanelItem **begin() { return data; }
    PanelItem **end() { return data + size; }
};
struct Cursor {
    void *sprite;
    unsigned char on;
    unsigned char state;
    char pad6[2];
    int timer;
};
struct RankPanel {
    char pad0[0x18];
    unsigned char visible;
    char pad19[3];
    float f1c;
    int state;
    char pad24[0xc0 - 0x24];
    EntryVec vec;
    Cursor *cursor;
};
struct Pair { char pad[0xc]; float a, b; };
struct SpriteHolder { void **vt; void *sprite; };
struct VecHolder { int pad0; int pad4; void *data; };

/* TOP-END */

extern "C" {
void fn_8011FAB8(void);
void fn_801A0004(void *s);
extern void IsCardValid();
extern void Sprite_AdvanceAnim();
extern void fn_801699D8();
extern unsigned int g_reverseRoundFlag;
extern unsigned int lbl_806D7AE0;
extern const float lbl_806D7AE4;
extern unsigned int lbl_806D7AE8;
extern unsigned int lbl_806D7AEC;
extern const float lbl_806D7AF0;
extern unsigned int lbl_806D7AF4;
extern const float lbl_806D7AF8;
extern unsigned int lbl_806D7B00;
extern unsigned int lbl_80361DCC[];
extern const float lbl_806D7B08;
void MemoryManager_TimedFree(void *p);
void Sprite_Destroy(void *s, int flag);
extern void __unexpected();
extern unsigned int lbl_8048EB44[];
extern unsigned int lbl_8048EEF4[];
extern void Alloc();
extern void PreloadResource();
extern void PtrVec_InsertFill();
extern void Sprite_InitWithAnim();
extern void TaRecord_GetEntry_Current();
extern void TaRecord_GetLastInsertedRank();
extern void TaRecord_GetTime_Current();
extern void __construct_array();
extern void fn_8013BFCC();
extern void fn_80167744();
extern void fn_8019FF6C();
extern void fn_801D8D3C();
extern void fn_801F9628();
extern void fn_801F96D0();
extern void get_title_name();
extern void memcpy();
extern unsigned int g_cupId;
extern unsigned int g_longRoundFlag;
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D7B10;
extern unsigned int lbl_806D7B14;
extern unsigned int lbl_806D7B18;
extern unsigned int lbl_806D7B1C;
extern unsigned int lbl_806D7B20;
extern unsigned int lbl_806D7B24;
extern unsigned int lbl_806D7B28;
extern unsigned int lbl_806D7B2C;
extern unsigned int lbl_806D7B30;
extern unsigned int lbl_806D7B34;
extern unsigned int lbl_806D7B38;
extern unsigned int lbl_806D7B3C;
extern unsigned int lbl_80361D60[];
extern void *lbl_8048EF20[];
extern void *lbl_8048EF34[];
extern void Sprite_CreateWithParams();
extern void fn_8019FF8C();
extern void isJapanese();
extern unsigned int lbl_806D7B40;
extern unsigned int lbl_806D7B44;
extern unsigned int lbl_806D7B48;
extern unsigned int lbl_80361D80[];
extern void dtor_8013EB50();
extern void ResCtrl_Init();
extern void fn_8011FAFC();
extern unsigned int lbl_806D7B4C;
extern void dtor_80082960();
extern void FUN_8003b120();
extern void SharedPtr_Init();
extern void __throw();
extern void strcpy();
extern void strlen();
extern unsigned int lbl_80361E40[];
extern unsigned int lbl_80361E60[];
extern unsigned int lbl_803F5700[];
extern unsigned int lbl_803F5710[];
extern unsigned int lbl_8048EF68[];
extern void dtor_80038DD4();
extern void dtor_80038E30();
void fn_80144430(RankPanel *self);
asm void fn_80144500(void);
void fn_801449D4(RankPanel *self);
void fn_80144ADC(RankPanel *self);
asm void fn_80144AF0(void);
asm void fn_80144C1C(void);
void fn_801458A4(Pair *p);
asm void fn_801458B4(void);
asm void fn_80145AF4(void);
SpriteHolder *fn_80145D34(SpriteHolder *self, short flag);
void fn_80145DA8(void);
void fn_80145DAC(void);
SpriteHolder *dtor_80145DB0(SpriteHolder *self, short flag);
asm void fn_80145E14(void);
asm void dtor_80145F04(void);
VecHolder *dtor_80145F9C(VecHolder *self, short flag);
asm struct PanelEntry **fn_80146000(struct EntryVec *v, int id);
asm void fn_801460D0(void);

#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_fn_80144500[8] = {
    0x39, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_80144AF0[40] = {
    0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C,
    0x00, 0x02, 0x00, 0x18, 0x00, 0x00, 0x00, 0xB0,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA8,
    0x00, 0x00, 0x00, 0x08, 0x8D, 0x00, 0x00, 0x08
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; void *f25; unsigned int f26; void *f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; void *f37; unsigned int f38; void *f39; unsigned int f40; void *f41; unsigned int f42; void *f43; unsigned int f44; void *f45; } extab_fn_80144C1C = { 0x590A0000, 0x000000E8, 0x00000060, 0x000001A4, 0x00110068, 0x000002F0, 0x00000070, 0x00000490, 0x00000078, 0x000005A0, 0x00000080, 0x000006B8, 0x00000088, 0x000007E0, 0x00000090, 0x000008F4, 0x00000098, 0x00000A2C, 0x000000A0, 0x00000A8C, 0x000000A8, 0x00000B40, 0x000000B0, 0x00000000, 0x8A800016, (void *)&MemoryManager_TimedFree, 0x8A800016, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800016, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; void *f17; unsigned int f18; unsigned int f19; void *f20; unsigned int f21; unsigned int f22; void *f23; unsigned int f24; void *f25; unsigned int f26; unsigned int f27; void *f28; unsigned int f29; } extab_fn_801458B4 = { 0x280A0000, 0x00000070, 0x00000048, 0x00000090, 0x00000040, 0x000000BC, 0x00000038, 0x000000CC, 0x00000068, 0x000000E4, 0x00000060, 0x00000104, 0x00490068, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000C0, (void *)&dtor_80145F9C, 0x8680001F, 0x00000000, (void *)&dtor_8013EB50, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000CC, (void *)&dtor_80145F04, 0x01000048 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; void *f17; unsigned int f18; unsigned int f19; void *f20; unsigned int f21; unsigned int f22; void *f23; unsigned int f24; void *f25; unsigned int f26; unsigned int f27; void *f28; unsigned int f29; } extab_fn_80145AF4 = { 0x280A0000, 0x00000070, 0x00000048, 0x00000090, 0x00000040, 0x000000BC, 0x00000038, 0x000000CC, 0x00000068, 0x000000E4, 0x00000060, 0x00000104, 0x00490068, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000C0, (void *)&dtor_80145F9C, 0x8680001F, 0x00000000, (void *)&dtor_8013EB50, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000CC, (void *)&dtor_80145F04, 0x01000048 };



__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80145E14 = { 0x080A0000, 0x000000DC, 0x00000010, 0x00000000, 0x82000008, (void *)&dtor_80082960 };

__declspec(section ".extab_user") static const unsigned char extab_dtor_80145F04[40] = {
    0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44,
    0x00, 0x06, 0x00, 0x18, 0x00, 0x00, 0x00, 0x6C,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64,
    0x00, 0x00, 0x00, 0x08, 0x8D, 0x00, 0x00, 0x08
};


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; void *f8; unsigned int f9; unsigned int f10; void *f11; } extab_fn_80146000 = { 0x20080000, 0x0000005C, 0x00050024, 0x00000080, 0x00000018, 0x00000000, 0x0780001C, 0x00000000, (void *)&dtor_80038E30, 0x8680001D, 0x00000000, (void *)&dtor_80038DD4 };

__declspec(section ".extab_user") static const unsigned char extab_fn_801460D0[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80144500 = {
    (void *)&fn_80144500, 0x000004D4, (void *)extab_fn_80144500
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80144AF0 = {
    (void *)&fn_80144AF0, 0x0000012C, (void *)extab_fn_80144AF0
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80144C1C = {
    (void *)&fn_80144C1C, 0x00000C88, (void *)&extab_fn_80144C1C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801458B4 = {
    (void *)&fn_801458B4, 0x00000240, (void *)&extab_fn_801458B4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80145AF4 = {
    (void *)&fn_80145AF4, 0x00000240, (void *)&extab_fn_80145AF4
};



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80145E14 = {
    (void *)&fn_80145E14, 0x000000F0, (void *)&extab_fn_80145E14
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_80145F04 = {
    (void *)&dtor_80145F04, 0x00000098, (void *)extab_dtor_80145F04
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80146000 = {
    (void *)&fn_80146000, 0x000000D0, (void *)&extab_fn_80146000
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801460D0 = {
    (void *)&fn_801460D0, 0x00000090, (void *)extab_fn_801460D0
};

}

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
    lis r3, lbl_80361DCC@ha
    lfs f31, lbl_806D7AE0(r2)
    mr r29, r30
    addi r0, r3, lbl_80361DCC@l
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
    lis r3, lbl_80361DCC@ha
    lfs f30, lbl_806D7AE0(r2)
    mr r28, r30
    addi r0, r3, lbl_80361DCC@l
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
    Cursor *c = self->cursor;
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

extern "C" asm void fn_80144AF0(void) { /* 0x80144AF0 size:0x12C */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    stw r30, 0x28(r1)
    mr r30, r4
    stw r29, 0x24(r1)
    mr. r29, r3
    stw r28, 0x20(r1)
    beq fn_80144AF0_L_80144BF0
    lis r3, lbl_8048EEF4@ha
    addi r0, r3, lbl_8048EEF4@l
    stw r0, 0x14(r29)
    lwz r28, 0xc8(r29)
    b fn_80144AF0_L_80144B54
    fn_80144AF0_L_80144B30:
    lwz r3, 0x0(r28)
    cmplwi r3, 0x0
    beq fn_80144AF0_L_80144B50
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80144AF0_L_80144B50:
    addi r28, r28, 0x4
    fn_80144AF0_L_80144B54:
    lwz r0, 0xc4(r29)
    lwz r3, 0xc8(r29)
    slwi r0, r0, 2
    add r0, r3, r0
    cmplw r28, r0
    bne fn_80144AF0_L_80144B30
    addic. r0, r29, 0xcc
    beq fn_80144AF0_L_80144BA4
    lwz r28, 0xcc(r29)
    cmplwi r28, 0x0
    beq fn_80144AF0_L_80144BA4
    lwz r3, 0x0(r28)
    li r4, 0x1
    bl Sprite_Destroy
    mr r3, r28
    bl MemoryManager_TimedFree
    b fn_80144AF0_L_80144BA4
    addi r3, r31, 0x8
    bl __unexpected
    fn_80144AF0_L_80144BA0:
    b fn_80144AF0_L_80144BA0
    fn_80144AF0_L_80144BA4:
    addic. r0, r29, 0xc0
    beq fn_80144AF0_L_80144BCC
    addic. r0, r29, 0xc0
    beq fn_80144AF0_L_80144BCC
    addic. r0, r29, 0xc0
    beq fn_80144AF0_L_80144BCC
    lwz r3, 0xc8(r29)
    cmplwi r3, 0x0
    beq fn_80144AF0_L_80144BCC
    bl MemoryManager_TimedFree
    fn_80144AF0_L_80144BCC:
    cmplwi r29, 0x0
    beq fn_80144AF0_L_80144BE0
    lis r3, lbl_8048EB44@ha
    addi r0, r3, lbl_8048EB44@l
    stw r0, 0x14(r29)
    fn_80144AF0_L_80144BE0:
    extsh. r0, r30
    ble fn_80144AF0_L_80144BF0
    mr r3, r29
    bl MemoryManager_TimedFree
    fn_80144AF0_L_80144BF0:
    mr r10, r31
    lwz r31, 0x2c(r31)
    mr r3, r29
    lwz r30, 0x28(r10)
    lwz r29, 0x24(r10)
    lwz r28, 0x20(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

extern "C" asm void fn_80144C1C(void) { /* 0x80144C1C size:0xC88 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stfd f29, 0x70(r1)
    psq_st f29, 0x78(r1), 0, 0
    stfd f28, 0x60(r1)
    psq_st f28, 0x68(r1), 0, 0
    stmw r21, 0x34(r1)
    mr r31, r3
    lbz r0, 0x18(r3)
    cmplwi r0, 0x1
    beq fn_80144C1C_L_80145870
    li r0, 0x1
    li r28, 0x0
    stb r0, 0x18(r31)
    la r30, lbl_806D7B0C(r2)  /* lbl_806D7B0C */
    lwz r0, lbl_806D10A0(r13)
    stw r28, 0x24(r1)
    cmplwi r0, 0x0
    bne fn_80144C1C_L_80144C80
    b fn_80144C1C_L_80144C84
    fn_80144C1C_L_80144C80:
    mr r28, r0
    fn_80144C1C_L_80144C84:
    bl TaRecord_GetLastInsertedRank
    lfs f30, lbl_806D7B10(r2)
    mr r27, r3
    lfs f29, lbl_806D7B18(r2)
    li r29, 0x0
    fn_80144C1C_L_80144C98:
    mr r3, r29
    bl TaRecord_GetTime_Current
    fmr f31, f1
    mr r3, r29
    bl TaRecord_GetEntry_Current
    mr r0, r3
    li r3, 0x94
    mr r24, r0
    bl Alloc
    mr. r22, r3
    beq fn_80144C1C_L_80144D80
    lis r3, lbl_8048EF34@ha
    lfs f0, 0x28(r31)
    addi r0, r3, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r22)
    li r0, 0x0
    lis r3, fn_801458A4@ha
    fadds f28, f1, f0
    stw r0, 0x4(r22)
    addi r4, r3, fn_801458A4@l
    addi r3, r22, 0xc
    li r5, 0x0
    stw r0, 0x8(r22)
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r6, 0x0
    lis r3, lbl_8048EF20@ha
    stb r6, 0x84(r22)
    addi r5, r3, lbl_8048EF20@l
    addi r4, r29, 0x1cde
    li r3, 0x7
    stb r6, 0x85(r22)
    li r0, 0x1
    lfs f1, lbl_806D7AF0(r2)
    stb r6, 0xc(r22)
    lfs f0, lbl_806D7AE4(r2)
    stb r6, 0x24(r22)
    stb r6, 0x3c(r22)
    stb r6, 0x54(r22)
    stb r6, 0x6c(r22)
    stw r5, 0x0(r22)
    sth r4, 0x88(r22)
    stw r3, 0x8c(r22)
    stb r6, 0x90(r22)
    stfs f28, 0x58(r22)
    stfs f28, 0x5c(r22)
    stfs f1, 0x60(r22)
    stfs f0, 0x64(r22)
    stfs f28, 0x68(r22)
    stb r0, 0x54(r22)
    stfs f30, 0x70(r22)
    stfs f30, 0x74(r22)
    stfs f1, 0x78(r22)
    stfs f0, 0x7c(r22)
    stfs f30, 0x80(r22)
    stb r0, 0x6c(r22)
    fn_80144C1C_L_80144D80:
    stw r22, 0x20(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0x20
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    li r3, 0x94
    bl Alloc
    mr. r22, r3
    beq fn_80144C1C_L_80144E7C
    lbz r3, 0xc(r24)
    extsb r3, r3
    bl fn_8013BFCC
    lis r4, lbl_8048EF34@ha
    lfs f0, 0x2c(r31)
    addi r0, r4, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r22)
    li r0, 0x0
    lis r4, fn_801458A4@ha
    extsh r21, r3
    stw r0, 0x4(r22)
    fadds f28, f1, f0
    addi r4, r4, fn_801458A4@l
    addi r3, r22, 0xc
    stw r0, 0x8(r22)
    li r5, 0x0
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r5, 0x0
    lis r3, lbl_8048EF20@ha
    stb r5, 0x84(r22)
    addi r4, r3, lbl_8048EF20@l
    li r3, 0x7
    lfs f1, lbl_806D7AF0(r2)
    stb r5, 0x85(r22)
    li r0, 0x1
    lfs f0, lbl_806D7AE4(r2)
    stb r5, 0xc(r22)
    stb r5, 0x24(r22)
    stb r5, 0x3c(r22)
    stb r5, 0x54(r22)
    stb r5, 0x6c(r22)
    stw r4, 0x0(r22)
    sth r21, 0x88(r22)
    stw r3, 0x8c(r22)
    stb r5, 0x90(r22)
    stfs f28, 0x58(r22)
    stfs f28, 0x5c(r22)
    stfs f1, 0x60(r22)
    stfs f0, 0x64(r22)
    stfs f28, 0x68(r22)
    stb r0, 0x54(r22)
    stfs f30, 0x70(r22)
    stfs f30, 0x74(r22)
    stfs f1, 0x78(r22)
    stfs f0, 0x7c(r22)
    stfs f30, 0x80(r22)
    stb r0, 0x6c(r22)
    fn_80144C1C_L_80144E7C:
    stw r22, 0x1c(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0x1c
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    mr r26, r24
    mr r25, r31
    li r22, 0x0
    fn_80144C1C_L_80144EAC:
    lhz r3, 0x0(r26)
    bl fn_801F96D0
    mr r0, r3
    li r3, 0x94
    mr r23, r0
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_80144F84
    lis r3, lbl_8048EF34@ha
    lfs f0, 0x30(r25)
    addi r0, r3, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r21)
    li r0, 0x0
    lis r3, fn_801458A4@ha
    fadds f28, f1, f0
    stw r0, 0x4(r21)
    addi r4, r3, fn_801458A4@l
    addi r3, r21, 0xc
    li r5, 0x0
    stw r0, 0x8(r21)
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r5, 0x0
    lis r3, lbl_8048EF20@ha
    stb r5, 0x84(r21)
    addi r4, r3, lbl_8048EF20@l
    li r3, 0x7
    lfs f1, lbl_806D7AF0(r2)
    stb r5, 0x85(r21)
    li r0, 0x1
    lfs f0, lbl_806D7AE4(r2)
    stb r5, 0xc(r21)
    stb r5, 0x24(r21)
    stb r5, 0x3c(r21)
    stb r5, 0x54(r21)
    stb r5, 0x6c(r21)
    stw r4, 0x0(r21)
    sth r23, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r5, 0x90(r21)
    stfs f28, 0x58(r21)
    stfs f28, 0x5c(r21)
    stfs f1, 0x60(r21)
    stfs f0, 0x64(r21)
    stfs f28, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f30, 0x70(r21)
    stfs f30, 0x74(r21)
    stfs f1, 0x78(r21)
    stfs f0, 0x7c(r21)
    stfs f30, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_80144F84:
    stw r21, 0x18(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0x18
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    mr r3, r23
    bl PreloadResource
    addi r22, r22, 0x1
    addi r25, r25, 0x4
    cmpwi r22, 0x5
    addi r26, r26, 0x2
    blt fn_80144C1C_L_80144EAC
    cmplwi r28, 0x0
    beq fn_80144C1C_L_80144FEC
    lbz r6, 0xc(r24)
    mr r3, r28
    lbz r4, 0xd(r24)
    lbz r5, 0xe(r24)
    extsb r6, r6
    lbz r7, 0xf(r24)
    bl get_title_name
    mr r30, r3
    fn_80144C1C_L_80144FEC:
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne fn_80144C1C_L_80144FFC
    la r30, lbl_806D7B0C(r2)  /* lbl_806D7B0C */
    fn_80144C1C_L_80144FFC:
    mr r25, r31
    li r22, 0x0
    li r23, 0x0
    fn_80144C1C_L_80145008:
    add r21, r30, r22
    lbz r0, 0x0(r21)
    extsb. r0, r0
    beq fn_80144C1C_L_80145160
    mr r4, r21
    addi r3, r1, 0x8
    li r5, 0x2
    bl memcpy
    lhz r0, 0x8(r1)
    rlwinm. r0, r0, 0, 16, 16
    beq fn_80144C1C_L_80145038
    addi r22, r22, 0x1
    fn_80144C1C_L_80145038:
    cmpwi r0, 0x0
    bne fn_80144C1C_L_8014504C
    lbz r0, 0x0(r21)
    extsb r0, r0
    sth r0, 0x8(r1)
    fn_80144C1C_L_8014504C:
    lhz r3, 0x8(r1)
    addi r22, r22, 0x1
    bl fn_801F9628
    mr r26, r3
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_80145124
    lis r3, lbl_8048EF34@ha
    lfs f0, 0x44(r25)
    addi r0, r3, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r21)
    li r0, 0x0
    lis r3, fn_801458A4@ha
    fadds f28, f1, f0
    stw r0, 0x4(r21)
    addi r4, r3, fn_801458A4@l
    addi r3, r21, 0xc
    li r5, 0x0
    stw r0, 0x8(r21)
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r5, 0x0
    lis r3, lbl_8048EF20@ha
    stb r5, 0x84(r21)
    addi r4, r3, lbl_8048EF20@l
    li r3, 0x7
    lfs f1, lbl_806D7AF0(r2)
    stb r5, 0x85(r21)
    li r0, 0x1
    lfs f0, lbl_806D7AE4(r2)
    stb r5, 0xc(r21)
    stb r5, 0x24(r21)
    stb r5, 0x3c(r21)
    stb r5, 0x54(r21)
    stb r5, 0x6c(r21)
    stw r4, 0x0(r21)
    sth r26, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r5, 0x90(r21)
    stfs f28, 0x58(r21)
    stfs f28, 0x5c(r21)
    stfs f1, 0x60(r21)
    stfs f0, 0x64(r21)
    stfs f28, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f30, 0x70(r21)
    stfs f30, 0x74(r21)
    stfs f1, 0x78(r21)
    stfs f0, 0x7c(r21)
    stfs f30, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_80145124:
    stw r21, 0x14(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0x14
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    mr r3, r26
    bl PreloadResource
    addi r23, r23, 0x1
    addi r25, r25, 0x4
    cmpwi r23, 0x16
    blt fn_80144C1C_L_80145008
    fn_80144C1C_L_80145160:
    slwi r0, r23, 2
    add r25, r31, r0
    b fn_80144C1C_L_80145264
    fn_80144C1C_L_8014516C:
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_80145238
    lis r3, lbl_8048EF34@ha
    lfs f0, 0x44(r25)
    addi r0, r3, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r21)
    li r0, 0x0
    lis r3, fn_801458A4@ha
    fadds f28, f1, f0
    stw r0, 0x4(r21)
    addi r4, r3, fn_801458A4@l
    addi r3, r21, 0xc
    li r5, 0x0
    stw r0, 0x8(r21)
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r6, 0x0
    lis r3, lbl_8048EF20@ha
    stb r6, 0x84(r21)
    addi r5, r3, lbl_8048EF20@l
    li r4, 0x1ecd
    li r3, 0x7
    stb r6, 0x85(r21)
    li r0, 0x1
    lfs f1, lbl_806D7AF0(r2)
    stb r6, 0xc(r21)
    lfs f0, lbl_806D7AE4(r2)
    stb r6, 0x24(r21)
    stb r6, 0x3c(r21)
    stb r6, 0x54(r21)
    stb r6, 0x6c(r21)
    stw r5, 0x0(r21)
    sth r4, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r6, 0x90(r21)
    stfs f28, 0x58(r21)
    stfs f28, 0x5c(r21)
    stfs f1, 0x60(r21)
    stfs f0, 0x64(r21)
    stfs f28, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f30, 0x70(r21)
    stfs f30, 0x74(r21)
    stfs f1, 0x78(r21)
    stfs f0, 0x7c(r21)
    stfs f30, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_80145238:
    stw r21, 0x10(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0x10
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    addi r25, r25, 0x4
    addi r23, r23, 0x1
    fn_80144C1C_L_80145264:
    cmpwi r23, 0x16
    blt fn_80144C1C_L_8014516C
    li r22, 0x0
    mr r25, r31
    fn_80144C1C_L_80145274:
    fmr f1, f31
    mr r3, r22
    bl fn_80167744
    mr r23, r3
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_80145350
    lis r3, lbl_8048EF34@ha
    lfs f0, 0x9c(r25)
    addi r0, r3, lbl_8048EF34@l
    lfs f1, lbl_806D7B14(r2)
    stw r0, 0x0(r21)
    li r0, 0x0
    lis r3, fn_801458A4@ha
    fadds f28, f1, f0
    stw r0, 0x4(r21)
    addi r4, r3, fn_801458A4@l
    addi r3, r21, 0xc
    li r5, 0x0
    stw r0, 0x8(r21)
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r6, 0x0
    lis r3, lbl_8048EF20@ha
    stb r6, 0x84(r21)
    addi r5, r3, lbl_8048EF20@l
    addi r4, r23, 0x1ce8
    li r3, 0x7
    stb r6, 0x85(r21)
    li r0, 0x1
    lfs f1, lbl_806D7AF0(r2)
    stb r6, 0xc(r21)
    lfs f0, lbl_806D7AE4(r2)
    stb r6, 0x24(r21)
    stb r6, 0x3c(r21)
    stb r6, 0x54(r21)
    stb r6, 0x6c(r21)
    stw r5, 0x0(r21)
    sth r4, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r6, 0x90(r21)
    stfs f28, 0x58(r21)
    stfs f28, 0x5c(r21)
    stfs f1, 0x60(r21)
    stfs f0, 0x64(r21)
    stfs f28, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f30, 0x70(r21)
    stfs f30, 0x74(r21)
    stfs f1, 0x78(r21)
    stfs f0, 0x7c(r21)
    stfs f30, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_80145350:
    stw r21, 0xc(r1)
    addi r3, r31, 0xc0
    addi r6, r1, 0xc
    li r5, 0x1
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    addi r22, r22, 0x1
    addi r25, r25, 0x4
    cmpwi r22, 0x9
    blt fn_80144C1C_L_80145274
    addi r29, r29, 0x1
    fadds f30, f30, f29
    cmpwi r29, 0xa
    blt fn_80144C1C_L_80144C98
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_8014547C
    lwz r5, g_cupId(r13)
    lis r3, lbl_8048EF34@ha
    addi r0, r3, lbl_8048EF34@l
    lwz r4, g_longRoundFlag(r13)
    lis r6, lbl_80361D60@ha
    slwi r5, r5, 2
    stw r0, 0x0(r21)
    li r0, 0x0
    addi r6, r6, lbl_80361D60@l
    lis r3, fn_801458A4@ha
    stw r0, 0x4(r21)
    add r6, r6, r5
    slwi r5, r4, 1
    addi r4, r3, fn_801458A4@l
    add r3, r6, r5
    stw r0, 0x8(r21)
    lha r22, -0x4(r3)
    addi r3, r21, 0xc
    li r5, 0x0
    li r6, 0x18
    li r7, 0x5
    bl __construct_array
    li r5, 0x0
    lis r3, lbl_8048EF20@ha
    stb r5, 0x84(r21)
    addi r4, r3, lbl_8048EF20@l
    li r3, 0x5
    lfs f3, lbl_806D7B1C(r2)
    stb r5, 0x85(r21)
    li r0, 0x1
    lfs f2, lbl_806D7AF0(r2)
    stb r5, 0xc(r21)
    lfs f1, lbl_806D7AE4(r2)
    stb r5, 0x24(r21)
    lfs f0, lbl_806D7B20(r2)
    stb r5, 0x3c(r21)
    stb r5, 0x54(r21)
    stb r5, 0x6c(r21)
    stw r4, 0x0(r21)
    sth r22, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r5, 0x90(r21)
    stfs f3, 0x58(r21)
    stfs f3, 0x5c(r21)
    stfs f2, 0x60(r21)
    stfs f1, 0x64(r21)
    stfs f3, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f0, 0x70(r21)
    stfs f0, 0x74(r21)
    stfs f2, 0x78(r21)
    stfs f1, 0x7c(r21)
    stfs f0, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_8014547C:
    stw r21, 0x24(r1)
    li r0, 0x1
    lfs f2, lbl_806D7AE4(r2)
    addi r3, r31, 0xc0
    lfs f1, lbl_806D7AF0(r2)
    addi r6, r1, 0x24
    stfs f2, 0x10(r21)
    li r5, 0x1
    lfs f0, lbl_806D7AE0(r2)
    stfs f1, 0x14(r21)
    stfs f0, 0x18(r21)
    stfs f2, 0x1c(r21)
    stfs f2, 0x20(r21)
    stb r0, 0xc(r21)
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_801455B8
    lis r4, lbl_8048EF34@ha
    li r5, 0x0
    addi r0, r4, lbl_8048EF34@l
    lis r3, fn_801458A4@ha
    stw r0, 0x0(r21)
    addi r4, r3, fn_801458A4@l
    li r0, 0x23
    addi r3, r21, 0xc
    stw r5, 0x4(r21)
    li r5, 0x0
    li r6, 0x18
    li r7, 0x5
    stw r0, 0x8(r21)
    bl __construct_array
    li r8, 0x0
    lis r4, lbl_8048EF20@ha
    stb r8, 0x84(r21)
    xoris r3, r27, 0x8000
    lis r0, 0x4330
    addi r7, r4, lbl_8048EF20@l
    stb r8, 0x85(r21)
    li r6, 0x1cf4
    li r5, 0x3
    li r4, 0x1
    stb r8, 0xc(r21)
    lfs f1, lbl_806D7B24(r2)
    stb r8, 0x24(r21)
    lfs f5, lbl_806D7AF0(r2)
    stb r8, 0x3c(r21)
    lfs f4, lbl_806D7AE4(r2)
    stb r8, 0x54(r21)
    lfd f2, lbl_806D7B00(r2)
    stb r8, 0x6c(r21)
    lfs f3, lbl_806D7B18(r2)
    stw r7, 0x0(r21)
    lfs f0, lbl_806D7B10(r2)
    sth r6, 0x88(r21)
    stw r5, 0x8c(r21)
    stb r4, 0x90(r21)
    stfs f1, 0x58(r21)
    stfs f1, 0x5c(r21)
    stfs f5, 0x60(r21)
    stfs f4, 0x64(r21)
    stfs f1, 0x68(r21)
    stw r3, 0x2c(r1)
    stw r0, 0x28(r1)
    lfd f1, 0x28(r1)
    stb r4, 0x54(r21)
    fsubs f1, f1, f2
    fmadds f0, f3, f1, f0
    stfs f0, 0x70(r21)
    stfs f0, 0x74(r21)
    stfs f5, 0x78(r21)
    stfs f4, 0x7c(r21)
    stfs f0, 0x80(r21)
    stb r4, 0x6c(r21)
    fn_80144C1C_L_801455B8:
    stw r21, 0x24(r1)
    li r0, 0x1
    lfs f2, lbl_806D7AE4(r2)
    addi r3, r31, 0xc0
    lfs f1, lbl_806D7AF0(r2)
    addi r6, r1, 0x24
    stfs f2, 0x10(r21)
    li r5, 0x1
    lfs f0, lbl_806D7AF8(r2)
    stfs f1, 0x14(r21)
    lfs f1, lbl_806D7B28(r2)
    stfs f0, 0x18(r21)
    lfs f0, lbl_806D7B2C(r2)
    stfs f2, 0x1c(r21)
    stfs f2, 0x20(r21)
    stb r0, 0xc(r21)
    lwz r4, 0x24(r1)
    stfs f1, 0x28(r4)
    stfs f1, 0x2c(r4)
    stfs f0, 0x30(r4)
    stfs f2, 0x34(r4)
    stfs f1, 0x38(r4)
    stb r0, 0x24(r4)
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    li r3, 0x30
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_80145648
    li r4, 0x74
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_80144C1C_L_80145648:
    lfs f1, lbl_806D7B30(r2)
    mr r3, r21
    lfs f0, lbl_806D7B34(r2)
    li r4, 0x1
    stfs f1, 0xc(r21)
    stfs f0, 0x10(r21)
    bl fn_8019FF6C
    li r3, 0x88
    bl Alloc
    mr. r22, r3
    beq fn_80144C1C_L_801456C8
    lis r4, lbl_8048EF34@ha
    li r0, 0x2d
    addi r4, r4, lbl_8048EF34@l
    lis r3, fn_801458A4@ha
    stw r4, 0x0(r22)
    addi r4, r3, fn_801458A4@l
    addi r3, r22, 0xc
    li r5, 0x0
    stw r21, 0x4(r22)
    li r6, 0x18
    li r7, 0x5
    stw r0, 0x8(r22)
    bl __construct_array
    li r0, 0x0
    stb r0, 0x84(r22)
    stb r0, 0x85(r22)
    stb r0, 0xc(r22)
    stb r0, 0x24(r22)
    stb r0, 0x3c(r22)
    stb r0, 0x54(r22)
    stb r0, 0x6c(r22)
    fn_80144C1C_L_801456C8:
    stw r22, 0x24(r1)
    li r0, 0x1
    lfs f2, lbl_806D7AE4(r2)
    addi r3, r31, 0xc0
    lfs f1, lbl_806D7AF0(r2)
    addi r6, r1, 0x24
    stfs f2, 0x10(r22)
    li r5, 0x1
    lfs f0, lbl_806D7B08(r2)
    stfs f1, 0x14(r22)
    stfs f0, 0x18(r22)
    stfs f2, 0x1c(r22)
    stfs f2, 0x20(r22)
    stb r0, 0xc(r22)
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    li r3, 0x94
    bl Alloc
    mr. r21, r3
    beq fn_80144C1C_L_801457E0
    lis r4, lbl_8048EF34@ha
    li r5, 0x0
    addi r0, r4, lbl_8048EF34@l
    lis r3, fn_801458A4@ha
    stw r0, 0x0(r21)
    addi r4, r3, fn_801458A4@l
    li r0, 0x2d
    addi r3, r21, 0xc
    stw r5, 0x4(r21)
    li r5, 0x0
    li r6, 0x18
    li r7, 0x5
    stw r0, 0x8(r21)
    bl __construct_array
    li r6, 0x0
    lis r3, lbl_8048EF20@ha
    stb r6, 0x84(r21)
    addi r5, r3, lbl_8048EF20@l
    li r4, 0x1872
    li r3, 0x7
    stb r6, 0x85(r21)
    li r0, 0x1
    lfs f3, lbl_806D7B38(r2)
    stb r6, 0xc(r21)
    lfs f2, lbl_806D7AF0(r2)
    stb r6, 0x24(r21)
    lfs f1, lbl_806D7AE4(r2)
    stb r6, 0x3c(r21)
    lfs f0, lbl_806D7B3C(r2)
    stb r6, 0x54(r21)
    stb r6, 0x6c(r21)
    stw r5, 0x0(r21)
    sth r4, 0x88(r21)
    stw r3, 0x8c(r21)
    stb r6, 0x90(r21)
    stfs f3, 0x58(r21)
    stfs f3, 0x5c(r21)
    stfs f2, 0x60(r21)
    stfs f1, 0x64(r21)
    stfs f3, 0x68(r21)
    stb r0, 0x54(r21)
    stfs f0, 0x70(r21)
    stfs f0, 0x74(r21)
    stfs f2, 0x78(r21)
    stfs f1, 0x7c(r21)
    stfs f0, 0x80(r21)
    stb r0, 0x6c(r21)
    fn_80144C1C_L_801457E0:
    stw r21, 0x24(r1)
    li r0, 0x1
    lfs f2, lbl_806D7AE4(r2)
    addi r3, r31, 0xc0
    lfs f1, lbl_806D7AF0(r2)
    addi r6, r1, 0x24
    stfs f2, 0x10(r21)
    li r5, 0x1
    lfs f0, lbl_806D7B08(r2)
    stfs f1, 0x14(r21)
    stfs f0, 0x18(r21)
    stfs f2, 0x1c(r21)
    stfs f2, 0x20(r21)
    stb r0, 0xc(r21)
    lwz r0, 0xc4(r31)
    lwz r4, 0xc8(r31)
    slwi r0, r0, 2
    add r4, r4, r0
    bl PtrVec_InsertFill
    lwz r3, 0xcc(r31)
    li r0, 0x6
    lwz r3, 0x0(r3)
    stw r0, 0x4(r3)
    lwz r3, g_cupId(r13)
    lwz r4, g_longRoundFlag(r13)
    bl fn_801D8D3C
    lwz r5, 0xcc(r31)
    li r3, 0x0
    lfs f0, lbl_806D7B20(r2)
    li r4, 0x1
    lwz r5, 0x0(r5)
    stfs f1, 0xc(r5)
    lwz r5, 0xcc(r31)
    lwz r5, 0x0(r5)
    stfs f0, 0x10(r5)
    bl fn_801699D8
    fn_80144C1C_L_80145870:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    psq_l f29, 0x78(r1), 0, 0
    lfd f29, 0x70(r1)
    psq_l f28, 0x68(r1), 0, 0
    lfd f28, 0x60(r1)
    lmw r21, 0x34(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

extern "C" void fn_801458A4(Pair *p)
{
    p->a = lbl_806D7AE4;
    p->b = lbl_806D7AE4;
}

extern "C" asm void fn_801458B4(void) { /* 0x801458B4 size:0x240 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    lis r4, lbl_8048EB44@ha
    lfs f1, lbl_806D7AE4(r2)
    stw r0, 0x54(r1)
    addi r0, r4, lbl_8048EB44@l
    li r4, 0x0
    lfs f0, lbl_806D7AF0(r2)
    stmw r27, 0x3c(r1)
    mr r31, r3
    lis r3, lbl_8048EEF4@ha
    stw r0, 0x14(r31)
    addi r0, r3, lbl_8048EEF4@l
    li r3, 0xc
    stw r4, 0x0(r31)
    stb r4, 0x4(r31)
    stfs f1, 0x8(r31)
    stfs f1, 0xc(r31)
    stfs f0, 0x10(r31)
    stw r0, 0x14(r31)
    stb r4, 0x18(r31)
    stfs f1, 0x1c(r31)
    stw r4, 0x20(r31)
    stb r4, 0x24(r31)
    stw r4, 0xc0(r31)
    stw r4, 0xc4(r31)
    stw r4, 0xc8(r31)
    bl Alloc
    mr. r28, r3
    beq fn_801458B4_L_80145974
    li r0, 0x0
    li r3, 0x30
    stb r0, 0x4(r28)
    stb r0, 0x5(r28)
    stw r0, 0x8(r28)
    bl Alloc
    mr. r29, r3
    beq fn_801458B4_L_80145970
    lfs f1, lbl_806D7B48(r2)
    li r4, 0x9e
    lfs f3, lbl_806D7AF0(r2)
    li r5, 0x1
    lfs f5, lbl_806D7AE4(r2)
    fmr f2, f1
    fmr f4, f3
    fmr f6, f5
    bl Sprite_CreateWithParams
    fn_801458B4_L_80145970:
    stw r29, 0x0(r28)
    fn_801458B4_L_80145974:
    stw r28, 0xcc(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq fn_801458B4_L_80145998
    li r4, 0x1c5
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_801458B4_L_80145998:
    lis r3, lbl_80361D80@ha
    li r30, 0x0
    addi r29, r3, lbl_80361D80@l
    mr r28, r30
    fn_801458B4_L_801459A8:
    lha r4, 0x0(r29)
    mr r3, r27
    addi r5, r1, 0x8
    bl fn_8019FF8C
    addi r30, r30, 0x1
    lfs f0, 0x8(r1)
    addi r0, r28, 0x28
    addi r28, r28, 0x4
    cmpwi r30, 0x26
    stfsx f0, r31, r0
    addi r29, r29, 0x2
    blt fn_801458B4_L_801459A8
    bl isJapanese
    cmpwi r3, 0x0
    beq fn_801458B4_L_80145AC0
    lfs f1, 0x44(r31)
    li r4, 0x15
    lfs f0, lbl_806D7B40(r2)
    subfic r0, r4, 0x16
    slwi r3, r4, 2
    fadds f1, f1, f0
    stfs f1, 0x48(r31)
    fadds f1, f1, f0
    stfs f1, 0x4c(r31)
    fadds f1, f1, f0
    stfs f1, 0x50(r31)
    fadds f1, f1, f0
    stfs f1, 0x54(r31)
    fadds f1, f1, f0
    stfs f1, 0x58(r31)
    fadds f1, f1, f0
    stfs f1, 0x5c(r31)
    fadds f1, f1, f0
    stfs f1, 0x60(r31)
    fadds f1, f1, f0
    stfs f1, 0x64(r31)
    fadds f1, f1, f0
    stfs f1, 0x68(r31)
    fadds f1, f1, f0
    stfs f1, 0x6c(r31)
    fadds f1, f1, f0
    stfs f1, 0x70(r31)
    fadds f1, f1, f0
    stfs f1, 0x74(r31)
    fadds f1, f1, f0
    stfs f1, 0x78(r31)
    fadds f1, f1, f0
    stfs f1, 0x7c(r31)
    fadds f1, f1, f0
    stfs f1, 0x80(r31)
    fadds f1, f1, f0
    stfs f1, 0x84(r31)
    fadds f1, f1, f0
    stfs f1, 0x88(r31)
    fadds f1, f1, f0
    stfs f1, 0x8c(r31)
    fadds f1, f1, f0
    stfs f1, 0x90(r31)
    fadds f1, f1, f0
    stfs f1, 0x94(r31)
    fadds f1, f1, f0
    mtctr r0
    cmpwi r4, 0x16
    bge fn_801458B4_L_80145AD0
    fn_801458B4_L_80145AA8:
    addi r0, r3, 0x44
    addi r3, r3, 0x4
    stfsx f1, r31, r0
    fadds f1, f1, f0
    bdnz fn_801458B4_L_80145AA8
    b fn_801458B4_L_80145AD0
    fn_801458B4_L_80145AC0:
    lfs f1, lbl_806D7B44(r2)
    lfs f0, 0x6c(r31)
    fadds f0, f1, f0
    stfs f0, 0x70(r31)
    fn_801458B4_L_80145AD0:
    mr r3, r27
    li r4, 0x1
    bl Sprite_Destroy
    mr r3, r31
    lmw r27, 0x3c(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" asm void fn_80145AF4(void) { /* 0x80145AF4 size:0x240 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    lis r4, lbl_8048EB44@ha
    lfs f1, lbl_806D7AE4(r2)
    stw r0, 0x54(r1)
    addi r0, r4, lbl_8048EB44@l
    li r4, 0x0
    lfs f0, lbl_806D7AF0(r2)
    stmw r27, 0x3c(r1)
    mr r31, r3
    lis r3, lbl_8048EEF4@ha
    stw r0, 0x14(r31)
    addi r0, r3, lbl_8048EEF4@l
    li r3, 0xc
    stw r4, 0x0(r31)
    stb r4, 0x4(r31)
    stfs f1, 0x8(r31)
    stfs f1, 0xc(r31)
    stfs f0, 0x10(r31)
    stw r0, 0x14(r31)
    stb r4, 0x18(r31)
    stfs f1, 0x1c(r31)
    stw r4, 0x20(r31)
    stb r4, 0x24(r31)
    stw r4, 0xc0(r31)
    stw r4, 0xc4(r31)
    stw r4, 0xc8(r31)
    bl Alloc
    mr. r28, r3
    beq fn_80145AF4_L_80145BB4
    li r0, 0x0
    li r3, 0x30
    stb r0, 0x4(r28)
    stb r0, 0x5(r28)
    stw r0, 0x8(r28)
    bl Alloc
    mr. r29, r3
    beq fn_80145AF4_L_80145BB0
    lfs f1, lbl_806D7B48(r2)
    li r4, 0x9e
    lfs f3, lbl_806D7AF0(r2)
    li r5, 0x1
    lfs f5, lbl_806D7AE4(r2)
    fmr f2, f1
    fmr f4, f3
    fmr f6, f5
    bl Sprite_CreateWithParams
    fn_80145AF4_L_80145BB0:
    stw r29, 0x0(r28)
    fn_80145AF4_L_80145BB4:
    stw r28, 0xcc(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq fn_80145AF4_L_80145BD8
    li r4, 0x1c5
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    fn_80145AF4_L_80145BD8:
    lis r3, lbl_80361D80@ha
    li r30, 0x0
    addi r29, r3, lbl_80361D80@l
    mr r28, r30
    fn_80145AF4_L_80145BE8:
    lha r4, 0x0(r29)
    mr r3, r27
    addi r5, r1, 0x8
    bl fn_8019FF8C
    addi r30, r30, 0x1
    lfs f0, 0x8(r1)
    addi r0, r28, 0x28
    addi r28, r28, 0x4
    cmpwi r30, 0x26
    stfsx f0, r31, r0
    addi r29, r29, 0x2
    blt fn_80145AF4_L_80145BE8
    bl isJapanese
    cmpwi r3, 0x0
    beq fn_80145AF4_L_80145D00
    lfs f1, 0x44(r31)
    li r4, 0x15
    lfs f0, lbl_806D7B40(r2)
    subfic r0, r4, 0x16
    slwi r3, r4, 2
    fadds f1, f1, f0
    stfs f1, 0x48(r31)
    fadds f1, f1, f0
    stfs f1, 0x4c(r31)
    fadds f1, f1, f0
    stfs f1, 0x50(r31)
    fadds f1, f1, f0
    stfs f1, 0x54(r31)
    fadds f1, f1, f0
    stfs f1, 0x58(r31)
    fadds f1, f1, f0
    stfs f1, 0x5c(r31)
    fadds f1, f1, f0
    stfs f1, 0x60(r31)
    fadds f1, f1, f0
    stfs f1, 0x64(r31)
    fadds f1, f1, f0
    stfs f1, 0x68(r31)
    fadds f1, f1, f0
    stfs f1, 0x6c(r31)
    fadds f1, f1, f0
    stfs f1, 0x70(r31)
    fadds f1, f1, f0
    stfs f1, 0x74(r31)
    fadds f1, f1, f0
    stfs f1, 0x78(r31)
    fadds f1, f1, f0
    stfs f1, 0x7c(r31)
    fadds f1, f1, f0
    stfs f1, 0x80(r31)
    fadds f1, f1, f0
    stfs f1, 0x84(r31)
    fadds f1, f1, f0
    stfs f1, 0x88(r31)
    fadds f1, f1, f0
    stfs f1, 0x8c(r31)
    fadds f1, f1, f0
    stfs f1, 0x90(r31)
    fadds f1, f1, f0
    stfs f1, 0x94(r31)
    fadds f1, f1, f0
    mtctr r0
    cmpwi r4, 0x16
    bge fn_80145AF4_L_80145D10
    fn_80145AF4_L_80145CE8:
    addi r0, r3, 0x44
    addi r3, r3, 0x4
    stfsx f1, r31, r0
    fadds f1, f1, f0
    bdnz fn_80145AF4_L_80145CE8
    b fn_80145AF4_L_80145D10
    fn_80145AF4_L_80145D00:
    lfs f1, lbl_806D7B44(r2)
    lfs f0, 0x6c(r31)
    fadds f0, f1, f0
    stfs f0, 0x70(r31)
    fn_80145AF4_L_80145D10:
    mr r3, r27
    li r4, 0x1
    bl Sprite_Destroy
    mr r3, r31
    lmw r27, 0x3c(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
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

extern "C" asm void fn_80145E14(void) { /* 0x80145E14 size:0xF0 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stw r31, 0x6c(r1)
    mr r31, r3
    addi r3, r1, 0x8
    bl ResCtrl_Init
    lha r3, 0x88(r31)
    li r0, 0x1
    lfs f0, lbl_806D7AF0(r2)
    stw r3, 0x8(r1)
    lfs f1, 0x80(r31)
    lfs f2, 0x68(r31)
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    lbz r0, 0xc(r31)
    cmplwi r0, 0x1
    bne fn_80145E14_L_80145E94
    lfs f1, lbl_806D7B4C(r2)
    li r3, -0x100
    lfs f0, 0x20(r31)
    fmuls f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x60(r1)
    lwz r0, 0x64(r1)
    rlwimi r3, r0, 0, 24, 31
    stw r3, 0x3c(r1)
    stw r3, 0x40(r1)
    stw r3, 0x44(r1)
    stw r3, 0x48(r1)
    fn_80145E14_L_80145E94:
    lfs f0, lbl_806D7AF0(r2)
    lbz r0, 0x24(r31)
    fmr f1, f0
    cmplwi r0, 0x1
    bne fn_80145E14_L_80145EAC
    lfs f0, 0x38(r31)
    fn_80145E14_L_80145EAC:
    lbz r0, 0x3c(r31)
    cmplwi r0, 0x1
    bne fn_80145E14_L_80145EBC
    lfs f1, 0x50(r31)
    fn_80145E14_L_80145EBC:
    stfs f0, 0x34(r1)
    stfs f1, 0x38(r1)
    lbz r0, 0x90(r31)
    cmplwi r0, 0x0
    beq fn_80145E14_L_80145EE4
    li r3, 0x1
    li r0, 0x4
    stw r3, 0x50(r1)
    stw r0, 0x54(r1)
    stw r3, 0x58(r1)
    fn_80145E14_L_80145EE4:
    lwz r4, 0x8c(r31)
    addi r3, r1, 0x8
    bl fn_8011FAFC
    lwz r0, 0x74(r1)
    lwz r31, 0x6c(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

extern "C" asm void dtor_80145F04(void) { /* 0x80145F04 size:0x98 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r1
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r29, r4
    stw r28, 0x20(r1)
    mr. r28, r3
    beq dtor_80145F04_L_80145F60
    lwz r30, 0x0(r28)
    cmplwi r30, 0x0
    beq dtor_80145F04_L_80145F50
    lwz r3, 0x0(r30)
    li r4, 0x1
    bl Sprite_Destroy
    mr r3, r30
    bl MemoryManager_TimedFree
    dtor_80145F04_L_80145F50:
    extsh. r0, r29
    ble dtor_80145F04_L_80145F60
    mr r3, r28
    bl MemoryManager_TimedFree
    dtor_80145F04_L_80145F60:
    mr r3, r28
    b dtor_80145F04_L_80145F74
    addi r3, r31, 0x8
    bl __unexpected
    dtor_80145F04_L_80145F70:
    b dtor_80145F04_L_80145F70
    dtor_80145F04_L_80145F74:
    mr r10, r31
    lwz r31, 0x2c(r31)
    lwz r30, 0x28(r10)
    lwz r29, 0x24(r10)
    lwz r28, 0x20(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
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

extern "C" asm struct PanelEntry **fn_80146000(struct EntryVec *v, int id) { /* 0x80146000 size:0xD0 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r4
    stw r30, 0x28(r1)
    mr r30, r3
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    lwz r0, 0x4(r3)
    cmplw r31, r0
    blt fn_80146000_L_801460A4
    lis r3, lbl_803F5710@ha
    addi r29, r1, 0x8
    addi r0, r3, lbl_803F5710@l
    lis r4, lbl_803F5700@ha
    stw r0, 0x8(r1)
    addi r0, r4, lbl_803F5700@l
    lis r3, lbl_80361E40@ha
    addi r28, r29, 0x4
    stw r0, 0x8(r1)
    addi r3, r3, lbl_80361E40@l
    bl strlen
    addi r3, r3, 0x1
    bl FUN_8003b120
    mr r4, r3
    mr r3, r28
    bl SharedPtr_Init
    lis r4, lbl_80361E40@ha
    lwz r3, 0x0(r28)
    addi r4, r4, lbl_80361E40@l
    bl strcpy
    lis r4, lbl_8048EF68@ha
    lis r3, lbl_80361E60@ha
    addi r0, r4, lbl_8048EF68@l
    lis r4, fn_801460D0@ha
    stw r0, 0x8(r1)
    addi r5, r4, fn_801460D0@l
    addi r3, r3, lbl_80361E60@l
    mr r4, r29
    bl __throw
    fn_80146000_L_801460A4:
    lwz r3, 0x8(r30)
    slwi r0, r31, 2
    add r3, r3, r0
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_801460D0(void) { /* 0x801460D0 size:0x90 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq fn_801460D0_L_80146144
    lis r3, lbl_8048EF68@ha
    addi r0, r3, lbl_8048EF68@l
    stw r0, 0x0(r30)
    beq fn_801460D0_L_80146134
    lis r3, lbl_803F5700@ha
    addic. r0, r30, 0x4
    addi r0, r3, lbl_803F5700@l
    stw r0, 0x0(r30)
    beq fn_801460D0_L_80146120
    addi r3, r30, 0x4
    li r4, -0x1
    bl dtor_80038E30
    fn_801460D0_L_80146120:
    cmplwi r30, 0x0
    beq fn_801460D0_L_80146134
    lis r3, lbl_803F5710@ha
    addi r0, r3, lbl_803F5710@l
    stw r0, 0x0(r30)
    fn_801460D0_L_80146134:
    extsh. r0, r31
    ble fn_801460D0_L_80146144
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_801460D0_L_80146144:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

