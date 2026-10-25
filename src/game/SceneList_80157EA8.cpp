
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D83D8[4];
extern unsigned char lbl_806D83E4[5];
extern unsigned char lbl_806D83F0[8];
extern unsigned char lbl_806D8438[3];
extern unsigned char lbl_806D8440[5];
extern unsigned char lbl_806D8450[4];
extern unsigned char lbl_806D8468[5];
extern unsigned char lbl_806D8474[5];
extern unsigned char lbl_806D847C[4];
extern unsigned char lbl_806D8480[4];
extern unsigned char lbl_806D8498[8];
extern unsigned char lbl_806D84A4[8];
extern unsigned char lbl_806D84AC[4];
extern unsigned char lbl_806D84D8[4];
/*
 * 0x80157940..0x8015A6E4: list helpers and the scene updates that use them.
 */
#pragma cplusplus on

struct ListNode {
    ListNode *prev;
    ListNode *next;
};

struct ListIter {
    ListNode *n;
};

struct List {
    int size;
    ListNode head;
};

struct DataBuf {
    int pad0;
    void *data;
};

class DrawObj {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void Draw();
};

struct DrawScene {
    char pad0[4];
    unsigned char hidden;
    char pad5[3];
    unsigned char state;
    char pad9[0x2c - 9];
    DrawObj *a;
    DrawObj *b;
};

struct InputView {
    char pad[0x14];
    int dir;
};

struct MenuTarget {
    char pad0[0xc];
    unsigned char sel;
    char padD[0x19d - 0xd];
    unsigned char flag;
};

struct OptionMenu {
    char pad0[0x1d];
    unsigned char toggleEnabled;
    char pad1E[2];
    MenuTarget *target;
    char pad24[0x20];
    float blink;
    char pad48[4];
    bool toggle;
    char pad4D[3];
    float fade50;
    float fade54;
    unsigned char sel;
    char pad59[3];
    float blink2;
    char pad60[4];
    int value;
    char pad68[0x1c];
    int scroll;
    int scrollTimer;
};

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
extern void Alloc();
extern void __throw();
extern void fn_801F7DAC();
void HSD_StateInvalidate(int state);
void fn_8011F994(int i);
void fn_8013D940(int i);
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void RumbleUpdate();
extern void SetRumbleMode();
extern void SetSyncTarget();
int WeatherSystem_PickVariant(int sel);
void clStream_setVolume(int ch, int vol);
extern void fn_8015A6E4();
extern void fn_801678FC();
extern void fn_801698B4();
unsigned char fn_8019083C(int ch);
extern void fn_801932F8();
extern void fn_801FE27C();
extern void fn_801FE348();
extern void fn_801FE390();
extern void fn_801FEF18();
extern unsigned int lbl_806D8390;
extern const float lbl_806D8394;
extern const float lbl_806D8398;
extern const float lbl_806D839C;
extern unsigned int lbl_806D83A0;
extern unsigned int lbl_806D83A4;
extern unsigned int lbl_806D83A8;
extern unsigned int lbl_806D83AC;
extern const float lbl_806D83B0;
extern unsigned int lbl_806D83B4;
extern unsigned int lbl_806D83B8;
extern unsigned int lbl_806D83BC;
extern unsigned int lbl_806D83C0;
void fn_801FE36C(void);
extern struct InputView *g_pInputState;
extern const float lbl_806D83C4;
extern const float lbl_806D83C8;
extern void GetTextureByIdAndLang();
extern void fn_80167744();
extern void fn_80168798();
extern void fn_80168D84();
extern void fn_80169334();
extern void fn_801695E0();
extern void isJapanese();
extern unsigned int lbl_806D83CC;
extern unsigned int lbl_806D83D0;
extern unsigned int lbl_806D83D4;
extern unsigned int lbl_806D83DC;
extern unsigned int lbl_806D83E0;
extern unsigned int lbl_806D83EC;
extern unsigned int lbl_806D83F8;
extern unsigned int lbl_806D83FC;
extern unsigned int lbl_806D8400;
extern unsigned int lbl_806D8404;
extern unsigned int lbl_806D8408;
extern unsigned int lbl_806D840C;
extern unsigned int lbl_806D8410;
extern unsigned int lbl_806D8414;
extern unsigned int lbl_806D8418;
extern unsigned int lbl_806D841C;
extern unsigned int lbl_806D8420;
extern unsigned int lbl_806D8424;
extern unsigned int lbl_806D8428;
extern unsigned int lbl_806D842C;
extern unsigned int lbl_806D8430;
extern unsigned int lbl_806D8434;
extern unsigned int lbl_806D843C;
extern unsigned int lbl_806D8448;
extern unsigned int lbl_80367E24[];
extern unsigned int lbl_80367E38[];
extern void fn_80168404();
extern unsigned int lbl_806D8454;
extern unsigned int lbl_806D8458;
extern unsigned int lbl_806D845C;
extern unsigned int lbl_806D8460;
extern unsigned int lbl_806D8464;
extern unsigned int lbl_806D8470;
extern unsigned int lbl_806D8484;
extern unsigned int lbl_806D8488;
extern unsigned int lbl_806D848C;
extern unsigned int lbl_806D8490;
extern unsigned int lbl_806D8494;
extern unsigned int lbl_806D84A0;
extern unsigned int lbl_803678D8[];
extern unsigned int lbl_806D84B0;
extern unsigned int lbl_806D84B4;
extern unsigned int lbl_806D84B8;
extern unsigned int lbl_806D84BC;
extern unsigned int lbl_806D84C0;
extern unsigned int lbl_806D84C4;
extern unsigned int lbl_806D84C8;
extern unsigned int lbl_806D84CC;
extern unsigned int lbl_806D84D0;
extern unsigned int lbl_806D84D4;
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void Item_GetDescriptorFieldC();
extern void PlayerData_GetUnlockedItemIdByIndex_U8();
extern void fn_8013BEC8();
extern void fn_80168B90();
extern void fn_8016918C();
extern void fn_8023D938();
extern void fn_8023DAA8();
extern unsigned int lbl_806D84DC;
extern unsigned int lbl_806D84E0;
extern unsigned int lbl_806D84E4;
extern unsigned int lbl_806D84E8;
extern unsigned int lbl_806D84EC;
extern unsigned int lbl_806D84F0;
extern unsigned int lbl_806D84F4;
extern unsigned int lbl_806D84F8;
extern unsigned int lbl_806D84FC;
extern unsigned int lbl_806D8500;
extern unsigned int lbl_806D8504;
extern unsigned int lbl_806D8508;
extern unsigned int lbl_806D850C;
extern unsigned int lbl_806D8510;
extern unsigned int lbl_806D8514;
extern unsigned int lbl_806D8518;
extern unsigned int lbl_806D851C;
extern unsigned int lbl_806D8520;
extern unsigned int lbl_806D8524;
extern unsigned int lbl_806D8528;
extern unsigned int lbl_806D852C;
extern unsigned int lbl_806D8530;
extern unsigned int lbl_806D8534;
extern unsigned int lbl_806D8538;
extern unsigned int lbl_806D853C;
extern unsigned int lbl_806D8540;
extern unsigned int lbl_806D8544;
extern unsigned int lbl_806D8548;
extern unsigned int lbl_806D854C;
extern unsigned int lbl_806D8550;
extern unsigned int lbl_806D8554;
extern unsigned int lbl_806D8558;
extern unsigned int lbl_806D855C;
extern unsigned int lbl_806D8560;
extern unsigned int lbl_806D8564;
extern unsigned int lbl_806D8568;
extern unsigned int lbl_806D856C;
extern unsigned int lbl_806D8570;
asm void fn_80157940(void);
void fn_801579F0(ListIter *ret, List *l, ListIter *it);
asm void fn_80157A68(void);
void fn_80157B20(List *l);
asm void fn_80157B38(void);
void fn_80157BE8(ListIter *ret, List *l, ListIter *it);
asm void fn_80157C60(void);
void fn_80157D18(List *l);
asm void fn_80157D30(void);
asm void fn_80157DE0(void);
void fn_80157EA8(List *l);
DataBuf *dtor_80157EC0(DataBuf *self, short flag);
void fn_80157F1C(DrawScene *self);
asm void fn_80157FB4(void);
void fn_801589BC(OptionMenu *self, int mode);
asm void fn_80158CE4(void);
asm void fn_8015915C(void);
asm void fn_801596D4(void);
asm void fn_80159BD0(void);

#pragma section R ".extab_user"




