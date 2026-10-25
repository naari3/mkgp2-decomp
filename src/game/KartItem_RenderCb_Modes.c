/*
 * KartItem TEV render callbacks and VisualEffectHolder dtor, 0x80056A48..0x80056CB0.
 */

typedef struct GXColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GXColor;

typedef struct VisualEffectHolder {
    unsigned char pad_00[0x10];
    void *drawEffect;
    unsigned char pad_14[0xA8 - 0x14];
    void *object;
} VisualEffectHolder;

extern const GXColor lbl_806D28A8;
extern const GXColor lbl_806D28AC;
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetTevColor(int reg, GXColor color);
extern void GXSetTevColorIn(int stage, int a, int b, int c, int d);
extern void GXSetTevColorOp(int stage, int op, int bias, int scale, unsigned char clamp, int reg);
extern void GXSetTevSwapModeTable(int id, int r, int g, int b, int a);
extern void GXSetTevSwapMode(int stage, int sel, int swap);
extern void fn_802C352C(int arg);
extern void DrawEffect_ReleaseCallbackResources(void *drawEffect);
extern void fn_802C2238(void);
extern void Object_DtorWithGXSync(void *object, int flag);
extern void MemoryManager_TimedFree(void *ptr);

#pragma exceptions on
void KartItem_RenderCb_Mode2or4_Post(int stage)
{
    GXSetTevOrder(stage, 0xFF, 0x100, 6);
    GXSetTevColor(1, lbl_806D28AC);
    GXSetTevColorIn(stage, 0, 0xF, 0xF, 2);
    GXSetTevColorOp(stage, 0, 0, 0, 1, 0);
}

void KartItem_RenderCb_Mode1_Pre(int stage)
{
    fn_802C352C(0);
    GXSetTevSwapModeTable(0, 0, 1, 2, 3);
    GXSetTevSwapMode(stage, 0, 0);
}

void KartItem_RenderCb_Mode1_Post(int stage, unsigned int channel)
{
    GXSetTevOrder(stage, 0xFF, 0x100, 6);
    switch (channel) {
    case 0:
    case 5:
    case 6:
    case 10:
    case 11:
    case 12:
        GXSetTevSwapModeTable(0, 0, 0, 0, 3);
        GXSetTevSwapMode(stage, 0, 0);
        break;
    case 1:
    case 4:
    case 7:
        GXSetTevSwapModeTable(0, 1, 1, 1, 3);
        GXSetTevSwapMode(stage, 0, 0);
        break;
    case 2:
    case 3:
    case 8:
    case 9:
        GXSetTevSwapModeTable(0, 2, 2, 2, 3);
        GXSetTevSwapMode(stage, 0, 0);
        break;
    }
    GXSetTevColor(1, lbl_806D28A8);
    GXSetTevColorIn(stage, 0xC, 0xF, 0, 2);
    GXSetTevColorOp(stage, 0, 0, 0, 1, 0);
}

VisualEffectHolder *VisualEffectHolder_Dtor(VisualEffectHolder *holder, short flag)
{
    if (holder != 0) {
        DrawEffect_ReleaseCallbackResources(holder->drawEffect);
        fn_802C2238();
        Object_DtorWithGXSync(holder->object, 1);
        if (flag > 0) {
            MemoryManager_TimedFree(holder);
        }
    }
    return holder;
}
#pragma exceptions reset
