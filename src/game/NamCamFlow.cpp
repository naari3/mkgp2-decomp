/* Partial native reconstruction of the indivisible 801F2B70 EH group.
 * Unimplemented methods remain in the target fallback; keep NonMatching. */
#include "game/NamCamFlow_private.h"

extern "C" void fn_801F2B70(NamCamFlow *self) {
    if (!self->finished) {
        fn_8011F994(0);
        if (self->camera == 1) fn_801F43F8(self->capture->image.p);
        fn_8011FAB8();
    }
}

extern "C" void fn_801F3198(NamCamFlow *self) {
    ResCtrl rc;
    if (self->camera == 1) {
        fn_80121E10(&rc);
        int japanese = isJapanese();
        int resource = 0x1A8;
        if (!japanese) resource = 0x50E;
        rc.resId = resource;
        rc.Show(lbl_803BE434[0], lbl_803BE434[1], lbl_806DA590);
        fn_8011FAFC(&rc, 1);
    }
    if (self->camera == 0) {
        fn_80121E10(&rc);
        int japanese = isJapanese();
        int resource = 0x1A7;
        if (!japanese) resource = 0x50D;
        rc.resId = resource;
        rc.Show(lbl_806DA588, lbl_806DA594, lbl_806DA590);
        fn_8011FAFC(&rc, 1);
    } else if (self->timer <= lbl_806DA854) {
        fn_801F8A34(fn_801F8E58(), self->text + 1, 1);
        fn_801F8A34(fn_801F8E58(), self->text + 2, 1);
    }
}

extern "C" void fn_801F38DC(VObject *p) { delete p; }

extern "C" void fn_801F32BC(NamCamFlow *self) {
    NamCamPlayerInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (!self->camera) {
        if (--self->timer <= 0) {
            self->state = 2;
            self->timer = lbl_806DA858;
            self->state = 3;
            self->color = 0;
        }
        return;
    }
    int number = 3;
    int time = 180;
    int id = 6;
    do {
        if (self->timer == time) {
            fn_801F4DF0(self->list, new NamCamCountdown(id, number), 0);
            FlowTask *task = fn_801F4DC0(self->list, id);
            if (task) {
                NamCamCountdown *counter = (NamCamCountdown *)fn_80271340(task, 0, lbl_806D0028, lbl_806D0020, 0);
                counter->x = lbl_806DA5CC;
                counter->y = lbl_806DA5D0;
            }
            fn_801F4DF0(self->list, new NamCamCountdown(id + 1, number), 0);
            task = fn_801F4DC0(self->list, id + 1);
            if (task) {
                NamCamCountdown *counter = (NamCamCountdown *)fn_80271340(task, 0, lbl_806D0028, lbl_806D0020, 0);
                counter->x = lbl_806DA5D4;
                counter->y = lbl_806DA5D0;
            }
        }
        --number;
        id -= 2;
        time -= 60;
    } while (number > 0);
    --self->timer;
    fn_801FE1FC(self->timer);
    bool finish = false;
    if (self->capture->ready && self->timer <= lbl_806DA854 && input->Pressed(0x2000))
        finish = true;
    if (self->timer <= 0) finish = true;
    if (finish) {
        self->state = 2;
        self->fade->Set(255, 0, 8);
        self->color = 0xFFFFFF00;
        fn_801FE1D8();
        fn_801F4D3C(self->list);
    }
}

extern "C" void fn_801F36D0(NamCamFlow *self) {
    ResCtrl rc;
    int player = GetDisplayBufferIndex();
    int role = player;
    if (g_localPcbRole >= 2)
        role = ((signed char *)SyncSlot_GetRecv())[player + 0x11];
    fn_80121E10(&rc);
    rc.resId = lbl_803BDF20.icons[self->player][role];
    rc.Show(lbl_806DA588, lbl_806DA598, lbl_806DA590);
    rc.SetScale(lbl_806DA5A8);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    int japanese = isJapanese();
    int resource = 0x1A9;
    if (!japanese) resource = 0x50F;
    rc.resId = resource;
    rc.Show(lbl_803BDF20.labels[0], lbl_803BDF20.labels[1], lbl_806DA590);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    if (!isJapanese()) rc.resId = lbl_803BDF20.playerLabels[player][0];
    else rc.resId = lbl_803BDF20.playerLabels[player][1];
    rc.Show(lbl_803BDF20.labels[2], lbl_803BDF20.labels[3], lbl_806DA590);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    if (!isJapanese()) rc.resId = lbl_803BDF20.modeLabels[self->player][0];
    else rc.resId = lbl_803BDF20.modeLabels[self->player][1];
    rc.Show(lbl_806DA578[0], lbl_806DA578[1], lbl_806DA590);
    fn_8011FAFC(&rc, 1);
    fn_801F8A34(fn_801F8E58(), self->text, 1);
}

extern "C" NamCamFlow *fn_801F3914(int player, int mode) {
    return (NamCamFlow *)new NamCamScene(player, mode);
}

extern "C" void fn_801F418C() {}

