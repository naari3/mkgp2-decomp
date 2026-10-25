/* clFlowCC debug overlay: shows the selected course entry while the stick is held left. */
struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
};

struct FlowCC {
    void *vtable;
    int entry;
    void *anim;
};

extern "C" {
extern const char clFlowCCInterface[];
extern const float lbl_806DA058;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
void OverlayText(int, int, int, const char *, ...);
const char *ResourceTable_GetFilePathPtr(int entry);
const char *fn_801228D4(int entry);
void fn_801A0004(void *anim);
void fn_8011FA98(void);
}

extern "C" void fn_801D3A70(FlowCC *self) {
    const char *s = clFlowCCInterface;

    if (InputMgr_GetPlayer(GetInputManager(), 0)->StickLeft() <= lbl_806DA058) {
        OverlayText(2, 0, 0, s + 0x1C);
        OverlayText(2, 0, 1, s + 0x30, self->entry);
        if (ResourceTable_GetFilePathPtr(self->entry) != 0) {
            OverlayText(2, 0, 2, s + 0x3C, ResourceTable_GetFilePathPtr(self->entry));
        }
        if (fn_801228D4(self->entry) != 0) {
            OverlayText(2, 0, 3, s + 0x48, fn_801228D4(self->entry));
        }
    }
    fn_801A0004(self->anim);
    fn_8011FA98();
}
