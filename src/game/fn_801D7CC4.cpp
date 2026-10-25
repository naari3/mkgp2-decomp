class Scene { public: virtual void v0(); virtual bool Begin(); virtual void End(); };
typedef struct FlowKartDraw {
    int unk0;
    int selection;
    int unk8;
    int state;
    char pad10[0xC];
    Scene *scene;
    void *lobj;
    void *drivers[2];
    char pad2C[0x3C];
    void *sprites[6];
    void *text;
    char ctrl[4];
} FlowKartDraw;
extern "C" {
extern int g_characterId;
extern short lbl_8049BBA8[];
extern const float lbl_806DA148, lbl_806DA14C, lbl_806DA150, lbl_806DA154;
void fn_8011FAB8(void);
void fn_801A1280(void);
void SetCourseScene3D(void *);
void LObjList_ApplyForCObj(void *);
void CObj_DebugVizPathFlush(void *);
void KartDriver_RenderTimed(void *, int, int);
void fn_801A1174(int, int, int, int, int);
void fn_801A1128(float, float);
void fn_801A0DF0(void);
void *fn_801F8E58(void);
void fn_801F8A34(void *, void *, int);
void fn_8011FAFC(void *, int);
void fn_801A0004(void *);
}

extern "C" void fn_801D7CC4(FlowKartDraw *self)
{
    fn_8011FAB8();
    fn_801A1280();
    if (self->scene != 0) {
        SetCourseScene3D(self->scene);
        if ((unsigned char)self->scene->Begin()) {
            LObjList_ApplyForCObj(self->lobj);
            CObj_DebugVizPathFlush(self->scene);
            if (self->drivers[self->selection] != 0) {
                KartDriver_RenderTimed(self->drivers[self->selection], 0, 1);
            }
            self->scene->End();
        }
        SetCourseScene3D(0);
    }
    if (self->state == 0 || self->state == 1 || self->state == 2) {
        fn_801A1174(0x16ad, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA148, lbl_806DA14C);
        fn_801A0DF0();
        fn_801A1174(lbl_8049BBA8[g_characterId], 4, 0, 0, 0);
        fn_801A1128(lbl_806DA150, lbl_806DA154);
        fn_801A0DF0();
        fn_801F8A34(fn_801F8E58(), self->text, 5);
        if (self->selection == 1) {
            fn_8011FAFC(self->ctrl, 5);
        }
    }
    if (self->sprites[0] != 0) fn_801A0004(self->sprites[0]);
    if (self->selection == 0) {
        if (self->sprites[2] != 0) fn_801A0004(self->sprites[2]);
    } else {
        if (self->sprites[1] != 0) fn_801A0004(self->sprites[1]);
    }
    if (self->sprites[3] != 0) fn_801A0004(self->sprites[3]);
    if (self->sprites[4] != 0) fn_801A0004(self->sprites[4]);
    if (self->sprites[5] != 0) fn_801A0004(self->sprites[5]);
}
