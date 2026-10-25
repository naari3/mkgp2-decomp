/*
 * CardPrinterChecker state handlers and error overlay, 0x8008F07C..0x8008F4CC.
 * The checker keeps its current state as a C++ pointer-to-member at +0x0.
 */

typedef struct CardPrinterStatePtr {
    int thisDelta;
    int vtblOffset;
    void *func;
} CardPrinterStatePtr;

typedef struct CardPrinterChecker {
    CardPrinterStatePtr state; /* 0x00 */
    int stage; /* 0x0C */
    int errorCode; /* 0x10 */
} CardPrinterChecker;

extern CardPrinterStatePtr lbl_803FE8E4; /* State_CleaningWait */
extern CardPrinterStatePtr lbl_803FE8F0; /* State_CardEjectWait */
extern CardPrinterStatePtr lbl_803FE8FC; /* done */
extern CardPrinterStatePtr lbl_803FE908; /* failed */

extern unsigned char lbl_80598A60[];

void DebugPrintf(const char *fmt, ...);
int isJapanese(void);
void TexMgr_DrawText_Format_Variant3(int mode, const char *fmt, float x, float y, ...);

unsigned char card_eject_state_machine(void);
unsigned char card_cleaning_state_machine(void);
unsigned char card_eject_init(void);
unsigned char card_send_cleaning_cmd_init(void);
int Sci2Card_GetPrintErrorCode(void);
unsigned char Sci2Card_GetByteFlag1224(void);
int Sci2Card_ClassifyStatusToCode(void);
unsigned char Sci2Card_WaitCleaningComplete(void);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_IsIdleOrExhausted(void *card);
unsigned char Sci2Card_IsStatusOkNonTerm(void *card);
void Sci2Card_BeginReset(void);
unsigned char Sci2Card_GetResponseStatus(void *card, unsigned char *s1, unsigned char *s2, unsigned char *s3);
void CardPrinterChecker_DrawResponseStatusBytes(unsigned char s1, unsigned char s2, unsigned char s3);
int Backup_PublishShadowCopy_Inline(void);

/* Never emitted; its literal puts the overlay title first in the string pool. */
static void CardPrinterChecker_PoolTitle(void)
{
    DebugPrintf("CLEANING START");
}

#pragma exceptions on

int CardPrinterChecker_State_CardEjectWait(CardPrinterChecker *self)
{
    if (!card_eject_state_machine()) {
        return 0;
    }
    if (Sci2Card_GetPrintErrorCode() != 1) {
        if (Sci2Card_GetByteFlag1224() == 1) {
            card_eject_init();
            return 0;
        }
        self->state = lbl_803FE908;
        self->stage = 0;
        self->errorCode = Sci2Card_ClassifyStatusToCode();
        return 1;
    }
    DebugPrintf("ccard eject ok\n");
    self->state = lbl_803FE8FC;
    self->stage = 0;
    return 1;
}

int CardPrinterChecker_State_CleaningWait(CardPrinterChecker *self)
{
    void *card;

    if (!Sci2Card_WaitCleaningComplete()) {
        return 0;
    }
    card = Sci2Card_Singleton_Get();
    if (!Sci2Card_IsIdleOrExhausted(card)) {
        return 0;
    }
    if (Sci2Card_IsStatusOkNonTerm(card) == 1) {
        DebugPrintf("cleaning ok\n");
        self->state = lbl_803FE8F0;
        card_eject_init();
        self->stage = 4;
        *(int *)(lbl_80598A60 + 0x26C) = 0;
        Backup_PublishShadowCopy_Inline();
        return 0;
    }
    DebugPrintf("cleaning error\n");
    self->state = lbl_803FE908;
    self->stage = 0;
    self->errorCode = Sci2Card_ClassifyStatusToCode();
    return 1;
}

int CardPrinterChecker_State_CardResetWait(CardPrinterChecker *self)
{
    int code;

    if (!card_cleaning_state_machine()) {
        return 0;
    }
    code = Sci2Card_GetPrintErrorCode();
    if (code != 1) {
        if (code == 6) {
            card_send_cleaning_cmd_init();
            return 0;
        }
        self->state = lbl_803FE908;
        self->stage = 0;
        self->errorCode = Sci2Card_ClassifyStatusToCode();
        return 1;
    }
    self->state = lbl_803FE8E4;
    self->stage = 3;
    Sci2Card_BeginReset();
    return 0;
}

void CardPrinterChecker_DrawErrorOverlay(CardPrinterChecker *self)
{
    unsigned char s3;
    unsigned char s2;
    unsigned char s1;

    Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &s1, &s2, &s3);
    CardPrinterChecker_DrawResponseStatusBytes(s1, s2, s3);
    TexMgr_DrawText_Format_Variant3(1, "CLEANING START", 236 - (isJapanese() == 1 ? 40 : 0), 28.0f);

    switch (self->stage) {
    case 2:
        TexMgr_DrawText_Format_Variant3(0, "STARTING CARD R/W CLEANING", 180.0f, 184.0f);
        TexMgr_DrawText_Format_Variant3(0, "PLASE INSERT CLEANING CARD", (isJapanese() == 1 ? 16 : 0) + 164, 216.0f);
        break;
    case 3:
        TexMgr_DrawText_Format_Variant3(0, "NOW CLEANING", 260.0f, 184.0f);
        TexMgr_DrawText_Format_Variant3(0, "PLEASE WAIT A MOMENT", 206.0f, 216.0f);
        break;
    case 4:
        TexMgr_DrawText_Format_Variant3(0, "CLEANING COMPLETE", 218.0f, 184.0f);
        TexMgr_DrawText_Format_Variant3(0, "PLEASE REMOVE CLEANING CARD", 176.0f, 216.0f);
        break;
    }
}

#pragma exceptions reset
