#include "game/types/nsWakeup.h"
#include "game/types/text_word.h"
extern "C" {

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

}
extern "C" {
extern const char lbl_80312DEC[] = "time out error\n";
extern const char lbl_80312DFC[] = "data recive error. retry %d\n";
extern const char lbl_80312E1C[] = "trans extend font to card printer\n";
extern const char CardTaskPrintJob_StepNoCardPrinter_rodata_80312E40[92] = {
    110, 111, 32, 117, 115, 101, 100, 32, 99, 97, 114, 100,
    32, 112, 114, 105, 110, 116, 101, 114, 10, 0, 0, 0,
    99, 97, 114, 100, 32, 112, 114, 105, 110, 116, 101, 114,
    32, 110, 111, 32, 101, 120, 101, 99, 10, 0, 0, 0,
    116, 114, 97, 110, 115, 102, 101, 114, 32, 116, 105, 109,
    101, 32, 105, 115, 32, 37, 102, 10, 0, 0, 0, 0,
    99, 97, 114, 100, 32, 114, 101, 109, 97, 105, 110, 32,
    99, 104, 101, 99, 107, 10, 0, 0
};
extern const char CardPrinterChecker_State_WaitStatus_rodata_80312E9C[88] = {
    119, 97, 105, 116, 32, 115, 116, 97, 116, 117, 115, 10,
    0, 0, 0, 0, 115, 101, 116, 117, 112, 32, 99, 108,
    101, 97, 110, 105, 110, 103, 10, 0, 99, 108, 101, 97,
    110, 105, 110, 103, 32, 115, 101, 108, 101, 99, 116, 10,
    0, 0, 0, 0, 99, 97, 114, 100, 32, 101, 106, 101,
    99, 116, 10, 0, 114, 101, 109, 97, 105, 110, 32, 99,
    97, 114, 100, 32, 106, 111, 98, 32, 101, 110, 100, 32,
    10, 0, 0, 0
};
extern const char lbl_80312EF4[] = "exec cleaning\n";
extern const char lbl_80312F04[] = "cleaning error\n";
extern const char lbl_80312F14[] = "error exec mode %d\n";
}
struct CardTaskEntry { clInterface *task; int desc; };
#include "game/types/CardTaskManager.h"
struct CardTaskDesc { clInterface *(*create)(); const char *text; };
extern "C" { extern CardTaskDesc g_cardTaskFactories[]; void fn_8011F994(int); extern const char lbl_806D32CC[5],lbl_806D32DC[3],lbl_806D32E0[6]; extern const float lbl_806D32D4,lbl_806D32D8,lbl_806D32E8,lbl_806D32F0; extern float lbl_806D32F4; }
static inline int CardCleaningError(PrintObject *self,unsigned char *table) {
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardCallback(table,0x23C); self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
static inline int CardSelectCleaning(PrintObject *self,unsigned char *table,const char *messages) {
    DebugPrintf(messages+0x65C);
    unsigned char needsCleaning=0;
    if (isJapanese()==0) {
        if (lbl_80598A60.cleaningCount>=100) needsCleaning=1;
    } else if (Backup_GetMinutesSinceBoot(0xA8)==1) needsCleaning=1;
    if (!needsCleaning) { self->step=CardCallback(table,0x26C); return 2; }
    DebugPrintf(messages+0x66C);
    self->step=CardCallback(table,0x278); self->result=5;
    return 1;
}
static inline void AddTask(CardTaskManager *self, clInterface *task, int kind)
{
    self->entries[self->count].task = task;
    self->entries[self->count].desc = kind;
    self->count++;
}
static inline void Initialize(CardTaskManager *self)
{
    self->count = 0;
    self->entries = (CardTaskEntry *)FUN_8003b120(32);
    self->entries[0].task = 0;
    self->entries[1].task = 0;
    self->entries[2].task = 0;
    self->entries[3].task = 0;
}

/* fakematch: uncalled diagnostic member preserves the observed pooled
 * class descriptions and setup messages, following clLineManager::PrintLines. */
void nsWakeup::clInterface::PrintClassNames() {
    DebugPrintf("nsWakeup::clCameraChecker");
    DebugPrintf("nsWakeup::clInterface");
    DebugPrintf("namcam check\n");
    DebugPrintf("nsWakeup::clCardPrinterChecker");
    DebugPrintf("init card printer\n");
    DebugPrintf("get status\n");
    DebugPrintf("nsWakeup::clButtonChecker");
    DebugPrintf("nsWakeup::clSteerChecker");
}
#pragma use_lmw_stmw on
extern "C" void CardTaskManager_RenderOverlay(CardTaskManager *m) {
    if (m->current < m->count) {
        clInterface *t = m->entries[m->current].task;
        if (t != 0) {
            TexMgr_DrawText_Format_Variant2(1, lbl_806D32D4, lbl_806D32D8, lbl_806D32DC,
                                            lbl_806D32CC[(m->frame >> 4) % 4U]);
            if (t->Ready() == 1) {
                t->Draw();
                for (int i = 0; i < 8; i++) {
                    fn_8011F994(7 - i);
                }
                return;
            }
        }
    }

    for (int i = 0; i < m->count; i++) {
        CardTaskEntry *e = &m->entries[i];
        clInterface *t = e->task;
        const char *desc = g_cardTaskFactories[e->desc].text;
        const char *name = lbl_8031285C[t->state];
        if (i > m->current) {
            name = lbl_806D32E0;
        }
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32E8, 0x3C + i * 0x26, lbl_806D32EC, desc);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F0, 0x3C + i * 0x26, lbl_806D32EC, name);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32F4, lbl_80312DC4);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32D8, lbl_80312DD4);
        if (i == m->current) {
            t->Draw();
        }
        for (int j = 0; j < 8; j++) {
            fn_8011F994(j);
        }
    }
}
#pragma use_lmw_stmw reset
void nsWakeup::clInterface::Draw() {}
unsigned char nsWakeup::clInterface::Ready() { return 0; }
extern "C" int CardTaskManager_Tick(CardTaskManager *self)
{
    int state;
    clInterface *task;

    self->frame++;
    if (self->current >= self->count) {
        self->linger--;
        return self->linger <= 0 ? 0 : 2;
    }
    task = self->entries[self->current].task;
    task->state = task->Tick();
    state = task->state;
    if (state == 2 || state == 4 || state == 5) {
        task->After();
        ServiceButtonExtra_Set(0);
        if (state == 5) {
            return 3;
        }
        self->current++;
        if (self->current < self->count) {
            self->entries[self->current].task->Init();
        }
    }
    return 2;
}
void nsWakeup::clInterface::Init() {}
void nsWakeup::clInterface::After() {}
namespace ManagerABI {
extern "C" CardTaskManager *DestroyCardTaskManager(CardTaskManager *self, short flag)
{
    int i;

    if (self != 0) {
        if (self->entries != 0) {
            for (i = 0; i < self->count; i++) {
                delete self->entries[i].task;
            }
        }
        MemoryManager_Free(self->entries);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
}
nsWakeup::clInterface::~clInterface() {}
extern "C" CardTaskManager *card_task_manager_create(CardTaskManager *self,
    unsigned char welcome, unsigned char card, unsigned char other)
{
    self->entries = 0;
    self->count = 0;
    self->current = 0;
    self->frame = 0;
    self->linger = 60;
    Initialize(self);
    if (welcome == 1) AddTask(self, g_cardTaskFactories[0].create(), 0);
    AddTask(self, g_cardTaskFactories[1].create(), 1);
    if (card == 1) AddTask(self, g_cardTaskFactories[2].create(), 2);
    if (other == 1) AddTask(self, g_cardTaskFactories[3].create(), 3);
    self->entries[self->current].task->Init();
    return self;
}
extern "C" WelcomeObject *CardTaskWelcome_New() { return new WelcomeObject; }
extern "C" int CardTaskWelcome_StepStatus(WelcomeObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    switch (int status = StrPcb_TimerTick(StrPcb_GetInstance())) {
    case 0: return 1;
    case 1: self->step = CardCallback(table,0x14C); self->result = 0; return 2;
    case 2: self->step = CardCallback(table,0x158); self->result = 2; return 3;
    default:
        DebugPrintf(lbl_80312F14, status);
        self->step = CardCallback(table,0x164); self->result = 3; return 3;
    }
}
extern "C" int CardTaskWelcome_StepCommCheck(WelcomeObject *self) {
    void *pcb = StrPcb_GetInstance();
    StrPcb_GetErrorCodeString(pcb);
    if (StrPcb_HasError(pcb) == 1 || StrPcb_GetCommErrorFlag(pcb) == 1) {
        self->step = CardTaskWelcome_StepCommCheck_data_803FE5C0; self->result = 2; return 3;
    }
    return 2;
}
extern "C" int CardTaskWelcome_StepInputCheck(WelcomeObject *) {
    InputMgr_GetPlayer(GetInputManager(), 0);
    return 3;
}
extern "C" void CardTaskWelcome_DrawStatus(WelcomeObject *) {
    CardDrawWelcome(0x80);
    void *pcb = StrPcb_GetInstance();
    if (!StrPcb_GetCommErrorFlag(pcb)) {
        CardDrawWelcome(0xC0);
        const char *error = StrPcb_GetErrorCodeString(pcb);
        TexMgr_DrawText_Format_Variant2(0, 308.0f, 296.0f, lbl_806D3338,
            error[0], error[1], error[2]);
    } else CardDrawWelcome(0x100);
    CardDrawFrame();
}
nsWakeup::clSteerChecker::~clSteerChecker() {}
unsigned char nsWakeup::clSteerChecker::Ready() {
    WelcomeObject *self=this;

    if (self->result == 2 || self->result == 3) return 1;
    return 0;
}
void nsWakeup::clSteerChecker::Init() {
    WelcomeObject *self=this;

    self->state = 1; self->step = CardTaskWelcome_StateInit_data_803FE5F0;
    self->result = 1; self->counter = 0;
    StrPcb_BeginTimedNeutral(StrPcb_GetInstance());
}
int nsWakeup::clSteerChecker::Tick() {
    WelcomeObject *self=this;

    ++self->counter;
    return PMF_CALL(self, self->step)();
}
void nsWakeup::clSteerChecker::After() {
}
void nsWakeup::clSteerChecker::Draw() {
    WelcomeObject *self=this;

    switch (self->result) {
    case 1:
        if ((self->counter & 31) < 24) CardDrawWelcome(0x40);
        break;
    case 2:
        CardDrawWelcome(0x80);
        {
            void *pcb = StrPcb_GetInstance();
            if (!StrPcb_GetCommErrorFlag(pcb)) {
                CardDrawWelcome(0xC0);
                const char *error = StrPcb_GetErrorCodeString(pcb);
                TexMgr_DrawText_Format_Variant2(0,308.0f,296.0f,lbl_806D3338,
                    error[0],error[1],error[2]);
            } else CardDrawWelcome(0x100);
            CardDrawFrame();
        }
        break;
    case 3: CardDrawWelcome(0); break;
    }
    if (self->result != 1) {
        ResCtrl rc;
        rc.mode=2;
        rc.width=540.0f; rc.height=380.0f;
        rc.Show(320.0f,240.0f,1.0f);
        rc.SetColor(0xFFFFFF7F);
        fn_8011FAFC(&rc,7);
    }
}
extern "C" WaitInputObject *CardTaskWaitInput_New() { return new WaitInputObject; }
nsWakeup::clButtonChecker::~clButtonChecker() {}
void nsWakeup::clButtonChecker::Init() {
    WaitInputObject *self=this;

    self->polling=1; self->button2000=0; self->button400=0; self->delay=60;
}
int nsWakeup::clButtonChecker::Tick() {
    WaitInputObject *self=this;

    if (self->delay != 0) { --self->delay; return 1; }
    if (self->polling) {
        ServiceInput *input = InputMgr_GetPlayer(GetInputManager(),0);
        if (lbl_80598A60.button2000 && input->Pressed(0x2000)==1) self->button2000=1;
        if (lbl_80598A60.button400 && input->Pressed(0x400)==1) self->button400=1;
        self->polling=0;
    }
    if (self->button2000) return 3;
    return (self->button400 != 0) + 2;
}
void nsWakeup::clButtonChecker::After() {
}
void nsWakeup::clButtonChecker::Draw() {
    WaitInputObject *self=this;

    if (self->button2000) {
        CardDrawWait(0x0);
        CardDrawWait(0x40);
    } else if (self->button400) {
        CardDrawWait(0x0);
        CardDrawWait(0x80);
    }
}
extern "C" PrintObject *CardTaskPrintJob_New() { return new PrintObject; }
extern "C" int CardTaskPrintJob_StepStart(PrintObject *self) {
    void *card = Sci2Card_Singleton_Get();
    if (!Sci2Card_IsIdleOrExhausted(card)) return 1;
    if (Sci2Card_IsStatusOkNonTerm(card)==1) {
        DebugPrintf(lbl_80312E1C);
        self->step=CardTaskPrintJob_StepStart_data_803FE758;
        self->started=OSGetTick();
        CardPrintJob_KickFontTransfer();
        return 1;
    }
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardTaskChecks_data_803FE6BC; self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
extern "C" int CardTaskPrintJob_StepNoCardPrinter(PrintObject *) {
    DebugPrintf(CardTaskPrintJob_StepNoCardPrinter_rodata_80312E40); return 4;
}
extern "C" int CardTaskPrintJob_StepWaitFontTransfer(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!CardPrintJob_TickFontTransfer(Sci2Card_Singleton_Get())) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) {
        DebugPrintf(messages+0x608);
        self->error=Sci2Card_ClassifyStatusToCode();
        self->step=CardCallback(table,0x23C); self->result=1;
        ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
        return 3;
    }
    DebugPrintf(messages+0x620, (float)CardMicroseconds(OSGetTick()-self->started)/1000000.0f);
    self->step=CardCallback(table,0x2B4);
    DebugPrintf(messages+0x638);
    if (!Sci2Card_BeginSpace()) self->step=CardCallback(table,0x2C0);
    else self->step=CardCallback(table,0x2CC);
    return 1;
}
extern "C" int CardPrinterChecker_State_WaitStatus(PrintObject *self) {
    DebugPrintf(CardPrinterChecker_State_WaitStatus_rodata_80312E9C);
    if (!Sci2Card_BeginSpace()) self->step=CardPrinterChecker_State_WaitStatus_data_803FE71C;
    else self->step=CardPrinterChecker_State_WaitStatus_data_803FE728;
    return 1;
}
extern "C" int CardPrinterChecker_State_SetupCleaning(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!Sci2Card_WaitPingStatus()) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) return CardCleaningError(self,table);
    if (!Sci2Card_GetByteFlag1224()) return CardSelectCleaning(self,table,messages);
    DebugPrintf(messages+0x680);
    self->step=CardCallback(table,0x290); self->result=4;
    card_eject_init(); return 1;
}
extern "C" int CardPrinterChecker_State_RemainCardJobEnd(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!card_eject_state_machine()) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) {
        if (Sci2Card_GetByteFlag1224()==1) { card_eject_init(); return 1; }
        return CardCleaningError(self,table);
    }
    DebugPrintf(messages+0x68C);
    return CardSelectCleaning(self,table,messages);
}
extern "C" int CardPrinterChecker_State_CleaningSelectInput(PrintObject *self) {
    ++self->frames;
    if (!self->selected) {
        ServiceInput *input=InputMgr_GetPlayer(GetInputManager(),0);
        if (input->Held(0x2000)==1) self->choice=0;
        else if (input->Held(0x400)==1) self->choice=1;
        if (self->choice!=-1) self->selected=1;
    }
    if (self->choice==0) {
        DebugPrintf(lbl_806D3328); self->step=CardPrinterChecker_State_CleaningSelectInput_data_803FE6D4; return 2;
    }
    if (self->choice==1) {
        DebugPrintf(lbl_80312EF4);
        self->step=CardPrinterChecker_State_CleaningSelectInput_data_803FE6E0; self->result=6;
        card_send_cleaning_cmd_init();
        CardPrinterChecker_StartCleaningJob(self->job.p);
    }
    return 1;
}
extern "C" int CardPrinterChecker_State_ExecCleaning(PrintObject *self) {
    if (!CardTaskPrintJob_IsRunning_Thunk(self->job.p)) return 1;
    if (CardTaskPrintJob_IsSuccess(self->job.p)==1) return 2;
    DebugPrintf(lbl_80312F04);
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardTaskChecks_data_803FE6BC; self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
extern "C" int fn_8008B668(CardTaskObject *self) { return self->state; }
extern "C" int CardPrinterChecker_State_WaitHandle(PrintObject *self) {
    if (!InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)) return 3;
    self->step=CardPrinterChecker_State_WaitHandle_data_803FE6C8; self->result=2;
    return 3;
}
extern "C" int CardPrinterChecker_ReadCleaningChoice(PrintObject *) {
    return InputMgr_GetPlayer(GetInputManager(),0)->Held(0x2400) == 0 ? 3 : 4;
}
nsWakeup::clCardPrinterChecker::~clCardPrinterChecker() {}
void nsWakeup::clCardPrinterChecker::Init() {
    PrintObject *self=this;

    if (!ServiceEnable_Get()) { self->step=CardPrinterChecker_State_InitPrinter_data_803FE764; }
    else {
        void *card=Sci2Card_Singleton_Get();
        DebugPrintf("init card printer\n"); DebugPrintf("get status\n");
        self->step=CardPrinterChecker_State_InitPrinter_data_803FE770;
        Sci2Card_SendCmdRetry(card,0);
    }
}
int nsWakeup::clCardPrinterChecker::Tick() {
    PrintObject *self=this;
 return PMF_CALL(self, self->step)(); }
