#include "game/types/text_word.h"
#include "game/types/c_region.h"
C_REGION_BEGIN

/* sdata symbols referenced from asm */
/* === extracted from auto_CardTaskManager_Rend_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned char lbl_806D3290[], lbl_806D3294[], lbl_806D3298[], lbl_806D32A0[], lbl_806D32A4[];
/* owned pool .rodata 0x80312850..0x80312DEC (tools/data2c.py) */
#pragma force_active on
extern const char Card_rodata_80312850[12] = "CHECKING...";
static const char *const lbl_8031285C[6] = {
    (const char *)lbl_806D3290, Card_rodata_80312850, (const char *)lbl_806D3294,
    (const char *)lbl_806D3298, (const char *)lbl_806D3290, (const char *)lbl_806D3290
};
extern const unsigned int data_803FE480_rodata_80312874[4] = { TEXT_WORD(0x97, '\\', 0x91, 'z'), TEXT_WORD(0x82, 0xB5, 0x82, 0xC8), TEXT_WORD(0x82, 0xA2, 0x97, 0xE1), TEXT_WORD(0x8A, 'O', 0, 0) };
extern const char lbl_80312884[] = "Program error";
extern const unsigned int data_803FE480_rodata_80312894[9] = { TEXT_WORD(0x83, 'n', 0x83, 0x93), TEXT_WORD(0x83, 'h', 0x83, 0x8B), TEXT_WORD(0x82, 0xC9, 0x8E, 0xE8), TEXT_WORD(0x82, 0xF0, 0x90, 'G'), TEXT_WORD(0x82, 0xEA, 0x82, 0xC8), TEXT_WORD(0x82, 0xA2, 0x82, 0xC5), TEXT_WORD(0x82, 0xAD, 0x82, 0xBE), TEXT_WORD(0x82, 0xB3, 0x82, 0xA2), 0x00000000 };
extern const char lbl_803128B8[] = "Do not touch wheel";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803128CC[6] = { TEXT_WORD(0x8C, 'W', 0x88, 0xF5), TEXT_WORD(0x82, 0xF0, 0x8C, 0xC4), TEXT_WORD(0x82, 0xF1, 0x82, 0xC5), TEXT_WORD(0x82, 0xAD, 0x82, 0xBE), TEXT_WORD(0x82, 0xB3, 0x82, 0xA2), 0x00000000 };
extern const char lbl_803128E4[] = "Please call an attendant";
extern const unsigned int data_803FE480_rodata_80312900[7] = { TEXT_WORD(0x83, 'n', 0x83, 0x93), TEXT_WORD(0x83, 'h', 0x83, 0x8B), TEXT_WORD(0x82, 0xC9, 0x88, 0xD9), TEXT_WORD(0x8F, 0xED, 0x82, 0xAA), TEXT_WORD(0x82, 0xA0, 0x82, 0xE8), TEXT_WORD(0x82, 0xDC, 0x82, 0xB7), 0x00000000 };
extern const char lbl_8031291C[] = "Wheel error";
extern const char lbl_80312928[] = "JVS I/O ERROR";
extern const unsigned int data_803FE480_rodata_80312938[8] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'e', 0x83, 0x80), TEXT_WORD(0x83, '{', 0x83, '^'), TEXT_WORD(0x83, 0x93, 0x82, 0xC9), TEXT_WORD(0x88, 0xD9, 0x8F, 0xED), TEXT_WORD(0x82, 0xAA, 0x82, 0xA0), TEXT_WORD(0x82, 0xE8, 0x82, 0xDC), TEXT_WORD(0x82, 0xB7, 0, 0) };
extern const char lbl_80312958[] = "Item button Error";
extern const unsigned int data_803FE480_rodata_8031296C[10] = { TEXT_WORD(0x91, 0xCE, 0x90, 0xED), TEXT_WORD(0x83, 'L', 0x83, 0x83), TEXT_WORD(0x83, 0x93, 0x83, 'Z'), TEXT_WORD(0x83, 0x8B, 0x83, '{'), TEXT_WORD(0x83, '^', 0x83, 0x93), TEXT_WORD(0x82, 0xC9, 0x88, 0xD9), TEXT_WORD(0x8F, 0xED, 0x82, 0xAA), TEXT_WORD(0x82, 0xA0, 0x82, 0xE8), TEXT_WORD(0x82, 0xDC, 0x82, 0xB7), 0x00000000 };
extern const char lbl_80312994[] = "Versus Cancel button Error";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803129B0[7] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 'R', 0x81), TEXT_WORD('^', 'W', 0x82, 0xCD), TEXT_WORD(0x8E, 'g', 0x97, 'p'), TEXT_WORD(0x82, 0xC5, 0x82, 0xAB), TEXT_WORD(0x82, 0xDC, 0x82, 0xB9), TEXT_WORD(0x82, 0xF1, 0, 0) };
extern const char lbl_803129CC[] = "Card R/W is out of order";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803129E8[15] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'e', 0x83, 0x80), TEXT_WORD(0x83, '{', 0x83, '^'), TEXT_WORD(0x83, 0x93, 0x82, 0xDC), TEXT_WORD(0x82, 0xBD, 0x82, 0xCD), TEXT_WORD(0x91, 0xCE, 0x90, 0xED), TEXT_WORD(0x83, 'L', 0x83, 0x83), TEXT_WORD(0x83, 0x93, 0x83, 'Z'), TEXT_WORD(0x83, 0x8B, 0x83, '{'), TEXT_WORD(0x83, '^', 0x83, 0x93), TEXT_WORD(0x82, 0xF0, 0x89, 0x9F), TEXT_WORD(0x82, 0xB5, 0x82, 0xC4), TEXT_WORD(0x82, 0xAD, 0x82, 0xBE), TEXT_WORD(0x82, 0xB3, 0x82, 0xA2), 0x00000000 };
extern const char lbl_80312A24[] = "Press Item button or Versus Cancel button";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312A50[6] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 0x82, 0xAA), TEXT_WORD(0x95, 0xA5, 0x82, 0xA2), TEXT_WORD(0x8F, 'o', 0x82, 0xB3), TEXT_WORD(0x82, 0xEA, 0x82, 0xDC), TEXT_WORD(0x82, 0xB7, 0, 0) };
extern const char lbl_80312A68[] = "Card will be ejected";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312A80[6] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 0x82, 0xF0), TEXT_WORD(0x82, 0xA8, 0x8E, 0xE6), TEXT_WORD(0x82, 0xE8, 0x82, 0xAD), TEXT_WORD(0x82, 0xBE, 0x82, 0xB3), TEXT_WORD(0x82, 0xA2, 0, 0) };
extern const char lbl_80312A98[] = "Take card";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312AA4[9] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 'R', 0x81), TEXT_WORD('^', 'W', 0x82, 0xCC), TEXT_WORD(0x83, 'N', 0x83, 0x8A), TEXT_WORD(0x81, '[', 0x83, 'j'), TEXT_WORD(0x83, 0x93, 0x83, 'O'), TEXT_WORD(0x8E, 0x9E, 0x8A, 0xFA), TEXT_WORD(0x82, 0xC5, 0x82, 0xB7), 0x00000000 };
extern const char lbl_80312AC8[] = "Please clean the card R/W";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312AE4[11] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 'R', 0x81), TEXT_WORD('^', 'W', 0x82, 0xCC), TEXT_WORD(0x83, 'N', 0x83, 0x8A), TEXT_WORD(0x81, '[', 0x83, 'j'), TEXT_WORD(0x83, 0x93, 0x83, 'O'), TEXT_WORD(0x82, 0xF0, 0x8E, 0xC0), TEXT_WORD(0x8D, 's', 0x82, 0xB5), TEXT_WORD(0x82, 0xC4, 0x82, 0xAD), TEXT_WORD(0x82, 0xBE, 0x82, 0xB3), TEXT_WORD(0x82, 0xA2, 0, 0) };
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B10[8] = { TEXT_WORD(0x8B, 'N', 0x93, 0xAE), TEXT_WORD(0x8C, 0xE3, 0x82, 0xC9), TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 0x83, 'N'), TEXT_WORD(0x83, 0x8A, 0x81, '['), TEXT_WORD(0x83, 'j', 0x83, 0x93), TEXT_WORD(0x83, 'O', 0x82, 0xF0), 0x00000000 };
extern const char lbl_80312B30[] = "          Skip";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B40[3] = { TEXT_WORD(0x82, 0xB5, 0x82, 0xC4), TEXT_WORD(0x89, 0xBA, 0x82, 0xB3), TEXT_WORD(0x82, 0xA2, 0, 0) };
extern const char lbl_80312B4C[] = "when activating";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B5C[6] = { TEXT_WORD(0x83, 'J', 0x81, '['), TEXT_WORD(0x83, 'h', 0x83, 'N'), TEXT_WORD(0x83, 0x8A, 0x81, '['), TEXT_WORD(0x83, 'j', 0x83, 0x93), TEXT_WORD(0x83, 'O', 0x82, 0xF0), 0x00000000 };
extern const char lbl_80312B74[] = "Card R/W will be cleaned";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B90[3] = { TEXT_WORD(0x8E, 0xC0, 0x8D, 's'), TEXT_WORD(0x82, 0xB5, 0x82, 0xDC), TEXT_WORD(0x82, 0xB7, 0, 0) };
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B9C[3] = { TEXT_WORD(0x83, 'X', 0x83, 'L'), TEXT_WORD(0x83, 'b', 0x83, 'v'), 0x00000000 };
extern const void *const CardPrinterChecker_Draw_rodata_80312BA8[26] = {
    (void *)&CardTaskManager_RenderOverlay_rodata_803128CC,
    (void *)&lbl_803128E4,
    (void *)&CardTaskManager_RenderOverlay_rodata_803129B0,
    (void *)&lbl_803129CC,
    (void *)&CardTaskManager_RenderOverlay_rodata_803129E8,
    (void *)&lbl_80312A24,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312A50,
    (void *)&lbl_80312A68,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312A80,
    (void *)&lbl_80312A98,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312AA4,
    (void *)&lbl_80312AC8,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312AE4,
    (void *)&lbl_806D32A0,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312B10,
    (void *)&lbl_80312B30,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312B40,
    (void *)&lbl_80312AC8,
    (void *)&lbl_806D32A0,
    (void *)&lbl_80312B4C,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312B5C,
    (void *)&lbl_80312B74,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312B90,
    (void *)&lbl_806D32A0,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312B9C,
    (void *)&lbl_806D32A4
};
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C10[6] = { TEXT_WORD(0x83, 'J', 0x83, 0x81), TEXT_WORD(0x83, 0x89, 0x82, 0xC9), TEXT_WORD(0x88, 0xD9, 0x8F, 0xED), TEXT_WORD(0x82, 0xAA, 0x82, 0xA0), TEXT_WORD(0x82, 0xE8, 0x82, 0xDC), TEXT_WORD(0x82, 0xB7, 0, 0) };
extern const char lbl_80312C28[] = "CAMERA ERROR";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C38[6] = { TEXT_WORD(0x83, 'J', 0x83, 0x81), TEXT_WORD(0x83, 0x89, 0x82, 0xCD), TEXT_WORD(0x8E, 'g', 0x97, 'p'), TEXT_WORD(0x82, 0xC5, 0x82, 0xAB), TEXT_WORD(0x82, 0xDC, 0x82, 0xB9), TEXT_WORD(0x82, 0xF1, 0, 0) };
extern const char lbl_80312C50[] = "CAMERA DISABLED";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C60[14] = { TEXT_WORD(0x83, 'A', 0x83, 'C'), TEXT_WORD(0x83, 'e', 0x83, 0x80), TEXT_WORD(0x83, '{', 0x83, '^'), TEXT_WORD(0x83, 0x93, 0x82, 0xDC), TEXT_WORD(0x82, 0xBD, 0x82, 0xCD), TEXT_WORD(0x91, 0xCE, 0x90, 0xED), TEXT_WORD(0x83, 'L', 0x83, 0x83), TEXT_WORD(0x83, 0x93, 0x83, 'Z'), TEXT_WORD(0x83, 0x8B, 0x83, '{'), TEXT_WORD(0x83, '^', 0x83, 0x93), TEXT_WORD(0x82, 0xF0, 0x89, 0x9F), TEXT_WORD(0x82, 0xB5, 0x82, 0xC4), TEXT_WORD(0x89, 0xBA, 0x82, 0xB3), TEXT_WORD(0x82, 0xA2, 0, 0) };
extern const char lbl_80312C98[] = "Press Item button or Versus Cancel Button";
extern const void *const CameraChecker_Draw_rodata_80312CC4[64] = {
    (void *)0x43540000,
    (void *)0x43800000,
    (void *)&CardTaskManager_RenderOverlay_rodata_803128CC,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x42EE0000,
    (void *)0x43700000,
    (void *)&lbl_803128E4,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43700000,
    (void *)0x43960000,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312C10,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43820000,
    (void *)0x43960000,
    (void *)&lbl_80312C28,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43480000,
    (void *)0x43800000,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312C38,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43480000,
    (void *)0x43800000,
    (void *)&lbl_80312C50,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x42C80000,
    (void *)0x43B40000,
    (void *)&CardTaskManager_RenderOverlay_rodata_80312C60,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43040000,
    (void *)0x43B40000,
    (void *)&lbl_80312C98,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF
};
static const char lbl_80312DC4[] = "Device Check";
static const char lbl_80312DD4[] = "MK2100-1-NA-MPR0-A36";
#pragma force_active reset

