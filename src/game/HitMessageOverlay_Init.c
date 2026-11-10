/* HitMessageOverlay_Init: one-shot overlay state reset, allocates the two
 * TweenInterp objects and preloads the overlay sprites.
 * TweenInterp_Dtor: deleting destructor (TweenInterp -> TweenBase). */

#include "game/types/TweenInterp.h"

extern char FlowFader_vtable_80419DC8[];      /* TweenBase vtable */
extern char lbl_80419DE0[];      /* TweenInterp vtable */

extern unsigned char HitMessageOverlay_bss_806D1478;
extern unsigned char lbl_806CF270;
extern int HitMessageOverlay_data_806CF274;
extern int HitMessageOverlay_data_806CF278;
extern int HitMessageOverlay_bss_806D147C;
extern int HitMessageOverlay_bss_806D1480;
extern float HitMessageOverlay_bss_806D1484;
extern float HitMessageOverlay_bss_806D1488;
extern TweenInterp *HitMessageOverlay_bss_806D148C;
extern TweenInterp *HitMessageOverlay_bss_806D1490;

extern const float lbl_806D4E90; /* 0.0 */
extern const float lbl_806D4EE0; /* 0.2 */

extern void *Alloc(unsigned long size);
extern void PreloadResource(int id);
extern void MemoryManager_TimedFree(void *p);

static inline TweenInterp *TweenInterp_New(void)
{
    TweenInterp *t = (TweenInterp *)Alloc(sizeof(TweenInterp));
    if (t != 0) {
        t->vtable = FlowFader_vtable_80419DC8;
        t->from = 0;
        t->to = 0;
        t->vtable = lbl_80419DE0;
        t->t = lbl_806D4E90;
        t->value = lbl_806D4E90;
        t->speed = lbl_806D4E90;
    }
    return t;
}

int HitMessageOverlay_Init(void);
TweenInterp *TweenInterp_Dtor(TweenInterp *self, short flag);

/* extab order differs from .text order (dtor entry first), so both
 * entries are emitted manually (.extab_user -> extab via objcopy). */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TweenInterp_Dtor[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_HitMessageOverlay_Init[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; const void *extab; } extabindex_HitMessageOverlay_Init = {
    (void *)&HitMessageOverlay_Init, 0x00000110, extab_HitMessageOverlay_Init
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; const void *extab; } extabindex_TweenInterp_Dtor = {
    (void *)&TweenInterp_Dtor, 0x0000005C, extab_TweenInterp_Dtor
};

#pragma exceptions off
int HitMessageOverlay_Init(void)
{
    if (HitMessageOverlay_bss_806D1478 == 1) {
        return 0;
    }
    lbl_806CF270 = 1;
    HitMessageOverlay_bss_806D1478 = 1;
    HitMessageOverlay_data_806CF274 = -1;
    HitMessageOverlay_data_806CF278 = -1;
    HitMessageOverlay_bss_806D147C = 0;
    HitMessageOverlay_bss_806D1480 = 0;
    HitMessageOverlay_bss_806D1484 = lbl_806D4E90;
    HitMessageOverlay_bss_806D1488 = lbl_806D4EE0;
    HitMessageOverlay_bss_806D148C = TweenInterp_New();
    HitMessageOverlay_bss_806D1490 = TweenInterp_New();
    PreloadResource(0xC6C);
    PreloadResource(0xC6D);
    PreloadResource(0xC6E);
    return 1;
}

TweenInterp *TweenInterp_Dtor(TweenInterp *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_80419DE0;
        if (self != 0) {
            self->vtable = FlowFader_vtable_80419DC8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
