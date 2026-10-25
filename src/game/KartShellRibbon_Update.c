/* KartShellRibbon_Update (0x800B3AA8): on its first tick it picks the
 * ribbon texture pair for the owner's player slot, from the cab/camera
 * state in arcade mode or from the PCB slot flags in mode 2. It falls back
 * to slot 6, preloads both textures and installs the draw callback. On
 * finish it releases them. */
#include "game/DrawEffectAccess.h"

typedef struct RibbonTexIds { int id[4]; } RibbonTexIds;

extern RibbonTexIds lbl_803292E0;
extern int g_gameMode;
extern unsigned char g_playerData[];
extern unsigned char g_namCamFlag;
extern unsigned char GetVBlankFlag(void);
extern unsigned char VBlankValue_Get(void);
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);
extern int fn_80231BD4(int slot, int character, int alt);
extern void PreloadResource(int id);
extern void fn_80120A08(int id);
extern void KartShellRibbon_DrawCb(unsigned char *self);

void KartShellRibbon_Update(unsigned char *self)
{
    if (!STATE) {
        unsigned char *driver = P(0x11C);
        RibbonTexIds tex;
        int slot;

        I(0x170) = -1;
        I(0x174) = -1;
        tex = lbl_803292E0;
        slot = *(int *)(driver + 0x1F4);
        if (g_gameMode == 0) {
            if (GetVBlankFlag() && VBlankValue_Get() != 1 && g_playerData[0x19D] != 0 &&
                g_namCamFlag != 0 && slot != 6) {
                I(0x170) = fn_80231BD4(slot, *(int *)(driver + 0x1F8), 0);
                I(0x174) = tex.id[slot];
            }
        } else if (g_gameMode == 2) {
            if (slot != 6 && ((PcbSlot_GetByIndex(slot)[3] >> 5) & 1)) {
                I(0x170) = fn_80231BD4(slot, *(int *)(driver + 0x1F8), 1);
                I(0x174) = tex.id[slot];
            }
        }
        if (I(0x170) == -1 && I(0x174) == -1) {
            I(0x170) = fn_80231BD4(6, *(int *)(driver + 0x1F8), 0);
            I(0x174) = -1;
        }
        if (I(0x170) != -1) {
            PreloadResource(I(0x170));
        }
        if (I(0x174) != -1) {
            PreloadResource(I(0x174));
        }
        *(void (**)(unsigned char *))(self + 0x78) = KartShellRibbon_DrawCb;
        P(0x7C) = self;
        STATE++;
    }

    if (FINISHED) {
        if (I(0x170) != -1) {
            fn_80120A08(I(0x170));
        }
        if (I(0x174) != -1) {
            fn_80120A08(I(0x174));
        }
        DrawEffect_Free(self);
    }
}
