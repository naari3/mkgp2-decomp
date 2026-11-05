#include "game/Sci2CardRetryReceipt.h"

int Sci2Card_BuildRetryReceiptLine(int line)
{
    char output[0x1400];
    char scratch[0x200];
    char number[4];
    /* Original rodata pool: formats at +0x468 and localized strings at +0x7B4. */
    const unsigned char *pool = lbl_80317948;
    unsigned char finish = 0;
    unsigned char update = 0;
    void *card = Sci2Card_Singleton_Get();
#define FORMAT (((const RetryReceiptFormat *)(pool + 0x468))[line].format)
#define MARK() if (lbl_806D123C == line) update = 1
#define CLEAR() memset(scratch, 0, 0x200)
#define APPEND() strcat(output, scratch)
#define NEWLINE() strcat(output, lbl_806D35BC)
    if (line < 0) {
        if (lbl_806D1225 == 0) Sci2Card_SendCmdLedSet(card, 12, 1);
        return line + 1;
    }
    memset(output, 0, 0x1400);
    switch (line) {
    case 0:
        CLEAR();
        sprintf(output, FORMAT, pool + 0x7B4);
        MARK();
        NEWLINE();
        ++line;
        break;
    case 1: {
        const char *text;
        CLEAR();
        if (!isJapanese()) text = Sci2Card_GetReceiptStringEntry(22);
        else text = Sci2Card_GetReceiptStringEntry(23);
        sprintf(scratch, FORMAT, text, lbl_806D35C0);
        MARK();
        APPEND();
        strcat(output, lbl_806D35C4);
        ++line;
        break;
    }
    case 2:
        CLEAR();
        MARK();
        sprintf(scratch, FORMAT, lbl_806CF0F0[isJapanese()]);
        APPEND();
        NEWLINE();
        ++line;
    case 3:
        CLEAR();
        MARK();
        sprintf(scratch, FORMAT, 99999);
        APPEND();
        NEWLINE();
        ++line;
    case 4: {
        const char *label;
        char *digits;
        const char *suffix;
        const char **table;
        int i;
        char *cursor;
        CLEAR();
        label = lbl_806D35C8;
        if (!isJapanese()) label = (const char *)pool + 0x7C0;
        memset(lbl_806D1230, 0, 7);
        sprintf(number, lbl_806D35D0, 999);
        cursor = number;
        table = lbl_803FFDF0;
        for (i = 0; i < 3; ++i, ++cursor) {
            if (*cursor != ' ') strcat(lbl_806D1230, table[*cursor - '0']);
            else strcat(lbl_806D1230, lbl_806D35D4);
        }
        digits = lbl_806D1230;
        suffix = lbl_806D35DC;
        if (!isJapanese()) suffix = lbl_806D35D8;
        sprintf(scratch, FORMAT, label, digits, suffix);
        MARK();
        APPEND();
        NEWLINE();
        ++line;
        break;
    }
    case 5:
        CLEAR();
        MARK();
        sprintf(scratch, FORMAT, pool + 0x7CC);
        APPEND();
        NEWLINE();
        ++line;
    case 6:
        CLEAR();
        MARK();
        sprintf(scratch, FORMAT, pool + 0x7D8);
        APPEND();
        strcat(output, lbl_806D35C4);
        ++line;
        break;
    case 7: {
        const char *a, *b, *c, *d;
        CLEAR();
        a = Sci2Card_GetReceiptStringEntry(6);
        b = Sci2Card_GetReceiptStringEntry(0);
        c = Sci2Card_GetReceiptStringEntry(7);
        d = Sci2Card_GetReceiptStringEntry(1);
        sprintf(scratch, FORMAT, Sci2Card_GetReceiptStringEntry(18), a, b, c, d);
        MARK();
        APPEND();
        NEWLINE();
        ++line;
        break;
    }
    case 8: {
        const char *a, *b, *c, *d;
        CLEAR();
        a = Sci2Card_GetReceiptStringEntry(2);
        b = Sci2Card_GetReceiptStringEntry(3);
        c = Sci2Card_GetReceiptStringEntry(4);
        d = Sci2Card_GetReceiptStringEntry(5);
        sprintf(scratch, FORMAT, Sci2Card_GetReceiptStringEntry(19), a, b, c, d);
        MARK();
        APPEND();
        NEWLINE();
        ++line;
        break;
    }
    case 9: {
        finish = 1;
        CLEAR();
        MARK();
        scratch[0] = 'A';
        scratch[1] = 'A';
        scratch[2] = 'A';
        scratch[3] = 'A';
        scratch[4] = 'A';
        scratch[5] = 'A';
        scratch[6] = 'A';
        scratch[7] = 'A';
        scratch[8] = 'A';
        scratch[9] = 'A';
        scratch[10] = 'A';
        scratch[11] = 'A';
        scratch[12] = 'A';
        scratch[13] = 'A';
        scratch[14] = 'A';
        scratch[15] = 'A';
        scratch[16] = 'A';
        scratch[17] = 'A';
        scratch[18] = 'A';
        scratch[19] = 'A';
        scratch[20] = 'A';
        scratch[21] = 'A';
        scratch[22] = 'A';
        scratch[23] = 'A';
        scratch[24] = 'A';
        scratch[25] = 0;
        APPEND();
        ++line;
        break;
    }
    default: return line;
    }
    Sci2Card_SendCmdRegister(card, output,
        (unsigned char)(((const RetryReceiptFormat *)(pool + 0x468))[line - 1].rows + 1),
        finish, update);
    return line;
}
