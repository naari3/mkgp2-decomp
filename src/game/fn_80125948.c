#pragma cplusplus on
#include "game/ChallengeDemoPrivate.h"
/* .rodata 0x80355A58..0x80356070: this TU's pool. The constructor reaches
 * its string literals through the hoisted section base like the target. */
extern "C" {
/* camera key table shared through a header (same bytes in clFlowKart_Init) */
extern const unsigned int lbl_80355A58[0xFF];
const unsigned int lbl_80355A58[0xFF] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
extern const char lbl_80355E54[], lbl_80355E6C[], lbl_80355E8C[];
extern const char lbl_80355E9C[], lbl_80355EA8[], lbl_80355EB4[];
const char lbl_80355E54[] = "challenge_demo_KP.dat";
const char lbl_80355E6C[] = "KP_callenge_player_set_joint";
const char lbl_80355E8C[] = "clCGameDemoKP";
const char lbl_80355E9C[] = "clJobRunner";
const char lbl_80355EA8[] = "clCGameDemo";
const char lbl_80355EB4[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
}
/* Particle/VFX holder (0x898 bytes, ctor fn_8016F010). */
struct DemoVfx {
    unsigned char opaque[0x898];
    DemoVfx();
};

struct ChallengeDemoBlock : DemoBase {
    unsigned char first;
    float time;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoNormal *extra;
    DemoNormal *effect;
    HSD_JObj *joint;
    HSD_JObj *effectJoints[5];
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *anchor;
    DemoVfx *vfx;
    HSD_JObj *bones[5];
    float boneFrame;
    float boneSpeed;
    ChallengeDemoBlock();
    virtual void _keyK();
    virtual int Update();
    virtual ~ChallengeDemoBlock();
};


extern "C" {
extern char lbl_806D6F24[7];
extern char lbl_806D6F2C[5];
extern float lbl_806CF4C0;
extern float lbl_806D1508;
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetFlagsAll(HSD_JObj *jobj, unsigned int flags);
void HSD_JObjClearFlagsAll(HSD_JObj *jobj, unsigned int flags);
float Saturate_Double(float v, float lo, float hi);
void SoundMgr_Play(int id);
void fn_80182204(HSD_JObj *jobj, unsigned char alpha);
void fn_80182B50(HSD_JObj *jobj, float u, float v);
void fn_8016EC80(DemoVfx *vfx);
}

/* HSD_JObj transform block (jobj.h). */
struct DemoJObjXform {
    char pad00[0x1C];
    float rotX, rotY, rotZ, rotW;
    float scaleX, scaleY, scaleZ;
    float transX, transY, transZ;
};

/* jobj.h inlines */
static inline unsigned char DemoJObjMtxIsDirty(HSD_JObj *jobj) {
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D6F24, 0x25D, lbl_806D6F2C);
    }
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void DemoJObjSetMtxDirty(HSD_JObj *jobj) {
    if (jobj && !DemoJObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void DemoJObjSetupMatrix(HSD_JObj *jobj) {
    if (!jobj) {
        return;
    }
    if (DemoJObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline float (*DemoJObjGetMtxPtr(HSD_JObj *jobj))[4] {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x47C, lbl_806D6F2C);
    }
    DemoJObjSetupMatrix(jobj);
    return jobj->mtx;
}

static inline void DemoJObjSetRotationY(HSD_JObj *jobj, float y) {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x2B8, lbl_806D6F2C);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D6F24, 0x2B9, (char *)lbl_80355EB4);
    }
    ((DemoJObjXform *)jobj)->rotY = y;
    if (!(jobj->flags & 0x2000000)) {
        DemoJObjSetMtxDirty(jobj);
    }
}

static inline void DemoJObjSetScaleX(HSD_JObj *jobj, float x) {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x325, lbl_806D6F2C);
    }
    ((DemoJObjXform *)jobj)->scaleX = x;
    if (!(jobj->flags & 0x2000000)) {
        DemoJObjSetMtxDirty(jobj);
    }
}

static inline void DemoJObjSetScaleY(HSD_JObj *jobj, float y) {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x333, lbl_806D6F2C);
    }
    ((DemoJObjXform *)jobj)->scaleY = y;
    if (!(jobj->flags & 0x2000000)) {
        DemoJObjSetMtxDirty(jobj);
    }
}

