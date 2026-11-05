#include "game/SpriteVoicePrivate.h"
extern signed char lbl_806D1775, lbl_806D1776, lbl_806D1777;
extern int lbl_806D1778;
extern unsigned int g_voiceTickCounter;
extern unsigned char g_bgmStateId;
void fn_801A32BC(void) {
    SpriteVoiceRaceEntry *current;
    g_bgmStateId = 0;
    current = &g_raceEntryArray[lbl_806D1775];
    if (lbl_806D1776 != -1) {
        if (lbl_806D1777 != 0 && current->player == 0) {
            SpriteVoice_Push(SpriteVoice_Select(current->character, current->id), 11, 1, 1);
            if (g_voiceTickCounter % 2 == 0) SpriteVoice_Push(0x1D0, 11, 1, 1);
            else SpriteVoice_Push(0x1D1, 11, 1, 1);
        } else if (lbl_806D1777 == 1 && current->player == 1 && current->distance > lbl_806D1778) {
            SpriteVoice_Push(SpriteVoice_Select(current->character, current->id), 11, 1, 1);
            if (g_voiceTickCounter % 2 == 0) SpriteVoice_Push(0x1D2, 11, 1, 1);
            else SpriteVoice_Push(0x1D3, 11, 1, 1);
        } else if (lbl_806D1777 >= 2 && current->player < g_raceEntryArray[lbl_806D1776].player) {
            if (g_voiceTickCounter % 4 == 0) {
                SpriteVoice_Push(SpriteVoice_Select(current->character, current->id), 11, 1, 1);
                SpriteVoice_Push(0x1E2, 11, 1, 1);
            } else if (g_voiceTickCounter % 4 == 1) {
                SpriteVoice_Push(SpriteVoice_Select(current->character, current->id), 11, 1, 1);
                SpriteVoice_Push(0x1D1, 11, 1, 1);
            } else if (g_voiceTickCounter % 4 == 2) {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1776].character,
                    g_raceEntryArray[lbl_806D1776].id), 11, 1, 1);
                SpriteVoice_Push(0x1E3, 11, 1, 1);
            } else {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1776].character,
                    g_raceEntryArray[lbl_806D1776].id), 11, 1, 1);
                SpriteVoice_Push(0x1E4, 11, 1, 1);
            }
        }
    }
}
