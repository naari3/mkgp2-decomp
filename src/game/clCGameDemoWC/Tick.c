#pragma cplusplus on
#include "game/clCGameDemoWC_Tick_private.h"

extern "C" {
extern char lbl_806D4FB0[7], lbl_806D4FB8[5];
extern const float lbl_806D4FA8, lbl_806D4FAC, lbl_806D4FC0;
extern float clCGameDemoWC_Tick_data_80419E88[];
extern int clCGameDemoWC_Tick_data_80419EA0[];
void KartItem_CancelAndQueueDefault(DemoDriver *);
void SetAnimWallHitA(DemoDriver *);
void SetAnimWallHitB(DemoDriver *);
}
/* HSD jobj.h inlines retain their independent argument assertions. */
static inline int JointMatrixIsDirty(HSD_JObj *joint)
{
    unsigned char dirty;
    if (!joint) __assert(lbl_806D4FB0, 0x25d, lbl_806D4FB8);
    dirty = 0;
    if (!(joint->flags & 0x800000) && (joint->flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void JointSetupMatrix(HSD_JObj *joint)
{
    if (!joint) __assert(lbl_806D4FB0, 0x47c, lbl_806D4FB8);
    if (joint && JointMatrixIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
}
static inline void SceneSetFrame(DemoScene *scene, float frame)
{
    if (!(scene->frame < 0.0f) && !(frame < 0.0f)) {
        scene->active = 1;
        scene->frame = frame;
    }
}
#pragma exceptions on
extern "C" int clCGameDemoWC_Tick(DemoWCTick *self)
{
    Vec previous, current, delta, eye, target;
    float distance;
    HSD_JObj *joint;
    if (self->first) self->first = 0;
    else {
        if (270.0f <= (self->frame += 1.0f)) return 15;
    }
    Object_SetField8_AndDirty(self->normal, self->frame);
    clNormal3D_Exec(self->normal);
    SceneSetFrame(self->scene, self->frame);
    self->scene->Tick(lbl_806D4FA8);
    self->aux->Tick();
    previous.x = self->matrix[0][3];
    previous.y = self->matrix[1][3];
    previous.z = self->matrix[2][3];
    PSMTXScale(self->matrix, lbl_806D4FAC, lbl_806D4FAC, lbl_806D4FAC);
    joint = self->joint;
    JointSetupMatrix(joint);
    PSMTXConcat(joint->mtx, self->matrix, self->matrix);
    current.x = self->matrix[0][3];
    current.y = self->matrix[1][3];
    current.z = self->matrix[2][3];
    Vec3_Subtract(&current, &previous, &delta);
    distance = lbl_806D4FA8 * Vec3_Magnitude(&delta);
    if (0.0f <= clCGameDemoWC_Tick_data_80419E88[self->event] && clCGameDemoWC_Tick_data_80419E88[self->event] <= self->frame) {
        DemoDriver *driver = self->driver;
        switch (clCGameDemoWC_Tick_data_80419EA0[self->event]) {
        case 0: KartItem_CancelAndQueueDefault(driver); break;
        case 1: SetAnimWallHitB(driver); break;
        case 2: SetAnimWallHitA(driver); break;
        }
        self->event++;
    }
    RenderObj_ItemStateMachine_Timed(self->driver, 0, 0.0f, lbl_806D4FC0 * distance);
    TornadoEffect_Tick(self->tornado, GetDisplayBufferIndex());
    CObj_LoadProjMatrix(self->scene, &eye);
    CObj_ApplyScissor(self->scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400) ? 15 : -2;
}
#pragma exceptions reset
