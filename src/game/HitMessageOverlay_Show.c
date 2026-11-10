/* HitMessageOverlay_Show (0x800ABF58): starts the "hit" message overlay
 * when attacker `src` hits `dst`. Picks the voice/message line for the
 * attacker's character (or the generic line 6), plays the hit SE and
 * fades the two overlay layers in. Returns 1 if the overlay was shown. */

typedef struct HitKart {
    unsigned char pad0[0x1F4];
    int lineSet;
    int character;
    unsigned char pad1FC[0x2D0 - 0x1FC];
    unsigned char state;
} HitKart;

#include "game/types/LineTable.h"

extern const float lbl_806D4E90; /* 0.0 */
extern const float lbl_806D4E94; /* 1.0 */
extern const float lbl_806D4E98; /* 140.0 */
extern unsigned char HitMessageOverlay_bss_806D1478;
extern int HitMessageOverlay_Show_rodata_80328B98[];
extern LineTable HitMessageOverlay_Show_rodata_80328BD0;
extern int g_gameMode;
extern unsigned char g_namCamFlag;
extern int HitMessageOverlay_data_806CF274;
extern int HitMessageOverlay_data_806CF278;
extern int HitMessageOverlay_bss_806D147C;
extern int HitMessageOverlay_bss_806D1480;
extern float HitMessageOverlay_bss_806D1484;
extern float HitMessageOverlay_bss_806D1488;
extern void *HitMessageOverlay_bss_806D148C;
extern void *HitMessageOverlay_bss_806D1490;
extern int HitMessageOverlay_bss_806D1494;
extern int HitMessageOverlay_bss_806D1498;
extern int SoundMgr_PlaySE(int se);
extern int fn_80231BD4(int set, int character, int alt);
extern int fn_80231B94(int set);
extern unsigned char fn_80231B74(int line);
extern unsigned char fn_80231644(int *outVoice, int *outLine, int *outExtra, int set, int character);
extern void fn_8020A734(void *layer, int mode, float from, float to);

int HitMessageOverlay_Show(HitKart *src, HitKart *dst, unsigned char playSe)
{
    int line;
    LineTable voices;
    int set;

    if (src == 0 || dst == 0) {
        return 0;
    }
    if (HitMessageOverlay_bss_806D1478 == 0) {
        return 0;
    }
    if (dst->state == 0) {
        return 0;
    }
    if (src->state == 1) {
        return 0;
    }
    if (playSe == 1) {
        SoundMgr_PlaySE(HitMessageOverlay_Show_rodata_80328B98[src->character]);
    }
    line = -1;
    voices = HitMessageOverlay_Show_rodata_80328BD0;
    set = src->lineSet;
    if (g_gameMode == 0) {
        if (set != 6 && g_namCamFlag == 1) {
            line = fn_80231BD4(set, src->character, 1);
            HitMessageOverlay_data_806CF278 = voices.lines[set];
            HitMessageOverlay_bss_806D1494 = fn_80231B94(set);
            HitMessageOverlay_bss_806D1498 = (fn_80231B74(line) == 1) + 1;
        } else {
            line = fn_80231BD4(6, src->character, 1);
            HitMessageOverlay_data_806CF278 = -1;
            HitMessageOverlay_bss_806D1494 = -1;
            HitMessageOverlay_bss_806D1498 = 0;
        }
    }
    if (g_gameMode == 2) {
        if (set != 6) {
            if (fn_80231644(&HitMessageOverlay_data_806CF278, &line, &HitMessageOverlay_bss_806D1494, set, src->character) == 0) {
                line = fn_80231BD4(6, src->character, 0);
                HitMessageOverlay_bss_806D1494 = fn_80231B94(src->lineSet);
                HitMessageOverlay_bss_806D1498 = 0;
            } else {
                HitMessageOverlay_bss_806D1498 = (fn_80231B74(line) == 1) + 1;
            }
        } else {
            line = fn_80231BD4(6, src->character, 1);
            HitMessageOverlay_data_806CF278 = -1;
            HitMessageOverlay_bss_806D1494 = -1;
            HitMessageOverlay_bss_806D1498 = 0;
        }
    }
    HitMessageOverlay_data_806CF274 = line;
    HitMessageOverlay_bss_806D147C = 0;
    HitMessageOverlay_bss_806D1480 = 0;
    HitMessageOverlay_bss_806D1484 = lbl_806D4E90;
    HitMessageOverlay_bss_806D1488 = lbl_806D4E94;
    fn_8020A734(HitMessageOverlay_bss_806D148C, 0x10, lbl_806D4E98, lbl_806D4E90);
    fn_8020A734(HitMessageOverlay_bss_806D1490, 0xA, lbl_806D4E90, lbl_806D4E94);
    return 1;
}
