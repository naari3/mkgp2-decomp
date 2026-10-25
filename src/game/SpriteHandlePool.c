/*
 * 0x8011DF98..0x8011EB1C: sprite handle pool. Releasing a handle runs its
 * draw-release callback, frees the pool slot and walks the chain of linked
 * handles (the self-recursion is inlined four levels deep). fn_8011E9C0
 * releases every live handle of one type under the frame profiler.
 */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern const float lbl_806D6D98;
extern const float lbl_806D6D9C;
extern float lbl_80657208[];
}

typedef struct SpriteHandle {
    signed char active;
    char pad1[3];
    int type;
    int next;
    unsigned char keep;
    unsigned char released;
    char padE[0xD8 - 0xE];
    unsigned char hasCallback;
    unsigned char callbackOn;
    char padDA[2];
    void (*callback)(void *arg);
    void *callbackArg;
} SpriteHandle;


extern "C" {
extern SpriteHandle g_SpriteHandlePool[];
extern int lbl_80677C38[];
}

typedef struct SpriteNode {
    int index;
    int pad;
    struct SpriteNode *next;
} SpriteNode;

typedef struct SpriteList {
    char pad[0x14];
    SpriteNode *head;
} SpriteList;

extern "C" SpriteList *lbl_806D1500;

class ScopedTimer {
public:
    inline ScopedTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D98);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