__declspec(section ".extab_user") static const unsigned char extab_fn_80157FB4[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_80158CE4[8] = {
    0x32, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8015915C[8] = {
    0x32, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_801596D4[8] = {
    0x62, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80159BD0[8] = {
    0x4A, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"




__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157FB4 = {
    (void *)&fn_80157FB4, 0x00000A08, (void *)extab_fn_80157FB4
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80158CE4 = {
    (void *)&fn_80158CE4, 0x00000478, (void *)extab_fn_80158CE4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8015915C = {
    (void *)&fn_8015915C, 0x00000578, (void *)extab_fn_8015915C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801596D4 = {
    (void *)&fn_801596D4, 0x000004FC, (void *)extab_fn_801596D4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80159BD0 = {
    (void *)&fn_80159BD0, 0x00000B14, (void *)extab_fn_80159BD0
};

}

static inline InputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}



extern "C" void fn_80157EA8(List *l)
{
    ListNode *h = &l->head;
    l->size = 0;
    h->next = h;
    h->prev = h;
}

extern "C" DataBuf *dtor_80157EC0(DataBuf *self, short flag)
{
    if (self) {
        if (self->data) {
            MemoryManager_TimedFree(self->data);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" void fn_80157F1C(DrawScene *self)
{
    if (self->hidden == 0 && self->state == 1) {
        self->a->Draw();
        self->b->Draw();
        HSD_StateInvalidate(-1);
        for (int i = 0; i < 8; i++) {
            fn_8013D940(i);
            fn_8011F994(i);
        }
        HSD_StateInvalidate(-1);
    }
}

extern "C" asm void fn_80157FB4(void) { /* 0x80157FB4 size:0xA08 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r31, r3
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    bne fn_80157FB4_L_8015899C
    lwz r3, 0x28(r31)
    bl fn_801FE27C
    lwz r3, 0x2c(r31)
    lwz r4, 0x28(r31)
    bl fn_801FEF18
    lwz r3, 0x28(r31)
    cmpwi r3, 0x0
    beq fn_80157FB4_L_80158008
    subi r0, r3, 0x1
    stw r0, 0x28(r31)
    fn_80157FB4_L_80158008:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D8390(r2)
    fcmpo cr0, f1, f0
    ble fn_80157FB4_L_80158058
    lbz r0, 0x1c(r31)
    cmplwi r0, 0x0
    bne fn_80157FB4_L_8015804C
    li r0, 0x1
    stb r0, 0x1c(r31)
    stb r0, 0x1d(r31)
    b fn_80157FB4_L_80158064
    fn_80157FB4_L_8015804C:
    li r0, 0x0
    stb r0, 0x1d(r31)
    b fn_80157FB4_L_80158064
    fn_80157FB4_L_80158058:
    li r0, 0x0
    stb r0, 0x1c(r31)
    stb r0, 0x1d(r31)
    fn_80157FB4_L_80158064:
    lwz r0, 0xc(r31)
    cmpwi r0, 0x1
    bne fn_80157FB4_L_80158314
    lwz r0, 0x28(r31)
    cmpwi r0, 0x0
    beq fn_80157FB4_L_801580CC
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x100
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne fn_80157FB4_L_801580CC
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x2000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80157FB4_L_801580F4
    fn_80157FB4_L_801580CC:
    li r3, 0x0
    li r4, 0x4
    li r5, 0xa
    bl SetRumbleMode
    bl fn_801FE348
    li r3, 0xe
    bl SetSyncTarget
    li r0, 0x8
    stw r0, 0xc(r31)
    b fn_80157FB4_L_80158314
    fn_80157FB4_L_801580F4:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x400
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80157FB4_L_80158314
    bl fn_801FE390
    lwz r3, 0x14(r31)
    addi r0, r3, 0x1
    stw r0, 0x18(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x5
    blt fn_80157FB4_L_80158140
    li r0, 0x0
    stw r0, 0x18(r31)
    fn_80157FB4_L_80158140:
    li r0, 0x2
    lfs f0, lbl_806D8394(r2)
    stw r0, 0xc(r31)
    stfs f0, 0x10(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x2
    beq fn_80157FB4_L_80158314
    bge fn_80157FB4_L_80158170
    cmpwi r0, 0x0
    beq fn_80157FB4_L_80158180
    bge fn_80157FB4_L_801581C0
    b fn_80157FB4_L_80158314
    fn_80157FB4_L_80158170:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_80158314
    bge fn_80157FB4_L_80158314
    b fn_80157FB4_L_80158304
    fn_80157FB4_L_80158180:
    stfs f0, 0x44(r31)
    li r3, 0x1
    lfs f1, lbl_806D8398(r2)
    lfs f0, lbl_806D839C(r2)
    stfs f1, 0x50(r31)
    stfs f0, 0x54(r31)
    lbz r30, 0x58(r31)
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_80157FB4_L_80158314
    mr r3, r30
    bl WeatherSystem_PickVariant
    mr r4, r3
    li r3, 0x1
    bl clStream_setVolume
    b fn_80157FB4_L_80158314
    fn_80157FB4_L_801581C0:
    stfs f0, 0x5c(r31)
    li r4, 0x0
    li r0, 0xc
    stw r4, 0x64(r31)
    stw r4, 0x60(r31)
    mtctr r0
    fn_80157FB4_L_801581D8:
    lwz r3, 0x20(r31)
    addi r0, r4, 0xa8
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80157FB4_L_80158208
    lwz r3, 0x60(r31)
    addi r0, r3, 0x1
    stw r0, 0x60(r31)
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    bge fn_80157FB4_L_80158208
    stw r4, 0x64(r31)
    fn_80157FB4_L_80158208:
    lwz r3, 0x20(r31)
    addi r0, r4, 0xa9
    addi r4, r4, 0x1
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80157FB4_L_8015823C
    lwz r3, 0x60(r31)
    addi r0, r3, 0x1
    stw r0, 0x60(r31)
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    bge fn_80157FB4_L_8015823C
    stw r4, 0x64(r31)
    fn_80157FB4_L_8015823C:
    lwz r3, 0x20(r31)
    addi r0, r4, 0xa9
    addi r4, r4, 0x1
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80157FB4_L_80158270
    lwz r3, 0x60(r31)
    addi r0, r3, 0x1
    stw r0, 0x60(r31)
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    bge fn_80157FB4_L_80158270
    stw r4, 0x64(r31)
    fn_80157FB4_L_80158270:
    lwz r3, 0x20(r31)
    addi r0, r4, 0xa9
    addi r4, r4, 0x1
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80157FB4_L_801582A4
    lwz r3, 0x60(r31)
    addi r0, r3, 0x1
    stw r0, 0x60(r31)
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    bge fn_80157FB4_L_801582A4
    stw r4, 0x64(r31)
    fn_80157FB4_L_801582A4:
    lwz r3, 0x20(r31)
    addi r0, r4, 0xa9
    addi r4, r4, 0x1
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80157FB4_L_801582D8
    lwz r3, 0x60(r31)
    addi r0, r3, 0x1
    stw r0, 0x60(r31)
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    bge fn_80157FB4_L_801582D8
    stw r4, 0x64(r31)
    fn_80157FB4_L_801582D8:
    addi r4, r4, 0x1
    bdnz fn_80157FB4_L_801581D8
    li r3, 0x1
    bl fn_8019083C
    clrlwi. r0, r3, 24
    beq fn_80157FB4_L_80158314
    bl fn_801932F8
    mr r4, r3
    li r3, 0x1
    bl clStream_setVolume
    b fn_80157FB4_L_80158314
    fn_80157FB4_L_80158304:
    li r3, -0x1
    li r0, 0x0
    stw r3, 0x84(r31)
    stw r0, 0x88(r31)
    fn_80157FB4_L_80158314:
    lfs f1, lbl_806D83A0(r2)
    li r3, 0x0
    lfs f2, lbl_806D83A4(r2)
    li r4, 0x640
    li r5, 0x0
    bl fn_801698B4
    lfs f1, lbl_806D83A8(r2)
    li r3, 0x0
    lfs f2, lbl_806D83AC(r2)
    li r4, 0x63f
    li r5, 0x0
    bl fn_801698B4
    lwz r3, 0x2c(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x30(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x34(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x34(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r3, 0x38(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x3c(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x40(r31)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r0, 0xc(r31)
    cmpwi r0, 0x2
    beq fn_80157FB4_L_801585D4
    bge fn_80157FB4_L_801583F0
    cmpwi r0, 0x0
    beq fn_80157FB4_L_80158408
    bge fn_80157FB4_L_8015850C
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_801583F0:
    cmpwi r0, 0x9
    beq fn_80157FB4_L_80158890
    bge fn_80157FB4_L_80158984
    cmpwi r0, 0x8
    bge fn_80157FB4_L_801587C4
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_80158408:
    lfs f1, 0x10(r31)
    lfs f3, lbl_806D83B0(r2)
    lfs f0, lbl_806D83B4(r2)
    fadds f1, f1, f3
    stfs f1, 0x10(r31)
    lfs f1, 0x10(r31)
    lwz r0, 0x14(r31)
    fdivs f31, f1, f0
    cmpwi r0, 0x2
    beq fn_80157FB4_L_80158484
    bge fn_80157FB4_L_80158444
    cmpwi r0, 0x0
    beq fn_80157FB4_L_80158454
    bge fn_80157FB4_L_8015846C
    b fn_80157FB4_L_801584C8
    fn_80157FB4_L_80158444:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_801584B4
    bge fn_80157FB4_L_801584C8
    b fn_80157FB4_L_8015849C
    fn_80157FB4_L_80158454:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015A6E4
    b fn_80157FB4_L_801584C8
    fn_80157FB4_L_8015846C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80159BD0
    b fn_80157FB4_L_801584C8
    fn_80157FB4_L_80158484:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_801596D4
    b fn_80157FB4_L_801584C8
    fn_80157FB4_L_8015849C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015915C
    b fn_80157FB4_L_801584C8
    fn_80157FB4_L_801584B4:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80158CE4
    fn_80157FB4_L_801584C8:
    lfs f1, lbl_806D8394(r2)
    li r3, 0x2
    lfs f0, lbl_806D83B0(r2)
    fmr f2, f1
    fmr f3, f1
    fsubs f4, f0, f31
    bl fn_801678FC
    lfs f1, 0x10(r31)
    lfs f0, lbl_806D83B4(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80157FB4_L_80158984
    li r0, 0x1
    lfs f0, lbl_806D8394(r2)
    stw r0, 0xc(r31)
    stfs f0, 0x10(r31)
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_8015850C:
    lwz r4, 0x14(r31)
    mr r3, r31
    bl fn_801589BC
    lwz r0, 0x14(r31)
    cmpwi r0, 0x2
    beq fn_80157FB4_L_80158580
    bge fn_80157FB4_L_80158538
    cmpwi r0, 0x0
    beq fn_80157FB4_L_80158548
    bge fn_80157FB4_L_80158564
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_80158538:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_801585B8
    bge fn_80157FB4_L_80158984
    b fn_80157FB4_L_8015859C
    fn_80157FB4_L_80158548:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_8015A6E4
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_80158564:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_80159BD0
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_80158580:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_801596D4
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_8015859C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_8015915C
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_801585B8:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_80158CE4
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_801585D4:
    lfs f2, 0x10(r31)
    lfs f1, lbl_806D83B0(r2)
    lfs f0, lbl_806D83B8(r2)
    fadds f1, f2, f1
    stfs f1, 0x10(r31)
    lfs f1, 0x10(r31)
    lwz r0, 0x18(r31)
    fdivs f31, f1, f0
    cmpwi r0, 0x2
    beq fn_80157FB4_L_80158658
    bge fn_80157FB4_L_80158610
    cmpwi r0, 0x0
    beq fn_80157FB4_L_80158620
    bge fn_80157FB4_L_8015863C
    b fn_80157FB4_L_801586A8
    fn_80157FB4_L_80158610:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_80158690
    bge fn_80157FB4_L_801586A8
    b fn_80157FB4_L_80158674
    fn_80157FB4_L_80158620:
    lfs f1, lbl_806D8394(r2)
    fmr f3, f31
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015A6E4
    b fn_80157FB4_L_801586A8
    fn_80157FB4_L_8015863C:
    lfs f1, lbl_806D8394(r2)
    fmr f3, f31
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80159BD0
    b fn_80157FB4_L_801586A8
    fn_80157FB4_L_80158658:
    lfs f1, lbl_806D8394(r2)
    fmr f3, f31
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_801596D4
    b fn_80157FB4_L_801586A8
    fn_80157FB4_L_80158674:
    lfs f1, lbl_806D8394(r2)
    fmr f3, f31
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015915C
    b fn_80157FB4_L_801586A8
    fn_80157FB4_L_80158690:
    lfs f1, lbl_806D8394(r2)
    fmr f3, f31
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80158CE4
    fn_80157FB4_L_801586A8:
    lfs f1, lbl_806D83BC(r2)
    li r3, 0x1
    lfs f0, lbl_806D83A8(r2)
    li r4, 0x63f
    lfs f2, lbl_806D83AC(r2)
    li r5, 0x0
    fnmsubs f1, f1, f31, f0
    bl fn_801698B4
    lwz r0, 0x14(r31)
    cmpwi r0, 0x2
    beq fn_80157FB4_L_80158738
    bge fn_80157FB4_L_801586E8
    cmpwi r0, 0x0
    beq fn_80157FB4_L_801586F8
    bge fn_80157FB4_L_80158718
    b fn_80157FB4_L_80158794
    fn_80157FB4_L_801586E8:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_80158778
    bge fn_80157FB4_L_80158794
    b fn_80157FB4_L_80158758
    fn_80157FB4_L_801586F8:
    lfs f0, lbl_806D83C0(r2)
    mr r3, r31
    lfs f2, lbl_806D8394(r2)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f3, lbl_806D83B0(r2)
    bl fn_8015A6E4
    b fn_80157FB4_L_80158794
    fn_80157FB4_L_80158718:
    lfs f0, lbl_806D83C0(r2)
    mr r3, r31
    lfs f2, lbl_806D8394(r2)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f3, lbl_806D83B0(r2)
    bl fn_80159BD0
    b fn_80157FB4_L_80158794
    fn_80157FB4_L_80158738:
    lfs f0, lbl_806D83C0(r2)
    mr r3, r31
    lfs f2, lbl_806D8394(r2)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f3, lbl_806D83B0(r2)
    bl fn_801596D4
    b fn_80157FB4_L_80158794
    fn_80157FB4_L_80158758:
    lfs f0, lbl_806D83C0(r2)
    mr r3, r31
    lfs f2, lbl_806D8394(r2)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f3, lbl_806D83B0(r2)
    bl fn_8015915C
    b fn_80157FB4_L_80158794
    fn_80157FB4_L_80158778:
    lfs f0, lbl_806D83C0(r2)
    mr r3, r31
    lfs f2, lbl_806D8394(r2)
    li r4, 0x2
    fmuls f1, f0, f31
    lfs f3, lbl_806D83B0(r2)
    bl fn_80158CE4
    fn_80157FB4_L_80158794:
    lfs f1, 0x10(r31)
    lfs f0, lbl_806D83B8(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80157FB4_L_80158984
    lwz r3, 0x18(r31)
    li r0, 0x1
    lfs f0, lbl_806D8394(r2)
    stw r3, 0x14(r31)
    stw r0, 0xc(r31)
    stfs f0, 0x10(r31)
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_801587C4:
    lwz r0, 0x14(r31)
    cmpwi r0, 0x2
    beq fn_80157FB4_L_8015882C
    bge fn_80157FB4_L_801587E4
    cmpwi r0, 0x0
    beq fn_80157FB4_L_801587F4
    bge fn_80157FB4_L_80158810
    b fn_80157FB4_L_8015887C
    fn_80157FB4_L_801587E4:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_80158864
    bge fn_80157FB4_L_8015887C
    b fn_80157FB4_L_80158848
    fn_80157FB4_L_801587F4:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_8015A6E4
    b fn_80157FB4_L_8015887C
    fn_80157FB4_L_80158810:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_80159BD0
    b fn_80157FB4_L_8015887C
    fn_80157FB4_L_8015882C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_801596D4
    b fn_80157FB4_L_8015887C
    fn_80157FB4_L_80158848:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_8015915C
    b fn_80157FB4_L_8015887C
    fn_80157FB4_L_80158864:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    lfs f3, lbl_806D83B0(r2)
    li r4, 0x1
    fmr f2, f1
    bl fn_80158CE4
    fn_80157FB4_L_8015887C:
    li r0, 0x9
    lfs f0, lbl_806D8394(r2)
    stw r0, 0xc(r31)
    stfs f0, 0x10(r31)
    b fn_80157FB4_L_80158984
    fn_80157FB4_L_80158890:
    lfs f1, 0x10(r31)
    lfs f3, lbl_806D83B0(r2)
    lfs f0, lbl_806D83B4(r2)
    fadds f1, f1, f3
    stfs f1, 0x10(r31)
    lfs f1, 0x10(r31)
    lwz r0, 0x14(r31)
    fdivs f31, f1, f0
    cmpwi r0, 0x2
    beq fn_80157FB4_L_8015890C
    bge fn_80157FB4_L_801588CC
    cmpwi r0, 0x0
    beq fn_80157FB4_L_801588DC
    bge fn_80157FB4_L_801588F4
    b fn_80157FB4_L_80158950
    fn_80157FB4_L_801588CC:
    cmpwi r0, 0x4
    beq fn_80157FB4_L_8015893C
    bge fn_80157FB4_L_80158950
    b fn_80157FB4_L_80158924
    fn_80157FB4_L_801588DC:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015A6E4
    b fn_80157FB4_L_80158950
    fn_80157FB4_L_801588F4:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80159BD0
    b fn_80157FB4_L_80158950
    fn_80157FB4_L_8015890C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_801596D4
    b fn_80157FB4_L_80158950
    fn_80157FB4_L_80158924:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_8015915C
    b fn_80157FB4_L_80158950
    fn_80157FB4_L_8015893C:
    lfs f1, lbl_806D8394(r2)
    mr r3, r31
    li r4, 0x1
    fmr f2, f1
    bl fn_80158CE4
    fn_80157FB4_L_80158950:
    lfs f1, lbl_806D8394(r2)
    fmr f4, f31
    li r3, 0x2
    fmr f2, f1
    fmr f3, f1
    bl fn_801678FC
    lfs f1, 0x10(r31)
    lfs f0, lbl_806D83B4(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80157FB4_L_80158984
    li r0, 0x1
    stb r0, 0x4(r31)
    fn_80157FB4_L_80158984:
    bl RumbleUpdate
    lbz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_80157FB4_L_8015899C
    li r0, 0x1
    stb r0, 0x8(r31)
    fn_80157FB4_L_8015899C:
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_801589BC(OptionMenu *self, int mode) {
    switch (mode) {
    case 0:
        if (input_state()) {
            int dir = input_state()->dir;
            if (dir == 1) {
                if (self->sel < 4) {
                    fn_801FE36C();
                    self->sel++;
                    self->target->sel = self->sel;
                    self->fade50 = lbl_806D8394;
                    self->fade54 = lbl_806D8394;
                    unsigned char v = self->sel;
                    if (fn_8019083C(1)) clStream_setVolume(1, WeatherSystem_PickVariant(v));
                }
            } else if (dir == -1) {
                if (self->sel != 0) {
                    fn_801FE36C();
                    self->sel--;
                    self->target->sel = self->sel;
                    self->fade50 = lbl_806D8394;
                    self->fade54 = lbl_806D8394;
                    unsigned char v = self->sel;
                    if (fn_8019083C(1)) clStream_setVolume(1, WeatherSystem_PickVariant(v));
                }
            }
        }
        if (self->toggleEnabled) {
            fn_801FE36C();
            self->toggle = !self->toggle;
            self->target->flag = self->toggle;
        }
        if (self->fade50 < lbl_806D8398) self->fade50 += lbl_806D83B0;
        if (self->fade54 < lbl_806D839C) self->fade54 += lbl_806D83B0;
        if ((self->blink += lbl_806D83B0) >= lbl_806D83C4) self->blink = lbl_806D8394;
        break;
    case 1:
        if (input_state()) {
            int dir = input_state()->dir;
            if (dir == 1) {
                fn_801FE36C();
                self->value++;
                if (self->value >= 60) self->value = 0;
                self->blink2 = lbl_806D8394;
            } else if (dir == -1) {
                fn_801FE36C();
                self->value--;
                if (self->value < 0) self->value = 59;
                self->blink2 = lbl_806D8394;
            }
        }
        if ((self->blink2 += lbl_806D83B0) >= lbl_806D83C8) self->blink2 = lbl_806D8394;
        break;
    case 2:
        break;
    case 3:
        if (self->scroll < 0) {
            if (self->scrollTimer > 0) self->scrollTimer--;
            else { self->scroll = 0; self->scrollTimer = 0; }
        } else if (++self->scrollTimer >= 4) {
            if (++self->scroll < 31) self->scrollTimer = 0;
            else { self->scroll = -1; self->scrollTimer = 120; }
        }
        break;
    case 4:
        break;
    }
}

extern "C" asm void fn_80158CE4(void) { /* 0x80158CE4 size:0x478 */
    nofralloc
    stwu r1, -0xe0(r1)
    mflr r0
    stw r0, 0xe4(r1)
    stfd f31, 0xd0(r1)
    psq_st f31, 0xd8(r1), 0, 0
    stfd f30, 0xc0(r1)
    psq_st f30, 0xc8(r1), 0, 0
    stfd f29, 0xb0(r1)
    psq_st f29, 0xb8(r1), 0, 0
    stfd f28, 0xa0(r1)
    psq_st f28, 0xa8(r1), 0, 0
    stfd f27, 0x90(r1)
    psq_st f27, 0x98(r1), 0, 0
    stfd f26, 0x80(r1)
    psq_st f26, 0x88(r1), 0, 0
    stfd f25, 0x70(r1)
    psq_st f25, 0x78(r1), 0, 0
    stfd f24, 0x60(r1)
    psq_st f24, 0x68(r1), 0, 0
    stfd f23, 0x50(r1)
    psq_st f23, 0x58(r1), 0, 0
    stfd f22, 0x40(r1)
    psq_st f22, 0x48(r1), 0, 0
    stfd f21, 0x30(r1)
    psq_st f21, 0x38(r1), 0, 0
    stmw r26, 0x18(r1)
    fmr f23, f1
    mr r26, r3
    fmr f22, f2
    mr r31, r4
    fmr f24, f3
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80158CE4_L_80158DE0
    lfs f0, lbl_806D83D0(r2)
    lis r3, lbl_80367E24@ha
    lfs f1, lbl_806D83CC(r2)
    addi r4, r3, lbl_80367E24@l
    fadds f21, f0, f22
    mr r3, r31
    fmr f3, f24
    fadds f1, f1, f23
    fmr f2, f21
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f0, lbl_806D83D4(r2)
    fmr f2, f21
    fmr f3, f24
    mr r3, r31
    fadds f1, f0, f23
    la r4, lbl_806D83D8(r2)  /* lbl_806D83D8 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f24
    lfs f0, lbl_806D83E0(r2)
    mr r3, r31
    fadds f1, f1, f23
    la r4, lbl_806D83E4(r2)  /* lbl_806D83E4 */
    fadds f2, f0, f22
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_80158CE4_L_80158E50
    fn_80158CE4_L_80158DE0:
    lfs f0, lbl_806D83D0(r2)
    lis r3, lbl_80367E38@ha
    lfs f1, lbl_806D83CC(r2)
    addi r4, r3, lbl_80367E38@l
    fadds f21, f0, f22
    mr r3, r31
    fmr f3, f24
    fadds f1, f1, f23
    fmr f2, f21
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D83EC(r2)
    fmr f2, f21
    fmr f3, f24
    mr r3, r31
    fadds f1, f0, f23
    la r4, lbl_806D83D8(r2)  /* lbl_806D83D8 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f24
    lfs f0, lbl_806D83E0(r2)
    mr r3, r31
    fadds f1, f1, f23
    la r4, lbl_806D83F0(r2)  /* lbl_806D83F0 */
    fadds f2, f0, f22
    creqv 6, 6, 6
    bl fn_80168D84
    fn_80158CE4_L_80158E50:
    lfs f1, lbl_806D83F8(r2)
    mr r28, r26
    lfs f0, lbl_806D83FC(r2)
    li r27, 0x0
    fadds f27, f1, f23
    lfs f28, lbl_806D8398(r2)
    fadds f26, f0, f22
    lfs f29, lbl_806D8400(r2)
    lfd f30, lbl_806D8448(r2)
    lis r29, 0x4330
    lfs f31, lbl_806D8394(r2)
    fn_80158CE4_L_80158E7C:
    xoris r0, r27, 0x8000
    lfs f3, lbl_806D8404(r2)
    stw r0, 0xc(r1)
    fmr f2, f26
    fmr f4, f3
    mr r3, r31
    stw r29, 0x8(r1)
    fmr f5, f24
    li r4, 0x7db
    lfd f0, 0x8(r1)
    li r5, 0x0
    fsubs f0, f0, f30
    fmadds f0, f29, f0, f27
    fadds f25, f28, f0
    fmr f1, f25
    bl fn_80169334
    lfs f0, 0x8c(r28)
    fcmpo cr0, f0, f31
    ble fn_80158CE4_L_80159098
    lfs f1, lbl_806D8408(r2)
    fmr f3, f24
    lfs f0, lbl_806D840C(r2)
    mr r3, r31
    fsubs f1, f25, f1
    li r4, 0x7dc
    fsubs f2, f26, f0
    li r5, 0x0
    bl fn_801695E0
    lfs f1, lbl_806D8410(r2)
    fmr f3, f24
    lfs f0, lbl_806D840C(r2)
    mr r3, r31
    fadds f1, f1, f25
    addi r4, r27, 0x7dd
    fsubs f2, f26, f0
    li r5, 0x0
    bl fn_801695E0
    lfs f1, lbl_806D83B0(r2)
    fmr f5, f24
    lfs f0, lbl_806D83B8(r2)
    mr r3, r31
    lfs f3, lbl_806D8414(r2)
    fsubs f1, f25, f1
    lwz r4, 0xa4(r28)
    fmr f4, f3
    li r5, 0x0
    fsubs f2, f26, f0
    addi r4, r4, 0x76c
    bl fn_80169334
    lwz r0, 0xec(r28)
    cmpwi r0, 0x2
    bne fn_80158CE4_L_80158F78
    lfs f1, lbl_806D83B4(r2)
    fmr f5, f24
    lfs f0, lbl_806D8418(r2)
    mr r3, r31
    lfs f3, lbl_806D841C(r2)
    fadds f1, f1, f25
    fsubs f2, f26, f0
    fmr f4, f3
    li r4, 0x7b0
    li r5, 0x0
    bl fn_80169334
    fn_80158CE4_L_80158F78:
    lfs f1, lbl_806D83B0(r2)
    fmr f3, f24
    lfs f0, lbl_806D83B8(r2)
    mr r3, r31
    lwz r0, 0xa4(r28)
    fsubs f1, f25, f1
    lwz r4, 0xbc(r28)
    slwi r0, r0, 1
    fadds f2, f0, f26
    add r4, r0, r4
    li r5, 0x0
    addi r4, r4, 0x7e4
    bl fn_801695E0
    lwz r0, 0xd4(r28)
    cmpwi r0, 0x0
    beq fn_80158CE4_L_80159028
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80158CE4_L_80158FF8
    li r3, 0x39
    li r4, -0x1
    bl GetTextureByIdAndLang
    lfs f1, lbl_806D8420(r2)
    mr r4, r3
    lfs f0, lbl_806D8424(r2)
    fmr f3, f24
    fsubs f1, f25, f1
    mr r3, r31
    fadds f2, f0, f26
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_80158CE4_L_80159028
    fn_80158CE4_L_80158FF8:
    li r3, 0x39
    li r4, -0x1
    bl GetTextureByIdAndLang
    lfs f1, lbl_806D8428(r2)
    mr r4, r3
    lfs f0, lbl_806D8424(r2)
    fmr f3, f24
    fsubs f1, f25, f1
    mr r3, r31
    fadds f2, f0, f26
    creqv 6, 6, 6
    bl fn_80168D84
    fn_80158CE4_L_80159028:
    lfs f1, lbl_806D842C(r2)
    li r26, 0x0
    lfs f0, lbl_806D8424(r2)
    lis r30, 0x4330
    fadds f21, f1, f26
    lfs f22, lbl_806D8428(r2)
    fsubs f25, f25, f0
    lfd f23, lbl_806D8448(r2)
    fn_80158CE4_L_80159048:
    lfs f1, 0x8c(r28)
    subfic r3, r26, 0x7
    bl fn_80167744
    xoris r0, r26, 0x8000
    mr r4, r3
    stw r0, 0xc(r1)
    fmr f2, f21
    fmr f3, f24
    mr r3, r31
    stw r30, 0x8(r1)
    addi r4, r4, 0x1ecd
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f23
    fmadds f1, f22, f0, f25
    bl fn_801695E0
    addi r26, r26, 0x1
    cmpwi r26, 0x8
    blt fn_80158CE4_L_80159048
    b fn_80158CE4_L_801590E0
    fn_80158CE4_L_80159098:
    lfs f1, lbl_806D8430(r2)
    fmr f3, f24
    lfs f0, lbl_806D8434(r2)
    mr r3, r31
    fsubs f1, f25, f1
    la r4, lbl_806D8438(r2)  /* lbl_806D8438 */
    fsubs f2, f26, f0
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f1, lbl_806D843C(r2)
    fmr f3, f24
    lfs f0, lbl_806D8428(r2)
    mr r3, r31
    fsubs f1, f25, f1
    la r4, lbl_806D8440(r2)  /* lbl_806D8440 */
    fadds f2, f0, f26
    creqv 6, 6, 6
    bl fn_80168D84
    fn_80158CE4_L_801590E0:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0x4
    blt fn_80158CE4_L_80158E7C
    psq_l f31, 0xd8(r1), 0, 0
    lfd f31, 0xd0(r1)
    psq_l f30, 0xc8(r1), 0, 0
    lfd f30, 0xc0(r1)
    psq_l f29, 0xb8(r1), 0, 0
    lfd f29, 0xb0(r1)
    psq_l f28, 0xa8(r1), 0, 0
    lfd f28, 0xa0(r1)
    psq_l f27, 0x98(r1), 0, 0
    lfd f27, 0x90(r1)
    psq_l f26, 0x88(r1), 0, 0
    lfd f26, 0x80(r1)
    psq_l f25, 0x78(r1), 0, 0
    lfd f25, 0x70(r1)
    psq_l f24, 0x68(r1), 0, 0
    lfd f24, 0x60(r1)
    psq_l f23, 0x58(r1), 0, 0
    lfd f23, 0x50(r1)
    psq_l f22, 0x48(r1), 0, 0
    lfd f22, 0x40(r1)
    psq_l f21, 0x38(r1), 0, 0
    lfd f21, 0x30(r1)
    lmw r26, 0x18(r1)
    lwz r0, 0xe4(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}

extern "C" asm void fn_8015915C(void) { /* 0x8015915C size:0x578 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stfd f30, 0x90(r1)
    psq_st f30, 0x98(r1), 0, 0
    stfd f29, 0x80(r1)
    psq_st f29, 0x88(r1), 0, 0
    stfd f28, 0x70(r1)
    psq_st f28, 0x78(r1), 0, 0
    stfd f27, 0x60(r1)
    psq_st f27, 0x68(r1), 0, 0
    stfd f26, 0x50(r1)
    psq_st f26, 0x58(r1), 0, 0
    stfd f25, 0x40(r1)
    psq_st f25, 0x48(r1), 0, 0
    stfd f24, 0x30(r1)
    psq_st f24, 0x38(r1), 0, 0
    stmw r26, 0x18(r1)
    fmr f29, f1
    lis r5, lbl_803678D8@ha
    fmr f30, f2
    mr r26, r3
    fmr f31, f3
    mr r27, r4
    addi r29, r5, lbl_803678D8@l
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8015915C_L_80159244
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f31
    lfs f1, lbl_806D83CC(r2)
    mr r3, r27
    fadds f24, f0, f30
    addi r4, r29, 0x578
    fadds f1, f1, f29
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f0, lbl_806D83D4(r2)
    fmr f2, f24
    fmr f3, f31
    mr r3, r27
    fadds f1, f0, f29
    la r4, lbl_806D8450(r2)  /* lbl_806D8450 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f31
    lfs f0, lbl_806D83E0(r2)
    mr r3, r27
    fadds f1, f1, f29
    la r4, lbl_806D83E4(r2)  /* lbl_806D83E4 */
    fadds f2, f0, f30
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_8015915C_L_801592B0
    fn_8015915C_L_80159244:
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f31
    lfs f1, lbl_806D83CC(r2)
    mr r3, r27
    fadds f24, f0, f30
    addi r4, r29, 0x58c
    fadds f1, f1, f29
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D83EC(r2)
    fmr f2, f24
    fmr f3, f31
    mr r3, r27
    fadds f1, f0, f29
    la r4, lbl_806D8450(r2)  /* lbl_806D8450 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f31
    lfs f0, lbl_806D83E0(r2)
    mr r3, r27
    fadds f1, f1, f29
    la r4, lbl_806D83F0(r2)  /* lbl_806D83F0 */
    fadds f2, f0, f30
    creqv 6, 6, 6
    bl fn_80168D84
    fn_8015915C_L_801592B0:
    lfs f1, lbl_806D8454(r2)
    li r30, 0x0
    lfs f0, lbl_806D8458(r2)
    lis r28, 0x4330
    fadds f24, f1, f30
    lfs f27, lbl_806D845C(r2)
    fadds f28, f0, f29
    lfd f26, lbl_806D8448(r2)
    fn_8015915C_L_801592D0:
    xoris r3, r30, 0x8000
    addi r0, r30, 0x7c
    stw r3, 0xc(r1)
    fmr f2, f24
    lbzx r0, r26, r0
    fmr f3, f31
    stw r28, 0x8(r1)
    mr r3, r27
    extsb r4, r0
    lfd f0, 0x8(r1)
    addi r4, r4, 0x3f7
    li r5, 0x0
    fsubs f0, f0, f26
    fmadds f1, f27, f0, f28
    bl fn_801695E0
    addi r30, r30, 0x1
    cmpwi r30, 0x3
    blt fn_8015915C_L_801592D0
    lfs f0, lbl_806D83D4(r2)
    li r30, 0x0
    lfs f27, lbl_806D845C(r2)
    lis r28, 0x4330
    fadds f28, f0, f29
    lfd f26, lbl_806D8448(r2)
    fn_8015915C_L_80159330:
    xoris r3, r30, 0x8000
    addi r0, r30, 0x7f
    stw r3, 0xc(r1)
    fmr f2, f24
    lbzx r0, r26, r0
    fmr f3, f31
    stw r28, 0x8(r1)
    mr r3, r27
    extsb r4, r0
    lfd f0, 0x8(r1)
    addi r4, r4, 0x3f7
    li r5, 0x0
    fsubs f0, f0, f26
    fmadds f1, f27, f0, f28
    bl fn_801695E0
    addi r30, r30, 0x1
    cmpwi r30, 0x3
    blt fn_8015915C_L_80159330
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8015915C_L_801593D0
    lfs f0, lbl_806D8464(r2)
    fmr f3, f31
    lfs f1, lbl_806D8460(r2)
    mr r3, r27
    fadds f24, f0, f30
    la r4, lbl_806D8468(r2)  /* lbl_806D8468 */
    fadds f1, f1, f29
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D8470(r2)
    fmr f2, f24
    fmr f3, f31
    mr r3, r27
    fadds f1, f0, f29
    la r4, lbl_806D8474(r2)  /* lbl_806D8474 */
    creqv 6, 6, 6
    bl fn_80168798
    b fn_8015915C_L_80159418
    fn_8015915C_L_801593D0:
    lfs f0, lbl_806D8464(r2)
    fmr f3, f31
    lfs f1, lbl_806D8460(r2)
    mr r3, r27
    fadds f24, f0, f30
    la r4, lbl_806D847C(r2)  /* lbl_806D847C */
    fadds f1, f1, f29
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D8470(r2)
    fmr f2, f24
    fmr f3, f31
    mr r3, r27
    fadds f1, f0, f29
    la r4, lbl_806D8480(r2)  /* lbl_806D8480 */
    creqv 6, 6, 6
    bl fn_80168798
    fn_8015915C_L_80159418:
    lfs f1, lbl_806D83CC(r2)
    lis r3, 0x6666
    lfs f0, lbl_806D8484(r2)
    addi r30, r3, 0x6667
    fadds f25, f1, f29
    lfs f26, lbl_806D83B4(r2)
    fadds f24, f0, f30
    lfd f27, lbl_806D8448(r2)
    lfs f28, lbl_806D8424(r2)
    li r28, 0x0
    lis r31, 0x4330
    fn_8015915C_L_80159444:
    mulhw r6, r30, r28
    lhz r0, 0x78(r26)
    stw r31, 0x8(r1)
    li r4, 0x647
    cmpw r28, r0
    stw r31, 0x10(r1)
    srawi r3, r6, 3
    srwi r5, r3, 31
    srawi r0, r6, 3
    add r3, r3, r5
    mulli r5, r3, 0x14
    srwi r3, r0, 31
    add r6, r0, r3
    subf r5, r5, r28
    xoris r3, r5, 0x8000
    xoris r0, r6, 0x8000
    stw r3, 0xc(r1)
    stw r0, 0x14(r1)
    lfd f1, 0x8(r1)
    lfd f0, 0x10(r1)
    fsubs f1, f1, f27
    fsubs f0, f0, f27
    fmadds f1, f26, f1, f25
    fmadds f2, f28, f0, f24
    bge fn_8015915C_L_801594E4
    lwz r0, 0x84(r26)
    add r3, r5, r6
    li r4, 0x654
    cmpw r3, r0
    bgt fn_8015915C_L_80159554
    subf r0, r3, r0
    lwz r3, 0x88(r26)
    slwi r0, r0, 2
    add r0, r3, r0
    srawi r0, r0, 2
    addze r3, r0
    cmpwi r3, 0x6
    bge fn_8015915C_L_80159554
    addi r4, r3, 0x654
    b fn_8015915C_L_80159554
    fn_8015915C_L_801594E4:
    clrlwi. r0, r6, 31
    beq fn_8015915C_L_801594F0
    li r4, 0x649
    fn_8015915C_L_801594F0:
    li r0, 0x11
    addi r3, r29, 0x4e0
    addi r6, r28, 0x1
    mtctr r0
    fn_8015915C_L_80159500:
    lwz r0, 0x0(r3)
    cmpw r6, r0
    bne fn_8015915C_L_8015954C
    lis r3, 0x6666
    subi r4, r4, 0x1
    addi r5, r3, 0x6667
    mulhw r0, r5, r6
    srawi r0, r0, 2
    srwi r3, r0, 31
    add r0, r0, r3
    mulli r0, r0, 0xa
    subf. r0, r0, r6
    bne fn_8015915C_L_80159554
    mulhw r0, r5, r28
    srawi r0, r0, 2
    srwi r3, r0, 31
    add r3, r0, r3
    addi r4, r3, 0x64a
    b fn_8015915C_L_80159554
    fn_8015915C_L_8015954C:
    addi r3, r3, 0x4
    bdnz fn_8015915C_L_80159500
    fn_8015915C_L_80159554:
    fmr f3, f31
    mr r3, r27
    li r5, 0x0
    bl fn_801695E0
    addi r28, r28, 0x1
    cmpwi r28, 0x64
    blt fn_8015915C_L_80159444
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_8015915C_L_801595E8
    lfs f0, lbl_806D848C(r2)
    fmr f5, f31
    lfs f1, lbl_806D8488(r2)
    mr r3, r27
    fadds f24, f0, f30
    lhz r5, 0x78(r26)
    lhz r0, 0x7a(r26)
    fadds f1, f1, f29
    lfs f3, lbl_806D8390(r2)
    fmr f2, f24
    lfs f4, lbl_806D83B0(r2)
    addi r4, r29, 0x5a0
    add r5, r5, r0
    creqv 6, 6, 6
    bl fn_80168404
    lfs f0, lbl_806D8490(r2)
    fmr f2, f24
    fmr f5, f31
    lfs f3, lbl_806D8390(r2)
    fadds f1, f0, f29
    lfs f4, lbl_806D83B0(r2)
    lhz r5, 0x78(r26)
    mr r3, r27
    addi r4, r29, 0x5b8
    creqv 6, 6, 6
    bl fn_80168404
    b fn_8015915C_L_80159680
    fn_8015915C_L_801595E8:
    lfs f0, lbl_806D848C(r2)
    fmr f3, f31
    lfs f1, lbl_806D8488(r2)
    mr r3, r27
    fadds f24, f0, f30
    addi r4, r29, 0x5cc
    fadds f1, f1, f29
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D8494(r2)
    fmr f2, f24
    fmr f3, f31
    lhz r4, 0x78(r26)
    lhz r0, 0x7a(r26)
    fadds f1, f0, f29
    mr r3, r27
    add r5, r4, r0
    la r4, lbl_806D8498(r2)  /* lbl_806D8498 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D8490(r2)
    fmr f2, f24
    fmr f3, f31
    mr r3, r27
    fadds f1, f0, f29
    addi r4, r29, 0x5dc
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D84A0(r2)
    fmr f2, f24
    fmr f3, f31
    lhz r5, 0x78(r26)
    fadds f1, f0, f29
    mr r3, r27
    la r4, lbl_806D84A4(r2)  /* lbl_806D84A4 */
    creqv 6, 6, 6
    bl fn_80168798
    fn_8015915C_L_80159680:
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    psq_l f30, 0x98(r1), 0, 0
    lfd f30, 0x90(r1)
    psq_l f29, 0x88(r1), 0, 0
    lfd f29, 0x80(r1)
    psq_l f28, 0x78(r1), 0, 0
    lfd f28, 0x70(r1)
    psq_l f27, 0x68(r1), 0, 0
    lfd f27, 0x60(r1)
    psq_l f26, 0x58(r1), 0, 0
    lfd f26, 0x50(r1)
    psq_l f25, 0x48(r1), 0, 0
    lfd f25, 0x40(r1)
    psq_l f24, 0x38(r1), 0, 0
    lfd f24, 0x30(r1)
    lmw r26, 0x18(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" asm void fn_801596D4(void) { /* 0x801596D4 size:0x4FC */
    nofralloc
    stwu r1, -0xe0(r1)
    mflr r0
    stw r0, 0xe4(r1)
    stfd f31, 0xd0(r1)
    psq_st f31, 0xd8(r1), 0, 0
    stfd f30, 0xc0(r1)
    psq_st f30, 0xc8(r1), 0, 0
    stfd f29, 0xb0(r1)
    psq_st f29, 0xb8(r1), 0, 0
    stfd f28, 0xa0(r1)
    psq_st f28, 0xa8(r1), 0, 0
    stfd f27, 0x90(r1)
    psq_st f27, 0x98(r1), 0, 0
    stfd f26, 0x80(r1)
    psq_st f26, 0x88(r1), 0, 0
    stfd f25, 0x70(r1)
    psq_st f25, 0x78(r1), 0, 0
    stfd f24, 0x60(r1)
    psq_st f24, 0x68(r1), 0, 0
    stfd f23, 0x50(r1)
    psq_st f23, 0x58(r1), 0, 0
    stfd f22, 0x40(r1)
    psq_st f22, 0x48(r1), 0, 0
    stmw r20, 0x10(r1)
    fmr f23, f1
    lis r5, lbl_803678D8@ha
    fmr f22, f2
    mr r20, r3
    fmr f26, f3
    mr r21, r4
    addi r30, r5, lbl_803678D8@l
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_801596D4_L_801597CC
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f26
    lfs f1, lbl_806D83CC(r2)
    mr r3, r21
    fadds f24, f0, f22
    addi r4, r30, 0x5e8
    fadds f1, f1, f23
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f0, lbl_806D83D4(r2)
    fmr f2, f24
    fmr f3, f26
    mr r3, r21
    fadds f1, f0, f23
    la r4, lbl_806D84AC(r2)  /* lbl_806D84AC */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f26
    lfs f0, lbl_806D83E0(r2)
    mr r3, r21
    fadds f1, f1, f23
    la r4, lbl_806D83E4(r2)  /* lbl_806D83E4 */
    fadds f2, f0, f22
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_801596D4_L_80159838
    fn_801596D4_L_801597CC:
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f26
    lfs f1, lbl_806D83CC(r2)
    mr r3, r21
    fadds f24, f0, f22
    addi r4, r30, 0x5f8
    fadds f1, f1, f23
    fmr f2, f24
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D83EC(r2)
    fmr f2, f24
    fmr f3, f26
    mr r3, r21
    fadds f1, f0, f23
    la r4, lbl_806D84AC(r2)  /* lbl_806D84AC */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f26
    lfs f0, lbl_806D83E0(r2)
    mr r3, r21
    fadds f1, f1, f23
    la r4, lbl_806D83F0(r2)  /* lbl_806D83F0 */
    fadds f2, f0, f22
    creqv 6, 6, 6
    bl fn_80168D84
    fn_801596D4_L_80159838:
    lfs f1, lbl_806D84B0(r2)
    addi r27, r30, 0x4b8
    lfs f0, lbl_806D84B4(r2)
    addi r26, r30, 0x4cc
    fadds f29, f1, f23
    lfs f30, lbl_806D842C(r2)
    fadds f28, f0, f22
    lfd f31, lbl_806D8448(r2)
    lfs f24, lbl_806D84CC(r2)
    li r24, 0x1
    lfs f25, lbl_806D84D0(r2)
    li r23, 0x0
    lis r31, 0x4330
    fn_801596D4_L_8015986C:
    xoris r0, r23, 0x8000
    addi r25, r23, 0x70
    stw r0, 0xc(r1)
    lbzx r3, r20, r25
    stw r31, 0x8(r1)
    clrlwi r0, r3, 27
    lfd f0, 0x8(r1)
    cmpwi r0, 0x1f
    fsubs f0, f0, f31
    fmadds f27, f30, f0, f28
    bne fn_801596D4_L_801598D8
    fmr f1, f29
    mr r3, r21
    fmr f2, f27
    li r4, 0x665
    fmr f3, f26
    li r5, 0x0
    bl fn_801695E0
    lfs f0, lbl_806D84B8(r2)
    fmr f2, f27
    fmr f3, f26
    mr r3, r21
    fadds f1, f0, f29
    li r4, 0x666
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_8015992C
    fn_801596D4_L_801598D8:
    cmpwi r23, 0x5
    bge fn_801596D4_L_801598F0
    clrlwi r0, r3, 28
    cmpwi r0, 0xf
    beq fn_801596D4_L_801598F0
    li r24, 0x0
    fn_801596D4_L_801598F0:
    fmr f1, f29
    mr r3, r21
    fmr f2, f27
    li r4, 0x667
    fmr f3, f26
    li r5, 0x0
    bl fn_801695E0
    lfs f0, lbl_806D84B8(r2)
    fmr f2, f27
    fmr f3, f26
    mr r3, r21
    fadds f1, f0, f29
    li r4, 0x668
    li r5, 0x0
    bl fn_801695E0
    fn_801596D4_L_8015992C:
    cmpwi r23, 0x5
    bne fn_801596D4_L_80159964
    clrlwi. r0, r24, 24
    bne fn_801596D4_L_80159964
    lfs f1, lbl_806D84BC(r2)
    fmr f3, f26
    lfs f0, lbl_806D84C0(r2)
    mr r3, r21
    fsubs f1, f29, f1
    li r4, 0x66f
    fsubs f2, f27, f0
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_801599BC
    fn_801596D4_L_80159964:
    lfs f1, lbl_806D84BC(r2)
    fmr f3, f26
    lfs f0, lbl_806D84C0(r2)
    mr r3, r21
    fsubs f1, f29, f1
    addi r4, r23, 0x669
    fsubs f2, f27, f0
    li r5, 0x0
    bl fn_801695E0
    lwz r0, 0x6c(r20)
    clrlwi r0, r0, 31
    cmpwi r0, 0x1
    bne fn_801596D4_L_801599BC
    lfs f1, lbl_806D84C4(r2)
    fmr f3, f26
    lfs f0, lbl_806D84C8(r2)
    mr r3, r21
    fsubs f1, f29, f1
    li r4, 0x670
    fadds f2, f0, f27
    li r5, 0x0
    bl fn_801695E0
    fn_801596D4_L_801599BC:
    fadds f23, f24, f27
    addi r29, r30, 0x4b8
    fadds f22, f25, f27
    addi r28, r30, 0x4cc
    li r22, 0x0
    fn_801596D4_L_801599D0:
    cmpwi r23, 0x5
    bne fn_801596D4_L_80159A04
    clrlwi. r0, r24, 24
    bne fn_801596D4_L_80159A04
    lfs f0, 0x0(r29)
    fmr f2, f23
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    addi r4, r22, 0x65a
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_80159A9C
    fn_801596D4_L_80159A04:
    cmpwi r22, 0x1
    blt fn_801596D4_L_80159A24
    subi r0, r22, 0x1
    li r3, 0x1
    lbzx r4, r20, r25
    slw r0, r3, r0
    and. r0, r4, r0
    beq fn_801596D4_L_80159A48
    fn_801596D4_L_80159A24:
    lfs f0, 0x0(r29)
    fmr f2, f23
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    addi r4, r22, 0x65f
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_80159A68
    fn_801596D4_L_80159A48:
    lfs f0, 0x0(r29)
    fmr f2, f23
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    addi r4, r22, 0x65a
    li r5, 0x0
    bl fn_801695E0
    fn_801596D4_L_80159A68:
    li r0, 0x1
    lbzx r3, r20, r25
    slw r0, r0, r22
    and. r0, r3, r0
    beq fn_801596D4_L_80159A9C
    lfs f0, 0x0(r28)
    fmr f2, f22
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    li r4, 0x664
    li r5, 0x0
    bl fn_801695E0
    fn_801596D4_L_80159A9C:
    addi r22, r22, 0x1
    addi r28, r28, 0x4
    cmpwi r22, 0x4
    addi r29, r29, 0x4
    blt fn_801596D4_L_801599D0
    lwz r0, 0x6c(r20)
    cmpwi r0, 0x2
    bge fn_801596D4_L_80159B40
    lbzx r0, r20, r25
    clrlwi r0, r0, 28
    cmpwi r0, 0xf
    bne fn_801596D4_L_80159B1C
    lfs f0, 0x10(r27)
    fmr f2, f23
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    li r4, 0x663
    li r5, 0x0
    bl fn_801695E0
    lbzx r0, r20, r25
    rlwinm. r0, r0, 0, 27, 27
    beq fn_801596D4_L_80159B60
    lfs f0, 0x10(r26)
    fmr f2, f22
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    li r4, 0x664
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_80159B60
    fn_801596D4_L_80159B1C:
    lfs f0, 0x10(r27)
    fmr f2, f23
    fmr f3, f26
    mr r3, r21
    fadds f1, f29, f0
    li r4, 0x65e
    li r5, 0x0
    bl fn_801695E0
    b fn_801596D4_L_80159B60
    fn_801596D4_L_80159B40:
    lfs f0, lbl_806D84D4(r2)
    fmr f2, f27
    fmr f3, f26
    mr r3, r21
    fadds f1, f0, f29
    li r4, 0x680
    li r5, 0x0
    bl fn_801695E0
    fn_801596D4_L_80159B60:
    addi r23, r23, 0x1
    cmpwi r23, 0x6
    blt fn_801596D4_L_8015986C
    psq_l f31, 0xd8(r1), 0, 0
    lfd f31, 0xd0(r1)
    psq_l f30, 0xc8(r1), 0, 0
    lfd f30, 0xc0(r1)
    psq_l f29, 0xb8(r1), 0, 0
    lfd f29, 0xb0(r1)
    psq_l f28, 0xa8(r1), 0, 0
    lfd f28, 0xa0(r1)
    psq_l f27, 0x98(r1), 0, 0
    lfd f27, 0x90(r1)
    psq_l f26, 0x88(r1), 0, 0
    lfd f26, 0x80(r1)
    psq_l f25, 0x78(r1), 0, 0
    lfd f25, 0x70(r1)
    psq_l f24, 0x68(r1), 0, 0
    lfd f24, 0x60(r1)
    psq_l f23, 0x58(r1), 0, 0
    lfd f23, 0x50(r1)
    psq_l f22, 0x48(r1), 0, 0
    lfd f22, 0x40(r1)
    lmw r20, 0x10(r1)
    lwz r0, 0xe4(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}

extern "C" asm void fn_80159BD0(void) { /* 0x80159BD0 size:0xB14 */
    nofralloc
    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stfd f31, 0xe0(r1)
    psq_st f31, 0xe8(r1), 0, 0
    stfd f30, 0xd0(r1)
    psq_st f30, 0xd8(r1), 0, 0
    stfd f29, 0xc0(r1)
    psq_st f29, 0xc8(r1), 0, 0
    stfd f28, 0xb0(r1)
    psq_st f28, 0xb8(r1), 0, 0
    stfd f27, 0xa0(r1)
    psq_st f27, 0xa8(r1), 0, 0
    stfd f26, 0x90(r1)
    psq_st f26, 0x98(r1), 0, 0
    stfd f25, 0x80(r1)
    psq_st f25, 0x88(r1), 0, 0
    stfd f24, 0x70(r1)
    psq_st f24, 0x78(r1), 0, 0
    stfd f23, 0x60(r1)
    psq_st f23, 0x68(r1), 0, 0
    stfd f22, 0x50(r1)
    psq_st f22, 0x58(r1), 0, 0
    stfd f21, 0x40(r1)
    psq_st f21, 0x48(r1), 0, 0
    stmw r23, 0x1c(r1)
    fmr f24, f1
    lis r5, lbl_803678D8@ha
    fmr f25, f2
    mr r30, r3
    fmr f26, f3
    mr r31, r4
    addi r23, r5, lbl_803678D8@l
    bl isJapanese
    cmpwi r3, 0x1
    bne fn_80159BD0_L_80159CD8
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f26
    lfs f1, lbl_806D83CC(r2)
    mr r3, r31
    fadds f27, f0, f25
    lwz r5, 0x60(r30)
    fadds f1, f1, f24
    addi r4, r23, 0x614
    li r6, 0x3c
    fmr f2, f27
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f0, lbl_806D83D4(r2)
    fmr f2, f27
    fmr f3, f26
    mr r3, r31
    fadds f1, f0, f24
    la r4, lbl_806D84D8(r2)  /* lbl_806D84D8 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D83DC(r2)
    fmr f3, f26
    lfs f0, lbl_806D83E0(r2)
    mr r3, r31
    fadds f1, f1, f24
    la r4, lbl_806D83E4(r2)  /* lbl_806D83E4 */
    fadds f2, f0, f25
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_80159BD0_L_80159D78
    fn_80159BD0_L_80159CD8:
    lfs f0, lbl_806D83D0(r2)
    fmr f3, f26
    lfs f1, lbl_806D83CC(r2)
    mr r3, r31
    fadds f27, f0, f25
    lwz r5, 0x60(r30)
    fadds f1, f1, f24
    addi r4, r23, 0x638
    fmr f2, f27
    creqv 6, 6, 6
    bl fn_80168798
    lfs f1, lbl_806D84DC(r2)
    fmr f3, f26
    lfs f0, lbl_806D83E0(r2)
    mr r3, r31
    fadds f2, f1, f24
    lfs f1, lbl_806D84E0(r2)
    fadds f28, f0, f25
    addi r4, r23, 0x64c
    li r5, 0x3c
    fsubs f1, f2, f1
    fmr f2, f28
    creqv 6, 6, 6
    bl fn_80168D84
    lfs f0, lbl_806D83EC(r2)
    fmr f2, f27
    fmr f3, f26
    mr r3, r31
    fadds f1, f0, f24
    la r4, lbl_806D84D8(r2)  /* lbl_806D84D8 */
    creqv 6, 6, 6
    bl fn_80168798
    lfs f0, lbl_806D83DC(r2)
    fmr f2, f28
    fmr f3, f26
    mr r3, r31
    fadds f1, f0, f24
    la r4, lbl_806D83F0(r2)  /* lbl_806D83F0 */
    creqv 6, 6, 6
    bl fn_80168D84
    fn_80159BD0_L_80159D78:
    lis r3, 0x2aab
    lwz r0, 0x64(r30)
    subi r3, r3, 0x5555
    lfs f29, lbl_806D84F0(r2)
    mulhw r0, r3, r0
    lfd f28, lbl_806D8448(r2)
    lfs f27, lbl_806D84EC(r2)
    li r24, 0x0
    lfs f31, lbl_806D84E8(r2)
    li r26, 0x0
    srawi r0, r0, 1
    lfs f30, lbl_806D84E4(r2)
    srwi r3, r0, 31
    lis r28, 0x4330
    add r23, r0, r3
    fn_80159BD0_L_80159DB4:
    xoris r0, r24, 0x8000
    stw r28, 0x8(r1)
    mr r27, r26
    li r25, 0x0
    stw r0, 0xc(r1)
    lfd f0, 0x8(r1)
    fsubs f0, f0, f28
    fmadds f0, f31, f0, f30
    fadds f23, f25, f0
    fn_80159BD0_L_80159DD8:
    xoris r0, r25, 0x8000
    stw r28, 0x8(r1)
    fmr f2, f23
    mr r3, r31
    stw r0, 0xc(r1)
    fmr f3, f26
    li r4, 0x7cf
    li r5, 0x0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f28
    fmadds f0, f29, f0, f27
    fadds f22, f24, f0
    fmr f1, f22
    bl fn_801695E0
    mr r3, r27
    bl PlayerData_GetUnlockedItemIdByIndex_U8
    clrlwi r3, r3, 24
    li r0, 0x9f
    srawi r5, r3, 31
    cmpw r24, r23
    srwi r4, r0, 31
    subfc r0, r0, r3
    adde r0, r5, r4
    clrlwi r29, r0, 24
    bne fn_80159BD0_L_80159EF4
    lwz r0, 0x64(r30)
    cmpw r0, r27
    beq fn_80159BD0_L_80159FC0
    lwz r4, 0x20(r30)
    addi r0, r27, 0xa8
    lbzx r0, r4, r0
    cmplwi r0, 0x0
    beq fn_80159BD0_L_80159EC0
    li r4, 0x0
    bl Item_GetDescriptorField0
    lfs f3, lbl_806D84F4(r2)
    mr r4, r3
    fmr f1, f22
    mr r3, r31
    fmr f2, f23
    li r5, 0x0
    fmr f4, f3
    fmr f5, f26
    bl fn_80169334
    cmplwi r29, 0x0
    beq fn_80159BD0_L_80159FC0
    lfs f1, lbl_806D83B8(r2)
    fmr f5, f26
    lfs f0, lbl_806D84F8(r2)
    mr r3, r31
    lfs f3, lbl_806D84F4(r2)
    fadds f1, f1, f22
    fsubs f2, f23, f0
    fmr f4, f3
    li r4, 0x7c5
    li r5, 0x0
    bl fn_80169334
    b fn_80159BD0_L_80159FC0
    fn_80159BD0_L_80159EC0:
    li r3, 0x0
    li r4, 0x0
    bl Item_GetDescriptorField0
    lfs f3, lbl_806D84F4(r2)
    mr r4, r3
    fmr f1, f22
    mr r3, r31
    fmr f2, f23
    li r5, 0x0
    fmr f4, f3
    fmr f5, f26
    bl fn_80169334
    b fn_80159BD0_L_80159FC0
    fn_80159BD0_L_80159EF4:
    lwz r4, 0x20(r30)
    addi r0, r27, 0xa8
    lbzx r0, r4, r0
    cmplwi r0, 0x0
    beq fn_80159BD0_L_80159F84
    li r4, 0x0
    bl Item_GetDescriptorField0
    lfs f5, lbl_806D8414(r2)
    mr r4, r3
    lfs f3, lbl_806D84F4(r2)
    fmr f1, f22
    fmr f2, f23
    mr r3, r31
    fmr f4, f3
    li r5, 0x0
    fmr f6, f5
    fmr f7, f5
    fmr f8, f26
    bl fn_8016918C
    cmplwi r29, 0x0
    beq fn_80159BD0_L_80159FC0
    lfs f5, lbl_806D8414(r2)
    fmr f8, f26
    lfs f1, lbl_806D83B8(r2)
    mr r3, r31
    lfs f0, lbl_806D84F8(r2)
    fmr f6, f5
    lfs f3, lbl_806D84F4(r2)
    fmr f7, f5
    li r4, 0x7c5
    fmr f4, f3
    li r5, 0x0
    fadds f1, f1, f22
    fsubs f2, f23, f0
    bl fn_8016918C
    b fn_80159BD0_L_80159FC0
    fn_80159BD0_L_80159F84:
    li r3, 0x0
    li r4, 0x0
    bl Item_GetDescriptorField0
    lfs f5, lbl_806D8414(r2)
    mr r4, r3
    lfs f3, lbl_806D84F4(r2)
    fmr f1, f22
    fmr f2, f23
    mr r3, r31
    fmr f4, f3
    li r5, 0x0
    fmr f6, f5
    fmr f7, f5
    fmr f8, f26
    bl fn_8016918C
    fn_80159BD0_L_80159FC0:
    addi r25, r25, 0x1
    addi r27, r27, 0x1
    cmpwi r25, 0xc
    blt fn_80159BD0_L_80159DD8
    addi r24, r24, 0x1
    addi r26, r26, 0xc
    cmpwi r24, 0x5
    blt fn_80159BD0_L_80159DB4
    li r27, 0x0
    lfs f29, lbl_806D84E8(r2)
    lfd f28, lbl_806D8448(r2)
    mr r26, r27
    lfs f27, lbl_806D84E4(r2)
    lis r24, 0x4330
    fn_80159BD0_L_80159FF8:
    xoris r0, r27, 0x8000
    stw r24, 0x8(r1)
    mr r25, r26
    li r28, 0x0
    stw r0, 0xc(r1)
    lfd f0, 0x8(r1)
    fsubs f0, f0, f28
    fmadds f30, f29, f0, f27
    fn_80159BD0_L_8015A018:
    lwz r0, 0x64(r30)
    cmpw r0, r25
    beq fn_80159BD0_L_8015A0E4
    lwz r3, 0x20(r30)
    addi r0, r25, 0xa8
    lbzx r0, r3, r0
    cmplwi r0, 0x0
    beq fn_80159BD0_L_8015A0E4
    mr r3, r25
    bl PlayerData_GetUnlockedItemIdByIndex_U8
    lwz r0, 0x68(r30)
    clrlwi r3, r3, 24
    cmpw r0, r3
    bne fn_80159BD0_L_8015A0E4
    xoris r3, r28, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    cmpw r27, r23
    lfd f2, lbl_806D8448(r2)
    stw r0, 0x8(r1)
    lfs f3, lbl_806D84F0(r2)
    lfd f1, 0x8(r1)
    lfs f0, lbl_806D84EC(r2)
    fsubs f1, f1, f2
    fmadds f0, f3, f1, f0
    bne fn_80159BD0_L_8015A0B4
    lfs f5, lbl_806D83B0(r2)
    fmr f8, f26
    lfs f3, lbl_806D84F4(r2)
    fadds f1, f24, f0
    fmr f6, f5
    mr r3, r31
    fmr f4, f3
    fmr f7, f5
    li r4, 0x7d3
    fadds f2, f25, f30
    li r5, 0x0
    bl fn_8016918C
    b fn_80159BD0_L_8015A0E4
    fn_80159BD0_L_8015A0B4:
    lfs f5, lbl_806D8414(r2)
    fmr f8, f26
    lfs f3, lbl_806D84F4(r2)
    fadds f1, f24, f0
    fmr f6, f5
    mr r3, r31
    fmr f4, f3
    fmr f7, f5
    li r4, 0x7d3
    fadds f2, f25, f30
    li r5, 0x0
    bl fn_8016918C
    fn_80159BD0_L_8015A0E4:
    addi r28, r28, 0x1
    addi r25, r25, 0x1
    cmpwi r28, 0xc
    blt fn_80159BD0_L_8015A018
    addi r27, r27, 0x1
    addi r26, r26, 0xc
    cmpwi r27, 0x5
    blt fn_80159BD0_L_80159FF8
    lfs f1, lbl_806D84FC(r2)
    fmr f3, f26
    lfs f0, lbl_806D8490(r2)
    mr r3, r31
    fadds f30, f1, f24
    li r4, 0x641
    fadds f31, f0, f25
    li r5, 0x0
    fmr f1, f30
    fmr f2, f31
    bl fn_801695E0
    lwz r3, 0x64(r30)
    cmpwi r3, 0x0
    blt fn_80159BD0_L_8015A678
    bl PlayerData_GetUnlockedItemIdByIndex_U8
    lis r4, 0x2aab
    lwz r7, 0x64(r30)
    subi r0, r4, 0x5555
    clrlwi r23, r3, 24
    mulhw r5, r0, r7
    lis r0, 0x4330
    li r3, 0x9f
    stw r0, 0x8(r1)
    srawi r6, r23, 31
    lfd f5, lbl_806D8448(r2)
    srwi r4, r3, 31
    subfc r3, r3, r23
    adde r6, r6, r4
    stw r0, 0x10(r1)
    srawi r3, r5, 1
    lfs f6, lbl_806D84F0(r2)
    srwi r4, r3, 31
    srawi r0, r5, 1
    add r3, r3, r4
    lfs f3, lbl_806D84EC(r2)
    mulli r5, r3, 0xc
    srwi r4, r0, 31
    lfs f2, lbl_806D84E8(r2)
    mr r3, r23
    add r0, r0, r4
    lfs f0, lbl_806D84E4(r2)
    subf r4, r5, r7
    xoris r0, r0, 0x8000
    xoris r4, r4, 0x8000
    stw r0, 0x14(r1)
    clrlwi r29, r6, 24
    stw r4, 0xc(r1)
    lfd f1, 0x10(r1)
    lfd f4, 0x8(r1)
    fsubs f1, f1, f5
    fsubs f4, f4, f5
    fmadds f28, f2, f1, f0
    fmadds f29, f6, f4, f3
    bl Item_GetDescriptorFieldC
    mr r24, r3
    mr r3, r23
    bl Item_GetDescriptorField8
    cmpwi r24, 0x0
    li r0, -0x1
    blt fn_80159BD0_L_8015A1F8
    addi r0, r24, 0x4f3
    fn_80159BD0_L_8015A1F8:
    mr r25, r0
    bl fn_8013BEC8
    cmpwi r31, 0x0
    lwz r4, 0x40(r30)
    mr r24, r3
    blt fn_80159BD0_L_8015A21C
    cmpwi r31, 0x8
    bge fn_80159BD0_L_8015A21C
    stw r31, 0x0(r4)
    fn_80159BD0_L_8015A21C:
    lfs f1, lbl_806D8500(r2)
    lfs f0, lbl_806D8504(r2)
    fadds f1, f1, f24
    lwz r3, 0x40(r30)
    fadds f0, f0, f25
    stfs f1, 0x8(r3)
    stfs f0, 0xc(r3)
    lwz r3, 0x40(r30)
    stfs f26, 0x10(r3)
    lwz r3, 0x40(r30)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f4, 0x5c(r30)
    lfs f3, lbl_806D8428(r2)
    fcmpo cr0, f4, f3
    bge fn_80159BD0_L_8015A28C
    lfs f1, lbl_806D8508(r2)
    lfs f0, lbl_806D850C(r2)
    fmuls f1, f1, f4
    lfs f2, lbl_806D84F4(r2)
    fmuls f0, f0, f4
    fdivs f1, f1, f3
    fdivs f0, f0, f3
    fadds f27, f2, f1
    fadds f21, f2, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A28C:
    lfs f0, lbl_806D8408(r2)
    fcmpo cr0, f4, f0
    bge fn_80159BD0_L_8015A2C4
    fsubs f5, f4, f3
    lfs f1, lbl_806D8514(r2)
    lfs f0, lbl_806D8520(r2)
    lfs f3, lbl_806D8518(r2)
    fmuls f4, f1, f5
    lfs f2, lbl_806D8510(r2)
    fmuls f1, f0, f5
    lfs f0, lbl_806D851C(r2)
    fmadds f27, f4, f3, f2
    fnmsubs f21, f1, f3, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A2C4:
    lfs f1, lbl_806D843C(r2)
    fcmpo cr0, f4, f1
    bge fn_80159BD0_L_8015A2FC
    fsubs f5, f4, f0
    lfs f1, lbl_806D8514(r2)
    lfs f0, lbl_806D8520(r2)
    lfs f3, lbl_806D8518(r2)
    fmuls f4, f1, f5
    lfs f2, lbl_806D8524(r2)
    fmuls f1, f0, f5
    lfs f0, lbl_806D8510(r2)
    fnmsubs f27, f4, f3, f2
    fmadds f21, f1, f3, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A2FC:
    lfs f0, lbl_806D8528(r2)
    fcmpo cr0, f4, f0
    bge fn_80159BD0_L_8015A33C
    fsubs f5, f4, f1
    lfs f1, lbl_806D8508(r2)
    lfs f0, lbl_806D852C(r2)
    lfs f3, lbl_806D8430(r2)
    fmuls f2, f1, f5
    lfs f4, lbl_806D8510(r2)
    fmuls f0, f0, f5
    lfs f1, lbl_806D851C(r2)
    fdivs f2, f2, f3
    fdivs f0, f0, f3
    fsubs f27, f4, f2
    fsubs f21, f1, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A33C:
    lfs f1, lbl_806D83B4(r2)
    fcmpo cr0, f4, f1
    bge fn_80159BD0_L_8015A37C
    fsubs f5, f4, f0
    lfs f1, lbl_806D8530(r2)
    lfs f0, lbl_806D852C(r2)
    lfs f3, lbl_806D8430(r2)
    fmuls f2, f1, f5
    lfs f4, lbl_806D84F4(r2)
    fmuls f0, f0, f5
    lfs f1, lbl_806D8534(r2)
    fdivs f2, f2, f3
    fdivs f0, f0, f3
    fsubs f27, f4, f2
    fsubs f21, f1, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A37C:
    lfs f0, lbl_806D8538(r2)
    fcmpo cr0, f4, f0
    bge fn_80159BD0_L_8015A3BC
    fsubs f5, f4, f1
    lfs f1, lbl_806D8540(r2)
    lfs f0, lbl_806D8548(r2)
    lfs f3, lbl_806D8544(r2)
    fmuls f2, f1, f5
    lfs f4, lbl_806D853C(r2)
    fmuls f0, f0, f5
    lfs f1, lbl_806D8524(r2)
    fdivs f2, f2, f3
    fdivs f0, f0, f3
    fadds f27, f4, f2
    fsubs f21, f1, f0
    b fn_80159BD0_L_8015A3EC
    fn_80159BD0_L_8015A3BC:
    fsubs f5, f4, f0
    lfs f1, lbl_806D8514(r2)
    lfs f0, lbl_806D8558(r2)
    lfs f3, lbl_806D8550(r2)
    fmuls f2, f1, f5
    lfs f4, lbl_806D854C(r2)
    fmuls f0, f0, f5
    lfs f1, lbl_806D8554(r2)
    fdivs f2, f2, f3
    fdivs f0, f0, f3
    fadds f27, f4, f2
    fadds f21, f1, f0
    fn_80159BD0_L_8015A3EC:
    fadds f23, f24, f29
    mr r3, r31
    fadds f22, f25, f28
    li r4, 0x7cf
    fmr f3, f27
    li r5, 0x0
    fmr f1, f23
    fmr f2, f22
    fmr f4, f21
    fmr f5, f26
    bl fn_80169334
    lwz r3, 0x20(r30)
    lwz r0, 0x64(r30)
    add r3, r3, r0
    lbz r0, 0xa8(r3)
    cmplwi r0, 0x0
    beq fn_80159BD0_L_8015A648
    mr r3, r23
    li r4, 0x0
    bl Item_GetDescriptorField0
    fmr f1, f23
    mr r4, r3
    fmr f2, f22
    mr r3, r31
    fmr f3, f27
    li r5, 0x0
    fmr f4, f21
    fmr f5, f26
    bl fn_80169334
    cmplwi r29, 0x0
    beq fn_80159BD0_L_8015A494
    lfs f1, lbl_806D855C(r2)
    fmr f3, f27
    lfs f0, lbl_806D8408(r2)
    fmr f4, f21
    fmr f5, f26
    mr r3, r31
    fmadds f1, f1, f27, f23
    fnmsubs f2, f0, f21, f22
    li r4, 0x7c5
    li r5, 0x0
    bl fn_80169334
    fn_80159BD0_L_8015A494:
    lwz r0, 0x68(r30)
    cmpw r0, r23
    bne fn_80159BD0_L_8015A4C4
    fmr f1, f23
    mr r3, r31
    fmr f2, f22
    li r4, 0x7d3
    fmr f3, f27
    li r5, 0x0
    fmr f4, f21
    fmr f5, f26
    bl fn_80169334
    fn_80159BD0_L_8015A4C4:
    lfs f1, lbl_806D8560(r2)
    fmr f3, f26
    lfs f0, lbl_806D83B0(r2)
    mr r3, r31
    fsubs f1, f30, f1
    mr r4, r25
    fadds f2, f0, f31
    li r5, 0x0
    bl fn_801695E0
    mr r3, r23
    li r4, 0x0
    bl Item_GetDescriptorField0
    lfs f1, lbl_806D8564(r2)
    mr r4, r3
    lfs f0, lbl_806D8434(r2)
    fmr f3, f26
    fsubs f1, f30, f1
    mr r3, r31
    fadds f2, f0, f31
    li r5, 0x0
    bl fn_801695E0
    cmplwi r29, 0x0
    beq fn_80159BD0_L_8015A544
    lfs f1, lbl_806D855C(r2)
    fmr f3, f26
    lfs f0, lbl_806D8430(r2)
    mr r3, r31
    fsubs f1, f30, f1
    li r4, 0x7c5
    fsubs f2, f31, f0
    li r5, 0x0
    bl fn_801695E0
    fn_80159BD0_L_8015A544:
    cmplwi r24, 0x0
    beq fn_80159BD0_L_8015A58C
    mr r3, r23
    bl fn_8023DAA8
    lfs f1, lbl_806D8568(r2)
    mr r4, r3
    lfs f2, lbl_806D856C(r2)
    mr r3, r31
    lfs f0, 0xc(r24)
    fsubs f1, f30, f1
    fsubs f2, f31, f2
    lfs f3, 0x0(r24)
    fmuls f6, f0, f26
    lfs f4, 0x4(r24)
    lfs f5, 0x8(r24)
    creqv 6, 6, 6
    bl fn_80168B90
    b fn_80159BD0_L_8015A5B8
    fn_80159BD0_L_8015A58C:
    mr r3, r23
    bl fn_8023DAA8
    lfs f1, lbl_806D8568(r2)
    mr r4, r3
    lfs f0, lbl_806D856C(r2)
    fmr f3, f26
    fsubs f1, f30, f1
    mr r3, r31
    fsubs f2, f31, f0
    creqv 6, 6, 6
    bl fn_80168D84
    fn_80159BD0_L_8015A5B8:
    mr r3, r23
    li r4, 0x0
    bl fn_8023D938
    lfs f1, lbl_806D8544(r2)
    mr r4, r3
    lfs f0, lbl_806D839C(r2)
    fmr f3, f26
    fadds f22, f1, f30
    mr r3, r31
    fsubs f2, f31, f0
    fmr f1, f22
    creqv 6, 6, 6
    bl fn_80168D84
    mr r3, r23
    li r4, 0x1
    bl fn_8023D938
    lfs f0, lbl_806D8550(r2)
    mr r4, r3
    fmr f1, f22
    mr r3, r31
    fmr f3, f26
    fsubs f2, f31, f0
    creqv 6, 6, 6
    bl fn_80168D84
    mr r3, r23
    li r4, 0x2
    bl fn_8023D938
    lfs f0, lbl_806D8570(r2)
    mr r4, r3
    fmr f1, f22
    mr r3, r31
    fmr f3, f26
    fadds f2, f0, f31
    creqv 6, 6, 6
    bl fn_80168D84
    b fn_80159BD0_L_8015A678
    fn_80159BD0_L_8015A648:
    li r3, 0x0
    li r4, 0x0
    bl Item_GetDescriptorField0
    fmr f1, f23
    mr r4, r3
    fmr f2, f22
    mr r3, r31
    fmr f3, f27
    li r5, 0x0
    fmr f4, f21
    fmr f5, f26
    bl fn_80169334
    fn_80159BD0_L_8015A678:
    psq_l f31, 0xe8(r1), 0, 0
    lfd f31, 0xe0(r1)
    psq_l f30, 0xd8(r1), 0, 0
    lfd f30, 0xd0(r1)
    psq_l f29, 0xc8(r1), 0, 0
    lfd f29, 0xc0(r1)
    psq_l f28, 0xb8(r1), 0, 0
    lfd f28, 0xb0(r1)
    psq_l f27, 0xa8(r1), 0, 0
    lfd f27, 0xa0(r1)
    psq_l f26, 0x98(r1), 0, 0
    lfd f26, 0x90(r1)
    psq_l f25, 0x88(r1), 0, 0
    lfd f25, 0x80(r1)
    psq_l f24, 0x78(r1), 0, 0
    lfd f24, 0x70(r1)
    psq_l f23, 0x68(r1), 0, 0
    lfd f23, 0x60(r1)
    psq_l f22, 0x58(r1), 0, 0
    lfd f22, 0x50(r1)
    psq_l f21, 0x48(r1), 0, 0
    lfd f21, 0x40(r1)
    lmw r23, 0x1c(r1)
    lwz r0, 0xf4(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr
}

