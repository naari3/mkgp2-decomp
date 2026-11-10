/* TaRecord_InsertResult @ 0x80074C30: insert a finished time into the
 * current course's best-time list and, for a top-10 time, its name record. */
typedef unsigned short wchar;

#include "game/types/HiScoreName.h"

#include "game/types/BackupHiScores.h"

extern int g_ccClass;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int TaRecord_bss_806D112C; /* last inserted rank */
extern BackupHiScores lbl_80598A60;

#pragma exceptions on
int TaRecord_InsertResult(wchar *name, unsigned char e0, unsigned char e1, unsigned char e2, unsigned char kart, float time)
{
    int cc = g_ccClass;
    int cls = cc - 1;
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int reverse = g_reverseRoundFlag;
    int i;
    HiScoreName *names;
    float *times;
    int j;
    int k;
    int n;

    TaRecord_bss_806D112C = -1;
    if (cc == 0) return -1;
    if (cls < 0 || cls >= 2) return -1;
    if (cup < 0 || cup >= 9) return -1;
    if (longRound < 0 || longRound >= 2) return -1;
    if (reverse < 0 || reverse >= 2) return -1;

    names = lbl_80598A60.names[cls][cup][longRound][reverse];
    times = lbl_80598A60.times[cls][cup][longRound][reverse];
    for (i = 0; i < 50; i++) {
        if (time < times[i]) {
            TaRecord_bss_806D112C = i;
            break;
        }
    }
    if (TaRecord_bss_806D112C >= 0) {
        for (j = 49; j > TaRecord_bss_806D112C; j--) {
            times[j] = times[j - 1];
        }
        times[TaRecord_bss_806D112C] = time;
        if (TaRecord_bss_806D112C < 10) {
            for (k = 9; k > TaRecord_bss_806D112C; k--) {
                for (n = 0; n < 6; n++) {
                    names[k].name[n] = names[k - 1].name[n];
                }
                names[k].kart = names[k - 1].kart;
                names[k].extra[0] = names[k - 1].extra[0];
                names[k].extra[1] = names[k - 1].extra[1];
                names[k].extra[2] = names[k - 1].extra[2];
            }
            for (n = 0; n < 6; n++) {
                names[TaRecord_bss_806D112C].name[n] = name[n];
            }
            names[TaRecord_bss_806D112C].kart = kart;
            names[TaRecord_bss_806D112C].extra[0] = e0;
            names[TaRecord_bss_806D112C].extra[1] = e1;
            names[TaRecord_bss_806D112C].extra[2] = e2;
        }
    }
    return TaRecord_bss_806D112C;
}
#pragma exceptions reset
