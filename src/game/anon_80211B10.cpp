/*
 * 0x80211B10..0x80211E6C: JumpDistanceMode draw (vtable lbl_804ECC08:
 * JumpDistanceMode_Update, this, dtor fn_80212EA4). Draws the course
 * scene and, when a card is inserted, the landing result grid.
 */

#include "game/JumpDistanceMode.h"

struct DrawMan;
struct TransitionEffect;
struct ItemBoxManager;

extern "C" {
extern DrawMan *lbl_806D10AC;
extern TransitionEffect *lbl_806D109C;
extern ItemBoxManager *lbl_806D10D0;
extern const float lbl_806DAD70;
extern const float lbl_806DADD4;
extern const float lbl_806DADD8;
extern const float lbl_806DADDC;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC1B8;
void clDrawMan_Buckets_Reset(DrawMan *dm);
void clDrawMan_SetMaxClipZ(DrawMan *dm, float z);
void clDrawMan_EndFrame_NoOp(DrawMan *dm);
void clDrawMan_Buckets_Dispatch(DrawMan *dm);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(Scene3D *scene);
void fn_8016B0C4(void);
void KartItem_RenderPipelinedWithEffects(void *kart, int a);
void Object_RenderJObjIfWithinRange(void *obj);
void CourseEnvironment_RenderObjects_Timed(void *env);
void Subsystem36c_DispatchPass2_Timed(void *env);
void Subsystem36c_DispatchPass4_Timed(void *env);
void fn_8023E2F8(void *p);
void clItemBoxManager_Draw(ItemBoxManager *m);
void ItemObjectManager_Render(void);
void DrawEffect_TickAndCull(void);
void TransitionEffect_RenderPass(TransitionEffect *t, int pass);
void fn_80253448(void *p, unsigned int color);
void fn_802535D4(void *p);
unsigned char IsCardValid(void);
void HSD_StateInvalidate(int state);
}

static inline DrawMan *GetDrawMan() {
    return lbl_806D10AC == 0 ? (DrawMan *)0 : lbl_806D10AC;
}

static inline TransitionEffect *GetTransition() {
    return lbl_806D109C == 0 ? (TransitionEffect *)0 : lbl_806D109C;
}

static inline ItemBoxManager *GetItemBoxMan() {
    return lbl_806D10D0 == 0 ? (ItemBoxManager *)0 : lbl_806D10D0;
}

static inline void DrawDigit(LandingGrid *d, GridCell *g) {
    GridCell *h = g;
    fn_8013D660(d->markers[0], h->x, g->y);
    fn_8013D570(d->markers[0], lbl_806DADD8 * h->rot);
    fn_8013D4B0(d->markers[0], h->alpha);
    d->markers[0]->Draw();
    for (int i = 0; i < 5; i++) {
        GridSlot *t = &h->slots[i];
        if (t->age >= 0) {
            fn_8013D660(d->markers[1], t->x, t->y);
            fn_8013D4B0(d->markers[1], lbl_806DAD70 - (float)t->age / lbl_806DADDC);
            d->markers[1]->Draw();
        }
    }
}

void JumpDistanceMode::Draw() {
    if (ready) {
        if (scene->Ready() == 1) {
            clDrawMan_Buckets_Reset(GetDrawMan());
            clDrawMan_SetMaxClipZ(GetDrawMan(), lbl_806DADD4);
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(car, 0);
            Object_RenderJObjIfWithinRange(lakitu);
            CourseEnvironment_RenderObjects_Timed(env);
            fn_8023E2F8(itemSlot);
            clItemBoxManager_Draw(GetItemBoxMan());
            Subsystem36c_DispatchPass2_Timed(env);
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(GetDrawMan());
            clDrawMan_Buckets_Dispatch(GetDrawMan());
            Subsystem36c_DispatchPass4_Timed(env);
            TransitionEffect_RenderPass(GetTransition(), 2);
            TransitionEffect_RenderPass(GetTransition(), 4);
            fn_80253448(hud, lbl_806DC1B0 | lbl_806DC190);
            scene->Render();
        }
        int i;
        LandingGrid *d = grid;
        if (IsCardValid()) {
            for (i = 0; i < 15; i++) {
                if (d->cells[i].visible) {
                    DrawDigit(d, &d->cells[i]);
                }
                if (d->cells2[i].visible) {
                    DrawDigit(d, &d->cells2[i]);
                }
            }
        }
        fn_80253448(hud, lbl_806DC1B8);
        fn_802535D4(hud);
        TransitionEffect_RenderPass(GetTransition(), 1);
        HSD_StateInvalidate(0x7F);
    }
}