extern "C" void fn_801F4190(NamCamCountdown *self) {
    ResCtrl rc;
    rc.resId = self->resource + 0x68C;
    rc.Show(self->x, self->y, lbl_806DA590);
    rc.SetColor(0xFFFFFF00 | (unsigned char)self->fade.p->Value());
    rc.SetScale(self->scale.p->Value());
    fn_8011FAFC(&rc, self->layer);
    if (self->timer == 15)
        self->scale.p->Set(lbl_806DA5C8, lbl_806DA590, 5);
    else if (self->timer == 40)
        self->scale.p->Set(lbl_806DA590, lbl_806DA5D8, 5);
    else if (self->timer == 45)
        self->scale.p->Set(lbl_806DA5D8, lbl_806DA5DC, 15);
    if (self->timer == 45) self->fade.p->Set(255, 0, 15);
    self->fade.p->Step();
    self->scale.p->Step();
    self->timer++;
    if (self->timer > 60) self->field0C = 1;
}

NamCamCountdown::~NamCamCountdown() {}
NamCamScaleHolder::~NamCamScaleHolder() throw() { delete p; }
NamCamListHolder::~NamCamListHolder() throw() { delete p; }
NamCamByteHolder::~NamCamByteHolder() { if (p) delete p; }
NamCamCapture::BufferOwner::~BufferOwner() { delete p; }
NamCamCapture::ImageOwner::~ImageOwner() { delete p; }
NamCamCaptureHolder::~NamCamCaptureHolder() throw() { delete p; }

NamCamBase::~NamCamBase() {}
NamCamScene::~NamCamScene() {
    fn_801F4D3C(list.p);
    delete[] text;
    fn_80120A08(0x50B);
    fn_80120A08(0x50C);
    fn_80120A08(0x68C);
    if (!isJapanese()) {
        fn_80120A08(0x50D);
        fn_80120A08(lbl_803BE4F4[player][0]);
        fn_80120A08(lbl_803BE444[player][0]);
    } else {
        fn_80120A08(0x1A7);
        fn_80120A08(lbl_803BE4F4[player][1]);
        fn_80120A08(lbl_803BE444[player][1]);
    }
    fn_801F8E54();
}

struct NamCamTexture {
    char data[0x4C];
    NamCamTexture();
};
NamCamImage::NamCamImage() : ready(0),
    display((unsigned char *)new NamCamTexture), scratch(new unsigned char) {}
NamCamBuffers::NamCamBuffers() : size(0x4B000), pixels(0) {
    pixels = FUN_8003b120(size);
}
NamCamCapture::NamCamCapture() : image(new NamCamImage), buffers(new NamCamBuffers),
    ready(0), pixels(FUN_8003b120(0x4B000)) { NamCam_Init(); }
NamCamBase::NamCamBase(int whichPlayer) : capture(new NamCamCapture),
    player(whichPlayer), fade(new FlowFaderI), color(0) {
    if (!GetVBlankFlag()) timer = lbl_806DA850;
    else if (VBlankValue_Get() == 1) timer = lbl_806DA850;
    else timer = lbl_806DA84C;
    fade.p->Set(255, 0, 22);
}
NamCamScene::NamCamScene(int whichPlayer, int mode) : NamCamBase(whichPlayer),
    state(0), list(new SceneListImpl) {
    if (!GetVBlankFlag()) camera = 0;
    else if (VBlankValue_Get() == 1) camera = 0;
    else camera = 1;
    SetSyncTarget(19);
    fn_801F8E58();
    PreloadResource(0x50B);
    PreloadResource(0x50C);
    PreloadResource(0x68C);
    if (!isJapanese()) {
        PreloadResource(0x50D);
        PreloadResource(lbl_803BE4F4[whichPlayer][0]);
        PreloadResource(lbl_803BE444[whichPlayer][0]);
    } else {
        PreloadResource(0x1A7);
        PreloadResource(lbl_803BE4F4[whichPlayer][1]);
        PreloadResource(lbl_803BE444[whichPlayer][1]);
    }
    text = new TextManager[3];
    text->visible = 1;
    fn_801F93EC(text, lbl_806DA570[0], lbl_806DA570[1]);
    if (Sci2Card_GetByteFlag1224()) fn_801F9014(text, g_playerData);
    else TexMgr_SetTexture(text, lbl_806DA5AC);
    text[1].color = 0xFFFFFFBF;
    fn_801F93D0(text + 1, lbl_806DA5B0, lbl_806DA5B0);
    text[2].color = 0xFFFFFFBF;
    fn_801F93D0(text + 2, lbl_806DA5B0, lbl_806DA5B0);
    if (!isJapanese()) {
        fn_801F93EC(text + 1, lbl_803BE54C[0], lbl_803BE54C[1]);
        TexMgr_SetTexture(text + 1, lbl_806DA94C[0]);
        fn_801F93EC(text + 2, lbl_803BE54C[2], lbl_803BE54C[3]);
        TexMgr_SetTexture(text + 2, lbl_806DA94C[1]);
    } else {
        fn_801F93EC(text + 1, lbl_803BE55C[0], lbl_803BE55C[1]);
        TexMgr_SetTexture(text + 1, lbl_806DA9EC[0]);
        fn_801F93EC(text + 2, lbl_803BE55C[2], lbl_803BE55C[3]);
        TexMgr_SetTexture(text + 2, lbl_806DA9EC[1]);
    }
}
