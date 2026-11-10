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
extern const unsigned int data_803FE480_rodata_80312874[4] = { 0x975C917A, 0x82B582C8, 0x82A297E1, 0x8A4F0000 };
extern const char lbl_80312884[] = "Program error";
extern const unsigned int data_803FE480_rodata_80312894[9] = { 0x836E8393, 0x8368838B, 0x82C98EE8, 0x82F09047, 0x82EA82C8, 0x82A282C5, 0x82AD82BE, 0x82B382A2, 0x00000000 };
extern const char lbl_803128B8[] = "Do not touch wheel";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803128CC[6] = { 0x8C5788F5, 0x82F08CC4, 0x82F182C5, 0x82AD82BE, 0x82B382A2, 0x00000000 };
extern const char lbl_803128E4[] = "Please call an attendant";
extern const unsigned int data_803FE480_rodata_80312900[7] = { 0x836E8393, 0x8368838B, 0x82C988D9, 0x8FED82AA, 0x82A082E8, 0x82DC82B7, 0x00000000 };
extern const char lbl_8031291C[] = "Wheel error";
extern const char lbl_80312928[] = "JVS I/O ERROR";
extern const unsigned int data_803FE480_rodata_80312938[8] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382C9, 0x88D98FED, 0x82AA82A0, 0x82E882DC, 0x82B70000 };
extern const char lbl_80312958[] = "Item button Error";
extern const unsigned int data_803FE480_rodata_8031296C[10] = { 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82C988D9, 0x8FED82AA, 0x82A082E8, 0x82DC82B7, 0x00000000 };
extern const char lbl_80312994[] = "Versus Cancel button Error";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803129B0[7] = { 0x834A815B, 0x83685281, 0x5E5782CD, 0x8E679770, 0x82C582AB, 0x82DC82B9, 0x82F10000 };
extern const char lbl_803129CC[] = "Card R/W is out of order";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_803129E8[15] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382DC, 0x82BD82CD, 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82F0899F, 0x82B582C4, 0x82AD82BE, 0x82B382A2, 0x00000000 };
extern const char lbl_80312A24[] = "Press Item button or Versus Cancel button";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312A50[6] = { 0x834A815B, 0x836882AA, 0x95A582A2, 0x8F6F82B3, 0x82EA82DC, 0x82B70000 };
extern const char lbl_80312A68[] = "Card will be ejected";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312A80[6] = { 0x834A815B, 0x836882F0, 0x82A88EE6, 0x82E882AD, 0x82BE82B3, 0x82A20000 };
extern const char lbl_80312A98[] = "Take card";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312AA4[9] = { 0x834A815B, 0x83685281, 0x5E5782CC, 0x834E838A, 0x815B836A, 0x8393834F, 0x8E9E8AFA, 0x82C582B7, 0x00000000 };
extern const char lbl_80312AC8[] = "Please clean the card R/W";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312AE4[11] = { 0x834A815B, 0x83685281, 0x5E5782CC, 0x834E838A, 0x815B836A, 0x8393834F, 0x82F08EC0, 0x8D7382B5, 0x82C482AD, 0x82BE82B3, 0x82A20000 };
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B10[8] = { 0x8B4E93AE, 0x8CE382C9, 0x834A815B, 0x8368834E, 0x838A815B, 0x836A8393, 0x834F82F0, 0x00000000 };
extern const char lbl_80312B30[] = "          Skip";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B40[3] = { 0x82B582C4, 0x89BA82B3, 0x82A20000 };
extern const char lbl_80312B4C[] = "when activating";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B5C[6] = { 0x834A815B, 0x8368834E, 0x838A815B, 0x836A8393, 0x834F82F0, 0x00000000 };
extern const char lbl_80312B74[] = "Card R/W will be cleaned";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B90[3] = { 0x8EC08D73, 0x82B582DC, 0x82B70000 };
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312B9C[3] = { 0x8358834C, 0x83628376, 0x00000000 };
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
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C10[6] = { 0x834A8381, 0x838982C9, 0x88D98FED, 0x82AA82A0, 0x82E882DC, 0x82B70000 };
extern const char lbl_80312C28[] = "CAMERA ERROR";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C38[6] = { 0x834A8381, 0x838982CD, 0x8E679770, 0x82C582AB, 0x82DC82B9, 0x82F10000 };
extern const char lbl_80312C50[] = "CAMERA DISABLED";
extern const unsigned int CardTaskManager_RenderOverlay_rodata_80312C60[14] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382DC, 0x82BD82CD, 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82F0899F, 0x82B582C4, 0x89BA82B3, 0x82A20000 };
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
