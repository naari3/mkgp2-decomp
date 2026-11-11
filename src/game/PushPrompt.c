#include "game/types/c_region.h"
C_REGION_BEGIN
/* clCSPartsMsgWindow: real six-slot sprite-parts descendant with the
 * additional message callback. Compiler-emitted RTTI/vtable and original
 * text-buffer initializer belong to this unit. Deferred definitions are
 * in reverse address order. */
C_REGION_END
#pragma cplusplus on

typedef struct { char c[256]; } TextBuf;
#ifdef __MWERKS__
typedef struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;
extern "C" void *__va_arg(va_list v_list, int type);
#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_end(ap) ((void)0)
#else
#include <stdarg.h>
#endif

extern "C" {
extern char lbl_8048EB44[];
extern char PushPrompt_vtable_8048ED34[];
extern const TextBuf PushPrompt_rodata_803607A8 = { {0} };
extern const float lbl_806D7998, lbl_806D799C, lbl_806D79A0, lbl_806D79A4;
extern const float lbl_806D79A8, lbl_806D79AC, lbl_806D79B0, lbl_806D79B4;
extern const float lbl_806D79B8, lbl_806D79BC, lbl_806D79C0, lbl_806D79C4;
extern const float lbl_806D79C8, lbl_806D79CC, lbl_806D79D0, lbl_806D79D4;
extern const float lbl_806D79D8, lbl_806D79DC, lbl_806D79E0, lbl_806D79E4;
extern const float lbl_806D79E8, lbl_806D79EC, lbl_806D79F0, lbl_806D79F4;
extern const float lbl_806D79F8, lbl_806D79FC, lbl_806D7A00, lbl_806D7A04;
extern const float lbl_806D7A08, lbl_806D7A0C, lbl_806D7A10;
#ifdef __MWERKS__
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_8016918C(void *, int, float, float, float, float, float, float, float, float, int);
static inline void fn_8016918C_Reordered(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a) { fn_8016918C((void *)obj, id, x, y, sx, sy, r, g, b, a, flag); }
#define fn_8016918C fn_8016918C_Reordered
#endif
#ifdef __MWERKS__
extern void fn_80169334(void *obj, int id, int flag, float x, float y, float sx, float sy, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169334(void *, int, float, float, float, float, float, int);
static inline void fn_80169334_Reordered(void *obj, int id, int flag, float x, float y, float sx, float sy, float a) { fn_80169334((void *)obj, id, x, y, sx, sy, a, flag); }
#define fn_80169334 fn_80169334_Reordered
#endif
extern void fn_801681E8(void *obj, const char *text, float x, float y, float sx, float sy, float r, float g, float b, float a, ...);
extern int vsprintf(char *buf, const char *fmt, va_list args);
extern void fn_80167440(void *p);
extern void fn_801673A8(void *p);
extern void fn_801674AC(void *p);
extern void fn_801675A4(void *p);
extern void fn_801676AC(void *p, int flag);
extern void fn_80120A08(int id);
extern void SetRumbleMode(unsigned int ch, unsigned int mode, int duration);
}

#include "game/types/InputPlayer.h"

extern "C" {
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *, int);
}

struct clCSPartsMsgWindow;



#include "game/types/clCSPartsMsgWindow.h"

#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))

clCSPartsMsgWindow::clCSPartsMsgWindow() {
    state = 0;
    t = 0.0f;
    anim = new SpriteAnim(0);
    px = lbl_806D7A0C;
    py = lbl_806D7A10;
    sx = 0.0f;
    sy = 0.0f;
    px2 = lbl_806D7A0C;
    py2 = lbl_806D7A10;
    sx2 = 0.0f;
    sy2 = 0.0f;
    fade = 0.0f;
}

clCSPartsMsgWindow::~clCSPartsMsgWindow() {
    fn_80120A08(0x57F);
    fn_801676AC(anim, 1);
}

void clCSPartsMsgWindow::Put(int id, int flag, float x, float y, float w, float h, float r, float g, float b, float a) {
    fn_8016918C((void *)obj, id, flag, x * sx + px, y * sy + py, w * sy, h * sy, r, g, b, a * fade);
}

