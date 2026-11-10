/*
 * MemoryManager_TimedFreeIfActive and CardPrinterChecker_StartCleaningJob,
 * 0x8008F504..0x8008F5A4.
 */

#include "game/types/CardPrinterStatePtr.h"

#include "game/types/CardPrinterChecker.h"

extern CardPrinterStatePtr CardPrinterChecker_StartCleaningJob_data_803FE8D8; /* State_CardResetWait */
extern const char lbl_803134B0[]; /* "exec cleaning\n" */

void DebugPrintf(const char *fmt, ...);
void MemoryManager_TimedFree(void *p);
unsigned char card_send_cleaning_cmd_init(void);

#pragma exceptions on

void *MemoryManager_TimedFreeIfActive(void *p, short flag)
{
    if (p != 0 && flag > 0) {
        MemoryManager_TimedFree(p);
    }
    return p;
}

void CardPrinterChecker_StartCleaningJob(CardPrinterChecker *self)
{
    DebugPrintf(lbl_803134B0);
    self->state = CardPrinterChecker_StartCleaningJob_data_803FE8D8;
    self->stage = 2;
    card_send_cleaning_cmd_init();
}

#pragma exceptions reset