static inline void DemoJObjSetScaleZ(HSD_JObj *jobj, float z) {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x341, lbl_806D6F2C);
    }
    ((DemoJObjXform *)jobj)->scaleZ = z;
    if (!(jobj->flags & 0x2000000)) {
        DemoJObjSetMtxDirty(jobj);
    }
}

static inline void DemoJObjSetTranslate(HSD_JObj *jobj, const Vec *t) {
    if (!jobj) {
        __assert(lbl_806D6F24, 0x3A9, lbl_806D6F2C);
    }
    ((DemoJObjXform *)jobj)->transX = t->x;
    ((DemoJObjXform *)jobj)->transY = t->y;
    ((DemoJObjXform *)jobj)->transZ = t->z;
    if (!(jobj->flags & 0x2000000)) {
        DemoJObjSetMtxDirty(jobj);
    }
}

#pragma cplusplus reset

/* callees used by the plain C views below */
extern void fn_8016EACC();
extern void MemoryManager_TimedFree();
extern void dtor_8002CDF4();
extern void fn_8016EFA8();
extern unsigned int lbl_80419F0C[];
extern unsigned int ChallengeDemoBlock_vtable_8048E258[];
extern void fn_801825C8();
extern void fn_801825FC();

#pragma cplusplus on
extern "C" void fn_80125948(DemoMode *self)
{
    if (self->camera->Ready() == 1) {
        clDrawMan_Buckets_Reset(GetDrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->camera);
        fn_8016B0C4();
        Object_RenderJObjTree(self->world, 7);
        Object_RenderJObjTree(self->extra, 7);
        KartDriver_RenderTimed(self->driver, 0, 1);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        Object_RenderJObjTree(self->effect, 7);
        fn_8016EACC(self->vfx);
        clDrawMan_EndFrame_NoOp(GetDrawMan());
        clDrawMan_Buckets_Dispatch(GetDrawMan());
        unsigned char alpha = 0;
        float frame = self->frame;
        if (frame < 30.0f) alpha = (255.0f - 255.0f * DemoClamp(frame / 30.0f, 0.0f, 1.0f));
        if (frame > 350.0f) alpha = (255.0f - 255.0f * DemoClamp((380.0f - frame) / 30.0f, 0.0f, 1.0f));
        if ((unsigned char)alpha) fn_80181790(self->camera, 0, 1.0f, 0, 0, alpha, 0);
        self->camera->Render();
        HSD_StateInvalidate(0x7f);
    }
}
#pragma cplusplus reset