void nsWakeup::clCardPrinterChecker::Draw() {
    PrintObject *self=this;

    switch (self->result) {
    case 1:
        if (isJapanese()==0) {
            const char *text=(const char *)CardPrinterChecker_Draw_rodata_80312BA8[isJapanese()];
            TexMgr_DrawText_Format_Variant2(1,212.0f,256.0f,lbl_806D32EC,text);
        } else {
            const char *text=(const char *)CardPrinterChecker_Draw_rodata_80312BA8[isJapanese()];
            TexMgr_DrawText_Format_Variant2(1,119.0f,240.0f,lbl_806D32EC,text);
        }
        CardPrinterChecker_DrawStatusErrorLabel(self->error);
        break;
    case 2: {
        const char *text=(const char *)CardPrinterChecker_Draw_rodata_80312BA8[2+isJapanese()];
        TexMgr_DrawText_Format_Variant2(1,float(164-(isJapanese()==1 ? 40:0)),256.0f,lbl_806D32EC,text);
        TexMgr_DrawText_Format_Variant2(0,136.0f,296.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[4+isJapanese()]);
        break;
    }
    case 3: {
        const char *text=(const char *)CardPrinterChecker_Draw_rodata_80312BA8[6+isJapanese()];
        TexMgr_DrawText_Format_Variant2(1,float(200-(isJapanese()==1 ? 50:0)),256.0f,lbl_806D32EC,text);
        break;
    }
    case 4: {
        TexMgr_DrawText_Format_Variant2(1,212.0f,256.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[8+isJapanese()]);
        ResCtrl rc;
        rc.resId=0x735; rc.Show(320.0f,348.0f,1.0f);
        fn_8011FAFC(&rc,0);
        break;
    }
    case 5: {
        TexMgr_DrawText_Format_Variant2(0,152.0f,184.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[12+isJapanese()]);
        if (isJapanese()==0) {
            TexMgr_DrawText_Format_Variant2(1,128.0f,142.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[10+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,288.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[14+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,304.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[16+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,320.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[18+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,392.0f,288.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[20+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,392.0f,304.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[22+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,152.0f,256.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[24+isJapanese()]);
        } else {
            TexMgr_DrawText_Format_Variant2(1,110.0f,158.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[10+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,57.0f,256.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[14+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,72.0f,288.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[16+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,72.0f,304.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[18+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,350.0f,288.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[20+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,360.0f,304.0f,lbl_806D32EC,(const char *)CardPrinterChecker_Draw_rodata_80312BA8[22+isJapanese()]);
        }
        CardDrawLeftChoice(self);
        { ResCtrl right;
        right.resId=0x896+(self->frames>>4)%4;
        right.Show(self->rightX,self->y,1.0f);
        fn_8011FAFC(&right,0); }
        break;
    }
    case 6: CardPrinterChecker_DrawErrorOverlay(self->job.p); break;
    }
    if (self->Ready()==1) CardDrawFrame();
}
unsigned char nsWakeup::clCardPrinterChecker::Ready() {
    PrintObject *self=this;
 return self->result!=0; }
extern "C" CameraObject *CameraChecker_Alloc() {
    return new CameraObject;
}
extern "C" int CameraChecker_State_Entry(CameraObject *self) {
    --self->countdown;
    if (StrPcb_IsInErrorState(StrPcb_GetInstance())==1 || self->countdown<0) {
        self->step=CameraChecker_State_Entry_data_803FE7C4;
        self->retries=3; self->timeout=300;
        NamCam_Init();
    }
    return 1;
}
extern "C" int fn_8008C034() { return 4; }
extern "C" int CameraChecker_State_DownloadWait(CameraObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    if (self->timeout-- < 0) {
        self->step=CardCallback(table,0x320); self->result=1;
        ServiceLatchAux97_Set(1); VBlankValue_Set(1);
        DebugPrintf(lbl_80312DEC); ServiceButtonExtra_Set(1);
        return 3;
    }
    char imageInfo[0x10];
    void *handle;
    if (NamCam_GetImageHandle(&handle,0)==0) return 1;
    self->timeout=300;
    void *buffer=FUN_8003b120(0x4B000);
    unsigned int loaded=NamCam_LoadImage(handle,buffer,imageInfo)!=0;
    MemoryManager_Free(buffer);
    if (!loaded) {
        DebugPrintf(lbl_80312DFC,--self->retries);
        if (self->retries<=0) { self->step=CardCallback(table,0x32C); return 1; }
    }
    self->step=CardCallback(table,0x338); return 2;
}
extern "C" int CameraChecker_State_WaitButton1000(CameraObject *self) {
    if (InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)==1) {
        self->result=2; self->step=CameraChecker_State_WaitButton1000_data_803FE794; VBlankEnable_Set(0);
    }
    return 3;
}
extern "C" int CameraChecker_State_WaitButton2400(CameraObject *self) {
    if (!InputMgr_GetPlayer(GetInputManager(),0)->Held(0x2400)) return 3;
    DebugPrintf(lbl_806D3310);
    self->result=0; self->step=CameraChecker_State_WaitButton2400_data_803FE788; return 3;
}
extern "C" int CameraChecker_State_ShutdownTick(CameraObject *self) {
    if (NamCam_TickShutdownCountdown()==0) return self->state;
    self->step=CameraChecker_State_ShutdownTick_data_803FE77C; return 4;
}
extern "C" int fn_8008C320(CameraObject *self) { return self->state; }
nsWakeup::clCameraChecker::~clCameraChecker() {}
unsigned char nsWakeup::clCameraChecker::Ready() {
    CameraObject *self=this;
 return self->result!=0; }
void nsWakeup::clCameraChecker::Init() {
    CameraObject *self=this;

    if (!GetVBlankFlag()) self->step=CameraChecker_State_WaitVBlank_data_803FE7D0;
    else { DebugPrintf("namcam check\n"); self->step=CameraChecker_State_WaitVBlank_data_803FE7DC; }
}
int nsWakeup::clCameraChecker::Tick() {
    CameraObject *self=this;

    CardFrameTimer timer;
    timer.started=OSGetTick();
    int result=PMF_CALL(self, self->step)();
    unsigned char slow=(float)CardMicroseconds(OSGetTick()-timer.started)/1000000.0f >= 1.0f ? 1 : 0;
    if (slow==1) StrPcb_DrainInputBuffer(StrPcb_GetInstance());
    return result;
}
void nsWakeup::clCameraChecker::After() {
 NamCam_End(); }
void nsWakeup::clCameraChecker::Draw() {
    CameraObject *self=this;

    switch (self->result) {
    case 1:
        CardDrawCamera(0x0);
        CardDrawCamera(0x40);
        break;
    case 2:
        CardDrawCamera(0x40);
        CardDrawCamera(0x80);
        CardDrawCamera(0xc0);
        break;
    }
    if (self->Ready()==1) CardDrawFrame();
}
#pragma use_lmw_stmw on
extern "C" void TexMgr_DrawText_Format(float x, float y, int font,
    int r, int g, int b, int a, const char *format, ...) {
    CardStackText text;
    char buffer[0x200];
    va_list args;
    text.font=font; text.color=(r<<24)|(g<<16)|(b<<8)|a;
    fn_801F93EC((TextManager *)&text,x,y);
    int enabled=OSDisableInterrupts();
    va_start(args,format); vsprintf(buffer,format,args); va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture((TextManager *)&text,buffer);
    fn_801F8A34(fn_801F8E58(),(TextManager *)&text,0);
}
#pragma use_lmw_stmw reset
extern "C" void TexMgr_DrawText_Format_Variant2(int font,float x,float y,const char *format,...) {
    CardStackText text;
    char buffer[0x200];
    va_list args;
    text.font=font; text.color=0xFFFFFFFF;
    fn_801F93EC((TextManager *)&text,x,y);
    int enabled=OSDisableInterrupts();
    va_start(args,format); vsprintf(buffer,format,args); va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture((TextManager *)&text,buffer);
    fn_801F8A34(fn_801F8E58(),(TextManager *)&text,0);
}