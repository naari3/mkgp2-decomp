/* Card reader data repair test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWReprintPagePrivate.h"

/* Player record (g_playerData layout); the grouped words are copied as
 * nested blocks. Packed tail words at +1BA..+1CE are not aligned to four. */
struct RepairWords3 {
    unsigned int w[3];
};
struct RepairWords16 {
    unsigned int w[16];
};
#pragma options align=packed
struct RepairPackedWords {
    unsigned int w[6];
};
#pragma options align=reset

struct RepairPlayerData {
    RepairWords3 head;
    unsigned char byte00C, byte00D;
    unsigned short half00E, half010;
    unsigned int word014;
    unsigned char byte018, byte019, byte01A;
    unsigned int word01C, word020, word024;
    RepairWords16 words028;
    RepairWords16 words068;
    unsigned char bytes0A8[0x79];
    unsigned char bytes121[0x69];
    RepairWords3 words18C;
    unsigned char byte198, byte199, byte19A, byte19B, byte19C;
    unsigned char byte19D, byte19E, byte19F, byte1A0;
    unsigned int word1A4;
    unsigned char byte1A8;
    unsigned int word1AC;
    unsigned char byte1B0, byte1B1;
    unsigned int word1B4;
    unsigned char byte1B8, byte1B9;
    RepairPackedWords words1BA;
    unsigned int word1D4;
    unsigned char byte1D8, byte1D9, byte1DA;
};
typedef char CheckRepairPlayerSize[sizeof(RepairPlayerData) == 0x1DC ? 1 : -1];

/* Backup record at self+0x274; the player block mirrors g_playerData. */
struct RepairBackup {
    unsigned char pad000[0x64];
    unsigned char captured;
    unsigned char pad065[7];
    int minute;  /* +6C */
    int hour;    /* +70 */
    int day;     /* +74 */
    int month;   /* +78 */
    int year;    /* +7C */
    unsigned char pad080[0x10];
    RepairPlayerData player; /* +90 */
};

extern "C" {
extern MenuItem lbl_803FCC60[];
extern ReprintStep lbl_803FDD38[];
extern RepairPlayerData g_playerData;
extern char lbl_806D2DBC[8]; /* "NO DATA" */
}

static inline RepairBackup *Repair_GetBackup(ReprintPage *self)
{
    return *(RepairBackup **)((char *)self + 0x274);
}

extern "C" int CardRW_DataRepair_Page(ReprintPage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->tick = 0;
        self->error = 1;
        self->failed = 0;
    }
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->step == 0) {
            if (self->error == 1 && input->Pressed(0x800)) {
                self->blink = 31;
                if (++self->selection > 1) self->selection = 0;
            }
            if (input->Pressed(0x1000)) {
                if (self->selection == 0) {
                    if (Repair_GetBackup(self)->captured == 1) {
                        self->selection = 100;
                        self->step = 1;
                        self->blink = 0;
                        self->tick = lbl_803FDD38[self->step].tick;
                        self->error = 1;
                        self->failed = 0;
                        g_playerData = Repair_GetBackup(self)->player;
                        self->error = Reprint_CheckError();
                        if (self->error != 1) {
                            self->failed = 1;
                            self->step = 6;
                            self->blink = 31;
                            self->tick = lbl_803FDD38[self->step].tick;
                        }
                    } else {
                        self->step = 100;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 6);
                }
            }
        } else if (self->step >= 100) {
            if (++self->step >= 280) {
                self->next = 5;
                CardRW_TestTopMenu_Page(self, 0, 6);
            }
        } else {
            if (self->tick != 0) {
                if (self->tick() == 1) {
                    if (!self->failed && lbl_803FDD38[self->step].checkError) {
                        self->error = Sci2Card_GetPrintErrorCode();
                        if (CardRW_ErrorDisplay(self, 0, 1, 0)) {
                            self->step = 6;
                            self->failed = 1;
                        }
                    }
                    if (self->step == 2 && !Sci2Card_GetByteFlag1224()) {
                        self->step = 0;
                        self->failed = 0;
                    }
                    ++self->step;
                    self->tick = lbl_803FDD38[self->step].tick;
                }
                if (self->failed && Reprint_HasFatalError(self)) self->blink = 31;
            } else {
                unsigned char leave = 1;
                if (CardRW_ErrorDisplay(self, 0, 1, 0) && !input->Pressed(0x1000)) leave = 0;
                if (!Reprint_HasFatalError(self) || leave) {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 6);
                }
            }
        }
    }
    if (phase == 2) {
        Reprint_DrawItems(self, lbl_803FCC60, self->selection + 4);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (self->text != 0) {
            RepairBackup *backup = Repair_GetBackup(self);
            if (backup->captured == 1) {
                DrawText(self->text, 252, 96, 7, 1.0f, strings + 0x2148, backup->year,
                         backup->month + 1, backup->day, backup->hour, backup->minute);
            } else if (self->blink <= 30) {
                DrawText(self->text, 252, 96, 7, 1.0f, lbl_806D2DBC);
            }
            if (!CardRW_ErrorDisplay(self, 1, 1, 0)) {
                if (self->step >= 100) {
                    if (self->blink <= 30)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2164);
                    if (self->blink <= 30)
                        DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2184);
                } else {
                    switch (self->step) {
                    case 1: case 2:
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x21a0);
                        if (self->blink <= 30)
                            DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2038);
                        break;
                    case 3: case 4: case 5: case 6:
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x21bc);
                        if (self->blink <= 30)
                            DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2064);
                        break;
                    case 7: case 8:
                        if (self->error == 1)
                            DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x21d4);
                        if (self->blink <= 30)
                            DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x1c58);
                        break;
                    }
                }
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