C_REGION_END
#pragma cplusplus on
class CardTask {
public:
    virtual unsigned char IsDone(void);
    virtual void v0C(void);
    virtual void v10(void);
    virtual void Render(void);
    int kind;
};

#include "game/types/CardTaskEntry.h"

#include "game/types/CardTaskManager.h"

struct CardTaskDesc {
    int id;
    const char *text;
};

extern "C" {
extern void TexMgr_DrawText_Format_Variant2(int layer, float x, float y, const char *fmt, ...);
extern void fn_8011F994(int layer);

extern const char lbl_806D32CC[5]; /* spinner chars */
extern const char lbl_806D32DC[3]; /* "%c" */
extern const char lbl_806D32E0[6];
extern const char lbl_806D32EC[3]; /* "%s" */
extern const float lbl_806D32D4;
extern const float lbl_806D32D8;
extern const float lbl_806D32E8;
extern const float lbl_806D32F0;
extern float lbl_806D32F4;
extern CardTaskDesc g_cardTaskFactories[];

void CardTaskManager_RenderOverlay(CardTaskManager *m);
}

#pragma exceptions on
#pragma use_lmw_stmw on
void CardTaskManager_RenderOverlay(CardTaskManager *m) {
    if (m->current < m->count) {
        CardTask *t = m->entries[m->current].task;
        if (t != 0) {
            TexMgr_DrawText_Format_Variant2(1, lbl_806D32D4, lbl_806D32D8, lbl_806D32DC,
                                            lbl_806D32CC[(m->frame >> 4) % 4U]);
            if (t->IsDone() == 1) {
                t->Render();
                for (int i = 0; i < 8; i++) {
                    fn_8011F994(7 - i);
                }
                return;
            }
        }
    }

    for (int i = 0; i < m->count; i++) {
        CardTaskEntry *e = &m->entries[i];
        CardTask *t = e->task;
        const char *desc = g_cardTaskFactories[e->desc].text;
        const char *name = lbl_8031285C[t->kind];
        if (i > m->current) {
            name = lbl_806D32E0;
        }
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32E8, 0x3C + i * 0x26, lbl_806D32EC, desc);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F0, 0x3C + i * 0x26, lbl_806D32EC, name);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32F4, lbl_80312DC4);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32D8, lbl_80312DD4);
        if (i == m->current) {
            t->Render();
        }
        for (int j = 0; j < 8; j++) {
            fn_8011F994(j);
        }
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma cplusplus reset
