/* Native reconstruction of the indivisible 801F2B70 EH group.
 * Several methods remain non-exact; keep NonMatching.
 * The root cleanup uses dtor_8007D0D4 via the per-TU EH name bridge. */
#include "game/NamCamFlow_private.h"
#include "game/NamCamFlow_layout_private.h"

extern "C" void fn_801F2B70(NamCamFlow *self) {
    if (!self->finished) {
        fn_8011F994(0);
        if (self->camera == 1) fn_801F43F8(self->capture->image.p);
        fn_8011FAB8();
    }
}

/* Update calls this method out of line in the target. */
#pragma auto_inline off
extern "C" void fn_801F3198(NamCamFlow *self) {
    ResCtrl rc;
    if (self->camera == 1) {
        fn_80121E10(&rc);
        int japanese = isJapanese();
        int resource = 0x1A8;
        if (!japanese) resource = 0x50E;
        rc.resId = resource;
        rc.Show(kNamCamConfirm[0], kNamCamConfirm[1], lbl_806DA590);
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

#pragma auto_inline reset

extern "C" void fn_801F38DC(VObject *p) { delete p; }

static inline void NamCamAddCountdown(FlowSceneList *list, int id, int number) {
    fn_801F4DF0(list, new NamCamCountdown(id, number), 0);
}

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
            NamCamAddCountdown(self->list, id, number);
            FlowTask *task = fn_801F4DC0(self->list, id);
            if (task) {
                NamCamCountdown *counter = (NamCamCountdown *)fn_80271340(task, 0, lbl_806D0028, lbl_806D0020, 0);
                counter->x = lbl_806DA5CC;
                counter->y = lbl_806DA5D0;
            }
            NamCamAddCountdown(self->list, id + 1, number);
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
    rc.resId = kNamCamIcons[self->player][role];
    rc.Show(lbl_806DA588, lbl_806DA598, lbl_806DA590);
    rc.SetScale(0.75f);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    int japanese = isJapanese();
    int resource = 0x1A9;
    if (!japanese) resource = 0x50F;
    rc.resId = resource;
    rc.Show(kNamCamLabels[0], kNamCamLabels[1], lbl_806DA590);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    if (isJapanese() == 0) resource = kNamCamPlayerLabels[player][0];
    else resource = kNamCamPlayerLabels[player][1];
    rc.resId = resource;
    rc.Show(kNamCamLabels[2], kNamCamLabels[3], lbl_806DA590);
    fn_8011FAFC(&rc, 1);
    fn_80121E10(&rc);
    if (isJapanese() == 0) rc.resId = kNamCamModes[self->player][0];
    else rc.resId = kNamCamModes[self->player][1];
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
    rc.SetColor(__rlwimi(0xFFFFFF00, self->fade.p->Value(), 0, 24, 31));
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
    /* Normal array destruction uses the global array-delete runtime. */
    ::delete[] text;
    fn_80120A08(0x50B);
    fn_80120A08(0x50C);
    fn_80120A08(0x68C);
    if (!isJapanese()) {
        fn_80120A08(0x50D);
        fn_80120A08(kNamCamModes[player][0]);
        fn_80120A08(kNamCamIcons[player][0]);
    } else {
        fn_80120A08(0x1A7);
        fn_80120A08(kNamCamModes[player][1]);
        fn_80120A08(kNamCamIcons[player][1]);
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
/* The separate FP/GPR argument banks preserve fn_801F93EC's ABI. */
extern "C" void NamCamText_SetPosition(float x, float y, TextManager *text);

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
        PreloadResource(kNamCamModes[whichPlayer][0]);
        PreloadResource(kNamCamIcons[whichPlayer][0]);
    } else {
        PreloadResource(0x1A7);
        PreloadResource(kNamCamModes[whichPlayer][1]);
        PreloadResource(kNamCamIcons[whichPlayer][1]);
    }
    text = new NamCamText[3];
    text->visible = 1;
    fn_801F93EC(text, lbl_806DA570[0], lbl_806DA570[1]);
    if (Sci2Card_GetByteFlag1224()) fn_801F9014(text, g_playerData);
    else TexMgr_SetTexture(text, lbl_806DA5AC);
    text[1].color = 0xFFFFFFBF;
    fn_801F93D0(text + 1, lbl_806DA5B0, lbl_806DA5B0);
    text[2].color = 0xFFFFFFBF;
    fn_801F93D0(text + 2, lbl_806DA5B0, lbl_806DA5B0);
    if (!isJapanese()) {
        NamCamText_SetPosition(kNamCamEnglish[0], kNamCamEnglish[1], text + 1);
        TexMgr_SetTexture(text + 1, lbl_806DA94C[0]);
        fn_801F93EC(text + 2, kNamCamEnglish[2], kNamCamEnglish[3]);
        TexMgr_SetTexture(text + 2, lbl_806DA94C[1]);
    } else {
        NamCamText_SetPosition(kNamCamJapanese[0], kNamCamJapanese[1], text + 1);
        TexMgr_SetTexture(text + 1, lbl_806DA9EC[0]);
        fn_801F93EC(text + 2, kNamCamJapanese[2], kNamCamJapanese[3]);
        TexMgr_SetTexture(text + 2, lbl_806DA9EC[1]);
    }
}

#include "game/NamCamFlow_missing_private.h"

NamCamList::~NamCamList() {
    fn_801F4D3C((FlowSceneList *)this);
    entries.EraseAll();
}
NamCamListImpl::~NamCamListImpl() {
    fn_801F4D3C((FlowSceneList *)this);
}

static inline void NamCamDrawBorders() {
        ResCtrl rc;
        rc.mode = 2;
        rc.SetSize(lbl_806DA580, lbl_806DA584);
        rc.Show(lbl_806DA588, lbl_806DA58C, lbl_806DA590);
        rc.SetColor(0x1BFFFF);
        fn_8011FAFC(&rc, 0);
        const float (*a)[2] = NamCamFlow_rodata_803BE3C4;
        const float (*b)[2] = NamCamFlow_rodata_803BE3E4;
        for (int i = 0; i < 4; ++i, ++a, ++b) {
            fn_80121E10(&rc);
            rc.resId = 0x50B;
            rc.Show(a[0][0], a[0][1], lbl_806DA590);
            fn_8011FAFC(&rc, 0);
            fn_80121E10(&rc);
            rc.resId = 0x50C;
            float y, x;
            x = b[0][0];
            y = b[0][1];
            rc.Show(x, y, lbl_806DA590);
            fn_8011FAFC(&rc, 0);
        }
    }

static inline void NamCamCopyCapture(NamCamFlow *self) {
        if (self->camera == 1) {
            GX_BeginDraw();
            GXTexModeSync();
            int width = lbl_80598A60.width;
            int height = lbl_80598A60.height;
            void *context = GetDisplayContext(GetDisplayBufferIndex());
            DrawNamCamImage(context,
                self->capture->buffers.p->pixels, 320, 240, 6,
                (unsigned short)((int)lbl_806DA5B4 - width),
                (unsigned short)((int)lbl_806DA5B8 - height),
                (unsigned short)((int)lbl_806DA5BC - width),
                (unsigned short)((int)lbl_806DA5C0 - height), 128, 128, 4);
            GX_EndDraw(0);
            if (self->camera == 1) ResetIOPorts();
        }
}

extern "C" void fn_801F2BC8(NamCamFlow *self) {
    if (self->finished) return;
    NamCamPlayerInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    NamCamSyncState *sync;
    switch (self->state) {
    case 0:
        sync = fn_801DAEC0();
        sync->state = 1;
        self->fade->Step();
        if (self->fade->Done()) self->state = 1;
        break;
    case 1:
        fn_801F32BC(self);
        break;
    case 2:
        sync = fn_801DAEC0();
        sync->state = 4;
        self->fade->Step();
        if (self->fade->Done()) {
            self->timer = lbl_806DA858;
            self->state = 3;
            self->color = 0;
        }
        break;
    case 3:
        sync = fn_801DAEC0();
        sync->state = 0;
        if (self->timer > 0) --self->timer;
        if (input->Pressed(0x2500) || self->timer <= 0) {
            SetSyncTarget(20);
            self->state = 4;
        }
        break;
    case 4:
        if (IsSyncReached()) self->state = 5;
        break;
    case 5:
        NamCamCopyCapture(self);
        self->fade->Set(0, 255, 22);
        self->state = 6;
        break;
    case 6:
        self->fade->Step();
        if (self->fade->Done()) self->state = 7;
        break;
    case 7:
        self->finished = 1;
        self->state = -1;
        break;
    }
    NamCamDrawBorders();
    fn_801F36D0(self);
    fn_801F3198(self);
    if (self->state >= 0 && self->state <= 2) {
        NamCamCapture *capture = self->capture;
        if (!NamCamFlow_bss_806D1964) { NamCamFlow_bss_806D1960 = 0; NamCamFlow_bss_806D1964 = 1; }
        if (NamCamFlow_bss_806D1960 > 0) --NamCamFlow_bss_806D1960;
        if (NamCamFlow_bss_806D1960 <= 0) {
            void *handle;
            unsigned char descriptor[12];
            if (NamCam_GetImageHandle(&handle, 0) == 1) {
                if (NamCam_LoadImage(handle, capture->pixels, descriptor) == 1) {
                    NamCamBuffers *buffer = capture->buffers.p;
                    void *pixels = capture->pixels;
                    memcpy(buffer->descriptor, descriptor, 12);
                    memcpy(buffer->pixels, pixels, buffer->size);
                    buffer = capture->buffers.p;
                    NamCamImage *image = capture->image.p;
                    pixels = buffer->pixels;
                    unsigned short *size = (unsigned short *)buffer->descriptor;
                    DCFlushRange(pixels, GXGetTexBufferSize(size[2], size[3], 6, 0, 0));
                    GXInitTexObj(image->texture, pixels, size[2], size[3],
                        6, 0, 0, 0);
                    GXInitTexObjLOD(image->texture, 0, 0,
                        lbl_806DA59C, lbl_806DA59C, lbl_806DA59C, 0, 0, 0);
                    image->ready = 1;
                }
                capture->ready = 1;
            }
            NamCamFlow_bss_806D1960 = 0;
        }
    }
    self->list->Update();
    ResCtrl overlay;
    unsigned int color = self->color | (unsigned char)self->fade->Value();
    fn_80121E10(&overlay);
    overlay.mode = 2;
    overlay.SetSize(lbl_806DA580, lbl_806DA584);
    overlay.Show(lbl_806DA588, lbl_806DA58C, lbl_806DA590);
    overlay.SetColor(color);
    fn_8011FAFC(&overlay, 7);
}

extern "C" void fn_801F43F8(NamCamImage *self) {
    if (!self->ready) return;
    float width = lbl_80598A60.width;
    float height = lbl_80598A60.height;
    int left = (int)(16.0f - width);
    int right = (int)(16.0f + width);
    int top = (int)(12.0f - height);
    int bottom = (int)(12.0f + height);
    int x0 = (int)(305.0f + (float)-(160 - left));
    int x1 = (int)(305.0f + (float)(160 - right));
    int y0 = (int)(140.0f + (float)-(120 - top));
    int y1 = (int)(140.0f + (float)(120 - bottom));
    int u0 = (int)(0.8f * (float)left);
    int u1 = (int)(0.8f * (lbl_806DA588 - (float)right));
    int v0 = (int)(1.0666667f * (float)top);
    int v1 = (int)(1.0666667f * (lbl_806DA58C - (float)bottom));
    NamCamFlow_data_804E52E0[0] = x0; NamCamFlow_data_804E52E0[1] = y0;
    NamCamFlow_data_804E52E0[2] = x1; NamCamFlow_data_804E52E0[3] = y0;
    NamCamFlow_data_804E52E0[4] = x1; NamCamFlow_data_804E52E0[5] = y1;
    NamCamFlow_data_804E52E0[6] = x0; NamCamFlow_data_804E52E0[7] = y1;
    NamCamFlow_data_804E52C0[0] = u0; NamCamFlow_data_804E52C0[1] = v0;
    NamCamFlow_data_804E52C0[2] = u1; NamCamFlow_data_804E52C0[3] = v0;
    NamCamFlow_data_804E52C0[4] = u1; NamCamFlow_data_804E52C0[5] = v1;
    NamCamFlow_data_804E52C0[6] = u0; NamCamFlow_data_804E52C0[7] = v1;
    fn_801F6804(self->display.p);
    fn_801F6588(0);
    GXSetZCompLoc(0);
    GXSetZMode(0, 7, 1);
    GXLoadTexObj(self->texture, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 255);
    GXSetTevOp(0, 3);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(0, 9, 0, 3, 0);
    GXSetVtxAttrFmt(0, 13, 1, 2, 8);
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(13, 2);
    GXSetArray(13, NamCamFlow_data_804E52C0, 4);
    GXBegin(128, 0, 4);
    short halfHeight, halfWidth;
    halfWidth = (short)(lbl_806DA594 * NamCamFlow_data_806D0014);
    halfHeight = (short)(lbl_806DA5F8 * NamCamFlow_data_806D0014);
    short x = NamCamFlow_data_806D0010, y = NamCamFlow_data_806D0012;
    NamCamPosition(x - halfWidth, y - halfHeight); NamCamTexCoord(0);
    NamCamPosition(halfWidth + x, y - halfHeight); NamCamTexCoord(1);
    NamCamPosition(halfWidth + x, halfHeight + y); NamCamTexCoord(2);
    NamCamPosition(x - halfWidth, halfHeight + y); NamCamTexCoord(3);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    fn_801F6790(self->display.p);
}
