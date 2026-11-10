/*
 * 0x8020AF08..0x8020B4F8: item showcase (spinning item model / shell
 * effect with a sparkle animation set) shown on the item get screen.
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
void operator delete(void *p) throw();

#include "game/types/ShowModel.h"

#include "game/types/ShowShellA.h"

#include "game/types/ShowShellB.h"

#include "game/types/ShowAnim.h"

#include "game/types/ShowXform.h"

extern "C" {
extern int g_humanPlayerCount;
extern const float lbl_806DAC08;
extern const float lbl_806DAC0C;
extern const float lbl_806DAC10;
extern const float lbl_806DAC14;
extern const float lbl_806DAC18;
extern const float lbl_806DAC1C;
extern const float lbl_806DAC20;
extern const float lbl_806DAC30;
extern const float lbl_806DAC34;
extern const float lbl_806DAC38;
extern const float lbl_806DAC3C;

void fn_8011FAB8(void);
void fn_80120A08(int res);
void PreloadResource(int res);
void *ItemRes_LookupByKey_Thunk(int key);
void fn_80169334(int a, int res, int b, float x, float y, float sx, float sy, float alpha);
void fn_8013D4B0(ShowModel *m, float alpha);
void fn_8013D50C(ShowModel *m, float r, float g, float b, float alpha);
void fn_8013D59C(ShowModel *m, float x, float y, float z);
void fn_8013D608(ShowModel *m, float x, float y, float z);
void fn_8013D634(ShowModel *m, float x, float y, float z);
void fn_8013D660(ShowModel *m, float x, float y);
void fn_8013D738(ShowModel *m, float a, float b);
void fn_8013D940(int layer);
void fn_8013DA00(void);
void fn_8013DAC8(ShowModel *m, int layer);
void fn_8013DB9C(void);
void fn_8013DBF8(void);
ShowXform *fn_8013BE98(int item);
void fn_8014D1E0(ShowShellA *s, float alpha);
void fn_8014D250(ShowShellA *s);
void fn_8014D2AC(ShowShellA *s);
void fn_8014CEE8(ShowShellB *s, float alpha);
void fn_8014CF44(ShowShellB *s);
void fn_8014CFA0(ShowShellB *s);
void fn_8013AB74(ShowAnim *a, int layer, int frame);
void fn_8013AE20(ShowAnim *a, float x, float y, float alpha);
void fn_8013B300(ShowAnim *a, int frame);
void fn_8013B4FC(ShowAnim *a, int frame);
void fn_8013B7A8(ShowAnim *a, ShowAnim *next);
}

#include "game/types/ItemShowcase.h"

struct ShowAnimCommand {
    int op, frames;
    float x, y, sx, sy, angle, r, g, b, alpha;
};

/* Separate programs share the compiler-generated section base. */
static const ShowAnimCommand sparkleA[9] = {
    {1, 45, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 241.0f, 156.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 5, 241.0f, 156.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {2, 15, 241.0f, 156.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f},
    {1, 10, 241.0f, 156.0f, 1.5f, 1.5f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 368.0f, 166.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 5, 368.0f, 166.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {2, 15, 368.0f, 166.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f},
    {5, 0, 368.0f, 166.0f, 1.5f, 1.5f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
};

static const ShowAnimCommand sparkleB[19] = {
    {1, 55, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 438.0f, 60.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 5, 438.0f, 60.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {2, 15, 438.0f, 60.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f},
    {1, 30, 438.0f, 60.0f, 1.5f, 1.5f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 10, 350.0f, 100.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 30, 350.0f, 100.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {1, 20, 350.0f, 100.0f, 2.0f, 2.0f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 360.0f, 166.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 10, 360.0f, 166.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {1, 13, 360.0f, 166.0f, 2.0f, 2.0f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 278.0f, 60.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 10, 278.0f, 60.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {1, 3, 278.0f, 60.0f, 2.0f, 2.0f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 368.0f, 166.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 10, 368.0f, 166.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {1, 4, 368.0f, 166.0f, 2.0f, 2.0f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {3, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};

static const ShowAnimCommand sparkleC[11] = {
    {1, 65, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 241.0f, 130.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 5, 241.0f, 130.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {2, 15, 241.0f, 130.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f},
    {1, 20, 241.0f, 130.0f, 1.5f, 1.5f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {1, 15, 241.0f, 130.0f, 1.5f, 1.5f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {2, 10, 270.0f, 176.0f, 0.300000012f, 0.300000012f, -1.57079637f, 1.0f, 1.0f, 1.0f, 0.5f},
    {2, 30, 270.0f, 176.0f, 1.0f, 1.0f, -0.52359879f, 1.0f, 1.0f, 1.0f, 1.0f},
    {1, 20, 270.0f, 176.0f, 2.0f, 2.0f, 1.57079637f, 1.0f, 1.0f, 1.0f, 0.0f},
    {3, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};

ItemShowcase::ItemShowcase(int t) {
    timer = 0;
    itemId = 0;
    model = 0;
    loaded = false;
    glow = lbl_806DAC10;
    alpha = lbl_806DAC10;
    shellA = 0;
    shellB = 0;
    anim = 0;
    itemId = g_humanPlayerCount;
    if (itemId <= 0) {
        return;
    }
    timer = t;
    glow = lbl_806DAC10;
    fn_8013DBF8();
    int id = itemId;
    if (id == 0x9B) {
        shellA = new ShowShellA(7, lbl_806DAC18, lbl_806DAC30, lbl_806DAC34);
        fn_8014D1E0(shellA, alpha);
    } else if (id == 0x9D) {
        shellB = new ShowShellB(7, lbl_806DAC18, lbl_806DAC30, lbl_806DAC34);
        fn_8014CEE8(shellB, alpha);
    } else {
        ShowXform *xf = fn_8013BE98(id);
        model = new ShowModel(ItemRes_LookupByKey_Thunk(itemId), 1);
        fn_8013D738(model, lbl_806DAC10, lbl_806DAC14);
        fn_8013D660(model, lbl_806DAC18, lbl_806DAC30);
        fn_8013D634(model, lbl_806DAC34 * xf->pos[0], lbl_806DAC34 * xf->pos[1], lbl_806DAC34 * xf->pos[2]);
        fn_8013D59C(model, lbl_806DAC38 * xf->rot[0], lbl_806DAC38 * xf->rot[1], lbl_806DAC38 * xf->rot[2]);
        float s = lbl_806DAC34 * xf->scale;
        fn_8013D608(model, s, s, s);
        if (itemId == 0x81) {
            fn_8013D50C(model, lbl_806DAC3C, lbl_806DAC3C, lbl_806DAC3C, alpha);
        } else {
            fn_8013D4B0(model, alpha);
        }
    }
    PreloadResource(0xBFF);
    loaded = true;
    PreloadResource(0x96A);
    anim = new ShowAnim(0x96A, 0, 1, sparkleA, 0);
    fn_8013B7A8(anim, new ShowAnim(0x96A, 0, 1, sparkleB, 0));
    fn_8013B7A8(anim, new ShowAnim(0x96A, 0, 1, sparkleC, 0));
    fn_8013B4FC(anim, -1);
}