#pragma cplusplus on
int ChallengeDemoBlock::Update() {
    if (first) {
        first = 0;
    } else {
        time += 1.0f;
        if (time >= 380.0f) {
            return 0xF;
        }
    }
    if (75.0f == time) {
        SoundMgr_Play(0xB5);
    }
    Object_SetField8_AndDirty(normal, time);
    clNormal3D_Exec(normal);
    {
        DemoScene *s = scene;
        float t = time;
        if (!(s->frame < 0.0f) && !(t < 0.0f)) {
            s->active = 1;
            s->frame = t;
        }
    }
    scene->Tick(-1.0f);
    Object_SetField8_AndDirty(extra, time);
    clNormal3D_Exec(extra);
    Object_SetField8_AndDirty(effect, time);
    clNormal3D_Exec(effect);
    if (effectJoints[0]) {
        if (time < 85.0f || time > 100.0f) {
            HSD_JObjSetFlagsAll(effectJoints[0], 0x10);
        } else {
            HSD_JObjClearFlagsAll(effectJoints[0], 0x10);
            float k = Saturate_Double((time - 85.0f) / 15.0f, 0.0f, 1.0f);
            DemoJObjSetScaleX(effectJoints[0], 1.2f * k + 1.0f);
            DemoJObjSetScaleY(effectJoints[0], 0.5f * k + 1.0f);
            DemoJObjSetScaleZ(effectJoints[0], 1.2f * k + 1.0f);
            fn_80182204(effectJoints[0], 255 - (int)(255.0f * k));
        }
    }
    if (effectJoints[1]) {
        if (time < 90.0f || time > 105.0f) {
            HSD_JObjSetFlagsAll(effectJoints[1], 0x10);
        } else {
            HSD_JObjClearFlagsAll(effectJoints[1], 0x10);
            float k = Saturate_Double((time - 90.0f) / 15.0f, 0.0f, 1.0f);
            DemoJObjSetScaleX(effectJoints[1], 1.2f * k + 1.0f);
            DemoJObjSetScaleY(effectJoints[1], 0.5f * k + 1.0f);
            DemoJObjSetScaleZ(effectJoints[1], 1.2f * k + 1.0f);
            fn_80182204(effectJoints[1], 255 - (int)(255.0f * k));
        }
    }
    if (effectJoints[2] && joint) {
        if (time > 80.0f) {
            HSD_JObjSetFlagsAll(effectJoints[2], 0x10);
        } else {
            float (*m)[4] = DemoJObjGetMtxPtr(joint);
            Vec pos;
            pos.x = m[0][3];
            pos.y = m[1][3];
            pos.z = m[2][3];
            pos.y += -265.0f;
            pos.z += -28.0f;
            DemoJObjSetTranslate(effectJoints[2], &pos);
            if (time >= 70.0f) {
                float k = Saturate_Double((time - 70.0f) / 10.0f, 0.0f, 1.0f);
                DemoJObjSetScaleX(effectJoints[2], 0.8f * k + 1.0f);
                DemoJObjSetScaleY(effectJoints[2], 1.0f - 0.9f * k);
            }
            fn_80182B50(effectJoints[2], lbl_806CF4C0, lbl_806D1508);
        }
    }
    if (effectJoints[3] && effectJoints[4]) {
        if (time >= 90.0f || time <= 125.0f) {
            float k = Saturate_Double((time - 120.0f) / 5.0f, 0.0f, 1.0f);
            unsigned char level = 255.0f * k;
            fn_80182204(effectJoints[3], 255 - level);
            fn_80182204(effectJoints[4], 255 - level);
        }
    }
    fn_80182B50(bones[0], 0.0f, 0.002f);
    fn_80182B50(bones[1], 0.0f, -0.002f);
    fn_80182B50(bones[2], 0.0f, -0.002f);
    boneFrame += 0.00087266444f;
    if (boneFrame >= 6.283184f) {
        boneFrame -= 6.283184f;
    }
    boneSpeed += 0.0005817763f;
    if (boneSpeed >= 6.283184f) {
        boneSpeed -= 6.283184f;
    }
    DemoJObjSetRotationY(bones[3], boneFrame);
    DemoJObjSetRotationY(bones[4], boneSpeed);
    Vec prev;
    prev.x = matrix[0][3];
    prev.y = matrix[1][3];
    prev.z = matrix[2][3];
    float angle = 0.0f;
    PSMTXScale(matrix, 1.45f, 1.45f, 1.45f);
    PSMTXConcat(DemoJObjGetMtxPtr(anchor), matrix, matrix);
    Vec cur;
    cur.x = matrix[0][3];
    cur.y = matrix[1][3];
    cur.z = matrix[2][3];
    Vec d;
    Vec3_Subtract(&cur, &prev, &d);
    float dist = Vec3_Magnitude(&d);
    if (0.0f != dist && time > 0.0f) {
        Vec fwd;
        fwd.x = matrix[0][2];
        fwd.y = matrix[1][2];
        fwd.z = matrix[2][2];
        Vec3_Normalize(&d, &d);
        Vec3_Normalize(&fwd, &fwd);
        Vec c;
        PSVECCrossProduct(&d, &fwd, &c);
        angle = 4.0f * (float)asin(c.x + c.y + c.z);
    }
    RenderObj_ItemStateMachine_Timed(driver, 0, angle, 0.06981111f * dist);
    TornadoEffect_Tick(tornado, GetDisplayBufferIndex());
    Vec eye;
    Vec target;
    CObj_LoadProjMatrix(scene, &eye);
    CObj_ApplyScissor(scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    fn_8016EC80(vfx);
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400)) {
        return 0xF;
    }
    return -2;
}
#pragma cplusplus reset


