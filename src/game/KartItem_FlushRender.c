/*
 * KartItem render-callback scheduling, 0x80056388..0x800566D4.
 */

typedef void (*KartItemRenderCb)(void);

typedef struct KartItemRender {
    unsigned char pad_00[4];
    int arg04;
    unsigned char pad_08[0x124 - 0x8];
    int mode124;
    int state128;
    unsigned char pad_12C[4];
    int phase130;
    unsigned char pad_134[4];
    int cycle138;
    unsigned char pad_13C[4];
    int pending140;
} KartItemRender;

extern void DVDLoad_AsyncStart(KartItemRenderCb post, KartItemRenderCb pre, int arg);
extern void DVDLoad_AsyncStop(void);
extern void fn_802C2274(void *sound);
extern unsigned char lbl_803F7808[];
extern unsigned char lbl_803F9834[];

extern void KartItem_RenderCb_DefaultCycle_Pre(void);
extern void KartItem_RenderCb_DefaultCycle_Post(void);
extern void KartItem_RenderCb_Mode1_Pre(void);
extern void KartItem_RenderCb_Mode1_Post(void);
extern void KartItem_RenderCb_Mode2or4_Pre(void);
extern void KartItem_RenderCb_Mode2or4_Post(void);
extern void KartItem_RenderCb_Mode3_Pre(void);
extern void KartItem_RenderCb_Mode3_Post(void);
extern void KartItem_RenderCb_Mode5_Pre(void);
extern void KartItem_RenderCb_Mode5_Post(void);
extern void KartItem_RenderCb_Mode6_Pre(void);
extern void KartItem_RenderCb_Mode6_Post(void);
extern void KartItem_RenderCb_Mode7_Pre(void);
extern void KartItem_RenderCb_Mode7_Post(void);

void KartItem_DispatchEffectRenderByState(KartItemRender *item);

#pragma exceptions on
void KartItem_FlushPendingRender(KartItemRender *item)
{
    int state = item->state128;

    if ((state == 10 || item->mode124 == 0) && state != 9) {
        if (state != 10 && (item->mode124 != 0 || item->cycle138 % 6 <= 3)) {
            DVDLoad_AsyncStop();
        }
        if (item->state128 != 0) {
            fn_802C2274(0);
        }
    }
}

void KartItem_FlushRenderIfReady(KartItemRender *item)
{
    int state = item->state128;

    if ((state == 10 || item->mode124 == 0) && state != 9) {
        KartItem_DispatchEffectRenderByState(item);
    }
}

void KartItem_FlushPendingRender_v2(KartItemRender *item)
{
    if (item->state128 != 10 && (item->mode124 != 0 || item->cycle138 % 6 <= 3)) {
        DVDLoad_AsyncStop();
    }
    if (item->state128 != 0) {
        fn_802C2274(0);
    }
}

void KartItem_DispatchEffectRenderByState(KartItemRender *item)
{
    if (item->state128 != 10) {
        if (item->cycle138 > 0) {
            if (item->cycle138 % 6 <= 3) {
                DVDLoad_AsyncStart(KartItem_RenderCb_DefaultCycle_Post, KartItem_RenderCb_DefaultCycle_Pre,
                                   item->arg04);
            }
        } else {
            switch (item->mode124) {
            case 1:
                if (item->phase130 % 8 <= 4) {
                    DVDLoad_AsyncStart(KartItem_RenderCb_Mode1_Post, KartItem_RenderCb_Mode1_Pre, item->arg04);
                }
                break;
            case 2:
                DVDLoad_AsyncStart(KartItem_RenderCb_Mode2or4_Post, KartItem_RenderCb_Mode2or4_Pre, item->arg04);
                break;
            case 3:
                DVDLoad_AsyncStart(KartItem_RenderCb_Mode3_Post, KartItem_RenderCb_Mode3_Pre, item->arg04);
                break;
            case 4:
                DVDLoad_AsyncStart(KartItem_RenderCb_Mode2or4_Post, KartItem_RenderCb_Mode2or4_Pre, item->arg04);
                break;
            case 5:
                DVDLoad_AsyncStart(KartItem_RenderCb_Mode5_Post, KartItem_RenderCb_Mode5_Pre, item->arg04);
                break;
            case 6:
                DVDLoad_AsyncStart(KartItem_RenderCb_Mode6_Post, KartItem_RenderCb_Mode6_Pre, item->arg04);
                break;
            default:
                if (item->pending140 > 0) {
                    item->mode124 = 7;
                    DVDLoad_AsyncStart(KartItem_RenderCb_Mode7_Post, KartItem_RenderCb_Mode7_Pre, 0);
                }
                break;
            }
        }
    }
    switch (item->state128) {
    case 9:
        fn_802C2274(lbl_803F7808);
        break;
    case 10:
        fn_802C2274(lbl_803F9834);
        break;
    default:
        item->state128 = 0;
        break;
    }
}
#pragma exceptions reset