class ScopedAccum {
public:
    inline ScopedAccum(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedAccum() {
        lbl_80657208[m_slot] +=
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D9C;
    }

private:
    volatile int m_slot;
    unsigned int m_startTick;
};

extern "C" {
extern void GXBegin();
extern void GXClearVtxDesc();
extern void GXLoadTexObj();
extern void GXLoadTlut();
extern void GXSetAlphaCompare();
extern void GXSetBlendMode();
extern void GXSetChanCtrl();
extern void GXSetCullMode();
extern void GXSetNumChans();
extern void GXSetNumTevStages();
extern void GXSetNumTexGens();
extern void GXSetProjectionv();
extern void GXSetScissor();
extern void GXSetTevAlphaIn();
extern void GXSetTevAlphaOp();
extern void GXSetTevColorIn();
extern void GXSetTevColorOp();
extern void GXSetTevOp();
extern void GXSetTevOrder();
extern void GXSetTexCoordGen2();
extern void GXSetViewport();
extern void GXSetVtxAttrFmt();
extern void GXSetVtxDesc();
extern void GXSetZCompLoc();
extern void GXSetZMode();
extern void fn_8011EC18();
extern void fn_802C14B8();
extern unsigned int lbl_806D14F0;
extern unsigned int lbl_806D14F1;
extern unsigned int lbl_806D14F4;
extern unsigned int lbl_806D14F8;
extern unsigned int lbl_806D14FC;
extern unsigned int lbl_803325D0[];
extern unsigned int lbl_806573A0[];
asm void fn_8011E31C(struct SpriteHandle *);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8011E31C[8] = {
    0x38, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8011E31C = {
    (void *)&fn_8011E31C, 0x000006A4, (void *)extab_fn_8011E31C
};

}


extern "C" void fn_8011DF98(SpriteHandle *h) {
    if (h && h->active && !h->released) {
        if (h->hasCallback == 1 && h->callbackOn == 1) {
            if (h->callback) {
                h->callback(h->callbackArg);
            } else {
                fn_8011E31C(h);
            }
        }
        h->released = 1;
        if (!h->keep) {
            h->active = 0;
            lbl_80677C38[h->type]--;
        }
        if (h->next != -1) {
            fn_8011DF98(&g_SpriteHandlePool[h->next]);
        }
    }
}

extern "C" asm void fn_8011E31C(struct SpriteHandle *) { /* 0x8011E31C size:0x6A4 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    lis r4, lbl_803325D0@ha
    stw r0, 0xb4(r1)
    addi r4, r4, lbl_803325D0@l
    li r0, 0x10
    addi r5, r1, 0x4
    stmw r25, 0x94(r1)
    mr r25, r3
    li r31, 0x0
    subi r4, r4, 0x4
    li r30, 0x0
    li r29, 0x0
    li r28, 0x0
    li r27, 0x0
    li r26, 0x0
    mtctr r0
    fn_8011E31C_L_8011E360:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz fn_8011E31C_L_8011E360
    lbz r0, lbl_806D14F0(r13)
    lbz r3, 0x25(r25)
    cmplw r0, r3
    beq fn_8011E31C_L_8011E388
    li r27, 0x1
    fn_8011E31C_L_8011E388:
    stb r3, lbl_806D14F0(r13)
    lbz r0, lbl_806D14F1(r13)
    lbz r4, 0x24(r25)
    extsb r0, r0
    extsb r3, r4
    cmpw r3, r0
    beq fn_8011E31C_L_8011E3A8
    li r26, 0x1
    fn_8011E31C_L_8011E3A8:
    stb r4, lbl_806D14F1(r13)
    lbz r0, 0x25(r25)
    cmplwi r0, 0x1
    bne fn_8011E31C_L_8011E3BC
    li r31, 0x1
    fn_8011E31C_L_8011E3BC:
    lbz r3, 0x24(r25)
    cmpwi r3, 0x1
    beq fn_8011E31C_L_8011E3CC
    li r30, 0x1
    fn_8011E31C_L_8011E3CC:
    extsb r0, r3
    cmpwi r0, 0x2
    beq fn_8011E31C_L_8011E3DC
    li r29, 0x1
    fn_8011E31C_L_8011E3DC:
    lbz r0, 0xb8(r25)
    cmplwi r0, 0x0
    beq fn_8011E31C_L_8011E3EC
    li r28, 0x1
    fn_8011E31C_L_8011E3EC:
    lbz r0, lbl_806D14FC(r13)
    extsb r0, r0
    cmpw r28, r0
    beq fn_8011E31C_L_8011E400
    li r26, 0x1
    fn_8011E31C_L_8011E400:
    cmpwi r27, 0x0
    stb r28, lbl_806D14FC(r13)
    beq fn_8011E31C_L_8011E4CC
    li r3, 0x4
    li r4, 0x1
    li r5, 0x1
    li r6, 0x1
    li r7, 0x1
    li r8, 0x2
    li r9, 0x2
    bl GXSetChanCtrl
    li r3, 0x7
    li r4, 0x0
    li r5, 0x0
    li r6, 0x7
    li r7, 0x0
    bl GXSetAlphaCompare
    li r3, 0x1
    bl GXSetZCompLoc
    li r3, 0x1
    li r4, 0x3
    li r5, 0x1
    bl GXSetZMode
    lis r3, lbl_806573A0@ha
    addi r6, r3, lbl_806573A0@l
    lwz r3, 0x38(r6)
    lwz r4, 0x3c(r6)
    lwz r5, 0x40(r6)
    lwz r6, 0x44(r6)
    bl GXSetScissor
    lis r3, lbl_806573A0@ha
    addi r3, r3, lbl_806573A0@l
    lfs f1, 0x20(r3)
    lfs f2, 0x24(r3)
    lfs f3, 0x28(r3)
    lfs f4, 0x2c(r3)
    lfs f5, 0x30(r3)
    lfs f6, 0x34(r3)
    bl GXSetViewport
    lis r3, lbl_806573A0@ha
    addi r3, r3, lbl_806573A0@l
    addi r3, r3, 0x4
    bl GXSetProjectionv
    lis r3, lbl_806573A0@ha
    addi r3, r3, lbl_806573A0@l
    lwz r3, 0x0(r3)
    bl GXSetCullMode
    li r3, -0x1
    bl fn_802C14B8
    lbz r3, 0x25(r25)
    bl fn_8011EC18
    fn_8011E31C_L_8011E4CC:
    lwz r3, 0x78(r25)
    lwz r4, 0x7c(r25)
    lwz r5, 0x80(r25)
    lwz r6, 0x84(r25)
    bl GXSetBlendMode
    cmpwi r26, 0x0
    beq fn_8011E31C_L_8011E56C
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E534
    li r3, 0x2
    bl GXSetNumTexGens
    li r3, 0x0
    li r4, 0x1
    li r5, 0x4
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    li r3, 0x1
    li r4, 0x1
    li r5, 0x5
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    b fn_8011E31C_L_8011E56C
    fn_8011E31C_L_8011E534:
    cmpwi r29, 0x0
    beq fn_8011E31C_L_8011E564
    li r3, 0x1
    bl GXSetNumTexGens
    li r3, 0x0
    li r4, 0x1
    li r5, 0x4
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    b fn_8011E31C_L_8011E56C
    fn_8011E31C_L_8011E564:
    li r3, 0x0
    bl GXSetNumTexGens
    fn_8011E31C_L_8011E56C:
    cmpwi r26, 0x0
    beq fn_8011E31C_L_8011E590
    cmpwi r30, 0x0
    bne fn_8011E31C_L_8011E588
    li r3, 0x0
    bl GXSetNumChans
    b fn_8011E31C_L_8011E590
    fn_8011E31C_L_8011E588:
    li r3, 0x1
    bl GXSetNumChans
    fn_8011E31C_L_8011E590:
    cmpwi r26, 0x0
    beq fn_8011E31C_L_8011E740
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E5AC
    li r3, 0x2
    bl GXSetNumTevStages
    b fn_8011E31C_L_8011E5B4
    fn_8011E31C_L_8011E5AC:
    li r3, 0x1
    bl GXSetNumTevStages
    fn_8011E31C_L_8011E5B4:
    cmpwi r29, 0x0
    bne fn_8011E31C_L_8011E5C8
    li r4, 0xff
    li r5, 0xff
    b fn_8011E31C_L_8011E5D0
    fn_8011E31C_L_8011E5C8:
    li r4, 0x0
    li r5, 0x0
    fn_8011E31C_L_8011E5D0:
    cmpwi r30, 0x0
    li r3, 0x0
    li r6, 0xff
    beq fn_8011E31C_L_8011E5E4
    li r6, 0x4
    fn_8011E31C_L_8011E5E4:
    bl GXSetTevOrder
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E604
    li r3, 0x1
    li r4, 0x1
    li r5, 0x1
    li r6, 0xff
    bl GXSetTevOrder
    fn_8011E31C_L_8011E604:
    lbz r0, 0x24(r25)
    extsb r0, r0
    cmpwi r0, 0x3
    beq fn_8011E31C_L_8011E654
    bge fn_8011E31C_L_8011E628
    cmpwi r0, 0x1
    beq fn_8011E31C_L_8011E634
    bge fn_8011E31C_L_8011E644
    b fn_8011E31C_L_8011E6C4
    fn_8011E31C_L_8011E628:
    cmpwi r0, 0x5
    bge fn_8011E31C_L_8011E6C4
    b fn_8011E31C_L_8011E68C
    fn_8011E31C_L_8011E634:
    li r3, 0x0
    li r4, 0x3
    bl GXSetTevOp
    b fn_8011E31C_L_8011E6D0
    fn_8011E31C_L_8011E644:
    li r3, 0x0
    li r4, 0x4
    bl GXSetTevOp
    b fn_8011E31C_L_8011E6D0
    fn_8011E31C_L_8011E654:
    li r3, 0x0
    li r4, 0x8
    li r5, 0x9
    li r6, 0xb
    li r7, 0xa
    bl GXSetTevColorIn
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x1
    li r8, 0x0
    bl GXSetTevColorOp
    b fn_8011E31C_L_8011E6D0
    fn_8011E31C_L_8011E68C:
    li r3, 0x0
    li r4, 0x8
    li r5, 0xf
    li r6, 0xf
    li r7, 0xa
    bl GXSetTevColorIn
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x1
    li r8, 0x0
    bl GXSetTevColorOp
    b fn_8011E31C_L_8011E6D0
    fn_8011E31C_L_8011E6C4:
    li r3, 0x0
    li r4, 0x0
    bl GXSetTevOp
    fn_8011E31C_L_8011E6D0:
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E740
    li r3, 0x1
    li r4, 0x0
    li r5, 0xf
    li r6, 0xf
    li r7, 0xf
    bl GXSetTevColorIn
    li r3, 0x1
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x1
    li r8, 0x0
    bl GXSetTevColorOp
    li r3, 0x1
    li r4, 0x7
    li r5, 0x4
    li r6, 0x0
    li r7, 0x7
    bl GXSetTevAlphaIn
    li r3, 0x1
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x1
    li r8, 0x0
    bl GXSetTevAlphaOp
    fn_8011E31C_L_8011E740:
    cmpwi r26, 0x0
    bne fn_8011E31C_L_8011E750
    cmpwi r27, 0x0
    beq fn_8011E31C_L_8011E7C8
    fn_8011E31C_L_8011E750:
    bl GXClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GXSetVtxDesc
    cmpwi r31, 0x0
    bne fn_8011E31C_L_8011E784
    li r3, 0x0
    li r4, 0x9
    li r5, 0x0
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    b fn_8011E31C_L_8011E79C
    fn_8011E31C_L_8011E784:
    li r3, 0x0
    li r4, 0x9
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    fn_8011E31C_L_8011E79C:
    cmpwi r30, 0x0
    beq fn_8011E31C_L_8011E7C8
    li r3, 0xb
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xb
    li r5, 0x1
    li r6, 0x5
    li r7, 0x0
    bl GXSetVtxAttrFmt
    fn_8011E31C_L_8011E7C8:
    cmpwi r29, 0x0
    beq fn_8011E31C_L_8011E83C
    lwz r3, 0x14(r25)
    lwz r0, lbl_806D14F4(r13)
    cmplw r3, r0
    beq fn_8011E31C_L_8011E808
    lwz r3, 0x18(r25)
    cmplwi r3, 0x0
    beq fn_8011E31C_L_8011E7F4
    li r4, 0x0
    bl GXLoadTlut
    fn_8011E31C_L_8011E7F4:
    lwz r3, 0x14(r25)
    li r4, 0x0
    bl GXLoadTexObj
    lwz r0, 0x14(r25)
    stw r0, lbl_806D14F4(r13)
    fn_8011E31C_L_8011E808:
    cmpwi r26, 0x0
    bne fn_8011E31C_L_8011E818
    cmpwi r27, 0x0
    beq fn_8011E31C_L_8011E83C
    fn_8011E31C_L_8011E818:
    li r3, 0xd
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xd
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    fn_8011E31C_L_8011E83C:
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E890
    lwz r3, 0xc4(r25)
    cmplwi r3, 0x0
    beq fn_8011E31C_L_8011E858
    li r4, 0x1
    bl GXLoadTlut
    fn_8011E31C_L_8011E858:
    lwz r3, 0xc0(r25)
    li r4, 0x1
    bl GXLoadTexObj
    lwz r0, 0xc0(r25)
    li r3, 0xe
    li r4, 0x1
    stw r0, lbl_806D14F8(r13)
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xe
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    fn_8011E31C_L_8011E890:
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GXBegin
    li r0, 0x4
    mr r3, r25
    mr r4, r25
    li r5, 0x0
    mtctr r0
    fn_8011E31C_L_8011E8B4:
    cmpwi r31, 0x0
    bne fn_8011E31C_L_8011E8D4
    lfs f1, 0x8c(r3)
    lis r6, 0xcc01
    lfs f0, 0x88(r3)
    stfs f0, -0x8000(r6)
    stfs f1, -0x8000(r6)
    b fn_8011E31C_L_8011E8F0
    fn_8011E31C_L_8011E8D4:
    lfs f2, 0x30(r25)
    lis r6, 0xcc01
    lfs f1, 0x8c(r3)
    lfs f0, 0x88(r3)
    stfs f0, -0x8000(r6)
    stfs f1, -0x8000(r6)
    stfs f2, -0x8000(r6)
    fn_8011E31C_L_8011E8F0:
    cmpwi r30, 0x0
    beq fn_8011E31C_L_8011E904
    lwz r0, 0x64(r4)
    lis r6, 0xcc01
    stw r0, -0x8000(r6)
    fn_8011E31C_L_8011E904:
    cmpwi r29, 0x0
    beq fn_8011E31C_L_8011E950
    lbz r7, 0x48(r25)
    addi r0, r1, 0x8
    lis r6, 0xcc01
    extsb r7, r7
    slwi r7, r7, 5
    add r8, r7, r5
    add r8, r0, r8
    lwz r7, 0x4(r8)
    lwz r0, 0x0(r8)
    slwi r8, r7, 3
    slwi r7, r0, 3
    addi r8, r8, 0xac
    addi r0, r7, 0xa8
    lfsx f1, r25, r8
    lfsx f0, r25, r0
    stfs f0, -0x8000(r6)
    stfs f1, -0x8000(r6)
    fn_8011E31C_L_8011E950:
    cmpwi r28, 0x0
    beq fn_8011E31C_L_8011E99C
    lbz r7, 0x48(r25)
    addi r0, r1, 0x8
    lis r6, 0xcc01
    extsb r7, r7
    slwi r7, r7, 5
    add r8, r7, r5
    add r8, r0, r8
    lwz r7, 0x4(r8)
    lwz r0, 0x0(r8)
    slwi r8, r7, 3
    slwi r7, r0, 3
    addi r8, r8, 0xcc
    addi r0, r7, 0xc8
    lfsx f1, r25, r8
    lfsx f0, r25, r0
    stfs f0, -0x8000(r6)
    stfs f1, -0x8000(r6)
    fn_8011E31C_L_8011E99C:
    addi r3, r3, 0x8
    addi r4, r4, 0x4
    addi r5, r5, 0x8
    bdnz fn_8011E31C_L_8011E8B4
    lmw r25, 0x94(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" void fn_8011E9C0(int type) {
    ScopedAccum accum(1);
    ScopedTimer timer(13);
    SpriteNode *node;
    SpriteNode *next;
    SpriteHandle *h;

    for (node = lbl_806D1500->head; node; node = next) {
        next = node->next;
        h = &g_SpriteHandlePool[node->index];
        if (type == h->type) {
            fn_8011DF98(h);
        }
    }
}