#pragma cplusplus on
extern "C" DemoMode *fn_80126728(DemoMode *self, short free_flag)
{
    if (self) {
        self->vtable = ChallengeDemoBlock_vtable_8048E258;
        SetActiveCamera(0, 0);
        if (self->owner >= 0) TransparentDraw_RemoveByOwner(self->owner);
        SetPlayerCarObject(0);
        SetCourseScene3D(0);
        if (self->camera) ((DemoDeleteView *)self->camera)->Destroy(1);
        Object_DtorWithGXSync(self->world, 1);
        Object_DtorWithGXSync(self->extra, 1);
        Object_DtorWithGXSync(self->effect, 1);
        VisualEffectHolder_Dtor(self->tornado, 1);
        KartDriver_Dtor(self->driver, 1);
        fn_8016EFA8(self->vfx, 1);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        SceneDrawList_Reset();
        if (lbl_806D10AC) ((DemoDeleteView *)lbl_806D10AC)->Destroy(1);
        lbl_806D10AC = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        if (self) {
            self->vtable = lbl_80419F0C;
            dtor_8002CDF4(self, 0);
        }
        if (free_flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma cplusplus reset

#pragma cplusplus on
#pragma readonly_strings on
extern "C" {
extern const char *lbl_806CF4B8;
extern const char *lbl_806CF4BC;
}

ChallengeDemoBlock::ChallengeDemoBlock() {
    first = 1;
    time = 0.0f;
    scene = 0;
    drawHandle = -1;
    normal = 0;
    extra = 0;
    joint = 0;
    effect = 0;
    effectJoints[0] = 0;
    effectJoints[1] = 0;
    effectJoints[2] = 0;
    effectJoints[3] = 0;
    effectJoints[4] = 0;
    driver = 0;
    tornado = 0;
    anchor = 0;
    PSMTXIdentity(matrix);
    vfx = 0;
    bones[0] = 0;
    bones[1] = 0;
    bones[2] = 0;
    bones[3] = 0;
    bones[4] = 0;
    boneFrame = 0.0f;
    boneSpeed = 0.0f;
    SetResourceLoadingFlag(0);
    DrawManager_GetOrCreate();
    DMAChannelManager_Init();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    scene = new DemoScene(lbl_806CF4B8, -1.0f, 0.0f);
    scene->Start(0.0f, 1.0f);
    normal = new DemoNormal(lbl_806CF4B8, 0);
    clNormal3D_SetScale(normal, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 0, 0.0f, 0.0f, 0.0f);
    anchor = ResolveJointByName(normal, lbl_806CF4BC);
    if (g_characterId == 4) {
        extra = new DemoNormal("boss_meka_koopa.dat", 0);
        joint = ResolveJointByName(extra, "challenge_meka_koopa_effect_set_joint");
    } else {
        extra = new DemoNormal("boss_koopa.dat", 0);
        joint = ResolveJointByName(extra, "challenge_koopa_effect_set_joint");
    }
    clNormal3D_SetScale(extra, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    fn_801825FC();
    effect = new DemoNormal("ef_cm5_02_opening.dat", 0);
    fn_801825C8();
    clNormal3D_SetScale(effect, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    effectJoints[0] = ResolveJointByName(effect, "_circle_wind2_joint");
    effectJoints[1] = ResolveJointByName(effect, "_circle_wind4_joint");
    effectJoints[2] = ResolveJointByName(effect, "_wind_sphere_joint");
    effectJoints[3] = ResolveJointByName(effect, "_b_wind_joint");
    effectJoints[4] = ResolveJointByName(effect, "_g_wind_joint");
    bones[0] = ResolveJointByName(normal, "KP_callenge_zyougan01_joint");
    bones[1] = ResolveJointByName(normal, "KP_callenge_zyougan02_joint");
    bones[2] = ResolveJointByName(normal, "KP_callenge_zyougan03_joint");
    bones[3] = ResolveJointByName(normal, "KP_callenge_kp01_skydome_joint");
    bones[4] = ResolveJointByName(normal, "KP_callenge_kp03_skycloud_joint");
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    vfx = new DemoVfx;
    SetResourceLoadingFlag(1);
}
extern "C" {
/* camera class names that follow the literals in the pool (unreferenced) */
extern const char lbl_80356054[], lbl_80356060[];
const char lbl_80356054[] = "clACamera";
const char lbl_80356060[] = "clCamera";
}
#pragma readonly_strings reset
#pragma cplusplus reset
