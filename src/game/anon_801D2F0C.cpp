/* Ranking display owner: animate, draw, reset a track and release children. */
#include "game/RankingSpriteOwner_private.h"
extern "C" {
extern const float lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FC0;
extern const float lbl_806DA004, lbl_806DA008, lbl_806DA00C, lbl_806DA010;
extern const float lbl_806DA014, lbl_806DA018, lbl_806DA01C;
extern const float lbl_806D6DE4, lbl_806D6DE8;
extern void *lbl_8049B53C[], *lbl_8048EF34[];
void Sprite_AdvanceAnim(RankingSprite *, float);
void fn_801A0004(RankingSprite *);
void fn_801A1280();
void fn_8011FAB8();
void *fn_801F8E58();
void fn_801F8A34(void *, TextManager *, int);
void SetCourseScene3D(RankingScene *);
void LObjList_ApplyForCObj(void *);
void CObj_DebugVizPathFlush(RankingScene *);
void KartDriver_RenderTimed(RankingDriver *, int, int);
void RenderObj_ItemStateMachine_Timed(RankingDriver *, int, float, float);
void fn_8011FAFC(ResCtrl *, int);
void fn_80121E10(ResCtrl *);
void MemoryManager_TimedFree(void *);
}

static inline void UpdateRankingTransform(RankingSpriteOwnerView *self) {
    Mtx scale, rotate, translate;
    self->value = self->from * (lbl_806D9FAC - self->time) + self->to * self->time;
    self->time += self->speed;
    if (self->time > lbl_806D9FAC) self->time = lbl_806D9FAC;
    PSMTXScale(scale, lbl_806DA004, lbl_806DA004, lbl_806DA004);
    PSMTXTrans(translate, self->value, self->placement->y, self->placement->z);
    PSMTXIdentity(self->matrix);
    PSMTXConcat(scale, self->matrix, self->matrix);
    PSMTXRotRad(rotate, 'x', lbl_806DA008 * self->placement->rx);
    PSMTXConcat(rotate, self->matrix, self->matrix);
    PSMTXRotRad(rotate, 'y', lbl_806DA008 * self->placement->ry);
    PSMTXConcat(rotate, self->matrix, self->matrix);
    PSMTXConcat(translate, self->matrix, self->matrix);
    RenderObj_ItemStateMachine_Timed(self->driver.p, 0, lbl_806D9FA8, lbl_806D9FA8);
}

extern "C" void fn_801D2F0C(RankingSpriteOwnerView *self) {
    float x = self->tracks[3].value;
    self->back.p->SetPos(x, self->y);
    self->front.p->SetPos(x, self->y);
    self->mark.p->SetPos(lbl_806DA010 + x, self->y - lbl_806DA00C);
    fn_801F93EC(&self->text0, x + self->labelPos[0][0], self->y + self->labelPos[0][1]);
    fn_801F93EC(&self->text2, x + self->labelPos[1][0], self->y + self->labelPos[1][1]);
    fn_801F93EC(&self->text1, x + self->labelPos[2][0], self->y + self->labelPos[2][1]);
    fn_801F8E90(&self->text0);
    fn_801F8E90(&self->text2);
    fn_801F8E90(&self->text1);
    Sprite_AdvanceAnim(self->back.p, lbl_806D9FC0);
    Sprite_AdvanceAnim(self->front.p, lbl_806D9FC0);
    Sprite_AdvanceAnim(self->mark.p, lbl_806D9FC0);
    UpdateRankingTransform(self);
}

extern "C" void fn_801D3118(RankingSpriteOwnerView *self) {
    fn_801A0004(self->back.p);
    fn_8011FAB8();
    fn_801A1280();
    void *draw = fn_801F8E58();
    fn_801F8A34(draw, &self->text0, 7);
    fn_801F8A34(draw, &self->text2, 7);
    fn_801F8A34(draw, &self->text1, 7);
    SetCourseScene3D(self->scene);
    if (self->scene->Begin()) {
        LObjList_ApplyForCObj(self->lights);
        CObj_DebugVizPathFlush(self->scene);
        KartDriver_RenderTimed(self->driver.p, 0, 1);
        self->scene->End();
        SetCourseScene3D(0);
    }
    ResCtrl ctrl;
    ctrl.resId = self->resource;
    ctrl.Show(self->labelPos[3][0] + self->tracks[3].value,
              self->y + self->labelPos[3][1], lbl_806D9FAC);
    if (self->alternate == 0) ctrl.SetScaleXY(lbl_806D6DE4, lbl_806D6DE8);
    fn_8011FAFC(&ctrl, 6);
    if (self->labelB >= 0) {
        fn_80121E10(&ctrl);
        ctrl.resId = self->labelB;
        ctrl.Show(self->labelPos[3][0] + self->tracks[3].value,
                  self->y + self->labelPos[3][1], lbl_806D9FAC);
        ctrl.SetScaleXY(lbl_806DA014, lbl_806DA018);
        fn_8011FAFC(&ctrl, 6);
    }
    if (self->labelA >= 0) {
        fn_80121E10(&ctrl);
        ctrl.resId = self->labelA;
        float offset = lbl_806D9FA8;
        if (self->labelVariant == 0) offset = lbl_806DA01C;
        ctrl.Show(self->labelPos[3][0] + self->tracks[3].value,
                  (self->y + self->labelPos[3][1]) - offset, lbl_806D9FAC);
        ctrl.SetScale(lbl_806DA014);
        fn_8011FAFC(&ctrl, 6);
    }
    fn_801A0004(self->front.p);
    if (self->hideMark != 1) fn_801A0004(self->mark.p);
}

extern "C" void fn_801D3354(RankingTrack *self) {
    self->speed = lbl_806D9FA8;
    self->time = lbl_806D9FA8;
}

extern "C" void *fn_801D3364(RankingSpriteOwnerView *self, short flag) {
    if (self) {
        self->vtable = lbl_8049B53C;
        self->driver.~RankingDriverSlot();
        self->mark.~RankingSpriteSlot();
        self->front.~RankingSpriteSlot();
        self->back.~RankingSpriteSlot();
        if (self) {
            self->vtable = lbl_8048EF34;
            Sprite_Destroy(self->baseSprite, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
