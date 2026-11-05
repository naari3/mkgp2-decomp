#include "game/Sci2CardScoreReceiptPrivate.h"

static inline void *Receipt_TitleTracker(void)
{
    void *tracker = lbl_806D10A0;
    if (tracker != 0) return tracker;
    return 0;
}

static inline const char *Receipt_RankText(unsigned char flag, unsigned char mode, int rank)
{
    int offset = 8;
    if (mode == 0) offset = 0;
    if (flag == 0) return lbl_806D35E8;
    return Sci2Card_GetReceiptStringEntry(offset + rank);
}

int Sci2Card_BuildScoreReceiptLine(int line)
{
    char output[0x1400];
    char row[0x200];
    char scratch[0x200];
    int key7;
    int key8;
    char number[4];
    unsigned char final = 0;
    unsigned char highlight = 0;
    void *card = Sci2Card_Singleton_Get();
    if (line < 0) {
        if (lbl_806D1225 == 0) Sci2Card_SendCmdLedSet(card, 12, 1);
        return line + 1;
    }
    memset(output, 0, sizeof(output));
    switch (line) {
    case 0:
        memset(row, 0, sizeof(row));
        sprintf(output, lbl_80317DB0[line].format, &g_playerData);
        if (lbl_806D123C == line) highlight = 1;
        strcat(output, lbl_806D35BC);
        line++;
        break;
    case 1:
        memset(row, 0, sizeof(row));
        sprintf(scratch, lbl_806D35C0);
        {
            const char *text;
            if (isJapanese() == 0) text = Sci2Card_GetReceiptStringEntry(22);
            else text = Sci2Card_GetReceiptStringEntry(23);
            sprintf(row, lbl_80317DB0[line].format, text, scratch);
        }
        if (lbl_806D123C == line) highlight = 1;
        strcat(output, row);
        strcat(output, lbl_806D35C4);
        line++;
        break;
    case 2:
        memset(row, 0, sizeof(row));
        if (lbl_806D123C == line) highlight = 1;
        {
            const char *title;
            if (g_playerData.hasTitle == 0) title = lbl_806D35E4;
            else title = lbl_806CF0F0[isJapanese()];
            sprintf(row, lbl_80317DB0[line].format, title);
        }
        strcat(output, row);
        strcat(output, lbl_806D35BC);
        line++;
        /* fall through */
    case 3:
        memset(row, 0, sizeof(row));
        if (lbl_806D123C == line) highlight = 1;
        sprintf(row, lbl_80317DB0[line].format, GetCoinMilage(&g_playerData));
        strcat(output, row);
        strcat(output, lbl_806D35BC);
        line++;
        /* fall through */
    case 4:
        if (g_playerData.wins != 0) {
            char *numberCursor;
            int wins;
            const char *digits;
            const char *label;
            const char *suffix;
            int i;
            memset(row, 0, sizeof(row));
            label = isJapanese() == 0 ? lbl_80318108 : lbl_806D35C8;
            wins = g_playerData.wins;
            memset(lbl_806D1230, 0, 7);
            sprintf(number, lbl_806D35D0, wins > 999 ? 999 : wins);
            numberCursor = number;
            for (i = 0; i < 3; i++, numberCursor++) {
                if (*numberCursor != ' ') strcat(lbl_806D1230, lbl_803FFDF0[*numberCursor - '0']);
                else strcat(lbl_806D1230, lbl_806D35D4);
            }
            digits = lbl_806D1230;
            suffix = isJapanese() == 0 ? lbl_806D35D8 : lbl_806D35DC;
            sprintf(row, lbl_80317DB0[line].format, label, digits, suffix);
            if (lbl_806D123C == line) highlight = 1;
            strcat(output, row);
            strcat(output, lbl_806D35BC);
        } else strcat(output, lbl_806D35BC);
        line++;
        break;
    case 5:
        memset(row, 0, sizeof(row));
        if (lbl_806D123C == line) highlight = 1;
        {
            void *title = Receipt_TitleTracker();
            const char *text;
            if (title == 0) text = lbl_806D35E4;
            else text = get_title_name_global(title);
            sprintf(row, lbl_80317DB0[line].format, text);
        }
        strcat(output, row);
        strcat(output, lbl_806D35BC);
        line++;
        /* fall through */
    case 6:
        memset(row, 0, sizeof(row));
        if (lbl_806D123C == line) highlight = 1;
        sprintf(row, lbl_80317DB0[line].format, Sci2Card_BuildItemGetReceiptLine());
        strcat(output, row);
        strcat(output, lbl_806D35C4);
        line++;
        break;
    case 7:
        memset(row, 0, sizeof(row));
        {
            unsigned char mode;
            unsigned char ranks[8];
            const char *a;
            const char *b;
            const char *c;
            const char *d;
            int i;
            key7 = 0;
            mode = 0;
            for (i = 0; i < 8; i++) ranks[i] = 0;
            Sci2Card_PopulateRankRowByMode(&key7, ranks, &mode);
            a = Receipt_RankText(ranks[6], mode, 6);
            b = Receipt_RankText(ranks[0], mode, 0);
            c = Receipt_RankText(ranks[7], mode, 7);
            d = Receipt_RankText(ranks[1], mode, 1);
            sprintf(row, lbl_80317DB0[line].format, Sci2Card_GetReceiptStringEntry(key7 * 2 + 16), a, b, c, d);
        }
        if (lbl_806D123C == line) highlight = 1;
        strcat(output, row);
        strcat(output, lbl_806D35BC);
        line++;
        break;
    case 8:
        memset(row, 0, sizeof(row));
        {
            unsigned char mode;
            unsigned char ranks[8];
            const char *a;
            const char *b;
            const char *c;
            const char *d;
            int i;
            key8 = 0;
            mode = 0;
            for (i = 0; i < 8; i++) ranks[i] = 0;
            Sci2Card_PopulateRankRowByMode(&key8, ranks, &mode);
            a = Receipt_RankText(ranks[2], mode, 2);
            b = Receipt_RankText(ranks[3], mode, 3);
            c = Receipt_RankText(ranks[4], mode, 4);
            d = Receipt_RankText(ranks[5], mode, 5);
            sprintf(row, lbl_80317DB0[line].format, Sci2Card_GetReceiptStringEntry(key8 * 2 + 17), a, b, c, d);
        }
        if (lbl_806D123C == line) highlight = 1;
        strcat(output, row);
        strcat(output, lbl_806D35BC);
        line++;
        break;
    case 9:
        final = 1;
        if (lbl_806D1225 == 0) {
            ScoreReceiptPlayer *player;
            char *record;
            memset(row, 0, sizeof(row));
            if (lbl_806D123C == line) highlight = 1;
            player = &g_playerData;
            fn_8018CC64();
            record = fn_8018B2E4();
            if (record == 0) {
                fn_8018B31C(player, player->character, player->kart, player->ccClass,
                    player->cup, player->longRound, player->reverse, GetCoinMilage(player),
                    player->b19B, player->b19C, player->b1B1, 0, player->raceTime / lbl_806D35F0);
                record = fn_8018B300();
            }
            if (record != 0) {
                sprintf(row, lbl_806D3580, record);
                strcat(output, row);
            }
            line++;
        } else line++;
        break;
    default:
        return line;
    }
    Sci2Card_SendCmdRegister(card, output, (unsigned char)(lbl_80317DB0[line - 1].line + 1), final, highlight);
    return line;
}