void clCSPartsMsgWindow::Print(float x, float y, float w, float h, float r, float g, float b, float a, const char *fmt, ...) {
    va_list args;
    TextBuf buf = PushPrompt_rodata_803607A8;
    va_start(args, fmt);
    vsprintf(buf.c, fmt, args);
    fn_801681E8((void *)obj, buf.c, x * sx + px, y * sy + py, w * sy, h * sy, r, g, b, a * fade);
}

void clCSPartsMsgWindow::Update()
{
    clCSPartsMsgWindow *self = this;
    float k;

    if (self->state == 3) {
        return;
    }
    self->t += 1.0f;
    switch (self->state) {
    case 0:
        if (self->t < 10.0f) {
            k = 0.1f * self->t;
            self->px2 = 20.0f * k;
            self->py2 = 20.0f * k;
            self->px = 0.0f;
            self->py = 0.0f;
            self->sx2 = LERP(1.1f, 2.0f, k);
            self->sy2 = LERP(0.35f, 0.63f, k);
            self->sx = LERP(0.4f, 1.1f, k);
            self->sy = LERP(0.4f, 1.1f, k);
        } else {
            k = 0.2f * (self->t - 10.0f);
            self->px2 = 20.0f - 20.0f * k;
            self->py2 = 20.0f - 20.0f * k;
            self->px = 0.0f;
            self->py = 0.0f;
            self->sx2 = LERP(2.0f, 1.8f, k);
            self->sy2 = LERP(0.63f, 0.57f, k);
            self->sx = LERP(1.1f, 1.0f, k);
            self->sy = LERP(1.1f, 1.0f, k);
        }
        self->fade = 1.0f;
        if (self->t >= 15.0f) {
            self->state = 1;
            self->t = 0.0f;
            fn_80167440(self->anim);
        }
        break;
    case 1:
        self->px = 0.0f;
        self->py = 0.0f;
        self->px2 = 0.0f;
        self->py2 = 0.0f;
        self->sx2 = 1.8f;
        self->sy2 = 0.57f;
        self->sx = 1.0f;
        self->sy = 1.0f;
        self->fade = 1.0f;
        if (self->t >= 180.0f || InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x100) ||
            InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x2000)) {
            self->state = 2;
            self->t = 0.0f;
            fn_801673A8(self->anim);
            SetRumbleMode(0, 1, 1);
        }
        break;
    case 2:
        if (self->t < 5.0f) {
            k = 0.2f * self->t;
            self->px2 = 20.0f * k;
            self->py2 = 20.0f * k;
            self->px = 0.0f;
            self->py = 0.0f;
            self->sx2 = LERP(1.8f, 2.0f, k);
            self->sy2 = LERP(0.57f, 0.63f, k);
            self->sx = LERP(1.0f, 1.1f, k);
            self->sy = LERP(1.0f, 1.1f, k);
        } else {
            k = 0.1f * (self->t - 5.0f);
            self->px2 = 20.0f - 20.0f * k;
            self->py2 = 20.0f - 20.0f * k;
            self->px = 0.0f;
            self->py = 0.0f;
            self->sx2 = LERP(2.0f, 0.0f, k);
            self->sy2 = LERP(0.63f, 0.0f, k);
            self->sx = LERP(1.1f, 0.0f, k);
            self->sy = LERP(1.1f, 0.0f, k);
        }
        self->fade = 1.0f - (1.0f / 15.0f) * self->t;
        if (self->t >= 15.0f) {
            self->state = 3;
            self->t = 0.0f;
            self->active = 1;
        }
        break;
    }
    self->px += 320.0f;
    self->py += 262.0f;
    self->px2 += 320.0f;
    self->py2 += 262.0f;
}

void clCSPartsMsgWindow::Draw() {
    if (state != 3) {
        fn_80169334((void *)obj, 0x57F, 0, px, py, sx, sy, fade);
        m20();
        fn_801675A4(anim);
    }
}

void clCSPartsMsgWindow::m1C() {
    fn_801674AC(anim);
}

void clCSPartsMsgWindow::m20() {
}
