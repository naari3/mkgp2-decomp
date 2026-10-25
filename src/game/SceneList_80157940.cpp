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
__declspec(section ".extab_user") static const unsigned char extab_fn_80157940[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_80157A68[8] = {
    0x28, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80157B38[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const unsigned char extab_fn_80157C60[8] = {
    0x28, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80157D30[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157940 = {
    (void *)&fn_80157940, 0x000000B0, (void *)extab_fn_80157940
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157A68 = {
    (void *)&fn_80157A68, 0x000000B8, (void *)extab_fn_80157A68
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157B38 = {
    (void *)&fn_80157B38, 0x000000B0, (void *)extab_fn_80157B38
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157C60 = {
    (void *)&fn_80157C60, 0x000000B8, (void *)extab_fn_80157C60
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80157D30 = {
    (void *)&fn_80157D30, 0x000000B0, (void *)extab_fn_80157D30
};




}

static inline InputView *input_state(void)
{
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}



extern "C" asm void fn_80157940(void) { /* 0x80157940 size:0xB0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    lwz r5, 0x0(r5)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    lwz r3, 0x0(r6)
    cmplw r5, r3
    bne fn_80157940_L_80157984
    stw r3, 0x0(r28)
    b fn_80157940_L_801579D0
    fn_80157940_L_80157984:
    lwz r4, 0x0(r3)
    lwz r3, 0x0(r5)
    lwz r0, 0x4(r4)
    stw r0, 0x4(r3)
    lwz r0, 0x0(r5)
    lwz r3, 0x4(r4)
    stw r0, 0x0(r3)
    b fn_80157940_L_801579BC
    fn_80157940_L_801579A4:
    lwz r0, 0x4(r3)
    stw r0, 0x0(r30)
    bl MemoryManager_TimedFree
    lwz r3, 0x0(r29)
    subi r0, r3, 0x1
    stw r0, 0x0(r29)
    fn_80157940_L_801579BC:
    lwz r3, 0x0(r30)
    lwz r0, 0x0(r31)
    cmplw r3, r0
    bne fn_80157940_L_801579A4
    stw r0, 0x0(r28)
    fn_80157940_L_801579D0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_801579F0(ListIter *ret, List *l, ListIter *it)
{
    ListNode *p = it->n;
    ListNode *next = p->next;
    ListNode *prev = p->prev;
    it->n = next;
    prev->next = next;
    p->next->prev = p->prev;
    MemoryManager_TimedFree(p);
    ListNode *r = it->n;
    int s = l->size;
    l->size = --s;
    ret->n = r;
}

extern "C" asm void fn_80157A68(void) { /* 0x80157A68 size:0xB8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr r29, r3
    mr r31, r1
    mr r30, r4
    mr r27, r5
    mr r28, r6
    li r3, 0x14
    bl Alloc
    addi r0, r30, 0x4
    addic. r4, r3, 0x8
    stw r0, 0x8(r31)
    stw r3, 0xc(r31)
    beq fn_80157A68_L_80157AC4
    lwz r0, 0x0(r28)
    lwz r3, 0x4(r28)
    stw r0, 0x0(r4)
    lwz r0, 0x8(r28)
    stw r3, 0x4(r4)
    stw r1, 0x24(r31)
    stw r0, 0x8(r4)
    fn_80157A68_L_80157AC4:
    lwz r5, 0x0(r27)
    li r3, 0x0
    lwz r6, 0xc(r31)
    lwz r4, 0x0(r5)
    stw r3, 0xc(r31)
    stw r6, 0x4(r4)
    lwz r0, 0x0(r5)
    stw r0, 0x0(r6)
    stw r6, 0x0(r5)
    stw r5, 0x4(r6)
    lwz r4, 0x0(r30)
    addi r0, r4, 0x1
    stw r0, 0x0(r30)
    stw r6, 0x0(r29)
    b fn_80157A68_L_80157B04
    bl MemoryManager_TimedFree
    fn_80157A68_L_80157B04:
    mr r10, r31
    lmw r27, 0x2c(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

extern "C" void fn_80157B20(List *l)
{
    ListNode *h = &l->head;
    l->size = 0;
    h->next = h;
    h->prev = h;
}

extern "C" asm void fn_80157B38(void) { /* 0x80157B38 size:0xB0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    lwz r5, 0x0(r5)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    lwz r3, 0x0(r6)
    cmplw r5, r3
    bne fn_80157B38_L_80157B7C
    stw r3, 0x0(r28)
    b fn_80157B38_L_80157BC8
    fn_80157B38_L_80157B7C:
    lwz r4, 0x0(r3)
    lwz r3, 0x0(r5)
    lwz r0, 0x4(r4)
    stw r0, 0x4(r3)
    lwz r0, 0x0(r5)
    lwz r3, 0x4(r4)
    stw r0, 0x0(r3)
    b fn_80157B38_L_80157BB4
    fn_80157B38_L_80157B9C:
    lwz r0, 0x4(r3)
    stw r0, 0x0(r30)
    bl MemoryManager_TimedFree
    lwz r3, 0x0(r29)
    subi r0, r3, 0x1
    stw r0, 0x0(r29)
    fn_80157B38_L_80157BB4:
    lwz r3, 0x0(r30)
    lwz r0, 0x0(r31)
    cmplw r3, r0
    bne fn_80157B38_L_80157B9C
    stw r0, 0x0(r28)
    fn_80157B38_L_80157BC8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_80157BE8(ListIter *ret, List *l, ListIter *it)
{
    ListNode *p = it->n;
    ListNode *next = p->next;
    ListNode *prev = p->prev;
    it->n = next;
    prev->next = next;
    p->next->prev = p->prev;
    MemoryManager_TimedFree(p);
    ListNode *r = it->n;
    int s = l->size;
    l->size = --s;
    ret->n = r;
}

extern "C" asm void fn_80157C60(void) { /* 0x80157C60 size:0xB8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr r29, r3
    mr r31, r1
    mr r30, r4
    mr r27, r5
    mr r28, r6
    li r3, 0x14
    bl Alloc
    addi r0, r30, 0x4
    addic. r4, r3, 0x8
    stw r0, 0x8(r31)
    stw r3, 0xc(r31)
    beq fn_80157C60_L_80157CBC
    lwz r0, 0x0(r28)
    lwz r3, 0x4(r28)
    stw r0, 0x0(r4)
    lwz r0, 0x8(r28)
    stw r3, 0x4(r4)
    stw r1, 0x24(r31)
    stw r0, 0x8(r4)
    fn_80157C60_L_80157CBC:
    lwz r5, 0x0(r27)
    li r3, 0x0
    lwz r6, 0xc(r31)
    lwz r4, 0x0(r5)
    stw r3, 0xc(r31)
    stw r6, 0x4(r4)
    lwz r0, 0x0(r5)
    stw r0, 0x0(r6)
    stw r6, 0x0(r5)
    stw r5, 0x4(r6)
    lwz r4, 0x0(r30)
    addi r0, r4, 0x1
    stw r0, 0x0(r30)
    stw r6, 0x0(r29)
    b fn_80157C60_L_80157CFC
    bl MemoryManager_TimedFree
    fn_80157C60_L_80157CFC:
    mr r10, r31
    lmw r27, 0x2c(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

extern "C" void fn_80157D18(List *l)
{
    ListNode *h = &l->head;
    l->size = 0;
    h->next = h;
    h->prev = h;
}

extern "C" asm void fn_80157D30(void) { /* 0x80157D30 size:0xB0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    lwz r5, 0x0(r5)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    lwz r3, 0x0(r6)
    cmplw r5, r3
    bne fn_80157D30_L_80157D74
    stw r3, 0x0(r28)
    b fn_80157D30_L_80157DC0
    fn_80157D30_L_80157D74:
    lwz r4, 0x0(r3)
    lwz r3, 0x0(r5)
    lwz r0, 0x4(r4)
    stw r0, 0x4(r3)
    lwz r0, 0x0(r5)
    lwz r3, 0x4(r4)
    stw r0, 0x0(r3)
    b fn_80157D30_L_80157DAC
    fn_80157D30_L_80157D94:
    lwz r0, 0x4(r3)
    stw r0, 0x0(r30)
    bl MemoryManager_TimedFree
    lwz r3, 0x0(r29)
    subi r0, r3, 0x1
    stw r0, 0x0(r29)
    fn_80157D30_L_80157DAC:
    lwz r3, 0x0(r30)
    lwz r0, 0x0(r31)
    cmplw r3, r0
    bne fn_80157D30_L_80157D94
    stw r0, 0x0(r28)
    fn_80157D30_L_80157DC0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
